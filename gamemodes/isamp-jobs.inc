#if defined _isamp_jobs_included
	#endinput
#endif
#define _isamp_jobs_included

//====[EMPLEOS]=================================================================

#define JOB_DELI	            1 		// Moto-delivery.
#define JOB_TAXI             	2 		// Conductor.
#define JOB_FARM             	3 		// Granjero.
#define JOB_TRAN                4       // Transportista.
#define JOB_GARB                5       // Basurero.
#define JOB_FELON               6
#define JOB_DRUGF          		7
#define JOB_DRUGD          		8

#define JOB_TAXI_MAXPASSENGERS  10

#define	MAX_DRUG_PURCHASE_PAYDAY 10

#define JOB_EXP_MULTIPLIER      3
//
#define BLD_PMA                 2
#define BLD_HOSP                5
#define BLD_HOSP2               11
#define BLD_SIDE                31
#define BLD_MAN                 36

#define JOB_WAITTIME            5  // Número de PayDays que tienes que esperar para poder tomar otro empleo.
#define JOB_NAME_FIELD_MAX		32

#define JOB_STATE_NONE          0
#define JOB_STATE_ACTIVE        1
#define JOB_STATE_FIRED         2
#define JOB_STATE_RESIGNED      3
#define JOB_STATE_FIRED_MISSING 4

#define JOB_TYPE_NONE           0
#define JOB_TYPE_LEGAL        	1
#define JOB_TYPE_ILLEGAL        2

//Enums

enum jInf {
	jName[JOB_NAME_FIELD_MAX],
	jType,
	Float:jTakeX,
	Float:jTakeY,
	Float:jTakeZ,
	jTakeW,
	jTakeI,
	jSkin,
	jTable[24],
	jCharge1[64],
	jCharge2[64],
	jCharge3[64],
	jCharge4[64],
	jCharge5[64],
	jBaseSalary,
};

new JobInfo[20][jInf];

enum pPlayerJob {
	pWorkingHours, // Cantidad de horas efectivas que trabajó (antiguedad)
	pLastWorked[64], // Ultimo día que trabajó
	pTotalEarnings,
	pCharge, // El cargo que ocupa (número)
	pState, // Estado laboral (despedido, renunció, activo, etc)
	pReputation // Imagen laboral: suma o resta puntos dependiendo de las cosas que pasan
};

new PlayerJobInfo[MAX_PLAYERS][pPlayerJob];

//Variables generales:

new bool:jobDuty[MAX_PLAYERS],
	CollectedProds[MAX_PLAYERS],
    LastCP[MAX_PLAYERS];
    
 new Float:jobVehicleHealth[MAX_PLAYERS],
    jobVehicle[MAX_PLAYERS],
    jobCheckpoint[MAX_PLAYERS],
    jobRoute[MAX_PLAYERS];

Job_IsVehicleWorking(vehicleid)
{
	foreach(new playerid : Player)
	{
	    if(jobVehicle[playerid] == vehicleid)
	        return 1;
	}
	return 0;
}

stock GetJobChargeName(job, charge)
{
	new str[64];
	
	switch(charge)
	{
		case 1: format(str, sizeof(str), "%s", JobInfo[job][jCharge1]);
		case 2: format(str, sizeof(str), "%s", JobInfo[job][jCharge2]);
		case 3: format(str, sizeof(str), "%s", JobInfo[job][jCharge3]);
		case 4: format(str, sizeof(str), "%s", JobInfo[job][jCharge4]);
		case 5: format(str, sizeof(str), "%s", JobInfo[job][jCharge5]);
	}
	return str;
}

stock GetJobType(job)
{
	return JobInfo[job][jType];
}

stock GetJobBaseSalary(job)
{
	return JobInfo[job][jBaseSalary];
}
	
//Funciones DB

stock LoadJobs()
{
	new query[128],
		id = 1;
		
	while(id < sizeof(JobInfo))
	{
	    format(query, sizeof(query),"SELECT * FROM `jobs` WHERE `id`=%d LIMIT 1", id);
  		mysql_function_query(dbHandle, query, true, "OnJobDataLoad", "i", id);
		id++;
	}
	return 1;
}

forward OnJobDataLoad(id);
public OnJobDataLoad(id)
{
   	new string[128],
		result[32],
		rows,
		fields;

	cache_get_data(rows, fields);

	if(rows)
	{
		cache_get_field_content(0, "jTakeW", result); 		JobInfo[id][jTakeW] = strval(result);
		cache_get_field_content(0, "jType", result); 		JobInfo[id][jType] 	= strval(result);
		cache_get_field_content(0, "jTakeI", result);		JobInfo[id][jTakeI]	= strval(result);
		cache_get_field_content(0, "jSkin", result); 		JobInfo[id][jSkin] 	= strval(result);
		cache_get_field_content(0, "jBaseSalary", result); 	JobInfo[id][jBaseSalary] = strval(result);

		cache_get_field_content(0, "jName", JobInfo[id][jName], 1, JOB_NAME_FIELD_MAX);
		cache_get_field_content(0, "jTable", JobInfo[id][jTable], 1, 24);

		cache_get_field_content(0, "jTakeX", result); 		JobInfo[id][jTakeX] = floatstr(result);
		cache_get_field_content(0, "jTakeY", result); 		JobInfo[id][jTakeY] = floatstr(result);
		cache_get_field_content(0, "jTakeZ", result); 		JobInfo[id][jTakeZ] = floatstr(result);

        cache_get_field_content(0, "jCharge1", JobInfo[id][jCharge1], 1, 64);
        cache_get_field_content(0, "jCharge2", JobInfo[id][jCharge2], 1, 64);
        cache_get_field_content(0, "jCharge3", JobInfo[id][jCharge3], 1, 64);
        cache_get_field_content(0, "jCharge4", JobInfo[id][jCharge4], 1, 64);
        cache_get_field_content(0, "jCharge5", JobInfo[id][jCharge5], 1, 64);

		CreateDynamicPickup(1274, 1, JobInfo[id][jTakeX], JobInfo[id][jTakeY], JobInfo[id][jTakeZ], JobInfo[id][jTakeW], JobInfo[id][jTakeI], -1);
        format(string, sizeof(string), "Escribe /tomarempleo para tomar el empleo de %s\n/consultarempleo para información detallada", JobInfo[id][jName]);
        CreateDynamic3DTextLabel(string, COLOR_WHITE, JobInfo[id][jTakeX], JobInfo[id][jTakeY], JobInfo[id][jTakeZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
	}
	return 1;
}

//Comandos de jobs

CMD:trabajar(playerid,params[])
{
	new job = PlayerInfo[playerid][pJob];

	if(PlayerInfo[playerid][pFaction] == FAC_MECH)
	{
	    if(!jobDuty[playerid])
		{
			SendClientMessageToAll(COLOR_LIGHTGREEN, "Anuncio: un mecánico se encuentra en servicio (Tel: 555).");
			jobDuty[playerid] = true;
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡Has dejado el servicio como mecánico!");
			jobDuty[playerid] = false;
		}
	}
	else
	{
		if(job == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún empleo!");
		if(jobDuty[playerid])
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya te encuentras trabajando!");
        if(PlayerInfo[playerid][pCantWork] != 0 && job != JOB_DELI)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya has trabajado lo suficiente! vé, y espera hasta el próximo día de pago.");

		switch(job)
		{
		    case JOB_TAXI:
			{
		    	if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_TAXI)
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un taxi!");
				if(PlayerInfo[playerid][pCarLic] == 0)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de conducir. No podrás trabajar sin ella.");
			        
				SendClientMessageToAll(COLOR_LIGHTGREEN, "Anuncio: un taxista se encuentra en servicio (Tel: 444).");
				jobDuty[playerid] = true;
			}
			case JOB_FARM:
		    {
		    	FarmJob_StartWork(playerid);
		    }
			case JOB_DRUGF:
			{
				DrugfJob_StartWork(playerid);
		    }
			case JOB_DRUGD:
			{
		        SendClientMessage(playerid, COLOR_WHITE, "Súbete a un vehículo con maletero y dirígete a la granja de drogas. Recuerda que necesitarás algo de espacio en él.");
		        SendClientMessage(playerid, COLOR_WHITE, "Una vez allí, tipea /comprar para comprar las bolsas de materia prima.");
		        DrugfJob_SetFinalCheckpoint(playerid);
			}
			case JOB_TRAN:
			{
				TranJob_StartWork(playerid);
		    }
			case JOB_GARB:
			{
				GarbJob_StartWork(playerid);
		    }
		    case JOB_DELI:
		    {
		        DeliJob_StartWork(playerid);
			}
			default:
				return 1;
		}
		if(PlayerInfo[playerid][pJobAllowed] == 1 && JobInfo[job][jSkin] > 0)
			SetPlayerSkin(playerid, JobInfo[job][jSkin]);
	}
	return 1;
}

stock GetDateString()
{
	new year, month, day, hour, minute, second, str[64];

	getdate(year, month, day);
	gettime(hour, minute, second);
	
	format(str, sizeof(str), "%02d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
	
	return str;
}

CMD:terminar(playerid,params[])
{
    if(PlayerInfo[playerid][pJob] == 0)
		return 1;
    if(!jobDuty[playerid])
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras trabajando!");

	switch(PlayerInfo[playerid][pJob])
	{
	    case JOB_FARM:
		{
			FarmJob_FinishWork(playerid);
		}
		case JOB_DRUGF:
		{
			DrugfJob_FinishWork(playerid);
		}
		default:
			return 1;
	}
	
	if(PlayerInfo[playerid][pJobAllowed] == 1)
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		
    jobDuty[playerid] = false;
	return 1;
}

CMD:dejarempleo(playerid,params[])
{
	new job = PlayerInfo[playerid][pJob];
	
    if(job == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2,"No tienes ningún empleo.");
	if(JobInfo[job][jType] != 0)
		return 1;
  	if(jobDuty[playerid])
	  	return SendClientMessage(playerid, COLOR_YELLOW2,"¡No puedes hacerlo mientras estás trabajando!");
    if(!PlayerToPoint(1.0, playerid, JobInfo[job][jTakeX],JobInfo[job][jTakeY],JobInfo[job][jTakeZ]))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes presentar tu renuncia a tu jefe, en tu lugar de trabajo.");

	if(GetJobType(job) == JOB_TYPE_LEGAL) // Si es legal, lo ponemos como que renunció.
	{
	    PlayerJobInfo[playerid][pState] = JOB_STATE_RESIGNED;
		SavePlayerJobData(playerid); // Guardamos la información del viejo, si fuese legal.
	}
	SendFMessage(playerid, COLOR_YELLOW2, "¡Has dejado tu empleo de %s!", JobInfo[job][jName]);
	PlayerInfo[playerid][pJob] = 0;
	return 1;
}
