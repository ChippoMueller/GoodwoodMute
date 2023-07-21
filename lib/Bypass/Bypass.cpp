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

    int buttonAState = digitalRead(FTSWA_PIN);
    int buttonBState = digitalRead(FTSWB_PIN);

    _masterstate = EEPROM.read(MASTER_STATE_ADDRESS);
    if (_masterstate > 1) _masterstate = 1;

    while (buttonAState == LOW){
    _setupstatusA = 1;
    SetupFlash(2);
    buttonAState = digitalRead(FTSWA_PIN);
    }

    if (_setupstatusA == 1) {
        _masterstate = !_masterstate;
        EEPROM.write(MASTER_STATE_ADDRESS, _masterstate);
    }

    _drystate = EEPROM.read(DRY_STATE_ADDRESS);
    if (_drystate > 1) _drystate = 1;

    while (buttonBState == LOW){
        _setupstatusB = 1;
        SetupFlash(1);
        buttonBState = digitalRead(FTSWB_PIN);
    }

    if (_setupstatusB == 1) {
        _drystate = !_drystate;
        EEPROM.write(DRY_STATE_ADDRESS, _drystate);
    }

    if (_setupstatusA == 0 && _setupstatusB == 0){
    
    if (_drystate == 0 && _masterstate == 0) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
        _ledb.write(LOW);
    }

    else if (_masterstate == 1 && _drystate == 0) {
        _ledb.write(HIGH);
        delay(50);
        _ledb.write(LOW);
    }

    else if (_masterstate == 0 && _drystate == 1) {
        _leda.write(HIGH);
        delay(50);
        _leda.write(LOW);
    }
}
    
    WriteOutputs(_masterstate);
    WriteOutputs(_drystate);
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleMasterState(void) {
    _masterstate = !_masterstate;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    WriteOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::ToggleDryState(void) {
    _drystate = !_drystate;
//    EEPROM.write(STATE_ADDRESS, _state);
    WriteOutputs(_drystate);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::WriteOutputs(uint8_t value) { 

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

void Bypass::SetupFlash(int led){
    unsigned long currentMillis = millis();

  if (currentMillis - _previousmillis >= _setupinterval) {
    // save the last time you blinked the LED
    _previousmillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (_ledstate == LOW) {
      _ledstate = HIGH;
    } else {
      _ledstate = LOW;
    }

    // set the LED with the ledState of the variable:
    if (led == 2){
        _leda.write(_ledstate);
    } else if (led == 1){
        _ledb.write(_ledstate);
    }
  }
}