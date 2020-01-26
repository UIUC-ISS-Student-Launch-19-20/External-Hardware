#include <Encoder.h>
#include <Servo.h>

Servo myservo;
Encoder myenc(2, 3);
long oldPosition  = -999;
long target[] = {100,200,300,400,500};
long done = 0;
int i = 0;
void setup() { 
    myservo.attach(9);
    Serial.begin(9600);
    myenc.write(0);
    myservo.write(90);
    done = target[sizeof(target) / sizeof(target[0]) - 1];
 } 
 
 void loop() {
    long newPosition = myenc.read();
    if (newPosition != oldPosition) {
        oldPosition = newPosition;
        // Serial.println(newPosition);
    }
    if(newPosition >= target[i]) {
       myservo.write(87);
       if(newPosition < done) {
         i++;
         delay(1000);
         myservo.write(90);
       }
    } 
 }
