#if defined _isamp_inventory_included
	#endinput
#endif
#define _isamp_inventory_included

//=====================SISTEMA DE INVENTARIO DE JUGADORES=======================

//================================CONSTANTES====================================

#define CONTAINER_INV_SPACE   	25

//=================================FUNCIONES====================================

forward PrintInvForPlayer(playerid, targetid); // Imprime el inventario del jugador X al jugador Y.

//==============================[EXPERIMENTAL]==================================

stock PrintInvForPlayer(playerid, targetid)
{
	if(!Container_Show(playerid, CONTAINER_TYPE_INV, PlayerInfo[playerid][pContainerID], targetid, 0))
		SendClientMessage(targetid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del inventario. Reportar a un scripter.");
	return 1;
}

CMD:inv(playerid, params[])
{
	cmd_inventario(playerid, params);
	return 1;
}

CMD:inventario(playerid, params[])
{
	new cmd[24], str[128];

    if(sscanf(params, "s[24]", cmd))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/inv)entario [comando] - {5CCAF1}[Comandos]:{C8C8C8} guardar - guardari");

		if(!Container_Show(playerid, CONTAINER_TYPE_INV, PlayerInfo[playerid][pContainerID], playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del inventario. Reportar a un administador.");
    }
	else
	{
		if(strcmp(cmd, "guardar", true) == 0)
		{
			if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
			if(PlayerInfo[playerid][pHealth] < 25.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar un item agonizando.");
			if(GetPVarInt(playerid, "GrupoPaintball") != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
			if(GetPVarInt(playerid, "cantSaveItems") == 1)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "隆Debes esperar un tiempo antes de volver a interactuar con otro item!");

			new itemid = GetHandItem(playerid, HAND_RIGHT),
		    	itemparam = GetHandParam(playerid, HAND_RIGHT);

			if(itemid == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
			if(isPlayerInTrainning(playerid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo mientras estas realizando el entrenamiento de tiro");
			if(!HasItemInvPermission(itemid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "Ese item no se puede guardar en el inventario.");
			if(!Container_AddItemAndParam(PlayerInfo[playerid][pContainerID], itemid, itemparam))
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en tu inventario.");

			SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado l贸gico y grafico de la mano.
			
			format(str, sizeof(str), "Utilizando su mano derecha, guarda un/a %s en su inventario.", GetItemName(itemid));
			PlayerCmeMessage(playerid, 15.0, 5000, str);
			
			SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	    }
		else if(strcmp(cmd, "guardari", true) == 0)
		{
			if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
			if(PlayerInfo[playerid][pHealth] < 25.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar un item agonizando.");
			if(GetPVarInt(playerid, "GrupoPaintball") != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
			if(GetPVarInt(playerid, "cantSaveItems") == 1)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "ebes esperar un tiempo antes de volver a interactuar con otro item!");

			new itemid = GetHandItem(playerid, HAND_LEFT),
		    	itemparam = GetHandParam(playerid, HAND_LEFT);

			if(itemid == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
			if(!HasItemInvPermission(itemid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "Ese item no se puede guardar en el inventario.");
			if(!Container_AddItemAndParam(PlayerInfo[playerid][pContainerID], itemid, itemparam))
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en tu inventario.");

			SetHandItemAndParam(playerid, HAND_LEFT, 0, 0); // Borrado l贸gico y grafico de la mano.

			SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
			
			format(str, sizeof(str), "Utilizando su mano izquierda, guarda un/a %s en su inventario.", GetItemName(itemid));
			PlayerCmeMessage(playerid, 15.0, 5000, str);
	    }
		else
		{
		    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/inv)entario [comando] - {5CCAF1}[Comandos]:{C8C8C8} guardar - guardari");
		}
	}
	return 1;
}

DestroyPlayerInventory(playerid)
{
	if(PlayerInfo[playerid][pContainerSQLID] > 0 && PlayerInfo[playerid][pContainerID] > 0)
	{
		Container_Destroy(PlayerInfo[playerid][pContainerID]);
	}
	return 1;
}

Dialog:Dlg_Show_Inv_Container(playerid, response, listitem, inputtext[])
{
	new container_id = Container_Selection[playerid][csId];

	ResetContainerSelection(playerid);

	if(response)
	{
        new itemid,
            itemparam,
            str[128],
            free_hand = SearchFreeHand(playerid);

		if(free_hand == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el item ya que tienes ambas manos ocupadas.");

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SetHandItemAndParam(playerid, free_hand, itemid, itemparam); // Creaci贸n l贸gica y grafica en la mano.

            SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);

			format(str, sizeof(str), "Toma un/a %s de su inventario y lo sostiene en una de sus manos.", GetItemName(itemid));
			PlayerCmeMessage(playerid, 15.0, 5000, str);
		}
		else
		{
	        SendClientMessage(playerid, COLOR_YELLOW2, "Inventario vac韔 o el slot especificado es inv醠ido.");
		}
	}
	return 1;
}

//============================[FIN EXPERIMENTAL]================================
