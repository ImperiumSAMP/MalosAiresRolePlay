#if defined _isamp_afk_included
	#endinput
#endif
#define _isamp_afk_included

//=================================CONSTANTES===================================

#define AFK_MAX_TIME 	5 	// En minutos, cuanto tarda en entrar al modo ausente/afk.

//=================================VARIABLES====================================

new Float:cAFKPos[MAX_PLAYERS][9],
	cAFKTimer[MAX_PLAYERS],
	cAFK[MAX_PLAYERS],
	TAFKT[MAX_PLAYERS],
	cTomarVW[MAX_PLAYERS];

//============================FUNCIONES PUBLICAS================================

forward AFKc(playerid);
forward AFKText(playerid);

//===========================CUERPO DE FUNCIONES================================

ResetAfkVariables(playerid)
{
    cAFK[playerid] = 0;
}

DestroyAfkTimer(playerid)
{
    KillTimer(cAFKTimer[playerid]);
    if(cAFK[playerid] == 1)
		SetPlayerVirtualWorld(playerid, (cTomarVW[playerid]));
}

StartAfkTimer(playerid)
{
    KillTimer(cAFKTimer[playerid]);
	cAFKTimer[playerid] = SetTimerEx("AFKc", AFK_MAX_TIME * 60000, true, "i", playerid);
}

IsPlayerAfk(playerid)
{
	return cAFK[playerid];
}

UpdateAfkSystem(playerid)
{
	GetPlayerCameraPos(playerid, cAFKPos[playerid][6], cAFKPos[playerid][7], cAFKPos[playerid][8]);
	if(cAFKPos[playerid][6] != cAFKPos[playerid][3] && cAFKPos[playerid][7] != cAFKPos[playerid][4] && cAFKPos[playerid][8] != cAFKPos[playerid][5])
	{
		if(cAFK[playerid] == 1)
		{
			SetPlayerVirtualWorld(playerid, (cTomarVW[playerid]));
			cAFK[playerid] = 0;
			KillTimer(cAFKTimer[playerid]);
			KillTimer(TAFKT[playerid]);
			cAFKTimer[playerid] = SetTimerEx("AFKc", AFK_MAX_TIME * 60000, true, "i", playerid);
		}
	}
}

public AFKc(playerid)
{
    GetPlayerCameraPos(playerid, cAFKPos[playerid][0], cAFKPos[playerid][1], cAFKPos[playerid][2]);
	if(cAFKPos[playerid][0] == cAFKPos[playerid][3] && cAFKPos[playerid][1] == cAFKPos[playerid][4] && cAFKPos[playerid][2] == cAFKPos[playerid][5])
    {
        if(cAFK[playerid] == 0)
        {
	    	cTomarVW[playerid] = GetPlayerVirtualWorld(playerid);
			SetPlayerVirtualWorld(playerid, 100);
	    	cAFK[playerid] = 1;
	    	if(GetPVarInt(playerid, "pPayTime") - (AFK_MAX_TIME * 60) > 0)
				SetPVarInt(playerid, "pPayTime", GetPVarInt(playerid, "pPayTime") - (AFK_MAX_TIME * 60));
	    	TAFKT[playerid] = SetTimerEx("AFKText", 3000, 1, "i", playerid);
	        return 1;
		}
		else
		{
		    cAFKPos[playerid][3] = cAFKPos[playerid][0];
			cAFKPos[playerid][4] = cAFKPos[playerid][1];
			cAFKPos[playerid][5] = cAFKPos[playerid][2];
		    KillTimer(cAFKTimer[playerid]);
		    cAFKTimer[playerid] = SetTimerEx("AFKc", AFK_MAX_TIME * 60000, true, "i", playerid);
	    	return 1;
		}
	}
	else
	{
	    cAFKPos[playerid][3] = cAFKPos[playerid][0];
		cAFKPos[playerid][4] = cAFKPos[playerid][1];
		cAFKPos[playerid][5] = cAFKPos[playerid][2];
	    KillTimer(cAFKTimer[playerid]);
	    cAFKTimer[playerid] = SetTimerEx("AFKc", AFK_MAX_TIME * 60000, true, "i", playerid);
	    return 1;
	}
}

public AFKText(playerid)
{
	if(cAFK[playerid] == 1)
	{
		new string[15];
	    format(string, sizeof(string), "MODO AUSENTE");
	    GameTextForPlayer(playerid, string, 3000, 3);
		return 1;
	}
	return 1;
}
