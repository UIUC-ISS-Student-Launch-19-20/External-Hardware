#include <Servo.h>

// Pin Declarations
Servo servo; // pin 4

#define solenoids 5
#define go_ayberk 9

// Command Variables
int clear_to_deploy = 0; // high once clearance given
int deployed = 0; // high once deployment occurs 

// Servo Variables
int maxSpeed = 0; // max winch speed

void setup() {
    digitalWrite(solenoids, LOW);
    servo.write(89); // turn off
}

void loop() {
    if(!clear_to_deploy && (go_ayberk == HIGH)) { // requires a go signal to proceed
        clear_to_deploy = 1;
    }
    if(clear_to_deploy) { // once Ayberk gives signal
        deployInit();
        deploy();
        delay(20000); // wait 20 seconds
        deployed = 1;
        kill();
    }
}

void deployInit() {
    digitalWrite(solenoids, HIGH);
    servo.attach(4);
    servo.write(89);
}

void deploy() {
  digitalWrite(4, HIGH);
  servo.write(maxSpeed);
}

void kill() {
  servo.detach();
  digitalWrite(4, LOW);
  while(1) { }
}
