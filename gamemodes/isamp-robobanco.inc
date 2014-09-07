 #if defined _isamp_robobanco_included
	#endinput
#endif
#define _isamp_robobanco_included

//==========================SISTEMA DE ROBO AL BANCO============================

//================================CONSTANTES====================================

#define MAX_GROUP_MEMBERS 		3
#define DINERO_BOVEDA     		200000

#define MIN_DUTYCOPS_NEEDED  	3
#define MIN_GROUPMEMBERS_NEEDED 4

#define ROBBERY_GROUP_NONE      -1

#define POS_BANK_DOOR_X         2305.53
#define POS_BANK_DOOR_Y         -15.85
#define POS_BANK_DOOR_Z         26.74

#define STAGE_COMPLETED         MIN_GROUPMEMBERS_NEEDED

#define STAGE_INICIO_ROBO       0
#define STAGE_REDUCIR_ENTORNO   1
#define STAGE_DETONAR_PUERTA    2
#define STAGE_DETONAR_BOVEDA    3
#define STAGE_TOMAR_DINERO      4

//==============================DATA STORAGE====================================

new
	bool:HoldingMoney[MAX_PLAYERS],
	HoldingMoneyTimer[MAX_PLAYERS];

enum RobberyGroupInfo {
	bool:ActiveLeadership,
	MembersID[MAX_GROUP_MEMBERS],
	RobberyStage,
	RobberyStageProgress
};

new RobberyGroup[MAX_PLAYERS][RobberyGroupInfo],
	RobberyGroupNumber[MAX_PLAYERS],
	PlayerRobberyStage[MAX_PLAYERS],
	GroupOffer[MAX_PLAYERS];

//===============================FUNCIONES======================================

forward ResetBankRobberyGroup(playerid);
forward bool:AddRobberyGroupMember(leaderid, playerid); // Agrega a "playerid" como miembro del grupo de robo del lider "leaderid". Si tuvo éxito, devuelve true. Si no hay espacio, false.
forward CountRobberyGroupMembers(leaderGroup); // Cuenta la cantidad de miembros conectados que hay en un grupo de robo (no incluye al lider).
forward CancelGroupOffer(playerid, reason);
forward PrintRobberyGroupForPlayer(leaderid, playerid); // Imprime los miembros del grupo de "liderid" al jugador "playerid". Cabe mencionar que en este sistema, la id del lider coincide con la del grupo.
forward GetRobberyGroupStage(group); // Devuelve la etapa en la que se encuentra el grupo de robo.

//======================IMPLEMENTACION DE FUNCIONES=============================

stock GetRobberyGroupStage(group)
{
	return RobberyGroup[group][RobberyStage];
}

stock ResetRobberyGroup(playerid)
{
	RobberyGroup[playerid][ActiveLeadership] = false;
	for(new i = 0; i < MAX_GROUP_MEMBERS; i++)
		RobberyGroup[playerid][MembersID][i] = INVALID_PLAYER_ID;
    RobberyGroupNumber[playerid] = ROBBERY_GROUP_NONE;
    GroupOffer[playerid] = INVALID_PLAYER_ID;
	HoldingMoneyTimer[playerid] = 0;
	HoldingMoney[playerid] = false;
}

stock bool:AddRobberyGroupMember(leaderid, playerid)
{
	for(new i = 0; i < MAX_GROUP_MEMBERS; i++)
	{
	    if(RobberyGroup[leaderid][MembersID][i] == INVALID_PLAYER_ID)
	    {
	        RobberyGroup[leaderid][MembersID][i] = playerid;
	        return true;
		}
	}
	return false;
}

stock CountRobberyGroupMembers(leaderGroup)
{
	new aux;
	
	if(IsPlayerConnected(leaderGroup))
	    aux++;
	for(new i = 0; i < MAX_GROUP_MEMBERS; i++)
	{
	    if(IsPlayerConnected(RobberyGroup[leaderGroup][MembersID][i]))
	        aux ++;
	}
	return aux;
}

public CancelGroupOffer(playerid, reason)
{
	if(reason == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La invitación ha sido cancelada ya que no has respondido en 15 segundos.");
		SendClientMessage(GroupOffer[playerid], COLOR_LIGHTBLUE, "La invitación ha sido cancelada ya que el sujeto no ha respondido en 15 segundos.");
	} else
		if(reason == 0)
		{
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la invitación.");
			SendFMessage(GroupOffer[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la invitación.", GetPlayerNameEx(playerid));
		}
	GroupOffer[playerid] = INVALID_PLAYER_ID;
	return 1;
}

stock PrintRobberyGroupForPlayer(leaderid, playerid)
{
	new memberid;
	
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "==========[Grupo de robo al Banco Central de Malos Aires]==========");
	SendFMessage(playerid, COLOR_WHITE, " Lider: %s (ID %d)", GetPlayerNameEx(leaderid), leaderid);
	for(new i = 0; i < MAX_GROUP_MEMBERS; i++)
	{
	    memberid = RobberyGroup[leaderid][MembersID][i];
	    if(memberid != INVALID_PLAYER_ID)
	    {
	        if(IsPlayerConnected(memberid))
 				SendFMessage(playerid, COLOR_WHITE, " %d - Miembro: %s (ID %d)" , i, GetPlayerNameEx(memberid), memberid);
			else
			    SendFMessage(playerid, COLOR_WHITE, " %d - Miembro: %s (Desconectado)" , i, GetPlayerNameEx(memberid));
		}
		else
		    SendFMessage(playerid, COLOR_WHITE, " %d - Miembro: Ninguno" , i);
	}
	return 1;
}

//================================COMANDOS======================================

CMD:grupocrear(playerid, params[])
{ 
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 8)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(RobberyGroupNumber[playerid] != ROBBERY_GROUP_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras en un grupo de robo.");
	
    RobberyGroup[playerid][ActiveLeadership] = true;
    RobberyGroupNumber[playerid] = playerid; // La id del grupo es la id del leader.
	SendClientMessage(playerid, COLOR_WHITE, "Has creado un grupo de robo para asaltar el Banco Central de Malos Aires.");
	SendClientMessage(playerid, COLOR_WHITE, "Para ver los miembros del grupo utiliza /grupomiembros. Par mas ayuda usa /grupoayuda.");
  	return 1;
}

CMD:grupoinfo(playerid, params[])
{
	new
		group = RobberyGroupNumber[playerid],
		str[128];
	if(group != ROBBERY_GROUP_NONE)
	{
	    PrintRobberyGroupForPlayer(group, playerid);
	    switch(RobberyGroup[group][RobberyStage])
	    {
	        case STAGE_INICIO_ROBO: format(str, sizeof(str), "Inicio de robo");
	        case STAGE_REDUCIR_ENTORNO: format(str, sizeof(str), "Reducción de empleados y rehenes");
	        case STAGE_DETONAR_PUERTA: format(str, sizeof(str), "Detonación de la puerta principal");
	        case STAGE_DETONAR_BOVEDA: format(str, sizeof(str), "Detonación de la bóveda");
	        case STAGE_TOMAR_DINERO: format(str, sizeof(str), "Extracción de dinero de la bóveda");
		}
	    SendFMessage(playerid, COLOR_WHITE, "Etapa: %s - Progreso: %d de %d", str, RobberyGroup[group][RobberyStageProgress], MIN_GROUPMEMBERS_NEEDED);
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "============================================================");
	}
	return 1;
}

CMD:grupoinvitar(playerid, params[])
{
	new targetid;

	if(RobberyGroup[playerid][ActiveLeadership])
	{
		if(sscanf(params, "u", targetid))
	    	return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /grupoinvitar  [ID/Jugador]");
  		if(targetid == INVALID_PLAYER_ID || targetid == playerid || !IsPlayerConnected(targetid))
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador invalido.");
		if(PlayerInfo[targetid][pJob] != JOB_FELON)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto tiene que tener el trabajo de delincuente.");
	 	if(ThiefJobInfo[targetid][pFelonLevel] < 7)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto necesita más experiencia como delincuente para formar un grupo");
		if(RobberyGroupNumber[targetid] != ROBBERY_GROUP_NONE)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Este sujeto ya pertenece a un grupo de robo.");

	 	GroupOffer[targetid] = playerid;
	 	SendFMessage(playerid, COLOR_LIGHTBLUE, "Invitaste a %s a formar parte de tu grupo de robo.", GetPlayerNameEx(targetid));
	 	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te invitó a su grupo de robo. Para aceptar usa /grupoaceptar, de lo contrario usa /grupocancelar.", GetPlayerNameEx(playerid));
	 	SetPVarInt(targetid, "CancelGroupOffer", SetTimerEx("CancelGroupOffer", 15 * 1000, false, "ii", targetid, 1));
	}
	return 1;
}

CMD:grupoaceptar(playerid, params[])
{
	new groupLeader = GroupOffer[playerid];

	if(groupLeader == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está invitando a un grupo.");
	if(RobberyGroupNumber[playerid] != ROBBERY_GROUP_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya perteneces a otro grupo de robo.");
    if(!IsPlayerConnected(groupLeader) || !ProxDetectorS(4.0, playerid, groupLeader))
    {
		KillTimer(GetPVarInt(playerid, "CancelGroupOffer"));
		CancelGroupOffer(playerid, 0);
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido o se encuentra muy lejos.");
	}
	if(!AddRobberyGroupMember(groupLeader, playerid))
    {
		KillTimer(GetPVarInt(playerid, "CancelGroupOffer"));
		CancelGroupOffer(playerid, 0);
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay mas espacio para miembros en ese grupo!");
	}

	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Excelente, ahora estas en el grupo de robo liderado por %s! Usa /grupoinfo para mas información.", GetPlayerNameEx(groupLeader));
  	SendFMessage(groupLeader, COLOR_LIGHTBLUE, "¡Excelente, %s aceptó y ahora forma parte de tu grupo de robo.", GetPlayerNameEx(playerid));
  	KillTimer(GetPVarInt(playerid, "CancelGroupOffer"));
	CancelGroupOffer(playerid, 2);
	return 1;
}

CMD:grupocancelar(playerid, params[])
{
	if(GroupOffer[playerid] == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está invitando a un grupo.");
	        
	KillTimer(GetPVarInt(playerid, "CancelGroupOffer"));
	CancelGroupOffer(playerid, 0);
    return 1;
}

//================================COMANDOS======================================

CMD:robarbanco(playerid, params[])
{
	if(!RobberyGroup[playerid][ActiveLeadership])
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider de un grupo de robo para utilizar este comando.");
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, POS_BANK_DOOR_X, POS_BANK_DOOR_Y, POS_BANK_DOOR_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Deben estar en el interior del Banco Central de Malos Aires, cercanos a la puerta.");
	for(new i = 0; i < MIN_GROUPMEMBERS_NEEDED; i++)
 	{
		if(!IsPlayerInRangeOfPoint(RobberyGroup[playerid][MembersID][i], 10.0, POS_BANK_DOOR_X, POS_BANK_DOOR_Y, POS_BANK_DOOR_Z))
    		return SendClientMessage(playerid, COLOR_YELLOW2, "Deben estar en el interior del Banco Central de Malos Aires, cercanos a la puerta.");
	}
 	if(CountCopsOnDuty() < MIN_DUTYCOPS_NEEDED)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
	if(CountRobberyGroupMembers(playerid) < MIN_GROUPMEMBERS_NEEDED)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser cuatro, de lo contrario no podras robar el banco.");
	if(GetRobberyGroupStage(playerid) != STAGE_INICIO_ROBO)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu grupo ya se encuentra en una etapa mas avanzada del robo.");

 	RobberyGroup[playerid][RobberyStage] = STAGE_REDUCIR_ENTORNO;
 	RobberyGroup[playerid][RobberyStageProgress] = 0;
 	PoliceBankRobberyAlarm();
 	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Comienzas a robar el banco de malos aires, reduce a los rehenes, detona las bovedas y llevate el dinero.");
 	return 1;
}

stock PoliceBankRobberyAlarm()
{
	new string[128];

	format(string, sizeof(string), "[Dpto. de policía]: La alarma del banco de Malos Aires ha sido activada: estan robando el banco. Acudan de inmediato.");
 	foreach(new i : Player)
 	{
		if(isPlayerCopOnDuty(i))
		{
		    SendClientMessage(i, COLOR_PMA, "================================[URGENTE]====================================");
			SendClientMessage(i, COLOR_PMA, string);
		}
 	}
}


CMD:reducirentorno(playerid, params[])
{
	if(PlayerRobberyStage[playerid] != STAGE_INICIO_ROBO)
	    return 1;
	if(GetRobberyGroupStage(RobberyGroupNumber[playerid]) != STAGE_REDUCIR_ENTORNO)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
  	if(CountRobberyGroupMembers(RobberyGroupNumber[playerid]) < MIN_GROUPMEMBERS_NEEDED)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser cuatro, de lo contrario no podras robar el banco.");

	PlayerActionMessage(playerid, 15.0, "toma su arma y apunta a las personas que estan en el lugar, haciendo que estas se tiren al suelo.");
	PlayerRobberyStage[playerid] = STAGE_REDUCIR_ENTORNO;
	SetPVarInt(playerid, "disabled", DISABLE_STEALING);
 	SetTimerEx("TimeReducirEntorno", 20 * 1000, false, "i", playerid);
 	return 1;
}

public TimeReducirEntorno(playerid)
{
	new group = RobberyGroupNumber[playerid];
	
	RobberyGroup[group][RobberyStageProgress]++;
	if(RobberyGroup[group][RobberyStageProgress] == STAGE_COMPLETED)
	{
        RobberyGroup[group][RobberyStage] = STAGE_DETONAR_PUERTA;
		PlayerDoMessage(playerid, 15.0, "Uno de los rehenes oprimió el boton de la alarma. Detona las puertas y toma el dinero antes que llegue la policía.(/detonarpuerta)");
	}
	return 1;
}

//==============================================================================

CMD:detonarpuerta(playerid, params[])
{
	if(RobberyGroupNumber[playerid] == ROBBERY_GROUP_NONE)
    	return 1;
	if(PlayerRobberyStage[playerid] != STAGE_REDUCIR_ENTORNO)
	    return 1;
	if(GetRobberyGroupStage(RobberyGroupNumber[playerid]) != STAGE_DETONAR_PUERTA)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
	if(CountRobberyGroupMembers(RobberyGroupNumber[playerid]) < MIN_GROUPMEMBERS_NEEDED)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser cuatro, de lo contrario no podras robar el banco.");

	PlayerActionMessage(playerid, 15.0, "coloca un detonador en la puerta de entrada hacia las bovedas y se aleja esperando la explosión");
	PlayerRobberyStage[playerid] = STAGE_DETONAR_PUERTA;
 	SetTimerEx("TimeDetonacionPuerta", 5 * 1000, false, "i", playerid);
 	return 1;
}


public TimeDetonacionPuerta(playerid)
{
	new group = RobberyGroupNumber[playerid];
	RobberyGroup[group][RobberyStageProgress]++;
	if(RobberyGroup[group][RobberyStageProgress] == STAGE_COMPLETED)
	{
        RobberyGroup[group][RobberyStage] = STAGE_DETONAR_BOVEDA;
		PlayerDoMessage(playerid, 15.0, "La puerta principal se rompió con la ultima detonación. Ya se puede acceder a la bóveda (/detonarboveda)");
	}
	return 1;
}
				
//==============================================================================

CMD:detonarboveda(playerid, params[])
{
	if(RobberyGroupNumber[playerid] == ROBBERY_GROUP_NONE)
    	return 1;
	if(PlayerRobberyStage[playerid] != STAGE_DETONAR_PUERTA)
	    return 1;
	if(GetRobberyGroupStage(RobberyGroupNumber[playerid]) != STAGE_DETONAR_BOVEDA)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
 	if(CountRobberyGroupMembers(RobberyGroupNumber[playerid]) < MIN_GROUPMEMBERS_NEEDED)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser cuatro, de lo contrario no podras robar el banco.");

	PlayerActionMessage(playerid, 15.0, "coloca un detonador en la puerta de entrada hacia las bovedas y se aleja esperando la explosión.");
	PlayerRobberyStage[playerid] = STAGE_DETONAR_BOVEDA;
 	SetTimerEx("TimeDetonacionBoveda", 5 * 1000, false, "i", playerid);
 	return 1;
}
			
public TimeDetonacionBoveda(playerid)
{
	new group = RobberyGroupNumber[playerid];
	RobberyGroup[group][RobberyStageProgress]++;
	if(RobberyGroup[group][RobberyStageProgress] == STAGE_COMPLETED)
	{
	    RobberyGroup[group][RobberyStage] = STAGE_TOMAR_DINERO;
		PlayerDoMessage(playerid, 15.0, "La puerta de la bóveda fue detonada. Retira todo el dinero que puedas y escapa antes que llegue la policía. (/tomardineroboveda)");
	}
	return 1;
}
		
//==============================================================================

CMD:tomardineroboveda(playerid, params[])
{	
	if(RobberyGroupNumber[playerid] == ROBBERY_GROUP_NONE)
    	return 1;
	if(PlayerRobberyStage[playerid] != STAGE_DETONAR_BOVEDA)
	    return 1;
	if(!RobberyGroup[playerid][ActiveLeadership])
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider de un grupo de robo para utilizar este comando.");
	if(GetRobberyGroupStage(RobberyGroupNumber[playerid]) != STAGE_TOMAR_DINERO)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
   	if(CountRobberyGroupMembers(RobberyGroupNumber[playerid]) < MIN_GROUPMEMBERS_NEEDED)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser cuatro, de lo contrario no podras robar el banco.");

	PlayerActionMessage(playerid, 15.0, "toma una bolsa y comienza a retirar dinero de la boveda.");
	SendClientMessage(playerid, COLOR_WHITE, "Debes esperar 30 segundos mientras llenas las bolsas de dinero.");
	PlayerRobberyStage[playerid] = STAGE_TOMAR_DINERO;
	SetTimerEx("TimeDineroBoveda", 30 * 1000, false, "i", playerid);
 	return 1;
}

public TimeDineroBoveda(playerid)
{
	new
		memberid,
		groupid = RobberyGroupNumber[playerid];

	RobberyGroup[groupid][RobberyStageProgress] = STAGE_COMPLETED;
	GivePlayerCash(playerid, DINERO_BOVEDA);
	HoldingMoney[playerid] = true;
	HoldingMoneyTimer[playerid] = SetTimerEx("TimeHoldMoney", 20 * 60 * 1000, false, "i", playerid);
	SendClientMessage(playerid, COLOR_WHITE, "¡Has terminado de robar el dinero, huye rapido o te atraparán! (OOC: Debes aguantar 20 min sin morir, deslogear o ser atrapado)");
	for(new i = 0; i < MAX_GROUP_MEMBERS; i++)
	{
	    memberid = RobberyGroup[groupid][MembersID][i];
	    SetPVarInt(memberid, "disabled", DISABLE_NONE);
		SendClientMessage(memberid, COLOR_WHITE, "¡El lider del grupo tiene la guita! Cubrílo, porque si se muere o es atrapado pierden todo el dinero robado.");
	}
	return 1;
}								

public TimeHoldMoney(playerid)
{
    HoldingMoney[playerid] = false;
} 					
