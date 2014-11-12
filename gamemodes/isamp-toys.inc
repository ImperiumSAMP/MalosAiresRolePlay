#if defined _isamp_toys_included
	#endinput
#endif
#define _isamp_toys_included

//===============================TOYS SYSTEM====================================

//================================CONSTANTES====================================

#define MAX_PLAYER_INDEX    	7 // El limite es 10 y es nativo de samp. Se pone 7 (va de 0 a 6) para guardar dos index para la mano izq - derecha y otro a la mascara, temporalmente.

#define TOY_CREATE             	1
#define TOY_UPDATE             	2
#define TOY_DESTROY            	3

//===============================DATA STORAGE===================================

enum toyInfo {
	Item,
	Amount,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:RotX,
	Float:RotY,
	Float:RotZ
}

new ToysInfo[MAX_PLAYERS][MAX_PLAYER_INDEX][toyInfo];

//======================CABECERA DE FUNCIONES PUBLICAS==========================

forward LoadToysInfo(playerid);
forward LoadToysItems(playerid);

forward OnToysInfoDataLoad(playerid);
forward SaveToyInfo(playerid, index, option);

forward OnPlayerEditToy(playerid, index, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ);

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
	    if(GetToyItem(playerid, index) > 0) // Ya tiene un item
	    {
	        DeleteToyItem(playerid, index);
	        if(itemid == 0) // Si quiere borrarlo
	        {
	        	ResetToy(playerid, index);
		    	SaveToyInfo(playerid, index, TOY_DESTROY);
			}
			else // Si quiere sobre-escribirlo
			{
		    	ToysInfo[playerid][index][Item] = itemid;
		    	ToysInfo[playerid][index][Amount] = param;
			    SaveToyInfo(playerid, index, TOY_UPDATE);
			    LoadToyItem(playerid, index);
			}
		} else
			if(itemid != 0) // Si no tiene un item y ademas quiere setear un item nuevo (crear uno)
	  		{
			   	ToysInfo[playerid][index][Item] = itemid;
			   	ToysInfo[playerid][index][Amount] = param;
			   	LoadToyItem(playerid, index);
		    	SaveToyInfo(playerid, index, TOY_CREATE);
			}
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
		SetPlayerAttachedObject(playerid, index, GetItemObjectModel(itemid), GetItemAttachBone(itemid), ToysInfo[playerid][index][PosX], ToysInfo[playerid][index][PosY], ToysInfo[playerid][index][PosZ], ToysInfo[playerid][index][RotX], ToysInfo[playerid][index][RotY], ToysInfo[playerid][index][RotZ]);
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
            SetPlayerAttachedObject(playerid, i, GetItemObjectModel(itemid), GetItemAttachBone(itemid), ToysInfo[playerid][i][PosX], ToysInfo[playerid][i][PosY], ToysInfo[playerid][i][PosZ], ToysInfo[playerid][i][RotX], ToysInfo[playerid][i][RotY], ToysInfo[playerid][i][RotZ]);
	}
}

ResetToy(playerid, index)
{
	ToysInfo[playerid][index][Item] = 0;
	ToysInfo[playerid][index][Amount] = 0;
	ToysInfo[playerid][index][PosX] = 0.0;
	ToysInfo[playerid][index][PosY] = 0.0;
	ToysInfo[playerid][index][PosZ] = 0.0;
	ToysInfo[playerid][index][RotX] = 0.0;
	ToysInfo[playerid][index][RotY] = 0.0;
	ToysInfo[playerid][index][RotZ] = 0.0;
}

ResetToys(playerid)
{
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    ResetToy(playerid, i);
	}
}

EditToy(playerid, index)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, index))
    	EditAttachedObject(playerid, index);
}

PrintToysForPlayer(playerid, targetid)
{
	SendClientMessage(targetid, COLOR_WHITE, "======================[Toys]========================");
	for(new i = 0; i < MAX_PLAYER_INDEX; i++)
	{
	    if(GetToyItem(playerid, i) > 0)
	        SendFMessage(targetid, COLOR_WHITE, " Index %d: %s", i, GetItemName(GetToyItem(playerid, i)));
	}
	SendClientMessage(targetid, COLOR_WHITE, "==================================================");
}

public OnPlayerEditToy(playerid, index, Float:posX, Float:posY, Float:posZ, Float:rotX, Float:rotY, Float:rotZ)
{
	if(index >= 0 && index < MAX_PLAYER_INDEX) // Automaticamente limita la edicion a los index reservados para toys.
	{
	    ToysInfo[playerid][index][PosX] = posX;
	    ToysInfo[playerid][index][PosY] = posY;
	    ToysInfo[playerid][index][PosZ] = posZ;
	    ToysInfo[playerid][index][RotX] = rotX;
	    ToysInfo[playerid][index][RotY] = rotY;
	    ToysInfo[playerid][index][RotZ] = rotZ;
	    SaveToyInfo(playerid, index, TOY_UPDATE);
	}
}

LoadToysInfo(playerid)
{
	new query[128];

	ResetToys(playerid); // Reseteamos la variable a cero y cargamos la nueva data (porque si no carga nada queda la data del anterior pj con misma id)
	format(query, sizeof(query), "SELECT * FROM `toys_info` WHERE `pId`= %d", PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnToysInfoDataLoad", "i", playerid);
	return 1;
}

public OnToysInfoDataLoad(playerid)
{
   	new result[128],
	   	rows,
	   	fields,
	   	aux = 0, // Desde el primer registro obtenido que se almacena en posicion cero dentro de los resultados
	   	index;

	cache_get_data(rows, fields);
	
	if(rows)
	{
	    while(aux < rows)
	    {
			cache_get_field_content(aux, "Index", result); 		index = strval(result);
			cache_get_field_content(aux, "Item", result); 		ToysInfo[playerid][index][Item] = strval(result);
			cache_get_field_content(aux, "Amount", result); 	ToysInfo[playerid][index][Amount] = strval(result);
			cache_get_field_content(aux, "PosX", result); 		ToysInfo[playerid][index][PosX] = floatstr(result);
			cache_get_field_content(aux, "PosY", result);		ToysInfo[playerid][index][PosY] = floatstr(result);
			cache_get_field_content(aux, "PosZ", result); 		ToysInfo[playerid][index][PosZ] = floatstr(result);
			cache_get_field_content(aux, "RotX", result); 		ToysInfo[playerid][index][RotX] = floatstr(result);
			cache_get_field_content(aux, "RotY", result); 		ToysInfo[playerid][index][RotY] = floatstr(result);
			cache_get_field_content(aux, "RotZ", result); 		ToysInfo[playerid][index][RotZ] = floatstr(result);
			aux ++;
		}
	}
	return 1;
}

public SaveToyInfo(playerid, index, option)
{
	new query[256];
	
	if(dontsave)
	    return 1;

	if(option == TOY_CREATE)
	{
		if(ToysInfo[playerid][index][Item] > 0)
		{
			format(query, sizeof(query), "INSERT INTO `toys_info` (pId, Index, Item, Amount, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES (%d, %d, %d, %d, %f, %f, %f, %f, %f, %f)",
				PlayerInfo[playerid][pID],
				index,
				ToysInfo[playerid][index][Item],
				ToysInfo[playerid][index][Amount],
				ToysInfo[playerid][index][PosX],
				ToysInfo[playerid][index][PosY],
				ToysInfo[playerid][index][PosZ],
				ToysInfo[playerid][index][RotX],
				ToysInfo[playerid][index][RotY],
				ToysInfo[playerid][index][RotZ]
			);
		}
	}
	else if(option == TOY_UPDATE)
	{
		if(ToysInfo[playerid][index][Item] > 0)
		{
			format(query, sizeof(query), "UPDATE `toys_info` SET `Item`=%d, `Amount`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f WHERE `pId`=%d AND `Index`=%d",
	            ToysInfo[playerid][index][Item],
	            ToysInfo[playerid][index][Amount],
				ToysInfo[playerid][index][PosX],
				ToysInfo[playerid][index][PosY],
				ToysInfo[playerid][index][PosZ],
				ToysInfo[playerid][index][RotX],
				ToysInfo[playerid][index][RotY],
				ToysInfo[playerid][index][RotZ],
				PlayerInfo[playerid][pID],
				index
			);
		}
	}
	else if(option == TOY_DESTROY)
	{
		format(query, sizeof(query), "DELETE FROM `toys_info` WHERE `pId`=%d AND `Index`=%d",
			PlayerInfo[playerid][pID],
			index
		);
	}
	
	mysql_function_query(dbHandle, query, false, "", "");
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
