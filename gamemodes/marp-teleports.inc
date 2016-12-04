#if defined _marp_teleports_included
	#endinput
#endif
#define _marp_teleports_included

/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||   Sistema dinámico para creación IG de teleports    ||||||||||||||
|||||||||||||        	Pheek Gaming Latinoamérica                ||||||||||||||
|||||||||||||           			2016              			  ||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// =============================== CONSTANTES ==================================

#define MAX_TELEPORTS               1000

#define TYPE_NORMAL                 0           // Teleport normal.
#define TYPE_HOUSE                  1           // Entrada principal a una casa.
#define TYPE_BUSINESS               2           // Entrada principal a un negocio.
#define TYPE_BUILDING               3           // Entrada principal a un edificio.

// ================================ FUNCIONES ==================================

forward LoadTeleports();
forward OnTeleportDataLoad(ID);
forward SaveTeleport(ID);
forward InsertTeleportData(ID);
forward DeleteTeleport(ID);
forward CreateTeleport(Float:FX, Float:FY, Float:FZ, Float:FA, FInt, FVW, Float:SX, Float:SY, Float:SZ, Float:SA, SInt, SVW, FHouse, FBiz, FBuilding, FPM, SPM, Type);
forward ResetTeleport(ID);
forward GetTeleportID(ID, type);
forward GetFirstNonCreatedTeleport();
forward LoadTeleportPickup(ID);
forward EnterTeleport(playerid, tpid);
forward LeaveTeleport(playerid, tpid);

//=========================== VARIABLES INTERNAS ===============================

enum TeleportParams {
	Created,
	Float:FirstX,
	Float:FirstY,
	Float:FirstZ,
	Float:FirstAngle,
	FirstInt,
	FirstVW,
	FirstHouse,
	FirstBiz,
	FirstBuilding,
	Float:SecondX,
	Float:SecondY,
	Float:SecondZ,
	Float:SecondAngle,
	SecondInt,
	SecondVW,
	SecondHouse,
	SecondBiz,
	SecondBuilding,
	FirstPickup,
	FirstPickupModel,
	SecondPickup,
	SecondPickupModel,
	Type
}

new Teleport[MAX_TELEPORTS][TeleportParams];

// =========================== MANEJO DE DATOS SQL =============================

stock LoadTeleports()
{
	new query[128];
	
	for(new tID; tID < MAX_TELEPORTS; tID++)
	{
	    format(query, sizeof(query),"SELECT * FROM `teleports_info` WHERE `tID` = %d LIMIT 1", tID);
		mysql_function_query(dbHandle, query, true, "OnTeleportDataLoad", "i", tID);
		LoadTeleportPickup(tID);
	}
	print("[INFO] Teleports cargados.");
	return 1;
}

public OnTeleportDataLoad(ID)
{
   	new result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows)
	{
		cache_get_field_content(0, "FirstX", result);			Teleport[ID][FirstX]    		= floatstr(result);
		cache_get_field_content(0, "FirstY", result); 			Teleport[ID][FirstY] 			= floatstr(result);
		cache_get_field_content(0, "FirstZ", result); 			Teleport[ID][FirstZ] 			= floatstr(result);
		cache_get_field_content(0, "FirstAngle", result); 		Teleport[ID][FirstAngle]		= floatstr(result);
		cache_get_field_content(0, "FirstInt", result); 		Teleport[ID][FirstInt] 			= strval(result);
		cache_get_field_content(0, "FirstVW", result); 			Teleport[ID][FirstVW] 			= strval(result);
		cache_get_field_content(0, "FirstHouse", result); 		Teleport[ID][FirstHouse]		= strval(result);
		cache_get_field_content(0, "FirstBiz", result); 		Teleport[ID][FirstBiz]			= strval(result);
		cache_get_field_content(0, "FirstBuilding", result); 	Teleport[ID][FirstBuilding]		= strval(result);

		cache_get_field_content(0, "SecondX", result);			Teleport[ID][SecondX]    		= floatstr(result);
		cache_get_field_content(0, "SecondY", result); 			Teleport[ID][SecondY] 			= floatstr(result);
		cache_get_field_content(0, "SecondZ", result); 			Teleport[ID][SecondZ] 			= floatstr(result);
		cache_get_field_content(0, "SecondAngle", result); 		Teleport[ID][SecondAngle] 		= floatstr(result);
		cache_get_field_content(0, "SecondInt", result); 		Teleport[ID][SecondInt]			= strval(result);
		cache_get_field_content(0, "SecondVW", result);			Teleport[ID][SecondVW] 			= strval(result);
		cache_get_field_content(0, "SecondHouse", result); 		Teleport[ID][SecondHouse]		= strval(result);
		cache_get_field_content(0, "SecondBiz", result); 		Teleport[ID][SecondBiz]			= strval(result);
		cache_get_field_content(0, "SecondBuilding", result); 	Teleport[ID][SecondBuilding]	= strval(result);

		cache_get_field_content(0, "FirstPickup", result);		Teleport[ID][FirstPickupModel]		= strval(result);
		cache_get_field_content(0, "SecondPickup", result);		Teleport[ID][SecondPickupModel]		= strval(result);
		cache_get_field_content(0, "Type", result); 			Teleport[ID][Type]				= strval(result);

	}
	return 1;
}

stock SaveTeleport(ID)
{
	new query[768];
	
	if(Teleport[ID][Loaded] == 0) return 1;
	
	format(query, sizeof(query), "UPDATE teleports_info SET");
	
	format(query, sizeof(query), "%s `FirstX`=%f, `FirstY`=%f, `FirstZ`=%f, `FirstAngle`=%f, `FirstInt`=%d, `FirstVW`=%d,",
	query,
	Teleport[ID][FirstX],
	Teleport[ID][FirstY],
	Teleport[ID][FirstZ],
	Teleport[ID][FirstAngle],
	Teleport[ID][FirstInt],
	Teleport[ID][FirstVW]
	);
	
	format(query, sizeof(query), "%s `SecondX`=%f, `SecondY`=%f, `SecondZ`=%f, `SecondAngle`=%f, `SecondInt`=%d, `SecondVW`=%d,",
	query,
	Teleport[ID][SecondX],
	Teleport[ID][SecondY],
	Teleport[ID][SecondZ],
	Teleport[ID][SecondAngle],
	Teleport[ID][SecondInt],
	Teleport[ID][SecondVW]
	);
	
	format(query, sizeof(query), "%s `FirstHouse`=%d, `FirstBiz`=%d, `FirstBuilding`=%d, `SecondHouse`=%d, `SecondBiz`=%d, `SecondBuilding`=%d,",
	query,
	Teleport[ID][FirstHouse],
	Teleport[ID][FirstBiz],
	Teleport[ID][FirstBuilding],
	Teleport[ID][SecondHouse],
	Teleport[ID][SecondBiz],
	Teleport[ID][SecondBuilding]
	
	format(query, sizeof(query), "%s `FirstPickup`=%d,`SecondPickup`=%d, `Type`=%d",
	query,
	Teleport[ID][FirstPickupModel],
	Teleport[ID][SecondPickupModel],
	Teleport[ID][Type]
	);
	
	format(query, sizeof(query), "%s WHERE `tID`=%d LIMIT 1", ID);
	);
	
	
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

stock InsertTeleportData(ID)
{
	new query[512];
	
	format(query, sizeof(query), "INSERT INTO `teleports_info`");

	format(query, sizeof(query), "%s (tID, FirstX, FirstY, FirstZ, FirstAngle, FirstInt, FirstVW, SecondX, SecondY, SecondZ, SecondAngle, SecondInt, SecondVW, FirstHouse, FirstBiz, FirstBuilding, SecondHouse, SecondBiz, SecondBuilding, FirstPickup, SecondPickup, Type)", query);
	
	format(query, sizeof(query), "%s VALUES (%d, %f, %f, %f, %f, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
	query,
	ID,
	Teleport[ID][FirstX],
	Teleport[ID][FirstY],
	Teleport[ID][FirstZ],
	Teleport[ID][FirstAngle],
	Teleport[ID][FirstInt],
	Teleport[ID][FirstVW],
	Teleport[ID][SecondX],
	Teleport[ID][SecondY],
	Teleport[ID][SecondZ],
	Teleport[ID][SecondAngle],
	Teleport[ID][SecondInt],
	Teleport[ID][SecondVW],
	Teleport[ID][FirstHouse],
	Teleport[ID][FirstBiz],
	Teleport[ID][FirstBuilding],
	Teleport[ID][SecondHouse],
	Teleport[ID][SecondBiz],
	Teleport[ID][SecondBuilding],
	Teleport[ID][FirstPickupModel],
	Teleport[ID][SecondPickupModel],
	Teleport[ID][Type]
	);
	
	mysql_function_query(dbHandle, query, false, "", "");
	Teleport[ID][Created] = 1;
	LoadTeleportPickup(ID);
	return 1;
}

stock DeleteTeleport(ID)
{
	new query[64];
	
	format(query, sizeof(query), "DELETE FROM `teleports_info` WHERE `tID` = %d", ID);
 	mysql_function_query(dbHandle, query, false, "", "");
 	
 	ResetTeleport(ID);
 	return 1;
}

// ================== OTRAS FUNCIONES / DATOS EN VARIABLES =====================

stock CreateTeleport(Float:FX, Float:FY, Float:FZ, Float:FA, FInt, FVW, Float:SX, Float:SY, Float:SZ, Float:SA, SInt, SVW, FHouse, FBiz, FBuilding, FPM, SPM, Type)
{
	new tID = GetFirstNonCreatedTeleport();
	
	if(tID == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No hay más espacio para teleports. REPORTAR BUG.");
		
	Teleport[tID][FirstX] = FX;
	Teleport[tID][FirstY] = FY;
	Teleport[tID][FirstZ] = FZ;
	Teleport[tID][FirstAngle] = FA;
	Teleport[tID][FirstInt] = FInt;
	Teleport[tID][FirstVW] = FVW;
	Teleport[tID][FirstHouse] = FHouse;
	Teleport[tID][FirstBiz] = FBiz;
	Teleport[tID][FirstBuilding] = FBuilding;
	Teleport[tID][SecondX] = SX;
	Teleport[tID][SecondY] = SY;
	Teleport[tID][SecondZ] = SZ;
	Teleport[tID][SecondAngle] = SA;
	Teleport[tID][SecondInt] = SInt;
	Teleport[tID][SecondVW] = SVW;
	Teleport[tID][SecondHouse] = SHouse;
	Teleport[tID][SecondBiz] = SBiz;
	Teleport[tID][SecondBuilding] = SBuilding;
	Teleport[tID][FirstPickupModel] = FPM;
	Teleport[tID][SecondPickupModel] = SPM;
	Teleport[tID][Type] = Type;
	InsertTeleportData(tID);
	LoadTeleportPickup(ID);
}

stock ResetTeleport(ID)
{
	Teleport[ID][Created] = 0;
	Teleport[ID][FirstX] = 0.0;
	Teleport[ID][FirstY] = 0.0;
	Teleport[ID][FirstZ] = 0.0;
	Teleport[ID][FirstAngle] = 0.0;
	Teleport[ID][FirstInt] = 0;
	Teleport[ID][FirstVW] = 0;
	Teleport[ID][FirstHouse] = 0;
	Teleport[ID][FirstBiz] = 0;
	Teleport[ID][FirstBuilding] = 0;
	Teleport[ID][SecondX] = 0.0;
	Teleport[ID][SecondY] = 0.0;
	Teleport[ID][SecondZ] = 0.0;
	Teleport[ID][SecondAngle] = 0.0;
	Teleport[ID][SecondInt] = 0;
	Teleport[ID][SecondVW] = 0;
	Teleport[ID][SecondHouse] = 0;
	Teleport[ID][SecondBiz] = 0;
	Teleport[ID][SecondBuilding] = 0;
	Teleport[ID][FirstPickupModel] = 0;
	Teleport[ID][Type] = TYPE_NORMAL;
	return 1;
}

stock GetTeleportID(ID, type)
{
	switch(type)
	{
	    case TYPE_HOUSE: return House[ID][EntrancePickupSQLID]
	    case TYPE_BUSINESS: return Business[ID][EntrancePickupSQLID]
	    case TYPE_BUILDING: return Building[ID][EntrancePickupSQLID]
	}
	return 1;
}

stock GetFirstNonCreatedTeleport()
{
	for(new i = 1; i < MAX_TELEPORTS; i++)
	{
	    if(Teleport[i][Created] == 1)
	        continue;
		else
		    return i;
	}
	return 0;
}

stock LoadTeleportPickup(ID)
{
	Teleport[ID][FirstPickup] = CreateDynamicPickup(Teleport[ID][FirstPickupModel], 1,
	Teleport[ID][FirstX],
	Teleport[ID][FirstY],
	Teleport[ID][FirstZ],
	Teleport[ID][FirstVW]);
	
	Teleport[ID][SecondPickup] = CreateDynamicPickup(Teleport[ID][SecondPickupModel], 1,
	Teleport[ID][SecondX],
	Teleport[ID][SecondY],
	Teleport[ID][SecondZ],
	Teleport[ID][SecondVW]);
	
	return 1;
}

stock EnterTeleport(playerid, tpid)
{
	switch(TeleportInfo[tpid][Type])
	{
		case TYPE_HOUSE: PlayerInfo[playerid][pCurrentHouse] = TeleportInfo[tpid][SecondHouse];
		case TYPE_BUSINESS: PlayerInfo[playerid][pCurrentBiz] = TeleportInfo[tpid][SecondBiz];
		case TYPE_BUILDING: PlayerInfo[playerid][pCurrentBuilding] = TeleportInfo[tpid][SecondBuilding];
	}
	
	SetPlayerPos(playerid, TeleportInfo[tpid][SecondX], TeleportInfo[tpid][SecondY], TeleportInfo[tpid][SecondZ]);
	SetPlayerFacingAngle(playerid, TeleportInfo[tpid][SecondAngle]);
	SetPlayerInterior(playerid, TeleportInfo[tpid][SecondInt]);
	SetPlayerVirtualWorld(playerid, TeleportInfo[tpid][SecondVW]);
	return 1;
}

stock LeaveTeleport(playerid, tpid)
{
	switch(TeleportInfo[tpid][Type])
	{
		case TYPE_HOUSE: PlayerInfo[playerid][pCurrentHouse] = TeleportInfo[tpid][FirstHouse];
		case TYPE_BUSINESS: PlayerInfo[playerid][pCurrentBiz] = TeleportInfo[tpid][FirstBiz];
		case TYPE_BUILDING: PlayerInfo[playerid][pCurrentBuilding] = TeleportInfo[tpid][FirstBuilding];
	}
	
	SetPlayerPos(playerid, TeleportInfo[tpid][FirstX], TeleportInfo[tpid][FirstY], TeleportInfo[tpid][FirstZ]);
	SetPlayerFacingAngle(playerid, TeleportInfo[tpid][FirstAngle]);
	SetPlayerInterior(playerid, TeleportInfo[tpid][FirstInt]);
	SetPlayerVirtualWorld(playerid, TeleportInfo[tpid][FirstVW]);
	return 1;
}

// ====================== Comandos administrativos =============================

CMD:atcrear(playerid, params[])
{
	new Float:pos[3], Float:Angle, pickup[2];
	
	if(sscanf(params, "ii", pickup[0], pickup[1]))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /atcrear [modelo de pickup entrada] [modelo de pickup salida]");
		
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, Angle);

	CreateTeleport(pos[0], pos[1], pos[2], Angle+180, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), pos[0], pos[1], pos[2], Angle+180,
	GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), 0, 0, 0, pickup[0], pickup[1], TYPE_NORMAL);
	return 1;
}

