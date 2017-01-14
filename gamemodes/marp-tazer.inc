#if defined _marp_taser_included
	#endinput
#endif
#define _marp_taser_included

//=============================SISTEMA DE TASER=================================

//================================DEFINES=======================================

#define TASER_TIME              20000
#define TASER_MAX_DISTANCE      15.0

#define TASER_NONE              0
#define TASER_EQUIPPED          1
#define TASER_USED              2
#define TASER_EMPTY             3

#define DISABLE_TASER			500

//================================FUNCIONES=====================================

forward checkTaser(playerid, issuerid, Float:amount, weaponid);
forward FinishTaserEffect(playerid);

public checkTaser(playerid, issuerid, Float:amount, weaponid)
{	
	if(weaponid == WEAPON_SILENCED && GetHandItem(issuerid, HAND_RIGHT) == ITEM_ID_TASER)
	{
		if(!IsPlayerInAnyVehicle(issuerid))
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
				if(ProxDetectorS(TASER_MAX_DISTANCE, issuerid, playerid))
				{
					if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
						return SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto está ocupado o actualmente inhabilitado.");
					SendFMessage(playerid, COLOR_YELLOW2, "¡Has sido taseado por %s!, el efecto dura %d segundos.", GetPlayerNameEx(issuerid), TASER_TIME / 1000);
					SendFMessage(issuerid, COLOR_YELLOW2, "¡Has taseado a %s por %d segundos!", GetPlayerNameEx(playerid), TASER_TIME / 1000);
					TogglePlayerControllable(playerid, false);
					SetPVarInt(playerid, "disabled", DISABLE_TASER);
					ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
					SetTimerEx("FinishTaserEffect", TASER_TIME, 0, "i", playerid);
					PlayerPlayerActionMessage(issuerid, playerid, 15.0, "dispara su taser cargado y le acierta a");
				}
				else
					SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto estaba demasiado lejos.");
			}
			else
				SendClientMessage(issuerid, COLOR_YELLOW2, "Debes bajar al sujeto del vehículo antes de tazearlo.");
		}
		else
			SendClientMessage(issuerid, COLOR_YELLOW2, "¡No lo puedes usar desde adentro de un vehículo!");
		return 1;
	}
	return 0;
}

public FinishTaserEffect(playerid)
{
    if(GetPVarInt(playerid, "disabled") == DISABLE_TASER)
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del taser se ha ido.");
		TogglePlayerControllable(playerid, true);
    	ApplyAnimation(playerid, "PED", "getup_front", 4.1, 0, 1, 1, 0, 1, 1);
    	SetPVarInt(playerid, "disabled", DISABLE_NONE);
    }
    return 1;
}

stock isPlayerUsingTaser(playerid)
{
	if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_TASER)
		return 1;
	else
		return 0;
}