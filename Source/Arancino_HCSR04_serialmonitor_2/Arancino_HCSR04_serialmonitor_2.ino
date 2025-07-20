#define Serial SerialUSB

const int trigPin = 5;
const int echoPin = 8;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measures echo time with timeout at 6000 µs (~102 cm)
  duration = pulseIn(echoPin, HIGH, 6000);  

  // If timeout expired → no objects detected in the maximum range
  if (duration == 0) {
    Serial.println("No objects within range");
  } else {
    // Distance calculation
    distance = (duration * 0.0343) / 2;

    // Apply a condition to only intercept objects from 20 cm to 100 cm away
    if (distance >= 20 && distance <= 100) {
      Serial.print("Object detected at ");
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      Serial.print("Object out of range: ");
      Serial.print(distance);
      Serial.println(" cm (ignored)");
    }
  }

  delay(500);
}
