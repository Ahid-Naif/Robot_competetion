#include <Stepper.h>
#include <Servo.h>

/* define variables that are stepper motor related */
const int stepsPerRevolution = 200;

// initialize the stepper library on pins 1 through 4:
Stepper myStepper(stepsPerRevolution, 1, 2, 3, 4);

/* define variables that are dc motors related */
int motorR_F = 5;  // right forward
int motorR_B = 6;  // right backward
int motorL_F = 9;  // left  forward
int motorL_B = 10; // left  backward

int motorSpeed = 150;

/* define variables that are limit switches related */
int dcSwitch = 7;      // limit switch that stops the dc motors
int stepperSwitch = 8; // limit switch that stops stepper motor

/* define variables that are servo motor */
Servo myservo; // create servo object to control a servo

int rotationAngle = 120; // variable to store the servo position

/* delay times */
unsigned long stepperMotorUp = 2000; // 2000 ms (2 seconds)
unsigned long backwardDelay  = 1000;
unsigned long rightDelay     = 500;
unsigned long forwardDelay   = 1000;
unsigned long leftDelay      = 500;
unsigned long rotationDelay  = 1000;

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
}

void loop()
{



    // repeat collecting balls steps twice
    // In other words, collect balls on three stages
    for (int i = 0; i <= 2; i++)
    {
        // move untill robot reaches the balls
        while (true)
        {
            moveForward(); // keep moving forward
            if (digitalRead(dcSwitch))
            {
                // if dc limit switch is pressed, stop moving forward
                break;
            }
        }

        // collect the balls
        while (true)
        {
            // rotate stepper motor in counterclockwise direction
            myStepper.step(-stepsPerRevolution); // keep moving counterclockwise or down
            if (digitalRead(stepperSwitch))
            {
                // if stepper limit switch is pressed, stop moving stepper motor
                break;
            }
        }

        // wait for 2 seconds
        delay(2000);

        // take the balls up
        // rotate stepper motor in clockwise direction
        myStepper.step(stepsPerRevolution);
        // wait for the stepper motor to move the balls up
        delay(stepperMotorUp);

        // move backward, then, turn right, then, move forward
        takeStep2Right();

        // turn left
        turnLeft();
        delay(leftDelay);
    }

    // go to other direction.. rotate 180 degress
    turnRight();
    delay(rotationDelay);

    // move untill robot reaches the other section
    while (true)
    {
        moveForward(); // keep moving forward
        if (digitalRead(dcSwitch))
        {
            // if dc limit switch is pressed, stop moving forward
            break;
        }
    }

    // throw the balls
    myservo.write(rotationAngle);
    delay(15);
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