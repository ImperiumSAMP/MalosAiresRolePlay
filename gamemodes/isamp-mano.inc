#if defined _isamp_mano_included
	#endinput
#endif
#define _isamp_mano_included

//===========================ARMARIOS PARA LAS CASAS============================

//================================CONSTANTES====================================

#define SLOT_TYPE_HAND          4

//============================VARIABLES INTERNAS================================

new HandInfo[MAX_PLAYERS][SlotInfo];

//===============================FUNCIONES======================================

forward GetHandItem(playerid);
forward GetHandParam(playerid);
forward SetHandItemAndParam(playerid, itemid, param);
forward ResetHand(playerid);
forward ResetAndSaveHand(playerid);
forward PrintHandForPlayer(playerid, targetid);
forward LoadHandInfo(playerid);

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock GetHandItem(playerid)
{
	return HandInfo[playerid][Item];
}

stock GetHandParam(playerid)
{
	return HandInfo[playerid][Amount];
}

stock SetHandItemAndParam(playerid, itemid, param)
{
	if(GetHandItem(playerid) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	{
	    DeleteHandItem(playerid);
		HandInfo[playerid][Item] = 0;
		HandInfo[playerid][Amount] = 0;
		SaveSlotInfo(SLOT_TYPE_HAND, playerid, 0); // Borramos el anterior
	}
	HandInfo[playerid][Item] = itemid;
	HandInfo[playerid][Amount] = param;
	SaveSlotInfo(SLOT_TYPE_HAND, playerid, 0);
	if(itemid != 0)
	    LoadHandItem(playerid);
	else
	    DeleteHandItem(playerid);
	return 1;
}

stock ResetHand(playerid)
{
	HandInfo[playerid][Item] = 0;
	HandInfo[playerid][Amount] = 0;
	return 1;
}

stock ResetAndSaveHand(playerid)
{
	if(HandInfo[playerid][Item] > 0)
	{
		HandInfo[playerid][Item] = 0;
		HandInfo[playerid][Amount] = 0;
		SaveSlotInfo(SLOT_TYPE_HAND, playerid, 0);
	}
	return 1;
}

stock PrintHandForPlayer(playerid, targetid)
{
	new itemid = GetHandItem(playerid);

	SendClientMessage(targetid, COLOR_WHITE, "======================[En la mano]=====================");
 	if(itemid > 0)
		SendFMessage(targetid, COLOR_WHITE, " - Item: %s - %s: %d", GetItemName(itemid), GetItemParamName(itemid), GetHandParam(playerid));
	else
	    SendClientMessage(targetid, COLOR_WHITE, " - Nada");
	SendClientMessage(targetid, COLOR_WHITE, "=====================================================");
	return 1;
}

stock LoadHandInfo(playerid)
{
	new
		query[128];
		
	ResetHand(playerid); // Reseteamos la variable a cero y cargamos la nueva data (porque si no carga nada queda la data del anterior pj con misma id)
	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_HAND, PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_HAND, playerid);
	return 1;
}

//==================================COMANDOS====================================

CMD:mano(playerid, params[])
{
	new
		command[128],
		targetid,
		string[128],
		itemid = GetHandItem(playerid),
		itemparam = GetHandParam(playerid);
	    
	if(sscanf(params, "s[128]I(-1)", command, targetid))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mano [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} usar - dar [ID/Jugador] - tirar");
		PrintHandForPlayer(playerid, playerid);
    } else {
        if(strcmp(command, "dar", true) == 0) {
        
			if(PlayerInfo[playerid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
			if(itemid == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tus manos.");
	  		if(targetid == INVALID_PLAYER_ID || targetid == playerid || !ProxDetectorS(2.0, playerid, targetid))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Jugador inválido o se encuentra muy lejos!");
	        if(PlayerInfo[playerid][pHealth] < 25.0)
	            return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes dar un item agonizando.");
			if(PlayerInfo[targetid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El usuario debe ser al menos nivel 3 para recibir un item.");
			if(GetHandItem(targetid) != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "El usuario tiene otro item en las manos.");
			    
			format(string, sizeof(string), "le entrega un/a %s a", GetItemName(itemid));
            PlayerPlayerActionMessage(playerid, targetid, 15.0, string);
			SetHandItemAndParam(targetid, itemid, itemparam); // Creación lógica y grafica.
			SetHandItemAndParam(playerid, 0, 0); // Borrado lógico y grafico.
			
		} else if(strcmp(command, "tirar", true) == 0) {
		
 			if(PlayerInfo[playerid][pHealth] < 25.0)
	            return SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡No puedes desechar un item agonizando!");
 			if(itemid == 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tus manos.");
			    
			DropObject(playerid);
			
		} else if(strcmp(command, "usar", true) == 0) {

			if(GetHandItem(playerid) == ITEM_ID_SANDWICH) {
	            PlayerActionMessage(playerid, 15.0, "comienza a comer un sandwich de jamon y queso.");
	            PlayerEat(playerid, 40.0);
	            if(GetHandParam(playerid) - 1 > 0)
	            	SetHandItemAndParam(playerid, ITEM_ID_SANDWICH, GetHandParam(playerid) - 1);
				else
					SetHandItemAndParam(playerid, 0, 0); // Borrado lógico y grafico
	        } else if(GetHandItem(playerid) == ITEM_ID_ALFAJOR) {
         		PlayerActionMessage(playerid, 15.0, "comienza a comer un alfajor.");
		        PlayerEat(playerid, 15.0);
		        if(GetHandParam(playerid) - 1 > 0)
		          	SetHandItemAndParam(playerid, ITEM_ID_ALFAJOR, GetHandParam(playerid) - 1);
				else
					SetHandItemAndParam(playerid, 0, 0); // Borrado lógico y grafico
			} else if(GetHandItem(playerid) == ITEM_ID_AGUAMINERAL) {
				PlayerActionMessage(playerid, 15.0, "comienza a beber de su botella de agua mineral.");
			    PlayerDrink(playerid, 50.0);
			    if(GetHandParam(playerid) - 1 > 0)
			      	SetHandItemAndParam(playerid, ITEM_ID_SANDWICH, GetHandParam(playerid) - 1);
				else
					SetHandItemAndParam(playerid, 0, 0); // Borrado lógico y grafico
			} else
  				SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
		}
	}
	return 1;
}
			
