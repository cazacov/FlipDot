#ifndef WEATHERCLIENT_H_
#define WEATHERCLIENT_H_

enum WeatherIcon
{
    kUnknown,
    kSunny,
    kPartlyCloudy,
    kMostlyCloudy,
    kCloudy,
    kFog,
    kRain,
    kSnow,
    kThunderstorm
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