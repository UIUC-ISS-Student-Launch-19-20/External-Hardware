#define burnwire_arms 2
#define burnwire_winch 3

#define photoresistor1 4
#define photoresistor2 5

#define arm1 6
#define arm2 7
#define arm3 8
#define arm4 9
#define irma 10

#define drone_tether 11 // cut arms, pr OR dr
#define drone_arms 12 // cut tether


//control variables
int arms_deploy = 0;
int drone_deploy = 0;

void setup() {
    pinMode(burnwire_arms, OUTPUT);
    pinMode(burnwire_winch, OUTPUT);
    pinMode(photoresistor1, INPUT);
    pinMode(photoresistor2, INPUT);
    pinMode(arm1, INPUT);
    pinMode(arm2, INPUT);
    pinMode(arm3, INPUT);
    pinMode(arm4, INPUT);
}

void loop() {
  if(! arms_deploy) {
    if(photoresistor1 | photoresistor2) {
      delay(5000);
      if (photoresistor1 | photoresistor2) {
        digitalWrite(burnwire_arms, HIGH);
        delay(3000);
        digitalWrite(burnwire_arms, LOW);
        arms_deploy = 1;
      } 
    }
    if(drone_arms == HIGH) {
        digitalWrite(burnwire_arms, HIGH);
        delay(3000);
        digitalWrite(burnwire_arms, LOW);
        arms_deploy = 1;
    }
  }

  if (arms_deploy == 1 && drone_tether == HIGH) {
    if (arm1 == HIGH && arm2 == HIGH && arm3 == HIGH && arm4 == HIGH) { 
       digitalWrite(burnwire_winch, HIGH);
       delay(3000);
       digitalWrite(burnwire_winch, LOW);
       drone_deploy = 1;
    }
  }
}
