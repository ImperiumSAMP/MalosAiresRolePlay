#if defined _isamp_toys_included
	#endinput
#endif
#define _isamp_toys_included

//===============================TOYS SYSTEM====================================

//================================CONSTANTES====================================

#define MAX_PLAYER_INDEX    	8 // El limite es 10 y es nativo de samp. Se pone 8 (va de 0 a 7) para guardar un index para la mano y otro a la mascara, temporalmente.
#define SLOT_TYPE_TOY      		5

//===============================DATA STORAGE===================================

new ToysInfo[MAX_PLAYERS][MAX_PLAYER_INDEX][SlotInfo];

//======================CABECERA DE FUNCIONES PUBLICAS==========================

forward LoadToysInfo(playerid);
forward LoadToysItems(playerid);

//================================FUNCIONES=====================================

SearchToyFreeIndex(playerid)
{
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    if(ToysInfo[playerid][i][Item] == 0)
	        return i;
	}
	return -1;
}

SetToyItemAndParam(playerid, index, itemid, param)
{
	if(index >= 0 && index < MAX_PLAYER_INDEX)
	{
	    if(GetToyItem(playerid, index) > 0)
	    {
	        DeleteToyItem(playerid, index);
    	    ToysInfo[playerid][index][Item] = 0;
	    	ToysInfo[playerid][index][Amount] = 0;
	    	SaveSlotInfo(SLOT_TYPE_TOY, playerid, index);
		}
	    ToysInfo[playerid][index][Item] = itemid;
	    ToysInfo[playerid][index][Amount] = param;
	    SaveSlotInfo(SLOT_TYPE_TOY, playerid, index);
	    if(itemid != 0)
	    	LoadToyItem(playerid, index);
	}
}

GetToyItem(playerid, index)
{
	if(index >= 0 && index < MAX_PLAYER_INDEX)
	    return ToysInfo[playerid][index][Item];
	else
		return 0;
}

GetToyParam(playerid, index)
{
	if(index >= 0 && index < MAX_PLAYER_INDEX)
	    return ToysInfo[playerid][index][Amount];
	else
		return 0;
}

DeleteToyItem(playerid, index)
{
	RemovePlayerAttachedObject(playerid, index);
}

LoadToyItem(playerid, index)
{
	new itemid = ToysInfo[playerid][index][Item];
	
	if(GetItemObjectModel(itemid) != 0)
	{
		SetPlayerAttachedObject(playerid, index, GetItemObjectModel(itemid), GetItemAttachBone(itemid));
		EditAttachedObject(playerid, index);
	}
}

LoadToysItems(playerid)
{
	new itemid;
	
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    itemid = ToysInfo[playerid][i][Item];
		if(GetItemObjectModel(itemid) != 0)
			SetPlayerAttachedObject(playerid, i, GetItemObjectModel(itemid), GetItemAttachBone(itemid));
	}
}

ResetToys(playerid)
{
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    ToysInfo[playerid][i][Item] = 0;
	    ToysInfo[playerid][i][Amount] = 0;
	}
}

EditToy(playerid, index)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, index))
    	EditAttachedObject(playerid, index);
}

PrintToysForPlayer(playerid, targetid)
{
	SendClientMessage(targetid, COLOR_WHITE, "======================[Toys]=====================");
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    if(GetToyItem(playerid, i) > 0)
	        SendFMessage(targetid, COLOR_WHITE, " Index %d: %s", i, GetItemName(GetToyItem(playerid, i)));
	}
	SendClientMessage(targetid, COLOR_WHITE, "==================================================");
}

LoadToysInfo(playerid)
{
	new query[128];

	ResetToys(playerid); // Reseteamos la variable a cero y cargamos la nueva data (porque si no carga nada queda la data del anterior pj con misma id)
	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_TOY, PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_TOY, playerid);
	return 1;
}
	
//================================COMANDOS======================================

CMD:toy(playerid, params[])
{
	new cmd[32], index;

	if(sscanf(params, "s[32]I(-1)", cmd, index))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /toy [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} equipar - desequipar [index] - editar [index]");
		PrintToysForPlayer(playerid, playerid);
    } else {
        if(strcmp(cmd, "equipar", true) == 0) {
        
			new itemid = GetHandItem(playerid);
			
			if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
			if(itemid == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tu mano para equiparte.");
			if(GetItemType(itemid) != ITEM_TOY)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes equiparte ese item (No es del tipo TOY).");
			index = SearchToyFreeIndex(playerid);
			if(index == -1)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes mas espacio para equiparte objetos.");

			new str[128];
			format(str, sizeof(str), "se equipa un/a %s.", GetItemName(itemid));
			PlayerActionMessage(playerid, 15.0, str);
			SetToyItemAndParam(playerid, index, itemid, GetHandParam(playerid));
			SetHandItemAndParam(playerid, 0, 0);
			
		} else if(strcmp(cmd, "desequipar", true) == 0) {
		
		    new itemid = GetToyItem(playerid, index);
		    
			if(itemid == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Index inválido.");
   			if(GetHandItem(playerid) != 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo ya que tienes otro item en tu mano.");

			new str[128];
			format(str, sizeof(str), "se saca su/s %s.", GetItemName(itemid));
			PlayerActionMessage(playerid, 15.0, str);
			SetHandItemAndParam(playerid, itemid, GetToyParam(playerid, index));
			SetToyItemAndParam(playerid, index, 0, 0);

		} else if(strcmp(cmd, "editar", true) == 0) {

			if(GetToyItem(playerid, index) == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Index inválido.");

			EditToy(playerid, index);
		}
	}
	return 1;
}
