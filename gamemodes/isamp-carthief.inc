#if defined _isamp_carthief_included
	#endinput
#endif
#define _isamp_carthief_included

//=========================SISTEMA DE ROBO DE AUTOS=============================

//=================================CONSTANTES===================================

#define POS_CAR_DEMOLITION_X 	2199.0042
#define POS_CAR_DEMOLITION_Y	-2033.5476
#define POS_CAR_DEMOLITION_Z 	13.5339
	
//============================FUNCIONES PUBLICAS================================

//============================FUNCIONES INTERNAS================================

//=========================IMPLEMENTACIÓN DE FUNCIONES==========================

//================================COMANDOS======================================

CMD:demoler(playerid, params[])
{
	new
		vehicleid = GetPlayerVehicleID(playerid),
		Float:vehiclehp,
		repuestos;

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para poder robar autos.");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el asiento de conductor de un vehículo!");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, POS_CAR_DEMOLITION_X, POS_CAR_DEMOLITION_Y, POS_CAR_DEMOLITION_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes demoler un auto robado el cualquier lugar.");
	if(VehicleInfo[vehicleid][VehType] != VEH_OWNED)
	    return SendClientMessage(playerid, COLOR_WHITE, "Comprador: Olvídalo, ese vehículo no me interesa. (OOC: Solo puedes demoler vehículos personales)");
	if(playerHasCarKey(playerid, vehicleid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes demoler un auto del cual tienes las llaves.");
	if(GetHandItem(playerid) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes espacio en tus manos para agarrar los repuestos.");

 	GetVehicleHealth(vehicleid, vehiclehp);
    repuestos = (floatround(vehiclehp, floatround_round) / 125) * 2;
    SetHandItemAndParam(playerid, ITEM_ID_REPUESTOAUTO, repuestos);
    LoadHandItem(playerid);
    SetVehicleToRespawn(vehicleid);
    PlayerActionMessage(playerid, 15.0, "Le entrega el vehículo al empleado del compactador de basura para que lo desarme y demuele.");
    SendFMessage(playerid, COLOR_WHITE, "Comprador: Bien, aquí tienes %d piezas de repuesto que pude sacarle al auto", repuestos);
	// fijaer cooldown para volver a demoler? o un maximo de hasta X por payday (con o sin cooldown entre demolers?) Mismo para /puente
	// Congelar auto en 9999.9999.9999 por X tiempo? o respawnear al toque.
	return 1;
}

CMD:ganzua(playerid, params[])
{
	new
		vehicleid = GetClosestVehicle(playerid, 4.0),
   	    Float:pos[3],
	    location[MAX_ZONE_NAME];

	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes la experiencia necesaria para poder robar autos.");
	if(IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes forzar una cerradura estando arriba de un vehiculo!");
	if(GetHandItem(playerid) != ITEM_ID_BARRETA)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una barreta en tus manos.");
	if(vehicleid == INVALID_VEHICLE_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estas cerca de ningun vehiculo.");
	if(VehicleInfo[vehicleid][VehLocked] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Las puertas está abiertas.");

  	TogglePlayerControllable(playerid, false);
  	PlayerActionMessage(playerid, 15.0, "Toma una herramienta y comienza a realizar unas maniobras sobre la manija de la puerta del vehículo");
    SendClientMessage(playerid, COLOR_WHITE, "Forzando la cerradura, aguarda un momento...");
    SetTimerEx("UsarGanzua", 20 * 1000, 0, "ii", playerid, vehicleid);
    
    if(random(10) > 4)
    {
		SendClientMessage(playerid, COLOR_WHITE, "Un civil te vió forzando la cerradura y alertó a la policía. ¡Apurate o te atraparán!");
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
		foreach(new i : Player)
		{
		    if(isPlayerCopOnDuty(i))
		    {
		        SendClientMessage(i, COLOR_PMA, "[Dpto. de policía]: un civil ha reportado un robo de auto. Hemos marcado la ubicacion en el radar.");
                SendFMessage(i, COLOR_PMA, "[Dpto. de policía]: El modelo del vehículo es un %s y la zona es %s.", GetVehicleName(vehicleid), location);
                SetPlayerCheckpoint(i, pos[0], pos[1], pos[2], 3.0);
			}
		}
	}
	return 1;
}

forward UsarGanzua(playerid, vehicleid);
public UsarGanzua(playerid, vehicleid)
{
    TogglePlayerControllable(playerid, true);

	if(GetHandItem(playerid) != ITEM_ID_BARRETA)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una barreta en tus manos.");

	if(random(10) > 4)
	{
		if(GetHandParam(playerid) == 1)
		{
			SetHandItemAndParam(playerid, 0, 0);
			DeleteHandItem(playerid);
		} else
			SetHandItemAndParam(playerid, ITEM_ID_BARRETA, GetHandParam(playerid) - 1);
	    SendClientMessage(playerid, COLOR_WHITE, "La barreta cedió y se rompió.");
	}
	else
	{
 		VehicleInfo[vehicleid][VehLocked] = 0;
 		SendClientMessage(playerid, COLOR_WHITE, "Forzaste con exito la cerradura.");
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
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el asiento de conductor de un vehículo!");
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(VehicleInfo[vehicleid][VehEngine] == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El motor del vehículo ya se encuentra prendido.");
	    
  	TogglePlayerControllable(playerid, false);
  	PlayerActionMessage(playerid, 15.0, "Se inclina hacia abajo en el asiento del conductor y realiza unas maniobras");
    SendClientMessage(playerid, COLOR_WHITE, "Desarmas la parte inferior del tablero y trabajas en el cableado. Aguarda un momento...");
    SetTimerEx("PuenteMotor", 20 * 1000, 0, "ii", playerid, vehicleid);
	return 1;
}

forward PuenteMotor(playerid, vehicleid);
public PuenteMotor(playerid, vehicleid)
{
    TogglePlayerControllable(playerid, true);
    if(random(10) > 4)
    {
        SetEngine(vehicleid, 1);
        SendClientMessage(playerid, COLOR_WHITE, "¡Perfecto! Conectas los cables correctos y el motor enciende. ¡Huye de aquí!");
	}
	else
		SendClientMessage(playerid, COLOR_WHITE, "Mala suerte, has fallado en tu intento por conectar los cables adecuados.");
	return 1;
}

