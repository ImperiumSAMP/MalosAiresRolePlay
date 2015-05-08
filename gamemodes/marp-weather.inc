#if defined _marp_weather_included
	#endinput
#endif
#define _marp_weather_included

#define INTERIOR_WEATHER_ID				1

#define MIN_TIME_WEATHER_CHANGE         5 // En horas
#define MAX_TIME_WEATHER_CHANGE         10 // En horas

enum WeatherInfo {
	wWeatherID,
	wNextWeatherID,
	wTimerID
};

new serverWeather[WeatherInfo];

SetServerWeather()
{
	serverWeather[wWeatherID] = random(19);
	serverWeather[wNextWeatherID] = random(19);
 	serverWeather[wTimerID] = SetTimer("WeatherAutoChange", (MIN_TIME_WEATHER_CHANGE + random(MAX_TIME_WEATHER_CHANGE - MIN_TIME_WEATHER_CHANGE)) * 60 * 60 * 1000, false);
}

GetNextServerWeather()
{
	return serverWeather[wNextWeatherID];
}

GetWeatherInfo(weatherid)
{
	new string[32];
	
	switch(weatherid)
	{
	    case 4, 7, 12, 15:
	        format(string, sizeof(string), "%s", "Nublado");
	    case 8, 16:
	        format(string, sizeof(string), "%s", "Lluvia");
	    case 9:
	        format(string, sizeof(string), "%s", "Niebla");
		case 17, 18:
	        format(string, sizeof(string), "%s", "Despejado con eclipse nocturno");
		default:
		    format(string, sizeof(string), "%s", "Despejado");
	}
	
	return string;
}

forward WeatherAutoChange();
public WeatherAutoChange()
{
	serverWeather[wWeatherID] = serverWeather[wNextWeatherID];
	serverWeather[wNextWeatherID] = random(19);
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
