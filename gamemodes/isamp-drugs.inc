#if defined _isamp_drugs_included
	#endinput
#endif
#define _isamp_drugs_included

//============================SISTEMA DE DROGAS=================================

//================================CONSTANTES====================================

#define ADICTION_UPDATE_TIME    300 // tiempo cada cuanto se actualiza la adiccion, en segundos, 5 min
#define ADICTION_MARIJUANA 		0.10 // cuanto suma una dosis al total porcentual de adiccion a las drogas
#define ADICTION_LSD       		0.25
#define ADICTION_ECSTASY   		0.35
#define ADICTION_COCAINE   		0.50
#define ADICTION_REHAB_PRICE    7000
#define ADICTION_ABSTINENCE_MAX 36000 // tiempo maximo para que te pida consumir con el minimo porcentaje de adiccion, en segundos 10 horas

//==============================DATA STORAGE====================================

new
    /* Sistema de adiccion y drogas */
	RehabOffer[MAX_PLAYERS],
 	DrugOfferType[MAX_PLAYERS],
 	DrugOffer[MAX_PLAYERS],
	DrugOfferAmount[MAX_PLAYERS],
	bool:SellingDrugs[MAX_PLAYERS],
	bool:DrugEffectEcstasy[MAX_PLAYERS],
	bool:DrugEffectLSD[MAX_PLAYERS],
	bool:DrugEffectCocaine[MAX_PLAYERS],
	bool:DrugEffectMarijuana[MAX_PLAYERS];

//===============================FUNCIONES======================================

//======================IMPLEMENTACION DE FUNCIONES=============================

//================================COMANDOS======================================


TIMER:CancelDrugTransfer(playerid, timer) {
	if(timer == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La oferta ha sido cancelada ya que no has respondido en 15 segundos.");
		SendClientMessage(DrugOffer[playerid], COLOR_LIGHTBLUE, "La oferta ha sido cancelada ya que el sujeto no ha respondido en 15 segundos.");
	}
	SellingDrugs[DrugOffer[playerid]] = false;
	DrugOffer[playerid] = INVALID_PLAYER_ID;
	DrugOfferType[playerid] = 0;
	DrugOfferAmount[playerid] = 0;
	return 1;
}

CMD:dardroga(playerid, params[])
{

	new string[128], targetid, type[32], amount;

	if(sscanf(params, "usd", targetid, type, amount))
	{
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dardroga [ID/Jugador] [tipo] [cantidad]");
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
	}
	if(SellingDrugs[playerid] == true)
	     return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras ofreciendo droga a otro sujeto, aguarda 15 segundos a que termine el intercambio.");
	if(targetid == INVALID_PLAYER_ID || targetid == playerid || !IsPlayerConnected(targetid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(GetDistanceBetweenPlayers(playerid, targetid) > 4.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La persona se encuentra demasiado lejos.");
	if(DrugOffer[targetid] != INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "La persona está con otra oferta en este momento.");
	if(amount <= 0 || amount > 5000)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no puede ser menor a 1 o mayor que 5000.");

	if(strcmp(type, "marihuana", true) == 0)
	{
 		if(PlayerInfo[playerid][pMarijuana] < amount)
   			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");
      	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido %d gramos de marihuana a %s. La oferta termina en 15 segundos.", amount, GetPlayerNameEx(targetid));
		format(string, sizeof(string), "%s quiere darte %d gramos de marihuana. Escribe '/aceptar droga' para aceptar. La oferta termina en 15 segundos.",GetPlayerNameEx(playerid), amount);
		DrugOfferType[targetid] = 1;
  	} else
		if(strcmp(type, "lsd", true) == 0)
		{
	       	if(PlayerInfo[playerid][pLSD] < amount)
	           	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");
	        SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido %d gramos de LSD a %s. La oferta termina en 15 segundos.", amount, GetPlayerNameEx(targetid));
        	format(string, sizeof(string), "%s quiere darte %d dosis de LSD. Escribe '/aceptar droga' para aceptar. La oferta termina en 15 segundos.",GetPlayerNameEx(playerid), amount);
			DrugOfferType[targetid] = 2;
	    } else
			if(strcmp(type, "extasis", true) == 0)
			{
	       		if(PlayerInfo[playerid][pEcstasy] < amount)
	           		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");
	       		SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido %d pastillas de éxtasis a %s. La oferta termina en 15 segundos.", amount, GetPlayerNameEx(targetid));
	    		format(string, sizeof(string), "%s quiere darte %d pastillas de éxtasis. Escribe '/aceptar droga' para aceptar. La oferta termina en 15 segundos.",GetPlayerNameEx(playerid), amount);
				DrugOfferType[targetid] = 3;
	    	} else
				if(strcmp(type, "cocaina", true) == 0)
				{
	       			if(PlayerInfo[playerid][pCocaine] < amount)
	           			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");
					SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido %d gramos de cocaína a %s. La oferta termina en 15 segundos.", amount, GetPlayerNameEx(targetid));
	    			format(string, sizeof(string), "%s quiere darte %d gramos de cocaina. Escribe '/aceptar droga' para aceptar. La oferta termina en 15 segundos.",GetPlayerNameEx(playerid), amount);
					DrugOfferType[targetid] = 4;
	   			 } else
					{
           				SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dardroga [IDJugador/ParteDelNombre] [tipo] [cantidad]");
						return SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
	    			}

   	SetPVarInt(targetid, "CancelDrugTransfer", SetTimerEx("CancelDrugTransfer", 15 * 1000, false, "ii", targetid, 1));
	SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
	DrugOffer[targetid] = playerid;
	DrugOfferAmount[targetid] = amount;
	SellingDrugs[playerid] = true;
	return 1;
}

SetDruggedPlayerGunSkills(playerid)
{
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 998);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 998);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);
}

forward RestartPlayerEffectCocaine(playerid);
public  RestartPlayerEffectCocaine(playerid)
{
    if(DrugEffectCocaine[playerid] == true)
    {
		SetNormalPlayerGunSkills(playerid);
		DrugEffectCocaine[playerid] = false;
		SendClientMessage(playerid, COLOR_YELLOW2, "El efecto de la cocaina se ha ido.");
	}
	return 1;
}

forward RestartPlayerEffectLSD(playerid);
public  RestartPlayerEffectLSD(playerid)
{
	if(DrugEffectLSD[playerid] == true)
	{
		new Float:playerhp;
		GetPlayerHealthEx(playerid, playerhp);
		if(playerhp > 100.0 && playerhp <= 115.0)
		    SetPlayerHealthEx(playerid, 100.0);
	    DrugEffectLSD[playerid] = false;
	    SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del LSD se ha ido.");
	}
	return 1;
}

forward RestartPlayerEffectEcstasy(playerid);
public  RestartPlayerEffectEcstasy(playerid)
{
	if(DrugEffectEcstasy[playerid] == true)
    {
		DrugEffectEcstasy[playerid] = false;
		SendClientMessage(playerid, COLOR_YELLOW2, "El efecto del éxtasis se ha ido.");
	}
	return 1;
}

forward RestartPlayerEffectMarijuana(playerid);
public RestartPlayerEffectMarijuana(playerid)
{
	if(DrugEffectMarijuana[playerid] == true)
    {
		DrugEffectMarijuana[playerid] = false;
		SendClientMessage(playerid, COLOR_YELLOW2, "El efecto de la marihuana se ha ido.");
	}
	return 1;
}

CMD:consumir(playerid, params[]) {
	new type[32];
	new weathers[4] = {234, 22, 401, -234};
	if(sscanf(params, "s[32]", type)) {
	    SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /consumir [tipo de droga]");
	    SendClientMessage(playerid, COLOR_YELLOW2, "Tipo s: marihuana - lsd - extasis - cocaina");
	    SendClientMessage(playerid, COLOR_YELLOW2, "Para ver cuánta droga tienes, utiliza '/bolsillo'.");
	} else if(strcmp(type, "marihuana", true) == 0) {

		if(PlayerInfo[playerid][pMarijuana] < 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes gramos de marihuana!");
		PlayerInfo[playerid][pMarijuana] -= 1;
		SetPlayerWeather(playerid, weathers[random(4)]);
		SetPVarInt(playerid, "drugEffect", 600);
		PlayerCmeMessage(playerid, 15.0, 8000, "fuma algo de marihuana.");
		AddPlayerAdiction(playerid, ADICTION_MARIJUANA);
		if(DrugEffectMarijuana[playerid] == false)
		{
   			DrugEffectMarijuana[playerid] = true;
			SetTimerEx("RestartPlayerEffectMarijuana", 600000, false, "i", playerid);
		}

	} else if(strcmp(type, "lsd", true) == 0) {

		if(PlayerInfo[playerid][pLSD] < 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes dosis de LSD!");
		PlayerInfo[playerid][pLSD] -= 1;
		SetPlayerWeather(playerid, weathers[random(4)]);
		SetPVarInt(playerid, "drugEffect", 600);
		PlayerCmeMessage(playerid, 15.0, 8000, "toma una dosis de LSD.");
		AddPlayerAdiction(playerid, ADICTION_LSD);
        if(DrugEffectLSD[playerid] == false)
        {
			if(PlayerInfo[playerid][pHealth] == 100.0)
			{
		    	SetPlayerHealthEx(playerid, 115.0);
		    	DrugEffectLSD[playerid] = true;
		    	SetTimerEx("RestartPlayerEffectLSD", 600000, false, "i", playerid);
			} else
			    SendClientMessage(playerid, COLOR_YELLOW2, "La droga no ha surtido efecto ya que no estabas en la plenitud de tu salud!");
		}

	} else if(strcmp(type, "extasis", true) == 0) {

		if(PlayerInfo[playerid][pEcstasy] < 1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes pastillas de éxtasis!");
		PlayerInfo[playerid][pEcstasy] -= 1;
		SetPlayerWeather(playerid, weathers[random(4)]);
		SetPVarInt(playerid, "drugEffect", 600);
		PlayerCmeMessage(playerid, 15.0, 8000, "toma una pastilla de éxtasis.");
		AddPlayerAdiction(playerid, ADICTION_ECSTASY);
		if(DrugEffectEcstasy[playerid] == false)
		{
   			DrugEffectEcstasy[playerid] = true;
			SetTimerEx("RestartPlayerEffectEcstasy", 600000, false, "i", playerid);
		}

	} else if(strcmp(type, "cocaina", true) == 0) {

		if(PlayerInfo[playerid][pCocaine] < 1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes gramos de cocaína!");
		PlayerInfo[playerid][pCocaine] -= 1;
		SetPlayerWeather(playerid, weathers[random(4)]);
		SetPVarInt(playerid, "drugEffect", 600);
		PlayerCmeMessage(playerid, 15.0, 8000, "aspira algo de cocaína mediante un tubo de papel.");
		AddPlayerAdiction(playerid, ADICTION_COCAINE);
		if(DrugEffectCocaine[playerid] == false)
		{
			SetDruggedPlayerGunSkills(playerid);
			DrugEffectCocaine[playerid] = true;
			SetTimerEx("RestartPlayerEffectCocaine",600000, false, "i", playerid);
		}

	}
	return 1;
}
