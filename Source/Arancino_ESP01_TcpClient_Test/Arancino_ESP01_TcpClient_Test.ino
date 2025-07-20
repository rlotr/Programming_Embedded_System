#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define ESP_AT_BAUD       115200

#define SERVER_IP   "192.168.1.78"
#define SERVER_PORT   8080

ESP8266 wifi(&EspSerial);

void setup(void)
{
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

void loop()
{
  uint8_t buffer[128] = {0};

  static uint8_t mux_id = 0;

  Serial.print("Create TCP ");

  if (wifi.createTCP(mux_id, SERVER_IP, SERVER_PORT))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("failed");
  }

  char hello[] = "Hello, this is Arancino client!";

  if (wifi.send(mux_id, (const uint8_t*)hello, strlen(hello)))
  {
    Serial.println("Send OK");
  }
  else
  {
    Serial.println("Send failed");
  }

  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);

  if (len > 0)
  {
    Serial.print("Received:[");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char)buffer[i]);
    }

    Serial.println("]");
  }

  wifi.releaseTCP(mux_id);

  delay(5000);
}
