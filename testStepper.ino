#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 12, 2, 3, 4);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
}

void loop() {
  // step one revolution  in one direction: (clockwise)
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction: (counterclockwise)
  myStepper.step(-stepsPerRevolution);
  delay(500);
}