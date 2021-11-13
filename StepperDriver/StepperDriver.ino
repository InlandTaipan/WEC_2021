
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

#define stepsTo45 255  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsTo45, 8, 10, 9, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  delay(100);
  while(analogRead(A0) < 600)
  {
     myStepper.step(stepsTo45/10);
     delay(100);
  }
  // step one revolution  in one direction:
  myStepper.step(stepsTo45);
 
  //step one revolution in the other direction:
  Serial.println("calibrated");
  delay(5000000);
}

void loop() {
}
