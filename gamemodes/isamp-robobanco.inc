 #if defined _isamp_robobanco_included
	#endinput
#endif
#define _isamp_robobanco_included

//==========================SISTEMA DE ROBO AL BANCO============================

//================================CONSTANTES====================================

#define BANK_ROBBERY_COOLDOWN   30 // En horas, tiempo para que el banco pueda volver a ser robado.

#define MAX_DINERO_BOVEDA     	150000

#define GROUP_MEMBERS 			3 // No incluye al lider

#define MIN_DUTYCOPS_NEEDED  	3
#define MIN_THIEFS_NEEDED 		4

#define POS_BANK_MAIN_DOOR_X    1505.9563
#define POS_BANK_MAIN_DOOR_Y    -1134.2867
#define POS_BANK_MAIN_DOOR_Z    1015.4702

#define POS_BANK_ACCESS_DOOR_X  1489.2488
#define POS_BANK_ACCESS_DOOR_Y  -1150.4886
#define POS_BANK_ACCESS_DOOR_Z  1015.3535

#define POS_BANK_SAFE_DOOR_X    1485.5316
#define POS_BANK_SAFE_DOOR_Y  	-1129.0477
#define POS_BANK_SAFE_DOOR_Z    1002.7582

#define POS_BANK_INSIDE_SAFE_X  1485.6517
#define POS_BANK_INSIDE_SAFE_Y  -1120.5665
#define POS_BANK_INSIDE_SAFE_Z  1002.7562

#define STAGE_COMPLETED         MIN_THIEFS_NEEDED

#define STAGE_INICIO_ROBO       0
#define STAGE_REDUCIR_ENTORNO   1
#define STAGE_DETONAR_PUERTA    2
#define STAGE_DETONAR_BOVEDA    3
#define STAGE_TOMAR_DINERO      4

//==============================DATA STORAGE====================================

new bankRobberyCooldown = 0;

enum RobberyGroupInfo {
	bool:Active,
	LeaderID,
	MembersID[GROUP_MEMBERS],
	RobberyStage,
	RobberyStageProgress
};

new RobberyGroup[RobberyGroupInfo];

new bool:isPlayerInRobberyGroup[MAX_PLAYERS],
	pRobberyStage[MAX_PLAYERS],
	pRobberyGroupOffer[MAX_PLAYERS],
	bool:pHoldingMoney[MAX_PLAYERS],
	pHoldingMoneyTimer[MAX_PLAYERS];
	
//============================DEBUG DE VARIABLES================================


CMD:robobancodebug(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;

	SendFMessage(playerid, COLOR_YELLOW, "bankRobberyCooldown = %d", bankRobberyCooldown);
	SendFMessage(playerid, COLOR_YELLOW, "Active = %b", RobberyGroup[Active]);
	SendFMessage(playerid, COLOR_YELLOW, "LeaderID = %d", RobberyGroup[LeaderID]);
	for(new i = 0; i < GROUP_MEMBERS; i++)
		SendFMessage(playerid, COLOR_YELLOW, "MembersID[%d] = %d", i, RobberyGroup[MembersID][i]);
	SendFMessage(playerid, COLOR_YELLOW, "RobberyStage = %d", RobberyGroup[RobberyStage]);
	SendFMessage(playerid, COLOR_YELLOW, "RobberyStageProgress = %d", RobberyGroup[RobberyStageProgress]);
	return 1;
}

CMD:playerrobobancodebug(playerid, params[])
{
	new id;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", id))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /playerrobobancodebug [playerid]");
	if(id < 0 || id >= MAX_PLAYERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID invalida.");

	SendFMessage(playerid, COLOR_YELLOW, "isPlayerInRobberyGroup = %b", isPlayerInRobberyGroup[id]);
	SendFMessage(playerid, COLOR_YELLOW, "pRobberyStage = %d", pRobberyStage[id]);
	SendFMessage(playerid, COLOR_YELLOW, "pRobberyGroupOffer = %d", pRobberyGroupOffer[id]);
	SendFMessage(playerid, COLOR_YELLOW, "pHoldingMoney = %b", pHoldingMoney[id]);
	SendFMessage(playerid, COLOR_YELLOW, "pHoldingMoneyTimer = %d", pHoldingMoneyTimer[id]);
	return 1;
}
	
//===============================FUNCIONES======================================

forward UpdateBankRobberyCooldown(); // Actualiza los tiempos de cooldown para volver a robar el banco

forward ResetRobberyGroup(); // Resetea todo el grupo a valores nulos.
forward ResetRobberyGroupVariables(playerid); // Resetea toda las variables de "playerid" asociadas al sistema de robo al banco.

forward bool:CreateRobberyGroup(playerid); // Intenta crear un grupo con "playerid" de lider. Retorna true si lo logró, o false si no hay mas lugar para grupos.
forward bool:AddRobberyGroupMember(playerid); // Intenta ingresar a "playerid" al grupo. Devuelve true si pudo hacerlo, o false si no hay espacio.
forward bool:RemoveRobberyGroupMember(playerid); // Intenta sacar a "playerid" del grupo. Devuelve true si pudo hacerlo, o false si no está en el grupo.
forward bool:IsPlayerRobberyGroupLeader(playerid); // Devuelve true si el jugador "playerid" es lider de un grupo, false en caso contrario.

forward CountRobberyGroupMembers(); // Cuenta la cantidad de miembros conectados que hay en el grupo (incluye al lider).
forward PrintRobberyGroupInfo(playerid); // Imprime la informacion del grupo al jugador "playerid".
forward GetRobberyGroupStage(); // Devuelve la etapa del robo en la que se encuentra el grupo.
forward OnPlayerLeaveRobberyGroup(playerid, reason);
forward RobberyGroupMessage(color, const string[]); // Manda un mensaje a todo las personas del grupo (lider y miembros).

forward PoliceBankRobberyAlarm();

forward CancelRobberyGroupOffer(playerid);
forward ReducirEmpleados(playerid);
forward DetonarPuerta(playerid);
forward DetonarBoveda(playerid);
forward RobarBoveda(playerid);
forward TimeHoldMoney(playerid);

//======================IMPLEMENTACION DE FUNCIONES=============================

stock UpdateBankRobberyCooldown()
{
	if(bankRobberyCooldown > 0)
	{
		bankRobberyCooldown--;
		if(bankRobberyCooldown == ((BANK_ROBBERY_COOLDOWN - 1) * 60 * 60)) // A la hora del robo, se crean devuelta las puertas.
		{
			if(!IsValidDynamicObject(BANK_ACCESS_DOOR))
				BANK_ACCESS_DOOR = CreateDynamicObject(1495, 1488.47302, -1151.01318, 1014.42529,   0.00000, 0.00000, 0.00000);
            if(!IsValidDynamicObject(BANK_SAFE_DOOR))
				BANK_SAFE_DOOR = CreateDynamicObject(2634, 1485.59802, -1128.59485, 1003.51611,   0.00000, 0.00000, 180.00000);
		}
	}
	return 1;
}

stock GetRobberyGroupStage()
{
	return RobberyGroup[RobberyStage];
}

stock bool:IsPlayerRobberyGroupLeader(playerid)
{
	if(isPlayerInRobberyGroup[playerid] && RobberyGroup[LeaderID] == playerid && RobberyGroup[Active])
		return true;
 	return false;
}

stock bool:CreateRobberyGroup(playerid)
{
    if(RobberyGroup[Active] == false)
    {
        ResetRobberyGroup();
        RobberyGroup[Active] = true;
        RobberyGroup[LeaderID] = playerid;
       	isPlayerInRobberyGroup[playerid] = true;
       	pRobberyStage[playerid] = 0;
		return true;
	}
	return false;
}

stock bool:AddRobberyGroupMember(playerid)
{
	for(new i = 0; i < GROUP_MEMBERS; i++)
	{
	    if(RobberyGroup[MembersID][i] == INVALID_PLAYER_ID)
	    {
	        RobberyGroup[MembersID][i] = playerid;
	        isPlayerInRobberyGroup[playerid] = true;
	        pRobberyStage[playerid] = 0;
	        return true;
		}
	}
	return false;
}

stock bool:RemoveRobberyGroupMember(playerid)
{
	for(new i = 0; i < GROUP_MEMBERS; i++)
	{
	    if(RobberyGroup[MembersID][i] == playerid)
	    {
	        RobberyGroup[MembersID][i] = INVALID_PLAYER_ID;
	        isPlayerInRobberyGroup[playerid] = false;
	        pRobberyStage[playerid] = 0;
	        return true;
		}
	}
	return false;
}

stock CountRobberyGroupMembers()
{
	new aux = 0;
	
	if(RobberyGroup[LeaderID] != INVALID_PLAYER_ID && IsPlayerConnected(RobberyGroup[LeaderID]))
	    aux++;
	for(new i = 0; i < GROUP_MEMBERS; i++)
	{
	    if(RobberyGroup[MembersID][i] != INVALID_PLAYER_ID && IsPlayerConnected(RobberyGroup[MembersID][i]))
	        aux ++;
	}
	return aux;
}

public CancelRobberyGroupOffer(playerid)
{
	pRobberyGroupOffer[playerid] = INVALID_PLAYER_ID;
	return 1;
}

stock PrintRobberyGroupInfo(playerid)
{
	new memberid, str[128];
	
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "==========[Grupo de robo al Banco Central de Malos Aires]==========");
	SendFMessage(playerid, COLOR_WHITE, " Jefe: %s (ID %d)", GetPlayerNameEx(RobberyGroup[LeaderID]), RobberyGroup[LeaderID]);
	for(new i = 0; i < GROUP_MEMBERS; i++)
	{
	    memberid = RobberyGroup[MembersID][i];
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
	switch(RobberyGroup[RobberyStage])
 	{
		case STAGE_INICIO_ROBO: format(str, sizeof(str), "Inicio de robo");
	    case STAGE_REDUCIR_ENTORNO: format(str, sizeof(str), "Reducción de empleados y rehenes");
	    case STAGE_DETONAR_PUERTA: format(str, sizeof(str), "Detonación de la puerta principal");
	    case STAGE_DETONAR_BOVEDA: format(str, sizeof(str), "Detonación de la bóveda");
	    case STAGE_TOMAR_DINERO: format(str, sizeof(str), "Extracción de dinero de la bóveda");
	}
	SendFMessage(playerid, COLOR_WHITE, "Etapa: %s - Progreso: %d de %d", str, RobberyGroup[RobberyStageProgress], MIN_THIEFS_NEEDED);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "============================================================");
	return 1;
}

stock RobberyGroupMessage(color, const string[])
{
	if(RobberyGroup[Active])
	{
        SendClientMessage(RobberyGroup[LeaderID], color, string);
		for(new i = 0; i < GROUP_MEMBERS; i++)
			SendClientMessage(RobberyGroup[MembersID][i], color, string);
	}
	return 1;
}

stock ResetRobberyGroup()
{
	RobberyGroup[Active] = false;
	RobberyGroup[RobberyStage] = 0;
	RobberyGroup[RobberyStageProgress] = 0;
	if(RobberyGroup[LeaderID] != INVALID_PLAYER_ID)
	{
		isPlayerInRobberyGroup[RobberyGroup[LeaderID]] = false;
		pRobberyStage[RobberyGroup[LeaderID]] = 0;
		RobberyGroup[LeaderID] = INVALID_PLAYER_ID;
	}
	for(new i = 0; i < GROUP_MEMBERS; i++)
	{
	    if(RobberyGroup[MembersID][i] != INVALID_PLAYER_ID)
	    {
	    	isPlayerInRobberyGroup[RobberyGroup[MembersID][i]] = false;
	    	pRobberyStage[RobberyGroup[MembersID][i]] = 0;
	    	RobberyGroup[MembersID][i] = INVALID_PLAYER_ID;
		}
	}
}

stock ResetRobberyGroupVariables(playerid)
{
	isPlayerInRobberyGroup[playerid] = false;
	pRobberyStage[playerid] = 0;
	pRobberyGroupOffer[playerid] = INVALID_PLAYER_ID;
	pHoldingMoney[playerid] = false;
	pHoldingMoneyTimer[playerid] = 0;
}
	
public OnPlayerLeaveRobberyGroup(playerid, reason)
{
	if(pHoldingMoney[playerid])
	{
		GivePlayerCash(playerid, -MAX_DINERO_BOVEDA);
		KillTimer(pHoldingMoneyTimer[playerid]);
		pHoldingMoney[playerid] = false;
		SendClientMessage(playerid, COLOR_WHITE, "No has aguantado el tiempo suficiente y has perdido todo el dinero robado.");
 	}
	if(isPlayerInRobberyGroup[playerid])
	{
	    new str[128];
	    
		if(IsPlayerRobberyGroupLeader(playerid))
		{
	 		if(reason == 1)
	 		    format(str, sizeof(str), "El grupo de robo ha sido eiminado ya que el lider %s se ha desconectado.", GetPlayerNameEx(playerid));
	 		else if(reason == 2)
	 		    format(str, sizeof(str), "El grupo de robo ha sido eiminado ya que el lider %s ha muerto.", GetPlayerNameEx(playerid));
    		RobberyGroupMessage(COLOR_WHITE, str);
			ResetRobberyGroup();
		} else
			{
				if(pRobberyStage[playerid] == STAGE_DETONAR_BOVEDA) // Si el miembro ya puso la ultima bomba (no tenía nada mas para hacer), no borramos el grupo, solo lo sacamos.
				{
					if(reason == 1)
	                    format(str, sizeof(str), "[Grupo de robo]: %s se ha desconectado pero es posible continuar sin él.", GetPlayerNameEx(playerid));
					else if(reason == 2)
		 		    	format(str, sizeof(str), "[Grupo de robo]: %s ha muerto pero es posible continuar sin él.", GetPlayerNameEx(playerid));
                    RobberyGroupMessage(COLOR_WHITE, str);
					RemoveRobberyGroupMember(playerid);
				} else
				    {
		                if(reason == 1)
		                    format(str, sizeof(str), "[Grupo de robo]: El grupo ha sido eliminado ya que %s se ha desconectado y no es posible continuar sin él.", GetPlayerNameEx(playerid));
						else if(reason == 2)
			 		    	format(str, sizeof(str), "[Grupo de robo]: El grupo ha sido eliminado ya que %s ha muerto y no es posible continuar sin él.", GetPlayerNameEx(playerid));
                        RobberyGroupMessage(COLOR_WHITE, str);
				  		ResetRobberyGroup();
					}
			}
	}
	return 1;
}

//================================COMANDOS======================================

CMD:grupoayuda(playerid, params[])
{
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

	SendClientMessage(playerid, COLOR_WHITE, "[Comandos]: /grupocrear /grupoeliminar /grupoinfo /grupoinvitar /grupoaceptar /grupoexpulsar /grupoabandonar");
	SendClientMessage(playerid, COLOR_WHITE, "[Info]: Para armar tu grupo de robo al banco, deberás crear un grupo e invitar a otros delincuentes para que se unan.");
	SendClientMessage(playerid, COLOR_WHITE, "[Comandos]: /robarbanco /reducirempleados /detonarpuerta /detonarboveda /robarboveda");
    SendClientMessage(playerid, COLOR_WHITE, "[Info]: Para concretar el robo, tendrás que pasar por varias etapas: tomar el lugar, explotar puertas y bóvedas, y robar el dinero.");
	return 1;
}

CMD:grupocrear(playerid, params[])
{
	if(PlayerInfo[playerid][pJob] != JOB_FELON)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
	if(ThiefJobInfo[playerid][pFelonLevel] < 8)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
	if(isPlayerInRobberyGroup[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras en un grupo de robo.");
	if(!CreateRobberyGroup(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya hay otro grupo de robo al banco en curso.");

	SendClientMessage(playerid, COLOR_WHITE, "Has creado un grupo de robo para asaltar el Banco Central de Malos Aires. Mas info en /grupoayuda.");
  	return 1;
}

CMD:grupoinvitar(playerid, params[])
{
	new targetid;

	if(!IsPlayerRobberyGroupLeader(playerid))
	    return 1;
	if(sscanf(params, "u", targetid))
	   	return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /grupoinvitar  [ID/Jugador]");
  	if(!IsPlayerConnected(targetid) || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
 	if(!ProxDetectorS(4.0, playerid, targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra muy lejos.");
	if(PlayerInfo[targetid][pJob] != JOB_FELON)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto tiene que tener el trabajo de delincuente.");
	if(ThiefJobInfo[targetid][pFelonLevel] < 6)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto necesita más experiencia como delincuente para formar un grupo.");
	if(isPlayerInRobberyGroup[targetid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Este sujeto ya pertenece a un grupo de robo.");
	if(pRobberyGroupOffer[targetid] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto tiene una invitación pendiente, aguarda.");

 	pRobberyGroupOffer[targetid] = playerid;
 	SendFMessage(playerid, COLOR_LIGHTBLUE, "Invitaste a %s a formar parte de tu grupo de robo. La oferta termina en 10 segs.", GetPlayerNameEx(targetid));
 	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te invitó a su grupo de robo. Para aceptar usa /grupoaceptar. La oferta termina en 10 segs.", GetPlayerNameEx(playerid));
 	SetTimerEx("CancelRobberyGroupOffer", 10000, false, "i", targetid);
	return 1;
}

CMD:grupoaceptar(playerid, params[])
{
	new leaderid = pRobberyGroupOffer[playerid], str[128];

	if(leaderid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está invitando a un grupo.");
	if(isPlayerInRobberyGroup[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya perteneces a un grupo de robo.");
    if(!IsPlayerConnected(leaderid) || !IsPlayerRobberyGroupLeader(leaderid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido / El sujeto no es lider de ningún grupo.");
	if(!ProxDetectorS(4.0, playerid, leaderid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra muy lejos.");
	if(!AddRobberyGroupMember(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay mas espacio para miembros en ese grupo!");

	format(str, sizeof(str), "%s ha ingresado al grupo de robo al banco. Mas información en /grupoayuda.", GetPlayerNameEx(playerid));
	RobberyGroupMessage(COLOR_LIGHTBLUE, str);
	return 1;
}

CMD:grupoexpulsar(playerid, params[])
{
	new targetid, str[128];

	if(!IsPlayerRobberyGroupLeader(playerid))
    	return 1;
	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /grupoexpulsar  [ID/Jugador]");
  	if(!IsPlayerConnected(targetid) || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido. Revisa el estado de tu grupo con /grupoinfo.");
	if(!RemoveRobberyGroupMember(targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido. Revisa el estado de tu grupo con /grupoinfo.");

	format(str, sizeof(str), "El lider %s ha expulsado a %s del grupo de robo al banco.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
	RobberyGroupMessage(COLOR_WHITE, str);
	return 1;
}

CMD:grupoabandonar(playerid, params[])
{
	new str[128];
	
	if(IsPlayerRobberyGroupLeader(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando siendo el lider. Puedes eliminar el grupo con /grupoeliminar.");
	if(isPlayerInRobberyGroup[playerid])
	{
	    format(str, sizeof(str), "%s ha abandonado el grupo de robo al banco.", GetPlayerNameEx(playerid));
	    RobberyGroupMessage(COLOR_WHITE, str);
	    RemoveRobberyGroupMember(playerid);
	}
	return 1;
}

CMD:grupoeliminar(playerid, params[])
{
	if(!IsPlayerRobberyGroupLeader(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No eres lider de ningún grupo de robo.");

	RobberyGroupMessage(COLOR_WHITE, "El lider ha eliminado el grupo de robo al banco. Mas info en /grupoayuda.");
	ResetRobberyGroup();
	return 1;
}

CMD:grupoinfo(playerid, params[])
{
	if(isPlayerInRobberyGroup[playerid])
	{
	    if(RobberyGroup[Active])
	    	PrintRobberyGroupInfo(playerid);
	}
	return 1;
}

//================================COMANDOS======================================

CMD:robarbanco(playerid, params[])
{
	new memberid,
		string[128];
	
	if(!IsPlayerRobberyGroupLeader(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider de un grupo de robo para utilizar este comando.");
	if(bankRobberyCooldown > 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Las bovedas del banco están vacias, no tiene sentido. (OOC: El banco todavía no está disponible para asaltar)");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, POS_BANK_MAIN_DOOR_X, POS_BANK_MAIN_DOOR_Y, POS_BANK_MAIN_DOOR_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El grupo completo debe estar en el interior del Banco Central de Malos Aires, cercanos a la puerta principal.");
	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano para iniciar el asalto.");
	for(new i = 0; i < GROUP_MEMBERS; i++)
 	{
 	    memberid = RobberyGroup[MembersID][i];
		if(memberid != INVALID_PLAYER_ID && IsPlayerConnected(memberid))
		{
			if(!IsPlayerInRangeOfPoint(memberid, 5.0, POS_BANK_MAIN_DOOR_X, POS_BANK_MAIN_DOOR_Y, POS_BANK_MAIN_DOOR_Z))
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "El grupo completo debe estar en el interior del Banco Central de Malos Aires, cercanos a la puerta principal.");
			if(!hasFireGun(memberid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "Todo tu equipo debe contar con algun arma de fuego en la mano.");
		}
	}
 	if(CountCopsOnDuty() < MIN_DUTYCOPS_NEEDED)
 	{
 		SendFMessage(playerid, COLOR_YELLOW2, "Deben haber minimo %d policias en servicio conectados.", MIN_DUTYCOPS_NEEDED);
 		return 1;
	}
	if(CountRobberyGroupMembers() < MIN_THIEFS_NEEDED)
	{
		SendFMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de robo deben ser %d, de lo contrario no podras robar el banco.", MIN_THIEFS_NEEDED);
		return 1;
	}
	if(GetRobberyGroupStage() != STAGE_INICIO_ROBO)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu grupo ya se encuentra en una etapa mas avanzada del robo.");

 	RobberyGroup[RobberyStage] = STAGE_REDUCIR_ENTORNO;
 	RobberyGroup[RobberyStageProgress] = 0;
 	pRobberyStage[playerid] = STAGE_INICIO_ROBO;
 	PlayerDoMessage(playerid, 15.0, "Un grupo armado de sujetos entra al banco violentamente y desenfundan sus armas");
	PlayerDoMessage(playerid, 15.0, "Uno de los empleados oprime el boton de la alarma, forzando la inminente llegada de la policía");
	RobberyGroupMessage(COLOR_LIGHTBLUE, "El robo consiste en etapas: reduce a los rehenes y detona las bóvedas para llevate el dinero. Mas info en /grupoayuda.");
    PoliceBankRobberyAlarm();
    bankRobberyCooldown = BANK_ROBBERY_COOLDOWN * 60 * 60;
    format(string, sizeof(string), "[ADMIN INFO]: %s (ID %d) ha iniciado un robo al Banco Central de Malos Aires.", GetPlayerNameEx(playerid), playerid);
	AdministratorMessage(COLOR_LIGHTBLUE, string, 1);
	return 1;
}

public PoliceBankRobberyAlarm()
{
	new string[128];

	format(string, sizeof(string), "[Dpto. de policía]: Ha sonado la alarma del Banco Central de Malos Aires. ¡Lo están robando!");
 	foreach(new i : Player)
 	{
		if(isPlayerCopOnDuty(i))
		{
		    SendClientMessage(i, COLOR_PMA, "================================[URGENTE]==================================");
			SendClientMessage(i, COLOR_PMA, string);
			SendClientMessage(i, COLOR_PMA, "================================[URGENTE]==================================");
		}
 	}
}


CMD:reducirempleados(playerid, params[])
{
	if(!isPlayerInRobberyGroup[playerid] || pRobberyStage[playerid] != STAGE_INICIO_ROBO)
    	return 1;
	if(GetRobberyGroupStage() != STAGE_REDUCIR_ENTORNO)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
	if(!hasFireGun(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un arma de fuego en la mano.");

	PlayerActionMessage(playerid, 15.0, "toma su arma y apunta a las personas que estan en el lugar, haciendo que estas se tiren al suelo.");
	pRobberyStage[playerid] = STAGE_REDUCIR_ENTORNO;
	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 0);
	GameTextForPlayer(playerid, "Reduciendo empleados y clientes...", 20000, 4);
 	SetTimerEx("ReducirEmpleados", 20000, false, "i", playerid);
 	return 1;
}

public ReducirEmpleados(playerid)
{
	if(isPlayerInRobberyGroup[playerid])
	{
		RobberyGroup[RobberyStageProgress]++;
		if(RobberyGroup[RobberyStageProgress] == STAGE_COMPLETED)
		{
	        RobberyGroup[RobberyStage] = STAGE_DETONAR_PUERTA;
	        RobberyGroup[RobberyStageProgress] = 0;
			PlayerDoMessage(playerid, 15.0, "Los empleados y clientes se encuentran reducidos en el piso. Es tiempo del siguiente paso");
		}
	}
	return 1;
}

//==============================================================================

CMD:detonarpuerta(playerid, params[])
{
	if(!isPlayerInRobberyGroup[playerid] || pRobberyStage[playerid] != STAGE_REDUCIR_ENTORNO)
    	return 1;
	if(GetRobberyGroupStage() != STAGE_DETONAR_PUERTA)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
	if(!IsPlayerInRangeOfPoint(playerid, 1.4, POS_BANK_ACCESS_DOOR_X, POS_BANK_ACCESS_DOOR_Y, POS_BANK_ACCESS_DOOR_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar junto a la puerta de acceso al resto del edificio.");

	PlayerActionMessage(playerid, 15.0, "comienza a colocar una carga explosiva en la puerta de acceso a las bóvedas.");
	pRobberyStage[playerid] = STAGE_DETONAR_PUERTA;
	TogglePlayerControllable(playerid, false);
	SetPVarInt(playerid, "disabled", DISABLE_FREEZE); // Para no descongelarse con /noanim.
	SetTimerEx("Unfreeze", 5 * 1000, false, "i", playerid);
	GameTextForPlayer(playerid, "Plantando explosivos...", 5 * 1000, 4);
 	SetTimerEx("DetonarPuerta", 10 * 1000, false, "i", playerid);
 	return 1;
}

public DetonarPuerta(playerid)
{
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
	
	if(isPlayerInRobberyGroup[playerid])
	{
		CreateExplosion(POS_BANK_ACCESS_DOOR_X, POS_BANK_ACCESS_DOOR_Y, POS_BANK_ACCESS_DOOR_Z, 0, 5.0);
		RobberyGroup[RobberyStageProgress]++;
		if(RobberyGroup[RobberyStageProgress] == STAGE_COMPLETED)
		{
	        RobberyGroup[RobberyStage] = STAGE_DETONAR_BOVEDA;
	        RobberyGroup[RobberyStageProgress] = 0;
	        PlayerDoMessage(playerid, 15.0, "La carga de C4 explota fuertemente y destruye la puerta principal, abriendo un hueco");
			DestroyDynamicObject(BANK_ACCESS_DOOR);
		} else
			PlayerDoMessage(playerid, 15.0, "La carga de C4 explota fuertemente y daña la puerta principal");
	}
	return 1;
}
				
//==============================================================================

CMD:detonarboveda(playerid, params[])
{
	if(!isPlayerInRobberyGroup[playerid] || pRobberyStage[playerid] != STAGE_DETONAR_PUERTA)
    	return 1;
	if(GetRobberyGroupStage() != STAGE_DETONAR_BOVEDA)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
 	if(!IsPlayerInRangeOfPoint(playerid, 1.4, POS_BANK_SAFE_DOOR_X, POS_BANK_SAFE_DOOR_Y, POS_BANK_SAFE_DOOR_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar junto a la bóveda del banco.");

	PlayerActionMessage(playerid, 15.0, "comienza a colocar una carga explosiva en la puerta de la bóveda del banco.");
	pRobberyStage[playerid] = STAGE_DETONAR_BOVEDA;
	TogglePlayerControllable(playerid, false);
	SetPVarInt(playerid, "disabled", DISABLE_FREEZE); // Para no descongelarse con /noanim.
	SetTimerEx("Unfreeze", 5 * 1000, false, "i", playerid);
	GameTextForPlayer(playerid, "Plantando explosivos...", 5 * 1000, 4);
 	SetTimerEx("DetonarBoveda", 10 * 1000, false, "i", playerid);
 	return 1;
}
			
public DetonarBoveda(playerid)
{
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
	
	if(isPlayerInRobberyGroup[playerid])
	{
		CreateExplosion(POS_BANK_SAFE_DOOR_X, POS_BANK_SAFE_DOOR_Y, POS_BANK_SAFE_DOOR_Z, 6, 10.0);
		RobberyGroup[RobberyStageProgress]++;
		if(RobberyGroup[RobberyStageProgress] == STAGE_COMPLETED)
		{
		    RobberyGroup[RobberyStage] = STAGE_TOMAR_DINERO;
		    RobberyGroup[RobberyStageProgress] = 0;
			PlayerDoMessage(playerid, 15.0, "La carga de C4 explota y la bóveda cede, pudiendose apreciar una gran cantidad de dinero dentro");
			DestroyDynamicObject(BANK_SAFE_DOOR);
		} else
		    PlayerDoMessage(playerid, 15.0, "La carga de C4 explota fuertemente y daña la parte delantera de la bóveda");
	}
	return 1;
}
		
//==============================================================================

CMD:robarboveda(playerid, params[])
{	
	if(!isPlayerInRobberyGroup[playerid] || pRobberyStage[playerid] != STAGE_DETONAR_BOVEDA)
    	return 1;
	if(!IsPlayerRobberyGroupLeader(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider de un grupo de robo para utilizar este comando.");
	if(GetRobberyGroupStage() != STAGE_TOMAR_DINERO)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Tu grupo se encuentra en otra etapa del robo.");
   	if(!IsPlayerInRangeOfPoint(playerid, 4.0, POS_BANK_INSIDE_SAFE_X, POS_BANK_INSIDE_SAFE_Y, POS_BANK_INSIDE_SAFE_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar dentro de la bóveda del Banco.");

	PlayerActionMessage(playerid, 15.0, "toma una bolsa y comienza a retirar dinero de la boveda.");
	SendClientMessage(playerid, COLOR_WHITE, "Debes esperar 30 segundos mientras llenas las bolsas de dinero.");
	pRobberyStage[playerid] = STAGE_TOMAR_DINERO;
	TogglePlayerControllable(playerid, false);
	SetPVarInt(playerid, "disabled", DISABLE_STEALING); // Para no descongelarse con /noanim.
	GameTextForPlayer(playerid, "Guardando el dinero...", 30 * 1000, 4);
	SetTimerEx("RobarBoveda", 30 * 1000, false, "i", playerid);
 	return 1;
}

public RobarBoveda(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
	
	if(isPlayerInRobberyGroup[playerid])
	{
		GivePlayerCash(playerid, MAX_DINERO_BOVEDA);
		pHoldingMoney[playerid] = true;
		pHoldingMoneyTimer[playerid] = SetTimerEx("TimeHoldMoney", 20 * 60 * 1000, false, "i", playerid);
		RobberyGroupMessage(COLOR_WHITE, "¡El lider ha terminado de guardar el dinero, huye rapido o te atraparán! (OOC: El dinero se pierde si el lider deslogea/muere)");
		ResetRobberyGroup();
	}
	return 1;
}								

public TimeHoldMoney(playerid)
{
    pHoldingMoney[playerid] = false;
}
