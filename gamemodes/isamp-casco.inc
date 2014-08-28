#if defined _isamp_casco_included
	#endinput
#endif
#define _isamp_casco_included

//=============================SISTEMA DE CASCO=============================
new
    //Casco de moto
	bool:HelmetB[MAX_PLAYERS];

//===============================FUNCIONES======================================

forward LoadHelmetForPlayer(playerid, itemid); // Carga el objeto visible del casco al jugador.
forward DeleteHelmetForPlayer(playerid); // Borra el objeto visible del jugador.

//======================IMPLEMENTACION DE FUNCIONES=============================
stock DeleteHelmetForPlayer(playerid)
{
	RemovePlayerAttachedObject(playerid, 8);
	RemovePlayerAttachedObject(playerid, 6);
	return 1;
}

stock LoadHelmetForPlayer(playerid, itemid)
{
	if(SearchInvForItem(playerid, itemid) != -1)
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
		new string[64];
	    format(string, sizeof(string), "se coloca el %s.", GetItemName(itemid));
    	PlayerActionMessage(playerid, 15.0, string);
	    EditAttachedObject(playerid, 8);
    	HelmetB[playerid] = true;
	}
	return 1;
}

stock MoveHelmetHeadToHand(playerid, itemid)
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
	    new string[64];
	    format(string, sizeof(string), "se quita el %s y lo sostiene en su mano derecha.", GetItemName(itemid));
    	PlayerActionMessage(playerid, 15.0, string);
    	RightHand[playerid] = itemid; //a futuro PlayerInfo[playerid][RightHand]
    	HelmetB[playerid] = false;
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
    if(SearchInvForItem(playerid, 56) == -1 && SearchInvForItem(playerid, 57) == -1 &&
	   SearchInvForItem(playerid, 58) == -1 && SearchInvForItem(playerid, 59) == -1 &&
	   SearchInvForItem(playerid, 60) == -1)
		return SendClientMessage (playerid, COLOR_LIGHTBLUE, "¡No tienes un casco!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    /*-------------*/
    new item;
    if(HelmetB[playerid])
    
        MoveHelmetHeadToHand(playerid, item);
	else
		LoadHelmetForPlayer(playerid, item);
	return 1;
}


