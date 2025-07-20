
#define Serial SerialUSB

const int pinLed = 2;
int value = 0;  //valore pwm

void setup() {
  Serial.begin(9600);       //inizializzo la seriale
  pinMode(pinLed, OUTPUT);  //setto il pin pwm come uscita

}

void loop() {
  //faccio crescere partendo da zero il valore del duty cycle fino al suo massimo
  for (value = 0; value < 255; value ++) {
    
    analogWrite(pinLed, value);
    Serial.println(value);

    delay(50);
    
  }
  delay(2000);
  //faccio diminuire, partendo dal suo massimo, il valore del duty cycle fino al suo minimo
  for (value = 255; value > 0 ; value --) {
    
    analogWrite(pinLed, value);
    Serial.println(value);

    delay(50);
    
  }

  

}
