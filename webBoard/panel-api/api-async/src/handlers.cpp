#include "handlers.h"
#include "base64.h"
#include "display.h"
extern Display display;

#include "fonts/bus_163_8x15.h"
#include "fonts/bus_169_6x7.h"

#define BIG_FONT bus_163_8x15
#define SMALL_FONT bus_169_6x7

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

void getStatusHandler(AsyncWebServerRequest* request) {
    StaticJsonDocument<500> data;
    data["displayPower"] = display.getDisplayPower() ? "true" : "false";
    data["backlightPower"] = display.getBacklightPower() ? "true" : "false";
    data["frameBuffer"] = base64encode(display.getPixels());
    
    String response;
    serializeJson(data, response);
    request->send(200, "application/json", response);
};