#include <RelaySwitch.h>

void RelaySwitch::Init(void) {
    pinMode(RELAYA_PIN, OUTPUT);
    pinMode(RELAYB_PIN, OUTPUT);
}