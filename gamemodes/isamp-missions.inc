#if defined _isamp_missions_included
	#endinput
#endif
#define _isamp_missions_included

//===================SISTEMA DE MINIMISIONES AUTOMATICAS========================

//=================================CONSTANTES===================================

#define MISSION_EVENT_TIME      4 // En minutos, tiempo mínimo entre misiones.
#define MISSION_EVENT_EXTRATIME 3 // En minutos, máximo que se le puede agregar al tiempo mínimo entre misiones.

#define MISSION_NONE            0
#define MISSION_MAT             1
#define MISSION_DRUG            2
#define MISSION_CAR             3

#define NUM_MISSION          	424

//=================================VARIABLES====================================

new pMissionEvent[MAX_PLAYERS],
	pMissionEventTimer[MAX_PLAYERS],
	pMissionEventStep[MAX_PLAYERS],
	pMissionEventParam[MAX_PLAYERS],
	pMissionEventParam2[MAX_PLAYERS];

//============================FUNCIONES PUBLICAS================================

forward CreateMissionEventTimer(playerid); // Crea el timer inicial que le dará misiones a playerid mientras esté conectado.
forward KillMissionEventTimer(playerid); // Destruye el timer que genera misiones a playerid.
forward bool:CheckMissionEventStep1(playerid); // Devuelve true si se efectuó exitosamente el paso de la etapa 1 a la 2 (o final) de la mision activa, false en caso contrario.
forward bool:CheckCancelMissionEventStep1(playerid); // Devuelve true si se efectuó exitosamente la cancelación de la mision activa en la etapa 1.
forward bool:CheckMissionEventStep2(playerid, text[]); // Devuelve true si se efectuó exitosamente el paso de la etapa 2 a la 3 (o final) de la mision activa, false en caso contrario.
forward bool:CheckMissionEventStep3(playerid, text[]); // Devuelve true si se efectuó exitosamente el paso de la etapa 3 a la 4 (o final) de la mision activa, false en caso contrario.
forward CheckMissionEventStep4(playerid);
forward ResetMissionEventVariables(playerid); // Resetea a valores default las variables del sistema.

//============================FUNCIONES INTERNAS================================

forward MissionEvent(playerid); // Public para crear las misiones. Utilizado por el timer principal.
forward CancelMissionEvent(playerid); // Cancela la mision si no respondió en cierto tiempo.

forward MissionMatLoad(playerid, vehicleid); // Public correspondiente a la carga de materiales de la mision MISSION_MAT.
forward MissionMatUnload(playerid, matsCount, vehicleid); // Public correspondiente a la descarga de materiales de la mision MISSION_MAT que termina la misión.

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

stock bool:CheckMissionEventStep1(playerid)
{
    if(pMissionEventStep[playerid] == 1)
	{
        PlayerActionMessage(playerid, 15.0, "saca su teléfono y atiende la llamada.");
	    switch(pMissionEvent[playerid])
		{
		    case MISSION_MAT:
		 		SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: nos ha llegado un cargamento de materiales, ¿vienes a buscarlo? También recibirás efectivo.");
		    case MISSION_DRUG:
		 		SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ando necesitando algo de merca, ¿tienes algo disponible? Pago bien.");
		    case MISSION_CAR:
		    	SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: tengo un trabajo para ti: consígueme el auto que te indique. Dinero facil, ¿qué dices?");
		}
  		Mobile[playerid] = NUM_MISSION;
		pMissionEventStep[playerid] = 2;
		return true;
	}
	return false;
}

stock bool:CheckCancelMissionEventStep1(playerid)
{
	if(pMissionEventStep[playerid] == 1)
	{
	    PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
     	ResetMissionEventVariables(playerid);
	    return true;
	}
	return false;
}

stock bool:CheckMissionEventStep2(playerid, text[])
{
	if(Mobile[playerid] == NUM_MISSION && pMissionEventStep[playerid] == 2)
	{
		if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
		{
		    switch(pMissionEvent[playerid])
			{
			    case MISSION_MAT:
			    {
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: bien, súbete a la van y di 'listo' una vez arriba.");
		            pMissionEventStep[playerid] = 3;
		            jobDuty[playerid] = true;
		            SetVehicleParamsForPlayer(FactionInfo[PlayerInfo[playerid][pFaction]][fMissionVeh], playerid, 1, 0);
				}
				case MISSION_DRUG:
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
			    case MISSION_CAR:
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
			}
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
		return true;
	}
	return false;
}

stock bool:CheckMissionEventStep3(playerid, text[])
{
	if(Mobile[playerid] == NUM_MISSION && pMissionEventStep[playerid] == 3)
	{
	    switch(pMissionEvent[playerid])
	    {
	        case MISSION_MAT:
	        {
				if((strcmp("listo", text, true) == 0) && (strlen(text) == strlen("listo")))
				{
				    if(GetPlayerVehicleID(playerid) == FactionInfo[PlayerInfo[playerid][pFaction]][fMissionVeh])
					{
						SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: te he marcado la localización en el GPS, vé a buscar los paquetes y llévalos a tu HQ.");
			            SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 4.0);
			            pMissionEventStep[playerid] = 4;
			            Mobile[playerid] = 255;
						PlayerActionMessage(playerid, 15.0, "cuelga la llamada y guarda su teléfono celular en el bolsillo.");
					} else
					    SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡súbete a la van, no tengo tiempo para vueltas!");
				} else
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: ¡no tengo tiempo para vueltas, di 'listo' una vez arriba!");
			}
			case MISSION_DRUG:
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Excelente, llevame la mercancia al lugar que te he pasado al celular. No te demores.");
                    SetPlayerCheckpoint(playerid, 2465.5369, -955.8604, 80.0118, 4.0);
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
			case MISSION_CAR:
			{
				if((strcmp("si", text, true) == 0) && (strlen(text) == strlen("si")))
				{
					SendClientMessage(playerid, COLOR_FADE1, "[Voz al teléfono]: Perfecto, llevame rapidamente el vehículo al lugar que te he pasado por el celular.");
                    SetPlayerCheckpoint(playerid, 91.0594, -164.6225, 2.5036, 4.0);
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
		return true;
	}
	return false;
}

stock CheckMissionEventStep4(playerid)
{
	switch(pMissionEvent[playerid])
	{
	    case MISSION_MAT:
	    {
	        new vehicleid = GetPlayerVehicleID(playerid),
	            factionid = PlayerInfo[playerid][pFaction];
	        
			if(pMissionEventStep[playerid] == 5)
			{
			    new matsCount = 0,
			        validslot = SearchTrunkForItem(vehicleid, ITEM_ID_MATERIALES);

			    if(validslot != -1)
			    {
       				matsCount = GetTrunkParam(vehicleid, validslot);
					FactionInfo[factionid][fMaterials] += matsCount;
					SetTrunkItemAndParam(vehicleid, validslot, 0, 0);
				}
				GameTextForPlayer(playerid, "Descargando materiales del vehículo...", 4000, 4);
				TogglePlayerControllable(playerid, false);
				SetTimerEx("MissionMatUnload", 4000, false, "ii", playerid, matsCount);
			}
			else if(pMissionEventStep[playerid] == 4)
			{
			    if(FactionInfo[factionid][fMissionVeh] == vehicleid)
				{
			        GameTextForPlayer(playerid, "Cargando materiales...", 4000, 4);
					TogglePlayerControllable(playerid, false);
					SetTimerEx("MissionMatLoad", 4000, false, "i", playerid, vehicleid);
				} else {
				    SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 5.4);
				    GameTextForPlayer(playerid, "Debes estar en el vehículo de la misión.", 1000, 4);
				}
			}
		}
		case MISSION_DRUG:
		{
			if(pMissionEventStep[playerid] == 4)
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
		case MISSION_CAR:
		{
  			if(pMissionEventStep[playerid] == 4)
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
      				        SendFMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Bien, en tiempo y forma. Aqui tienes $%d por el coche. Nunca nos vimos.", GetVehiclePrice(vehicleid, 100) / 180);
							GivePlayerCash(playerid, GetVehiclePrice(vehicleid, 100) / 180);
							SetVehicleToRespawn(vehicleid);
							PlayerActionMessage(playerid, 15.0, "le entrega un vehículo a un sujeto desconocido y recibe a cambio un paquete.");
					  	} else
      				        SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Te dije que estuviese en buen estado y andando, no esta porquería. Dios mio...");
      				} else
	    				SendClientMessage(playerid, COLOR_YELLOW2, "No puedes entregar un auto del cual tienes las llaves. Se anula la misión.");
				} else
				    SendClientMessage(playerid, COLOR_WHITE, "Sujeto desconocido: Este no es el modelo que te había pedido idiota, me haces perder el tiempo.");
        		ResetMissionEventVariables(playerid);
			}
		}
	}
}

//=================CARGA DE MATERIALES POR MISION PARA MAFIAS===================

public MissionMatLoad(playerid, vehicleid)
{
	new validslot;

    TogglePlayerControllable(playerid, true);
    
    validslot = SearchTrunkFreeSlot(vehicleid);
	if(validslot == -1)
	{
        SendClientMessage(playerid, COLOR_YELLOW2, "El maletero se encuentra lleno, toma algo de él y vuelve a intentarlo.");
		SetPlayerCheckpoint(playerid, 2792.4609, -2417.5508, 13.7599, 5.4);
    	SetVehiclePos(vehicleid, 2767.2983, -2417.6804, 13.7573);
	} else
		{
		    foreach(new i : Player)
			{
			    if(playerid != i && PlayerInfo[i][pFaction] == PlayerInfo[playerid][pFaction] && GetPlayerVehicleID(i) == vehicleid)
					pMissionEventParam[playerid]++;
			}
			pMissionEventStep[playerid] = 5;
			SetTrunkItemAndParam(vehicleid, validslot, ITEM_ID_MATERIALES, MISSION_BOX_MATS + (MISSION_BOX_EXTRA * pMissionEventParam[playerid]) * (random(MISSION_MATS_MAX_BOXES) + 1 + MISSION_MATS_MIN_BOXES));
			SetPlayerCheckpoint(playerid, VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], 4.0);
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "SMS de anónimo: vuelve al HQ con la carga. Solo alguien con experiencia podrá ensamblarlas.");
		}
	return 1;
}

//================DESCARGA DE MATERIALES POR MISION PARA MAFIAS=================

public MissionMatUnload(playerid, matsCount, vehicleid)
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
