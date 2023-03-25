#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>


Bounce ftsw = Bounce();

byte holdArray[1] = {    // declare the "holdArray"
  0,
};

Bypass bypass;

byte readButton(byte i, int retrigger, long holdDur);

void setup() {
  
  #ifdef __DEBUG__
      Serial.begin(9600);
  #endif 

  pinMode(FTSWA_PIN, INPUT_PULLUP);
  ftsw.attach(FTSWA_PIN);
  ftsw.interval(40);


  bypass.Init();
}

void loop(){

//  ftsw.update();            // poll inputs every loop
  byte bypassButton = readButton(0, 0, 2000); // sets up the bypassButton array (i, retrigger, 2000mS)

  if (bypassButton == 1) {                      // if the bypass button has been tapped
    bypass.ToggleMasterState();
  }

  if (bypassButton == 2) {                      // if the switch has been held for 2 seconds
    bypass.ToggleDryState();
  }

  bypass.policeLights();
}




byte readButton(byte i, int retrigger, long holdDur) {

  ftsw.update();                     //update debounced state

  byte buttonState = 0;                   // setup the "buttonState" variable
  

  if (holdDur == 0) {                     // if the switch has been held for 0mS
    if (ftsw.risingEdge()) {        // if the switch is let go

      buttonState = 1;                    // the buttonState is 1
    }
  }

  else if (ftsw.read() == LOW && holdArray[i] == 0 && ftsw.duration() > holdDur ) {   // if the switch has been held for more than 2000mS

    buttonState = 2;                     // the buttonState is 2

    if (retrigger > 0) {                 // if retrigger is longer that 0mS
      buttonState = 1;                   // the buttonState is 1
      ftsw.interval(retrigger);     // return the updated state of the button
    }

    else holdArray[i] = 1;               // holdArray[i] is 1     
  }

  else if (ftsw.risingEdge() && holdArray[i] == 0) {   // if the switch has been pressed but not held

    buttonState = 1;                    // write the button state to 1

  }

  if (ftsw.risingEdge() && holdArray[i] == 1) {    // if the switch has been pressed  and the hold array is 1

    buttonState = 3;                                    // the button state is 3

    holdArray[i] = 0;                                   // write the hold array low
  }

  return buttonState;                                   // the value is the button state
}