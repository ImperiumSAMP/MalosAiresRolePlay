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
CMD:empezarpaintball(playerid,params[])
{ 
	if(PaintballPlay == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El paintball ya fué iniciado.");
	if(!IsPlayerInRangeOfPoint(playerid, 25.0, POS_PAINTBALL_X, POS_PAINTBALL_Y, POS_PAINTBALL_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes encontrarte en la zona donde se realizan los paintballs.");
	
	PaintballPlay = 1;
	return 1;
}


CMD:comenzarpaintball(playerid, params[])
{
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de empezar el conteo debes iniciar el Paintball y crear los grupos. (/empezarpaintball)");
	if(PaintballStart == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El juego está en proceso, no puedes iniciar un conteo ahora.");
	
    SendClientMessage(playerid, -1, "Has comenzado el juego.");
	foreach(new i : Player) 
	{
		if(GetPVarInt(i, "GrupoPaintball") > 0)
		{
			GameTextForPlayer(i, "YA!!!", 7000, 3);
			PaintballStart = 1;
		}
	}
	return 1;
}

CMD:pbmaxplayers(playerid, params[]) {
	new equipo[4], maxplayers;

	if(sscanf(params, "si", equipo, maxplayers)) {
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /pbmaxplayers [equipo: azul - rojo] [máximo de jugadores]");
	} else if(strcmp(equipo, "azul", true) == 0) {
		BlueTeamMaxPlayers = maxplayers;
		SendFMessage(playerid, COLOR_WHITE, "Configuraste el límite de jugadores del equipo azul a %d.", maxplayers);
	} else if(strcmp(equipo, "rojo", true) == 0) {
		RedTeamMaxPlayers = maxplayers;
		SendFMessage(playerid, COLOR_WHITE, "Configuraste el límite de jugadores del equipo rojo a %d.", maxplayers);
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
		} else { SendClientMessage(playerid, COLOR_WHITE, "¡El equipo azul está lleno! Podés modificar el límite de jugadores con /pbmaxplayers."); }
	} else if(strcmp(equipo, "rojo", true) == 0) {
	    if(RedTeamPlayers < RedTeamMaxPlayers) {
	        SetPVarInt(target, "GrupoPaintball", 1);
	        RedTeamPlayers += 1;
	        SendFMessage(playerid, COLOR_WHITE, "Invitaste a %s al equipo rojo de Paintball.", GetPlayerNameEx(target));
		} else { SendClientMessage(playerid, COLOR_WHITE, "¡El equipo rojo está lleno! Podés modificar el límite de jugadores con /pbmaxplayers."); }
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "Los posibles equipos son rojo y azul.");
	}
	return 1;
}

CMD:resetpaintball(playerid, params[]) 
{
    PaintballPlay = 0,
    PaintballStart = 0,
    BlueTeamPlayers = 0,
	RedTeamPlayers = 0,
    BlueTeamMaxPlayers = 0,
    RedTeamMaxPlayers = 0;
	foreach(new i : Player)	
	{
	    SetPVarInt(i, "GrupoPaintball", 0);
	}
    return 1;
}
	
	
	
	
	
	
	
	
	
	

