#if defined _isamp_anim_hablar
#endinput
#endif 
#define _isamp_anim_hablar

new
	bool:TextAnim[MAX_PLAYERS] = false; //para animacion al hablar
	
CMD:animhablar (playerid, params[])
{
	if (!TextAnim[playerid])
	{
 		TextAnim[playerid] = true;
 		SendClientMessage (playerid, COLOR_WHITE, "Animación al hablar: {FF4600}ACTIVADA{C8C8C8}");
	}
	else {
 		TextAnim[playerid] = false;
 		SendClientMessage (playerid, COLOR_WHITE, "Animación al hablar: {FF4600}DESACTIVADA{C8C8C8}");
	}
	return 1;
}

forward EndAnim (playerid);
public EndAnim (playerid)
{
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

