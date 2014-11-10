#if defined _isamp_ascensor_included
	#endinput
#endif
#define _isamp_ascensor_included

//===========================SISTEMA DE ASCENSOR================================

//============================VARIABLES INTERNAS================================

new
	liftTimer,
	bool:liftBeingUsed = false;
	
//============================FUNCIONES PUBLICAS================================

forward bool:IsLiftMoving(); // Devuelve verdadero si el ascensor está operando, o falso en caso contrario.
forward bool:IsPlayerOnLift(playerid); // Devuelve verdadero si el jugador está dentro del ascensor, o falso si no lo está.
forward GetLiftFloor(); // Devuelve el piso en el que está el ascensor. Retorna -1 si no está en ninguno.
forward GetPlayerFloor(playerid); // Devuelve el piso (si está en el lobby) del jugador. Retorna -1 si está en ninguno.
forward MoveLiftTo(piso); // Inicia el ciclo de movimiento de las puertas y del ascensor hacia el piso indicado.
forward OpenLiftDoor(piso); // Abre las puertas del ascensor en el piso indicado.
forward CloseLiftDoor(piso);// Cierra las puertas del ascensor en el piso indicado.

//============================FUNCIONES INTERNAS================================

forward StartLiftMovement(piso);
forward OnLiftMoveToFloor(piso);
forward EndLiftMovement();

//===========================IMPLEMENTACIÓN DE FUNCIONES========================

stock bool:IsLiftBeingUsed()
{
	return liftBeingUsed;
}

stock bool:IsPlayerOnLift(playerid)
{
    new Float:cx, Float:cy, Float:cz;

	GetObjectPos(ascensor, cx, cy, cz);

	if(IsPlayerInRangeOfPoint(playerid, 2, cx, cy, cz))
	    return true;
	else
	    return false;
}

stock GetLiftFloor()
{
    new Float:cx, Float:cy, Float:cz;

	GetObjectPos(ascensor, cx, cy, cz);

	if(cz == 51.44730) return 0;
	else if(cz == 106.73450) return 6;
	else if(cz == 116.52700) return 7;
	else if(cz == 126.31950) return 8;
	else if(cz == 136.11200) return 9;
	else if(cz == 145.90450) return 10;
	else if(cz == 155.69701) return 11;

	return -1;
}

stock GetPlayerFloor(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 50.5699)) return 0;
    else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 105.8405)) return 6;
    else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 115.6330)) return 7;
    else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 125.4255)) return 8;
    else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 135.2180)) return 9;
    else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 145.0105)) return 10;
	else if(IsPlayerInRangeOfPoint(playerid, 3, 1468.7391, -1356.1432, 154.8030)) return 11;
	else return -1;
}

public MoveLiftTo(piso)
{
	if(liftBeingUsed == false)
	{
	 	liftBeingUsed = true;
	    CloseLiftDoor(GetLiftFloor());
	    SetTimerEx("StartLiftMovement", 2000, false, "i", piso); // Tarda 2 segundos en cerrar las puertas.
   }
    return 1;
}

public StartLiftMovement(piso)
{
	switch(piso)
	{
		case 0: MoveObject(ascensor, 1470.77930, -1356.14099, 51.44730, 3, 0.00000, 0.00000, 0.00000);
		case 6: MoveObject(ascensor, 1470.77930, -1356.14099, 106.73450, 3, 0.00000, 0.00000, 0.00000);
		case 7: MoveObject(ascensor, 1470.77930, -1356.14099, 116.52700, 3, 0.00000, 0.00000, 0.00000);
		case 8:	MoveObject(ascensor, 1470.77930, -1356.14099, 126.31950, 3, 0.00000, 0.00000, 0.00000);
		case 9:	MoveObject(ascensor, 1470.77930, -1356.14099, 136.11200, 3, 0.00000, 0.00000, 0.00000);
		case 10: MoveObject(ascensor, 1470.77930, -1356.14099, 145.90450, 3, 0.00000, 0.00000, 0.00000);
		case 11: MoveObject(ascensor, 1470.77930, -1356.14099, 155.69701, 3, 0.00000, 0.00000, 0.00000);
		default: return 1;
	}

	liftTimer = SetTimerEx("OnLiftMoveToFloor", 1000, true, "i", piso); // Timer recursivo para darnos cuenta cuando llega al piso de destino.

	return 1;
}

public OnLiftMoveToFloor(piso)
{
	if(GetLiftFloor() == piso) // Cuando llega a destino, abrimos las puertas y borramos el timer.
	{
		OpenLiftDoor(piso);
		KillTimer(liftTimer);
	 	SetTimer("EndLiftMovement", 3000, false);
	}
	return 1;
}

public EndLiftMovement()
{
	liftBeingUsed = false;
}

stock OpenLiftDoor(piso)
{
	switch(piso)
	{
		case 0:
		{
			MoveObject(puertaIzquierdaPiso0, 1470.65369, -1354.41602, 51.46690, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso0, 1470.65369, -1357.8719, 51.46690, 1, 0.00000, 0.00000, 0.00000);
		}
		case 6:
		{
			MoveObject(puertaIzquierdaPiso6, 1470.65369, -1354.41602, 106.70910, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso6, 1470.65369, -1357.8719, 106.70910, 1, 0.00000, 0.00000, 0.00000);
		}
		case 7:
		{
			MoveObject(puertaIzquierdaPiso7, 1470.65369, -1354.41602, 116.50160, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso7, 1470.65369, -1357.8719, 116.50160, 1, 0.00000, 0.00000, 0.00000);
		}
		case 8:
		{
			MoveObject(puertaIzquierdaPiso8, 1470.65369, -1354.41602, 126.29410, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso8, 1470.65369, -1357.8719, 126.29410, 1, 0.00000, 0.00000, 0.00000);
		}
		case 9:
		{
			MoveObject(puertaIzquierdaPiso9, 1470.65369, -1354.41602, 136.08659, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso9, 1470.65369, -1357.8719, 136.08659, 1, 0.00000, 0.00000, 0.00000);
		}
		case 10:
		{
			MoveObject(puertaIzquierdaPiso10, 1470.65369, -1354.41602, 145.87910, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso10, 1470.65369, -1357.8719, 145.87910, 1, 0.00000, 0.00000, 0.00000);
		}
		case 11:
		{
			MoveObject(puertaIzquierdaPiso11, 1470.65369, -1354.41602, 155.67160, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso11, 1470.65369, -1357.8719, 155.671600, 1, 0.00000, 0.00000, 0.00000);
		}
		default:
		    return 1;
	}
	return 1;
}

stock CloseLiftDoor(piso)
{
    switch(piso)
	{
		case 0:
		{
			MoveObject(puertaIzquierdaPiso0, 1470.65369, -1356.13599, 51.46690, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso0, 1470.65369, -1356.13000, 51.46690, 1, 0.00000, 0.00000, 0.00000);
		}
		case 6:
		{
			MoveObject(puertaIzquierdaPiso6, 1470.65369, -1356.13599, 106.70910, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso6, 1470.65369, -1356.13000, 106.70910, 1, 0.00000, 0.00000, 0.00000);
		}
		case 7:
		{
			MoveObject(puertaIzquierdaPiso7, 1470.65369, -1356.13599, 116.50160, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso7, 1470.65369, -1356.13000, 116.50160, 1, 0.00000, 0.00000, 0.00000);
		}
		case 8:
		{
			MoveObject(puertaIzquierdaPiso8, 1470.65369, -1356.13599, 126.29410, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso8, 1470.65369, -1356.13000, 126.29410, 1, 0.00000, 0.00000, 0.00000);
		}
		case 9:
		{
			MoveObject(puertaIzquierdaPiso9, 1470.65369, -1356.13599, 136.08659, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso9, 1470.65369, -1356.13000, 136.08659, 1, 0.00000, 0.00000, 0.00000);
		}
		case 10:
		{
			MoveObject(puertaIzquierdaPiso10, 1470.65369, -1356.13599, 145.87910, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso10, 1470.65369, -1356.13000, 145.87910, 1, 0.00000, 0.00000, 0.00000);
		}
		case 11:
		{
			MoveObject(puertaIzquierdaPiso11, 1470.65369, -1356.13599, 155.67160, 1, 0.00000, 0.00000, 0.00000);
			MoveObject(puertaDerechaPiso11, 1470.65369, -1356.13000, 155.67160, 1, 0.00000, 0.00000, 0.00000);
		}
		default:
		    return 1;
	}
	return 1;
}

//================================COMANDOS======================================

CMD:ascensor(playerid, params[])
{
	new piso = GetPlayerFloor(playerid);

	if(piso != -1)
	{
	    if(GetLiftFloor() == piso)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "¡El ascensor está en tu piso!");
		if(IsLiftBeingUsed())
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El ascensor está en uso, inténtalo en un rato.");

		MoveLiftTo(piso);
		PlayerActionMessage(playerid, 15.0, "presiona un botón para llamar al ascensor.");
		SendClientMessage(playerid, COLOR_WHITE, "Aguarda un momento a que el ascensor llegue a tu piso.");
	}
	return 1;
}

CMD:piso(playerid, params[])
{
	new piso;

	if(sscanf(params, "i", piso))
	    return SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /piso [0, 6, 7, 8, 9, 10 u 11]");
	if(piso != 0 && (piso < 6 || piso > 11))
	    return SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /piso [0, 6, 7, 8, 9, 10 u 11]");
	if(IsPlayerOnLift(playerid) == false)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar en el ascensor para usarlo!");
	if(piso == GetLiftFloor())
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Ya te encuentras en ese piso!");
	if(IsLiftBeingUsed())
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡El ascensor está en uso!");

    PlayerActionMessage(playerid, 15.0, "presiona un botón en el panel del ascensor.");
	MoveLiftTo(piso);

	return 1;
}
