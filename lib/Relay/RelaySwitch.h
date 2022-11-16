#ifndef RELAYSWITCH_H
#define RELAYSWITCH_H

#include <Arduino.h>
#include <Goodwood.h>

class RelaySwitch {
  public:
  RelaySwitch(uint8_t pin){this->_pin = pin;}
  void Init();
  inline void write(bool value) {digitalWrite(_pin, value);}

  private:
  uint8_t _pin;
};


#endif