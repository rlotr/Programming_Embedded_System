#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define HOST_NAME   "arduino.tips"        //"www.yahoo.com"
//#define HOST_NAME   "www.yahoo.com"
#define HOST_PORT   80

// Your board <-> ESP_AT baud rate:
#define ESP_AT_BAUD       115200

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

uint8_t buffer[2048] = {0};

void loop()
{
  static uint8_t mux_id = 0;
  
  Serial.print("Create TCP ");

  if (wifi.createTCP(mux_id, HOST_NAME, HOST_PORT))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  //char hello[] = "GET / HTTP/1.1\r\nHost: www.yahoo.com\r\nConnection: close\r\n\r\n";
  char hello[] = "GET /asciilogo.txt HTTP/1.1\r\nHost: arduino.tips\r\nConnection: close\r\n\r\n";

  wifi.send(mux_id, (const uint8_t*)hello, strlen(hello));

  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);

  if (len > 0)
  {
    Serial.println("=========================Received============================");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char) buffer[i]);
    }

    Serial.println("\n============================================================");
  }

  delay(5000);

  if (wifi.releaseTCP(mux_id))
  {
    Serial.println("Release TCP OK");
  } else {
    Serial.println("Release TCP failed");

  }

  //while (1);
  delay(10000);
}
