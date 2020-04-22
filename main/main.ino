#include <Stepper.h>
#include <Servo.h>

/* define variables that are stepper motor related */
const int stepsPerRevolution = 150;

// initialize the stepper library on pins 1 through 4:
Stepper myStepper(stepsPerRevolution, 12, 2, 3, 4);

/* define variables that are dc motors related */
int motorR_F = 5;  // right forward
int motorR_B = 6;  // right backward
int motorL_F = 11; // left  forward
int motorL_B = 10; // left  backward

int motorSpeed = 150;

/* define variables that are limit switches related */
int dcSwitch = 7;      // limit switch that stops the dc motors
int stepperSwitch = 8; // limit switch that stops stepper motor

/* define variables that are servo motor */
Servo myservo; // create servo object to control a servo

int rotationAngle = 120; // variable to store the servo position

/* delay times */
unsigned long stepperMotorUp = 10000; // 2000 ms (2 seconds)
unsigned long backwardDelay = 3000;
unsigned long rightDelay = 2000;
unsigned long forwardDelay = 2000;
unsigned long leftDelay = 2000;
unsigned long rotationDelay = 1000;

/*
    We have 3 stages:
        stage No. 1 => moving forward
        stage No. 2 => collect balls moving stepper motor
        stage No. 3 => take balls up moving stepper motor
        stage No. 4 => moving to the next position
            These four stages are repeated three times.. a counter keeps a record
        stage No. 5 => throwing balls
*/

int stage = 0;   // initial state is zero
int counter = 0; // to keep record of how many times the 1st four stages are repeated

void setup()
{
    // set stepper motor speed at 60 rpm:
    myStepper.setSpeed(60);

    // set motor terminals as OUTPUT
    pinMode(motorR_F, OUTPUT);
    pinMode(motorR_B, OUTPUT);
    pinMode(motorL_F, OUTPUT);
    pinMode(motorL_B, OUTPUT);

    // set limit switches as INPUT
    pinMode(dcSwitch, INPUT);
    pinMode(stepperSwitch, INPUT);

    // attach the servo on pin 9 to the servo object
    myservo.attach(9);
    myservo.write(0);

    pinMode(13, OUTPUT);
    pinMode(1, OUTPUT);

    // turn all motors OFF
    digitalWrite(1, LOW);
    digitalWrite(13, LOW);

    stage = 1;
}

void loop()
{
    if (stage == 1)
    {
        // At stage 1, move untill robot reaches the balls
        digitalWrite(13, HIGH);
        moveForward(); // keep moving forward
        if (digitalRead(dcSwitch))
        {
            // if dc limit switch is pressed, stop all motors
            stop();
            digitalWrite(13, LOW);
            // then, go to stage 2
            stage = 2;
        }
    }

    if (stage == 2)
    {
        // At stage 2, collect the balls

        // rotate stepper motor in counterclockwise direction
        digitalWrite(1, HIGH);
        myStepper.step(-stepsPerRevolution); // keep moving counterclockwise or down
        if (digitalRead(stepperSwitch))
        {
            // if stepper limit switch is pressed, go to stage 3
            stage = 3;
        }
    }

    if(stage == 3)
    {
        // At stage 3, move stepper motor clockwise or up
        
        for(int i = 0; i < 10; i++)
        {
            myStepper.step(stepsPerRevolution); // keep moving clockwise or up
        }
        delay(500);
        digitalWrite(1, LOW);
        stage = 4;
    }

    if(stage == 4)
    {
        digitalWrite(13, HIGH);
        takeStep2Right();
        stage = 5;
        turnLeft();
        delay(leftDelay);

        counter++;
        if(counter == 3)
        {
            stage = 5;
        }
        else
        {
            stage = 1;
        }    
    }

    if(stage == 5)
    {
        turnRight();
        delay(rotationDelay);
        stage = 6;
    }

    if(stage == 6)
    {
        moveForward(); // keep moving forward
        if (digitalRead(dcSwitch))
        {
            myservo.write(rotationAngle);
            delay(15);
            stage = 0;
        }
    }
}

void moveForward()
{
    // right forward
    analogWrite(motorR_F, motorSpeed);
    analogWrite(motorR_B, 0);
    // left forward
    analogWrite(motorL_F, motorSpeed);
    analogWrite(motorL_B, 0);
}

void moveBackward()
{
    // right backward
    analogWrite(motorR_F, 0);
    analogWrite(motorR_B, motorSpeed);
    // left backward
    analogWrite(motorL_F, 0);
    analogWrite(motorL_B, motorSpeed);
}

void turnRight()
{
    // right backward
    analogWrite(motorR_F, 0);
    analogWrite(motorR_B, motorSpeed);
    // left forward
    analogWrite(motorL_F, motorSpeed);
    analogWrite(motorL_B, 0);
}

void turnLeft()
{
    // right forward
    analogWrite(motorR_F, motorSpeed);
    analogWrite(motorR_B, 0);
    // left backward
    analogWrite(motorL_F, 0);
    analogWrite(motorL_B, motorSpeed);
}

void stop()
{
    // stop forward
    analogWrite(motorR_F, 0);
    analogWrite(motorR_B, 0);
    // stop backward
    analogWrite(motorL_F, 0);
    analogWrite(motorL_B, 0);
}

void takeStep2Right()
{
    // move backward a little bit
    moveBackward();
    delay(backwardDelay);

    // turn right
    turnRight();
    delay(rightDelay);

    // move forward a little bit
    moveForward();
    delay(forwardDelay);
}