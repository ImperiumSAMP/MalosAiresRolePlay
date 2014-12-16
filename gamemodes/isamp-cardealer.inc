#if defined _isamp_cardealer_included
	#endinput
#endif
#define _isamp_cardealer_included

//=================================CONSTANTES===================================

#define MAX_DEALERS             2

#define CAR_DEALER_GROTTI       0
#define CAR_DEALER_JEFFERSON    1

#define MAX_DEALER_CARS         20

#define DLG_CARDEALER1	    	10031
#define DLG_CARDEALER2	    	10032
#define DLG_CARDEALER3	    	10033
#define DLG_CARDEALER4	    	10034

//=================================VARIABLES====================================

enum DealerModelInfo {
	dModel,
	dStock,
	dAllowImport
};

new CarDealerInfo[MAX_DEALERS][MAX_DEALER_CARS][DealerModelInfo];

new carModelSelection[MAX_PLAYERS],
	carColor1Selection[MAX_PLAYERS],
	carColor2Selection[MAX_PLAYERS];

//============================FUNCIONES PUBLICAS================================

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
        SendFMessage(playerid, COLOR_YELLOW, "CarDealerInfo[%d][%d] dAllowImport = %d", dealer, x, CarDealerInfo[dealer][x][dAllowImport]);
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
	        	format(string, sizeof(string), "%s\n%s - En stock: entrega inmediata - $%d - Slots: %d", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100), GetVehicleModelTrunkSlots(model));
			}
			else if(CarDealerInfo[dealer][i][dStock] == 0 && CarDealerInfo[dealer][i][dAllowImport])
			{
   				format(string, sizeof(string), "%s\n%s - Entrega en 5 paydays - $%d - Slots: %d", string, GetVehicleModelName(model), GetVehicleModelPrice(model, 100), GetVehicleModelTrunkSlots(model));
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
			ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el número de color primario que desea.\nColores básicos:\n0 - Negro\n1 - Blanco\n2 - Azul\n3 - Rojo\n6 - Amarillo\n16 - Verde\nPara ver una lista mas amplia de colores, visite nuestro catálogo online: http://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
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
			ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el numero de color {00FF00}primario {FFFFFF}que desea.\nColores básicos:\n0 - Negro\n1 - Blanco\n2 - Azul\n3 - Rojo\n6 - Amarillo\n16 - Verde\nPara ver una lista mas amplia de colores, visite nuestro catálogo online: http://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa un número de color válido (0-255).");
		}
		
		carColor1Selection[playerid] = color1;
		ShowPlayerDialog(playerid, DLG_CARDEALER3, DIALOG_STYLE_INPUT, "Selección de color 2", "Ingrese a continuación el número de color {00FF00}secundario {FFFFFF}que desea.\nColores básicos:\n0 - Negro\n1 - Blanco\n2 - Azul\n3 - Rojo\n6 - Amarillo\n16 - Verde\nPara ver una lista mas amplia de colores, visite nuestro catálogo online: http://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
	}
	else
	    cmd_vercatalogo(playerid, "");
 	return 1;
}

OnCarDealer3DialogResponse(playerid, response, inputtext[])
{
	if(response)
	{
		new color2 = strval(inputtext);

		if(color2 < 0 || color2 > 255)
		{
			ShowPlayerDialog(playerid, DLG_CARDEALER3, DIALOG_STYLE_INPUT, "Selección de color 2", "Ingrese a continuación el numero de color {00FF00}secundario {FFFFFF}que desea.\nColores básicos:\n0 - Negro\n1 - Blanco\n2 - Azul\n3 - Rojo\n6 - Amarillo\n16 - Verde\nPara ver una lista mas amplia de colores, visite nuestro catálogo online: http://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
			return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa un número de color válido (0-255).");
		}

		carColor2Selection[playerid] = color2;
  		new str[128];
  		format(str, sizeof(str), "Detalles del pedido:\n\tVehículo: %s\n\tColor primario: %d\n\tColor secundario: %d", GetVehicleModelName(carModelSelection[playerid]), carColor1Selection[playerid], carColor2Selection[playerid]);
		ShowPlayerDialog(playerid, DLG_CARDEALER4, DIALOG_STYLE_MSGBOX, "Confirmación de la compra", str, "Comprar", "Cancelar");
	}
	else
	    ShowPlayerDialog(playerid, DLG_CARDEALER2, DIALOG_STYLE_INPUT, "Selección de color 1", "Ingrese a continuación el numero de color {00FF00}primario {FFFFFF}que desea.\nColores básicos:\n0 - Negro\n1 - Blanco\n2 - Azul\n3 - Rojo\n6 - Amarillo\n16 - Verde\nPara ver una lista mas amplia de colores, visite nuestro catálogo online: http://wiki.sa-mp.com/wiki/Vehicle_Color_IDs", "Continuar", "Volver");
 	return 1;
}

OnCarDealer4DialogResponse(playerid, response)
{
	if(response)
	{
		new dealer = GetPlayerCarDealer(playerid);

		if(dealer == -1)
     		return SendClientMessage(playerid, COLOR_YELLOW2, "Error: debes estar en una consecionaria.");

		SendClientMessage(playerid, COLOR_YELLOW2, "COMPRARVEHÍCULO");
	}
 	return 1;
}
