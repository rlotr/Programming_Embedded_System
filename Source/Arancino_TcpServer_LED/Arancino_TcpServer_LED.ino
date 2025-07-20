#include <defines.h>
#include <ESP_AT_Lib.h>

#define Serial SerialUSB

#define ESP_AT_BAUD   115200
#define PORT          8080

#define PIN_LED       5

bool ledState;
String command;
char replay[30];

ESP8266 wifi(&EspSerial);

void setup()
{

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  ledState=false;

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
  uint8_t mux_id;

  uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);

  if (len > 0)
  {

    Serial.print("Received from :");
    Serial.println(mux_id);
        
    command="";
    for (uint32_t i = 0; i < len; i++) { command+=(char)buffer[i]; }
    command.trim();

    Serial.println("Command : " + command);

    if (command=="LED-ON") {
      if ( !ledState ) {
        digitalWrite(PIN_LED, HIGH);
        ledState=true;
        strcpy(replay,"The LED is turned ON");
      } else {
        strcpy(replay,"The LED is already turned ON");
      }
    } 
    else if (command=="LED-OFF") {
      if ( ledState ) {
        digitalWrite(PIN_LED, LOW);
        ledState=false;
        strcpy(replay,"The LED is turned OFF");
      }else {
        strcpy(replay,"The LED is already turned OFF");
      }
    }
    else if (command=="STATUS") {
      if ( ledState ) {
        strcpy(replay,"The LED is ON");
      } else {
          strcpy(replay,"The LED is OFF");
      }
    }
    else {
      Serial.println("Unknow Command !");
      strcpy(replay,"Unknow Command !");
    }
  
    wifi.send(mux_id, (const uint8_t*)replay, strlen(replay));
    
  }

}
