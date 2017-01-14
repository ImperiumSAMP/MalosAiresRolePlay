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
forward CreateTeleport(Float:FX, Float:FY, Float:FZ, Float:FA, FInt, FVW, FHouse, FBiz, FBuilding, Float:SX, Float:SY, Float:SZ, Float:SA, SInt, SVW, SHouse, SBiz, SBuilding, FPM, SPM, TType);
forward ResetTeleport(ID);
forward GetTeleportID(ID, type);
forward GetFirstNonCreatedTeleport();
forward LoadTeleportPickup(ID);
forward IsOnATeleport(playerid, bool:First);
forward EnterTeleport(playerid);

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
	    format(query, sizeof(query),"SELECT * FROM `teleports_info` WHERE `tID` = %d", tID);
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

		Teleport[ID][Created] = 1;
	}
	return 1;
}

stock SaveTeleport(ID)
{
	new query[768];
	
	if(Teleport[ID][Created] == 0) return 1;
	
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
	);
	
	format(query, sizeof(query), "%s `FirstPickup`=%d,`SecondPickup`=%d, `Type`=%d",
	query,
	Teleport[ID][FirstPickupModel],
	Teleport[ID][SecondPickupModel],
	Teleport[ID][Type]
	);
	
	format(query, sizeof(query), "%s WHERE `tID` = %d", query, ID);
	
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

stock CreateTeleport(Float:FX, Float:FY, Float:FZ, Float:FA, FInt, FVW, FHouse, FBiz, FBuilding, Float:SX, Float:SY, Float:SZ, Float:SA, SInt, SVW, SHouse, SBiz, SBuilding, FPM, SPM, TType)
{
	new tID = GetFirstNonCreatedTeleport();
	
	if(tID == 0) // No debería pasar porque hay filtro en todos los comandos, pero si alguien en un futuro toca algo...
		return 1;
	
	Teleport[tID][Created] = 1;
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
	Teleport[tID][Type] = TType;
	InsertTeleportData(tID);
	LoadTeleportPickup(tID);
	return 1;
}

stock ResetTeleport(ID)
{
	if(Teleport[ID][FirstPickupModel] != 0)
		DestroyDynamicPickup(Teleport[ID][FirstPickup]);
	if(Teleport[ID][SecondPickupModel] != 0)
		DestroyDynamicPickup(Teleport[ID][SecondPickup]);
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
	Teleport[ID][SecondPickupModel] = 0;
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

stock CheckForEntrancePickupTeleport(tpid)
{
	for(new i; i < MAX_HOUSES; i++)
	{
		if(House[i][EntrancePickupSQLID] == tpid)
			return i;
	}

	/*
	for(new i; i < MAX_BUSINESS; i++)
	{
		if(Business[i][EntrancePickupSQLID] == tpid)
			return i;
	}
	
	for(new i; i < MAX_BUILDINGS; i++)
	{
		if(Business[i][EntrancePickupSQLID] == tpid)
			return i;
	}
	*/
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

stock IsOnATeleport(playerid, bool:First)
{
	new tpcount, tpid;
	
	for(new i; i < MAX_TELEPORTS; i++)
	{
		if(First)
		{
			if(PlayerToPoint(1.0, playerid, Teleport[i][FirstX], Teleport[i][FirstY], Teleport[i][FirstZ]) && Teleport[i][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[i][FirstInt] == GetPlayerInterior(playerid))
			{
				tpcount++;
				tpid = i;
			}
		}
		else
		{
			if(PlayerToPoint(1.0, playerid, Teleport[i][SecondX], Teleport[i][SecondY], Teleport[i][SecondZ]) && Teleport[i][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[i][SecondInt] == GetPlayerInterior(playerid))
			{
				tpcount++;
				tpid = i;
			}
		}
	}
	
	switch(tpcount)
	{
		case 0: return 0;
		case 1: return tpid;
		default: SendClientMessage(playerid, COLOR_WHITE, "[SCRIPT ERROR] Hay más de un teleport en tu posición. Reportar a un scripter.");
	}
	
	return 0;
}

stock EnterTeleport(playerid)
{
	new tpid;
	
	tpid = IsOnATeleport(playerid, true);
	
	if(tpid == 0)
	{
		tpid = IsOnATeleport(playerid, false);
		
		if(tpid == 0)
			return 1;
		
		switch(Teleport[tpid][Type])
		{
			case TYPE_HOUSE: PlayerInfo[playerid][pCurrentHouse] = Teleport[tpid][FirstHouse];
			case TYPE_BUSINESS: PlayerInfo[playerid][pCurrentBiz] = Teleport[tpid][FirstBiz];
			case TYPE_BUILDING: PlayerInfo[playerid][pCurrentBuilding] = Teleport[tpid][FirstBuilding];
		}
	
		SetPlayerPos(playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]);
		SetPlayerFacingAngle(playerid, Teleport[tpid][FirstAngle]);
		SetPlayerInterior(playerid, Teleport[tpid][FirstInt]);
		SetPlayerVirtualWorld(playerid, Teleport[tpid][FirstVW]);
	}
	else
	{
		switch(Teleport[tpid][Type])
		{
			case TYPE_HOUSE: PlayerInfo[playerid][pCurrentHouse] = Teleport[tpid][SecondHouse];
			case TYPE_BUSINESS: PlayerInfo[playerid][pCurrentBiz] = Teleport[tpid][SecondBiz];
			case TYPE_BUILDING: PlayerInfo[playerid][pCurrentBuilding] = Teleport[tpid][SecondBuilding];
		}
	
		SetPlayerPos(playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]);
		SetPlayerFacingAngle(playerid, Teleport[tpid][SecondAngle]);
		SetPlayerInterior(playerid, Teleport[tpid][SecondInt]);
		SetPlayerVirtualWorld(playerid, Teleport[tpid][SecondVW]);
	}
	return 1;
}

// ====================== Comandos administrativos =============================


CMD:ateleports(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[LVL 20] /atcrear /atborrar /atpos /atinterior /atvworld /atpickup");
	return 1;
}

CMD:atcrear(playerid, params[])
{
	new Float:pos[3], Float:Angle, pickup[2], tpid = GetFirstNonCreatedTeleport();
	
	if(sscanf(params, "ii", pickup[0], pickup[1]))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atcrear [modelo de pickup entrada] [modelo de pickup salida]");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] Para que no tenga pickup, configurar como modelo '0'.");
	}
	if(pickup[0] < 0 || pickup[1] < 0)
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Modelo de pickup inválido.");
	if(GetFirstNonCreatedTeleport() == 0)
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[SCRIPT ERROR] No hay más espacio para teleports. Reportar a un scripter.");
	
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, Angle);

	CreateTeleport(pos[0], pos[1], pos[2], Angle+180, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), 0, 0, 0, pos[0], pos[1], pos[2], Angle+180,
	GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), 0, 0, 0, pickup[0], pickup[1], TYPE_NORMAL);
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] Se creó teleport con el ID %d. La posición, interior y virtual world son los tuyos actuales.", tpid);
	return 1;
}

CMD:atborrar(playerid, params[])
{
	new tpid;
	
	if(sscanf(params, "i", tpid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atborrar [Teleport ID]");
	if(Teleport[tpid][Created] == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El teleport no está creado (ID inválida).");
	if(CheckForEntrancePickupTeleport(tpid) != 0)
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[ERROR] El teleport está asociado como entrada principal de una casa/negocio/edificio.");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[ERROR] Para borrarlo deberás usar el correspondiente comando. (/acasas, /anegocios, /aedificios)");
	}
	
	ResetTeleport(tpid);
	DeleteTeleport(tpid);
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El teleport ID %d fue borrado.", tpid);
	return 1;
}

CMD:atpos(playerid, params[])
{
	new Float:pos[3], Float:Angle, tpid, param;
	
	if(sscanf(params, "ii", tpid, param))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atpos [Teleport ID] [0 = Entrada | 1 = Salida]");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] La posición de entrada/salida del teleport se configurará en tu lugar actual.");
	}
	if(param > 1 || param < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Ingresa un parámetro válido. 0 para configurar la entrada y 1 para la salida.");
	if(Teleport[tpid][Created] == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El teleport no está creado (ID inválida).");
	
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, Angle);

	if(param)
	{
		Teleport[tpid][SecondX] = pos[0];
		Teleport[tpid][SecondY] = pos[1];
		Teleport[tpid][SecondZ] = pos[2];
		Teleport[tpid][SecondAngle] = Angle+180;
		if(Teleport[tpid][SecondPickupModel] != 0)
		{
			DestroyDynamicPickup(Teleport[tpid][FirstPickup]);
			DestroyDynamicPickup(Teleport[tpid][SecondPickup]);
		}
		SendFMessage(playerid, COLOR_WHITE, "[INFO] La posición de salida del teleport ID %d fue puesta en %f, %f, %f - (%f°).", tpid, pos[0], pos[1], pos[2], Angle+180);
	}
	else
	{
		Teleport[tpid][FirstX] = pos[0];
		Teleport[tpid][FirstY] = pos[1];
		Teleport[tpid][FirstZ] = pos[2];
		Teleport[tpid][FirstAngle] = Angle+180;
		if(Teleport[tpid][FirstPickupModel] != 0)
		{
			DestroyDynamicPickup(Teleport[tpid][FirstPickup]);
			DestroyDynamicPickup(Teleport[tpid][SecondPickup]);
		}
		SendFMessage(playerid, COLOR_WHITE, "[INFO] La posición de entrada del teleport ID %d fue puesta en %f, %f, %f - (%f°).", tpid, pos[0], pos[1], pos[2], Angle+180);
	}
	
	SaveTeleport(tpid);
	LoadTeleportPickup(tpid);
	return 1;
}

CMD:atinterior(playerid, params[])
{
	new tpid, interior, param;
	
	if(sscanf(params, "iii", tpid, interior, param))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atinterior [Teleport ID] [interior] [0 = Entrada | 1 = Salida]");
	if(param > 1 || param < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Ingresa un parámetro válido. 0 para configurar la entrada y 1 para la salida.");
	if(interior < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El interior ingresado no es válido.");
	if(Teleport[tpid][Created] == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El teleport no está creado (ID inválida).");
	
	if(param)
	{
		Teleport[tpid][SecondInt] = interior;
		if(Teleport[tpid][SecondPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][SecondPickup]);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El interior de salida del teleport ID %d fue configurado en %d.", tpid, interior);
	}
	else
	{
		Teleport[tpid][FirstInt] = interior;
		if(Teleport[tpid][FirstPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][FirstPickup]);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El interior de entrada del teleport ID %d fue configurado en %d.", tpid, interior);
	}
	
	SaveTeleport(tpid);
	LoadTeleportPickup(tpid);
	return 1;
}

CMD:atvworld(playerid, params[])
{
	new tpid, vworld, param;
	
	if(sscanf(params, "iii", tpid, vworld, param))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atvworld [Teleport ID] [Virtual World] [0 = Entrada | 1 = Salida]");
	if(param > 1 || param < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Ingresa un parámetro válido. 0 para configurar la entrada y 1 para la salida.");
	if(vworld < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El virtual world ingresado no es válido.");
	if(Teleport[tpid][Created] == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El teleport no está creado (ID inválida).");
	
	if(param)
	{
		Teleport[tpid][SecondVW] = vworld;
		if(Teleport[tpid][SecondPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][SecondPickup]);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El virtual world de salida del teleport ID %d fue configurado en %d.", tpid, vworld);
	}
	else
	{
		Teleport[tpid][FirstVW] = vworld;
		if(Teleport[tpid][FirstPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][FirstPickup]);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El virtual world de entrada del teleport ID %d fue configurado en %d.", tpid, vworld);
	}
	
	SaveTeleport(tpid);
	LoadTeleportPickup(tpid);
	return 1;
}

CMD:atpickup(playerid, params[])
{
	new tpid, pickup, param;
	
	if(sscanf(params, "iii", tpid, pickup, param))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /atpickup [Teleport ID] [Modelo del pickup] [0 = Entrada | 1 = Salida]");
	if(param > 1 || param < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Ingresa un parámetro válido. 0 para configurar la entrada y 1 para la salida.");
	if(pickup < 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El modelo de pickup ingresado no es válido.");
	if(Teleport[tpid][Created] == 0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "El teleport no está creado (ID inválida).");
	
	if(param)
	{
		if(Teleport[tpid][SecondPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][SecondPickup]);
		Teleport[tpid][SecondPickupModel] = pickup;
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El modelo de pickup del teleport ID %d fue configurado en %d.", tpid, pickup);
	}
	else
	{
		if(Teleport[tpid][FirstPickupModel] != 0)
			DestroyDynamicPickup(Teleport[tpid][FirstPickup]);
		Teleport[tpid][FirstPickupModel] = pickup;
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El modelo de pickup del teleport ID %d fue configurado en %d.", tpid, pickup);
	}
	
	SaveTeleport(tpid);
	LoadTeleportPickup(tpid);
	return 1;
}

CMD:atgetid(playerid, params[])
{
	new tpid = IsOnATeleport(playerid, true);
	
	if(tpid == 0)
		tpid = IsOnATeleport(playerid, false);
	
	
	if(tpid == 0)
		return 1;
	
	if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El teleport de tu posición es el ID %d y estás en la entrada.", tpid);
	else
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[INFO] El teleport en tu posición es el ID %d y estás en la salida.", tpid);
	
	return 1;
}

