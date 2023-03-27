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
  void policeLights();
  void setupFlash();
  byte readButton(byte i, int retrigger, long holdDur);
  

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  Led _ledc = Led(LEDC_PIN);
//  uint8_t _masterstate = 0;                       // the master state variable
//  uint8_t _drystate = 0;                          // the dry state variable
  bool _masterstate = 0;                       // the master state variable
  bool _drystate = 0;                          // the dry state variable
  bool _relayAState = 0;
  bool _relayBState = 0;
  bool _ledAState = 0;
  bool _ledBState = 0;
  unsigned long _previousMillis = 0;
  int _interval = _redInterval;
  const long _redInterval = 2000;
  const long _blueInterval = 150;
  const long _setupInterval = 75;
//  const long _blinkInterval = 150;
//  const long _pauseInterval = 1000;
};

#endif