
/*

Arancino Mignon datalogger on MicroSD with timestamp

*/

#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <RTCZero.h>

#define Serial SerialUSB
#define DHTTYPE DHT11

// Pin definitions
const int DHTPin = 38;
const int chipSelect = 9;

// DHT sensor setup
DHT dht(DHTPin, DHTTYPE);

// RTC object
RTCZero rtc;

// File object
File dataFile;

// Date settings
const byte day = 1;
const byte month = 1;
const byte year = 25;

// Time settings
const byte hours = 12;
const byte minutes = 0;
const byte seconds = 0;

void setup() {

  Serial.begin(9600);
  dht.begin();

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
  Serial.println("SD Card ready.");

  // Initialize RTC
  rtc.begin();
  rtc.setDate(day, month, year);
  rtc.setTime(hours, minutes, seconds);
  
  // Create/open the file and write header if first run
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Date,Time,Temperature (C),Humidity (%)");
    dataFile.close();
  } else {
    Serial.println("Error opening file!");
  }
}

void loop() {

  // Read DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Build timestamp string
  String date = String(rtc.getDay()) + "/" + String(rtc.getMonth()) + "/" + String(2000 + rtc.getYear());
  String time = String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" + String(rtc.getSeconds());

  // Write to SD
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(date);
    dataFile.print(",");
    dataFile.print(time);
    dataFile.print(",");
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
