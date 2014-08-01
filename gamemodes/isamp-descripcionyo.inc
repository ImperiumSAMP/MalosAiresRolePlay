#if defined _isamp_descripcion_yo
#endinput
#endif 
#define _isamp_descripcion_yo
#define MAX_CARACTERES 80
COMMAND:yo(playerid, params[])
{
new str[128];
new text[81];
if(sscanf(params, "s[90]", text)) return SendClientMessage (playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /yo [Descripción] (Recuerda que solo se permiten 80 caracteres) ");
{
if(text[80] > MAX_CARACTERES)return SendClientMessage (playerid, COLOR_GREY, "Has pasado el limite de caracteres, reduce tu descripción.");
format (str, sizeof (str), "{FF0000}Tu descripción ahora es:{FFFFFF} %s", text);
SendClientMessage (playerid, -1, str);
SetPlayerChatBubble(playerid, text, COLOR_RED, 20.0 , 100000000000 );
format(str, sizeof(str), "{cccccc}Para borrar tu descripción usá /borraryo");
SendClientMessage (playerid, -1, str);
}
return 1;
}
COMMAND:borraryo(playerid, params[])
{
new str[128];
format (str, sizeof (str), "Borraste tu descripción, para volver a poner una usá el comando /yo");
SendClientMessage(playerid, -1, str);
SetPlayerChatBubble(playerid,"", COLOR_RED, 20.0, 1000);
return 1;
}