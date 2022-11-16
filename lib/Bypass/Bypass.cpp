#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    _relay.Init();
    _led.Init();
    _state = EEPROM.read(STATE_ADDRESS);
    writeOutputs(_state);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleState(void) {
    _state = !_state;                   
    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_state);
    #ifdef __DEBUG__
        Serial.print("state: "); Serial.println(_state);
    #endif
}

 void Bypass::WriteState(bool value) {
    _state = value;
    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_state);
    #ifdef __DEBUG__
            Serial.print("state: "); Serial.println(_state);
    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) {
    _relay.write(value);             
    _led.write(value);                     
}