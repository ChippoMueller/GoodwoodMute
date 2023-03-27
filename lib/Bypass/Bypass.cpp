#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    int _buttonState = digitalRead(FTSWA_PIN);
    bool _setupState = 0;
    _relaya.Init();
    _relayb.Init();
    _leda.Init();
    _ledb.Init();
    _masterstate = EEPROM.read(MASTER_STATE_ADDRESS);
    if (_masterstate > 1) _masterstate = 1;

        while (_buttonState == LOW){
            _setupState = 1;
            setupFlash();
            _buttonState = digitalRead(FTSWA_PIN);
        }
    
    if (_setupState == 1){
        _masterstate = !_masterstate;
        EEPROM.write(MASTER_STATE_ADDRESS, _masterstate);
    } else {
        _leda.write(1);
        delay(50);
        _leda.write(0);
        }

    #ifdef __DEBUG__
      Serial.print("Boot Master: "); Serial.print(_masterstate); Serial.print(" ");
      Serial.print("Setup: "); Serial.println(_setupState);
    #endif

    writeOutputs(_masterstate);
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

   if (_masterstate == 1) {
        if (_drystate == 1) {
            _relayAState = 1;
            _relayBState = 1;
            policeLights();
            } else {
                _relayAState = 1;
                _relayBState = 1;
                _ledAState = 1;
                _ledBState = 0;
            }
    } else {
        if (_drystate == 1) {
            _relayAState = 0;
            _relayBState = 1;
            _ledAState = 0;
            _ledBState = 1;
        } else {
            _relayAState = 0;
            _relayBState = 0;
            _ledAState = 0;
            _ledBState = 0;
        }
    }

    _relaya.write(_relayAState);
    _relayb.write(_relayBState);
    _leda.write(_ledAState);
    _ledb.write(_ledBState);

    #ifdef __DEBUG__
      Serial.print("Master: "); Serial.print(_masterstate);
      Serial.print(" Dry: "); Serial.println(_drystate);
    #endif
    
}

 void Bypass::policeLights(){
    if (_masterstate == 1 && _drystate == 1){

    unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _interval) {
    // save the last time you blinked the LED
    _previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (_ledAState == 0) {
      _ledAState = 1;
      _ledBState = 0;
      _interval = _redInterval;
    } else {
      _ledAState = 0;
      _ledBState = 1;
      _interval = _blueInterval;
    }
  }
  }
    _leda.write(_ledAState);
    _ledb.write(_ledBState);
}

void Bypass::setupFlash(){
    unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _setupInterval) {
    // save the last time you blinked the LED
    _previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (_ledAState == 0) {
      _ledAState = 1;
    } else {
      _ledAState = 0;
    }

    // set the LED with the ledState of the variable:
    _leda.write(_ledAState);
  }
}