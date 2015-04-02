#if defined _marp_playerjob_included
	#endinput
#endif
#define _marp_playerjob_included

#define DLG_JOB_INFO_1 			10036
#define DLG_JOB_INFO_2 			10037

stock LoadPlayerJobData(playerid)
{
	if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
	{
		new	query[128];
		
	    format(query, sizeof(query), "SELECT * FROM `%s` WHERE pID = %d", JobInfo[PlayerInfo[playerid][pJob]][jTable], PlayerInfo[playerid][pID]);
		mysql_function_query(dbHandle, query, true, "OnPlayerJobDataLoad", "i", playerid);
	}
	return 1;
}

forward OnPlayerJobDataLoad(playerid);
public OnPlayerJobDataLoad(playerid)
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
	}
	else // Tiene un job legal pero no tiene su correspondiente registro en la DB? (No debería de pasar) Error, reportar. Y le seteamos job NULO, para evitar inconvenientes si quisiese usarlo.
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "[ERROR]: Error al cargar la información del empleo ID %d desde la base de datos. Reportar a un administrador.", PlayerInfo[playerid][pJob]);
        PlayerInfo[playerid][pJob] = 0;
	}
}

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
		    if(job == JOB_TAXI && (PlayerInfo[playerid][pCarLic] == 0))
		        return SendClientMessage(playerid, COLOR_WHITE, "No puedo emplearte si no tienes licencia de manejo, hasta luego.");
            if(job == JOB_DRUGD && (PlayerInfo[playerid][pFaction] == 0 || FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_ILLEGAL || PlayerInfo[playerid][pLevel] < 3) )
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar este empleo. (OOC: Requiere que tengas contactos y seas nivel 3)"); // Si no es de la mafia o es menor a nivel 3
			if(job == JOB_DRUGF && PlayerInfo[playerid][pLevel] < 3) // para coshechar droga minimo nivel 3
				return SendClientMessage(playerid, COLOR_WHITE, "Granjero: buscamos gente con experiencia, no aceptamos novatos. ¡Sal de aquí! (OOC: Requiere nivel 3)"); // Si es uno nuevo en el servidor o multicuenta

			if(GetJobType(job) == JOB_TYPE_LEGAL) // Para comprobar si ya tuvo ese empleo y si por ende ya tiene un registro en DB asociado a ese job.
			{
				SetPlayerJob(playerid, job);
			}
			else
   			{
				if(job == JOB_FELON)
                	createThiefJob(playerid);
                	
				PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
				PlayerInfo[playerid][pJob] = job;
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades!, ahora eres un %s, para ver los comandos disponibles, escribe /ayuda.", JobInfo[job][jName]);
				SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d PayDay/s antes de volver a tomar un empleo.", PlayerInfo[playerid][pJobTime]);
			}
			return 1;
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tomar un empleo en cualquier lugar!");
	return 1;
}

CMD:setjob(playerid, params[])
{
	new string[128], job, targetid;

	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;
	if(sscanf(params, "ui", targetid, job))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setjob [ID/Jugador] [id empleo]");
	if(!IsPlayerConnected(targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(job < 0 || job >= 20)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Empleo inválido.");

	SendFMessage(targetid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} %s te ha seteado el empleo a %d (%s).", GetPlayerNameEx(playerid), job, JobInfo[job][jName]);
	format(string, sizeof(string), "[Staff]: %s ha seteado el empleo de %s a %d (%s).", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), job, JobInfo[job][jName]);
	AdministratorMessage(COLOR_ADMINCMD, string, 1);

	if(GetJobType(PlayerInfo[targetid][pJob]) == JOB_TYPE_LEGAL) // Si es legal, lo ponemos como que renunció.
	{
	    PlayerJobInfo[targetid][pState] = JOB_STATE_RESIGNED;
		SavePlayerJobData(targetid); // Guardamos la información del viejo, si fuese legal.
	}
    PlayerInfo[targetid][pJob] = job;

	if(GetJobType(job) == JOB_TYPE_LEGAL) // Para comprobar si ya tuvo ese empleo y si por ende ya tiene un registro en DB asociado a ese job.
		SetPlayerJob(targetid, job, 1);
	else if(job == JOB_FELON)
		createThiefJob(targetid);
	return 1;
}

stock SetPlayerJob(playerid, job, admincmd=0)
{
    new query[128];

    format(query, sizeof(query), "SELECT * FROM `%s` WHERE pID = %d", JobInfo[job][jTable], PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnPlayerJobDataCheck", "iii", playerid, job, admincmd);
	return 1;
}

forward OnPlayerJobDataCheck(playerid, job, admincmd);
public OnPlayerJobDataCheck(playerid, job, admincmd)
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
  		    SendFMessage(playerid, COLOR_WHITE, "Empleador: Fuiste despedido de este lugar %s, no te queremos devuelta.", GetPlayerNameEx(playerid));
		}
		else
  		{
  		    PlayerJobInfo[playerid][pState] = JOB_STATE_ACTIVE;
			PlayerJobInfo[playerid][pWorkingHours] = 0; // Al renunciar, se borra la antiguedad.
			cache_get_field_content(0, "pCharge", result); 			PlayerJobInfo[playerid][pCharge] = strval(result);
			cache_get_field_content(0, "pReputation", result); 		PlayerJobInfo[playerid][pReputation] = strval(result);
			cache_get_field_content(0, "pTotalEarnings", result);   PlayerJobInfo[playerid][pTotalEarnings] = strval(result);
			cache_get_field_content(0, "pLastWorked", PlayerJobInfo[playerid][pLastWorked], 1, 64);
			
			PlayerInfo[playerid][pJob] = job;
			PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades, ahora eres un %s!. Para ver los comandos disponibles escribe /ayuda.", JobInfo[job][jName]);
			SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d PayDays antes de volver a tomar un empleo.", PlayerInfo[playerid][pJobTime]);
			if(!admincmd)
			{
				SendFMessage(playerid, COLOR_WHITE, "Empleador: %s, ¿sos vos?. Es bueno que hayas vuelto. Esperemos que esta vez no renuncies.", GetPlayerNameEx(playerid));
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
		SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades!, ahora eres un %s, para ver los comandos disponibles, escribe /ayuda.", JobInfo[job][jName]);
		SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d PayDay/s antes de volver a tomar un empleo.", PlayerInfo[playerid][pJobTime]);
		if(!admincmd)
			SendFMessage(playerid, COLOR_WHITE, "Empleador: Bienvenido a nuestra empresa, %s. Empezarás como %s. ¡Suerte y a trabajar!", GetPlayerNameEx(playerid), GetJobChargeName(job, PlayerJobInfo[playerid][pCharge]));
		format(query, sizeof(query), "INSERT INTO `%s` (`pID`, `pLastWorked`) VALUES ('%d', '%s')", JobInfo[job][jTable], PlayerInfo[playerid][pID], PlayerJobInfo[playerid][pLastWorked]);
		mysql_function_query(dbHandle, query, false, "", "");
	}
}

stock UpdatePlayerJobLastWorked(playerid)
{
	new str[64];
	format(str, sizeof(str), "%s", GetDateString());
	strmid(PlayerJobInfo[playerid][pLastWorked], str, 0, strlen(str), 255);
}

forward SavePlayerJobData(playerid);
public SavePlayerJobData(playerid)
{
	if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
	{
		new query[256];

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
	return 1;
}

CMD:verempleo(playerid, params[])
{
	if(GetJobType(PlayerInfo[playerid][pJob]) == JOB_TYPE_LEGAL)
	{
	    new content[300];
	    
		format(content, sizeof(content), "Empleo: %s\nCargo: %s\nDías trabajados: %d\nUltimo día de trabajo: %s\nIngresos totales: $%d\nImagen laboral: %s\nEstado laboral: %s",
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
    else if(reputation > -100)
    	format(str, sizeof(str), "{FFB900}Mala{a9c4e4}"); // Naranja claro
    else if(reputation > -200)
    	format(str, sizeof(str), "{FF5900}Muy mala{a9c4e4}"); // Naranja rojizo
    else
    	format(str, sizeof(str), "{FF0000}Horrible{a9c4e4}"); // Rojo
        
	return str;
}

stock GetJobStateString(status)
{
	new str[64];
	
	if(status == JOB_STATE_ACTIVE)
	    format(str, sizeof(str), "{00FF00}En actividad{a9c4e4}"); // Verde
	else if(status == JOB_STATE_FIRED)
	    format(str, sizeof(str), "{FF0000}Despedido{a9c4e4}"); // Rojo
	else if(status == JOB_STATE_RESIGNED)
        format(str, sizeof(str), "{FFFF00}Renunció{a9c4e4}"); // Amarillo
	else if(status == JOB_STATE_NONE)
        format(str, sizeof(str), "{868282}Nunca trabajó{a9c4e4}"); // Gris

	return str;
}

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
	SendClientMessage(playerid, COLOR_YELLOW2, "No estas en un lugar donde se contraten empleados.");
	return 1;
}

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
		content[300],
		auxInformation[128] = "";

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
		        format(auxInformation, sizeof(auxInformation), "Has sido despedido de este lugar y no podrás tomar nuevamente el trabajo.");
			case JOB_STATE_RESIGNED:
				format(auxInformation, sizeof(auxInformation), "Como habías renunciado, volverás a entrar con tu último cargo pero perderás toda antiguedad acumulada.");
		}
		format(content, sizeof(content), "Empleo: %s\nCargo: %s\nDías trabajados: %d\nUltimo día de trabajo: %s\nIngresos totales: $%d\nImagen laboral: %s\nEstado laboral: %s\n\n%s",
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
	    format(auxInformation, sizeof(auxInformation), "En esta empresa se valora el buen desempeño laboral, como también se castiga el malo.");
		format(content, sizeof(content), "Empleo: %s\nCargo en el que comienzas: %s\nGanancias iniciales por día: %d\n\n%s",
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

#define JOB_GARB_CRONOMETRO  	1

new pCronometro[MAX_PLAYERS],
	pCronometroTimer[MAX_PLAYERS],
	PlayerText:PTD_Cronometro[MAX_PLAYERS];

CrearCronometro(playerid, type, time)
{
	if(pCronometro[playerid] == 0 && pCronometroTimer[playerid] == 0 && time > 0)
	{
		PTD_Cronometro[playerid] = CreatePlayerTextDraw(playerid, 516.000000, 166.687500, " ");
		PlayerTextDrawLetterSize(playerid, PTD_Cronometro[playerid], 0.464500, 1.621875);
		PlayerTextDrawAlignment(playerid, PTD_Cronometro[playerid], 1);
		PlayerTextDrawColor(playerid, PTD_Cronometro[playerid], -1);
		PlayerTextDrawSetShadow(playerid, PTD_Cronometro[playerid], 0);
		PlayerTextDrawSetOutline(playerid, PTD_Cronometro[playerid], -1);
		PlayerTextDrawBackgroundColor(playerid, PTD_Cronometro[playerid], 255);
		PlayerTextDrawFont(playerid, PTD_Cronometro[playerid], 1);
		PlayerTextDrawSetProportional(playerid, PTD_Cronometro[playerid], 1);
		PlayerTextDrawShow(playerid, PTD_Cronometro[playerid]);
		pCronometro[playerid] = time;
		pCronometroTimer[playerid] = SetTimerEx("Cronometro", 1000, true, "ii", playerid, type);
		return 1;
	}
	return 0;
}

BorrarCronometro(playerid)
{
	if(pCronometroTimer[playerid] != 0)
	{
		KillTimer(pCronometroTimer[playerid]);
    	PlayerTextDrawDestroy(playerid, PTD_Cronometro[playerid]);
		pCronometro[playerid] = 0;
		pCronometroTimer[playerid] = 0;
	}
}

forward Cronometro(playerid, type);
public Cronometro(playerid, type)
{
	if(pCronometro[playerid] <= 0)
	{
	 	switch(type)
	 	{
	 	    case JOB_GARB_CRONOMETRO:
	 	        GarbJob_TravelTimeLimit(playerid);
		}
	    BorrarCronometro(playerid);
	}
	else
	{
		new minutes, segs, str[32];

		if(pCronometro[playerid] >= 60)
		{
		    minutes = floatround(pCronometro[playerid] / 60, floatround_floor);
		    segs = pCronometro[playerid] - minutes * 60;
		    format(str, sizeof(str), "Tiempo: %02dm%02ds", minutes, segs);
		    PlayerTextDrawSetString(playerid, PTD_Cronometro[playerid], str);
		}
		else
	 	{
		 	format(str, sizeof(str), "Tiempo: %02ds", pCronometro[playerid]);
		    PlayerTextDrawSetString(playerid, PTD_Cronometro[playerid], str);
		}
		pCronometro[playerid]--;
	}
	return 1;
}
