#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// PIN MAP //
// COUNTER-CLOCKWISE            // CLOCKWISE        PxXX    Physical Pin
#define FTSW_PIN (4)           // (0)              PB00    13
#define RELAYA_PIN (0)          // (9)              PB01    2
#define RELAYB_PIN (1)          // (9)              PB01    3
#define LED_PIN (9)             // (3)              PA01    10


typedef enum inputs{
  FTSW_INPUT,
} Input_t;

enum EepromAddresses : uint8_t {
  STATE_ADDRESS,
};

// #define __DEBUG__   // comment out when not using Uno

#endif
