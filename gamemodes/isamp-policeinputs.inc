#if defined _isamp_policeinputs_included
	#endinput
#endif
#define _isamp_policeinputs_included

/*
+----------------------------------------------------------------------------+
|                                                                            |
|            Sistema de insumos de la Policia Metropolitana y SIDE           |
|							  	  por crEpid							     |
|                                                                            |
|              System inputs of the Metropolitan Police and SIDE             |
|							  	   by crEpid							     |
|                                                                            |
+----------------------------------------------------------------------------+
*/

// LOG DEFINE
#define LOG_INPUTS              4

// DEFINES POS DUTY MOVIDO
#define POS_POLICE_DUTY_X 		223.3068
#define POS_POLICE_DUTY_Y       186.2766
#define POS_POLICE_DUTY_Z       1003.0000

#define POS_SIDE_DUTY_X         261.8023
#define POS_SIDE_DUTY_Y			109.7926
#define POS_SIDE_DUTY_Z			1004.6172

// SIDE DEFINES
#define INPUTS_SIDE_CASE1					42
#define INPUTS_SIDE_CASE2                 	48
#define INPUTS_SIDE_CASE3                 	135
#define INPUTS_SIDE_CASE4					217
#define INPUTS_SIDE_CASE5					48


// POLICE DEFINES
#define INPUTS_POLICE_CASE1					11
#define INPUTS_POLICE_CASE2                 25
#define INPUTS_POLICE_CASE3                 32
#define INPUTS_POLICE_CASE4                 63
#define INPUTS_POLICE_CASE5                 65
#define INPUTS_POLICE_CASE6                 72
#define INPUTS_POLICE_CASE7                 117
#define INPUTS_POLICE_CASE8                 192
#define INPUTS_POLICE_CASE9                 166
#define INPUTS_POLICE_CASE10                117

// DEFINES BUY INPUTS
#define POS_INPUTS_NORTE_X                  1417.3534
#define POS_INPUTS_NORTE_Y                  -1282.6400
#define POS_INPUTS_NORTE_Z                  13.5661

#define POS_INPUTS_SUR_X                    2394.1809
#define POS_INPUTS_SUR_Y                    -2008.6335
#define POS_INPUTS_SUR_Z                    13.5537


new
    GEOF = 0,
 	STARS = 0
;


stock IsAtArmoryInputs(playerid)
{
	if (PlayerToPoint(4.0, playerid, POS_INPUTS_NORTE_X, POS_INPUTS_NORTE_Y, POS_INPUTS_NORTE_Z) ||
		PlayerToPoint(4.0, playerid, POS_INPUTS_SUR_X, POS_INPUTS_SUR_Y, POS_INPUTS_SUR_Z)) {
        return 1;
    }
    return 0;
}

forward OnLogPmaLoad(playerid, targetname[]);
public OnLogPmaLoad(playerid, targetname[])
{
	new result[128],
        result2[128],
	     rows,
	     fields,
	     cont,
	     aux = 0,
	     str[128] = "";

	cache_get_data(rows, fields);

	if(rows)
	{
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "=========================[Registros de %s]=========================", targetname);
		while(aux < rows)
		{
		    cache_get_field_content(aux, "text", result);
   			cache_get_field_content(aux, "date", result2);
			format(str, sizeof(str), "%s[%s] %s | ", str, result2, result);
			cont ++;
			if(cont == 3)
			{
			   cont = 0;
			   SendClientMessage(playerid, COLOR_WHITE, str);
			   format(str, sizeof(str), "");
			}
			aux ++;
		}
		if(cont != 3)
		  SendClientMessage(playerid, COLOR_WHITE, str);
	}
	else
	SendClientMessage(playerid, COLOR_YELLOW2, "Esa persona no posee ningún registro de equipo en la base de datos de la PMA.");
	return 1;
}

stock printLogPma(playerid,targetname[]) {
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `log_inputs` WHERE pName='%s' ORDER BY date DESC LIMIT 30", targetname);
	mysql_function_query(dbHandle, query, true, "OnLogPmaLoad", "is", playerid, targetname);
	return 1;
}

//                                COMANDOS

CMD:sequipo(playerid, params[])
{
	new equipo, string[128];

	if(!isPlayerSideOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando en cualquier lado.");
	if(sscanf(params, "i", equipo))
	{
		SendClientMessage(playerid, COLOR_WHITE, "{5CCAF1}[Sintaxis]:{C8C8C8} /sequipo [equipo]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ Casilleros SIDE _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Externo");
		SendClientMessage(playerid, COLOR_GRAD1, "| 2: Agente");
		SendClientMessage(playerid, COLOR_GRAD2, "| 3: Alpha (S.T.A.R.S.)");
		SendClientMessage(playerid, COLOR_GRAD2, "| 4: Bravo (S.T.A.R.S.)");
		SendClientMessage(playerid, COLOR_GRAD3, "| 5: Staff Profesional");
		return 1;
	}
	if(!CheckTakeInputs(playerid))
	{
		SendClientMessage(playerid, COLOR_YELLOW2, "ARMERO: Ya has tomado demasiadas armas y municiones, pídele autorización a un superior a ver si te dejo tomar más o no.");
		PlayerInfo[playerid][pTakeInputs] = 4;
		return 1;
	}
	if(!CheckFreeSpaceForDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un slot del inventario, la espalda, y ambas manos libres para guardar el equipo.");
	switch(equipo)
	{
		case 1:
		{
        	if(PlayerInfo[playerid][pRank] > 8)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE1)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
			    ResetPlayerWeapons(playerid);
			    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
			    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
	            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_SILENCED, 100);
	            FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_SIDE_CASE1;
	            format(string, sizeof(string), "EQUIPO 1");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
		}
		case 2:
		{
  			if(PlayerInfo[playerid][pRank] > 7)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE2)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
				ResetPlayerWeapons(playerid);
			    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
			    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
	            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
	            FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_SIDE_CASE2;
	            format(string, sizeof(string), "EQUIPO 2");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
		 	}
		}
		case 3:
		{
        	if(PlayerInfo[playerid][pRank] > 4 || STARS != 1)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	         	ResetPlayerWeapons(playerid);
			    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
	            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
	            SetBackItemAndParam(playerid, WEAPON_SNIPER, 40);
				SetPlayerSkin(playerid, 285); // Geof
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_SIDE_CASE3;
				format(string, sizeof(string), "EQUIPO 3");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
		}
		case 4:
		{
        	if(PlayerInfo[playerid][pRank] > 4 || STARS != 1)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE4)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	         	ResetPlayerWeapons(playerid);
			    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
	            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
	            SetBackItemAndParam(playerid, WEAPON_M4, 250);
				SetPlayerSkin(playerid, 285); // Geof
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_SIDE_CASE4;
				format(string, sizeof(string), "EQUIPO 4");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
		}
		case 5:
		{
  			if(PlayerInfo[playerid][pRank] > 3)
     			return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE5)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	  			ResetPlayerWeapons(playerid);
			    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
			    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
	            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
	            FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_SIDE_CASE5;
	            format(string, sizeof(string), "EQUIPO 5");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
		}
	}
	PlayerActionMessage(playerid, 15.0, "toma su equipo de los casilleros.");
	tazerStatus[playerid] = TAZER_EQUIPPED;
	if(PlayerInfo[playerid][pRank] > 2)
	{
	    if(PlayerInfo[playerid][pTakeInputs] == 4) {
	        PlayerInfo[playerid][pTakeInputs] -= 2;
	    } else if(PlayerInfo[playerid][pTakeInputs] == 3) {
	        PlayerInfo[playerid][pTakeInputs] -= 1;
	    } else {
			PlayerInfo[playerid][pTakeInputs] += 1;
		}
 	}
	return 1;
}

CMD:pequipo(playerid, params[])
{
	new equipo, string[128];

	if(!isPlayerCopOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	if(sscanf(params, "i", equipo))
	{
		SendClientMessage(playerid, COLOR_WHITE, "{5CCAF1}[Sintaxis]:{C8C8C8} /pequipo [equipo]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ Casilleros PM _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Macana - Tazer (Cadete)							6: Macana - Tazer - Granada de humo - Deagle - Escopeta (GEOF 1)");
		SendClientMessage(playerid, COLOR_GRAD1, "| 2: Macana - Tazer - 9mm (Oficial)                   7: Macana - Tazer - Granada de humo - Deagle - MP5 (GEOF. 2)");
		SendClientMessage(playerid, COLOR_GRAD2, "| 3: Macana - Tazer - 9mm - Escopeta (Cabo)	        8: Macana - Tazer - Granada de humo - Deagle - Fusil M4 (GEOF 3)");
		SendClientMessage(playerid, COLOR_GRAD2, "| 4: Macana - Tazer - Deagle - Escopeta (Sargento)	9: Macana - Tazer - Granada de humo - Deagle - Rifle francotirador (GEOF 4)");
		SendClientMessage(playerid, COLOR_GRAD3, "| 5: Macana - Tazer - Deagle - Rifle (Sargento Mayor)	10: Macana - Tazer - Deagle - MP5 (D.I.)");
		return 1;
	}
	if(!CheckTakeInputs(playerid))
	{
		SendClientMessage(playerid, COLOR_YELLOW2, "ARMERO: Ya has tomado demasiadas armas y municiones, pídele autorización a un superior a ver si te dejo tomar más o no.");
		PlayerInfo[playerid][pTakeInputs] = 4;
		return 1;
	}
	if(!CheckFreeSpaceForDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un slot del inventario, la espalda, y ambas manos libres para guardar el equipo.");
	switch(equipo)
	{
		case 1:
		{
  			if(PlayerInfo[playerid][pRank] > 8)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
			if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE1)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	    		ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE1;
				format(string, sizeof(string), "EQUIPO 1");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
      	}
       	case 2:
		{
    		if(PlayerInfo[playerid][pRank] > 7)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE2)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	    		ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_COLT45, 100);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE2;
				format(string, sizeof(string), "EQUIPO 2");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
   			}
		}
  		case 3:
  		{
    		if(PlayerInfo[playerid][pRank] > 6)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
				ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_COLT45, 100);
				SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 25);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE3;
				format(string, sizeof(string), "EQUIPO 3");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
       	}
       	case 4:
	   	{
	   		if(PlayerInfo[playerid][pRank] > 5)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE4)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
			    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 75);
				SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 40);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE4;
				format(string, sizeof(string), "EQUIPO 4");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
   		}
        case 5:
		{
            if(PlayerInfo[playerid][pRank] > 4)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE5)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
			    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 75);
				SetBackItemAndParam(playerid, WEAPON_RIFLE, 40);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE5;
				format(string, sizeof(string), "EQUIPO 5");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        case 6:
		{
        	if(PlayerInfo[playerid][pRank] > 6 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE6)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	    	    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
				SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 60);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE6;
				format(string, sizeof(string), "EQUIPO 6");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        case 7:
		{
			if(PlayerInfo[playerid][pRank] > 5 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE7)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
	    	    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
				SetBackItemAndParam(playerid, WEAPON_MP5, 200);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE7;
				format(string, sizeof(string), "EQUIPO 7");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        case 8:
		{
			if(PlayerInfo[playerid][pRank] > 4 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE8)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
			    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
				SetBackItemAndParam(playerid, WEAPON_M4, 200);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE8;
				format(string, sizeof(string), "EQUIPO 8");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        case 9:
		{
			if(PlayerInfo[playerid][pRank] > 4 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE9)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
				ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
				SetBackItemAndParam(playerid, WEAPON_SNIPER, 40);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE9;
				format(string, sizeof(string), "EQUIPO 9");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        case 10:
		{
			if(PlayerInfo[playerid][pRank] > 4)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE10)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
			else
			{
			    ResetPlayerWeapons(playerid);
				SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
				SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 35);
				SetBackItemAndParam(playerid, WEAPON_MP5, 200);
				FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= INPUTS_POLICE_CASE10;
				format(string, sizeof(string), "EQUIPO 10");
    			log(playerid, LOG_INPUTS, string);
				SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: Quedan %d insumos.", FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
			}
        }
        default:
            return SendClientMessage(playerid, COLOR_YELLOW2, "Selecciona una opción de equipo válida.");
	}
	SetPlayerArmour(playerid, 100);
	PlayerActionMessage(playerid, 15.0, "toma su equipo de los casilleros.");
	tazerStatus[playerid] = TAZER_EQUIPPED;
	if(PlayerInfo[playerid][pRank] > 2)
	{
	    if(PlayerInfo[playerid][pTakeInputs] == 4) {
	        PlayerInfo[playerid][pTakeInputs] -= 2;
	    } else if(PlayerInfo[playerid][pTakeInputs] == 3) {
	        PlayerInfo[playerid][pTakeInputs] -= 1;
	    } else {
			PlayerInfo[playerid][pTakeInputs] += 1;
		}
 	}
	return 1;
}

CMD:inputs(playerid, params[]) {
	SendFMessage(playerid, COLOR_GREEN, "[DEBUG]: %d Inputs.", PlayerInfo[playerid][pTakeInputs]);
	return 1;
}

CMD:pautorizar(playerid, params[])
{
	new targetid, string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;
	if(PlayerInfo[playerid][pRank] > 3)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Tu rango no tiene acceso a este comando.");
    if(PlayerInfo[playerid][pRadio] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una radio, vé y compra una en algún 24-7.");
    if(sscanf(params, "u", targetid))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /pautorizar [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inválida.");
	if(PlayerInfo[targetid][pTakeInputs] == 4) {
     	PlayerInfo[targetid][pTakeInputs] = 3;
	    PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
		if(!usingMask[playerid])
			format(string, sizeof(string), "%s dice por radio: Armero, autorizo a %s a retirar más armas y municiones.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "Enmascarado dice por radio: Armero, autorice a %s a retirar mas armas y municiones.", GetPlayerNameEx(targetid));
  		ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 0);
        SendClientMessage(playerid, COLOR_PMA, string);
	}
    return 1;
}

CMD:sautorizar(playerid, params[])
{
	new targetid, string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_SIDE)
        return 1;
	if(PlayerInfo[playerid][pRank] > 3)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Tu rango no tiene acceso a este comando.");
    if(PlayerInfo[playerid][pRadio] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una radio, vé y compra una en algún 24-7.");
    if(sscanf(params, "u", targetid))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /sautorizar [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inválida.");
	if(PlayerInfo[targetid][pTakeInputs] == 4) {
     	PlayerInfo[targetid][pTakeInputs] = 3;
	    PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
		if(!usingMask[playerid])
			format(string, sizeof(string), "%s dice por radio: Armero, autorizo a %s a retirar más armas y municiones.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "Enmascarado dice por radio: Armero, autorice a %s a retirar mas armas y municiones.", GetPlayerNameEx(targetid));
  		ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 0);
        SendClientMessage(playerid, COLOR_PMA, string);
	}
    return 1;
}

CMD:verregistros(playerid, params[])
{
	new targetname[MAX_PLAYER_NAME];

    if(PlayerInfo[playerid][pRank] > 2)
        return 1;
    if(PlayerInfo[playerid][pFaction] == FAC_SIDE || PlayerInfo[playerid][pFaction] == FAC_PMA)
    {
	    if(sscanf(params, "s[24]", targetname))
	     return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /verregistros [Nombre del jugador] (Con el '_')");

		mysql_real_escape_string(targetname, targetname);
		printLogPma(playerid, targetname);
	}
	return 1;
}
