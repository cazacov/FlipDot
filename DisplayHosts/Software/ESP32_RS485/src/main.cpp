#include <Arduino.h>
#include <Wire.h>
#include <XantoI2C.h>

#include "VM_IIC.h"
#include "display.h"

#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

const uint8_t PIN_SCL = 21;
const uint8_t PIN_SDA = 5;
const uint8_t PIN_LAMP = 22;
const uint8_t PIN_DISPLAY = 23;

void handle_root();
void handle_display_on();
void handle_display_off();

Display display(PIN_SDA, PIN_SCL, PIN_DISPLAY, PIN_LAMP);

WebServer server(80); 

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  do  {
    wl_status_t status = WiFi.status();
    if (status == WL_CONNECTED) {
      break;
    }
    Serial.println(status);
    delay(1000);
  } while(true);

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root);
  server.on("/displayon", handle_display_on);
  server.on("/displayoff", handle_display_off);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}

void handle_display_on() {
  Serial.print("display on");
  display.displayOn();
  server.send(200, "text/plain", "Display on");
}

void handle_display_off() {
  Serial.print("display off");
  display.displayOff();
  server.send(200, "text/plain", "Display off");
}