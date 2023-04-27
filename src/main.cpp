#include <Bounce2.h>



/*
Filename: Interfacer_Sum_Code_.ino
Project name: Goodwood Audio Interfacer Code
Created by: Jon Ashley
First usable date: August 15, 2017.
Edited August 15, 2017.
Description: 

Chip: ATtiny44 Spencer Konde Core
Programmer USBTinyISP (ATtiny)
Clock: 1mHz internal
BOD Enabled 4.3V
*/

#include <EEPROM.h>

const int spst = 4;  // momentary switch
const int dryPin = 0;  // the mute relay pin
const int wetPin = 1;   // the sum relay pin
const int red = 9;  // the red LED pin
const int green = 8;  // the green LED pin
const int blue = 7; // the blue LED pin
//const int remote = ?;

boolean dryMuteState = 0;  // 0 = bypassed, 1 = engaged
boolean dryMixState = 0;
void tap();
void hold();
void muteDry(byte dryMute);
void mixDry(byte dryMix);

Bounce button[1] = {
  Bounce( spst, 25 ),  //setup debounce for first push button
};

byte holdArray[1] = {    // declare the "holdArray"
  0,
};

byte readButton(byte i, int retrigger, long holdDur) {

  button[i].update();                     //update debounced state

  byte buttonState = 0;                   // setup the "buttonState" variable
  

  if (holdDur == 0) {                     // if the switch has been held for 0mS
    if (button[i].rose()) {              // if the switch is let go

      buttonState = 1;                    // the buttonState is 1
    }
  }

  else if (button[i].read() == LOW && holdArray[i] == 0 && button[i].currentDuration() > holdDur ) {   // if the switch has been held for more than 2000mS

    buttonState = 2;                     // the buttonState is 2

    if (retrigger > 0) {                 // if retrigger is longer that 0mS
      buttonState = 1;                   // the buttonState is 1
      button[i].interval(retrigger);       // return the updated state of the button
    }

    else holdArray[i] = 1;               // holdArray[i] is 1     
  }

  else if (button[i].rose() && holdArray[i] == 0) {   // if the switch has been pressed but not held

    buttonState = 1;                    // write the button state to 1

  }

  if (button[i].rose() && holdArray[i] == 1) {    // if the switch has been pressed  and the hold array is 1

    buttonState = 3;                                    // the button state is 3

    holdArray[i] = 0;                                   // write the hold array low
  }

  return buttonState;                                   // the value is the button state
}


// the setup routine runs once when you press reset:
void setup() {

//   Configure inputs and outputs
  pinMode(spst, INPUT_PULLUP);
  pinMode(dryPin, OUTPUT);
  pinMode(wetPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

// Read the button once and then throw away the result
  byte fakeButton = readButton(0, 0, 500);      // added May 13, 2017

  
// Load last state upon from before power down
  dryMuteState = EEPROM.read(0);
  digitalWrite(dryPin, dryMuteState);
   
  dryMixState = EEPROM.read(1);
  digitalWrite(wetPin, dryMixState);

   if (digitalRead(spst) == LOW) {    // if the switch is held on powerup
   dryMuteState = !dryMuteState;            // flip the mute state
   EEPROM.write(0, dryMuteState);        // write the new mute state to EEPROM
  }

}

// the loop routine runs over and over again forever:
void loop() {

  if (dryMuteState == 1) {
    if (dryMixState == 1) {
      digitalWrite(red, 0);                             
      digitalWrite(green, 0);
      digitalWrite(blue, 1);
      digitalWrite(dryPin, 1);
      digitalWrite(wetPin, 1);
    } else {
      digitalWrite(red, 1);                             
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      digitalWrite(dryPin, 1);
      digitalWrite(wetPin, 1);
    }
  } else {
    if (dryMixState == 1) {
      digitalWrite(red, 0);                             // then all LEDs are off
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      digitalWrite(dryPin, 0);
      digitalWrite(wetPin, 0);
    } else {
      digitalWrite(red, 0);                             // then all LEDs are off
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      digitalWrite(dryPin, 0);
      digitalWrite(wetPin, 1);
    }
  }
/*
  if (dryMuteState == 0 && dryMixState == 0) {                               // if the pedal IS NOT muted
    digitalWrite(red, 0);                             // then all LEDs are off
    digitalWrite(green, 0);
    digitalWrite(blue, 0);
    digitalWrite(dryPin, 1);
    digitalWrite(wetPin, 1);
  }

  if (dryMuteState == 0 && dryMixState == 1) {                               // if the pedal IS NOT muted
    digitalWrite(red, 0);                             // then all LEDs are off
    digitalWrite(green, 0);
    digitalWrite(blue, 0);
    digitalWrite(dryPin, 1);
    digitalWrite(wetPin, 0);
  }

  if (dryMuteState == 1 && dryMixState == 0) {                               // if the pedal IS muted
    digitalWrite(red, 1);                             
    digitalWrite(green, 0);
    digitalWrite(blue, 0);
    digitalWrite(dryPin, 0);
    digitalWrite(wetPin, 0);
  }

  if (dryMuteState == 1 && dryMixState == 1) {                               // if the pedal IS muted
    digitalWrite(red, 0);                             
    digitalWrite(green, 0);
    digitalWrite(blue, 1);
    digitalWrite(dryPin, 0);
    digitalWrite(wetPin, 0);
  }
  */
  byte bypassButton = readButton(0, 0, 2000); // sets up the bypassButton array (i, retrigger, 2000mS)

  if (bypassButton == 1) {                      // if the bypass button has been tapped
    tap();
  }

  if (bypassButton == 2) {                      // if the switch has been held for 2 seconds
    hold();
  }

}

void muteDry(byte mute) {

  digitalWrite(dryPin, mute); 
  
}

void tap() {

    dryMuteState = !dryMuteState;
    muteDry(dryMuteState);
    
}

void hold() {

    dryMixState = !dryMixState;
    mixDry(dryMixState);
    EEPROM.write(1, dryMixState);

    if (dryMuteState == 0) {
      if (dryMixState == 1) {
        digitalWrite(red, 0);
        digitalWrite(green, 0);
        digitalWrite(blue, 1); 
        delay(50);
//        digitalWrite(red, 0);
//        digitalWrite(green, 0);
        digitalWrite(blue, 0);
        delay(50);
//        digitalWrite(red, 0);
//        digitalWrite(green, 0);
        digitalWrite(blue, 1);
        delay(50);
//        digitalWrite(red, 0);
//        digitalWrite(green, 0);
        digitalWrite(blue, 0);
      }
      else {
        digitalWrite(red, 1);
        digitalWrite(green, 0);
        digitalWrite(blue, 0); 
        delay(50);
        digitalWrite(red, 0);
//        digitalWrite(green, 0);
//        digitalWrite(blue, 0);
        delay(50);
        digitalWrite(red, 1);
//        digitalWrite(green, 0);
//        digitalWrite(blue, 0);
        delay(50);
        digitalWrite(red, 0);
//        digitalWrite(green, 0);
//        digitalWrite(blue, 0);
      }   
   }
}
  

void mixDry(byte mix) {
if (dryMixState == 0);{
  digitalWrite(wetPin, mix); 
}
}



