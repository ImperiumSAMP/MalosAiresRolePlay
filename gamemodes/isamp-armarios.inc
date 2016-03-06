#if defined _isamp_armarios_included
	#endinput
#endif
#define _isamp_armarios_included

//===========================ARMARIOS PARA LAS CASAS============================

//================================CONSTANTES====================================

//============================VARIABLES INTERNAS================================

new LockerStatus[MAX_HOUSES];

//===============================FUNCIONES======================================

//=================================COMANDOS=====================================

//============================[EXPERIMENTAL]====================================

CMD:arm(playerid, params[])
{
 	cmd_armario(playerid, params);
	return 1;
}

CMD:armario(playerid, params[])
{
	new cmd[32],
		param1,
		param2[32],
		houseid = GetPlayerHouse(playerid);

	if(houseid == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "隆Debes estar dentro de una casa!");

	if(sscanf(params, "s[32]I(-1)S(-1)[32]", cmd, param1, param2))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/arm)ario [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar (para abrirlo o cerrarlo) - guardar");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomardinero [cant] - guardardinero [cant] - tomardroga [cant] [tipo] - guardardroga [cant] [tipo]");

		if(LockerStatus[houseid] == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");

		if(!Container_Show(houseid, CONTAINER_TYPE_HOUSE, House[houseid][ContainerID], playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del armario. Reportar a un administador.");

		SendClientMessage(playerid, COLOR_WHITE, "======================[ARMARIO]======================");
        if(House[houseid][Money] > 0) {
        	SendFMessage(playerid, COLOR_WHITE, " - Dinero en efectivo: $%d", House[houseid][Money]);
		}
		if(House[houseid][Marijuana] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Marihuana: %d gramos.", House[houseid][Marijuana]);
		}
		if(House[houseid][LSD] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - LSD: %d dosis.", House[houseid][LSD]);
		}
		if(House[houseid][Ecstasy] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - 蓌tasis: %d dosis.", House[houseid][Ecstasy]);
		}
		if(House[houseid][Cocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Coca韓a: %d gramos.", House[houseid][Cocaine]);
		}
        SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
		return 1;

	}
	
	if(strcmp(cmd, "usar", true) == 0) {
	
		if((House[houseid][Income] == 1 && House[houseid][Tenant] == PlayerInfo[playerid][pName]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerCmeMessage(playerid, 15.0, 5000, "Coloca unas llaves en la cerradura de la puerta y abre el armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PlayerCmeMessage(playerid, 15.0, 5000, "Cierra las puertas del armario y quita las llaves de la cerradura.");
			    	LockerStatus[houseid] = 0;
				}
		}
		else if((House[houseid][Income] == 0 && House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerCmeMessage(playerid, 15.0, 5000, "Coloca unas llaves en la cerradura de la puerta y abre el armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PPlayerCmeMessage(playerid, 15.0, 5000, "Cierra las puertas del armario y quita las llaves de la cerradura.");
			    	LockerStatus[houseid] = 0;
				}
		} else
			return SendClientMessage(playerid, COLOR_YELLOW2, "o tienes las llaves de este armario!");
			
	} else if(strcmp(cmd, "tomardinero", true) == 0) {
	
 		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 200000)
            return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de $1 o mas de $200.000 por vez.");
		if(param1 > House[houseid][Money])
		   return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de dinero.");

        House[houseid][Money] -= param1;
        GivePlayerCash(playerid, param1);
        SaveHouse(houseid);
		PlayerCmeMessage(playerid, 15.0, 5000, "Toma algo de dinero del interior del armario.");

	} else if(strcmp(cmd, "guardardinero", true) == 0) {

 		if(LockerStatus[houseid] == 0)
      		return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes usar 茅ste comando estando agonizando!");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "ebes ser al menos nivel 3 para utilizar 閟te comando!");
		if(param1 < 1 || param1 > 200000)
 			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes guardar menos de $1 o mas de $200.000!");
		if((House[houseid][Money] + param1) > 10000000)
   			return SendClientMessage(playerid, COLOR_YELLOW2, "l armario s贸lo puede contener hasta $10.000.000!");
		if(GetPlayerCash(playerid) < param1)
 			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de dinero.");

		House[houseid][Money] += param1;
        GivePlayerCash(playerid, -param1);
        SaveHouse(houseid);
        PlayerCmeMessage(playerid, 15.0, 5000, "Guarda algo de dinero en el interior del armario.");

	} else if(strcmp(cmd, "guardar", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes hacerlo en 閟te momento!");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes usar 閟te comando estando agonizando!");
		if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes hacerlo con el tazer!");
		if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_TELEFONO_CELULAR)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes hacerlo con el tel茅fono!");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "ebes esperar un tiempo antes de volver a interactuar con otro item!");

		new itemid = GetHandItem(playerid, HAND_RIGHT),
			itemparam = GetHandParam(playerid, HAND_RIGHT),
			str[128];

		if(itemid == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		if(!Container_AddItemAndParam(House[houseid][ContainerID], itemid, itemparam))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el armario / El 韙em es demasiado chico para guardarse en un armario.");

		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado l贸gico y grafico.
		
		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
		
		format(str, sizeof(str), "Guarda un/a %s en el armario.", GetItemName(itemid));
		PlayerCmeMessage(playerid, 15.0, 5000, str);

	} else if(strcmp(cmd, "guardari", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes usar 閟te comando estando agonizando!");
		if(GetHandItem(playerid, HAND_LEFT) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes hacerlo con el tazer!");
		if(GetHandItem(playerid, HAND_LEFT) == ITEM_ID_TELEFONO_CELULAR)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes hacerlo con el telefono!");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "ebes esperar un tiempo antes de volver a interactuar con otro item!");

		new itemid = GetHandItem(playerid, HAND_LEFT),
			itemparam = GetHandParam(playerid, HAND_LEFT),
			str[128];

		if(itemid == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		if(!Container_AddItemAndParam(House[houseid][ContainerID], itemid, itemparam))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el armario / El 韙em es demasiado chico para guardarse en un armario.");

		SetHandItemAndParam(playerid, HAND_LEFT, 0, 0); // Borrado l贸gico y grafico.

		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

		format(str, sizeof(str), "Guarda un/a %s en el interior del armario.", GetItemName(itemid));
		PlayerCmeMessage(playerid, 15.0, 5000, str);

	} else if(strcmp(cmd, "tomardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes retirar menos de 1 o mas de 10.000!");

		if(strcmp(param2, "marihuana", true) == 0) {
		    if(param1 > House[houseid][Marijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Marijuana] -= param1;
            PlayerInfo[playerid][pMarijuana] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del interior del armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {
  			if(param1 > House[houseid][LSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][LSD] -= param1;
            PlayerInfo[playerid][pLSD] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del interior del armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > House[houseid][Cocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Cocaine] -= param1;
            PlayerInfo[playerid][pCocaine] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del interior del armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > House[houseid][Ecstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Ecstasy] -= param1;
            PlayerInfo[playerid][pEcstasy] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del interior del armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un t韕o de droga v醠ido.");

	} else if(strcmp(cmd, "guardardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes usar 閟te comando estando agonizando!");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "ebes ser al menos nivel 3 para utilizar este comando!");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes guardar menos de 1 o mas de 10.000!");

		if(strcmp(param2, "marihuana", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pMarijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Marijuana] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Marijuana] += param1;
            PlayerInfo[playerid][pMarijuana] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el interior del armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {

  			if(param1 > PlayerInfo[playerid][pLSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][LSD] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][LSD] += param1;
            PlayerInfo[playerid][pLSD] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el interior del armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pCocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Cocaine] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Cocaine] += param1;
            PlayerInfo[playerid][pCocaine] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el interior del armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pEcstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Ecstasy] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Ecstasy] += param1;
            PlayerInfo[playerid][pEcstasy] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el interior del armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un t韕o de droga v醠ido.");
	}
	return 1;
}

Dialog:Dlg_Show_House_Container(playerid, response, listitem, inputtext[])
{
	new houseid = Container_Selection[playerid][csOriginalId],
 		container_id = Container_Selection[playerid][csId];

	ResetContainerSelection(playerid);
	
   	if(response)
	{
        new itemid,
            itemparam,
            str[128],
			free_hand = SearchFreeHand(playerid);

		if(GetPlayerHouse(playerid) != houseid)
    		return SendClientMessage(playerid, COLOR_YELLOW2, "ebes estar en la casa!");
		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "o puedes usar 茅ste comando estando agonizando!");
		if(free_hand == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el item ya que tienes ambas manos ocupadas.");

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SetHandItemAndParam(playerid, free_hand, itemid, itemparam); // Creaci贸n l贸gica y grafica en la mano.

            SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

			format(str, sizeof(str), "Toma un/a %s del interior del armario.", GetItemName(itemid));
			PlayerCmeMessage(playerid, 15.0, 5000, str);
		}
		else
		{
	        SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra vac韔 o el slot especificado es inv醠ido.");
		}
	}
	return 1;
}

CMD:containerdebug(playerid, params[])
{
	new id;
	new type;

	if(sscanf(params, "iI(1)", type, id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /containerdebug [tipo] [houseid/vehicleid]");

	if(type == 1)
	{
		SendFMessage(playerid, -1, "Veh[ContainerID] = %d, Veh[ContainerSQLID] = %d", VehicleInfo[id][VehContainerID], VehicleInfo[id][VehContainerSQLID]);
		SendFMessage(playerid, -1, "container inicializo con total: %d, used: %d", Container_GetTotalSpace(VehicleInfo[id][VehContainerID]), Container_GetUsedSpace(VehicleInfo[id][VehContainerID]));
	    SendFMessage(playerid, -1, "container inicializo con sqlid: %d, minimo item space: %d", Container_GetSQLID(VehicleInfo[id][VehContainerID]), Container_GetMinItemSpace(VehicleInfo[id][VehContainerID]));
	}
	else if(type == 4)
	{
		SendFMessage(playerid, -1, "House[ContainerID] = %d, House[ContainerSQLID] = %d", House[id][ContainerID], House[id][ContainerSQLID]);
		SendFMessage(playerid, -1, "container inicializo con total: %d, used: %d", Container_GetTotalSpace(House[id][ContainerID]), Container_GetUsedSpace(House[id][ContainerID]));
	    SendFMessage(playerid, -1, "container inicializo con sqlid: %d, minimo item space: %d", Container_GetSQLID(House[id][ContainerID]), Container_GetMinItemSpace(House[id][ContainerID]));
	}
	return 1;
}

//==============================[FIN EXPERIMENTAL]==============================
