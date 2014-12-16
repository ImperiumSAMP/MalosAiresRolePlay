#if defined _isamp_gangzones_included
	#endinput
#endif
#define _isamp_gangzones_included

//===========================SISTEMA DE BARRIOS=================================

//=================================DEFINES======================================

#define MAX_GANGZONES           8

#define GANGZONE_CAPTURE_TIME   600 // En segundos, 10 min. Lo que tienen que mantenerse dentro para capturarlo.
#define GANGZONE_CAPTURE_UPDATE 5 // En segundos, cada cuanto actualiza el sistema mientras están en guerra.
#define GANGZONE_REDISPUTE_TIME 18000 // En segundos, 5 horas. Tiempo hasta que un barrio pueda ser recapturado.
#define GANGZONE_HOLDING_TIME   28800 // En segundos, 8 horas. Tiempo máximo que puede mantener una faccion el dominio.

#define GANGZONE_NUNEZ          0
#define GANGZONE_LA_BOCA        1
#define GANGZONE_EL_CORONA      2
#define GANGZONE_VILLA_LATA     3
#define GANGZONE_FUERTE_APACHE  4
#define GANGZONE_AVELLANEDA     5
#define GANGZONE_WILLOWFIELD    6
#define GANGZONE_SEVILLE_BEACH  7

//==================================NEWS========================================

enum GangZoneInfo {
	gzID,
	gzFaction,
	gzDisputed
};

new GangZone[MAX_GANGZONES][GangZoneInfo];
new GangZoneWarCountdownTimer[MAX_GANGZONES];
new GangZoneWarCountdown[MAX_GANGZONES];
new GangZoneWarEndTimer[MAX_GANGZONES];
new IsFactionTakingGangZone[MAX_FACTIONS];
new EndGangZoneHoldingFactionTimer[MAX_GANGZONES];

CMD:tomarbarrio(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], gangzonefaction, gangzone, cont1 = 0, cont2 = 0;

	if(faction == 0)
	    return 1;
 	if(FactionInfo[faction][fType] != FAC_TYPE_GANG)
 	    return 1;
	if(PlayerInfo[playerid][pRank] != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Para iniciar la toma de un barrio debes ser el lider de la facción.");
	if(IsFactionTakingGangZone[faction] == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu facción ya está tomando un barrio en estos momentos.");
	gangzone = GetPlayerGangZone(playerid);
	if(gangzone == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en ningún barrio de conflicto.");
	gangzonefaction = GangZone[gangzone][gzFaction];
	if(gangzonefaction == faction)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Esta zona ya se encuentra bajo tu dominio.");
    if(GangZone[gangzone][gzDisputed] == 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Este barrio ha estado en disputa hace poco tiempo, espera un tiempo para reclamarlo.");

	foreach(new i : Player)
	{
		if(gangzonefaction != 0 && PlayerInfo[i][pFaction] == gangzonefaction)
	    	cont1 ++;
		else
	        if(PlayerInfo[i][pFaction] == faction)
			{
	 		    if(GetPlayerGangZone(i) == gangzone)
	   				cont2 ++;
			}
	}
 	if(gangzonefaction != 0 && cont1 < 2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debe haber al menos dos integrantes conectados de la facción que domina este barrio.");
	if(cont2 < 4)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Deben ser al menos cuatro personas de la facción para tomar un barrio.");

    foreach(new i : Player)
	{
	    if(PlayerInfo[i][pFaction] == faction)
	    {
	        SendFMessage(i, COLOR_PMA, "[DISPUTA]: %s ha iniciado una toma de un barrio. Se marcará y titilará en el mapa hasta que termine.", GetPlayerNameEx(playerid));
			GangZoneFlashForPlayer(i, GangZone[gangzone][gzID], 0xFFFFFF77);
		} else
		    if(gangzonefaction != 0 && PlayerInfo[i][pFaction] == gangzonefaction)
 	    	{
		        SendClientMessage(i, COLOR_PMA, "[DISPUTA]: Están tomando nuestro barrio. Se marcará y titilará en el mapa hasta que termine.");
				GangZoneFlashForPlayer(i, GangZone[gangzone][gzID], 0xFFFFFF77);
			}
	}
	GangZone[gangzone][gzDisputed] = 1;
	IsFactionTakingGangZone[faction] = 1;
	SetTimerEx("EnableGangZoneDispute", GANGZONE_REDISPUTE_TIME * 1000, false, "i", gangzone);
	GangZoneWarCountdownTimer[gangzone] = SetTimerEx("GangZoneWar", GANGZONE_CAPTURE_UPDATE * 1000, true, "ii", gangzone, faction);
	return 1;
}

forward EndGangZoneHoldingFaction(gangzone);
public EndGangZoneHoldingFaction(gangzone)
{
	GangZone[gangzone][gzFaction] = 0;
	foreach(new playerid : Player)
	{
	    if(PlayerInfo[playerid][pFaction] != 0)
	    {
	        if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_GANG)
	        {
  			    HideGangZonesToPlayer(playerid);
			    ShowGangZonesToPlayer(playerid); // Para actualizarlo a color gris, es decir, a barrio sin dueño
	        }
		}
	}
	return 1;
}

forward EnableGangZoneDispute(gangzone);
public EnableGangZoneDispute(gangzone)
{
	GangZone[gangzone][gzDisputed] = 0;
	return 1;
}

forward GangZoneWar(gangzone, faction);
public GangZoneWar(gangzone, faction)
{
	new cont = 0, Float:health;

	foreach(new playerid : Player)
	{
 		if(PlayerInfo[playerid][pFaction] == faction)
		{
	 		if(GetPlayerGangZone(playerid) == gangzone)
	 		{
			 	GetPlayerHealthEx(playerid, health);
				if(health > 25.0)
	   				cont ++;
			}
		}
	}
 	if(cont < 2 && GangZoneWarEndTimer[gangzone] == 0)
 	{
 		SendFactionMessage(faction, COLOR_PMA, "[DISPUTA]: Se necesita mas gente dentro de la zona o perderán el barrio en 30 segundos.");
		GangZoneWarEndTimer[gangzone] = SetTimerEx("EndGangZoneWar", 30 * 1000, false, "iii", gangzone, faction, 2);
	} else
		if(cont >= 2 && GangZoneWarEndTimer[gangzone] != 0)
		{
 			SendFactionMessage(faction, COLOR_PMA, "[DISPUTA]: ¡Bien! Seguimos con la toma del barrio.");
 			KillTimer(GangZoneWarEndTimer[gangzone]);
 			GangZoneWarEndTimer[gangzone] = 0;
		}

	GangZoneWarCountdown[gangzone] += 5;
	if(GangZoneWarCountdown[gangzone] >= GANGZONE_CAPTURE_TIME)
	{
	    if(cont >= 2)
	    	EndGangZoneWar(gangzone, faction, 1);
		else
	        EndGangZoneWar(gangzone, faction, 2);
	}
	return 1;
}

forward EndGangZoneWar(gangzone, faction, endingtype);
public EndGangZoneWar(gangzone, faction, endingtype)
{
	KillTimer(GangZoneWarCountdownTimer[gangzone]);
	KillTimer(GangZoneWarEndTimer[gangzone]);
	GangZoneWarCountdownTimer[gangzone] = 0;
	GangZoneWarCountdown[gangzone] = 0;
	GangZoneWarEndTimer[gangzone] = 0;
	IsFactionTakingGangZone[faction] = 0;
	new defenderfaction = GangZone[gangzone][gzFaction];
	switch(endingtype)
	{
	    case 1:
	    {
	        GangZone[gangzone][gzFaction] = faction;
			foreach(new playerid : Player)
			{
				if(defenderfaction != 0 && PlayerInfo[playerid][pFaction] == defenderfaction)
				{
			    	SendClientMessage(playerid, COLOR_PMA, "[DISPUTA]: Hemos perdido el control del barrio.");
			    	GangZoneStopFlashForPlayer(playerid, GangZone[gangzone][gzID]);
			    	HideGangZonesToPlayer(playerid);
			    	ShowGangZonesToPlayer(playerid); // Para actualizarlo con el nuevo color de la nueva faccion
				}
				else
			        if(PlayerInfo[playerid][pFaction] == faction)
			        {
                        SendClientMessage(playerid, COLOR_PMA, "[DISPUTA]: ¡Bien, el barrio es nuestro! Debemos mantenerlo bajo control y nos dará buen dinero.");
                        GangZoneStopFlashForPlayer(playerid, GangZone[gangzone][gzID]);
                        HideGangZonesToPlayer(playerid);
                        ShowGangZonesToPlayer(playerid); // Para actualizarlo con el nuevo color de la nueva faccion
                        if(EndGangZoneHoldingFactionTimer[gangzone] != 0)
                            KillTimer(EndGangZoneHoldingFactionTimer[gangzone]);
                       	SetTimerEx("EndGangZoneHoldingFaction", GANGZONE_HOLDING_TIME * 1000, false, "i", gangzone);
					}
			}
		}
		case 2:
	    {
			foreach(new playerid : Player)
			{
				if(defenderfaction != 0 && PlayerInfo[playerid][pFaction] == defenderfaction)
				{
			    	SendClientMessage(playerid, COLOR_PMA, "[DISPUTA]: ¡Bien, hemos defendido el barrio con éxito y sigue siendo nuestro!");
                    GangZoneStopFlashForPlayer(playerid, GangZone[gangzone][gzID]);
                    if(EndGangZoneHoldingFactionTimer[gangzone] != 0)
                    	KillTimer(EndGangZoneHoldingFactionTimer[gangzone]);
                   	SetTimerEx("EndGangZoneHoldingFaction", GANGZONE_HOLDING_TIME * 1000, false, "i", gangzone);
				}
				else
			        if(PlayerInfo[playerid][pFaction] == faction)
			        {
                        SendClientMessage(playerid, COLOR_PMA, "[DISPUTA]: La disputa se ha acabado, no hemos podido tomar el barrio.");
                        GangZoneStopFlashForPlayer(playerid, GangZone[gangzone][gzID]);
					}
			}
		}
	}
	return 1;
}

stock HideGangZonesToPlayer(playerid)
{
    for(new i = 0; i < MAX_GANGZONES; i++)
    {
        GangZoneHideForPlayer(playerid, GangZone[i][gzID]);
	}
	return 1;
}

stock ShowGangZonesToPlayer(playerid)
{
	for(new i = 0; i < MAX_GANGZONES; i++)
	{
		switch(GangZone[i][gzFaction])
		{
		    case 0: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0x00000077);
			case 11: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0x0000FF77);
			case 12: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0x00FF0077);
			case 13: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0xFF000077);
			case 14: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0xFFFF0077);
			case 15: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0x00FFFF77);
			default: GangZoneShowForPlayer(playerid, GangZone[i][gzID], 0x00000077);
		}
	}
	return 1;
}

stock LoadGangZones()
{
	GangZone[GANGZONE_NUNEZ][gzID] = GangZoneCreate(1828.318, -1310.774, 2117.333, -1054.171);
	GangZone[GANGZONE_LA_BOCA][gzID] = GangZoneCreate(2337.898, -1741.078, 2531.842, -1622.646);
	GangZone[GANGZONE_EL_CORONA][gzID] = GangZoneCreate(1813.106, -2183.225, 1965.22, -1954.256);
	GangZone[GANGZONE_VILLA_LATA][gzID] = GangZoneCreate(1527.894, -2187.173, 1813.106, -2084.531);
	GangZone[GANGZONE_FUERTE_APACHE][gzID] = GangZoneCreate(1991.839, -1764.764, 2200.996, -1527.9);
	GangZone[GANGZONE_AVELLANEDA][gzID] = GangZoneCreate(2109.728, -1219.976, 2326.489, -971.2684);
	GangZone[GANGZONE_WILLOWFIELD][gzID] = GangZoneCreate(2204.798, -2060.845, 2531.842, -1875.301);
	GangZone[GANGZONE_SEVILLE_BEACH][gzID] = GangZoneCreate(2604.096, -2060.845, 2786.632, -1902.935);
	return 1;
}

stock GetPlayerGangZone(playerid)
{
	new Float:px, Float:py, Float:pz;

	GetPlayerPos(playerid, px, py, pz);

	if(px >= 1828.318 && px <= 2117.333 && py >= -1310.774 && py <= -1054.171) return GANGZONE_NUNEZ;
	if(px >= 2337.898 && px <= 2531.842 && py >= -1741.078 && py <= -1622.646) return GANGZONE_LA_BOCA;
	if(px >= 1813.106 && px <= 1965.220 && py >= -2183.225 && py <= -1954.256) return GANGZONE_EL_CORONA;
	if(px >= 1527.894 && px <= 1813.106 && py >= -2187.173 && py <= -2084.531) return GANGZONE_VILLA_LATA;
	if(px >= 1991.839 && px <= 2200.996 && py >= -1764.764 && py <= -1527.900) return GANGZONE_FUERTE_APACHE;
	if(px >= 2109.728 && px <= 2326.489 && py >= -1219.976 && py <= -971.2684) return GANGZONE_AVELLANEDA;
	if(px >= 2204.798 && px <= 2531.842 && py >= -2060.845 && py <= -1875.301) return GANGZONE_WILLOWFIELD;
	if(px >= 2604.096 && px <= 2786.632 && py >= -2060.845 && py <= -1902.935) return GANGZONE_SEVILLE_BEACH;

	return -1;
}

stock GetGangZoneLiderIncome(playerid)
{
	new income = 0;
 	for(new i = 0; i < MAX_GANGZONES; i++)
	{
		if(GangZone[i][gzFaction] == PlayerInfo[playerid][pFaction])
		{
			income += 500;
		}
	}
	return income;
}

stock DestroyGangZones()
{
	GangZoneDestroy(GangZone[GANGZONE_NUNEZ][gzID]);
	GangZoneDestroy(GangZone[GANGZONE_LA_BOCA][gzID]);
	GangZoneDestroy(GangZone[GANGZONE_EL_CORONA][gzID]);
	GangZoneDestroy(GangZone[GANGZONE_VILLA_LATA][gzID]);
	GangZoneDestroy(GangZone[GANGZONE_FUERTE_APACHE][gzID]);
	GangZoneDestroy(GangZone[GANGZONE_AVELLANEDA][gzID]);
 	GangZoneDestroy(GangZone[GANGZONE_WILLOWFIELD][gzID]);
 	GangZoneDestroy(GangZone[GANGZONE_SEVILLE_BEACH][gzID]);
	return 1;
}
