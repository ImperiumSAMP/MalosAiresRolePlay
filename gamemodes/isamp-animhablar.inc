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
    SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "Animación al hablar: {C8C8C8}ACTIVADA");
}
else
{
    TextAnim = 0;
    SendClientMessage (playerid, COLOR_LIGHTYELLOW2, "Animación al hablar: {C8C8C8}DESACTIVADA");
}
return 1;
}


forward EndAnim (playerid);
public EndAnim (playerid)
 {
ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
return 1;
 }

