#if defined _isamp_racesystem_included
	#endinput
#endif
#define _isamp_racesystem_included

//=================================DEFINES======================================

#define MAX_SERVER_RACES        3
#define MAX_RACE_CHECKPOINTS	20
#define MAX_RACE_DRIVERS        8

//==================================NEWS========================================



//=============================RESET VARIABLES==================================



//============================SISTEMA DE CARRERAS===============================

enum rRaceInfo {
	rCreatorID,
	rDriversID[MAX_RACE_DRIVERS],
	rCheckpointsCount,
	rLaps
};

new Float:TrackInfo[MAX_SERVER_RACES][MAX_RACE_CHECKPOINTS][3];
new RaceInfo[MAX_SERVER_RACES][rRaceInfo];

enum pPlayerRaceInfo {
	pRaceID,
	pLap,
	pCheckpointCount
};

new PlayerRaceInfo[MAX_PLAYERS][pPlayerRaceInfo];

CMD:racedebug(playerid, params[])
{
	new id;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", id))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /racedebug [raceid]");

	SendFMessage(playerid, COLOR_YELLOW, "rCreatorID [%d] = %d", id, RaceInfo[id][rCreatorID]);
	for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		SendFMessage(playerid, COLOR_YELLOW, "rDriversID [%d][%d] = %d", id, i, RaceInfo[id][rDriversID][i]);
	SendFMessage(playerid, COLOR_YELLOW, "rCheckpointCounter [%d] = %d", id, RaceInfo[id][rCheckpointsCount]);
	SendFMessage(playerid, COLOR_YELLOW, "rLaps [%d] = %d", id, RaceInfo[id][rLaps]);
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

	SendFMessage(playerid, COLOR_YELLOW, "pRaceID [%d] = %d", id, PlayerRaceInfo[id][pRaceID]);
	SendFMessage(playerid, COLOR_YELLOW, "pLap [%d] = %d", id, PlayerRaceInfo[id][pLap]);
	SendFMessage(playerid, COLOR_YELLOW, "pCheckpointCount [%d] = %d", id, PlayerRaceInfo[id][pCheckpointCount]);
	return 1;
}

stock ResetRaceVariables(raceid)
{
	RaceInfo[raceid][rCreatorID] = INVALID_PLAYER_ID;
	for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		RaceInfo[raceid][rDriversID][i] = INVALID_PLAYER_ID;
	RaceInfo[raceid][rCheckpointsCount] = 0;
	RaceInfo[raceid][rLaps] = 0;
}

stock ResetServerRacesVariables()
{
	for(new i = 0; i < MAX_SERVER_RACES; i++)
	    ResetRaceVariables(i);
}

stock ResetPlayerRaceVariables(playerid)
{
    PlayerRaceInfo[playerid][pRaceID] = -1;
    PlayerRaceInfo[playerid][pLap] = 0;
    PlayerRaceInfo[playerid][pCheckpointCount] = 0;
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
        return 1;
	if(PlayerRaceInfo[playerid][pRaceID] != -1)
	    return 1;
	if(CreateRace(playerid))
	    SendClientMessage(playerid, COLOR_WHITE, "Has creado una carrera. Para ver la lista de comandos disponibles usa /carreraayuda");
	else
        SendClientMessage(playerid, COLOR_YELLOW2, "No hay mas espacio para carreras en el servidor: hay otras en curso en este momento");
	return 1;
}

stock SetRaceLaps(playerid, raceid, laps)
{
	if(playerid == RaceInfo[raceid][rCreatorID])
	{
	   	RaceInfo[raceid][rLaps] = laps;
	}
}

CMD:carreravueltas(playerid, params[])
{
	new laps;
	
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
	if(sscanf(params, "i", laps))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreravueltas [nro de vueltas] (1-50)");
	if(laps < 1 || laps > 50)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreravueltas [nro de vueltas] (1-50)");

	SetRaceLaps(playerid, PlayerRaceInfo[playerid][pRaceID], laps);
	return 1;
}

stock AddNewRaceCheckpoint(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(playerid == RaceInfo[raceid][rCreatorID])
		{
		    if(RaceInfo[raceid][rCheckpointsCount] <= MAX_RACE_CHECKPOINTS)
		    {
				new Float:xpos, Float:ypos, Float:zpos;
				GetPlayerPos(playerid, xpos, ypos, zpos);
				TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][0] = xpos;
			 	TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][1] = ypos;
			    TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][2] = zpos;
			   	RaceInfo[raceid][rCheckpointsCount]++;
			}
		}
	}
}

CMD:carreranuevocp(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] > MAX_RACE_CHECKPOINTS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agregar mas checkpoints en la carrera.");

	AddNewRaceCheckpoint(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock DeleteLastRaceCheckpoint(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(playerid == RaceInfo[raceid][rCreatorID])
		{
		    RaceInfo[raceid][rCheckpointsCount]--;
			TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][0] = 0;
		 	TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][1] = 0;
		    TrackInfo[raceid][RaceInfo[raceid][rCheckpointsCount]][2] = 0;
		}
	}
}

CMD:carreraborrarcp(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes borrar mas checkpoints en la carrera ya que no tienes ninguno");

	DeleteLastRaceCheckpoint(playerid, PlayerRaceInfo[playerid][pRaceID]);
	return 1;
}

stock bool:AddNewRaceDriver(playerid, driverid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(playerid == RaceInfo[raceid][rCreatorID])
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
	if(!IsPlayerConnected(targetid) || !ProxDetectorS(4.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido o se encuentra muy lejos.");
	if(PlayerRaceInfo[targetid][pRaceID] != -1 && playerid != targetid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se encuentra en otra carrera.");
	if(AddNewRaceDriver(playerid, targetid, PlayerRaceInfo[playerid][pRaceID]))
	{
	    SendFMessage(playerid, COLOR_WHITE, "%s ha ingresado a la carrera.", GetPlayerNameEx(targetid));
	    SendFMessage(targetid, COLOR_WHITE, "Has ingresado a la carrera organizada por %s.", GetPlayerNameEx(playerid));
	} else
	    SendClientMessage(playerid, COLOR_YELLOW2, "No hay mas lugar para corredores en la carrera.");
	return 1;
}
	

stock DeleteRaceDriver(playerid, driverid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
		if(playerid == RaceInfo[raceid][rCreatorID])
		{
  			for(new i = 0; i < MAX_RACE_DRIVERS; i++)
			{
			    if(RaceInfo[raceid][rDriversID][i] == driverid)
			    {
			        RaceInfo[raceid][rDriversID][i] = INVALID_PLAYER_ID;
			        PlayerRaceInfo[driverid][pRaceID] = -1;
			        return true;
				}
   			}
		}
	}
	return false;
}

CMD:carreraexpulsar(playerid, params[])
{
	new targetid;

	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
    if(sscanf(params, "d", targetid))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /carreraexpulsar [ID/Jugador]");
	if(!IsPlayerConnected(targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(DeleteRaceDriver(playerid, targetid, PlayerRaceInfo[playerid][pRaceID]))
	{
	    SendFMessage(playerid, COLOR_WHITE, "%s ha sido expulsado de la carrera.", GetPlayerNameEx(targetid));
	    SendFMessage(targetid, COLOR_WHITE, "Has sido expulsado de la carrera organizada por %s.", GetPlayerNameEx(playerid));
	} else
	    SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no se encuentra anotado como corredor de la carrera.");
	return 1;
}


stock PrintRaceInfo(playerid, raceid)
{
	if(raceid >= 0 && raceid < MAX_SERVER_RACES)
	{
	    SendClientMessage(playerid, COLOR_WHITE, "==================================");
	    SendFMessage(playerid, COLOR_WHITE, " - Organizador: %s", GetPlayerNameEx(RaceInfo[raceid][rCreatorID]));
	    SendFMessage(playerid, COLOR_WHITE, " - Vueltas: %d", RaceInfo[raceid][rLaps]);
		SendClientMessage(playerid, COLOR_WHITE, " - Pilotos:");
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
		        SendFMessage(playerid, COLOR_WHITE, " %s", GetPlayerNameEx(RaceInfo[raceid][rDriversID][i]));
	   	}
		SendClientMessage(playerid, COLOR_WHITE, "==================================");
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
		for(new i = 0; i < MAX_RACE_DRIVERS; i++)
		{
		    if(RaceInfo[raceid][rDriversID][i] != INVALID_PLAYER_ID)
				SetPlayerRaceCheckpoint(RaceInfo[raceid][rDriversID][i], 0, TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], TrackInfo[raceid][1][0], TrackInfo[raceid][1][1], TrackInfo[raceid][1][2], 10.0);
		}
	}
	return 1;
}

CMD:carrerainiciar(playerid, params[])
{
	if(PlayerRaceInfo[playerid][pRaceID] == -1)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCreatorID] != playerid)
	    return 1;
	if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rLaps] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No has seteado la cantidad de vueltas de la carrera. Usa /carreravueltas para ello.");
    if(RaceInfo[PlayerRaceInfo[playerid][pRaceID]][rCheckpointsCount] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera debe contar con al menos 3 checkpoints. Usa /carreranuevocp para ello.");
 	if(CountRaceDrivers(PlayerRaceInfo[playerid][pRaceID]) < 2)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "La carrera debe contar con al menos 2 corredores. Usa /carrerainvitar para agregar corredores.");

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

		if(pcp + 1 == rcp) // Entró al anteultimo checkpoint de la vuelta
		{
			if(pl == rl) // Si está en la ultima vuelta le seteamos el ultimo checkpoint con estilo "finish - bandera a cuadros"
				SetPlayerRaceCheckpoint(driverid, 1, TrackInfo[raceid][rcp-1][0], TrackInfo[raceid][rcp-1][1], TrackInfo[raceid][rcp-1][2], 0.0, 0.0, 0.0, 10);
			else // Sino le seteamos el ultimo de esa vuelta mirando al primero de la siguiente vuelta
				SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][rcp-1][0], TrackInfo[raceid][rcp-1][1], TrackInfo[raceid][rcp-1][2], TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], 10.0);
		}
		else if(pcp == rcp) // Entró al ultimo checkpoint de la vuelta
		{
			if(PlayerRaceInfo[driverid][pLap] == RaceInfo[raceid][rLaps]) // Termina la carrera
		    {
		        SendClientMessage(driverid, COLOR_WHITE, "Has terminado la carrera.");
			} else // Termina la vuelta
				{
			        SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][0][0], TrackInfo[raceid][0][1], TrackInfo[raceid][0][2], TrackInfo[raceid][1][0], TrackInfo[raceid][1][1], TrackInfo[raceid][1][2], 10.0);
			        PlayerRaceInfo[driverid][pLap] ++;
			        PlayerRaceInfo[driverid][pCheckpointCount] = 0;
				}
		}
		else // Vuelta comun, con checkpoint entre medio de meta y largada
		    SetPlayerRaceCheckpoint(driverid, 0, TrackInfo[raceid][pcp][0], TrackInfo[raceid][pcp][1], TrackInfo[raceid][pcp][2], TrackInfo[raceid][pcp+1][0], TrackInfo[raceid][pcp+1][0], TrackInfo[raceid][pcp+1][0], 10.0);
	}
}
