// Define the pins for the LEDs
const int RedLedPin = 23; // GPIO 23 (Pin D23 on Arancino Connector)
const int GreenLedPin = 22; // GPIO 22 (Pin D22 on Arancino Connector)
const int YellowLedPin = 24; // GPIO 24 (Pin D24 on Arancino Connector)

void setup() {
  // Initialize each LED pin as an output
  pinMode(RedLedPin, OUTPUT);
  pinMode(GreenLedPin, OUTPUT);
  pinMode(YellowLedPin, OUTPUT);
  
  // Ensure all LEDs are off initially
  digitalWrite(RedLedPin, LOW);
  digitalWrite(GreenLedPin, LOW);
  digitalWrite(YellowLedPin, LOW);
  
}

void loop() {
    digitalWrite(RedLedPin, HIGH);    // Turn on the red LED
    digitalWrite(GreenLedPin, LOW);   // Turn off the green LED
    digitalWrite(YellowLedPin, LOW);  // Turn off the yellow LED
    delay(1000);                      // wait 1 seconds
     
    digitalWrite(RedLedPin, LOW);     // Turn off the red LED
    digitalWrite(GreenLedPin, HIGH);  // Turn on the green LED
    digitalWrite(YellowLedPin, LOW);  // Turn off the yellow LED
    delay(1000);                      // wait 1 seconds

    digitalWrite(RedLedPin, LOW);     // Turn off the red LED
    digitalWrite(GreenLedPin, LOW);   // Turn off the green LED
    digitalWrite(YellowLedPin, HIGH); // Turn on the yellow LED
    delay(1000);                      // wait 1 seconds

}
