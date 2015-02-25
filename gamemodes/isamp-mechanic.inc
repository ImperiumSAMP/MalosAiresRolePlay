#if defined _isamp_mechanic_included
	#endinput
#endif
#define _isamp_mechanic_included

//=====================SISTEMA Y COMANDOS DE MECANICO===========================

//================================CONSTANTES====================================

#define DLG_TUNING              	10020

#define JOB_MECH_MAXPRICE       	1000

#define MEC_OFFICE_X				1584.54
#define MEC_OFFICE_Y        		-1819.68
#define MEC_OFFICE_Z        		13.34

#define MEC_TUNING_PLACE_X      	1595.92
#define MEC_TUNING_PLACE_Y      	-1840.69
#define MEC_TUNING_PLACE_Z      	13.48

#define MEC_REPAIR_PLACE_X      	1594.65
#define MEC_REPAIR_PLACE_Y      	-1797.73
#define MEC_REPAIR_PLACE_Z      	13.34

#define MEC_CARPART_SHOP_X      	976.1300
#define MEC_CARPART_SHOP_Y   		-1254.8500
#define MEC_CARPART_SHOP_Z      	16.9400

#define MEC_OFFER_REPARACION    	1
#define MEC_OFFER_CERRADURA     	2
#define MEC_OFFER_TUNING        	3
#define MEC_OFFER_DESTUNING     	4

//==============================DATA STORAGE====================================

new RepairClient[MAX_PLAYERS],
	RepairOffer[MAX_PLAYERS],
	RepairProducts[MAX_PLAYERS],
	RepairPrice[MAX_PLAYERS],
	RepairType[MAX_PLAYERS],
	RepairOfferTimer[MAX_PLAYERS];

new TMTuneTimers[5];

//==============================FUNCIONES=======================================

forward ResetRepairOffer(playerid);
forward EndRepairOffer(playerid);

forward Cerrajeria(playerid);
forward AutoReparacion(playerid, paynsprayid);
forward Reparacion(playerid);
forward Destuning(playerid);

forward GetRepairMaterialCost(vehicleid);

forward CloseTuneGate0();
forward CloseTuneGate1();
forward CloseTuneGate2();
forward CloseTuneGate3();
forward CloseTuneGate4();
forward CountMecasDuty();


//=======================IMPLEMENTACIÓN DE FUNCIONES============================

public CloseTuneGate0()
{
    if(TMTune[0][0] == 1)
	{
	    TMTune[0][0] = 0;
	    MoveObject(TMTune[0][1], -2716.01, 217.88, 5.48, 1, 0.00, 0.00, 0.00);
	}
	return 1;
}

public CloseTuneGate1()
{
    if(TMTune[1][0] == 1)
	{
	    TMTune[1][0] = 0;
	    MoveObject(TMTune[1][1],  2644.83, -2039.06, 14.32, 1, 0.00, 0.00, 73.08);
	}
	return 1;
}

public CloseTuneGate2()
{
    if(TMTune[2][0] == 1)
	{
	    TMTune[2][0] = 0;
	    MoveObject(TMTune[2][1], -1935.01, 238.70, 33.69, 1, 0.00, 0.00, 0.00);
	}
	return 1;
}

public CloseTuneGate3()
{
    if(TMTune[3][0] == 1)
	{
	    TMTune[3][0] = 0;
	    MoveObject(TMTune[3][1], 1043.17, -1025.85, 33.66, 1, 0.00, 0.00, 0.00);
	}
	return 1;
}

public CloseTuneGate4()
{
    if(TMTune[4][0] == 1)
	{
	    TMTune[4][0] = 0;
	    MoveObject(TMTune[4][1], 2387.38, 1043.45, 11.82, 1, 0.00, 0.00, 0.00);
	}
	return 1;
}

public ResetRepairOffer(playerid)
{
	RepairClient[playerid] = 999;
	RepairOffer[playerid] = 999;
	RepairPrice[playerid] = 0;
	RepairType[playerid] = 0;
	RepairProducts[playerid] = 0;
	return 1;
}

public EndRepairOffer(playerid)
{
	RepairClient[RepairOffer[playerid]] = 999;
    ResetRepairOffer(playerid);
    return 1;
}

stock GetRepairMaterialCost(vehicleid)
{
    new Float:vhp,
		repuestos;
		
   	GetVehicleHealth(vehicleid, vhp);
 	if(vhp < 750.0)
 	{
		repuestos = floatround(((750.0 - vhp) / 125), floatround_ceil);
        if(IsABike(vehicleid))
            repuestos --; // las motos piden 1 repuesto menos
		return repuestos;
	}
 	return 0;
}

public Cerrajeria(playerid)
{
    new	vehicleid = GetPlayerVehicleID(playerid);

	if(GetPlayerCash(playerid) >= RepairPrice[playerid])
	{
		deleteExtraKeysForCar(vehicleid);
		SendFMessage(playerid, COLOR_YELLOW2, "La cerradura de su vehículo ha sido cambiada por %s (costo: $%d).", GetPlayerNameEx(RepairOffer[playerid]), RepairPrice[playerid]);
		SendFMessage(RepairOffer[playerid], COLOR_YELLOW2, "Cambiaste la cerradura del vehículo de %s, $%d han sido añadidos a su PayDay.", GetPlayerNameEx(playerid), RepairPrice[playerid]);
		PlayerInfo[RepairOffer[playerid]][pPayCheck] += RepairPrice[playerid];
		GivePlayerCash(playerid, -RepairPrice[playerid]);
	} else {
	    SendClientMessage(RepairOffer[playerid], COLOR_YELLOW2, "El jugador no tiene el dinero necesario.");
	    SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
	}
	TogglePlayerControllable(playerid, true);
	EndRepairOffer(playerid);
	return 1;
}

public Reparacion(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid),
		mechanic = RepairOffer[playerid];
		
    TogglePlayerControllable(playerid, true);
    
	if(GetPlayerCash(playerid) < RepairPrice[playerid])
 	{
  		SendClientMessage(mechanic, COLOR_YELLOW2, "El jugador no tiene el dinero necesario.");
		SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
		return EndRepairOffer(playerid);
	}
	
	if(RepairProducts[playerid] > 0)
	{
	    if(FactionInfo[FAC_MECH][fMaterials] < RepairProducts[playerid])
	    {
			SendFMessage(playerid, COLOR_YELLOW2, "La reparación se canceló ya que el taller no cuenta con los repuestos necesarios (%d).", RepairProducts[playerid]);
			SendFMessage(mechanic, COLOR_YELLOW2, "La reparación se canceló ya que el taller no cuenta con los repuestos necesarios (%d).", RepairProducts[playerid]);
			return EndRepairOffer(playerid);
		}

		FactionInfo[FAC_MECH][fMaterials] -= RepairProducts[playerid];
		FactionInfo[FAC_MECH][fBank] += RepairProducts[playerid] * (GetItemPrice(ITEM_ID_REPUESTOAUTO) + 25);
	}
	
	RepairVehicle(vehicleid);
	VehicleInfo[vehicleid][VehHP] = 100;
	SendFMessage(playerid, COLOR_YELLOW2, "Su vehículo ha sido reparado por %s (costo: $%d).", GetPlayerNameEx(mechanic), RepairPrice[playerid]);
	SendFMessage(mechanic, COLOR_YELLOW2, "Reparaste el vehículo de %s, $%d han sido añadidos a su PayDay.", GetPlayerNameEx(playerid), RepairPrice[playerid] - RepairProducts[playerid] * GetItemPrice(ITEM_ID_REPUESTOAUTO));
	PlayerInfo[mechanic][pPayCheck] += RepairPrice[playerid] - RepairProducts[playerid] * GetItemPrice(ITEM_ID_REPUESTOAUTO);
	GivePlayerCash(playerid, -RepairPrice[playerid]);
	EndRepairOffer(playerid);
    return 1;
}

public Destuning(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid),
		part;

	for(new i = 0; i < 14; i++)
	{
		part = VehicleInfo[vehicleid][VehCompSlot][i];
		if(part != 0)
		{
		   	RemoveVehicleComponent(vehicleid, part);
		   	VehicleInfo[vehicleid][VehCompSlot][i] = 0;
		}
	}
	SendFMessage(playerid, COLOR_WHITE, "Las partes tuning de su vehículo han sido removidas por %s.", GetPlayerNameEx(RepairOffer[playerid]));
	SendFMessage(RepairOffer[playerid], COLOR_WHITE, "Has removido las partes tuning del vehículo de %s.", GetPlayerNameEx(playerid));
	TogglePlayerControllable(playerid, true);
	EndRepairOffer(playerid);
	return 1;
}

stock isPlayerMecOnDuty(playerid)
{
	if(PlayerInfo[playerid][pFaction] == FAC_MECH && jobDuty[playerid])
	    return true;
	else
	    return false;
}

public CountMecasDuty()
{
	new aux = 0;
 	foreach(new i : Player)
 	{
        if(isPlayerMecOnDuty(i))
    	    aux ++;
 	}
 	return aux;
}

//================================COMANDOS======================================

CMD:ayudamec(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] == FAC_MECH)
	{
	    SendClientMessage(playerid, COLOR_WHITE, "[COMANDOS DE MECÁNICO]: /mecequipo - /mecreparar - /mecremolcar - /mectaller - /mecdestunear - /mectunear - /mectuning - /meccerradura");
        SendClientMessage(playerid, COLOR_WHITE, "/meccomprar - /mecguardar - /mecdeposito");
        if(PlayerInfo[playerid][pRank] == 1)
        	SendClientMessage(playerid, COLOR_WHITE, "[Lider] /mecretirar");
	}
	return 1;
}

CMD:mecequipo(playerid, params[])
{
	new option, hand;

	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
	    return 1;
	if(sscanf(params, "i", option))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecequipo [ropa] (1-5)");
	if(option < 1 || option > 5)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecequipo [ropa] (1-5)");
    if(!PlayerToPoint(3.0, playerid, MEC_OFFICE_X, MEC_OFFICE_Y, MEC_OFFICE_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la oficina del taller, al lado de los estantes donde se guardan las vestimentas de trabajo.");
   	if(!jobDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio.");
	if(option == 5)
	{
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
        PlayerActionMessage(playerid, 15.0, "devuelve su ropa de trabajo al estante y se viste con sus vestimentas personales.");
	} else
	    {
    		hand = SearchFreeHand(playerid);
			if(hand == -1)
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener alguna mano libre para agarrar el aerosol de pintura.");
			switch(option)
			{
			    case 1: SetPlayerSkin(playerid, 8);
			    case 2: SetPlayerSkin(playerid, 50);
			    case 3: SetPlayerSkin(playerid, 42);
			    case 4: SetPlayerSkin(playerid, 268);
			}
			SetHandItemAndParam(playerid, hand, WEAPON_SPRAYCAN, 750);
			PlayerActionMessage(playerid, 15.0, "toma unas vestimentas del estante y se las pone. Luego agarra un aerosol de pintura.");
		}
	return 1;
}

CMD:meccomprar(playerid, params[])
{
	new cant, freehand;
	
 	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
	if(sscanf(params, "i", cant))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /meccomprar [Cantidad de repuestos]");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, MEC_CARPART_SHOP_X, MEC_CARPART_SHOP_Y, MEC_CARPART_SHOP_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes comprar repuestos en cualquier lado.");
	freehand = SearchFreeHand(playerid);
	if(freehand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes las manos ocupadas y no puedes agarrar los repuestos.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
	if(cant < 1 || cant > 15)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes sostener menos de 1 o mas de 15 repuestos con la mano.");
	if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_REPUESTOAUTO) * cant)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "No tienes el efectivo necesario, necesitas $%d. (Costo por repuesto: $%d)", GetItemPrice(ITEM_ID_REPUESTOAUTO) * cant, GetItemPrice(ITEM_ID_REPUESTOAUTO));
		return 1;
	}

	SetHandItemAndParam(playerid, freehand, ITEM_ID_REPUESTOAUTO, cant);
	GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_REPUESTOAUTO) * cant);
	SendFMessage(playerid, COLOR_WHITE, "Has comprado %d repuestos a un precio de $%d.", cant, GetItemPrice(ITEM_ID_REPUESTOAUTO) * cant);
	return 1;
}

CMD:mecguardar(playerid, params[])
{
	new string[128], hand;
	
 	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
	hand = SearchHandsForItem(playerid, ITEM_ID_REPUESTOAUTO);
	if(hand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ningún repuesto en alguna de tus manos para guardar en el depósito del taller.");
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_TUNING_PLACE_X, MEC_TUNING_PLACE_Y, MEC_TUNING_PLACE_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el galpón de repuestos y tuning.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");

	format(string, sizeof(string), "[Taller Mecánico]: %s ha guardado %d repuestos en el depósito del taller.", GetPlayerNameEx(playerid), GetHandParam(playerid, hand));
	SendFactionMessage(FAC_MECH, COLOR_WHITE, string);
	FactionInfo[FAC_MECH][fMaterials] += GetHandParam(playerid, hand);
	SetHandItemAndParam(playerid, hand, 0, 0);
	return 1;
}

CMD:mecretirar(playerid, params[])
{
	new cant, string[128], freehand;

 	if(PlayerInfo[playerid][pFaction] != FAC_MECH || PlayerInfo[playerid][pRank] != 1)
        return 1;
	if(sscanf(params, "i", cant))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecretirar [Cantidad de repuestos]");
	if(cant < 1 || cant > 10)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes retirar hasta 10 repuestos del depósito.");
	freehand = SearchFreeHand(playerid);
	if(freehand == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes las manos ocupadas y no puedes agarrar los repuestos.");
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_TUNING_PLACE_X, MEC_TUNING_PLACE_Y, MEC_TUNING_PLACE_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el galpón de repuestos y tuning.");
	if(FactionInfo[FAC_MECH][fMaterials] < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay más repuestos en el depósito del taller: está vacio.");
	if(FactionInfo[FAC_MECH][fMaterials] < cant)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay tantos repuestos en el depósito del taller.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");

	format(string, sizeof(string), "[Taller Mecánico]: %s ha retirado %d repuestos del depósito del taller.", GetPlayerNameEx(playerid), cant);
	SendFactionMessage(FAC_MECH, COLOR_WHITE, string);
	FactionInfo[FAC_MECH][fMaterials] -= cant;
	SetHandItemAndParam(playerid, freehand, ITEM_ID_REPUESTOAUTO, cant);
	return 1;
}

CMD:mecdeposito(playerid, params[])
{
 	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;

	SendFMessage(playerid, COLOR_WHITE, "[Taller Mecánico]: Actualmente nuestro depósito cuenta con %d repuestos de vehículos.", FactionInfo[FAC_MECH][fMaterials]);
 	return 1;
}

CMD:mecremolcar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		targetVehicleid = GetClosestVehicle(playerid, 7.0);

    if(PlayerInfo[playerid][pFaction] != FAC_MECH && PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;
	if(GetVehicleModel(vehicleid) != 525 || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Tienes que estar conduciendo una grúa!");
	if(targetVehicleid == INVALID_VEHICLE_ID)
	    return 1;

	if(IsTrailerAttachedToVehicle(vehicleid))
		DetachTrailerFromVehicle(vehicleid);
	else
		AttachTrailerToVehicle(targetVehicleid, vehicleid);
	return 1;
}

CMD:mecreparar(playerid,params[])
{
	new target, vehicleid, repuestos, price, factionveh, carAvailable = 0;

    if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
	if(sscanf(params, "ui", target, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecreparar [ID/Jugador] [Precio]");
	if(!jobDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No te encuentras en servicio.");
  	if(RepairClient[playerid] < 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes una oferta de trabajo con otro cliente!");
 	if(target == playerid || !IsPlayerConnected(target))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
 	if(!ProxDetectorS(4.0, playerid, target) || !IsPlayerInAnyVehicle(target))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no se encuentra cerca tuyo o no está dentro de un vehiculo.");
	if(GetPlayerState(target) == PLAYER_STATE_PASSENGER)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes reparar un vehiculo desde adentro, ni tampoco repararselo a un pasajero.");

	vehicleid = GetPlayerVehicleID(target);
 	repuestos = GetRepairMaterialCost(vehicleid);
    	
    if(repuestos > 0)
	{
	    if(FactionInfo[FAC_MECH][fMaterials] < repuestos)
	    {
	        SendFMessage(playerid, COLOR_YELLOW2, "El vehículo está muy dañado y necesita de %d nuevos repuestos, pero el taller no cuenta con dicho stock.", repuestos);
	    	return 1;
	    }
		if(GetVehicleType(vehicleid) == VTYPE_CAR) // Se puede remolcar.
		{
	 		if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_REPAIR_PLACE_X, MEC_REPAIR_PLACE_Y, MEC_REPAIR_PLACE_Z))
    		{
		        SendFMessage(playerid, COLOR_YELLOW2, "El vehículo está muy dañado y necesita de %d nuevos repuestos.", repuestos);
		        SendClientMessage(playerid, COLOR_YELLOW2, "Para repararlo, debes estar en el galpón de repuestos del taller y que haya stock.");
				return 1;
			}
		}
		else
		{
			if(!IsPlayerInAnyVehicle(playerid))
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Para reparar un vehículo muy dañado que no puede ser remolcado al taller, debes estar en un vehículo de facción.");
            factionveh = GetPlayerVehicleID(playerid);
            if(VehicleInfo[factionveh][VehFaction] != FAC_MECH)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Para reparar un vehículo muy dañado que no puede ser remolcado al taller, debes estar en un vehículo de facción.");
			carAvailable = 1;
		}
	}
 	if(price < (repuestos * GetItemPrice(ITEM_ID_REPUESTOAUTO)) || price > JOB_MECH_MAXPRICE)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "¡El precio no debe ser menor a %d (Costo material) ni mayor a %d!", repuestos * GetItemPrice(ITEM_ID_REPUESTOAUTO), JOB_MECH_MAXPRICE);
	    return 1;
 	}
 	if(carAvailable == 0 && IsPlayerInAnyVehicle(playerid))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes reparar un vehículo desde adentro, ni tampoco repararselo a un pasajero.");

	RepairOffer[target] = playerid;
	RepairPrice[target] = price;
	RepairType[target] = MEC_OFFER_REPARACION;
	RepairProducts[target] = repuestos;
	RepairClient[playerid] = target;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s reparar su vehículo por $%d. La propuesta vence en 10 segs.", GetPlayerNameEx(target), price);
	SendFMessage(target, COLOR_LIGHTBLUE, "%s te ofreció reparar el vehículo por $%d. Usa /mecaceptar. La propuesta vence en 10 segs.", GetPlayerNameEx(playerid), price);
	RepairOfferTimer[target] = SetTimerEx("EndRepairOffer", 10000, false, "i", target);
	return 1;
}

CMD:meccerradura(playerid, params[])
{
	new target, price;

	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
	if(sscanf(params, "ui", target, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /meccerradura [ID/Jugador] [Precio]");
    if(!jobDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio.");
 	if(RepairClient[playerid] < 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes una oferta de trabajo con otro cliente!");
	if(price < 0 || price > JOB_MECH_MAXPRICE)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "¡El precio no debe ser mayor a %d o menor a 0!", JOB_MECH_MAXPRICE);
	    return 1;
 	}
 	if(!IsPlayerConnected(target) || target == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
 	if(!ProxDetectorS(5.0, playerid, target) || !IsPlayerInAnyVehicle(target))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no se encuentra cerca tuyo o no está dentro de un vehículo.");
	if(IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes cambiar una cerradura estando arriba de un vehículo.");
	if(!playerOwnsCar(target, GetPlayerVehicleID(target)))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El auto no pertenece al usuario.");

	RepairOffer[target] = playerid;
	RepairPrice[target] = price;
	RepairType[target] = MEC_OFFER_CERRADURA;
	RepairClient[playerid] = target;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s cambiar la cerradura por $%d. La propuesta vence en 10 segs.", GetPlayerNameEx(target), price);
	SendFMessage(target, COLOR_LIGHTBLUE, "%s quiere cambiarte la cerradura por $%d. Usa /mecaceptar. Tienes 10 segs.", GetPlayerNameEx(playerid), price);
	RepairOfferTimer[target] = SetTimerEx("EndRepairOffer", 10000, false, "i", target);
	return 1;
}

CMD:mecdestunear(playerid, params[])
{
	new target;

 	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
  		return 1;
    if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecdestunear [ID/Jugador]");
 	if(!jobDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio");
 	if(RepairClient[playerid] < 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes una oferta de trabajo con otro cliente!");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie!");
  	if(target == INVALID_PLAYER_ID || !IsPlayerConnected(target))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
  	if(!ProxDetectorS(5.0, playerid, target))
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no está cerca tuyo.");
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_TUNING_PLACE_X, MEC_TUNING_PLACE_Y, MEC_TUNING_PLACE_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el galpón de tuning del Taller Mercury.");
	if(!IsPlayerInAnyVehicle(target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no esta en un vehiculo.");
	new vID = GetPlayerVehicleID(target);
    if(GetVehicleType(vID) != VTYPE_CAR)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Tipo de vehículo invalido.");
    if(!playerHasCarKey(target, vID))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no es dueño de ese vehiculo.");

    RepairOffer[target] = playerid;
    RepairType[target] = MEC_OFFER_DESTUNING;
    RepairPrice[target] = 0;
    RepairClient[playerid] = target;
    SendClientMessage(target, COLOR_LIGHTBLUE, "Te han ofrecido destunear tu auto, usa /mecaceptar si quieres. Tienes 10 segs para responder.");
    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Le has propuesto al cliente destunear su auto. La oferta termina en 10 segs.");
	RepairOfferTimer[target] = SetTimerEx("EndRepairOffer", 10000, false, "i", target);
	return 1;
}

CMD:mecaceptar(playerid, params[])
{
	if(RepairOffer[playerid] == 999)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ningún mecánico te ha ofrecido algún trabajo sobre el vehículo!");
	if(GetPlayerCash(playerid) < RepairPrice[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente para pagar el trabajo!");
    if(!IsPlayerConnected(RepairOffer[playerid]))
        return SendClientMessage(playerid, COLOR_YELLOW2, "El mecánico no está conectado.");
	if(!IsPlayerInAnyVehicle(playerid) && RepairType[playerid] != MEC_OFFER_TUNING)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en un ningún vehiculo.");
	if(!ProxDetectorS(5.0, playerid, RepairOffer[playerid]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El mecánico no está cerca tuyo.");

	switch(RepairType[playerid])
	{
	    case MEC_OFFER_REPARACION:
	    {
			GameTextForPlayer(playerid, "El mecanico esta reparando su vehiculo...", 6000, 1);
			GameTextForPlayer(RepairOffer[playerid], "Reparando vehiculo...", 6000, 1);
			KillTimer(RepairOfferTimer[playerid]);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Reparacion", 6000, false, "i", playerid);
		}
		case MEC_OFFER_CERRADURA:
		{
			GameTextForPlayer(playerid, "El mecanico esta cambiando la cerradura...", 6000, 1);
			GameTextForPlayer(RepairOffer[playerid], "Cambiando cerradura...", 6000, 1);
			KillTimer(RepairOfferTimer[playerid]);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Cerrajeria", 6000, false, "i", playerid);
		}
		case MEC_OFFER_DESTUNING:
		{
 			new vID = GetPlayerVehicleID(playerid);
			if(GetVehicleType(vID) != VTYPE_CAR)
			   	return SendClientMessage(playerid, COLOR_YELLOW2, "Vehiculo inválido.");
			if(!playerHasCarKey(playerid, vID))
				return SendClientMessage(playerid, COLOR_YELLOW2, "No eres dueño de ese vehiculo.");
				
			GameTextForPlayer(playerid, "El mecanico esta removiendo las partes tuneadas...", 6000, 1);
			GameTextForPlayer(RepairOffer[playerid], "Removiendo partes tuneadas...", 6000, 1);
			KillTimer(RepairOfferTimer[playerid]);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Destuning", 6000, false, "i", playerid);
		}
		case MEC_OFFER_TUNING:
		{
  			RepairClient[RepairOffer[playerid]] = playerid;
			SendClientMessage(playerid, COLOR_WHITE, "Has aceptado la propuesta de tuneo.");
			SendClientMessage(RepairOffer[playerid], COLOR_WHITE, "Han aceptado tu propuesta, usa /mectuning estando como conductor del vehículo a tunear.");
		}
	}
	return 1;
}

CMD:mectunear(playerid,params[])
{
	new target, tuningVehicleID;

    if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mectunear [ID/Jugador]");
	if(!jobDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio");
 	if(PlayerInfo[playerid][pRank] > 5)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente.");
	if(RepairClient[playerid] < 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya tienes una oferta de trabajo con otro cliente!");
  	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar de conductor en el auto que vas a tunear!");
 	if(target == INVALID_PLAYER_ID || !IsPlayerConnected(target))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador invalido.");
  	if(!ProxDetectorS(5.0, playerid, target))
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no está cerca tuyo.");
	tuningVehicleID = GetPlayerVehicleID(playerid);
	if(!playerHasCarKey(target, tuningVehicleID))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no es dueño de este vehiculo.");
    if(GetVehicleType(tuningVehicleID) != VTYPE_CAR && GetVehicleType(tuningVehicleID) != VTYPE_BIKE)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tipo de vehículo invalido.");
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_TUNING_PLACE_X, MEC_TUNING_PLACE_Y, MEC_TUNING_PLACE_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el galpón de tuning del Taller Mercury.");

    SendClientMessage(target, COLOR_LIGHTBLUE, "Te han ofrecido un tuneo, usa /mecaceptar si así lo deseas. La oferta termina en dos minutos.");
    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has ofrecido un tuneo, el tiempo para poder tunearlo termina en dos minutos.");
	RepairOffer[target] = playerid;
	RepairType[target] = MEC_OFFER_TUNING;
	RepairPrice[target] = 0;
	SetTimerEx("EndRepairOffer", 120000, false, "i", target);
	return 1;
}

CMD:mectuning(playerid, params[])
{
    new clientID = RepairClient[playerid],
		title[64],
		content[256];

    if(PlayerInfo[playerid][pFaction] != FAC_MECH)
        return 1;
    if(!jobDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio.");
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, MEC_TUNING_PLACE_X, MEC_TUNING_PLACE_Y, MEC_TUNING_PLACE_Z))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el galpón de tuning del Taller Mercury.");
    if(PlayerInfo[playerid][pRank] > 5)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente.");
 	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar de conductor del auto que vas a tunear!");
    if(clientID == 999)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes autorización del dueño para tunear este vehículo.");
	if(RepairOffer[clientID] != playerid || RepairType[clientID] != MEC_OFFER_TUNING)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Error, se cancela el tuning.");
	new vID = GetPlayerVehicleID(playerid);
  	if(!playerHasCarKey(clientID, vID))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Este auto no es de tu cliente.");
   	if(GetVehicleType(vID) != VTYPE_CAR && GetVehicleType(vID) != VTYPE_BIKE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Vehiculo invalido.");

	format(title, sizeof(title), "Menú de tuning del Taller Mercury");
	format(content, sizeof(content), "Color 1 $1500\nColor 2 $1500\nLlantas $4000\nSuspension Hidraulica $4000\nOxido Nitroso $10000");
	TogglePlayerControllable(playerid, false);
	ShowPlayerDialog(playerid, DLG_TUNING, DIALOG_STYLE_LIST, title, content, "Seleccionar", "Cerrar");
	return 1;
}

CMD:mectaller(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
		return 1;
	if(PlayerInfo[playerid][pRank] > 4)
	{
        SendFMessage(playerid, COLOR_YELLOW2, "Debes ser al menos un '%s' para poder utilizar este comando.", GetRankName(FAC_MECH, 3));
        return 1;
	}
 	if(PlayerToPoint(5.0, playerid, -2714.6985, 222.1743, 4.3281)) // Wheel Arch Angels San Fierro.
	{
 	    if(TMTune[0][0] <= 0)
	 	{
 	        TMTune[0][0] = 1;
 	    	MoveObject(TMTune[0][1], -2716.01, 217.88, 10, 1, 0.00, 0.00, 0.00);
 	    	TMTuneTimers[0] = SetTimer("CloseTuneGate0", 1000 * 60 * 5, false);
		}
		else
		{
		    KillTimer(TMTuneTimers[0]);
		    TMTune[0][0] = 0;
		    MoveObject(TMTune[0][1], -2716.01, 217.88, 5.48, 1, 0.00, 0.00, 0.00);
		}
	}
	else if(PlayerToPoint(5.0, playerid, 2649.7874, -2037.5381, 13.5500)) // Loco Low Co. Los Santos.
	{
 	    if(TMTune[1][0] <= 0)
	 	{
 	        TMTune[1][0] = 1;
 	    	MoveObject(TMTune[1][1], 2651.19, -2039.01, 14.32, 1, 0.00, 0.00, -73.08);
 	    	TMTuneTimers[1] = SetTimer("CloseTuneGate1", 1000 * 60 * 5, false);
		}
		else
		{
			KillTimer(TMTuneTimers[1]);
		    TMTune[1][0] = 0;
		    MoveObject(TMTune[1][1], 2644.83, -2039.06, 14.32, 1, 0.00, 0.00, -73.08);
		}
	}
	else if(PlayerToPoint(5.0, playerid, -1931.3779, 237.0436, 34.3470)) // TransFender San Fierro.
	{
 	    if(TMTune[2][0] <= 0)
	 	{
 	        TMTune[2][0] = 1;
 	    	MoveObject(TMTune[2][1],  -1927.87, 238.66, 33.70, 1, 0.00, 0.00, 0.00);
 	    	TMTuneTimers[2] = SetTimer("CloseTuneGate2", 1000 * 60 * 5, false);
		}
		else
		{
		    KillTimer(TMTuneTimers[2]);
		    TMTune[2][0] = 0;
		    MoveObject(TMTune[2][1], -1935.01, 238.70, 33.69, 1, 0.00, 0.00, 0.00);
		}
	}
	else if(PlayerToPoint(5.0, playerid, 1044.7301, -1027.6169, 32.1016)) // TransFender Los Santos.
	{
 	    if(TMTune[3][0] <= 0)
	 	{
 	        TMTune[3][0] = 1;
 	    	MoveObject(TMTune[3][1], 1050.63, -1025.82, 33.66, 1, 0.00, 0.00, 0.00);
 	    	TMTuneTimers[3] = SetTimer("CloseTuneGate3", 1000 * 60 * 5, false);
		}
		else
		{
		    KillTimer(TMTuneTimers[3]);
		    TMTune[3][0] = 0;
		    MoveObject(TMTune[3][1], 1043.17, -1025.85, 33.66, 1, 0.00, 0.00, 0.00);
		}
	}
	else if(PlayerToPoint(5.0, playerid, 2391.1355, 1041.8885, 10.8203)) // TransFender Las Venturas.
	{
 	    if(TMTune[4][0] <= 0)
 		{
 	        TMTune[4][0] = 1;
 	    	MoveObject(TMTune[4][1], 2394.90, 1043.69, 11.82, 1, 0.00, 90.00, 90.00);
       		TMTuneTimers[4] = SetTimer("CloseTuneGate4", 1000 * 60 * 5, false);
		}
		else
		{
		    KillTimer(TMTuneTimers[4]);
		    TMTune[4][0] = 0;
		    MoveObject(TMTune[4][1], 2387.38, 1043.45, 11.82, 1, 0.00, 0.00, 0.00);
		}
	}
	else
		SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar junto a la puerta de un Transfender, Loco Low Co. o Wheel Arch Angels.");
	return 1;
}

//============================AUTO REPARACION===================================

#define PAYNSPRAY_BEACH             1
#define PAYNSPRAY_NORTH             2
#define PAYNSPRAY_WILLOWFIELD       3

new Float:PayNSprayPos[3][3] = {
	{488.6190, -1731.6849, 11.1661}, // Santa Marina Beach
	{1024.9825, -1032.6246, 31.9083}, // Norte
	{2074.8698, -1831.4533, 13.4793} // Unity
};

new bool:PayNSprayOccupied[3];

stock GetPlayerPayNSpray(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, PayNSprayPos[0][0], PayNSprayPos[0][1], PayNSprayPos[0][2]))
		return PAYNSPRAY_BEACH;
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, PayNSprayPos[1][0], PayNSprayPos[1][1], PayNSprayPos[1][2]))
	    return PAYNSPRAY_NORTH;
	else if(IsPlayerInRangeOfPoint(playerid, 2.0, PayNSprayPos[2][0], PayNSprayPos[2][1], PayNSprayPos[2][2]))
	    return PAYNSPRAY_WILLOWFIELD;
	return 0;
}


public AutoReparacion(playerid, paynsprayid)
{
    new	vehicleid = GetPlayerVehicleID(playerid);

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		RepairVehicle(vehicleid);
	    VehicleInfo[vehicleid][VehHP] = 100;
	    ChangeVehicleColor(vehicleid, VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2]);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Su vehículo ha sido reparado exitosamente.");
		if(paynsprayid == PAYNSPRAY_BEACH)
		{
		 	SetVehiclePos(vehicleid, PayNSprayPos[0][0], PayNSprayPos[0][1], PayNSprayPos[0][2]);
			SetVehicleZAngle(vehicleid, -7.4);
		}
		else if(paynsprayid == PAYNSPRAY_NORTH)
		{
			SetVehiclePos(vehicleid, PayNSprayPos[1][0], PayNSprayPos[1][1], PayNSprayPos[1][2]);
			SetVehicleZAngle(vehicleid, 180.0);
		}
		else if(paynsprayid == PAYNSPRAY_WILLOWFIELD)
		{
			SetVehiclePos(vehicleid, PayNSprayPos[2][0], PayNSprayPos[2][1], PayNSprayPos[2][2]);
			SetVehicleZAngle(vehicleid, -90.0);
		}
	} else
		SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el asiento de conductor del vehículo.");
		
	PayNSprayOccupied[paynsprayid - 1] = false;
    return 1;
}

CMD:repararvehiculo(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		repuestos,
		price,
		paynsprayid = GetPlayerPayNSpray(playerid);
	
	if(paynsprayid == 0)
	    return 1;
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el asiento del conductor de un vehículo!");
    if(CountMecasDuty() >= 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Hay un mecánico en servicio, contactalo para reparar el vehículo.");
	if(PayNSprayOccupied[paynsprayid - 1])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Hay otro vehículo en reparación en el taller, espera a que salga.");
 	repuestos = GetRepairMaterialCost(vehicleid);
	price = repuestos * GetItemPrice(ITEM_ID_REPUESTOAUTO) + 250;
	if(GetPlayerCash(playerid) < price)
	{
		SendFMessage(playerid, COLOR_YELLOW2, "No tienes dinero suficiente para reparar el vehículo. ($%d)", price);
		return 1;
	}
	switch(paynsprayid)
	{
	    case PAYNSPRAY_BEACH:
	    {
	        SetVehiclePos(vehicleid, 487.4321, -1741.4934, 11.6462);
	        SetVehicleZAngle(vehicleid, 172.5599);
		}
	    case PAYNSPRAY_NORTH:
	    {
	        SetVehiclePos(vehicleid, 1024.7690, -1023.3354, 32.5920);
	        SetVehicleZAngle(vehicleid, 0.0);
		}
		case PAYNSPRAY_WILLOWFIELD:
		{
		    SetVehiclePos(vehicleid, 2063.2903, -1831.4307, 13.9557);
		    SetVehicleZAngle(vehicleid, 90.0000);
		}
	}
	PayNSprayOccupied[paynsprayid - 1] = true;
	GivePlayerCash(playerid, -price);
	GameTextForPlayer(playerid, "Su vehiculo esta siendo reparado...", 6000, 1);
	SendFMessage(playerid, COLOR_WHITE, "Su vehículo estará listo en %d segundos por $%d pesos.", 30 + 30 * repuestos, price);
	SetTimerEx("AutoReparacion", 30 * 1000 + repuestos * 30 * 1000, false, "ii", playerid, paynsprayid); // 30 segs reparación basica y si se necesitan, 30 segs por repuesto requerido.
	return 1;
}

