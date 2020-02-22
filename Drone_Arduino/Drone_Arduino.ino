#define burnwire_arms 2
#define burnwire_winch 3

#define photoresistor1 4
#define photoresistor2 5

#define arm1 6
#define arm2 7
#define arm3 8
#define arm4 9
#define irma 10

#define go_in 11
#define go_out 12

//control variables
int arms_deploy = 0;

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
          digitalWrite(burnwire_arms, HIGH);
          arms_deploy = 1;
      }
  }
  
}
