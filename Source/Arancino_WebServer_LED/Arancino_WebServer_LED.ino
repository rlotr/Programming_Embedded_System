
#include "defines.h"
#include <ESP_AT_Lib.h>         // Low-level AT command communication
#include <WiFiEspAT.h>          // Simplified WiFi layer based on ESP_AT_Lib
#include <WiFiWebServer.h>      // HTTP server wrapper compatible with AT-based modules

#define LED_PIN 5               // Define the GPIO pin connected to the LED

int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 0;                // number of requests received

bool ledState = false;

WiFiWebServer server(80);

// Function that returns the HTML content for the web page
String htmlPage() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<title>LED Control</title>";
  html += "</head><body>";
  html += "<h2>Remote LED Control</h2>";
  html += "<form action='/led' method='GET'>";
  html += "<button type='submit' name='state' value='ON'>Turn ON</button>";
  html += "<button type='submit' name='state' value='OFF'>Turn OFF</button>";
  html += "</form>";
  html += "<p>Current LED state: ";
  html += ledState ? "ON" : "OFF";  // Dynamically shows current LED state
  html += "</p></body></html>";
  return html;
}

// Handler for the root path ("/") – serves the HTML page
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

// Handler for "/led?state=ON" or "/led?state=OFF"
void handleLedControl() {
  // Check if the URL has a query parameter "state"
  if (server.hasArg("state")) {
    String state = server.arg("state");

    // Compare the parameter and act accordingly
    if (state == "ON") {
      digitalWrite(LED_PIN, HIGH);   // Turn LED ON
      ledState = true;
    } else if (state == "OFF") {
      digitalWrite(LED_PIN, LOW);    // Turn LED OFF
      ledState = false;
    }
  }

  // After changing the LED state, redirect back to the home page
  server.sendHeader("Location", "/");
  server.send(303);  // HTTP 303 = "See Other"
}


void setup()
{

  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  while(!Serial);

#if WIFI_USING_ESP_AT

  // initialize serial for ESP module
  EspSerial.begin(115200);
  // initialize ESP module
  WiFi.init(&EspSerial);

#endif

#if !(ESP32 || ESP8266)

  // check for the presence of the shield
#if USE_WIFI_NINA

  if (WiFi.status() == WL_NO_MODULE)
#else
  if (WiFi.status() == WL_NO_SHIELD)
#endif
  {
    // don't continue
    while (true);
  }

#endif

  status = WiFi.begin(ssid, pass);

  delay(1000);

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED)
  {
    delay(500);
    // Connect to WPA/WPA2 network
    status = WiFi.status();
  }

  // Define URL routes and their corresponding handlers
  server.on("/", handleRoot);           // Main page
  server.on("/led", handleLedControl);  // Form submission

  // Start the HTTP server
  server.begin();

}

void loop()
{
  server.handleClient();    // Check for new HTTP requests
}
