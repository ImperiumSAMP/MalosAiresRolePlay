#if defined _isamp_mano_included
	#endinput
#endif
#define _isamp_mano_included

//==============================MODELADO DE MANO================================

//================================CONSTANTES====================================

#define SLOT_TYPE_HAND		    4

// #define HAND_LEFT             	0
// #define HAND_RIGHT              1

//============================VARIABLES INTERNAS================================

new HandInfo[MAX_PLAYERS][2][SlotInfo];

//===============================FUNCIONES======================================

forward GetHandItem(playerid, hand);
forward GetHandParam(playerid, hand);
forward SetHandItemAndParam(playerid, hand, itemid, param);
forward ResetHand(playerid, hand);
forward ResetAndSaveHand(playerid, hand);
forward PrintHandForPlayer(playerid, hand, targetid);
forward LoadHandInfo(playerid, hand);

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
		if(GetItemType(itemid) == ITEM_WEAPON && hand == HAND_RIGHT)
 			RemovePlayerWeapon(playerid, itemid);
	}
	HandInfo[playerid][hand][Item] = itemid;
	HandInfo[playerid][hand][Amount] = param;
	SaveSlotInfo(SLOT_TYPE_HAND, playerid, hand);
	if(GetItemType(itemid) == ITEM_WEAPON && hand == HAND_RIGHT)
		GivePlayerWeapon(playerid, itemid, param);
	if(itemid != 0)
	    LoadHandItem(playerid, hand);
	else
	    DeleteHandItem(playerid, hand);
	return 1;
}

stock ResetHand(playerid, hand)
{
	HandInfo[playerid][hand][Item] = 0;
	HandInfo[playerid][hand][Amount] = 0;
	return 1;
}

stock ResetAndSaveHand(playerid, hand)
{
	if(HandInfo[playerid[hand][Item] > 0)
	{
		HandInfo[playerid][hand][Item] = 0;
		HandInfo[playerid][hand][Amount] = 0;
        SaveSlotInfo(SLOT_TYPE_HAND, playerid, hand);
	}
	return 1;
}

stock PrintHandsForPlayer(playerid, targetid)
{
	new rightitem = GetHandItem(playerid, HAND_RIGHT),
	    leftitem = GetHandItem(playerid, HAND_LEFT);

	SendClientMessage(targetid, COLOR_WHITE, "======================[En la mano]=====================");
 	if(rightitem > 0)
		SendFMessage(targetid, COLOR_WHITE, " [Mano derecha] - Item: %s - %s: %d", GetItemName(rightitem), GetItemParamName(rightitem), GetHandParam(playerid, HAND_RIGHT));
	else
	    SendClientMessage(targetid, COLOR_WHITE, "[Mano derecha] - Nada");
 	if(leftitem > 0)
		SendFMessage(targetid, COLOR_WHITE, " [Mano izquierda] - Item: %s - %s: %d", GetItemName(leftitem), GetItemParamName(leftitem), GetHandParam(playerid, HAND_LEFT));
	else
	    SendClientMessage(targetid, COLOR_WHITE, "[Mano izquierda] - Nada");
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

stock LoadHandInfo(playerid, hand)
{
	new query[128];
		
	ResetHand(playerid, hand); // Reseteamos la variable a cero y cargamos la nueva data (porque si no carga nada queda la data del anterior pj con misma id)
	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d AND `Slot` = %d", SLOT_TYPE_HAND, PlayerInfo[playerid][pID], hand);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_HAND, playerid);
	return 1;
}

//==================================COMANDOS====================================

CMD:mano(playerid, params[])
{
	new command[128],
		targetid;
	    
	if(sscanf(params, "s[128]I(-1)", command, targetid))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mano [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar - dar [ID/Jugador] - tirar - agarrar - cambiar");
		PrintHandsForPlayer(playerid, playerid);
    } else {
        if(strcmp(command, "dar", true) == 0) {
        
            new rightitem = GetHandItem(playerid, HAND_RIGHT),
            	rightparam = GetHandParam(playerid, HAND_RIGHT),
                str[128];
            
			if(PlayerInfo[playerid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
			if(rightitem == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tus mano derecha.");
	  		if(targetid == playerid || !ProxDetectorS(2.0, playerid, targetid))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Jugador inválido o se encuentra muy lejos!");
			if(PlayerInfo[targetid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El usuario debe ser al menos nivel 3 para recibir un item.");
			if(GetHandItem(targetid, HAND_RIGHT) != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "El usuario tiene otro item en las mano derecha.");
			    
			format(str, sizeof(str), "le entrega un/a %s a", GetItemName(rightitem));
            PlayerPlayerActionMessage(playerid, targetid, 15.0, str);
			SetHandItemAndParam(targetid, HAND_RIGHT, rightitem, rightparam); // Creación lógica y grafica.
			SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico.

		} else if(strcmp(command, "cambiar", true) == 0) {
		
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
			    
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
			if(GetHandItem(playerid, HAND_RIGHT) == 0)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tu mano derecha.");

			DropObject(playerid);

		} else if(strcmp(command, "agarrar", true) == 0) {

			if(PlayerInfo[playerid][pHealth] < 25.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar un objeto agonizando.");
		    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
			if(GetHandItem(playerid, HAND_RIGHT) != 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el objeto ya que tienes algo en tus mano derecha.");

			TakeObject(playerid);
			
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
			
