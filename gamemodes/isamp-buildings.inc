#if defined _isamp_buildings_included
	#endinput
#endif
#define _isamp_buildings_included

//======================SISTEMA Y COMANDOS DE EDIFICIOS=========================

//================================CONSTANTES====================================

#define MAX_BUILDINGS           100

//============================VARIABLES INTERNAS================================

enum BuildingSystem {
	blID,
	blText[64],
	blText2[64],
	blEntranceFee,
	blLocked,
	Float:blOutsideX,
	Float:blOutsideY,
	Float:blOutsideZ,
	Float:blOutsideAngle,
	Float:blInsideX,
	Float:blInsideY,
	Float:blInsideZ,
	Float:blInsideAngle,
	blInsideInt,
	blOutsideInt,
	blPickupModel,
	// Datos temporales.
	bool:blLoaded,
	bool:blInsert,
	bool:blDelete,
	blInsideWorld,
	blOutsidePickup,
	blInsidePickup,
	blFaction,
	Text3D:blOutsideLabel,
	Text3D:blInsideLabel,
	blRadio
};

new Building[MAX_BUILDINGS][BuildingSystem];

//================================FUNCIONES=====================================

forward GetPlayerBuilding(playerid);
forward bool:EnterBuilding(playerid);
forward bool:LeaveBuilding(playerid);

//========================IMPLEMENTACION DE FUNCIONES===========================
	
stock GetPlayerBuilding(playerid)
{
	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
	    if(Building[i][blInsideInt] == GetPlayerInterior(playerid) && Building[i][blInsideWorld] == GetPlayerVirtualWorld(playerid) && Building[i][blInsideWorld] != 0)
			return i;
	}
	return 0;
}

stock bool:EnterBuilding(playerid)
{
	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
		if(PlayerToPoint(1.0, playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]))
		{
			if(Building[i][blLocked] == 0 || AdminDuty[playerid])
			{
			    if(Building[i][blEntranceFee] == 0 || GetPlayerCash(playerid) >= Building[i][blEntranceFee])
				{
					SetPlayerInterior(playerid, Building[i][blInsideInt]);
					SetPlayerVirtualWorld(playerid, Building[i][blInsideWorld]);
					SetPlayerPos(playerid, Building[i][blInsideX], Building[i][blInsideY], Building[i][blInsideZ]);
					SetPlayerFacingAngle(playerid, Building[i][blInsideAngle]);
					PlayRadioStreamForPlayer(playerid, Building[i][blRadio]);
					GivePlayerCash(playerid, -Building[i][blEntranceFee]);
					if(Building[i][blEntranceFee] > 0)
						SendFMessage(playerid, COLOR_YELLOW2, "¡Te han cobrado $%d para ingresar al edificio %s!", Building[i][blEntranceFee], Building[i][blText]);
					else
					    SendFMessage(playerid, COLOR_YELLOW2, "¡Bienvenido al edificio %s!", Building[i][blText]);
					SetCameraBehindPlayer(playerid);
				} else
					GameTextForPlayer(playerid, "~r~No tienes el dinero suficiente!", 2000, 2);
			} else
				GameTextForPlayer(playerid, "~r~Cerrado!", 2000, 4);
			return true;
		}
	}
	return false;
}

stock bool:LeaveBuilding(playerid)
{
	for(new i = 0; i < sizeof(Building); i++)
	{
		if(PlayerToPoint(1.0, playerid, Building[i][blInsideX], Building[i][blInsideY], Building[i][blInsideZ]))
		{
		    if(GetPlayerVirtualWorld(playerid) == Building[i][blInsideWorld])
			{
				if(Building[i][blLocked] == 0 || AdminDuty[playerid])
				{
					SetPlayerInterior(playerid, Building[i][blOutsideInt]);
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerPos(playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]);
					SetPlayerFacingAngle(playerid, Building[i][blOutsideAngle]);
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

CMD:cerrar(playerid, params[])
{
	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
		if(PlayerToPoint(1.0, playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]) || PlayerToPoint(1.0, playerid, Building[i][blInsideX], Building[i][blInsideY], Building[i][blInsideZ]))
		{
			if(Building[i][blFaction] != 0 && PlayerInfo[playerid][pFaction] == Building[i][blFaction])
			{
				if(Building[i][blLocked] == 0)
				{
				    Building[i][blLocked] = 1;
				    GameTextForPlayer(playerid, "Puertas cerradas", 2000, 4);
				    PlayerActionMessage(playerid, 15.0, "toma un manojo de llaves de su bolsillo y cierra la puerta.");
    			}
			} else {
				GameTextForPlayer(playerid, "~r~No tienes las llaves", 2000, 4);
			}
		}
	}
	return 1;
}

CMD:abrir(playerid, params[])
{
	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
		if(PlayerToPoint(1.0, playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]) || PlayerToPoint(1.0, playerid, Building[i][blInsideX], Building[i][blInsideY], Building[i][blInsideZ]))
		{
			if(Building[i][blFaction] != 0 && PlayerInfo[playerid][pFaction] == Building[i][blFaction])
			{
				if(Building[i][blLocked] == 1)
				{
				    Building[i][blLocked] = 0;
				    GameTextForPlayer(playerid, "Puertas abiertas", 2000, 4);
				    PlayerActionMessage(playerid, 15.0, "toma un manojo de llaves de su bolsillo y abre la puerta.");
    			}
			} else {
				GameTextForPlayer(playerid, "~r~No tienes las llaves", 2000, 4);
			}
		}
	}
	return 1;
}

//========================COMANDOS ADMIN DE EDIFICIOS===========================

CMD:aedificios(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Comandos de edificios]:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/aeinfo /aeinsert - /aeremove - /aevworld - /aegetid - /aetexto - /aetexto2 - /aeentrada - /aesalida - /aecosto");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/aecerrado - /aetele - /aepickup - /aefaccion - /aeradio");
	return 1;
}

CMD:aeinfo(playerid, params[])
{
	new id;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeinfo [IDedificio]");
	if(id < 1 || id >= MAX_BUILDINGS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");

	SendFMessage(playerid, COLOR_WHITE, "=======================[Negocio %d '%s']=======================", id, Building[id][blText]);
	SendFMessage(playerid, COLOR_WHITE, "- Texto: %s", Building[id][blText]);
	SendFMessage(playerid, COLOR_WHITE, "- Texto2: %s", Building[id][blText2]);
	SendFMessage(playerid, COLOR_WHITE, "- Costo de entrada: $%d", Building[id][blEntranceFee]);
	SendFMessage(playerid, COLOR_WHITE, "- Cerrado: %d", Building[id][blLocked]);
	SendFMessage(playerid, COLOR_WHITE, "- Facción: %d", Building[id][blFaction]);
	return 1;
}

CMD:aeremove(playerid, params[])
{
	new blid;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "d", blid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeremove [idedificio]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");

	Building[blid][blDelete] = true;
	saveBuilding(blid);
	return 1;
}

CMD:aeinsert(playerid, params[])
{
	new blid, name[32], Float:entAngle, locked, fee, faction, pickupModel;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dddds[32]", fee, locked, pickupModel,  faction, name))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeinsert [costo entrada] [locked] [modelo pickup] [faccion, 0 = n/a] [text (64 ch)]");
	if(locked != 1 && locked != 0)
	    return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} el valor 'locked' no puede ser diferente a 1 o 0.");

	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
	    if(!Building[i][blLoaded])
		{
	        Building[i][blLoaded] = true;
			blid = i;
			break;
		}
	}

	GetPlayerPos(playerid, Building[blid][blOutsideX], Building[blid][blOutsideY], Building[blid][blOutsideZ]);
	GetPlayerFacingAngle(playerid, entAngle);

    Building[blid][blOutsideInt] = GetPlayerInterior(playerid);
	Building[blid][blOutsideAngle] = entAngle + 180;
	Building[blid][blEntranceFee] = fee;
	Building[blid][blLocked] = locked;
	Building[blid][blPickupModel] = pickupModel;
	Building[blid][blFaction] = faction;
	Building[blid][blInsert] = true;
	mysql_real_escape_string(name, name,1,sizeof(name));
 	strmid(Building[blid][blText], (name), 0, strlen((name)), 64);
 	saveBuilding(blid);
	return 1;
}

CMD:aegetid(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 10)
		return 1;

	for(new i = 1; i < MAX_BUILDINGS; i++)
	{
		if(PlayerToPoint(1.0, playerid, Building[i][blOutsideX], Building[i][blOutsideY], Building[i][blOutsideZ]))
		{
		    SendFMessage(playerid, COLOR_WHITE, "ID del edificio: %d", i);
		    return 1;
		}
	}
	SendClientMessage(playerid, COLOR_WHITE, "No se ha encontrado ningún edificio en tu posición.");
	return 1;
}

CMD:aetexto(playerid, params[])
{
	new blid, text[64];

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "ds[64]", blid, text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aetexto [idedificio] [texto 64 chars]");
 	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	if(strlen(text) > 64)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes hasta 64 caracteres.");
		
 	mysql_real_escape_string(text, text, 1, sizeof(text));
 	strmid(Building[blid][blText], (text), 0, strlen((text)), 64);
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado el texto del edificio [%d] a '%s'.", blid, text);
	saveBuilding(blid);
	return 1;
}

CMD:aeradio(playerid, params[])
{
	new blid, radio;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "ii", blid, radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeradio [ID edificio] [ID radio]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	if(radio < 0 || radio > 15)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio válida: del 1 al 15. Usa 0 para dejarlo sin radio.");

	Building[blid][blRadio] = radio;
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: Has seteado la radio del edificio %d a %d.", blid, Building[blid][blRadio]);
	return 1;
}

CMD:aetexto2(playerid, params[])
{
	new blid, text[64];

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "ds[64]", blid, text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aetexto2 [idedificio] [texto 64 chars]");
 	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	if(strlen(text) > 64)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes hasta 64 caracteres.");

	mysql_real_escape_string(text, text, 1, sizeof (text));
 	strmid(Building[blid][blText2], (text), 0, strlen((text)), 64);
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado el texto2 del edificio [%d] a '%s'.", blid, text);
	saveBuilding(blid);
	return 1;
}

CMD:aeentrada(playerid, params[])
{
	new string[128], blid, entranceInterior, Float:entranceX, Float:entranceY, Float:entranceZ, Float:entranceAngle;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "d", blid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeentrada [idedificio] - setea la entrada a tu posición, tu ángulo será el adoptado al salir.");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	    
    GetPlayerPos(playerid, entranceX, entranceY, entranceZ);
    GetPlayerFacingAngle(playerid, entranceAngle);
    entranceInterior = GetPlayerInterior(playerid);
	Building[blid][blOutsideX] = entranceX;
	Building[blid][blOutsideY] = entranceY;
	Building[blid][blOutsideZ] = entranceZ;
	Building[blid][blOutsideAngle] = entranceAngle + 180;
	Building[blid][blOutsideInt] = entranceInterior;
	format(string, sizeof(string), "Entrada del edificio [%d] seteada a X:%f Y:%f Z:%f A:%f Interior:%d", blid, entranceX, entranceY, entranceZ, entranceAngle, entranceInterior);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	saveBuilding(blid);
	return 1;
}

CMD:aesalida(playerid, params[])
{
	new string[128], blid, exitInterior, Float:exitX, Float:exitY, Float:exitZ, Float:exitAngle;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "d", blid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aesalida [idedificio] - setea la salida a tu posición, tu ángulo será el adoptado al ingresar.");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	    
	GetPlayerPos(playerid, exitX, exitY, exitZ);
 	GetPlayerFacingAngle(playerid, exitAngle);
    exitInterior = GetPlayerInterior(playerid);
	Building[blid][blInsideX] = exitX;
	Building[blid][blInsideY] = exitY;
	Building[blid][blInsideZ] = exitZ;
	Building[blid][blInsideAngle] = exitAngle + 180;
	Building[blid][blInsideInt] = exitInterior;
	Building[blid][blInsideWorld] = blid * 1000;
	format(string, sizeof(string), "Salida del edificio [%d] seteada a X:%f Y:%f Z:%f A:%f Interior:%d", blid, exitX, exitY, exitZ, exitAngle, exitInterior);
	SendClientMessage(playerid, COLOR_ADMINCMD, string);
	saveBuilding(blid);
	return 1;
}

CMD:aecosto(playerid, params[])
{
	new blid, cost;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", blid, cost))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aecosto [idedificio] [costo de entrada]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");

	Building[blid][blEntranceFee] = cost;
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado el costo de entrada al edificio [%d] a %d.", blid, cost);
	saveBuilding(blid);
	return 1;
}

CMD:aefaccion(playerid, params[])
{
	new blid, faction;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", blid, faction))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aefaccion [idedificio] [facción, 0 = ninguna]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");

	Building[blid][blFaction] = faction;
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado la facción del edificio [%d] a %d.", blid, faction);
	saveBuilding(blid);
	return 1;
}

CMD:aepickup(playerid, params[])
{
	new blid, pickupModel;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", blid, pickupModel))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aepickup [idedificio] [id modelo]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	    
	Building[blid][blPickupModel] = pickupModel;
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado el pickup del edificio [%d] a %d.", blid, pickupModel);
	saveBuilding(blid);
	return 1;
}

CMD:aevworld(playerid, params[])
{
	new blid, vworld;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", blid, vworld))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aevworld [idedificio] [mundo virtual]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	    
	Building[blid][blInsideWorld] = vworld;
	SendFMessage(playerid, COLOR_ADMINCMD, "Has seteado el mundo virtual del edificio [%d] a %d.", blid, vworld);
	saveBuilding(blid);
	return 1;
}

CMD:aecerrado(playerid, params[])
{
	new blid, locked;

    if(PlayerInfo[playerid][pAdmin] < 20)
		return 1;
	if(sscanf(params, "dd", blid, locked))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aecerrado [idedificio] [1=SI, 0=NO]");
	if(locked < 0 || locked > 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El valor no puede ser menor a 0 o mayor a 1.");
	if(blid < 1 || blid >= MAX_BUILDINGS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");
	    
	Building[blid][blLocked] = locked;
	switch(locked)
	{
	    case 0: SendFMessage(playerid, COLOR_ADMINCMD, "Has abierto el edificio [%d]", blid);
	    case 1: SendFMessage(playerid, COLOR_ADMINCMD, "Has cerrado el edificio [%d]", blid);
	}
	saveBuilding(blid);
	return 1;
}

CMD:aetele(playerid, params[])
{
	new blid;

    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "i", blid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aetele [ID edificio]");
	if(blid < 1 || blid >= MAX_BUILDINGS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID de edificio inválida.");

	SetPlayerPos(playerid, Building[blid][blOutsideX], Building[blid][blOutsideY], Building[blid][blOutsideZ]);
	SetPlayerInterior(playerid, Building[blid][blOutsideInt]);
	return 1;
}

