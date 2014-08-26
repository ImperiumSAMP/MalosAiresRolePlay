#if defined _isamp_maletin_included
	#endinput
#endif
#define _isamp_maletin_included

//=============================SISTEMA DE MALETINES=============================

//================================CONSTANTES====================================

#define MAX_DINERO_MALETIN 200000

//===============================FUNCIONES======================================

forward LoadBreifCaseForPlayer(playerid); // Carga el objeto visible del maletin al jugador.
forward DeleteBriefCaseForPlayer(playerid); // Borra el objeto visible del jugador.
forward GiveBriefCasePlayerToPlayer(playerid, targetid); // Pasa el objeto visible de un jugador a otro.

//======================IMPLEMENTACION DE FUNCIONES=============================

stock LoadBriefCaseForPlayer(playerid)
{
	if(SearchInvForItem(playerid, 55) != -1)
	    SetPlayerAttachedObject(playerid, 9, 1210, 5, 0.301999, 0.082999, -0.012000, 0.000000, -90.599975, -0.999999, 1.000000, 1.000000, 1.000000);
	return 1;
}

stock DeleteBriefCaseForPlayer(playerid)
{
	RemovePlayerAttachedObject(playerid, 9);
	return 1;
}

stock GiveBriefCasePlayerToPlayer(playerid, targetid)
{
    SetPlayerAttachedObject(targetid, 7, 1210, 5, 0.301999, 0.082999, -0.012000, 0.000000, -90.599975, -0.999999, 1.000000, 1.000000, 1.000000);
    RemovePlayerAttachedObject(playerid, 7);
    return 1;
}

//================================COMANDOS======================================

CMD:maletin(playerid, params[])
{
	new
	    command[40],
	    amount,
	    validslot = SearchInvForItem(playerid, 55);

	if(validslot == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de un maletín en tu inventario.");
		
	if(sscanf(params, "s[40]i", command, amount))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /maletin [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} retirar [dinero] - guardar [dinero]");

	} else if(strcmp(command, "retirar", true) == 0) {
		
		    new briefCaseMoney = GetInvParam(playerid, validslot);
		    if(amount <= 0 || amount > briefCaseMoney)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inválida.");
		        
		    GivePlayerCash(playerid, amount);
			SetInvItemAndParam(playerid, validslot, 55, briefCaseMoney - amount);
			PlayerActionMessage(playerid, 15.0, "abre su maletín y retira algo de su interior.");
			
	} else if(strcmp(command, "guardar", true) == 0) {
		
	    new briefCaseMoney = GetInvParam(playerid, validslot);
	    if(amount <= 0 || amount > GetPlayerCash(playerid))
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inválida.");
		if(amount + briefCaseMoney > MAX_DINERO_MALETIN)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tanto dinero no entra en el maletín!");

	    GivePlayerCash(playerid, -amount);
		SetInvItemAndParam(playerid, validslot, 55, briefCaseMoney + amount);
		PlayerActionMessage(playerid, 15.0, "abre su maletín y guarda algo en su interior.");
	}
	return 1;
}
