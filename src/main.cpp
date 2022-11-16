
#include <Arduino.h>
#include <Bounce2.h>
#include <Goodwood.h>
#include <Bypass.h>
#include <EEPROM.h>

void setup() {

digitalWrite(ledA, !ledAState);
digitalWrite(relayA, !relayAState);
delay(50); 
digitalWrite(ledA, ledAState);
digitalWrite(relayA, relayAState);

}

void loop(){

int reading = digitalRead(switchAPin); 

if (reading != lastSwitchAState) {

  lastDebounceTime = millis(); 
}

if ((millis() - lastDebounceTime) > debounceDelay) {

 if (reading != switchAPinState) {
      switchAPinState = reading;

      if (switchAPinState == LOW) {

        ledAState = !ledAState; 
        relayAState = !relayAState;   
      }
      }
}
  
  digitalWrite(ledA, ledAState);
  digitalWrite(relayA, relayAState);


  lastSwitchAState = reading; 
  

}