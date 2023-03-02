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
  void ToggleABState(void);
  void ToggleYState(void);
  void writeRelayOutputs(uint8_t value);
  void writeLedOutputs(uint8_t value);

  private:
  RelaySwitch _relayA = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayB = RelaySwitch(RELAYB_PIN);
  Led _ledA = Led(LEDA_PIN);
  Led _ledB = Led(LEDB_PIN);
  Led _ledC = Led(LEDC_PIN);
  uint8_t _abstate = 0;                       // the master state variable
  uint8_t _ystate = 0;                       // the master state variable
};

#endif