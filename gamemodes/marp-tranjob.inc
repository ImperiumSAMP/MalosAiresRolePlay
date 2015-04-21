#if defined _marp_tranjob_included
	#endinput
#endif
#define _marp_tranjob_included

#define JOB_TRAN_TRAVEL_TIME  	12 // Tiempo limite para hacer el recorrido, en minutos.

new Float:JOB_TRAN_POS[][3] = {
	// Puntos de transporte.
	{2173.3335,-2264.3806,13.3377},
    {1984.9891,-2103.1277,13.5426},
    {1934.3876,-2022.4773,13.5391},
    {1848.0168,-1794.6053,13.5380},
    {1681.3280,-1587.3014,13.4504},
    {2095.2166,-1216.5635,23.8710},
    {2374.7629,-1200.3588,27.4134},
    {2366.5222,-1341.8680,23.9054},
    {2362.9202,-1527.8542,23.8142},
    {2437.0708,-1736.6228,13.6174},
    {2434.7507,-1927.6259,13.4213},
    {2286.7681,-1980.3414,13.5587},
    {2164.2163,-1889.4619,13.4035},
    {996.5835,-1298.9790,13.3789},
    {834.8406,-1391.3583,13.4296},
    {875.6892,-1796.0223,13.7804}
};

TranJob_StartWork(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if(getVehicleType(vehicleid) != VEH_JOB || getVehicleJob(vehicleid) != JOB_TRAN)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un camión de transporte!");
	if(PlayerInfo[playerid][pCarLic] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de conducir. No podrás trabajar sin ella.");
   	if(Job_IsVehicleWorking(vehicleid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Ese vehículo actualmente esta siendo usado para trabajar por otro empleado.");
	if(!Cronometro_Crear(playerid, JOB_TRAN_TRAVEL_TIME * 60, "TranJob_TravelTimeLimit"))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: No se pudo crear el cronometro asociado al trabajo. Reportar a un administrador.");


	SetPlayerCheckpoint(playerid, JOB_TRAN_POS[0][0], JOB_TRAN_POS[0][1], JOB_TRAN_POS[0][2], 5.0);
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	SendClientMessage(playerid, COLOR_WHITE, "Vé al deposito y carga la mercadería en el camión. Luego tendrás que distribuirla a los distintos mercados de la ciudad.");
    SendFMessage(playerid, COLOR_WHITE, "Tienes %d minutos para terminar el recorrido. Si llegas más tarde no se te pagará, y tu imagen laboral empeorará.", JOB_TRAN_TRAVEL_TIME);
    SendClientMessage(playerid, COLOR_WHITE, "Recuerda también que si entregas el camión en peor estado del que lo recibiste, tu imagen laboral disminuirá.");
	jobDuty[playerid] = true;
	GetVehicleHealth(vehicleid, jobVehicleHealth[playerid]);
	SetEngine(vehicleid, 1);
	jobVehicle[playerid] = vehicleid;
	jobCheckpoint[playerid] = 0;
	return 1;
}

TranJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_TRAN && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_TRAN)
	    return 1;
	return 0;
}

forward TranJob_TravelTimeLimit(playerid);
public TranJob_TravelTimeLimit(playerid)
{
    PlayerInfo[playerid][pCantWork] = 1;
    jobDuty[playerid] = false;
    SetEngine(jobVehicle[playerid], 0);
	SetVehicleToRespawn(jobVehicle[playerid]);
	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	SendClientMessage(playerid, COLOR_WHITE, "Te has pasado del tiempo límite: tu jefe se ha enojado y además no recibirás ninguna paga el día de hoy.");
	UpdatePlayerJobLastWorked(playerid);
	PlayerJobInfo[playerid][pReputation] -= 30;
	return 1;
}

forward TranJob_NextCheckpoint(playerid, cp);
public TranJob_NextCheckpoint(playerid, cp)
{
    TogglePlayerControllable(playerid, true);
    jobCheckpoint[playerid]++;
    
    if(cp == 16)
    {
        SendClientMessage(playerid, COLOR_WHITE, "Has terminado de repartir la mercadería. Ahora vuelve a la central y estaciona el camión en su lugar.");
        SetPlayerCheckpoint(playerid, VehicleInfo[jobVehicle[playerid]][VehPosX], VehicleInfo[jobVehicle[playerid]][VehPosY], VehicleInfo[jobVehicle[playerid]][VehPosZ], 5.0);
	}
	else
	{
	    GameTextForPlayer(playerid, "Dirigete al siguiente punto de descarga", 1500, 4);
	    SetPlayerCheckpoint(playerid, JOB_TRAN_POS[cp][0], JOB_TRAN_POS[cp][1], JOB_TRAN_POS[cp][2], 5.0);
	}
	return 1;
}
	    
TranJob_PlayerEnterCheckpoint(playerid)
{
	new actualCP = jobCheckpoint[playerid],
	    vehicleid = GetPlayerVehicleID(playerid);

	if(jobVehicle[playerid] != vehicleid)
	{
	    SetTimerEx("TranJob_NextCheckpoint", 5000, false, "ii", playerid, actualCP); // Le vuelvo a poner el checkpoint al que no pudo entrar, pero despues de unos segundos.
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el camión de transporte con el que empezaste a trabajar!");
	}
	if(actualCP == 0)
	{
		GameTextForPlayer(playerid, "Cargando mercaderia...", 8000, 4);
		TogglePlayerControllable(playerid, false);
		SetTimerEx("TranJob_NextCheckpoint", 8000, false, "ii", playerid, actualCP + 1);
	}
	else if(actualCP < 16)
	{
	    GameTextForPlayer(playerid, "Descargando mercaderia...", 5000, 4);
	    TogglePlayerControllable(playerid, false);
	    SetTimerEx("TranJob_NextCheckpoint", 5000, false, "ii", playerid, actualCP + 1);
	}
	else if(actualCP == 16)
	{
 		PlayerJobInfo[playerid][pWorkingHours]++;
		TranJob_Payment(playerid, vehicleid);
		RemovePlayerFromVehicle(playerid);
  		SetEngine(vehicleid, 0);
		SetVehicleToRespawn(vehicleid);
	    PlayerInfo[playerid][pCantWork] = 1;
	    jobDuty[playerid] = false;
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		PlayerActionMessage(playerid, 15.0, "estaciona el camion de transporte en su lugar.");
		UpdatePlayerJobLastWorked(playerid);
        TranJob_CheckPromotePlayer(playerid);
		Cronometro_Borrar(playerid);
	}
	return 1;
}

TranJob_Payment(playerid, vehicleid)
{
	new paycheck, Float:vHealth, injuriesCost, seniorityBonus, chargeBonus;
		
    GetVehicleHealth(vehicleid, vHealth);
    if(vHealth + 30.0 < jobVehicleHealth[playerid])
    {
        PlayerJobInfo[playerid][pReputation] -= floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil) / 10; // La reputación que baja es proporcional al daño del vehículo (un décimo)
        injuriesCost = floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil); // Se le paga x$$$ menos correspondientes a la diferencia de vida en el vehículo.
		SendClientMessage(playerid, COLOR_WHITE, "Tu jefe se enojó con vos ya que entregaste el camión en mal estado.");
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

TranJob_CheckPromotePlayer(playerid)
{
	if(140 * PlayerJobInfo[playerid][pCharge] >= PlayerJobInfo[playerid][pWorkingHours] && PlayerJobInfo[playerid][pReputation] >= 0 && PlayerJobInfo[playerid][pCharge] < 5) // Minimo de X horas trabajadas (proporcional al siguiente puesto) y de una imágen laboral neutral.
	{
	    if(PlayerJobInfo[playerid][pWorkingHours] + PlayerJobInfo[playerid][pReputation] / 10 >= 180 * PlayerJobInfo[playerid][pCharge]) // Para ascender hay que llegar a una cantidad de puntos. Nuestro puntaje se suma entre la reputacion y la antiguedad.
	    {
	        PlayerJobInfo[playerid][pCharge]++;
	        SendFMessage(playerid, COLOR_WHITE, "¡Enhorabuena! has sido promovido a %s, lo que te garantiza una mejora en tu sueldo. ¡Buen trabajo! Sigue así.", GetJobChargeName(JOB_TRAN, PlayerJobInfo[playerid][pCharge]));
		}
	}
}
