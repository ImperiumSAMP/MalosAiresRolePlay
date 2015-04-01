#if defined _marp_tranjob_included
	#endinput
#endif
#define _marp_tranjob_included

#define JOB_TRAN_MAXPRODS       8 		// Cargas máximas que se pueden transportar.
#define JOB_TRAN_PRODVALUE      225    	// VALOR POR PAQUETE

new Float:JOB_TRAN_POS[][3] = {
	// Puntos de transporte.
    {1879.1420,-1617.4001,13.6332},
    {1933.8116,-1777.0908,13.5565},
    {1072.1393,-1576.8750,13.6338},
    {1005.5207,-933.0194,42.3528},
    {425.3821,-1323.6420,15.0959},
    {938.3804,-1795.8016,13.9731},
    {1208.7485,-1856.8451,13.6338},
    {2125.1741,-1116.2593,25.4264},
    {2225.7415,-1140.4315,25.8735},
    {2351.3555,-1305.5288,24.1854},
    {2646.6379,-1103.8756,68.9008},
    {2858.3772,-1536.1311,11.1725},
    {2849.4207,-1483.9521,11.0082},
    {1928.3282,-1131.2484,25.2764},
    {1447.2676,-1029.3236,23.9110},
    {1046.4854,-1034.7568,32.0465},
    // Punto de entrega (16).
    {2186.1924,-2263.9763,13.6376}
};

TranJob_StartWork(playerid)
{
	if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_TRAN)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un camión de transporte!");

	SendClientMessage(playerid, COLOR_WHITE, "Entrega los paquetes en los puntos rojos del mapa y vuelve a buscar más o bien utiliza /terminar cuando lo desees.");
    SendClientMessage(playerid, COLOR_WHITE, "Te pagarán acorde a la cantidad de paquetes entregados y no podrás volver a trabajar durante este día de pago.");
	SetPlayerCheckpoint(playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2], 5.4);
	jobDuty[playerid] = true;
	SetEngine(GetPlayerVehicleID(playerid), 1);
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	return 1;
}

TranJob_FinishWork(playerid)
{
	if(!PlayerToPoint(20.0, playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve a la zona indicada!");
    if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_TRAN)
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar adentro de un camión!");

	SendFMessage(playerid, COLOR_WHITE, "Has descargado %d paquetes por lo tanto recibirás $%d en el próximo día de pago.", CollectedProds[playerid], CollectedProds[playerid] * JOB_TRAN_PRODVALUE);
	PlayerInfo[playerid][pCantWork] = 1;
	carryingProd[playerid] = false;
	LastCP[playerid] = -1;
	PlayerInfo[playerid][pPayCheck] += CollectedProds[playerid] * JOB_TRAN_PRODVALUE;
	PlayerJobInfo[playerid][pTotalEarnings]+= CollectedProds[playerid] * JOB_TRAN_PRODVALUE;
	PlayerJobInfo[playerid][pWorkingHours]++;
    UpdatePlayerJobLastWorked(playerid);
	CollectedProds[playerid] = 0;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	PlayerActionMessage(playerid, 15.0, "estaciona el camión.");
	return 1;
}

TranJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_TRAN && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_TRAN)
	    return 1;
	return 0;
}

TranJob_PlayerEnterCheckpoint(playerid)
{
	if(CollectedProds[playerid] < JOB_TRAN_MAXPRODS)
	{
	    if(carryingProd[playerid])
		{
		    new str[128];
	        carryingProd[playerid] = false;
            CollectedProds[playerid]++;
            format(str, sizeof(str), "Paquetes entregados: %d/%d", CollectedProds[playerid], JOB_TRAN_MAXPRODS);
			GameTextForPlayer(playerid, str, 1400, 1);
			SetPlayerCheckpoint(playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2], 5.4);
			if(CollectedProds[playerid] == JOB_TRAN_MAXPRODS)
				SendClientMessage(playerid, COLOR_WHITE, "¡Has terminado con tu trabajo!, vuelve a la agencia.");
	    }
		else
		{
	        if(CollectedProds[playerid] == JOB_TRAN_MAXPRODS)
				return SendClientMessage(playerid, COLOR_WHITE, "Tipea /terminar para confirmar los envíos.");

            carryingProd[playerid] = true;
	       	new rCP = -1;
			while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid])
			{
	 			rCP = random(sizeof(JOB_TRAN_POS));
	 		}
	 		LastCP[playerid] = rCP;
            SetPlayerCheckpoint(playerid, JOB_TRAN_POS[rCP][0], JOB_TRAN_POS[rCP][1], JOB_TRAN_POS[rCP][2], 5.4);
	    }
    }
    return 1;
}
