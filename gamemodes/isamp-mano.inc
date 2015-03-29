#if defined _isamp_mano_included
	#endinput
#endif
#define _isamp_mano_included

//==============================MODELADO DE MANO================================

//================================CONSTANTES====================================

#define SLOT_TYPE_HAND		    4

// #define HAND_LEFT             	0
// #define HAND_RIGHT              1

#define SAVE_UPDATE             1
#define SAVE_CREATE             2
#define SAVE_DESTROY            3

//============================VARIABLES INTERNAS================================

new HandInfo[MAX_PLAYERS][2][SlotInfo];

//===============================FUNCIONES======================================

forward GetHandItem(playerid, hand);
forward GetHandParam(playerid, hand);
forward SetHandItemAndParam(playerid, hand, itemid, param);
forward ResetHands(playerid);
forward ResetAndSaveHands(playerid);
forward PrintHandForPlayer(playerid, hand, targetid);
forward LoadHandsInfo(playerid);
forward SearchHandsForItem(playerid, itemid);
forward SearchFreeHand(playerid);
forward SynchronizeWeaponAmmo(playerid, ammo);

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
		SaveSlotInfo(SLOT_TYPE_HAND, playerid, hand); // Borramos el anterior
	}
	if(itemid != 0)
	{
	    HandInfo[playerid][hand][Item] = itemid;
		HandInfo[playerid][hand][Amount] = param;
		LoadHandItem(playerid, hand);
        SaveSlotInfo(SLOT_TYPE_HAND, playerid, hand);
	}
	return 1;
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

stock ResetAndSaveHands(playerid)
{
	if(HandInfo[playerid][HAND_LEFT][Item] > 0 && GetItemType(HandInfo[playerid][HAND_LEFT][Item]) == ITEM_WEAPON)
	    SetHandItemAndParam(playerid, HAND_LEFT, 0, 0);
	if(HandInfo[playerid][HAND_RIGHT][Item] > 0 && GetItemType(HandInfo[playerid][HAND_RIGHT][Item]) == ITEM_WEAPON)
		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	return 1;
}

stock PrintHandsForPlayer(playerid, targetid)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
	    leftitem = GetHandItem(playerid, HAND_LEFT);

	SendClientMessage(targetid, COLOR_WHITE, "======================[En la mano]=====================");
 	if(rightitem > 0)
		SendFMessage(targetid, COLOR_WHITE, "[Mano derecha] - Item: %s - %s: %d", GetItemName(rightitem), GetItemParamName(rightitem), GetHandParam(playerid, HAND_RIGHT));
	else
	    SendClientMessage(targetid, COLOR_WHITE, "[Mano derecha] - Nada");
 	if(leftitem > 0)
		SendFMessage(targetid, COLOR_WHITE, "[Mano izquierda] - Item: %s - %s: %d", GetItemName(leftitem), GetItemParamName(leftitem), GetHandParam(playerid, HAND_LEFT));
	else
	    SendClientMessage(targetid, COLOR_WHITE, "[Mano izquierda] - Nada");
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

stock LoadHandsInfo(playerid)
{
	new query[128];
		
	ResetHands(playerid); // Reseteamos la variable a cero y cargamos la nueva data (porque si no carga nada queda la data del anterior pj con misma id)
	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_HAND, PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_HAND, playerid);
	return 1;
}

//==========[Sincronizacion del arma en mano con las balas gastadas]============

new bool:cantSaveSync[MAX_PLAYERS];

forward CantSaveSyncTimer(playerid);
public CantSaveSyncTimer(playerid)
{
    cantSaveSync[playerid] = false;
	return 1;
}

stock SynchronizeWeaponAmmo(playerid, ammo)
{
	HandInfo[playerid][HAND_RIGHT][Amount] = ammo;
	if(cantSaveSync[playerid] == false)
	{
	    SaveSlotInfo(SLOT_TYPE_HAND, playerid, HAND_RIGHT, SAVE_UPDATE);
	    cantSaveSync[playerid] = true;
		SetTimerEx("CantSaveSyncTimer", 2000, false, "i", playerid);
	}
	if(ammo <= 0) // Se le terminó el arma
	    SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
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
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
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

CMD:mano(playerid, params[])
{
	new command[128],
		targetid;
	    
	if(sscanf(params, "s[128]", command, targetid))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mano [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar - tirar - tirari - agarrar - agarrari - cambiar - combinar");
		PrintHandsForPlayer(playerid, playerid);
    } else {
		if(strcmp(command, "cambiar", true) == 0) {
		
		    new rightitem = GetHandItem(playerid, HAND_RIGHT),
		        rightparam = GetHandParam(playerid, HAND_RIGHT),
		        leftitem = GetHandItem(playerid, HAND_LEFT),
		        leftparam = GetHandParam(playerid, HAND_LEFT);
		        
            if(rightitem == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer. Utiliza /guardartazer.");
			if(rightitem == ITEM_ID_TELEFONO_CELULAR)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el telefono celular.");
            if(GetPVarInt(playerid, "cantSaveItems") == 1)
 				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
	    		
          	SetHandItemAndParam(playerid, HAND_RIGHT, leftitem, leftparam);
          	SetHandItemAndParam(playerid, HAND_LEFT, rightitem, rightparam);
          	SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 3000, false, "i", playerid);
			SendClientMessage(playerid, COLOR_WHITE, "Has intercambiado de una mano a otra los ítems que estabas sosteniendo.");

		} else if(strcmp(command, "combinar", true) == 0) {

		    new rightitem = GetHandItem(playerid, HAND_RIGHT),
		        rightparam = GetHandParam(playerid, HAND_RIGHT),
		        leftitem = GetHandItem(playerid, HAND_LEFT),
		        leftparam = GetHandParam(playerid, HAND_LEFT);

			if(rightitem == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer. Utiliza /guardartazer.");
			if(rightitem == 0 || leftitem == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes tener la misma arma en ambas manos.");
			if(GetItemType(rightitem) != ITEM_WEAPON || GetItemType(leftitem) != ITEM_WEAPON)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes tener la misma arma en ambas manos.");
			if(rightitem != leftitem)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes tener la misma arma en ambas manos.");
			if(rightparam + leftparam > 400)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad conjunta de balas no puede superar las 400.");

			SetHandItemAndParam(playerid, HAND_LEFT, 0, 0);
			SetHandItemAndParam(playerid, HAND_RIGHT, rightitem, rightparam + leftparam);

		} else if(strcmp(command, "tirar", true) == 0) {

			DropObject(playerid, HAND_RIGHT);

		} else if(strcmp(command, "tirari", true) == 0) {
		
			DropObject(playerid, HAND_LEFT);

		} else if(strcmp(command, "agarrar", true) == 0) {

			TakeObject(playerid, HAND_RIGHT);

		} else if(strcmp(command, "agarrari", true) == 0) {

			TakeObject(playerid, HAND_LEFT);
			
		} else if(strcmp(command, "usar", true) == 0) {

			if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_SANDWICH) {
	            PlayerActionMessage(playerid, 15.0, "comienza a comer un sándwich de jámon y queso.");
	            PlayerEat(playerid, 40);
	            if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
	            	SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_SANDWICH, GetHandParam(playerid, HAND_RIGHT) - 1);
				else
					SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
	        } else if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_ALFAJOR) {
         		PlayerActionMessage(playerid, 15.0, "comienza a comer un alfajor.");
		        PlayerEat(playerid, 15);
		        if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
		          	SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_ALFAJOR, GetHandParam(playerid, HAND_RIGHT) - 1);
				else
					SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
			} else if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_AGUAMINERAL) {
				PlayerActionMessage(playerid, 15.0, "comienza a beber de su botella de agua mineral.");
			    PlayerDrink(playerid, 50);
			    if(GetHandParam(playerid, HAND_RIGHT) - 1 > 0)
			      	SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_SANDWICH, GetHandParam(playerid, HAND_RIGHT) - 1);
				else
					SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico
			} else
  				SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
		}
	}
	return 1;
}
			
