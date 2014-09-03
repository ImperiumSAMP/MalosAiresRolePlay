 #if defined _isamp_robobanco_included
	#endinput
#endif
#define _isamp_robobanco_included

#define MAX_MEMBERS_GROUP 3
#define DINERO_BOVEDA     200000
 
 new 
    TheftBank[MAX_PLAYERS] = 0,
    bool:groupinvite[MAX_PLAYERS],
	GroupLeader[MAX_PLAYERS] = 0,
	LeaderInvite[MAX_PLAYERS],
	MembersGroup[MAX_MEMBERS_GROUP] = 0,
	ConectedMembers[MAX_PLAYERS] = 0,
	ReduciendoEntorno[MAX_PLAYERS] = 0,
	EntornoReducido[MAX_PLAYERS] = 0,
	DetonandoPuerta[MAX_PLAYERS] = 0,
	DetonacionPuertaBoveda[MAX_PLAYERS] = 0,
	DetonandoBoveda[MAX_PLAYERS] = 0,
	DetonacionBoveda[MAX_PLAYERS] = 0,
	TomandoDineroBoveda[MAX_PLAYERS] = 0,
	DineroBoveda[MAX_PLAYERS] = 0,
	HoldMoney[MAX_PLAYERS] = 0;
 
 
 CMD:robarbanco(playerid, params[]) 
{ 
 new
    cont2 = 0,
	cont3 = 0;
 
 if(!IsPlayerInRangeOfPoint(playerid, 10.0, 2305.531494, -15.851466, 26.749565))
    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la puerta desde adentro del banco.");
		
 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

 if(ThiefJobInfo[playerid][pFelonLevel] < 8)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
		
 if(GroupLeader[playerid] == 0) 
    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider del grupo para utilizar este comando.");
			
 foreach(new i : Player)
 {
        if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i])
   			cont3 ++;
		   
 }		
    
 if(cont3 < 3)
 	return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
 
 foreach(new i : Player)
 {
	    if(ConectedMembers[i] == 6)
	   		cont2 ++;
 }
 if(cont2 < 3)
 	return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de asalto deben ser cuatro, de lo contrario no podras robar el banco.");
					
 TheftBank[playerid] = 1;
 SendClientMessage(playerid, COLOR_LIGHTBLUE, "Comienzas a robar el banco de malos aires, reduce a los rehenes, detona las bovedas y llevate el dinero.");
 return 1;
}
 //==============================================================//==============================================================//==============================================================//==============================================================
 
 TIMER:CancelGroupInvite(playerid, reason) {
	if(reason == 1) {
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La invitación ha sido cancelada ya que no has respondido en 30 segundos.");
		SendClientMessage(LeaderInvite[playerid], COLOR_LIGHTBLUE, "La invitación ha sido cancelada ya que el sujeto no ha respondido en 30 segundos.");
	} else
		if(reason == 0) {
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la invitación.");
			SendFMessage(LeaderInvite[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la invitación.", GetPlayerNameEx(playerid));
		}
	groupinvite[LeaderInvite[playerid]] = false;
	LeaderInvite[playerid] = INVALID_PLAYER_ID;
	return 1;
}
 
CMD:formargrupo(playerid, params[]) 
{ 
 new 
    targetid;
 
 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");

 if(ThiefJobInfo[playerid][pFelonLevel] < 8)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");
		
 if(sscanf(params, "u", targetid))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /formargrupo  [ID/Jugador]");
			
 if(PlayerInfo[targetid][pJob] != JOB_FELON)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto tiene que tener el trabajo de delincuente.");
			    
 if(ThiefJobInfo[targetid][pFelonLevel] < 7)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto necesita más experiencia como delincuente para formar un grupo");
						
 if(targetid == INVALID_PLAYER_ID || targetid == playerid)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador invalido.");
							
 if(MembersGroup[playerid] == MAX_MEMBERS_GROUP)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El grupo de asalto ya tiene la maxima capacidad de integrantes.(Cuatro)");
							
 if(ConectedMembers[playerid] == 6)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Este sujeto ya pertenece a tu grupo de asalto.");
						        
 groupinvite[playerid] = true;		
 LeaderInvite[targetid] = playerid;	
 SendFMessage(playerid, COLOR_LIGHTBLUE, "Invitaste a %s para formar tu grupo de asalto.", GetPlayerNameEx(targetid));
 SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te ha invitado para formar su grupo de asalto, para aceptar pon /aceptargrupoasalto de lo contrario pon /cancelargrupoasalto.", GetPlayerNameEx(playerid));			
 SetPVarInt(targetid, "CancelGroupInvite", SetTimerEx("CancelGroupInvite", 30 * 1000, 0, "ii", targetid, 1));	
 return 1;								
}
//==============================================================//==============================================================//==============================================================//==============================================================

CMD:aceptargrupoasalto(playerid, params[])
{
	new 
		inviterid = LeaderInvite[playerid];
      
    if(inviterid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está invitando a un grupo.");
    if(!IsPlayerConnected(inviterid) || !groupinvite[inviterid])
	{
		KillTimer(GetPVarInt(playerid, "CancelGroupInvite"));
		CancelGroupInvite(playerid, 0);
		return SendClientMessage(playerid, COLOR_YELLOW2, "Hubo un error durante la invitación, cancelando...");
    }
    if(!ProxDetectorS(4.0, playerid, inviterid))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
		
    ConectedMembers[playerid] = 6;
	MembersGroup[playerid] ++;
    GroupLeader[inviterid] = 1;
  	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Excelente, ahora estas formando el grupo de asalto de %s", GetPlayerNameEx(inviterid));
  	SendFMessage(inviterid, COLOR_LIGHTBLUE, "¡Excelente, %s aceptó y ahora forma parte de tu grupo de asalto", GetPlayerNameEx(playerid));
  	KillTimer(GetPVarInt(playerid, "CancelGroupInvite"));
	CancelGroupInvite(playerid, 2);
    return 1;
}

CMD:cancelargrupoasalto(playerid, params[])
{
    new 
	   inviterid = LeaderInvite[playerid];
		 
	if(inviterid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está invitando a un grupo.");
	        
	KillTimer(GetPVarInt(playerid, "CancelGroupInvite"));	
	CancelGroupInvite(playerid,0);
    return 1;
}

//==============================================================//==============================================================//==============================================================//==============================================================

CMD:reducirentorno(playerid, params[])
{
 new 
    cont2 = 0,
	cont3 = 0,
	string[128];
 
 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
    
 if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando."); 
		
 if(TheftBank[playerid] == 0)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Utiliza /robarbanco para iniciar el robo.");

 foreach(new i : Player)
 {
        if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i])
   			cont3 ++;
 }		
    
 if(cont3 < 3)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
	    
 foreach(new i : Player)
 {
	    if(ConectedMembers[i] == 6)
	   		cont2 ++;
 }
	            
 if(cont2 < 3)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de asalto deben ser cuatro, de lo contrario no podras robar el banco.");
		
 PlayerActionMessage(playerid, 15.0, "toma su arma y apunta a todo las personas que estan en el lugar, haciendo que estos se tiren al suelo.");
 if(EntornoReducido[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Todos los rehenes ya estan reducidos en el suelo, boca abajo.");
			
 if(ReduciendoEntorno[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Aun estas reduciendo a los rehenes, espera a que todos estos esten acostados en el piso. (20 segundos)");
		        
 format(string, sizeof(string), "[Dpto. de policía]: La alarma del banco de Malos Aires ha sido activada, estan robando el banco. Acudan de inmediato.");		                
 foreach(new play : Player)
 {
		if(PlayerInfo[play][pFaction] == FAC_PMA && CopDuty[play])
			SendClientMessage(play, COLOR_PMA, string);
 }
 ReduciendoEntorno[playerid] = 1;
 SetTimerEx("TimeReducirEntorno", 20000, false, "i", playerid);
 return 1;
}

public TimeReducirEntorno(playerid)
{
	ReduciendoEntorno[playerid] = 0;
	foreach(new i : Player)
	{
	    if(ConectedMembers[i] == 6)
		{
	   	    EntornoReducido[i] = 1;
			SetPVarInt(i, "disabled", DISABLE_STEALING);
			SendClientMessage(i, COLOR_LIGHTBLUE, "Uno de los rehenes oprimió el boton de la alarma, detona las puertas y toma el dinero antes que llegue la policía.(/detonarpuerta)");
	    }
	}
    return 1;
}
//==============================================================//==============================================================//==============================================================//==============================================================

CMD:detonarpuerta(playerid, params[])
{
 new 
    cont2 = 0,
	cont3 = 0;

 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
    
 if(ThiefJobInfo[playerid][pFelonLevel] < 7)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");  
		
 foreach(new i : Player)
 {
        if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i])
    	    cont3 ++;
 }		
    
 if(cont3 < 3)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
			
 foreach(new i : Player)
 {
        if(ConectedMembers[i] == 6)
            cont2 ++;
 }
 if(cont2 < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de asalto deben ser cuatro, de lo contrario no podras robar el banco.");		
			
 if(EntornoReducido[playerid] == 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes reducir a los rehenes antes de detonar la puerta de la boveda.");
				
 if(DetonacionPuertaBoveda[playerid] == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "La puerta de acceso a las bovedas ya ha sido detonada, sigue con las siguientes.");
			
 if(ReduciendoEntorno[playerid] != 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Aun estas reduciendo a los rehenes, espera a que todos estos esten acostados en el piso. (20 segundos)");

 PlayerActionMessage(playerid, 15.0, "coloca un detonador en la puerta de entrada hacia las bovedas y se aleja esperando la explosión");
 if(DetonandoPuerta[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes esperar a que explote la primera bomba para poner otro detonador en las bovedas. (5 segundos)");		
                            
 DetonandoPuerta[playerid] = 1;
 SetTimerEx("TimeDetonacionPuerta", 5000, false, "i", playerid);
 return 1;
}


public TimeDetonacionPuerta(playerid)
{
	DetonandoPuerta[playerid] = 0;
	foreach(new i : Player)
	{
	    if(ConectedMembers[i] == 6)
		{
	 	    DetonacionPuertaBoveda[i] = 1;
		    SendClientMessage(i, COLOR_LIGHTBLUE, "Las puerta principal fue detonada, ya puedes acceder donde se encuentran las bovedas. (/detonarboveda)");
		}
	}
	return 1;
}				
//==============================================================//==============================================================//==============================================================//==============================================================	

CMD:detonarboveda(playerid, params[])
{
 new 
    cont2 = 0,
	cont3 = 0;
 
 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
    
 if(ThiefJobInfo[playerid][pFelonLevel] < 7)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");  
			
 foreach(new i : Player)
 {
        if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i])
 	        cont3 ++;
 }		
    
 if(cont3 < 3)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
			
 foreach(new i : Player)
 {
	    if(ConectedMembers[i] == 6)
	   	     cont2 ++;
 }
	        
 if(cont2 < 3)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de asalto deben ser cuatro, de lo contrario no podras robar el banco.");		
			
 if(EntornoReducido[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes reducir a los rehenes antes de detonar la puerta de la boveda.");
				
 if(ReduciendoEntorno[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Aun estas reduciendo a los rehenes, espera a que todos estos esten acostados en el piso. (20 segundos)");
				
 if(DetonacionPuertaBoveda[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de detonar la boveda tienes que detonar la puerta principal para pasar donde se encuentran las bovedas.");
			
 if(DetonandoPuerta[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Esta por detonar la bomba colocada en la puerta principal, espera a que esta explote para continuar.");
		   
 PlayerActionMessage(playerid, 15.0, "coloca un detonador en la puerta de entrada hacia las bovedas y se aleja esperando la explosión");
 if(DetonandoBoveda[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes esperar a que explote la bomba para continuar. (5 segundos)");		
								
 DetonandoBoveda[playerid] = 1;
 SetTimerEx("TimeDetonacionBoveda", 5000, false, "i", playerid);
 return 1;
}
			
public TimeDetonacionBoveda(playerid)
{
	DetonandoBoveda[playerid] = 0;
	foreach(new i : Player)
	{
	    if(ConectedMembers[i] == 6)
		{
		    DetonacionBoveda[i] = 1;
		    SendClientMessage(i, COLOR_LIGHTBLUE, "La puerta de la boveda fue detonada, retira todo el dinero que puedas y escapa antes que llegue la policía. (/tomardineroboveda)");
		}
	}
	return 1;
}						
//==============================================================//==============================================================//==============================================================//==============================================================	

CMD:tomardineroboveda(playerid, params[])
{	
 new 
    cont2 = 0,
	cont3 = 0;
	
 if(PlayerInfo[playerid][pJob] != JOB_FELON)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener el trabajo de delincuente para utilizar este comando.");
    
 if(ThiefJobInfo[playerid][pFelonLevel] < 8)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas más experiencia para utilizar este comando.");  
		
 foreach(new i : Player)
 {
        if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i])
    	    cont3 ++;
 }		
    
 if(cont3 < 3)
    return SendClientMessage(playerid, COLOR_YELLOW2, "Deben haber minimo tres policias en servicio conectados.");
			
 foreach(new i : Player)
 {
        if(ConectedMembers[i] == 6)
            cont2 ++;
 }
			
 if(cont2 < 3)
    return SendClientMessage(playerid, COLOR_YELLOW2, "Recuerda que en tu grupo de asalto deben ser cuatro, de lo contrario no podras robar el banco.");		
			
 if(GroupLeader[playerid] == 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el lider del grupo para utilizar este comando.");
			
 if(EntornoReducido[playerid] == 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes reducir a los rehenes antes de detonar la puerta de la boveda.");
				
 if(ReduciendoEntorno[playerid] != 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Aun estas reduciendo a los rehenes, espera a que todos estos esten acostados en el piso. (20 segundos)");
				
 if(DetonacionPuertaBoveda[playerid] == 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de detonar la boveda tienes que detonar la puerta principal para pasar donde se encuentran las bovedas.");
			
 if(DetonandoPuerta[playerid] != 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Esta por detonar la bomba colocada en la puerta principal, espera a que esta explote para continuar.");
			
 if(DetonacionBoveda[playerid] == 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de intentar tomar el dinero de la boveda tienes que abrirla detonando la misma.");
							
 if(DetonandoBoveda[playerid] != 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes esperar a que explote la bomba colocado en la boveda para continuar. (5 segundos)");
									
 if(TomandoDineroBoveda[playerid] != 0)
	return SendClientMessage(playerid, COLOR_YELLOW2, "El lider del grupo ya esta juntando todo el dinero en una bolsa.");
											
 if(DineroBoveda[playerid] == 1)
	return SendClientMessage(playerid, COLOR_YELLOW2, "Ya has tomado el dinero de la boveda, escapa de la policia");
									            
 PlayerActionMessage(playerid, 15.0, "toma una bolsa y comienza a retirar dinero de la boveda");
 SendClientMessage(playerid, -1, "Debes esperar 30 segundos mientras llenas las bolsas de dinero.");
 TomandoDineroBoveda[playerid] = 1;
 HoldMoney[playerid] = 1;
 SetTimerEx("TimeDineroBoveda", 30000, false, "i", playerid);
 SetTimerEx("TimeHoldMoney", 1200000, false, "i", playerid);
 return 1;
}					

public TimeDineroBoveda(playerid)
{
	TomandoDineroBoveda[playerid] = 0;
	GivePlayerCash(playerid, DINERO_BOVEDA);
	foreach(new i : Player)
	{
	    if(ConectedMembers[i] == 6)
		{
	   	    DineroBoveda[i] = 1;
			SetPVarInt(i, "disabled", DISABLE_NONE);
		    SendClientMessage(i, COLOR_LIGHTBLUE, "El lider del grupo tiene el dinero. Cubrelo, ya que si este muere pierden toda la plata robada.");
			SendClientMessage(i, COLOR_YELLOW2, "OOC: El lider tiene que aguantar veinte minutos con la plata sin ser matado, agarrado, y tampoco puede deslogear. Sino perderan el dinero.");
	    }
	}
	return 1;
}								

public TimeHoldMoney(playerid)
{
    HoldMoney[playerid] = 0;
} 					