#include <Servo.h>          // includes Servo Library

Servo myservo;              // create servo object to control servo motor

const int pos = 0;          // initializes a variable whose value will be the position to be given to the servo
const int servoPin = 2;     // define the pin of servo signal line, in this case the Arancino PWM output pin 

void setup() {

  myservo.attach(servoPin); // attaches the servo on servoPin to the servo object

}

void loop() {

  // set a loop that goes from 0 degrees to 180 degrees in steps of 1 degree
  for (pos = 0; pos <= 180; pos += 1) { 

    // tell servo to go to position in variable "pos"
    myservo.write(pos);

    // waits 15ms for the servo to reach the position
    delay(15);                       

  }

  // repeats the previous loop in reverse goes from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    delay(15);
  }

}
