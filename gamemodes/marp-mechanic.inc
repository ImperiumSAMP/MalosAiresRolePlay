#if defined _marp_mechanic_included
	#endinput
#endif
#define _marp_mechanic_included

//=====================SISTEMA Y COMANDOS DE MECANICO===========================

new CarLiftState[4] = 0,
	BoxDoorState[5] = 0;

//================================CONSTANTES====================================

#define JOB_MECH_MAXPRICE       	1000

#define OFFROAD_WHEEL_ID 			1025
#define SHADOW_WHEEL_ID 			1073
#define MEGA_WHEEL_ID 				1074
#define RIMSHINE_WHEEL_ID 			1075
#define WIRES_WHEEL_ID 				1076
#define CLASSIC_WHEEL_ID 			1077
#define TWIST_WHEEL_ID 				1078
#define CUTTER_WHEEL_ID 			1079
#define SWITCH_WHEEL_ID 			1080
#define GROVE_WHEEL_ID 				1081
#define IMPORT_WHEEL_ID 			1082
#define DOLLAR_WHEEL_ID 			1083
#define TRANCE_WHEEL_ID 			1084
#define ATOMIC_WHEEL_ID 			1085
#define AHAB_WHEEL_ID 				1096
#define VIRTUAL_WHEEL_ID 			1097
#define ACCESS_WHEEL_ID 			1098

#define MEC_OFFICE_X				2514.9958
#define MEC_OFFICE_Y        		-1538.2114
#define MEC_OFFICE_Z        		1001.0859

#define MEC_TUNING_PLACE_X      	2514.4778
#define MEC_TUNING_PLACE_Y      	-1553.4338
#define MEC_TUNING_PLACE_Z      	24.0215

#define MEC_REPAIR_PLACE_X      	2514.4778
#define MEC_REPAIR_PLACE_Y      	-1553.4338
#define MEC_REPAIR_PLACE_Z      	24.0215

#define MEC_REPAIR_RANGE            30.0

#define MEC_CARPART_SHOP_X      	976.1300
#define MEC_CARPART_SHOP_Y   		-1254.8500
#define MEC_CARPART_SHOP_Z      	16.9400

#define MEC_LIFT1_X			2498.9763
#define MEC_LIFT1_Y			-1552.2126
#define MEC_LIFT1_Z			24.0215

#define MEC_LIFT2_X			2507.9758
#define MEC_LIFT2_Y			-1552.2126
#define MEC_LIFT2_Z			24.0215

#define MEC_LIFT3_X			2516.9712
#define MEC_LIFT3_Y			-1552.2126
#define MEC_LIFT3_Z			24.0215

#define MEC_LIFT4_X			2525.9624
#define MEC_LIFT4_Y			-1552.2126
#define MEC_LIFT4_Z			24.0215

#define MEC_BOX1_X			2505.0798
#define MEC_BOX1_Y			-1542.4404
#define MEC_BOX1_Z			24.0215

#define MEC_BOX2_X			2514.0881
#define MEC_BOX2_Y			-1542.4404
#define MEC_BOX2_Z			24.0215

#define MEC_BOX3_X			2523.0923
#define MEC_BOX3_Y			-1542.4404
#define MEC_BOX3_Z			24.0215

#define MEC_BOX4_X			2532.0781
#define MEC_BOX4_Y			-1542.4404
#define MEC_BOX4_Z			24.0215

#define MEC_BOX5_X			2503.08521
#define MEC_BOX5_Y			-1578.65002
#define MEC_BOX5_Z			25.42830

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
        if(GetVehicleType(vehicleid) == VTYPE_BIKE)
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
	VehicleInfo[vehicleid][VehPaintjob] = 3;
	ChangeVehiclePaintjob(vehicleid, 3);
	SaveVehicle(vehicleid);
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
	 		if(!IsPlayerInRangeOfPoint(playerid, MEC_REPAIR_RANGE, MEC_REPAIR_PLACE_X, MEC_REPAIR_PLACE_Y, MEC_REPAIR_PLACE_Z))
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
    new clientID = RepairClient[playerid];

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

	TogglePlayerControllable(playerid, false);
	Dialog_Show(playerid, Tuning_Main_Menu, DIALOG_STYLE_TABLIST, "Menú de tuning", "Color primario\t$1.500\nColor secundario\t$1.500\nVinilos\t$10.000\nLlantas\t$4.000\nSuspensión hidraulica\t$4.000\nÓxido nitroso\t$10.000", "Seleccionar", "Cerrar");
	return 1;
}

Dialog:Tuning_Main_Menu(playerid, response, listitem, inputtext[])
{
    TogglePlayerControllable(playerid, true);
    
    new vehicleid = GetPlayerVehicleID(playerid);
    
    if(response)
	{
	    switch(listitem)
	    {
	        case 0:
		    {
				TogglePlayerControllable(playerid, false);
				Dialog_Show(playerid, Tuning_Color1, DIALOG_STYLE_INPUT, "Color primario", "{FFEFD5}Ingrese la ID del color primario a pintar:", "Pintar", "Cerrar");
			}
			case 1:
			{
				TogglePlayerControllable(playerid, false);
				Dialog_Show(playerid, Tuning_Color2, DIALOG_STYLE_INPUT, "Color secundario", "{FFEFD5}Ingrese la ID del color secundario a pintar:", "Pintar", "Cerrar");
			}
			case 2:
			{
				new vehmodel = GetVehicleModel(vehicleid);

				if(vehmodel == 561 || vehmodel == 560 || vehmodel == 559 || vehmodel == 558 || vehmodel == 562 ||
				    vehmodel == 565 || vehmodel == 483 || vehmodel == 575 || vehmodel == 576 || vehmodel == 567 ||
				    vehmodel == 536 || vehmodel == 535 || vehmodel == 534)
				{
				    TogglePlayerControllable(playerid, false);
				    Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
				}
				else
				{
				    SendClientMessage(playerid, COLOR_YELLOW2, "Ese modelo de vehículo no tiene acceso a vinilos o capas de pintura.");
					TogglePlayerControllable(playerid, false);
					Dialog_Show(playerid, Tuning_Main_Menu, DIALOG_STYLE_TABLIST, "Menú de tuning", "Color primario\t$1.500\nColor secundario\t$1.500\nVinilos\t$10.000\nLlantas\t$4.000\nSuspensión hidraulica\t$4.000\nÓxido nitroso\t$10.000", "Seleccionar", "Cerrar");
				}
			}
			case 3:
			{
			    if(GetVehicleType(vehicleid) == VTYPE_BIKE)
	    			return SendClientMessage(playerid, COLOR_WHITE, "Vehiculo inválido.");

				TogglePlayerControllable(playerid, false);
				Dialog_Show(playerid, Tuning_Wheels_Menu, DIALOG_STYLE_LIST, "Llantas disponibles", "Offroad\nShadow\nMega\nRimshine\nWires\nClassic\nTwist\nCutter\nSwitch\nGrove\nImport\nDollar\nTrance\nAtomic\nAhab\nVirtual\nAccess", "Instalar", "Cerrar");
			}
			case 4:
			{
			    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			        return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
			    if(GetVehicleType(vehicleid) == VTYPE_BIKE)
	    			return SendClientMessage(playerid, COLOR_WHITE, "Vehículo invalido!");
				if(GetPlayerCash(playerid) < 4000)
				    return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($4000).");

			    VehicleInfo[vehicleid][VehCompSlot][CARMODTYPE_HYDRAULICS] = 1087;
			    AddVehicleComponent(vehicleid, 1087);
				GivePlayerCash(playerid, -4000);
			    PlayerActionMessage(playerid, 15.0, "comienza a instalar la suspensión hidráulica en el vehículo.");
			    SaveVehicle(vehicleid);
			}
			case 5:
			{
			    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			        return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
			    if(GetVehicleType(vehicleid) == VTYPE_BIKE)
	    			return SendClientMessage(playerid, COLOR_WHITE, "Vehículo invalido!");
				if(GetPlayerCash(playerid) < 10000)
				    return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($10000).");

			    VehicleInfo[vehicleid][VehCompSlot][CARMODTYPE_NITRO] = 1010;
			    AddVehicleComponent(vehicleid, 1010);
				GivePlayerCash(playerid, -10000);
			    PlayerActionMessage(playerid, 15.0, "comienza a instalar el óxido nitroso en el vehículo.");
			    SaveVehicle(vehicleid);
			}
		}
	}
	return 1;
}

Dialog:Tuning_Paintjob_Menu(playerid, response, listitem, inputtext[])
{
    TogglePlayerControllable(playerid, false);

    new vehicleid = GetPlayerVehicleID(playerid);

    switch(listitem)
    {
        case 0:
        {
            if(response)
			{
				PaintjobPreview(playerid, vehicleid, 0);
				Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
			}
			else
			{
				if(GetPlayerCash(playerid) < PRICE_VEHICLE_PAINTJOB)
				{
					SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente ($%d).", PRICE_VEHICLE_PAINTJOB);
					return 1;
				}
				SendFMessage(playerid, COLOR_WHITE, "Has pintado el vehículo con el vinilo seleccionado por $%d.", PRICE_VEHICLE_PAINTJOB);
				GivePlayerCash(playerid, -PRICE_VEHICLE_PAINTJOB);
			    ChangeVehiclePaintjob(vehicleid, 0);
			    VehicleInfo[vehicleid][VehPaintjob] = 0;
			    SaveVehicle(vehicleid);
			    TogglePlayerControllable(playerid, true);
			}
		}
        case 1:
        {
            if(GetVehicleModel(vehicleid) == 483) // Camper
			{
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ese modelo de vehículo no tiene disponible un segundo vinilo.");
		    	Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
				return 1;
			}

            if(response)
			{
				PaintjobPreview(playerid, vehicleid, 1);
				Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
			}
			else
			{
				if(GetPlayerCash(playerid) < PRICE_VEHICLE_PAINTJOB)
				{
					SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente ($%d).", PRICE_VEHICLE_PAINTJOB);
					return 1;
				}
				SendFMessage(playerid, COLOR_WHITE, "Has pintado el vehículo con el vinilo seleccionado por $%d.", PRICE_VEHICLE_PAINTJOB);
				GivePlayerCash(playerid, -PRICE_VEHICLE_PAINTJOB);
			    ChangeVehiclePaintjob(vehicleid, 1);
			    VehicleInfo[vehicleid][VehPaintjob] = 1;
			    SaveVehicle(vehicleid);
			    TogglePlayerControllable(playerid, true);
			}
		}
        case 2:
        {
			if(GetVehicleModel(vehicleid) == 483 || GetVehicleModel(vehicleid) == 575) // Camper y Broadway
			{
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ese modelo de vehículo no tiene disponible un tercer vinilo.");
		    	Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
				return 1;
			}

            if(response)
			{
				PaintjobPreview(playerid, vehicleid, 2);
				Dialog_Show(playerid, Tuning_Paintjob_Menu, DIALOG_STYLE_LIST, "Selecciona el vinilo que quieras visualizar o pintar", "Vinilo 1\nVinilo 2\nVinilo 3\nCerrar", "Visualizar", "Pintar");
			}
			else
			{
				if(GetPlayerCash(playerid) < PRICE_VEHICLE_PAINTJOB)
				{
					SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente ($%d).", PRICE_VEHICLE_PAINTJOB);
					return 1;
				}
				SendFMessage(playerid, COLOR_WHITE, "Has pintado el vehículo con el vinilo seleccionado por $%d.", PRICE_VEHICLE_PAINTJOB);
				GivePlayerCash(playerid, -PRICE_VEHICLE_PAINTJOB);
			    ChangeVehiclePaintjob(vehicleid, 2);
			    VehicleInfo[vehicleid][VehPaintjob] = 2;
			    SaveVehicle(vehicleid);
			    TogglePlayerControllable(playerid, true);
			}
		}
		case 3:
		{
		    TogglePlayerControllable(playerid, true);
		}
	}
	return 1;
}

Dialog:Tuning_Color1(playerid, response, listitem, inputtext[])
{
    TogglePlayerControllable(playerid, true);
    
    new vehicleid = GetPlayerVehicleID(playerid);
    
    if(response)
    {
	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
		if(GetPlayerCash(playerid) < 1500)
			return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($1500).");
		new color = strval(inputtext);
		if(color < 0 || color > 255)
		    return SendClientMessage(playerid, COLOR_WHITE, "Ingresa un valor entre 0 y 255");

		PlayerActionMessage(playerid, 15.0, "comienza a pintar el color primario del vehículo.");
	    GivePlayerCash(playerid, -1500);
	    VehicleInfo[vehicleid][VehColor1] = color;
	    ChangeVehicleColor(vehicleid, VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2]);
	    SaveVehicle(vehicleid);
	}
	return 1;
}

Dialog:Tuning_Color2(playerid, response, listitem, inputtext[])
{
    TogglePlayerControllable(playerid, true);

    new vehicleid = GetPlayerVehicleID(playerid);
    
    if(response)
    {
	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
		if(GetPlayerCash(playerid) < 1500)
			return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($1500).");
		new color = strval(inputtext);
		if(color < 0 || color > 255)
		    return SendClientMessage(playerid, COLOR_WHITE, "Ingresa un valor entre 0 y 255.");

		PlayerActionMessage(playerid, 15.0, "comienza a pintar el color secundario del vehículo.");
	    GivePlayerCash(playerid, -1500);
	    VehicleInfo[vehicleid][VehColor2] = color;
	    ChangeVehicleColor(vehicleid, VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2]);
	    SaveVehicle(vehicleid);
    }
    return 1;
}

Dialog:Tuning_Wheels_Menu(playerid, response, listitem, inputtext[])
{
    TogglePlayerControllable(playerid, true);
    
    new vehicleid = GetPlayerVehicleID(playerid);
    
    if(response)
    {
	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
		if(GetPlayerCash(playerid) < 4000)
			return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($4000).");

	    PlayerActionMessage(playerid, 15.0, "comienza a instalar las nuevas llantas en el vehículo.");
		GivePlayerCash(playerid, -4000);
		
		new wheel;

		switch(listitem)
		{
		    case 0: wheel = OFFROAD_WHEEL_ID;
		    case 1: wheel = SHADOW_WHEEL_ID;
		    case 2: wheel = MEGA_WHEEL_ID;
		    case 3: wheel = RIMSHINE_WHEEL_ID;
		    case 4: wheel = WIRES_WHEEL_ID;
		    case 5: wheel = CLASSIC_WHEEL_ID;
		    case 6: wheel = TWIST_WHEEL_ID;
		    case 7: wheel = CUTTER_WHEEL_ID;
		    case 8: wheel = SWITCH_WHEEL_ID;
		    case 9: wheel = GROVE_WHEEL_ID;
		    case 10: wheel = IMPORT_WHEEL_ID;
		    case 11: wheel = DOLLAR_WHEEL_ID;
		    case 12: wheel = TRANCE_WHEEL_ID;
		    case 13: wheel = ATOMIC_WHEEL_ID;
		    case 14: wheel = AHAB_WHEEL_ID;
		    case 15: wheel = VIRTUAL_WHEEL_ID;
		    case 16: wheel = ACCESS_WHEEL_ID;
		}
		AddVehicleComponent(vehicleid, wheel);
		VehicleInfo[vehicleid][VehCompSlot][CARMODTYPE_WHEELS] = wheel;
		SaveVehicle(vehicleid);
	}
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

//==============================================================================

public OnVehicleMod(playerid, vehicleid, componentid)
{
    if(GetPlayerInterior(playerid) == 0)
    {
        BanPlayer(playerid, INVALID_PLAYER_ID, "Cheat Vehicle Mod", 0);
        return 1;
	}
	if(VehicleInfo[vehicleid][VehType] != VEH_OWNED)
	{
    	SendClientMessage(playerid, COLOR_YELLOW2, "Las modificaciones no se guardarán permanentemente ya que por el momento solo se pueden tunear autos personales.");
		return 1;
	}
	if(GetVehicleComponentType(componentid) == CARMODTYPE_NITRO || GetVehicleComponentType(componentid) == CARMODTYPE_WHEELS || GetVehicleComponentType(componentid) == CARMODTYPE_HYDRAULICS)
  	{
 		SendClientMessage(playerid, COLOR_YELLOW2, "Las modificaciones de llantas, óxido nitroso y suspensión no se guardarán, ya que se hacen en un taller mecánico.");
		return 1;
	}
 	if(GetPlayerCash(playerid) < PRICE_VEHICLE_MODS)
  	{
  	    SendFMessage(playerid, COLOR_YELLOW2, "Las modificación no ha sido guardada permanentemente ya que no tienes el dinero suficiente ($%d).", PRICE_VEHICLE_MODS);
		return 1;
	}
	
	VehicleInfo[vehicleid][VehCompSlot][GetVehicleComponentType(componentid)] = componentid;
	SaveVehicle(vehicleid);
    GivePlayerCash(playerid, -PRICE_VEHICLE_MODS);
    GiveFactionMoney(FAC_MECH, PRICE_VEHICLE_MODS / 10);
    SendFMessage(playerid, COLOR_WHITE, "Las modificación te ha costado un extra de $%d, y ha sido guardada permanentemente.", PRICE_VEHICLE_MODS);
    return 1;
}

PaintjobPreview(playerid, vehicleid, paintjob)
{
	ChangeVehiclePaintjob(vehicleid, paintjob);
	if(paintjobPreviewTimer[playerid] == 0)
	{
	    SendClientMessage(playerid, COLOR_WHITE, "[INFO]: En 40 segundos se restaurará la pintura original del vehículo, ya que estás en modo de pre-visualización.");
	    paintjobPreviewTimer[playerid] = SetTimerEx("RestoreOriginalPaintjob", 40000, false, "ii", vehicleid, playerid);
	}
}

forward RestoreOriginalPaintjob(vehicleid, playerid);
public RestoreOriginalPaintjob(vehicleid, playerid)
{
	ChangeVehiclePaintjob(vehicleid, VehicleInfo[vehicleid][VehPaintjob]);
    paintjobPreviewTimer[playerid] = 0;
	return 1;
}

CMD:mecelevador(playerid, params[]) {
	new direccion[6];

	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
		return 1;

	if(sscanf(params, "s", direccion)) 
	{
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /mecelevador [dirección: subir - bajar]");
	} 
	else if(strcmp(direccion, "subir", true) == 0) 
	{
		if(PlayerToPoint(2.0, playerid, MEC_LIFT1_X, MEC_LIFT1_Y, MEC_LIFT1_Z)) // Primer elevador
		{

			if(CarLiftState[0] == 0) // En el piso
			{
				MoveObject(CarLift[0][0], 2502.91235, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][1], 2502.91235, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][2], 2502.91235, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][3], 2500.90503, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][4], 2500.90503, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][5], 2500.90503, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][6], 2503.02930, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][7], 2503.02930, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][8], 2500.05005, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][9], 2500.05005, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[0] = 1; // Pasa a la altura intermedia
				return 1;
			}
			if(CarLiftState[0] == 1) // Altura intermedia
			{
				MoveObject(CarLift[0][0], 2502.91235, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][1], 2502.91235, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][2], 2502.91235, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][3], 2500.90503, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][4], 2500.90503, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][5], 2500.90503, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][6], 2503.02930, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][7], 2503.02930, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][8], 2500.05005, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][9], 2500.05005, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[0] = 2; // Pasa a la altura máxima
				return 1;
			}
			if(CarLiftState[0] == 2) // Altura máxima
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura máxima!");
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT2_X, MEC_LIFT2_Y, MEC_LIFT2_Z))  // Segundo elevador
		{

			if(CarLiftState[1] == 0) // En el piso
			{
				MoveObject(CarLift[1][0], 2511.90991, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][1], 2511.90991, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][2], 2511.90991, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][3], 2509.90259, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][4], 2509.90259, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][5], 2509.90259, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][6], 2512.02856, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][7], 2512.02856, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][8], 2509.04932, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][9], 2509.04932, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[1] = 1; // Pasa a la altura intermedia
				return 1;
			}
			if(CarLiftState[1] == 1) // Altura intermedia
			{
				MoveObject(CarLift[1][0], 2511.90991, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][1], 2511.90991, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][2], 2511.90991, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][3], 2509.90259, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][4], 2509.90259, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][5], 2509.90259, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][6], 2512.02856, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][7], 2512.02856, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][8], 2509.04932, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][9], 2509.04932, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[1] = 2; // Pasa a la altura máxima
				return 1;
			}
			if(CarLiftState[1] == 2) // Altura máxima
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura máxima!");
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT3_X, MEC_LIFT3_Y, MEC_LIFT3_Z))  // Tercer elevador
		{

			if(CarLiftState[2] == 0) // En el piso
			{
				MoveObject(CarLift[2][0], 2520.90747, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][1], 2520.90747, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][2], 2520.90747, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][3], 2518.90015, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][4], 2518.90015, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][5], 2518.90015, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][6], 2521.02759, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][7], 2521.02759, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][8], 2518.04834, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][9], 2518.04834, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[2] = 1; // Pasa a la altura intermedia
				return 1;
			}
			if(CarLiftState[2] == 1) // Altura intermedia
			{
				MoveObject(CarLift[2][0], 2520.90747, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][1], 2520.90747, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][2], 2520.90747, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][3], 2518.90015, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][4], 2518.90015, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][5], 2518.90015, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][6], 2521.02759, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][7], 2521.02759, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][8], 2518.04834, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][9], 2518.04834, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[2] = 2; // Pasa a la altura máxima
				return 1;
			}
			if(CarLiftState[2] == 2) // Altura máxima
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura máxima!");
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT4_X, MEC_LIFT4_Y, MEC_LIFT4_Z))  // Cuarto elevador
		{

			if(CarLiftState[3] == 0) // En el piso
			{
				MoveObject(CarLift[3][0], 2529.90479, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][1], 2529.90552, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][2], 2529.90479, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][3], 2527.89795, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][4], 2527.89795, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][5], 2527.89795, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][6], 2530.02686, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][7], 2530.02686, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][8], 2527.04761, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][9], 2527.04761, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[3] = 1; // Pasa a la altura intermedia
				return 1;
			}
			if(CarLiftState[3] == 1) // Altura intermedia
			{
				MoveObject(CarLift[3][0], 2529.90479, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][1], 2529.90552, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][2], 2529.90479, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][3], 2527.89795, -1551.49353, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][4], 2527.89795, -1549.05115, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][5], 2527.89795, -1547.87915, 25.7421, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][6], 2530.02686, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][7], 2530.02686, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][8], 2527.04761, -1552.22412, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][9], 2527.04761, -1547.87463, 25.2021, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[3] = 2; // Pasa a la altura máxima
				return 1;
			}
			if(CarLiftState[3] == 2) // Altura máxima
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura máxima!");
				return 1;
			}
		}
	}
	else if(strcmp(direccion, "bajar", true) == 0)
	{
		if(PlayerToPoint(2.0, playerid, MEC_LIFT1_X, MEC_LIFT1_Y, MEC_LIFT1_Z)) // Primer elevador
		{
			if(CarLiftState[0] == 0) // En el piso
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura mínima!");
				return 1;
			}

			if(CarLiftState[0] == 1) // Altura intermedia
			{
				MoveObject(CarLift[0][0], 2502.91235, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][1], 2502.91235, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][2], 2502.91235, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][3], 2500.90503, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][4], 2500.90503, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][5], 2500.90503, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][6], 2503.02930, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][7], 2503.02930, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][8], 2500.05005, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][9], 2500.05005, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[0] = 0; // Pasa a la altura mínima
				return 1;
			}
			if(CarLiftState[0] == 2) // Altura máxima
			{
				MoveObject(CarLift[0][0], 2502.91235, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][1], 2502.91235, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][2], 2502.91235, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][3], 2500.90503, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][4], 2500.90503, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][5], 2500.90503, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][6], 2503.02930, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][7], 2503.02930, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][8], 2500.05005, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[0][9], 2500.05005, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[0] = 1; // Pasa al nivel intermedio
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT2_X, MEC_LIFT2_Y, MEC_LIFT2_Z)) // Segundo elevador
		{

			if(CarLiftState[1] == 0) // En el piso
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura mínima!");
				return 1;
			}
			if(CarLiftState[1] == 1) // Altura intermedia
			{
				MoveObject(CarLift[1][0], 2511.90991, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][1], 2511.90991, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][2], 2511.90991, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][3], 2509.90259, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][4], 2509.90259, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][5], 2509.90259, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][6], 2512.02856, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][7], 2512.02856, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][8], 2509.04932, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][9], 2509.04932, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[1] = 0; // Pasa a la altura mínima
				return 1;
			}
			if(CarLiftState[1] == 2) // Altura máxima
			{
				MoveObject(CarLift[1][0], 2511.90991, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][1], 2511.90991, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][2], 2511.90991, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][3], 2509.90259, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][4], 2509.90259, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][5], 2509.90259, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][6], 2512.02856, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][7], 2512.02856, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][8], 2509.04932, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[1][9], 2509.04932, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[1] = 1; // Pasa a la altura intermedia
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT3_X, MEC_LIFT3_Y, MEC_LIFT3_Z)) // Tercer elevador
		{

			if(CarLiftState[2] == 0) // En el piso
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura mínima!");
				return 1;
			}
			if(CarLiftState[2] == 1) // Altura intermedia
			{
				MoveObject(CarLift[2][0], 2520.90747, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][1], 2520.90747, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][2], 2520.90747, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][3], 2518.90015, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][4], 2518.90015, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][5], 2518.90015, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][6], 2521.02759, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][7], 2521.02759, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][8], 2518.04834, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][9], 2518.04834, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[2] = 0; // Pasa a la altura mínima
				return 1;
			}
			if(CarLiftState[2] == 2) // Altura máxima
			{
				MoveObject(CarLift[2][0], 2520.90747, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][1], 2520.90747, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][2], 2520.90747, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][3], 2518.90015, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][4], 2518.90015, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][5], 2518.90015, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][6], 2521.02759, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][7], 2521.02759, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][8], 2518.04834, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[2][9], 2518.04834, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[2] = 1; // Pasa a la altura intermedia
				return 1;
			}
		}
		if(PlayerToPoint(2.0, playerid, MEC_LIFT4_X, MEC_LIFT4_Y, MEC_LIFT4_Z)) // Cuarto elevador
		{

			if(CarLiftState[3] == 0) // En el piso
			{
				SendClientMessage(playerid, COLOR_WHITE, "¡El elevador ya está en su altura mínima!");
				return 1;
			}
			if(CarLiftState[3] == 1) // Altura intermedia
			{
				MoveObject(CarLift[3][0], 2529.90479, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][1], 2529.90552, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][2], 2529.90479, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][3], 2527.89795, -1551.49353, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][4], 2527.89795, -1549.05115, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][5], 2527.89795, -1547.87915, 23.00110, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][6], 2530.02686, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][7], 2530.02686, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][8], 2527.04761, -1552.22412, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][9], 2527.04761, -1547.87463, 22.48530, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[3] = 0; // Pasa a la altura mínima
				return 1;
			}
			if(CarLiftState[3] == 2) // Altura máxima
			{
				MoveObject(CarLift[3][0], 2529.90479, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][1], 2529.90552, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][2], 2529.90479, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][3], 2527.89795, -1551.49353, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][4], 2527.89795, -1549.05115, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][5], 2527.89795, -1547.87915, 24.6369, 1, 90.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][6], 2530.02686, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][7], 2530.02686, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][8], 2527.04761, -1552.22412, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(CarLift[3][9], 2527.04761, -1547.87463, 24.1069, 1, 0.00000, 0.00000, 0.00000);
				PlayerActionMessage(playerid, 15.0, "presiona un botón en el tablero del elevador.");
				CarLiftState[3] = 1; // Pasa a la altura intermedia
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "¡Elige una opción válida!");
	}
	return 1;
}

CMD:mecpuerta(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] != FAC_MECH)
		return 1;

	if(PlayerToPoint(2.0, playerid, MEC_BOX1_X, MEC_BOX1_Y, MEC_BOX1_Z))
	{
	    if(BoxDoorState[0] == 0) // La puerta está cerrada
	    {
			MoveObject(TMBoxDoor[0], 2501.51221, -1545.00256, 26.45690, 1, 85.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[0] = 1;
	    }
	    else // La puerta está abierta
	    {
			MoveObject(TMBoxDoor[0], 2501.51221, -1541.55261, 26.25690, 1, 0.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[0] = 0;
	    }
	}
	
	if(PlayerToPoint(2.0, playerid, MEC_BOX2_X, MEC_BOX2_Y, MEC_BOX2_Z))
	{
	    if(BoxDoorState[1] == 0) // La puerta está cerrada
	    {
			MoveObject(TMBoxDoor[1], 2510.52441, -1545.00256, 26.45690, 1, 85.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[1] = 1;
	    }
	    else // La puerta está abierta
	    {
			MoveObject(TMBoxDoor[1], 2510.52441, -1541.55261, 26.25690, 1, 0.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[1] = 0;
	    }
	}
	
	if(PlayerToPoint(2.0, playerid, MEC_BOX3_X, MEC_BOX3_Y, MEC_BOX3_Z))
	{
	    if(BoxDoorState[2] == 0) // La puerta está cerrada
	    {
			MoveObject(TMBoxDoor[2], 2519.52393, -1545.00256, 26.45690, 1, 85.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[2] = 1;
	    }
	    else // La puerta está abierta
	    {
			MoveObject(TMBoxDoor[2], 2519.52393, -1541.55261, 26.25690, 1, 0.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[2] = 0;
	    }
	}
	
	if(PlayerToPoint(2.0, playerid, MEC_BOX4_X, MEC_BOX4_Y, MEC_BOX4_Z))
	{
	    if(BoxDoorState[3] == 0) // La puerta está cerrada
	    {
			MoveObject(TMBoxDoor[3], 2528.50708, -1545.00256, 26.45690, 1, 85.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[3] = 1;
	    }
	    else // La puerta está abierta
	    {
			MoveObject(TMBoxDoor[3], 2528.50708, -1541.55261, 26.25690, 1, 0.00000, 0.00000, 0.00000);
			PlayerActionMessage(playerid, 15.0, "presiona un botón en el control de la puerta.");
	        BoxDoorState[3] = 0;
	    }
	}

	if(PlayerToPoint(5.0, playerid, MEC_BOX5_X, MEC_BOX5_Y, MEC_BOX5_Z))
	{
	    if(BoxDoorState[4] == 0) // La puerta está cerrada
	    {
			MoveObject(TMBoxDoor[4], 2500.53320, -1578.65002, 25.66030, 1, -85.00000, 0.00000, 90.00000);
	        BoxDoorState[4] = 1;
	    }
	    else // La puerta está abierta
	    {
			MoveObject(TMBoxDoor[4], 2503.08521, -1578.65002, 25.42830, 1, 0.00000, 0.00000, 90.00000);
	        BoxDoorState[4] = 0;
	    }
	}
	return 1;
}
