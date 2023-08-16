#include <Bypass.h>
/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::Bypassed(void) {
    _state = 0;                 
    writeOutputs(); 
}

 void Bypass::Active(void) {
    _state = 1;
    writeOutputs();
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(void) {
    if (_state == 0){
        _relay.write(0);
        _led.write(0); 
    } else {
        _relay.write(1);
        _led.write(1);
    }                   
}