#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

Bounce ftsw = Bounce();
Bounce toggle = Bounce();

Bypass bypass;

void setup() {
  
//  #ifdef __DEBUG__
//      Serial.begin(9600);
//  #endif 
  pinMode(FTSW_PIN, INPUT_PULLUP);
  ftsw.attach(FTSW_PIN);
  ftsw.interval(40);

  pinMode(TOGGLE_PIN, INPUT_PULLUP);
  toggle.attach(TOGGLE_PIN);
  toggle.interval(40);

  bypass.Init();

}

void loop(){

  ftsw.update();            // poll inputs every loop
  toggle.update();

  if (ftsw.fell()) {
    bypass.ToggleMuteState();
//    #ifdef __DEBUG__
//        Serial.println("footswitch a fell");
//    #endif
  }

  if (toggle.read() == 1) {
    bypass.Trails();
  } else {
    bypass.NoTrails();
  }
}

