#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

Bounce ftsw = Bounce();

Bypass bypass;

void setup() {
  
  #ifdef __DEBUG__
      Serial.begin(9600);
  #endif 

  pinMode(FTSW_PIN, INPUT_PULLUP);
  ftsw.attach(FTSW_PIN);
  ftsw.interval(40);

  bypass.Init();

}

void loop(){

  ftsw.update();            // poll inputs every loop

  if (ftsw.fell()) {
    bypass.ToggleState();
  }
}

