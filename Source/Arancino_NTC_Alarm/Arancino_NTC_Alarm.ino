
#define Serial SerialUSB

// PIN Definition
const int sensorPin = A0;   // Thermistor on A0 analog pin
const int ledPin = 10;      // Blinking LED on GPIO D10
const int buzzerPin = 38;   // Buzzer on GPIO D38

// Thermistor constants
const float BETA = 3950;  // Thermistor Beta Coefficient
const float T0 = 298.15;  // Reference temperature (Kelvin)
const float R0 = 10000;   // Thermistor nominal resistance at 25°C

// Temperature thresholds (in Celsius)
const float thresholdTempHigh = 40.0;  // Alarm activation threshold
const float thresholdTempLow = 38.0;   // Alarm shutdown threshold

bool alarmActive = false;  // Initial alarm state

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  // Reading temperature from thermistor
  float temperature = readTemperature();

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // If the temperature exceeds the activation threshold, it turns on the alarm 
  if (temperature > thresholdTempHigh) {
    alarmActive = true;
  } 
  // If the temperature drops below the shutdown threshold, it turns off the alarm
  else if (temperature < thresholdTempLow) {
    alarmActive = false;
  }

  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH);
    blinkLED();
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}

// Function to read temperature from thermistor
float readTemperature() {

  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (3.3 / 1023.0);  // Conversion to voltage

  // Calculating thermistor resistance
  float resistance = (3.3 * R0 / voltage) - 10000;

  // Temperature calculation with the Steinhart-Hart formula
  float temperature = 1.0 / (1.0 / T0 + (1.0 / BETA) * log(resistance)) - 273.15;
  
  return temperature;

}

// Function to blink the LED when the alarm is active
void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  }
}
