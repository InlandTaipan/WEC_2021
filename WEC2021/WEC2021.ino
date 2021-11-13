#include <Servo.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  serial.begin()
}

void loop() {
  // put your main code here, to run repeatedly:
  serial.printf(digitalRead(A0));
  delay(10);
}
