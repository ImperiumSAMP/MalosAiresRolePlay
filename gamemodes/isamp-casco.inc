#if defined _isamp_casco_included
	#endinput
#endif
#define _isamp_casco_included

//=============================SISTEMA DE CASCO=================================

//===============================CONSTANTES=====================================

//==============================DATA STORAGE====================================

//===============================FUNCIONES======================================

forward HelmetToHead(playerid, itemid); // Ubica visiblemente el casco en la cabeza del jugador.
forward DeleteItemFromHead(playerid);// Borra visiblemente el item de la cabeza del jugador.

//======================IMPLEMENTACION DE FUNCIONES=============================

stock DeleteItemFromHead(playerid)
{
	RemovePlayerAttachedObject(playerid, 8);
	return 1;
}

stock HelmetToHead(playerid, itemid)
{
    if(SearchInvForItem(playerid, itemid) != -1)
	{
		switch(itemid)
		{
		    case ITEM_ID_CASCOCOMUN: SetPlayerAttachedObject(playerid, 8, 18645, BONE_ID_HEAD, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case ITEM_ID_CASCOMOTOCROSS: SetPlayerAttachedObject(playerid, 8, 18976, BONE_ID_HEAD, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case ITEM_ID_CASCOROJO: SetPlayerAttachedObject(playerid, 8, 18977, BONE_ID_HEAD, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case ITEM_ID_CASCOBLANCO: SetPlayerAttachedObject(playerid, 8, 18978, BONE_ID_HEAD, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case ITEM_ID_CASCOROSA: SetPlayerAttachedObject(playerid, 8, 18979, BONE_ID_HEAD, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
			default: return 1;
	    }
	    EditAttachedObject(playerid, 8);
	}
	return 1;
}

//===================================COMANDOS===================================

CMD:cas(playerid, params[])
{
	cmd_casco(playerid, params);
	return 1;
}

CMD:casco(playerid, params[])
{
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
		
    new casco1 = SearchInvForItem(playerid, ITEM_ID_CASCOCOMUN),
        casco2 = SearchInvForItem(playerid, ITEM_ID_CASCOMOTOCROSS),
		casco3 = SearchInvForItem(playerid, ITEM_ID_CASCOROJO),
		casco4 = SearchInvForItem(playerid, ITEM_ID_CASCOBLANCO),
		casco5 = SearchInvForItem(playerid, ITEM_ID_CASCOROSA),
		handitem = GetHandItem(playerid);
		
    if(casco1 == -1 && casco2 == -1 && casco3 == -1 && casco4 == -1 && casco5 == -1) // Caso de que no tenga un casco puesto en la cabeza (en el inventario).
    {
        new handparam = GetHandParam(playerid);
        if(handitem == ITEM_ID_CASCOCOMUN || handitem == ITEM_ID_CASCOMOTOCROSS || handitem == ITEM_ID_CASCOROJO ||
			handitem == ITEM_ID_CASCOBLANCO || handitem == ITEM_ID_CASCOROSA) // Entonces analizamos si uso /casco porque tenia uno en las manos.
		{
			new validslot = SearchInvFreeSlot(playerid);
			if(validslot == -1)
			    return SendClientMessage (playerid, COLOR_YELLOW2, "¡No tienes espacio en el inventario para equiparte el casco!");
			SetHandItemAndParam(playerid, 0, 0);
			DeleteHandItem(playerid);
            SetInvItemAndParam(playerid, validslot, handitem, handparam);
            HelmetToHead(playerid, handitem);
		    new string[124];
		    format(string, sizeof(string), "se coloca el %s en la cabeza.", GetItemName(handitem));
	    	PlayerActionMessage(playerid, 15.0, string);
		} else
		    return SendClientMessage (playerid, COLOR_YELLOW2, "¡No tienes ningún casco en tus manos!");
	} else
	    {
	        if(handitem != 0)
	            return SendClientMessage (playerid, COLOR_YELLOW2, "No puedes sacarte el casco ya que tienes algo en tus manos.");

			new invitem, invparam, invslot;
			if(casco1 != -1) { invitem = ITEM_ID_CASCOCOMUN; invslot = casco1; }
			else if(casco2 != -1) { invitem = ITEM_ID_CASCOMOTOCROSS; invslot = casco2; }
			else if(casco3 != -1) { invitem = ITEM_ID_CASCOROJO; invslot = casco3; }
			else if(casco4 != -1) { invitem = ITEM_ID_CASCOBLANCO; invslot = casco4; }
			else if(casco5 != -1) { invitem = ITEM_ID_CASCOROSA; invslot = casco5; }
			
			invparam = GetInvParam(playerid, invslot);
			SetInvItemAndParam(playerid, invslot, 0, 0);
			DeleteItemFromHead(playerid);
			SetHandItemAndParam(playerid, invitem, invparam);
			LoadHandItem(playerid);
   			new string[124];
		    format(string, sizeof(string), "sostiene su %s en su mano derecha.", GetItemName(invitem));
	    	PlayerActionMessage(playerid, 15.0, string);
		}
	return 1;
}


