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
  void WriteOutputs(uint8_t value);
  void SetupFlash(int led);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  Led _ledc = Led(LEDC_PIN);
  bool _masterstate = 0;                       // the master state variable
  bool _drystate = 0;                          // the dry state variable
  bool _ledstate = 0;
  bool _setupstatusA = 0;
  bool _setupstatusB = 0;
  unsigned long _previousmillis = 0;
  const long _setupinterval = 75;
};

#endif