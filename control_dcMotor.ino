int motorR_F = 5;  // right forward
int motorR_B = 6;  // right backward
int motorL_F = 11;  // left  forward
int motorL_B = 10; // left  backward

int motorSpeed = 200;

void setup() {
 pinMode(motorR_F,OUTPUT);
 pinMode(motorR_B,OUTPUT);
 pinMode(motorL_F,OUTPUT);
 pinMode(motorL_B,OUTPUT);
}

void loop() {
  // right forward
  analogWrite(motorR_F, motorSpeed);
  analogWrite(motorR_B, 0);

  // left forward
  analogWrite(motorL_F, motorSpeed);
  analogWrite(motorL_B, 0);
  delay(2000);
}