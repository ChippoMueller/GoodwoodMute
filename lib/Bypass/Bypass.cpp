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
    _masterstate = EEPROM.read(MASTER_STATE_ADDRESS);
    if (_masterstate > 1) _masterstate = 1;
    if (digitalRead(FTSWA_PIN) == LOW) {
        _masterstate = !_masterstate;
    EEPROM.write(MASTER_STATE_ADDRESS, _masterstate);
       
        for (int flash = 1; flash <= 4; ++flash) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
        delay(50);
        }
    }
    
    if (_masterstate == 0) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }
/*
    else if (_masterstate == 1 && _drystate == 0) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }

    else if (_masterstate == 0 && _drystate == 1) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
    }
    */
    writeOutputs(_masterstate);
    writeOutputs(_drystate);

}
/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleMasterState(void) {
    _masterstate = !_masterstate;                  
    writeOutputs(_masterstate);
}

 void Bypass::ToggleDryState(void) {
    _drystate = !_drystate;
    writeOutputs(_drystate);
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 
/*
    if (_masterstate == 1) {
        _relaya.write(_masterstate);     // Mini relays
        _relayb.write(_masterstate);     // Mini relays
        _leda.write(_masterstate);
    } 

    if (_masterstate == 0) {
        _relaya.write(_masterstate);     // Mini relays
        _relayb.write(_masterstate);     // Mini relays
        _leda.write(_masterstate);
    } 

    if (_drystate == 1) {
        _ledb.write(_drystate);
   } 

    if (_drystate == 0) {
        _ledb.write(_drystate);
    } 

    if (_masterstate == 0 && _drystate == 1) {
        _relayb.write(_drystate);      // Mini relays
        _ledb.write(_drystate);
    } 

    if (_masterstate == 0 && _drystate == 0) {
        _relayb.write(_drystate);      // Mini relays
        _ledb.write(_drystate);
    } 

    if (_masterstate == 1 && _drystate == 1)
        policeLights();
    }
    */

   if (_masterstate == 1) {
        if (_drystate == 1) {
            _relayAState = 0;
            _relayBState = 0;
            policeLights();
            } else {
                _relayAState = 0;
                _relayBState = 0;
                _ledAState = 1;
                _ledBState = 0;
            }
    } else {
        if (_drystate == 1) {
            _relayAState = 1;
            _relayBState = 0;
            _ledAState = 0;
            _ledBState = 1;
        } else {
            _relayAState = 1;
            _relayBState = 1;
            _ledAState = 0;
            _ledBState = 0;
        }
    }

    _relaya.write(_relayAState);
    _relayb.write(_relayBState);
    _leda.write(_ledAState);
    _ledb.write(_ledBState);

    #ifdef __DEBUG__
      Serial.print("Master: "); Serial.print(_masterstate); Serial.print(" ");
      Serial.print("Dry: "); Serial.println(_drystate);
    #endif
    
}

 void Bypass::policeLights(){
    if (_masterstate == 1 && _drystate == 1){
 //   _ledAState = 1;
 //   _ledBState = 0;

    unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= redInterval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (_ledAState == 0) {
      _ledAState = 1;
      _ledBState = 0;
    } else {
      _ledAState = 0;
      _ledBState = 1;
    }
  }
  }
    _leda.write(_ledAState);
    _ledb.write(_ledBState);
}