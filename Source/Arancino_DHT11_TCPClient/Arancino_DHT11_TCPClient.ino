#include <defines.h>
#include <ESP_AT_Lib.h>
#include <DHT.h>
#include <RTCZero.h>

#define Serial SerialUSB

#define ESP_AT_BAUD       115200

#define SERVER_IP   "192.168.1.78"
#define SERVER_PORT   8080

#define TRANSMISSION_INTERVAL 60000UL  // 1 minute

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

void setup()
{

  // Initialize DHT11 Sensor
  dht.begin();
  
  // Initialize RTC
  rtc.begin();
  rtc.setDate(day, month, year);
  rtc.setTime(hours, minutes, seconds);

  Serial.begin(115200);

  while (!Serial && millis() < 5000);

#if defined(BOARD_NAME)
  Serial.println("\nStart TCPClientSingle on " + String(BOARD_NAME));
#else
  Serial.println("\nStart TCPClientSingle");
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

  static uint8_t mux_id = 0;
  unsigned long now = millis();

  if (now - lastSendTime >= TRANSMISSION_INTERVAL) {

    lastSendTime = now;

    // Read DHT sensor
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      delay(2000);
      return;
    }

    // Build timestamp string
    String date = String(rtc.getDay()) + "/" + String(rtc.getMonth()) + "/" + String(2000 + rtc.getYear());
    String time = String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" + String(rtc.getSeconds());
    
    String message = "[" + String(date) + " " + String(time) + "] ";
    message += "TEMP=" + String(temp, 1) + "C | HUM=" + String(hum, 1) + "%\n";

    Serial.print("Sending: ");
    Serial.print(message);
    
    // ---------------------------------------------------

    Serial.print("Create TCP ");

    if (wifi.createTCP(mux_id, SERVER_IP, SERVER_PORT))
    {
      Serial.println("OK");
    }
    else
    {
      Serial.println("failed");
    }
    
    const char* mess = message.c_str();

    if (wifi.send(mux_id, (const uint8_t*)mess, strlen(mess)))
    {
      Serial.println("Send OK");
    }
    else
    {
      Serial.println("Send failed");
    }
    
    wifi.releaseTCP(mux_id);  
  
    // ---------------------------------------------------

  }
	
}
