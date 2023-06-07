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
  void ToggleMuteState(void);
  void Trails(void);
  void NoTrails(void);
  void writeOutputs(uint8_t value);

  private:
  RelaySwitch _inputrelay = RelaySwitch(RELAYA_PIN);
  RelaySwitch _outputrelay = RelaySwitch(RELAYB_PIN);
  Led _red = Led(LEDA_PIN);
  Led _blue = Led(LEDB_PIN);
  int _led = 0;
  bool _mutestate = 0;                      
  bool _trails = 0;                       
};

#endif