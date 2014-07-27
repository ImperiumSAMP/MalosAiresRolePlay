#if defined _isamp_thiefjob_included
	#endinput
#endif
#define _isamp_thiefjob_included

enum tThiefJob {
	pFelonExp,
	pFelonLevel,
	pRobPersonLimit,
	pRobLastVictimPID,
	pTheftLastVictimPID,
	pTheftPersonLimit,
	pRob247Limit,
	pTheft247Limit,
	pRobHouseLimit
};
new ThiefJobInfo[MAX_PLAYERS][tThiefJob];

new policeCallTime[MAX_PLAYERS],
	theftTime[MAX_PLAYERS],
	felon[MAX_PLAYERS];
	
// Sistema de mascaras
new isUsingMaskInSlot[MAX_PLAYERS]; // -1 si no usa, caso contrario guarda el slot donde la tiene attacheada

stock resetThiefVariables(playerid){
	ThiefJobInfo[playerid][pFelonExp] = 0;
	ThiefJobInfo[playerid][pFelonLevel] = 1;
	ThiefJobInfo[playerid][pRobPersonLimit] = 999999999;
	ThiefJobInfo[playerid][pRobLastVictimPID] = INVALID_PLAYER_ID;
	ThiefJobInfo[playerid][pTheftLastVictimPID] = INVALID_PLAYER_ID;
	ThiefJobInfo[playerid][pTheftPersonLimit] = 999999999;
	ThiefJobInfo[playerid][pRobHouseLimit] = 999999999;
	ThiefJobInfo[playerid][pRob247Limit] = 999999999;
	ThiefJobInfo[playerid][pTheft247Limit] = 999999999;

	theftTime[playerid] = -1;
	felon[playerid] = INVALID_PLAYER_ID;
	policeCallTime[playerid] = 0;
}

stock loadThiefJobData(playerid,MysqlID){
	new		
		query[256];

	printf("\nLoading thiefJobData for player id: %d sqlid: %d\n",MysqlID);
    format(query, sizeof(query), "SELECT * FROM `thiefJob` WHERE id=%d", MysqlID);
	mysql_function_query(dbHandle, query, true, "OnThiefJobDataLoad", "i", playerid);
	return 1;
}

forward OnThiefJobDataLoad(playerid);
public OnThiefJobDataLoad(playerid) {
	new
		rows,
		fields,
		result[32];
	
	cache_get_data(rows, fields);
	if(rows)
	{	
		cache_get_field_content(0, "pFelonExp", result); 		ThiefJobInfo[playerid][pFelonExp] 		= strval(result);
		cache_get_field_content(0, "pFelonLevel", result); 		ThiefJobInfo[playerid][pFelonLevel] 		= strval(result);
		cache_get_field_content(0, "pRobPersonLimit", result);	ThiefJobInfo[playerid][pRobPersonLimit] 	= strval(result);
		cache_get_field_content(0, "pRobLastVictimPID", result);ThiefJobInfo[playerid][pRobLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftLastVictimPID", result);ThiefJobInfo[playerid][pTheftLastVictimPID] = strval(result);
		cache_get_field_content(0, "pTheftPersonLimit", result);ThiefJobInfo[playerid][pTheftPersonLimit] = strval(result);
		cache_get_field_content(0, "pRobHouseLimit", result); 	ThiefJobInfo[playerid][pRobHouseLimit] 	= strval(result);
		cache_get_field_content(0, "pRob247Limit", result); 	ThiefJobInfo[playerid][pRob247Limit] 		= strval(result);
		cache_get_field_content(0, "pTheft247Limit", result); 	ThiefJobInfo[playerid][pTheft247Limit] 	= strval(result);
	}
}

stock createThiefJob(playersqlid){
		new query[128];
		printf("\nCreating thiefJob for player sqlid=%d",playersqlid); 
		format(query,sizeof(query),"INSERT INTO `thief_job` (`accountid`) VALUES ('playersqlid')", playersqlid);
		printf("\nQuery is: %s",query);
		mysql_function_query(dbHandle, query, false, "", "");
}

forward saveThiefJob(playerid);
public saveThiefJob(playerid){
	new query[512];
	
	format(query,sizeof(query), "UPDATE thief_job set pFelonExp=%d,pFelonLevel=%d,pRobPersonLimit=%d,pRobLastVictimPID=%d,pTheftLastVictimPID=%d,pTheftPersonLimit=%d,pRob247Limit=%d,pTheft247Limit=%d,pRobHouseLimit=%d WHERE `accountid`=%d",			
            ThiefJobInfo[playerid][pFelonExp],
			ThiefJobInfo[playerid][pFelonLevel],
			ThiefJobInfo[playerid][pRobPersonLimit],
			ThiefJobInfo[playerid][pRobLastVictimPID],
			ThiefJobInfo[playerid][pTheftLastVictimPID],
			ThiefJobInfo[playerid][pTheftPersonLimit],
			ThiefJobInfo[playerid][pRob247Limit],
			ThiefJobInfo[playerid][pTheft247Limit],
			ThiefJobInfo[playerid][pRobHouseLimit],
			getPlayerMysqlId(playerid));

	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

forward theftTimer(playerid, type, biz);
public theftTimer(playerid, type, biz) {
	new
		felonLevel = ThiefJobInfo[playerid][pFelonLevel],
	    string[128];
	    
	if(type == 0) {
		if(theftTime[playerid] > 0) {
		    if(theftTime[playerid] == policeCallTime[playerid]) {
				new
					rnd;

		       	if(felonLevel >= 6) {
				    rnd = random(3);
				} else if(felonLevel == 1) {
				    rnd = random(4);
				} else if(felonLevel == 2) {
					rnd = random(3);
				} else if(felonLevel >= 3) {
				    rnd = random(2);
				}
				if(rnd == 0 || (felonLevel >= 6 && rnd == 1)) {
				} else {
				    robberyAlert(playerid,"hurto en negocio","anónimo",Business[biz][bName]);	
					
			        SendClientMessage(playerid, COLOR_WHITE, "¡Un empleado ha notado tu accionar y ha llamado a la policía!");
			        SendClientMessage(playerid, COLOR_WHITE, "Puedes utilizar /correr para escapar dejando toda la mercancía o esperar para terminar.");
				}
			}
	 		format(string, sizeof(string), "~w~Tomando mercancia   ~r~%d~w~ segundos", theftTime[playerid]);
	 		GameTextForPlayer(playerid, string, 1000, 4);
	        theftTime[playerid]--;
		} else if(theftTime[playerid] == 0) {
			new
				takeMoney = (80 * felonLevel) + random(310 * felonLevel);
		    theftTime[playerid] = -1;
			SendFMessage(playerid, COLOR_WHITE, "Has tomado la mercancía por un valor de $%d, ¡retírate de la tienda!", takeMoney);
			TogglePlayerControllable(playerid, true);
			GivePlayerCash(playerid, takeMoney);
			if(ThiefJobInfo[playerid][pFelonLevel] == 2) {
				GiveJobExp(playerid, JOB_FELON, 6);
			}
			SetPVarInt(playerid, "disabled", DISABLE_NONE);
			KillTimer(GetPVarInt(playerid, "theftTimer"));
			printf("%s hurto tienda", GetPlayerNameEx(playerid));
		}
	} else if(type == 1) {
	    if(theftTime[playerid] > 0) {
		    if(theftTime[playerid] == policeCallTime[playerid]) {
				
				robberyAlert(playerid,"robo a mano armada","anónimo",Business[biz][bName]);				

		        SendClientMessage(playerid, COLOR_WHITE, "¡Un empleado ha notado tu accionar y ha llamado a la policía!");
		        SendClientMessage(playerid, COLOR_WHITE, "Puedes utilizar /correr para escapar dejando todo el dinero o esperar para terminar.");
		    }
		    format(string, sizeof(string), "~w~Guardando dinero ~r~%d~w~ segundos", theftTime[playerid]);
	 		GameTextForPlayer(playerid, string, 1000, 4);
	        theftTime[playerid]--;
        } else if(theftTime[playerid] == 0) {
			new takeMoney;
            theftTime[playerid] = -1;
            takeMoney = (260 * felonLevel) + random(860 * felonLevel);
			SendFMessage(playerid, COLOR_WHITE, "Has robado $%d de la caja, ¡escapa antes de que venga la policía!", takeMoney);
			TogglePlayerControllable(playerid, true);
			GivePlayerCash(playerid, takeMoney);
			if(ThiefJobInfo[playerid][pFelonLevel] == 4) {
		 		GiveJobExp(playerid, PlayerInfo[playerid][pJob], 5);
		 	}
			DeletePVar(playerid, "stealAmount");
			SetPVarInt(playerid, "disabled", DISABLE_NONE);
			KillTimer(GetPVarInt(playerid, "theftTimer"));
			printf("%s asalto tienda", GetPlayerNameEx(playerid));
        }
	} else if(type == 2){
	    if(theftTime[playerid] > 0) {
	        if(theftTime[playerid] == policeCallTime[playerid]) {
			    		
				robberyAlert(playerid,"hurto en domicilio particular","anónimo","",biz);
				
		        SendClientMessage(playerid, COLOR_WHITE, "¡Un vecino ha notado tu entrada forzosa y ha llamado a la policía!");
		        SendClientMessage(playerid, COLOR_WHITE, "Puedes utilizar /correr para escapar dejando la bolsa de objetos o esperar para terminar.");
		    }
		    format(string, sizeof(string), "~w~Robando objetos ~r~%d~w~ segundos", theftTime[playerid]);
	 		GameTextForPlayer(playerid, string, 1000, 4);
	        theftTime[playerid]--;
        } else if(theftTime[playerid] == 0) {
			new takeMoney = (200 * felonLevel) + random(600 * felonLevel);
            theftTime[playerid] = -1;
			SendFMessage(playerid, COLOR_WHITE, "Has robado $%d objetos de valor, ¡escapa antes de que venga la policía!", takeMoney);
			TogglePlayerControllable(playerid, true);
			GivePlayerCash(playerid, takeMoney);
			if(ThiefJobInfo[playerid][pFelonLevel] == 5) {
		 		GiveJobExp(playerid, JOB_FELON, 6);
		 	}
			DeletePVar(playerid, "stealAmount");
			SetPVarInt(playerid, "disabled", DISABLE_NONE);
			KillTimer(GetPVarInt(playerid, "theftTimer"));
			printf("%s hurto casa", GetPlayerNameEx(playerid));
        }
	}
	return 1;
}

stock robberyAlert(playerid,accusedOf[],accusedBy[],propName[],houseId=0){
	new string[128];
	
 	if(isUsingMaskInSlot[playerid] == -1) // Si roba sin mascara le damos sosp
 	{
		if(GetPlayerWantedLevelEx(playerid) < 2)
			SetPlayerWantedLevelEx(playerid, 2);
		else
			SetPlayerWantedLevelEx(playerid, GetPlayerWantedLevelEx(playerid) + 1);
	}
	
	if(houseId){
	    format(string, sizeof(string), "[Dpto. de policía]: un vecino ha reportado una intrusión en la casa Nro %d. Marcamos la dirección en su GPS.", houseId);
		foreach(new play : Player)
		{
			if(PlayerInfo[play][pFaction] == FAC_PMA && CopDuty[play])
			{
			    SendClientMessage(play, COLOR_PMA, string);
				SetPlayerCheckpoint(play, House[houseId][EntranceX], House[houseId][EntranceY], House[houseId][EntranceZ], 2.0);
			}
		}
	} else {
		format(string, sizeof(string), "[Dpto. de policía]: un civil ha reportado un sospechoso por %s en %s.", accusedOf, propName);
		foreach(new play : Player)
		{
			if(PlayerInfo[play][pFaction] == FAC_PMA && CopDuty[play])
			    SendClientMessage(play, COLOR_PMA, string);
		}
	}
	
	format(PlayerInfo[playerid][pAccusedOf], 64, accusedOf);
	format(PlayerInfo[playerid][pAccusedBy], 24, accusedBy);

}

public robberyCancel(playerid) {
    SendClientMessage(playerid, COLOR_YELLOW2, "El robo ha sido cancelado porque no respondiste en 30 segundos.");
    SendClientMessage(felon[playerid], COLOR_YELLOW2, "El robo ha sido cancelado porque la victima no ha respondido en 30 segundos.");
    felon[playerid] = INVALID_PLAYER_ID;
	return 1;
}

public GiveJobExp(playerid, job, exp) {
    if(job == JOB_FELON) {
        new
			level = ThiefJobInfo[playerid][pFelonLevel];
			
		if(level >= 6) {
			return 2;
		}

		if(ThiefJobInfo[playerid][pFelonExp] + exp >= GetJobExpNeeded(playerid, job)) {
			ThiefJobInfo[playerid][pFelonLevel]++;
			ThiefJobInfo[playerid][pFelonExp] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡Ahora eres un delincuente más experimentado y tienes acceso a nuevos comandos!");
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		}
		ThiefJobInfo[playerid][pFelonExp] += exp;
	}
	return 1;
}

stock GetJobExpNeeded(playerid, job) {
	if(job == JOB_FELON) {
        new level = ThiefJobInfo[playerid][pFelonLevel], result;
        result = (level * level + 15) * (JOB_EXP_MULTIPLIER + level);
		return result;
	}
	return 0;
}

stock updateThiefCounters(playerid){
	if(ThiefJobInfo[playerid][pRobPersonLimit] > 0)
		ThiefJobInfo[playerid][pRobPersonLimit]--;
		
	if(ThiefJobInfo[playerid][pTheftPersonLimit] > 0)
		ThiefJobInfo[playerid][pTheftPersonLimit]--;
		
	if(ThiefJobInfo[playerid][pRob247Limit] > 0)
		ThiefJobInfo[playerid][pRob247Limit]--;

	if(ThiefJobInfo[playerid][pRobHouseLimit] > 0)
		ThiefJobInfo[playerid][pRobHouseLimit]--;
		
	if(ThiefJobInfo[playerid][pTheft247Limit] > 0)
		ThiefJobInfo[playerid][pTheft247Limit]--;
}

// Thief system commands

CMD:asaltar(playerid, params[]) {
	new
	    targetMoney,
		randomAmount,
	    string[128],
		target;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	if(ThiefJobInfo[playerid][pFelonLevel] < 3)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para poder asaltar.");

    if(isPlayerJailed(playerid) > 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo estando encarcelado.");

	if(sscanf(params, "u", target)) {
        SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /asaltar [IDJugador/ParteDelNombre]");
        SendClientMessage(playerid, COLOR_WHITE, "Info: si la víctima se encuentra agonizando no obtendrás experiencia.");
		return 1;
	}

	if(target == playerid)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No te puedes hurtar a tí mismo.");

	if(ThiefJobInfo[playerid][pRobPersonLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a robar.", ThiefJobInfo[playerid][pRobPersonLimit] / 60);
	    return 1;
	}

    if(target == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador incorrecto.");

	if(PlayerInfo[playerid][pFaction] != 0 && PlayerInfo[target][pFaction] == PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a esta persona.");

	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");

	if(ThiefJobInfo[playerid][pRobLastVictimPID] == getPlayerMysqlId(target) && !AdminDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar dos veces seguidas a la misma persona.");

  	if(GetDistanceBetweenPlayers(playerid, target) > 4.0)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra demasiado lejos.");

  	if(felon[target] != INVALID_PLAYER_ID)
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya esta siendo robado.");

    if(PlayerInfo[target][pLevel] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un personaje menor de nivel 3.");

	targetMoney = GetPlayerCash(target);
	if(targetMoney <= 0) {
		format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(target));
		PlayerActionMessage(playerid, 15.0, string);
		return 1;
	}
    if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED) {
        SendFMessage(playerid, COLOR_WHITE, "Has intentado robarle a %s, espera la reacción del sujeto...", GetPlayerNameEx(target));
        SendClientMessage(target, COLOR_WHITE, "Te están intentando robar, puedes '/resistirte', '/cooperar' o '/mentir'.");
        SendClientMessage(target, COLOR_WHITE, "Recuerda que si el ladrón te descubre mintiendo se enfadará y perderás más dinero.");
        felon[target] = playerid;
        SetPVarInt(playerid, "robberyCancel", SetTimerEx("robberyCancel", 30000, false, "i", target));
	} else
		{
	        if(targetMoney <= 100)
	            randomAmount = targetMoney;
			else
	  			randomAmount = (targetMoney/2) + random(targetMoney/2) + 1; // Obtendrá si o si la mitad del dinero del jugador, más un valor aleatorio entre 0 y la totalidad de la otra mitad.
	        // Ponemos un límite para volver a robar de 15m.
			ThiefJobInfo[playerid][pRobPersonLimit] = 60 * (15 - random(5));
	  		format(string, sizeof(string), "le ha robado algo de dinero a %s tomando provecho de su incapacidad.", GetPlayerNameEx(target));
	 		PlayerActionMessage(playerid, 15.0, string);
	        printf("%s asalto agonizando a %s", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
			GivePlayerCash(playerid, randomAmount);
			GivePlayerCash(target, -randomAmount);
			if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED && ThiefJobInfo[playerid][pFelonLevel] == 3) {
		 		GiveJobExp(playerid, PlayerInfo[playerid][pJob], 5);
		 	}
			ThiefJobInfo[playerid][pRobLastVictimPID] = getPlayerMysqlId(target);
		}
	if(random(2) == 1) {
		if(GetPlayerWantedLevelEx(playerid) < 2) {
       		SetPlayerWantedLevelEx(playerid, 2);
		} else {
			SetPlayerWantedLevelEx(playerid, GetPlayerWantedLevelEx(playerid) + 1);
		}
		format(string, sizeof(string), "[Dpto. de policía]: un civil ha reportado a %s como sospechoso de robo a mano armada.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
		format(PlayerInfo[playerid][pAccusedOf], 64, "robo a mano armada");
		format(PlayerInfo[playerid][pAccusedBy], 24, "anónimo");
    }
	return 1;
}

CMD:resistirte(playerid, params[]) {
	if(felon[playerid] != INVALID_PLAYER_ID) {
		PlayerActionMessage(playerid, 15.0, "se resiste al robo.");
		SendClientMessage(felon[playerid], COLOR_WHITE, "La victima ha rechazado darte del dinero.");
		KillTimer(GetPVarInt(felon[playerid], "robberyCancel"));
		felon[playerid] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:mentir(playerid, params[]) {
	new
	    string[128],
	    targetMoney = GetPlayerCash(playerid);
	    
	if(felon[playerid] != INVALID_PLAYER_ID) {
	    if(random(1 + ThiefJobInfo[felon[playerid]][pFelonLevel]) == 0) {
			format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(playerid));
			PlayerActionMessage(felon[playerid], 15.0, string);
			SendClientMessage(playerid, COLOR_WHITE, "Has logrado engañar al delincuente y no has perdido dinero.");
	    } else {
	        PlayerActionMessage(playerid, 15.0, "ha sido descubierto intentando engañar al ladrón.");
            format(string, sizeof(string), "le ha robado algo de dinero a %s.", GetPlayerNameEx(playerid));
        	PlayerActionMessage(felon[playerid], 15.0, string);
			GivePlayerCash(felon[playerid], targetMoney);
			GivePlayerCash(playerid, -targetMoney);
	   		if(ThiefJobInfo[felon[playerid]][pFelonLevel] == 3) {
		 		GiveJobExp(felon[playerid], PlayerInfo[felon[playerid]][pJob], 5);
		 	}
			printf("%s asalto a %s", GetPlayerNameEx(felon[playerid]), GetPlayerNameEx(playerid));
	    }
	    ThiefJobInfo[felon[playerid]][pRobLastVictimPID] = getPlayerMysqlId(playerid);
	    ThiefJobInfo[felon[playerid]][pRobPersonLimit] = 60 * (15 - random(5));
	    KillTimer(GetPVarInt(felon[playerid], "robberyCancel"));
	    felon[playerid] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:cooperar(playerid, params[]) {
	new
	    string[128],
	    targetMoney = GetPlayerCash(playerid),
		randomAmount = targetMoney / 2 + random(targetMoney / 2) + 1;

	if(felon[playerid] != INVALID_PLAYER_ID) {
	    if(targetMoney > 1) {
			format(string, sizeof(string), "le ha robado algo de dinero a %s.", GetPlayerNameEx(playerid));
			PlayerActionMessage(felon[playerid], 15.0, string);
			SendClientMessage(playerid, COLOR_YELLOW2, "Has cooperado y el ladrón te ha robado algo de dinero.");
			GivePlayerCash(felon[playerid], randomAmount);
			GivePlayerCash(playerid, -randomAmount);
			if(ThiefJobInfo[felon[playerid]][pFelonLevel] == 3) {
		 		GiveJobExp(felon[playerid], PlayerInfo[felon[playerid]][pJob], 5);
		 	}
		} else {
			format(string, sizeof(string), "intenta robarle algo de dinero a %s pero al parecer no tiene nada.", GetPlayerNameEx(playerid));
			PlayerActionMessage(felon[playerid], 15.0, string);
		}
		printf("%s asalto a %s", GetPlayerNameEx(felon[playerid]), GetPlayerNameEx(playerid));
		ThiefJobInfo[felon[playerid]][pRobPersonLimit] = 60 * (15 - random(5));
		ThiefJobInfo[felon[playerid]][pRobLastVictimPID] = getPlayerMysqlId(playerid);
		KillTimer(GetPVarInt(felon[playerid], "robberyCancel"));
		felon[playerid] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:asaltartienda(playerid, params[]) {
	new
	    business = GetPlayerBusiness(playerid);
	    
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	if(ThiefJobInfo[playerid][pFelonLevel] < 4)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
		
	if(ThiefJobInfo[playerid][pRob247Limit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a asaltar.", ThiefJobInfo[playerid][pRob247Limit] / 60);
	    return 1;
	}

    if(Business[business][bType] != BIZ_247 && Business[business][bType] != BIZ_CLOT && Business[business][bType] != BIZ_CLOT2 && Business[business][bType] != BIZ_CLUB && Business[business][bType] != BIZ_CLUB2 && Business[business][bType] != BIZ_REST && Business[business][bType] != BIZ_HARD)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un 24-7 / Local de ropa / Bar / Discoteca o Club Nocturno / Restaurant.");

	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");

	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0);
	
	PlayerActionMessage(playerid, 15.0, "apunta al empleado con el arma y le hace una seña para que le de todo el dinero.");
	
	policeCallTime[playerid] = 20 + random(35);
	SetPVarInt(playerid, "theftTimer", SetTimerEx("theftTimer", 1000, true, "iii", playerid, 1, business));
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	theftTime[playerid] = 60;
	ThiefJobInfo[playerid][pRob247Limit] = 60 * 60;
	return 1;
}

CMD:hurtarcasa(playerid, params[]) {
	new house = GetPlayerHouse(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	if(ThiefJobInfo[playerid][pFelonLevel] < 5)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");

	if(ThiefJobInfo[playerid][pRobHouseLimit] != 0)
 	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a hurtar.", ThiefJobInfo[playerid][pRobHouseLimit] / 60);
	    return 1;
	}

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en una casa.");

 	if(house == PlayerInfo[playerid][pHouseKey])
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes robar tu propia casa!");

	PlayerActionMessage(playerid, 15.0, "empieza a buscar objetos de valor y los almacena en una bolsa.");
	policeCallTime[playerid] = 20 + random(60);
	SetPVarInt(playerid, "theftTimer", SetTimerEx("theftTimer", 1000, true, "iii", playerid, 2, house));
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	theftTime[playerid] = 100;
	ThiefJobInfo[playerid][pRobHouseLimit] = 40 * 60;
	return 1;
}

CMD:hurtartienda(playerid, params[]) {
	new
	    business = GetPlayerBusiness(playerid);
	    
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	if(ThiefJobInfo[playerid][pFelonLevel] < 2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");

	if(ThiefJobInfo[playerid][pTheft247Limit] != 0)
 	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a hurtar.", ThiefJobInfo[playerid][pTheft247Limit] / 60);
	    return 1;
	}

    if(Business[business][bType] != BIZ_247 && Business[business][bType] != BIZ_CLOT && Business[business][bType] != BIZ_CLOT2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un 24-7 o en una tienda de ropa.");
		
    ThiefJobInfo[playerid][pTheft247Limit] = 60 * 30;
	
	PlayerActionMessage(playerid, 15.0, "comienza a tomar mercancía y guardarla debajo de su ropa.");
	theftTime[playerid] = 60;
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
	policeCallTime[playerid] = 20 + random(35);
	SetPVarInt(playerid, "theftTimer", SetTimerEx("theftTimer", 1000, true, "iii", playerid, 0, business));
	return 1;
}

CMD:correr(playerid, params[]) {
    if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	if(GetPVarInt(playerid, "disabled") != DISABLE_STEALING)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar robando para utilizar este comando.");
	    
	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
    theftTime[playerid] = -1;
    DeletePVar(playerid, "stealAmount");
	KillTimer(GetPVarInt(playerid, "theftTimer"));
	PlayerActionMessage(playerid, 15.0, "arroja al suelo todo el dinero/mercancía robado.");
	return 1;
}

CMD:hurtar(playerid, params[])
{
	new rnd, string[128], target, felonLevel = ThiefJobInfo[playerid][pFelonLevel], targetMoney, takeMoney;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
    if(PlayerInfo[playerid][pJailed] > 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo estando encarcelado.");
	if(IsPlayerInAnyVehicle(playerid) && GetVehicleType(GetPlayerVehicleID(playerid)) != VTYPE_BIKE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo desde un vehículo.");
	if(sscanf(params, "u", target)) {
        SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /hurtar [ID/Jugador]");
        SendClientMessage(playerid, COLOR_WHITE, "Info: si la víctima se encuentra agonizando no obtendrás experiencia.");
		return 1;
	}
	if(target == playerid)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No te puedes hurtar a tí mismo.");
	if(ThiefJobInfo[playerid][pTheftPersonLimit] > 0) {
	    SendFMessage(playerid, COLOR_YELLOW2, "Has superado el límite de hurtos, espera %d minutos.", ThiefJobInfo[playerid][pTheftPersonLimit] / 60);
	    return 1;
	}
    if(target == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador incorrecto.");
	if(PlayerInfo[playerid][pFaction] != 0 && PlayerInfo[target][pFaction] == PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a esta persona.");
  	if(GetDistanceBetweenPlayers(playerid, target) > 1.2)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Recuerda que debes estar cerca del bolsillo/cartera de la víctima!");
  	if(felon[target] != INVALID_PLAYER_ID)
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya esta siendo robado.");
    if(PlayerInfo[target][pLevel] < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes robar a un personaje menor de nivel 3.");
	if(ThiefJobInfo[playerid][pTheftLastVictimPID] == getPlayerMysqlId(target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No le puedes hurtar dos veces seguidas a la misma persona.");
 	targetMoney = GetPlayerCash(target);
    if(targetMoney <= 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no tiene nada de valor.");

	rnd = random(3);
	if(rnd == 0) // 33 % de que falle.
	{
		format(string, sizeof(string), "ha realizado unas maniobras para hurtar algo del bolsillo de %s pero es descubierto.", GetPlayerNameEx(target));
        PlayerActionMessage(playerid, 15.0, string);
        SendClientMessage(playerid, COLOR_WHITE, "¡Has fallado y el sujeto lo ha notado, mejor comienza a correr!");
	} else
	    {
			takeMoney = random(110 * felonLevel) + 60;
			if(takeMoney > targetMoney)
   				takeMoney = targetMoney;
		    SendFMessage(playerid, COLOR_WHITE, "Has tomado $%d del sujeto sin que éste se percate de lo sucedido, actúa como si nada hubiera pasado.", takeMoney);
		    SendClientMessage(target, COLOR_WHITE, "[AVISO OOC]: Un sujeto te ha hurtado sin que te des cuenta. Esta información NO la puedes usar IC.");
			GivePlayerCash(target, -takeMoney);
			GivePlayerCash(playerid, takeMoney);
		}
 	if(GetPVarInt(target, "disabled") != DISABLE_DYING && GetPVarInt(target, "disabled") != DISABLE_DEATHBED && ThiefJobInfo[playerid][pFelonLevel] == 1) {
 		GiveJobExp(playerid, PlayerInfo[playerid][pJob], 1);
 	}
	ThiefJobInfo[playerid][pTheftPersonLimit] = 600;
	ThiefJobInfo[playerid][pTheftLastVictimPID] = getPlayerMysqlId(target);
	printf("%s hurto a %s", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
	return 1;
}

CMD:verexp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_WHITE, "Experiencia:");
	SendFMessage(playerid, COLOR_WHITE, "* Delincuente - nivel: %d exp: %d/%d", ThiefJobInfo[playerid][pFelonLevel], ThiefJobInfo[playerid][pFelonExp], GetJobExpNeeded(playerid, JOB_FELON));
	return 1;
}

CMD:delincuenteayuda(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
	    return 1;
	SendClientMessage(playerid, COLOR_WHITE, "[Delincuente]: /hurtar /hurtartienda /asaltar /asaltartienda /hurtarcasa /verexp");
	SendClientMessage(playerid, COLOR_WHITE, "Info: al delinquir conseguirás puntos de experiencia, dependiendo de tu nivel de delincuente algunos...");
	SendClientMessage(playerid, COLOR_WHITE, "delitos no otorgarán más conocimiento del que ya tienes.");
	return 1;
}
