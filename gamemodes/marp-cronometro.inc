#if defined _marp_cronometro_included
	#endinput
#endif
#define _marp_cronometro_included

////////////////////////////////////////////////////////////////////////////////
// 				Sencillo sistema de cronometro/cuenta atrás.                  //
//                                                                            //
// Para que sirve: Inicia una cuenta atrás (con textdraw mostrandola) desde   //
// el tiempo deseado en segundos y, al llegar a cero, llama a la función      //
// PUBLICA que se indicó por parámetro.                                       //
//                                                                            //
// Al finalizar, se borra automaticamente el cronometro y su timer. También,  //
// si se lo requiere, se pueden borrar ambas cosas con Cronometro_Borrar en   //
// cualquier momento de su ejecución. Recuerde borrarlo en desconexión.		  //
//                                                                            //
// Por ahora solo tiene soporte para un cronometro a la vez por jugador.      //
//                                                                            //
// Si el cronometro se creó con éxito, Cronometro_Crear devuelve 1. Caso      //
// contrario (parámetros inválidos o ese jugador ya tiene un cronometro       //
// funcionando en ese momento), devuelve 0.                                   //
////////////////////////////////////////////////////////////////////////////////

new pCronometroTime[MAX_PLAYERS],
	pCronometroTimer[MAX_PLAYERS],
	pCronometroFunction[MAX_PLAYERS][32],
	PlayerText:PTD_Cronometro[MAX_PLAYERS];

Cronometro_Crear(playerid, time, function[])
{
	if(pCronometroTime[playerid] == 0 && pCronometroTimer[playerid] == 0 && time > 0 && function[0])
	{
		PTD_Cronometro[playerid] = CreatePlayerTextDraw(playerid, 516.000000, 166.687500, " ");
		PlayerTextDrawLetterSize(playerid, PTD_Cronometro[playerid], 0.464500, 1.621875);
		PlayerTextDrawSetOutline(playerid, PTD_Cronometro[playerid], -1);
		PlayerTextDrawShow(playerid, PTD_Cronometro[playerid]);
		pCronometroTime[playerid] = time;
		format(pCronometroFunction[playerid], 32, "%s", function);
		pCronometroTimer[playerid] = SetTimerEx("Cronometro", 1000, true, "i", playerid);
		return 1;
	}
	return 0;
}

Cronometro_Borrar(playerid)
{
	if(pCronometroTimer[playerid] > 0)
	{
		KillTimer(pCronometroTimer[playerid]);
    	PlayerTextDrawDestroy(playerid, PTD_Cronometro[playerid]);
		pCronometroTime[playerid] = 0;
		pCronometroTimer[playerid] = 0;
	}
}

forward Cronometro(playerid);
public Cronometro(playerid)
{
	if(pCronometroTime[playerid] > 0)
	{
		new minutes, segs, str[32];

		if(pCronometroTime[playerid] >= 60)
		{
		    minutes = floatround(pCronometroTime[playerid] / 60, floatround_floor);
		    segs = pCronometroTime[playerid] - minutes * 60;
		    format(str, sizeof(str), "Tiempo: %02dm%02ds", minutes, segs);
		    PlayerTextDrawSetString(playerid, PTD_Cronometro[playerid], str);
		}
		else
	 	{
		 	format(str, sizeof(str), "Tiempo: %02ds", pCronometroTime[playerid]);
		    PlayerTextDrawSetString(playerid, PTD_Cronometro[playerid], str);
		}
		pCronometroTime[playerid]--;
	}
	else
	{
 	    if(pCronometroFunction[playerid][0]) // Chequear que no esté vacio
 	    {
	 		CallLocalFunction(pCronometroFunction[playerid], "i", playerid);
	 	}
	    Cronometro_Borrar(playerid);
	}
	return 1;
}
