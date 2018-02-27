#ifndef WEATHERCLIENT_H_
#define WEATHERCLIENT_H_

enum WeatherIcon
{
    kSunny,
    kPartlyCloudy,
    kMostlyCloudy,
    kCloudy,
    kFog,
    kRain,
    kSnow,
    kThunderstorms,
    kUnknown
};

class WeatherClient
{
private:
    bool ParseResponse(char* response);    
    bool is_connected;
public:
    WeatherClient();
    void Begin();
    bool GetWeatherData();
    float temperature_current;
    WeatherIcon weather_icon;
private:
};

#endif