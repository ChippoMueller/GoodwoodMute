#include <Arduino.h>
#include <Bounce2.h>

const int BUTTON_PIN = 8;
const int LED_PIN = 7;
const int SAMPLE_SIZE = 4;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long pressTimes[SAMPLE_SIZE];
int pressIndex = 0;
float bpm = 0.0;

unsigned long prevMillis = 0;

unsigned long currMillis = 0;

unsigned long interval = 0;

 

Bounce ftsw = Bounce();

void setup() {

  // Initialise the pressTimes Array with zero’s

 for (int i = 0; i < SAMPLE_SIZE; i++) {                  

           pressTimes[i] = 0;
  }
 
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  ftsw.attach(BUTTON_PIN);
  ftsw.interval(40);

  Serial.begin(9600);

}

void loop() {
  ftsw.update();

  int reading = ftsw.read();

//  if (reading != lastButtonState) {
//    lastDebounceTime = millis();
//  }

  if (ftsw.fell()) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // record the interval

   currMillis = millis();

   if ( prevMillis != 0 ) {

         interval = currMillis - prevMillis;

   }

   prevMillis = currMillis;

 

 if ( interval > 0 ) {                                                                               // avoid storing interval of zero first time through

    pressTimes[pressIndex] = interval;
    pressIndex = (pressIndex + 1) % SAMPLE_SIZE;

 

         // This is wrong until the array is filled . i.e. the first three times through the loop

         //      The 1st time through, the array will contain [interval, 0, 0, 0]

         //             2nd  time [interval, interval, 0, 0]

         //             3rd time [interval, interval, interval, 0] 

      

         // calculate the average BPM
          unsigned long sum = 0;

          int arrayElements = 0;


          for (int i = 0; i < SAMPLE_SIZE; i++) {
      
            if (pressTimes[i] != 0) {
            
                sum += pressTimes[i];

                arrayElements ++;
            }
          }
     
           unsigned long avgPressTime = sum / arrayElements;

           bpm = 60000.0 / avgPressTime;

           Serial.print("BPM: ");           // love this, good boy!!!
           Serial.println(bpm);
          }
    }


/*
        // flash the LED at the calculated tempo
        int interval = (int)(60.0 / bpm * 1000.0 / 2.0);
        digitalWrite(LED_PIN, HIGH);
        delay(interval);
        digitalWrite(LED_PIN, LOW);
        delay(interval);
*/

    }
  }

  lastButtonState = reading;
}