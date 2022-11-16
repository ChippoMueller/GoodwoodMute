#ifndef BYPASS_H
#define BYPASS_H

#include <Arduino.h>
#include <Goodwood.h>
#include <EEPROM.h>
#include <Led.h>
#include <RelaySwitch.h>

class Bypass {
  public:
  void Init(void);
  void ToggleState(void);
  void WriteState(bool value);
  void writeOutputs(uint8_t value);

  private:
  RelaySwitch _relay = RelaySwitch(RELAY_PIN);
  Led _led = Led(LED_PIN);
  uint8_t _state = 1;                       // the master state variable
};

#endif