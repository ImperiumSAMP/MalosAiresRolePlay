#if defined _isamp_descripcion_yo
#endinput
#endif 
#define _isamp_descripcion_yo

new
	Text3D:DescLabel[MAX_PLAYERS],
	GCounter[MAX_PLAYERS] = 0,
	textodescripcion[70][MAX_PLAYERS];
	
CMD:yo(playerid, params[])
{ 
	new
	    str[120],
	    Float:X,
	    Float:Y,
	    Float:Z;
	    
	if(sscanf(params, "s[70]", textodescripcion[playerid]))
	     return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /yo [descripción]. La descripción no puede ser mayor a 65 caracteres.");

	if(GCounter[playerid] == 1)
	{
		SendFMessage(playerid, COLOR_WHITE , "Tu descripción actual es: %s", textodescripcion[playerid]);
    	return 1;
	}
	if(GCounter[playerid] == 0)
	{
		if(strlen(textodescripcion[playerid]) > 65)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Texto demasiado largo.");
			
		GetPlayerPos(playerid, X, Y, Z);
		format(str, sizeof(str), "%s", textodescripcion[playerid]);
		DescLabel[playerid] = Create3DTextLabel(textodescripcion[playerid], COLOR_RED, X, Y, Z, 10, -1);
		Attach3DTextLabelToPlayer(DescLabel[playerid], playerid, 0.0, 0.0, 0.3);
		SendFMessage(playerid, COLOR_WHITE, "Tu descripción es: %s .Usa /yob para eliminarla.", textodescripcion[playerid]);
		GCounter[playerid] = 1;
	} else {
		Update3DTextLabelText(DescLabel[playerid], COLOR_RED, textodescripcion[playerid]);
		Attach3DTextLabelToPlayer(DescLabel[playerid], playerid, 0.0, 0.0, 0.3);
		SendFMessage(playerid, COLOR_WHITE, "Tu descripción es: %s", textodescripcion[playerid]);
	}
	return 1;
} 

CMD:yob(playerid, params[])
{
	if(GCounter[playerid] != 0)
	{
		 GCounter[playerid] = 0;
		 Delete3DTextLabel(DescLabel[playerid]);
		 SendClientMessage(playerid, COLOR_WHITE, "Borraste tu descripción actual.");
	} else {
		SendClientMessage(playerid, -1, "No tenés ninguna descripción actualmente");
	}
	return 1;
}
