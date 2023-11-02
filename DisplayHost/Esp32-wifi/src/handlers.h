#pragma once

#include "AsyncJson.h"
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

extern AsyncCallbackJsonWebHandler* postDataHandler;
extern AsyncCallbackJsonWebHandler* postDataBlockHandler;
extern AsyncCallbackJsonWebHandler* postTextSmallHandler;
extern AsyncCallbackJsonWebHandler* postTextBigHandler;
extern AsyncCallbackJsonWebHandler* postTextAddHandler;
extern AsyncCallbackJsonWebHandler* postBusHandler;
extern AsyncCallbackJsonWebHandler* postClsHandler;
extern AsyncCallbackJsonWebHandler* postTestHandler;
extern AsyncCallbackJsonWebHandler* postSetBlockHandler;
extern AsyncCallbackJsonWebHandler* postStartGameOfLife;
extern AsyncCallbackJsonWebHandler* postRunPacman;
extern AsyncCallbackJsonWebHandler* postStartCounter;
extern AsyncCallbackJsonWebHandler* postStartNewYear;
extern AsyncCallbackJsonWebHandler* postStartWaiting;

void getStatusHandler(AsyncWebServerRequest* request);
void notFoundHandler(AsyncWebServerRequest* request);