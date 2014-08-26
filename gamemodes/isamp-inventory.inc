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
forward SetInvItemAndParam(playerid, invslot, itemid, param); // Setea item y cantidad en el slot indicado.
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

	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_INV, playerid);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_INV, playerid);
	return 1;
}

