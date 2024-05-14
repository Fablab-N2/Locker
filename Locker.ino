#include <Stepper.h>

// Defines the number of steps per rotation
Stepper myStepper = Stepper(1000, 13,12,11,10);

// password per lock
int lock_1_pass = "1A56B";
int lock_2_pass = "584CA";

// lock engaged (flase = open / true = closed)
bool lock_1 = true;
bool lock_2 = true;

float status1 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}


void loop() {
  if (lock_1 == false && lock_1_pass == "1A56B") {
    // turn on the light
    digitalWrite(2, HIGH);

    // use the motor to open the lock
    myStepper.setSpeed(10);
    myStepper.step(100);
    delay(2000);
  }
  else {
    digitalWrite(3, LOW);
  }
  

  if (lock_2 == true && lock_2_pass == "584CA") {
    // turn on the light
    digitalWrite(2, HIGH);

    // use the motor to open the lock
    myStepper.setSpeed(10);
    myStepper.step(2038);
    delay(200);
  }
  else {
    digitalWrite(3, LOW);
  }
}