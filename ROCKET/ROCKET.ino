#include <Encoder.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

// Pin Declarations
Servo servo;
Encoder encoder(2,3);

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

#define solenoids 5
#define go_avionics 8
#define go_drone 9

// Command Variables
int clear_to_deploy = 0; // high once clearance given
int deploy = 0; // high once altitude attained

// Encoder and Servo Variables
int oldPosition = -999;
int newPosition;
int finalTarget = 10000; // in Encoder Units
int target = 0;
int targetInc = 750;
int maxSpeed = 180; // max winch speed
int scaleFactor;
unsigned int lastRefreshPosition = 0;
unsigned int unitsPerRotation = 2350; // corresponds to one full rotation of the ENCODER (not servo)
unsigned int totalRotations = 0;

// Timer Values
unsigned long refreshInterval = 1000; // 1 second
unsigned long lastRefresh = 0; 

// Barometer Variables
float initAlt; // initialized as altitude of launch sight
float releaseAlt; // absolute altitude
float targetReleaseAlt = 700 / 3.28084; // our target relative to ground (converted 700ft to meters)
float altitude; // current altitude


void setup() {
    if (! baro.begin()) {
      // put in troubleshooting here
    }
    initAlt = baro.getAltitude();
    releaseAlt = initAlt + targetReleaseAlt;
    digitalWrite(solenoids, LOW);
//    Serial.begin(9600);
}

void loop() {
    if(!clear_to_deploy & (go_avionics | go_drone)) { // requires a go signal to proceed
        clear_to_deploy = 1;
    }
    if(clear_to_deploy & !deploy) { // used once go signal, before target altitude
       baroInst();
    }
    if(deploy) { // once target altitude reached and clear signal
        timer();
        encoderUpdate();
        rotationCount();
        speedRefresh();
        if(newPosition >= finalTarget) {
            kill();
        }
    }
}

void baroInst() {
  altitude = baro.getAltitude();
  if(altitude <= releaseAlt) {
      deployInit();
      deploy = 1;
  }
}

void deployInit() {
    digitalWrite(solenoids, HIGH);
    timerInit();
    encoder.write(0);
    servo.attach(4);
    servo.write(89);
}

void timerInit() {
    lastRefresh = millis();
}

void timer() {
    if (millis() - lastRefresh >= refreshInterval) {
        lastRefresh = millis();
        target += targetInc;
    }
}

void rotationCount() {
    if ((newPosition - lastRefreshPosition >= unitsPerRotation) && millis() > 2000) {
        lastRefreshPosition = newPosition; 
        totalRotations = totalRotations + 1;
    }
}

void encoderUpdate() {
  newPosition = encoder.read();
  if (newPosition != oldPosition) {
      oldPosition = newPosition;
  }
}

void speedRefresh() {
    scaleFactor = (target - newPosition) / 250; // scales by maximum that position is expected to be off by
    if (scaleFactor < 0) {
      scaleFactor = scaleFactor * -1;
    }
    if (scaleFactor > 1) {
        scaleFactor = 1; 
    }
}

void kill() {
  servo.detach();
  digitalWrite(4, LOW);
  while(1) { }
}
