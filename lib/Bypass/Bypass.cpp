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
    _cleanstate = EEPROM.read(CLEAN_STATE_ADDRESS);
    _fxstate = EEPROM.read(FX_STATE_ADDRESS);

    if (_cleanstate > 1) _cleanstate = 1;
    if (_fxstate > 1) _fxstate = 1;

    if (digitalRead(FTSWA_PIN) == LOW) {
        _cleanstate = !_cleanstate;
    EEPROM.write(CLEAN_STATE_ADDRESS, _cleanstate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
        delay(50);
        }
    }
    
    if (digitalRead(FTSWB_PIN) == LOW) {
        _fxstate = !_fxstate;
    EEPROM.write(FX_STATE_ADDRESS, _fxstate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
        delay(50);
        }
    }

    if (_cleanstate == 0 && _fxstate == 0){
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
        _ledb.write(LOW);
    }
    
    if (_cleanstate == 0 && _fxstate == 1) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }

    if (_fxstate == 0 && _cleanstate == 1) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
    }
    
    writeOutputs(_cleanstate);
    writeOutputs(_fxstate);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleCleanState(void) {
    _cleanstate = !_cleanstate;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_cleanstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::ToggleFxState(void) {
    _fxstate = !_fxstate;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_fxstate);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 

    if (_cleanstate == 1){
        _relaya.write(0);
        _leda.write(1);
    } else {
        _relaya.write(1);
        _leda.write(0);
    }

    if (_fxstate == 1){
        _relayb.write(0);
        _ledb.write(1);
    } else {
        _relayb.write(1);
        _ledb.write(0);
    }
}