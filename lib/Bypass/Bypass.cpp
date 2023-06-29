#include <Bypass.h>


void Bypass::MagnetLive(void) {
    _magnetState = 1;                  
    writeOutputs(_magnetState);
}

void Bypass::MagnetMute(void) {
    _magnetState = 0;                  
    writeOutputs(_magnetState);
}

void Bypass::PiezoLive(void) {
    _piezoState = 1;
    writeOutputs(_piezoState);
}

void Bypass::PiezoMute(void) {
    _piezoState = 0;
    writeOutputs(_piezoState);
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 

    if (_magnetState == 1){
        _relayb.write(0);
        _ledb.write(1);
        } else {
        _relayb.write(1);
        _ledb.write(0);
        }
    
    if (_piezoState == 1){
        _relaya.write(0);
        _leda.write(1);
        } else {
        _relaya.write(1);
        _leda.write(0);
        }
}