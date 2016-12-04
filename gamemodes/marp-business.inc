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

new Business[MAX_BUSINESS][BusinessSystem];

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

	format(query, sizeof(query), "%s, `Price`=%d, `Money`=%d, `Locked`=%d, `Radio`=%d, `IncomePrice`=%d, `IncomeAmount`=%d, `RentalExpiration`=%d",
		query,
		Business[ID][Price],
		Business[ID][Money],
		Business[ID][Locked],
		Business[ID][Radio],
		Business[ID][IncomePrice],
		Business[ID][IncomeAmount],
		Business[ID][HouseRentalExpiration]
	);

	format(query, sizeof(query), "WHERE `Id`=%d", ID);

	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

stock SaveHouses()
{
  	new ID = 1;

	while(ID < MAX_HOUSES)
	{
	    SaveHouse(ID);
		ID++;
	}
    print("[INFO] casas guardadas.");
	return 1;
}

stock CreateHouse(ID)
{
	new query[128];

    if(dontsave)
		return 1;

    format(query, sizeof(query), "INSERT INTO `houses` (Id, HousePrice, Locked)");
	format(query, sizeof(query), "%s VALUES (%d, %d, %d)",
	    query,
	    ID,
		House[ID][HousePrice],
		House[ID][Locked]
	);
	mysql_function_query(dbHandle, query, false, "", "");

	//=========================CREACION DE CONTENEDOR===========================

    Container_Create(GetHouseLockerSpace(ID), 10, House[ID][ContainerID], House[ID][ContainerSQLID]);

	//==========================================================================

	House[ID][Created] = 1;
	return 1;
}


// ================== OTRAS FUNCIONES / DATOS EN VARIABLES =====================


stock DeleteHouse(ID)
{

 	House[ID][Created] = 0;
	House[ID][Owned] = 0;
	House[ID][OwnerSQLID] = 0;
	House[ID][IncomePrice] = 0;
	House[ID][IncomeAmount] = 0;
	House[ID][HousePrice] = 0;
	House[ID][Money] = 0;
	House[ID][Locked] = 0;
	House[ID][Radio] = 0;


	//==========================BORRADO DE CONTENEDOR===========================
	if(HouseHasContainer(ID))
	{
	    Container_Fully_Destroy(House[ID][ContainerID], House[ID][ContainerSQLID]);
	    House[ID][ContainerID] = 0;
	    House[ID][ContainerSQLID] = 0;
	}
	//==========================================================================


	// AGREGAR BORRADO DE TELEPORT
	OnHouseDelete(ID);
	return 1;
}

stock GetHouseLockerSpace(houseid)
{
	if(houseid <= 0 || houseid >= MAX_HOUSES)
		return 0;

	new hprice = House[houseid][HousePrice];

	if(hprice < MIN_PRICE_LOCKER1) return LOCKER1_SPACE;
	if(hprice < MIN_PRICE_LOCKER2) return LOCKER2_SPACE;
	if(hprice < MIN_PRICE_LOCKER3) return LOCKER3_SPACE;
	if(hprice < MIN_PRICE_LOCKER4) return LOCKER4_SPACE;
	if(hprice < MIN_PRICE_LOCKER5) return LOCKER5_SPACE;
	if(hprice < MIN_PRICE_LOCKER6) return LOCKER6_SPACE;
	if(hprice < MIN_PRICE_LOCKER7) return LOCKER7_SPACE;
	if(hprice < MIN_PRICE_LOCKER8) return LOCKER8_SPACE;
	if(hprice < MIN_PRICE_LOCKER9) return LOCKER9_SPACE;
	if(hprice < MIN_PRICE_LOCKER10) return LOCKER10_SPACE;
	if(hprice >= MIN_PRICE_LOCKER11) return LOCKER11_SPACE;

	return 0;
}

stock GetPlayerHouse(playerid)
{
	return PlayerInfo[playerid][pCurrentHouse];
}

stock PrintHouseAdress(houseid)
{
	new tpid, houselocation[MAX_ZONE_NAME], string[MAX_ZONE_NAME + 5];
	tpid = House[houseid][EntrancePickupSQLID];
	
	GetCoords2DZone(Teleport[tpid][FirstX], Teleport[tpid][FirstY], houselocation, MAX_ZONE_NAME);
	format(string, sizeof(string), "%s %d", houselocation, houseid);
	return string;
}

stock PrintPlayerHouseAddress(playerid, targetid)
{
	return después vemos que hacemo con esto;
}

stock CheckHousesRentForRentalExpirationAdvises(playerid)
{
	for(new houseid = 1; houseid < MAX_HOUSES; houseid++)
	{
		if(House[houseid][TenantSQLID] != PlayerInfo[playerid][pID]) continue;
		
		switch(House[houseid][HouseRentalExpiration])
		{
			case 0:
			{
				House[houseid][TenantSQLID] = 0;
				House[houseid][TenantName] = "";
				House[houseid][Locked] = 1;
				SendFMessage(playerid, COLOR_LIGHTGREEN, "El contrato de alquiler que mantenías para la vivienda en %s finalizó. Las cosas que no hayas retirado fueron perdidas.", PrintHouseAdress(houseid))
			}
			case 1: SendFMessage(playerid, COLOR_LIGHTGREEN, "Te queda 1 payday antes de que finalice el contrato de la vivienda que alquilas en %s, retira tus cosas antes o te desalojarán y las perderás.", PrintHouseAdress(houseid));
			case 2 .. 4: SendFMessage(playerid, COLOR_LIGHTGREEN, "Te quedan %d paydays antes de que finalice el contrato de la vivienda que alquilas en %s, retira tus cosas antes o te desalojarán y las perderás.", House[houseid][HouseRentalExpiration], PrintHouseAdress(houseid));
			case 5:
			{
				SendFMessage(playerid, COLOR_LIGHTGREEN, "SMS de Inmobiliaria: Señor, le queremos informar que el dueño de la vivienda que usted alquila en %s...", PrintHouseAdress(houseid));
				SendClientMessage(playerid, COLOR_LIGHTGREEN, "SMS de Inmobiliaria: ...ha decidido rescindirle el contrato, tiene 5 dias (paydays) para retirar sus pertenencias.");
			}						
			default: continue;
		}
	}
	return 1;
}

stock PlayerCantPayRent(playerid, houseid)
{
	if(PlayerInfo[playerid][pBank] < House[houseid][IncomePrice])
	    return true;
	else
		return false;
}

stock HouseHasContainer(houseid)
{
	if(House[houseid][ContainerSQLID] > 0 && House[houseid][ContainerID] > 0)
	    return 1;
	return 0;
}

stock IsPlayerOnOutsideHouseDoor(playerid, house)
{
	new tpid = House[house][EntrancePickupSQLID];

	if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
		return true;
	return false;
}

stock IsPlayerOnInsideHouseDoor(playerid, house)
{
	new tpid = House[house][EntrancePickupSQLID];

	if(PlayerToPoint(1.0, playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]) && Teleport[tpid][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][SecondInt] == GetPlayerInterior(playerid))
		return true;
	return false;
}

stock GetPlayerNearestHouse(playerid)
{
	new tpid, house[2], housecount;

	for(house[0] = 1;house[0] < MAX_HOUSES; house[0]++)
	{
	    tpid = House[house][EntrancePickupSQLID];
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
			housecount++; house[1] = house[0];
	}

	switch(housecount)
	{
		case 0: return 0; // No hay pickups de entrada a una casa en esa posición/interior/virtualworld.
		case 1: return house[1]; // Hay un solo pickup de entrada a una casa en esa posición/interior/virtualworld.
	}
	return -1; // Hay más de un pickup de entrada a una casa en esa posición/interior/virtualworld.
}

stock IsTenantOrOwnerOfTheHouse(playerid, house)
{
	if(House[house][OwnerSQLID] == PlayerInfo[playerid][pID] || House[house][TenantSQLID] == PlayerInfo[playerid][pID])
	    return true;
	else
		return false;
}

//=============================COMANDOS DE CASA=================================

CMD:ayudacasa(playerid, params[])
{
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[CASA] /casacomprar - /casavender - /casavendera - /casaalquilar - /casadesalquilar - /casaradio");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[CASA] /casaenalquiler - /casasinalquiler - /casacontrato - /puerta - /armario - /llenarbotella");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]{C8C8C8} Si alguien alquila tu casa y quieres rescindirle el contrato utiliza '/casacontrato'");
	return 1;
}

CMD:casaradio(playerid, params[])
{
	new radio, houseid, radioamount;
	houseid = GetPlayerHouse(playerid);
	radioamount = Radio_GetAmount();

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /casaradio [ID radio]");
	if(House[houseid][TenantSQLID] != PlayerInfo[playerid][pID] && House[houseid][OwnerSQLID] != PlayerInfo[playerid][pID])
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No estás en tu casa.");
	if(radio < 0 || radio > radioamount)
		return SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Debes ingresar una radio válida: del 1 al %d. Usa 0 para dejarla sin radio.", radioamount);

    House[houseid][Radio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]{C8C8C8} Has seteado la radio de tu casa a %d.", House[houseid][Radio]);
	if(House[houseid][Radio] > 0)
	    Radio_Set(playerid, House[houseid][Radio], RADIO_TYPE_HOUSE);
	SaveHouse(houseid);
	return 1;
}

CMD:casacomprar(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid);
	
	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][OwnerSQLID] != 0 || House[nearesthouse][TenantSQLID] != 0)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Esta casa no está a la venta.");
			if(GetPlayerCash(playerid) < House[nearesthouse][HousePrice])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
			    
			House[nearesthouse][OwnerSQLID] = PlayerInfo[playerid][pID];
			format(House[nearesthouse][OwnerName], MAX_PLAYER_NAME, "%s", name);
				
			GivePlayerCash(playerid, -House[nearesthouse][HousePrice]);
			SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has comprado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
			PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y éste le entrega un par de llaves.");
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casavender(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid);
	
	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡No podés vender una casa que no es tuya!");
			    
			House[nearesthouse][OwnerSQLID] = 0;
			House[nearesthouse][OwnerName] = "";
			House[nearesthouse][Locked] = 1;
			Container_Empty(House[nearesthouse][ContainerID]);
			
			if(House[nearesthouse][IncomePrice] != 0)
			{
				if(House[nearesthouse][IncomeAmount] != 0)
				{
					SendFMessage(playerid, COLOR_WHITE, "Cobraste $%d pendientes, del alquiler de tu inquilino.", House[nearesthouse][IncomeAmount]);
					GivePlayerCash(playerid, House[nearesthouse][IncomeAmount]);
					House[nearesthouse][IncomeAmount] = 0;
				}
				House[nearesthouse][IncomePrice] = 0;
				House[nearesthouse][HouseRentalExpiration] = 0;
			}
	
			GivePlayerCash(playerid, House[nearesthouse][HousePrice] / 3 * 2); // 66 % del valor original.
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendFMessage(playerid, COLOR_WHITE, "¡Has vendido tu casa por $%d!", House[nearesthouse][HousePrice] / 3 * 2);
			PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casavendera(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid),
		targetid,
		price;

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(sscanf(params, "ui", targetid, price))
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casavendera [ID/Jugador] [Precio]");
			if(House[nearesthouse][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta no es tu casa!");
			if(GetDistanceBetweenPlayers(playerid, targetid) > 5.0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no está cerca tuyo.");
			if(price < 1 || price > 10000000)
				return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $10,000,000.");
			if(OfferingHouse[playerid])
				return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras vendiendo una casa.");
			    
			OfferingHouse[playerid] = true;
			HouseOfferPrice[targetid] = price;
			HouseOffer[targetid] = playerid;
			SendFMessage(playerid, COLOR_LIGHTBLUE, "Le ofreces las llaves y la escritura de tu casa a %s por $%d.", GetPlayerNameEx(targetid), price);
			SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te esta ofreciendo venderte su casa por $%d.", GetPlayerNameEx(playerid), price);
			SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/casaaceptar' para aceptar la oferta o '/casacancelar' para cancelar.");
			SetPVarInt(targetid, "CancelHouseTransfer", SetTimerEx("CancelHouseTransfer", 10000, false, "ii", targetid, 1));
	    }
	}
	return 1;
}

CMD:casaaceptar(playerid, params[])
{
	new sellerid = HouseOffer[playerid],
	    price = HouseOfferPrice[playerid],
	    houseid,
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));
	
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

	houseid = PlayerInfo[sellerid][pHouseKey];
	House[houseid][OwnerSQLID] = PlayerInfo[playerid][pID];
	format(House[houseid][OwnerName], MAX_PLAYER_NAME, "%s", name);
	House[houseid][Locked] = 1;
	
	if(House[houseid][IncomePrice] != 0)
	{
	    if(House[houseid][IncomeAmount] != 0)
	    {
	        SendFMessage(sellerid, COLOR_WHITE, "Cobraste $%d pendientes, del alquiler de tu inquilino.", House[houseid][IncomeAmount]);
			GivePlayerCash(sellerid, House[houseid][IncomeAmount]);
			House[houseid][IncomeAmount] = 0;
		}
		House[houseid][IncomePrice] = 0;
		House[houseid][HouseRentalExpiration] = 0;
	}
	
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

CMD:puerta(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid), tpid;

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: if(GetPlayerHouse(playerid) == 0) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	}
	
	if(GetPlayerHouse(playerid) == 0) // Del lado de afuera.
	{
		if(!IsTenantOrOwnerOfTheHouse(playerid, nearesthouse))
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de esta casa!");

		switch(House[nearesthouse][Locked])
		{
			case 0:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
				House[nearesthouse][Locked] = 1;
			}
			case 1:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
				House[nearesthouse][Locked] = 0;
			}
		}
	}
	else // Del lado de adentro.
	{
		tpid = House[nearesthouse][EntrancePickupSQLID];
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]) && Teleport[tpid][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][SecondInt] == GetPlayerInterior(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la puerta de la casa!");

		switch(House[nearesthouse][Locked])
		{
			case 0:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
				House[nearesthouse][Locked] = 1;
			}
			case 1:
			{
				PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
				House[nearesthouse][Locked] = 0;
			}
		}
	}
	return 1;
}