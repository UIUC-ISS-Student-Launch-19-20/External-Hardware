#include <Encoder.h>
#include <Servo.h>

Servo myservo; // create servo object
Encoder myenc(2, 3); // create encoder object

// values for the encoder and servo
long oldPosition  = -999; // initialize an old position
long newPosition; // creates variable to hold new position
long finalTarget = 5000; // declare the final descent target
long target = 0; // set the initial target value
long offTarget; // creates variable to hold difference between current position and target
int maxSpeed = 180; // sets maximum speed of the servo
int scaleFactor; // creates variable for scaling of servo speed based on accuracy of position

// values for the timer
unsigned long timerStart = 0;
boolean timerRunning = false;
unsigned long refreshInterval = 1000; // reset every 1 second
unsigned long lastRefreshTime = 0;
unsigned long endTime = 10000; // end after 10 seconds

void setup() { 
    myservo.attach(9); // attach servo to Arduino pin
    myenc.write(0); // write the base value to the encoder
    Serial.begin(9600);

    timerStart = millis(); // start timer
    timerRunning = true; // not finished yet (is false when finished)
 } 
 
 void loop() {
    // check if endTime has been reached; if so, turn off servo
    if (timerRunning && ((millis() - timerStart >= endTime))) {
      timerRunning = false;
      myservo.write(87);
    }

    // increments target every time the refresh interval is completed
    if (millis() - lastRefreshTime >= refreshInterval) {
      lastRefreshTime = millis();
      target += 500;
      Serial.print("lastRefreshTime: ");
      Serial.println(lastRefreshTime);
      Serial.print("target: ");
      Serial.println(target);
    }
    
    newPosition = myenc.read(); // create instance of variable for new encoder position
    if (newPosition != oldPosition) {
        oldPosition = newPosition; // set the current position of encoder to old position for next loop
//        Serial.println(newPosition); // print position of rotary encoder to the serial monitor
    }

    offTarget = target - newPosition; 
    scaleFactor = offTarget / 250; // scales by maximum that position is expected to be off by
    if (scaleFactor > 1) {
      scaleFactor = 1; 
    } else if (scaleFactor < -1) {
      scaleFactor = -1;
    }

    if (newPosition >= finalTarget) {
      myservo.write(87); // turn off servo
      while(1) {}
    }

    myservo.write(maxSpeed * scaleFactor);
    
    /*   
    if(newPosition >= target) {
       myservo.write(87); // turn off servo
       if (newPosition <= finalTarget) {
         delay(10); // delay, replace with adequate action
         myservo.write(180); // turn on servo
       }
 
    }
    */ 
 }
