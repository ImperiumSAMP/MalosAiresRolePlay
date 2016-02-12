#if defined _marp_horseraces_included
    #endinput
#endif
#define _marp_horseraces_included
#define HR_MAXNAMES 20

forward CreateHR();
forward RunHR();
forward ResetHR();

new horseNames[5][128];
new bool:boolNames[HR_MAXNAMES];
new winnerHR;
new bool:runningHR;
new betsHR[MAX_PLAYERS][5];
new bool:alreadyBetHR[MAX_PLAYERS];
new bool:isWatchingHR[MAX_PLAYERS];
new hourHR;
new minuteHR;
new secondHR;

public CreateHR()
{
	runningHR = false;
	new i;
	for(i = 0; i < HR_MAXNAMES; i++)
		boolNames[i] = false;

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		alreadyBetHR[i] = false;
		for(new num = 0; num < 5; num++)
		    betsHR[i][num] = 0;
	}

	new num;
	for(i = 0; i < 5; i++)
	{
		do num = random(HR_MAXNAMES);
  		while (boolNames[num]);
		boolNames[num] = true;

		switch(num)
		{
			case 0: format(horseNames[i], sizeof(horseNames[]), "Morocho Pierre");
			case 1: format(horseNames[i], sizeof(horseNames[]), "Chimestrum");
			case 2: format(horseNames[i], sizeof(horseNames[]), "Curruhue");
			case 3: format(horseNames[i], sizeof(horseNames[]), "Dr Calzado");
			case 4: format(horseNames[i], sizeof(horseNames[]), "Verdolaga");
			case 5: format(horseNames[i], sizeof(horseNames[]), "Trueno Veloz");
			case 6: format(horseNames[i], sizeof(horseNames[]), "Tiro al Blanco");
			case 7: format(horseNames[i], sizeof(horseNames[]), "Tren Urbano");
			case 8: format(horseNames[i], sizeof(horseNames[]), "Rica Milanesa");
			case 9: format(horseNames[i], sizeof(horseNames[]), "Manito Brasilero");
			case 10: format(horseNames[i], sizeof(horseNames[]), "El Furioso");
			case 11: format(horseNames[i], sizeof(horseNames[]), "Good Boy");
			case 12: format(horseNames[i], sizeof(horseNames[]), "Bad Boy");
			case 13: format(horseNames[i], sizeof(horseNames[]), "Gordito Bueno");
			case 14: format(horseNames[i], sizeof(horseNames[]), "Sorpresa");
			case 15: format(horseNames[i], sizeof(horseNames[]), "Gran Torino");
			case 16: format(horseNames[i], sizeof(horseNames[]), "Caballo Blanco");
			case 17: format(horseNames[i], sizeof(horseNames[]), "Perro Mojado");
			case 18: format(horseNames[i], sizeof(horseNames[]), "Slow Coverfield");
			case 19: format(horseNames[i], sizeof(horseNames[]), "Monje Tibetano");
		}
	}

	gettime(hourHR, minuteHR, secondHR);
	minuteHR += 5;
	SetTimer("RunHR", 300000, false); // 5 minutos
	return 1;
}

public RunHR()
{
	runningHR = true;
    new Float:time[5];
    new luck = random(100);
	if(luck < 25) winnerHR = 0;
		else if(luck < 50) winnerHR = 1;
			else if(luck < 73) winnerHR = 2;
				else if(luck < 90) winnerHR = 3;
					else winnerHR = 4;

	for(new i = 0; i < 5; i++)
	{
		luck = random(20);
		switch(luck)
		{
			case 0: time[i] = 0.999;
			case 1: time[i] = 0.997;
			case 2: time[i] = 0.995;
	        case 3: time[i] = 0.992;
			case 4: time[i] = 0.99;
			case 5: time[i] = 0.985;
			case 6: time[i] = 0.98;
			case 7: time[i] = 0.975;
			case 8: time[i] = 0.97;
			case 9: time[i] = 0.965;
			case 10: time[i] = 0.96;
			case 11: time[i] = 0.95;
			case 12: time[i] = 0.94;
	        case 13: time[i] = 0.93;
			case 14: time[i] = 0.91;
			case 15: time[i] = 0.89;
			case 16: time[i] = 0.87;
			case 17: time[i] = 0.85;
			case 18: time[i] = 0.83;
			case 19: time[i] = 0.80;
		}
	}
	time[winnerHR] = 1;

	MoveObject(horseObj[0], 795.68701, 1619.68835, 4.02860, time[0]);
	MoveObject(horseObj[1], 798.68701, 1619.68835, 4.02860, time[1]);
	MoveObject(horseObj[2], 801.68701, 1619.68835, 4.02860, time[2]);
	MoveObject(horseObj[3], 804.68701, 1619.68835, 4.02860, time[3]);
	MoveObject(horseObj[4], 807.68701, 1619.68835, 4.02860, time[4]);

    new msg[128];
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if(isWatchingHR[i])
        {
			format(msg, sizeof(msg), "Relator dice: ¡Arranca la carrera!");
			SendClientMessage(i, COLOR_WHITE, msg);
		}
	}

    SetTimer("ResetHR", 60000, false); // Un minuto
	return 1;
}

public ResetHR()
{
	new bool:ok = false;
	new textbet[128];
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if(alreadyBetHR[i])
		{
	    	for (new g = 0; g < 5; g++)
	    	{
	    		if((!ok) && (betsHR[i][g] > 0))
				{
					if(g == winnerHR)
					{
					    if(winnerHR == 0)
					    {
							GivePlayerCash(i, betsHR[i][winnerHR] * 2);
							format(textbet, sizeof(textbet), "¡Has ganado $%d!", betsHR[i][winnerHR] * 2);
							SendClientMessage(i, COLOR_YELLOW2, textbet);
						}
						else if(winnerHR == 1)
						{
						    GivePlayerCash(i, betsHR[i][winnerHR] * 2);
							format(textbet, sizeof(textbet), "¡Has ganado $%d!", betsHR[i][winnerHR] * 2);
							SendClientMessage(i, COLOR_YELLOW2, textbet);
						}
						else if(winnerHR == 2)
						{
						    GivePlayerCash(i, betsHR[i][winnerHR] * 3);
							format(textbet, sizeof(textbet), "¡Has ganado $%d!", betsHR[i][winnerHR] * 3);
							SendClientMessage(i, COLOR_YELLOW2, textbet);
						}
						else if(winnerHR == 3)
						{
						    GivePlayerCash(i, betsHR[i][winnerHR] * 5);
							format(textbet, sizeof(textbet), "¡Has ganado $%d!", betsHR[i][winnerHR] * 5);
							SendClientMessage(i, COLOR_YELLOW2, textbet);
						}
						else if(winnerHR == 4)
						{
						    GivePlayerCash(i, betsHR[i][winnerHR] * 10);
							format(textbet, sizeof(textbet), "¡Has ganado $%d!", betsHR[i][winnerHR] * 10);
							SendClientMessage(i, COLOR_YELLOW2, textbet);
						}
					}
					else
					{
					   	GivePlayerCash(i, -betsHR[i][g]);
                        format(textbet, sizeof(textbet), "¡Has perdido $%d!", betsHR[i][g]);
					    SendClientMessage(i, COLOR_YELLOW2, textbet);
					}
					ok = true;
				}
			}
			ok = false;
		}
	}

	runningHR = false;
    new aux = winnerHR + 1;
    new msg[128];

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if(isWatchingHR[i])
        {
			format(msg, sizeof(msg), "Relator dice: ¡El ganador es: %s, con el numero %d!", horseNames[winnerHR], aux);
			SendClientMessage(i, COLOR_WHITE, msg);
		}
	}

	MoveObject(horseObj[0], 795.68701, 1669.14832, 4.02860, 1000000);
	MoveObject(horseObj[1], 798.68701, 1669.14832, 4.02860, 1000000);
	MoveObject(horseObj[2], 801.68701, 1669.14832, 4.02860, 1000000);
	MoveObject(horseObj[3], 804.68701, 1669.14832, 4.02860, 1000000);
	MoveObject(horseObj[4], 807.68701, 1669.14832, 4.02860, 1000000);

	CreateHR();
	return 1;
}
//================================[COMMANDS]====================================
	CMD:habilitarcarrera(playerid, params[])
	{
	    new msg[128];
	    format(msg, sizeof(msg), "Carreras habilitadas");
	    SendClientMessage(playerid, COLOR_RED, msg);
	    CreateHR();

	    return 1;
	}

	CMD:ayudacarrera(playerid, params[])
	{
	    new msg[128];
	    new msg1[128];
	    format(msg, sizeof(msg), "Comandos disponibles sobre carrera de caballos");
	    SendClientMessage(playerid, COLOR_YELLOW, msg);
	    format(msg1, sizeof(msg), "/infocarrera - /vercarrera - /salircarrera - /gotocarrera - /apostarcaballo");
	    SendClientMessage(playerid, COLOR_WHITE, msg1);

	    return 1;
	}

	CMD:apostarcaballo(playerid, params[])
	{
		new numHorse;
		new numBet;
	    if(sscanf(params, "ii", numHorse, numBet))
			return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /apostarcaballo [numero de caballo] [apuesta]");

		numHorse -= 1;

		if(alreadyBetHR[playerid])
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya apostaste en esta carrera.");
		if(runningHR)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Hay una carrera en progreso.");
		if(numHorse < 0 || numHorse > 4)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Ese caballo no existe.");
		if(numBet < 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La apuesta mínima es de $1.");
  		if(GetPlayerCash(playerid) < numBet)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de esa cantidad en efectivo.");

		betsHR[playerid][numHorse] = numBet;
		alreadyBetHR[playerid] = true;

		new string[128];
		new bettext[128];
		format(string, sizeof(string), "se acerca a la ventanilla y hace una apuesta.");
		cmd_me(playerid, string);
		format(bettext, sizeof(bettext), "Apostaste $%d a '%s'.", numBet, horseNames[numHorse]);
		SendClientMessage(playerid, COLOR_WHITE, bettext);

		return 1;
	}

	CMD:infocarrera(playerid, params[])
	{
		new text0[128];
		new text1[128];
		new text2[128];
		new text3[128];
		new text4[128];
  		new showTimeLeft[128];

		SendClientMessage(playerid, COLOR_RED, "Nro | Dividendo | Nombre del caballo");
		format(text0, sizeof(text0), "  1  |       2.0       | %s", horseNames[0]);
		SendClientMessage(playerid, COLOR_WHITE, text0);
		format(text1, sizeof(text0), "  2  |      2.0       | %s", horseNames[1]);
		SendClientMessage(playerid, COLOR_WHITE, text1);
		format(text2, sizeof(text0), "  3  |      3.0       | %s", horseNames[2]);
		SendClientMessage(playerid, COLOR_WHITE, text2);
		format(text3, sizeof(text0), "  4  |      5. 0      | %s", horseNames[3]);
		SendClientMessage(playerid, COLOR_WHITE, text3);
		format(text4, sizeof(text0), "  5  |      10.0    | %s", horseNames[4]);
		SendClientMessage(playerid, COLOR_WHITE, text4);

		if(!runningHR)
		{
		    new hour;
			new minute;
			new second;
			new minute2 = minuteHR;
			new second2 = secondHR;
			gettime(hour,minute,second);
			if(second > second2)
			{
				second2 += 60;
				minute2 -= 1;
			}
			second = second2 - second;
			if(minute > minute2) minute2 += 60;
			minute = minute2 - minute;

			if((minute < 5) && (minute > 0))
			{
				if(second > 9)
				{
					format(showTimeLeft, sizeof(text0), "CARTEL | La carrera arranca en %d:%d minutos |", minute, second);
					SendClientMessage(playerid, COLOR_YELLOW, showTimeLeft);
				}
				else
				{
				    format(showTimeLeft, sizeof(text0), "CARTEL | La carrera arranca en %d:%0d minutos |", minute, second);
					SendClientMessage(playerid, COLOR_YELLOW, showTimeLeft);
				}
			}
			else if (minute == 0)
			{
                format(showTimeLeft, sizeof(text0), "CARTEL | La carrera arranca en %d segundos |", second);
				SendClientMessage(playerid, COLOR_YELLOW, showTimeLeft);
    		}
    		else
    		{
               	format(showTimeLeft, sizeof(text0), "CARTEL | Los caballos estan posicionandose |", second);
				SendClientMessage(playerid, COLOR_YELLOW, showTimeLeft);
    		}
		}
		else
		{
 			format(showTimeLeft, sizeof(text0), "CARTEL | Carrera en progreso |");
			SendClientMessage(playerid, COLOR_YELLOW, showTimeLeft);
		}
		return 1;
	}

	CMD:vercarrera(playerid, params[])
	{
		TogglePlayerControllable(playerid, 0);
		SetPlayerPos(playerid, 787, 1640.1511, 55);
		SetPlayerCameraPos(playerid, 787, 1643.5, 45);
		SetPlayerCameraLookAt(playerid, 801, 1643.5, 0);
		isWatchingHR[playerid] = true;

		return 1;
	}

	CMD:salircarrera(playerid, params[])
	{
		SetPlayerPos(playerid, 787.3289, 1642.1511, 7.7802);
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
		isWatchingHR[playerid] = false;

		return 1;
	}

	CMD:gotocarrera(playerid, params[])
	{
		SetPlayerPos(playerid, 787.3289, 1642.1511, 7.7802);
		return 1;
	}
