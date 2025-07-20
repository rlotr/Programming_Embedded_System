
#define Serial SerialUSB

// Include the necessary libraries
#include <DHT.h>

// Define the DHT11 sensor type
#define DHTTYPE DHT11

// Define the Arancino Mignon GPIO pin to which the DHT11 out is connected
#define DHTPIN 38

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {

    // Start serial communication for debugging
    Serial.begin(9600);
    
    // Initialize the DHT sensor
    dht.begin();
    
    // Print an initial message
    Serial.println("DHT11 Sensor Reading Started...");
        
}

void loop() {

    // Wait before reading again (DHT11 has a slow response time)
    delay(2000);
    
    // Read temperature and humidity
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();  // Celsius by default

    // Check if the readings are valid
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Print the values to the Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

}
