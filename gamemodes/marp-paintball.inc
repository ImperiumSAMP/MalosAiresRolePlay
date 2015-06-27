#if defined _marp_paintball_included
	#endinput
#endif
#define _marp_paintball_included

// DEFINES
#define POS_PAINTBALL_X     	142 
#define POS_PAINTBALL_Y     	2501 
#define POS_PAINTBALL_Z     	16

#define POS_DISQUALIFIED_X  	2575.6660
#define POS_DISQUALIFIED_Y  	2834.5100
#define POS_DISQUALIFIED_Z  	19.9922

new PaintballPlay = 0,
    PaintballStart = 0,
    BlueTeamPlayers = 0,
	RedTeamPlayers = 0,
    BlueTeamMaxPlayers = 0,
    RedTeamMaxPlayers = 0;


// COMANDOS
CMD:pbcrear(playerid,params[])
{ 
	if(PaintballPlay == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya hay un evento de paintball en curso.");
	if(!IsPlayerInRangeOfPoint(playerid, 25.0, POS_PAINTBALL_X, POS_PAINTBALL_Y, POS_PAINTBALL_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes encontrarte en la zona donde se realizan los paintballs.");
	
	PaintballPlay = 1;
	return 1;
}


CMD:pbcomenzar(playerid, params[])
{
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de comenzar el juego debes crear el Paintball y configurar los equipos.");
	if(PaintballStart == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El juego est· en proceso, no puedes volver a iniciarlo ahora. (Usa /pbreset para terminarlo/reiniciarlo)");
	
    SendClientMessage(playerid, -1, "Has comenzado el juego.");
	foreach(new i : Player) 
	{
		if(GetPVarInt(i, "GrupoPaintball") > 0)
		{
			GameTextForPlayer(i, "YA!!!", 7000, 3);
			PaintballStart = 1;
			GivePlayerGun(i, 23, 100);
			if(GetPVarInt(i, "GrupoPaintball") == 1) {
			    SetPlayerSkin(i, 16); }
			if(GetPVarInt(i, "GrupoPaintball") == 2) {
			    SetPlayerSkin(i, 260); }
		}
	}
	return 1;
}

CMD:pbmaxplayers(playerid, params[]) {
	new equipo[4], maxplayers;

	if(sscanf(params, "si", equipo, maxplayers)) {
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /pbmaxplayers [equipo: azul - rojo] [m√°ximo de jugadores]");
	} else if(strcmp(equipo, "azul", true) == 0) {
		BlueTeamMaxPlayers = maxplayers;
		SendFMessage(playerid, COLOR_WHITE, "Configuraste el l√≠mite de jugadores del equipo azul a %d.", maxplayers);
	} else if(strcmp(equipo, "rojo", true) == 0) {
		RedTeamMaxPlayers = maxplayers;
		SendFMessage(playerid, COLOR_WHITE, "Configuraste el l√≠mite de jugadores del equipo rojo a %d.", maxplayers);
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "Los posibles equipos son rojo y azul.");
	}
	return 1;
}

CMD:pbinvitar(playerid, params[]) {
	new equipo[4], target;

	if(sscanf(params, "su", equipo, target)) {
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /pbinvitar [equipo: azul - rojo] [ID/Nombre del jugador a invitar]");
	} else if(strcmp(equipo, "azul", true) == 0) {
	    if(BlueTeamPlayers < BlueTeamMaxPlayers) {
	        SetPVarInt(target, "GrupoPaintball", 2);
	        BlueTeamPlayers += 1;
	        SendFMessage(playerid, COLOR_WHITE, "Invitaste a %s al equipo azul de Paintball.", GetPlayerNameEx(target));
			SendFMessage(target, COLOR_WHITE, "El administrador %s te agreg√≥ al equipo azul de Paintball.", GetPlayerNameEx(playerid));
		} else { SendClientMessage(playerid, COLOR_WHITE, "¬°El equipo azul est√° lleno! Pod√©s modificar el l√≠mite de jugadores con /pbmaxplayers."); }
	} else if(strcmp(equipo, "rojo", true) == 0) {
	    if(RedTeamPlayers < RedTeamMaxPlayers) {
	        SetPVarInt(target, "GrupoPaintball", 1);
	        RedTeamPlayers += 1;
	        SendFMessage(playerid, COLOR_WHITE, "Invitaste a %s al equipo rojo de Paintball.", GetPlayerNameEx(target));
			SendFMessage(target, COLOR_WHITE, "El administrador %s te agreg√≥ al equipo rojo de Paintball.", GetPlayerNameEx(playerid));
		} else { SendClientMessage(playerid, COLOR_WHITE, "¬°El equipo rojo est√° lleno! Pod√©s modificar el l√≠mite de jugadores con /pbmaxplayers."); }
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "Los posibles equipos son rojo y azul.");
	}
	return 1;
}

CMD:pbreset(playerid, params[])
{
    PaintballPlay = 0,
    PaintballStart = 0,
    BlueTeamPlayers = 0,
	RedTeamPlayers = 0,
    BlueTeamMaxPlayers = 0,
    RedTeamMaxPlayers = 0;
	foreach(new i : Player)	
	{
		if(GetPVarInt(i, "GrupoPaintball") != 0)
		{
	    	SetPVarInt(i, "GrupoPaintball", 0);
			SetHandItemAndParam(i, HAND_RIGHT, 0, 0);
			PhoneHand[i] = 0;
		}
	}
    return 1;
}

CMD:pbayuda(playerid, params[])
{
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[LVL 20]{C8C8C8} /pbcrear - /pbmaxplayers - /pbinvitar - /pbcomenzar - /pbinfo - /pbplayers - /pbreset");
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Para iniciar un evento de Paintball deber·s, por empezar, crearlo con el comando /pbcrear");
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Una vez creado el evento, configura la cantidad m·xima de jugadores por equipo e invita a los usuarios.");
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Para comenzar con el evento, usa el comando /pbcomenzar. El evento permanecer· activo hasta que lo termines con /pbreset.");
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Para informaciÛn detallada sobre el evento creado usa los comandos /pbinfo y /pbplayers.");
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Ante cualquier problema con el sistema, reinicia el paintball con /pbreset y vuelve a crearlo.");
	return 1;
}

CMD:pbinfo(playerid, params[])
{
	
	if(PaintballPlay == 0)
	    return SendClientMessage(playerid, COLOR_WHITE, "No hay un paintball creado.");

	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}---{C8C8C8} InformaciÛn del Paintball {878EE7}---");
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}LÌmite de jugadores equipo {0004FF}azul{878EE7}: {C8C8C8} %d", BlueTeamMaxPlayers);
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}LÌmite de jugadores equipo {FF0000}rojo{878EE7}: {C8C8C8} %d", RedTeamMaxPlayers);
	if(PaintballStart == 0) {
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}Evento iniciado: {C8C8C8} No."); }
	if(PaintballStart == 1) {
	SendClientMessage(playerid, COLOR_WHITE, "{878EE7}Evento iniciado: {C8C8C8} SÌ."); }
	return 1;
}

CMD:pbplayers(playerid, params[])
{
	new string[128], count = 0;

	if(PaintballPlay == 0)
		return SendClientMessage(playerid, COLOR_WHITE, "No hay un paintball creado.");

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "{878EE7}[Paintball] {C8C8C8}Lista de jugadores equipo {FF0000}rojo{C8C8C8}:");
	foreach(new i : Player)
	{
	    if(GetPVarInt(i, "GrupoPaintball") == 1)
		{
			format(string, sizeof(string), "%s", GetPlayerNameEx(i));
			SendClientMessage(playerid, COLOR_WHITE, string);
			count++;
		}
	}
	if(count == 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, "No hay ning˙n jugador en el equipo rojo.");
	}
	
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "{878EE7}[Paintball] {C8C8C8}Lista de jugadores equipo {0004FF}azul{C8C8C8}:");
	foreach(new i : Player)
	{
	    if(GetPVarInt(i, "GrupoPaintball") == 2)
		{
			format(string, sizeof(string), "%s", GetPlayerNameEx(i));
			SendClientMessage(playerid, COLOR_WHITE, string);
			count++;
		}
	}
	if(count == 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, "No hay ning˙n jugador en el equipo azul.");
	}
	return 1;
}
	
	
	
	
	
	
	
	
	

