#if defined _isamp_inventory_included
	#endinput
#endif
#define _isamp_inventory_included

//=====================SISTEMA DE INVENTARIO DE JUGADORES=======================

//================================CONSTANTES====================================

#define INV_MAX_SLOTS           2
#define SLOT_TYPE_INV      		3

//============================VARIABLES INTERNAS================================

enum SlotInfo {
	Item,
	Amount,
};

new InvInfo[MAX_PLAYERS][INV_MAX_SLOTS][SlotInfo];

//===============================FUNCIONES======================================

forward GetInvItem(playerid, invslot); // Devuelve el nro de item del slot indicado del inventario del jugador. En caso de error retorna -1.
forward GetInvParam(playerid, invslot); // Devuelve el parametro "cantidad" del slot indicado del inventario del jugador. En caso de error retorna -1.
forward SetInvItemAndParam(playerid, invslot, itemid, param); // Setea item y cantidad en el slot indicado. Guardado instantaneo en la DB.
forward ResetInv(playerid); // Borra todo slot del inventario del jugador y lo resetea a cero.
forward SearchInvForItem(playerid, itemid); // Busca un item pasado por parametro dentro de un inventario. Si existe, devuelve el slot en el que está, sino retorna -1.
forward PrintInvForPlayer(playerid, targetid); // Imprime el inventario del jugador X al jugador Y.
forward SearchInvFreeSlot(playerid); // Busca por el primer slot vacio en el inventario y devuelve su posicion. De no haber espacio retorna -1.
forward LoadInvInfo(playerid); // Carga desde la base de datos al GM en ejecución el inventario del jugador indicado.

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock GetInvItem(playerid, invslot)
{
	if(invslot >= 0 && invslot < INV_MAX_SLOTS)
		return InvInfo[playerid][invslot][Item];
	else
	    return -1;
}

stock GetInvParam(playerid, invslot)
{
	if(invslot >= 0 && invslot < INV_MAX_SLOTS)
		return InvInfo[playerid][invslot][Amount];
	else
		return -1;
}

stock SetInvItemAndParam(playerid, invslot, itemid, param)
{
	if(invslot >= 0 && invslot < INV_MAX_SLOTS)
	{
	    if(GetInvItem(playerid, invslot) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	    {
			InvInfo[playerid][invslot][Item] = 0;
			InvInfo[playerid][invslot][Amount] = 0;
			SaveSlotInfo(SLOT_TYPE_INV, playerid, invslot); // Borramos el anterior
		}
		InvInfo[playerid][invslot][Item] = itemid;
		InvInfo[playerid][invslot][Amount] = param;
		SaveSlotInfo(SLOT_TYPE_INV, playerid, invslot);
	}
	return 1;
}

stock ResetInv(playerid)
{
	for(new i = 0; i < INV_MAX_SLOTS; i++)
	{
		InvInfo[playerid][i][Item] = 0;
		InvInfo[playerid][i][Amount] = 0;
	    if(InvInfo[playerid][i][Item] > 0)
   			SaveSlotInfo(SLOT_TYPE_INV, playerid, i);
	}
	return 1;
}

stock SearchInvFreeSlot(playerid)
{
    for(new i = 0; i < INV_MAX_SLOTS; i++)
    {
        if(InvInfo[playerid][i][Item] == 0)
            return i;
	}
	return -1;
}

stock SearchInvForItem(playerid, itemid)
{
	for(new i = 0; i < INV_MAX_SLOTS; i++)
	{
		if(InvInfo[playerid][i][Item] == itemid)
		    return i;
	}
	return -1;
}

stock PrintInvForPlayer(playerid, targetid)
{
	new
	    itemid;

 	SendClientMessage(targetid, COLOR_WHITE, "======================[Inventario]======================");
	for(new i = 0; i < INV_MAX_SLOTS; i++)
	{
		itemid = GetInvItem(playerid, i);
	    if(itemid > 0)
			SendFMessage(targetid, COLOR_WHITE, " - %d- Item: %s - %s: %d", i, GetItemName(itemid), GetItemParamName(itemid), GetInvParam(playerid, i));
	    else
	        SendFMessage(targetid, COLOR_WHITE, " - %d- Vacio", i);
	}
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

stock LoadInvInfo(playerid)
{
	new
		query[128];

	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_INV, PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_INV, playerid);
	return 1;
}

//================================COMANDOS======================================

CMD:inv(playerid, params[]) {
	cmd_inventario(playerid, params);
	return 1;
}

CMD:inventario(playerid, params[]) {
	new
	    returnid,
	    text[128];

    if(sscanf(params, "s[128]I(-1)", text, returnid)) {
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/inv)entario [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomar [slot] - guardar [slot, opcional] - desechar - consumir [slot]");
		PrintInvForPlayer(playerid, playerid);
    } else {
		if(strcmp(text, "tomar", true) == 0) {

	        if(GetItemType(GetInvItem(playerid, returnid)) == ITEM_WEAPON) {
	            GivePlayerWeapon(playerid, GetInvItem(playerid, returnid), GetInvParam(playerid, returnid));
	            SetInvItemAndParam(playerid, returnid, 0, 0);
			} else
	            SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");

	    } else if(strcmp(text, "desechar", true) == 0) {

	        if(PlayerInfo[playerid][pHealth] < 25.0)
	            return SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡No puedes desechar un item agonizando!");
	        if(GetInvItem(playerid, returnid) == 0) {
	        	new string[128];
      			format(string, sizeof(string), "ha desechado disimuladamente un/a %s.", GetItemName(GetInvItem(playerid, returnid)));
         		PlayerActionMessage(playerid, 8.0, string);
				SetInvItemAndParam(playerid, returnid, 0, 0);
	        } else
	            SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");

 		} else if(strcmp(text, "consumir", true) == 0) {

			if(GetInvItem(playerid, returnid) == 52) {
	            PlayerActionMessage(playerid, 15.0, "saca un sandwich de su bolsillo y se lo come.");
	            PlayerEat(playerid, 40.0);
	            if(GetInvParam(playerid, returnid) - 1 > 0)
	            	SetInvItemAndParam(playerid, returnid, 52, GetInvParam(playerid, returnid) - 1);
				else
					SetInvItemAndParam(playerid, returnid, 0, 0);
	        } else
				if(GetInvItem(playerid, returnid) == 53) {
		            PlayerActionMessage(playerid, 15.0, "saca un alfajor de su bolsillo y se lo come.");
		            PlayerEat(playerid, 15.0);
		            if(GetInvParam(playerid, returnid) - 1 > 0)
		            	SetInvItemAndParam(playerid, returnid, 53, GetInvParam(playerid, returnid) - 1);
					else
						SetInvItemAndParam(playerid, returnid, 0, 0);
				} else
					if(GetInvItem(playerid, returnid) == 54) {
			            PlayerActionMessage(playerid, 15.0, "saca una botellita de agua de su bolsillo y se la toma.");
			            PlayerDrink(playerid, 50.0);
			            if(GetInvParam(playerid, returnid) - 1 > 0)
			            	SetInvItemAndParam(playerid, returnid, 54, GetInvParam(playerid, returnid) - 1);
						else
							SetInvItemAndParam(playerid, returnid, 0, 0);
					} else
  						SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");

	    } else if(strcmp(text, "guardar", true) == 0) {

	        if(PlayerInfo[playerid][pHealth] < 25.0)
	            return SendClientMessage(playerid, COLOR_LIGHTBLUE, "No puedes guardar un arma agonizando");
			if(GetPVarInt(playerid, "cantSaveItems") == 1)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
			if(isPlayerCopOnDuty(playerid) || isPlayerSideOnDuty(playerid))
    			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacer esto en servicio!");
			new weaponID = GetPlayerWeapon(playerid);
   			if(!HasItemInvPermission(weaponID))
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");

			new validslot;
			if(returnid == -1)
			{
			    validslot = SearchInvFreeSlot(playerid);
				if(validslot == -1)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "¡El inventario se encuentra lleno!");
       		} else
			   {
			        validslot = returnid;
			   		if(validslot < 0 || validslot >= INV_MAX_SLOTS)
					   	return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido.");
		        	if(GetInvItem(playerid, validslot) == 0)
		        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un item en ese slot.");
				}

    		SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 4000, false, "i", playerid);
			SetInvItemAndParam(playerid, validslot, GetPlayerWeapon(playerid), GetPlayerAmmo(playerid));
			RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));
	    }
	}
	return 1;
}
