#include <LiquidCrystal.h>

// GPIO pins for LCD display control

#define RS 8
#define ENABLE 4

#define DB4 38
#define DB5 3
#define DB6 6
#define DB7 7

// Initialize the library by associating any needed LCD interface pin 
// with the Arancino GPIO pin number it is connected to
LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

// Define ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 29;

// Define LED pin for "GO!" signal
const int ledPin  = 24;

// Variables for distance measurement
long duration;
float distance;
float initialDistance;

// Variables for timing
unsigned long startTime;
unsigned long reactionTime;

// Distance variation threshold to detect movement (in cm)
const float tolerance = 5.0;

void setup() {
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW); // Turn off LED

  // Initialize the LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  lcd.print("Reflex Game Ready");
  delay(2000); // Show welcome message
  lcd.clear();
}

void loop() {
  // --- PHASE 1: WAIT FOR PLAYER'S HAND ---
  lcd.setCursor(0, 0);
  lcd.print("Place hand at");
  lcd.setCursor(0, 1);
  lcd.print("10-15 cm...");

  // Continuously check until hand is in position
  initialDistance = readDistance();
  while (initialDistance < 10 || initialDistance > 15) {
    initialDistance = readDistance();
    delay(100);
  }

  // Notify player to get ready
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Get ready...");
  delay(1000);

  // --- PHASE 2: RANDOM WAIT BEFORE "GO!" ---
  int waitTime = random(2000, 5000); // 2 to 5 seconds
  delay(waitTime);

  // --- PHASE 3: "GO!" SIGNAL ---
  digitalWrite(ledPin, HIGH); // Turn on LED as signal
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GO!");

  // Record time when signal is given
  startTime = millis();

  // --- PHASE 4: WAIT FOR HAND TO MOVE ---
  while (true) {
    distance = readDistance();

    // If distance changes beyond threshold, detect reaction
    if (abs(distance - initialDistance) > tolerance) {
      reactionTime = millis() - startTime;
      digitalWrite(ledPin, LOW); // Turn off LED

      // Display result on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reaction time:");
      lcd.setCursor(0, 1);
      lcd.print(reactionTime);
      lcd.print(" ms");

      break;
    }
    delay(10); // Sampling delay
  }

  // Wait before starting a new round
  delay(3000);
}

// --- Function to read distance from HC-SR04 ---
float readDistance() {
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure pulse duration on ECHO pin
  duration = pulseIn(echoPin, HIGH, 20000); // Timeout: 20 ms (~3.4 m)

  // If no echo, return 0
  if (duration == 0) return 0;

  // Convert time to distance in cm
  return (duration * 0.0343) / 2;
}
