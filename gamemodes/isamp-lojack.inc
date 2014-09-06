#if defined _isamp_lojack_included
	#endinput
#endif
#define _isamp_lojack_included

//============================SISTEMA DE GPS LOJACK=============================

//================================CONSTANTES====================================

#define PRICE_GPS   		500

//==============================DATA STORAGE====================================

//===============================FUNCIONES======================================

forward FindGps(playerid);

//======================IMPLEMENTACION DE FUNCIONES=============================

public FindGps(playerid)
{
	DisablePlayerCheckpoint(playerid);
	return 1;
}

//================================COMANDOS======================================

CMD:lojack(playerid, params[])
{
	new
		vehicleid,
		Float: X,
		Float: Y,
		Float: Z;

	if(sscanf(params, "i", vehicleid))
		return SendClientMessage (playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /lojack [ID vehículo]");
    if(!playerOwnsCar(playerid, vehicleid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El vehiculo no te pertenece.");
    if(PlayerInfo[playerid][pPhoneNumber] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Requieres de un telefono para utilizar el Lojack!");
	if(GetPlayerCash(playerid) < PRICE_GPS)
		return SendClientMessage (playerid, COLOR_YELLOW2, "No tienes dinero suficiente para rastrear el vehículo. ($500)");

	foreach(new i : Player)
	{
 		if(IsPlayerInVehicle(i, vehicleid))
   			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes localizar tu vehiculo en este momento.");
	}

	GivePlayerCash(playerid, -PRICE_GPS);
	GetVehiclePos(vehicleid, X, Y, Z);
	SetPlayerCheckpoint (playerid, X, Y, Z, 3);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡Lograste rastrear el vehículo!");
	SetTimerEx("FindGps", 60 * 1000, false, "i", playerid);
	return 1;
}

