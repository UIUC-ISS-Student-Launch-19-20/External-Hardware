#include <Encoder.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Servo myservo; // create servo object
Encoder myenc(2, 3); // create encoder object
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

// values for the encoder and servo
long oldPosition  = -999; // initialize an old position
long newPosition; // creates variable to hold new position
long finalTarget = 10000; // declare the final descent target
long target = 0; // set the initial target value
long offTarget; // creates variable to hold difference between current position and target
int maxSpeed = 180; // sets maximum speed of the servo
int scaleFactor; // creates variable for scaling of servo speed based on accuracy of position

// values for the timer
unsigned long timerStart = 0;
boolean timerRunning = false;
unsigned long refreshInterval = 500; // reset every 1 second
unsigned long lastRefreshTime = 0;
unsigned long endTime = 10000; // end after 10 seconds

// values for rotation counting
unsigned long lastRefreshCount = 0;
unsigned long unitsPerRot = 2350; // 2350 encoder units corresponds to one full rotation
unsigned long totalRotations = 0; 

// variables for altimeter
float pressure;
float initAlt;
int altCount = 0; // use to set initAlt only once
float altitude;
float tempC;

void setup() { 
    myservo.attach(9); // attach servo to Arduino pin
    myenc.write(0); // write the base value to the encoder
    Serial.begin(9600);

    timerStart = millis(); // start timer
    timerRunning = true; // not finished yet (is false when finished)

  }
 
 void loop() {
    // check for altimeter connection
    if (! baro.begin()) {
      Serial.println("CAN'T CONNECT TO ALTIMETER");
      return;
    }

    pressure = baro.getPressure();
    altitude = baro.getAltitude();
    tempC = baro.getTemperature();

    if (altCount == 0) {
      initAlt = altitude;
      Serial.print("INITIAL ALTITUDE: "); Serial.print(initAlt); Serial.println(" m");
      altCount++;
    }

    // Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" m");
    // Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" pascals");
    // Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" C");

    if (altitude - initAlt < 0.3) {
      myservo.detach();
      digitalWrite(9, LOW);
      return;
    }

    // increments target every time the refresh interval is completed
    if (millis() - lastRefreshTime >= refreshInterval) {
      lastRefreshTime = millis();
      target += 750;
    }
    
    newPosition = myenc.read(); // create instance of variable for new encoder position
    if (newPosition != oldPosition) {
        oldPosition = newPosition; // set the current position of encoder to old position for next loop
        Serial.print("encoder position: "); Serial.println(newPosition);
    }

    // counts total number of rotations completed by encoder
    // waits 2 sec to start calculating due to inaccuracy of initial encoder readings 
    if (newPosition - lastRefreshCount >= unitsPerRot && millis() > 2000) {
      lastRefreshCount = newPosition; 
      totalRotations += 1;
      Serial.print("ROTATIONS COMPLETED: "); Serial.println(totalRotations);
    }

    offTarget = target - newPosition; 
    scaleFactor = offTarget / 250; // scales by maximum that position is expected to be off by
    if (scaleFactor < 0) {
      scaleFactor = scaleFactor * -1;
    }
    if (scaleFactor > 1) {
      scaleFactor = 1; 
    }

    if (newPosition >= finalTarget) {
      Serial.print("FINAL POSITION: ");
      Serial.println(newPosition);
      myservo.detach(); // turn off servo
      digitalWrite(9, LOW);
      while(1) {} 
    }

    myservo.attach(9);
    myservo.write(180 - (maxSpeed * scaleFactor));
    Serial.println("");
    
 }
