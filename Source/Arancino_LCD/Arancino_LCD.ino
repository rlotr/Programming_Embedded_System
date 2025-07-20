
#include <LiquidCrystal.h>  // Library for LCD display

// GPIO pins for LCD display control

#define RS 8
#define ENABLE 4

#define DB4 3
#define DB5 10
#define DB6 11
#define DB7 38

// Initialize the library by associating any needed LCD interface pin 
// with the Arancino GPIO pin number it is connected to
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

void setup() {

  lcd.begin(16, 2);             // Set up 16 columns, 2 rows
  lcd.print("Hello, world!");   // Print on first line
  delay(2000);
  lcd.setCursor(0, 1);          // Move to second line
  lcd.print("LCD is working");

}

void loop() {
  // Nothing happens here
}
