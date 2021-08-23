#include <Arduino.h>
#include <Wire.h>
#include <XantoI2C.h>

#include "VM_IIC.h"
#include "display.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <neotimer.h>

#include "handlers.h"
#include "secrets.h"
#include "BaseAnimation.h"

const uint8_t PIN_SCL = 21;
const uint8_t PIN_SDA = 5;
const uint8_t PIN_LAMP = 22;
const uint8_t PIN_DISPLAY = 23;

//flag to use from web update to reboot the ESP
bool shouldReboot = false;

Display display(PIN_SDA, PIN_SCL, PIN_DISPLAY, PIN_LAMP);
BaseAnimation* animation = new BaseAnimation();

AsyncWebServer server(80); 

Neotimer mytimer = Neotimer(10);

void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  display.setDisplayPower(true);
  delay(200);
  display.clearDisplay();
  // Initialize WiFi connection
  display.setCursor(5,2);
  display.print("Connecting WiFi...");
  display.update();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  do  {
    wl_status_t status = WiFi.status();
    if (status == WL_CONNECTED) {
      break;
    }
    Serial.println(status);
    delay(500);
  } while(true);

  Serial.println("");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
  display.cls();
  display.setCursor(5,1);
  display.print("Online");
  display.setCursor(5,10);
  display.print("IP:");
  display.print(WiFi.localIP());
  display.update(); 
   
  server.on("/displayon", HTTP_GET, [](AsyncWebServerRequest *request){
    display.setDisplayPower(true);
    request->send(200, "text/plain", "Display on");
  });

  server.on("/displayoff", HTTP_GET, [](AsyncWebServerRequest *request){
    display.setDisplayPower(false);
    request->send(200, "text/plain", "Display off");
  });

  server.on("/lighton", HTTP_GET, [](AsyncWebServerRequest *request){
    display.setBacklightPower(true);
    request->send(200, "text/plain", "Light on");
  });

  server.on("/lightoff", HTTP_GET, [](AsyncWebServerRequest *request){
    display.setBacklightPower(false);
    request->send(200, "text/plain", "Light off");
  });

  server.on("/status", HTTP_GET, getStatusHandler);
  server.addHandler(postDataHandler);
  server.addHandler(postTextSmallHandler);
  server.addHandler(postTextBigHandler);
  server.addHandler(postBusHandler);
  server.addHandler(postClsHandler);
  server.addHandler(postTestHandler);
  server.addHandler(postStartGameOfLife);
  server.addHandler(postRunPacman);

  // attach filesystem root at URL /
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound(notFoundHandler);

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  Serial.println("HTTP server started");
  delay(100); 

  mytimer.start();
}

void loop() {
  if(shouldReboot){
    Serial.println("Rebooting...");
    delay(100);
    ESP.restart();
  }

  if(mytimer.repeat() && animation != NULL){
    if (animation->isActive) {
      animation->nextStep(display); 
    }
  }
}

