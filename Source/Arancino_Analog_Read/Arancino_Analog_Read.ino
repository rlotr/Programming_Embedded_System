
#define Serial SerialUSB

const int potPin = A0; // Potentiometer connected to A0

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int potValue = analogRead(potPin); // Read the potentiometer value (0-1023)
  float voltage = potValue * (3.3 / 1024.0); // Convert to voltage (3.3V max)
  
  // Print the raw value and corresponding voltage to the Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(500); // Wait 500 ms before the next reading
}
