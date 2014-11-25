#if defined _isamp_gim_sistem
	#endinput
#endif
#define _isamp_gim_sistem
//=================================DEFINES======================================

#define REPE_BARRA          30
#define REPE_PESAS	        35
#define REPE_VUELTAS        20


//================================VARIABLES=====================================

new Exercising[MAX_PLAYERS],
    FinishExercisingDay[MAX_PLAYERS],
	ExercisingPesas[MAX_PLAYERS],
	ExercisingBarras[MAX_PLAYERS],
	ExercisingTrote[MAX_PLAYERS],
	GimSkin[MAX_PLAYERS],
	DoPesas[MAX_PLAYERS],
	ReloadPesas[MAX_PLAYERS],
	CountRepePesas[MAX_PLAYERS];
	
//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock ResetGimStatics(playerid)
{
    Exercising[playerid] = 0;
	ExercisingPesas[playerid] = 0;
	ExercisingBarras[playerid] = 0;
	ExercisingTrote[playerid] = 0;
	GimSkin[playerid] = 0;
	DoPesas[playerid] = 0;
	ReloadPesas[playerid] = 0;
	CountRepePesas[playerid] = 0;
	return 1;
}


CMD:entrenar(playerid, params[])
{
    new entrenamiento; 
	    
    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 756.2304, 5.4078, 1000.6985))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el GIM para usar este comando.");
	
    if(FinishExercisingDay[playerid] == 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya haz entrenado suficiente por hoy.");
		
	if(Exercising[playerid]== 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras entrenando, si quieres dejar de entrenar usá /terminarentrenamiento.");
		
	if(sscanf(params,"i",entrenamiento))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /entrenar [1-3]. 1:Pesas 2:Barra 3:Trote continuo");
		
	switch(entrenamiento)
	{
	    case 1:
		{
	        Exercising[playerid] = 1;
			ExercisingPesas[playerid] = 1;
	        PlayerActionMessage(playerid, 15.0, "toma la ropa deportiva del stand y se la pone para empezar a realizar pesas");
	        GimSkin[playerid] = GetPlayerSkin(playerid);
	        SetPlayerSkin(playerid, 292);
			SendClientMessage(playerid, -1, "Dirijete al sector de pesas y pon el comando: /realizarpesas");
	    }
		case 2:
		{
		    Exercising[playerid] = 1;
			ExercisingBarras[playerid] = 1;
	        PlayerActionMessage(playerid, 15.0, "toma la ropa deportiva del stand y se la pone para empezar a realizar barras");
	        GimSkin[playerid] = GetPlayerSkin(playerid);
	        SetPlayerSkin(playerid, 96);
			SendClientMessage(playerid, -1, "Dirijete al sector de pesas y pon el comando: /realizarbarra");
		}
		case 3:
		{  
		    Exercising[playerid] = 1;
			ExercisingTrote[playerid] = 1;
	        PlayerActionMessage(playerid, 15.0, "toma la ropa deportiva del stand y se la pone para empezar a trotar por el gimnasio");
	        GimSkin[playerid] = GetPlayerSkin(playerid);
	        SetPlayerSkin(playerid, 96);
			SendClientMessage(playerid, -1, "Preparate y cuando estes listo pon /comenzartrote para empezar a correr");
		}
	}
    return 1;
}

CMD:realizarpesas(playerid, params[])
{	
    new freehand;
    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 772.8693, 5.6093, 1000.7802))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la zona de pesas.");
	if(ExercisingPesas[playerid] != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ir a la zona de casilleros y cambiarte, luego puedes venir aquí.");
	
	PlayerActionMessage(playerid, 15.0, "toma unas pesas del suelo y comienza a hacer ejercicio.");
	freehand = SearchFreeHand(playerid);
	if(freehand == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar el item.");
	SetPlayerAttachedObject(playerid, INDEX_ID_HAND_RIGHT, 2916, BONE_ID_RIGHTHAND, 0.154, 0.028, -0.049, 0.0, -97.3, -156.3, 1.0, 1.0, 1.0);
	DoPesas[playerid]= 1;
	return 1;
}

CMD:terminarentrenamiento(playerid,params[])
{
    SendClientMessage(playerid, COLOR_GREY, "Haz terminado tu entrenamiento por el dia de hoy.");
	FinishExercisingDay[playerid] = 1;
	ResetGimStatics(playerid);
}
	
	
	
	
		
		
		
		
	/* notas: falta el rango de donde se puedan poner todos los comandos, la idea seria poner uno de cada uno, faltan agregar varios if, setearr el objeto en la mano, recordar las anim como iban cada una y apretar con la letra up y down que estan en
	la wiki donde te dice q letra es y varias cosas, mañana lo sigo */  
		
		
		
		
		
		
		
		
		