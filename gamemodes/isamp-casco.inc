#if defined _isamp_casco_included
	#endinput
#endif
#define _isamp_casco_included

//=============================SISTEMA DE CASCO=============================
new
    //Casco de moto
	bool:HelmetOnHead[MAX_PLAYERS];

//===============================FUNCIONES======================================

forward LoadHelmetForPlayer(playerid, itemid = -1); // Carga el objeto visible del casco a la mano del jugador. Se puede opcionalmente indicar cual es el casco pasandole la ID. Si no se sabe el casco se pasa -1.
forward DeleteHelmetForPlayer(playerid); // Borra el objeto visible del jugador.
forward GiveHelmetPlayerToPlayer(playerid, targetid, itemid); // Le pasa el casco visible de un jugador al otro.
forward HelmetToHead(playerid, itemid); // Ubica lógica y visiblemente el casco en la cabeza del jugador (si tiene uno).
forward HelmetToHand(playerid, itemid); // Ubica lógica y visiblemente el casco en la mano del jugador (si tiene uno)

//======================IMPLEMENTACION DE FUNCIONES=============================

stock DeleteHelmetForPlayer(playerid)
{
	if(HelmetOnHead[playerid] == true)
	{
		RemovePlayerAttachedObject(playerid, 8);
		HelmetOnHead[playerid] = false;
	}
	else
 		{
 		    RightHand[playerid] = -1;
			RemovePlayerAttachedObject(playerid, 6);
		}
	return 1;
}

stock LoadHelmetForPlayer(playerid, itemid = -1)
{
	if(itemid != -1)
	{
		if(SearchInvForItem(playerid, itemid) != -1)
		    HelmetToHand(playerid, itemid);
	} else
	    {
		    if(SearchInvForItem(playerid, ITEM_ID_CASCOCOMUN) != -1) HelmetToHand(playerid, ITEM_ID_CASCOCOMUN);
				else if(SearchInvForItem(playerid, ITEM_ID_CASCOMOTOCROSS) != -1) HelmetToHand(playerid, ITEM_ID_CASCOMOTOCROSS);
	  				else if(SearchInvForItem(playerid, ITEM_ID_CASCOROJO) != -1) HelmetToHand(playerid, ITEM_ID_CASCOROJO);
					else if(SearchInvForItem(playerid, ITEM_ID_CASCOBLANCO) != -1) HelmetToHand(playerid, ITEM_ID_CASCOBLANCO);
						else if(SearchInvForItem(playerid, ITEM_ID_CASCOROSA) != -1) HelmetToHand(playerid, ITEM_ID_CASCOROSA);
		}
	return 1;
}

stock GiveHelmetPlayerToPlayer(playerid, targetid, itemid)
{
	DeleteHelmetForPlayer(playerid);
	HelmetToHand(targetid, itemid);
	return 1;
}

stock HelmetToHead(playerid, itemid)
{
    if(SearchInvForItem(playerid, itemid) != -1 && RightHand[playerid] == itemid && HelmetOnHead[playerid] == false)
	{
	    DeleteHelmetForPlayer(playerid);
		switch(itemid)
		{
		    case 56: SetPlayerAttachedObject(playerid, 8, 18645, 2, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case 57: SetPlayerAttachedObject(playerid, 8, 18976, 2, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case 58: SetPlayerAttachedObject(playerid, 8, 18977, 2, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case 59: SetPlayerAttachedObject(playerid, 8, 18978, 2, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
		    case 60: SetPlayerAttachedObject(playerid, 8, 18979, 2, 0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000);
	    }
	    new string[124];
	    format(string, sizeof(string), "se coloca el %s.", GetItemName(itemid));
    	PlayerActionMessage(playerid, 15.0, string);
	    EditAttachedObject(playerid, 8);
	    RightHand[playerid] = -1;
    	HelmetOnHead[playerid] = true;
	}
	return 1;
}

stock HelmetToHand(playerid, itemid)
{
    if(SearchInvForItem(playerid, itemid) != -1)
	{
	    DeleteHelmetForPlayer(playerid);
		switch(itemid)
		{
		    case 56: SetPlayerAttachedObject(playerid, 6, 18645, 5, 0.070000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
		    case 57: SetPlayerAttachedObject(playerid, 6, 18976, 5, 0.070000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
		    case 58: SetPlayerAttachedObject(playerid, 6, 18977, 5, 0.070000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
		    case 59: SetPlayerAttachedObject(playerid, 6, 18978, 5, 0.070000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
		    case 60: SetPlayerAttachedObject(playerid, 6, 18979, 5, 0.070000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
	    }
	    new string[124];
	    format(string, sizeof(string), "sostiene su %s en su mano derecha.", GetItemName(itemid));
    	PlayerActionMessage(playerid, 15.0, string);
    	RightHand[playerid] = itemid; //a futuro PlayerInfo[playerid][RightHand]
    	HelmetOnHead[playerid] = false;
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
    new casco1 = SearchInvForItem(playerid, 56),
        casco2 = SearchInvForItem(playerid, 57),
		casco3 = SearchInvForItem(playerid, 58),
		casco4 = SearchInvForItem(playerid, 59),
		casco5 = SearchInvForItem(playerid, 60),
		item;
    if(casco1 == -1 && casco2 == -1 && casco3 == -1 && casco4 == -1 && casco5 == -1)
		return SendClientMessage (playerid, COLOR_YELLOW2, "¡No tienes un casco!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");

	if (casco1 != -1) item = GetInvItem(playerid, casco1);
		else if (casco2 != -1) item = GetInvItem(playerid, casco2);
			else if (casco3 != -1) item = GetInvItem(playerid, casco3);
				else if (casco4 != -1) item = GetInvItem(playerid, casco4);
					else if (casco5 != -1) item = GetInvItem(playerid, casco5);

    if(HelmetOnHead[playerid])
        HelmetToHand(playerid, item);
	else
		HelmetToHead(playerid, item);
	return 1;
}


