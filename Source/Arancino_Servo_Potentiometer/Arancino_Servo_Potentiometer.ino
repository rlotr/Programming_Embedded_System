#include <Servo.h>          // includes Servo Library

Servo myservo;              // create servo object to control servo motor

const int servoPin = 2;     // define the pin of servo signal line, in this case the Arancino PWM output pin 
const int potPin = A0;      // analog pin used to connect the potentiometer
int potVal;                 // variable to read the potentiometer value from the analog pin

void setup() {

  myservo.attach(servoPin); // attaches the servo on servoPin to the servo object

}

void loop() {

  potVal = analogRead(potPin);            // reads the potentiometer value from the analog pin

  potVal = map(potVal, 0, 1023, 0, 180);  // scale it to use it with the servo

  myservo.write(potVal);                  // sets the servo position

  delay(15);                              // waits for the servo to get there

}
