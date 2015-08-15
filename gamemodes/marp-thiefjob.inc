#if defined _marp_thiefjob_included
	#endinput
#endif
#define _marp_thiefjob_included

//================================CONSTANTES====================================

#define THIEF_HOUSE_THEFT       1
#define THIEF_HOUSE_ROBBERY     2
#define THIEF_SHOP_THEFT        3
#define THIEF_SHOP_ROBBERY      4
#define THIEF_PERSON_ROBBERY    5

//==================================DATA========================================

enum tThiefJob {
	pFelonExp,
	pFelonLevel,
	pRobPersonLimit,
	pRobLastVictimPID,
	pTheftLastVictimPID,
	pTheftPersonLimit,
	pRob247Limit,
	pTheft247Limit,
	pRobHouseLimit,
	pRob2HouseLimit,
	pForceDoorLimit,
	pForceEngineLimit,
	pDesarmCarLimit
};

new ThiefJobInfo[MAX_PLAYERS][tThiefJob];

new thief_stealing[MAX_PLAYERS],
	thief_timer[MAX_PLAYERS],
	thief_timer_secs[MAX_PLAYERS],
	thief_timer_police_call[MAX_PLAYERS],
	thief_target[MAX_PLAYERS],
	thief_type[MAX_PLAYERS],
	victim_thief[MAX_PLAYERS];

ResetThiefVariables(playerid)
{
	ThiefJobInfo[playerid][pFelonExp] = 0;
	ThiefJobInfo[playerid][pFelonLevel] = 0;
	ThiefJobInfo[playerid][pRobPersonLimit] = 0;
	ThiefJobInfo[playerid][pRobLastVictimPID] = INVALID_PLAYER_ID;
	ThiefJobInfo[playerid][pTheftLastVictimPID] = INVALID_PLAYER_ID;
	ThiefJobInfo[playerid][pTheftPersonLimit] = 0;
	ThiefJobInfo[playerid][pRobHouseLimit] = 0;
	ThiefJobInfo[playerid][pRob2HouseLimit] = 0;
	ThiefJobInfo[playerid][pRob247Limit] = 0;
	ThiefJobInfo[playerid][pTheft247Limit] = 0;
	ThiefJobInfo[playerid][pForceDoorLimit] = 0;
	ThiefJobInfo[playerid][pForceEngineLimit] = 0;
	ThiefJobInfo[playerid][pDesarmCarLimit] = 0;

	thief_timer_secs[playerid] = -1;
	thief_timer_police_call[playerid] = 0;
	victim_thief[playerid] = INVALID_PLAYER_ID;
}
	
//==============================DB CONNECTION===================================

LoadThiefJobData(playerid)
{
	new	query[128];

    format(query, sizeof(query), "SELECT * FROM `thief_job` WHERE accountid = %d", PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnThiefJobDataLoad", "i", playerid);
	return 1;
}

forward OnThiefJobDataLoad(playerid);
public OnThiefJobDataLoad(playerid)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows)
	{
		cache_get_field_content(0, "pFelonExp", result); 			ThiefJobInfo[playerid][pFelonExp] = strval(result);
		cache_get_field_content(0, "pFelonLevel", result); 			ThiefJobInfo[playerid][pFelonLevel] = strval(result);
		cache_get_field_content(0, "pRobPersonLimit", result);		ThiefJobInfo[playerid][pRobPersonLimit] = strval(result);
		cache_get_field_content(0, "pRobLastVictimPID", result);	ThiefJobInfo[playerid][pRobLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftLastVictimPID", result);	ThiefJobInfo[playerid][pTheftLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftPersonLimit", result);	ThiefJobInfo[playerid][pTheftPersonLimit] = strval(result);
		cache_get_field_content(0, "pRobHouseLimit", result); 		ThiefJobInfo[playerid][pRobHouseLimit] = strval(result);
		cache_get_field_content(0, "pRob2HouseLimit", result); 		ThiefJobInfo[playerid][pRob2HouseLimit] = strval(result);
		cache_get_field_content(0, "pRob247Limit", result); 		ThiefJobInfo[playerid][pRob247Limit] = strval(result);
		cache_get_field_content(0, "pTheft247Limit", result); 		ThiefJobInfo[playerid][pTheft247Limit] = strval(result);
		cache_get_field_content(0, "pForceDoorLimit", result);		ThiefJobInfo[playerid][pForceDoorLimit] = strval(result);
		cache_get_field_content(0, "pForceEngineLimit", result);	ThiefJobInfo[playerid][pForceEngineLimit] = strval(result);
		cache_get_field_content(0, "pDesarmCarLimit", result);		ThiefJobInfo[playerid][pDesarmCarLimit] = strval(result);
	}
	else
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "[ERROR]: Error al cargar la información del empleo ID %d desde la base de datos. Reportar a un administrador.", PlayerInfo[playerid][pJob]);
        PlayerInfo[playerid][pJob] = 0;
	}
	return 1;
}

SaveThiefJobData(playerid)
{
	new query[512];

	format(query,sizeof(query), "UPDATE thief_job set pFelonExp=%d,pFelonLevel=%d,pRobPersonLimit=%d,pRobLastVictimPID=%d,pTheftLastVictimPID=%d,pTheftPersonLimit=%d,pRob247Limit=%d,pTheft247Limit=%d,pRobHouseLimit=%d,pRob2HouseLimit=%d,pForceDoorLimit=%d,pForceEngineLimit=%d,pDesarmCarLimit=%d WHERE `accountid`=%d",
 		ThiefJobInfo[playerid][pFelonExp],
		ThiefJobInfo[playerid][pFelonLevel],
		ThiefJobInfo[playerid][pRobPersonLimit],
		ThiefJobInfo[playerid][pRobLastVictimPID],
		ThiefJobInfo[playerid][pTheftLastVictimPID],
		ThiefJobInfo[playerid][pTheftPersonLimit],
		ThiefJobInfo[playerid][pRob247Limit],
		ThiefJobInfo[playerid][pTheft247Limit],
		ThiefJobInfo[playerid][pRobHouseLimit],
		ThiefJobInfo[playerid][pRob2HouseLimit],
		ThiefJobInfo[playerid][pForceDoorLimit],
		ThiefJobInfo[playerid][pForceEngineLimit],
		ThiefJobInfo[playerid][pDesarmCarLimit],
		getPlayerMysqlId(playerid)
	);

	mysql_function_query(dbHandle, query, false, "", "");
}

SetThiefJobForPlayer(playerid)
{
	new query[128];

	format(query, sizeof(query), "SELECT * FROM `thief_job` WHERE accountid = %d", PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnPlayerThiefJobCheck", "i", playerid);
}

forward OnPlayerThiefJobCheck(playerid);
public OnPlayerThiefJobCheck(playerid)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows) // Alguna vez lo tuvo, por ende encontró un registro en DB.
	{
		cache_get_field_content(0, "pFelonExp", result); 			ThiefJobInfo[playerid][pFelonExp] = strval(result);
		cache_get_field_content(0, "pFelonLevel", result); 			ThiefJobInfo[playerid][pFelonLevel] = strval(result);
		cache_get_field_content(0, "pRobPersonLimit", result);		ThiefJobInfo[playerid][pRobPersonLimit] = strval(result);
		cache_get_field_content(0, "pRobLastVictimPID", result);	ThiefJobInfo[playerid][pRobLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftLastVictimPID", result);	ThiefJobInfo[playerid][pTheftLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftPersonLimit", result);	ThiefJobInfo[playerid][pTheftPersonLimit] = strval(result);
		cache_get_field_content(0, "pRobHouseLimit", result); 		ThiefJobInfo[playerid][pRobHouseLimit] = strval(result);
		cache_get_field_content(0, "pRob2HouseLimit", result); 		ThiefJobInfo[playerid][pRob2HouseLimit] = strval(result);
		cache_get_field_content(0, "pRob247Limit", result); 		ThiefJobInfo[playerid][pRob247Limit] = strval(result);
		cache_get_field_content(0, "pTheft247Limit", result); 		ThiefJobInfo[playerid][pTheft247Limit] = strval(result);
		cache_get_field_content(0, "pForceDoorLimit", result);		ThiefJobInfo[playerid][pForceDoorLimit] = strval(result);
		cache_get_field_content(0, "pForceEngineLimit", result);	ThiefJobInfo[playerid][pForceEngineLimit] = strval(result);
		cache_get_field_content(0, "pDesarmCarLimit", result);		ThiefJobInfo[playerid][pDesarmCarLimit] = strval(result);

	}
	else // Primera vez que lo tiene
	{
	    new query[128];

		ThiefJobInfo[playerid][pFelonLevel] = 1;

		format(query, sizeof(query), "INSERT INTO `thief_job` (`accountid`) VALUES ('%d')", PlayerInfo[playerid][pID]);
		mysql_function_query(dbHandle, query, false, "", "");
	}

	PlayerInfo[playerid][pJob] = JOB_FELON;
	PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades, ahora eres un %s!. Para saber los comandos disponibles mira en /delincuenteayuda y en /ayuda.", JobInfo[JOB_FELON][jName]);
	SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d paydays antes de volver a tomar otro empleo.", PlayerInfo[playerid][pJobTime]);
	return 1;
}

//==================================COMANDOS====================================

CMD:hurtarcasa(playerid, params[])
{
	new house_id = GetPlayerHouse(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 5)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(ThiefJobInfo[playerid][pRobHouseLimit] != 0)
 	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a hurtar.", ThiefJobInfo[playerid][pRobHouseLimit] / 60);
	    return 1;
	}
	if(house_id == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en una casa.");
 	if(house_id == PlayerInfo[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes robar tu propia casa!");

	thief_stealing[playerid] = 1;
	thief_timer_police_call[playerid] = 20 + random(60);
	thief_timer_secs[playerid] = 100;
	thief_type[playerid] = THIEF_HOUSE_THEFT;
	thief_target[playerid] = house_id;
	thief_timer[playerid] = SetTimerEx("theftTimer", 1000, true, "iii", playerid, 2, house_id);
	
	PlayerActionMessage(playerid, 15.0, "empieza a buscar objetos de valor y los almacena en una bolsa.");
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	ThiefJobInfo[playerid][pRobHouseLimit] = 40 * 60;
	return 1;
}

CMD:asaltarcasa(playerid, params[])
{
    new house_id = GetPlayerHouse(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 6)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(ThiefJobInfo[playerid][pRob2HouseLimit] != 0)
 	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a asaltar.", ThiefJobInfo[playerid][pRob2HouseLimit] / 60);
	    return 1;
	}
	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");
	if(house_id == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en una casa.");
 	if(house_id == PlayerInfo[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes robar tu propia casa!");

	thief_stealing[playerid] = 1;
	thief_timer_police_call[playerid] = 20 + random(60);
	thief_timer_secs[playerid] = 100;
	thief_type[playerid] = THIEF_HOUSE_ROBBERY;
	thief_target[playerid] = house_id;
	thief_timer[playerid] = SetTimerEx("theftTimer", 1000, true, "iii", playerid, 3, house_id);
	
	PlayerActionMessage(playerid, 15.0, "comienza a buscar dinero por la casa y lo guarda en una bolsa.");
	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	ThiefJobInfo[playerid][pRob2HouseLimit] = 50 * 60;
	return 1;
}

CMD:hurtartienda(playerid, params[])
{
	new biz_id = GetPlayerBusiness(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(ThiefJobInfo[playerid][pTheft247Limit] != 0)
 	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a hurtar.", ThiefJobInfo[playerid][pTheft247Limit] / 60);
	    return 1;
	}
	if(biz_id > 0 && biz_id == PlayerInfo[playerid][pBizKey])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hurtar tu propio negocio.");
    if(Business[biz_id][bType] != BIZ_247 && Business[biz_id][bType] != BIZ_CLOT && Business[biz_id][bType] != BIZ_CLOT2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un 24-7 o en una tienda de ropa.");

	thief_stealing[playerid] = 1;
	thief_timer_police_call[playerid] = 20 + random(35);
	thief_timer_secs[playerid] = 60;
	thief_type[playerid] = THIEF_SHOP_THEFT;
	thief_target[playerid] = biz_id;
	thief_timer[playerid] = SetTimerEx("theftTimer", 1000, true, "iii", playerid, 0, biz_id);

	PlayerActionMessage(playerid, 15.0, "comienza a tomar mercancía y guardarla debajo de su ropa.");
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	ThiefJobInfo[playerid][pTheft247Limit] = 60 * 30;
	return 1;
}

CMD:asaltartienda(playerid, params[])
{
	new biz_id = GetPlayerBusiness(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 4)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(ThiefJobInfo[playerid][pRob247Limit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a asaltar.", ThiefJobInfo[playerid][pRob247Limit] / 60);
	    return 1;
	}
	if(biz_id > 0 && biz_id == PlayerInfo[playerid][pBizKey])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes asaltar tu propio negocio.");
    if(Business[biz_id][bType] != BIZ_247 && Business[biz_id][bType] != BIZ_CLOT &&
		Business[biz_id][bType] != BIZ_CLOT2 && Business[biz_id][bType] != BIZ_CLUB &&
		Business[biz_id][bType] != BIZ_CLUB2 && Business[biz_id][bType] != BIZ_REST &&
		Business[biz_id][bType] != BIZ_HARD && Business[biz_id][bType] != BIZ_PIZZERIA &&
		Business[biz_id][bType] != BIZ_BURGER1 && Business[biz_id][bType] != BIZ_BURGER2 &&
		Business[biz_id][bType] != BIZ_BELL)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un 24-7 / Local de ropa / Bar / Discoteca o Club Nocturno / Restaurant / Comidas rápidas.");
	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");

	thief_stealing[playerid] = 1;
	thief_timer_police_call[playerid] = 20 + random(35);
	thief_timer_secs[playerid] = 60;
	thief_type[playerid] = THIEF_SHOP_ROBBERY;
	thief_target[playerid] = biz_id;
	thief_timer[playerid] = SetTimerEx("theftTimer", 1000, true, "iii", playerid, 1, biz_id);
	
	PlayerActionMessage(playerid, 15.0, "apunta al empleado con el arma y le hace una seña para que le de todo el dinero.");
    ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	ThiefJobInfo[playerid][pRob247Limit] = 60 * 60;
	return 1;
}

forward RobberyCancel(playerid);
public RobberyCancel(playerid)
{
    SendClientMessage(playerid, COLOR_YELLOW2, "El robo ha sido cancelado porque no respondiste en 30 segundos.");
    SendClientMessage(victim_thief[playerid], COLOR_YELLOW2, "El robo ha sido cancelado porque la victima no ha respondido en 30 segundos.");
    victim_thief[playerid] = INVALID_PLAYER_ID;
	return 1;
}

public GiveJobExp(playerid, job, exp)
{
    if(job == JOB_FELON)
	{
		if(ThiefJobInfo[playerid][pFelonExp] + exp >= GetJobExpNeeded(playerid, job))
		{
			ThiefJobInfo[playerid][pFelonLevel]++;
			ThiefJobInfo[playerid][pFelonExp] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡Ahora eres un delincuente más experimentado y tienes acceso a nuevos comandos!");
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		} else
			ThiefJobInfo[playerid][pFelonExp] += exp;
	}
	return 1;
}

stock GetJobExpNeeded(playerid, job)
{
	if(job == JOB_FELON)
	{
        new
			level = ThiefJobInfo[playerid][pFelonLevel],
			result;

        result = (level * level + 15) * (JOB_EXP_MULTIPLIER + level);
		return result;
	}
	return 0;
}

stock UpdateThiefCounters(playerid)
{
	if(ThiefJobInfo[playerid][pRobPersonLimit] > 0)
		ThiefJobInfo[playerid][pRobPersonLimit]--;

	if(ThiefJobInfo[playerid][pTheftPersonLimit] > 0)
		ThiefJobInfo[playerid][pTheftPersonLimit]--;

	if(ThiefJobInfo[playerid][pRob247Limit] > 0)
		ThiefJobInfo[playerid][pRob247Limit]--;

	if(ThiefJobInfo[playerid][pRobHouseLimit] > 0)
		ThiefJobInfo[playerid][pRobHouseLimit]--;

	if(ThiefJobInfo[playerid][pRob2HouseLimit] > 0)
	    ThiefJobInfo[playerid][pRob2HouseLimit]--;

	if(ThiefJobInfo[playerid][pTheft247Limit] > 0)
		ThiefJobInfo[playerid][pTheft247Limit]--;

	if(ThiefJobInfo[playerid][pForceDoorLimit] > 0)
	    ThiefJobInfo[playerid][pForceDoorLimit]--;

	if(ThiefJobInfo[playerid][pForceEngineLimit] > 0)
	    ThiefJobInfo[playerid][pForceEngineLimit]--;

	if(ThiefJobInfo[playerid][pDesarmCarLimit] > 0)
	    ThiefJobInfo[playerid][pDesarmCarLimit]--;
}

CMD:asaltar(playerid, params[])
{
	new target_money,
		robbery_amount,
	    string[128],
		target;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 3)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para poder asaltar.");
    if(PlayerInfo[playerid][pJailed] != JAIL_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo estando encarcelado.");
	if(sscanf(params, "u", target))
	{
        SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /asaltar [ID/Jugador]");
        SendClientMessage(playerid, COLOR_WHITE, "Info: si la víctima se encuentra agonizando no obtendrás experiencia.");
		return 1;
	}
	if(ThiefJobInfo[playerid][pRobPersonLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a robar.", ThiefJobInfo[playerid][pRobPersonLimit] / 60);
	    return 1;
	}
	if(target == playerid || !IsPlayerConnected(target))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(PlayerInfo[playerid][pFaction] != 0 && PlayerInfo[target][pFaction] == PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un miembro de tu misma facción.");
	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");
	if(ThiefJobInfo[playerid][pRobLastVictimPID] == getPlayerMysqlId(target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar dos veces seguidas a la misma persona.");
  	if(GetDistanceBetweenPlayers(playerid, target) > 4.0)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra demasiado lejos.");
  	if(victim_thief[target] != INVALID_PLAYER_ID || thief_target[playerid] != INVALID_PLAYER_ID)
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya esta siendo robado o ya te encuentras robando a otra persona.");
    if(PlayerInfo[target][pLevel] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un personaje menor de nivel 3.");

	target_money = GetPlayerCash(target);
	
	if(target_money <= 0)
	{
		format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(target));
		PlayerActionMessage(playerid, 15.0, string);
		return 1;
	}
    if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED)
	{
        SendFMessage(playerid, COLOR_WHITE, "Has intentado robarle a %s, espera la reacción del sujeto...", GetPlayerNameEx(target));
        SendClientMessage(target, COLOR_WHITE, "Te están intentando robar, puedes usar '/resistirte', '/cooperar' o '/mentir'.");
        SendClientMessage(target, COLOR_WHITE, "Recuerda que si el ladrón te descubre mintiendo se enfadará y perderás más dinero.");
    	thief_stealing[playerid] = 1;
		thief_type[playerid] = THIEF_PERSON_ROBBERY;
		thief_target[playerid] = target;
		victim_thief[target] = playerid;
		thief_timer[playerid] = SetTimerEx("RobberyCancel", 30000, false, "i", target);
	}
	else
	{
        if(target_money <= 100)
        {
            robbery_amount = target_money;
		}
		else
		{
  			robbery_amount = (target_money / 2) + random(target_money / 2);

  			if(robbery_amount > 50000)
  			{
  			    robbery_amount = 50000;
			}
		}
		
		ThiefJobInfo[playerid][pRobPersonLimit] = 60 * (15 - random(5));
  		format(string, sizeof(string), "le ha robado algo de dinero a %s tomando provecho de su incapacidad.", GetPlayerNameEx(target));
 		PlayerActionMessage(playerid, 15.0, string);
		GivePlayerCash(playerid, robbery_amount);
		GivePlayerCash(target, -robbery_amount);
		if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED && ThiefJobInfo[playerid][pFelonLevel] == 3)
		{
	 		GiveJobExp(playerid, PlayerInfo[playerid][pJob], 5);
	 	}
		ThiefJobInfo[playerid][pRobLastVictimPID] = getPlayerMysqlId(target);
	}
	if(random(2))
	{
		SetPlayerWantedLevelEx(playerid, GetPlayerWantedLevelEx(playerid) + 1);
		format(string, sizeof(string), "[Dpto. de policía]: un civil ha reportado a %s como sospechoso de robo a mano armada.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
		format(PlayerInfo[playerid][pAccusedOf], 64, "robo a mano armada");
		format(PlayerInfo[playerid][pAccusedBy], 24, "anónimo");
    }
	return 1;
}

CMD:resistirte(playerid, params[])
{
	if(victim_thief[playerid] != INVALID_PLAYER_ID)
	{
	    if(thief_target[victim_thief[playerid]] == playerid && IsPlayerConnected(victim_thief[playerid]))
	    {
			PlayerActionMessage(playerid, 15.0, "forcejea con el ladrón y se resiste al robo.");
			SendClientMessage(victim_thief[playerid], COLOR_WHITE, "La víctima se ha resistido y ha rechazado darte dinero.");
			KillTimer(thief_timer[victim_thief[playerid]]);
			thief_target[victim_thief[playerid]] = INVALID_PLAYER_ID;
			victim_thief[playerid] = INVALID_PLAYER_ID;
		}
	}
	return 1;
}

CMD:mentir(playerid, params[])
{
	new string[128],
	    target_money = GetPlayerCash(playerid),
	    thief_id = victim_thief[playerid];

	if(thief_id != INVALID_PLAYER_ID)
	{
		if(thief_target[thief_id] == playerid && IsPlayerConnected(thief_id))
 		{
 		    if(target_money > 1)
			{
			    if(random(1 + ThiefJobInfo[thief_id][pFelonLevel]) == 0)
				{
					format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(playerid));
					PlayerActionMessage(thief_id, 15.0, string);
					SendClientMessage(playerid, COLOR_WHITE, "Has logrado engañar al delincuente exitosamente y no te ha robado dinero.");
			    }
				else
				{
			        PlayerActionMessage(playerid, 15.0, "le miente al ladrón y le dice que no tiene dinero.");
		            format(string, sizeof(string), "se da cuenta del engaño, se enfurece, y le roba algo de dinero a %s.", GetPlayerNameEx(playerid));
		        	PlayerActionMessage(thief_id, 15.0, string);
		        	if(target_money > 50000)
		        	{
		        	    target_money = 50000;
					}
					GivePlayerCash(thief_id, target_money);
					GivePlayerCash(playerid, -target_money);
			   		if(ThiefJobInfo[thief_id][pFelonLevel] == 3)
		   			{
				 		GiveJobExp(thief_id, PlayerInfo[thief_id][pJob], 5);
				 	}
			    }
			}
			else
			{
				format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(playerid));
				PlayerActionMessage(thief_id, 15.0, string);
			}
		    ThiefJobInfo[thief_id][pRobLastVictimPID] = getPlayerMysqlId(playerid);
		    ThiefJobInfo[thief_id][pRobPersonLimit] = 60 * (15 - random(5));
		    KillTimer(thief_timer[thief_id]);
		    thief_target[thief_id] = INVALID_PLAYER_ID;
		    victim_thief[playerid] = INVALID_PLAYER_ID;
		}
	}
	return 1;
}

CMD:cooperar(playerid, params[])
{
	new string[128],
	    target_money = GetPlayerCash(playerid),
		robbery_amount = target_money / 2 + random(target_money / 2),
		thief_id = victim_thief[playerid];

	if(thief_id != INVALID_PLAYER_ID)
	{
		if(thief_target[thief_id] == playerid && IsPlayerConnected(thief_id))
 		{
		    if(target_money > 1)
			{
				format(string, sizeof(string), "le ha robado algo de dinero a %s con su cooperación.", GetPlayerNameEx(playerid));
				PlayerActionMessage(thief_id, 15.0, string);
				SendClientMessage(playerid, COLOR_YELLOW2, "Has cooperado y el ladrón te ha robado algo de dinero.");
				if(robbery_amount > 50000)
				{
				    robbery_amount = 50000;
				}
				GivePlayerCash(thief_id, robbery_amount);
				GivePlayerCash(playerid, -robbery_amount);
				if(ThiefJobInfo[thief_id][pFelonLevel] == 3)
				{
			 		GiveJobExp(thief_id, PlayerInfo[thief_id][pJob], 5);
				}
			}
			else
			{
				format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(playerid));
				PlayerActionMessage(thief_id, 15.0, string);
			}
			ThiefJobInfo[thief_id][pRobPersonLimit] = 60 * (15 - random(5));
			ThiefJobInfo[thief_id][pRobLastVictimPID] = getPlayerMysqlId(playerid);
		    KillTimer(thief_timer[thief_id]);
		    thief_target[thief_id] = INVALID_PLAYER_ID;
			victim_thief[playerid] = INVALID_PLAYER_ID;
		}
	}
	return 1;
}

CMD:hurtar(playerid, params[])
{
	new rnd,
		string[128],
		target,
		target_money,
		theft_money;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
 	if(ThiefJobInfo[playerid][pFelonLevel] < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "[BUG] Tendrías que empezar el job con nivel 1 de delincuente, repórtalo a un administrador.");
    if(PlayerInfo[playerid][pJailed] != JAIL_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo estando encarcelado.");
	if(sscanf(params, "u", target))
	{
        SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /hurtar [ID/Jugador]");
        SendClientMessage(playerid, COLOR_WHITE, "Info: si la víctima se encuentra agonizando no obtendrás experiencia.");
		return 1;
	}
	if(ThiefJobInfo[playerid][pTheftPersonLimit] > 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Has superado el límite de hurtos, espera %d minutos.", ThiefJobInfo[playerid][pTheftPersonLimit] / 60);
	    return 1;
	}
	if(target == playerid || !IsPlayerConnected(target))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
    if(IsPlayerInAnyVehicle(playerid) && GetVehicleType(GetPlayerVehicleID(playerid)) != VTYPE_BIKE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo desde un vehículo.");
	if(PlayerInfo[playerid][pFaction] != 0 && PlayerInfo[target][pFaction] == PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un miembro de tu misma facción.");
  	if(GetDistanceBetweenPlayers(playerid, target) > 1.2)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Recuerda que debes estar cerca del bolsillo/cartera de la víctima!");
  	if(victim_thief[target] != INVALID_PLAYER_ID || thief_target[playerid] != INVALID_PLAYER_ID)
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya está siendo robado o ya te encuentras robando a alguien.");
    if(PlayerInfo[target][pLevel] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un personaje menor de nivel 3.");
	if(ThiefJobInfo[playerid][pTheftLastVictimPID] == getPlayerMysqlId(target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes hurtar dos veces seguidas a la misma persona.");

	target_money = GetPlayerCash(target);
    if(target_money <= 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no tiene nada de valor.");

	rnd = random(3);
	if(rnd == 0) // 33 % de que falle.
	{
		format(string, sizeof(string), "ha realizado unas maniobras para hurtar algo del bolsillo de %s pero es descubierto.", GetPlayerNameEx(target));
        PlayerActionMessage(playerid, 15.0, string);
        SendClientMessage(playerid, COLOR_WHITE, "¡Has fallado y el sujeto lo ha notado, mejor comienza a correr!");
	}
	else
    {
		theft_money = 30 + random(20);
		if(theft_money > target_money)
		{
			theft_money = target_money;
		}
		SendFMessage(playerid, COLOR_WHITE, "Has tomado $%d del sujeto sin que éste se percate de lo sucedido, actúa como si nada hubiera pasado.", theft_money);
	    SendClientMessage(target, COLOR_WHITE, "[AVISO OOC]: Un sujeto te ha hurtado sin que te des cuenta. Esta información NO la puedes usar IC.");
		GivePlayerCash(target, -theft_money);
		GivePlayerCash(playerid, theft_money);
	}
 	if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED && ThiefJobInfo[playerid][pFelonLevel] == 1)
	 {
 		GiveJobExp(playerid, PlayerInfo[playerid][pJob], 1);
 	}
	ThiefJobInfo[playerid][pTheftPersonLimit] = 600;
	ThiefJobInfo[playerid][pTheftLastVictimPID] = getPlayerMysqlId(target);
	return 1;
}

CMD:correr(playerid, params[])
{
    if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(GetPVarInt(playerid, "disabled") != DISABLE_STEALING)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar robando para utilizar este comando.");

	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
    thief_timer_secs[playerid] = -1;
	KillTimer(thief_timer[playerid]);
	PlayerActionMessage(playerid, 15.0, "arroja al suelo todo el dinero/mercancía robado.");
	return 1;
}

CMD:verexp(playerid, params[])
{
	if(PlayerInfo[playerid][pJob] == JOB_FELON)
		SendFMessage(playerid, COLOR_WHITE, "[*Empleo de delincuente*] Nivel: %d Exp: %d/%d", ThiefJobInfo[playerid][pFelonLevel], ThiefJobInfo[playerid][pFelonExp], GetJobExpNeeded(playerid, JOB_FELON));
	return 1;
}

CMD:delincuenteayuda(playerid, params[])
{
	if(PlayerInfo[playerid][pJob] == JOB_FELON)
	{
		SendClientMessage(playerid, COLOR_WHITE, "[Ladron]: /hurtar /hurtartienda /asaltar /asaltartienda /hurtarcasa /asaltarcasa /verexp");
		SendClientMessage(playerid, COLOR_WHITE, "[Ladron de bancos]: /grupoayuda");
	    SendClientMessage(playerid, COLOR_WHITE, "[Ladron de vehículos]: /barreta /puente /desarmar");
		SendClientMessage(playerid, COLOR_WHITE, "Info: al robar con un comando de tu nivel obtendrás experiencia para subir de nivel y desbloquear nuevos comandos.");
	}
	return 1;
}
