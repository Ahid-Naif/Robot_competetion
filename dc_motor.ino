#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 200; 

Stepper myStepper(stepsPerRevolution, 12, 2, 3, 4);

int servoPin = 9;
Servo servo;
int angle = 70;  // servo position in degrees

// Motor A connections -- right motor
int in1 = 5;
int in2 = 6;
// Motor B connections -- left motor
int in3 = 11;
int in4 = 10;

void setup()
{
  // Set all the motor control pins to outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // set the speed at 60 rpm:
  myStepper.setSpeed(10);

  // set servo motor pin output
  servo.attach(servoPin);
}

void Straight()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
}

void Backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
}

void Right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop()
{
  delay(2000);
  Straight();
  delay(3000);
  Stop();
  delay(1000);
  Right();
  delay(40);
  Stop();
  delay(1000);
  Straight();
  delay(2500);
  Stop();
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(2000);
  myStepper.step(stepsPerRevolution);
  delay(2000);
  Backward();
  delay(1000);
  Stop();
  delay(500);
  Left();
  delay(1350);
  Stop();
  delay(1000);
  Straight();
  delay(2075);
  Stop();
  delay(1000);
  Right();
  delay(1400);
  Straight();
  delay(1800);
  Stop();
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(2000);
  myStepper.step(stepsPerRevolution);
  delay(2000);
  Backward();
  delay(1000);
  Stop();
  delay(500);
  Left();
  delay(1350);
  Stop();
  delay(1000);
  Straight();
  delay(1050);
  Stop();
  delay(1000);
  Right();
  delay(1400);
  Straight();
  delay(1800);
  Stop();
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(2000);
  myStepper.step(stepsPerRevolution);
  delay(2000);
  Backward();
  delay(1500);
  Left();
  delay(2850);
  Straight();
  delay(9000);
  Stop();
  delay(500);
  myStepper.step(-1500);
  delay(2000);
  for(angle = 70; angle < 180; angle++) {
        servo.write(angle);
        delay(50);
    }
  myStepper.step(2000);
  delay(2000);
  while(1){};  
//    
//  // now scan back from 180 to 0 degrees
//  for(angle = 180; angle > 0; angle--) {
//        servo.write(angle);
//        delay(15);
//  }
}
