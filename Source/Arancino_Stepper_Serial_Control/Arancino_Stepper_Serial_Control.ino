
#include <AccelStepper.h>

#define Serial SerialUSB

// Define motor interface type
// 4 means 4-wire full-step interface (for ULN2003 + 28BYJ-48)
#define FULLSTEP 4

// Define GPIO Arancino pins connected to ULN2003 input

const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 3;
const int IN4 = 38;

// Create AccelStepper object
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(FULLSTEP, IN1, IN3, IN2, IN4);

// Default settings
long targetPosition = 0;
int currentSpeed = 100;
int maxSpeed = 800;
int acceleration = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Serial Control with AccelStepper");
  Serial.println("Commands: GOTO <steps>, SPEED <value>, RESET, STATUS");

  // Configure the motor driver
  stepper.setMaxSpeed(maxSpeed);        // set maximum allowed speed
  stepper.setAcceleration(acceleration);// set acceleration
  stepper.setSpeed(currentSpeed);       // set initial speed (for continuous mode if needed)
}

void loop() {
  // Run motor to current target position (non-blocking)
  stepper.run();

  // Check for serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read user input line
    input.trim();                                // Remove spaces and newlines

    // Command: GOTO <position>
    if (input.startsWith("GOTO")) {
      long pos = input.substring(5).toInt(); // extract position
      stepper.moveTo(pos);                   // set new absolute target
      Serial.print("Moving to: ");
      Serial.println(pos);
    }

    // Command: SPEED <value>
    else if (input.startsWith("SPEED")) {
      int newSpeed = input.substring(6).toInt();
      if (newSpeed > 0 && newSpeed <= maxSpeed) {
        currentSpeed = newSpeed;
        stepper.setMaxSpeed(currentSpeed);
        Serial.print("Speed set to: ");
        Serial.println(currentSpeed);
      } else {
        Serial.println("Invalid speed value (1 - 800 steps/s)");
      }
    }

    // Command: RESET (go back to position 0)
    else if (input == "RESET") {
      stepper.moveTo(0);
      Serial.println("Returning to origin (0)");
    }

    // Command: STATUS (print current state)
    else if (input == "STATUS") {
      Serial.print("Current Position: ");
      Serial.println(stepper.currentPosition());
      Serial.print("Target Position: ");
      Serial.println(stepper.targetPosition());
      Serial.print("Speed: ");
      Serial.println(currentSpeed);
    }

    // Unknown command
    else {
      Serial.println("Unknown command. Try: GOTO <steps>, SPEED <value>, RESET, STATUS");
    }
  }
}
