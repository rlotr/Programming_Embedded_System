
#define Serial SerialUSB

#define MOTOR_PIN 2             // D2 PWM Output Digital Pin
#define BUTTON_PIN 4            // D4 GPIO Digital Pin
#define POTENTIOMETER_PIN A0    // Analog Input Pin
#define BOOT_TIME 500

bool buttonPressed = false;
int lastButtonState = LOW;
unsigned long startTime = 0;
int motorSpeed;

void setup(){
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop(){
  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != lastButtonState && buttonState == HIGH){
    if(!buttonPressed){
      startTime = millis();
    }
    buttonPressed = !buttonPressed;
  }
  lastButtonState = buttonState;

  if(buttonPressed){
    if((millis()-startTime) > BOOT_TIME){
      motorSpeed = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 100, 255);
      analogWrite(MOTOR_PIN, motorSpeed);
    }else{
      analogWrite(MOTOR_PIN, 255);
    }
  }else{
    analogWrite(MOTOR_PIN, 0);
  }

  Serial.print("Motor: ");
  Serial.print(buttonPressed ? "ON" : "OFF");
  Serial.print(" | PWM: ");
  Serial.println(motorSpeed);

  delay(50);
}
