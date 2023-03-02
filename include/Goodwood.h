#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// PIN MAP //
// COUNTER-CLOCKWISE             // CLOCKWISE        PxXX    Physical Pin
#define FTSWA_PIN (4)            // (9)              PB00    7
#define FTSWB_PIN (3)            // (8)              PB00    6
#define RELAYA_PIN (1)           // (12)             PB01    3
#define RELAYB_PIN (0)           // (13)             PB01    2
#define LEDA_PIN (9)             // (3)              PA01    12
#define LEDB_PIN (8)             // (4)              PA01    11
#define LEDC_PIN (7)             // (5)              PA01    10



typedef enum inputs{
  FTSWA_INPUT,
  FTSWB_INPUT
} Input_t;

enum EepromAddresses : uint8_t {
  AB_STATE_ADDRESS,
  Y_STATE_ADDRESS,
};

// #define __DEBUG__   // comment out when not using Uno

#endif