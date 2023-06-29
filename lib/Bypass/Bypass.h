#ifndef BYPASS_H
#define BYPASS_H

#include <Arduino.h>
#include <Goodwood.h>
#include <EEPROM.h>
#include <Led.h>
#include <RelaySwitch.h>

class Bypass {
  public:
  void MagnetLive(void);
  void MagnetMute(void);
  void PiezoLive(void);
  void PiezoMute(void);
  void writeOutputs(uint8_t value);

  private:
  RelaySwitch _relaya = RelaySwitch(RELAYA_PIN);
  RelaySwitch _relayb = RelaySwitch(RELAYB_PIN);
  Led _leda = Led(LEDA_PIN);
  Led _ledb = Led(LEDB_PIN);
  Led _ledc = Led(LEDC_PIN);
  bool _magnetState = 0;                       // the magnet state variable
  bool _piezoState = 0;                        // the piezo state variable
};

#endif