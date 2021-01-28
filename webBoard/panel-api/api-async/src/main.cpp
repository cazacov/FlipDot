#include <Arduino.h>
#include <Wire.h>
#include <XantoI2C.h>

#include "VM_IIC.h"
#include "display.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "secrets.h"

const uint8_t PIN_SCL = 21;
const uint8_t PIN_SDA = 5;
const uint8_t PIN_LAMP = 22;
const uint8_t PIN_DISPLAY = 23;

void onRequest(AsyncWebServerRequest *request){
  //Handle Unknown Request
  request->send(404);
}

//flag to use from web update to reboot the ESP
bool shouldReboot = false;

Display display(PIN_SDA, PIN_SCL, PIN_DISPLAY, PIN_LAMP);

AsyncWebServer server(80); 

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }


  // Initialize WiFi connection
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

  
  server.on("/displayon", HTTP_GET, [](AsyncWebServerRequest *request){
    display.displayOn();
    request->send(200, "text/plain", "Display on");
  });

  server.on("/displayoff", HTTP_GET, [](AsyncWebServerRequest *request){
    display.displayOff();
    request->send(200, "text/plain", "Display off");
  });
  
  // attach filesystem root at URL /
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound(onRequest);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  if(shouldReboot){
    Serial.println("Rebooting...");
    delay(100);
    ESP.restart();
  }
}

