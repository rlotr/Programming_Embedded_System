// Define pin connections
const int ledPin = 12;    // LED connected to GPIO D12
const int buttonPin = 23; // Button connected to GPIO D23 

// Variables for button state tracking
bool ledState = false;  // LED is initially OFF


void setup() {
  pinMode(ledPin, OUTPUT); // Set LED as output
  //pinMode(buttonPin, INPUT_PULLDOWN); // Set button as input with pull-down resistor
  pinMode(buttonPin, INPUT); // Set button as input
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(50); // Debounce delay
    ledState = !ledState; // Toggle LED state
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    delay(300); // Prevent multiple toggles
  }
}