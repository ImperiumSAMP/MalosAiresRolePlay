#if defined _isamp_racesystem_included
	#endinput
#endif
#define _isamp_racesystem_included

//=================================DEFINES======================================

#define MAX_SERVER_RACES        3
#define MAX_RACE_CHECKPOINTS	20
#define MAX_RACE_DRIVERS        8

//================================VARIABLES=====================================

enum rRaceInfo {
	rCreatorID,
	rDriversID[MAX_RACE_DRIVERS],
	rCheckpointsCount,
	rLaps,
	rWinner,
 	bool:rStarted
};

new Float:TrackInfo[MAX_SERVER_RACES][MAX_RACE_CHECKPOINTS][3];
new RaceInfo[MAX_SERVER_RACES][rRaceInfo];

enum pPlayerRaceInfo {
	pRaceID,
	pLap,
	pCheckpointCount,
	pRaceOffer
};

new PlayerRaceInfo[MAX_PLAYERS][pPlayerRaceInfo];

//================================FUNCIONES=====================================

forward ResetPlayerRaceVariables(playerid);
forward ResetServerRacesVariables();
forward CancelRaceOffer(playerid);
forward OnPlayerLeaveRace(playerid);

//=============================RESET VARIABLES==================================

stock ResetServerRacesVariables()
{
	for(new i = 0; i < MAX_SERVER_RACES; i++)
 		ResetRaceVariables(i);
}

stock ResetRaceVariables(raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
	    if(RaceInfo[raceid][rCreatorID] != INVALID_PLAYER_ID)
	    {
	        ResetPlayerRaceVariables(RaceInfo[raceid][rCreatorID]);
	    	RaceInfo[raceid][rCreatorID] = INVALID_PLAYER_ID;
		}
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
		    {
		        ResetPlayerRaceVariables(RaceInfo[raceid][rDriversID][i]);
            	RaceInfo[raceid][rDriversID][i] = INVALID_PLAYER_ID;
	 		}
		}
		RaceInfo[raceid][rCheckpointsCount] = 0;
		RaceInfo[raceid][rLaps] = 0;
		RaceInfo[raceid][rWinner] = INVALID_PLAYER_ID;
		RaceInfo[raceid][rStarted] = false;
	}
}

stock ResetPlayerRaceVariables(playerid)
{
    PlayerRaceInfo[playerid][pRaceID] = -1;
    PlayerRaceInfo[playerid][pLap] = 0;
    PlayerRaceInfo[playerid][pCheckpointCount] = 0;
    PlayerRaceInfo[playerid][pRaceOffer] = INVALID_PLAYER_ID;
}

stock RaceMessage(raceid, color, const string[])
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
 		SendClientMessage(RaceInfo[raceid][rCreatorID], color, string);
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
			SendClientMessage(RaceInfo[raceid][rDriversID][i], color, string);
	}
	return 1;
}

public OnPlayerLeaveRace(playerid)
{
    if(PlayerRaceInfo[playerid][pRaceID] != -1)
    {
        new str[128];
        
        if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] == playerid)
        {
			format(str, sizeof(str), "[Carrera]: La carrera ha sido eliminada ya que el organizador %s se ha desconectado.", GetPlayerNameEx(playerid));
			RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
			ResetRaceVariables(PlayerRaceInfo[playerid][pRaceID]);
		} else
		    {
		        format(str, sizeof(str), "[Carrera]: %s ha sido removido de la carrera ya que se ha desconectado.", GetPlayerNameEx(playerid));
                RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
				DeleteRaceDriver(playerid, PlayerRaceInfo[playerid][pRaceID]);
			}
	}
	return 1;
}
    

//============================DEBUG DE VARIABLES================================


CMD:racedebug(playerid, params[])
{
	new id;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", id))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /racedebug [raceid]");
	if(id < 0 || id >= MAX_SERVER_RACES)
        return SendClientMessage(playerid, COLOR_YELLOW2, "ID invalida.");
        
	SendFMessage(playerid, COLOR_YELLOW, "rCreatorID [%d] = %d", id, RaceInfo[id][rCreatorID]);
	for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		SendFMessage(playerid, COLOR_YELLOW, "rDriversID [%d][%d] = %d", id, i, RaceInfo[id][rDriversID][i]);
	SendFMessage(playerid, COLOR_YELLOW, "rCheckpointCounter [%d] = %d", id, RaceInfo[id][rCheckpointsCount]);
	SendFMessage(playerid, COLOR_YELLOW, "rLaps [%d] = %d", id, RaceInfo[id][rLaps]);
	SendFMessage(playerid, COLOR_YELLOW, "rWinner [%d] = %d", id, RaceInfo[id][rWinner]);
	SendFMessage(playerid, COLOR_YELLOW, "rStarted [%d] = %b", id, RaceInfo[id][rStarted]);
	for(new x = 0; x < MAX_RACE_CHECKPOINTS; x++)
	    SendFMessage(playerid, COLOR_YELLOW, "TrackInfo [%d][%d] = %.1f , %.1f , %.1f", id, x, TrackInfo[id][x][0], TrackInfo[id][x][1], TrackInfo[id][x][2]);
	return 1;
}

CMD:playerracedebug(playerid, params[])
{
	new id;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", id))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /playerracedebug [playerid]");
	if(id < 0 || id >= MAX_PLAYERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID invalida.");
	    
	SendFMessage(playerid, COLOR_YELLOW, "pRaceID [%d] = %d", id, PlayerRaceInfo[id][pRaceID]);
	SendFMessage(playerid, COLOR_YELLOW, "pLap [%d] = %d", id, PlayerRaceInfo[id][pLap]);
	SendFMessage(playerid, COLOR_YELLOW, "pCheckpointCount [%d] = %d", id, PlayerRaceInfo[id][pCheckpointCount]);
	SendFMessage(playerid, COLOR_YELLOW, "pRaceOffer [%d] = %d", id, PlayerRaceInfo[id][pRaceOffer]);
	return 1;
}

//============================SISTEMA DE CARRERAS===============================

CMD:carreraayuda(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Sistema de carreras]: /carreracrear - /carrerainfo - /carreraeliminar - /carreravueltas - /carreranuevocp");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/carreraborrarcp - /carrerainvitar - /carreraaceptar - /carreraexpulsar - /carrerainiciar - /carreraabandonar");
	return 1;
}

stock bool:CreateRace(playerid)
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	{
		for(new i = 0; i < MAX_SERVER_RACES; i++)
		{
		    if(RaceInfo[i][rCreatorID] == INVALID_PLAYER_ID)
		    {
		        ResetRaceVariables(i);
		        RaceInfo[i][rCreatorID] = playerid;
		        PlayerRaceInfo[playerid][pRaceID] = i;
		        return true;
			}
		}
	}
	return false;
}

CMD:carreracrear(playerid, params[])
{
    if(PlayerInfo[playerid][pLevel] < 15)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Para organizar carreras debes ser un usuario experimentado en el servidor ((Nivel 15)).");
	if(PlayerRaceInfo[playerid][pRaceID] != -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras en una carrera.");
	if(CreateRace(playerid))
	    SendClientMessage(playerid, COLOR_WHITE, "Has creado una carrera. Para ver la lista de comandos disponibles usa /carreraayuda.");
	else
        SendClientMessage(playerid, COLOR_YELLOW2, "No hay mas espacio para carreras en el servidor: hay otras corriendose en este momento.");
	return 1;
}

CMD:carreraeliminar(playerid, params[])
{
	new str[128];
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;

	format(str, sizeof(str), "[Carrera]: El organizador %s ha eliminado la carrera.", GetPlayerNameEx(playerid));
    RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
	ResetRaceVariables(PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock SetRaceLaps(raceid, laps)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
		RaceInfo[raceid][rLaps] = laps;
}

CMD:carreravueltas(playerid, params[])
{
	new laps, str[128];
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
 	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	if(sscanf(params, "i", laps))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreravueltas [nro de vueltas] (1-50)");
	if(laps < 1 || laps > 50)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreravueltas [nro de vueltas] (1-50)");

	format(str, sizeof(str), "[Carrera]: El organizador %s ha seteado la carrera en %d vueltas.", GetPlayerNameEx(playerid), laps);
    RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
	SetRaceLaps(PlayerRaceInfo[playerid][pRaceID], laps);
	return 1;
}

stock AddNewRaceCheckpoint(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
 		if(RaceInfo[raceid][rCheckpointsCount] < MAX_RACE_CHECKPOINTS)
		{
			new Float:xpos, Float:ypos, Float:zpos;
			GetPlayerPos(playerid, xpos, ypos, zpos);
			TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][0] = xpos;
		 	TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][1] = ypos;
		    TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][2] = zpos;
		   	RaceInfo[raceid][rCheckpointsCount]++;
		   	SendClientMessage(playerid, COLOR_WHITE, "Checkpoint agregado. Puedes quitar el último checkpoint puesto usando /carreraborrarcp.");
		}
	}
}

CMD:carreranuevocp(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
 	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] >= MAX_RACE_CHECKPOINTS)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "No puedes agregar mas checkpoints en la carrera (MAX: %d).", MAX_RACE_CHECKPOINTS);
		return 1;
	}
	
	AddNewRaceCheckpoint(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock DeleteLastRaceCheckpoint(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(RaceInfo[raceid][rCheckpointsCount] > 0)
		{
		    RaceInfo[raceid][rCheckpointsCount]--;
			TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][0] = 0.0;
		 	TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][1] = 0.0;
		    TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][2] = 0.0;
			SendClientMessage(playerid, COLOR_WHITE, "El último checkpoint que habías agregado ha sido borrado.");
		}
	}
}

CMD:carreraborrarcp(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
 	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes borrar mas checkpoints en la carrera ya que no tienes ninguno.");

	DeleteLastRaceCheckpoint(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock bool:AddNewRaceDriver(driverid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(IsPlayerConnected(driverid))
 		{
		    for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		    {
		        if(RaceInfo[raceid][rDriversID][i] == INVALID_PLAYER_ID)
		        {
		            RaceInfo[raceid][rDriversID][i] = driverid;
		            PlayerRaceInfo[driverid][pRaceID] = raceid;
		            PlayerRaceInfo[driverid][pCheckpointCount] = 0;
		            PlayerRaceInfo[driverid][pLap] = 1;
		            return true;
				}
			}
		}
	}
	return false;
}

CMD:carrerainvitar(playerid, params[])
{
	new targetid;
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
    if(sscanf(params, "d", targetid))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carrerainvitar [ID/Jugador]");
 	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	if(!IsPlayerConnected(targetid) || !ProxDetectorS(4.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido o se encuentra muy lejos.");
	if(PlayerRaceInfo[targetid][pRaceOffer] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador tiene otra invitación a una carrera pendiente, aguarda.");
	if(PlayerRaceInfo[targetid][pRaceID] != -1)
	{
		if(playerid != targetid)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se encuentra en otra carrera.");
		else // Esto es para poder meternos en nuestra propia carrera una sola vez (si detecta que ya estamos dentro lo anula)
		{
		    for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		    {
		        if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rDriversID][i] == playerid)
					return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras como corredor en tu carrera.");
			}
  		}
	}

 	SendFMessage(playerid, COLOR_LIGHTBLUE, "Has invitado a %s para que se una a la carrera como piloto. La oferta dura 10 segs.", GetPlayerNameEx(targetid));
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te invitó a correr en una carrera. Usa /carreraaceptar si lo deseas. La oferta dura 10 segs.", GetPlayerNameEx(playerid));
    PlayerRaceInfo[targetid][pRaceOffer] = playerid;
    SetTimerEx("CancelRaceOffer", 10000, false, "i", targetid);
	return 1;
}

public CancelRaceOffer(playerid)
{
    PlayerRaceInfo[playerid][pRaceOffer] = INVALID_PLAYER_ID;
    return 1;
}

CMD:carreraaceptar(playerid, params[])
{
	new offer = PlayerRaceInfo[playerid][pRaceOffer], str[128];

	if(offer == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido unirte a una carrera.");
	if(PlayerRaceInfo[playerid][pRaceID] != -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras en una carrera.");
	if(!IsPlayerConnected(offer) || !ProxDetectorS(4.0, playerid, offer))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido o se encuentra muy lejos.");
    if(PlayerRaceInfo[offer][pRaceID] == -1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto que te invitó ya no es organizador de ninguna carrera.");
 	if(RaceInfo[PlayerRaceInfo[offer][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	    
	if(AddNewRaceDriver(playerid, PlayerRaceInfo[offer][pRaceID]))
	{
		SendFMessage(offer, COLOR_LIGHTGREEN, "%s ha aceptado la invitación a tu carrera.", GetPlayerNameEx(playerid));
		SendFMessage(playerid, COLOR_LIGHTGREEN, "Entraste a la carrera de %s. Usa /carreraayuda y /carrerainfo para mas detalles.", GetPlayerNameEx(offer));
		format(str, sizeof(str), "[Carrera]: %s ha ingresado como corredor a la carrera.", GetPlayerNameEx(playerid));
		RaceMessage(PlayerRaceInfo[offer][pRaceID], COLOR_WHITE, str);
	} else
	    SendFMessage(playerid, COLOR_YELLOW2, "No hay mas lugar para corredores en la carrera (MAX:%d).", MAX_RACE_DRIVERS);
	return 1;
}

stock DeleteRaceDriver(driverid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
			if(RaceInfo[raceid][rDriversID][i] == driverid)
			{
		        RaceInfo[raceid][rDriversID][i] = INVALID_PLAYER_ID;
				ResetPlayerRaceVariables(driverid);
			}
   		}
	}
}

CMD:carreraabandonar(playerid, params[])
{
	new str[128];
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] == playerid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes abandonar la carrera si eres el organizador. Debes eliminarla usando /carreraeliminar.");

	format(str, sizeof(str), "[Carrera]: %s ha abandonado la carrera.", GetPlayerNameEx(playerid));
	RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
	DeleteRaceDriver(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

CMD:carreraexpulsar(playerid, params[])
{
	new targetid, str[128];

	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
    if(sscanf(params, "d", targetid))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreraexpulsar [ID/Jugador]");
	if(!IsPlayerConnected(targetid) || playerid == targetid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(PlayerRaceInfo[playerid][pRaceID] != PlayerRaceInfo[targetid][pRaceID])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no se encuentra anotado en tu carrera.");

	format(str, sizeof(str), "[Carrera]: %s ha sido expulsado de la carrera por %s.", GetPlayerNameEx(targetid), GetPlayerNameEx(playerid));
	RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
	DeleteRaceDriver(targetid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}


stock PrintRaceInfo(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "================[CARRERA]================");
	    SendFMessage(playerid, COLOR_WHITE, " - Organizador: %s", GetPlayerNameEx(RaceInfo[raceid][rCreatorID]));
	    SendFMessage(playerid, COLOR_WHITE, " - Vueltas: %d", RaceInfo[raceid][rLaps]);
	    if(RaceInfo[raceid][rWinner] != INVALID_PLAYER_ID)
	    	SendFMessage(playerid, COLOR_WHITE, " - Ganador: %s", GetPlayerNameEx(RaceInfo[raceid][rWinner]));
		if(RaceInfo[raceid][rStarted])
		    SendClientMessage(playerid, COLOR_WHITE, " - Empezó: Si");
		else
		    SendClientMessage(playerid, COLOR_WHITE, " - Empezó: No");
		SendClientMessage(playerid, COLOR_WHITE, " - Pilotos:");
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
		        SendFMessage(playerid, COLOR_WHITE, " %s", GetPlayerNameEx(RaceInfo[raceid][rDriversID][i]));
	   	}
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "===========================================");
	}
}

CMD:carrerainfo(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;

	PrintRaceInfo(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock CountRaceDrivers(raceid)
{
	new aux = 0;
	
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
		        aux++;
	   	}
	}
	return aux;
}

stock StartRace(raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
	    RaceInfo[raceid][rStarted] = true;
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
		    {
				SetPlayerRaceCheckpoint(RaceInfo[raceid][rDriversID][i], 0, TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], TrackInfo[raceid][1][0], TrackInfo[raceid][1][1], TrackInfo[raceid][1][2], 10.0);
				GameTextForPlayer(RaceInfo[raceid][rDriversID][i], "COMIENZA LA CARRERA", 1000, 6);
			}
		}
	}
	return 1;
}

CMD:carrerainiciar(playerid, params[])
{
	new str[128];
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
 	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rStarted] == true)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera ya ha comenzado.");
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rLaps] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No has seteado la cantidad de vueltas de la carrera. Usa /carreravueltas para hacerlo.");
    if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera debe contar con al menos 3 checkpoints. Usa /carreranuevocp para agregar nuevos checkpoints.");
 	if(CountRaceDrivers(PlayerRaceInfo[playerid][pRaceID]) < 2)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera debe contar con al menos 2 corredores. Usa /carrerainvitar para agregar corredores.");

	format(str, sizeof(str), "[Carrera]: %s ha dado inicio a la carrera. ¡A correr!", GetPlayerNameEx(playerid));
	RaceMessage(PlayerRaceInfo[playerid][pRaceID], COLOR_WHITE, str);
	StartRace(PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock OnDriverRaceCheckpoint(driverid, raceid)
{
	if(raceid != -1)
	{
		DisablePlayerRaceCheckpoint(driverid);
		PlayerRaceInfo[driverid][pCheckpointCount]++;

		new pcp = PlayerRaceInfo[driverid][pCheckpointCount], // pcp = player check point
		    rcp = RaceInfo[raceid][rCheckpointsCount], // rcp = race check point
		    pl = PlayerRaceInfo[driverid][pLap], // pl = player lap
		    rl = RaceInfo[raceid][rLaps]; // rl = race laps

		if(pcp == rcp) // Entró al ultimo checkpoint de la vuelta
		{
			if(pl == rl) // Si está en la ultima vuelta le seteamos en el checkpoint de la largada la bandera a cuadros
				SetPlayerRaceCheckpoint(driverid, 1, TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], 0.0, 0.0, 0.0, 10);
			else // Sino le seteamos el checkpoint de la largada de la nueva vuelta apuntando al segundo cp.
				SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], TrackInfo[raceid][1][0], TrackInfo[raceid][1][1], TrackInfo[raceid][1][2], 10.0);
		}
		else if(pcp == rcp + 1) // Entró al primer checkpoint luego de una vuelta (largada/bandera a cuadros)
		{
			if(pl == rl) // Termina la carrera
		    {
		        new str[128];
		        if(RaceInfo[raceid][rWinner] == INVALID_PLAYER_ID)
		        {
	            	format(str, sizeof(str), "[Carrera]: %s ha ganado la carrera.", GetPlayerNameEx(driverid));
					RaceMessage(raceid, COLOR_LIGHTGREEN, str);
					GameTextForPlayer(driverid, "¡Ganaste!", 1000, 3);
                    RaceInfo[raceid][rWinner] = driverid;
				} else
				    {
	  					format(str, sizeof(str), "[Carrera]: %s ha terminado la carrera.", GetPlayerNameEx(driverid));
						RaceMessage(raceid, COLOR_WHITE, str);
				    }
			} else // Termina la vuelta
				{
			        SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][1][0], TrackInfo[raceid][1][1], TrackInfo[raceid][1][2], TrackInfo[raceid][2][0], TrackInfo[raceid][2][1], TrackInfo[raceid][2][2], 10.0);
			        PlayerRaceInfo[driverid][pLap] ++;
			        PlayerRaceInfo[driverid][pCheckpointCount] = 1;
				}
		}
		else // checkpoint comun, con checkpoint entremedio de meta y largada
		    SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][pcp][0], TrackInfo[raceid][pcp][1], TrackInfo[raceid][pcp][2], TrackInfo[raceid][pcp+1][0], TrackInfo[raceid][pcp+1][0], TrackInfo[raceid][pcp+1][0], 10.0);
	}
}
