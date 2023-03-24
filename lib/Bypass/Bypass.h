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
  void ToggleMasterState(void);
  void ToggleDryState(void);
  void pressType();
  void writeOutputs(uint8_t value);
  byte readButton(byte i, int retrigger, long holdDur);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  Led _ledc = Led(LEDC_PIN);
  uint8_t _masterstate = 0;                       // the master state variable
  uint8_t _drystate = 0;                          // the dry state variable
};

#endif