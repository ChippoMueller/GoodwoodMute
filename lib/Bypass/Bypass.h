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
  void Live(void);
  void Mute(void);
  void DryLive(void);
  void DryMute(void);
  void writeOutputs(uint8_t value);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  bool _masterstate = 0;                          // the master state variable
  bool _drystate = 0;                          // the dry state variable
};

#endif