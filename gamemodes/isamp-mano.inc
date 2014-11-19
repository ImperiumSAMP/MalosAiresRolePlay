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
	HandInfo[playerid][hand][Item] = itemid;
	HandInfo[playerid][hand][Amount] = param;
	SaveSlotInfo(SLOT_TYPE_HAND, playerid, hand);
	if(itemid != 0)
	    LoadHandItem(playerid, hand);
	else
	    DeleteHandItem(playerid, hand);
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
	if(HandInfo[playerid][HAND_LEFT][Item] > 0)
	{
		HandInfo[playerid][HAND_LEFT][Item] = 0;
		HandInfo[playerid][HAND_LEFT][Amount] = 0;
        SaveSlotInfo(SLOT_TYPE_HAND, playerid, HAND_LEFT);
	}
	if(HandInfo[playerid][HAND_RIGHT][Item] > 0)
	{
		HandInfo[playerid][HAND_RIGHT][Item] = 0;
		HandInfo[playerid][HAND_RIGHT][Amount] = 0;
        SaveSlotInfo(SLOT_TYPE_HAND, playerid, HAND_RIGHT);
	}
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
}

//==================================COMANDOS====================================

CMD:mano(playerid, params[])
{
	new command[128],
		targetid;
	    
	if(sscanf(params, "s[128]", command, targetid))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mano [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar - tirar - tirari - agarrar - agarrari - cambiar");
		PrintHandsForPlayer(playerid, playerid);
    } else {
		if(strcmp(command, "cambiar", true) == 0) {
		
		    new rightitem = GetHandItem(playerid, HAND_RIGHT),
		        rightparam = GetHandParam(playerid, HAND_RIGHT),
		        leftitem = GetHandItem(playerid, HAND_LEFT),
		        leftparam = GetHandParam(playerid, HAND_LEFT);
		        
          	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico.
          	SetHandItemAndParam(playerid, HAND_LEFT, 0, 0); // Borrado lógico y grafico.
          	SetHandItemAndParam(playerid, HAND_RIGHT, leftitem, leftparam);
          	SetHandItemAndParam(playerid, HAND_LEFT, rightitem, rightparam);
			SendClientMessage(playerid, COLOR_WHITE, "Has intercambiado de una mano a otra los items que estabas sosteniendo.");
			
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
	            PlayerActionMessage(playerid, 15.0, "comienza a comer un sandwich de jamon y queso.");
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
			
