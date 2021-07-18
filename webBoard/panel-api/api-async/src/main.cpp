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

#include "fonts/bus_163_8x15.h"
#include "fonts/bus_169_6x7.h"

#include <string>

#include "AsyncJson.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

//#include <Fonts/FreeSans9pt7b.h>
#define BIG_FONT bus_163_8x15
#define SMALL_FONT bus_169_6x7


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

AsyncCallbackJsonWebHandler* postTextSmallHandler = new AsyncCallbackJsonWebHandler("/textSmall", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  std::string line1 = jsonDoc["line1"];
  std::string line2 = jsonDoc["line2"];


  Serial.println("Text SMALL");
  Serial.println(line1.c_str());
  Serial.println(line2.c_str());

  display.cls();
  display.setFont(&SMALL_FONT);
  display.setCursor(0,8);
  display.print(line1.c_str());
  display.setCursor(0,17);
  display.print(line2.c_str());
  display.update();
  display.setFont();

  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postTextBigHandler = new AsyncCallbackJsonWebHandler("/textBig", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  std::string text = jsonDoc["text"];

  Serial.println("Text BIG");
  Serial.println(text.c_str());

  display.cls();
  display.setFont(&BIG_FONT);
  display.setCursor(0,16);
  display.print(text.c_str());
  display.update();
  display.setFont();

  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postTestHandler = new AsyncCallbackJsonWebHandler("/test", [](AsyncWebServerRequest *request, JsonVariant &json) {
  Serial.println("Test");
  display.test();
  request->send(200, "application/json", "{ \"accepted\": true }");
});

void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  delay(100);

  display.setDisplayPower(true);
  delay(200);
  display.clearDisplay();
  delay(500);

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
    delay(1000);
  } while(true);

  Serial.println("");
  Serial.println("WiFi connected successfully");
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

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    StaticJsonDocument<500> data;
    data["displayPower"] = display.getDisplayPower() ? "true" : "false";
    data["backlightPower"] = display.getBacklightPower() ? "true" : "false";
    data["frameBuffer"] = base64encode(display.getPixels());
    
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
  });

  server.addHandler(postDataHandler);
  server.addHandler(postTextSmallHandler);
  server.addHandler(postTextBigHandler);
  server.addHandler(postTestHandler);

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

