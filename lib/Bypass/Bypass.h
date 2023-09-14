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
  void SetupFlash(void);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _led = Led(LED_PIN);
  bool _state = 0;                       // the master state variable
  bool _setupstatus = 0;
  bool _ledstate = 0;
  unsigned long _previousmillis = 0;
  const long _setupinterval = 75;
};

#endif