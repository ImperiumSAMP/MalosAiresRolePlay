#if defined _isamp_jobs_included
	#endinput
#endif
#define _isamp_jobs_included

// Misiones.
#define JOB_EVENT_TIMER         55//25  // Tiempo en minutos minimo entre eventos de empleo.
#define JOB_EVENT_MAXTIMER      90//60  // Tiempo extra random, varía entre 0 y la cantidad especificada y se añaden al mínimo.

//====[EMPLEOS]=================================================================
//#define JOB_MECH              1 		// Mecánicos.
#define JOB_TAXI             	2 		// Conductor.
#define JOB_FARM             	3 		// Granjero.
#define JOB_TRAN                4       // Transportista.
#define JOB_GARB                5       // Basurero.
#define JOB_FELON               6
#define JOB_DRUGF          		7
#define JOB_DRUGD          		8

#define FAC_TYPE_ILLEGAL        0
#define FAC_TYPE_GOV            1
#define FAC_TYPE_LEGAL          2
#define FAC_TYPE_GANG	        3

#define JOB_TAXI_MAXPASSENGERS  10

#define JOB_FARM_MAXPRODS       20
#define JOB_FARM_PRODVALUE      200  
#define JOB_DRUGF_MAXPRODS      30
#define JOB_DRUGF_PRODVALUE     160

#define JOB_TRAN_MAXPRODS       8 		// Cargas máximas que se pueden transportar.
#define JOB_TRAN_PRODVALUE      500    	// VALOR POR PAQUETE

#define JOB_GARB_MONEY       	4000 	// MONEY + random(MONEY / 2)

#define JOB_EXP_MULTIPLIER      3
//
#define BLD_PMA                 2
#define BLD_HOSP                5
#define BLD_HOSP2               11
#define BLD_SIDE                31
#define BLD_MAN                 36

#define JOB_WAITTIME            5  // Número de PayDays que tienes que esperar para poder tomar otro empleo.
#define JOB_NAME_FIELD_MAX		32

//Enums

enum jInf {
	jName[JOB_NAME_FIELD_MAX],
	jType,
	Float:jTakeX,
	Float:jTakeY,
	Float:jTakeZ,
	jTakeW,
	jTakeI,
	jTakePID,
	jSkin,
};
new JobInfo[20][jInf];

//Coordinates

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

forward jobBreakTimer(playerid, job);

//Variables generales:

new 
	bool:jobDuty[MAX_PLAYERS],
	LastCP[MAX_PLAYERS],
	CollectedProds[MAX_PLAYERS],
	bool:carryingProd[MAX_PLAYERS],
	jobBreak[MAX_PLAYERS];

stock jobRequiresVehicle(jobid){
	return jobid == JOB_FARM || jobid == JOB_DRUGF || jobid == JOB_TRAN || jobid == JOB_GARB;
}
	
//Funciones DB
stock LoadJobs() {
	new query[128], id = 1;
	while(id < sizeof(JobInfo)) {
	    format(query, sizeof(query),"SELECT * FROM `jobs` WHERE `id`=%d LIMIT 1", id);
  		mysql_function_query(dbHandle, query, true, "OnJobDataLoad", "i", id);
		id++;
	}
	return 1;
}

forward OnJobDataLoad(id);
public OnJobDataLoad(id) {
   	new
   	    string[128],
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

	if(rows) {
		cache_get_field_content(0, "jTakeW", result); 				JobInfo[id][jTakeW] 			= strval(result);
		cache_get_field_content(0, "jType", result); 				JobInfo[id][jType] 				= strval(result);
		cache_get_field_content(0, "jTakeI", result);				JobInfo[id][jTakeI]				= strval(result);
		cache_get_field_content(0, "jSkin", result); 				JobInfo[id][jSkin] 				= strval(result);

		cache_get_field_content(0, "jName", 						JobInfo[id][jName], 1, JOB_NAME_FIELD_MAX);

		cache_get_field_content(0, "jTakeX", result); 				JobInfo[id][jTakeX] 			= floatstr(result);
		cache_get_field_content(0, "jTakeY", result); 				JobInfo[id][jTakeY] 			= floatstr(result);
		cache_get_field_content(0, "jTakeZ", result); 				JobInfo[id][jTakeZ] 			= floatstr(result);
				
		if(JobInfo[id][jType] == 0) {
			JobInfo[id][jTakePID] = CreateDynamicPickup(1274, 1, JobInfo[id][jTakeX], JobInfo[id][jTakeY], JobInfo[id][jTakeZ], JobInfo[id][jTakeW], JobInfo[id][jTakeI], -1);
            format(string, sizeof(string), "Escribe /tomarempleo \npara tomar el empleo de %s", JobInfo[id][jName]);
            CreateDynamic3DTextLabel(string, COLOR_WHITE, JobInfo[id][jTakeX], JobInfo[id][jTakeY], JobInfo[id][jTakeZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
		}
	}
	return 1;
}


//Comandos de jobs
CMD:comenzar(playerid,params[])
	cmd_trabajar(playerid, params);

CMD:trabajar(playerid,params[]) {
	new job = PlayerInfo[playerid][pJob];
	    
	if(PlayerInfo[playerid][pFaction] == FAC_MECH) {
		SendClientMessageToAll(COLOR_LIGHTGREEN, "Anuncio: un mecánico se encuentra en servicio (Tel: 555).");
		jobDuty[playerid] = true;
	} else if(job != 0) {
		if(!jobDuty[playerid]) {
	        if(PlayerInfo[playerid][pCantWork] == 0) {
			    if(job == JOB_TAXI) {

			    	if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_TAXI) {
						SendClientMessageToAll(COLOR_LIGHTGREEN, "Anuncio: un taxista se encuentra en servicio (Tel: 444).");
						jobDuty[playerid] = true;
			       	} else {
		       	    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un taxi!");
		       	    	return 1;
			       	}
			    } else if(job == JOB_FARM) {
			    	if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_FARM) {
			    	    SendClientMessage(playerid, COLOR_WHITE, "Dirígete a los puntos rojos para cosechar, al finalizar deberás traer la cosecha y tipear /terminar para descargarla.");
                        SendClientMessage(playerid, COLOR_WHITE, "Puedes descargar los materiales cuando quieras, pero te pagarán acorde a la cantidad y no podras volver a trabajar durante este día de pago.");
						new rCP = -1;
						while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid]) {
					 		rCP = random(sizeof(JOB_FARM_POS));
						}
						LastCP[playerid] = rCP;
						SetPlayerCheckpoint(playerid, JOB_FARM_POS[rCP][0], JOB_FARM_POS[rCP][1], JOB_FARM_POS[rCP][2], 5.4);
						jobDuty[playerid] = true;
						PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
						SetEngine(GetPlayerVehicleID(playerid), 1);
			       	} else {
		       	    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a una cosechadora!");
		       	    	return 1;
			       	}
			    } else if(job == JOB_DRUGF) {
			    	if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_DRUGF) {
			    	    SendClientMessage(playerid, COLOR_WHITE, "Dirígete a los puntos rojos para cosechar, al finalizar deberás traer la materia prima y tipear /terminar.");
						SendClientMessage(playerid, COLOR_WHITE, "Solo recibirás la paga si terminas completamente con tu trabajo.");
						new rCP = -1;
						while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid]) {
					 		rCP = random(sizeof(JOB_DRUGF_POS));
						}
						LastCP[playerid] = rCP;
						SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], 5.4);
						jobDuty[playerid] = true;
						PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
						SetEngine(GetPlayerVehicleID(playerid), 1);
			       	} else {
		       	    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a una cosechadora!");
		       	    	return 1;
			       	}
			    } else if(job == JOB_DRUGD) {
			        SendClientMessage(playerid, COLOR_WHITE, "Súbete a un vehículo con maletero y dirígete a la granja de drogas. Recuerda que necesitarás algo de espacio en él.");
			        SendClientMessage(playerid, COLOR_WHITE, "Una vez allí, tipea /comprar para comprar las bolsas de materia prima.");
			        SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][0], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][1], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][2], 5.4);
				} else if(job == JOB_TRAN) {
			    	if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_TRAN) {
			    	    SendClientMessage(playerid, COLOR_WHITE, "Entrega los paquetes en los puntos rojos del mapa y vuelve a buscar más o bien utiliza /terminar cuando lo desees.");
                        SendClientMessage(playerid, COLOR_WHITE, "Te pagarán acorde a la cantidad de paquetes entregados y no podras volver a trabajar durante este día de pago.");
						SetPlayerCheckpoint(playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2], 5.4);
						jobDuty[playerid] = true;
						SetEngine(GetPlayerVehicleID(playerid), 1);
						PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
			       	} else {
		       	    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un camión!");
		       	    	return 1;
			       	}
			    } else if(job == JOB_GARB) {
			    	if(getVehicleType(GetPlayerVehicleID(playerid)) == VEH_JOB && getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_GARB) {
						new
						    gbCP = 0,
							route = random(2);
						    
                        SetPVarInt(playerid, "jobVehicle", GetPlayerVehicleID(playerid));
             			jobDuty[playerid] = true;
             			if(route == 0) {
			 	 			SetPlayerCheckpoint(playerid, JOB_GARB_POS_R0[gbCP][0], JOB_GARB_POS_R0[gbCP][1], JOB_GARB_POS_R0[gbCP][2], 5.4);
						} else if(route == 1) {
						    SetPlayerCheckpoint(playerid, JOB_GARB_POS_R1[gbCP][0], JOB_GARB_POS_R1[gbCP][1], JOB_GARB_POS_R1[gbCP][2], 5.4);
						}
						PlayerActionMessage(playerid, 15.0, "ha encendido el motor del vehículo.");
						SetEngine(GetPlayerVehicleID(playerid), 1);
						SendClientMessage(playerid, COLOR_WHITE, "Completa el siguiente recorrido para dejar la ciudad libre de basura, al final, serás recompensado por tu trabajo.");
			       	} else {
		       	    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ingresar a un camión recolector!");
		       	    	return 1;
			       	}
			    } else {
					return 1;
				}
			    if(PlayerInfo[playerid][pJobAllowed] == 1 && JobInfo[job][jSkin] > 0) {
					SetPlayerSkin(playerid, JobInfo[job][jSkin]);
				}
			} else {
			    SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya has trabajado lo suficiente! vé, y espera hasta el próximo día de pago.");
			}
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya te encuentras trabajando!");
		}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún empleo!");
	}
	return 1;
}

CMD:terminar(playerid,params[]) {
	new
	    job = PlayerInfo[playerid][pJob];

    if(job == 0)
		return 1;
		
    if(!jobDuty[playerid]) {
    	SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras trabajando!");
		return 1;
	}
	
	if(PlayerInfo[playerid][pJob] == JOB_FARM) {
		if(PlayerToPoint(20.0, playerid, JOB_FARM_POS[17][0], JOB_FARM_POS[17][1], JOB_FARM_POS[17][2])) {
            if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_FARM) {
            	PlayerActionMessage(playerid, 15.0, "descarga todo el producto y estaciona la cosechadora.");
				SendFMessage(playerid, COLOR_LIGHTBLUE, "Has recolectado %d toneladas por lo tanto recibirás $%d en el próximo día de pago.", CollectedProds[playerid], CollectedProds[playerid] * JOB_FARM_PRODVALUE);
			    PlayerInfo[playerid][pCantWork] = 1;
			    LastCP[playerid] = -1;
			    PlayerInfo[playerid][pPayCheck] += CollectedProds[playerid] * JOB_FARM_PRODVALUE;
			    CollectedProds[playerid] = 0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			} else {
			    SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar adentro de una cosechadora!");
		    	return 1;
			}
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve y descarga los productos en la zona indicada!");
		    return 1;
		}
	} else if(PlayerInfo[playerid][pJob] == JOB_DRUGF) {
	
		if(!PlayerToPoint(20.0, playerid, JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][0], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][1], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][2]))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve y descarga los productos en la zona indicada!");

        if(getVehicleJob(GetPlayerVehicleID(playerid)) != JOB_DRUGF)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en una cosechadora!");
	  
	    if(LastCP[playerid] != sizeof(JOB_DRUGF_POS) - 1)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No has terminado con tu trabajo!, vé y continua cosechando.");

		PlayerActionMessage(playerid, 15.0, "descarga el producto y estaciona la cosechadora.");
		SendFMessage(playerid, COLOR_LIGHTBLUE, "Has recolectado 5 bolsas de materia prima, por lo tanto recibirás $%d en el próximo día de pago.", CollectedProds[playerid] * JOB_DRUGF_PRODVALUE);
	    PlayerInfo[playerid][pCantWork] = 1;
	    LastCP[playerid] = -1;
	    ServerInfo[sDrugRawMats] += 5;
	    GivePlayerCash(playerid, CollectedProds[playerid] * JOB_DRUGF_PRODVALUE);
	    CollectedProds[playerid] = 0;
	
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	} else if(PlayerInfo[playerid][pJob] == JOB_TRAN) {
		if(PlayerToPoint(20.0, playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2])) {
			if(getVehicleJob(GetPlayerVehicleID(playerid)) == JOB_TRAN) {
			    SendFMessage(playerid, COLOR_WHITE, "Has descargado %d paquetes por lo tanto recibirás $%d en el próximo día de pago.", CollectedProds[playerid], CollectedProds[playerid] * JOB_TRAN_PRODVALUE);
			    PlayerInfo[playerid][pCantWork] = 1;
				carryingProd[playerid] = false;
			    LastCP[playerid] = -1;
			    PlayerInfo[playerid][pPayCheck] += CollectedProds[playerid] * JOB_TRAN_PRODVALUE;
			    CollectedProds[playerid] = 0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
				PlayerActionMessage(playerid, 15.0, "estaciona el camión.");
			} else {
			    SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar adentro de un camión!");
		    	return 1;
			}
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2, "¡Ve a la zona indicada!");
		    return 1;
		}
	}
	if(PlayerInfo[playerid][pJobAllowed] == 1) {
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	}
    jobDuty[playerid] = false;
	return 1;
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
	
	for(new id = 1; id < sizeof(JobInfo); id++)
	{
		if(PlayerToPoint(1.0, playerid,JobInfo[id][jTakeX], JobInfo[id][jTakeY], JobInfo[id][jTakeZ]))
		{
		    if(id == JOB_TAXI && (PlayerInfo[playerid][pCarLic] == 0))
		        return SendClientMessage(playerid, COLOR_WHITE, "No puedo emplearte si no tienes licencia de manejo, hasta luego.");
		    if(JobInfo[id][jType] != 0)
               	return 1;
            if(id == JOB_DRUGD && (FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_ILLEGAL || PlayerInfo[playerid][pLevel] < 3) )
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar este empleo. (OOC: Requiere que tengas contactos y seas nivel 3)"); // Si no es de la mafia o es menor a nivel 3
			if(id == JOB_DRUGF && PlayerInfo[playerid][pLevel] < 3) // para coshechar droga minimo nivel 3
				return SendClientMessage(playerid, COLOR_WHITE, "Granjero: buscamos gente con experiencia, no aceptamos novatos. ¡Sal de aquí! (OOC: Requiere nivel 3)"); // Si es uno nuevo en el servidor o multicuenta

			if(id == JOB_FELON)
                createThiefJob(playerid);

			PlayerInfo[playerid][pJobTime] = JOB_WAITTIME;
			PlayerInfo[playerid][pJob] = id;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendFMessage(playerid, COLOR_YELLOW3, "¡Felicidades!, ahora eres un %s, para ver los comandos disponibles, escribe /ayuda.", JobInfo[id][jName]);
			SendFMessage(playerid, COLOR_YELLOW3, "Debes esperar %d PayDay/s antes de volver a tomar un empleo.", PlayerInfo[playerid][pJobTime]);
			return 1;
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tomar un empleo en cualquier lugar!");
	return 1;
}

CMD:dejarempleo(playerid,params[])
{
    if(PlayerInfo[playerid][pJob] == 0)
		return SendClientMessage(playerid,COLOR_YELLOW2,"No tienes ningún empleo.");
  	if(jobDuty[playerid])
	  	return SendClientMessage(playerid,COLOR_YELLOW2,"¡No puedes hacerlo mientras estás trabajando!");

	for(new id = 1; id < sizeof(JobInfo); id++)
	{
		if(PlayerToPoint(1.0, playerid,JobInfo[id][jTakeX],JobInfo[id][jTakeY],JobInfo[id][jTakeZ]))
		{
  			if(id != PlayerInfo[playerid][pJob])
				return SendClientMessage(playerid,COLOR_YELLOW2,"¡No trabajas aquí!");
			if(JobInfo[id][jType] != 0)
	            return 1;

			SendFMessage(playerid, COLOR_YELLOW2, "¡Has dejado tu empleo de %s!", JobInfo[id][jName]);
			PlayerInfo[playerid][pJob] = 0;
			return 1;
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes dejar tu empleo en cualquier lugar! Vé y presenta la renuncia ante tu jefe.");
	return 1;
}

//===============================COMANDOS DE ADMIN==============================

CMD:setjob(playerid, params[])
{
	new string[128], job, targetid;

	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;

	if(sscanf(params,"ui", targetid, job))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setjob [ID/Jugador] [id empleo]");
	if(!IsPlayerConnected(targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(job < 0 || job >= 20)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Empleo inválido.");
	    
	SendFMessage(targetid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} %s te ha seteado el empleo a %d (%s).", GetPlayerNameEx(playerid), job, JobInfo[job][jName]);
	format(string, sizeof(string), "[Staff]: %s ha seteado el empleo de %s a %d (%s).", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), job, JobInfo[job][jName]);
	AdministratorMessage(COLOR_ADMINCMD, string, 1);
    PlayerInfo[targetid][pJob] = job;
	if(job == JOB_FELON)
		createThiefJob(playerid);
	return 1;
}


//Timers
public jobBreakTimer(playerid, job) {
	if(jobBreak[playerid] > 0) {
		jobBreak[playerid]--;
		if(jobBreak[playerid] == 40) {
		    SendClientMessage(playerid, COLOR_WHITE, "¡Te quedan 40 segundos para ingresar al vehículo!");
		}
		SetPVarInt(playerid, "jobBreakTimerID", SetTimerEx("jobBreakTimer", 1000, false, "dd", playerid, job));
	} else {
	    SendClientMessage(playerid, COLOR_WHITE, "¡Has agotado el tiempo disponible para ingresar al vehículo!");
	    SendClientMessage(playerid, COLOR_WHITE, "No recibirás ninguna paga y no podrás volver a trabajar hasta el próximo día de pago.");
	    PlayerInfo[playerid][pCantWork] = 1;
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		jobDuty[playerid] = false;
		if(PlayerInfo[playerid][pJobAllowed] == 1) {
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		}
		CollectedProds[playerid] = 0;
		LastCP[playerid] = -1;
		
		DisablePlayerCheckpoint(playerid);
		
		if(job == JOB_GARB) {
			DeletePVar(playerid, "garbageCheckpoint");
			DeletePVar(playerid, "garbageRoute");
		}
		SetEngine(GetPlayerVehicleID(playerid), 0);
		SetVehicleToRespawn(GetPVarInt(playerid, "jobVehicle"));
		DeletePVar(playerid, "jobVehicle");
		KillTimer(GetPVarInt(playerid, "jobBreakTimerID"));
	}
	return 1;
}
