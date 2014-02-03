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
