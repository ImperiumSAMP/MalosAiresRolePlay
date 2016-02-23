#if defined _isamp_factions_included
	#endinput
#endif
#define _isamp_factions_included

//Defines
#define MAX_FACTIONS            21

//====[FACCIONES]===============================================================
#define FAC_NONE                0
#define FAC_PMA                 1 		// Polic�a Metropolitana.
#define FAC_HOSP                2       // SAME
#define FAC_SIDE                3		// SIDE
#define FAC_GOB	                4       // Malos Aires Ciudad
#define FAC_MECH                5       // TMMA
#define FAC_MAN                 6       // CTR-MAN
#define FAC_FREE_LEGAL_1        7       // Faccion Legal
#define FAC_FREE_LEGAL_2        8       // Faccion Legal
#define FAC_FREE_LEGAL_3        9       // Faccion Legal
#define FAC_FREE_LEGAL_4        10       // Faccion Legal
#define FAC_FREE_ILLEGAL_GANG_1 11       // Faccion Ilegal Gang
#define FAC_FREE_ILLEGAL_GANG_2 12       // Faccion Ilegal Gang
#define FAC_FREE_ILLEGAL_GANG_3 13       // Faccion Ilegal Gang
#define FAC_FREE_ILLEGAL_GANG_4 14       // Faccion Ilegal Gang
#define FAC_FREE_ILLEGAL_GANG_5 15       // Faccion Ilegal Gang
#define FAC_FREE_ILLEGAL_MAF_1	16       // Faccion Ilegal Mafia
#define FAC_FREE_ILLEGAL_MAF_2 	17       // Faccion Ilegal Mafia
#define FAC_FREE_ILLEGAL_MAF_3 	18       // Faccion Ilegal Mafia
#define FAC_FREE_ILLEGAL_MAF_4 	19       // Faccion Ilegal Mafia
#define FAC_FREE_ILLEGAL_MAF_5 	20       // Faccion Ilegal Mafia


#define FAC_TYPE_ILLEGAL        0
#define FAC_TYPE_GOV            1
#define FAC_TYPE_LEGAL          2
#define FAC_TYPE_GANG	        3


//Enums
enum Factions {
	fName[50],
	fMaterials,
	fBank,
	fPayDay1,
	fPayDay2,
	fPayDay3,
	fPayDay4,
	fPayDay5,
	fPayDay6,
	fPayDay7,
	fPayDay8,
	fPayDay9,
	fPayDay10,
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
	fJoinRank,
	fType,
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

stock isPlayerCopOnDuty(playerid)
{
	if(PlayerInfo[playerid][pFaction] == FAC_PMA && CopDuty[playerid])
	    return true;
	else
	    return false;
}

stock isPlayerSideOnDuty(playerid)
{
	if(PlayerInfo[playerid][pFaction] == FAC_SIDE && SIDEDuty[playerid])
	    return true;
	else
		return false;
}

forward CountCopsOnDuty();
public CountCopsOnDuty()
{
	new aux = 0;
 	foreach(new i : Player)
 	{
        if(isPlayerCopOnDuty(i))
    	    aux ++;
 	}
 	return aux;
}

//==========================FACTION MONEY FUNCTIONS=============================

stock GiveFactionMoney(factionid, money)
{
	FactionInfo[factionid][fBank] += money;
}

stock SetFactionMoney(factionid, money)
{
	FactionInfo[factionid][fBank] = money;
}

stock GetFactionMoney(factionid)
{
	return FactionInfo[factionid][fBank];
}
//=======================COMANDOS DE ADMIN PARA FACCIONES=======================

CMD:afacciones(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "==============================[COMANDOS DE ADMIN PARA FACCIONES]==============================");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 10]:{C8C8C8} /afexpulsar /afvehiculos /afallowjob /afinfo - /aftipo - /afnombre - /afrangos");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 10]:{C8C8C8} /afrangoingreso - /afdinero - /afmats - /afrango - /afvehmision");
	return 1;
}

CMD:afinfo(playerid, params[])
{
	new id, string[128];

	if(sscanf(params, "i", id))
		 return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afinfo [idfacción]");
	if(id < 0 || id >= MAX_FACTIONS)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");

	format(string, sizeof(string), "{878EE7}[ID %d]:{C8C8C8} Nombre de facción: %s - Materiales: %d - Dinero: $%d - Rango de ingreso: %d - Tipo: %d",id, FactionInfo[id][fName],FactionInfo[id][fMaterials],GetFactionMoney(id),FactionInfo[id][fJoinRank],FactionInfo[id][fType]);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	format(string, sizeof(string), "{878EE7}[ID %d]:{C8C8C8} Cantidad de rangos: %d - Permiso de empleo: %d", id,FactionInfo[id][fRankAmount],FactionInfo[id][fAllowJob]);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	return 1;
}

CMD:afallowjob(playerid, params[])
{
	new factionID, option;

	if(sscanf(params, "ii", factionID, option))
		 return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afallowjob [idfacción] [1=SI 0=NO]");
	if(factionID < 1 || factionID >= MAX_FACTIONS)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");

	FactionInfo[factionID][fAllowJob] = option;
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} El permiso de empleo de la facción %d ha sido ajustado a %d.", factionID, option);
	SaveFactions();
	return 1;
}

CMD:aftipo(playerid, params[])
{
	new string[128], factionID, type;

	if(sscanf(params, "dd", factionID, type)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aftipo [idfacción] [tipo]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[TIPOS]:{C8C8C8} 0 - Ilegal | 1 - Gobierno | 2 - Legal | 3 - Pandilla");
	} else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fType] = type;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} El tipo de la facción %d ha sido ajustado a %d.", factionID, type);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afvehiculos(playerid, params[])
{
	new factionID;
	if(sscanf(params, "dd", factionID))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afvehiculos [idfacción]");
    if(factionID < 1 && factionID >= MAX_FACTIONS)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");
    SendFMessage(playerid, COLOR_LIGHTYELLOW2, "===============|Vehiculos de la facción: %s|===============", FactionInfo[factionID][fName]);
	for(new i=0; i<MAX_VEH; i++)
	{
	    if(VehicleInfo[i][VehFaction] == factionID)
	        SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} Vehículo ID %d - Modelo %s", i, GetVehicleName(i));
	}
	SendClientMessage(playerid, COLOR_YELLOW, "====================================================================");
	return 1;
}

CMD:afrango(playerid, params[]) {
	new
	    string[128],
	    factionID,
		rankID,
		rankName[32];

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
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} El nombre del rango %d perteneciente a la facción %d ha sido cambiado a %s.", rankID, factionID, rankName);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
		SaveFactions();
	}
	return 1;
}

CMD:afmats(playerid, params[]) {
	new
	    string[128],
	    factionID,
		mats;

	if(sscanf(params, "dd", factionID, mats)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afdmats [idfacción] [cantidad]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS) {
    	FactionInfo[factionID][fMaterials] = mats;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} La cantidad de materiales de la facción %d ha sido ajustada a %d.", factionID, mats);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afdinero(playerid, params[])
{
	new string[128],
	    factionID,
		money;
		
	if(sscanf(params, "dd", factionID, money))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afdinero [idfacción] [cantidad]");
	if(factionID < 1 || factionID >= MAX_FACTIONS)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");

	SetFactionMoney(factionID, money);
	format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} La cantidad de dinero de la facción %d ha sido ajustada a %d.", factionID, money);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
    SaveFactions();
	return 1;
}

CMD:afvehmision(playerid, params[]) {
	new
	    string[128],
	    vehicleid,
		faction;


	if(sscanf(params, "dd", faction, vehicleid)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afvehmision [idfacción] [idvehiculo]");
	else if(faction >= 0 && faction < MAX_FACTIONS) {
    	FactionInfo[faction][fMissionVeh] = vehicleid;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} El vehículo de misión de la facción %d ha sido ajustado a %d.", faction, vehicleid);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta.");
	}
	return 1;
}

CMD:afrangoingreso(playerid, params[]) {
	new
	    string[128],
	    factionID,
		joinRank;


	if(sscanf(params, "dd", factionID, joinRank)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afrangoingreso [idfacción] [rango 2-10]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && joinRank >= 2 && joinRank <= 10) {
    	FactionInfo[factionID][fJoinRank] = joinRank;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} El rango de ingreso de la facción %d ha sido ajustada a %d.", factionID, joinRank);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta o el rango es mayor a 10 o menor a 2.");
	}
	return 1;
}

CMD:afrangos(playerid, params[]) {
	new
	    string[128],
	    factionID,
		rankNum;
		
	if(sscanf(params, "dd", factionID, rankNum)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afrangos [idfacción] [cantidad de rangos 2-10]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && rankNum >= 2 && rankNum <= 10) {
	    FactionInfo[factionID][fRankAmount] = rankNum;
		format(string, sizeof string, "{878EE7}[INFO]:{C8C8C8} La cantidad de rangos de la facción %d ha sido ajustada a %d.", factionID, rankNum);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	    SaveFactions();
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de facción incorrecta o la cantidad de rangos es mayor a 10 o menor a 2.");
	}
	return 1;
}

CMD:afnombre(playerid, params[]) {
	new
	    string[128],
	    factionID,
		name[32];


	if(sscanf(params, "ds[32]", factionID, name)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afnombre [idfacción] [nombre 32 chars]");
	else if(factionID >= 0 && factionID < MAX_FACTIONS && strlen(name) <= 32) {
	 	mysql_real_escape_string(name, name);
	 	strmid(FactionInfo[factionID][fName], (name), 0, strlen((name)), 32);
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} El nombre de la facción %d a sido ajustado a %s.", factionID, name);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
		SaveFactions();
	}
	return 1;
}

CMD:afexpulsar(playerid, params[]) {
	new
	    reason[64],
		string[128],
	    targetID;

	if(sscanf(params, "uS(sin razon)[64]", targetID, reason)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /afexpulsar [playerid/ParteDelNombre] [razón]");
	else if(IsPlayerConnected(targetID) && targetID != INVALID_PLAYER_ID) {
		format(string, sizeof(string), "%s ha sido expulsado de su facción por el administrador %s, razón: %s.", GetPlayerNameEx(targetID), GetPlayerNameEx(playerid), reason);
		SendClientMessageToAll(COLOR_ADMINCMD, string);
		SetPlayerFaction(targetID, 0, 0);
		SpawnPlayer(targetID);
	} else {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[ERROR]:{C8C8C8} ID de usuario inválida.");
	}
	return 1;
}

CMD:comprarmateriales(playerid, params[])
{
	new amount,
		freehand = SearchFreeHand(playerid);

	if(PlayerInfo[playerid][pFaction] != FAC_NONE && FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_ILLEGAL)
    {	
		if(!PlayerToPoint(4.0, playerid, 2349.8408, -1216.3939, 22.5000))
	        return SendClientMessage(playerid, COLOR_YELLOW, "¡No puedes usar éste comando en cualquier lado!");
	    if(sscanf(params, "i", amount))
	    {
	        SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprarmateriales [cantidad] | $%d cada material.", GetItemPrice(ITEM_ID_MATERIALES));
			return 1;
		}
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
		if(freehand == -1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar la caja de insumos.");
		if(amount < 1 || amount > 1300)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad de materiales no debe ser menor a 1 o mayor a 1300.");
		if(GetPlayerCash(playerid) < amount * GetItemPrice(ITEM_ID_MATERIALES))
		{
			SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, necesitas $%d.", amount * GetItemPrice(ITEM_ID_MATERIALES));
			return 1;
		}

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	    SetHandItemAndParam(playerid, freehand, ITEM_ID_MATERIALES, amount);
		GivePlayerCash(playerid, -amount * GetItemPrice(ITEM_ID_MATERIALES));
		SendClientMessage(playerid, COLOR_WHITE, "Vé al deposito y descarga los materiales con /guardarmateriales. Utiliza /nocargar para sacar la animación de carga.");
		PlayerActionMessage(playerid, 15.0, "compra una caja de materiales y la guarda en el maletero del vehículo.");
	} else {
	    SendClientMessage(playerid, COLOR_FADE1, "Desconocido dice: ¿Te conozco?");
	}
	return 1;
}

CMD:guardarmateriales(playerid, params[])
{
	new hand = SearchHandsForItem(playerid, ITEM_ID_MATERIALES),
	    amount;

    if(PlayerInfo[playerid][pFaction] != FAC_NONE && FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_ILLEGAL)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
		if(hand == -1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener una caja de materiales en tus manos para descargar.");
		amount = GetHandParam(playerid, hand);
		if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] + amount > 270000)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cargar más materiales al depósito ya que el mismo está lleno.");

	    for(new i = 1; i < MAX_BUILDINGS; i++)
		{
			if(PlayerToPoint(2.0, playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]) || PlayerToPoint(2.0, playerid, Building[i][blInsideX], Building[i][blInsideY], Building[i][blInsideZ]))
			{
				if(Building[i][blFaction] != 0 && PlayerInfo[playerid][pFaction] == Building[i][blFaction])
				{
	                FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] += amount;
					SetHandItemAndParam(playerid, hand, 0, 0);
					PlayerActionMessage(playerid, 15.0, "descarga una caja de insumos en el depósito.");
				}
				return 1;
			}
		}
	}
 	return 1;
}
