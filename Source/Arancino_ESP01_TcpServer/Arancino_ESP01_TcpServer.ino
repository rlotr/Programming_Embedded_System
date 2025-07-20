#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define ESP_AT_BAUD       115200

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

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP())
  {
    Serial.println("Set AP/STA Mode OK");
  }
  else
  {
    Serial.println("Set AP/STA Mode failed");
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

  if (wifi.startTCPServer(8090))
  {
    Serial.println("Start TCP server OK");
  }
  else
  {
    Serial.println("start TCP server failed");
  }

  if (wifi.setTCPServerTimeout(10))
  {
    Serial.println("Set TCP server timeout 10 seconds");
  }
  else
  {
    Serial.println("Set TCP server timeout failed");
  }

  Serial.println("Done");
}

void loop()
{
  uint8_t buffer[128] = {0};
  uint8_t mux_id;

  uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);

  if (len > 0)
  {
    Serial.print("Status:[");
    Serial.print(wifi.getIPStatus().c_str());
    Serial.println("]");

    Serial.print("Received from :");
    Serial.println(mux_id);
    Serial.print("[");

    for (uint32_t i = 0; i < len; i++)
    {
      Serial.print((char)buffer[i]);
    }

    Serial.println("]");

    if (wifi.send(mux_id, buffer, len))
    {
      Serial.println("Send back OK");
    }
    else
    {
      Serial.println("Send back failed");
    }

    if (wifi.releaseTCP(mux_id))
    {
      Serial.print("Release TCP ");
      Serial.print(mux_id);
      Serial.println(" OK");
    }
    else
    {
      Serial.print("Release TCP ");
      Serial.print(mux_id);
      Serial.println(" failed");
    }

    Serial.print("Status:[");
    Serial.print(wifi.getIPStatus().c_str());
    Serial.println("]");
  }
}
