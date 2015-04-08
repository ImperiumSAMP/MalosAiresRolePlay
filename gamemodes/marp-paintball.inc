#if defined _marp_paintball_included
	#endinput
#endif
#define _marp_paintball_included

new PaintballPlay = 0,
    PaintballStart = 0,
	PaintballCountdownStart = 0,
	PaintballCountdownSecs = 11;

CMD:empezarpaintball(playerid,params[])
{ 
    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(PaintballPlay == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El paintball ya fué iniciado.");
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, 2308 ,-1610 ,484))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes encontrarte en la zona donde se realizan los paintballs.");
	
	PaintballPlay = 1;
	return 1;
}

CMD:creargruporojo(playerid, params[])
{
	new player1, player2, player3, player4, player5;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de crear los grupos debes iniciar el Paintball. (/empezarpaintball)");
	if(sscanf(params, "uuuuu", player1, player2, player3, player4, player5))
	   	return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /creargruporojo  [ID/Jugador1] [ID/Jugador2] [ID/Jugador3] [ID/Jugador4] [ID/Jugador5]");
	
	SetPVarInt(player1, "GrupoPaintball", 1);
	SetPVarInt(player2, "GrupoPaintball", 1);
	SetPVarInt(player3, "GrupoPaintball", 1);
	SetPVarInt(player4, "GrupoPaintball", 1);
	SetPVarInt(player5, "GrupoPaintball", 1);
	SendFMessage(playerid, -1, "Haz invitado a %s, %s, %s, %s y %s al grupo rojo de Paintball.", GetPlayerNameEx(player1), GetPlayerNameEx(player2), GetPlayerNameEx(player3), GetPlayerNameEx(player4), GetPlayerNameEx(player5));
	return 1;
}

CMD:creargrupoazul(playerid, params[])
{
	new player1, player2, player3, player4, player5;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de crear los grupos debes iniciar el Paintball. (/empezarpaintball)");
	if(sscanf(params, "uuuuu", player1, player2, player3, player4, player5))
	   	return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /creargrupoazul  [ID/Jugador1] [ID/Jugador2] [ID/Jugador3] [ID/Jugador4] [ID/Jugador5]");
	
	SetPVarInt(player1, "GrupoPaintball", 2);
	SetPVarInt(player2, "GrupoPaintball", 2);
	SetPVarInt(player3, "GrupoPaintball", 2);
	SetPVarInt(player4, "GrupoPaintball", 2);
	SetPVarInt(player5, "GrupoPaintball", 2);
	SendFMessage(playerid, -1, "Haz invitado a %s, %s, %s, %s y %s al grupo azul de Paintball.", GetPlayerNameEx(player1), GetPlayerNameEx(player2), GetPlayerNameEx(player3), GetPlayerNameEx(player4), GetPlayerNameEx(player5));
	return 1;
}

CMD:creargrupoverde(playerid, params[])
{
	new player1, player2, player3, player4, player5;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de crear los grupos debes iniciar el Paintball. (/empezarpaintball)");
	if(sscanf(params, "uuuuu", player1, player2, player3, player4, player5))
	   	return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /creargrupoverde  [ID/Jugador1] [ID/Jugador2] [ID/Jugador3] [ID/Jugador4] [ID/Jugador5]");
	
	SetPVarInt(player1, "GrupoPaintball", 3);
	SetPVarInt(player2, "GrupoPaintball", 3);
	SetPVarInt(player3, "GrupoPaintball", 3);
	SetPVarInt(player4, "GrupoPaintball", 3);
	SetPVarInt(player5, "GrupoPaintball", 3);
	SendFMessage(playerid, -1, "Haz invitado a %s, %s, %s, %s y %s al grupo verde de Paintball.", GetPlayerNameEx(player1), GetPlayerNameEx(player2), GetPlayerNameEx(player3), GetPlayerNameEx(player4), GetPlayerNameEx(player5));
	return 1;
}

forward PaintballCountdown(playerid);
public PaintballCountdown(playerid)
{ 
    PaintballCountdownSecs --;
    if (PaintballCountdownSecs > 0)
	{
 	    new PaintballCountdownString[10];
	    format(PaintballCountdownString, sizeof(PaintballCountdownString), "%d", PaintballCountdownSecs);
        GameTextForPlayer(playerid, PaintballCountdownString, 500, 3);    
	}
	if(PaintballCountdownSecs == 0)
	{
		GameTextForPlayer(playerid, "YA!!!", 500, 3);
		PaintballCountdownSecs = 11;
		PaintballStart = 1;
		PaintballCountdownStart = 0;
		KillTimer(GetPVarInt(playerid, "TimerPaintball"));
    }     
	return 1;
}
CMD:conteopaintball(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(PaintballPlay != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Antes de empezar el conteo debes iniciar el Paintball y crear los grupos. (/empezarpaintball)");
	if(PaintballCountdownStart == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El conteo ya fué iniciado.");
	if(PaintballStart == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El juego está en proceso, no puedes iniciar un conteo ahora.");
	
    
    SendClientMessage(playerid, -1, "Haz comenzado el conteo del paintbail");
	foreach(new i : Player) 
	{
		if(GetPVarInt(i, "GrupoPaintball") > 0)
		{
            SetPVarInt(i, "TimerPaintball", SetTimerEx("PaintballCountdown", 1000, 1, "i", playerid));
		}
	}
	PaintballCountdownStart = 1;
	return 1;
}





