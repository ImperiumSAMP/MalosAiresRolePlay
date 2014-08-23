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

forward getItemType(itemid);
forward getLockerItem(lockerid, lockerslot);
forward getLockerParam(lockerid, lockerslot);
forward setLockerItemAndParam(lockerid, lockerslot, itemid, param);
forward resetLocker(lockerid);
forward GetHouseMaxLockerSlots(houseid);

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock getLockerItem(lockerid, lockerslot)
{
	new itemid = -1;

	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
		itemid = LockerInfo[lockerid][lockerslot][Item];
	return itemid;
}

stock getLockerParam(lockerid, lockerslot)
{
	new param = -1;

	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
		param = LockerInfo[lockerid][lockerslot][Amount];
	return param;
}

stock setLockerItemAndParam(lockerid, lockerslot, itemid, param)
{
	if(lockerslot >= 0 && lockerslot < MAX_LOCKER_SLOTS)
	{
	    if(getLockerItem(lockerid, lockerslot) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	    {
			LockerInfo[lockerid][lockerslot][Item] = 0;
			LockerInfo[lockerid][lockerslot][Amount] = 0;
			SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, lockerslot); // Borramos el anterior
		}
		LockerInfo[lockerid][lockerslot][Item] = itemid;
		LockerInfo[lockerid][lockerslot][Amount] = param;
		SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, lockerslot);
	}
	return 1;
}

stock resetLocker(lockerid)
{
	for(new i = 0; i < MAX_LOCKER_SLOTS; i++)
	{
	    if(LockerInfo[lockerid][i][Item] > 0)
	    {
	    	LockerInfo[lockerid][i][Item] = 0;
		    LockerInfo[lockerid][i][Amount] = 0;
		    SaveSlotInfo(SLOT_TYPE_LOCKER, lockerid, i);
		} else
		    {
	    		LockerInfo[lockerid][i][Item] = 0;
		    	LockerInfo[lockerid][i][Amount] = 0;
			}
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

CMD:arm(playerid, params[])
{
 	cmd_armario(playerid, params);
	return 1;
}

CMD:armario(playerid, params[])
{
	new text[128], param1, param2[32], itemid, paramcant, houseid = GetPlayerHouse(playerid);

	if(houseid == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar dentro de una casa!");

	if(sscanf(params, "s[128]I(-1)S(-1)[32]", text, param1, param2))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/arm)ario [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar (para abrirlo o cerrarlo) - tomar [slot de item] - guardar [slot, opcional] - tomardinero [cantidad]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} guardardinero [cantidad] - tomardroga [cantidad] [tipo de droga] - guardardroga [cantidad] [tipo de droga]");

		if(LockerStatus[houseid] == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");

        SendClientMessage(playerid, COLOR_WHITE, "=======================[Armario]=======================");
		for(new i = 0; i < GetHouseMaxLockerSlots(houseid); i++) {
            itemid = getLockerItem(houseid, i);
            paramcant = getLockerParam(houseid, i);
            if(getItemType(itemid) == ITEM_WEAPON)
				SendFMessage(playerid, COLOR_WHITE, " - %d- Arma: %s - Munición: %d", i, itemName[itemid], paramcant);
			else
				if(getItemType(itemid) == ITEM_OTHER)
					SendFMessage(playerid, COLOR_WHITE, " - %d- Item: %s - Cantidad: %d", i, itemName[itemid], paramcant);
			 	else
				 	SendFMessage(playerid, COLOR_WHITE, " - %d- Nada", i);
        }
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
		    SendFMessage(playerid, COLOR_WHITE, " - Extasis: %d dosis.", House[houseid][Ecstasy]);
		}
		if(House[houseid][Cocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Cocaína: %d gramos.", House[houseid][Cocaine]);
		}
        SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
		return 1;

	}
	if(strcmp(text, "usar", true) == 0) {

	    if(houseid != PlayerInfo[playerid][pHouseKey] && !AdminDuty[playerid])
	        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este armario!");

		if(LockerStatus[houseid] != 1)
		{
		    PlayerActionMessage(playerid, 15.0, "abre con su llave las puertas del armario.");
		    LockerStatus[houseid] = 1;
		} else
			{
		    	PlayerActionMessage(playerid, 15.0, "cierra las puertas del armario con su llave.");
		    	LockerStatus[houseid] = 0;
			}

	} else if(strcmp(text, "tomardinero", true) == 0) {

 		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 200000)
            return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de $1 o mas de $200.000 por vez.");
		if(param1 > House[houseid][Money])
		   return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de dinero.");

        House[houseid][Money] -= param1;
        GivePlayerCash(playerid, param1);
        saveHouse(houseid);
		PlayerActionMessage(playerid, 15.0, "toma algo de dinero del armario.");

	} else if(strcmp(text, "guardardinero", true) == 0) {

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
        saveHouse(houseid);
        PlayerActionMessage(playerid, 15.0, "guarda algo de dinero en el armario.");

	} else if(strcmp(text, "tomar", true) == 0) {

 		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
   		if(getItemType(getLockerItem(houseid, param1)) != ITEM_WEAPON)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");

   		GivePlayerWeapon(playerid, getLockerItem(houseid, param1), getLockerParam(houseid, param1));
   		setLockerItemAndParam(houseid, param1, 0 ,0);

	} else if(strcmp(text, "guardar", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
 		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
        if(PlayerInfo[playerid][pLevel] < 3)
            return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
		if((PlayerInfo[playerid][pFaction] == FAC_PMA && CopDuty[playerid]) || (PlayerInfo[playerid][pFaction] == FAC_SIDE && SIDEDuty[playerid]))
    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacer esto en servicio!");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
		if(GetPlayerWeapon(playerid) < 1 || (GetPlayerWeapon(playerid) > 34 && GetPlayerWeapon(playerid) != 43))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
		if(param1 == -1) // Si no eligió donde guardarlo
		{
			for(new i = 0; i < GetHouseMaxLockerSlots(houseid); i++) {
			    if(getItemType(getLockerItem(houseid, i)) == ITEM_NONE) {
			        param1 = i; // Encontramos un slot libre
			        break;
				}
			}
			if(param1 == -1)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡El armario se encuentra lleno!");
		} else // Si nos dijo donde guardarlo
			{
			    if(param1 < 0 || param1 >= GetHouseMaxLockerSlots(houseid))
			        return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido.");
				if(getItemType(getLockerItem(houseid, param1)) != ITEM_NONE)
				    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un item en ese slot.");
			}

     	SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 4000, false, "i", playerid);
		setLockerItemAndParam(houseid, param1, GetPlayerWeapon(playerid), GetPlayerAmmo(playerid));
		RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));

	} else if(strcmp(text, "tomardroga", true) == 0) {

		if(LockerStatus[houseid] == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El armario se encuentra cerrado con llave.");
		if(param1 < 1 || param1 > 10000)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar menos de 1 o mas de 10.000.");

		if(strcmp(param2, "marihuana", true) == 0) {
		    if(param1 > House[houseid][Marijuana])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Marijuana] -= param1;
            PlayerInfo[playerid][pMarijuana] += param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {
  			if(param1 > House[houseid][LSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][LSD] -= param1;
            PlayerInfo[playerid][pLSD] += param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > House[houseid][Cocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Cocaine] -= param1;
            PlayerInfo[playerid][pCocaine] += param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > House[houseid][Ecstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No hay esa cantidad de droga.");

            House[houseid][Ecstasy] -= param1;
            PlayerInfo[playerid][pEcstasy] += param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete desconocido del armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");

	} else if(strcmp(text, "guardardroga", true) == 0) {

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
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "LSD", true) == 0) {

  			if(param1 > PlayerInfo[playerid][pLSD])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][LSD] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][LSD] += param1;
            PlayerInfo[playerid][pLSD] -= param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "cocaina", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pCocaine])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Cocaine] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Cocaine] += param1;
            PlayerInfo[playerid][pCocaine] -= param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

		} else if(strcmp(param2, "extasis", true) == 0) {

		    if(param1 > PlayerInfo[playerid][pEcstasy])
		        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de droga.");
		    if((House[houseid][Ecstasy] + param1) > 10000)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes almacenar hasta 10.000 en el armario.");

            House[houseid][Ecstasy] += param1;
            PlayerInfo[playerid][pEcstasy] -= param1;
            saveHouse(houseid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete desconocido en el armario.");

        } else
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingrese un típo de droga válido.");
	}
	return 1;
}

