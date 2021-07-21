#pragma once

#include "AsyncJson.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

extern AsyncCallbackJsonWebHandler* postDataHandler;
extern AsyncCallbackJsonWebHandler* postTextSmallHandler;
extern AsyncCallbackJsonWebHandler* postTextBigHandler;
extern AsyncCallbackJsonWebHandler* postTestHandler;
extern AsyncCallbackJsonWebHandler* postStartAutomaton;

void getStatusHandler(AsyncWebServerRequest* request);
void notFoundHandler(AsyncWebServerRequest* request);