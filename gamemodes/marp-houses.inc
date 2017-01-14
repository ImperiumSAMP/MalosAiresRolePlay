#if defined _marp_houses_included
	#endinput
#endif
#define _marp_houses_included


/*
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||   Sistema dinámico para creación IG de casas		  ||||||||||||||
|||||||||||||        	Pheek Gaming Latinoamérica                ||||||||||||||
|||||||||||||           			2016              			  ||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

// =============================== CONSTANTES ==================================

#define MIN_PRICE_LOCKER1           100000
#define MIN_PRICE_LOCKER2           200000
#define MIN_PRICE_LOCKER3           300000
#define MIN_PRICE_LOCKER4           400000
#define MIN_PRICE_LOCKER5           500000
#define MIN_PRICE_LOCKER6           600000
#define MIN_PRICE_LOCKER7           700000
#define MIN_PRICE_LOCKER8           800000
#define MIN_PRICE_LOCKER9           900000
#define MIN_PRICE_LOCKER10          1000000
#define MIN_PRICE_LOCKER11          1100000

#define LOCKER1_SPACE               400
#define LOCKER2_SPACE               500
#define LOCKER3_SPACE               600
#define LOCKER4_SPACE               700
#define LOCKER5_SPACE               800
#define LOCKER6_SPACE               900
#define LOCKER7_SPACE               1000
#define LOCKER8_SPACE               1100
#define LOCKER9_SPACE               1200
#define LOCKER10_SPACE              1300
#define LOCKER11_SPACE              1400

// ================================ FUNCIONES ==================================

forward LoadHouses();
forward OnHouseDataLoad(ID);
forward OnHouseDelete(ID);
forward SaveHouse(ID);
forward SaveHouses();
forward CreateHouse(ID);
forward DeleteHouse(ID);
forward GetHouseLockerSpace(houseid);
forward GetPlayerHouse(playerid);
forward PrintHouseAdress(houseid);
forward PlayerCantPayRent(playerid, houseid);
forward RentalExpirationCheck(playerid);
forward HouseHasContainer(houseid);
forward GetFirstNonCreatedHouse();
forward IsPlayerOnOutsideHouseDoor(playerid, house);
forward IsPlayerOnInsideHouseDoor(playerid, house);
forward GetPlayerNearestHouse(playerid);
forward IsTenantOrOwnerOfTheHouse(playerid, house);
forward ResetHouseOffer(playerid);

// =========================== MANEJO DE DATOS SQL =============================

stock LoadHouses()
{
	new query[128],
		ID = 1;

	while(ID < MAX_HOUSES)
	{
	    format(query, sizeof(query),"SELECT * FROM `houses` WHERE `Id` = %d", ID);
		mysql_function_query(dbHandle, query, true, "OnHouseDataLoad", "i", ID);
		ID++;
	}
	print("[INFO] casas cargadas.");
	return 1;
}

public OnHouseDataLoad(ID)
{
   	new result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows)
	{
		cache_get_field_content(0, "OwnerName", 					House[ID][OwnerName], 1, MAX_PLAYER_NAME);
		cache_get_field_content(0, "OwnerSQLID", result);			House[ID][OwnerSQLID]    	= strval(result);
		cache_get_field_content(0, "TenantName", 					House[ID][TenantName], 1, MAX_PLAYER_NAME);
		cache_get_field_content(0, "TenantSQLID", result);			House[ID][TenantSQLID]    	= strval(result);
		
		cache_get_field_content(0, "IncomePrice", result); 			House[ID][IncomePrice] 				= strval(result);
		cache_get_field_content(0, "IncomeAmount", result); 		House[ID][IncomeAmount]				= strval(result);
		cache_get_field_content(0, "RentalExpiration", result); 	House[ID][RentalExpiration]	= strval(result);
		
		cache_get_field_content(0, "HousePrice", result); 			House[ID][HousePrice] 		= strval(result);
		cache_get_field_content(0, "Money", result); 				House[ID][Money] 			= strval(result);
		cache_get_field_content(0, "Locked", result); 				House[ID][Locked]			= strval(result);
		cache_get_field_content(0, "Radio", result); 				House[ID][Radio]			= strval(result);


		cache_get_field_content(0, "EntrancePickupSQLID", result); 	House[ID][EntrancePickupSQLID]	= strval(result);
		cache_get_field_content(0, "ContainerSQLID", result); 		House[ID][ContainerSQLID] 		= strval(result);

		//===========================CARGA DE CONTENEDOR========================

		if(House[ID][ContainerSQLID] > 0)
		    House[ID][ContainerID] = Container_Load(House[ID][ContainerSQLID]);
		else
		    Container_Create(GetHouseLockerSpace(ID), 4, House[ID][ContainerID], House[ID][ContainerSQLID]);

		//======================================================================

		House[ID][Created] = 1;
	}
	return 1;
}

stock SaveHouse(ID)
{
	new query[512];

    if(House[ID][Created] == 0)
		return 1;

	format(query, sizeof(query), "UPDATE `houses` SET");

	format(query, sizeof(query), "%s `OwnerName`='%s', `OwnerSQLID`=%d, `TenantName`='%s', `TenantSQLID`=%d, `ContainerSQLID`=%d, `EntrancePickupSQLID`=%d",
		query,
	    House[ID][OwnerName],
	    House[ID][OwnerSQLID],
	    House[ID][TenantName],
	    House[ID][TenantSQLID],
	    House[ID][ContainerSQLID],
	    House[ID][EntrancePickupSQLID]
	);

	format(query, sizeof(query), "%s, `HousePrice`=%d, `Money`=%d, `Locked`=%d, `Radio`=%d, `IncomePrice`=%d, `IncomeAmount`=%d, `RentalExpiration`=%d",
		query,
		House[ID][HousePrice],
		House[ID][Money],
		House[ID][Locked],
		House[ID][Radio],
		House[ID][IncomePrice],
		House[ID][IncomeAmount],
		House[ID][RentalExpiration]
	);

	format(query, sizeof(query), "%s WHERE `Id` = %d", query, ID);

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

    format(query, sizeof(query), "INSERT INTO `houses` (Id, HousePrice)");
	format(query, sizeof(query), "%s VALUES (%d, %d)",
	    query,
	    ID,
		House[ID][HousePrice]
	);
	mysql_function_query(dbHandle, query, false, "", "");

	//=========================CREACION DE CONTENEDOR===========================

    Container_Create(GetHouseLockerSpace(ID), 10, House[ID][ContainerID], House[ID][ContainerSQLID]);

	//==========================================================================

	House[ID][Created] = 1;
	return 1;
}


// ================== OTRAS FUNCIONES / DATOS EN VARIABLES =====================


stock ResetHouse(ID)
{
 	House[ID][Created] = 0;
	House[ID][OwnerSQLID] = 0;
	House[ID][IncomePrice] = 0;
	House[ID][IncomeAmount] = 0;
	House[ID][HousePrice] = 0;
	House[ID][Money] = 0;
	House[ID][Locked] = 0;
	House[ID][Radio] = 0;
	
	if(HouseHasContainer(ID))
	{
	    Container_Fully_Destroy(House[ID][ContainerID], House[ID][ContainerSQLID]);
	    House[ID][ContainerID] = 0;
	    House[ID][ContainerSQLID] = 0;
	}

	ResetTeleport(House[ID][EntrancePickupSQLID]);
	DeleteTeleport(House[ID][EntrancePickupSQLID]);
	return 1;
}

stock DeleteHouse(ID)
{
	new query[128];
	
	format(query, sizeof(query), "DELETE FROM `houses` WHERE `Id` = %d", ID);
 	mysql_function_query(dbHandle, query, false, "", "");
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

stock PlayerCantPayRent(playerid, houseid)
{
	if(PlayerInfo[playerid][pBank] < House[houseid][IncomePrice])
	    return true;
	else
		return false;
}

stock RentalExpirationCheck(playerid)
{
	for(new i; i < MAX_HOUSES; i++)
	{
		if(House[i][TenantSQLID] == PlayerInfo[playerid][pID] && House[i][RentalExpiration] > 0)
		{
			switch(House[i][RentalExpiration])
			{
				case 5:
				{
					SendFMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmobiliaria: Señor, le queremos informar que el dueño de la vivienda que usted alquila en %s...", PrintHouseAdress(i));
					SendClientMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmobiliaria: ...ha descidido rescindirle el contrato, tiene 5 dias (paydays) para retirar sus pertenencias.");
					House[i][RentalExpiration] -= 1;
					SaveHouse(i);
				}
				case 2 .. 4:
				{
					SendFMessage(playerid,COLOR_LIGHTGREEN,"Te quedan %d paydays para finalizar el contrato de tu alquiler en %s, retira tus cosas antes o las perderás.", House[i][RentalExpiration], PrintHouseAdress(i));
					House[i][RentalExpiration] -= 1;
					SaveHouse(i);
				}
				case 1:
				{
					SendFMessage(playerid, COLOR_WHITE, "Te han desalojado de tu vivienda en %s, todo lo que hayas dejado dentro dalo por perdido.", PrintHouseAdress(i));
					House[i][TenantSQLID] = 0;
					format(House[i][TenantName], 24, "Ninguno.");
					House[i][Locked] = 1;
					House[i][RentalExpiration] = 0;
					SaveHouse(i);
				}
			}
		}
	}
}

stock HouseHasContainer(houseid)
{
	if(House[houseid][ContainerSQLID] > 0 && House[houseid][ContainerID] > 0)
	    return 1;
	return 0;
}

stock GetFirstNonCreatedHouse()
{
	for(new i = 1; i < MAX_HOUSES; i++)
		if(House[i][Created] == 0)
			return i;
	
	return 0;
}

stock IsPlayerOnHouseDoor(playerid, house, bool:Outside)
{
	new tpid = House[house][EntrancePickupSQLID];
	
	if(Outside)
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
			return true;
	else
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][SecondX], Teleport[tpid][SecondY], Teleport[tpid][SecondZ]) && Teleport[tpid][SecondVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][SecondInt] == GetPlayerInterior(playerid))
			return true;

	return false;
}

stock GetPlayerNearestHouse(playerid)
{
	new tpid, house[2], housecount;

	for(house[0] = 1;house[0] < MAX_HOUSES; house[0]++)
	{
	    tpid = House[house[0]][EntrancePickupSQLID];
		if(PlayerToPoint(1.0, playerid, Teleport[tpid][FirstX], Teleport[tpid][FirstY], Teleport[tpid][FirstZ]) && Teleport[tpid][FirstVW] == GetPlayerVirtualWorld(playerid) && Teleport[tpid][FirstInt] == GetPlayerInterior(playerid))
		{
			housecount++;
			house[1] = house[0];
		}
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

stock ResetHouseOffer(playerid)
{
    OfferingHouse[playerid] = false;
	HouseOfferPrice[playerid] = -1;
	HouseOffer[playerid][0] = INVALID_PLAYER_ID;
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
	new radio, houseid, radioamount, string[128];
	houseid = GetPlayerHouse(playerid);
	radioamount = Radio_GetAmount();

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /casaradio [ID radio]");
	if(House[houseid][TenantSQLID] != PlayerInfo[playerid][pID] && House[houseid][OwnerSQLID] != PlayerInfo[playerid][pID])
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No estás en tu casa.");
	if(radio < 0 || radio > radioamount)
	{
		format(string, sizeof(string), "Debes ingresar una emisora de radio válida: del 0 al %d.", radioamount);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
		return 1;
	}

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
			format(House[nearesthouse][OwnerName], MAX_PLAYER_NAME, "%s", GetPlayerNameEx(playerid));
				
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
			format(House[nearesthouse][OwnerName], 25, "Ninguno.");
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
				House[nearesthouse][RentalExpiration] = 0;
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
			HouseOffer[targetid][0] = playerid;
			HouseOffer[targetid][1] = nearesthouse;
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
	new sellerid = HouseOffer[playerid][0],
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

	houseid = HouseOffer[playerid][1];
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
		House[houseid][RentalExpiration] = 0;
	}
	
	GivePlayerCash(playerid, -price);
    GivePlayerCash(sellerid, price);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(sellerid, 1052, 0.0, 0.0, 0.0);
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
	if(HouseOffer[playerid][0] == INVALID_PLAYER_ID)
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
		SendClientMessage(HouseOffer[playerid][0], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 10 segundos.");
	}
	else
		if(reason == 0)
		{
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la oferta.");
			SendFMessage(HouseOffer[playerid][0], COLOR_LIGHTBLUE, "%s ha rechazado la oferta.", GetPlayerNameEx(playerid));
		}

 	ResetHouseOffer(HouseOffer[playerid][0]);
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
	
	if(!IsTenantOrOwnerOfTheHouse(playerid, nearesthouse) && !AdminDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de esta casa!");
	
	if(GetPlayerHouse(playerid) == 0) // Del lado de afuera.
	{

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

//========================COMANDOS DE ALQUILER DE CASAS=========================

CMD:casaalquilar(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid),
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][TenantSQLID] != 0 || House[nearesthouse][IncomePrice] == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta casa no está disponible para alquilar!");
			if(House[nearesthouse][OwnerSQLID] == PlayerInfo[playerid][pID])
			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes alquilar tu propia casa!");
			if(GetPlayerCash(playerid) < House[nearesthouse][IncomePrice])
			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
			    
			House[nearesthouse][TenantSQLID] = PlayerInfo[playerid][pID];
			format(House[nearesthouse][TenantName], MAX_PLAYER_NAME, "%s", name);

			GivePlayerCash(playerid, -House[nearesthouse][IncomePrice]);
			SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has alquilado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
			PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y éste le entrega un par de llaves.");
			
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casadesalquilar(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid),
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][TenantSQLID] != 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa que alquilas!");

			House[nearesthouse][TenantSQLID] = 0;
			format(House[nearesthouse][TenantName], 24, "Ninguno.");
			House[nearesthouse][Locked] = 1;
			
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, COLOR_WHITE, "¡Has dejado de alquilar la casa!");
			PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casaenalquiler(playerid, params[])
{

	new nearesthouse = GetPlayerNearestHouse(playerid), price, string[128];

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Esta casa no es tuya!");
			if(sscanf(params, "i", price))
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /casaenalquiler [Precio]");
			if(House[nearesthouse][TenantSQLID] != 0)
			    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "La casa actualmente tiene un inquilino. Puedes rescindirle el contrato con '/casacontrato'.");
			if(price > (House[nearesthouse][HousePrice] / 100))
			{
				format(string, sizeof(string), "El monto máximo de alquiler que puedes pedir para esta casa es de $%d.", (House[nearesthouse][HousePrice] / 100));
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
				return 1;
			}

			SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} Colocaste tu casa en alquiler por $%d, si alguien la alquila no podras utilizar el armario.", price);
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} El pago del alquiler se realiza por cada payday del inquilino y lo recibirás al cobrar tu payday.");
			House[nearesthouse][IncomePrice] = price;
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casasinalquiler(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid);

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Esta casa no es tuya!");
			if(House[nearesthouse][TenantSQLID] != 0)
			    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "La casa actualmente tiene un inquilino. Puedes rescindirle el contrato con '/casacontrato'.");
			if(House[nearesthouse][IncomePrice] > 0)
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Tu casa no está en alquiler actualmente!");

			SendClientMessage(playerid, COLOR_LIGHTYELLOW2,"{878EE7}[INFO]{C8C8C8} Tu casa ya no se encuentra disponible para ser alquilada.");
			House[nearesthouse][IncomePrice] = 0;
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}

CMD:casacontrato(playerid, params[])
{
	new nearesthouse = GetPlayerNearestHouse(playerid);

	switch(nearesthouse)
	{
		case -1: return SendClientMessage(playerid, COLOR_YELLOW2, "¡Hay más de una casa en tu posición! Reportar a un administrador.");
	    case 0: return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en la entrada de una casa!");
	    default:
	    {
			if(House[nearesthouse][OwnerSQLID] != PlayerInfo[playerid][pID])
				return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Esta casa no es tuya!");
			if(House[nearesthouse][IncomePrice] == 0)
			    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Esta casa no está en alquiler!");
			if(House[nearesthouse][TenantSQLID] == 0)
			    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡Esta casa no tiene un inquilino!");

			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]{C8C8C8} El inquilino en breve será informado de la rescisión del contrato de alquiler. Dentro de 5 paydays será desalojado.");
			House[nearesthouse][RentalExpiration] = 5;
			SaveHouse(nearesthouse);
	    }
	}
	return 1;
}


// COMANDOS ADMINISTRATIVOS

CMD:acasas(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "==============================[COMANDOS DE ADMIN PARA CASAS]==============================");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 3]{C8C8C8} /actele");
	if(PlayerInfo[playerid][pAdmin] >= 4)
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 4]{C8C8C8} /acinfo");
	if(PlayerInfo[playerid][pAdmin] >= 5)
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 5]{C8C8C8} /acalquilar - /acnoalquilar");
	if(PlayerInfo[playerid][pAdmin] >= 20)
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 20]{C8C8C8} /accrear - /acborrar - /acprecio - /acvender");
    	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{C8C8C8}Para setear posiciones deberás usar los comandos de /ateleports.");
	}
	return 1;
}

CMD:acprecio(playerid, params[])
{
	new houseid,
		price,
		string[128];

    if(sscanf(params, "ii", houseid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acprecio [ID casa] [Precio]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][HousePrice] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	if(price < 1 || price > 80000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige un precio entre $1 y $80.000.000.");
	    
	House[houseid][HousePrice] = price;
	format(string, sizeof(string), "{878EE7}[INFO]{C8C8C8} el precio de la casa %d ha sido ajustado a $%d.", houseid, price);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	
	if(HouseHasContainer(houseid))
	{
	    Container_Empty(House[houseid][ContainerID]);
	    Container_SetTotalSpace(House[houseid][ContainerID], GetHouseLockerSpace(houseid));
	}
	    
	SaveHouse(houseid);
	return 1;
}

CMD:acvender(playerid, params[])
{
	new houseid,
		string[128];
	
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acvender [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    

	House[houseid][OwnerSQLID] = 0;
	format(House[houseid][OwnerName], 24, "");
	House[houseid][TenantSQLID] = 0;
	format(House[houseid][TenantName], 24, "");
	House[houseid][Locked] = 1;
	House[houseid][Money] = 0;
	House[houseid][Radio] = 0;
    House[houseid][IncomePrice] = 0;
    House[houseid][RentalExpiration] = 0;
	House[houseid][IncomeAmount] = 0;
	
	if(HouseHasContainer(houseid))
	    Container_Empty(House[houseid][ContainerID]);
	
	SaveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]{C8C8C8} la casa %d ha sido vendida.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:accrear(playerid, params[])
{
	new price,
		houseid = GetFirstNonCreatedHouse(),
		tpid = GetFirstNonCreatedTeleport(),
		Float:Pos[3],
		Float:angle;

    if(sscanf(params, "i", price))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /accrear [precio de la casa] [tipo de casa]");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} Tipos de casa posibles: 1. Pobre | 2. Clase media | 3. Clase media alta | 4. Clase alta | 5. Mansión ");
	}
	if(price < 1 || price > 80000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige un precio de $1 a $80.000.000.");
	if(houseid == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Todas las casas están creadas. Reportar a un scripter.");
	
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	GetPlayerFacingAngle(playerid, angle);
	
	ResetHouse(houseid);
	House[houseid][HousePrice] = price;
	CreateTeleport(Pos[0], Pos[1], Pos[2], angle+180, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid),
	PlayerInfo[playerid][pCurrentHouse], PlayerInfo[playerid][pCurrentBiz], PlayerInfo[playerid][pCurrentBuilding],
	225.756989, 1240.000000, 1082.149902, angle+180, 2, 15000 + houseid, houseid, 0, 0, 1239, 1239, TYPE_HOUSE);
	CreateHouse(houseid);
	House[houseid][EntrancePickupSQLID] = tpid;
	SaveHouse(houseid);
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO] {C8C8C8}has creado la casa ID %d.", houseid);
	return 1;
}

CMD:acborrar(playerid, params[])
{
	new houseid;

    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acborrar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");

	ResetHouse(houseid);
	DeleteHouse(houseid);
	
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} la casa %d ha sido BORRADA.", houseid);
	return 1;
}

CMD:acinfo(playerid, params[])
{
	new id;

	if(sscanf(params, "i", id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acinfo [ID casa]");
	if(id < 1 || id >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[id][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");

	SendFMessage(playerid, COLOR_WHITE, "=======================[Casa %d]=======================", id);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño SQLID: %d", House[id][OwnerSQLID]);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s", House[id][OwnerName]);
	SendFMessage(playerid, COLOR_WHITE, "- Inquilino SQLID: %d", House[id][TenantSQLID]);
	SendFMessage(playerid, COLOR_WHITE, "- Inquilino: %s", House[id][TenantName]);
	SendFMessage(playerid, COLOR_WHITE, "- Costo de compra: $%d", House[id][HousePrice]);
	SendFMessage(playerid, COLOR_WHITE, "- Dinero: %d", House[id][Money]);
 	SendFMessage(playerid, COLOR_WHITE, "- Cerrada: %d", House[id][Locked]);
 	SendFMessage(playerid, COLOR_WHITE, "- Costo de alquiler: $%d", House[id][IncomePrice]);
 	SendFMessage(playerid, COLOR_WHITE, "- Ganancias: $%d", House[id][IncomeAmount]);
 	SendFMessage(playerid, COLOR_WHITE, "- Aviso de desalojo: $%d", House[id][RentalExpiration]);
	return 1;
}

CMD:actele(playerid, params[])
{
	new houseid, interior, virtualworld, Float:pos[3];

	if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /actele [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	    
	pos[0] = Teleport[House[houseid][EntrancePickupSQLID]][FirstX];
	pos[1] = Teleport[House[houseid][EntrancePickupSQLID]][FirstY];
	pos[2] = Teleport[House[houseid][EntrancePickupSQLID]][FirstZ];
	interior = 	Teleport[House[houseid][EntrancePickupSQLID]][FirstInt];
	virtualworld = 	Teleport[House[houseid][EntrancePickupSQLID]][FirstInt];
	
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SetPlayerInterior(playerid, interior);
	SetPlayerVirtualWorld(playerid, virtualworld);
	return 1;
}

CMD:acalquilar(playerid, params[])
{
	new houseid;

    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	if(House[houseid][TenantSQLID] != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
	
	House[houseid][IncomePrice] = House[houseid][HousePrice] / 100;
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} el precio de alquiler de la casa %d ha sido ajustado a $%d.", houseid, House[houseid][IncomePrice]);
	SaveHouse(houseid);
	return 1;
}

CMD:acnoalquilar(playerid, params[])
{
	new houseid;

    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]{C8C8C8} /acalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Created] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida: la casa no está creada.");
	
	House[houseid][IncomePrice] = 0;
	House[houseid][TenantSQLID] = 0;
	House[houseid][RentalExpiration] = 0;
	format(House[houseid][TenantName], 24, "");
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]{C8C8C8} el alquiler en la casa ID %d fue retirado.", houseid);
	SaveHouse(houseid);
	return 1;
}