#define Serial SerialUSB

// Pin assignment
const int trigPin = 5;   // Arancino GPIO Pin to set Sensor Trigger 
const int echoPin = 8;   // Arancino GPIO Pin to recive Sensor Echo

// Variables for distance calculating 
long duration;
float distance;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // We will use the serial monitor to display the distance
  Serial.begin(9600);
}

void loop() {

  // Make sure the trigger is LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 10µs HIGH pulse to start measurement
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Echo time reading (with timeout of 2900 µs ≈ 50 cm)
  duration = pulseIn(echoPin, HIGH, 2900UL);
  
  // Check if the timeout has occurred
  if (duration == 0) {
    Serial.println("Timeout: No object detected");
  } else {
    // Distance calculation in cm: (time in µs / 2) * speed of sound (0.0343 cm/µs)
    distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500); // waiting for next reading
}
