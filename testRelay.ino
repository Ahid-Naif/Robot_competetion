void setup()
{
    pinMode(13, OUTPUT);
    pinMode(1, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH);
    digitalWrite(1, LOW);
    delay(2000);
    digitalWrite(13, LOW);
    digitalWrite(1, HIGH);
    delay(2000);
}