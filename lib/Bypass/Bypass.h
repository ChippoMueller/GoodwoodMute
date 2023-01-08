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
  void ToggleDry1State(void);
  void ToggleDry2State(void);
  void WriteDry1State(bool value);
  void WriteDry2State(bool value);
  void writeDry1Outputs(uint8_t value);
  void writeDry2Outputs(uint8_t value);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  uint8_t _dry1state = 1;                       // the master state variable
  uint8_t _dry2state = 1;                       // the master state variable
};

#endif