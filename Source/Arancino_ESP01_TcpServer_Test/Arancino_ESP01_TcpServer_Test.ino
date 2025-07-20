#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define ESP_AT_BAUD   115200
#define PORT          8080

ESP8266 wifi(&EspSerial);

void setup()
{

  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(1000);

#if defined(BOARD_NAME)
  Serial.println("\nStart TCPServer on " + String(BOARD_NAME));
#else
  Serial.println("\nStart TCPServer");
#endif

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  if (wifi.setOprToStation())
  {
    Serial.println("Set STA Mode OK");
  }
  else
  {
    Serial.println("Set STA Mode failed");
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

  if (wifi.enableMUX())
  {
    Serial.println("enableMUX OK");
  }
  else
  {
    Serial.println("enableMUX failed");
  }

  if (wifi.startTCPServer(PORT))
  {
    Serial.println("Start TCP server on port " +String(PORT)+" OK");
  }
  else
  {
    Serial.println("start TCP server failed");
  }

  Serial.println("Done");
}

void loop()
{
  uint8_t buffer[128] = {0};
  uint8_t replay[128] = {0};
  uint8_t mux_id;

  uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);

  if (len > 0)
  {
    Serial.print("Status:[");
    Serial.print(wifi.getIPStatus().c_str());
    Serial.print("]");
    Serial.println("");

    Serial.print("Received from :");
    Serial.println(mux_id);
    Serial.print("[");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char)buffer[i]);
    }

    Serial.print("]");
    Serial.println("");

    String mess = "Hello from ESP-01 TCP server!";
    mess.getBytes(replay, mess.length());

    if (wifi.send(mux_id, replay, sizeof(replay)))
    {
      Serial.println("Send back OK");
    }
    else
    {
      Serial.println("Send back failed");
    }

    wifi.releaseTCP(mux_id);

    Serial.print("Status:[");
    Serial.print(wifi.getIPStatus().c_str());
    Serial.print("]");
    Serial.println("");

  }
}
