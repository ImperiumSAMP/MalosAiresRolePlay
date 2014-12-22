#if defined _isamp_saludo_coordinado 
	#endinput
#endif 
#define _isamp_saludo_coordinado

new saluteOffer[MAX_PLAYERS],
	saluteStyle[MAX_PLAYERS];
 
stock PlayerFacePlayer(playerid, targetid)
{
	new Float:Angle;
		
	GetPlayerFacingAngle(playerid, Angle);
	SetPlayerFacingAngle(targetid, Angle + 180);
	return 1;
}

CMD:saludar(playerid, params[])
{
	new targetid,
		style;
	
	if(sscanf(params, "ui", targetid, style))
		return SendClientMessage(playerid, COLOR_GREY, "{FF4600}[Sintaxis]:{C8C8C8} /saludar [ID/Jugador] [Estilo 1-7]");
	if(style > 7 || style < 1)
		return SendClientMessage (playerid, COLOR_YELLOW2, "Solo puedes elegir entre los estilos 1 y 7!");
	if(targetid == playerid || !ProxDetectorS(1.5, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Jugador inválido o se encuentra muy lejos!");

	saluteOffer[targetid] = playerid;
	saluteStyle[targetid] = style;
	SendFMessage(playerid, COLOR_WHITE, "Saludaste a %s, pero debes esperar su respuesta.", GetPlayerNameEx(targetid));
	SendFMessage(targetid, COLOR_WHITE, "%s está intentando coordinar un saludo con vos, usa /saludo aceptar.", GetPlayerNameEx(playerid));
	return 1;
}

CMD:saludo(playerid, params[])
{
	new cmd[32];
		
	if(sscanf(params, "s[32]", cmd))
		return SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /saludo aceptar");

	if(strcmp(cmd, "aceptar") == 0)
	{
	    if(saluteOffer[playerid] == INVALID_PLAYER_ID)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido un saludo.");
		if(saluteOffer[playerid] == playerid || !ProxDetectorS(1.5, playerid, saluteOffer[playerid]))
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Jugador inválido o se encuentra muy lejos!");

		PlayerFacePlayer(playerid, saluteOffer[playerid]);
		switch(saluteStyle[playerid])
		{
			case 1:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 2:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 3:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 4:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 5:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 6:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
			}
			case 7:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
				ApplyAnimation(saluteOffer[playerid], "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
			}
		}
		saluteOffer[playerid] = INVALID_PLAYER_ID;
		saluteStyle[playerid] = 0;
	}
	return 1;
}
