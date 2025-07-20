#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define ESP_AT_BAUD       115200

ESP8266 wifi(&EspSerial);

void setup() {

  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(1000);

#if defined(BOARD_NAME)
  Serial.println("\nStart ConnectWiFi on " + String(BOARD_NAME));
#else
  Serial.println("\nStart ConnectWiFi");
#endif

  Serial.println(ESP_AT_LIB_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());
  Serial.println("\n");

  Serial.println(wifi.getAPList());

  if (wifi.setOprToStation())
  {
    Serial.println("Set STA Mode OK");
  }
  else
  {
    Serial.println("Set STA Mode failed");
  }
  Serial.println(wifi.getOprMode());

  if (wifi.joinAP(SSID, PASSWORD))
  {
    Serial.println("Connect to WiFi OK");
    
  }
  else
  {
    Serial.println("Connect to WiFi failed");
  }

  delay(10000);

  Serial.print("IP: ");
  Serial.println(wifi.getLocalIP().c_str());

  Serial.println("Done");

}

void loop() {
 

}
