#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

Bounce ftswa = Bounce();
Bounce ftswb = Bounce();

Bypass bypass;

void setup() {
  
//  #ifdef __DEBUG__
//      Serial.begin(9600);
//  #endif 
  pinMode(FTSWA_PIN, INPUT_PULLUP);
  ftswa.attach(FTSWA_PIN);
  ftswa.interval(40);

  pinMode(FTSWB_PIN, INPUT_PULLUP);
  ftswb.attach(FTSWB_PIN);
  ftswb.interval(40);

  bypass.Init();

}

void loop(){

  ftswa.update();            // poll inputs every loop
  ftswb.update();

  if (ftswa.fell()) {
    bypass.ToggleMasterState();
//    #ifdef __DEBUG__
//        Serial.println("footswitch a fell");
//    #endif
  }

  if (ftswb.fell()) {
    bypass.ToggleDryState();
//    #ifdef __DEBUG__
//        Serial.println("footswitch b fell");
//    #endif
  }
}

