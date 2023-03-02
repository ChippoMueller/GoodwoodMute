#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    _relayA.Init();
    _relayB.Init();
    _ledA.Init();
    _ledB.Init();
    _ledC.Init();
    _abstate = EEPROM.read(AB_STATE_ADDRESS);
    if (_abstate > 1) _abstate = 1;
    if (digitalRead(FTSWA_PIN) == LOW) {
        _abstate = !_abstate;
    EEPROM.write(AB_STATE_ADDRESS, _abstate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _ledA.write(HIGH);
        _ledB.write(HIGH);
        delay(50);
        _ledA.write(LOW);
        _ledB.write(LOW);
        delay(50);
        }
    }
    if (_abstate == 0) {
        _ledA.write(HIGH);
        _ledB.write(HIGH);
        delay(50);
        _ledA.write(LOW);
        _ledB.write(LOW);
    }
    
    _ystate = EEPROM.read(Y_STATE_ADDRESS);
    if (_ystate > 1) _ystate = 1;
    if (digitalRead(FTSWB_PIN) == LOW) {
        _ystate = !_ystate;
    EEPROM.write(Y_STATE_ADDRESS, _ystate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _ledC.write(HIGH);
        delay(50);
        _ledC.write(LOW);
        delay(50);
        }
    }
    if (_ystate == 0) {
        _ledC.write(HIGH);
        delay(50);
        _ledC.write(LOW);
    }

    writeRelayOutputs(_abstate);
    writeLedOutputs(_abstate);
    writeRelayOutputs(_ystate);
    writeLedOutputs(_ystate);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleABState(void) {
    _abstate = !_abstate;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeRelayOutputs(_abstate);
    writeLedOutputs(_abstate);
//    #ifdef __DEBUG__
//        Serial.print("state: "); Serial.println(_state);
//    #endif
}

 void Bypass::ToggleYState(void) {
    _ystate = !_ystate;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeRelayOutputs(_ystate);
    writeLedOutputs(_ystate);
//    #ifdef __DEBUG__
//            Serial.print("state: "); Serial.println(_state);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeRelayOutputs(uint8_t value) {
    if (_ystate == 1) {
        _relayA.write(0);
        _relayB.write(0);
    } 
    else if (_ystate == 0 && _abstate == 0) {
        _relayA.write(0);
        _relayB.write(1);
    } 
    else if (_ystate == 0 && _abstate == 1) {
        _relayA.write(1);
        _relayB.write(0);
    }
    }
    

    void Bypass::writeLedOutputs(uint8_t value) {
    if (_abstate == 0) {
        _ledA.write(1);
        _ledB.write(0);
    }

    if (_abstate == 1) {
        _ledA.write(0);
        _ledB.write(1);
    }

    if (_ystate == 0) {
        _ledC.write(0);
    }

    if (_ystate == 1) {
        _ledC.write(1);
    }      
}