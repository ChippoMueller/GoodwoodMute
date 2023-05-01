#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    _relaya.Init();
    _relayb.Init();
    _leda.Init();
    _ledb.Init();
    _drystate = EEPROM.read(DRY_STATE_ADDRESS);
    if (_drystate > 1) _drystate = 1;
    if (digitalRead(FTSWB_PIN) == LOW) {
        _drystate = !_drystate;
    EEPROM.write(DRY_STATE_ADDRESS, _drystate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
        delay(50);
        }
    }
    
    if (_drystate == 0) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
        _ledb.write(LOW);
    }

    else if (_drystate == 0) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }

    else if ( _drystate == 1) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
    }
    
    writeOutputs(_drystate);

}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::Live(void) {
    _masterstate = 1;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

void Bypass::Mute(void) {
    _masterstate = 0;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::ToggleDryState(void) {
    _drystate = !_drystate;
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
    } else {
        _relaya.write(0);
        if (_drystate == 1){
            _relayb.write(1);
            _leda.write(0);
            _ledb.write(1);
        } else {
            _relayb.write(0);
            _leda.write(0);
            _ledb.write(0);
        }
    }
}