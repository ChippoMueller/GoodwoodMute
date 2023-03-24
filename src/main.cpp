#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>


Bounce ftswa = Bounce();
Bounce button[1] = {
Bounce( ftswa, 25 ),  //setup debounce for first push button
};

byte holdArray[1] = {    // declare the "holdArray"
  0,
};

Bypass bypass;


void setup() {
  
//  #ifdef __DEBUG__
//      Serial.begin(9600);
//  #endif 
  pinMode(FTSWA_PIN, INPUT_PULLUP);
  ftswa.attach(FTSWA_PIN);
  ftswa.interval(40);


  bypass.Init();
}

void loop(){

  ftswa.update();            // poll inputs every loop
  if (ftswa.rose() && ftswa.previousDuration() <= shortPressTime){
//    bypass.ToggleMasterState();
  }

  if (ftswa.read() == LOW && ftswa.currentDuration() >= longPressTime)
//    bypass.ToggleDryState();
}


byte Bypass::readButton(byte i, int retrigger, long holdDur) {

  button[i].update();                     //update debounced state

  byte buttonState = 0;                   // setup the "buttonState" variable
  

  if (holdDur == 0) {                     // if the switch has been held for 0mS
    if (button[i].risingEdge()) {        // if the switch is let go

      buttonState = 1;                    // the buttonState is 1
    }
  }

  else if (button[i].read() == LOW && holdArray[i] == 0 && button[i].duration() > holdDur ) {   // if the switch has been held for more than 2000mS

    buttonState = 2;                     // the buttonState is 2

    if (retrigger > 0) {                 // if retrigger is longer that 0mS
      buttonState = 1;                   // the buttonState is 1
      button[i].rebounce(retrigger);     // return the updated state of the button
    }

    else holdArray[i] = 1;               // holdArray[i] is 1     
  }

  else if (button[i].risingEdge() && holdArray[i] == 0) {   // if the switch has been pressed but not held

    buttonState = 1;                    // write the button state to 1

  }

  if (button[i].risingEdge() && holdArray[i] == 1) {    // if the switch has been pressed  and the hold array is 1

    buttonState = 3;                                    // the button state is 3

    holdArray[i] = 0;                                   // write the hold array low
  }

  return buttonState;                                   // the value is the button state
}