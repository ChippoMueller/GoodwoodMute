#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

Bounce ftswa = Bounce();

Bypass bypass;

void setup() {
  
//  #ifdef __DEBUG__
//      Serial.begin(9600);
//  #endif 
  pinMode(FTSW_PIN, INPUT_PULLUP);
  ftswa.attach(FTSW_PIN);
  ftswa.interval(40);

  bypass.Init();

}

void loop(){

  ftswa.update();            // poll inputs every loop

  if (ftswa.fell()) {
    bypass.ToggleState();
    #ifdef __DEBUG__
        Serial.println("footswitch a fell");
    #endif
  }
}

