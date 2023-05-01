#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

Bounce toggle = Bounce();
Bounce rmt = Bounce();

Bypass bypass;

void setup() {
  
//  #ifdef __DEBUG__
//      Serial.begin(9600);
//  #endif 
  pinMode(FTSWA_PIN, INPUT_PULLUP);
  toggle.attach(FTSWA_PIN);
  toggle.interval(40);

  pinMode(FTSWB_PIN, INPUT_PULLUP);
  rmt.attach(FTSWB_PIN);
  rmt.interval(40);

  bypass.Init();

}

void loop(){

  toggle.update();            // poll inputs every loop
  rmt.update();

  if (toggle.read() == LOW) {
    bypass.Live();
    if (rmt.read() == HIGH) {
    bypass.DryLive();
  } else {
    bypass.DryMute();
  }
  } else {
    bypass.Mute();
  }
}

