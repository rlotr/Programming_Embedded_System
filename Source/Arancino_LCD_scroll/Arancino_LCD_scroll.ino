
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

// Long message to scroll
String message = "Welcome to Arancino Projects!";
int scrollDelay = 300;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Starting LCD...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Scroll the message from right to left
  for (int i = 0; i < message.length() - 15; i++) {
    lcd.setCursor(0, 0);
    lcd.print(message.substring(i, i + 16)); // Display 16 characters
    delay(scrollDelay);
  }

  // Pause and show another message on second row
  lcd.setCursor(0, 1);
  lcd.print("Let's begin!");
  delay(2000);

  // Clear and restart
  lcd.clear();
  delay(1000);
}
