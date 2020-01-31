#include <Encoder.h>
#include <Servo.h>

Servo myservo; // create servo object
Encoder myenc(2, 3); // create encoder object
long oldPosition  = -999; // initialize an old position
long target[] = {100,200,300,400,500};  // array of target to control descent speed of servo
long done = target[sizeof(target) / sizeof(target[0]) - 1]; // intialize a variable for when to end project
int i = 0; // initialize index for the array
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
    if(newPosition >= target[i]) {
       myservo.write(87); // turn off servo
       Serial.print("PAUSED, reached target ");
       Serial.print(target[i]);
       Serial.println();
       if(newPosition < done) {
         i++; // increment target index
         delay(100); // delay, replace with adequate action
         myservo.write(90); // turn on servo
       }
    } 
 }
