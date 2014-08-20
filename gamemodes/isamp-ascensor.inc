#if defined _isamp_ascensor_included
	#endinput
#endif
#define _isamp_ascensor_included

//-------ASCENSORES DEPTOS -----------------------------------------------------
//-------ASCENSORES DEPTOS -----------------------------------------------------
//-------ASCENSORES DEPTOS -----------------------------------------------------

CMD:piso(playerid, params[])
{
	new numeroDePiso;
	new bool:permisoParaMover = false;

	if(sscanf(params,"i",numeroDePiso))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /piso [0-6-7-8-9-10-11]");
	if(IsObjectMoving(ascensor))
		return SendClientMessage(playerid, COLOR_YELLOW2,"El ascensor está en uso");

	if  (IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 50.5699) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 105.8405) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 115.6330) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 125.4255) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 135.2180) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 145.0105) ||
		IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 154.8030) )

	{
		new Float:coordX0, Float:coordY0, Float:coordZ0;
		new Float:coordX6, Float:coordY6, Float:coordZ6;
		new Float:coordX7, Float:coordY7, Float:coordZ7;
		new Float:coordX8, Float:coordY8, Float:coordZ8;
		new Float:coordX9, Float:coordY9, Float:coordZ9;
		new Float:coordX10, Float:coordY10, Float:coordZ10;
		new Float:coordX11, Float:coordY11, Float:coordZ11;

		GetObjectPos(puertaDerechaPiso0, coordX0, coordY0, coordZ0);
		GetObjectPos(puertaDerechaPiso6, coordX6, coordY6, coordZ6);
		GetObjectPos(puertaDerechaPiso7, coordX7, coordY7, coordZ7);
		GetObjectPos(puertaDerechaPiso8, coordX8, coordY8, coordZ8);
		GetObjectPos(puertaDerechaPiso9, coordX9, coordY9, coordZ9);
		GetObjectPos(puertaDerechaPiso10, coordX10, coordY10, coordZ10);
		GetObjectPos(puertaDerechaPiso11, coordX11, coordY11, coordZ11);

		if (coordY0 == (-1356.13000) && coordY6 == (-1356.13000) &&
			coordY7 == (-1356.13000) && coordY8 == (-1356.13000) &&
			coordY9 == (-1356.13000) && coordY10 == (-1356.13000) &&
			coordY11 == (-1356.13000) ) permisoParaMover = true;

		if( permisoParaMover == true)
		{
			switch(numeroDePiso)
			{
				case 0:	MoveObject(ascensor, 1470.77930, -1356.14099, 51.44730, 3, 0.00000, 0.00000, 0.00000);
				case 6: MoveObject(ascensor, 1470.77930, -1356.14099, 106.73450, 3, 0.00000, 0.00000, 0.00000);
				case 7: MoveObject(ascensor, 1470.77930, -1356.14099, 116.52700, 3, 0.00000, 0.00000, 0.00000);
				case 8: MoveObject(ascensor, 1470.77930, -1356.14099, 126.31950, 3, 0.00000, 0.00000, 0.00000);
				case 9: MoveObject(ascensor, 1470.77930, -1356.14099, 136.11200, 3, 0.00000, 0.00000, 0.00000);
				case 10: MoveObject(ascensor, 1470.77930, -1356.14099, 145.90450, 3, 0.00000, 0.00000, 0.00000);
				case 11: MoveObject(ascensor, 1470.77930, -1356.14099, 155.69701, 3, 0.00000, 0.00000, 0.00000);
				default: SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /piso [0-6-7-8-9-10-11]");
			}
			SendClientMessage(playerid, COLOR_YELLOW2, "Has activado el ascensor");
		}
		else SendClientMessage(playerid, COLOR_YELLOW2,"Espera a que las puertas de todos los pisos estén cerradas");
		}
	return 1;
}

public CerrarPuertaDeAscensor(numeroDePiso)
{
    switch(numeroDePiso)
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
	}
	return 1;
}

CMD:ascensor(playerid, params[])
{
	new Float:coordX, Float:coordY, Float:coordZ;
	new cerrarPisoNumero;
	if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 50.5699) )
		{
			GetObjectPos(ascensor, coordX, coordY, coordZ);
			if( coordZ == 51.44730 )
			{
		    	MoveObject(puertaIzquierdaPiso0, 1470.65369, -1354.41602, 51.46690, 1, 0.00000, 0.00000, 0.00000);
				MoveObject(puertaDerechaPiso0, 1470.65369, -1357.8719, 51.46690, 1, 0.00000, 0.00000, 0.00000);
				cerrarPisoNumero = 0;
				SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
			}
			else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
		}
	else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 105.8405) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 106.73450 )
				{
		    		MoveObject(puertaIzquierdaPiso6, 1470.65369, -1354.41602, 106.70910, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso6, 1470.65369, -1357.8719, 106.70910, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 6;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
    else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 115.6330) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 116.52700 )
				{
		    		MoveObject(puertaIzquierdaPiso7, 1470.65369, -1354.41602, 116.50160, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso7, 1470.65369, -1357.8719, 116.50160, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 7;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
     else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 125.4255) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 126.31950 )
				{
		    		MoveObject(puertaIzquierdaPiso8, 1470.65369, -1354.41602, 126.29410, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso8, 1470.65369, -1357.8719, 126.29410, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 8;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
     else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 135.2180) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 136.11200 )
				{
		    		MoveObject(puertaIzquierdaPiso9, 1470.65369, -1354.41602, 136.08659, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso9, 1470.65369, -1357.8719, 136.08659, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 9;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
     else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 145.0105) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 145.90450 )
				{
		    		MoveObject(puertaIzquierdaPiso10, 1470.65369, -1354.41602, 145.87910, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso10, 1470.65369, -1357.8719, 145.87910, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 10;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
     else if( IsPlayerInRangeOfPoint(playerid, 4, 1468.7391, -1356.1432, 154.8030) )
		    {
				GetObjectPos(ascensor, coordX, coordY, coordZ);
				if( coordZ == 155.69701 )
				{
		    		MoveObject(puertaIzquierdaPiso11, 1470.65369, -1354.41602, 155.67160, 1, 0.00000, 0.00000, 0.00000);
					MoveObject(puertaDerechaPiso11, 1470.65369, -1357.8719, 155.671600, 1, 0.00000, 0.00000, 0.00000);
					cerrarPisoNumero = 11;
					SetTimerEx("CerrarPuertaDeAscensor", 4000, 0, "i", cerrarPisoNumero);
				}
				else SendClientMessage(playerid, COLOR_YELLOW2, "Espera a que el ascensor esté en tu piso");
			}
	return 1;
}
