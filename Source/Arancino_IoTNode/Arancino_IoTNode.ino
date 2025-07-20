#include <defines.h>
#include <ESP_AT_Lib.h>
#include <DHT.h>
#include <RTCZero.h>

#define Serial SerialUSB

#define ESP_AT_BAUD    115200

#define SERVER_HOST   "192.168.1.78"
#define SERVER_PORT   5000
#define POST_PATH     "/"
#define GET_PATH      "/command"

#define TRANSMISSION_INTERVAL 15000UL  // 15 seconds

#define LEDPIN    4
#define DHTPIN    5
#define DHTTYPE   DHT11

// DHT sensor setup
DHT dht(DHTPIN, DHTTYPE);

// RTC object
RTCZero rtc;

unsigned long lastSendTime = 0;

// Date settings
const byte day = 1;
const byte month = 1;
const byte year = 25;

// Time settings
const byte hours = 12;
const byte minutes = 0;
const byte seconds = 0;

ESP8266 wifi(&EspSerial);

void sendSensorData() {

  static uint8_t mux_id = 0;

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor reading failed !");
    return;
  }

  char timestamp[20];
  snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d",
           rtc.getYear() + 2000,
           rtc.getMonth(),
           rtc.getDay(),
           rtc.getHours(),
           rtc.getMinutes(),
           rtc.getSeconds());

  String body = "timestamp=" + String(timestamp) +
                "&temp=" + String(temp, 1) +
                "&hum=" + String(hum, 1);

  String httpPOSTRequest =
    "POST " + String(POST_PATH) + " HTTP/1.1\r\n" +
    "Host: " + SERVER_HOST + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "Content-Length: " + String(body.length()) + "\r\n\r\n" +
    body;

    Serial.println("Sending POST Request : " + httpPOSTRequest);

    Serial.print("Create TCP to POST ");

    if (wifi.createTCP(mux_id, SERVER_HOST, SERVER_PORT))
    {
      Serial.println("OK");
    }
    else
    {
      Serial.println("failed");
    }
    
    const char* message = httpPOSTRequest.c_str();

    if (wifi.send(mux_id, (const uint8_t*)message, strlen(message)))
    {
      Serial.println("Send OK");
    }
    else
    {
      Serial.println("Send failed");
    }
    
    wifi.releaseTCP(mux_id);  
  
}

void checkCommandFromServer() {

  static uint8_t mux_id = 0;
  uint8_t buffer[128] = {0};
  String response = "";

  String httpGETRequest = "GET " + String(GET_PATH) + " HTTP/1.1\r\n" + "Host: " + SERVER_HOST + "\r\n\r\n";

  Serial.println("Sending GET  : " + httpGETRequest);

  Serial.println("Create TCP to GET ");

  if (wifi.createTCP(mux_id, SERVER_HOST, SERVER_PORT))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  const char* message = httpGETRequest.c_str();

  Serial.println("Send GET message : ");
  for (uint32_t i = 0; i < strlen(message); i++)
  {
    Serial.print((char) message[i]);
  }

  if (wifi.send(mux_id, (const uint8_t*)message, strlen(message)))
  {
    Serial.println("Send OK");
  }
  else
  {
    Serial.println("Send failed");
  }

  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);
  Serial.println((len));

  if ( len > 0 ) {

    for (uint32_t i = 0; i < len; i++) { response+=(char)buffer[i]; }
    response.trim();

    Serial.println("Server says : " + response);

    if (response.indexOf("LED=ON") != -1) {
      digitalWrite(LEDPIN, HIGH);
    } else if (response.indexOf("LED=OFF") != -1) {
      digitalWrite(LEDPIN, LOW);
    }

  }

  wifi.releaseTCP(mux_id);  

}

void setup()
{

  // Initialize a LED as actuator
  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,LOW);

  // Initialize DHT11 Sensor
  dht.begin();
  
  // Initialize RTC
  rtc.begin();
  rtc.setDate(day, month, year);
  rtc.setTime(hours, minutes, seconds);

  Serial.begin(115200);

  while (!Serial && millis() < 5000);

#if defined(BOARD_NAME)
  Serial.println("\nStart IoT node on " + String(BOARD_NAME));
#else
  Serial.println("\nStart IoT node");
#endif

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("Set STA Mode ");

  if (wifi.setOprToStation())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  if (wifi.joinAP(SSID, PASSWORD))
  {
    Serial.println("Connect to WiFi OK");

    delay(10000);

    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  }
  else
  {
    Serial.println("Connect to WiFi failed");
  }

  Serial.print("enableMUX ");
  
  if (wifi.enableMUX())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }
  
  Serial.println("Done");
}

void loop() {

  unsigned long now = millis();

  if (now - lastSendTime >= TRANSMISSION_INTERVAL) {

    lastSendTime = now;

    Serial.println("Send Sensor Data ---------------------------------------------------");
    sendSensorData();

    Serial.println("Check Command From Server ------------------------------------------");
    checkCommandFromServer();    

  }
	
}
