#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Goodwood.h>

class Led {
    public:
    Led(uint8_t pin) {this->_pin = pin;}
    void Init();
    inline void write(bool value) {digitalWrite(_pin, value);}

    private:
    uint8_t _state = 0;
    uint8_t _pin;
};

#endif