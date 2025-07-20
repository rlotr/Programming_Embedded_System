
// Include the AccelStepper Library
#include <AccelStepper.h>

// Define motor interface type
// 4 means 4-wire full-step interface (for ULN2003 + 28BYJ-48)
#define FULLSTEP 4
#define STEP_PER_REVOLUTION 2048 // this value is from datasheet

// Define GPIO Arancino pins connected to ULN2003 input

const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 3;
const int IN4 = 38;

// Create AccelStepper object
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(FULLSTEP, IN1, IN3, IN2, IN4);

void setup() {
  stepper.setMaxSpeed(1000);      // set the maximum speed
  stepper.setAcceleration(50);    // set acceleration
  stepper.setSpeed(100);          // set initial speed
}

void loop() {

  // change direction once the motor reaches target position
  
  stepper.moveTo(STEP_PER_REVOLUTION);
  while (stepper.distanceToGo() != 0) 
  {  stepper.run(); }

  stepper.stop();
  delay(1000);

  stepper.moveTo(0);  // set target back at start position
  while (stepper.distanceToGo() != 0) 
  {  stepper.run(); }  

}

