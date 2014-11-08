#if defined _isamp_business_included
	#endinput
#endif
#define _isamp_business_included

#define MAX_BUSINESS	        100

// Mensajes del sistema.
#define BUSINESS_TYPES 			"1: Restaurant - 2: Sucursal telefónica - 3: 24-7 - 4: Ammunation - 5: Publicidad - 6: Tienda de ropa urbana"
#define BUSINESS_TYPES2 		"7: Bar/Club - 8: Tienda de ropa fina - 9: Casino - 10: Ferreteria - 11: Discoteca - 12: Pizzeria - 13: McDonals"
#define BUSINESS_TYPES3         "14: Burger King - 15: Comidas Rápidas - 16: Accesorios"

#define DLG_BIZ_HARD            10026
#define DLG_BIZ_ACCESS          10027

// Negocios.
#define BIZ_REST          		1
#define BIZ_PHON                2
#define BIZ_247                	3
#define BIZ_AMMU                4
#define BIZ_ADVE                5
#define BIZ_CLOT                6
#define BIZ_CLUB                7
#define BIZ_CLOT2               8
#define BIZ_CASINO              9
#define BIZ_HARD                10
#define BIZ_CLUB2               11
#define BIZ_PIZZERIA            12
#define BIZ_BURGER1             13
#define BIZ_BURGER2             14
#define BIZ_BELL                15
#define BIZ_ACCESS              16

enum RES_PRICELIST {
		bplItemName[64],
		bplPrice,
		Float:bplEatAmount,
		Float:bplDrinkAmount
};

static const RestMenu[][RES_PRICELIST] = {
	//Restaurant
	{"Milanesa con papas", 80, 70.0, 0.0},
	{"Pollo al horno con verduras", 90, 70.0, 0.0},
	{"Ravioles de espinaca con salsa parisiene", 90, 70.0, 0.0},
	{"Ensalada Cáesar", 70, 60.0, 0.0},
	{"Bife de cerdo a la plancha", 90, 70.0, 0.0},
	{"Pastel de papa casero", 75, 70.0, 0.0},
	{"Asado completo con bebida", 120, 100.0, 70.0}
};

static const PizzaMenu[][RES_PRICELIST] = {
	 //Pizza
	{"Pizza de Muzzarella", 65, 65.0, 0.0},
	{"Pizza de Fugazzeta", 70, 70.0, 0.0},
	{"Pizza de Calabresa", 80, 80.0, 0.0},
	{"Pizza Especial con bebida", 100, 70.0, 50.0},
	{"Pizza Estilo Primavera", 90, 85.0, 0.0},
	{"Pizza De Jamón, Roquefort y Morrones con bebida", 105, 85.0, 60.0},
	{"Pizza de 4 Quesos Artesanal con bebida", 115, 95.0, 65.0}
};

static const McMenu[][RES_PRICELIST] = {
	 //McDonals
	{"Angus Beacon con gaseosa grande y papas grandes", 110, 75.0, 40.0},
	{"Doble Cuarto de libra con papas medianas y gaseosa mediana", 95, 60.0, 30.0},
	{"Triple Mac", 60, 50.0, 0.0},
	{"Big Mac con gaseosa mediana", 70, 50.0, 35.0},
	{"McNifica", 50, 40.0, 0.0},
	{"MacFiesta con huevo y gaseosa grande", 55, 45.0, 30.0},
	{"Jugo de naranja McDonals", 25, 0.0, 45.0}
};

static const BurgerMenu[][RES_PRICELIST] = {
	 //Burger King
	{"Whopper con queso y papas medianas", 70, 60.0, 0.0},
	{"SteakHouse Burger XT con papas Noisette", 80, 70.0, 0.0},
	{"Hamburguesa con queso", 35, 30.0, 0.0},
	{"BK Stacker Cuádruple con vaso grande y papas medianas", 105, 80.0, 45.0},
	{"King de pollo Francés con papas pequeñas", 70, 60.0, 0.0},
	{"Tendergrill Max con vaso mediano y papas grandes", 90, 60.0, 35.0},
	{"Churrasquito Pampeano con vaso grande", 100, 70.0, 40.0}
};

static const BellMenu[][RES_PRICELIST] = {
	 //Chuckin Bell
	{"Pechuga de pollo", 65, 65.0, 0.0},
	{"Albóndigas", 50, 40.0, 0.0},
	{"Café con tostado de jamón y queso", 55, 40.0, 40.0},
	{"Churrasco con papas fritas y bebida", 80, 55.0, 40.0},
	{"Sandwich de Lomo Grille con bebida", 70, 50.0, 40.0},
	{"Rabas a la provenzal con bebida", 85, 65.0, 40.0},
	{"Ensalada del bosque con Villa del Sur", 50, 35.0, 65.0}
};

static const HardItems[] = {
	1, // Nudillos
	6, // Pala
	15, // Baston
	2, // Palo de golf
	5, // Bate
	7, // Palo de pool
	11, // Consolador
	10, // Consolador Doble punta
	12, // Vibrador
	13, // Vibrador Plateado
	ITEM_ID_CASCOCOMUN, ITEM_ID_CASCOMOTOCROSS, ITEM_ID_CASCOROJO, ITEM_ID_CASCOBLANCO,
	ITEM_ID_CASCOROSA, ITEM_ID_CASCO_OBRERO
};

static const AccessItems[] = {
	ITEM_ID_SOMBRERO_COWBOY_NEGRO, ITEM_ID_SOMBRERO_COWBOY_MARRON, ITEM_ID_SOMBRERO_COWBOY_BORDO,
	ITEM_ID_RELOJ_SWATCH, ITEM_ID_RELOJ_ROLEX, ITEM_ID_RELOJ_CASIO, ITEM_ID_RELOJ_SWISSARMY,
	ITEM_ID_RELOJ_FESTINA, ITEM_ID_SOMBRERO_ANTIGUO, ITEM_ID_BIGOTE_FALSO1, ITEM_ID_BIGOTE_FALSO2,
	ITEM_ID_SOMBRERO_BLANCO, ITEM_ID_GORRO_ROJO, ITEM_ID_GORRO_ESTAMPADO, ITEM_ID_GORRO_NEGRO,
	ITEM_ID_GORRO_PLAYERO_NEGRO, ITEM_ID_GORRO_PLAYERO_CUADROS, ITEM_ID_GORRA_MILITAR,
	ITEM_ID_GORRA_GRIS_ESTAMPADA, ITEM_ID_GORRA_BLANCA_ESTAMPADA, ITEM_ID_ANTEOJO_DE_SOL,
	ITEM_ID_ANTEOJO_DEPORTIVO_NEGRO, ITEM_ID_ANTEOJO_DEPORTIVO_ROJO, ITEM_ID_ANTEOJO_DEPORTIVO_AZUL,
	ITEM_ID_ANTEOJO_RAYBAN_NEGRO, ITEM_ID_ANTEOJO_RAYBAN_VERDE, ITEM_ID_ANTEOJO_RAYBAN_AZUL,
	ITEM_ID_GORRA_SIMPLE_NEGRA, ITEM_ID_GORRA_SIMPLE_AZUL, ITEM_ID_GORRA_SIMPLE_VERDE
};

static const AmmuItems[] = {
	22, // 9mm
	24, // Deagle
	25, // Escopeta
	33 //Rifle de caza
};

//Enums
enum BusinessSystem {
	bID,
	bName[128],
	bOwner[MAX_PLAYER_NAME],
	bOwnerSQLID,
	Float:bOutsideX,
	Float:bOutsideY,
	Float:bOutsideZ,
	Float:bOutsideAngle,
	Float:bInsideX,
	Float:bInsideY,
	Float:bInsideZ,
	Float:bInsideAngle,
	bOutsideInt,
	bInsideInt,
	bEnterable,
	bPrice,
	bEntranceFee,
	bTill,
	bLocked,
	bType,
	bProducts,
	// Datos temporales.
	bool:bLoaded,
	bool:bInsert,
	bool:bDelete,
	bInsideWorld,
	bOutsidePickup,
	bInsidePickup,
	Text3D:bOutsideLabel,
	Text3D:bInsideLabel,
	bRadio
}
new Business[MAX_BUSINESS][BusinessSystem];
new bool:openBizPermission[MAX_BUSINESS];

	//Venta de negocios
new	bool:OfferingBusiness[MAX_PLAYERS],
	BusinessOfferPrice[MAX_PLAYERS],
	BusinessOffer[MAX_PLAYERS];

//==================================FUNCIONES===================================

forward GetPlayerBusiness(playerid);
forward ResetBusinessOffer(playerid);
forward bool:EnterBusiness(playerid);
forward bool:LeaveBusiness(playerid);

forward OnPlayerBuyHard(playerid, biz);
forward OnPlayerBuyHardDialog(playerid, listitem);
forward OnPlayerBuyClot(biz, playerid);
forward OnPlayerBuyAmmu(biz, playerid, params[]);
forward OnPlayerBuyAccess(playerid, biz);
forward OnPlayerBuyAccessDialog(playerid, listitem);

//==========================IMPLEMENTACION DE FUNCIONES=========================

stock ResetBusinessOffer(playerid)
{
	OfferingBusiness[playerid] = false;
	BusinessOfferPrice[playerid] = -1;
	BusinessOffer[playerid] = INVALID_PLAYER_ID;
}

stock GetPlayerBusiness(playerid)
{
	for(new i = 1; i < MAX_BUSINESS; i++)
	{
	    if(Business[i][bInsideInt] == GetPlayerInterior(playerid) && Business[i][bInsideWorld] == GetPlayerVirtualWorld(playerid) && Business[i][bInsideWorld] != 0)
			return i;
	}
	return 0;
}

stock bool:EnterBusiness(playerid)
{
	for(new i = 1; i < MAX_BUSINESS; i++)
	{
		if(PlayerToPoint(1.0, playerid,Business[i][bOutsideX], Business[i][bOutsideY], Business[i][bOutsideZ]))
		{
			if(Business[i][bEnterable] == 0)
			{
				SendClientMessage(playerid, COLOR_YELLOW2,"Negocio temporalmente deshabilitado.");
				return true;
			}
			if(PlayerInfo[playerid][pBizKey] == i)
			{
	           	SetPlayerInterior(playerid, Business[i][bInsideInt]);
				SetPlayerPos(playerid, Business[i][bInsideX] + 2 * floatcos(Business[i][bInsideAngle] + 90, degrees), Business[i][bInsideY] + 2 * floatsin(Business[i][bInsideAngle] + 90, degrees), Business[i][bInsideZ]);
				SetPlayerVirtualWorld(playerid, Business[i][bInsideWorld]);
	            SetPlayerFacingAngle(playerid, Business[i][bInsideAngle]);
	            SetCameraBehindPlayer(playerid);
	            PlayRadioStreamForPlayer(playerid, Business[i][bRadio]);
    		} else
		    	{
			    	if(Business[i][bLocked] == 1 && AdminDuty[playerid] != 1) {
						GameTextForPlayer(playerid, "~r~negocio cerrado.", 2000, 4);
						return true;
					}
					if(GetPlayerCash(playerid) < Business[i][bEntranceFee]) {
						SendClientMessage(playerid,COLOR_YELLOW2,"¡No tienes el dinero suficiente!");
						return true;
					}
					SetPlayerInterior(playerid, Business[i][bInsideInt]);
					SetPlayerPos(playerid, Business[i][bInsideX] + 2 * floatcos(Business[i][bInsideAngle] + 90, degrees), Business[i][bInsideY] + 2 * floatsin(Business[i][bInsideAngle] + 90, degrees), Business[i][bInsideZ]);
					SetPlayerVirtualWorld(playerid, Business[i][bInsideWorld]);
					SetPlayerFacingAngle(playerid, Business[i][bInsideAngle]);
					SetCameraBehindPlayer(playerid);
					PlayRadioStreamForPlayer(playerid, Business[i][bRadio]);
					GivePlayerCash(playerid, -Business[i][bEntranceFee]);
					if(Business[i][bEntranceFee] > 0)
                        SendFMessage(playerid, COLOR_YELLOW2, "¡Te han cobrado $%d para ingresar al negocio %s!", Business[i][bEntranceFee], Business[i][bName]);
					switch(Business[i][bType])
					{
					    case BIZ_247, BIZ_CLOT, BIZ_CLOT2, BIZ_AMMU, BIZ_HARD, BIZ_ACCESS:
			    			SendClientMessage(playerid, COLOR_YELLOW2, "Utiliza /comprar para comprar en este negocio.");
					    case BIZ_CLUB, BIZ_CLUB2:
					    	SendClientMessage(playerid, COLOR_YELLOW2, "Utiliza /beber para comprar una bebida.");
						case BIZ_REST, BIZ_PIZZERIA, BIZ_BURGER1, BIZ_BURGER2, BIZ_BELL:
  							SendClientMessage(playerid, COLOR_YELLOW2, "Utiliza /comer para comprar comida.");
						case BIZ_CASINO:
 	    					SendClientMessage(playerid, COLOR_YELLOW2, "Utiliza /beber para comprar una bebida o /apostar para jugar en el casino.");
					}
					if(Business[i][bProducts] == 0)
						GameTextForPlayer(playerid, "~r~sin productos.", 2000, 4);
					Business[i][bTill] += Business[i][bEntranceFee];
					saveBusiness(i);
				}
			return true;
		}
	}
	return false;
}

stock bool:LeaveBusiness(playerid)
{
	for(new i = 0; i < MAX_BUSINESS; i++)
	{
		if(PlayerToPoint(1.0, playerid, Business[i][bInsideX], Business[i][bInsideY], Business[i][bInsideZ]))
		{
		    if(GetPlayerVirtualWorld(playerid) == Business[i][bInsideWorld])
			{
		        if(Business[i][bType] == BIZ_CLOT || Business[i][bType] == BIZ_CLOT2)
				{
					DestroySelectionMenu(playerid);
					CancelSelectTextDraw(playerid);
				}
				if(Business[i][bLocked] == 0 || AdminDuty[playerid] >= 1)
				{
					SetPlayerInterior(playerid, Business[i][bOutsideInt]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerPos(playerid,Business[i][bOutsideX],Business[i][bOutsideY],Business[i][bOutsideZ]);
		            SetPlayerFacingAngle(playerid, Business[i][bOutsideAngle]);
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

//=============================COMANDOS DE NEGOCIO==============================

CMD:ayudanegocio(playerid, params[])
{
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[NEGOCIO]: /negociocomprar - /negociovender - /negocioinfo - /negocioentrada - /negocionombre - /negociollave");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"/negociodepositar - /negocioretirar - /negocioradio - /negociovendera - /ayudaproductos");
	return 1;
}

CMD:ayudaproductos(playerid, params[])
{
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"Para comprar productos dirígete a la zona de transportistas, y estaciona en la puerta del depósito.");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"Una vez allí, escribe /comprar, y cuando llegues con la mercaderia a la entrada de tu negocio usa /descargar.");
	return 1;
}

CMD:negociollave(playerid, params[])
{
	new bizID = PlayerInfo[playerid][pBizKey];
	
	if(bizID == 0 && Business[bizID][bOwnerSQLID] == PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No eres propietario de ningún negocio!");
	if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");

	if(Business[bizID][bLocked] == 1)
	{
		if(openBizPermission[bizID] == false)
			return SendClientMessage(playerid, COLOR_YELLOW2,"¡Debes esperar hasta el próximo dia de pago!");
			
		Business[bizID][bLocked] = 0;
		PlayerActionMessage(playerid, 15.0, "toma unas llaves de su bolsillo y abre las puertas del negocio.");
	} else
		{
			Business[bizID][bLocked] = 1;
			PlayerActionMessage(playerid, 15.0, "toma unas llaves de su bolsillo y cierra las puertas del negocio.");
			SendClientMessage(playerid, COLOR_YELLOW2,"Una vez cerrado, no podrás abrirlo hasta el próximo payday y perderas los ingresos de ese día.");
			openBizPermission[bizID] = false;
		}
	saveBusiness(bizID);
    return 1;
}

CMD:negocioretirar(playerid,params[])
{
	new
	    ammount,
		bizID = PlayerInfo[playerid][pBizKey];

	if(sscanf(params, "i", ammount))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negocioretirar [Cantidad]");
	if(bizID == 0 && Business[bizID][bOwnerSQLID] == PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No eres propietario de ningún negocio!");
	if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Te encuentras demasiado lejos de la caja!");
  	if(ammount > 1000000 || ammount < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar más de $1.000.000 o menos de $1.");
 	if(ammount > Business[bizID][bTill])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes esa cantidad de dinero en la caja!");

	GivePlayerCash(playerid, ammount);
	Business[bizID][bTill] -= ammount;
	SendFMessage(playerid, COLOR_WHITE, "Has retirado $%d de la caja registradora, nuevo total: $%d.", ammount, Business[bizID][bTill]);
	PlayerActionMessage(playerid, 15.0, "abre la caja registradora y retira algo de dinero dentro.");
	saveBusiness(bizID);
	return 1;
}

CMD:negociodepositar(playerid, params[])
{
	new
	    ammount,
		bizID = PlayerInfo[playerid][pBizKey];

	if(sscanf(params, "i", ammount))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negociodepositar [Cantidad]");
	if(bizID == 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No eres propietario de ningún negocio!");
 	if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld])
  		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Te encuentras demasiado lejos de la caja!");
	if(GetPlayerCash(playerid) < ammount)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes esa cantidad de dinero!");
	if(ammount > 1000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes depositar más de $1.000.000.");
 	if(Business[bizID][bTill] >= 1000000)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "La caja se encuentra actualmente llena. (MAX: $1.000.000)");

	GivePlayerCash(playerid, -ammount);
	Business[bizID][bTill] += ammount;
	SendFMessage(playerid, COLOR_WHITE, "Has depositado $%d en la caja registradora, nuevo total: $%d.", ammount, Business[bizID][bTill]);
	PlayerActionMessage(playerid, 15.0, "abre la caja registradora y guarda algo de dinero dentro.");
	saveBusiness(bizID);
	return 1;
}

CMD:negocioentrada(playerid,params[])
{
	new
	    string[128],
	    bizID = PlayerInfo[playerid][pBizKey],
	    price;
	
	if(sscanf(params, "i", price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negocioentrada [Precio]");
	if(bizID == 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un negocio!");
	if(!PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) && !PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");
	if(price < 0 || price > 10000)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡El costo de la entrada no debe ser menor a $0 ni mayor a $10000!");

	Business[bizID][bEntranceFee] = price;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el costo de entrada a tu negocio ahora es de $%d.", Business[bizID][bEntranceFee]);
	SendClientMessage(playerid, COLOR_WHITE, string);
	saveBusiness(bizID);
	return 1;
}

CMD:negocionombre(playerid,params[])
{
	new
	    string[128],
	    bizID = PlayerInfo[playerid][pBizKey],
	    bizName[64];
	
	if(sscanf(params, "s[64]", bizName))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negocionombre [Nombre] (64 caracteres)");
	if(bizID == 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un negocio!");
	if(!PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) && !PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");

	mysql_real_escape_string(bizName, bizName);
	strmid(Business[bizID][bName], bizName, 0, strlen(bizName), 255);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el nombre de tu negocio ahora es  '%s'.",Business[bizID][bName]);
	SendClientMessage(playerid, COLOR_WHITE, string);
	saveBusiness(bizID);
	return 1;
}

CMD:negocioinfo(playerid,params[])
{
	new bizID = PlayerInfo[playerid][pBizKey];
	
	if(bizID == 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún negocio!");
	if(!PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) && !PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");
	    
 	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "====[Información sobre el negocio]====");
    SendFMessage(playerid, COLOR_WHITE, "Nombre: 	%s", Business[bizID][bName]);
    SendFMessage(playerid, COLOR_WHITE, "Caja:		$%d", Business[bizID][bTill]);
    SendFMessage(playerid, COLOR_WHITE, "Cerrado: 	%d", Business[bizID][bLocked]);
    SendFMessage(playerid, COLOR_WHITE, "Productos: 	%d", Business[bizID][bProducts]);
    SendFMessage(playerid, COLOR_WHITE, "Entrada: 	$%d", Business[bizID][bEntranceFee]);
    SendFMessage(playerid, COLOR_WHITE, "Radio:  %d", Business[bizID][bRadio]);
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "=====================================");
	return 1;
}

CMD:negociocomprar(playerid,params[])
{
	new
	    string[128],
		name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	if(PlayerInfo[playerid][pBizKey] != 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tener más de un negocio!");

	for(new bizID = 0; bizID < MAX_BUSINESS; bizID++)
	{
		if(PlayerToPoint(2.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) && Business[bizID][bOwnerSQLID] == -1)
		{
		    if(Business[bizID][bPrice] == 0)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio se encuentra deshabilitado.");
			if(GetPlayerCash(playerid) < Business[bizID][bPrice])
				return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
				
			PlayerInfo[playerid][pBizKey] = bizID;
			Business[bizID][bOwnerSQLID] = PlayerInfo[playerid][pID];
			strmid(Business[bizID][bOwner], name, 0, strlen(name), 255);
			GivePlayerCash(playerid, -Business[bizID][bPrice]);
   			PlayerActionMessage(playerid, 15.0, "le entrega una gran suma de dinero al vendedor y recibe las llaves del negocio.");
   			SendClientMessage(playerid, COLOR_YELLOW2, "¡Felicitaciones, has comprado este negocio! Para ver los comandos disponibles utiliza /ayudanegocio.");
			saveBusiness(bizID);
			format(string, sizeof(string), "[ALERTA DE USUARIO]: %s (DBID: %d) > compra de negocio ID: %d.", name, PlayerInfo[playerid][pID], bizID);
			AdministratorMessage(COLOR_ADMINCMD, string, 2);
			return 1;
		}
	}
	return 1;
}

CMD:negocioradio(playerid,params[])
{
	new
	    radio,
	    bizID = PlayerInfo[playerid][pBizKey];

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negocioradio [ID radio]");
	if(bizID == 0 || Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un negocio!");
	if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld])
 		return SendClientMessage(playerid, COLOR_YELLOW2, "No te encuentras en tu negocio.");
	if(radio < 0 || radio > 15)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio válida: del 1 al 15. Usa 0 para dejarlo sin radio.");

	Business[bizID][bRadio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: Has seteado la radio del negocio a %d.", Business[bizID][bRadio]);
	PlayRadioStreamForPlayer(playerid, Business[bizID][bRadio]);
	return 1;
}

CMD:negociovender(playerid,params[])
{
	new
	    bizID = PlayerInfo[playerid][pBizKey],
		name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));
	
	if(bizID == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún negocio para vender!");
	if(!PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en la entrada de tu negocio para venderlo!");
	if(strcmp(Business[bizID][bOwner], name, true) != 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Error, el negocio no está a tu nombre (Consulta a un administrador).");

	Business[bizID][bLocked] = 0;
	Business[bizID][bOwnerSQLID] = -1;
	strmid(Business[bizID][bOwner], "Ninguno", 0, strlen("Ninguno"), 255);
	GivePlayerCash(playerid, Business[bizID][bPrice] / 10 * 7); // 70 % del valor original.
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Has vendido tu negocio por $%d!", Business[bizID][bPrice] / 10 * 7);
	PlayerInfo[playerid][pBizKey] = 0;
	PlayerActionMessage(playerid, 15.0, "rompe el contrato, y le da las llaves del negocio al agente inmobiliario.");
	saveBusiness(bizID);
	return 1;
}

CMD:negociovendera(playerid, params[])
{
	new
		bizID = PlayerInfo[playerid][pBizKey],
		targetid,
		price,
		name[MAX_PLAYER_NAME];

	if(sscanf(params, "ui", targetid, price))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negociovendera [ID/Jugador] [Precio]");
	if(bizID == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener un negocio para utilizar este comando!");
	if(!PlayerToPoint(2.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la puerta de tu negocio.");
   	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
  	if(price < 1 || price > 30000000)
   		return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $30,000,000.");
  	if(OfferingBusiness[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras vendiendo un negocio.");
	if(!ProxDetectorS(4.0, playerid, targetid))
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
	GetPlayerName(playerid, name, sizeof(name));
    if(strcmp(Business[bizID][bOwner], name, true) != 0 || Business[bizID][bOwnerSQLID] != PlayerInfo[playerid][pID])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Error, el negocio no está a tu nombre (Consulta a un administrador).");

	OfferingBusiness[playerid] = true;
	BusinessOfferPrice[targetid] = price;
	BusinessOffer[targetid] = playerid;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le ofreces las llaves y escritura de tu negocio a %s por $%d.",GetPlayerNameEx(targetid), price);
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te esta ofreciendo venderte su negocio por $%d.", GetPlayerNameEx(playerid), price);
	SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/negocioaceptar' para aceptar la oferta o '/negociocancelar' para cancelar.");
	SetPVarInt(targetid, "CancelBusinessTransfer", SetTimerEx("CancelBusinessTransfer", 15 * 1000, false, "ii", targetid, 1));
	return 1;
}

CMD:negocioaceptar(playerid, params[])
{
	new
		sellerid = BusinessOffer[playerid],
	   	price = BusinessOfferPrice[playerid],
	   	businessid,
	   	name[MAX_PLAYER_NAME];
	    	
  	if(sellerid == INVALID_PLAYER_ID)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo un negocio.");
	if(!IsPlayerConnected(sellerid) || !OfferingBusiness[sellerid])
	{
	    KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	    CancelBusinessTransfer(playerid, 2);
		return SendClientMessage(playerid, COLOR_YELLOW2, "Hubo un error durante la venta, cancelando...");
	}
	if(!ProxDetectorS(4.0, playerid, sellerid))
 	   	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no está cerca tuyo.");
	if(GetPlayerCash(playerid) < price)
	{
	    KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	    SendClientMessage(sellerid, COLOR_YELLOW2, "El jugador no tiene el dinero necesario, cancelando...");
	    CancelBusinessTransfer(playerid, 2);
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, cancelando...");
	}
	if(PlayerInfo[playerid][pBizKey] != 0)
	{
	    KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	    SendClientMessage(sellerid, COLOR_YELLOW2, "El jugador ya tiene un negocio, cancelando...");
	    CancelBusinessTransfer(playerid, 2);
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un negocio, cancelando...");
	}

   	businessid = PlayerInfo[sellerid][pBizKey];
	GetPlayerName(playerid, name, sizeof(name));
	Business[businessid][bLocked] = 0;
	strmid(Business[businessid][bOwner], name, 0, strlen(name), 255);
	Business[businessid][bOwnerSQLID] = PlayerInfo[playerid][pID];
	GivePlayerCash(playerid, -price);
    GivePlayerCash(sellerid, price);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(sellerid, 1052, 0.0, 0.0, 0.0);
    PlayerInfo[playerid][pBizKey] = businessid;
    PlayerInfo[sellerid][pBizKey] = 0;
    PlayerPlayerActionMessage(sellerid, playerid, 15.0 , "toma las llaves y la escritura de su negocio y se las entrega a");
  	SendFMessage(playerid, COLOR_LIGHTBLUE, "¡Felicidades, has comprado el negocio por $%d! Usa /ayudanegocio para ver los comandos disponibles.", price);
  	SendFMessage(sellerid, COLOR_LIGHTBLUE, "¡Felicitaciones, has vendido tu negocio por $%d!", price);
  	KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	CancelBusinessTransfer(playerid, 2);
	return 1;
}

CMD:negociocancelar(playerid, params[])
{
	new sellerid = BusinessOffer[playerid];

	if(sellerid == INVALID_PLAYER_ID)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te está vendiendo un negocio.");

	KillTimer(GetPVarInt(playerid, "CancelBusinessTransfer"));
	CancelBusinessTransfer(playerid,0);
	return 1;
}

TIMER:CancelBusinessTransfer(playerid, reason)
{
	if(reason == 1)
	{
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que no has respondido en 15 segundos.");
		SendClientMessage(BusinessOffer[playerid], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 30 segundos.");
	} else
		if(reason == 0)
		{
	    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la oferta.");
			SendFMessage(BusinessOffer[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la oferta.", GetPlayerNameEx(playerid));
		}

	ResetBusinessOffer(BusinessOffer[playerid]);
	ResetBusinessOffer(playerid);
	return 1;
}

//========================COMANDOS ADMIN DE NEGOCIOS============================

CMD:anegocios(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Negocios:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/aninfo /aninsert /anremove /angetid /anproductos /anprecio /antipo");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/anentrada /ansalida /annombre /anhabilitado /anvender /antele /anvworld /ancaja");
	return 1;
}


CMD:aninfo(playerid, params[])
{
	new id;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aninfo [IDnegocio]");
	if(id < 1 || id >= MAX_BUSINESS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de negocio inválida.");

	SendFMessage(playerid, COLOR_WHITE, "=======================[Negocio %d '%s']=======================", id, Business[id][bName]);
	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s [pid %d]", Business[id][bOwner], Business[id][bOwnerSQLID]);
	SendFMessage(playerid, COLOR_WHITE, "- Habilitado: %d", Business[id][bEnterable]);
	SendFMessage(playerid, COLOR_WHITE, "- Costo de compra: $%d", Business[id][bPrice]);
	SendFMessage(playerid, COLOR_WHITE, "- Costo de entrada: $%d", Business[id][bEntranceFee]);
	SendFMessage(playerid, COLOR_WHITE, "- Caja: $%d", Business[id][bTill]);
	SendFMessage(playerid, COLOR_WHITE, "- Productos: %d", Business[id][bProducts]);
	SendFMessage(playerid, COLOR_WHITE, "- Cerrado: %d", Business[id][bLocked]);
	SendFMessage(playerid, COLOR_WHITE, "- Tipo: %d", Business[id][bType]);
	return 1;
}

CMD:anremove(playerid, params[]) {
	new
	    id;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "d", id)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anremove [idnegocio]");
	else if(id >= 1 && id < MAX_BUSINESS) {
		Business[id][bDelete] = true;
		saveBusiness(id);
	}
	return 1;
}

CMD:aninsert(playerid, params[]) {
	new
	    id,
	    name[32],
	    interior,
     	Float:entAngle,
	    locked,
	    enterable,
	    fee,
	    price;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "ddddds[32]", fee, price, interior, locked, enterable, name))
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aninsert [costo entrada] [costo neg] [int] [locked] [tiene interior 1-0] [nombre (32ch)]");
	else if(locked != 1 && locked != 0 || enterable != 1 && enterable != 0) {
	    SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} el valor 'locked' o 'enterable' no puede ser diferente a 1 o 0.");
	} else {
		for(new i = 1; i < MAX_BUSINESS; i++) {
		    if(!Business[i][bLoaded]) {
		        Business[i][bLoaded] = true;
				id = i;
				break;
			}
		}

	    GetPlayerPos(playerid, Business[id][bOutsideX], Business[id][bOutsideY], Business[id][bOutsideZ]);
	    GetPlayerFacingAngle(playerid, entAngle);
		Business[id][bEnterable] = enterable;
		Business[id][bPrice] = price;
	    Business[id][bOutsideInt] = GetPlayerInterior(playerid);
	    Business[id][bInsideInt] = interior;
		Business[id][bOutsideAngle] = entAngle + 180;
		Business[id][bEntranceFee] = fee;
		Business[id][bLocked] = locked;
		Business[id][bInsert] = true;
		mysql_real_escape_string(name, name);
	 	strmid(Business[id][bName], (name), 0, strlen((name)), 32);
	 	saveBusiness(id);
	}
	return 1;
}

CMD:angetid(playerid, params[]) {
    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	for(new i = 0; i < MAX_BUSINESS; i++)	{
		if(PlayerToPoint(1.0, playerid, Business[i][bOutsideX], Business[i][bOutsideY], Business[i][bOutsideZ])) {
		    SendFMessage(playerid, COLOR_WHITE, "ID del negocio: %d", i);
		    return 1;
		}
	}
	SendClientMessage(playerid, COLOR_WHITE, "No se ha encontrado ningún negocio en tu posición.");
	return 1;
}

CMD:ancaja(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    money;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "ii", bizID, money))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ancaja [idnegocio] [dinero]");
	if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bTill] = money;
		format(string, sizeof(string), "Has seteado la caja del negocio [%d] en %d.", bizID, money);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:antele(playerid, params[])
{
	new bizID;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", bizID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /antele [IDnegocio]");
	if(bizID < 1 || bizID >= MAX_BUSINESS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de negocio inválida.");

	SetPlayerPos(playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]);
	SetPlayerInterior(playerid, Business[bizID][bOutsideInt]);
	return 1;
}

CMD:anhabilitado(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    enterable;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", bizID, enterable)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anhabilitado [idnegocio] [1=SI, 0=NO]");
	else if(enterable < 0 || enterable > 1) {
	    SendClientMessage(playerid, COLOR_ADMINCMD, "El valor no puede ser menor a 0 o mayor a 1.");
	    return 1;
	} else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bEnterable] = enterable;
		switch(enterable) {
		    case 0: format(string, sizeof(string), "Has deshabilitado el negocio [%d]", bizID);
		    case 1: format(string, sizeof(string), "Has habilitado el negocio [%d]", bizID);
		}
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:anproductos(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    products;

    if(PlayerInfo[playerid][pAdmin] < 4)
		return 1;
	if(sscanf(params, "dd", bizID, products)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anproductos [idnegocio] [cantidad]");
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bProducts] = products;
		format(string, sizeof(string), "Has seteado los productos del negocio [%d] a %d.", bizID, products);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:anprecio(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    price;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", bizID, price)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anprecio [idnegocio] [precio]");
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bPrice] = price;
		format(string, sizeof(string), "Has seteado el precio del negocio [%d] a %d.", bizID, price);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:antipo(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    type;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", bizID, type)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Tipos de negocio:");
	    SendClientMessage(playerid, COLOR_ADMINCMD, BUSINESS_TYPES);
		SendClientMessage(playerid, COLOR_ADMINCMD, BUSINESS_TYPES2);
		SendClientMessage(playerid, COLOR_ADMINCMD, BUSINESS_TYPES3);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /antipo [idnegocio] [tipo]");
	}
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bType] = type;
		format(string, sizeof(string), "Has seteado el tipo del negocio [%d] a %d.", bizID, type);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:anvworld(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    vworld;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", bizID, vworld)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anvworld [idnegocio] [mundo virtual]");
	}
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bInsideWorld] = vworld;
		format(string, sizeof(string), "Has seteado el mundo virtual del negocio [%d] a %d.", bizID, vworld);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:anentrada(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    entranceInterior,
		Float:entranceX,
		Float:entranceY,
		Float:entranceZ,
		Float:entranceAngle;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "d", bizID)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anentrada [idnegocio] - setea la entrada a tu posición, tu ángulo será el adoptado al salir.");
	}
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
	    GetPlayerPos(playerid, entranceX, entranceY, entranceZ);
	    GetPlayerFacingAngle(playerid, entranceAngle);
	    entranceInterior = GetPlayerInterior(playerid);
		Business[bizID][bOutsideX] = entranceX;
		Business[bizID][bOutsideY] = entranceY;
		Business[bizID][bOutsideZ] = entranceZ;
		Business[bizID][bOutsideAngle] = entranceAngle;
		Business[bizID][bOutsideInt] = entranceInterior;
		format(string, sizeof(string), "Entrada del negocio [%d] seteada a X:%f Y:%f Z:%f A:%f Interior:%d", bizID, entranceX, entranceY, entranceZ, entranceAngle, entranceInterior);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
		ReloadBizIcon(bizID);
	}
	return 1;
}

CMD:ansalida(playerid, params[]) {
	new
	    string[128],
	    bizID,
	    exitInterior,
		Float:exitX,
		Float:exitY,
		Float:exitZ,
		Float:exitAngle;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "d", bizID)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ansalida [idnegocio] - setea la salida del negocio a tu posición, tu ángulo será el adoptado al ingresar.");
	}
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		GetPlayerPos(playerid, exitX, exitY, exitZ);
	    GetPlayerFacingAngle(playerid, exitAngle);
	    exitInterior = GetPlayerInterior(playerid);
		Business[bizID][bInsideX] = exitX;
		Business[bizID][bInsideY] = exitY;
		Business[bizID][bInsideZ] = exitZ;
		Business[bizID][bInsideAngle] = exitAngle + 180;
		Business[bizID][bInsideInt] = exitInterior;
		Business[bizID][bInsideWorld] = bizID;
		format(string, sizeof(string), "Salida del negocio [%d] seteada a X:%f Y:%f Z:%f A:%f Interior:%d", bizID, exitX, exitY, exitZ, exitAngle, exitInterior);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:annombre(playerid, params[]) {
	new
	    string[128],
	    bizID,
		name[32];

    if(PlayerInfo[playerid][pAdmin] < 4)
		return 1;

	if(sscanf(params, "ds[32]", bizID, name)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /annombre [idnegocio] [nombre 32 chars]");
	else if(bizID >= 0 && bizID < MAX_BUSINESS && strlen(name) <= 32) {
	 	mysql_real_escape_string(name, name);
	 	strmid(Business[bizID][bName], (name), 0, strlen((name)), 32);
		format(string, sizeof(string), "Has seteado el nombre del negocio [%d] a '%s'.", bizID, name);
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		saveBusiness(bizID);
	}
	return 1;
}

CMD:anvender(playerid, params[])
{
	new
	    pconnected = 0,
	    string[128],
	    bizID;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "i", bizID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anvender [ID negocio]");
	if(bizID < 1 || bizID >= MAX_BUSINESS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de negocio inválida.");

	if(Business[bizID][bOwnerSQLID] != -1)
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pBizKey] == bizID)
			{
                PlayerInfo[i][pBizKey] = 0;
                pconnected = 1;
			}
		}
  		if(pconnected == 0)
		{
			format(string, sizeof(string), "UPDATE `accounts` SET `BizKey` = '0' WHERE `BizKey` = %d", bizID);
			mysql_function_query(dbHandle, string, false, "", "");
		}
	}
	Business[bizID][bLocked] = 0;
	Business[bizID][bOwnerSQLID] = -1;
	strmid(Business[bizID][bOwner], "Ninguno", 0, strlen("Ninguno"), 255);
	saveBusiness(bizID);
	format(string, sizeof(string), "[ALERTA DE ADMIN]: %s (DBID: %d) > venta de negocio ID: %d.", PlayerName(playerid), PlayerInfo[playerid][pID], bizID);
	AdministratorMessage(COLOR_ADMINCMD, string, 2);
	return 1;
}

//=======================NEGOCIOS TIPO RESTAURANT===============================

stock bizSellProduct(businessid,playerid,price,productCount=1){
	if(GetPlayerCash(playerid)<price)
		return 0;
	
	GivePlayerCash(playerid, 0-price);
	Business[businessid][bTill] += price;
	Business[businessid][bProducts]-=productCount;
	saveBusiness(businessid);	
	return 1;
}

stock bizShowMenu(playerid,const menu[][RES_PRICELIST],menusize){
	new itemText[128];
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comer [item]");						
	
	for(new i=0; i!= menusize;i++)
	{
		format(itemText,sizeof(itemText),"%d) - %s - Precio $%d",i+1,menu[i][bplItemName],menu[i][bplPrice]);
		SendClientMessage(playerid, COLOR_WHITE, itemText);
	}
	return 1;
}

stock processRestMenu(params[],playerid,businessid,const menu[][RES_PRICELIST],menusize){
	new option;
	new eatMessage[128];	
	
	if(sscanf(params, "i", option))
		return bizShowMenu(playerid,menu,menusize);
			
	if(option > menusize)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ese menú no se encuentra en la carta, ordena alguno de los disponibles!");
		
	option=option-1;
	
	if(!bizSellProduct(businessid,playerid,menu[option][bplPrice]))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Vuelve cuando tengas el dinero suficiente!");						

	
	format(eatMessage,sizeof(eatMessage),"realiza un pedido al dependiente del local: %s.",  menu[option][bplItemName]);
	PlayerActionMessage(playerid, 15.0, eatMessage);
	
	if(menu[option][bplEatAmount] > 0.0) PlayerEat(playerid, menu[option][bplEatAmount]);
	if(menu[option][bplDrinkAmount] > 0.0) PlayerDrink(playerid, menu[option][bplDrinkAmount]);
	
	return 1;
}

CMD:comer(playerid, params[])
{	
	new i;
	
	if(GetPVarInt(playerid, "disabled") == DISABLE_DYING || GetPVarInt(playerid, "disabled") == DISABLE_DEATHBED)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");

	i=GetPlayerBusiness(playerid);
	
	switch(Business[i][bType]) {
		case BIZ_REST: 		return processRestMenu(params,playerid,i,RestMenu,sizeof(RestMenu));
		case BIZ_PIZZERIA:	return processRestMenu(params,playerid,i,PizzaMenu,sizeof(PizzaMenu));
		case BIZ_BURGER1:	return processRestMenu(params,playerid,i,McMenu,sizeof(McMenu));
		case BIZ_BURGER2:	return processRestMenu(params,playerid,i,BurgerMenu,sizeof(BurgerMenu));
		case BIZ_BELL:		return processRestMenu(params,playerid,i,BellMenu,sizeof(BellMenu));
	}					
	return 1;
}

//===========================NEGOCIO FERRETERIA/HARD============================

public OnPlayerBuyHard(playerid, biz)
{
	if(Business[biz][bProducts] < 1)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio se ha quedado sin stock, vuelve mas tarde.");

    TogglePlayerControllable(playerid, false);
	ShowPlayerHardBizDialog(playerid, biz);
	return 1;
}

ShowPlayerHardBizDialog(playerid, biz)
{
	new title[64], content[600] = "";

	format(title, sizeof(title), "%s", Business[biz][bName]);
	for(new i = 0; i < sizeof(HardItems); i++)
	{
		format(content, sizeof(content), "%s{FFEFD5}%s {556B2F}$%d\n", content, GetItemName(HardItems[i]), GetItemPrice(HardItems[i]));
	}

	ShowPlayerDialog(playerid, DLG_BIZ_HARD, DIALOG_STYLE_LIST, title, content, "Comprar", "Cerrar");
	return 1;
}

public OnPlayerBuyHardDialog(playerid, listitem)
{
	new biz = GetPlayerBusiness(playerid), itemid, itemprice, str[128];

 	if(biz == 0)
    	return 1;

	itemid = HardItems[listitem];
	itemprice = GetItemPrice(itemid);

	if(GetPlayerCash(playerid) < itemprice)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente.");

	switch(GetItemType(itemid))
	{
	    case ITEM_WEAPON:
	        GivePlayerWeapon(playerid, itemid, 1);
		default:
		{
		    if(GetHandItem(playerid) != 0)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes agarrar otro item con tus manos!");
			SetHandItemAndParam(playerid, itemid, 1);
		}
	}
    GivePlayerCash(playerid, -itemprice);
    Business[biz][bTill] += itemprice;
    Business[biz][bProducts] --;
    saveBusiness(biz);
 	format(str, sizeof(str), "le paga al vendedor y compra un/a %s.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	return 1;
}

//===========================NEGOCIO DE ACCESORIOS==============================

public OnPlayerBuyAccess(playerid, biz)
{
	if(Business[biz][bProducts] < 1)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio se ha quedado sin stock, vuelve mas tarde.");

    TogglePlayerControllable(playerid, false);
	ShowPlayerAccessBizDialog(playerid, biz);
	return 1;
}

ShowPlayerAccessBizDialog(playerid, biz)
{
	new title[64], content[1200] = "";

	format(title, sizeof(title), "%s", Business[biz][bName]);
	for(new i = 0; i < sizeof(AccessItems); i++)
	{
		format(content, sizeof(content), "%s{FFEFD5}%s {556B2F}$%d\n", content, GetItemName(AccessItems[i]), GetItemPrice(AccessItems[i]));
	}

	ShowPlayerDialog(playerid, DLG_BIZ_ACCESS, DIALOG_STYLE_LIST, title, content, "Comprar", "Cerrar");
	return 1;
}

public OnPlayerBuyAccessDialog(playerid, listitem)
{
	new biz = GetPlayerBusiness(playerid), itemid, itemprice, str[128];

 	if(biz == 0)
    	return 1;

	itemid = AccessItems[listitem];
	itemprice = GetItemPrice(itemid);

	if(GetPlayerCash(playerid) < itemprice)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente.");
	if(GetHandItem(playerid) != 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes agarrar otro item con tus manos!");

	SetHandItemAndParam(playerid, itemid, 1);
    GivePlayerCash(playerid, -itemprice);
    Business[biz][bTill] += itemprice;
    Business[biz][bProducts] --;
    saveBusiness(biz);
 	format(str, sizeof(str), "le paga al vendedor y compra un/a %s.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	return 1;
}

//============================NEGOCIO DE ROPA/CLOT==============================

public OnPlayerBuyClot(biz, playerid)
{
	new skintype;
	
	if(Business[biz][bProducts] < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio no tiene stock de productos. Intenta volviendo mas tarde");

	TogglePlayerControllable(playerid, false);
	DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "skinc_active", 1);
	if(Business[biz][bType] == BIZ_CLOT)
	{
		if(PlayerInfo[playerid][pSex] == 1)
	    	skintype = 1;
		else
			skintype = 3;
	} else
  		if(Business[biz][bType] == BIZ_CLOT2)
    	{
    		if(PlayerInfo[playerid][pSex] == 1)
	    		skintype = 2;
			else
				skintype = 4;
	    }
    CreateSelectionMenu(playerid, skintype);
	SelectTextDraw(playerid, 0xACCBF1FF);
	return 1;
}

//===========================NEGOCIO DE ARMAS/AMMU==============================

ShowAmmuCatalog(playerid)
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [número] [balas]");
 	for(new i = 0; i < sizeof(AmmuItems); i++)
 	{
 	    if(GetItemType(AmmuItems[i]) == ITEM_WEAPON)
			SendFMessage(playerid, COLOR_LIGHTYELLOW2, " %d) %s - $%d por munición", i, GetItemName(AmmuItems[i]), GetItemPrice(AmmuItems[i]));
		else
		    SendFMessage(playerid, COLOR_LIGHTYELLOW2, " %d) %s - $%d", i, GetItemName(AmmuItems[i]), GetItemPrice(AmmuItems[i]));
	}
	return 1;
}

public OnPlayerBuyAmmu(biz, playerid, params[])
{
	new option, param, itemid, price, str[128];
	
	if(Business[biz][bProducts] < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio no tiene stock de productos. Intenta volviendo mas tarde");
    if(sscanf(params, "iI(-1)", option, param))
        return ShowAmmuCatalog(playerid);
	if(option < 0 || option >= sizeof(AmmuItems))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa un numero de opcion válido.");

	itemid = AmmuItems[option];
	switch(GetItemType(itemid))
	{
		case ITEM_WEAPON:
		{
		    if(!PlayerInfo[playerid][pWepLic])
	    		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes comprar si no tienes una licencia de portación de armas.");
	    	if(param < 1 || param > 200)
	    	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes comprar menos de 1 bala ni más de 200.");
			price = GetItemPrice(itemid) * param;
	  		if(GetPlayerCash(playerid) < price)
			{
				SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, necesitas $%d.", price);
				return 1;
			}

			GivePlayerWeapon(playerid, itemid, param);
	  		GivePlayerCash(playerid, -price);
			Business[biz][bTill] += price / 2; // la mitad para evitar abusos de sacar armas gratis para el dueño
		}
		default:
		{
  			if(GetHandItem(playerid) != 0)
		        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes agarrar otro item con tus manos!");
	  		if(GetPlayerCash(playerid) < GetItemPrice(itemid))
				return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente.");

			SetHandItemAndParam(playerid, itemid, 1);
			GivePlayerCash(playerid, -GetItemPrice(itemid));
			Business[biz][bTill] += GetItemPrice(itemid);
		}
	}
	format(str, sizeof(str), "le paga al vendedor y compra un/a %s.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	Business[biz][bProducts]--;
	saveBusiness(biz);
	return 1;
}
