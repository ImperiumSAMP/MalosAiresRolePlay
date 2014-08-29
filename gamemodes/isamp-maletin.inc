#if defined _isamp_maletin_included
	#endinput
#endif
#define _isamp_maletin_included

//=============================SISTEMA DE MALETINES=============================

//================================CONSTANTES====================================

#define MAX_DINERO_MALETIN 200000

//===============================FUNCIONES======================================

forward BriefCaseToHand(playerid, targetid); // Crea el objeto visible en la mano del jugador.
forward GiveBriefCaseHandToHand(playerid, targetid); // Borra el objeto visible de un jugador y se lo asigna a otro.

//======================IMPLEMENTACION DE FUNCIONES=============================

stock BriefCaseToHand(playerid)
{
    SetPlayerAttachedObject(playerid, 6, 1210, 5, 0.301999, 0.082999, -0.012000, 0.000000, -90.599975, -0.999999, 1.000000, 1.000000, 1.000000);
    return 1;
}

stock GiveBriefCaseHandToHand(playerid, targetid)
{
	RemovePlayerAttachedObject(playerid, 6);
	SetPlayerAttachedObject(targetid, 6, 1210, 5, 0.301999, 0.082999, -0.012000, 0.000000, -90.599975, -0.999999, 1.000000, 1.000000, 1.000000);
	return 1;
}

//================================COMANDOS======================================

CMD:maletin(playerid, params[])
{
	new
	    command[40],
	    amount,
	    briefCaseMoney = GetHandParam(playerid);

	if(GetHandItem(playerid) != ITEM_ID_MALETIN)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de un maletín en tus manos.");
		
	if(sscanf(params, "s[40]i", command, amount))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /maletin [comando]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} retirar [dinero] - guardar [dinero]");

	} else if(strcmp(command, "retirar", true) == 0) {
		
		    if(amount <= 0 || amount > briefCaseMoney)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inválida.");
		        
		    GivePlayerCash(playerid, amount);
			SetHandItemAndParam(playerid, ITEM_ID_MALETIN, briefCaseMoney - amount);
			PlayerActionMessage(playerid, 15.0, "abre su maletín y retira algo de su interior.");
			ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
			
	} else if(strcmp(command, "guardar", true) == 0) {
		
	    if(amount <= 0 || amount > GetPlayerCash(playerid))
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Cantidad inválida.");
		if(amount + briefCaseMoney > MAX_DINERO_MALETIN)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tanto dinero no entra en el maletín!");

	    GivePlayerCash(playerid, -amount);
		SetHandItemAndParam(playerid, ITEM_ID_MALETIN, briefCaseMoney + amount);
		PlayerActionMessage(playerid, 15.0, "abre su maletín y guarda algo en su interior.");
		ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	}
	return 1;
}
