#if defined _isamp_houses_included
	#endinput
#endif
#define _isamp_houses_included

//========================SISTEMA Y COMANDOS DE CASA============================

//================================CONSTANTES====================================

#define MAX_HOUSES              200

//============================VARIABLES INTERNAS================================

enum HouseSystem {
	Owner[MAX_PLAYER_NAME],
	Float:EntranceX,
	Float:EntranceY,
	Float:EntranceZ,
	EntranceInterior,
	Float:EntranceAngle,
	Float:ExitX,
	Float:ExitY,
	Float:ExitZ,
	ExitInterior,
	Float:ExitAngle,
	Owned,
	Tenant[MAX_PLAYER_NAME],
	IncomeAccept,
	Income,
	IncomePrice,
	IncomePriceAdd,
	InsideWorld,
	HousePrice,
	Money,
	Locked,
	hEntrancePickup,
	hExitPickup,
	Text3D:hEntranceLabel,
	Text3D:hExitLabel,
	Marijuana,
	LSD,
	Ecstasy,
	Cocaine,
	hRadio
};

new House[MAX_HOUSES][HouseSystem];

// Venta de casas

new
	bool:OfferingHouse[MAX_PLAYERS],
	HouseOfferPrice[MAX_PLAYERS],
	HouseOffer[MAX_PLAYERS];
	
//================================FUNCIONES=====================================

forward ResetHouseOffer(playerid);
forward GetPlayerHouse(playerid);
forward bool:EnterHouse(playerid);
forward bool:LeaveHouse(playerid);

//========================IMPLEMENTACION DE FUNCIONES===========================
	
stock ResetHouseOffer(playerid)
{
    OfferingHouse[playerid] = false;
	HouseOfferPrice[playerid] = -1;
	HouseOffer[playerid] = INVALID_PLAYER_ID;
}

stock GetPlayerHouse(playerid)
{
	for(new i = 1; i < MAX_HOUSES; i++)
	{
	    if(House[i][ExitInterior] == GetPlayerInterior(playerid) && House[i][InsideWorld] == GetPlayerVirtualWorld(playerid) && House[i][InsideWorld] != 0)
			return i;
	}
	return 0;
}

stock bool:EnterHouse(playerid)
{
	for(new i = 1; i < MAX_HOUSES; i++)
	{
		if(PlayerToPoint(1.0, playerid,House[i][EntranceX], House[i][EntranceY], House[i][EntranceZ]))
		{
			if(House[i][Locked] == 0 || AdminDuty[playerid])
			{
				SetPlayerInterior(playerid,House[i][ExitInterior]);
				SetPlayerPos(playerid,House[i][ExitX], House[i][ExitY], House[i][ExitZ]);
				SetPlayerVirtualWorld(playerid, House[i][InsideWorld]);
				SetPlayerFacingAngle(playerid, House[i][ExitAngle]);
				SetCameraBehindPlayer(playerid);
				PlayRadioStreamForPlayer(playerid, House[i][hRadio]);
			} else
				GameTextForPlayer(playerid, "~r~Cerrado!", 2000, 4);
			return true;
		}
	}
	return false;
}

stock bool:LeaveHouse(playerid)
{
	for(new i = 0; i < sizeof(House); i++)
	{
		if(PlayerToPoint(1.0, playerid, House[i][ExitX], House[i][ExitY], House[i][ExitZ]))
		{
			if(GetPlayerVirtualWorld(playerid) == House[i][InsideWorld])
			{
		        if(House[i][Locked] == 0 || AdminDuty[playerid])
				{
					SetPlayerInterior(playerid,House[i][EntranceInterior]);
					SetPlayerPos(playerid,House[i][EntranceX],House[i][EntranceY],House[i][EntranceZ]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerFacingAngle(playerid,House[i][EntranceAngle]);
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
			saveHouse(PlayerInfo[playerid][pHouseKeyIncome]);
			PlayerInfo[playerid][pHouseKeyIncome] = 0;
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 3)
	    {
	        SendClientMessage(playerid, COLOR_WHITE, "En el próximo payday rescinde el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
	        House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 2;
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 4)
	    {
            SendClientMessage(playerid, COLOR_WHITE, "Te quedan 2 paydays antes de que rescinda el contrato de la vivienda en la cual vives, retira tus cosas antes o te desalojaran y las perderas.");
            House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 3;
		} else if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] == 5)
	    {
	        SendClientMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmoviliaria: Señor, le queremos informar que el dueño de la vivienda la cual usted alquila ha decidido...");
    		SendClientMessage(playerid,COLOR_LIGHTGREEN,"SMS de Inmoviliaria: ...rescindirle el contrato, tiene 3 dias (paydays) para retirar sus pertenencias.");
            House[PlayerInfo[playerid][pHouseKeyIncome]][Income] = 4;
		}
	}
	
}

GetPlayerHouseAddress(playerid)
{
	new targetid, houselocation[MAX_ZONE_NAME];
	
    if(PlayerInfo[playerid][pHouseKey] != 0 && House[PlayerInfo[playerid][pHouseKey]][Income]!= 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
	    GetCoords2DZone(House[PlayerInfo[playerid][pHouseKeyIncome]][EntranceX],House[PlayerInfo[playerid][pHouseKeyIncome]][EntranceY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKeyIncome], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0 && House[PlayerInfo[playerid][pHouseKey]][Income]!= 0)
	{
	    SendClientMessage(targetid, COLOR_WHITE, "Domicilio: No tiene");
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
	    GetCoords2DZone(House[PlayerInfo[playerid][pHouseKeyIncome]][EntranceX],House[PlayerInfo[playerid][pHouseKeyIncome]][EntranceY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKey], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] != 0)
	{
		GetCoords2DZone(House[PlayerInfo[playerid][pHouseKey]][EntranceX],House[PlayerInfo[playerid][pHouseKey]][EntranceY], houselocation, MAX_ZONE_NAME);
		SendFMessage(targetid, COLOR_WHITE, "Domicilio: %d %s", PlayerInfo[playerid][pHouseKey], houselocation);
	}
	else if(PlayerInfo[playerid][pHouseKey] == 0 && PlayerInfo[playerid][pHouseKeyIncome] != 0)
	{
		GetCoords2DZone(House[PlayerInfo[playerid][pHouseKey]][EntranceX],House[PlayerInfo[playerid][pHouseKey]][EntranceY], houselocation, MAX_ZONE_NAME);
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
	new
	    radio,
	    houseid = GetPlayerHouse(playerid);

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casaradio [ID radio]");
	if(houseid == 0 || houseid != PlayerInfo[playerid][pHouseKey])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en tu casa.");
	if(radio < 0 || radio > 15)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio válida: del 1 al 15. Usa 0 para dejarlo sin radio.");

    House[houseid][hRadio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "{878EE7}[INFO]:{C8C8C8} Has seteado la radio de tu casa a %d.", House[houseid][hRadio]);
	PlayRadioStreamForPlayer(playerid, House[houseid][hRadio]);
	return 1;
}

CMD:casacomprar(playerid, params[])
{
    new name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(PlayerInfo[playerid][pHouseKey] != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tener más de una casa!");
		
    for(new h = 0; h < sizeof(House); h++)
	{
		if(PlayerToPoint(2.0, playerid, House[h][EntranceX], House[h][EntranceY], House[h][EntranceZ]) && House[h][Owned] == 0)
		{
		    if(House[h][Tenant] == PlayerInfo[playerid][pName])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes comprar la casa que alquilas!");
		    if(House[h][HousePrice] <= 0)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta casa no tiene precio!, probablemente no está a la venta.");
			if(GetPlayerCash(playerid) < House[h][HousePrice])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
						
			PlayerInfo[playerid][pHouseKey] = h;
			House[h][Owned] = 1;
			strmid(House[h][Owner], name, 0, strlen(name), 255);
			GivePlayerCash(playerid, -House[h][HousePrice]);
			SetPlayerInterior(playerid, House[h][ExitInterior]);
			SetPlayerVirtualWorld(playerid, h + 15000);
			SetPlayerPos(playerid, House[h][ExitX], House[h][ExitY], House[h][ExitZ]);
			SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has comprado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
		   	PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y este le entrega un par de llaves.");
			saveHouse(h);
			return 1;
		}
    }
	return 1;
}

CMD:casavender(playerid, params[])
{
	new
	    house = PlayerInfo[playerid][pHouseKey],
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
	if(!PlayerToPoint(1.0, playerid, House[house][EntranceX], House[house][EntranceY], House[house][EntranceZ]))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu casa para venderla!");
	if(strcmp(House[house][Owner], name, true) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");

	if(House[house][Income] >= 1)
	{
	    House[house][IncomePrice] = House[house][HousePrice] / 100;
	}
	House[house][Locked] = 1;
	House[house][Owned] = 0;
	strmid(House[house][Owner], "Ninguno", 0, strlen("Ninguno"), 255);
	GivePlayerCash(playerid, House[house][HousePrice] / 3 * 2); // 66 % del valor original.
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendFMessage(playerid, COLOR_WHITE, "¡Has vendido tu casa por $%d!", House[house][HousePrice] / 3 * 2);
	PlayerInfo[playerid][pHouseKey] = 0;
	PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
	saveHouse(house);
	return 1;
}

CMD:casavendera(playerid, params[])
{
	new
		house = PlayerInfo[playerid][pHouseKey],
		targetid,
		price,
		name[MAX_PLAYER_NAME];

	if(sscanf(params, "ui", targetid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casavendera [ID/Jugador] [Precio]");
	if(house == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener una casa para utilizar este comando!");
    if(!PlayerToPoint(2.0, playerid, House[house][EntranceX], House[house][EntranceY], House[house][EntranceZ]))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la puerta de tu casa.");
   	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
  	if(price < 1 || price > 10000000)
   		return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $10,000,000.");
  	if(OfferingHouse[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras vendiendo una casa.");
	if(!ProxDetectorS(4.0, playerid, targetid))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
	GetPlayerName(playerid, name, sizeof(name));
    if(strcmp(House[house][Owner], name, true) != 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");

	OfferingHouse[playerid] = true;
	HouseOfferPrice[targetid] = price;
	HouseOffer[targetid] = playerid;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le ofreces las llaves y escritura de tu casa a %s por $%d.", GetPlayerNameEx(targetid), price);
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te esta ofreciendo venderte su casa por $%d.", GetPlayerNameEx(playerid), price);
	SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/casaaceptar' para aceptar la oferta o '/casacancelar' para cancelar.");
	SetPVarInt(targetid, "CancelHouseTransfer", SetTimerEx("CancelHouseTransfer", 15 * 1000, false, "ii", targetid, 1));
	return 1;
}

CMD:casaaceptar(playerid, params[])
{
	new
		sellerid = HouseOffer[playerid],
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
	if(!ProxDetectorS(4.0, playerid, sellerid))
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

	houseid = PlayerInfo[sellerid][pHouseKey];
	GetPlayerName(playerid, name, sizeof(name));
	House[houseid][Locked] = 1;
	House[houseid][Owned] = 1;
	strmid(House[houseid][Owner], name, 0, strlen(name), 255);
	GivePlayerCash(playerid, -price);
    GivePlayerCash(sellerid, price);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(sellerid, 1052, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pHouseKey] = houseid;
    PlayerInfo[sellerid][pHouseKey] = 0;
    PlayerPlayerActionMessage(sellerid, playerid, 15.0 , "toma las llaves y la escritura de su casa y se las entrega a");
  	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Felicidades, has comprado la casa por $%d! Usa /ayudacasa para ver los comandos disponibles.", price);
  	SendFMessage(sellerid, COLOR_LIGHTBLUE, "¡Felicitaciones, has vendido tu casa por $%d!", price);
  	KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	CancelHouseTransfer(playerid, 2);
	return 1;
}

CMD:casacancelar(playerid, params[])
{
	new sellerid = HouseOffer[playerid];

	if(sellerid == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo una casa.");
    	
 	KillTimer(GetPVarInt(playerid, "CancelHouseTransfer"));
	CancelHouseTransfer(playerid, 0);
	return 1;
}

TIMER:CancelHouseTransfer(playerid, reason)
{
	if(reason == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que no has respondido en 15 segundos.");
		SendClientMessage(HouseOffer[playerid], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 15 segundos.");
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
    new
	    house = PlayerInfo[playerid][pHouseKey],
	    houseincome = PlayerInfo[playerid][pHouseKeyIncome],
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));
	if(house != 0 || houseincome != 0)
	{
		if(PlayerToPoint(1.0, playerid, House[house][EntranceX], House[house][EntranceY], House[house][EntranceZ]) || (PlayerToPoint(2.0, playerid, House[house][ExitX], House[house][ExitY], House[house][ExitZ]) && GetPlayerVirtualWorld(playerid) == house + 15000))
		{
		    if(House[house][Locked] == 1)
			{
				House[house][Locked] = 0;
			    PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
			} else {
				House[house][Locked] = 1;
		        PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
			}
			return 1;
		}
		if(PlayerToPoint(1.0, playerid, House[houseincome][EntranceX], House[houseincome][EntranceY], House[houseincome][EntranceZ]) || (PlayerToPoint(2.0, playerid, House[houseincome][ExitX], House[houseincome][ExitY], House[houseincome][ExitZ]) && GetPlayerVirtualWorld(playerid) == houseincome + 15000))
		{
	        if(House[houseincome][Locked] == 1)
			{
				House[houseincome][Locked] = 0;
			    PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y abre la puerta.");
			} else {
				House[houseincome][Locked] = 1;
		        PlayerActionMessage(playerid, 15.0, "toma las llaves de su casa y cierra la puerta.");
			}
			return 1;
		}
	} else {
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes una casa ni alquilas una!");
	}
	return 1;
}

//========================COMANDOS DE ALQUILER DE CASAS=========================
CMD:casaalquilar(playerid, params[])
{
    new name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

    for(new h = 0; h < sizeof(House); h++)
	{
		if(PlayerToPoint(2.0, playerid, House[h][EntranceX], House[h][EntranceY], House[h][EntranceZ]) && House[h][Income] == 0)
		{
		    if(House[h][Owner] == PlayerInfo[playerid][pName])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes alquilar tu propia casa!");
            if(PlayerInfo[playerid][pHouseKeyIncome] != 0)
				return 1;
		    if(House[h][IncomePrice] <= 0)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Esta casa no tiene precio!, probablemente no está en alquiler.");
			if(GetPlayerCash(playerid) < House[h][IncomePrice])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");

			PlayerInfo[playerid][pHouseKeyIncome] = h;
			House[h][Income] = 1;
			strmid(House[h][Tenant], name, 0, strlen(name), 255);
			GivePlayerCash(playerid, -House[h][IncomePrice]);
			SetPlayerInterior(playerid, House[h][ExitInterior]);
			SetPlayerVirtualWorld(playerid, h + 15000);
			SetPlayerPos(playerid, House[h][ExitX], House[h][ExitY], House[h][ExitZ]);
			SendClientMessage(playerid, COLOR_WHITE, "¡Felicidades, has alquilado esta propiedad! Para ver los comandos disponibles utiliza /ayudacasa.");
		   	PlayerActionMessage(playerid, 15.0, "le da un paquete lleno de dinero al agente inmobiliario y este le entrega un par de llaves.");
			saveHouse(h);
			return 1;
		}
    }
	return 1;
}

CMD:casadesalquilar(playerid, params[])
{
    new
	    house = PlayerInfo[playerid][pHouseKeyIncome],
	    name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(house == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes alquilar una casa para utilizar este comando!");
	if(!PlayerToPoint(1.0, playerid, House[house][EntranceX], House[house][EntranceY], House[house][EntranceZ]))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de la casa que alquilas para desalquilar la misma!");
	if(strcmp(House[house][Tenant], name, true) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, la casa no está a tu nombre (Consulta a un administrador).");

    if(House[house][Owned] == 0)
	{
	    House[house][IncomePrice] = House[house][HousePrice] / 100;
	}
	House[house][Locked] = 1;
	House[house][Income] = 0;
	strmid(House[house][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, COLOR_WHITE, "¡Has dejado de alquilar la casa!");
	PlayerInfo[playerid][pHouseKeyIncome] = 0;
	PlayerActionMessage(playerid, 15.0 , "toma las llaves de su casa y se las entrega al agente inmobiliario.");
	saveHouse(house);
	return 1;
}

CMD:casaenalquiler(playerid, params[])
{
	new
		houseid,
		price,
		string[128];

    if(sscanf(params, "ii", houseid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casaenalquiler [ID casa] [Precio]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
    if(House[houseid][Owner] != PlayerInfo[playerid][pName])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes alquilar una casa que no es de tu propiedad!");
	if(House[houseid][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
	if(price > House[houseid][HousePrice] / 100)
	{
		format(string, sizeof(string), "[INFO]: El máximo permitido de alquiler es de %d.", House[houseid][HousePrice] / 100);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		return 1;
	}
	    
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Colocaste tu casa en alquiler por $%d, si alguien la alquila no podras utilizar el '/armario'.", price);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} El pago del alquiler se realiza por cada payday del inquilino y lo recibirás al cobrar tu payday.");

	House[houseid][IncomePrice] = price;
	House[houseid][IncomeAccept] = 1;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);

	saveHouse(houseid);
	return 1;
}

CMD:casasinalquiler(playerid, params[])
{
	new houseid,
		price;

    if(sscanf(params, "ii", houseid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casasinalquiler [ID casa] [Precio]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Owner] != PlayerInfo[playerid][pName])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes alquilar una casa que no es de tu propiedad!");
	if(House[houseid][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
		
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} Ya has sacado tu casa de alquiler.");

	House[houseid][IncomePrice] = 0;
	House[houseid][IncomeAccept] = 0;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);

	saveHouse(houseid);
	return 1;
}

CMD:casacontrato(playerid, params[])
{
	new
		houseid;

    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /casacontrato [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Owner] != PlayerInfo[playerid][pName])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes rescindir el contrato de una casa que no es de tu propiedad!");
	if(House[houseid][Income] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa no tiene un inquilino.");

	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} El inquilino en breve será informado de que haz rescindido el contrato de alquiler...");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} ...dentro de 3 paydays será desalojada la vivienda.");

	House[houseid][Income] = 5;
	saveHouse(houseid);
	return 1;
}

//=========================COMANDOS DE ADMIN DE CASAS===========================

CMD:acasas(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[COMANDOS]:{C8C8C8} /acinfo - /acdisp - /acentrada - /acsalida - /actele - /acprecio - /acvender - /acinterior");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[COMANDOS]:{C8C8C8} /acalquilar - /acnoalquilar");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} para agregar una casa consulta con el comando '/acdisp' qué casa está disponible para ser añadida.");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{C8C8C8}Deberás estar mirando hacia la puerta para que el ángulo de salida sea el correcto.");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{C8C8C8}No utilizar '/acalquilarall' si ya fue utilizado.");
	return 1;
}

CMD:acdisp(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] == 20)
	{
    	for(new c = 1; c < MAX_HOUSES; c++)
		{
		    if(House[c][HousePrice] == 0)
		    {
		        new string[128];
		    	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la próxima casa disponible para su colocación es la: %d.", c);
				SendClientMessage(playerid, COLOR_ADMINCMD, string);
				return 1;
			}
		}
	}
	return 1;
}

CMD:acinterior(playerid, params[])
{
	new
	    houseid,
	    interiorid,
	    string[128];
	    
	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
	if(sscanf(params, "ii", houseid, interiorid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acinfo [ID casa] [ID interior (1-42)]");
 	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(interiorid < 1 ||interiorid > 42)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El interior debe estar entre 1-42.");

	switch(interiorid)
	{
	    case 1:
		{
			House[houseid][ExitX] = 235.508994;
			House[houseid][ExitY] = 1189.169897;
			House[houseid][ExitZ] = 1080.339966;
			House[houseid][ExitInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
   		}
		case 2:
		{
			House[houseid][ExitX] = 225.756989;
			House[houseid][ExitY] = 1240.000000;
			House[houseid][ExitZ] = 1082.149902;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
  				}
		case 3:
		{
			House[houseid][ExitX] = 223.043991;
			House[houseid][ExitY] = 1289.259888;
			House[houseid][ExitZ] = 1082.199951;
			House[houseid][ExitInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 4:
		{
			House[houseid][ExitX] = 225.630997;
			House[houseid][ExitY] = 1022.479980;
			House[houseid][ExitZ] = 1084.069946;
			House[houseid][ExitInterior] = 7;
			format(string, sizeof string, "Casa: %d - descripción: muy grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 5:
		{
			House[houseid][ExitX] = 295.138977;
			House[houseid][ExitY] = 1474.469971;
			House[houseid][ExitZ] = 1080.519897;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 6:
		{
			House[houseid][ExitX] = 327.9199;
			House[houseid][ExitY] = 1477.7240;
			House[houseid][ExitZ] = 1084.4375;
			House[houseid][ExitAngle] = 177.3231 + 180;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 7:
	 	{
			House[houseid][ExitX] = 387.2003;
			House[houseid][ExitY] = 1471.7095;
			House[houseid][ExitZ] = 1080.1949;
			House[houseid][ExitAngle] = 270.7622 + 180;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD,string);
		}
		case 8:
		{
			House[houseid][ExitX] = 375.971985;
			House[houseid][ExitY] = 1417.269897;
			House[houseid][ExitZ] = 1081.409912;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
		case 9:
		{
			House[houseid][ExitX] = 490.810974;
			House[houseid][ExitY] = 1401.489990;
			House[houseid][ExitZ] = 1080.339966;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
     	case 10:
		{
			House[houseid][ExitX] = 447.734985;
			House[houseid][ExitY] = 1400.439941;
			House[houseid][ExitZ] = 1084.339966;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
        case 11:
		{
			House[houseid][ExitX] = 227.722992;
			House[houseid][ExitY] = 1114.389893;
			House[houseid][ExitZ] = 1081.189941;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 12:
		{
			House[houseid][ExitX] = 260.983978;
			House[houseid][ExitY] = 1286.549927;
			House[houseid][ExitZ] = 1080.299927;
			House[houseid][ExitInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 13:
		{
			House[houseid][ExitX] = 221.666992;
			House[houseid][ExitY] = 1143.389893;
			House[houseid][ExitZ] = 1082.679932;
			House[houseid][ExitInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 14:
		{
			House[houseid][ExitX] = 27.132700;
			House[houseid][ExitY] = 1341.149902;
			House[houseid][ExitZ] = 1084.449951;
			House[houseid][ExitInterior] = 10;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 15:
		{
			House[houseid][ExitX] = -262.601990;
			House[houseid][ExitY] = 1456.619995;
			House[houseid][ExitZ] = 1084.449951;
			House[houseid][ExitInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: grande - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 16:
		{
			House[houseid][ExitX] = 22.778299;
			House[houseid][ExitY] = 1404.959961;
			House[houseid][ExitZ] = 1084.449951;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 17:
		{
			House[houseid][ExitX] = 140.278000;
			House[houseid][ExitY] = 1368.979980;
			House[houseid][ExitZ] = 1083.969971;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: grande - 4 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 18:
		{
			House[houseid][ExitX] = 234.045990;
			House[houseid][ExitY] = 1064.879883;
			House[houseid][ExitZ] = 1084.309937;
			House[houseid][ExitInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: grande - 3 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 19:
		{
			House[houseid][ExitX] = -68.294098;
			House[houseid][ExitY] = 1353.469971;
			House[houseid][ExitZ] = 1080.279907;
			House[houseid][ExitInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - ningún dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 20:
		{
			House[houseid][ExitX] = -285.548981;
			House[houseid][ExitY] = 1470.979980;
			House[houseid][ExitZ] = 1084.449951;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 1 dormitorio - 1 living room - 1 cocina", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
    	}
    	case 21:
		{
			House[houseid][ExitX] = -42.581997;
			House[houseid][ExitY] = 1408.109985;
			House[houseid][ExitZ] = 1084.449951;
			House[houseid][ExitInterior] = 8;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - ningún dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 22:
		{
			House[houseid][ExitX] = 83.0659;
			House[houseid][ExitY] = 1322.3271;
			House[houseid][ExitZ] = 1083.8662;
			House[houseid][ExitAngle] = 175.1501 + 180;
			House[houseid][ExitInterior] = 9;
			format(string, sizeof string, "Casa: %d - descripción: mediana - 2 dormitorios", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 23:
		{
			House[houseid][ExitX] = 260.941986;
			House[houseid][ExitY] = 1238.509888;
			House[houseid][ExitZ] = 1084.259888;
			House[houseid][ExitInterior] = 9;
			format(string, sizeof string, "Casa: %d - descripción: pequeña - 1 dormitorio", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 24:
		{
			House[houseid][ExitX] = 244.411987;
			House[houseid][ExitY] = 305.032990;
			House[houseid][ExitZ] = 999.231995;
			House[houseid][ExitInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: Denise's Bedroom", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
     	case 25:
		{
			House[houseid][ExitX] = 271.884979;
			House[houseid][ExitY] = 306.631989;
			House[houseid][ExitZ] = 999.325989;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Katie's Bedroom", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
      	case 26:
		{
			House[houseid][ExitX] = 291.282990;
			House[houseid][ExitY] = 310.031982;
			House[houseid][ExitZ] = 999.154968;
			House[houseid][ExitInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: Helena's Bedroom (barn) - limited movement.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 27:
		{
			House[houseid][ExitX] = 302.181000;
			House[houseid][ExitY] = 300.722992;
			House[houseid][ExitZ] = 999.231995;
			House[houseid][ExitInterior] = 4;
			format(string, sizeof string, "Casa: %d - descripción: Michelle's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 28:
		{
			House[houseid][ExitX] = 322.197998;
			House[houseid][ExitY] = 302.497986;
			House[houseid][ExitZ] = 999.231995;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Barbara's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 29:
		{
			House[houseid][ExitX] = 346.870025;
			House[houseid][ExitY] = 309.259033;
			House[houseid][ExitZ] = 999.155700;
			House[houseid][ExitInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: Millie's Bedroom.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 30:
		{
			House[houseid][ExitX] = 2496.049805;
			House[houseid][ExitY] = -1693.929932;
			House[houseid][ExitZ] = 1014.750000;
			House[houseid][ExitInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: CJ's Mom's House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 31:
		{
			House[houseid][ExitX] = 1263.079956;
			House[houseid][ExitY] = -785.308960;
			House[houseid][ExitZ] = 1091.959961;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Madd Dogg's Mansion (West door).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 32:
		{
			House[houseid][ExitX] = 2464.109863;
			House[houseid][ExitY] = -1698.659912;
			House[houseid][ExitZ] = 1013.509949;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Ryder's house.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 33:
		{
			House[houseid][ExitX] = 2526.459961;
			House[houseid][ExitY] = -1679.089966;
			House[houseid][ExitZ] = 1015.500000;
			House[houseid][ExitInterior] = 1;
			format(string, sizeof string, "Casa: %d - descripción: Sweet's House (South side of house is fucked).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 34:
		{
			House[houseid][ExitX] = 2543.659912;
			House[houseid][ExitY] = -1303.629883;
			House[houseid][ExitZ] = 1025.069946;
			House[houseid][ExitInterior] = 2;
			format(string, sizeof string, "Casa: %d - descripción: Big Smoke's Crack Factory (Ground Floor).", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 35:
		{
			House[houseid][ExitX] = 744.542969;
			House[houseid][ExitY] = 1437.669922;
			House[houseid][ExitZ] = 1102.739990;
			House[houseid][ExitInterior] = 6;
			format(string, sizeof string, "Casa: %d - descripción: Fanny Batter's Whore House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
		}
     	case 36:
  		{
			House[houseid][ExitX] = 964.106995;
			House[houseid][ExitY] = -53.205498;
			House[houseid][ExitZ] = 1001.179993;
			House[houseid][ExitInterior] = 3;
			format(string, sizeof string, "Casa: %d - descripción: Tiger Skin Rug Brothel.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 37:
		{
			House[houseid][ExitX] = 2350.339844;
			House[houseid][ExitY] = -1181.649902;
			House[houseid][ExitZ] = 1028.000000;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Burning Desire Gang House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 38:
		{
			House[houseid][ExitX] = 2807.619873;
			House[houseid][ExitY] = -1171.899902;
			House[houseid][ExitZ] = 1025.579956;
			House[houseid][ExitInterior] = 8;
			format(string, sizeof string, "Casa: %d - descripción: Colonel Furhberger's House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 39:
		{
			House[houseid][ExitX] = 318.564972;
			House[houseid][ExitY] = 1118.209961;
			House[houseid][ExitZ] = 1083.979980;
			House[houseid][ExitInterior] = 5;
			format(string, sizeof string, "Casa: %d - descripción: Crack Den.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 40:
		{
			House[houseid][ExitX] = 2324.419922;
			House[houseid][ExitY] = -1147.539917;
			House[houseid][ExitZ] = 1050.719971;
			House[houseid][ExitInterior] = 12;
			format(string, sizeof string, "Casa: %d - descripción: Unused Safe House.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
     	case 41:
		{
			House[houseid][ExitX] = 446.622986;
			House[houseid][ExitY] = 509.318970;
			House[houseid][ExitZ] = 1001.419983;
			House[houseid][ExitInterior] = 12;
			format(string, sizeof string, "Casa: %d - descripción: habitación motel Budget Inn.", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
        case 42:
		{
			House[houseid][ExitX] = 2216.339844;
			House[houseid][ExitY] = -1150.509888;
			House[houseid][ExitZ] = 1025.799927;
			House[houseid][ExitInterior] = 15;
			format(string, sizeof string, "Casa: %d - descripción: Jefferson Motel. (REALLY EXPENSIVE)", houseid);
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
     	}
	}
	saveHouse(houseid);
	return 1;
}

CMD:acprecio(playerid, params[])
{
	new
		houseid,
		price,
		string[128];

	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "ii", houseid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acprecio [ID casa] [Precio]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(price < 0 || price > 10000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige un precio de $0 a $10.000.000.");
	    
	House[houseid][HousePrice] = price;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el precio de la casa %d ha sido ajustado a $%d.", houseid, price);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	ResetLocker(houseid); // Al cambiar el precio se cambian los slots de armario, por ende reseteamos todo para evitar bugs.
	saveHouse(houseid);
	return 1;
}

CMD:acvender(playerid, params[])
{
	new
		houseid,
		pconnected = 0,
		string[128];
	
	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acvender [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	    
	if(House[houseid][Owned] == 1)
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pHouseKey] == houseid)
			{
   				PlayerInfo[i][pHouseKey] = 0;
				pconnected = 1;
			}
		}
		if(pconnected == 0)
		{
			format(string, sizeof(string), "UPDATE `accounts` SET `HouseKey` = 0 WHERE `Name` = '%s' AND `HouseKey` = %d", House[houseid][Owner], houseid);
			mysql_function_query(dbHandle, string, false, "", "");
		}
	}
	House[houseid][Locked] = 1;
	House[houseid][Owned] = 0;
	House[houseid][Marijuana] = 0;
	House[houseid][LSD] = 0;
	House[houseid][Ecstasy] = 0;
	House[houseid][Cocaine] = 0;
	strmid(House[houseid][Owner], "Ninguno", 0, strlen("Ninguno"), 255);
	ResetLocker(houseid);
	saveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la casa %d ha sido vendida.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:acentrada(playerid, params[])
{
	new
		houseid,
		Float:angle,
		string[128];
		
	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acentrada [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	    
	GetPlayerPos(playerid, House[houseid][EntranceX], House[houseid][EntranceY], House[houseid][EntranceZ]);
	House[houseid][EntranceInterior] = GetPlayerInterior(playerid);
	GetPlayerFacingAngle(playerid, angle);
	House[houseid][EntranceAngle] = angle + 180;
	saveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la entrada de la casa %d ha sido cambiada a tu posición.", houseid);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	return 1;
}

CMD:acsalida(playerid, params[])
{
	new
		houseid,
		Float:angle,
		string[128];

	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acsalida [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	    
	GetPlayerPos(playerid, House[houseid][ExitX], House[houseid][ExitY], House[houseid][ExitZ]);
	House[houseid][ExitInterior] = GetPlayerInterior(playerid);
	GetPlayerFacingAngle(playerid, angle);
	House[houseid][ExitAngle] = angle + 180;
	saveHouse(houseid);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la salida de la casa %d ha sido cambiada a tu posición.", houseid);
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

	SendFMessage(playerid, COLOR_WHITE, "=======================[Casa %d]=======================", id);
	SendFMessage(playerid, COLOR_WHITE, "- Tiene dueño: %d", House[id][Owned]);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s", House[id][Owner]);
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

	SetPlayerPos(playerid, House[houseid][EntranceX], House[houseid][EntranceY], House[houseid][EntranceZ]);
	SetPlayerInterior(playerid, House[houseid][EntranceInterior]);
	return 1;
}

//====================COMANDOS DE ADMIN DE ALQUILER DE CASAS====================
CMD:acalquilar(playerid, params[])
{
	new
		houseid,
		price,
		string[128];

	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");

	price = House[houseid][HousePrice] / 100;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el precio de alquiler de la casa %d ha sido ajustado a $%d.", houseid, price);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	
	House[houseid][IncomePrice] = price;
	House[houseid][IncomeAccept] = 1;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	
	saveHouse(houseid);
	return 1;
}

CMD:acnoalquilar(playerid, params[])
{
	new
		houseid,
		price,
		string[128];

	if(PlayerInfo[playerid][pAdmin] != 20)
	    return 1;
    if(sscanf(params, "i", houseid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /acnoalquilar [ID casa]");
	if(houseid < 1 || houseid >= MAX_HOUSES)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de casa inválida.");
	if(House[houseid][Income] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La casa tiene un inquilino.");
		
	price = 0;
    House[houseid][IncomePrice] = price;
	House[houseid][IncomeAccept] = 0;
	House[houseid][Income] = 0;
	strmid(House[houseid][Tenant], "Ninguno", 0, strlen("Ninguno"), 255);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el precio de alquiler de la casa %d ha sido ajustado a $%d.", houseid, price);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	saveHouse(houseid);
	return 1;
}
