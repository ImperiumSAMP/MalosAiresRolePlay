#if defined _marp_garbjob_included
	#endinput
#endif
#define _marp_garbjob_included

#define JOB_GARB_TRAVEL_TIME  	10 // Tiempo limite para hacer el recorrido, en minutos.

forward GarbJob_LoadingTimer(playerid, garbcp);

new Float:JOB_GARB_POS_R0[][3] = {
	// basureros ruta oeste
	{2416.5730,-1982.5348,13.0964},
	{2316.1499,-1959.5759,13.1051},
	{2095.5801,-1891.8380,13.0947},
	{2040.2618,-1810.0276,13.1099},
	{1964.1158,-1767.0380,13.1099},
	{1837.2772,-1749.1176,13.1099},
	{1578.1523,-1729.1829,13.1099},
	{1349.9713,-1729.9696,13.1099},
	{1322.6595,-1529.6226,13.1099},
	{1144.6719,-1392.5767,13.3237},
	{932.5922,-1392.6332,12.9839},
	{624.9330,-1430.7775,13.6419},
	{260.6046,-1434.2141,13.2730},
	{471.4320,-1313.2888,15.0369},
	{756.5276,-1065.1980,23.6607},
	{1069.5193,-962.5571,42.2988},
	{1350.2448,-1058.4478,26.3018},
	{1432.6157,-1162.3704,23.3888},
	{1451.5614,-1298.7955,13.1099},
	{1427.3477,-1576.6962,13.0883},
	{1719.5588,-1597.1793,13.0875},
	{1746.7151,-1713.8253,13.1099},
	{1819.0933,-1804.3193,13.1204},
	{1959.1876,-2015.9716,13.1177},
	{2385.3523,-1975.1807,13.1099},
    {2389.2288,-2064.5564,13.2214} 	// entraga 25
};

new Float:JOB_GARB_POS_R1[][3] = {
	// basureros ruta este
	{2416.1792,-2020.9438,13.1418},
	{2476.4333,-1934.5983,13.0717},
	{2711.6902,-1972.1912,13.0594},
	{2771.5774,-1963.7712,13.0783},
	{2645.8135,-1598.2715,12.0833},
	{2645.6782,-1362.1589,32.2359},
	{2595.5840,-1253.8698,46.7980},
	{2703.3892,-1186.4670,68.9670},
	{2575.7156,-1045.0909,69.1411},
	{2255.7195,-1047.6941,51.5216},
	{1974.7074,-1074.7692,24.5354},
	{1901.5074,-1133.1996,24.0768},
	{2025.8148,-1072.6514,24.2742},
	{2159.2893,-1223.5388,23.5435},
	{2268.2837,-1261.4368,23.5436},
	{2209.7693,-1432.7487,23.5503},
	{2364.6401,-1526.9608,23.5552},
	{2397.0527,-1730.0308,13.1099},
	{2129.3398,-1749.9578,13.1302},
	{2079.8037,-1795.3230,13.1156},
	{2152.0408,-1896.6810,13.1071},
	{2297.5706,-1896.5006,13.1260},
	{2311.2969,-1956.7001,13.0992},
	{2386.9607,-1975.1156,13.1099},
	{2411.1948,-2013.1652,13.0868},
    {2389.2288,-2064.5564,13.2214} // entraga 25
};

GarbJob_StartWork(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);

	if(getVehicleType(vehicleid) != VEH_JOB || getVehicleJob(vehicleid) != JOB_GARB)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un camión recolector!");
	if(PlayerInfo[playerid][pCarLic] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de conducir. No podrás trabajar sin ella.");
		
	new route = random(2);

	if(route == 0)
	{
 		SetPlayerCheckpoint(playerid, JOB_GARB_POS_R0[0][0], JOB_GARB_POS_R0[0][1], JOB_GARB_POS_R0[0][2], 5.0);
	}
	else if(route == 1) 
	{
	    SetPlayerCheckpoint(playerid, JOB_GARB_POS_R1[0][0], JOB_GARB_POS_R1[0][1], JOB_GARB_POS_R1[0][2], 5.0);
	}
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	SendClientMessage(playerid, COLOR_WHITE, "Completa el recorrido para dejar la ciudad libre de basura. Al finalizar serás recompensado por tu trabajo.");
    SendFMessage(playerid, COLOR_WHITE, "Tienes %d minutos para terminar el recorrido. Si llegas más tarde no se te pagará, y tu imagen laboral empeorará.", JOB_GARB_TRAVEL_TIME);
    SendClientMessage(playerid, COLOR_WHITE, "Recuerda también que si entregas el camión recolector en peor estado del que lo recibiste, tu imagen laboral disminuirá.");
	jobDuty[playerid] = true;
	GetVehicleHealth(vehicleid, jobVehicleHealth[playerid]);
	SetEngine(vehicleid, 1);
	jobVehicle[playerid] = vehicleid;
	jobCheckpoint[playerid] = 0;
	jobRoute[playerid] = route;
	CrearCronometro(playerid, JOB_GARB_CRONOMETRO, JOB_GARB_TRAVEL_TIME * 60);
	return 1;
}

GarbJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_GARB && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_GARB)
	    return 1;
	return 0;
}

GarbJob_PlayerEnterCheckpoint(playerid)
{
    new gbCP = jobCheckpoint[playerid],
		vehicleid = GetPlayerVehicleID(playerid);

	if(jobVehicle[playerid] != vehicleid)
	{
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el camión de transporte con el que empezaste a trabajar!");
	}
    if(gbCP == 26)
	{
		TogglePlayerControllable(playerid, false);
		GameTextForPlayer(playerid, "Vaciando camión...", 6000, 4);
		SetTimerEx("GarbJob_LoadingTimer", 6000, false, "ii", playerid, gbCP);
		BorrarCronometro(playerid);
    }
	else
	{
        TogglePlayerControllable(playerid, false);
        GameTextForPlayer(playerid, "Cargando basura...", 3000, 4);
    	SetTimerEx("GarbJob_LoadingTimer", 3000, false, "ii", playerid, gbCP);
		jobCheckpoint[playerid]++;
		if(jobRoute[playerid] == 0)
		{
 			SetPlayerCheckpoint(playerid, JOB_GARB_POS_R0[gbCP+1][0], JOB_GARB_POS_R0[gbCP+1][1], JOB_GARB_POS_R0[gbCP+1][2], 5.0);
		}
		else if(jobRoute[playerid] == 1)
		{
		    SetPlayerCheckpoint(playerid, JOB_GARB_POS_R1[gbCP+1][0], JOB_GARB_POS_R1[gbCP+1][1], JOB_GARB_POS_R1[gbCP+1][2], 5.0);
		}
    }
	return 1;
}

GarbJob_TravelTimeLimit(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    
    PlayerInfo[playerid][pCantWork] = 1;
    jobDuty[playerid] = false;
    if(jobVehicle[playerid] == vehicleid)
    {
	    SetEngine(vehicleid, 0);
		SetVehicleToRespawn(vehicleid);
	}
	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	SendClientMessage(playerid, COLOR_WHITE, "Te has pasado del tiempo límite: tu jefe se ha enojado y además no recibirás ninguna paga el día de hoy.");
	UpdatePlayerJobLastWorked(playerid);
	PlayerJobInfo[playerid][pReputation] -= 30;
}

public GarbJob_LoadingTimer(playerid, garbcp)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	
    TogglePlayerControllable(playerid, true);
    if(garbcp == 25)
	{
		SendClientMessage(playerid, COLOR_WHITE, "Vuelve y vacía el camión en el depósito.");
  	}
  	else if(garbcp == 26)
	{
	    PlayerJobInfo[playerid][pWorkingHours]++;
	    GarbJob_Payment(playerid, vehicleid);
		RemovePlayerFromVehicle(playerid);
	    SetEngine(vehicleid, 0);
		SetVehicleToRespawn(vehicleid);
  		PlayerInfo[playerid][pCantWork] = 1;
	    jobDuty[playerid] = false;
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		PlayerActionMessage(playerid, 15.0, "abre las puertas del depósito y vacía el camión recolector.");
		UpdatePlayerJobLastWorked(playerid);
        GarbJob_CheckPromotePlayer(playerid);
        BorrarCronometro(playerid);
  	}
	return 1;
}

GarbJob_Payment(playerid, vehicleid)
{
	new paycheck, Float:vHealth, injuriesCost, seniorityBonus, chargeBonus;

    GetVehicleHealth(vehicleid, vHealth);
    if(vHealth + 30.0 < jobVehicleHealth[playerid])
    {
        PlayerJobInfo[playerid][pReputation] -= floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil) / 10; // La reputación que baja es proporcional al daño del vehículo (un décimo)
        injuriesCost = floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil); // Se le paga x$$$ menos correspondientes a la diferencia de vida en el vehículo.
		SendClientMessage(playerid, COLOR_WHITE, "Tu jefe se enojó con vos ya que entregaste el camión recolector en mal estado.");
	}
	else
	    PlayerJobInfo[playerid][pReputation]++;

	seniorityBonus = PlayerJobInfo[playerid][pWorkingHours] / 2; // Extra por antiguedad
	chargeBonus = (PlayerJobInfo[playerid][pCharge] - 1) * 100; // Extra por cargo

	paycheck = GetJobBaseSalary(JOB_TRAN) + seniorityBonus + chargeBonus - injuriesCost;
	PlayerInfo[playerid][pPayCheck] += paycheck;
	PlayerJobInfo[playerid][pTotalEarnings] += paycheck;

	SendFMessage(playerid, COLOR_WHITE, "¡Enhorabuena! has finalizado tu trabajo y recibirás $%d en el próximo payday.", paycheck);
	SendFMessage(playerid, COLOR_WHITE, "[Detalles]: Salario base: $%d - Bonus por antiguedad: $%d - Bonus por cargo: $%d - Descuento por roturas: ${FF0000}%d", GetJobBaseSalary(JOB_TRAN), seniorityBonus, chargeBonus, injuriesCost);
}

GarbJob_CheckPromotePlayer(playerid)
{
	if(140 * PlayerJobInfo[playerid][pCharge] >= PlayerJobInfo[playerid][pWorkingHours] && PlayerJobInfo[playerid][pReputation] >= 0 && PlayerJobInfo[playerid][pCharge] < 5) // Minimo de X horas trabajadas (proporcional al siguiente puesto) y de una imágen laboral neutral.
	{
	    if(PlayerJobInfo[playerid][pWorkingHours] + PlayerJobInfo[playerid][pReputation] / 10 >= 180 * PlayerJobInfo[playerid][pCharge]) // Para ascender hay que llegar a una cantidad de puntos. Nuestro puntaje se suma entre la reputacion y la antiguedad.
	    {
	        PlayerJobInfo[playerid][pCharge]++;
	        SendFMessage(playerid, COLOR_WHITE, "¡Enhorabuena! has sido promovido a %s, lo que te garantiza una mejora en tu sueldo. ¡Buen trabajo! Sigue así.", GetJobChargeName(JOB_GARB, PlayerJobInfo[playerid][pCharge]));
		}
	}
}
