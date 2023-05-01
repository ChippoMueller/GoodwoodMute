#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);  
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::Live(void) {
    _masterstate = 0;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

void Bypass::Mute(void) {
    _masterstate = 1;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

void Bypass::DryLive(void) {
    _drystate = 0;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_drystate);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

void Bypass::DryMute(void) {
    _drystate = 1;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_drystate);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 

    if (_masterstate == 1){
        _relaya.write(1);
        _relayb.write(1);
        _leda.write(1);
        _ledb.write(0);
    } else {
        _relaya.write(0);
        _leda.write(0);
        if (_drystate == 1){
            _relayb.write(1);
            _ledb.write(1);
        } else {
            _relayb.write(0);
            _ledb.write(0);
        }
    }
}