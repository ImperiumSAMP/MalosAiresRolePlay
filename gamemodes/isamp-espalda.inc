#if defined _isamp_espalda_included
	#endinput
#endif
#define _isamp_espalda_included

//===========================MODELADO DE ESPALDA================================

//================================CONSTANTES====================================

#define SLOT_TYPE_BACK          5

//============================VARIABLES INTERNAS================================

new BackInfo[MAX_PLAYERS][SlotInfo];

//===============================FUNCIONES======================================

forward OnBackDataLoad(playerid);

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

static const BackWeapons[] =
{
	WEAPON_KATANA, WEAPON_SHOTGUN,
	WEAPON_MP5, WEAPON_AK47, WEAPON_M4,
	WEAPON_RIFLE, WEAPON_SNIPER
};

stock bool:HasBackPermission(itemid)
{
	for(new i = 0; i < sizeof(BackWeapons); i++)
	{
	    if(itemid == BackWeapons[i])
	        return true;
	}
	return false;
}

stock GetBackItem(playerid)
{
	return BackInfo[playerid][Item];
}

stock GetBackParam(playerid)
{
	return BackInfo[playerid][Amount];
}

stock ResetBackInfo(playerid)
{
	BackInfo[playerid][Item] = 0;
	BackInfo[playerid][Amount] = 0;
}

stock SetBackItemAndParam(playerid, itemid, param)
{
	new query[128];
	if(BackInfo[playerid][Item] > 0)
	{
	    DetachBackItem(playerid);
	    if(itemid == 0)
		{
			ResetBackInfo(playerid);
			format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `Type`=%d AND `Id`=%d", SLOT_TYPE_BACK, PlayerInfo[playerid][pID]);
	        mysql_function_query(dbHandle, query, false, "", "");
		}
		else
		{
			BackInfo[playerid][Item] = itemid;
			BackInfo[playerid][Amount] = param;
			format(query, sizeof(query), "UPDATE `slots_info` SET `Item`=%d, `Amount`=%d WHERE `Type`=%d AND `Id`=%d", itemid, param, SLOT_TYPE_BACK, PlayerInfo[playerid][pID]);
            mysql_function_query(dbHandle, query, false, "", "");
			AttachBackItem(playerid);
		}
	}
	else if(itemid > 0)
	{
		BackInfo[playerid][Item] = itemid;
		BackInfo[playerid][Amount] = param;
		format(query, sizeof(query), "INSERT INTO `slots_info` (`Type`, `Id`, `Item`, `Amount`) VALUES (%d, %d, %d, %d)", SLOT_TYPE_BACK, PlayerInfo[playerid][pID], itemid, param);
        mysql_function_query(dbHandle, query, false, "", "");
		AttachBackItem(playerid);
	}
}

stock AttachBackItem(playerid)
{
	if(GetItemObjectModel(GetBackItem(playerid)) != 0)
		SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(GetBackItem(playerid)), BONE_ID_SPINE, -0.18, -0.18, -0.15, -36.0, 5.0, 5.0);
}

stock DetachBackItem(playerid)
{
	RemovePlayerAttachedObject(playerid, INDEX_ID_BACK);
}

stock ResetAndSaveBack(playerid)
{
	new query[128];
	
	if(BackInfo[playerid][Item] > 0 && GetItemType(BackInfo[playerid][Item]) == ITEM_WEAPON)
	{
	    DetachBackItem(playerid);
		ResetBackInfo(playerid);
		format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `Type`=%d AND `Id`=%d", SLOT_TYPE_BACK, PlayerInfo[playerid][pID]);
	    mysql_function_query(dbHandle, query, false, "", "");
	}
	return 1;
}

stock PrintBackForPlayer(playerid, targetid)
{
	SendClientMessage(targetid, COLOR_WHITE, "======================[En la espalda]=====================");
 	if(GetBackItem(playerid) > 0)
 	    SendFMessage(targetid, COLOR_WHITE,"- Item: %s - %s: %d", GetItemName(GetBackItem(playerid)), GetItemParamName(GetBackItem(playerid)), GetBackParam(playerid));
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

stock LoadBackInfo(playerid)
{
	new query[128];
		
	ResetBackInfo(playerid);
	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`=%d AND `Id`=%d", SLOT_TYPE_BACK, PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnBackDataLoad", "i", playerid);
	return 1;
}

public OnBackDataLoad(playerid)
{
	new result[128], rows, fields;

	cache_get_data(rows, fields);
	
	if(rows)
	{
		cache_get_field_content(0, "Item", result);     BackInfo[playerid][Item] = strval(result);
		cache_get_field_content(0, "Amount", result);   BackInfo[playerid][Amount] = strval(result);
	}
	return 1;
}

//==================================COMANDOS====================================

CMD:esp(playerid, params[]) {
	cmd_espalda(playerid, params);
	return 1;
}

stock SaveItemOnBack(playerid, playerhand)
{
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	if(PlayerInfo[playerid][pHealth] < 25.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo mientras agonizas.");
	if(GetPVarInt(playerid, "cantSaveItems") == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");

	new itemid = GetHandItem(playerid, playerhand);

	if(itemid == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
	if(!HasBackPermission(itemid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ese item no se puede colgar en el hombro.");

	SetBackItemAndParam(playerid, itemid, GetHandParam(playerid, playerhand));
	SetHandItemAndParam(playerid, playerhand, 0, 0); // Borrado lógico y grafico de la mano.
	SendFMessage(playerid, COLOR_WHITE, "Has colgado un/a %s en tu hombro.", GetItemName(itemid));
  	SetPVarInt(playerid, "cantSaveItems", 1);
	SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	return 1;
}

stock TakeItemFromBack(playerid, playerhand)
{
	new itemid = GetBackItem(playerid),
		itemparam = GetBackParam(playerid),
		str[128];

	if(itemid <= 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada colgado de tu hombro.");
	if(GetHandItem(playerid, playerhand) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano ocupada.");

	SetHandItemAndParam(playerid, playerhand, itemid, itemparam); // Creación lógica y grafica en la mano.
	SetBackItemAndParam(playerid, 0, 0); // Borrado lógico del item del hombro.
	format(str, sizeof(str), "toma un/a %s de su hombro.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	return 1;
}

CMD:espalda(playerid, params[])
{
	new cmd[32];

    if(sscanf(params, "s[32]", cmd))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/esp)alda [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomar/tomari - guardar/guardari");
		PrintBackForPlayer(playerid, playerid);
		return 1;
    }
    
	if(strcmp(cmd, "tomar", true) == 0)
	{
		TakeItemFromBack(playerid, HAND_RIGHT);

    } else if(strcmp(cmd, "tomari", true) == 0)
	{
		TakeItemFromBack(playerid, HAND_LEFT);

    } else if(strcmp(cmd, "guardar", true) == 0)
	{
		SaveItemOnBack(playerid, HAND_RIGHT);

    } else if(strcmp(cmd, "guardari", true) == 0)
	{
		SaveItemOnBack(playerid, HAND_LEFT);
	}
	return 1;
}

