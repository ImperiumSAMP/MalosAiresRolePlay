#if defined _isamp_armarios_included
	#endinput
#endif
#define _isamp_armarios_included

new LockerStatus[MAX_HOUSES];

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
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar dentro de una casa!");

	if(sscanf(params, "s[32]I(-1)S(-1)[32]", cmd, param1, param2))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/arm)ario [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} llave - guardar - guardari - guardardinero - tomardinero");

		if(LockerStatus[houseid] == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");

		if(!Container_Show(houseid, CONTAINER_TYPE_HOUSE, House[houseid][ContainerID], playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del armario. Reportar a un administador.");
		return 1;
	}
	
	if(strcmp(cmd, "llave", true) == 0)
	{
		if(House[houseid][TenantSQLID] == PlayerInfo[playerid][pID] || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			}
			else
			{
			    PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    LockerStatus[houseid] = 0;
			}
		}
		else if(House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID] || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			}
			else
			{
			    PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    LockerStatus[houseid] = 0;
			}
		}
		else
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este armario!");	
	}
	else if(strcmp(cmd, "tomardinero", true) == 0)
	{
 		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 200000)
            return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de $1 o mas de $200.000 por vez.");
		if(param1 > House[houseid][Money])
		   return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de dinero.");

        House[houseid][Money] -= param1;
        GivePlayerCash(playerid, param1);
        SaveHouse(houseid);
		PlayerActionMessage(playerid, 15.0, "toma algo de dinero del armario.");
	}
	else if(strcmp(cmd, "guardardinero", true) == 0)
	{
 		if(LockerStatus[houseid] == 0)
      		return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
		if(param1 < 1 || param1 > 200000)
 			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar menos de $1 o mas de $200.000 por vez.");
		if((House[houseid][Money] + param1) > 10000000)
   			return SendClientMessage(playerid, COLOR_YELLOW2, "¡El armario solo puede contener hasta $10.000.000!");
		if(GetPlayerCash(playerid) < param1)
 			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de dinero.");

		House[houseid][Money] += param1;
        GivePlayerCash(playerid, -param1);
        SaveHouse(houseid);
        PlayerActionMessage(playerid, 15.0, "guarda algo de dinero en el armario.");
	}
	else if(strcmp(cmd, "guardar", true) == 0)
	{
		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_TELEFONO_CELULAR)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el telefono.");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");

		new itemid = GetHandItem(playerid, HAND_RIGHT),
			itemparam = GetHandParam(playerid, HAND_RIGHT),
			str[128];

		if(itemid == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		if(!Container_AddItemAndParam(House[houseid][ContainerID], itemid, itemparam))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el armario / El ítem es demasiado chico para guardarse en un armario.");

		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico.
		
		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
		
		format(str, sizeof(str), "guarda un/a %s en el armario.", GetItemName(itemid));
		PlayerActionMessage(playerid, 15.0, str);

	}
	else if(strcmp(cmd, "guardari", true) == 0)
	{
		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(GetHandItem(playerid, HAND_LEFT) == ITEM_ID_TELEFONO_CELULAR)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el telefono.");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");

		new itemid = GetHandItem(playerid, HAND_LEFT),
			itemparam = GetHandParam(playerid, HAND_LEFT),
			str[128];

		if(itemid == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		if(!Container_AddItemAndParam(House[houseid][ContainerID], itemid, itemparam))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el armario / El ítem es demasiado chico para guardarse en un armario.");

		SetHandItemAndParam(playerid, HAND_LEFT, 0, 0); // Borrado lógico y grafico.

		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

		format(str, sizeof(str), "guarda un/a %s en el armario.", GetItemName(itemid));
		PlayerActionMessage(playerid, 15.0, str);
        }
		else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");
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
    		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la casa.");
		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(free_hand == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el item ya que tienes ambas manos ocupadas.");

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SetHandItemAndParam(playerid, free_hand, itemid, itemparam); // Creación lógica y grafica en la mano.

            SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

			format(str, sizeof(str), "toma un/a %s del armario.", GetItemName(itemid));
			PlayerActionMessage(playerid, 15.0, str);
		}
		else
		{
	        SendClientMessage(playerid, COLOR_YELLOW2, "Armario vacio o el slot es inválido.");
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