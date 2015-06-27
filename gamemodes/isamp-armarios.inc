#if defined _isamp_armarios_included
	#endinput
#endif
#define _isamp_armarios_included

//===========================ARMARIOS PARA LAS CASAS============================

//================================CONSTANTES====================================

#define SLOT_TYPE_LOCKER        1
#define MAX_LOCKER_SLOTS 		22

//============================VARIABLES INTERNAS================================

new LockerInfo[MAX_HOUSES][MAX_LOCKER_SLOTS][SlotInfo];
new LockerStatus[MAX_HOUSES];

//===============================FUNCIONES======================================

forward GetLockerItem(lockerid, lockerslot); // Devuelve el nro de item del slot indicado del armario de la casa. En caso de error retorna -1.
forward GetLockerParam(lockerid, lockerslot); // Devuelve el parametro "cantidad" del slot indicado del armario de la casa. En caso de error retorna -1.
forward SetLockerItemAndParam(lockerid, lockerslot, itemid, param); // Setea item y cantidad en el slot indicado. Guardado instantaneo en la DB.
forward ResetLocker(lockerid); // Borra todo slot del armario de la casa y lo resetea a cero.
forward GetHouseMaxLockerSlots(houseid); // Devuelve el nro de slots que tiene una casa X (se basa en su precio).
forward SearchLockerForItem(lockerid, itemid); // Busca un item pasado por parametro dentro de un armario. Si existe, devuelve el slot en el que está, sino retorna -1.
forward SearchLockerFreeSlot(lockerid); // Busca por el primer slot vacio en el armario y devuelve su posicion. De no haber espacio retorna -1.
forward PrintLockerForPlayer(lockerid, targetid);// Imprime el armario de la casa al jugador indicado.

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock GetLockerItem(lockerid, lockerslot)
{
	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
		return LockerInfo[lockerid][lockerslot][Item];
	else
		return -1;
}

stock GetLockerParam(lockerid, lockerslot)
{
	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
		return LockerInfo[lockerid][lockerslot][Amount];
	else
		return -1;
}

stock SetLockerItemAndParam(lockerid, lockerslot, itemid, param)
{
	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
	{
	    if(GetLockerItem(lockerid, lockerslot) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	    {
			LockerInfo[lockerid][lockerslot][Item] = 0;
			LockerInfo[lockerid][lockerslot][Amount] = 0;
			SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, lockerslot); // Borramos el anterior
		}
		if(itemid != 0)
		{
			LockerInfo[lockerid][lockerslot][Item] = itemid;
			LockerInfo[lockerid][lockerslot][Amount] = param;
			SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, lockerslot);
		}
	}
	return 1;
}

stock ResetLocker(lockerid)
{
	for(new i = 0; i < MAX_LOCKER_SLOTS; i++)
	{
	    if(LockerInfo[lockerid][i][Item] > 0)
	    {
   			LockerInfo[lockerid][i][Item] = 0;
			LockerInfo[lockerid][i][Amount] = 0;
		    SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, i);
		}
	}
	return 1;
}

stock SearchLockerForItem(lockerid, itemid)
{
	for(new i = 0; i < MAX_LOCKER_SLOTS; i++)
	{
		if(LockerInfo[lockerid][i][Item] == itemid)
		    return i;
	}
	return -1;
}

stock SearchLockerFreeSlot(lockerid)
{
	new houseslots = GetHouseMaxLockerSlots(lockerid);
	
    for(new i = 0; i < houseslots; i++)
    {
        if(LockerInfo[lockerid][i][Item] == 0)
            return i;
	}
	return -1;
}

stock PrintLockerForPlayer(lockerid, targetid)
{
	new itemid, houseslots = GetHouseMaxLockerSlots(lockerid);

 	SendClientMessage(targetid, COLOR_WHITE, "=======================[Armario]=======================");
	for(new i = 0; i < houseslots; i++)
	{
		itemid = GetLockerItem(lockerid, i);
	    if(itemid > 0)
			SendFMessage(targetid, COLOR_WHITE, " - %d- Item: %s - %s: %d", i, GetItemName(itemid), GetItemParamName(itemid), GetLockerParam(lockerid, i));
	    else
	        SendFMessage(targetid, COLOR_WHITE, " - %d- Vacío", i);
	}
	return 1;
}

GetHouseMaxLockerSlots(houseid)
{
	if(houseid == 0) return 0;
	new hprice = House[houseid][HousePrice];
	if(hprice < 100000) return 8;
	if(hprice < 200000) return 10;
	if(hprice < 300000) return 12;
	if(hprice < 400000) return 14;
	if(hprice < 500000) return 16;
	if(hprice < 600000) return 17;
	if(hprice < 700000) return 18;
	if(hprice < 800000) return 19;
	if(hprice < 900000) return 20;
	if(hprice < 1000000) return 21;
	if(hprice >= 1000000) return 22;
	return 0;
}

//=================================COMANDOS=====================================

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
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar (para abrirlo o cerrarlo) - tomar/tomari [slot de item] - guardar/guardari [slot (opcional)]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomardinero [cant] - guardardinero [cant] - tomardroga [cant] [tipo] - guardardroga [cant] [tipo]");

		if(LockerStatus[houseid] == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");

        PrintLockerForPlayer(houseid, playerid);
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
		    SendFMessage(playerid, COLOR_WHITE, " - Éxtasis: %d dosis.", House[houseid][Ecstasy]);
		}
		if(House[houseid][Cocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Cocaína: %d gramos.", House[houseid][Cocaine]);
		}
        SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
		return 1;

	}
	if(strcmp(cmd, "usar", true) == 0) {

		if((House[houseid][Income] == 1 && House[houseid][Tenant] == PlayerInfo[playerid][pName]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    	LockerStatus[houseid] = 0;
				}
		}
		else if((House[houseid][Income] == 0 && House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    	LockerStatus[houseid] = 0;
				}
		} else
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este armario!");
			
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
		PlayerActionMessage(playerid, 15.0, "toma algo de dinero del armario.");

	} else if(strcmp(cmd, "guardardinero", true) == 0) {

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

	} else if(strcmp(cmd, "tomar", true) == 0) {

        TakeItemFromLocker(playerid, HAND_RIGHT, houseid, param1);

	} else if(strcmp(cmd, "tomari", true) == 0) {

		TakeItemFromLocker(playerid, HAND_LEFT, houseid, param1);

	} else if(strcmp(cmd, "guardar", true) == 0) {

		SaveItemOnLocker(playerid, HAND_RIGHT, houseid, param1);

	} else if(strcmp(cmd, "guardari", true) == 0) {

		SaveItemOnLocker(playerid, HAND_LEFT, houseid, param1);

	} else if(strcmp(cmd, "tomardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de 1 o mas de 10.000.");

		if(strcmp(param2, "marihuana", true) == 0) {
		    if(param1 > House[houseid][Marijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Marijuana] -= param1;
            PlayerInfo[playerid][pMarijuana] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {
  			if(param1 > House[houseid][LSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][LSD] -= param1;
            PlayerInfo[playerid][pLSD] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > House[houseid][Cocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Cocaine] -= param1;
            PlayerInfo[playerid][pCocaine] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > House[houseid][Ecstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Ecstasy] -= param1;
            PlayerInfo[playerid][pEcstasy] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");

	} else if(strcmp(cmd, "guardardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar menos de 1 o mas de 10.000.");

		if(strcmp(param2, "marihuana", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pMarijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Marijuana] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Marijuana] += param1;
            PlayerInfo[playerid][pMarijuana] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {

  			if(param1 > PlayerInfo[playerid][pLSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][LSD] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][LSD] += param1;
            PlayerInfo[playerid][pLSD] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pCocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Cocaine] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Cocaine] += param1;
            PlayerInfo[playerid][pCocaine] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pEcstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Ecstasy] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Ecstasy] += param1;
            PlayerInfo[playerid][pEcstasy] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");
	}
	return 1;
}

stock TakeItemFromLocker(playerid, playerhand, houseid, lockerslot)
{
	if(LockerStatus[houseid] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
 	if(PlayerInfo[playerid][pHealth] < 25)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");

	new itemid = GetLockerItem(houseid, lockerslot),
		itemparam = GetLockerParam(houseid, lockerslot),
		str[128];

	if(itemid <= 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
	if(GetHandItem(playerid, playerhand) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano ocupada.");
	    
	SetHandItemAndParam(playerid, playerhand, itemid, itemparam);
	SetLockerItemAndParam(houseid, lockerslot, 0 ,0);
   	format(str, sizeof(str), "toma un/a %s del armario.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	return 1;
}

stock SaveItemOnLocker(playerid, playerhand, houseid, lockerslot)
{
	if(LockerStatus[houseid] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
 	if(PlayerInfo[playerid][pHealth] < 25)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
	if(GetHandItem(playerid, playerhand) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
	if(GetPVarInt(playerid, "GrupoPaintball") != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
	if(GetHandItem(playerid, playerhand) == ITEM_ID_TELEFONO_CELULAR)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el telefono.");
	if(GetPVarInt(playerid, "cantSaveItems") == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");

	new itemid = GetHandItem(playerid, playerhand),
		validslot,
		str[128];

	if(itemid == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		
	if(lockerslot == -1) // Si no eligió donde guardarlo
	{
		validslot = SearchLockerFreeSlot(houseid);
		if(validslot == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡El armario se encuentra lleno!");
	} else // Si nos dijo donde guardarlo
		{
		    validslot = lockerslot;
		    if(validslot < 0 || validslot >= GetHouseMaxLockerSlots(houseid))
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido.");
			if(GetLockerItem(houseid, validslot) != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un item en ese slot.");
		}

	SetLockerItemAndParam(houseid, validslot, itemid, GetHandParam(playerid, playerhand));
	SetHandItemAndParam(playerid, playerhand, 0, 0);
	format(str, sizeof(str), "guarda un/a %s en el armario.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	SetPVarInt(playerid, "cantSaveItems", 1);
	SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	return 1;
}

//============================[EXPERIMENTAL]====================================


CMD:arm2(playerid, params[])
{
 	cmd_armario2(playerid, params);
	return 1;
}

CMD:armario2(playerid, params[])
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
		    SendFMessage(playerid, COLOR_WHITE, " - Éxtasis: %d dosis.", House[houseid][Ecstasy]);
		}
		if(House[houseid][Cocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Cocaína: %d gramos.", House[houseid][Cocaine]);
		}
        SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
		return 1;

	}
	if(strcmp(cmd, "usar", true) == 0) {

		if((House[houseid][Income] == 1 && House[houseid][Tenant] == PlayerInfo[playerid][pName]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    	LockerStatus[houseid] = 0;
				}
		}
		else if((House[houseid][Income] == 0 && House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
		{
		    if(LockerStatus[houseid] != 1)
			{
			    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
			    LockerStatus[houseid] = 1;
			} else
				{
			    	PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
			    	LockerStatus[houseid] = 0;
				}
		} else
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este armario!");

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
		PlayerActionMessage(playerid, 15.0, "toma algo de dinero del armario.");

	} else if(strcmp(cmd, "guardardinero", true) == 0) {

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

	} else if(strcmp(cmd, "guardar", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
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

	} else if(strcmp(cmd, "tomardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de 1 o mas de 10.000.");

		if(strcmp(param2, "marihuana", true) == 0) {
		    if(param1 > House[houseid][Marijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Marijuana] -= param1;
            PlayerInfo[playerid][pMarijuana] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {
  			if(param1 > House[houseid][LSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][LSD] -= param1;
            PlayerInfo[playerid][pLSD] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > House[houseid][Cocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Cocaine] -= param1;
            PlayerInfo[playerid][pCocaine] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > House[houseid][Ecstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Ecstasy] -= param1;
            PlayerInfo[playerid][pEcstasy] += param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");

	} else if(strcmp(cmd, "guardardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar menos de 1 o mas de 10.000.");

		if(strcmp(param2, "marihuana", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pMarijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Marijuana] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Marijuana] += param1;
            PlayerInfo[playerid][pMarijuana] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {

  			if(param1 > PlayerInfo[playerid][pLSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][LSD] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][LSD] += param1;
            PlayerInfo[playerid][pLSD] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pCocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Cocaine] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Cocaine] += param1;
            PlayerInfo[playerid][pCocaine] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pEcstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Ecstasy] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Ecstasy] += param1;
            PlayerInfo[playerid][pEcstasy] -= param1;
            SaveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");
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
            str[128];

		if(GetPlayerHouse(playerid) != houseid)
    		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la casa.");
		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	 	if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(GetHandItem(playerid, HAND_RIGHT) != 0)
    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano ocupada.");

		SendFMessage(playerid, COLOR_WHITE, "Vector ID %d e id original es %d, en slot %d", container_id, houseid, listitem);

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SendFMessage(playerid, COLOR_WHITE, "Seleccionado del slot %d, el item %d con parametro %d", listitem, itemid, itemparam);

			SetHandItemAndParam(playerid, HAND_RIGHT, itemid, itemparam); // Creación lógica y grafica en la mano.

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

//==============================[FIN EXPERIMENTAL]==============================
