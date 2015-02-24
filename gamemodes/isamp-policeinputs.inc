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
#define INPUTS_SIDE_CASE1					178
#define INPUTS_SIDE_CASE2                 	211
#define INPUTS_SIDE_CASE3                 	695
#define INPUTS_SIDE_CASE4					1150
#define INPUTS_SIDE_CASE5					211


// POLICE DEFINES
#define INPUTS_POLICE_CASE1					6
#define INPUTS_POLICE_CASE2                 83
#define INPUTS_POLICE_CASE3                 133
#define INPUTS_POLICE_CASE4                 295
#define INPUTS_POLICE_CASE5                 306
#define INPUTS_POLICE_CASE6                 256
#define INPUTS_POLICE_CASE7                 506
#define INPUTS_POLICE_CASE8                 922
#define INPUTS_POLICE_CASE9                 778
#define INPUTS_POLICE_CASE10                595

// DEFINES BUY INPUTS
#define POS_INPUTS_NORTE_X                  1417.3534
#define POS_INPUTS_NORTE_Y                  -1282.6400
#define POS_INPUTS_NORTE_Z                  13.5661

#define POS_INPUTS_SUR_X                    2394.1809
#define POS_INPUTS_SUR_Y                    -2008.6335
#define POS_INPUTS_SUR_Z                    13.5537

// DEFINES UNLOAD INPUTS
#define PMA_WAREHOUSE_X             1568.69
#define PMA_WAREHOUSE_Y             -1689.97
#define PMA_WAREHOUSE_Z             6.21875

#define SIDE_WAREHOUSE_X            1216.94
#define SIDE_WAREHOUSE_Y            -1676.9
#define SIDE_WAREHOUSE_Z            13.4521


new GEOF = 0,
 	STARS = 0
;


stock IsAtArmoryInputs(playerid)
{
	if(PlayerToPoint(4.0, playerid, POS_INPUTS_NORTE_X, POS_INPUTS_NORTE_Y, POS_INPUTS_NORTE_Z) ||
		PlayerToPoint(4.0, playerid, POS_INPUTS_SUR_X, POS_INPUTS_SUR_Y, POS_INPUTS_SUR_Z)) {
        return 1;
    }
    return 0;
}

stock bool:CheckFreeSpaceForDuty(playerid)
{
	if(GetHandItem(playerid, HAND_RIGHT) != 0 || GetHandItem(playerid, HAND_LEFT) != 0 || GetBackItem(playerid) != 0 || SearchInvFreeSlot(playerid) == -1)
	    return false;
	else
		return true;
}

stock bool:CheckTakeInputs(playerid)
{
	if(PlayerInfo[playerid][pTakeInputs] >= 2)
	    return false;
	else
		return true;
}

//===================================COMANDOS===================================

CMD:schaleco(playerid, params[])
{
	new Float:armour;

    if(!isPlayerSideOnDuty(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar junto a los casilleros!");

    GetPlayerArmour(playerid, armour);
    
	if(armour == 0.0)
	{
		PlayerActionMessage(playerid, 15.0, "toma un chaleco antibalas de su casillero.");
		SetPlayerArmour(playerid, 100);
	}
	else
	{
		PlayerActionMessage(playerid, 15.0, "deja el chaleco antibalas en su casillero.");
		SetPlayerArmour(playerid, 0);
	}
	return 1;
}

CMD:sequipo(playerid, params[])
{
	new equipo;

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
		return SendClientMessage(playerid, COLOR_YELLOW2, "ARMERO: Ya has tomado demasiadas armas y municiones, pídele autorización a un superior para retirar nuevamente.");
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

		    ResetPlayerWeapons(playerid);
		    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
		    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_SILENCED, 100);
            PlayerTakeInput(playerid, FAC_SIDE, INPUTS_SIDE_CASE1, "EQUIPO 1");
		}
		case 2:
		{
  			if(PlayerInfo[playerid][pRank] > 7)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE2)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

			ResetPlayerWeapons(playerid);
		    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
		    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
            PlayerTakeInput(playerid, FAC_SIDE, INPUTS_SIDE_CASE2, "EQUIPO 2");
		}
		case 3:
		{
        	if(PlayerInfo[playerid][pRank] > 4 || STARS != 1)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
				
         	ResetPlayerWeapons(playerid);
		    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
            SetBackItemAndParam(playerid, WEAPON_SNIPER, 40);
			SetPlayerSkin(playerid, 285); // Geof
			PlayerTakeInput(playerid, FAC_SIDE, INPUTS_SIDE_CASE3, "EQUIPO 3");
		}
		case 4:
		{
        	if(PlayerInfo[playerid][pRank] > 4 || STARS != 1)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE4)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
				
         	ResetPlayerWeapons(playerid);
		    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
            SetBackItemAndParam(playerid, WEAPON_M4, 250);
			SetPlayerSkin(playerid, 285); // Geof
			PlayerTakeInput(playerid, FAC_SIDE, INPUTS_SIDE_CASE4, "EQUIPO 4");
		}
		case 5:
		{
  			if(PlayerInfo[playerid][pRank] > 3)
     			return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < INPUTS_SIDE_CASE5)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

  			ResetPlayerWeapons(playerid);
		    SetHandItemAndParam(playerid, HAND_LEFT, WEAPON_CAMERA, 20);
		    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_KNIFE, 1);
            SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 60);
            PlayerTakeInput(playerid, FAC_SIDE, INPUTS_SIDE_CASE5, "EQUIPO 5");
		}
	}
	PlayerActionMessage(playerid, 15.0, "toma su equipo de los casilleros.");
	tazerStatus[playerid] = TAZER_EQUIPPED;
	return 1;
}

CMD:pequipo(playerid, params[])
{
	new equipo;

	if(!isPlayerCopOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	if(sscanf(params, "i", equipo))
	{
		SendClientMessage(playerid, COLOR_WHITE, "{5CCAF1}[Sintaxis]:{C8C8C8} /pequipo [equipo]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ Casilleros PM _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Macana - Tazer (Cadete)							 6: Macana - Tazer - Granada de humo - Deagle - Escopeta (GEOF 1)");
		SendClientMessage(playerid, COLOR_GRAD1, "| 2: Macana - Tazer - 9mm (Oficial)                    7: Macana - Tazer - Granada de humo - Deagle - MP5 (GEOF. 2)");
		SendClientMessage(playerid, COLOR_GRAD1, "| 3: Macana - Tazer - 9mm - Escopeta (Oficial Mayor)	 8: Macana - Tazer - Granada de humo - Deagle - Fusil M4 (GEOF 3)");
		SendClientMessage(playerid, COLOR_GRAD1, "| 4: Macana - Tazer - Deagle - Escopeta (Subinspector) 9: Macana - Tazer - Granada de humo - Deagle - Rifle francotirador (GEOF 4)");
		SendClientMessage(playerid, COLOR_GRAD1, "| 5: Macana - Tazer - Deagle - Rifle (Inspector)		 10: Macana - Tazer - Deagle - MP5 (D.I.)");
		return 1;
	}
	if(!CheckTakeInputs(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "ARMERO: Ya has tomado demasiadas armas y municiones, pídele autorización a un superior a ver si te dejo tomar más o no.");
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
				
    		ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE1, "EQUIPO 1");
      	}
       	case 2:
		{
    		if(PlayerInfo[playerid][pRank] > 7)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE2)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

    		ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_COLT45, 100);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE2, "EQUIPO 2");
		}
  		case 3:
  		{
    		if(PlayerInfo[playerid][pRank] > 6)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

			ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_COLT45, 100);
			SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 25);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE3, "EQUIPO 3");
       	}
       	case 4:
	   	{
	   		if(PlayerInfo[playerid][pRank] > 5)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE4)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

		    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 75);
			SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 40);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE4, "EQUIPO 4");
   		}
        case 5:
		{
            if(PlayerInfo[playerid][pRank] > 4)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE5)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

		    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 75);
			SetBackItemAndParam(playerid, WEAPON_RIFLE, 40);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE5, "EQUIPO 5");
        }
        case 6:
		{
        	if(PlayerInfo[playerid][pRank] > 6 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE6)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

    	    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
			SetBackItemAndParam(playerid, WEAPON_SHOTGUN, 60);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE6, "EQUIPO 6");
        }
        case 7:
		{
			if(PlayerInfo[playerid][pRank] > 5 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE7)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
				
    	    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
			SetBackItemAndParam(playerid, WEAPON_MP5, 200);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE7, "EQUIPO 7");
        }
        case 8:
		{
			if(PlayerInfo[playerid][pRank] > 4 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE8)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

		    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
			SetBackItemAndParam(playerid, WEAPON_M4, 200);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE8, "EQUIPO 8");
        }
        case 9:
		{
			if(PlayerInfo[playerid][pRank] > 4 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo o G.E.O.F. no está autorizado.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE9)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");
				
			ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_TEARGAS, 4);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 50);
			SetBackItemAndParam(playerid, WEAPON_SNIPER, 40);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE9, "EQUIPO 9");
        }
        case 10:
		{
			if(PlayerInfo[playerid][pRank] > 4)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
            if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] <= INPUTS_POLICE_CASE10)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No hay insumos suficientes en el depósito.");

		    ResetPlayerWeapons(playerid);
			SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
			SetInvItemAndParam(playerid, SearchInvFreeSlot(playerid), WEAPON_DEAGLE, 35);
			SetBackItemAndParam(playerid, WEAPON_MP5, 200);
			PlayerTakeInput(playerid, FAC_PMA, INPUTS_POLICE_CASE10, "EQUIPO 10");
        }
        default:
            return SendClientMessage(playerid, COLOR_YELLOW2, "Selecciona una opción de equipo válida.");
	}
	PlayerActionMessage(playerid, 15.0, "toma su equipo de los casilleros.");
	tazerStatus[playerid] = TAZER_EQUIPPED;
	return 1;
}

CMD:ptazer(playerid, params[])
{
	if(!isPlayerCopOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	PlayerActionMessage(playerid, 15.0, "toma un tazer de los casilleros.");
	ResetPlayerWeapons(playerid);
	tazerStatus[playerid] = TAZER_EQUIPPED;
	return 1;
}

CMD:stazer(playerid, params[])
{
	if(!isPlayerSideOnDuty(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar junto a los casilleros!");
	PlayerActionMessage(playerid, 15.0, "toma un tazer de los casilleros.");
	ResetPlayerWeapons(playerid);
	tazerStatus[playerid] = TAZER_EQUIPPED;
	return 1;
}

CMD:pmacana(playerid, params[])
{
	if(!isPlayerCopOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	if(!CheckFreeSpaceForDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener la mano derecha libre para tomar la macana.");
	ResetPlayerWeapons(playerid);
    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
	PlayerActionMessage(playerid, 15.0, "toma una macana de los casilleros.");
	return 1;
}

CMD:smacana(playerid, params[])
{
	if(!isPlayerSideOnDuty(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar junto a los casilleros!");
	if(!CheckFreeSpaceForDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener la mano derecha libre para tomar la macana.");
    ResetPlayerWeapons(playerid);
    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_NITESTICK, 1);
	PlayerActionMessage(playerid, 15.0, "toma una macana de los casilleros.");
	return 1;
}

CMD:pchaleco(playerid, params[])
{
	new Float:armour;

    if(!isPlayerCopOnDuty(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar junto a los casilleros!");

    GetPlayerArmour(playerid, armour);
    
	if(armour == 0.0)
	{
		PlayerActionMessage(playerid, 15.0, "toma un chaleco antibalas de su casillero.");
		SetPlayerArmour(playerid, 100);
	}
	else
	{
		PlayerActionMessage(playerid, 15.0, "deja el chaleco antibalas en su casillero.");
		SetPlayerArmour(playerid, 0);
	}
	return 1;
}

CMD:inputsdebug(playerid, params[])
{
	new targetid;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /inputdebug [playerid]");
	if(targetid < 0 || targetid >= MAX_PLAYERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	    
	SendFMessage(playerid, COLOR_YELLOW, "pTakeInputs [%d] = %d", targetid, PlayerInfo[targetid][pTakeInputs]);
	return 1;
}

PlayerTakeInput(playerid, faction, input, text[])
{
	FactionInfo[faction][fMaterials] -= input;
	log(playerid, LOG_INPUTS, text);
	if(PlayerInfo[playerid][pRank] > 2)
		PlayerInfo[playerid][pTakeInputs] ++;
}

ResetPlayerInputs(playerid)
{
    PlayerInfo[playerid][pTakeInputs] = 0;
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
    if(!IsPlayerConnected(targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inválida.");
	    
	if(PlayerInfo[targetid][pTakeInputs] >= 2)
	{
     	PlayerInfo[targetid][pTakeInputs] --;
     	PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
     	format(string, sizeof(string), "%s ha autorizado a %s a retirar más armas y municiones del depósito.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
     	SendFactionMessage(FAC_PMA, COLOR_PMA, string);
		if(!usingMask[playerid])
			format(string, sizeof(string), "%s dice por radio: Armero, autorizo a %s a retirar más armas y municiones.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "Enmascarado dice por radio: Armero, autorizo a %s a retirar mas armas y municiones.", GetPlayerNameEx(targetid));
  		ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 1);
	}
    return 1;
}

CMD:sautorizar(playerid, params[])
{
	new targetid, string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_SIDE)
        return 1;
	if(PlayerInfo[playerid][pRank] > 2)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Tu rango no tiene acceso a este comando.");
    if(PlayerInfo[playerid][pRadio] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una radio, vé y compra una en algún 24-7.");
    if(sscanf(params, "u", targetid))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /sautorizar [ID/Jugador]");
    if(!IsPlayerConnected(targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inválida.");

	if(PlayerInfo[targetid][pTakeInputs] >= 2)
	{
     	PlayerInfo[targetid][pTakeInputs] --;
     	PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
     	format(string, sizeof(string), "%s ha autorizado a %s a retirar más armas y municiones del depósito.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
     	SendFactionMessage(FAC_SIDE, COLOR_PMA, string);
		if(!usingMask[playerid])
			format(string, sizeof(string), "%s dice por radio: Armero, autorizo a %s a retirar más armas y municiones.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "Enmascarado dice por radio: Armero, autorizo a %s a retirar mas armas y municiones.", GetPlayerNameEx(targetid));
  		ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 1);
	}
    return 1;
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

CMD:verregistros(playerid, params[])
{
	new targetname[MAX_PLAYER_NAME],
	    query[128];

    if(PlayerInfo[playerid][pRank] > 4)
        return 1;
    if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;
    if(sscanf(params, "s[24]", targetname))
		return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /verregistros [Nombre del jugador] (Con el '_')");

	mysql_real_escape_string(targetname, targetname);
	format(query, sizeof(query), "SELECT * FROM `log_inputs` WHERE `pName` = '%s' ORDER BY date DESC LIMIT 30", targetname);
	mysql_function_query(dbHandle, query, true, "OnLogPmaLoad", "is", playerid, targetname);
	return 1;
}

CMD:comprarinsumos(playerid, params[])
{
	new amount,
		freehand = SearchFreeHand(playerid);
	
	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
    	return 1;
	if(!IsAtArmoryInputs(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando en cualquier lado.");
    if(sscanf(params, "i", amount))
    {
        SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [cantidad] | $%d cada insumo.", GetItemPrice(ITEM_ID_MATERIALES));
		return 1;
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
	if(freehand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar la caja de insumos.");
	if(amount < 1 || amount > 1300)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad de insumos no debe ser menor a 1 o mayor a 1300.");
	if(GetPlayerCash(playerid) < amount * GetItemPrice(ITEM_ID_MATERIALES))
	{
		SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, necesitas $%d.", amount * GetItemPrice(ITEM_ID_MATERIALES));
		return 1;
	}

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    SetHandItemAndParam(playerid, freehand, ITEM_ID_MATERIALES, amount);
	GivePlayerCash(playerid, -amount * GetItemPrice(ITEM_ID_MATERIALES));
	SendClientMessage(playerid, COLOR_WHITE, "Vé al depósito y descarga los insumos con /guardarinsumos. Utiliza /nocargar para sacar la animación de carga.");
	PlayerActionMessage(playerid, 15.0, "compra una caja de insumos.");
	return 1;
}

CMD:guardarinsumos(playerid, params[])
{
	new hand = SearchHandsForItem(playerid, ITEM_ID_MATERIALES),
	    amount;

    if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
    	return 1;
	if(!PlayerToPoint(4.0, playerid, PMA_WAREHOUSE_X, PMA_WAREHOUSE_Y, PMA_WAREHOUSE_Z) && !PlayerToPoint(4.0, playerid, SIDE_WAREHOUSE_X, SIDE_WAREHOUSE_Y, SIDE_WAREHOUSE_Z))
		return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
	if(hand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener una caja de insumos en tus manos para descargar.");
	amount = GetHandParam(playerid, hand);
	if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] + amount > 270000)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar más insumos al depósito ya que el mismo está lleno.");
	
	FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] += amount;
	SetHandItemAndParam(playerid, hand, 0, 0);
	PlayerActionMessage(playerid, 15.0, "descarga una caja de insumos en el depósito.");
 	return 1;
}
