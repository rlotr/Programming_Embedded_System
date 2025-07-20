
#include <LiquidCrystal.h>  // Library for LCD display
#include <DHT.h>            // Library for DHT sensor

#define DHTPIN 5       // DHT11 sensor GPIO pin
#define DHTTYPE DHT11  // Sensor type

// GPIO pins for LCD display control

#define RS 8
#define ENABLE 4

#define DB4 3
#define DB5 10
#define DB6 11
#define DB7 38

// DHT Sensor Initialization
DHT dht(DHTPIN, DHTTYPE);

// Initialize the library by associating any needed LCD interface pin 
// with the Arancino GPIO pin number it is connected to
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

void setup() {
    lcd.begin(16, 2);  // Set the display to 16 columns and 2 rows
    dht.begin();       // Start the DHT11 sensor

    lcd.print("Temp & Humidity");
    delay(2000);
    lcd.clear();
}

void loop() {
    float temp = dht.readTemperature();  // Temperature reading
    float hum = dht.readHumidity();      // Humidity reading

    if (isnan(temp) || isnan(hum)) {
        lcd.setCursor(0, 0);
        lcd.print("Sensor Error");
        return;
    }

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(hum);
    lcd.print("%");

    delay(2000); // Update every 2 seconds
}
