#if defined _isamp_business_included
	#endinput
#endif
#define _isamp_business_included

#define MAX_BUSINESS	        100

// Mensajes del sistema.
#define BUSINESS_TYPES 			"1: Restaurant - 2: Sucursal telefónica - 3: 24-7 - 4: Ammunation - 5: Publicidad - 6: Tienda de ropa urbana - 7: Bar/Club - 8: Tienda de ropa fina"
#define BUSINESS_TYPES2 		" "

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
}
new Business[MAX_BUSINESS][BusinessSystem];
new bool:openBizPermission[MAX_BUSINESS];

//Admin commands
//====[NEGOCIOS]================================================================
CMD:anegocios(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 20) return 1;

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Negocios:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/ainfonegocio /aninsert /anremove /angetid /anproductos /anprecio /antipo");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/anentrada /ansalida /annombre /anhabilitado /anvender /antele /anvworld /ancaja");
	return 1;
}

CMD:ainfonegocio(playerid, params[]) {
	new
	    id;

    if(PlayerInfo[playerid][pAdmin] < 2) return 1;

	if(sscanf(params, "d", id)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ainfonegocio [idnegocio]");
	} else if(id >= 1 && id < MAX_BUSINESS) {
	    SendFMessage(playerid, COLOR_WHITE, "|---- Negocio %d '%s' ----|", id, Business[id][bName]);
	    SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s [pid %d]", Business[id][bOwner], Business[id][bOwnerSQLID]);
	    SendFMessage(playerid, COLOR_WHITE, "- Habilitado: %d", Business[id][bEnterable]);
	    SendFMessage(playerid, COLOR_WHITE, "- Costo de compra: $%d", Business[id][bPrice]);
	    SendFMessage(playerid, COLOR_WHITE, "- Costo de entrada: $%d", Business[id][bEntranceFee]);
	    SendFMessage(playerid, COLOR_WHITE, "- Caja: $%d", Business[id][bTill]);
        SendFMessage(playerid, COLOR_WHITE, "- Productos: %d", Business[id][bProducts]);
	    SendFMessage(playerid, COLOR_WHITE, "- Cerrado: %d", Business[id][bLocked]);
	    SendFMessage(playerid, COLOR_WHITE, "- Tipo: %d", Business[id][bType]);
	} else {
	    SendClientMessage(playerid, COLOR_YELLOW2, "Negocio inexistente.");
	}
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
//[NEGOCIOS] Comandos

CMD:ayudanegocio(playerid, params[]) {
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"/comprarnegocio - /vendernegocio - /infonegocio - /entradanegocio - /nombrenegocio - /abrirnegocio");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"/negociodepositar - /negocioretirar - /ayudaproductos");
	return 1;
}

CMD:ayudaproductos(playerid, params[]){
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"Para comprar productos dirígete a la zona de transportistas, y estaciona en la puerta del depósito.");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"Una vez allí, escribe /comprar, y cuando llegues con la mercaderia a la entrada de tu negocio usa /descargar.");
	return 1;
}

CMD:abrirnegocio(playerid, params[]) {
    new
		playerName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, playerName, sizeof(playerName));
    for(new bizID = 0; bizID < MAX_BUSINESS; bizID++)	{
		if(PlayerToPoint(3.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) || PlayerToPoint(3.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ])) {
			if(PlayerInfo[playerid][pBizKey] == bizID && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
				if(Business[bizID][bLocked] == 1) {
					if(openBizPermission[bizID] == false)
				        return SendClientMessage(playerid, COLOR_YELLOW2,"¡Debes esperar hasta el próximo dia de pago!");
					Business[bizID][bLocked] = 0;
                    PlayerActionMessage(playerid, 15.0, "toma unas llaves de su bolsillo y abre las puertas del negocio.");
				} else {
					Business[bizID][bLocked] = 1;
                    PlayerActionMessage(playerid, 15.0, "toma unas llaves de su bolsillo y cierra las puertas del negocio.");
                    SendClientMessage(playerid, COLOR_YELLOW2,"Una vez cerrado, no podrás abrirlo hasta el próximo payday y perderas los ingresos de ese día.");
                    openBizPermission[bizID] = false;
				}
				saveBusiness(bizID);
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_YELLOW2,"¡No tienes las llaves de este negocio!");
				return 1;
			}
		}
	}
    return 1;
}

CMD:negocioretirar(playerid,params[]) {
	new
	    string[128],
	    ammount,
		bizID = PlayerInfo[playerid][pBizKey];

	if(sscanf(params, "d", ammount)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negocioretirar [cantidad]");
	else if(bizID != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
		if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld]) {
	        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Te encuentras demasiado lejos de la caja!");
	    }
  		if(ammount > Business[bizID][bTill]) {
    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes esa cantidad de dinero en la caja!");
		}
	    if(ammount > 1000000 || ammount < 1) {
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes retirar más de $1.000.000 o menos de $1.");
	    }
		GivePlayerCash(playerid, ammount);
		Business[bizID][bTill] -= ammount;
		format(string, sizeof(string), "Has retirado $%d de la caja registradora, nuevo total: $%d.", ammount, Business[bizID][bTill]);
		SendClientMessage(playerid, COLOR_WHITE, string);
    	PlayerActionMessage(playerid, 15.0, "abre la caja registradora y retira algo de dinero dentro.");
        saveBusiness(bizID);
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No eres propietario de ningún negocio!");
	}
	return 1;
}

CMD:negociodepositar(playerid, params[]) {
	new
		string[128],
	    ammount,
		bizID = PlayerInfo[playerid][pBizKey];

	if(sscanf(params, "d", ammount)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /negociodepositar [cantidad]");
	else if(bizID != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
		if(!PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]) || GetPlayerVirtualWorld(playerid) != Business[bizID][bInsideWorld]) {
	        return SendClientMessage(playerid, COLOR_YELLOW2, "¡Te encuentras demasiado lejos de la caja!");
	    }
    	if(GetPlayerCash(playerid) < ammount) {
    		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes esa cantidad de dinero!");
		}
	    if(ammount > 1000000) {
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes depositar más de $1.000.000.");
	    }
	    if(Business[bizID][bTill] >= 1000000) {
	        return SendClientMessage(playerid, COLOR_YELLOW2, "La caja se encuentra actualmente llena.");
	    }
		GivePlayerCash(playerid, -ammount);
		Business[bizID][bTill] += ammount;
		format(string, sizeof(string), "Has depositado $%d en la caja registradora, nuevo total: $%d.", ammount, Business[bizID][bTill]);
		SendClientMessage(playerid, COLOR_WHITE, string);
        PlayerActionMessage(playerid, 15.0, "abre la caja registradora y guarda algo de dinero dentro.");
        saveBusiness(bizID);
		return 1;
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No eres propietario de ningún negocio!");
	}
	return 1;
}

CMD:entradanegocio(playerid,params[]) {
	new
	    string[128],
	    bizID = PlayerInfo[playerid][pBizKey],
	    playerName[MAX_PLAYER_NAME],
	    price;

	GetPlayerName(playerid, playerName, sizeof(playerName));
	if(sscanf(params, "d", price)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /entradanegocio [precio de entrada]");
	else if(bizID != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
		if(PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) || PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))	{
			if(price < 0 || price > 10000) {
				SendClientMessage(playerid, COLOR_YELLOW2, "¡El costo de la entrada no debe ser menor a $0 ni mayor a $10000!");
				return 1;
			}
			Business[bizID][bEntranceFee] = price;
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el costo de entrada a tu negocio ahora es de $%d.", Business[bizID][bEntranceFee]);
			SendClientMessage(playerid, COLOR_WHITE, string);
			saveBusiness(bizID);
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");
		}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un negocio!");
	}
	return 1;
}

CMD:nombrenegocio(playerid,params[]) {
	new
	    string[128],
	    bizID = PlayerInfo[playerid][pBizKey],
	    playerName[MAX_PLAYER_NAME],
	    bizName[64];

	GetPlayerName(playerid, playerName, sizeof(playerName));
	if(sscanf(params, "s[64]", bizName)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /nombrenegocio [nombre - 64 caracteres]");
	else if(bizID != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
		if(PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) || PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))	{
			mysql_real_escape_string(bizName, bizName);
			strmid(Business[bizID][bName], bizName, 0, 64, 255);
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el nombre de tu negocio ahora es  '%s'.",Business[bizID][bName]);
			SendClientMessage(playerid, COLOR_WHITE, string);
			saveBusiness(bizID);
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");
		}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un negocio!");
	}
	return 1;
}

CMD:infonegocio(playerid,params[]) {
	new
	    string[128],
		bizID = PlayerInfo[playerid][pBizKey],
		playerName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, playerName, sizeof(playerName));
	if(bizID != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
		if(PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) || PlayerToPoint(20.0, playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]))	{
            SendClientMessage(playerid, COLOR_WHITE, "----[Información sobre el negocio]----");
            format(string, sizeof(string), "Nombre: 	%s", Business[bizID][bName]);
            SendClientMessage(playerid, COLOR_WHITE, string);
            format(string, sizeof(string), "Caja:		$%d", Business[bizID][bTill]);
            SendClientMessage(playerid, COLOR_WHITE, string);
            format(string, sizeof(string), "Cerrado: 	%d", Business[bizID][bLocked]);
            SendClientMessage(playerid, COLOR_WHITE, string);
            format(string, sizeof(string), "Productos: 	%d", Business[bizID][bProducts]);
            SendClientMessage(playerid, COLOR_WHITE, string);
            format(string, sizeof(string), "Entrada: 	$%d", Business[bizID][bEntranceFee]);
            SendClientMessage(playerid, COLOR_WHITE, string);
            SendClientMessage(playerid, COLOR_WHITE, "--------------------------------------");
			return 1;
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en tu negocio!");
		}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún negocio!");
	}
	return 1;
}

CMD:comprarnegocio(playerid,params[]) {
	new
	    string[128],
		playerName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, playerName, sizeof(playerName));
	for(new bizID = 0; bizID < MAX_BUSINESS; bizID++)	{
		if(PlayerToPoint(2.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]) && Business[bizID][bOwnerSQLID] == -1) {
		    if(Business[bizID][bPrice] == 0) {
		        SendClientMessage(playerid, COLOR_YELLOW2, "Parece que este negocio se encuentra deshabilitado...");
				return 1;
		    }
			if(PlayerInfo[playerid][pBizKey] != 0 && Business[PlayerInfo[playerid][pBizKey]][bOwnerSQLID] == PlayerInfo[playerid][pID]) {
				SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes tener más de un negocio!");
				return 1;
			}
			if(GetPlayerCash(playerid) > Business[bizID][bPrice]) {
				PlayerInfo[playerid][pBizKey] = bizID;
				Business[bizID][bOwnerSQLID] = PlayerInfo[playerid][pID];
				strmid(Business[bizID][bOwner], playerName, 0, strlen(playerName), 255);
				GivePlayerCash(playerid, -Business[bizID][bPrice]);
				SetPlayerInterior(playerid, Business[bizID][bInsideInt]);
				SetPlayerVirtualWorld(playerid, Business[bizID][bInsideWorld]);
				SetPlayerPos(playerid, Business[bizID][bInsideX], Business[bizID][bInsideY], Business[bizID][bInsideZ]);
				SetPlayerFacingAngle(playerid, Business[bizID][bInsideAngle]);
				SetCameraBehindPlayer(playerid);
   				PlayerActionMessage(playerid, 15.0, "toma dinero de su bolsillo y firma un contrato, luego recibe las llaves del negocio.");
   				SendClientMessage(playerid, COLOR_YELLOW2, "¡Felicitaciones, has comprado este negocio!");
				saveBusiness(bizID);
				format(string, sizeof(string), "[ALERTA DE USUARIO]: %s (DBID: %d) > compra de negocio ID: %d.", playerName, PlayerInfo[playerid][pID], bizID);
				AdministratorMessage(COLOR_ADMINCMD, string, 2);
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
				return 1;
			}
		}
	}
	return 1;
}

CMD:jetx(playerid,params[]) {
	if(PlayerInfo[playerid][pAdmin] < 5)
	    return 1;

    SetPlayerSpecialAction(playerid,2);
    return 1;
}

CMD:vendernegocio(playerid,params[]) {
	new
	    string[128],
		playerName[MAX_PLAYER_NAME],
		bizID;

	GetPlayerName(playerid, playerName, sizeof(playerName));
	if(PlayerInfo[playerid][pBizKey] != 0 && strcmp(playerName, Business[PlayerInfo[playerid][pBizKey]][bOwner], true) == 0) {
		bizID = PlayerInfo[playerid][pBizKey];
		if(PlayerToPoint(1.0, playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ])) {
			Business[bizID][bLocked] = 0;
			Business[bizID][bOwnerSQLID] = -1;
			strmid(Business[bizID][bOwner], "Ninguno", 0, strlen("Ninguno"), 255);
			GivePlayerCash(playerid, (Business[bizID][bPrice] / 100) * 70); // 70 porciento del valor original
			format(string, sizeof(string), "¡Has vendido el negocio por $%d!", (Business[bizID][bPrice] / 100) * 70);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			PlayerInfo[playerid][pBizKey] = 0;
			PlayerActionMessage(playerid, 15.0, "rompe el contrato, y le da las llaves del negocio al inmobiliario.");
			saveBusiness(bizID);
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2,"¡Debes estar en la entrada de tu negocio para venderlo!");
		}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes ningún negocio para vender!");
	}
	return 1;
}

//Comandos de admin relacionados con negocios


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

CMD:antele(playerid, params[]) {
	new
	    bizID;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;

	if(sscanf(params, "d", bizID)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /antele [idnegocio]");
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		SetPlayerPos(playerid, Business[bizID][bOutsideX], Business[bizID][bOutsideY], Business[bizID][bOutsideZ]);
		SetPlayerInterior(playerid, Business[bizID][bOutsideInt]);
	}
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

    if(PlayerInfo[playerid][pAdmin] < 4)
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

    if(PlayerInfo[playerid][pAdmin] < 10)
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

CMD:anvender(playerid, params[]) {
	new
	    string[128],
	    query[128],
	    bizID;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	if(sscanf(params, "d", bizID)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /anvender [idnegocio]");
	else if(bizID >= 0 && bizID < MAX_BUSINESS) {
		Business[bizID][bLocked] = 0;
		foreach(Player, i) {
			if(PlayerInfo[i][pID] == Business[bizID][bOwnerSQLID]) {
                PlayerInfo[i][pBizKey] = 0;
			} else {
			    format(query, sizeof(query), "UPDATE `accounts` SET `BizKey`='0' WHERE `Id`=%d", PlayerInfo[i][pID]);
				mysql_function_query(dbHandle, query, false, "", "");
			}
		}
		Business[bizID][bOwnerSQLID] = -1;
		strmid(Business[bizID][bOwner], "Ninguno", 0, strlen("Ninguno"), 255);
		format(string, sizeof(string), "[ALERTA DE ADMIN]: %s (DBID: %d) > venta de negocio ID: %d.", PlayerName(playerid), PlayerInfo[playerid][pID], bizID);
		AdministratorMessage(COLOR_ADMINCMD, string, 2);
		saveBusiness(bizID);
		ReloadBizIcon(bizID);
	}
	return 1;
}
