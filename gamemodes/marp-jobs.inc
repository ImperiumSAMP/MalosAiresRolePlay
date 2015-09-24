#if defined _marp_jobs_included
	#endinput
#endif
#define _marp_jobs_included

//====[EMPLEOS]=================================================================

#define JOB_DELI	            1
#define JOB_TAXI             	2 	
#define JOB_FARM             	3 	
#define JOB_TRAN                4     
#define JOB_GARB                5       
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

#define JOB_STATE_NONE          0
#define JOB_STATE_ACTIVE        1
#define JOB_STATE_FIRED         2
#define JOB_STATE_RESIGNED      3
#define JOB_STATE_FIRED_MISSING 4

#define JOB_TYPE_NONE           0
#define JOB_TYPE_LEGAL        	1
#define JOB_TYPE_ILLEGAL        2

#define DLG_JOB_INFO_1 			10036
#define DLG_JOB_INFO_2 			10037

//===============================DATA STORAGE===================================

enum e_job_info {
	jName[32],
	jType,
	jBaseSalary,
	jSkin,
	jRpPoints,
	Float:jTakeX,
	Float:jTakeY,
	Float:jTakeZ,
	jTakeW,
	jTakeI,
	jTable[24],
	jCharge1[64],
	jCharge2[64],
	jCharge3[64],
	jCharge4[64],
	jCharge5[64]
};

new JobInfo[][e_job_info] = {

/*0*/	{"NONE", 0,	0, 0, 0, 0.0, 0.0, 0.0, 0, 0, "NONE", "NONE", "NONE", "NONE", "NONE", "NONE"},
/*1*/   {"Moto Delivery", 1, 375, 0, 0, 1739.45, -1583.3, 14.15, 0, 0, "job_deli", "Aprendiz", "Cadete", "Mensajero", "Mensajero experimentado", "Supervisor"},
/*2*/   {"Taxista", 1, 0, 0, 0, 1813.68, -1896.36, 13.5781, 0, 0, "job_taxi", "Chofer", "Chofer", "Chofer", "Chofer", "Chofer"},
/*3*/   {"Granjero", 1, 1800, 32, 0, -31.0715, 54.5695, 3.1172, 0, 0, "job_farm", "Aprendiz", "Ayudante de maquinas", "Chofer de maquina", "Evaluador de cosecha", "Supervisor"},
/*4*/   {"Transportista", 1, 1800, 206, 0, 2229.23, -2208.34, 13.5469, 0, 0, "job_tran", "Aprendiz", "Carguero", "Chofer de camión", "Encargado de logística", "Supervisor"},
/*5*/   {"Basurero", 1, 1800, 236, 0, 2405.58, -2060.67, 13.5469, 0, 0, "job_garb", "Aprendiz", "Recolector", "Compactador", "Chofer de camión", "Supervisor"},
/*6*/   {"Delincuente", 2, 0, 0, 1, 2614.12, -1393.15, 34.8954, 0, 0, "NONE", "NONE", "NONE", "NONE", "NONE", "NONE"},
/*7*/   {"Cosechador de Materia Prima", 2, 0, 0, 0, -1060.79, -1205.49, 129.322, 0, 0, "NONE", "NONE", "NONE", "NONE", "NONE", "NONE"},
/*8*/   {"Narcotraficante", 2, 0, 0, 1, 2548.96, -1331.56, 34.2638, 0, 0, "NONE", "NONE", "NONE", "NONE", "NONE", "NONE"}

};

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

//==============================================================================

Job_IsVehicleWorking(vehicleid)
{
	foreach(new playerid : Player)
	{
	    if(jobVehicle[playerid] == vehicleid)
	        return 1;
	}
	return 0;
}

//==============================================================================

stock Job_WorkingPlayerDisconnect(playerid)
{
	if(jobDuty[playerid] && jobVehicle[playerid])
	{
 		jobDuty[playerid] = false;
	    SetEngine(jobVehicle[playerid], 0);
	    SetVehicleToRespawn(jobVehicle[playerid]);
	    jobVehicle[playerid] = 0;
	}
}

//==============================================================================

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

//==============================================================================

GetJobType(job)
{
	return JobInfo[job][jType];
}

//==============================================================================

GetJobBaseSalary(job)
{
	return JobInfo[job][jBaseSalary];
}

//==============================================================================

Job_GetRpPointsNeeded(job)
{
	return JobInfo[job][jRpPoints];
}

//==============================================================================

Jobs_LoadPickups()
{
	new jsize = sizeof(JobInfo),
	    string[128];
	
	for(new i = 1; i < jsize; i++)
	{
		CreateDynamicPickup(1274, 1, JobInfo[i][jTakeX], JobInfo[i][jTakeY], JobInfo[i][jTakeZ], JobInfo[i][jTakeW], JobInfo[i][jTakeI], -1);
        format(string, sizeof(string), "Escribe /tomarempleo para tomar el empleo de %s\nUsa /consultarempleo para más información.", JobInfo[i][jName]);
        CreateDynamic3DTextLabel(string, COLOR_WHITE, JobInfo[i][jTakeX], JobInfo[i][jTakeY], JobInfo[i][jTakeZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
	}
}

//==============================================================================

ResetJobVariables(playerid)
{
    ResetThiefVariables(playerid);
    
	PlayerJobInfo[playerid][pWorkingHours] = 0;
	strmid(PlayerJobInfo[playerid][pLastWorked], " ", 0, strlen(" "), 255);
	PlayerJobInfo[playerid][pTotalEarnings] = 0;
	PlayerJobInfo[playerid][pCharge] = 0;
	PlayerJobInfo[playerid][pState] = 0;
	PlayerJobInfo[playerid][pReputation] = 0;
}

//==============================================================================

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

//==============================================================================

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

//==============================================================================

CMD:tomarempleo(playerid,params[])
{
	new string[128];

    if(PlayerInfo[playerid][pJobAllowed] == 0)
    	return SendClientMessage(playerid,COLOR_YELLOW2,"¡No puedes tomar este empleo perteneciendo a esta facción!");
    if(PlayerInfo[playerid][pJob] != 0)
		return SendClientMessage(playerid,COLOR_YELLOW2,"¡Ya tienes un empleo!");
	if(PlayerInfo[playerid][pJobTime] != 0)
	{
		format(string, sizeof(string), "¡Debes esperar %d PayDay/s antes de tomar otro empleo!", PlayerInfo[playerid][pJobTime]);
		return SendClientMessage(playerid, COLOR_YELLOW2, string);
	}

	for(new job = 1; job < sizeof(JobInfo); job++)
	{
		if(PlayerToPoint(1.0, playerid, JobInfo[job][jTakeX], JobInfo[job][jTakeY], JobInfo[job][jTakeZ]))
		{
		    if(PlayerInfo[playerid][pRolePoints] < Job_GetRpPointsNeeded(job))
		        return SendClientMessage(playerid, COLOR_WHITE, "[OOC]: No tienes suficientes puntos de rol para tomar este trabajo.");
		    if((job == JOB_TAXI || job == JOB_TRAN || job == JOB_GARB || job == JOB_DELI) && PlayerInfo[playerid][pCarLic] == 0)
		        return SendClientMessage(playerid, COLOR_WHITE, "No puedo emplearte si no tienes licencia de manejo, hasta luego.");
            if(job == JOB_DRUGD && (PlayerInfo[playerid][pFaction] == 0 || FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_ILLEGAL || PlayerInfo[playerid][pLevel] < 3) )
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar este empleo. (OOC: Requiere que tengas contactos y seas nivel 3)"); // Si no es de la mafia o es menor a nivel 3
			if(job == JOB_DRUGF && PlayerInfo[playerid][pLevel] < 3) // para coshechar droga minimo nivel 3
				return SendClientMessage(playerid, COLOR_WHITE, "Granjero: buscamos gente con experiencia, no aceptamos novatos. ¡Sal de aquí! (OOC: Requiere nivel 3)"); // Si es uno nuevo en el servidor o multicuenta

			SetPlayerJob(playerid, job);
			return 1;
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tomar un empleo en cualquier lugar!");
	return 1;
}

//==============================================================================

CMD:dejarempleo(playerid,params[])
{
	new job = PlayerInfo[playerid][pJob];
	
    if(job == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2,"No tienes ningún empleo.");
  	if(jobDuty[playerid])
	  	return SendClientMessage(playerid, COLOR_YELLOW2,"¡No puedes hacerlo mientras estás trabajando!");
    if(!PlayerToPoint(1.0, playerid, JobInfo[job][jTakeX],JobInfo[job][jTakeY],JobInfo[job][jTakeZ]))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes presentar tu renuncia a tu jefe, en tu lugar de trabajo.");

	SavePlayerJobData(playerid, 1, 1); // Guardamos el viejo
	ResetJobVariables(playerid); // Reseteamos todo a cero
	SetPlayerJob(playerid, 0); // Seteamos job nulo
	SendFMessage(playerid, COLOR_YELLOW2, "¡Has dejado tu empleo de %s!", JobInfo[job][jName]);
	return 1;
}

//==============================================================================

LoadPlayerJobData(playerid)
{
	if(PlayerInfo[playerid][pJob])
	{
	    if(PlayerInfo[playerid][pJob] == JOB_FELON)
	    {
     		LoadThiefJobData(playerid);
		}
		else if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
		{
			new	query[128];

		    format(query, sizeof(query), "SELECT * FROM `%s` WHERE pID = %d", JobInfo[PlayerInfo[playerid][pJob]][jTable], PlayerInfo[playerid][pID]);
			mysql_function_query(dbHandle, query, true, "OnLegalJobDataLoad", "i", playerid);
		}
	}
}

//==============================================================================

forward OnLegalJobDataLoad(playerid);
public OnLegalJobDataLoad(playerid)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows)
	{
		cache_get_field_content(0, "pWorkingHours", result); 	PlayerJobInfo[playerid][pWorkingHours] = strval(result);
		cache_get_field_content(0, "pCharge", result); 			PlayerJobInfo[playerid][pCharge] = strval(result);
		cache_get_field_content(0, "pState", result);		 	PlayerJobInfo[playerid][pState] = strval(result);
		cache_get_field_content(0, "pReputation", result); 		PlayerJobInfo[playerid][pReputation] = strval(result);
		cache_get_field_content(0, "pTotalEarnings", result); 	PlayerJobInfo[playerid][pTotalEarnings] = strval(result);
		cache_get_field_content(0, "pLastWorked", PlayerJobInfo[playerid][pLastWorked], 1, 64);

		if(PlayerJobInfo[playerid][pState] == JOB_STATE_FIRED_MISSING)
		{
		    PlayerInfo[playerid][pJob] = 0;
			SendClientMessage(playerid, COLOR_WHITE, "[INFO]: Te han despedido de tu trabajo por faltar demasiado tiempo seguido.");
		}
	}
	else
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "[ERROR]: Error al cargar la información del empleo ID %d desde la base de datos. Reportar a un administrador.", PlayerInfo[playerid][pJob]);
        PlayerInfo[playerid][pJob] = 0;
	}
	return 1;
}

//==============================================================================

SavePlayerJobData(playerid, resigned=0, leftjob=0)
{
	if(PlayerInfo[playerid][pJob])
	{
		if(PlayerInfo[playerid][pJob] == JOB_FELON)
	    {
			SaveThiefJobData(playerid);
		}
		else if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
		{
			new query[256];
		    					
		    if(resigned)
		    	PlayerJobInfo[playerid][pState] = JOB_STATE_RESIGNED;
			if(leftjob)
			    PlayerJobInfo[playerid][pWorkingHours] = 0;

			format(query, sizeof(query), "UPDATE %s SET pWorkingHours=%d, pCharge=%d, pState=%d, pLastWorked='%s', pTotalEarnings=%d, pReputation=%d WHERE `pID`=%d",
				JobInfo[PlayerInfo[playerid][pJob]][jTable],
				PlayerJobInfo[playerid][pWorkingHours],
				PlayerJobInfo[playerid][pCharge],
				PlayerJobInfo[playerid][pState],
				PlayerJobInfo[playerid][pLastWorked],
				PlayerJobInfo[playerid][pTotalEarnings],
				PlayerJobInfo[playerid][pReputation],
				PlayerInfo[playerid][pID]
			);

			mysql_function_query(dbHandle, query, false, "", "");
		}
	}
}

//==============================================================================

SetPlayerJob(playerid, job, admincmd=0)
{
	if(job == JOB_FELON)
 	{
		SetThiefJobForPlayer(playerid);
    }
    else if(GetJobType(job) == JOB_TYPE_LEGAL)
    {
		new query[128];

		format(query, sizeof(query), "SELECT * FROM `%s` WHERE pID = %d", JobInfo[job][jTable], PlayerInfo[playerid][pID]);
		mysql_function_query(dbHandle, query, true, "OnLegalJobDataCheck", "iii", playerid, job, admincmd);
	}
	else if(job == 0)
	{
	    PlayerInfo[playerid][pJob] = 0;
	}
	else
	{
		PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
		PlayerInfo[playerid][pJob] = job;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades!, ahora eres un %s, para ver los comandos disponibles, escribe /ayuda.", JobInfo[job][jName]);
		SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d PayDay/s antes de volver a tomar un empleo.", PlayerInfo[playerid][pJobTime]);
	}
}

//==============================================================================

CMD:setjob(playerid, params[])
{
	new string[128], job, targetid;

	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;
	if(sscanf(params, "ui", targetid, job))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setjob [ID/Jugador] [ID empleo]");
	if(!IsPlayerConnected(targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(job < 0 || job >= sizeof(JobInfo))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Empleo inválido.");

	SavePlayerJobData(targetid, 1); // Guardamos el viejo
	ResetJobVariables(targetid); // Reseteamos todo a cero

	SendFMessage(targetid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} %s te ha seteado el empleo a %d (%s).", GetPlayerNameEx(playerid), job, JobInfo[job][jName]);
	if(PlayerInfo[targetid][pRolePoints] < Job_GetRpPointsNeeded(job))
	    SendFMessage(playerid, COLOR_RED, "[RECORDATORIO]: %s no cumplía con los puntos de rol necesarios para el empleo (%d).", GetPlayerNameEx(targetid), Job_GetRpPointsNeeded(job));
	format(string, sizeof(string), "[Staff]: %s ha seteado el empleo de %s a %d (%s).", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), job, JobInfo[job][jName]);
	AdministratorMessage(COLOR_ADMINCMD, string, 1);

	SetPlayerJob(targetid, job, 1); // Seteamos el nuevo
	return 1;
}

//==============================================================================

forward OnLegalJobDataCheck(playerid, job, admincmd);
public OnLegalJobDataCheck(playerid, job, admincmd)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows) // Alguna vez tuvo el job.
	{
  		cache_get_field_content(0, "pState", result);

		if(strval(result) == JOB_STATE_FIRED && !admincmd) // Fue despedido y fue mediante /tomarempleo y no mediante /setjob
  		{
  		    SendFMessage(playerid, COLOR_WHITE, "Empleador: Fuiste despedido de este lugar por mal desempeño, %s, y no te queremos devuelta.", GetPlayerNameEx(playerid));
		}
		else if(strval(result) == JOB_STATE_FIRED_MISSING && !admincmd)
		{
  		    SendFMessage(playerid, COLOR_WHITE, "Empleador: Fuiste despedido de este lugar por faltar demasiado tiempo al trabajo, %s, y no te queremos devuelta.", GetPlayerNameEx(playerid));
		}
		else
  		{
  		    PlayerJobInfo[playerid][pState] = JOB_STATE_ACTIVE;
			cache_get_field_content(0, "pWorkingHours", result); 	PlayerJobInfo[playerid][pWorkingHours] = strval(result);
   			cache_get_field_content(0, "pCharge", result); 			PlayerJobInfo[playerid][pCharge] = strval(result);
			cache_get_field_content(0, "pReputation", result); 		PlayerJobInfo[playerid][pReputation] = strval(result);
			cache_get_field_content(0, "pTotalEarnings", result);   PlayerJobInfo[playerid][pTotalEarnings] = strval(result);
			UpdatePlayerJobLastWorked(playerid);

			PlayerInfo[playerid][pJob] = job;
			PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades, ahora eres un %s!. Para saber los comandos disponibles mira en /ayuda, seccion [Empleo].", JobInfo[job][jName]);
			SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d paydays antes de volver a tomar otro empleo.", PlayerInfo[playerid][pJobTime]);
			if(!admincmd)
			{
				SendFMessage(playerid, COLOR_WHITE, "Empleador: %s, ¿sos vos?. Es bueno que hayas vuelto. Esperemos que esta vez no renuncies.", GetPlayerNameEx(playerid));
                SendClientMessage(playerid, COLOR_WHITE, "Recuerda que, ya que habías renunciado, perdiste toda antiguedad acumulada en el trabajo.");
			}
		}
	}
	else // Nunca lo tuvo
	{
		new query[128];

		PlayerJobInfo[playerid][pWorkingHours] = 0;
		PlayerJobInfo[playerid][pCharge] = 1;
		PlayerJobInfo[playerid][pState] = JOB_STATE_ACTIVE;
		PlayerJobInfo[playerid][pReputation] = 0;
  		UpdatePlayerJobLastWorked(playerid);
		PlayerInfo[playerid][pJob] = job;
		PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades, ahora eres un %s!. Para saber los comandos disponibles mira en /ayuda, seccion [Empleo].", JobInfo[job][jName]);
		SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d paydays antes de volver a tomar otro empleo.", PlayerInfo[playerid][pJobTime]);
		if(!admincmd)
		{
			SendFMessage(playerid, COLOR_WHITE, "Empleador: Bienvenido a nuestra empresa, %s. Empezarás como %s. ¡Suerte y a trabajar!", GetPlayerNameEx(playerid), GetJobChargeName(job, PlayerJobInfo[playerid][pCharge]));
		}
		format(query, sizeof(query), "INSERT INTO `%s` (`pID`, `pLastWorked`) VALUES ('%d', '%s')", JobInfo[job][jTable], PlayerInfo[playerid][pID], PlayerJobInfo[playerid][pLastWorked]);
		mysql_function_query(dbHandle, query, false, "", "");
	}
	return 1;
}

//==============================================================================

GetDateString()
{
	new year, month, day, hour, minute, second, str[64];

	getdate(year, month, day);
	gettime(hour, minute, second);

	format(str, sizeof(str), "%02d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

	return str;
}

//==============================================================================

UpdatePlayerJobLastWorked(playerid)
{
	new str[64];
	format(str, sizeof(str), "%s", GetDateString());
	strmid(PlayerJobInfo[playerid][pLastWorked], str, 0, strlen(str), 255);
}

//==============================================================================

CMD:verempleo(playerid, params[])
{
	if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
	{
	    new content[300];

		format(content, sizeof(content), "Empleo: %s\nCargo: %s\nTrabajos realizados: %d\nUltimo día de trabajo: %s\nIngresos totales: $%d\nImagen laboral: %s\nEstado laboral: %s",
		    JobInfo[PlayerInfo[playerid][pJob]][jName],
		    GetJobChargeName(PlayerInfo[playerid][pJob], PlayerJobInfo[playerid][pCharge]),
		    PlayerJobInfo[playerid][pWorkingHours],
		    PlayerJobInfo[playerid][pLastWorked],
		    PlayerJobInfo[playerid][pTotalEarnings],
			GetJobReputationString(PlayerJobInfo[playerid][pReputation]),
   			GetJobStateString(PlayerJobInfo[playerid][pState])
		);

	    ShowPlayerDialog(playerid, DLG_JOB_INFO_1, DIALOG_STYLE_MSGBOX, "Información de tu empleo", content, "Cerrar", "");
	}
	return 1;
}

//==============================================================================

stock GetJobReputationString(reputation)
{
	new str[64];

    if(reputation > 300)
        format(str, sizeof(str), "{00FF00}Excelente{a9c4e4}"); // Verde claro
    else if(reputation > 200)
    	format(str, sizeof(str), "{97D000}Muy buena{a9c4e4}"); // Verde turbio
    else if(reputation > 100)
    	format(str, sizeof(str), "{CFFF00}Buena{a9c4e4}"); // Verde amarillo
    else if(reputation >= 0)
    	format(str, sizeof(str), "{FFFF00}Neutral{a9c4e4}"); // Amarillo
    else if(reputation > -70)
    	format(str, sizeof(str), "{FFB900}Mala{a9c4e4}"); // Naranja claro
    else if(reputation > -140)
    	format(str, sizeof(str), "{FF5900}Muy mala{a9c4e4}"); // Naranja rojizo
    else
    	format(str, sizeof(str), "{FF0000}Horrible{a9c4e4}"); // Rojo

	return str;
}

//==============================================================================

stock GetJobStateString(status)
{
	new str[64];

	if(status == JOB_STATE_ACTIVE)
	    format(str, sizeof(str), "{00FF00}En actividad{a9c4e4}"); // Verde
	else if(status == JOB_STATE_FIRED)
	    format(str, sizeof(str), "{FF0000}Despedido - Mal desempeño{a9c4e4}"); // Rojo
	else if(status == JOB_STATE_FIRED_MISSING)
	    format(str, sizeof(str), "{FF0000}Despedido - No asiste a trabajar{a9c4e4}"); // Rojo
	else if(status == JOB_STATE_RESIGNED)
        format(str, sizeof(str), "{FFFF00}Renunció{a9c4e4}"); // Amarillo
	else if(status == JOB_STATE_NONE)
        format(str, sizeof(str), "{868282}Nunca trabajó{a9c4e4}"); // Gris

	return str;
}

//==============================================================================

CMD:consultarempleo(playerid, params[])
{
	for(new job = 1; job < sizeof(JobInfo); job++)
	{
	    if(GetJobType(job) == JOB_TYPE_LEGAL)
	    {
			if(PlayerToPoint(1.0, playerid, JobInfo[job][jTakeX], JobInfo[job][jTakeY], JobInfo[job][jTakeZ]))
			{
			    if(job == PlayerInfo[playerid][pJob])
			        return SendClientMessage(playerid, COLOR_YELLOW2, "Actualmente tienes este empleo, utiliza /verempleo.");

			    new query[128];

			    format(query, sizeof(query), "SELECT * FROM `%s` WHERE pID = %d", JobInfo[job][jTable], PlayerInfo[playerid][pID]);
				mysql_function_query(dbHandle, query, true, "OnPlayerInvestJob", "ii", playerid, job);
				return 1;
			}
		}
	}
	return 1;
}

//==============================================================================

forward OnPlayerInvestJob(playerid, job);
public OnPlayerInvestJob(playerid, job)
{
	new rows,
		fields,
		result[32],
		stateResult,
		workingHoursResult,
		chargeResult,
		reputationResult,
		totalEarningsResult,
		lastWorkedResult[64],
		content[400],
		auxInformation[200] = "";

	cache_get_data(rows, fields);

	if(rows) // Alguna vez tuvo el job.
	{
  		cache_get_field_content(0, "pState", result);   			stateResult = strval(result);
		cache_get_field_content(0, "pWorkingHours", result); 		workingHoursResult = strval(result);
		cache_get_field_content(0, "pCharge", result); 				chargeResult = strval(result);
		cache_get_field_content(0, "pReputation", result); 			reputationResult = strval(result);
		cache_get_field_content(0, "pTotalEarnings", result); 		totalEarningsResult = strval(result);
		cache_get_field_content(0, "pLastWorked", lastWorkedResult, 1 ,64);

		switch(stateResult)
		{
		    case JOB_STATE_FIRED:
		        format(auxInformation, sizeof(auxInformation), "Has sido despedido de este lugar por mal desempeño y no podrás tomar nuevamente el trabajo.");
			case JOB_STATE_FIRED_MISSING:
			    format(auxInformation, sizeof(auxInformation), "Has sido despedido de este lugar por faltar al trabajo y no podrás tomarlo nuevamente.");
			case JOB_STATE_RESIGNED:
				format(auxInformation, sizeof(auxInformation), "Como habías renunciado, volverás a entrar con tu último cargo pero perderás toda antiguedad acumulada.");
		}
		format(content, sizeof(content), "Empleo: %s\nCargo: %s\nTrabajos realizados: %d\nUltimo día de trabajo: %s\nIngresos totales: $%d\nImagen laboral: %s\nEstado laboral: %s\n\n%s",
		    JobInfo[job][jName],
		    GetJobChargeName(job, chargeResult),
		    workingHoursResult,
		    lastWorkedResult,
		    totalEarningsResult,
			GetJobReputationString(reputationResult),
   			GetJobStateString(stateResult),
	  		auxInformation
		);
	}
	else // Nunca lo tuvo
	{
	    format(auxInformation, sizeof(auxInformation), "En esta empresa tendrás la oportunidad de escalar puestos y mejorar tus ganancias\nsi tienes un buen desempeño. Pero también ten en cuenta que te pueden echar si tu desempeño es malo.");
		format(content, sizeof(content), "Empleo: %s\nCargo en el que comienzas: %s\nGanancias iniciales por trabajo: $%d\n\n%s",
		    JobInfo[job][jName],
		    GetJobChargeName(job, 1),
		    GetJobBaseSalary(job),
	  		auxInformation
		);
	}
	ShowPlayerDialog(playerid, DLG_JOB_INFO_2, DIALOG_STYLE_MSGBOX, "Información del empleo", content, "Cerrar", "");
	return 1;
}

//==============================================================================

Job_GiveReputation(playerid, reputation)
{
    PlayerJobInfo[playerid][pReputation] += reputation;

	if(PlayerJobInfo[playerid][pReputation] < -210)
	{
	    SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Has sido despedido de tu empleo '%s' por mal desempeño en tus tareas laborales.", JobInfo[PlayerInfo[playerid][pJob]][jName]);
		PlayerJobInfo[playerid][pState] = JOB_STATE_FIRED;
		SavePlayerJobData(playerid);
		ResetJobVariables(playerid);
		SetPlayerJob(playerid, 0);
	}
}
