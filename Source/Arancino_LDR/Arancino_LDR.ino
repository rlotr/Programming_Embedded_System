#define Serial SerialUSB

// PIN Defintion
const int sensorPin = A0;  // LDR connected to analog pin A0
const int ledPin = 24;     // LED connected to GPIO 24

// LED On Threshold (can be calibrated based on the environment)
const int threshold = 500;  

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Read analog value (0-1023)
  float voltage = sensorValue * (3.3 / 1023.0); // Voltage conversion

  Serial.print("LDR Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH);  // Turns on the LED if there is low light
  } else {
    digitalWrite(ledPin, LOW);   // Turns off the LED if the light is sufficient
  }

  delay(500);  // Update time
}
