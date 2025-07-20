#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

// Your board <-> ESP_AT baud rate:
#define ESP_AT_BAUD       115200

const char host[] = "webhook.site";
const uint16_t port = 80;
const char path[] = "/3b927abd-479c-4326-b19b-6855ecc62631";


ESP8266 wifi(&EspSerial);

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(1000);

#if defined(BOARD_NAME)
  Serial.println("\nStart HTTPGET on " + String(BOARD_NAME));
#else
  Serial.println("\nStart HTTPGET");
#endif

  Serial.println(ESP_AT_LIB_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  Serial.print("Set AP/STA Mode ");

  if (wifi.setOprToStationSoftAP())
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  if (wifi.joinAP(SSID, PASSWORD))
  {

    delay(5000);

    Serial.println("Connect to WiFi OK");
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
    Serial.println("enableMUX OK");
  }
  else
  {
    Serial.println("enableMUX failed");
  }

  Serial.println("Done");
}


void loop()
{

  static uint8_t mux_id = 0;
  
  Serial.print("Create TCP ");

  if (wifi.createTCP(mux_id, host, port))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  randomSeed(millis());
  float temperature = random(10,40);
  float humidity = random(10,90);

  String payload = "{\"temperature\":";
  payload += String(temperature);
  payload += ",\"humidity\":";
  payload += String(humidity);
  payload += "}";


  String httpRequest;
  httpRequest += "POST " + String(path) + " HTTP/1.1\r\n";
  httpRequest += "Host: " + String(host) + "\r\n";
  httpRequest += "Content-Type: application/json\r\n";
  httpRequest += "Content-Length: " + String(payload.length()) + "\r\n";
  httpRequest += "Connection: close\r\n\r\n";
  httpRequest += payload;

  char message[httpRequest.length()+1];
  strcpy(message, httpRequest.c_str()); 

  Serial.println(httpRequest);

  wifi.send(mux_id, (const uint8_t*)message, strlen(message));


  delay(10000);
}
