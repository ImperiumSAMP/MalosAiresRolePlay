#if defined _isamp_cardealer_included
	#endinput
#endif
#define _isamp_cardealer_included

//=================================CONSTANTES===================================

#define MAX_DEALERS             2

#define CAR_DEALER_GROTTI       0
#define CAR_DEALER_JEFFERSON    1

#define MAX_DEALER_CARS         32

#define DLG_CARDEALER1	    	10031
#define DLG_CARDEALER2	    	10032
#define DLG_CARDEALER3	    	10033
#define DLG_CARDEALER4	    	10034

#define MODEL_CREATE            1
#define MODEL_UPDATE            2
#define MODEL_DELETE            3

//=================================VARIABLES====================================

enum DealerModelInfo {
	dModel,
	dStock
};

new CarDealerInfo[MAX_DEALERS][MAX_DEALER_CARS][DealerModelInfo];

new carModelSelection[MAX_PLAYERS],
	carColor1Selection[MAX_PLAYERS],
	carColor2Selection[MAX_PLAYERS];

forward OnDealershipDataLoad(dealer);
forward SaveDealershipModel(dealer, dealerslot, option);

//============================FUNCIONES PUBLICAS================================

LoadCarDealerships()
{
	new query[128];
	
	for(new i = 0; i < MAX_DEALERS; i++)
	{
		format(query, sizeof(query), "SELECT * FROM `dealerships_info` WHERE `Id`=%d LIMIT %d", i, MAX_DEALER_CARS);
		mysql_function_query(dbHandle, query, true, "OnDealershipDataLoad", "i", i);
	}
	return 1;
}

public OnDealershipDataLoad(dealer)
{
   	new result[128],
	   	rows,
	   	fields,
	   	aux = 0; // Desde el primer registro obtenido que se almacena en posicion cero dentro de los resultados

	cache_get_data(rows, fields);

	if(rows)
	{
		while(aux < rows)
	    {
			cache_get_field_content(aux, "Model", result); 			CarDealerInfo[dealer][aux][dModel] = strval(result);
			cache_get_field_content(aux, "Stock", result); 			CarDealerInfo[dealer][aux][dStock] = strval(result);
			aux ++;
		}
	}
	return 1;
}

public SaveDealershipModel(dealer, dealerslot, option)
{
	new query[256];

	if(dontsave)
	    return 1;

	if(option == MODEL_CREATE)
	{
		format(query, sizeof(query), "INSERT INTO `dealerships_info` (`Id`, `Model`, `Stock`) VALUES (%d, %d, %d)",
		    dealer,
		    CarDealerInfo[dealer][dealerslot][dModel],
		    CarDealerInfo[dealer][dealerslot][dStock]
		);
	}
	else if(option == MODEL_UPDATE)
	{
		format(query, sizeof(query), "UPDATE `dealerships_info` SET `Stock`=%d WHERE `Id`=%d AND `Model`=%d",
		    CarDealerInfo[dealer][dealerslot][dStock],
  		    dealer,
		    CarDealerInfo[dealer][dealerslot][dModel]
		);
	}
	else if(option == MODEL_DELETE)
	{
		format(query, sizeof(query), "DELETE FROM `dealerships_info` WHERE `Id`=%d AND `Model`=%d",
  		    dealer,
		    CarDealerInfo[dealer][dealerslot][dModel]
		);
	}
	
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}


SearchCarDealerForModel(dealer, model)
{
	if(dealer >= 0 && dealer < MAX_DEALERS)
	{
		for(new i = 0; i < MAX_DEALER_CARS; i++)
		{
		    if(CarDealerInfo[dealer][i][dModel] == model)
		        return i;
		}
	}
	return -1;
}

CMD:cardealerdebug(playerid, params[])
{
	new dealer;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", dealer))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /cardealerdebug [id consecionaria]");
	if(dealer < 0 || dealer >= MAX_DEALERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID inválida.");

    for(new x = 0; x < MAX_DEALER_CARS; x++)
    {
        SendFMessage(playerid, COLOR_YELLOW, "CarDealerInfo[%d][%d] dModel = %d", dealer, x, CarDealerInfo[dealer][x][dModel]);
        SendFMessage(playerid, COLOR_YELLOW, "CarDealerInfo[%d][%d] dStock = %d", dealer, x, CarDealerInfo[dealer][x][dStock]);
	}
	return 1;
}

CMD:playercardealerdebug(playerid, params[])
{
	new targetid;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "i", targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /playercardealerdebug [playerid]");
	if(targetid < 0 || targetid >= MAX_PLAYERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");

	SendFMessage(playerid, COLOR_YELLOW, "carModelSelection [%d] = %d", targetid, carModelSelection[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "carColor1Selection [%d] = %d", targetid, carColor1Selection[targetid]);
	SendFMessage(playerid, COLOR_YELLOW, "carColor2Selection [%d] = %d", targetid, carColor2Selection[targetid]);
	return 1;
}

GetPlayerCarDealer(playerid)
{
	if(PlayerToPoint(3.0, playerid, 542.3592, -1292.8329, 17.1696))
	    return CAR_DEALER_GROTTI;
	else if (PlayerToPoint(3.0, playerid, 2131.7793, -1150.9172, 24.0211))
	    return CAR_DEALER_JEFFERSON;

	return -1;
}

CMD:agregarmodelo(playerid, params[])
{
	new dealer, model, carstock;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "iii", dealer, model, carstock))
		return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agregarmodelo [ID consecionaria] [modelo] [stock] (IDs Grotti:0 - Jefferson:1)");
	if(GetPlayerCarDealer(playerid) == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes estar en la consecionaria y chequear que nadie esté comprando en este momento.");
	if(dealer < 0 || dealer >= MAX_DEALERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de consecionaria inválida.");
	if(model < 400 || model > 611)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de modelo inválida.");
	if(carstock < 1 || carstock > 50)
     	return SendClientMessage(playerid, COLOR_YELLOW2, "Stock inválido: solo se permite de 1 a 50.");

	for(new i = 0; i < MAX_DEALER_CARS; i++)
	{
	    if(CarDealerInfo[dealer][i][dModel] == model)
	    {
	        SendFMessage(playerid, COLOR_WHITE, "El modelo %d ya se encontraba a la venta en la consecionaria ID %d con un stock de %d.", model, dealer, CarDealerInfo[dealer][i][dStock]);
            SendFMessage(playerid, COLOR_WHITE, "Ahora el stock de ese modelo ha sido seteado en %d unidades.", carstock);
            CarDealerInfo[dealer][i][dStock] = carstock;
            SaveDealershipModel(dealer, i, MODEL_UPDATE);
            return 1;
		}
	}
	
	for(new x = 0; x < MAX_DEALER_CARS; x++)
	{
	    if(CarDealerInfo[dealer][x][dModel] == 0)
	    {
	        CarDealerInfo[dealer][x][dModel] = model;
	        CarDealerInfo[dealer][x][dStock] = carstock;
	    	SendFMessage(playerid, COLOR_WHITE, "Has agregado el modelo %d con un stock de %d unidades a la consecionaria ID %d.", model, carstock, dealer);
            SaveDealershipModel(dealer, x, MODEL_CREATE);
			return 1;
		}
	}
	
	SendFMessage(playerid, COLOR_YELLOW2, "No hay mas lugar para otro modelo a la venta en la consecionaria ID %d (MAX:%d).", dealer, MAX_DEALER_CARS);
	return 1;
}

CMD:borrarmodelo(playerid, params[])
{
	new dealer, model;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "ii", dealer, model))
		return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /borrarmodelo [ID consecionaria] [modelo] (IDs Grotti:0 - Jefferson:1)");
	if(GetPlayerCarDealer(playerid) == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes estar en la consecionaria y chequear que nadie esté comprando en este momento.");
	if(dealer < 0 || dealer >= MAX_DEALERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de consecionaria inválida.");
	if(model < 400 || model > 611)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de modelo inválida.");

	for(new i = 0; i < MAX_DEALER_CARS; i++)
	{
	    if(CarDealerInfo[dealer][i][dModel] == model)
	    {
	        SaveDealershipModel(dealer, i, MODEL_DELETE);
            CarDealerInfo[dealer][i][dModel] = 0;
			CarDealerInfo[dealer][i][dStock] = 0;
	        SendFMessage(playerid, COLOR_WHITE, "El modelo %d ha sido quitado de venta en la consecionaria ID %d.", model, dealer);
		    return 1;
		}
	}

	SendFMessage(playerid, COLOR_YELLOW2, "Error: el modelo %d no se encuentra a la venta en la consecionaria ID %d.", model, dealer);
	return 1;
}

LoadCarDealerPickups()
{
    CreateDynamicPickup(1239, 1, 542.3592, -1292.8329, 17.1696);
    CreateDynamic3DTextLabel("Consecionaria\n/vercatalogo para ver los vehículos en venta.", COLOR_WHITE, 542.3592, -1292.8329, 17.1696 + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    CreateDynamicPickup(1239, 1, 2131.7793, -1150.9172, 24.0211);
    CreateDynamic3DTextLabel("Consecionaria\n/vercatalogo para ver los vehículos en venta.", COLOR_WHITE, 2131.7793, -1150.9172, 24.0211 + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

CMD:vercatalogo(playerid, params[])
{
	new string[2000] = "Modelo\t\tPrecio\t\tMaletero",
	    dealer = GetPlayerCarDealer(playerid),
	    model;

	if(dealer == -1)
     	return SendClientMessage(playerid, COLOR_YELLOW2, "Para usar este comando debes estar en una consecionaria.");
     	
	for(new i = 0; i < MAX_DEALER_CARS; i++)
	{
	    model = CarDealerInfo[dealer][i][dModel];
	    if(model != 0)
	    {
	        if(CarDealerInfo[dealer][i][dStock] > 0)
	        {
	            if(GetVehicleModelTrunkSlots(model) > 0)
	        		format(string, sizeof(string), "%s\n%s\t\t$%d\t\tSlots: %d", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100), GetVehicleModelTrunkSlots(model));
				else
				    format(string, sizeof(string), "%s\n%s\t\t$%d\t\tNo tiene", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100));
			}
		}
	}
	ShowPlayerDialog(playerid, DLG_CARDEALER1, DIALOG_STYLE_LIST, "Catálogo de vehículos en venta", string, "Seleccionar", "Cerrar");
	return 1;
}
	
OnCarDealerDialogResponse(playerid, response, listitem)
{
	new dealer = GetPlayerCarDealer(playerid),
	    aux = 0;
	
	if(dealer == -1)
     	return SendClientMessage(playerid, COLOR_YELLOW2, "Error: debes estar en una consecionaria.");

	if(response)
	{
		if(listitem == 0)
			cmd_vercatalogo(playerid, "");
  		else
  		{
  		    for(new i = 0; i < MAX_DEALER_CARS; i++)
  		    {
  		    	if(CarDealerInfo[dealer][i][dModel] != 0)
  		    	    aux++;
				if(aux == listitem)
				{
                    carModelSelection[playerid] = CarDealerInfo[dealer][i][dModel];
                    break;
				}
			}
			ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el número de color {00FF00}primario {a9c4e4}que desea.\n\nColores básicos:\n\t0 - Negro\n\t1 - Blanco\n\t2 - Azul\n\t3 - Rojo\n\t6 - Amarillo\n\t16 - Verde\n\nPara ver una lista mas amplia de colores, visite nuestro catálogo online:\n\thttp://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
  		}
	}
 	return 1;
}

OnCarDealer2DialogResponse(playerid, response, inputtext[])
{
	if(response)
	{
		new color1 = strval(inputtext);
		
		if(color1 < 0 || color1 > 255)
		{
			ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el numero de color {00FF00}primario {a9c4e4}que desea.\n\nColores básicos:\n\t0 - Negro\n\t1 - Blanco\n\t2 - Azul\n\t3 - Rojo\n\t6 - Amarillo\n\t16 - Verde\n\nPara ver una lista mas amplia de colores, visite nuestro catálogo online:\n\thttp://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa un número de color válido (0-255).");
		}
		
		carColor1Selection[playerid] = color1;
		ShowPlayerDialog(playerid, DLG_CARDEALER3, DIALOG_STYLE_INPUT, "Selección de color 2", "Ingrese a continuación el número de color {00FF00}secundario {a9c4e4}que desea.\n\nColores básicos:\n\t0 - Negro\n\t1 - Blanco\n\t2 - Azul\n\t3 - Rojo\n\t6 - Amarillo\n\t16 - Verde\n\nPara ver una lista mas amplia de colores, visite nuestro catálogo online:\n\thttp://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
	}
	else
	    cmd_vercatalogo(playerid, "");
 	return 1;
}

OnCarDealer3DialogResponse(playerid, response, inputtext[])
{
	if(response)
	{
		new color2 = strval(inputtext),
		    dealer = GetPlayerCarDealer(playerid),
		    str[128];

		if(dealer == -1)
     		return SendClientMessage(playerid, COLOR_YELLOW2, "Error: debes estar en una consecionaria.");
		if(color2 < 0 || color2 > 255)
		{
			ShowPlayerDialog(playerid, DLG_CARDEALER3, DIALOG_STYLE_INPUT, "Selección de color 2", "Ingrese a continuación el numero de color {00FF00}secundario {a9c4e4}que desea.\n\nColores básicos:\n\t0 - Negro\n\t1 - Blanco\n\t2 - Azul\n\t3 - Rojo\n\t6 - Amarillo\n\t16 - Verde\n\nPara ver una lista mas amplia de colores, visite nuestro catálogo online:\n\thttp://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa un número de color válido (0-255).");
		}

        carColor2Selection[playerid] = color2;
  		format(str, sizeof(str), "Detalles del pedido:\n\n\tModelo: %s\n\tColor primario: %d\n\tColor secundario: %d\n\tPrecio: $%d", GetVehicleModelName(carModelSelection[playerid]), carColor1Selection[playerid], carColor2Selection[playerid], GetVehicleModelPrice(carModelSelection[playerid], 100));
		ShowPlayerDialog(playerid, DLG_CARDEALER4, DIALOG_STYLE_MSGBOX, "Confirmación de la compra", str, "Comprar", "Cancelar");
	}
	else
	    ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el numero de color {00FF00}primario {a9c4e4}que desea.\n\nColores básicos:\n\t0 - Negro\n\t1 - Blanco\n\t2 - Azul\n\t3 - Rojo\n\t6 - Amarillo\n\t16 - Verde\n\nPara ver una lista mas amplia de colores, visite nuestro catálogo online:\n\thttp://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
 	return 1;
}

OnCarDealer4DialogResponse(playerid, response)
{
	if(response)
	{
		new dealer = GetPlayerCarDealer(playerid),
		    price = GetVehicleModelPrice(carModelSelection[playerid], 100),
		    dealerSlot = SearchCarDealerForModel(dealer, carModelSelection[playerid]),
 		   	newveh = -1,
		    playerName[MAX_PLAYER_NAME];

		if(dealer == -1)
     		return SendClientMessage(playerid, COLOR_YELLOW2, "Error: debes estar en una consecionaria.");
		if(dealerSlot == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Error: ese modelo ya no se encuentra a la venta.");
		if(CarDealerInfo[dealer][dealerSlot][dStock] <= 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Error: ese modelo ya no se encuentra a la venta.");
		if(getPlayerFreeKeySlots(playerid) < 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Error: no tienes más espacio en tu llavero para otra llave.");
		if(GetPlayerCash(playerid) < price)
        	return SendClientMessage(playerid, COLOR_YELLOW2,"* Vendedor: ¡Vuelve cuando tengas el dinero suficiente!");

		for(new vid = 1; vid < MAX_VEH; vid++)
		{
			if(VehicleInfo[vid][VehType] == VEH_NONE)
			{
			    newveh = vid;
			    break;
			}
	    }
	    if(newveh == -1) // Si no encontró ningun auto de tipo VEH_NONE es pq ya no hay mas lugar dentro de los MAX_VEH
			return SendClientMessage(playerid, COLOR_YELLOW2, "[OOC]: No hay mas espacio para autos en el servidor. REPORTAR A UN ADMIN.");

        CarDealerInfo[dealer][dealerSlot][dStock] --;
        if(CarDealerInfo[dealer][dealerSlot][dStock] == 0)
        {
            SaveDealershipModel(dealer, dealerSlot, MODEL_DELETE);
	        CarDealerInfo[dealer][dealerSlot][dModel] = 0;
		}
		else
		    SaveDealershipModel(dealer, dealerSlot, MODEL_UPDATE);

		GivePlayerCash(playerid, -price);
	 	GetPlayerName(playerid, playerName, sizeof(playerName));
		VehicleInfo[newveh][VehType] = VEH_OWNED;
		VehicleInfo[newveh][VehOwnerSQLID] = PlayerInfo[playerid][pID];
		VehicleInfo[newveh][VehOwnerName] = playerName;
		VehicleInfo[newveh][VehColor1] = carColor1Selection[playerid];
		VehicleInfo[newveh][VehColor2] = carColor2Selection[playerid];
		VehicleInfo[newveh][VehModel] = carModelSelection[playerid];
		format(VehicleInfo[newveh][VehPlate], 32, "%c%c%c-%d%d%d",65+random(26),65+random(26),65+random(26),random(10),random(10),random(10));

		if(dealer == CAR_DEALER_JEFFERSON)
		{
			VehicleInfo[newveh][VehPosX] = 2128.3428;
			VehicleInfo[newveh][VehPosY] = -1135.8184;
			VehicleInfo[newveh][VehPosZ] = 25.1607;
			VehicleInfo[newveh][VehAngle] = 355.3852;
		}
		else if(dealer == CAR_DEALER_GROTTI)
		{
			VehicleInfo[newveh][VehPosX] = 546.8687;
			VehicleInfo[newveh][VehPosY] = -1266.7017;
			VehicleInfo[newveh][VehPosZ] = 16.8674;
			VehicleInfo[newveh][VehAngle] = 302.5064;
		}

		VehicleInfo[newveh][VehFuel] = 100;
		SendFMessage(playerid, COLOR_YELLOW2, "¡Felicidades, has comprado un %s! El vehículo se encuentra en el estacionamiento de la consecionaria.", GetVehicleModelName(carModelSelection[playerid]));
		SendClientMessage(playerid, COLOR_WHITE, "Recuerda estacionarlo fuera de la consecionaria con '/vehestacionar'. De no hacerlo podrá ser incautado.");

	 	DestroyVehicle(newveh);
		newveh = CreateVehicle(VehicleInfo[newveh][VehModel], VehicleInfo[newveh][VehPosX], VehicleInfo[newveh][VehPosY], VehicleInfo[newveh][VehPosZ], VehicleInfo[newveh][VehAngle], VehicleInfo[newveh][VehColor1], VehicleInfo[newveh][VehColor2], -1);

		addKeyToPlayer(playerid, newveh, playerid);
		SaveVehicle(newveh);
	}
 	return 1;
}
