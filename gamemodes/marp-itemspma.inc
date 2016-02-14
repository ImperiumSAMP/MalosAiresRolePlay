#if defined _marp_itemspma_included
	#endinput
#endif
#define _marp_itemspma_included

//=================================DEFINES======================================

#define MAX_PMAITEMS 100

//==================================NEWS========================================

new pmaitems[MAX_PMAITEMS];

//======================SISTEMA DE PERIMETROS PARA LA PMA=======================
CMD:pponer(playerid, params[])
{
	new objetos;
	
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;
	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en servicio.");
    if(PlayerInfo[playerid][pRank] > 9)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el rango suficiente!");
   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");
   	if(sscanf(params, "i", objetos)){
   	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /pponer [N° de objeto]");
   	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1 Cono - 2 Barricada - 3 Baliza - 4 Baliza inrompible - 5 Baliza con flecha - 6 Cinta policial - 7 Barricada de metal");
   	    return 1;
	}
    
    new Float:x, Float:y, Float:z, Float:fAngle;
    
    switch(objetos)
    {
        case 1: // Cono
        {
            for(new i; i < MAX_PMAITEMS; i++)
			{
                if(pmaitems[i] == 0)
				{
                	GetPlayerPos(playerid, x, y, z);
                	GetPlayerFacingAngle(playerid, fAngle);

                	if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1238, x-0.5, y, z-0.7, 0.0, 0.0, 0.0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cono policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(1238, x, y-0.5, z-0.7, 0.0, 0.0, 0.0);
						Streamer_Update(playerid);
     					PlayerActionMessage(playerid, 15.0, "ubica una cono policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
						}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1238, x+0.5, y, z-0.7, 0.0, 0.0, 0.0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cono policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					} else {
					    pmaitems[i] = CreateDynamicObject(1238, x, y+0.5, z-0.7, 0.0, 0.0, 0.0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cono policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 2: // Barricada
        {
 			for(new i; i < MAX_PMAITEMS; i++)
			{
            	if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1459, x-0.5, y, z-0.7, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(1459, x, y-0.5, z-0.7, 0.0, 0.0, 180);
						Streamer_Update(playerid);
    					PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1459, x+0.5, y, z-0.7, 0.0, 0.0, 270);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					} else {
				    	pmaitems[i] = CreateDynamicObject(1459, x, y+0.5, z-0.7, 0.0, 0.0, 0.0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 3: // Baliza 1
		{
           	for(new i; i < MAX_PMAITEMS; i++)
			{
           		if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1282, x-0.8, y, z-0.5, 0.0, 0.0, 0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(1282, x, y-0.8, z-0.5, 0.0, 0.0, 90);
						Streamer_Update(playerid);
    					PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1282, x+0.8, y, z-0.5, 0.0, 0.0, 0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					} else {
				    	pmaitems[i] = CreateDynamicObject(1282, x, y+0.8, z-0.5, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 4:  // Baliza inrompible
		{
           	for(new i; i < MAX_PMAITEMS; i++)
			{
           		if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1427, x-0.8, y, z-0.5, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(1427, x, y-0.8, z-0.5, 0.0, 0.0, 0);
						Streamer_Update(playerid);
    					PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1427, x+0.8, y, z-0.5, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
 						return 1;
					} else {
				    	pmaitems[i] = CreateDynamicObject(1427, x, y+0.8, z-0.5, 0.0, 0.0, 0);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 5: // Baliza con flecha
		{
		    for(new i; i < MAX_PMAITEMS; i++)
			{
           		if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1425, x-0.8, y, z-0.5, 0.0, 0.0, 270);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(1425, x, y-0.8, z-0.5, 0.0, 0.0, 0);
						Streamer_Update(playerid);
   						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1425, x+0.8, y, z-0.5, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					} else { // 0 grados
				    	pmaitems[i] = CreateDynamicObject(1425, x, y+0.8, z-0.5, 0.0, 0.0, 180);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una baliza policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 6: // Cinta de la policia
		{
		    for(new i; i < MAX_PMAITEMS; i++)
			{
           		if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(19834, x-0.8, y, z, 0.0, 0.0, 270);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cinta policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
						pmaitems[i] = CreateDynamicObject(19834, x, y-0.8, z, 0.0, 0.0, 0);
						Streamer_Update(playerid);
   						PlayerActionMessage(playerid, 15.0, "ubica una cinta policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(19834, x+0.8, y, z, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cinta policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					} else { // 0 grados
				    	pmaitems[i] = CreateDynamicObject(19834, x, y+0.8, z, 0.0, 0.0, 180);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una cinta policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
		case 7: // Barricada de metal
		{
		    for(new i; i < MAX_PMAITEMS; i++)
			{
           		if(pmaitems[i] == 0)
				{
               		GetPlayerPos(playerid, x, y, z);
               		GetPlayerFacingAngle(playerid, fAngle);

               		if(fAngle <= 135 && fAngle >= 45){ // 90 grados
						pmaitems[i] = CreateDynamicObject(1424, x-0.8, y, z-0.4, 0.0, 0.0, 270);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 225 && fAngle >= 135){ // 180 grados
      					pmaitems[i] = CreateDynamicObject(1424, x, y-0.8, z-0.4, 0.0, 0.0, 0);
						Streamer_Update(playerid);
   						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
					if(fAngle <= 315 && fAngle >= 225){ // 270 grados
						pmaitems[i] = CreateDynamicObject(1424, x+0.8, y, z-0.4, 0.0, 0.0, 90);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					} else { // 0 grados
				    	pmaitems[i] = CreateDynamicObject(1424, x, y+0.8, z-0.4, 0.0, 0.0, 180);
						Streamer_Update(playerid);
						PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
						SendClientMessage(playerid, COLOR_YELLOW2, "Para quitar el objeto por /pquitar cerca de este o para eidtar por /peditar.");
						return 1;
					}
				}
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "No hay más objetos disponibles.");
		}
	}
	return 0;
}

CMD:pquitar(playerid, params[])
{
   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");

    new Float:x, Float:y, Float:z;

	for(new i; i < MAX_PMAITEMS; i++)
	{
	    GetDynamicObjectPos(pmaitems[i], x, y, z);
	    if(IsPlayerInRangeOfPoint(playerid, 1.5, x, y, z)){
	        DestroyDynamicObject(pmaitems[i]);
	        pmaitems[i] = 0;
	        PlayerActionMessage(playerid, 15.0, "quita el objeto que tiene frente a el.");
	        return 1;
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "No estas cerca de ningún objeto.");
	return 1;
}
	
