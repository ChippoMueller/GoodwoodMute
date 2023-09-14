#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
        _ledb.write(LOW);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::MasterLive(void) {
    _masterstate = 0; 
    WriteOutputs();                 
}

void Bypass::MasterMute(void) {
    _masterstate = 1; 
    WriteOutputs();                 
}

void Bypass::DryLive(void) {
    _drystate = 0;     
    WriteOutputs();             
}

void Bypass::DryMute(void) {
    _drystate = 1;
    WriteOutputs();                  
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::WriteOutputs(void) { 

    if (_masterstate == 1){
        _relaya.write(1);
        _relayb.write(1);
        _leda.write(1);
        
        if (_drystate == 1){
            _ledb.write(1);
        } else {
            _ledb.write(0);
        }
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