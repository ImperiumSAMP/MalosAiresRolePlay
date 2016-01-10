#if defined _isamp_espalda_included
	#endinput
#endif
#define _isamp_espalda_included

//===========================MODELADO DE ESPALDA================================

//============================VARIABLES INTERNAS================================

new BackInfo[MAX_PLAYERS][SlotInfo];

//===============================FUNCIONES======================================

forward OnBackDataLoad(playerid);

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

static const BackWeapons[] =
{
	WEAPON_KATANA, WEAPON_SHOTGUN,
	WEAPON_MP5, WEAPON_AK47, WEAPON_M4,
	WEAPON_RIFLE, WEAPON_SNIPER,
	ITEM_ID_MOCHILAGRANDE, ITEM_ID_MOCHILACHICA,
	ITEM_ID_MOCHILAMEDIANA
};

stock HasBackPermission(itemid)
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
	if(BackInfo[playerid][Item] > 0)
	{
	    DetachBackItem(playerid);
		ResetBackInfo(playerid);
	}
	if(itemid > 0)
	{
		BackInfo[playerid][Item] = itemid;
		BackInfo[playerid][Amount] = param;
		AttachBackItem(playerid);
	}
}

stock AttachBackItem(playerid)
{
	if(GetItemObjectModel(BackInfo[playerid][Item]) != 0)
	{
	    switch(BackInfo[playerid][Item])
	    {
	        case ITEM_ID_MOCHILAGRANDE:
	        	SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(BackInfo[playerid][Item]), BONE_ID_SPINE, 0.000, 0.000, 0.000, 0.000, 86.999, 0.000);
	        case ITEM_ID_MOCHILACHICA:
	        	SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(BackInfo[playerid][Item]), BONE_ID_SPINE, -0.151, -0.063, -0.013, 0.000, 0.000, 0.000);
			case ITEM_ID_MOCHILAMEDIANA:
                SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(BackInfo[playerid][Item]), BONE_ID_SPINE, 0.000, -0.127, -0.006, 0.000, 88.099, 0.000);
			default:
				SetPlayerAttachedObject(playerid, INDEX_ID_BACK, GetItemObjectModel(BackInfo[playerid][Item]), BONE_ID_SPINE, -0.18, -0.18, -0.15, -36.0, 5.0, 5.0);
		}
	}
}

stock DetachBackItem(playerid)
{
	RemovePlayerAttachedObject(playerid, INDEX_ID_BACK);
}

stock PrintBackForPlayer(playerid, targetid)
{
	SendClientMessage(targetid, COLOR_WHITE, "======================[En la espalda]=====================");
 	if(GetBackItem(playerid) > 0)
 	    SendFMessage(targetid, COLOR_WHITE,"- Item: %s - %s: %d", GetItemName(GetBackItem(playerid)), GetItemParamName(GetBackItem(playerid)), GetBackParam(playerid));
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

//=================BORRADO DE ARMAS AL MORIR SI NO ES COPDUTY===================

ResetBackWeapon(playerid)
{
	if(BackInfo[playerid][Item] > 0 && GetItemType(BackInfo[playerid][Item]) == ITEM_WEAPON)
	{
     	DetachBackItem(playerid);
		ResetBackInfo(playerid);
	}
	return 1;
}

//=======DESTRUCTOR DE LOS CONTENEDORES EN MEMORIA ASOCIADOS A LA ESPALDA=======

DestroyPlayerBack(playerid)
{
	if(GetItemType(BackInfo[playerid][Item]) == ITEM_CONTAINER)
	{
	    Container_Destroy(BackInfo[playerid][Amount]);
	}
	return 1;
}

//==================================COMANDOS====================================

CMD:esp(playerid, params[])
{
	cmd_espalda(playerid, params);
	return 1;
}

stock SaveItemOnBack(playerid, playerhand)
{
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en éste momento.");
	if(PlayerInfo[playerid][pHealth] < 25.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacerlo mientras estas agonizando!");
	if(GetPVarInt(playerid, "cantSaveItems") == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");

	new itemid = GetHandItem(playerid, playerhand);
	 str[128];

	if(GetBackItem(playerid) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes algo colgado en ese lado de tu hombro!");
	if(itemid == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
	if(!HasBackPermission(itemid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ese item no se puede colgar en el hombro.");

	SetBackItemAndParam(playerid, itemid, GetHandParam(playerid, playerhand));
	SetHandItemAndParam(playerid, playerhand, 0, 0); // Borrado lógico y grafico de la mano.
	format(str, sizeof(str), "pasa la cuerda de el/la %s por su brazo y cuello, para posteriormente colgarlo en el hombro.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
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
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada colgado en tu espalda.");
	if(GetHandItem(playerid, playerhand) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano ocupada.");

	SetHandItemAndParam(playerid, playerhand, itemid, itemparam); // Creación lógica y grafica en la mano.
	SetBackItemAndParam(playerid, 0, 0); // Borrado lógico del item del hombro.
	format(str, sizeof(str), "descuelga de su hombro el/la %s y lo/a sostiene con una de sus manos.", GetItemName(itemid));
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

