
// Define the LED pin
const int ledPin = 2; // GPIO 2 corresponds to Pin 3 on the Arancino Connector

void setup() {
  // Configure GPIO 2 as an output pin
  // This prepares the pin to send a HIGH or LOW signal to control the LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn on the LED by setting the pin HIGH
  // When the pin is HIGH, a voltage of 3.3V is applied to the LED, lighting it up
  digitalWrite(ledPin, HIGH);

  // Wait for 1 second (1000 milliseconds) with the LED ON
  delay(1000);

  // Turn off the LED by setting the pin LOW
  // When the pin is LOW, no voltage is applied, and the LED turns off
  digitalWrite(ledPin, LOW);

  // Wait for 1 second (1000 milliseconds) with the LED OFF
  delay(1000);

  // The loop repeats continuously, so the LED will keep blinking
}


