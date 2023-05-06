// Tap Tap Program

#include <Arduino.h>
#include <Bounce2.h>

 #define __DEBUG__   // comment out when not using Uno


const int BUTTON_PIN = 8;
const int LED_PIN = 7;
const int SAMPLE_SIZE = 1;

const unsigned long LIGHT_ON_INTERVAL = 50;                    // milliseconds that light should be on for

// when blinking

const unsigned long MAX_FLASH_INTERVAL = 1500;             // maximum interval time  500 millis  = 120 bpm
const unsigned long BOOT_FLASH_INTERVAL = 1000;             // flash rate in milliseconds at bootup

//                                            1000 millis  = 60   bpm
//                                            1500 millis  = 40   bpm
//                                            2000 millis  = 30   bpm

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long flashInterval = BOOT_FLASH_INTERVAL;         // The interval at bootup of between button presses
float bpm = 60000.0 / BOOT_FLASH_INTERVAL;

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
unsigned long intervalStartMillis = 0;

bool flashIntervalStart = 1;                                                    // Controls when light goes on when blinking

Bounce ftsw = Bounce();                                            // ftsw is an instance of a BOUNCE Object

void setup() {

  #ifdef __DEBUG__
      Serial.begin(9600);
  #endif 

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  ftsw.attach(BUTTON_PIN);                                // Attach the debouncer to a pin
  ftsw.interval(40);                                      // Use a debounce interval of 40 milliseconds

}

void loop() {

ftsw.update();                                                   // Update the Bounce instance ???

void testFunction(void);

//  ***  There are three button states:   reading, buttonState and lastButtonState ???  ***

//  ***  I’m sure we can get by with just buttonState and lastButtonState                        ***
                                                                              
testFunction();
                                                        // finish Main Loop
}

void testFunction(){

// Main test to control blinking
 

if (flashInterval > 0) {

 

      if (flashIntervalStart == 1) {

                 digitalWrite(LED_PIN, HIGH);              // Interval Start - Turn light on

                 flashIntervalStart = 0;

 

      } else if (millis() >= intervalStartMillis + LIGHT_ON_INTERVAL) {     // lights been on long enough

                 digitalWrite(LED_PIN, LOW);            // Turn light off

     

       if (millis() >= intervalStartMillis + flashInterval) {     // interval complete repeat blinking

                 intervalStartMillis = millis();

                 flashIntervalStart = 1;
      }
  }
}

 

// Detect button state change and if preesed calculate a new blinking interval

  if ((millis() - lastDebounceTime) > debounceDelay) {            // a specified time has passed (50 milliseconds)
    if (ftsw.fell()) {                                 // update last button state to current button state
      lastDebounceTime = millis();
           // calculate the interval between button presses and keep time button pressed

      currMillis = intervalStartMillis = millis();

     

      if ( prevMillis != 0 ) {

        

         if ((currMillis - prevMillis) < MAX_FLASH_INTERVAL) {          // Anything greater than max flash interval is too slow in bpm

                 flashInterval = currMillis - prevMillis;

                 flashIntervalStart = 1;                                                             // Start the flashing process, otherwise leave flashing as is

                 Serial.print("Accepted interval: ");                                                      // Debugging

           }  else {

                    Serial.print("Rejected interval too large: ");                          // Debugging

      }

         

           bpm = 60000.0 / flashInterval;

         
           Serial.print("BPM: ");                                                                        // Debugging - love this, good boy!!!
           Serial.println(bpm);       

    }   
        prevMillis = currMillis;   
}
  }   
}






/*
// Tap Tap Program

#include <Arduino.h>
#include <Bounce2.h>

 #define __DEBUG__   // comment out when not using Uno


const int BUTTON_PIN = 8;
const int LED_PIN = 7;
const int SAMPLE_SIZE = 1;

const unsigned long LIGHT_ON_INTERVAL = 50;                    // milliseconds that light should be on for

// when blinking

const unsigned long MAX_FLASH_INTERVAL = 1500;             // maximum interval time  500 millis  = 120 bpm
const unsigned long BOOT_FLASH_INTERVAL = 1000;             // flash rate in milliseconds at bootup

//                                            1000 millis  = 60   bpm
//                                            1500 millis  = 40   bpm
//                                            2000 millis  = 30   bpm

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long flashInterval = BOOT_FLASH_INTERVAL;         // The interval at bootup of between button presses
float bpm = 60000.0 / BOOT_FLASH_INTERVAL;

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
unsigned long intervalStartMillis = 0;

bool flashIntervalStart = 1;                                                    // Controls when light goes on when blinking

Bounce ftsw = Bounce();                                            // ftsw is an instance of a BOUNCE Object

void setup() {

  #ifdef __DEBUG__
      Serial.begin(9600);
  #endif 

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  ftsw.attach(BUTTON_PIN);                                // Attach the debouncer to a pin
  ftsw.interval(40);                                      // Use a debounce interval of 40 milliseconds

}

void loop() {

ftsw.update();                                                   // Update the Bounce instance ???

void testFunction(void);

//  ***  There are three button states:   reading, buttonState and lastButtonState ???  ***

//  ***  I’m sure we can get by with just buttonState and lastButtonState                        ***
                                                                              
testFunction();
                                                        // finish Main Loop
}

void testFunction(){
  int reading = ftsw.read();                                      // read the state of the footswitch (HIGH or LOW). Must include debounce time 40 milliseconds

//if (reading != lastButtonState) {                        // footswitch has changed state - reset lastDebounceTime
//    lastDebounceTime = millis();
//}

//if (ftsw.fell()) {                        // footswitch has changed state - reset lastDebounceTime
//    lastDebounceTime = millis();
//}

// Main test to control blinking
 

if (flashInterval > 0) {

 

      if (flashIntervalStart == 1) {

                 digitalWrite(LED_PIN, HIGH);              // Interval Start - Turn light on

                 flashIntervalStart = 0;

 

      } else if (millis() >= intervalStartMillis + LIGHT_ON_INTERVAL) {     // lights been on long enough

                 digitalWrite(LED_PIN, LOW);            // Turn light off

     

       if (millis() >= intervalStartMillis + flashInterval) {     // interval complete repeat blinking

                 intervalStartMillis = millis();

                 flashIntervalStart = 1;
      }
  }
}

 

// Detect button state change and if preesed calculate a new blinking interval

 

  if ((millis() - lastDebounceTime) > debounceDelay) {            // a specified time has passed (50 milliseconds)
    if (reading != buttonState) {                                 // update last button state to current button state
     

      buttonState = reading;

      if (buttonState == LOW) {                                                     // current state is high so footswitch has been pressed

           // calculate the interval between button presses and keep time button pressed

      currMillis = intervalStartMillis = millis();

     

      if ( prevMillis != 0 ) {

        

         if ((currMillis - prevMillis) < MAX_FLASH_INTERVAL) {          // Anything greater than max flash interval is too slow in bpm

                 flashInterval = currMillis - prevMillis;

                 flashIntervalStart = 1;                                                             // Start the flashing process, otherwise leave flashing as is

                 Serial.print("Accepted interval: ");                                                      // Debugging

           }  else {

                    Serial.print("Rejected interval too large: ");                          // Debugging

      }

         

           bpm = 60000.0 / flashInterval;

         
           Serial.print("BPM: ");                                                                        // Debugging - love this, good boy!!!
           Serial.println(bpm);       

    }   
        prevMillis = currMillis;   
  }
}
  lastButtonState = reading;

  }   
}

*/