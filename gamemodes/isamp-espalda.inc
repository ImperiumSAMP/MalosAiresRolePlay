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
	WEAPON_BAT, WEAPON_KATANA, WEAPON_SHOTGUN,
	WEAPON_MP5, WEAPON_AK47, WEAPON_M4,
	WEAPON_RIFLE, WEAPON_SNIPER
};

stock BackPermission(itemid)
{
	for(new i = 0; i < sizeof(BackWeapons); i++)
	{
	    if(itemid == BackWeapons[i])
	        return 1;
	}
	return 0;
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
			AttachBackItem(playerid);
		}
	}
	else if(itemid > 0)
	{
		BackInfo[playerid][Item] = itemid;
		BackInfo[playerid][Amount] = param;
		format(query, sizeof(query), "INSERT INTO `slots_info` (`Type`, `Id`, `Item`, `Amount`) VALUES (%d, %d, %d, %d)", SLOT_TYPE_BACK, PlayerInfo[playerid][pID], itemid, param);
		AttachBackItem(playerid);
	}
}

stock AttachBackItem(playerid)
{
	if(GetItemObjectModel(GetBackItem(playerid)) != 0)
		SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(GetBackItem(playerid)), BONE_ID_SPINE, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
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

