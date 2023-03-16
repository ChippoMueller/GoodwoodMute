#include <Bypass.h>

void Bypass::live() {
    _relaya.write(LOW);
    _relayb.write(LOW);              
//    EEPROM.write(STATE_ADDRESS, _state);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

void Bypass::masterMute() {
    _relaya.write(HIGH);
    _relayb.write(HIGH);              
//    EEPROM.write(STATE_ADDRESS, _state);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::dryMute() {
    _relaya.write(LOW);
    _relayb.write(HIGH);
//    EEPROM.write(STATE_ADDRESS, _state);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}