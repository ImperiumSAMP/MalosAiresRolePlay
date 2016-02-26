#if defined _isamp_carthief_included
	#endinput
#endif
#define _isamp_carthief_included

//=========================SISTEMA DE ROBO DE AUTOS=============================

//=================================CONSTANTES===================================

#define POS_CAR_DEMOLITION_X 	2199.0042
#define POS_CAR_DEMOLITION_Y	-2033.5476
#define POS_CAR_DEMOLITION_Z 	13.5339

#define STOLEN_CAR_MISSING_TIME 60 // En minutos, tiempo hasta que vuelva a aparecer una vez desarmado.

#define CMD_BARRETA_COOLDOWN    50 // En minutos
#define CMD_GANZUA_COOLDOWN     40 // En minutos
#define CMD_PUENTE_COOLDOWN     50 // En minutos
#define CMD_DESARMAR_COOLDOWN   60 // En minutos
	
//============================FUNCIONES PUBLICAS================================

forward HideStolenCar(vehicleid); // Hace desaparecer el auto durante STOLEN_CAR_MISSING_TIME minutos.

//============================FUNCIONES INTERNAS================================

forward UsarBarreta(playerid, vehicleid);
forward UsarGanzua(playerid, vehicleid);
forward PuenteMotor(playerid, vehicleid);

//=========================IMPLEMENTACIÓN DE FUNCIONES==========================

public UsarBarreta(playerid, vehicleid)
{
	new hand;
	
    TogglePlayerControllable(playerid, true);
    SetPVarInt(playerid, "disabled", DISABLE_NONE);

    hand = SearchHandsForItem(playerid, ITEM_ID_BARRETA);
    if(hand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una barreta en alguna de tus manos.");

	if(random(10) > 4)
	{
		if(GetHandParam(playerid, hand) == 1)
			SetHandItemAndParam(playerid, hand, 0, 0);
		else
			SetHandItemAndParam(playerid, hand, ITEM_ID_BARRETA, GetHandParam(playerid, hand) - 1);
	    SendClientMessage(playerid, COLOR_WHITE, "La barreta cedió y se rompió.");
	}
	else
	{
 		VehicleInfo[vehicleid][VehLocked] = 0;
 		SendClientMessage(playerid, COLOR_WHITE, "Forzaste con éxito la cerradura.");
		if(ThiefJobInfo[playerid][pFelonLevel] == 7)
 			GiveJobExp(playerid, JOB_FELON, 2);
        ThiefJobInfo[playerid][pForceDoorLimit] = CMD_BARRETA_COOLDOWN * 60;
 	}
	return 1;
}

public UsarGanzua(playerid, vehicleid)
{
    new hand;

    TogglePlayerControllable(playerid, true);
    SetPVarInt(playerid, "disabled", DISABLE_NONE);

    hand = SearchHandsForItem(playerid, ITEM_ID_GANZUA);
    if(hand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una ganzúa en alguna de tus manos.");

	if(random(10) > 7)
	{
		if(GetHandParam(playerid, hand) == 1)
			SetHandItemAndParam(playerid, hand, 0, 0);
		else
			SetHandItemAndParam(playerid, hand, ITEM_ID_GANZUA, GetHandParam(playerid, hand) - 1);
	    SendClientMessage(playerid, COLOR_WHITE, "La ganzúa cedió y se rompió.");
	}
	else
	{
 		VehicleInfo[vehicleid][VehLocked] = 0;
 		SendClientMessage(playerid, COLOR_WHITE, "Forzaste con éxito la cerradura.");
		if(ThiefJobInfo[playerid][pFelonLevel] == 7)
 			GiveJobExp(playerid, JOB_FELON, 2);
        ThiefJobInfo[playerid][pForceDoorLimit] = CMD_GANZUA_COOLDOWN * 60;
 	}
	return 1;
}

public PuenteMotor(playerid, vehicleid)
{
    TogglePlayerControllable(playerid, true);
    SetPVarInt(playerid, "disabled", DISABLE_NONE);

    if(random(10) > 4)
    {
        SetEngine(vehicleid, 1);
        SendClientMessage(playerid, COLOR_WHITE, "¡Perfecto! Conectas los cables correctos y el motor enciende. ¡Huye de aquí!");
		if(ThiefJobInfo[playerid][pFelonLevel] == 7)
 			GiveJobExp(playerid, JOB_FELON, 2);
        ThiefJobInfo[playerid][pForceEngineLimit] = CMD_PUENTE_COOLDOWN * 60;
	}
	else
		SendClientMessage(playerid, COLOR_WHITE, "Mala suerte, has fallado en tu intento por conectar los cables correctos.");
	return 1;
}

stock HideStolenCar(vehicleid)
{
	SetVehicleToRespawn(vehicleid); // Respawn para sacar a los jugadores del vehículo (no funciona loopear y sacar a los que esten en el vehículo)
    SetVehiclePos(vehicleid, 8888.0, 8888.0, 888.0); // Lo hacemos desaparecer un rato
    SetTimerEx("respawnVeh", STOLEN_CAR_MISSING_TIME * 60 * 1000, false, "i", vehicleid);
}

//================================COMANDOS======================================

CMD:barreta(playerid, params[])
{
	new vehicleid = GetClosestVehicle(playerid, 4.0),
   	    Float:pos[3],
	    location[MAX_ZONE_NAME];

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para utilizar este comando.");
	if(ThiefJobInfo[playerid][pForceDoorLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a forzar una cerradura.", ThiefJobInfo[playerid][pForceDoorLimit] / 60);
	    return 1;
	}
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacerlo en este momento!");
	if(IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes forzar una cerradura estando arriba del vehiculo!");
	if(SearchHandsForItem(playerid, ITEM_ID_BARRETA) == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una barreta en alguna de tus manos.");
	if(vehicleid == INVALID_VEHICLE_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estas cerca de ningún vehículo.");
	if(VehicleInfo[vehicleid][VehLocked] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Las puertas están abiertas.");

  	TogglePlayerControllable(playerid, false);
  	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
  	PlayerActionMessage(playerid, 15.0, "toma una herramienta y comienza a realizar unas maniobras sobre la manija de la puerta del vehículo.");
    GameTextForPlayer(playerid, "Forzando cerradura, aguarda...", 20 * 1000, 4);
    SetTimerEx("UsarBarreta", 20 * 1000, 0, "ii", playerid, vehicleid);
    
    if(random(10) > 4)
    {
		SendClientMessage(playerid, COLOR_WHITE, "Un civil te vió forzando la cerradura y alertó a la policía. ¡Apúrate o te atraparán!");
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
		foreach(new i : Player)
		{
		    if(isPlayerCopOnDuty(i))
		    {
		        SendClientMessage(i, COLOR_PMA, "[Dpto. de policía]: Un civil ha reportado un robo de auto en curso. Hemos marcado la ubicación en el radar.");
                SendFMessage(i, COLOR_PMA, "[Dpto. de policía]: El modelo del vehículo es un %s y la zona es %s.", GetVehicleName(vehicleid), location);
                SetPlayerCheckpoint(i, pos[0], pos[1], pos[2], 3.0);
			}
		}
	}
	return 1;
}

CMD:ganzua(playerid, params[])
{
    new vehicleid = GetClosestVehicle(playerid, 4.0),
   	    Float:pos[3],
	    location[MAX_ZONE_NAME];

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para utilizar este comando.");
	if(ThiefJobInfo[playerid][pForceDoorLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a forzar una cerradura.", ThiefJobInfo[playerid][pForceDoorLimit] / 60);
	    return 1;
	}
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacerlo en este momento!");
	if(IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes forzar una cerradura estando arriba del vehiculo!");
	if(SearchHandsForItem(playerid, ITEM_ID_GANZUA) == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una ganzúa en alguna de tus manos.");
	if(vehicleid == INVALID_VEHICLE_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estas cerca de ningún vehículo.");
	if(VehicleInfo[vehicleid][VehLocked] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Las puertas están abiertas.");

  	TogglePlayerControllable(playerid, false);
  	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
  	PlayerActionMessage(playerid, 15.0, "toma una herramienta y comienza a realizar unas maniobras sobre la manija de la puerta del vehículo.");
    GameTextForPlayer(playerid, "Forzando cerradura, aguarda...", 40 * 1000, 4);
    SetTimerEx("UsarBarreta", 40 * 1000, 0, "ii", playerid, vehicleid);

    if(random(10) > 2)
    {
		SendClientMessage(playerid, COLOR_WHITE, "Un civil te vió forzando la cerradura y alertó a la policía. ¡Apúrate o te atraparán!");
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
		foreach(new i : Player)
		{
		    if(isPlayerCopOnDuty(i))
		    {
		        SendClientMessage(i, COLOR_PMA, "[Dpto. de policía]: Un civil ha reportado un robo de auto en curso. Hemos marcado la ubicación en el radar.");
                SendFMessage(i, COLOR_PMA, "[Dpto. de policía]: El modelo del vehículo es un %s y la zona es %s.", GetVehicleName(vehicleid), location);
                SetPlayerCheckpoint(i, pos[0], pos[1], pos[2], 3.0);
			}
		}
	}
	return 1;
}

CMD:puente(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para poder robar autos.");
	if(ThiefJobInfo[playerid][pForceEngineLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a puentear el arranque.", ThiefJobInfo[playerid][pForceEngineLimit] / 60);
	    return 1;
	}
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacerlo en este momento!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el asiento de conductor de un vehículo!");
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(VehicleInfo[vehicleid][VehEngine] == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El motor del vehículo ya se encuentra prendido.");
	    
  	TogglePlayerControllable(playerid, false);
  	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
  	PlayerActionMessage(playerid, 15.0, "se inclina hacia abajo en el asiento del conductor y realiza unas maniobras.");
  	GameTextForPlayer(playerid, "Desarmando tambor de arranque, aguarda...", 20 * 1000, 4);
    SetTimerEx("PuenteMotor", 20 * 1000, 0, "ii", playerid, vehicleid);
	return 1;
}

CMD:desarmar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		Float:vehiclehp,
		freehand,
		repuestos;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para utilizar este comando.");
	if(ThiefJobInfo[playerid][pDesarmCarLimit] != 0)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a desarmar un vehículo.", ThiefJobInfo[playerid][pDesarmCarLimit] / 60);
	    return 1;
	}
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacerlo en este momento!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el asiento del conductor de un vehículo!");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, POS_CAR_DEMOLITION_X, POS_CAR_DEMOLITION_Y, POS_CAR_DEMOLITION_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes dirigirte al desarmadero con el vehículo robado.");
	if(VehicleInfo[vehicleid][VehType] != VEH_OWNED)
	    return SendClientMessage(playerid, COLOR_WHITE, "Comprador: Olvídalo, ese vehículo no me interesa. (OOC: Solo puedes desarmar vehículos personales)");
	if(playerHasCarKey(playerid, vehicleid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes desarmar un auto del cual tienes las llaves.");
	freehand = SearchFreeHand(playerid);
	if(freehand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes tus manos ocupadas y no puedes agarrar los repuestos.");

 	GetVehicleHealth(vehicleid, vehiclehp);
    repuestos = floatround(vehiclehp) / GetItemPrice(ITEM_ID_REPUESTOAUTO) * 3; // Entrega una cantidad de repuestos proporcional al buen estado (hp) del auto
    SetHandItemAndParam(playerid, freehand, ITEM_ID_REPUESTOAUTO, repuestos);
    HideStolenCar(vehicleid);
    PlayerActionMessage(playerid, 15.0, "le entrega el vehículo al empleado del compactador de basura para que lo desarme y demuela.");
    SendFMessage(playerid, COLOR_WHITE, "Comprador: Bien, aquí tienes %d piezas de repuesto que pude sacarle al auto.", repuestos);
    ThiefJobInfo[playerid][pDesarmCarLimit] = CMD_DESARMAR_COOLDOWN * 60;
	return 1;
}
