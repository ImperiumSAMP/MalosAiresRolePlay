#if defined _isamp_houses_included
	#endinput
#endif
#define _isamp_houses_included

//========================SISTEMA Y COMANDOS DE CASA============================

//================================CONSTANTES====================================

#define MAX_HOUSES              500

//============================VARIABLES INTERNAS================================

enum HouseSystem {
	Created,
	Owned,
	OwnerSQLID,
	OwnerName[MAX_PLAYER_NAME],
	Float:OutsideX,
	Float:OutsideY,
	Float:OutsideZ,
	Float:OutsideAngle,
	OutsideInterior,
	OutsideWorld,
	Float:InsideX,
	Float:InsideY,
	Float:InsideZ,
	Float:InsideAngle,
	InsideInterior,
	InsideWorld,
	Tenant[MAX_PLAYER_NAME],
	IncomeAccept,
	Income,
	IncomePrice,
	IncomePriceAdd,
	HousePrice,
	Money,
	Locked,
	hOutsidePickup,
	hInsidePickup,
	Text3D:hOutsideLabel,
	Text3D:hInsideLabel,
	Marijuana,
	LSD,
	Ecstasy,
	Cocaine,
	Radio
};

new House[MAX_HOUSES][HouseSystem];

// Venta de casas
new bool:OfferingHouse[MAX_PLAYERS],
	HouseOfferPrice[MAX_PLAYERS],
	HouseOffer[MAX_PLAYERS];
	
//================================FUNCIONES=====================================

forward ResetHouseOffer(playerid);
forward GetPlayerHouse(playerid);
forward bool:EnterHouse(playerid);
forward bool:LeaveHouse(playerid);

//========================IMPLEMENTACION DE FUNCIONES===========================

stock LoadHouses()
{
	new query[128],
		id = 1;
		
	while(id < MAX_HOUSES)
	{
	    format(query, sizeof(query),"SELECT * FROM `houses` WHERE `Id` = %d LIMIT 1", id);
		mysql_function_query(dbHandle, query, true, "OnHouseDataLoad", "i", id);
		id++;
	}
	print("[INFO]: casas cargadas.");
	return 1;
}

forward OnHouseDataLoad(id);
public OnHouseDataLoad(id)
{
   	new result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows)
	{
		cache_get_field_content(0, "Owned", result); 				House[id][Owned] 				= strval(result);
		cache_get_field_content(0, "OwnerSQLID", result);			House[id][OwnerSQLID]    		= strval(result);
		cache_get_field_content(0, "OwnerName", 					House[id][OwnerName], 1, MAX_PLAYER_NAME);

		cache_get_field_content(0, "OutsideX", result); 			House[id][OutsideX] 			= floatstr(result);
		cache_get_field_content(0, "OutsideY", result); 			House[id][OutsideY] 			= floatstr(result);
		cache_get_field_content(0, "OutsideZ", result); 			House[id][OutsideZ] 			= floatstr(result);
		cache_get_field_content(0, "OutsideAngle", result); 		House[id][OutsideAngle] 		= floatstr(result);
		cache_get_field_content(0, "OutsideInterior", result); 		House[id][OutsideInterior]		= strval(result);
		cache_get_field_content(0, "OutsideWorld", result); 		House[id][OutsideWorld]			= strval(result);

		cache_get_field_content(0, "InsideX", result); 				House[id][InsideX] 				= floatstr(result);
		cache_get_field_content(0, "InsideY", result); 				House[id][InsideY] 				= floatstr(result);
		cache_get_field_content(0, "InsideZ", result); 				House[id][InsideZ] 				= floatstr(result);
		cache_get_field_content(0, "InsideAngle", result); 			House[id][InsideAngle] 			= floatstr(result);
		cache_get_field_content(0, "InsideInterior", result); 		House[id][InsideInterior] 		= strval(result);
		cache_get_field_content(0, "InsideWorld", result); 			House[id][InsideWorld] 			= strval(result);

		cache_get_field_content(0, "HousePrice", result); 			House[id][HousePrice] 			= strval(result);
		cache_get_field_content(0, "Money", result); 				House[id][Money] 				= strval(result);
		cache_get_field_content(0, "Locked", result); 				House[id][Locked]				= strval(result);
		cache_get_field_content(0, "Marijuana", result); 			House[id][Marijuana]			= strval(result);
		cache_get_field_content(0, "LSD", result); 					House[id][LSD]					= strval(result);
		cache_get_field_content(0, "Cocaine", result); 				House[id][Cocaine]				= strval(result);
		cache_get_field_content(0, "Ecstasy", result); 				House[id][Ecstasy]				= strval(result);
		cache_get_field_content(0, "Radio", result); 				House[id][Radio]				= strval(result);

		cache_get_field_content(0, "Tenant", 						House[id][Tenant], 1, MAX_PLAYER_NAME);
		cache_get_field_content(0, "IncomeAccept", result); 		House[id][IncomeAccept] 		= strval(result);
		cache_get_field_content(0, "Income", result); 				House[id][Income] 				= strval(result);
		cache_get_field_content(0, "IncomePrice", result); 			House[id][IncomePrice] 			= strval(result);
		cache_get_field_content(0, "IncomePriceAdd", result); 		House[id][IncomePriceAdd] 		= strval(result);

        House[id][Created] = 1;
		House[id][hOutsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, House[id][OutsideX], House[id][OutsideY], House[id][OutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
		House[id][hInsideLabel] = CreateDynamic3DTextLabel("-", 0x008080FF, House[id][InsideX], House[id][InsideY], House[id][InsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, House[id][InsideWorld], House[id][InsideInterior], -1, 100.0);
        ReloadHouseIcon(id);
	}
	return 1;
}

stock ReloadHouseIcon(houseid)
{
    new string[228],
		houseLoc[MAX_ZONE_NAME];

	DestroyDynamic3DTextLabel(House[houseid][hOutsideLabel]);
	DestroyDynamic3DTextLabel(House[houseid][hInsideLabel]);

	DestroyDynamicPickup(House[houseid][hOutsidePickup]);
	DestroyDynamicPickup(House[houseid][hInsidePickup]);

    House[houseid][hInsidePickup] = CreateDynamicPickup(19198, 1, House[houseid][InsideX], House[houseid][InsideY], House[houseid][InsideZ], House[houseid][InsideWorld]);

	GetCoords2DZone(House[houseid][OutsideX], House[houseid][OutsideY], houseLoc, MAX_ZONE_NAME);

	if(House[houseid][Owned] == 0 && House[houseid][IncomeAccept] == 0 && House[houseid][Income] == 0) {
		format(string, sizeof(string), "{21A325}Casa a la venta {FFFFFF}\nUtiliza /casacomprar\nDirección: %d %s\nPrecio: $%d", houseid, houseLoc, House[houseid][HousePrice]);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1273, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}else if(House[houseid][Owned] == 0 && House[houseid][IncomeAccept] == 1 && House[houseid][Income] == 0) {
		format(string, sizeof(string), "{21A325}Casa en alquiler {FFFFFF}\nUtiliza /casaalquilar\nDirección: %d %s\nPrecio: $%d", houseid, houseLoc, House[houseid][IncomePrice]);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1273, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}else if(House[houseid][Owned] == 0 && House[houseid][IncomeAccept] == 1 && House[houseid][Income] != 0) {
	    format(string, sizeof(string), "{49AFE6}Casa con inquilino {FFFFFF}\nDirección: %d %s\nPresiona ENTER para entrar", houseid, houseLoc);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1239, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}else if(House[houseid][Owned] == 1 && House[houseid][IncomeAccept] == 1 && House[houseid][Income] != 0) {
	    format(string, sizeof(string), "{49AFE6}Casa con inquilino {FFFFFF}\nDirección: %d %s\nPresiona ENTER para entrar", houseid, houseLoc);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1239, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}else if(House[houseid][Owned] == 1 && House[houseid][IncomeAccept] == 1 && House[houseid][Income] == 0) {
	    format(string, sizeof(string), "{21A325}Casa en alquiler {FFFFFF}\nUtiliza /casaalquilar\nDirección: %d %s\nPrecio: $%d", houseid, houseLoc, House[houseid][IncomePrice]);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1273, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}else if(House[houseid][Owned] == 1 && House[houseid][IncomeAccept] == 0 && House[houseid][Income] == 0) {
	    format(string, sizeof(string), "{49AFE6}Casa con dueño {FFFFFF}\nDirección: %d %s\nPresiona ENTER para entrar", houseid, houseLoc);
		House[houseid][hOutsidePickup] = CreateDynamicPickup(1239, 1, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ], -1);
	}

	House[houseid][hOutsideLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
	House[houseid][hInsideLabel] = CreateDynamic3DTextLabel("{A9E2F3}Presiona ENTER para salir", COLOR_WHITE, House[houseid][InsideX], House[houseid][InsideY], House[houseid][InsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, House[houseid][InsideWorld], -1, -1, 100.0);
}

stock CreateHouse(id)
{
	new query[1024];

    if(dontsave)
		return 1;

    format(query, sizeof(query), "INSERT INTO `houses` (Id, OwnerName, OutsideX, OutsideY, OutsideZ, OutsideAngle, OutsideInterior, OutsideWorld, InsideX, InsideY, InsideZ, InsideInterior, InsideWorld, HousePrice, Locked)");
	format(query, sizeof(query), "%s VALUES (%d, '%s', %f, %f, %f, %f, %d, %d, %f, %f, %f, %d, %d, %d, %d)",
	    query,
	    id,
		House[id][OwnerName],
	    House[id][OutsideX],
	    House[id][OutsideY],
	    House[id][OutsideZ],
	    House[id][OutsideAngle],
	    House[id][OutsideInterior],
	    House[id][OutsideWorld],
	    House[id][InsideX],
		House[id][InsideY],
		House[id][InsideZ],
		House[id][InsideInterior],
		House[id][InsideWorld],
		House[id][HousePrice],
		House[id][Locked]
	);
	mysql_function_query(dbHandle, query, false, "", "");

	House[id][Created] = 1;
	House[id][hOutsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, House[id][OutsideX], House[id][OutsideY], House[id][OutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
	House[id][hInsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, House[id][InsideX], House[id][InsideY], House[id][InsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, House[id][InsideWorld], House[id][InsideInterior], -1, 100.0);
    ReloadHouseIcon(id);
	return 1;
}

stock DeleteHouse(id)
{
	new query[128];

    if(dontsave)
		return 1;

 	DestroyDynamic3DTextLabel(House[id][hOutsideLabel]);
	DestroyDynamic3DTextLabel(House[id][hInsideLabel]);
	DestroyDynamicPickup(House[id][hOutsidePickup]);
	DestroyDynamicPickup(House[id][hInsidePickup]);

	format(query, sizeof(query), "DELETE FROM `houses` WHERE `Id` = %d", id);
 	mysql_function_query(dbHandle, query, false, "", "");

 	House[id][Created] = 0;
	House[id][Owned] = 0;
	House[id][OwnerSQLID] = 0;
	strmid(House[id][OwnerName], "", 0, strlen(""), 255);
	House[id][OutsideX] = 0.0;
    House[id][OutsideY] = 0.0;
    House[id][OutsideZ] = 0.0;
    House[id][OutsideAngle] = 0.0;
    House[id][OutsideInterior] = 0;
    House[id][OutsideWorld] = 0;
    House[id][InsideX] = 0.0;
	House[id][InsideY] = 0.0;
	House[id][InsideZ] = 0.0;
	House[id][InsideAngle] = 0.0;
	House[id][InsideInterior] = 0;
	House[id][InsideWorld] = 0;
	strmid(House[id][Tenant], "", 0, strlen(""), 255);
	House[id][IncomeAccept] = 0;
	House[id][Income] = 0;
	House[id][IncomePrice] = 0;
	House[id][IncomePriceAdd] = 0;
	House[id][HousePrice] = 0;
	House[id][Money] = 0;
	House[id][Locked] = 0;
	House[id][Marijuana] = 0;
	House[id][LSD] = 0;
	House[id][Ecstasy] = 0;
	House[id][Cocaine] = 0;
	House[id][Radio] = 0;
	return 1;
}

SaveHouses()
{
  	new id = 1;

    if(dontsave)
		return 1;

	while(id < MAX_HOUSES)
	{
	    SaveHouse(id);
		id++;
	}
    print("[INFO]: casas guardadas.");
	return 1;
}

stock SaveHouse(id)
{
	new query[1512];

    if(dontsave || House[id][Created] == 0)
		return 1;
		
	format(query, sizeof(query), "UPDATE `houses` SET `Owned`=%d, `OwnerSQLID`=%d, `OwnerName`='%s', `OutsideX`=%f, `OutsideY`=%f, `OutsideZ`=%f, `OutsideAngle`=%f, `OutsideInterior`=%d, `OutsideWorld`=%d",
	    House[id][Owned],
	    House[id][OwnerSQLID],
	    House[id][OwnerName],
	    House[id][OutsideX],
	    House[id][OutsideY],
	    House[id][OutsideZ],
	    House[id][OutsideAngle],
	    House[id][OutsideInterior],
	    House[id][OutsideWorld]
	);
	format(query, sizeof(query), "%s, `InsideX`=%f, `InsideY`=%f, `InsideZ`=%f, `InsideAngle`=%f, `InsideInterior`=%d, `InsideWorld`=%d, `HousePrice`=%d, `Money`=%d, `Locked`=%d, `Marijuana`=%d, `LSD`=%d",
		query,
	    House[id][InsideX],
		House[id][InsideY],
		House[id][InsideZ],
		House[id][InsideAngle],
		House[id][InsideInterior],
		House[id][InsideWorld],
		House[id][HousePrice],
		House[id][Money],
		House[id][Locked],
		House[id][Marijuana],
		House[id][LSD]
	);
	format(query, sizeof(query), "%s, `Cocaine`=%d, `Ecstasy`=%d, `Radio`=%d, `Tenant`='%s', `IncomeAccept`=%d, `Income`=%d, `IncomePrice`=%d, `IncomePriceAdd`=%d WHERE `Id`=%d",
		query,
		House[id][Cocaine],
		House[id][Ecstasy],
		House[id][Radio],
		House[id][Tenant],
		House[id][IncomeAccept],
		House[id][Income],
		House[id][IncomePrice],
		House[id][IncomePriceAdd],
		id
	);

	mysql_function_query(dbHandle, query, false, "", "");
	ReloadHouseIcon(id);
	return 1;
}
	
stock ResetHouseOffer(playerid)
{
    OfferingHouse[playerid] = false;
	HouseOfferPrice[playerid] = -1;
	HouseOffer[playerid] = INVALID_PLAYER_ID;
}

stock GetPlayerHouse(playerid)
{
	new pint = GetPlayerInterior(playerid),
	    pworld = GetPlayerVirtualWorld(playerid);

	for(new i = 1; i < MAX_HOUSES; i++)
	{
	    if(House[i][Created] == 1 && House[i][InsideInterior] == pint && House[i][InsideWorld] == pworld)
			return i;
	}
	return 0;
}

stock bool:EnterHouse(playerid)
{
	for(new i = 1; i < MAX_HOUSES; i++)
	{
	    if(House[i][Created] == 1)
	    {
	    	if(IsPlayerOnOutsideHouseDoor(playerid, i))
	    	{
				if(House[i][Locked] == 0 || AdminDuty[playerid])
				{
					SetPlayerInterior(playerid, House[i][InsideInterior]);
					SetPlayerVirtualWorld(playerid, House[i][InsideWorld]);
					SetPlayerPos(playerid, House[i][InsideX], House[i][InsideY], House[i][InsideZ]);
					SetPlayerFacingAngle(playerid, House[i][InsideAngle]);
					SetCameraBehindPlayer(playerid);
					PlayRadioStreamForPlayer(playerid, House[i][Radio]);
				} else
					GameTextForPlayer(playerid, "~r~Cerrado!", 2000, 4);
				return true;
			}
		}
	}
	return false;
}

stock bool:LeaveHouse(playerid)
{
	for(new i = 1; i < MAX_HOUSES; i++)
	{
		if(House[i][Created] == 1)
	    {
	    	if(IsPlayerOnInsideHouseDoor(playerid, i))
	    	{
		        if(House[i][Locked] == 0 || AdminDuty[playerid])
				{
					SetPlayerInterior(playerid, House[i][OutsideInterior]);
					SetPlayerVirtualWorld(playerid, House[i][OutsideWorld]);
					SetPlayerPos(playerid, House[i][OutsideX], House[i][OutsideY], House[i][OutsideZ]);
					SetPlayerFacingAngle(playerid, House[i][OutsideAngle]);
					SetCameraBehindPlayer(playerid);
					PlayRadioStreamForPlayer(playerid, 0);
				} else
					GameTextForPlayer(playerid, "~r~Cerrado!", 2000, 4);
				return true;
			}
		}
	}
	return false;
}

RentalExpiration(playerid)
{
    if(PlayerInfo[playerid][pHouseKeyIncome] != 0 && House[PlayerInfo[playerid][pHouseKeyIncome]][Income] >= 2)
	{
        if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 2)
	    {
	        SendClientMessage(playerid, COLOR_WHITE, "Te han desalojado de tu vivienda como se te informo que pasaria, todo lo que hayas dejado dentro dalo por perdido.");
        	House[PlayerInfo[playerid][pHouseKeyIncome]][Locked] = 1;
			House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 0;
			House[PlayerInfo[playerid][pHouseKeyIncome]][IncomeAccept] = 0;
			strmid(House[PlayerInfo[playerid][pHouseKeyIncome]][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
			SaveHouse(PlayerInfo[playerid][pHouseKeyIncome]);
			PlayerInfo[playerid][pHouseKeyIncome] = 0;
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 3)
	    {
	        SendClientMessage(playerid, COLOR_WHITE, "En el próximo payday rescinde el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
	        House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 2;
	        SaveHouse(PlayerInfo[playerid][pHouseKeyIncome]);
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 4)
	    {
            SendClientMessage(playerid, COLOR_WHITE, "Te quedan 2 paydays antes de que rescinda el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
            House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 3;
            SaveHouse(PlayerInfo[playerid][pHouseKeyIncome]);
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 5)
	    {
	        SendClientMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmobiliaria: Señor, le queremos informar que el dueño de la vivienda la cual usted alquila ha decidido...");
    		SendClientMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmobiliaria: ...rescindirle el contrato, tiene 3 dias (paydays) para retirar sus pertenencias.");
            House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 4;
            SaveHouse(PlayerInfo[playerid][pHouseKeyIncome]);
		}
	}
}

PrintHouseRentAdvise(playerid)
{
	if(PlayerInfo[playerid][pHouseKeyIncome] != 0 && House[PlayerInfo[playerid][pHouseKeyIncome]][Income] >= 3)
	{
	    if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 5)
	    {
	        SendClientMessage(playerid, COLOR_WHITE, "Te quedan 3 paydays antes de que finalice el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
		}
		else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 4)
	    {
            SendClientMessage(playerid, COLOR_WHITE, "Te quedan 2 paydays antes de que finalice el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
		}
		else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 3)
	    {
            SendClientMessage(playerid, COLOR_WHITE, "En el próximo payday rescinde el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
		}
	}
}

PrintPlayerHouseAddress(playerid, targetid)
{
	new houselocation[MAX_ZONE_NAME];
	
    if(PlayerInfo[playerid][pHouseKey] != 0 && House[PlayerInfo[playerid][pHouseKey]][Income]!= 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
	    GetCoords2DZone(House[PlayerInfo[playerid][pHouseKeyIncome]][OutsideX],House[PlayerInfo[playerid][pHouseKeyIncome]][OutsideY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKeyIncome], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0 && House[PlayerInfo[playerid][pHouseKey]][Income]!= 0)
	{
	    SendClientMessage(targetid, COLOR_WHITE, "Domicilio: No tiene");
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
	    GetCoords2DZone(House[PlayerInfo[playerid][pHouseKeyIncome]][OutsideX],House[PlayerInfo[playerid][pHouseKeyIncome]][OutsideY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKey], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0)
	{
		GetCoords2DZone(House[PlayerInfo[playerid][pHouseKey]][OutsideX],House[PlayerInfo[playerid][pHouseKey]][OutsideY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKey], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] == 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
		GetCoords2DZone(House[PlayerInfo[playerid][pHouseKey]][OutsideX],House[PlayerInfo[playerid][pHouseKey]][OutsideY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKeyIncome], houselocation);
	}
	else
		SendClientMessage(targetid, COLOR_WHITE, "Domicilio: No tiene");
}

//=============================COMANDOS DE CASA=================================

CMD:ayudacasa(playerid, params[])
{
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[CASA]: /casacomprar - /casavender - /casavendera - /casaalquilar - /casadesalquilar - /casaradio - /puerta - /armario");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[CASA]: /casaenalquiler - /casasinalquiler - /casacontrato");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} Si alguien alquila tu casa y quieres rescindirle el contrato utiliza '/casacontrato'");
	return 1;
}

CMD:casaradio(playerid, params[])
{
	new radio,
	    houseid = GetPlayerHouse(playerid);

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casaradio [ID radio]");
	if(houseid == 0 || houseid != PlayerInfo[playerid][pHouseKey])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en tu casa.");
	if(radio < 0 || radio > 16)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio válida: del 1 al 16. Usa 0 para dejarlo sin radio.");

    House[houseid][Radio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]:{C8C8C8} Has seteado la radio de tu casa a %d.", House[houseid][Radio]);
	PlayRadioStreamForPlayer(playerid, House[houseid][Radio]);
	SaveHouse(houseid);
	return 1;
}

CMD:casacomprar(playerid, params[])
{
    new name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(PlayerInfo[playerid][pHouseKey] != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tener más de una casa!");
		
    for(new h = 1; h < MAX_HOUSES; h++)
	{
	    if(House[h][Created] == 1)
	    {
    		if(IsPlayerOnOutsideHouseDoor(playerid, h))
    		{
				if(House[h][Owned] == 1)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "Esta casa no está a la venta.");
			    if(House[h][Tenant] == PlayerInfo[playerid][pName])
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes comprar la casa que alquilas!");
			    if(House[h][HousePrice] <= 0)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta casa no tiene precio!, probablemente no está a la venta.");
				if(GetPlayerCash(playerid) < House[h][HousePrice])
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");

				GetPlayerName(playerid, name, sizeof(name));
				PlayerInfo[playerid][pHouseKey] = h;
				House[h][Owned] = 1;
				House[h][OwnerSQLID] = PlayerInfo[playerid][pID];
				strmid(House[h][OwnerName], name, 0, strlen(name), 255);
				SetPlayerInterior(playerid, House[h][InsideInterior]);
				SetPlayerVirtualWorld(playerid, House[h][InsideWorld]);
				SetPlayerPos(playerid, House[h][InsideX], House[h][InsideY], House[h][InsideZ]);
				SetPlayerFacingAngle(playerid, House[h][InsideAngle]);
				SetCameraBehindPlayer(playerid);
				PlayRadioStreamForPlayer(playerid, House[h][Radio]);
				GivePlayerCash(playerid, -House[h][HousePrice]);
				SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has comprado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
			   	PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y este le entrega un par de llaves.");
				SaveHouse(h);
				return 1;
			}
		}
    }
	return 1;
}

CMD:casavender(playerid, params[])
{
	new house = PlayerInfo[playerid][pHouseKey];

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para venderla!");
	if(House[house][OwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");

	if(House[house][Income] >= 1)
	    House[house][IncomePrice] = House[house][HousePrice] / 100;
	House[house][Owned] = 0;
	House[house][OwnerSQLID] = 0;
	strmid(House[house][OwnerName], "Ninguno", 0, strlen("Ninguno"), 255);
	House[house][Locked] = 1;
	PlayerInfo[playerid][pHouseKey] = 0;
	GivePlayerCash(playerid, House[house][HousePrice] / 3 * 2); // 66 % del valor original.
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendFMessage(playerid, COLOR_WHITE, "¡Has vendido tu casa por $%d!", House[house][HousePrice] / 3 * 2);
	PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
	SaveHouse(house);
	return 1;
}

CMD:casavendera(playerid, params[])
{
	new house = PlayerInfo[playerid][pHouseKey],
		targetid,
		price;

	if(sscanf(params, "ui", targetid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casavendera [ID/Jugador] [Precio]");
	if(house == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para venderla!");
   	if(targetid == playerid || !ProxDetectorS(3.0, playerid, targetid))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido o el sujeto no está cerca tuyo.");
  	if(price < 1 || price > 10000000)
   		return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $10,000,000.");
  	if(OfferingHouse[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras vendiendo una casa.");
 	if(House[house][OwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");

	OfferingHouse[playerid] = true;
	HouseOfferPrice[targetid] = price;
	HouseOffer[targetid] = playerid;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le ofreces las llaves y la escritura de tu casa a %s por $%d.", GetPlayerNameEx(targetid), price);
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te esta ofreciendo venderte su casa por $%d.", GetPlayerNameEx(playerid), price);
	SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/casaaceptar' para aceptar la oferta o '/casacancelar' para cancelar.");
	SetPVarInt(targetid, "CancelHouseTransfer", SetTimerEx("CancelHouseTransfer", 10000, false, "ii", targetid, 1));
	return 1;
}

CMD:casaaceptar(playerid, params[])
{
	new sellerid = HouseOffer[playerid],
	    price = HouseOfferPrice[playerid],
	    houseid,
	    name[MAX_PLAYER_NAME];

	if(sellerid == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo una casa.");
	if(!IsPlayerConnected(sellerid) || !OfferingHouse[sellerid])
	{
	    KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	    CancelHouseTransfer(playerid, 2);
		return SendClientMessage(playerid, COLOR_YELLOW2, "Hubo un error durante la venta, cancelando...");
	}
	if(!ProxDetectorS(3.0, playerid, sellerid))
 	   	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
	if(GetPlayerCash(playerid) < price)
	{
	    KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	    CancelHouseTransfer(playerid, 2);
	    SendClientMessage(sellerid, COLOR_YELLOW2, "El jugador no tiene el dinero necesario, cancelando...");
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, cancelando...");
	}
	if(PlayerInfo[playerid][pHouseKey] != 0)
	{
	    KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	    CancelHouseTransfer(playerid, 2);
		SendClientMessage(sellerid, COLOR_YELLOW2, "El jugador ya tiene una casa, cancelando...");
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes una casa, cancelando...");
	}
	if(PlayerInfo[sellerid][pHouseKey] == 0)
	{
	    KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	    CancelHouseTransfer(playerid, 2);
		SendClientMessage(sellerid, COLOR_YELLOW2, "No tienes una casa, cancelando...");
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no tiene una casa, cancelando...");
	}

	houseid = PlayerInfo[sellerid][pHouseKey];
	GetPlayerName(playerid, name, sizeof(name));
	House[houseid][Owned] = 1;
	House[houseid][OwnerSQLID] = PlayerInfo[playerid][pID];
	strmid(House[houseid][OwnerName], name, 0, strlen(name), 255);
	House[houseid][Locked] = 1;
	GivePlayerCash(playerid, -price);
    GivePlayerCash(sellerid, price);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(sellerid, 1052, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pHouseKey] = houseid;
    PlayerInfo[sellerid][pHouseKey] = 0;
    SaveHouse(houseid);
    PlayerPlayerActionMessage(sellerid, playerid, 15.0 , "toma las llaves y la escritura de su casa y se las entrega a");
  	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Felicidades, has comprado la casa por $%d! Usa /ayudacasa para ver los comandos disponibles.", price);
  	SendFMessage(sellerid, COLOR_LIGHTBLUE, "¡Felicitaciones, has vendido tu casa por $%d!", price);
  	KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	CancelHouseTransfer(playerid, 2);
	return 1;
}

CMD:casacancelar(playerid, params[])
{
	if(HouseOffer[playerid] == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo una casa.");
    	
 	KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	CancelHouseTransfer(playerid, 0);
	return 1;
}

TIMER:CancelHouseTransfer(playerid, reason)
{
	if(reason == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que no has respondido en 10 segundos.");
		SendClientMessage(HouseOffer[playerid], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 10 segundos.");
	}
	else
		if(reason == 0)
		{
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la oferta.");
			SendFMessage(HouseOffer[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la oferta.", GetPlayerNameEx(playerid));
		}
		
 	ResetHouseOffer(HouseOffer[playerid]);
 	ResetHouseOffer(playerid);
	return 1;
}

IsPlayerOnOutsideHouseDoor(playerid, house)
{
	if(PlayerToPoint(1.0, playerid, House[house][OutsideX], House[house][OutsideY], House[house][OutsideZ]) && House[house][OutsideWorld] == GetPlayerVirtualWorld(playerid))
		return 1;
	return 0;
}

IsPlayerOnInsideHouseDoor(playerid, house)
{
	if(PlayerToPoint(1.0, playerid, House[house][InsideX], House[house][InsideY], House[house][InsideZ]) && House[house][InsideWorld] == GetPlayerVirtualWorld(playerid))
		return 1;
	return 0;
}

CMD:puerta(playerid, params[])
{
    new house = PlayerInfo[playerid][pHouseKey],
	    houseincome = PlayerInfo[playerid][pHouseKeyIncome];

	if(house == 0 && houseincome == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes una casa ni alquilas una!");

	if(IsPlayerOnOutsideHouseDoor(playerid, house) || IsPlayerOnInsideHouseDoor(playerid, house))
	{
	    if(House[house][Locked] == 1)
		{
			House[house][Locked] = 0;
		    PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
		}
		else
		{
			House[house][Locked] = 1;
	        PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
		}
		return 1;
	}
	
	if(IsPlayerOnOutsideHouseDoor(playerid, houseincome) || IsPlayerOnInsideHouseDoor(playerid, houseincome))
	{
        if(House[houseincome][Locked] == 1)
		{
			House[houseincome][Locked] = 0;
		    PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
		}
		else
		{
			House[houseincome][Locked] = 1;
	        PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
		}
		return 1;
	}
	return 1;
}

//========================COMANDOS DE ALQUILER DE CASAS=========================

CMD:casaalquilar(playerid, params[])
{
    new name[MAX_PLAYER_NAME];
    
    if(PlayerInfo[playerid][pHouseKeyIncome] != 0)
		return 1;
		
    for(new h = 1; h < MAX_HOUSES; h++)
	{
	    if(IsPlayerOnOutsideHouseDoor(playerid, h))
	    {
			if(House[h][Income] == 0)
			{
			    if(House[h][OwnerSQLID] == PlayerInfo[playerid][pID])
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes alquilar tu propia casa!");
			    if(House[h][IncomePrice] <= 0)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta casa no tiene precio!, probablemente no está en alquiler.");
				if(GetPlayerCash(playerid) < House[h][IncomePrice])
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");

				PlayerInfo[playerid][pHouseKeyIncome] = h;
				House[h][Income] = 1;
				GetPlayerName(playerid, name, sizeof(name));
				strmid(House[h][Tenant], name, 0, strlen(name), 255);
				GivePlayerCash(playerid, -House[h][IncomePrice]);
				SetPlayerInterior(playerid, House[h][InsideInterior]);
				SetPlayerVirtualWorld(playerid, House[h][InsideWorld]);
				SetPlayerPos(playerid, House[h][InsideX], House[h][InsideY], House[h][InsideZ]);
				SetPlayerFacingAngle(playerid, House[h][InsideAngle]);
				SetCameraBehindPlayer(playerid);
				PlayRadioStreamForPlayer(playerid, House[h][Radio]);
				SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has alquilado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
			   	PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y este le entrega un par de llaves.");
				SaveHouse(h);
				return 1;
			}
		}
    }
	return 1;
}

CMD:casadesalquilar(playerid, params[])
{
    new house = PlayerInfo[playerid][pHouseKeyIncome],
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar alquilando una casa para utilizar este comando!");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de la casa que alquilas para utilizar este comando!");
	if(strcmp(House[house][Tenant], name, true) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, no figuras como inquilino de la casa (Consulta a un administrador).");

    if(House[house][Owned] == 0)
	    House[house][IncomePrice] = House[house][HousePrice] / 100;
	House[house][Locked] = 1;
	House[house][Income] = 0;
	strmid(House[house][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, COLOR_WHITE, "¡Has dejado de alquilar la casa!");
	PlayerInfo[playerid][pHouseKeyIncome] = 0;
	PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
	SaveHouse(house);
	return 1;
}

CMD:casaenalquiler(playerid, params[])
{
	new house = PlayerInfo[playerid][pHouseKey],
		price,
		string[128];

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
    if(sscanf(params, "i", price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casaenalquiler [Precio]");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para utilizar este comando!");
	if(House[house][OwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");
	if(House[house][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
	if(price > House[house][HousePrice] / 100)
	{
		format(string, sizeof(string), "[INFO]: El máximo permitido de alquiler es de %d.", House[house][HousePrice] / 100);
		SendClientMessage(playerid, COLOR_YELLOW2, string);
		return 1;
	}
	    
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Colocaste tu casa en alquiler por $%d, si alguien la alquila no podras utilizar el armario.", price);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} El pago del alquiler se realiza por cada payday del inquilino y lo recibirás al cobrar tu payday.");
	House[house][IncomePrice] = price;
	House[house][IncomeAccept] = 1;
	strmid(House[house][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	SaveHouse(house);
	return 1;
}

CMD:casasinalquiler(playerid, params[])
{
	new house = PlayerInfo[playerid][pHouseKey];

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para utilizar este comando!");
	if(House[house][OwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");
	if(House[house][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
		
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} Has sacado tu casa de alquiler: ya no se encuentra disponible para ser alquilada.");
	House[house][IncomePrice] = 0;
	House[house][IncomeAccept] = 0;
	strmid(House[house][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	SaveHouse(house);
	return 1;
}

CMD:casacontrato(playerid, params[])
{
	new house = PlayerInfo[playerid][pHouseKey];

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
	if(!IsPlayerOnOutsideHouseDoor(playerid, house))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para utilizar este comando!");
	if(House[house][OwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");
	if(House[house][Income] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa no tiene un inquilino.");

	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} El inquilino en breve será informado de que haz rescindido el contrato de alquiler...");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} ...dentro de 3 paydays será desalojada la vivienda.");
	House[house][Income] = 5;
	SaveHouse(house);
	return 1;
}

//=========================COMANDOS DE ADMIN DE CASAS===========================

CMD:acasas(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[COMANDOS]:{C8C8C8} /acinfo - /accrear - /acborrar - /acentrada - /acsalida - /actele - /acprecio - /acvender - /acinterior");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[COMANDOS]:{C8C8C8} /acalquilar - /acnoalquilar");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{C8C8C8}Seteando posiciones, deberás estar mirando hacia la puerta para que el ángulo de salida sea el correcto.");
	return 1;
}

CMD:acinterior(playerid, params[])
{
	new houseid,
	    interiorid,
	    string[128];
	    
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "ii", houseid, interiorid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acinterior [ID casa] [ID interior (1-42)]");
 	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
 	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	if(interiorid < 1 ||interiorid > 42)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El interior debe estar entre 1-42.");

	switch(interiorid)
	{
	    case 1:
		{
			House[houseid][InsideX] = 235.508994;
			House[houseid][InsideY] = 1189.169897;
			House[houseid][InsideZ] = 1080.339966;
			House[houseid][InsideInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
   		}
		case 2:
		{
			House[houseid][InsideX] = 225.756989;
			House[houseid][InsideY] = 1240.000000;
			House[houseid][InsideZ] = 1082.149902;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
  				}
		case 3:
		{
			House[houseid][InsideX] = 223.043991;
			House[houseid][InsideY] = 1289.259888;
			House[houseid][InsideZ] = 1082.199951;
			House[houseid][InsideInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 4:
		{
			House[houseid][InsideX] = 225.630997;
			House[houseid][InsideY] = 1022.479980;
			House[houseid][InsideZ] = 1084.069946;
			House[houseid][InsideInterior] = 7;
			format(string, sizeof string, "Casa: %d - descripción: muy grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 5:
		{
			House[houseid][InsideX] = 295.138977;
			House[houseid][InsideY] = 1474.469971;
			House[houseid][InsideZ] = 1080.519897;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 6:
		{
			House[houseid][InsideX] = 327.9199;
			House[houseid][InsideY] = 1477.7240;
			House[houseid][InsideZ] = 1084.4375;
			House[houseid][InsideAngle] = 177.3231 + 180;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 7:
	 	{
			House[houseid][InsideX] = 387.2003;
			House[houseid][InsideY] = 1471.7095;
			House[houseid][InsideZ] = 1080.1949;
			House[houseid][InsideAngle] = 270.7622 + 180;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD,string);
		}
		case 8:
		{
			House[houseid][InsideX] = 375.971985;
			House[houseid][InsideY] = 1417.269897;
			House[houseid][InsideZ] = 1081.409912;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 9:
		{
			House[houseid][InsideX] = 490.810974;
			House[houseid][InsideY] = 1401.489990;
			House[houseid][InsideZ] = 1080.339966;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
     	case 10:
		{
			House[houseid][InsideX] = 447.734985;
			House[houseid][InsideY] = 1400.439941;
			House[houseid][InsideZ] = 1084.339966;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
        case 11:
		{
			House[houseid][InsideX] = 227.722992;
			House[houseid][InsideY] = 1114.389893;
			House[houseid][InsideZ] = 1081.189941;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 12:
		{
			House[houseid][InsideX] = 260.983978;
			House[houseid][InsideY] = 1286.549927;
			House[houseid][InsideZ] = 1080.299927;
			House[houseid][InsideInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 13:
		{
			House[houseid][InsideX] = 221.666992;
			House[houseid][InsideY] = 1143.389893;
			House[houseid][InsideZ] = 1082.679932;
			House[houseid][InsideInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 14:
		{
			House[houseid][InsideX] = 27.132700;
			House[houseid][InsideY] = 1341.149902;
			House[houseid][InsideZ] = 1084.449951;
			House[houseid][InsideInterior] = 10;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 15:
		{
			House[houseid][InsideX] = -262.601990;
			House[houseid][InsideY] = 1456.619995;
			House[houseid][InsideZ] = 1084.449951;
			House[houseid][InsideInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: grande - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 16:
		{
			House[houseid][InsideX] = 22.778299;
			House[houseid][InsideY] = 1404.959961;
			House[houseid][InsideZ] = 1084.449951;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 17:
		{
			House[houseid][InsideX] = 140.278000;
			House[houseid][InsideY] = 1368.979980;
			House[houseid][InsideZ] = 1083.969971;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 18:
		{
			House[houseid][InsideX] = 234.045990;
			House[houseid][InsideY] = 1064.879883;
			House[houseid][InsideZ] = 1084.309937;
			House[houseid][InsideInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 19:
		{
			House[houseid][InsideX] = -68.294098;
			House[houseid][InsideY] = 1353.469971;
			House[houseid][InsideZ] = 1080.279907;
			House[houseid][InsideInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - ningún dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 20:
		{
			House[houseid][InsideX] = -285.548981;
			House[houseid][InsideY] = 1470.979980;
			House[houseid][InsideZ] = 1084.449951;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorio - 1 living room - 1 cocina", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 21:
		{
			House[houseid][InsideX] = -42.581997;
			House[houseid][InsideY] = 1408.109985;
			House[houseid][InsideZ] = 1084.449951;
			House[houseid][InsideInterior] = 8;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - ningún dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 22:
		{
			House[houseid][InsideX] = 83.0659;
			House[houseid][InsideY] = 1322.3271;
			House[houseid][InsideZ] = 1083.8662;
			House[houseid][InsideAngle] = 175.1501 + 180;
			House[houseid][InsideInterior] = 9;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 23:
		{
			House[houseid][InsideX] = 260.941986;
			House[houseid][InsideY] = 1238.509888;
			House[houseid][InsideZ] = 1084.259888;
			House[houseid][InsideInterior] = 9;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 24:
		{
			House[houseid][InsideX] = 244.411987;
			House[houseid][InsideY] = 305.032990;
			House[houseid][InsideZ] = 999.231995;
			House[houseid][InsideInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: Denise's Bedroom", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
     	case 25:
		{
			House[houseid][InsideX] = 271.884979;
			House[houseid][InsideY] = 306.631989;
			House[houseid][InsideZ] = 999.325989;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Katie's Bedroom", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
      	case 26:
		{
			House[houseid][InsideX] = 291.282990;
			House[houseid][InsideY] = 310.031982;
			House[houseid][InsideZ] = 999.154968;
			House[houseid][InsideInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: Helena's Bedroom (barn) - limited movement.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 27:
		{
			House[houseid][InsideX] = 302.181000;
			House[houseid][InsideY] = 300.722992;
			House[houseid][InsideZ] = 999.231995;
			House[houseid][InsideInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: Michelle's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 28:
		{
			House[houseid][InsideX] = 322.197998;
			House[houseid][InsideY] = 302.497986;
			House[houseid][InsideZ] = 999.231995;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Barbara's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 29:
		{
			House[houseid][InsideX] = 346.870025;
			House[houseid][InsideY] = 309.259033;
			House[houseid][InsideZ] = 999.155700;
			House[houseid][InsideInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: Millie's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 30:
		{
			House[houseid][InsideX] = 2496.049805;
			House[houseid][InsideY] = -1693.929932;
			House[houseid][InsideZ] = 1014.750000;
			House[houseid][InsideInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: CJ's Mom's House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 31:
		{
			House[houseid][InsideX] = 1263.079956;
			House[houseid][InsideY] = -785.308960;
			House[houseid][InsideZ] = 1091.959961;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Madd Dogg's Mansion (West door).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 32:
		{
			House[houseid][InsideX] = 2464.109863;
			House[houseid][InsideY] = -1698.659912;
			House[houseid][InsideZ] = 1013.509949;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Ryder's house.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 33:
		{
			House[houseid][InsideX] = 2526.459961;
			House[houseid][InsideY] = -1679.089966;
			House[houseid][InsideZ] = 1015.500000;
			House[houseid][InsideInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: Sweet's House (South side of house is fucked).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 34:
		{
			House[houseid][InsideX] = 2543.659912;
			House[houseid][InsideY] = -1303.629883;
			House[houseid][InsideZ] = 1025.069946;
			House[houseid][InsideInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Big Smoke's Crack Factory (Ground Floor).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 35:
		{
			House[houseid][InsideX] = 744.542969;
			House[houseid][InsideY] = 1437.669922;
			House[houseid][InsideZ] = 1102.739990;
			House[houseid][InsideInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: Fanny Batter's Whore House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
     	case 36:
  		{
			House[houseid][InsideX] = 964.106995;
			House[houseid][InsideY] = -53.205498;
			House[houseid][InsideZ] = 1001.179993;
			House[houseid][InsideInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: Tiger Skin Rug Brothel.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 37:
		{
			House[houseid][InsideX] = 2350.339844;
			House[houseid][InsideY] = -1181.649902;
			House[houseid][InsideZ] = 1028.000000;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Burning Desire Gang House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 38:
		{
			House[houseid][InsideX] = 2807.619873;
			House[houseid][InsideY] = -1171.899902;
			House[houseid][InsideZ] = 1025.579956;
			House[houseid][InsideInterior] = 8;
			format(string, sizeof string, "Casa: %d - descripción: Colonel Furhberger's House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 39:
		{
			House[houseid][InsideX] = 318.564972;
			House[houseid][InsideY] = 1118.209961;
			House[houseid][InsideZ] = 1083.979980;
			House[houseid][InsideInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Crack Den.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 40:
		{
			House[houseid][InsideX] = 2324.419922;
			House[houseid][InsideY] = -1147.539917;
			House[houseid][InsideZ] = 1050.719971;
			House[houseid][InsideInterior] = 12;
			format(string, sizeof string, "Casa: %d - descripción: Unused Safe House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 41:
		{
			House[houseid][InsideX] = 446.622986;
			House[houseid][InsideY] = 509.318970;
			House[houseid][InsideZ] = 1001.419983;
			House[houseid][InsideInterior] = 12;
			format(string, sizeof string, "Casa: %d - descripción: habitación motel Budget Inn.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 42:
		{
			House[houseid][InsideX] = 2216.339844;
			House[houseid][InsideY] = -1150.509888;
			House[houseid][InsideZ] = 1025.799927;
			House[houseid][InsideInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: Jefferson Motel. (REALLY EXPENSIVE)", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
	}
	SaveHouse(houseid);
	return 1;
}

CMD:acprecio(playerid, params[])
{
	new houseid,
		price,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "ii", houseid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acprecio [ID casa] [Precio]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	if(price < 0 || price > 10000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige un precio de $0 a $10.000.000.");
	    
	House[houseid][HousePrice] = price;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el precio de la casa %d ha sido ajustado a $%d.", houseid, price);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	ResetLocker(houseid); // Al cambiar el precio se cambian los slots de armario, por ende reseteamos todo para evitar bugs.
	SaveHouse(houseid);
	return 1;
}

CMD:acvender(playerid, params[])
{
	new houseid,
		string[128];
	
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acvender [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    

	foreach(new i : Player)
	{
		if(PlayerInfo[i][pHouseKey] == houseid)
			PlayerInfo[i][pHouseKey] = 0;
		if(PlayerInfo[i][pHouseKeyIncome] == houseid)
			PlayerInfo[i][pHouseKeyIncome] = 0;
	}
	format(string, sizeof(string), "UPDATE `accounts` SET `HouseKey` = 0 WHERE `HouseKey` = %d", houseid);
	mysql_function_query(dbHandle, string, false, "", "");
	format(string, sizeof(string), "UPDATE `accounts` SET `HouseKeyIncome` = 0 WHERE `HouseKeyIncome` = %d", houseid);
	mysql_function_query(dbHandle, string, false, "", "");

	House[houseid][Owned] = 0;
	House[houseid][OwnerSQLID] = 0;
	strmid(House[houseid][OwnerName], "Ninguno", 0, strlen("Ninguno"), 255);
	House[houseid][Locked] = 1;
	House[houseid][Money] = 0;
	House[houseid][Marijuana] = 0;
	House[houseid][LSD] = 0;
	House[houseid][Ecstasy] = 0;
	House[houseid][Cocaine] = 0;
	House[houseid][Radio] = 0;
    House[houseid][IncomePrice] = 0;
    House[houseid][IncomePriceAdd] = 0;
	House[houseid][IncomeAccept] = 0;
	House[houseid][Income] = 0;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	ResetLocker(houseid);
	SaveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la casa %d ha sido vendida.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:accrear(playerid, params[])
{
	new price,
		Float:angle,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "i", price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /accrear [Precio de la casa]");
	if(price < 1 || price > 10000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige un precio de $1 a $10.000.000.");

	for(new i = 1; i < MAX_HOUSES; i++)
	{
		if(House[i][Created] == 0)
		{
			GetPlayerFacingAngle(playerid, angle);
			GetPlayerPos(playerid, House[i][OutsideX], House[i][OutsideY], House[i][OutsideZ]);
			House[i][OutsideAngle] = angle + 180;
			House[i][OutsideInterior] = GetPlayerInterior(playerid);
			House[i][OutsideWorld] = GetPlayerVirtualWorld(playerid);
			// Se setea por default un interior de casa basico
			House[i][InsideX] = 235.508994;
			House[i][InsideY] = 1189.169897;
			House[i][InsideZ] = 1080.339966;
			House[i][InsideInterior] = 3;
			House[i][InsideWorld] = 15000 + i;
			House[i][HousePrice] = price;
			House[i][Locked] = 1;
			strmid(House[i][OwnerName], "Ninguno", 0, strlen("Ninguno"), 255);
			CreateHouse(i);
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} has creado la casa ID %d. Se le ha asignado un interior básico por default.", i);
            SendClientMessage(playerid, COLOR_ADMINCMD, string);
			return 1;
		}
	}

	format(string, sizeof(string), "Error: la casa no pudo ser creada porque se ha alcanzado el máximo de casas en el servidor (%d).", MAX_HOUSES);
    SendClientMessage(playerid, COLOR_YELLOW2, string);
	return 1;
}

CMD:acborrar(playerid, params[])
{
	new houseid,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acborrar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");

	foreach(new i : Player)
	{
		if(PlayerInfo[i][pHouseKey] == houseid)
			PlayerInfo[i][pHouseKey] = 0;
		if(PlayerInfo[i][pHouseKeyIncome] == houseid)
			PlayerInfo[i][pHouseKeyIncome] = 0;
	}
	
	format(string, sizeof(string), "UPDATE `accounts` SET `HouseKey` = 0 WHERE `HouseKey` = %d", houseid);
	mysql_function_query(dbHandle, string, false, "", "");
	format(string, sizeof(string), "UPDATE `accounts` SET `HouseKeyIncome` = 0 WHERE `HouseKeyIncome` = %d", houseid);
	mysql_function_query(dbHandle, string, false, "", "");

	ResetLocker(houseid);
	DeleteHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la casa %d ha sido BORRADA.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:acentrada(playerid, params[])
{
	new houseid,
		Float:angle,
		string[128];
		
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acentrada [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    
 	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ]);
	House[houseid][OutsideInterior] = GetPlayerInterior(playerid);
	House[houseid][OutsideWorld] = GetPlayerVirtualWorld(playerid);
	House[houseid][OutsideAngle] = angle + 180;
	SaveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la entrada de la casa %d ha sido cambiada a tu posición, interior y VWorld.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:acsalida(playerid, params[])
{
	new houseid,
		Float:angle,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acsalida [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerPos(playerid, House[houseid][InsideX], House[houseid][InsideY], House[houseid][InsideZ]);
	House[houseid][InsideInterior] = GetPlayerInterior(playerid);
	House[houseid][InsideAngle] = angle + 180;
	SaveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la salida de la casa %d ha sido cambiada a tu posición y a tu interior.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
 	return 1;
}

CMD:acinfo(playerid, params[])
{
	new id;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acinfo [ID casa]");
	if(id < 1 || id >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[id][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");

	SendFMessage(playerid, COLOR_WHITE, "=======================[Casa %d]=======================", id);
	SendFMessage(playerid, COLOR_WHITE, "- Tiene dueño: %d", House[id][Owned]);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño SQLID: %d", House[id][OwnerSQLID]);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s", House[id][OwnerName]);
	SendFMessage(playerid, COLOR_WHITE, "- Costo de compra: $%d", House[id][HousePrice]);
	SendFMessage(playerid, COLOR_WHITE, "- Dinero: %d", House[id][Money]);
 	SendFMessage(playerid, COLOR_WHITE, "- Cerrada: %d", House[id][Locked]);
 	SendFMessage(playerid, COLOR_WHITE, "- Inquilino: %s", House[id][Tenant]);
 	SendFMessage(playerid, COLOR_WHITE, "- Casa alquilada: %d", House[id][Income]);
 	SendFMessage(playerid, COLOR_WHITE, "- Casa en alquiler: %d", House[id][IncomeAccept]);
 	SendFMessage(playerid, COLOR_WHITE, "- Costo de alquiler: $%d", House[id][IncomePrice]);
 	SendFMessage(playerid, COLOR_WHITE, "- Ganancias: $%d", House[id][IncomePriceAdd]);
	return 1;
}

CMD:actele(playerid, params[])
{
	new houseid;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /actele [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    
	SetPlayerInterior(playerid, House[houseid][OutsideInterior]);
	SetPlayerVirtualWorld(playerid, House[houseid][OutsideWorld]);
	SetPlayerPos(playerid, House[houseid][OutsideX], House[houseid][OutsideY], House[houseid][OutsideZ]);
	return 1;
}

CMD:acalquilar(playerid, params[])
{
	new houseid,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 4)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	if(House[houseid][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
	
	House[houseid][IncomePrice] = House[houseid][HousePrice] / 100;
	House[houseid][IncomeAccept] = 1;
	House[houseid][Income] = 0;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el precio de alquiler de la casa %d ha sido ajustado a $%d.", houseid, House[houseid][IncomePrice]);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	SaveHouse(houseid);
	return 1;
}

CMD:acnoalquilar(playerid, params[])
{
	new houseid,
		string[128];

	if(PlayerInfo[playerid][pAdmin] < 4)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acnoalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");

	foreach(new i : Player)
	{
		if(PlayerInfo[i][pHouseKeyIncome] == houseid)
			PlayerInfo[i][pHouseKeyIncome] = 0;
	}
	
	format(string, sizeof(string), "UPDATE `accounts` SET `HouseKeyIncome` = 0 WHERE `HouseKeyIncome` = %d", houseid);
	mysql_function_query(dbHandle, string, false, "", "");
		
    House[houseid][IncomePrice] = 0;
	House[houseid][IncomeAccept] = 0;
	House[houseid][IncomePriceAdd] = 0;
	House[houseid][Income] = 0;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la casa %d ya no está disponible para ser rentada.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	SaveHouse(houseid);
	return 1;
}
