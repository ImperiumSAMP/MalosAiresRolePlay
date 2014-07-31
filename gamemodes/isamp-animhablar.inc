#if defined _isamp_anim_hablar
#endinput
#endif 
#define _isamp_anim_hablar
new TextAnim = 0;//para animacion al hablar
CMD:animhablar (playerid, params[])
{
if (TextAnim == 0)
{
    TextAnim = 1;
    SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "Animación al hablar: {FF4600}ACTIVADA{C8C8C8}");
}
else
{
    TextAnim = 0;
    SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "Animación al hablar: {FF4600}DESACTIVADA{C8C8C8}");
}
return 1;
}


forward EndAnim (playerid);
public EndAnim (playerid)
 {
ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
return 1;
 }

