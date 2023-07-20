#include <Bypass.h>
/*!
    @brief Initialises the relay and led.
    Loads the previous _state from EEPROM.
*/
void Bypass::Init(void) {
    _relay.Init();
    _led.Init();

    int buttonState = digitalRead(FTSW_PIN);

    _state = EEPROM.read(STATE_ADDRESS);
    if (_state > 1) _state = 1;

    while (buttonState == LOW){
    _setupstatus = 1;
    SetupFlash();
    buttonState = digitalRead(FTSW_PIN);
    }

    if (_setupstatus == 1) {
        _state = !_state;
    EEPROM.write(STATE_ADDRESS, _state);
    }
       
    if (_setupstatus == 0 && _state == 0) {
        _led.write(HIGH);
        delay(50);
        _led.write(LOW);
    }

    writeOutputs(_state);
    #ifdef __DEBUG__
        Serial.print("Init state: "); Serial.println(_state);
    #endif
}

/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleState(void) {
    _state = !_state;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_state);
}

 void Bypass::WriteState(bool value) {
    _state = value;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_state);
    #ifdef __DEBUG__
            Serial.print("Write value: "); Serial.println(value);
    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) {
    _relay.write(value);        // use for mini relays   
//    _relay.write(!value);    // use for large relays
    _led.write(value);                     
}

void Bypass::SetupFlash(void){
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
     _led.write(_ledstate);
 
  }
}