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
#include "base64.h"

#include "AsyncJson.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

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

AsyncCallbackJsonWebHandler* postDataHandler = new AsyncCallbackJsonWebHandler("/data", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  const char* data64 = jsonDoc["frameBuffer"];

  if (data64) {
    Serial.print("Got new frameBuffer: ");
    Serial.print(data64);
    std::vector<uint8_t> frameBuffer = base64decode(data64);
    display.setPixels(frameBuffer);
    request->send(200, "application/json", "{ \"accepted\": true }");
  }
  else {
    request->send(400, "application/json", "{ \"error\": \"Invalid request\" }");
  }
});


void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  delay(100);

  display.displayOn();
  delay(200);
  display.clearDisplay();
  delay(500);

  // Initialize WiFi connection
  
  
  display.print("WiFi: ");
  display.print(WIFI_SSID);
  display.update();
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
  display.setCursor(0,8);
  display.print("IP:");
  display.print(WiFi.localIP());
  display.update(); 
   
  server.on("/displayon", HTTP_GET, [](AsyncWebServerRequest *request){
    display.displayOn();
    request->send(200, "text/plain", "Display on");
  });

  server.on("/displayoff", HTTP_GET, [](AsyncWebServerRequest *request){
    display.displayOff();
    request->send(200, "text/plain", "Display off");
  });

  server.on("/lighton", HTTP_GET, [](AsyncWebServerRequest *request){
    display.backlightOn();
    request->send(200, "text/plain", "Light on");
  });

  server.on("/lightoff", HTTP_GET, [](AsyncWebServerRequest *request){
    display.backlightOff();
    request->send(200, "text/plain", "Light off");
  });

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){

    StaticJsonDocument<500> data;
    data["frameBuffer"] = base64encode(display.getPixels());
    
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
  });

  server.addHandler(postDataHandler);

  // attach filesystem root at URL /
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound([](AsyncWebServerRequest *request) {
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
  });

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
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

