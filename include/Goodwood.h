#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// PIN MAP //
// COUNTER-CLOCKWISE           // CLOCKWISE        PxXX    Physical Pin
#define FTSWA_PIN (4)          // (8)              PB00    7
#define FTSWB_PIN (3)          // (9)              PB00    6
#define RELAYA_PIN (0)         // (14)             PB01    2
#define RELAYB_PIN (1)         // (13)             PB01    3
#define LEDA_PIN (8)           // (3)              PA01    11
#define LEDB_PIN (9)           // (2)              PA01    12


typedef enum inputs{
  FTSWA_INPUT,
  FTSWB_INPUT,
} Input_t;

enum EepromAddresses : uint8_t {
  DRY1_ADDRESS,
  DRY2_ADDRESS,
};

// #define __DEBUG__   // comment out when not using Uno

#endif
