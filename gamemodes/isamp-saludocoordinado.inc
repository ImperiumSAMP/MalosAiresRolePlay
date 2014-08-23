#if defined _isamp_saludo_coordinado 
#endinput
#endif 
#define _isamp_saludo_coordinado
 
stock PlayerFacePlayer(playerid, targetid)
{
	new
		Float:Angle;
		
	GetPlayerFacingAngle(playerid, Angle);
	SetPlayerFacingAngle(targetid, Angle + 180);
	return 1;
}

CMD:saludar(playerid, params[])
{
	new
		targetid,
		style;
	
	if(sscanf (params, "rd", targetid, style))
		return SendClientMessage (playerid, COLOR_GREY, "{FF4600}[Sintaxis]:{C8C8C8} /saludar [Id/ParteDelNombre] [Estilo 1-7]");
	if(GetDistanceBetweenPlayers (playerid, targetid) > 3.5)
		return SendClientMessage (playerid, COLOR_YELLOW2, "El jugador está demasiado lejos.");
	if(style > 7 || style < 1)
		return SendClientMessage (playerid, COLOR_YELLOW2, "Solo puedes elegir entre los estilos 1 y 7!");
	if(!IsPlayerConnected (targetid))
		return SendClientMessage (playerid, COLOR_YELLOW2, "Jugador inválido o no conectado.");

	SetPVarInt (playerid, "saludando", targetid);
	SetPVarInt(playerid, "style", style);
	SendFMessage (playerid, COLOR_LIGHTYELLOW2, "Saludaste a %s, pero debes esperar su respuesta.", GetPlayerNameEx(targetid));
	SendFMessage (targetid, COLOR_LIGHTYELLOW2, "%s está intentando coordinar un saludo con vos, usa /saludo aceptar.", GetPlayerNameEx (playerid));
	return 1;
}

CMD:saludo(playerid, params[])
{
	new
		count,
		cmd;
		
	if(sscanf(params, "%s", cmd))
		return SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /saludo [comando]");

	if(strcmp(params, "aceptar") == 0)
	{
		foreach(Player, i)
		{
			if(GetPVarInt(i, "saludando") == playerid)
			{
				if(GetDistanceBetweenPlayers (playerid, i) > 1)
				{
					count++;
					SendClientMessage (playerid, COLOR_YELLOW2, "Estas demasiado lejos de quien te saludo, no puedes aceptar.");
				} else
					{
					    count++;
						PlayerFacePlayer(playerid, i);
						switch(GetPVarInt(i, "style"))
						{
							case 1:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 2:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 3:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 4:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 5:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 6:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
							}
							case 7:
							{
								ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
								ApplyAnimation(i, "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
							}
						}
						SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
						SendFMessage(playerid, COLOR_WHITE, "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
						SendFMessage(i, COLOR_WHITE, "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
						DeletePVar(i, "style");
						count = 0;
					}
			}
		}
	}
	if(count == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está intentando saludar o quizás el comando es incorrecto. (/saludo aceptar)");
	return 1;
}
