int dcSwitch = 7; // limit switch that stops the dc motors
int stepperSwitch = 8; // limit switch that stops stepper motor

void setup()
{
    // set limit switches as INPUT
    pinMode(dcSwitch, INPUT);
    pinMode(stepperSwitch, INPUT);

    Serial.begin(9600);
}

void loop()
{
    Serial.print("DC switch: ");
    Serial.println(digitalRead(dcSwitch));
    Serial.print("Stepper motor: ");
    Serial.print(digitalRead(stepperSwitch));
}