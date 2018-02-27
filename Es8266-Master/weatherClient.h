#ifndef WEATHERCLIENT_H_
#define WEATHERCLIENT_H_


class WeatherClient
{
private:
    bool ParseResponse(char* response);    
    bool is_connected;
public:
    WeatherClient();
    void Begin();
    bool GetWeatherData();
private:
};

#endif