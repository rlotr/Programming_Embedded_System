// Define pin connections
const int ledPin = 12;    // LED connected to GPIO D12
const int buttonPin = 23; // Button connected to GPIO D23 

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED as output
  //pinMode(buttonPin, INPUT_PULLDOWN); // Set button as input with pull-down resistor
  pinMode(buttonPin, INPUT); // Set button as input
}

void loop() {
  // Read the button state
  int buttonState = digitalRead(buttonPin);

  // If the button is pressed, turn on the LED
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(50); // Small delay for stability
}
