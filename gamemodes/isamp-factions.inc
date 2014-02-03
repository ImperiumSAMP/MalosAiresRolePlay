#if defined _isamp_factions_included
	#endinput
#endif
#define _isamp_factions_included

//Defines
#define MAX_FACTIONS            20

//====[FACCIONES]===============================================================
#define FAC_NONE                0
#define FAC_PMA                 1 		// Policía Metropolitana.
#define FAC_HOSP                2
#define FAC_FORZ                3
#define FAC_CHIN                4
#define FAC_BERT                5
#define FAC_MAN                 6
#define FAC_MECH                7
#define FAC_RIV                	8
#define FAC_BOCA               	9
#define FAC_SIDE                10


//Enums
enum Factions {
	fName[50],
	fMaterials,
	fDrugs,
	fBank,
	fRank1[35],
	fRank2[35],
	fRank3[35],
	fRank4[35],
	fRank5[35],
	fRank6[35],
	fRank7[35],
	fRank8[35],
	fRank9[35],
	fRank10[35],
	fSkin1,
	fSkin2,
	fSkin3,
	fSkin4,
	fSkin5,
	fSkin6,
	fSkin7,
	fSkin8,
	fSkin9,
	fSkin10,
	fJoinRank,
	fUseSkins,
	fType,//For Government factions etc
	fRankAmount,
	fAllowJob,
	fMissionVeh,
};

new FactionInfo[MAX_FACTIONS][Factions];

new MedDuty[MAX_PLAYERS],
	CopDuty[MAX_PLAYERS],
	CopTrace[MAX_PLAYERS],
	SIDEDuty[MAX_PLAYERS],
	PlayerCuffed[MAX_PLAYERS];

//General functions

stock isPlayerCopOnDuty(playerid){
	return PlayerInfo[playerid][pFaction] == 1 && CopDuty[playerid] == 1;
}


//Admin commands

//[CMD_A7]
//====[FACCIONES]===============================================================
CMD:afacciones(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 20) return 1;

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Comandos de facciones]:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/afexpulsar /aftipo /afnombre /afusaskins /afrangos /afrangoingreso /afdrogas /afdinero /afmats /afskin /afrango /afvehmision");
	return 1;
}

CMD:aftipo(playerid, params[]) {
	new
	    string[128],
	    factionID,
		type;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, type)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aftipo [idfacción] [tipo]");
        SendClientMessage(playerid, COLOR_WHITE, "Tipos: 0 ilegal | 1 gobierno | 2 legal | 3 pandilla");
	} else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fType] = type;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} el tipo de la facción %d ha sido ajustado a %d.", factionID, type);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afrango(playerid, params[]) {
	new
	    string[128],
	    factionID,
		rankID,
		rankName[32];

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dds[32]", factionID, rankID, rankName)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afrango [idfacción] [rango 1-10] [nombre 32 chars]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && rankID >= 1 && rankID <= 10) {
	   	mysql_real_escape_string(rankName, rankName);
	    switch(rankID) {
	        case 1: strmid(FactionInfo[factionID][fRank1], (rankName), 0, strlen((rankName)), 32);
	        case 2: strmid(FactionInfo[factionID][fRank2], (rankName), 0, strlen((rankName)), 32);
	        case 3: strmid(FactionInfo[factionID][fRank3], (rankName), 0, strlen((rankName)), 32);
	        case 4: strmid(FactionInfo[factionID][fRank4], (rankName), 0, strlen((rankName)), 32);
	        case 5: strmid(FactionInfo[factionID][fRank5], (rankName), 0, strlen((rankName)), 32);
	        case 6: strmid(FactionInfo[factionID][fRank6], (rankName), 0, strlen((rankName)), 32);
	        case 7: strmid(FactionInfo[factionID][fRank7], (rankName), 0, strlen((rankName)), 32);
	        case 8: strmid(FactionInfo[factionID][fRank8], (rankName), 0, strlen((rankName)), 32);
	        case 9: strmid(FactionInfo[factionID][fRank9], (rankName), 0, strlen((rankName)), 32);
			case 10: strmid(FactionInfo[factionID][fRank10], (rankName), 0, strlen((rankName)), 32);
	    }
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el nombre del rango %d perteneciente a la facción %d ha sido cambiado a %s.", rankID, factionID, rankName);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		SaveFactions();
	}
	return 1;
}

CMD:afskin(playerid, params[]) {
	new
	    string[128],
	    factionID,
		rankID,
		skin;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "ddd", factionID, rankID, skin)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afskin [idfacción] [rango 1-10] [id skin]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && rankID >= 1 && rankID <= 10) {
	    switch(rankID) {
	        case 1: FactionInfo[factionID][fSkin1] = skin;
	        case 2: FactionInfo[factionID][fSkin2] = skin;
	        case 3: FactionInfo[factionID][fSkin3] = skin;
	        case 4: FactionInfo[factionID][fSkin4] = skin;
	        case 5: FactionInfo[factionID][fSkin5] = skin;
	        case 6: FactionInfo[factionID][fSkin6] = skin;
	        case 7: FactionInfo[factionID][fSkin7] = skin;
	        case 8: FactionInfo[factionID][fSkin8] = skin;
	        case 9: FactionInfo[factionID][fSkin9] = skin;
			case 10: FactionInfo[factionID][fSkin10] = skin;
	    }
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el skin de la facción %d perteneciente al rango %d ha sido cambiado a %d.", factionID, rankID, skin);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		SaveFactions();
	}
	return 1;
}

CMD:afmats(playerid, params[]) {
	new
	    string[128],
	    factionID,
		mats;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, mats)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afdmats [idfacción] [cantidad]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fMaterials] = mats;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} la cantidad de materiales de la facción %d ha sido ajustada a %d.", factionID, mats);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afdinero(playerid, params[]) {
	new
	    string[128],
	    factionID,
		money;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, money)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afdinero [idfacción] [cantidad]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fBank] = money;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} la cantidad de dinero de la facción %d ha sido ajustada a %d.", factionID, money);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afvehmision(playerid, params[]) {
	new
	    string[128],
	    vehicleid,
		faction;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", faction, vehicleid)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afvehmision [idfacción] [idvehiculo]");
	else if(faction >= 0 && faction < MAX_FACTIONS) {
    	FactionInfo[faction][fMissionVeh] = vehicleid;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} el vehículo de misión de la facción %d ha sido ajustado a %d.", faction, vehicleid);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afdrogas(playerid, params[]) {
	new
	    string[128],
	    factionID,
		drugs;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, drugs)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afdrogas [idfacción] [cantidad]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fDrugs] = drugs;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} la cantidad de drogas de la facción %d ha sido ajustada a %d.", factionID, drugs);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}


CMD:afrangoingreso(playerid, params[]) {
	new
	    string[128],
	    factionID,
		joinRank;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, joinRank)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afrangoingreso [idfacción] [rango 2-10]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && joinRank >= 2 && joinRank <= 10) {
    	FactionInfo[factionID][fJoinRank] = joinRank;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} el rango de ingreso de la facción %d ha sido ajustada a %d.", factionID, joinRank);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta o el rango es mayor a 10 o menor a 2.");
	}
	return 1;
}

CMD:afrangos(playerid, params[]) {
	new
	    string[128],
	    factionID,
		rankNum;

	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "dd", factionID, rankNum)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afrangos [idfacción] [cantidad de rangos 2-10]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && rankNum >= 2 && rankNum <= 10) {
	    FactionInfo[factionID][fRankAmount] = rankNum;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} la cantidad de rangos de la facción %d ha sido ajustada a %d.", factionID, rankNum);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción incorrecta o la cantidad de rangos es mayor a 10 o menor a 2.");
	}
	return 1;
}

CMD:afusaskins(playerid, params[]) {
	new
	    string[128],
	    factionID;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "d", factionID)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afusaskins [idfacción]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS) {
		if(FactionInfo[factionID][fUseSkins]) {
			FactionInfo[factionID][fUseSkins] = 0;
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la facción %d ya no utiliza skins propios.", factionID);
			SaveFactions();

		} else {
			FactionInfo[factionID][fUseSkins] = 1;
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la facción %d ahora utiliza skins propios.", factionID);
			foreach(new i : Player)	{
				if(PlayerInfo[i][pFaction] == factionID) {
					SetPlayerToFactionSkin(i);
				}
	       	}
		}
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		SaveFactions();
	}
	return 1;
}

CMD:afnombre(playerid, params[]) {
	new
	    string[128],
	    factionID,
		name[32];

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "ds[32]", factionID, name)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afnombre [idfacción] [nombre 32 chars]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && strlen(name) <= 32) {
	 	mysql_real_escape_string(name, name);
	 	strmid(FactionInfo[factionID][fName], (name), 0, strlen((name)), 32);
		format(string, sizeof(string), "Has seteado el nombre de la facción [%d] a '%s'.", factionID, name);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		SaveFactions();
	}
	return 1;
}

CMD:afexpulsar(playerid, params[]) {
	new
	    reason[64],
		string[128],
	    targetID;

    if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;

	if(sscanf(params, "uS(sin razon)[64]", targetID, reason)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afexpulsar [playerid/ParteDelNombre] [razón]");
	else if(IsPlayerConnected(targetID) && targetID != INVALID_PLAYER_ID) {
		format(string, sizeof(string), "%s ha sido expulsado de su facción por el administrador %s, razón: %s", GetPlayerNameEx(targetID), GetPlayerNameEx(playerid), reason);
		SendClientMessageToAll(COLOR_ADMINCMD, string);
		SetPlayerFaction(targetID, 0, 0);
		SpawnPlayer(targetID);
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} usuario inválido.");
	}
	return 1;
}
