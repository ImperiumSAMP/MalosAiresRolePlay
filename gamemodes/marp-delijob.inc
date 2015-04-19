#if defined _marp_delijob_included
	#endinput
#endif
#define _marp_delijob_included

#define JOB_DELI_STOREPLACE_X       1741.24
#define JOB_DELI_STOREPLACE_Y       -1562.16
#define JOB_DELI_STOREPLACE_Z       14.16

#define JOB_DELI_MAX_DELIVERYS      5

enum DeliJob_RouteInfo {
	Float:djX,
	Float:djY,
	Float:djZ,
	djTime
}

static const DeliJob_Route[][DeliJob_RouteInfo] = {
	{1439.3058, -926.6467, 39.6477, 80},
	{1525.7418, -774.5235, 79.8811, 95},
	{1442.7665, -629.5516, 95.7186, 105},
	{1033.1843, -809.6239, 101.8516, 125},
	{836.9149, -893.5928, 68.7689, 115},
 	{689.8444, -1053.7305, 50.1541, 142},
	{551.5204, -1197.1387, 44.5455, 134},
	{200.0531, -1385.0724, 48.6990, 131},
	{248.4863, -1262.6874, 69.7666, 140},
	{345.8627, -1191.2847, 76.5199, 152},
	{474.1737, -1174.8789, 63.6685, 150},
	{908.5896, -684.1473, 116.1911, 150},
	{1003.3759, -644.3123, 121.4506, 165},
	{1110.1738, -964.7603, 42.7233, 95},
	{1275.7544, -1066.0847, 28.9254, 92},
	{1247.5719, -1100.8672, 26.6719, 85},
	{1334.9695, -1065.8662, 28.0768, 75},
	{1190.5178, -1025.3774, 32.5469, 101},
	{1092.9587, -1093.6184, 25.5307, 96},
	{573.2700, -1573.0392, 16.1797, 108},
	{364.3013, -1599.1323, 31.9686, 99},
	{329.9218, -1514.5978, 35.8672, 116},
	{301.6986, -1609.2399, 33.1205, 119},
	{451.4945, -1479.3191, 30.8217, 118},
	{305.5432, -1771.6835, 4.5418, 126},
	{206.8645, -1770.6487, 4.3271, 140},
	{168.1399, -1770.7959, 4.4059, 124},
	{2232.5164, -1159.4286, 25.4431, 86},
	{2378.5925, -1197.8383, 26.9964, 88},
	{2579.2097, -1389.8606, 28.4168, 98},
	{2389.6272, -1547.0151, 23.6463, 81},
	{2312.2031, -1327.7529, 23.5887, 85},
	{2504.2839, -1054.7465, 68.7408, 109},
	{2259.4575, -1064.8844, 48.9365, 110},
	{2176.1047, -1000.3945, 62.5274, 90},
	{2201.2290, -1110.3525, 24.9869, 87},
	{2141.3728, -1176.8253, 23.5552, 68},
	{1996.4288, -1281.7885, 23.5420, 70},
	{1830.1071, -1174.8458, 23.3921, 55},
	{1728.4203, -1180.2593, 23.4062, 56},
	{1587.2603, -1319.1085, 17.1226, 56},
	{1449.2810, -1342.7710, 13.1087, 58},
	{1392.3855, -1386.3190, 13.1181, 63},
	{1235.1714, -1459.3789, 13.1126, 60},
	{1213.8494, -1858.2449, 13.1186, 74},
	{1026.4001, -1771.8937, 13.1244, 82},
	{912.9034, -1822.7805, 12.1036, 90},
	{662.1538, -1791.8245, 12.0412, 104},
	{540.7659, -1811.2538, 5.6326, 112},
	{385.5496, -1820.9386, 7.4038, 112},
	{365.1925, -1638.3317, 32.4608, 117},
	{374.1253, -1416.1790, 33.8681, 129},
	{457.3859, -1376.1747, 23.2685, 119},
	{644.2280, -1353.9694, 13.1185, 110},
	{724.9738, -1437.6512, 13.1042, 119},
	{841.2798, -1477.6545, 13.1670, 100},
	{774.1593, -1511.3673, 13.1198, 98},
	{778.3951, -1572.3734, 13.1138, 96},
	{832.0608, -1599.7253, 13.1177, 93},
	{937.4967, -1562.4418, 13.1185, 84},
	{1160.8230, -1584.2101, 13.1159, 74},
	{1485.0763, -1863.6694, 13.1120, 72},
	{1630.5979, -1903.5100, 13.1208, 54},
	{1846.7078, -1872.2468, 13.1423, 54},
	{1980.5719, -1997.6008, 13.1245, 70},
	{1907.6268, -2044.4760, 13.1163, 82},
	{1856.6500, -1991.0896, 13.1125, 81},
	{1804.1267, -2124.2188, 13.5138, 90},
	{1664.2416, -2115.5017, 13.1070, 98},
	{2281.0366, -2364.7205, 13.1191, 120},
	{2649.0771, -2385.0730, 13.1997, 120},
	{2755.5432, -2382.4824, 13.1989, 120},
	{2269.7637, -1885.8168, 13.1157, 120},
	{2353.3743, -1990.4171, 13.1077, 120},
	{2435.7744, -1924.0054, 13.1136, 120},
	{2734.7529, -1926.1731, 13.1120, 120},
	{2653.1238, -1990.8837, 13.3035, 120},
	{2508.8572, -2001.8585, 13.1167, 120},
	{2069.7893, -1903.7882, 13.0720, 120},
	{2269.1912, -1826.1661, 13.1098, 120},
	{2481.5491, -1756.4528, 13.1122, 120},
	{2518.9348, -1678.4635, 14.1900, 120},
	{2263.8599, -1470.4756, 23.3661, 120},
	{2233.6533, -1457.7091, 23.5807, 120},
	{2204.2678, -1412.9717, 23.5416, 120}
};

stock DeliJob_GetVehicleCharge(vehicleid)
{
    new modelid = GetVehicleModel(vehicleid);
    
 	switch(modelid)
 	{
 	    case 462: return 1; //faggio
		case 581: return 3; //bf400
		case 461: return 5; //pcj600
	}
	return 1;
}

DeliJob_StartWork(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid),
	    destination = random(sizeof(DeliJob_Route));

    if(getVehicleJob(vehicleid) != JOB_DELI)
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en una moto de reparto!");
	if(DeliJob_GetVehicleCharge(vehicleid) > PlayerJobInfo[playerid][pCharge])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tu cargo en la empresa no tiene acceso a ese modelo de moto!");
	if(PlayerInfo[playerid][pCarLic] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de conducir. No podrás trabajar sin ella.");
	if(PlayerInfo[playerid][pCantWork] >= JOB_DELI_MAX_DELIVERYS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya has alcanzado el máximo de entregas posibles por este día de pago.");

	SetPlayerCheckpoint(playerid, JOB_DELI_STOREPLACE_X, JOB_DELI_STOREPLACE_Y, JOB_DELI_STOREPLACE_Z, 2.0);
	PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
	SendClientMessage(playerid, COLOR_WHITE, "¡Rápido! Vé al fondo y agarra un paquete para entregar. Luego tendrás que viajar a la velocidad de un rayo y entregarlo lo antes posible.");
    SendFMessage(playerid, COLOR_WHITE, "Tienes %d segs para ir, entregar el paquete, y volver a la central. Si llegas tarde, no te pagarán y tu imagen laboral empeorará.", DeliJob_Route[destination][djTime]);
    SendClientMessage(playerid, COLOR_WHITE, "Recuerda también que si entregas la moto en peor estado de como la recibiste, tu imagen laboral disminuirá.");
	jobDuty[playerid] = true;
	SetEngine(vehicleid, 1);
	jobVehicle[playerid] = vehicleid;
	jobCheckpoint[playerid] = 0;
	jobRoute[playerid] = destination;
    GetVehicleHealth(vehicleid, jobVehicleHealth[playerid]);
    CrearCronometro(playerid, JOB_DELI_CRONOMETRO, DeliJob_Route[destination][djTime]);
	return 1;
}

DeliJob_IsPlayerWorking(playerid, vehicleid)
{
	if(PlayerInfo[playerid][pJob] == JOB_DELI && jobDuty[playerid] && VehicleInfo[vehicleid][VehJob] == JOB_DELI)
	    return 1;
	return 0;
}

forward DeliJob_NextCheckpoint(playerid, cp);
public DeliJob_NextCheckpoint(playerid, cp)
{
    TogglePlayerControllable(playerid, true);
    jobCheckpoint[playerid]++;
    if(cp == 1)
    {
        SendClientMessage(playerid, COLOR_WHITE, "¡Rapido! Entrega el paquete en la dirección indicada.");
        SetPlayerCheckpoint(playerid, DeliJob_Route[jobRoute[playerid]][djX], DeliJob_Route[jobRoute[playerid]][djY], DeliJob_Route[jobRoute[playerid]][djZ], 2.0);
    }
    else if(cp == 2)
    {
        new tip = random(20);
        if(tip > 0)
        {
            SendFMessage(playerid, COLOR_WHITE, "El cliente te ha dado $%d de propina.", tip);
            GivePlayerCash(playerid, tip);
        }
        GameTextForPlayer(playerid, "Vuelve a la central y estaciona la moto en su lugar", 1500, 4);
		SetPlayerCheckpoint(playerid, VehicleInfo[jobVehicle[playerid]][VehPosX], VehicleInfo[jobVehicle[playerid]][VehPosY], VehicleInfo[jobVehicle[playerid]][VehPosZ], 2.0);
    }
	return 1;
}

DeliJob_PlayerEnterCheckpoint(playerid)
{
	new actualCP = jobCheckpoint[playerid],
	    vehicleid = GetPlayerVehicleID(playerid);
	    
	if(actualCP == 0)
	{
		GameTextForPlayer(playerid, "Guardando paquete...", 4000, 4);
		TogglePlayerControllable(playerid, false);
		SetTimerEx("DeliJob_NextCheckpoint", 4000, false, "ii", playerid, actualCP + 1);
	}
	else if(actualCP == 1)
	{
	    GameTextForPlayer(playerid, "Entregando paquete...", 4000, 4);
	    TogglePlayerControllable(playerid, false);
	    SetTimerEx("DeliJob_NextCheckpoint", 4000, false, "ii", playerid, actualCP + 1);
	}
	else if(actualCP == 2)
	{
	    PlayerInfo[playerid][pCantWork]++;
 		PlayerJobInfo[playerid][pWorkingHours]++;
		DeliJob_Payment(playerid, vehicleid);
		RemovePlayerFromVehicle(playerid);
  		SetEngine(vehicleid, 0);
		SetVehicleToRespawn(vehicleid);
	    jobDuty[playerid] = false;
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		PlayerActionMessage(playerid, 15.0, "estaciona la moto en su lugar.");
		UpdatePlayerJobLastWorked(playerid);
        DeliJob_CheckPromotePlayer(playerid);
		BorrarCronometro(playerid);
	}
	return 1;
}

DeliJob_TravelTimeLimit(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);

    PlayerInfo[playerid][pCantWork]++;
    jobDuty[playerid] = false;
    if(jobVehicle[playerid] == vehicleid)
	{
	    SetEngine(vehicleid, 0);
		SetVehicleToRespawn(vehicleid);
	}
	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	SendClientMessage(playerid, COLOR_WHITE, "Te has pasado del tiempo límite: tu jefe se ha enojado y además no recibirás ninguna paga por la entrega fallida.");
	UpdatePlayerJobLastWorked(playerid);
	PlayerJobInfo[playerid][pReputation] -= 6;
}

DeliJob_Payment(playerid, vehicleid)
{
	new paycheck, Float:vHealth, injuriesCost, seniorityBonus, chargeBonus;

    GetVehicleHealth(vehicleid, vHealth);
    if(vHealth + 30.0 < jobVehicleHealth[playerid])
    {
        PlayerJobInfo[playerid][pReputation] -= floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil) / 20; // La reputación que baja es proporcional al daño del vehículo (un décimo)
        injuriesCost = floatround(jobVehicleHealth[playerid] - vHealth, floatround_ceil) / 2; // Se le paga x$$$ menos correspondientes a la diferencia de vida en el vehículo / 2.
		SendClientMessage(playerid, COLOR_WHITE, "Tu jefe se enojó con vos ya que entregaste la moto en mal estado.");
	}
	else
	    PlayerJobInfo[playerid][pReputation]++;

	seniorityBonus = PlayerJobInfo[playerid][pWorkingHours] / 10; // Extra por antiguedad
	chargeBonus = (PlayerJobInfo[playerid][pCharge] - 1) * 20; // Extra por cargo

	paycheck = GetJobBaseSalary(JOB_DELI) + seniorityBonus + chargeBonus - injuriesCost;
	PlayerInfo[playerid][pPayCheck] += paycheck;
	PlayerJobInfo[playerid][pTotalEarnings] += paycheck;

	SendFMessage(playerid, COLOR_WHITE, "¡Enhorabuena! has finalizado la entrega a tiempo y recibirás $%d adicionales en el próximo payday. Puedes hacer %d entrega/s más el día de hoy.", paycheck, JOB_DELI_MAX_DELIVERYS - PlayerInfo[playerid][pCantWork]);
	SendFMessage(playerid, COLOR_WHITE, "[Detalles]: Pago base por entrega: $%d - Bonus por antiguedad: $%d - Bonus por cargo: $%d - Descuento por roturas: ${FF0000}%d", GetJobBaseSalary(JOB_DELI), seniorityBonus, chargeBonus, injuriesCost);
}

DeliJob_CheckPromotePlayer(playerid)
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
