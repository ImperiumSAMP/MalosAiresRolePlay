#if defined _isamp_mano_included
	#endinput
#endif
#define _isamp_mano_included

//==============================MODELADO DE MANO================================

//================================CONSTANTES====================================

// #define HAND_LEFT             	0
// #define HAND_RIGHT              1

#define SAVE_UPDATE             1
#define SAVE_CREATE             2
#define SAVE_DESTROY            3

//============================VARIABLES INTERNAS================================

enum SlotInfo {
	Item,
	Amount,
};

new HandInfo[MAX_PLAYERS][2][SlotInfo];

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock GetHandItem(playerid, hand)
{
	return HandInfo[playerid][hand][Item];
}

stock GetHandParam(playerid, hand)
{
	return HandInfo[playerid][hand][Amount];
}

stock SetHandItemAndParam(playerid, hand, itemid, param)
{
	if(GetHandItem(playerid, hand) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	{
	    DeleteHandItem(playerid, hand);
		HandInfo[playerid][hand][Item] = 0;
		HandInfo[playerid][hand][Amount] = 0;
	}
	
	if(itemid > 0)
	{
	    HandInfo[playerid][hand][Item] = itemid;
		HandInfo[playerid][hand][Amount] = param;
		LoadHandItem(playerid, hand);
	}
}

stock SearchHandsForItem(playerid, itemid)
{
	if(HandInfo[playerid][HAND_RIGHT][Item] == itemid)
	    return HAND_RIGHT;
	else if(HandInfo[playerid][HAND_LEFT][Item] == itemid)
	    return HAND_LEFT;
	else
	    return -1;
}

stock SearchFreeHand(playerid)
{
	if(HandInfo[playerid][HAND_RIGHT][Item] == 0)
	    return HAND_RIGHT;
	else if(HandInfo[playerid][HAND_LEFT][Item] == 0)
	    return HAND_LEFT;
	else
	    return -1;
}

stock ResetHands(playerid)
{
	HandInfo[playerid][HAND_LEFT][Item] = 0;
	HandInfo[playerid][HAND_LEFT][Amount] = 0;
	HandInfo[playerid][HAND_RIGHT][Item] = 0;
	HandInfo[playerid][HAND_RIGHT][Amount] = 0;
	return 1;
}

stock PrintRightHandForPlayer(playerid, targetid)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
		rightparam = GetHandParam(playerid, HAND_RIGHT),
		itemname[64],
		itemparam[64],
		itemtype = GetItemType(rightitem);
	
	format(itemname, sizeof(itemname), "%s", GetItemName(rightitem));
	format(itemparam, sizeof(itemparam), "%s", GetItemParamName(rightitem));
	
	if(rightitem == 0)
		return SendClientMessage(targetid, COLOR_WHITE, "[Mano derecha] - Nada");
		
	if(itemtype == ITEM_FIREWEAPON)
	{
		if(rightparam > 0)
		{
		    format(itemname, sizeof(itemname), "%s cargada", GetItemName(rightitem));
			rightparam -= 1;
		}
		if(rightparam == 0)
		    format(itemname, sizeof(itemname), "%s descargada", GetItemName(rightitem));
	}
		
	SendFMessage(targetid, COLOR_WHITE, "[Mano derecha] - Item: %s - %s: %d", itemname, itemparam, rightparam);
	return 1;
}

stock PrintLeftHandForPlayer(playerid, targetid)
{
	new leftitem = GetHandItem(playerid, HAND_LEFT),
		leftparam = GetHandParam(playerid, HAND_LEFT),
		itemname[64],
		itemparam[64],
		itemtype = GetItemType(leftitem);

	format(itemname, sizeof(itemname), "%s", GetItemName(leftitem));
	format(itemparam, sizeof(itemparam), "%s", GetItemParamName(leftitem));

	if(leftitem == 0)
		return SendClientMessage(targetid, COLOR_WHITE, "[Mano izquierda] - Nada");

	if(itemtype == ITEM_FIREWEAPON)
	{
		if(leftparam > 0)
		{
		    format(itemname, sizeof(itemname), "%s cargada", GetItemName(leftitem));
		    leftparam -= 1;
		}
		if(leftparam == 0)
		    format(itemname, sizeof(itemname), "%s descargada", GetItemName(leftitem));
	}

	SendFMessage(targetid, COLOR_WHITE, "[Mano izquierda] - Item: %s - %s: %d", itemname, itemparam, leftparam);
	return 1;
}

stock PrintHandsForPlayer(playerid, targetid)
{

	SendClientMessage(targetid, COLOR_WHITE, "======================[En la mano]=====================");
	PrintRightHandForPlayer(playerid, targetid);
	PrintLeftHandForPlayer(playerid, targetid);
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

//=================SISTEMA DE CARGADORES===================

stock ReloadWeapon(playerid)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
		leftitem = GetHandItem(playerid, HAND_LEFT),
		rightparam = GetHandParam(playerid, HAND_RIGHT),
		leftparam = GetHandParam(playerid, HAND_LEFT);

	if(GetItemType(rightitem) == ITEM_FIREWEAPON)
	{
		if(rightparam > 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Tu arma ya está cargada. Usa /mano separar para retirar el cargador");
			
		switch(rightitem)
		{
		    case ITEM_ID_9MM: if(leftitem != ITEM_ID_CARGADOR_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		    case ITEM_ID_9MM_SILENCED: if(leftitem != ITEM_ID_CARGADOR_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		    case ITEM_ID_DEAGLE: if(leftitem != ITEM_ID_CARGADOR_DEAGLE) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_UZI: if(leftitem != ITEM_ID_CARGADOR_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_TEC9: if(leftitem != ITEM_ID_CARGADOR_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_MP5: if(leftitem != ITEM_ID_CARGADOR_MP5) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_M4: if(leftitem != ITEM_ID_CARGADOR_M4) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_AK47: if(leftitem != ITEM_ID_CARGADOR_AK47) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		}
		SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, leftparam + 1);
		SetHandItemAndParam(playerid, HAND_LEFT, 0, 0);
		PlayerCmeMessage(playerid, 15.0, 5000, "calza el cargador en el arma, con la mano contraria.");
		return 1;
	}

	else if(GetItemType(leftitem) == ITEM_FIREWEAPON)
	{
	 	switch(leftitem)
		{
		    case ITEM_ID_9MM: if(rightitem != ITEM_ID_CARGADOR_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		    case ITEM_ID_9MM_SILENCED: if(rightitem != ITEM_ID_CARGADOR_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		    case ITEM_ID_DEAGLE: if(rightitem != ITEM_ID_CARGADOR_DEAGLE) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto");
			case ITEM_ID_UZI: if(rightitem != ITEM_ID_CARGADOR_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_TEC9: if(rightitem != ITEM_ID_CARGADOR_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_MP5: if(rightitem != ITEM_ID_CARGADOR_MP5) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto");
			case ITEM_ID_M4: if(rightitem != ITEM_ID_CARGADOR_M4) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
			case ITEM_ID_AK47: if(rightitem != ITEM_ID_CARGADOR_AK47) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar tu arma con este objeto.");
		}
		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
		SetHandItemAndParam(playerid, HAND_LEFT, leftitem, rightparam + 1);
		PlayerCmeMessage(playerid, 15.0, 5000, "calza el cargador en el arma, con la mano contraria.");
		return 1;
	}
	return 1;
}

stock ReplenishClip(playerid)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
		leftitem = GetHandItem(playerid, HAND_LEFT),
		rightparam = GetHandParam(playerid, HAND_RIGHT),
		leftparam = GetHandParam(playerid, HAND_LEFT);

	switch(rightitem)
	{
		case ITEM_ID_CARGADOR_9MM: if(rightparam == 17) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
		case ITEM_ID_CARGADOR_DEAGLE: if(rightparam == 7) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
		case ITEM_ID_CARGADOR_UZI: if(rightparam == 50) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
		case ITEM_ID_CARGADOR_MP5: if(rightparam == 30) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
		case ITEM_ID_CARGADOR_M4: if(rightparam == 50) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
		case ITEM_ID_CARGADOR_AK47: if(rightparam == 30) return SendClientMessage(playerid, COLOR_YELLOW2, "Tu cargador ya está lleno.");
	}

	if(GetItemType(rightitem) == ITEM_WEAPONMAG)
	{
		switch(rightitem)
		{
		    case ITEM_ID_CARGADOR_9MM: if(leftitem != ITEM_ID_CAJA_BALAS_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		    case ITEM_ID_CARGADOR_DEAGLE: if(leftitem != ITEM_ID_CAJA_BALAS_DEAGLE) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		    case ITEM_ID_CARGADOR_UZI: if(leftitem != ITEM_ID_CAJA_BALAS_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_MP5: if(leftitem != ITEM_ID_CAJA_BALAS_MP5) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_M4: if(leftitem != ITEM_ID_CAJA_BALAS_M4) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_AK47: if(leftitem != ITEM_ID_CAJA_BALAS_AK47) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		}
		SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, rightparam + 1);
		SetHandItemAndParam(playerid, HAND_LEFT, leftitem, leftparam - 1);
		PlayerCmeMessage(playerid, 15.0, 5000, "retira un proyectil de la caja y lo inserta en el cargador, haciendo presión.");
		return 1;
	}

	else if(GetItemType(leftitem) == ITEM_WEAPONMAG)
	{
	 	switch(leftitem)
		{
		    case ITEM_ID_CARGADOR_9MM: if(rightitem != ITEM_ID_CAJA_BALAS_9MM) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		    case ITEM_ID_CARGADOR_DEAGLE: if(rightitem != ITEM_ID_CAJA_BALAS_DEAGLE) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		    case ITEM_ID_CARGADOR_UZI: if(rightitem != ITEM_ID_CAJA_BALAS_UZI) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_MP5: if(rightitem != ITEM_ID_CAJA_BALAS_MP5) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_M4: if(rightitem != ITEM_ID_CAJA_BALAS_M4) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
			case ITEM_ID_CARGADOR_AK47: if(rightitem != ITEM_ID_CAJA_BALAS_AK47) return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes rellenar tu cargador con este objeto.");
		}
		SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, rightparam - 1);
		SetHandItemAndParam(playerid, HAND_LEFT, leftitem, leftparam + 1);
		PlayerCmeMessage(playerid, 15.0, 5000, "retira un proyectil de la caja y lo inserta en el cargador, haciendo presión.");
		return 1;
	}
	return 1;
}

//==========[Sincronizacion del arma en mano con las balas gastadas]============

SynchronizeWeaponAmmo(playerid, ammo)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
	    itemtype = GetItemType(rightitem);

	switch(itemtype)
	{
	    case ITEM_WEAPON:
		{
		    if(ammo <= 0)
				SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
			else
			    HandInfo[playerid][HAND_RIGHT][Amount] = ammo;
		}
		
	    case ITEM_FIREWEAPON:
	    {
		    if(ammo < 2)
			{
				SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
				SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, 1);
			}
			else
			    HandInfo[playerid][HAND_RIGHT][Amount] = ammo + 1;
	    }
	}
}

//=================BORRADO DE ARMAS AL MORIR SI NO ES COPDUTY===================

ResetHandsWeapons(playerid)
{
	if(HandInfo[playerid][HAND_LEFT][Item] > 0 && GetItemType(HandInfo[playerid][HAND_LEFT][Item]) == ITEM_WEAPON)
        SetHandItemAndParam(playerid, HAND_LEFT, 0, 0);
	if(HandInfo[playerid][HAND_RIGHT][Item] > 0 && GetItemType(HandInfo[playerid][HAND_RIGHT][Item]) == ITEM_WEAPON)
		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	return 1;
}

//=======DESTRUCTOR DE LOS CONTENEDORES EN MEMORIA ASOCIADOS A LAS MANOS========

DestroyPlayerHands(playerid)
{
    if(GetItemType(HandInfo[playerid][HAND_RIGHT][Item]) == ITEM_CONTAINER)
	{
	    Container_Destroy(HandInfo[playerid][HAND_RIGHT][Amount]);
	}
    if(GetItemType(HandInfo[playerid][HAND_LEFT][Item]) == ITEM_CONTAINER)
	{
	    Container_Destroy(HandInfo[playerid][HAND_LEFT][Amount]);
	}
	return 1;
}

//==================================COMANDOS====================================

stock GiveItemFromPlayerToPlayer(playerid, playerhand, targetid)
{
 	new itemid = GetHandItem(playerid, playerhand),
	 	str[128],
		targetfreehand;

	if(itemid == 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ningún item en esa mano.");
    if(targetid == playerid || !ProxDetectorS(2.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Jugador inválido o se encuentra muy lejos!");
	if(GetPVarInt(playerid, "cantSaveItems") == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro ítem!");
	if(GetPVarInt(playerid, "GrupoPaintball") != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
	if(itemid == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
	if(itemid == ITEM_ID_TELEFONO_CELULAR)
   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con tu teléfono");
	targetfreehand = SearchFreeHand(targetid);
	if(targetfreehand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto tiene ambas manos ocupadas y no puede agarrar nada más.");

	SetHandItemAndParam(targetid, targetfreehand, itemid, GetHandParam(playerid, playerhand));
	SetHandItemAndParam(playerid, playerhand, 0, 0);
	format(str, sizeof(str), "le entrega un/a %s a", GetItemName(itemid));
 	PlayerPlayerActionMessage(playerid, targetid, 15.0, str);
	SetPVarInt(playerid, "cantSaveItems", 1);
	SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	return 1;
}

CMD:dar(playerid, params[])
{
	new targetid;

	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dar [ID/Jugador]");

	GiveItemFromPlayerToPlayer(playerid, HAND_RIGHT, targetid);
	return 1;
}

CMD:dari(playerid, params[])
{
	new targetid;

	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dari [ID/Jugador]");

	GiveItemFromPlayerToPlayer(playerid, HAND_LEFT, targetid);
	return 1;
}

CMD:mc(playerid, params[])
{
	cmd_mano(playerid, "cambiar");
	return 1;
}

CMD:mano(playerid, params[])
{
	new command[32],
		newskin,
		rightitem = GetHandItem(playerid, HAND_RIGHT),
		rightparam = GetHandParam(playerid, HAND_RIGHT),
		leftitem = GetHandItem(playerid, HAND_LEFT),
		leftparam = GetHandParam(playerid, HAND_LEFT),
		itemtype = GetItemType(rightitem);
	    
	if(sscanf(params, "s[32]", command))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mano [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar - tirar - tirari - agarrar - agarrari - cambiar - combinar - separar - ver - guardar");
		PrintHandsForPlayer(playerid, playerid);
    } else {
		if(strcmp(command, "cambiar", true) == 0) {
		        
            if(rightitem == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer. Utiliza /guardartazer.");
			if(rightitem == ITEM_ID_TELEFONO_CELULAR)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el telefono celular.");
			if(GetPVarInt(playerid, "GrupoPaintball") != 0)
	            return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
            if(GetPVarInt(playerid, "cantSaveItems") == 1)
 				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro ítem!");
	    		
          	SetHandItemAndParam(playerid, HAND_RIGHT, leftitem, leftparam);
          	SetHandItemAndParam(playerid, HAND_LEFT, rightitem, rightparam);
          	SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 3000, false, "i", playerid);
			SendClientMessage(playerid, COLOR_WHITE, "Has intercambiado de una mano a otra los ítems que estabas sosteniendo.");

		} else if(strcmp(command, "combinar", true) == 0) {
		
			if(rightparam > 0 && itemtype == ITEM_FIREWEAPON)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu arma ya está cargada, usa /mano separar para descargarla.");

			ReloadWeapon(playerid);
			ReplenishClip(playerid);

		} else if(strcmp(command, "separar", true) == 0) {
			if(GetItemType(rightitem) != ITEM_FIREWEAPON)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Únicamente puedes usar este comando con armas.");
			if(SearchFreeHand(playerid) == -1)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Para descargar el arma necesitas la mano izquierda libre.");
			if(rightparam == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu arma está actualmente descargada.");
				    
			switch(rightitem)
			{
				case ITEM_ID_9MM: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_9MM, rightparam - 1);
				case ITEM_ID_9MM_SILENCED: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_9MM, rightparam - 1);
				case ITEM_ID_DEAGLE: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_DEAGLE, rightparam - 1);
				case ITEM_ID_UZI: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_UZI, rightparam - 1);
				case ITEM_ID_TEC9: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_UZI, rightparam - 1);
				case ITEM_ID_MP5: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_MP5, rightparam - 1);
				case ITEM_ID_M4: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_M4, rightparam - 1);
				case ITEM_ID_AK47: SetHandItemAndParam(playerid, HAND_LEFT, ITEM_ID_CARGADOR_AK47, rightparam - 1);
			}
			SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, 0);
			PlayerActionMessage(playerid, 15.0, "descalza el cargador del arma y lo sostiene con la mano izquierda.");


		} else if(strcmp(command, "tirar", true) == 0) {

			DropObject(playerid, HAND_RIGHT);

		} else if(strcmp(command, "tirari", true) == 0) {
		
			DropObject(playerid, HAND_LEFT);

		} else if(strcmp(command, "agarrar", true) == 0) {

			TakeObject(playerid, HAND_RIGHT);

		} else if(strcmp(command, "agarrari", true) == 0) {

			TakeObject(playerid, HAND_LEFT);
			
		} else if(strcmp(command, "ver", true) == 0) {

			new item = GetHandItem(playerid, HAND_RIGHT),
			    param = GetHandParam(playerid, HAND_RIGHT);
			    
			if(GetItemType(item) != ITEM_CONTAINER)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ningún ítem en la mano derecha del tipo contenedor.");
			if(!Container_Show(playerid, CONTAINER_TYPE_ITEM, param, playerid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del item. Reportar a un administador.");

		} else if(strcmp(command, "guardar", true) == 0) {

			new left_item = GetHandItem(playerid, HAND_LEFT),
			    left_param = GetHandParam(playerid, HAND_LEFT);

			if(GetItemType(GetHandItem(playerid, HAND_RIGHT)) != ITEM_CONTAINER)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ningún ítem en la mano derecha del tipo contenedor.");
			if(left_item == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ningún ítem en la mano izquierda para guardar.");
			if(left_item == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
			if(GetPVarInt(playerid, "GrupoPaintball") != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
			if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
			if(PlayerInfo[playerid][pHealth] < 25.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar un item agonizando.");
			if(!Container_AddItemAndParam(GetHandParam(playerid, HAND_RIGHT), left_item, left_param))
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el contenedor.");

			SetHandItemAndParam(playerid, HAND_LEFT, 0, 0); // Borrado lógico y grafico de la mano.

			SendFMessage(playerid, COLOR_WHITE, "Has guardado un/a %s en el contenedor que tienes en la mano derecha.", GetItemName(left_item));

			SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
				
		} else if(strcmp(command, "usar", true) == 0) {

			switch(rightitem)
			{
			    case ITEM_ID_SANDWICH:
			    {
	            	PlayerActionMessage(playerid, 15.0, "come un pedazo de su sándwich de jamón y queso.");
	            	PlayerEat(playerid, 10);
	            	if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
	            		SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_SANDWICH, GetHandParam(playerid, HAND_RIGHT) - 1);
					else
						SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
					return 1;
				}
			    
			    case ITEM_ID_ALFAJOR:
			    {
					PlayerActionMessage(playerid, 15.0, "comienza a comer un alfajor.");
					PlayerEat(playerid, 15);
					if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
						SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_ALFAJOR, GetHandParam(playerid, HAND_RIGHT) - 1);
					else
						SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
					return 1;
				}
			    
			    case ITEM_ID_AGUAMINERAL:
			    {
					if(GetHandParam(playerid, HAND_RIGHT) > 0) {
						PlayerActionMessage(playerid, 15.0, "toma un trago de su botella de agua.");
						PlayerDrink(playerid, 10);
						SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_AGUAMINERAL, GetHandParam(playerid, HAND_RIGHT) - 1);
					} else
						SendClientMessage(playerid, COLOR_YELLOW2, "¡La botella esta vacia! Necesitas llenar tu botella para usarla.");
					return 1;
				}
			    
			    case ITEM_ID_CERVEZA:
			    {
					PlayerActionMessage(playerid, 15.0, "toma un trago de su botella de cerveza.");
					PlayerDrink(playerid, 10);
					PlayerDrinkAlcohol(playerid, 4);
					if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
						SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_CERVEZA, GetHandParam(playerid, HAND_RIGHT) - 1);
					else
						SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
					return 1;
			    }

				case ITEM_ID_VESTIMENTA:
				{
				    if(PlayerInfo[playerid][pSex] == 0 && GetPlayerSkin(playerid) != 138)
				        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes ropa puesta, usa /desvestirse para quitártela!");
					if(PlayerInfo[playerid][pSex] == 1 && GetPlayerSkin(playerid) != 252)
						return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes ropa puesta, usa /desvestirse para quitártela!");
					PlayerActionMessage(playerid, 15.0, "se viste con la ropa que tiene en mano.");
					newskin = GetHandParam(playerid, HAND_RIGHT);
					GameTextForPlayer(playerid, "~w~Vistiendose...", 3000, 4);
					ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 1, 0, 0, 0, 0);
					SetTimerEx("GetDressed", 4000, false, "ii", playerid, newskin);
					SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
					return 1;
				}
				
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
		}
	}
	return 1;
}

Dialog:Dlg_Show_Item_Container(playerid, response, listitem, inputtext[])
{
	new container_id = Container_Selection[playerid][csId];

	ResetContainerSelection(playerid);

	if(response)
	{
        new itemid,
            itemparam,
            str[128];

		if(GetHandItem(playerid, HAND_LEFT) != 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano izquierda ocupada.");

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SetHandItemAndParam(playerid, HAND_LEFT, itemid, itemparam); // Creación lógica y grafica en la mano.

            SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

			format(str, sizeof(str), "toma un/a %s del contenedor de su mano derecha.", GetItemName(itemid));
			PlayerActionMessage(playerid, 15.0, str);
		}
		else
		{
	        SendClientMessage(playerid, COLOR_YELLOW2, "Contenedor vacio o el slot es inválido.");
		}
	}
	return 1;
}
