#if defined _marp_drugfjob_included
	#endinput
#endif
#define _marp_drugfjob_included

#define JOB_DRUGF_MAXPRODS      30
#define JOB_DRUGF_PRODVALUE     55

new Float:JOB_DRUGF_POS[][3] = {
 	/* Puntos de recolección */
    {-1169.2928,-933.8162,128.7808},
    {-1022.6741,-926.0404,128.7850},
    {-1013.9845,-1051.4232,128.7930},
    {-1182.5314,-1052.3065,128.7805},
    {-1185.0731,-1010.0791,128.7914},
    {-1110.0996,-923.5186,128.7824},
    {-1114.6896,-1051.2513,128.7912},
    {-1016.3898,-983.6778,128.7819},
    {-1125.3112,-1027.3689,128.7837},
    {-1151.9413,-944.1597,128.7837},
    {-1088.3264,-941.3833,128.7837},
    {-1039.1461,-996.3032,128.7837},
    {-1115.7479,-1026.9470,128.7837},
    {-1158.1211,-981.7162,128.7837},
    {-1048.6957,-987.6217,128.7837},
    {-1080.2288,-994.1992,128.7837},
    /* Punto de entrega */
    {-1056.1754,-1195.4763,128.6771}
};

DrugfJob_StartWork(playerid)
{
	if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_DRUGF)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a una cosechadora!");

	SendClientMessage(playerid, COLOR_WHITE, "Dirígete a los puntos rojos para cosechar, al finalizar deberás traer la materia prima y tipear /terminar.");
	SendClientMessage(playerid, COLOR_WHITE, "Solo recibirás la paga si terminas completamente con tu trabajo.");
	new rCP = -1;
	while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid])
	{
		rCP = random(sizeof(JOB_DRUGF_POS));
	}
	LastCP[playerid] = rCP;
	SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], 5.4);
	jobDuty[playerid] = true;
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	SetEngine(GetPlayerVehicleID(playerid), 1);
	return 1;
}

DrugfJob_FinishWork(playerid)
{
	if(!PlayerToPoint(20.0, playerid, JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][0], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][1], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][2]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve y descarga los productos en la zona indicada!");
    if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_DRUGF)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en una cosechadora!");
    if(LastCP[playerid] != sizeof(JOB_DRUGF_POS) - 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No has terminado con tu trabajo!, vé y continua cosechando.");

	PlayerActionMessage(playerid, 15.0, "descarga el producto y estaciona la cosechadora.");
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Has recolectado 1 bolsa de materia prima, por lo tanto recibes $%d.", CollectedProds[playerid] * JOB_DRUGF_PRODVALUE);
    PlayerInfo[playerid][pCantWork] = 1;
    LastCP[playerid] = -1;
    ServerInfo[sDrugRawMats] += 1;
    GivePlayerCash(playerid, CollectedProds[playerid] * JOB_DRUGF_PRODVALUE);
    CollectedProds[playerid] = 0;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return 1;
}

DrugfJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_DRUGF && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_DRUGF)
	    return 1;
	return 0;
}

DrugfJob_PlayerEnterCheckpoint(playerid)
{
	if(CollectedProds[playerid] < JOB_DRUGF_MAXPRODS)
	{
	   	new rCP = -1, str[128];
		while(rCP == -1 || rCP == LastCP[playerid] || GetDistance(JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], JOB_DRUGF_POS[LastCP[playerid]][0], JOB_DRUGF_POS[LastCP[playerid]][1], JOB_DRUGF_POS[LastCP[playerid]][2]) < 30)
		{
			rCP = random(sizeof(JOB_DRUGF_POS) - 2);
		}
		LastCP[playerid] = rCP;
	    CollectedProds[playerid]++;
	    format(str, sizeof(str), "Producto: %d/%d", CollectedProds[playerid], JOB_DRUGF_MAXPRODS);
		GameTextForPlayer(playerid, str, 1400, 1);
		if(CollectedProds[playerid] == JOB_DRUGF_MAXPRODS)
		{
		 	DrugfJob_SetFinalCheckpoint(playerid);
			SendClientMessage(playerid, COLOR_WHITE, "¡Has terminado con tu trabajo!, ahora vé y descarga el material (/terminar).");
	    	LastCP[playerid] = sizeof(JOB_DRUGF_POS) - 1;
		}
		else
		{
		    SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], 5.4);
		}
	}
	return 1;
}

DrugfJob_SetFinalCheckpoint(playerid)
{
	SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][0], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][1], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][2], 5.4);
	return 1;
}
