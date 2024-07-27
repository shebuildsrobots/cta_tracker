/*
 * Adapted from ArduinoGetStarted.com.
 */

#include <WiFiS3.h>
#include <LiquidCrystal.h>

#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;  // your network SSID (name)
char pass[] = SECRET_PASS;  // your network password (use for WPA, or use as key for WEP)

WiFiClient client;
int status = WL_IDLE_STATUS;

int HTTP_PORT = 80;
String HTTP_METHOD = "GET";
char HOST_NAME[] = "lapi.transitchicago.com";
String PATH_NAME = "/api/1.0/ttarrivals.aspx";

// Pull the stopID you care about and sub here. 
// See CTA documentation at https://www.transitchicago.com/developers/ttdocs/#_Toc296199903.
String queryString = "&stpid=30169&max=1";

// Specify pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  // Specify screen size
  lcd.begin(16, 2);
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_NAME + "?key=" + API_KEY + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();  // end HTTP header

    while (client.connected()) {
      if (client.available()) {
        // Extract the fields we care about here. 
        // See CTA documentation at https://www.transitchicago.com/developers/ttdocs/#_Toc296199903.
          if(client.find("<staNm>")){
          String staNm = client.readStringUntil('<');
          Serial.println(staNm + String(" Station"));
          client.flush();
          lcd.print(staNm);
          }
          if(client.find("<stpDe>")){
          String stpDe = client.readStringUntil('<');
          Serial.println(stpDe);
          client.flush();
          }
          if(client.find("<arrT>")){
          String arrT = client.readStringUntil('<');
          Serial.println("Arriving at " + arrT);
          client.flush();
          // Move to next line
          lcd.setCursor(0,1);
          lcd.print(arrT);
          }
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {  // if not connected:
    Serial.println("connection failed");
  }
}

void loop() {
  // Pull as frequently as you'd like. 
}
