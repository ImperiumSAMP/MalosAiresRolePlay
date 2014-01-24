#if defined _isamp_tazer_included
	#endinput
#endif
#define _isamp_tazer_included

/* Sistema de tazer */

#define TAZER_TIME              10000
#define TAZER_MAX_DISTANCE      16.0

new TENIAMM[MAX_PLAYERS],   // Sistema de TAZER
	MM[MAX_PLAYERS],
	MMA[MAX_PLAYERS],
	TENIAMMSILENCIADA[MAX_PLAYERS],
	MMSILENCIADA[MAX_PLAYERS],
	MMASILENCIADA[MAX_PLAYERS],
	TENIADEAGLE[MAX_PLAYERS],
	DEAGLE[MAX_PLAYERS],
	DEAGLEA[MAX_PLAYERS],
	TENIATAZER[MAX_PLAYERS],
	TAZER[MAX_PLAYERS],
	TAZERA[MAX_PLAYERS],
	TTAZER[MAX_PLAYERS],
	TAZERENMANO[MAX_PLAYERS];
	
resetTazer(playerid){
	TAZERENMANO[playerid] = 0;
	TTAZER[playerid] = 0;
}

forward checkTazer(playerid,issuerid,Float:amount,weaponid);
public checkTazer(playerid,issuerid,Float:amount,weaponid) {	
	if( weaponid == 23 && TAZERENMANO[issuerid] == 1) 
	{

		if(CopDuty[issuerid] != 1 && SIDEDuty[issuerid] != 1)
			return 1;

		new Float:victimHealth;
		GetPlayerHealthEx(playerid, victimHealth);
		SetPlayerHealthEx(playerid, victimHealth + amount);

		if(!IsPlayerInAnyVehicle(issuerid)) {
			if(!IsPlayerInAnyVehicle(playerid)) {

				if(ProxDetectorS(12.0, issuerid, playerid)){
					if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
						return SendClientMessage(issuerid, COLOR_YELLOW2, "El sujeto está ocupado o actualmente inhabilitado.");

					SendFMessage(playerid, COLOR_YELLOW2, "¡Has sido tazeado por %s!, el efecto dura %d segundos.", GetPlayerNameEx(issuerid), TAZER_TIME / 1000);
					SendFMessage(issuerid, COLOR_YELLOW2, "¡Has tazeado a %s por %d segundos!", GetPlayerNameEx(playerid), TAZER_TIME / 1000);
					TogglePlayerControllable(playerid, 0);
					SetPVarInt(playerid, "disabled", DISABLE_TAZER);
					ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
					SetTimerEx("FinishTazerEffect", 10000, 0, "i", playerid);
					PlayerPlayerActionMessage(issuerid, playerid, 15.0, "ha tazeado a");
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


// SIST TAZER //

forward FinishTazerEffect(playerid);
public FinishTazerEffect(playerid)
{
    if(GetPVarInt(playerid, "disabled") == DISABLE_TAZER) {
	    SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del tazer se ha ido.");
		TogglePlayerControllable(playerid, 1);
    	ApplyAnimation(playerid, "PED", "getup_front", 4.1, 0, 1, 1, 0, 1, 1);
    	DeletePVar(playerid, "disabled");
    }
    return 1;
}

CMD:tomartazer(playerid, params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA) return 1;
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0) {
    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en servicio!");
    	return 1;
	}
	if(TTAZER[playerid] == 0) {
    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar equipado!");
    	return 1;
	}
	if(TTAZER[playerid] == 3 && TENIATAZER[playerid] == 3){
 		SendClientMessage(playerid, COLOR_YELLOW2, "¡Tu tazer no tiene mas munición, vuelve a la comisaria a recargarlo!");
        return 1;
	}
	if(TAZERENMANO[playerid] == 1){
 		SendClientMessage(playerid, COLOR_YELLOW2, "¡Tienes el tazer en la mano!");
    	return 1;
	}

    new sweapon, sammo;
    for (new i=0; i<9; i++)
    {
        GetPlayerWeaponData(playerid, i, sweapon, sammo);
        if(sweapon != 0)
        {
			if(sweapon == 22){
       			TENIAMM[playerid] = 1;
			    MM[playerid] = sweapon;
			    MMA[playerid] = sammo;
			}
			if(sweapon == 23){
       			TENIAMMSILENCIADA[playerid] = 1;
			    MMSILENCIADA[playerid] = sweapon;
			    MMASILENCIADA[playerid] = sammo;
			}
			if(sweapon == 24){
			    TENIADEAGLE[playerid] = 1;
			    DEAGLE[playerid] = sweapon;
			    DEAGLEA[playerid] = sammo;
			}
        }
    }
    RemovePlayerWeapon(playerid, MMSILENCIADA[playerid]);
    TAZERENMANO[playerid] = 1;
    if(TTAZER[playerid] == 1){
 		GivePlayerWeapon(playerid, 23, 10);
	}
	if(TTAZER[playerid] == 2){
 		GivePlayerWeapon(playerid, TAZER[playerid], TAZERA[playerid]);
	}
	return 1;
}

/*

TTAZER[playerid] = 0 //APENAS LOGEAS SIN NADA
TTAZER[playerid] = 1 //AL PONERTE UN EQUIPO
TTAZER[playerid] = 2 //TENIAS UNO GASTASTE BALAS Y TE QUEDAN ALGUNAS
TTAZER[playerid] = 3 //TENIAS UNO GASTATE TODAS LAS BALAS, VOLVE A RECARGAR PUTO

*/

CMD:guardartazer(playerid, params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA) return 1;
    if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0) {
    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en servicio!");
    	return 1;
	}
	if(TTAZER[playerid] == 0) {
    	SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar equipado!");
    	return 1;
	}
	if(TAZERENMANO[playerid] == 0){
 		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el tazer en la mano!");
    	return 1;
	}
	new sweapon, sammo;
    for (new i=0; i<9; i++)
    {
        GetPlayerWeaponData(playerid, i, sweapon, sammo);
        if(sweapon != 0)
        {
			if(sweapon == 23 && TTAZER[playerid] != 3){
			    TENIATAZER[playerid] = 1;
			    TAZER[playerid] = sweapon;
			    TAZERA[playerid] = sammo;
			    RemovePlayerWeapon(playerid, TAZER[playerid]);
			    TTAZER[playerid] = 2;
			}
			if(sweapon == 23 && TAZERA[playerid] == 0) {
                TENIATAZER[playerid] = 3;
				TTAZER[playerid] = 3;
   			}
        }
    }
    TAZERENMANO[playerid] = 0;
	if(TENIAMM[playerid] == 1){
	GivePlayerWeapon(playerid, MM[playerid], MMA[playerid]);
	}
	if(TENIAMMSILENCIADA[playerid] == 1){
	GivePlayerWeapon(playerid, MMSILENCIADA[playerid], MMASILENCIADA[playerid]);
	}
	if(TENIADEAGLE[playerid] == 1){
	GivePlayerWeapon(playerid, DEAGLE[playerid], DEAGLEA[playerid]);
	}
	return 1;
}

