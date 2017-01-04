#if defined _marp_wounds
	#endinput
#endif
#define _marp_wounds

/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||   		     Sistema de heridas   				  ||||||||||||||
|||||||||||||           			2016              			  ||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// Bodyparts
#define BODY_PART_TORSO         3
#define BODY_PART_GROIN         4
#define BODY_PART_LEFT_ARM      5
#define BODY_PART_RIGHT_ARM     6
#define BODY_PART_LEFT_LEG      7
#define BODY_PART_RIGHT_LEG     8
#define BODY_PART_HEAD          9

new TakeLegShot[MAX_PLAYERS];

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	new Float:armour;

    GetPlayerArmour(playerid, armour);

    if(issuerid != INVALID_PLAYER_ID)
	{
		//==========================SPRAY NO SACA VIDA==========================

 		if(weaponid == WEAPON_SPRAYCAN)
            return 1;

	    //===============================TAZER==================================

		if(checkTazer(playerid, issuerid, amount, weaponid))
		    return 1;

		//==============================HEADSHOT================================

		/*if(bodypart == BODY_PART_HEAD && TakeHeadShot[playerid] == 0 && isWeaponForHeadshot(weaponid))
		{
			SendFMessage(playerid, COLOR_WHITE, "Has recibido un disparo en la cabeza y entras en estado de agonia. Dicho disparo lo realizo %s", GetPlayerNameEx(issuerid));
		    SetPlayerHealthEx(playerid, 24);
            TakeHeadShot[playerid] = 1;
            return 1;
		}*/

		//=========================DISPARO EN PIERNAS===========================

		if(bodypart == BODY_PART_LEFT_LEG || bodypart == BODY_PART_RIGHT_LEG && TakeLegShot[playerid] == 0)
		{
            SendFMessage(playerid, COLOR_WHITE, "Has recibido un disparo en una de tus piernas al intentar correr te caeras. Dicho disparo lo realizo %s", GetPlayerNameEx(issuerid));
			TakeLegShot[playerid] = 1;
   			return 1;
		}
		//==========================HERIDAS DE BALA=============================

		if(amount > 4.0)
			CheckDamageWound(playerid, weaponid, bodypart, Float:armour);

		//========================EFECTOS DE LA DROGA===========================

		if(weaponid == 0)
		{
		    amount = amount/2; // Bajamos el daño base por puño para hacer mas duraderas las peleas y para darle utilidad a las armas melee.

		    if(DrugEffectEcstasy[issuerid] == false || DrugEffectMarijuana[playerid] == false)  // Si no tienen los 2 la droga contraria
		    {
			    if(DrugEffectEcstasy[issuerid] == true)
			    {
			    	amount = (amount / 10) * 17; // subimos 70 porciento el daño a trompadas que inflige si esta drogado con LSD
	    			if(armour > 0)
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)) );
					else
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
					return 1;
				}
				if(DrugEffectMarijuana[playerid] == true)
				{
	                amount = (amount / 2); // reducimos 50 porciento el daño a trompadas que recibe si esta drogado con marihuana
					if(armour > 0)
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)));
					else
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
					return 1;
				}
			}
		}
	}

	if(armour > 0.0)
	{
	    if(bodypart == BODY_PART_LEFT_ARM || bodypart == BODY_PART_RIGHT_ARM || bodypart == BODY_PART_LEFT_LEG || bodypart == BODY_PART_RIGHT_LEG)
            SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
		else
			SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)));
	}
	else
 		SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);

    return 1;
}

/*stock isWeaponForHeadshot(weaponid)
{
	if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_SILENCED || weaponid == WEAPON_DEAGLE ||
		weaponid == WEAPON_SHOTGUN ||weaponid == WEAPON_UZI || weaponid == WEAPON_MP5 ||
		weaponid == WEAPON_AK47 || weaponid == WEAPON_M4 || weaponid == WEAPON_TEC9 ||
		weaponid == WEAPON_RIFLE || weaponid == WEAPON_SNIPER )
	    return 1;

	return 0;
}*/

stock AccurateShot(playerid)
{
	new weathers[4] = {234, 22, 401, -234};
	SetPlayerWeather(playerid, weathers[random(4)]);
    SetPlayerDrunkLevel (playerid, 10500);
    GameTextForPlayer(playerid, "Te dieron un disparo certero", 5000, 1);
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        ApplyAnimation(playerid, "SWEET", "SWEET_INJUREDLOOP", 4.0, 0, 0, 1, 0, 0);
    SetTimerEx("RecoverLastShot", 5000, false, "i", playerid);
    return 1;
}

stock CrossArmour(playerid)
{
	new weathers[4] = {234, 22, 401, -234};
	SetPlayerWeather(playerid, weathers[random(4)]);
	SetPlayerDrunkLevel (playerid, 10500);
	GameTextForPlayer(playerid, "Un disparo te ha atravesado el chaleco", 5000, 1);
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			ApplyAnimation(playerid, "SWEET", "SWEET_INJUREDLOOP", 4.0, 0, 0, 1, 0, 0);
	SetTimerEx("RecoverLastShot", 5000, false, "i", playerid);
	return 1;
}

public RecoverLastShot(playerid)
{
	SyncPlayerTimeAndWeather(playerid);
	SetPlayerDrunkLevel(playerid, 0);
	return 1;
}

stock CheckDamageWound(playerid, weaponid, bodypart, Float: armour)
{
	new wepProbability = 0,
	    bodyProbability = 0,
	    option = random(100);

	switch(weaponid)
	{
	    case WEAPON_DEAGLE: wepProbability = 10;
	    case WEAPON_SHOTGUN: wepProbability = 15;
	    case WEAPON_UZI: wepProbability = 5;
 	    case WEAPON_MP5: wepProbability = 8;
	    case WEAPON_AK47: wepProbability = 10;
	    case WEAPON_M4: wepProbability = 10;
	    case WEAPON_TEC9: wepProbability = 8;
	    case WEAPON_RIFLE: wepProbability = 15;
	    case WEAPON_SNIPER: wepProbability = 20;
	    default: return 0;
	}

	switch(bodypart)
	{
	    case BODY_PART_TORSO: bodyProbability = 29;
	    case BODY_PART_LEFT_ARM: bodyProbability = 14;
	    case BODY_PART_RIGHT_ARM: bodyProbability = 14;
	    case BODY_PART_LEFT_LEG: bodyProbability = 24;
	    case BODY_PART_RIGHT_LEG: bodyProbability = 24;
	    default: return 0;
	}

	if((bodypart == BODY_PART_TORSO) && armour > 0.0)
	{
	    if(option <= wepProbability)
	        CrossArmour(playerid);
	}
	else
	{
	    if(option <= wepProbability + bodyProbability)
	        AccurateShot(playerid);
	}
	return 1;
}
