#include "weatherClient.h"
#include <ESP8266WiFi.h>
#include "wifi_secrets.h"
#include <ArduinoJson.h>

#define WUNDERGROUND "api.wunderground.com"

// HTTP request
const char WUNDERGROUND_REQ[] =
    "GET /api/" WG_KEY "/conditions/q/" WG_LOCATION ".json HTTP/1.1\r\n"
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: " WUNDERGROUND "\r\n"
    "Connection: close\r\n"
    "\r\n";

WeatherClient::WeatherClient()
{
    is_connected = false;
}

void WeatherClient::Begin()
{
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int retry_count = 20;

    while (WiFi.status() != WL_CONNECTED && retry_count--)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    if (WiFi.status() == WL_CONNECTED)
    {
        is_connected = true;
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        is_connected = false;
        Serial.println("WiFi connection failed.");
    }
}

#pragma align(4)
char respBuf[8192];

bool WeatherClient::GetWeatherData()
{
    // Open socket to WU server port 80
    Serial.print(F("Connecting to "));
    Serial.println(WUNDERGROUND);

    // Use WiFiClient class to create TCP connections
    WiFiClient httpclient;
    const int httpPort = 80;
    if (!httpclient.connect(WUNDERGROUND, httpPort))
    {
        Serial.println(F("connection failed"));
        return false;
    }

    // This will send the http request to the server
    Serial.print(WUNDERGROUND_REQ);
    httpclient.print(WUNDERGROUND_REQ);
    httpclient.flush();

    // Collect http response headers and content from Weather Underground
    // HTTP headers are discarded.
    // The content is formatted in JSON and is left in respBuf.
    int respLen = 0;
    bool skip_headers = true;

    Serial.println("Reading headers..");
    while (httpclient.connected() || httpclient.available())
    {
        String aLine = httpclient.readStringUntil('\n');
        Serial.println(aLine);
        delay(10);
        // Blank line denotes end of headers
        if (aLine.length() <= 1)
        {
            break;
        }
    }

    Serial.println("Reading body");

    while (httpclient.connected() || httpclient.available())
    {
        int bytesIn;
        int bufSize = sizeof(respBuf) - respLen;
        bytesIn = httpclient.read((uint8_t *)&respBuf[respLen], sizeof(respBuf) - respLen);
        if (bytesIn > 0)
        {
            respLen += bytesIn;
            if (respLen > sizeof(respBuf))
                respLen = sizeof(respBuf);
        }
        else if (bytesIn < 0)
        {
            Serial.print(F("read error "));
            Serial.println(bytesIn);
            delay(10);
        }
        delay(1);
    }

    httpclient.stop();

    if (respLen >= sizeof(respBuf))
    {
        Serial.print(F("respBuf overflow "));
        Serial.println(respLen);
        return false;
    }
    // Terminate the C string
    respBuf[respLen++] = '\0';
    Serial.print(F("respLen "));
    Serial.println(respLen);
    return ParseResponse(respBuf);
}

bool WeatherClient::ParseResponse(char *json)
{
    StaticJsonBuffer<3 * 1024> jsonBuffer;

    // Skip characters until first '{' found
    // Ignore chunked length, if present
    char *jsonstart = strchr(json, '{');

    //Serial.print(F("jsonstart ")); Serial.println(jsonstart);
    if (jsonstart == NULL)
    {
        Serial.println(F("JSON data missing"));
        return false;
    }
    json = jsonstart;

    // Parse JSON
    JsonObject &root = jsonBuffer.parseObject(json);
    if (!root.success())
    {
        Serial.println(F("jsonBuffer.parseObject() failed"));
        return false;
    }

    // Extract weather info from parsed JSON
    JsonObject &current = root["current_observation"];
    const float temp_f = current["temp_f"];
    Serial.print(temp_f, 1);
    Serial.print(F(" F, "));
    const float temp_c = current["temp_c"];
    Serial.print(temp_c, 1);
    Serial.print(F(" C, "));
    const char *humi = current[F("relative_humidity")];
    Serial.print(humi);
    Serial.println(F(" RH"));
    const char *weather = current["weather"];
    Serial.println(weather);
    const char *pressure_mb = current["pressure_mb"];
    Serial.println(pressure_mb);
    const char *observation_time = current["observation_time_rfc822"];
    Serial.println(observation_time);

    // Extract local timezone fields
    const char *local_tz_short = current["local_tz_short"];
    Serial.println(local_tz_short);
    const char *local_tz_long = current["local_tz_long"];
    Serial.println(local_tz_long);
    const char *local_tz_offset = current["local_tz_offset"];
    Serial.println(local_tz_offset);
    return true;
}