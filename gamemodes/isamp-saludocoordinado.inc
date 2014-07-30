#if defined _isamp_saludo_coordinado 
#endinput
#endif 
#define _isamp_saludo_coordinado 
stock PlayerFacePlayer(playerid, targetid) {
new
Float:Angle;
GetPlayerFacingAngle(playerid, Angle);
SetPlayerFacingAngle(targetid, Angle + 180);
return 1;
}
CMD:saludar (playerid, params[])
{
new targetid, str[100], style;
if (sscanf (params, "dd", targetid, style)) return SendClientMessage (playerid, COLOR_GREY, "{FF4600}[Sintaxis]:{C8C8C8} /saludar [Id/ParteDelNombre] [Estilo 1-7]");
{
if (GetDistanceBetweenPlayers (playerid, targetid) > 3.5) return SendClientMessage (playerid, COLOR_GREY, "¡El jugador está demasiado lejos!");
if (targetid == playerid) return SendClientMessage (playerid, -1, "No podés hacerlo con ti mismo.");
if (style > 7 || style < 1) return SendClientMessage (playerid, COLOR_RED, "¡Sólo podés elegir entre estilo 1 y 7!");
if (!IsPlayerConnected (targetid)) {
SendClientMessage (playerid, COLOR_GREY, "Jugador inválido o no conectado.");
return 1;
}
SetPVarInt (playerid, "saludando", targetid);
SetPVarInt(playerid, "style", style);
format (str, sizeof (str), "Saludaste a %s, pero debés esperar su respuesta.", GetPlayerNameEx (targetid));
SendClientMessage (playerid, COLOR_LIGHTRED, str);
format (str, sizeof (str), "%s está intentando coordinar un saludo con vos, usá /aceptar saludo.", GetPlayerNameEx (playerid));
SendClientMessage (targetid, COLOR_LIGHTRED, str);
}
return 1;
}
CMD:aceptarsaludo (playerid, params[])
{
new count, str[100], cmd;
if (sscanf(params, "%s", cmd)) return SendClientMessage (playerid, COLOR_GREY, "{FF4600}[Sintaxis]:{C8C8C8} /aceptar [comando]");
{
if (strcmp (params, "saludo") == 0)
{
foreach (Player, i)
{
if (GetPVarInt(i, "saludando") == playerid)
{
if (GetDistanceBetweenPlayers (playerid, i) > 1)
{
count++;
SendClientMessage (playerid, COLOR_GREY, "Estás demasiado lejos de quien te saludo, no podés aceptar.");
} else {
switch(GetPVarInt(i, "style"))
{
case 1:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation(i, "GANGS", "hndshkaa", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 2:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 3:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkca", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 4:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkcb", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 5:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkda", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 6:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkea", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
case 7:
{
count++;
PlayerFacePlayer(playerid, i);
ApplyAnimation( playerid, "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
ApplyAnimation( i, "GANGS", "hndshkfa", 4.0, 0, 1, 1, 0, 0, 0);
SetPVarInt(i, "saludando", INVALID_PLAYER_ID);
format(str, sizeof(str), "* %s acepta el saludo de %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(i));
ProxDetector(30.0, playerid, str, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
format(str, sizeof(str), "* Aceptaste coordinar un saludo con %s", GetPlayerNameEx(i));
SendClientMessage (playerid, COLOR_GREY, str);
format(str, sizeof(str), "* %s aceptó coordinar un saludo con vos.", GetPlayerNameEx(playerid));
SendClientMessage (i, COLOR_GREY, str);
DeletePVar(i, "style");
}
}
}
}
}
}
}
if(count == 0)
return SendClientMessage(playerid, COLOR_WHITE, "Nadie te está intentando saludar o quizás el comando es incorrecto (/aceptar saludo).");
return 1;
}