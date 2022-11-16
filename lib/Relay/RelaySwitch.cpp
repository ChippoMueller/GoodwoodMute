#include <RelaySwitch.h>

void RelaySwitch::Init(void) {
    pinMode(RELAY_PIN, OUTPUT);
}