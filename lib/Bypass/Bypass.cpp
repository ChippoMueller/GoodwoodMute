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
    _dry1state = EEPROM.read(DRY1_ADDRESS);
    if (_dry1state > 1) _dry1state = 1;
    if (digitalRead(FTSWA_PIN) == LOW) {
        _dry1state = !_dry1state;
    EEPROM.write(DRY1_ADDRESS, _dry1state);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
        delay(50);
        }
    }
    if (_dry1state == 0) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }
    _dry2state = EEPROM.read(DRY2_ADDRESS);
    if (_dry2state > 1) _dry2state = 1;
    if (digitalRead(FTSWB_PIN) == LOW) {
        _dry2state = !_dry2state;
    EEPROM.write(DRY2_ADDRESS, _dry2state);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
        delay(50);
        }
    }
    if (_dry2state == 0) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
    }
    writeDry1Outputs(_dry1state);
    writeDry2Outputs(_dry2state);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleDry1State(void) {
    _dry1state = !_dry1state;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeDry1Outputs(_dry1state);
//    #ifdef __DEBUG__
//        Serial.print("state: "); Serial.println(_state);
//    #endif
}

void Bypass::ToggleDry2State(void) {
    _dry2state = !_dry2state;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeDry2Outputs(_dry2state);
//    #ifdef __DEBUG__
//        Serial.print("state: "); Serial.println(_state);
//    #endif
}

 void Bypass::WriteDry1State(bool value) {
    _dry1state = value;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeDry1Outputs(_dry1state);
//    #ifdef __DEBUG__
//            Serial.print("state: "); Serial.println(_state);
//    #endif
}

void Bypass::WriteDry2State(bool value) {
    _dry2state = value;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeDry2Outputs(_dry2state);
//    #ifdef __DEBUG__
//            Serial.print("state: "); Serial.println(_state);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeDry1Outputs(uint8_t value) {
    _relaya.write(value);        // use for mini relays   
//    _relay.write(!value);    // use for large relays
    _leda.write(value);                     
}

void Bypass::writeDry2Outputs(uint8_t value) {
    _relayb.write(value);        // use for mini relays   
//    _relay.write(!value);    // use for large relays
    _ledb.write(value);                     
}