/*

Datalogger with Arancino Mignon that:
  - Reads data from a DHT11 sensor
  - Periodically records data on a microSD card via SPI interface
  - Save data in a CSV file

SD card attached to SPI bus as follows:
  MISO - pin 22 on Arancino Mignon
  MOSI - pin 23 on Arancino Mignon
  SCK - pin 24 on Arancino Mignon
  CS - pin 9 on Arancino Mignon

*/

#include <SPI.h>      // library for SPI protocol management
#include <SD.h>       // library for SD card module management
#include <DHT.h>

#define Serial SerialUSB

// Pin definitions
const int DHTPin = 38;
const int chipSelect = 9; // CS pin for SD card module

// DHT sensor setup
#define DHTTYPE DHT11
DHT dht(DHTPin, DHTTYPE);

// File object
File dataFile;

void setup() {

  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
  Serial.println("SD Card ready.");

  // Optional: Create/open the file and add headers if needed
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Temperature (C),Humidity (%)");
    dataFile.close();
  } else {
    Serial.println("Error opening file!");
  }

}

void loop() {

  // Read sensor values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Open file to append data
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(temperature);
    dataFile.print(",");
    dataFile.println(humidity);
    dataFile.close();
    Serial.println("Data written to SD card.");
  } else {
    Serial.println("Error opening file for writing.");
  }

  delay(5000); // Log every 5 seconds
  
}
