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

new TakeLegShot[MAX_PLAYERS];
new TakeHeadShot[MAX_PLAYERS];

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	return OnPlayerTakeDamage(damagedid, playerid, amount, weaponid, bodypart);
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	new Float:armour;
	
	GetPlayerArmour(playerid, armour);

    if(issuerid != INVALID_PLAYER_ID)
	{
		//==========================SPRAY NO SACA VIDA==========================
		
 		if(weaponid == WEAPON_SPRAYCAN || weaponid == WEAPON_FIREEXTINGUISHER)
            return 1;

	    //===============================TAZER==================================

		if(checkTaser(playerid, issuerid, amount, weaponid))
		    return 1;

		//==============================HEADSHOT================================

		if(bodypart == BODY_PART_HEAD && TakeHeadShot[playerid] == 0 && isWeaponForHeadshot(weaponid) && DistanceForHeadshot(playerid, issuerid, weaponid))
		{
			SendFMessage(playerid, COLOR_WHITE, "Has recibido un disparo en la cabeza y entras en estado de agonia. Dicho disparo lo realizo %s", GetPlayerNameEx(issuerid));
		    SetPlayerHealthEx(playerid, 24);
            TakeHeadShot[playerid] = 1;
            return 1;
		}

		//=========================DISPARO EN PIERNAS===========================

		if((bodypart == BODY_PART_LEFT_LEG || bodypart == BODY_PART_RIGHT_LEG) && TakeLegShot[playerid] == 0)
		{
            SendFMessage(playerid, COLOR_WHITE, "Has recibido un disparo en una de tus piernas al intentar correr te caeras. Dicho disparo lo realizo %s", GetPlayerNameEx(issuerid));
			TakeLegShot[playerid] = 1;
   			return 1;
		}
		//==========================HERIDAS DE BALA=============================

		if(amount > 4.0)
			CheckDamageWound(playerid, weaponid, bodypart, Float:armour);
		
		if(armour > 0.0)
		{
			if(bodypart == BODY_PART_LEFT_ARM || bodypart == BODY_PART_RIGHT_ARM || bodypart == BODY_PART_LEFT_LEG || bodypart == BODY_PART_RIGHT_LEG)
				SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
			else
			{
				PlayerInfo[playerid][pArmour] = armour - amount;
				SetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
			}
		}
		else
			SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
	}
    return 1;
}

stock DistanceForHeadshot(playerid, issuerid, weaponid)
{
	switch(weaponid)
	{
		case WEAPON_COLT45: if(GetDistanceBetweenPlayers(playerid, issuerid) < 15.0) return 1;
		case WEAPON_SILENCED: if(GetDistanceBetweenPlayers(playerid, issuerid) < 15.0) return 1;
		case WEAPON_DEAGLE: if(GetDistanceBetweenPlayers(playerid, issuerid) < 20.0) return 1;
		case WEAPON_SHOTGUN: if(GetDistanceBetweenPlayers(playerid, issuerid) < 5.0) return 1;
		case WEAPON_UZI: if(GetDistanceBetweenPlayers(playerid, issuerid) < 10.0) return 1;
		case WEAPON_MP5: if(GetDistanceBetweenPlayers(playerid, issuerid) < 20.0) return 1;
		case WEAPON_AK47: if(GetDistanceBetweenPlayers(playerid, issuerid) < 35.0) return 1;
		case WEAPON_M4: if(GetDistanceBetweenPlayers(playerid, issuerid) < 35.0) return 1;
		case WEAPON_TEC9: if(GetDistanceBetweenPlayers(playerid, issuerid) < 10.0) return 1;
		case WEAPON_RIFLE: if(GetDistanceBetweenPlayers(playerid, issuerid) < 35.0) return 1;
		case WEAPON_SNIPER: if(GetDistanceBetweenPlayers(playerid, issuerid) < 100.0) return 1;
	}
	return 0;
}

stock isWeaponForHeadshot(weaponid)
{
	if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_SILENCED || weaponid == WEAPON_DEAGLE ||
		weaponid == WEAPON_SHOTGUN ||weaponid == WEAPON_UZI || weaponid == WEAPON_MP5 ||
		weaponid == WEAPON_AK47 || weaponid == WEAPON_M4 || weaponid == WEAPON_TEC9 ||
		weaponid == WEAPON_RIFLE || weaponid == WEAPON_SNIPER )
	    return 1;

	return 0;
}

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
	new wepProbability ,
	    bodyProbability,
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
