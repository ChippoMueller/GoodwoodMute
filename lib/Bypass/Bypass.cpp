#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    _inputrelay.Init();
    _outputrelay.Init();
    _red.Init();
    _blue.Init();
    if (digitalRead(TOGGLE_PIN) == 0){
        _trails = 0;
    } else {
        _trails = 1;
    }
    _mutestate = EEPROM.read(STATE_ADDRESS);
    if (_mutestate > 1) _mutestate = 1;
    if (digitalRead(FTSW_PIN) == LOW) {
        _mutestate = !_mutestate;
    EEPROM.write(STATE_ADDRESS, _mutestate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        if (_trails == 0){
        _red.write(1);
        delay(50);
        _red.write(0);
        delay(50);
        } else {
        _blue.write(1);
        delay(50);
        _blue.write(0);
        delay(50);
        }

        }
    } else {
        if (_trails == 0){
        _red.write(1);
        delay(50);
        _red.write(0);
        delay(50);
        } else {
        _blue.write(1);
        delay(50);
        _blue.write(0);
        delay(50);
        }
    }
    
    writeOutputs(_mutestate);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleMuteState(void) {
    _mutestate = !_mutestate;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_mutestate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::Trails(void) {
    _trails = 1;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_trails);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

void Bypass::NoTrails(void) {
    _trails = 0;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_trails);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 

    if (_trails == 0){
        if (_mutestate == 1){
            _inputrelay.write(0);
            _outputrelay.write(1);
            _red.write(1);
            _blue.write(0);
        } else {
            _inputrelay.write(0);
            _outputrelay.write(0);
            _red.write(0);
            _blue.write(0);
        }
    } else {
        if (_mutestate == 1){
            _inputrelay.write(1);
            _outputrelay.write(0);
            _red.write(0);
            _blue.write(1);
        } else {
            _inputrelay.write(0);
            _outputrelay.write(0);
            _red.write(0);
            _blue.write(0);
        }
    }
}