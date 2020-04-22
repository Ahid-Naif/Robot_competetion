int motorR_F = 5;  // right forward
int motorR_B = 6;  // right backward
int motorL_F = 10;  // left  forward
int motorL_B = 11; // left  backward

int motorSpeed = 250;

void setup() {
 pinMode(motorR_F,OUTPUT);
 pinMode(motorR_B,OUTPUT);
 pinMode(motorL_F,OUTPUT);
 pinMode(motorL_B,OUTPUT);
}

void loop() {
 
  // left forward
  analogWrite(motorL_F, motorSpeed);
  analogWrite(motorL_B, 0);
  delay(2000);
}