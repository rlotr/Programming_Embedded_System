#define Serial SerialUSB

// Define pin connections
const int potPin = A0; // Potentiometer connected to A0
const int ledPin = 2;  // LED connected to GPIO 2 (Pin 3)

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Initialize Serial Monitor at 9600 baud
}

void loop() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(potPin);

  // Convert raw ADC value to voltage (0V - 3.3V)
  float voltage = potValue * (3.3 / 1023.0);

  // Map potentiometer value (0-1023) to PWM range (0-255)
  int brightness = map(potValue, 0, 1023, 0, 255);

  // Set LED brightness using PWM
  analogWrite(ledPin, brightness);

  // Print values to Serial Monitor for debugging
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | LED Brightness: ");
  Serial.println(brightness);

  delay(100); // Smooth transition
}
