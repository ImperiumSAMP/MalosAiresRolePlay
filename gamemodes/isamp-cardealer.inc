#if defined _isamp_cardealer_included
	#endinput
#endif
#define _isamp_cardealer_included

//=================================CONSTANTES===================================

#define MAX_DEALERS             2

#define CAR_DEALER_GROTTI       0
#define CAR_DEALER_JEFFERSON    1

#define MAX_DEALER_CARS         20

#define DLG_CARDEALER	    	10031

//=================================VARIABLES====================================

enum DealerModelInfo {
	dModel,
	dStock,
	dAllowImport
};

new CarDealerInfo[MAX_DEALERS][MAX_DEALER_CARS][DealerModelInfo];

//============================FUNCIONES PUBLICAS================================

CMD:agregarmodelo(playerid, params[])
{
	new dealer, model, carstock, allowimport;

	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "iiii", dealer, model, carstock, allowimport))
		return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agregarmodelo [ID consecionaria] [modelo] [stock] [permite importación 0:no - 1:si] (IDs Grotti:0 - Jefferson:1)");
	if(dealer < 0 || dealer >= MAX_DEALERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de consecionaria inválida.");
	if(model < 400 || model > 611)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de modelo inválida.");
	if(carstock < 0 || carstock > 10)
     	return SendClientMessage(playerid, COLOR_YELLOW2, "Stock inválido: solo se permite de 0 a 10. Un stock de '0' equivale a que se demore la entrega del vehículo.");
	if(allowimport != 0 && allowimport != 1)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Debe indicar 0 o 1 en el campo 'permite importación'. Si es 0, el modelo se quita del catálogo de venta cuando llega a stock 0.");
	if(allowimport == 0 && carstock == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Los valores 'stock' y 'permite importación' no pueden valer 0 simultaneamente.");

	for(new i = 0; i < MAX_DEALER_CARS; i++)
	{
	    if(CarDealerInfo[dealer][i][dModel] == model)
	    {
	        SendFMessage(playerid, COLOR_WHITE, "El modelo %d ya se encontraba a la venta en la consecionaria ID %d con un stock de %d y permiso de importación de %d.", model, dealer, CarDealerInfo[dealer][i][dStock], CarDealerInfo[dealer][i][dAllowImport]);
            SendFMessage(playerid, COLOR_WHITE, "Ahora el stock de ese modelo ha sido seteado en %d con un permiso de importación en %d.", carstock, allowimport);
            CarDealerInfo[dealer][i][dStock] = carstock;
            CarDealerInfo[dealer][i][dAllowImport] = allowimport;
            return 1;
		}
	}
	
	for(new x = 0; x < MAX_DEALER_CARS; x++)
	{
	    if(CarDealerInfo[dealer][x][dModel] == 0)
	    {
	        CarDealerInfo[dealer][x][dModel] = model;
	        CarDealerInfo[dealer][x][dStock] = carstock;
	        CarDealerInfo[dealer][x][dAllowImport] = allowimport;
	    	SendFMessage(playerid, COLOR_WHITE, "Has agregado el modelo %d con un stock de %d y permiso de importación en %d a la consecionaria ID %d.", model, carstock, allowimport, dealer);
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
	if(dealer < 0 || dealer >= MAX_DEALERS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de consecionaria inválida.");
	if(model < 400 || model > 611)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de modelo inválida.");

	for(new i = 0; i < MAX_DEALER_CARS; i++)
	{
	    if(CarDealerInfo[dealer][i][dModel] == model)
	    {
            CarDealerInfo[dealer][i][dModel] = 0;
			CarDealerInfo[dealer][i][dStock] = 0;
			CarDealerInfo[dealer][i][dAllowImport] = 0;
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
    CreateDynamic3DTextLabel("/vercatalogo para ver los vehículos en venta.", COLOR_WHITE, 542.3592, -1292.8329, 17.1696 + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    CreateDynamicPickup(1239, 1, 2131.7793, -1150.9172, 24.0211);
    CreateDynamic3DTextLabel("/vercatalogo para ver los vehículos en venta.", COLOR_WHITE, 2131.7793, -1150.9172, 24.0211 + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

GetPlayerCarDealer(playerid)
{
	if(PlayerToPoint(3.0, playerid, 542.3592, -1292.8329, 17.1696))
	    return CAR_DEALER_GROTTI;
	else if (PlayerToPoint(3.0, playerid, 2131.7793, -1150.9172, 24.0211))
	    return CAR_DEALER_JEFFERSON;
	    
	return -1;
}

CMD:vercatalogo(playerid, params[])
{
	new string[800] = "Modelo - Tiempo de entrega - Precio - Maletero",
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
	        	format(string, sizeof(string), "%s\n%s - En stock: entrega inmediata - %d - Slots: %d", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100), GetVehicleModelTrunkSlots(model));
			}
			else if(CarDealerInfo[dealer][i][dStock] == 0 && CarDealerInfo[dealer][i][dAllowImport])
			{
   				format(string, sizeof(string), "%s\n%s - Entrega en 5 paydays - %d - Slots: %d", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100), GetVehicleModelTrunkSlots(model));
			}
		}
	}
	ShowPlayerDialog(playerid, DLG_CARDEALER, DIALOG_STYLE_LIST, "Catálogo de vehículos en venta", string, "Seleccionar", "Cerrar");
	return 1;
}

