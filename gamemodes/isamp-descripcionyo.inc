#if defined _isamp_descripcion_yo
#endinput
#endif 
#define _isamp_descripcion_yo
new Text3D:DescLabel[MAX_PLAYERS]; 
new GCounter[MAX_PLAYERS] = 0; 
CMD:yo(playerid, params[]){ 
new 
    texto[70], 
    str[120], 
    str2[120], 
    Float:X, 
    Float:Y, 
    Float:Z; 
if(sscanf(params, "s[70]", texto)){ 
    SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /yo [descripción]"); 
    SendClientMessage(playerid, COLOR_GREY, "No olvides que la descripción no puede ser mayor a 65 caracteres."); 
    return 1; 
} 
if(GCounter[playerid] == 0){
if(strlen(texto) > 65) return SendClientMessage(playerid, COLOR_WHITE, "Texto demasiado largo.");
GetPlayerPos(playerid, X, Y, Z); 
format(str, sizeof(str), "%s", texto); 
DescLabel[playerid] = Create3DTextLabel(texto, COLOR_LIGHTRED, X, Y, Z, 25.0, -1); 
Attach3DTextLabelToPlayer(DescLabel[playerid], playerid, 0.0, 0.0, 0.3); 
SendFMessage(playerid, -1, "{C8C8C8}Tu descripción es:{FFFFFF} %s {C8C8C8}usá /yob para eliminarla.", texto); 
GCounter[playerid] = 1; 
} else { 
    Update3DTextLabelText(DescLabel[playerid], COLOR_LIGHTRED, texto); 
    Attach3DTextLabelToPlayer(DescLabel[playerid], playerid, 0.0, 0.0, 0.3); 
    format(str2, sizeof(str2), "{C8C8C8}Tu descripción es:{FFFFFF} %s", texto); 
    SendClientMessage(playerid, -1, str2); 
} 
return 1; 
} 

CMD:yob(playerid, params[]){ 
GCounter[playerid] = 0; 
Delete3DTextLabel(DescLabel[playerid]); 
SendClientMessage(playerid, -1, "Borraste tu descripción actual."); 
return 1; 
}  