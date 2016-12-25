/*
 * controlbox.ino: Runs code on the motor control box
 * 
 * This code has the arduino control two TalonSR motor controllers. 
 * The control board is set up with three SPDT switches and two 
 * potentiometers. One switch controls the "sync" setting, which 
 * while turned on has both motor controllers running at the same
 * speeds. The other switches are set up to control the direction
 * and the potentiometers control the speeds.
 * 
 */


#include <Servo.h>

// Pin Maps
const int sync = 2;
const int direction1 = 3;
const int direction2 = 4;

const int speed1 = A0;
const int speed2 = A1;

const int output1 = 5; // Must be a PWM Output
const int output2 = 6; // Must be a PWM Output

// Servos
Servo motor1;
Servo motor2;

// Constants
const int idle = 1500;
const int forward = 2000;
const int reverse = 1000;

const int maxInput = 1023;
const int minInput = -1023;

void setup() {
  // Set pin modes
  pinMode(sync, INPUT);
  pinMode(direction1, INPUT);
  pinMode(direction2, INPUT);

  // Connect Talons ("Servos")
  motor1.attach(output1);
  motor2.attach(output2);
}

void loop() {
  int power1 = 0;
  int power2 = 0;

  // Get power for motor 1
  power1 = analogRead(speed1);
  if(digitalRead(direction1 == LOW) {
    // Make power negative if the direction switch is off (down)
    power1 *= -1;
  }

  // Get power for motor 2
  power2 = analogRead(speed2);
  if(digitalRead(direction2 == LOW) {
    // Make power negative if the direction switch is off (down)
    power2 *= -1;
  }
  
  // Check the Sync status
  if(digitalRead(sync) == HIGH) {
    // If sync is on, run both motors based on input 1
    power2 = power1;
  }

  // Map the values to the servo outputs
  power1 = map(power1, minInput, reverse, maxInput, forward);
  power2 = map(power2, minInput, reverse, maxInput, forward);

  // Output the values to the Talons
  motor1.writeMicroseconds(power1);
  motor2.writeMicroseconds(power2);
}
