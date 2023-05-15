// Tap Tap Program

#include <Arduino.h>
#include <Bounce2.h>

 #define __DEBUG__   // comment out when not using Uno


const int BUTTON_PIN = 8;
const int LED_PIN = 7;
const int SAMPLE_SIZE = 4;

const unsigned long LIGHT_ON_INTERVAL = 50;                    // milliseconds that light should be on for

// when blinking

const unsigned long MAX_TAP_INTERVAL = 1500;             // maximum interval time  500 millis  = 120 bpm
const unsigned long BOOT_TAP_INTERVAL = 1000;             // Tap rate in milliseconds at bootup

//                                            1000 millis  = 60   bpm
//                                            1500 millis  = 40   bpm
//                                            2000 millis  = 30   bpm

//int buttonState = HIGH;
//int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long tapInterval = BOOT_TAP_INTERVAL;         // The interval at bootup of between button presses
int bpm = int(60000.0 / BOOT_TAP_INTERVAL);          // starting BPM value
float averageTapInterval;     // The average tap interval as a fraction

unsigned long intervalArray[SAMPLE_SIZE];     // Array of intervals between taps

unsigned long prevMillis = 0;
unsigned long currMillis = 0;
unsigned long intervalStartMillis = 0;

int tapCount = 0;             // Keep count of taps 

bool tapIntervalStart = 1;    // Controls when light goes on when blinking

Bounce ftsw = Bounce();       // ftsw is an instance of a BOUNCE Object

void ControlFlashing(void);
void ControlButtonPress(void);
void InitialiseIntervalArray(void);
void UpdateIntervalArray(unsigned long tapInterval, int tapIndex);
float CalculateAvgInterval();

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

ControlFlashing();
ControlButtonPress();
                                                                              
}

void ControlFlashing(void){

// Main test to control flashing
 

if (tapInterval > 0) {

 

      if (tapIntervalStart == 1) {

                 digitalWrite(LED_PIN, HIGH);              // Interval Start - Turn light on

                 tapIntervalStart = 0;

 

      } else if (millis() >= intervalStartMillis + LIGHT_ON_INTERVAL) {     // lights been on long enough

                 digitalWrite(LED_PIN, LOW);            // Turn light off

     

       if (millis() >= intervalStartMillis + tapInterval) {     // interval complete repeat blinking

                 intervalStartMillis = millis();

                 tapIntervalStart = 1;
      }
  }
}
}

void ControlButtonPress(void){

// Detect button state change and if preesed calculate a new blinking interval

  if ((millis() - lastDebounceTime) > debounceDelay) {            // a specified time has passed (50 milliseconds)
    if (ftsw.fell()) {                                 // update last button state to current button state
      lastDebounceTime = millis();
           // calculate the interval between button presses and keep time button pressed

      currMillis = intervalStartMillis = millis();

         if ((currMillis - prevMillis) < MAX_TAP_INTERVAL) {          // Anything greater than max tap interval is too slow in bpm

         unsigned long currInterval = currMillis - prevMillis;        // Calculate the tap interval
         UpdateIntervalArray(currInterval, tapCount % SAMPLE_SIZE);   // Update the array of intervals
         averageTapInterval = CalculateAvgInterval();                 // Tap interval for BPM calculation
         tapInterval = long (averageTapInterval + .5);                // Rounded tap interval for flashing light 
         tapCount++;                                                  // Increment tap count
         tapIntervalStart = 1;                                        // Start the flashing process, otherwise leaving flashing as is
         bpm = int((60000.0 / averageTapInterval) + .5);              // Calculate beats per minute

                 tapInterval = currMillis - prevMillis;

              #ifdef __DEBUG__
                 Serial.print("Accepted interval: ");                                                      // Debugging
              #endif

           }  else {              // Considered to be the first tap

          InitialiseIntervalArray();        // Fill interval array with zeros
          tapCount = 0;                         // Reset tap counter

              #ifdef __DEBUG__
                    Serial.print("Rejected interval too large: ");          // Debugging
              #endif
      }

        #ifdef __DEBUG__
           Serial.print("BPM: ");               // Debugging
           Serial.println(bpm);      
        #endif 

        prevMillis = currMillis;   
    }
  }   
}

void InitialiseIntervalArray(void) {
  // Initialise the interval array with zeros 
  
  for (int i = 0; i < SAMPLE_SIZE; i++){
    intervalArray[i] = 0;
  }
}

void UpdateIntervalArray(unsigned long tapInterval, int tapIndex){
  intervalArray[tapIndex] = tapInterval;
}

float CalculateAvgInterval(){
  // Need to process first iterations trhu the loop till array fills
  // The 1st time through, the array will contain [interval, 0, 0, 0]
  // 2nd time [interval, interval, 0, 0]
  // 3rd time [interval, interval, interval, 0]
  // thru to [last intervals, 2nd last interval, 3rd last interval, 4th last interval]

  // calculate the average BPM
  unsigned long sum = 0;
  int arrayElements = 0;
  float avgIntervals;

  for (int i = 0; i < SAMPLE_SIZE; i++){
    if (intervalArray[i] != 0) {
      sum += intervalArray[i];
      arrayElements++;
    }
    else {
      i = SAMPLE_SIZE;
    }
  }

  if (arrayElements > 0) {      // Avoid divisions by zero
   avgIntervals = (float(sum) / float(arrayElements));   // Calculate average intervals from intervals array
   return (avgIntervals);
  } else {
  return (tapInterval);
  }
}