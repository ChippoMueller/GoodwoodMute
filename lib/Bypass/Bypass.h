#ifndef BYPASS_H
#define BYPASS_H

#include <Arduino.h>
#include <Goodwood.h>
#include <EEPROM.h>
#include <Led.h>
#include <RelaySwitch.h>

class Bypass {
  public:
  void Bypassed(void);
  void Active(void);
  void writeOutputs(void);

  private:
  RelaySwitch _relay = RelaySwitch(RELAY_PIN);
  Led _led = Led(LED_PIN);
  bool _state = 0;                       // the master state variable
};

#endif