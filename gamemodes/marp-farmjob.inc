#if defined _marp_farmjob_included
	#endinput
#endif
#define _marp_farmjob_included

#define JOB_FARM_MAXPRODS       20
#define JOB_FARM_PRODVALUE      90

new Float:JOB_FARM_POS[][3] = {
	/* Puntos de recolección */
    {-183.3806,-79.5342,4.0951},
    {-219.4385,-68.9600,4.0950},
    {-259.0175,-56.5420,4.0950},
    {-252.6187,4.2398,3.4380},
    {-202.4771,12.5146,4.0940},
    {-158.9618,-3.1515,4.0950},
    {-135.8669,48.6686,4.0950},
    {-177.7080,69.3499,4.0969},
    {-224.9103,89.6337,3.2921},
    {-200.7006,153.6604,6.4168},
    {-128.2134,131.4797,4.2139},
    {20.5564,49.0627,4.0969},
    {63.5040,3.6344,2.1527},
    {32.9894,-61.0243,2.8295},
    {-4.2428,-21.0476,4.0951},
    {-2.5429,-56.3804,4.0950},
    {-32.1306,-102.6864,4.0953},
    /* Punto de entrega */
    {-36.8495,61.0254,4.0947}
};

FarmJob_StartWork(playerid)
{
	if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_FARM)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a una cosechadora!");

	SendClientMessage(playerid, COLOR_WHITE, "Dirígete a los puntos rojos para cosechar, al finalizar deberás traer la cosecha y tipear /terminar para descargarla.");
    SendClientMessage(playerid, COLOR_WHITE, "Puedes descargar los materiales cuando quieras, pero te pagarán acorde a la cantidad y no podras volver a trabajar durante este día de pago.");
	new rCP = -1;
	while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid])
	{
		rCP = random(sizeof(JOB_FARM_POS));
	}
	LastCP[playerid] = rCP;
	SetPlayerCheckpoint(playerid, JOB_FARM_POS[rCP][0], JOB_FARM_POS[rCP][1], JOB_FARM_POS[rCP][2], 5.4);
	jobDuty[playerid] = true;
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	SetEngine(GetPlayerVehicleID(playerid), 1);
	return 1;
}

FarmJob_FinishWork(playerid)
{
	if(!PlayerToPoint(20.0, playerid, JOB_FARM_POS[17][0], JOB_FARM_POS[17][1], JOB_FARM_POS[17][2]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve y descarga los productos en la zona indicada!");
	if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_FARM)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar adentro de una cosechadora!");

	PlayerActionMessage(playerid, 15.0, "descarga todo el producto y estaciona la cosechadora.");
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Has recolectado %d toneladas por lo tanto recibirás $%d en el próximo día de pago.", CollectedProds[playerid], CollectedProds[playerid] * JOB_FARM_PRODVALUE);
	PlayerInfo[playerid][pCantWork] = 1;
	LastCP[playerid] = -1;
	PlayerJobInfo[playerid][pWorkingHours]++;
	strmid(PlayerJobInfo[playerid][pLastWorked], GetDateString(), 0, strlen(GetDateString()));
	PlayerInfo[playerid][pPayCheck] += CollectedProds[playerid] * JOB_FARM_PRODVALUE;
	CollectedProds[playerid] = 0;
	jobBreak[playerid] = 80;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return 1;
}

FarmJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_FARM && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_FARM)
	    return 1;
	return 0;
}

FarmJob_PlayerEnterCheckpoint(playerid)
{
	if(CollectedProds[playerid] < JOB_FARM_MAXPRODS)
	{
	   	new rCP = -1, str[128];
		while(rCP == -1 || rCP == LastCP[playerid])
		{
			rCP = random(sizeof(JOB_FARM_POS) - 2);
		}
		LastCP[playerid] = rCP;
	    CollectedProds[playerid]++;
	    format(str, sizeof(str), "Producto: %d/%d", CollectedProds[playerid], JOB_FARM_MAXPRODS);
		GameTextForPlayer(playerid, str, 1400, 1);
		if(CollectedProds[playerid] == JOB_FARM_MAXPRODS)
		{
		 	SetPlayerCheckpoint(playerid, JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][0], JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][1], JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][2], 5.4);
			SendClientMessage(playerid, COLOR_WHITE, "¡Has terminado con tu trabajo!, ahora vé y descarga el material (/terminar).");
		}
		else
		{
		    SetPlayerCheckpoint(playerid, JOB_FARM_POS[rCP][0], JOB_FARM_POS[rCP][1], JOB_FARM_POS[rCP][2], 5.4);
		}
	}
	return 1;
}

