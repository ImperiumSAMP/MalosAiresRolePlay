#if defined _marp_business_included
	#endinput
#endif
#define _marp_business_included


/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||   Sistema dinámico para creación IG de negocios	  ||||||||||||||
|||||||||||||        	Pheek Gaming Latinoamérica                ||||||||||||||
|||||||||||||           			2016              			  ||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// =============================== CONSTANTES ==================================

#define MAX_BUSINESS				500

#define BIZ_SHOP					1
#define BIZ_OTHER					2

// ================================ FUNCIONES ==================================

forward LoadAllBusiness();
forward OnBusinessDataLoad(ID);
forward OnBusinessDelete(ID);
forward SaveBusiness(ID);
forward SaveAllBusiness();
forward CreateBusiness(ID);
forward DeleteBusiness(ID);
forward GetBusinessLockerSpace(ID);
forward GetPlayerBusiness(playerid);
forward IsPlayerOnOutsideBusinessDoor(playerid, ID);
forward IsPlayerOnInsideBusinessDoor(playerid, ID);
forward GetPlayerNearestBusiness(playerid);
forward IsOwnerOfTheBusiness(playerid, ID);

// =========================== VARIABLES INTERNAS ==============================

enum BusinessSystem {
	Created,
	OwnerName[MAX_PLAYER_NAME],
	OwnerSQLID,
	HasExtInt,
	Float:AreaX[2],
	Float:AreaY[2],
	Float:AreaZ[2],
	Type,
	Products,
	Price,
	Money,
	Locked,
	Radio,

	EntrancePickupSQLID,
	ContainerSQLID,
	ContainerID
};

new Business[MAX_BUSINESS][BusinessSystem],
	OfferingBusiness[MAX_PLAYERS],
	BusinessOfferPrice[MAX_PLAYERS],
	BusinessOffer[MAX_PLAYERS];

// =========================== MANEJO DE DATOS SQL =============================

stock LoadAllBusiness()
{
	new query[128],
		ID = 1;

	while(ID < MAX_BUSINESS)
	{
	    format(query, sizeof(query),"SELECT * FROM `business` WHERE `Id` = %d LIMIT 1", ID);
		mysql_function_query(dbHandle, query, true, "OnBusinessDataLoad", "i", ID);
		ID++;
	}
	print("[INFO] negocios cargados.");
	return 1;
}

public OnBusinessDataLoad(ID)
{
   	new result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows)
	{
		cache_get_field_content(0, "OwnerName", 					Business[ID][OwnerName], 1, MAX_PLAYER_NAME);
		cache_get_field_content(0, "OwnerSQLID", result);			Business[ID][OwnerSQLID]    	= strval(result);
		
		cache_get_field_content(0, "HasExteriorInt", result);		Business[ID][HasExtInt]    		= strval(result);

		cache_get_field_content(0, "AreaMinX", result); 			Business[ID][AreaX][0]			= floatstr(result);
		cache_get_field_content(0, "AreaMaxX", result); 			Business[ID][AreaX][1]			= floatstr(result);
		cache_get_field_content(0, "AreaMinY", result); 			Business[ID][AreaY][0]			= floatstr(result);
		cache_get_field_content(0, "AreaMaxY", result); 			Business[ID][AreaY][1]			= floatstr(result);
		cache_get_field_content(0, "AreaMinZ", result); 			Business[ID][AreaZ][0]			= floatstr(result);
		cache_get_field_content(0, "AreaMaxZ", result); 			Business[ID][AreaZ][1]			= floatstr(result);

		cache_get_field_content(0, "Type", result); 				Business[ID][Type] 				= strval(result);
		cache_get_field_content(0, "Products", result); 			Business[ID][Products] 			= strval(result);
		
		cache_get_field_content(0, "Price", result); 				Business[ID][Price] 			= strval(result);
		cache_get_field_content(0, "Money", result); 				Business[ID][Money] 			= strval(result);
		cache_get_field_content(0, "Locked", result); 				Business[ID][Locked]			= strval(result);
		cache_get_field_content(0, "Radio", result); 				Business[ID][Radio]				= strval(result);

		cache_get_field_content(0, "EntrancePickupSQLID", result); 	Business[ID][EntrancePickupSQLID]	= strval(result);
		cache_get_field_content(0, "ContainerSQLID", result); 		Business[ID][ContainerSQLID] 		= strval(result);

		//===========================CARGA DE CONTENEDOR========================

		if(Business[ID][ContainerSQLID] > 0)
		    Business[ID][ContainerID] = Container_Load(Business[ID][ContainerSQLID]);
		else
		    Container_Create(GetBusinessLockerSpace(ID), 4, Business[ID][ContainerID], Business[ID][ContainerSQLID]);

		//======================================================================

		Business[ID][Created] = 1;
	}
	return 1;
}

public OnBusinessDelete(ID)
{
	new query[128];
	
	format(query, sizeof(query), "DELETE FROM `business` WHERE `Id` = %d", ID);
 	mysql_function_query(dbHandle, query, false, "", "");
}

stock SaveBusiness(ID)
{
	new query[512];

    if(Business[ID][Created] == 0)
		return 1;

	format(query, sizeof(query), "UPDATE `business` SET");

	format(query, sizeof(query), "%s `OwnerName`='%s', `OwnerSQLID`=%d, `HasExteriorInt`=%d, `EntrancePickupSQLID`=%d, `ContainerSQLID`=%d",
		query,
	    Business[ID][OwnerName],
	    Business[ID][OwnerSQLID],
	    Business[ID][HasExtInt],
	    Business[ID][EntrancePickupSQLID],
		Business[ID][ContainerSQLID]
	);

	format(query, sizeof(query), "%s, `Price`=%d, `Money`=%d, `Locked`=%d, `Radio`=%d, `Type`=%d, `Products`=%d",
		query,
		Business[ID][Price],
		Business[ID][Money],
		Business[ID][Locked],
		Business[ID][Radio],
		Business[ID][Type],
		Business[ID][Products]
	);

	format(query, sizeof(query), "WHERE `Id`=%d", ID);

	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

stock SaveBusiness()
{
  	new ID = 1;

	while(ID < MAX_BUSINESS)
	{
	    SaveBusiness(ID);
		ID++;
	}
    print("[INFO] negocios guardados.");
	return 1;
}

stock CreateBusiness(ID)
{
	new query[128];

    if(dontsave)
		return 1;

    format(query, sizeof(query), "INSERT INTO `business` (Id)");
	format(query, sizeof(query), "%s VALUES (%d)",
	    query,
	    ID,
	);
	mysql_function_query(dbHandle, query, false, "", "");

	//=========================CREACION DE CONTENEDOR===========================

    Container_Create(GetBusinessLockerSpace(ID), 10, Business[ID][ContainerID], Business[ID][ContainerSQLID]);

	//==========================================================================

	Business[ID][Created] = 1;
	return 1;
}


// ================== OTRAS FUNCIONES / DATOS EN VARIABLES =====================


stock DeleteBusiness(ID) /* !!!!! */
{
	Business[ID][Price] = 0;
	Business[ID][Money] = 0;
	Business[ID][Locked] = 0;
	Business[ID][Radio] = 0;


	//==========================BORRADO DE CONTENEDOR===========================
	if(BusinessHasContainer(ID)) /* !!!!! */
	{
	    Container_Fully_Destroy(Business[ID][ContainerID], Business[ID][ContainerSQLID]);
	    Business[ID][ContainerID] = 0;
	    Business[ID][ContainerSQLID] = 0;
	}
	//==========================================================================


	// AGREGAR BORRADO DE TELEPORT
	OnBusinessDelete(ID);
	return 1;
}

stock GetBusinessLockerSpace(biz)
{
	/* !!!!! */
}

stock GetPlayerBusiness(playerid)
{
	return PlayerInfo[playerid][pCurrentBiz];
}

stock PrintBusinessAdress(biz)
{
	new tpid, bizlocation[MAX_ZONE_NAME], string[MAX_ZONE_NAME + 5];
	tpid = Business[biz][EntrancePickupSQLID];
	
	GetCoords2DZone(Teleport[tpid][FirstX], Teleport[tpid][FirstY], bizlocation, MAX_ZONE_NAME);
	format(string, sizeof(string), "%s %d", bizlocation, biz);
	return string;
}

stock BusinessHasContainer(bizid)
{
	if(Business[bizid][ContainerSQLID] > 0 && Business[bizid][ContainerID] > 0)
	    return 1;
	return 0;
}

stock IsPlayerOnOutsideBusinessDoor(playerid, biz)
{
	new tpid = Business[biz][EntrancePickupSQLID];

	if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
		return true;
	return false;
}

stock IsPlayerOnInsideBusinessDoor(playerid, biz)
{
	new tpid = Business[biz][EntrancePickupSQLID];

	if(PlayerToPoint(1.0, playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]) && Teleport[tpid][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][SecondInt] == GetPlayerInterior(playerid))
		return true;
	return false;
}

stock GetPlayerNearestBusiness(playerid)
{
	new tpid, biz[2], bizcount;

	for(biz[0] = 1;biz[0] < MAX_BUSINESS; biz[0]++)
	{
	    tpid = Business[biz[0]][EntrancePickupSQLID];
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
			bizcount++; biz[1] = biz[0];
	}

	switch(bizcount)
	{
		case 0: return 0; // No hay pickups de entrada a un negocio en esa posición/interior/virtualworld.
		case 1: return biz[1]; // Hay un solo pickup de entrada a un negocio en esa posición/interior/virtualworld.
	}
	return -1; // Hay más de un pickup de entrada a un negocio en esa posición/interior/virtualworld.
}

stock IsOwnerOfTheBusiness(playerid, biz)
{
	if(Business[biz][OwnerSQLID] == PlayerInfo[playerid][pID])
	    return true;
	else
		return false;
}

//=============================COMANDOS DE NEGOCIOS=================================

CMD:ayudanegocio(playerid, params[])
{
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[NEGOCIO] /negociocomprar - /negociovender - /negociovendera - /negocioradio");
	return 1;
}

CMD:negocioradio(playerid, params[])
{
	new radio, bizid, radioamount;
	bizid = GetPlayerBusiness(playerid);
	radioamount = Radio_GetAmount();

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintáxis]{C8C8C8} /negocioradio [ID radio]");
	if(!IsOwnerOfTheBusiness(playerid, bizid))
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Este negocio no te pertenece.");
	if(radio < 0 || radio > radioamount)
		return SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Debes ingresar una radio válida: del 1 al %d. Usa 0 para dejarlo sin radio.", radioamount);

    Business[bizid][Radio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Has seteado la radio de tu negocio a %d.", Business[bizid][Radio]);
	if(Business[bizid][Radio] > 0)
	    Radio_Set(playerid, Business[bizid][Radio], RADIO_TYPE_BIZ);
	SaveBusiness(bizid);
	return 1;
}

CMD:negociocomprar(playerid, params[])
{
	new nearestbiz = GetPlayerNearestBusiness(playerid);
	
	switch(nearestbiz)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de un negocio en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de un negocio!");
	    default:
	    {
			if(Business[nearestbiz][OwnerSQLID] != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Este negocio no está a la venta.");
			if(GetPlayerCash(playerid) < Business[nearestbiz][Price])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
			    
			Business[nearestbiz][OwnerSQLID] = PlayerInfo[playerid][pID];
			format(Business[nearestbiz][OwnerName], MAX_PLAYER_NAME, "%s", GetPlayerNameEx(playerid));
				
			GivePlayerCash(playerid, -Business[nearestbiz][BusinessPrice]);
			SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has comprado esta propiedad! Para ver los comandos disponibles utiliza /ayudanegocio.");
			PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y éste le entrega un par de llaves.");
			SaveBusiness(nearestbiz);
	    }
	}
	return 1;
}

CMD:negociovender(playerid, params[])
{
	new nearestbiz = GetPlayerNearestBusiness(playerid);
	
	switch(nearestbiz)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de un negocio en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de un negocio!");
	    default:
	    {
			if(Business[nearestbiz][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡No podés vender un negocio que no es tuyo!");
			    
			Business[nearestbiz][OwnerSQLID] = 0;
			Business[nearestbiz][OwnerName] = "";
			Business[nearestbiz][Locked] = 1;
			Container_Empty(Business[nearestbiz][ContainerID]);
	
			GivePlayerCash(playerid, Business[nearestbiz][BusinessPrice] / 3 * 2); // 66 % del valor original.
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendFMessage(playerid, COLOR_WHITE, "¡Has vendido tu negocio por $%d!", Business[nearestbiz][BusinessPrice] / 3 * 2);
			PlayerActionMessage(playerid, 15.0 , "toma las llaves de su negocio y se las entrega al agente inmobiliario.");
			SaveBusiness(nearestbiz);
	    }
	}
	return 1;
}

CMD:negociovendera(playerid, params[])
{
	new nearestbiz = GetPlayerNearestBusiness(playerid),
		targetid,
		price;

	switch(nearestbiz)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de un negocio en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de un negocio!");
	    default:
	    {
			if(sscanf(params, "ui", targetid, price))
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negociovendera [ID/Jugador] [Precio]");
			if(Business[nearestbiz][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta no es tu negocio!");
			if(GetDistanceBetweenPlayers(playerid, targetid) > 5.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no está cerca tuyo.");
			if(price < 1 || price > 10000000)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $10,000,000.");
			if(OfferingBusiness[playerid])
				return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras vendiendo un negocio.");
			    
			OfferingBusiness[playerid] = true;
			BusinessOfferPrice[targetid] = price;
			BusinessOffer[targetid] = playerid;
			SendFMessage(playerid, COLOR_LIGHTBLUE, "Le ofreces las llaves y la escritura de tu negocio a %s por $%d.", GetPlayerNameEx(targetid), price);
			SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te esta ofreciendo venderte su negocio por $%d.", GetPlayerNameEx(playerid), price);
			SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/negocioaceptar' para aceptar la oferta o '/negociocancelar' para cancelar.");
			SetPVarInt(targetid, "CancelBusinessTransfer", SetTimerEx("CancelBusinessTransfer", 10000, false, "ii", targetid, 1));
	    }
	}
	return 1;
}

CMD:negocioaceptar(playerid, params[])
{
	new sellerid = BusinessOffer[playerid],
	    price = BusinessOfferPrice[playerid],
	    bizid,
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));
	
	if(sellerid == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo un negocio.");
	if(!IsPlayerConnected(sellerid) || !OfferingBusiness[sellerid])
	{
	    KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	    CancelBusinessTransfer(playerid, 2);
		return SendClientMessage(playerid, COLOR_YELLOW2, "Hubo un error durante la venta, cancelando...");
	}
	if(!ProxDetectorS(3.0, playerid, sellerid))
 	   	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
	if(GetPlayerCash(playerid) < price)
	{
	    KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	    CancelBusinessTransfer(playerid, 2);
	    SendClientMessage(sellerid, COLOR_YELLOW2, "El jugador no tiene el dinero necesario, cancelando...");
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, cancelando...");
	}

	bizid = PlayerInfo[sellerid][pBusinessKey];
	Business[bizid][OwnerSQLID] = PlayerInfo[playerid][pID];
	format(Business[bizid][OwnerName], MAX_PLAYER_NAME, "%s", name);
	Business[bizid][Locked] = 1;
	
	GivePlayerCash(playerid, -price);
    GivePlayerCash(sellerid, price);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(sellerid, 1052, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pBusinessKey] = bizid;
    PlayerInfo[sellerid][pBusinessKey] = 0;
    SaveBusiness(bizid);
    PlayerPlayerActionMessage(sellerid, playerid, 15.0 , "toma las llaves y la escritura de su negocio y se las entrega a");
  	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Felicidades, has comprado el negocio por $%d! Usa /ayudanegocio para ver los comandos disponibles.", price);
  	SendFMessage(sellerid, COLOR_LIGHTBLUE, "¡Felicitaciones, has vendido tu negocio por $%d!", price);
  	KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	CancelBusinessTransfer(playerid, 2);
	return 1;
}

CMD:negociocancelar(playerid, params[])
{
	if(BusinessOffer[playerid] == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo un negocio.");

 	KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	CancelBusinessTransfer(playerid, 0);
	return 1;
}

TIMER:CancelBusinessTransfer(playerid, reason)
{
	if(reason == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que no has respondido en 10 segundos.");
		SendClientMessage(BusinessOffer[playerid], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 10 segundos.");
	}
	else
		if(reason == 0)
		{
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la oferta.");
			SendFMessage(BusinessOffer[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la oferta.", GetPlayerNameEx(playerid));
		}

 	ResetBusinessOffer(BusinessOffer[playerid]);
 	ResetBusinessOffer(playerid);
	return 1;
}

CMD:puerta(playerid, params[])
{
	new nearestbiz = GetPlayerNearestBusiness(playerid), tpid;

	switch(nearestbiz)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de un negocio en tu posición! Reportar a un administrador.");
	    case 0: if(GetPlayerBusiness(playerid) == 0) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de un negocio!");
	}
	
	if(GetPlayerBusiness(playerid) == 0) // Del lado de afuera.
	{
		if(!IsTenantOrOwnerOfTheBusiness(playerid, nearestbiz))
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este negocio!");

		switch(Business[nearestbiz][Locked])
		{
			case 0:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su negocio y cierra la puerta.");
				Business[nearestbiz][Locked] = 1;
			}
			case 1:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su negocio y abre la puerta.");
				Business[nearestbiz][Locked] = 0;
			}
		}
	}
	else // Del lado de adentro.
	{
		tpid = Business[nearestbiz][EntrancePickupSQLID];
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]) && Teleport[tpid][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][SecondInt] == GetPlayerInterior(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la puerta del negocio!");

		switch(Business[nearestbiz][Locked])
		{
			case 0:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su negocio y cierra la puerta.");
				Business[nearestbiz][Locked] = 1;
			}
			case 1:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su negocio y abre la puerta.");
				Business[nearestbiz][Locked] = 0;
			}
		}
	}
	return 1;
}