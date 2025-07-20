/*

Temperature-Based DC Fan Speed Control (DHT11 + L293D)

*/

#include <DHT.h>

#define Serial SerialUSB   // For debug purpose

// Define the DHT11 sensor
#define DHTPIN 38          // DHT11 data pin connected to GPIO D38
#define DHTTYPE DHT11      // Define sensor type
DHT dht(DHTPIN, DHTTYPE);  // Create DHT object

// Define motor control pins (connected to L293D inputs)
const int enable1Pin = 11;  // Define Arancino PWM Output to L293D enable 1 pin

void setup() {
  Serial.begin(9600);       // Start serial communication for debugging
  dht.begin();              // Initialize the DHT sensor
}

void loop() {
  // Read temperature from the DHT11 sensor
  float temperature = dht.readTemperature(); // Returns temperature in Celsius

  // Check if reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT11");
    delay(2000);
    return; // Skip this loop iteration if reading failed
  }

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Define threshold values for temperature-based control
  const float Tmin = 25.0;   // Minimum temperature before the fan starts
  const float Tmax = 40.0;   // Maximum temperature for full fan speed

  int pwmValue;              // PWM value to control motor speed (0–255)

  // Map temperature to PWM output
  if (temperature < Tmin) {
    pwmValue = 0;  // Fan off
  } else if (temperature > Tmax) {
    pwmValue = 255; // Fan at full speed
  } else {
    // Scale temperature between Tmin and Tmax to a PWM range
    // Starting from 100 avoids weak PWM signals that can cause stuttering
    pwmValue = map(temperature, Tmin, Tmax, 100, 255);
  }

  // Apply PWM signal to control fan speed
  analogWrite(enable1Pin, pwmValue);

  delay(2000); // Wait 2 seconds before next reading
}
