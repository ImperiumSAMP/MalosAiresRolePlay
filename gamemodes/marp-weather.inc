#if defined _marp_weather_included
	#endinput
#endif
#define _marp_weather_included

#define INTERIOR_WEATHER_ID				1

#define MIN_TIME_WEATHER_CHANGE         5 // En horas
#define MAX_TIME_WEATHER_CHANGE         20 // En horas

enum WeatherInfo {
	wWeatherID,
	wTimerID
};

new serverWeather[WeatherInfo];

SetServerWeather()
{
	serverWeather[wWeatherID] = random(19);
 	serverWeather[wTimerID] = SetTimer("WeatherAutoChange", (MIN_TIME_WEATHER_CHANGE + random(MAX_TIME_WEATHER_CHANGE - MIN_TIME_WEATHER_CHANGE)) * 60 * 60 * 1000, false);
}

forward WeatherAutoChange();
public WeatherAutoChange()
{
	serverWeather[wWeatherID] = random(19);
	serverWeather[wTimerID] = SetTimer("WeatherAutoChange", (MIN_TIME_WEATHER_CHANGE + random(MAX_TIME_WEATHER_CHANGE - MIN_TIME_WEATHER_CHANGE)) * 60 * 60 * 1000, false);
 	SyncWeatherForAll();
	return 1;
}

SyncWeatherForAll()
{
	foreach(new i : Player)
	{
		if(!GetPlayerInterior(i))
			SetPlayerWeather(i, serverWeather[wWeatherID]);
	}
}

SyncPlayerWeather(playerid)
{
	if(!GetPlayerInterior(playerid) && !GetPlayerVirtualWorld(playerid))
		SetPlayerWeather(playerid, serverWeather[wWeatherID]);
	else
		SetPlayerWeather(playerid, INTERIOR_WEATHER_ID);
}

CMD:clima(playerid, params[])
{
	new weather;

	if(sscanf(params, "i", weather))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /clima [ID clima]");
	if(weather < -500 || weather > 500)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de clima inválida (de -500 a 500).");

	serverWeather[wWeatherID] = weather;
	KillTimer(serverWeather[wTimerID]);
	serverWeather[wTimerID] = SetTimer("WeatherAutoChange", (MIN_TIME_WEATHER_CHANGE + random(MAX_TIME_WEATHER_CHANGE - MIN_TIME_WEATHER_CHANGE)) * 60 * 60 * 1000, false);
	SyncWeatherForAll();
	return 1;
}
