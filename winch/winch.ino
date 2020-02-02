#include <Encoder.h>
#include <Servo.h>

Servo myservo; // create servo object
Encoder myenc(2, 3); // create encoder object

long oldPosition  = -999; // initialize an old position
long finalTarget = 500; // final descent target
long target = 0;

unsigned long delayStart = 0;
boolean delayRunning = false;
unsigned long refreshInterval = 1000; // reset every 1 second
unsigned long lastRefreshTime = 0;

void setup() { 
    myservo.attach(9); // attach servo to Arduino pin
    myenc.write(0); // write the base value to the encoder
    Serial.begin(9600);

    delayStart = millis(); // start delay
    delayRunning = true; // not finished yet (is false when finished)
 } 
 
 void loop() {
    // check if 
    if (delayRunning && ((millis() - delayStart >= 10000))) {
      delayRunning = false;
      Serial.println("DONE");    
    }
    
    if (millis() - lastRefreshTime >= refreshInterval) {
      lastRefreshTime = millis();
      target += 100;
      Serial.print("lastRefreshTime: ");
      Serial.println(lastRefreshTime);
      Serial.print("target: ");
      Serial.println(target);
    }
    
    long newPosition = myenc.read(); // create instance of variable for new encoder position
    if (newPosition != oldPosition) {
        oldPosition = newPosition; // set the current position of encoder to old position for next loop
//        Serial.println(newPosition); // print position of rotary encoder to the serial monitor
    }

    if(newPosition >= target) {
       myservo.write(87); // turn off servo
       if (newPosition <= finalTarget) {
         delay(10); // delay, replace with adequate action
         myservo.write(90); // turn on servo
       }
 
    }  
 }
