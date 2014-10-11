#if defined _isamp_missions_included
	#endinput
#endif
#define _isamp_missions_included

//===================SISTEMA DE MINIMISIONES AUTOMATICAS========================

//=================================CONSTANTES===================================

#define MISSION_EVENT_TIME      3 // En minutos, tiempo mínimo entre misiones.
#define MISSION_EVENT_EXTRATIME 2 // En minutos, máximo que se le puede agregar al tiempo mínimo entre misiones.

#define MISSION_NONE            0
#define MISSION_MAT             1
#define MISSION_DRUG		    2
#define MISSION_CAR             3

#define NUM_MISSION          	424

#define MAX_MISSION_DRUG_POS    4
#define MAX_MISSION_CAR_POS     3

//=================================VARIABLES====================================

new pMissionEvent[MAX_PLAYERS],
	pMissionEventTimer[MAX_PLAYERS],
	pMissionEventStep[MAX_PLAYERS],
	pMissionEventParam[MAX_PLAYERS],
	pMissionEventParam2[MAX_PLAYERS];

static const Float:MissionDrugsPos[MAX_MISSION_DRUG_POS][3] = {
	{2744.1577, -2016.5842, 13.5036},
	{1640.4705, -2108.3301, 13.6469},
	{864.1969, -615.7695, 18.3109},
	{2465.5369, -955.8604, 80.0118}
};

static const Float:MissionCarPos[MAX_MISSION_CAR_POS][3] = {
	{91.0594, -164.6225, 2.5036},
	{2351.7014, -651.6862, 127.9594},
	{1273.6932, 154.2808, 20.1258}
};

//============================FUNCIONES PUBLICAS================================

forward CreateMissionEventTimer(playerid); // Crea el timer inicial que le dará misiones a playerid mientras esté conectado.
forward KillMissionEventTimer(playerid); // Destruye el timer que genera misiones a playerid.
forward ResetMissionEventVariables(playerid); // Resetea a valores default las variables del sistema.

forward bool:CheckMissionEvent(playerid, step, text[] = "NULO");
// Chequea si hay alguna mision activa y de ser asi devuelve true y ejecuta el codigo, de lo contrario false.
// El parametro 'text' es opcional y sirve para guardar, si fuese necesario, el texto que contiene alguna respuesta del jugador ante una pregunta de la mision.
// 'step' indica que etapa tiene que ejecutar

forward bool:PlayerCancelMissionEvent(playerid); // Devuelve true si se efectuó exitosamente la cancelación de la mision activa en la etapa 1.

//============================FUNCIONES INTERNAS================================

forward MissionEvent(playerid); // Public para crear las misiones. Utilizado por el timer principal.
forward CancelMissionEvent(playerid); // Cancela la mision si no respondió en cierto tiempo.

forward bool:MissionMaterials(playerid, step, text[]); // Todo el codigo separado en etapas de la misión en cuestión.
forward bool:MissionCar(playerid, step, text[]);
forward bool:MissionDrugs(playerid, step, text[]);

forward MissionMaterialsLoad(playerid, vehicleid); // Public correspondiente a la carga de materiales de la mision MISSION_MAT.
forward MissionMaterialsUnload(playerid, matsCount, vehicleid); // Public correspondiente a la descarga de materiales de la mision MISSION_MAT que termina la misión.

//=========================IMPLEMENTACIÓN DE FUNCIONES==========================

stock CreateMissionEventTimer(playerid)
{
	if(PlayerInfo[playerid][pFaction] > 0 && FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_ILLEGAL)
	    pMissionEventTimer[playerid] = SetTimerEx("MissionEvent", 60 * 1000 * (MISSION_EVENT_TIME + random(MISSION_EVENT_EXTRATIME)), false, "i", playerid); // No es recursivo para hacer uso del random en tiempo.
}

stock KillMissionEventTimer(playerid)
{
	KillTimer(pMissionEventTimer[playerid]);
}

stock ResetMissionEventVariables(playerid)
{
	pMissionEvent[playerid] = MISSION_NONE;
	pMissionEventStep[playerid] = 0;
	pMissionEventParam[playerid] = 0;
	pMissionEventParam2[playerid] = 0;
}

CMD:missioneventdebug(playerid, params[])
{
	new targetid;
	
	if(PlayerInfo[playerid][pAdmin] > 20)
	    return 1;
	if(sscanf(params, "i", targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /missioneventdebug [playerid]");

	SendFMessage(playerid, COLOR_YELLOW, "pMissionEvent [%d] = %d", targetid, pMissionEvent[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "pMissionEventStep [%d] = %d", targetid, pMissionEventStep[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "pMissionEventParam [%d] = %d", targetid, pMissionEventParam[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "pMissionEventParam2 [%d] = %d", targetid, pMissionEventParam2[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "pMissionEventTimer [%d] = %d", targetid, pMissionEventTimer[targetid]);
	return 1;
}

public MissionEvent(playerid)
{
	new factionID = PlayerInfo[playerid][pFaction];
	// Creamos el timer que llamará a la próxima misión.
	pMissionEventTimer[playerid] = SetTimerEx("MissionEvent", 60 * 1000 * (MISSION_EVENT_TIME + random(MISSION_EVENT_EXTRATIME)), false, "i", playerid);

	if(PlayerInfo[playerid][pJailed] != 0 || random(2) == 0 || pMissionEvent[playerid] != MISSION_NONE)
	    return 1;

	if(factionID > 0 && FactionInfo[factionID][fType] == FAC_TYPE_ILLEGAL)
	{
		PlayerDoMessage(playerid, 15.0, "Un teléfono ha comenzado a sonar.");
		SendClientMessage(playerid, COLOR_WHITE, "Tienes una llamada, utiliza /atender o /colgar.");
		pMissionEvent[playerid] = 1 + random(3); // Tipo de misión aleatorio.
		SetTimerEx("CancelMissionEvent", 35000, false, "i", playerid);
		pMissionEventStep[playerid] = 1;
	}
	return 1;
}

public CancelMissionEvent(playerid)
{
	if(pMissionEventStep[playerid] == 1)
 	{
		PlayerDoMessage(playerid, 15.0, "Han colgado...");
        ResetMissionEventVariables(playerid);
	}
	return 1;
}

stock bool:PlayerCancelMissionEvent(playerid)
{
	if(pMissionEventStep[playerid] == 1)
	{
	    PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
     	ResetMissionEventVariables(playerid);
	    return true;
	}
	return false;
}

stock bool:CheckMissionEvent(playerid, step, text[] = "NULO")
{
	switch(pMissionEvent[playerid])
	{
	    case MISSION_NONE:
			return false;
	    case MISSION_MAT:
			return MissionMaterials(playerid, step, text);
	    case MISSION_DRUG:
	        return MissionDrugs(playerid, step, text);
	    case MISSION_CAR:
			return MissionCar(playerid, step, text);
	}
	return false;
}

stock bool:MissionCar(playerid, step, text[])
{
	if(step != pMissionEventStep[playerid])
	    return false;
	    
	switch(step)
	{
		case 1: // Atender la llamada.
		{
		    PlayerActionMessage(playerid, 15.0, "saca su teléfono y atiende la llamada.");
			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tengo un trabajo para ti: consígueme el auto que te indique. Dinero facil, ¿qué dices?");
	        Mobile[playerid] = NUM_MISSION;
			pMissionEventStep[playerid] = 2;
		}
		case 2: // Responder si está interesado o no
		{
			if(Mobile[playerid] == NUM_MISSION)
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					new bool:isCar = false,
			            vehicleid;

			        while(isCar == false)
			        {
			   			vehicleid = 1 + random(MAX_VEH - 1);
			        	if(GetVehicleType(vehicleid) == VTYPE_CAR)
			        	    isCar = true;
					}
					pMissionEventParam[playerid] = vehicleid;
					pMissionEventStep[playerid] = 3;
					SendFMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Escucha, necesito que me consigas un %s en buen estado. ¿Puedes hacerlo?", GetVehicleName(vehicleid));
				}
				else if((strcmp("no", text, true) == 0) && (strlen(text) == strlen("no")))
				{
		 			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tú te lo pierdes, adiós...");
		            PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
		            Mobile[playerid] = 255;
		            ResetMissionEventVariables(playerid);
	            }
				else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡No tengo tiempo para vueltas, di 'si' o 'no'!");
			}
		}
		case 3: // Responder si acepta o no
		{
        	if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
			{
				SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Perfecto, llevame rapidamente el vehículo al lugar que te he pasado por el celular.");
				new rnd = random(MAX_MISSION_CAR_POS);
				SetPlayerCheckpoint(playerid, MissionCarPos[rnd][0], MissionCarPos[rnd][1], MissionCarPos[rnd][2], 3.0);
				pMissionEventStep[playerid] = 4;
			    Mobile[playerid] = 255;
           		jobDuty[playerid] = true;
				PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
			}
			else if((strcmp("no", text, true) == 0) && (strlen(text) == strlen("no")))
			{
				SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tú te lo pierdes, adiós...");
		        PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
		        Mobile[playerid] = 255;
            	ResetMissionEventVariables(playerid);
			}
			else
				SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡No tengo tiempo para vueltas, di 'si' o 'no'!");
		}
		case 4: // Entregar el auto
		{
  			new vehicleid = GetPlayerVehicleID(playerid);
			if(GetVehicleModel(vehicleid) == GetVehicleModel(pMissionEventParam[playerid]))
			{
      			if(!playerHasCarKey(playerid, vehicleid))
      			{
      			    new Float:vhp;
      			    GetVehicleHealth(vehicleid, vhp);
      			    if(vhp > 500.0 && VehicleInfo[vehicleid][VehEngine] == 1)
      			    {
      			        new price = GetVehiclePrice(vehicleid, 100) / 180;
      			        if(price < 3000)
						  	price = 3000;
      			        SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, en tiempo y forma. Aqui tienes $%d por el coche. Nunca nos vimos.", price);
						GivePlayerCash(playerid, price);
						HideStolenCar(vehicleid);
						PlayerActionMessage(playerid, 15.0, "le entrega un vehículo a un sujeto desconocido y recibe a cambio un paquete.");
				  	} else
      			        SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Te dije que estuviese en buen estado y andando, no esta porquería. Dios mio...");
      			} else
	    			SendClientMessage(playerid, COLOR_YELLOW2, "No puedes entregar un auto del cual tienes las llaves. Se anula la misión.");
			} else
			    SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: ¿Y el auto que te pedí...? Me haces perder el tiempo.");
        	ResetMissionEventVariables(playerid);
		}
	}
	return true;
}

stock bool:MissionDrugs(playerid, step, text[])
{
	if(step != pMissionEventStep[playerid])
	    return false;
	    
	switch(step)
	{
		case 1: // Atender la llamada
		{
		    PlayerActionMessage(playerid, 15.0, "saca su teléfono y atiende la llamada.");
			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ando necesitando algo de merca, ¿tienes algo disponible? Pago bien.");
	        Mobile[playerid] = NUM_MISSION;
			pMissionEventStep[playerid] = 2;
		}
		case 2: // Responder si está interesado o no
		{
			if(Mobile[playerid] == NUM_MISSION)
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					pMissionEventParam[playerid] = 30 + random(20);
				    switch(random(3))
				    {
				        case 0:
				        {
				            pMissionEventParam2[playerid] = 0;
				            SendFMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Escucha, busco %d gramos de marihuana. ¿Tienes esa cantidad?", pMissionEventParam[playerid]);
						}
				        case 1:
				        {
				            pMissionEventParam2[playerid] = 1;
				            SendFMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Escucha, busco %d dosis de lsd. ¿Tienes esa cantidad?", pMissionEventParam[playerid]);
						}
				        case 2:
				        {
				            pMissionEventParam2[playerid] = 2;
				            SendFMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Escucha, busco %d pastillas de éxtasis. ¿Tienes esa cantidad?", pMissionEventParam[playerid]);
						}
				        case 3:
				        {
				            pMissionEventParam2[playerid] = 3;
				            SendFMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Escucha, busco %d gramos de cocaína. ¿Tienes esa cantidad?", pMissionEventParam[playerid]);
						}
					}
     				pMissionEventStep[playerid] = 3;
				}
				else if((strcmp("no", text, true) == 0) && (strlen(text) == strlen("no")))
				{
		 			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tú te lo pierdes, adiós...");
		            PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
		            Mobile[playerid] = 255;
		            ResetMissionEventVariables(playerid);
	            }
				else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡No tengo tiempo para vueltas, di 'si' o 'no'!");
			}
		}
		case 3: // Responder si acepta o no
		{
			if(Mobile[playerid] == NUM_MISSION)
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Excelente, llevame la mercancia al lugar que te he pasado al celular. No te demores.");
					new rnd = random(MAX_MISSION_DRUG_POS);
					SetPlayerCheckpoint(playerid, MissionDrugsPos[rnd][0], MissionDrugsPos[rnd][1], MissionDrugsPos[rnd][2], 3.0);
					pMissionEventStep[playerid] = 4;
			        Mobile[playerid] = 255;
           			jobDuty[playerid] = true;
					PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
				}
				else if((strcmp("no", text, true) == 0) && (strlen(text) == strlen("no")))
				{
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tú te lo pierdes, adiós...");
		            PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
		            Mobile[playerid] = 255;
              		ResetMissionEventVariables(playerid);
				}
				else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡No tengo tiempo para vueltas, di 'si' o 'no'!");
			}
		}
		case 4: // Entregar la droga
		{
			switch(pMissionEventParam2[playerid])
   			{
				case 0:
    			{
			        if(PlayerInfo[playerid][pMarijuana] >= pMissionEventParam[playerid])
			        {
			         	SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, veo que me has traido lo que te pedí. Aqui tienes $%d por la mercancía.", pMissionEventParam[playerid] * 50);
						GivePlayerCash(playerid, pMissionEventParam[playerid] * 50);
						PlayerInfo[playerid][pMarijuana] -= pMissionEventParam[playerid];
						PlayerActionMessage(playerid, 8.0, "le entrega un paquete a un sujeto desconocido y éste se aleja rapidamente.");
					} else
			       	    SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: No tienes la cantidad que te he pedido idiota. Me haces perder el tiempo.");
     			}
			    case 1:
			    {
			    	if(PlayerInfo[playerid][pLSD] >= pMissionEventParam[playerid])
			        {
			            SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, veo que me has traido lo que te pedí. Aqui tienes $%d por la mercancía.", pMissionEventParam[playerid] * 60);
						GivePlayerCash(playerid, pMissionEventParam[playerid] * 60);
						PlayerInfo[playerid][pLSD] -= pMissionEventParam[playerid];
						PlayerActionMessage(playerid, 8.0, "le entrega un paquete a un sujeto desconocido y éste se aleja rapidamente.");
					} else
			            SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: No tienes la cantidad que te he pedido idiota. Me haces perder el tiempo.");
     			}
			    case 2:
			    {
			    	if(PlayerInfo[playerid][pEcstasy] >= pMissionEventParam[playerid])
			        {
			            SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, veo que me has traido lo que te pedí. Aqui tienes $%d por la mercancía.", pMissionEventParam[playerid] * 70);
						GivePlayerCash(playerid, pMissionEventParam[playerid] * 70);
						PlayerInfo[playerid][pEcstasy] -= pMissionEventParam[playerid];
						PlayerActionMessage(playerid, 8.0, "le entrega un paquete a un sujeto desconocido y éste se aleja rapidamente.");
					} else
			            SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: No tienes la cantidad que te he pedido idiota. Me haces perder el tiempo.");
 				}
			    case 3:
			    {
			    	if(PlayerInfo[playerid][pCocaine] >= pMissionEventParam[playerid])
			        {
			            SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, veo que me has traido lo que te pedí. Aqui tienes $%d por la mercancía.", pMissionEventParam[playerid] * 80);
						GivePlayerCash(playerid, pMissionEventParam[playerid] * 80);
						PlayerInfo[playerid][pCocaine] -= pMissionEventParam[playerid];
						PlayerActionMessage(playerid, 8.0, "le entrega un paquete a un sujeto desconocido y éste se aleja rapidamente.");
					} else
			            SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: No tienes la cantidad que te he pedido idiota. Me haces perder el tiempo.");
     			}
			}
        	ResetMissionEventVariables(playerid);
		}
	}
	return true;
}



stock bool:MissionMaterials(playerid, step, text[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
	    factionid = PlayerInfo[playerid][pFaction];

	if(step != pMissionEventStep[playerid])
	    return false;
	    
	switch(step)
	{
		case 1: // Atender la llamada
		{
		    PlayerActionMessage(playerid, 15.0, "saca su teléfono y atiende la llamada.");
			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: nos ha llegado un cargamento de materiales, ¿vienes a buscarlo? También recibirás efectivo.");
	        Mobile[playerid] = NUM_MISSION;
			pMissionEventStep[playerid] = 2;
		}
		case 2: // Responder si acepta o no
		{
			if(Mobile[playerid] == NUM_MISSION)
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: bien, súbete a la van y di 'listo' una vez arriba.");
		   			pMissionEventStep[playerid] = 3;
				    jobDuty[playerid] = true;
				    SetVehicleParamsForPlayer(FactionInfo[PlayerInfo[playerid][pFaction]][fMissionVeh], playerid, 1, 0);
				}
				else if((strcmp("no", text, true) == 0) && (strlen(text) == strlen("no")))
				{
		 			SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tú te lo pierdes, adiós...");
		            PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
		            Mobile[playerid] = 255;
		            ResetMissionEventVariables(playerid);
	            }
				else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡No tengo tiempo para vueltas, di 'si' o 'no'!");
			}
		}
		case 3: // Responder 'listo' cuando esté en la van
		{
		    if(Mobile[playerid] == NUM_MISSION)
		    {
				if((strcmp("listo", text, true) == 0) && (strlen(text) == strlen("listo")))
				{
                    if(vehicleid == FactionInfo[factionid][fMissionVeh])
					{
						SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: te he pasado la dirección a tu celular. Vé a buscar los paquetes y llévalos a tu HQ.");
						SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 3.0);
						pMissionEventStep[playerid] = 4;
						Mobile[playerid] = 255;
						PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
                	} else
					    SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡súbete a la van, no tengo tiempo para vueltas!");
			 	} else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡no tengo tiempo para vueltas, di 'listo' una vez arriba!");
			}
		}
		case 4: // Carga de materiales cuando llega a destino
		{
			if(FactionInfo[factionid][fMissionVeh] == vehicleid)
			{
				GameTextForPlayer(playerid, "Cargando materiales en el vehiculo...", 6000, 4);
				TogglePlayerControllable(playerid, false);
				SetTimerEx("MissionMaterialsLoad", 6000, false, "ii", playerid, vehicleid);
			} else {
				SetPlayerPos(playerid, 2767.2983, -2417.6804, 13.7573);
				SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 3.0);
				SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vehiculo de la misión.");
			}
		}
		case 5: // Descarga de materiales cuando llege a destino HQ
		{
			if(FactionInfo[factionid][fMissionVeh] == vehicleid)
			{
				new matsCount = 0,
					validslot = SearchTrunkForItem(vehicleid, ITEM_ID_MATERIALES);

			    if(validslot != -1)
			    {
	   				matsCount = GetTrunkParam(vehicleid, validslot);
					FactionInfo[factionid][fMaterials] += matsCount;
					SetTrunkItemAndParam(vehicleid, validslot, 0, 0);
				}
				GameTextForPlayer(playerid, "Descargando materiales del vehiculo...", 6000, 4);
				TogglePlayerControllable(playerid, false);
				SetTimerEx("MissionMaterialsUnload", 6000, false, "iii", playerid, matsCount, vehicleid);
			} else {
				SendClientMessage(playerid, COLOR_YELLOW2, "Debías estar en el vehículo de la misión. ¡Lo has perdido! Se anula la misión.");
                ResetMissionEventVariables(playerid);
                jobDuty[playerid] = false;
			}
		}
	}
	return true;
}

//=================CARGA DE MATERIALES POR MISION PARA MAFIAS===================

public MissionMaterialsLoad(playerid, vehicleid)
{
    TogglePlayerControllable(playerid, true);

    new validslot = SearchTrunkFreeSlot(vehicleid);

	if(validslot == -1)
	{
        SendClientMessage(playerid, COLOR_YELLOW2, "El maletero se encuentra lleno, toma algo de él y vuelve a intentarlo.");
		SetVehiclePos(vehicleid, 2767.2983, -2417.6804, 13.7573);
		SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 3.0);
	} else
		{
		    foreach(new i : Player)
			{
			    if(playerid != i && PlayerInfo[i][pFaction] == PlayerInfo[playerid][pFaction] && GetPlayerVehicleID(i) == vehicleid)
					pMissionEventParam[playerid]++;
			}
			pMissionEventStep[playerid] = 5;
			SetTrunkItemAndParam(vehicleid, validslot, ITEM_ID_MATERIALES, MISSION_BOX_MATS + (MISSION_BOX_EXTRA * pMissionEventParam[playerid]) * (random(MISSION_MATS_MAX_BOXES) + 1 + MISSION_MATS_MIN_BOXES));
			SetPlayerCheckpoint(playerid, VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], 3.0);
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "SMS de anónimo: vuelve al HQ con la carga. Solo alguien con experiencia podrá ensamblarlas.");
		}
	return 1;
}

//================DESCARGA DE MATERIALES POR MISION PARA MAFIAS=================

public MissionMaterialsUnload(playerid, matsCount, vehicleid)
{
	TogglePlayerControllable(playerid, true);
	SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);
	jobDuty[playerid] = false;
	SendFMessage(playerid, COLOR_WHITE, "Has descargado %d materiales en el HQ y recibido una ganancia de $%d.", matsCount, MISSION_MATS_REWARD + MISSION_MATS_EXTRA * pMissionEventParam[playerid]);
	GivePlayerCash(playerid, MISSION_MATS_REWARD + MISSION_MATS_EXTRA * pMissionEventParam[playerid]);
	SetVehicleToRespawn(vehicleid);
 	ResetMissionEventVariables(playerid);
    return 1;
}
