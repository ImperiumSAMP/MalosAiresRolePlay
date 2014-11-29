#if defined _isamp_tazer_included
	#endinput
#endif
#define _isamp_tazer_included

//=============================SISTEMA DE TAZER=================================

//================================DEFINES=======================================

#define TAZER_TIME              10000
#define TAZER_MAX_DISTANCE      16.0

#define TAZER_NONE              0
#define TAZER_EQUIPPED          1
#define TAZER_USED              2
#define TAZER_EMPTY             3

//===============================VARIABLES======================================

new tazerAmmo[MAX_PLAYERS],
	tazerStatus[MAX_PLAYERS],
	tazerInUse[MAX_PLAYERS];
	
resetTazer(playerid)
{
	tazerInUse[playerid] = 0;
	tazerStatus[playerid] = TAZER_NONE;
	tazerAmmo[playerid] = 0;
}

//================================FUNCIONES=====================================

forward checkTazer(playerid, issuerid, Float:amount, weaponid);
public checkTazer(playerid, issuerid, Float:amount, weaponid)
{	
	if(weaponid == WEAPON_SILENCED && tazerInUse[issuerid])
	{
		if(!IsPlayerInAnyVehicle(issuerid))
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(ProxDetectorS(TAZER_MAX_DISTANCE, issuerid, playerid))
				{
					if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
						return SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto está ocupado o actualmente inhabilitado.");
					SendFMessage(playerid, COLOR_YELLOW2, "¡Has sido tazeado por %s!, el efecto dura %d segundos.", GetPlayerNameEx(issuerid), TAZER_TIME / 1000);
					SendFMessage(issuerid, COLOR_YELLOW2, "¡Has tazeado a %s por %d segundos!", GetPlayerNameEx(playerid), TAZER_TIME / 1000);
					TogglePlayerControllable(playerid, false);
					SetPVarInt(playerid, "disabled", DISABLE_TAZER);
					ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
					SetTimerEx("FinishTazerEffect", TAZER_TIME, 0, "i", playerid);
					PlayerPlayerActionMessage(issuerid, playerid, 15.0, "dispara su tazer cargado y le acierta a");
				} else {
					 SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto estaba demasiado lejos.");
				}
			} else {
				SendClientMessage(issuerid, COLOR_YELLOW2, "Debes bajar al sujeto del vehículo antes de tazearlo.");
			}
		} else {
			SendClientMessage(issuerid, COLOR_YELLOW2, "¡No lo puedes usar desde adentro de un vehículo!");
		}
		return 1;
	}
	return 0;
}

forward FinishTazerEffect(playerid);
public FinishTazerEffect(playerid)
{
    if(GetPVarInt(playerid, "disabled") == DISABLE_TAZER)
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del tazer se ha ido.");
		TogglePlayerControllable(playerid, true);
    	ApplyAnimation(playerid, "PED", "getup_front", 4.1, 0, 1, 1, 0, 1, 1);
    	SetPVarInt(playerid, "disabled", DISABLE_NONE);
    }
    return 1;
}

stock isPlayerUsingTazer(playerid)
{
	return tazerInUse[playerid];
}

//================================COMANDOS======================================

CMD:tomartazer(playerid, params[])
{
	if(!isPlayerCopOnDuty(playerid) && !isPlayerSideOnDuty(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en servicio!");
	if(tazerStatus[playerid] == TAZER_NONE)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar equipado con un tazer!");
	if(tazerStatus[playerid] == TAZER_EMPTY)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tu tazer no tiene mas munición, vuelve a la comisaria a recargarlo!");
	if(tazerInUse[playerid])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tienes el tazer en la mano!");
	if(GetHandItem(playerid, HAND_RIGHT) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tienes la mano ocupada!");

    tazerInUse[playerid] = 1;
    
    if(tazerStatus[playerid] == TAZER_EQUIPPED)
   		SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_SILENCED, 10);
	if(tazerStatus[playerid] == TAZER_USED)
	    SetHandItemAndParam(playerid, HAND_RIGHT, WEAPON_SILENCED, tazerAmmo[playerid]);
	    
    SendClientMessage(playerid, COLOR_WHITE, "Has tomado tu tazer. Para guardarlo usa /guardartazer.");
	return 1;
}

CMD:guardartazer(playerid, params[])
{
	if(!isPlayerCopOnDuty(playerid) && !isPlayerSideOnDuty(playerid))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en servicio!");
	if(tazerStatus[playerid] == TAZER_NONE)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar equipado con un tazer!");
	if(!tazerInUse[playerid])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el tazer en la mano!");

    if(GetHandItem(playerid, HAND_RIGHT) != WEAPON_SILENCED) // Si se le acabó el tazer y por quedarse sin balas se borró de la mano
    {
        tazerAmmo[playerid] = 0;
        tazerStatus[playerid] = TAZER_EMPTY;
	}
	else
	{
		new weapon, ammo;
	 	GetPlayerWeaponData(playerid, 2, weapon, ammo); // Silenced se guarda en slot 2 de weapondatas
		if(weapon == WEAPON_SILENCED)
		{
			if(tazerStatus[playerid] != TAZER_EMPTY)
			{
			    tazerAmmo[playerid] = ammo;
			    if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED)
			    	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
			    tazerStatus[playerid] = TAZER_USED;
			}
			if(tazerAmmo[playerid] == 0)
				tazerStatus[playerid] = TAZER_EMPTY;
		}
	}
    tazerInUse[playerid] = 0;
    SendClientMessage(playerid, COLOR_WHITE, "Has guardado tu tazer. Para usarlo nuevamente usa /tomartazer o vé a recargarlo si se te ha acabado.");
	return 1;
}
// inmunidad al anticheat en comandos que te sacan el arma de la mano . Idem si ammo es 0 y esta arriba de un coche
// chekear intentos de edit, si son eventos solitarios ignorar al admin, si se repiten seguidos, avisar, o si son con armas duras
