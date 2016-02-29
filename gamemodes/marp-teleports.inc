#if defined _marp_teleports_included
	#endinput
#endif
#define _marp_teleports_included

/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||   Sistema dinámico para creación IG de teleports    ||||||||||||||
|||||||||||||        	Casas | Negocios | Edificios              ||||||||||||||
|||||||||||||           			2016              			  ||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

#define MAX_TELEPORTS               1000

#define TYPE_NORMAL                 0           // Teleport normal.
#define TYPE_HOUSE                  1           // Entrada principal a una casa.
#define TYPE_BUSINESS               2           // Entrada principal a un negocio.
#define TYPE_BUILDING               3           // Entrada principal a un edificio.

forward OnTeleportDataLoad(ID);

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
	FirstPickupModel,
	SecondPickupModel,
	Type
}

new TeleportInfo[MAX_TELEPORTS][TeleportParams];

// =========================== MANEJO DE DATOS SQL =============================

stock LoadTeleports()
{
	new query[128];
	
	for(new tID; tID < MAX_TELEPORTS; tID++)
	{
	    format(query, sizeof(query),"SELECT * FROM `pickups_info` WHERE `tID` = %d LIMIT 1", tID);
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
		cache_get_field_content(0, "FirstX", result);			TeleportInfo[ID][FirstX]    		= floatstr(result);
		cache_get_field_content(0, "FirstY", result); 			TeleportInfo[ID][FirstY] 			= floatstr(result);
		cache_get_field_content(0, "FirstZ", result); 			TeleportInfo[ID][FirstZ] 			= floatstr(result);
		cache_get_field_content(0, "FirstAngle", result); 		TeleportInfo[ID][FirstAngle]		= floatstr(result);
		cache_get_field_content(0, "FirstInt", result); 		TeleportInfo[ID][FirstInt] 			= strval(result);
		cache_get_field_content(0, "FirstVW", result); 			TeleportInfo[ID][FirstVW] 			= strval(result);
		cache_get_field_content(0, "FirstHouse", result); 		TeleportInfo[ID][FirstHouse]		= strval(result);
		cache_get_field_content(0, "FirstBiz", result); 		TeleportInfo[ID][FirstBiz]			= strval(result);
		cache_get_field_content(0, "FirstBuilding", result); 	TeleportInfo[ID][FirstBuilding]		= strval(result);

		cache_get_field_content(0, "SecondX", result);			TeleportInfo[ID][SecondX]    		= floatstr(result);
		cache_get_field_content(0, "SecondY", result); 			TeleportInfo[ID][SecondY] 			= floatstr(result);
		cache_get_field_content(0, "SecondZ", result); 			TeleportInfo[ID][SecondZ] 			= floatstr(result);
		cache_get_field_content(0, "SecondAngle", result); 		TeleportInfo[ID][SecondAngle] 		= floatstr(result);
		cache_get_field_content(0, "SecondInt", result); 		TeleportInfo[ID][SecondInt]			= strval(result);
		cache_get_field_content(0, "SecondVW", result);			TeleportInfo[ID][SecondVW] 			= strval(result);
		cache_get_field_content(0, "SecondHouse", result); 		TeleportInfo[ID][SecondHouse]		= strval(result);
		cache_get_field_content(0, "SecondBiz", result); 		TeleportInfo[ID][SecondBiz]			= strval(result);
		cache_get_field_content(0, "SecondBuilding", result); 	TeleportInfo[ID][SecondBuilding]	= strval(result);

		cache_get_field_content(0, "FirstPickupModel", result);	TeleportInfo[ID][FirstPickupModel]	= strval(result);
		cache_get_field_content(0, "SecondPickupModel", result);TeleportInfo[ID][SecondPickupModel]	= strval(result);
		cache_get_field_content(0, "Type", result); 			TeleportInfo[ID][Type]				= strval(result);

	}
	return 1;
}

stock SaveTeleport(ID)
{
	new query[768];
	
	if(TeleportInfo[ID][Loaded] == 0) return 1;
	
	format(query, sizeof(query), "UPDATE pickups_info SET");
	
	format(query, sizeof(query), "%s `FirstX`=%f, `FirstY`=%f, `FirstZ`=%f, `FirstAngle`=%f, `FirstInt`=%d, `FirstVW`=%d,",
	query,
	TeleportInfo[ID][FirstX],
	TeleportInfo[ID][FirstY],
	TeleportInfo[ID][FirstZ],
	TeleportInfo[ID][FirstAngle],
	TeleportInfo[ID][FirstInt],
	TeleportInfo[ID][FirstVW]
	);
	
	format(query, sizeof(query), "%s `SecondX`=%f, `SecondY`=%f, `SecondZ`=%f, `SecondAngle`=%f, `SecondInt`=%d, `SecondVW`=%d,",
	query,
	TeleportInfo[ID][SecondX],
	TeleportInfo[ID][SecondY],
	TeleportInfo[ID][SecondZ],
	TeleportInfo[ID][SecondAngle],
	TeleportInfo[ID][SecondInt],
	TeleportInfo[ID][SecondVW]
	);
	
	format(query, sizeof(query), "%s `FirstHouse`=%d, `FirstBiz`=%d, `FirstBuilding`=%d, `SecondHouse`=%d, `SecondBiz`=%d, `SecondBuilding`=%d,",
	query,
	TeleportInfo[ID][FirstHouse],
	TeleportInfo[ID][FirstBiz],
	TeleportInfo[ID][FirstBuilding],
	TeleportInfo[ID][SecondHouse],
	TeleportInfo[ID][SecondBiz],
	TeleportInfo[ID][SecondBuilding]
	
	format(query, sizeof(query), "%s `FirstPickupModel`=%d,`SecondPickupModel`=%d, `Type`=%d",
	query,
	TeleportInfo[ID][FirstPickupModel],
	TeleportInfo[ID][SecondPickupModel],
	TeleportInfo[ID][Type]
	);
	
	format(query, sizeof(query), "%s WHERE `tID`=%d LIMIT 1", ID);
	);
	
	
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

stock InsertTeleportData(ID)
{
	new query[512];
	
	format(query, sizeof(query), "INSERT INTO `pickups_info`");

	format(query, sizeof(query), "%s (FirstX, FirstY, FirstZ, FirstAngle, FirstInt, FirstVW, SecondX, SecondY, SecondZ, SecondAngle, SecondInt, SecondVW, FirstHouse, FirstBiz, FirstBuilding, SecondHouse, SecondBiz, SecondBuilding, FirstPickupModel, SecondPickupModel, Type)", query);
	
	format(query, sizeof(query), "%s VALUES (%f, %f, %f, %f, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
	query,
	TeleportInfo[ID][FirstX],
	TeleportInfo[ID][FirstY],
	TeleportInfo[ID][FirstZ],
	TeleportInfo[ID][FirstAngle],
	TeleportInfo[ID][FirstInt],
	TeleportInfo[ID][FirstVW],
	TeleportInfo[ID][SecondX],
	TeleportInfo[ID][SecondY],
	TeleportInfo[ID][SecondZ],
	TeleportInfo[ID][SecondAngle],
	TeleportInfo[ID][SecondInt],
	TeleportInfo[ID][SecondVW],
	TeleportInfo[ID][FirstHouse],
	TeleportInfo[ID][FirstBiz],
	TeleportInfo[ID][FirstBuilding],
	TeleportInfo[ID][SecondHouse],
	TeleportInfo[ID][SecondBiz],
	TeleportInfo[ID][SecondBuilding],
	TeleportInfo[ID][FirstPickupModel],
	TeleportInfo[ID][SecondPickupModel],
	TeleportInfo[ID][Type]
	);
	
	mysql_function_query(dbHandle, query, false, "", "");
	TeleportInfo[ID][Created] = 1;
	LoadTeleportPickup(ID);
	return 1;
}

stock DeleteTeleport(ID)
{
	new query[64];
	
	format(query, sizeof(query), "DELETE FROM `pickups_info` WHERE `tID` = %d", ID);
 	mysql_function_query(dbHandle, query, false, "", "");
 	
 	ResetTeleportInfo(ID);
 	return 1;
}

// =================== Otras funciones / Datos "locales" =======================

stock CreateTeleport(Float:FX, Float:FY, Float:FZ, Float:FA, FInt, FVW, Float:SX, Float:SY, Float:SZ, Float:SA, SInt, SVW, FHouse, FBiz, FBuilding, FPM, SPM, Type)
{
	new tID = GetFirstNonCreatedTeleport();
	
	if(tID == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No hay más espacio para teleports. REPORTAR A UN SCRIPTER.");
		
	TeleportInfo[tID][FirstX] = FX;
	TeleportInfo[tID][FirstY] = FY;
	TeleportInfo[tID][FirstZ] = FZ;
	TeleportInfo[tID][FirstAngle] = FA;
	TeleportInfo[tID][FirstInt] = FInt;
	TeleportInfo[tID][FirstVW] = FVW;
	TeleportInfo[tID][FirstHouse] = FHouse;
	TeleportInfo[tID][FirstBiz] = FBiz;
	TeleportInfo[tID][FirstBuilding] = FBuilding;
	TeleportInfo[tID][SecondX] = SX;
	TeleportInfo[tID][SecondY] = SY;
	TeleportInfo[tID][SecondZ] = SZ;
	TeleportInfo[tID][SecondAngle] = SA;
	TeleportInfo[tID][SecondInt] = SInt;
	TeleportInfo[tID][SecondVW] = SVW;
	TeleportInfo[tID][SecondHouse] = SHouse;
	TeleportInfo[tID][SecondBiz] = SBiz;
	TeleportInfo[tID][SecondBuilding] = SBuilding;
	TeleportInfo[tID][FirstPickupModel] = FPM;
	TeleportInfo[tID][SecondPickupModel] = SPM;
	TeleportInfo[tID][Type] = Type;
	InsertTeleportData(tID);
}

stock ResetTeleportInfo(ID)
{
	TeleportInfo[ID][Created] = 0;
	TeleportInfo[ID][FirstX] = 0.0;
	TeleportInfo[ID][FirstY] = 0.0;
	TeleportInfo[ID][FirstZ] = 0.0;
	TeleportInfo[ID][FirstAngle] = 0.0;
	TeleportInfo[ID][FirstInt] = 0;
	TeleportInfo[ID][FirstVW] = 0;
	TeleportInfo[ID][FirstHouse] = 0;
	TeleportInfo[ID][FirstBiz] = 0;
	TeleportInfo[ID][FirstBuilding] = 0;
	TeleportInfo[ID][SecondX] = 0.0;
	TeleportInfo[ID][SecondY] = 0.0;
	TeleportInfo[ID][SecondZ] = 0.0;
	TeleportInfo[ID][SecondAngle] = 0.0;
	TeleportInfo[ID][SecondInt] = 0;
	TeleportInfo[ID][SecondVW] = 0;
	TeleportInfo[ID][SecondHouse] = 0;
	TeleportInfo[ID][SecondBiz] = 0;
	TeleportInfo[ID][SecondBuilding] = 0;
	TeleportInfo[ID][FirstPickupModel] = 0;
	TeleportInfo[ID][Type] = 0;
	return 1;
}

stock GetFirstNonCreatedTeleport()
{
	for(new i = 1; i < MAX_TELEPORTS; i++)
	{
	    if(TeleportInfo[i][Created] == 1)
	        continue;
		else
		    return i;
	}
	return 0;
}

stock LoadTeleportPickup(ID)
{
	CreateDynamicPickup(TeleportInfo[ID][FirstPickupModel], 1,
	TeleportInfo[ID][FirstX],
	TeleportInfo[ID][FirstY],
	TeleportInfo[ID][FirstZ],
	TeleportInfo[ID][FirstVW]);
	
	CreateDynamicPickup(TeleportInfo[ID][SecondPickupModel], 1,
	TeleportInfo[ID][SecondX],
	TeleportInfo[ID][SecondY],
	TeleportInfo[ID][SecondZ],
	TeleportInfo[ID][SecondVW]);
	
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
	GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), 0, 0, 0, pickup[0], pickup[1], 0);
	return 1;
}

