#include <Encoder.h>
#include <Servo.h>

Servo myservo; // create servo object
Encoder myenc(2, 3); // create encoder object
long oldPosition  = -999; // initialize an old position
long finalTarget = 1000; // final descent target
long target = -1;

void setup() { 
    myservo.attach(9); // attach servo to Arduino pin
    myservo.write(90); // initialize servo speed
    myenc.write(0); // write the base value to the encoder
    Serial.begin(9600);
    Serial.println("Servo and Rotary Encoder Test");
 } 
 
 void loop() {
    long newPosition = myenc.read(); // create instance of variable for new encoder position
    if (newPosition != oldPosition) {
        oldPosition = newPosition; // set the current position of encoder to old position for next loop
        Serial.println(newPosition);
    }
    if(newPosition >= target) {
       myservo.write(87); // turn off servo
       if(newPosition < finalTarget) {
         target += 10; // increment target index
         delay(10); // delay, replace with adequate action
         myservo.write(90); // turn on servo
       }
    } 
 }
