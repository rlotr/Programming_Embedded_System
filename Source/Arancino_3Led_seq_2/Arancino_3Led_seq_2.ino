// Define the pins for the LEDs
const int RedLedPin = 23; // GPIO 23 (Pin D23 on Arancino Connector)
const int GreenLedPin = 22; // GPIO 22 (Pin D22 on Arancino Connector)
const int YellowLedPin = 24; // GPIO 24 (Pin D24 on Arancino Connector)

// Define the number of LEDs and their pins in an array
const int ledPins[] = {RedLedPin, GreenLedPin, YellowLedPin};
const int numLeds = 3; // Total number of LEDs

void setup() {
  // Initialize each LED pin as an output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Set each GPIO as output
    digitalWrite(ledPins[i], LOW); // Ensure all LEDs are off initially
  }
}

void loop() {
  // Loop through each LED in the array
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn on the current LED
    delay(500); // Keep the LED on for 500ms
    digitalWrite(ledPins[i], LOW); // Turn off the current LED
  }
  
  // Add a delay between cycles for better visualization
  delay(500);
}
