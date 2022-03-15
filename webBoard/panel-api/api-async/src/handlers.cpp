#include <cstdio>

#include "handlers.h"
#include "base64.h"
#include "display.h"
#include "CellAutomaton.h"
#include "pacman.h"
#include "CounterAnimation.h"
#include "newyearanimation.h"
extern Display display;
extern BaseAnimation* animation;
#include "utf2ascii.h"

#include "fonts/bus_163_8x15.h"
#include "fonts/bus_169_6x7.h"
#include "fonts/bus_numbers_171_6x15.h"
#include "fonts/bus_160_10x19.h"

#define BUS_19_FONT bus_160_10x19
#define BIG_FONT bus_163_8x15
#define SMALL_FONT bus_169_6x7
#define NUMBERS_FONT bus_numbers_171_6x15



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

  animation->end(display);
  if (data64) {
    Serial.print("Got new frameBuffer: ");
    Serial.println(data64);
    std::vector<uint8_t> frameBuffer = base64decode(data64);
    Serial.print("Buffer size: ");
    Serial.println(frameBuffer.size());
    display.setPixels(frameBuffer);
    request->send(200, "application/json", "{ \"accepted\": true }");
  }
  else {
    request->send(400, "application/json", "{ \"error\": \"Invalid request\" }");
  }
});

AsyncCallbackJsonWebHandler* postDataBlockHandler = new AsyncCallbackJsonWebHandler("/datablock", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  
  uint16_t top = jsonDoc["top"];
  uint16_t left = jsonDoc["left"];
  uint16_t width = jsonDoc["width"];
  uint16_t height = jsonDoc["height"];

  // left and width msut be multiples of 8
  left &= 0xFFF8;
  width &= 0xFFF8;
 
  const char* data64 = jsonDoc["frameBuffer"];
  animation->end(display);
  if (data64) {
    Serial.print("Got new frameBuffer: ");
    Serial.println(data64);
    std::vector<uint8_t> frameBuffer = base64decode(data64);
    Serial.print("Buffer size: ");
    Serial.println(frameBuffer.size());
    char buf[100];
    sprintf(buf, "Left: %d,\tTop: %d,\tWidth: %d,\tHeight: %d", left, top, width, height);
    Serial.println(buf);
    display.setPixelBlock(left, top, width, height, frameBuffer);
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
  String line1 = utf8ascii(jsonDoc["line1"]);
  String line2 = utf8ascii(jsonDoc["line2"]);


  Serial.println("Text SMALL");
  Serial.println(line1.c_str());
  Serial.println(line2.c_str());

  animation->end(display);
  display.cls();
  display.setFont(&SMALL_FONT);
  display.setCursor(0,7);
  display.print(line1.c_str());
  display.setCursor(0,17);
  display.print(line2.c_str());
  display.update();
  display.setFont();

  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postTextBigHandler = new AsyncCallbackJsonWebHandler("/textBig", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<600> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  String text = utf8ascii(jsonDoc["text"]);
  //text = utf8ascii(text);

  Serial.println("Text BIG");
  Serial.println(text.c_str());

  animation->end(display);
  display.cls();
  display.setFont(&BIG_FONT);
  display.setCursor(0,16);
  display.print(text.c_str());
  display.update();
  display.setFont();

  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postTestHandler = new AsyncCallbackJsonWebHandler("/test", [](AsyncWebServerRequest *request, JsonVariant &json) {
  animation->end(display);
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

void notFoundHandler(AsyncWebServerRequest* request) {
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
};

AsyncCallbackJsonWebHandler* postStartGameOfLife = new AsyncCallbackJsonWebHandler("/gameoflife", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  std::string text = jsonDoc["closed"];
  boolean isClosed = (text == "true");
  Serial.println("Start animation");
  
  if (animation != NULL) {
    delete animation;
  }

  auto cellAnimation = new CellAutomaton();
  animation = cellAnimation;
  cellAnimation->begin(display, isClosed);
 
  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postRunPacman = new AsyncCallbackJsonWebHandler("/pacman", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  
  Serial.println("Run pacman");
  
  if (animation != NULL) {
    delete animation;
  }

  animation = new Pacman();
  animation->begin(display);
 
  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postStartCounter = new AsyncCallbackJsonWebHandler("/counter", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  
  Serial.println("Start Counter");
  
  if (animation != NULL) {

    delete animation;
  }
  auto counterAnimation = new CounterAnimation();
  animation = counterAnimation;
  display.cls();
  display.setFont(&BIG_FONT);
  display.setCursor(0,16);
  display.print("K8s costs");
  counterAnimation->begin(display, 138, 123456);
 
  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postClsHandler = new AsyncCallbackJsonWebHandler("/cls", [](AsyncWebServerRequest *request, JsonVariant &json) {
  animation->end(display);
  Serial.println("CLS");
  display.cls();
  display.update();
  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postBusHandler = new AsyncCallbackJsonWebHandler("/bus", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  int route = jsonDoc["route"].as<int>();
  String glyph = jsonDoc["glyph"].as<String>();
  String line1 = utf8ascii(jsonDoc["line1"].as<String>());
  String line2 = utf8ascii(jsonDoc["line2"].as<String>());

  animation->end(display);
  display.cls();

  if (glyph != "null") {
    display.setFont(&BUS_19_FONT);
    display.setCursor(0,18);
    if (glyph == "chess") {
      glyph = "\x82";
    } else if (glyph == "children") {
      glyph = "\x83";  
    } else if (glyph == "sport") {
      glyph = "\x88";  
    } else if (glyph == "tram") {
      glyph = "\x8B";  
    } else if (glyph == "sbahn") {
      glyph = "\x8C";  
    } else if (glyph == "PR") {
      glyph = "\x9D";  
    } else if (glyph == "fill") {
      glyph = "\xD8";  
    } else if (glyph == "chess2") {
      glyph = "\xD9";  
    } else if (glyph == "NE") {
      glyph = "\xE2";  
    } else if (glyph == "SB") {
      glyph = "\xE4";  
    } else if (glyph == "CE") {
      glyph = "\xE5";  
    } else if (glyph == "DB") {
      glyph = "\xE6";  
    } else if (glyph == "city") {
      glyph = "\xE7";  
    }
    else {
      glyph = utf8ascii(glyph);
    }
    display.print(glyph);
  } else if (route > 0) {
    display.setFont(&NUMBERS_FONT);
    display.setCursor(0,16);
    display.print(route);
  }
  display.setFont(&SMALL_FONT);
  display.setCursor(34,7);
  display.print(line1.c_str());
  display.setCursor(34,17);
  display.print(line2.c_str());
  display.update();
  display.setFont();

  request->send(200, "application/json", "{ \"accepted\": true }");
});

AsyncCallbackJsonWebHandler* postStartNewYear = new AsyncCallbackJsonWebHandler("/newyear", [](AsyncWebServerRequest *request, JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  
  Serial.println("Let it snow!");
  
  if (animation != NULL) {
    delete animation;
  }

  animation = new NewYear();
  animation->begin(display);
 
  request->send(200, "application/json", "{ \"accepted\": true }");
});