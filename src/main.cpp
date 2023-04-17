#include <Arduino.h>
#include <Bounce2.h>
#include <EEPROM.h>

 #define __DEBUG__   // comment out when not using Uno

// define the input and output pins
const int buttonPin = 8; // the pin for the tap tempo button
const int ledPin = 7; // the pin for the LED indicator
const int outputPin = 6; // the pin for the output signal

// define variables for tap tempo
unsigned long lastTapTime = 0; // the time of the last tap
unsigned long tapInterval = 0; // the time between taps
bool isTapping = false; // whether the user is currently tapping
int tapCount = 0; // the number of taps

// define variables for output signal
unsigned long lastOutputTime = 0; // the time of the last output signal
unsigned long outputInterval = 0; // the time between output signals

Bounce ftsw = Bounce();

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(outputPin, OUTPUT);

  
  #ifdef __DEBUG__
      Serial.begin(9600);
  #endif 

  pinMode(buttonPin, INPUT_PULLUP);
  ftsw.attach(buttonPin);
  ftsw.interval(40);
}

void loop(){

  // read the state of the button
  int buttonState = digitalRead(buttonPin);

  // check if the button is pressed
  if (buttonState == LOW) {
    if (!isTapping) {
      // if this is the first tap, start the tap tempo
      isTapping = true;
      tapCount = 1;
      digitalWrite(ledPin, HIGH);
      lastTapTime = millis();
    } else {
      // if this is not the first tap, calculate the tap tempo
      unsigned long tapTime = millis();
      tapInterval = tapTime - lastTapTime;
      lastTapTime = tapTime;
      tapCount++;


      // update the LED to indicate the number of taps
      if (tapCount == 1) {
//        digitalWrite(ledPin, HIGH);
      } else if (tapCount == 2) {
//        digitalWrite(ledPin, HIGH);
//        delay(50);
//       digitalWrite(ledPin, LOW);
//        delay(50);
//        digitalWrite(ledPin, HIGH);
      } else if (tapCount == 3) {
//        digitalWrite(ledPin, HIGH);
//        delay(50);
//        digitalWrite(ledPin, LOW);
//        delay(50);
//        digitalWrite(ledPin, HIGH);
//        delay(50);
//        digitalWrite(ledPin, LOW);
//        delay(50);
//        digitalWrite(ledPin, HIGH);
      } else {
//        digitalWrite(ledPin, HIGH);
//        delay(50);
//        digitalWrite(ledPin, LOW);
      }
    }
  } else if (isTapping) {
    // if the button is released, stop the tap tempo and start the output signal
    isTapping = false;
    digitalWrite(ledPin, LOW);

    // calculate the output interval based on the tap tempo
    outputInterval = tapInterval / 2;

    // output the signal
    unsigned long outputTime = millis();
    if ((outputTime - lastOutputTime) >= outputInterval) {
      digitalWrite(ledPin, HIGH);
      delayMicroseconds(1);
      digitalWrite(ledPin, LOW);
      lastOutputTime = outputTime;
    }
  }

      #ifdef __DEBUG__
          Serial.print("isTapping: "); Serial.println(isTapping);
      #endif
}