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
    
    if (_drystate == 0 && _masterstate == 0) {
        _leda.write(HIGH);
        _ledb.write(HIGH);
        delay(50);
        _leda.write(LOW);
        _ledb.write(LOW);
    }

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
    
    writeOutputs(_masterstate);
    writeOutputs(_drystate);

}

void Bypass::pressType() {
    #define SHORT_PRESS_TIME 500 // 500 milliseconds
    #define LONG_PRESS_TIME  3000 // 3000 milliseconds

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

  // read the state of the switch/button:
  currentState = digitalRead(FTSWA_PIN);

  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration < SHORT_PRESS_TIME ){
      ToggleMasterState();
    }

    if ( pressDuration > LONG_PRESS_TIME ) {
      ToggleDryState();
      } 

  // save the the last state
  lastState = currentState;
    }
}
/*!
    @brief Toggles _state, stores the new _state value to the EEPROM, and writes the outputs.
*/
void Bypass::ToggleMasterState(void) {
    _masterstate = !_masterstate;                  
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_masterstate);
//    #ifdef __DEBUG__
//        Serial.print("master state: "); Serial.println(_masterstate);
//    #endif
}

 void Bypass::ToggleDryState(void) {
    _drystate = !_drystate;
//    EEPROM.write(STATE_ADDRESS, _state);
    writeOutputs(_drystate);
//    #ifdef __DEBUG__
//            Serial.print("dry state: "); Serial.println(_drystate);
//    #endif
}

/*!
    @brief Writes all of the outputs: Relay, LedA, LedB, LedC.
    @param value the value to write.
*/
void Bypass::writeOutputs(uint8_t value) { 

    if (_masterstate == 1) {
//        _relaya.write(LOW);      // Big relays
//        _relayb.write(LOW);      // Big relays
        _relaya.write(HIGH);     // Mini relays
        _relayb.write(HIGH);     // Mini relays
        _leda.write(HIGH);
        _ledb.write(LOW);
    } 

    if (_masterstate == 0) {
//        _relaya.write(HIGH);    // Big relays
//        _relayb.write(HIGH);    // Big relays
        _relaya.write(LOW);     // Mini relays
        _relayb.write(LOW);     // Mini relays
        _leda.write(LOW);
        _ledb.write(LOW);
    } 

    if (_drystate == 1) {
        _ledb.write(HIGH);
    } 

    if (_drystate == 0) {
        _ledb.write(LOW);
    } 

    if (_masterstate == 0 && _drystate == 1) {
//        _relayb.write(LOW);      // Big relays
        _relayb.write(HIGH);      // Mini relays
    } 

    if (_masterstate == 0 && _drystate == 0) {
//        _relayb.write(HIGH);      // Big relays
        _relayb.write(LOW);      // Mini relays
    } 
}