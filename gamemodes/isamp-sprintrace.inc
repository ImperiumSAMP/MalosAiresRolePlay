#if defined _isamp_sprintrace_included
	#endinput
#endif
#define _isamp_sprintrace_included

//=================================DEFINES======================================

#define MAX_SPRINTRACE_POS      27

//==================================NEWS========================================

new /* Sistema de picadas */
	SprintRaceOffer[MAX_PLAYERS],
	SprintRaceOpponent[MAX_PLAYERS],
	SprintRaceBet[MAX_PLAYERS],
	SprintRaceCountdownSecs[MAX_PLAYERS],
	SprintRaceTimer[MAX_PLAYERS];

/* Sistema de picadas - Posiciones de llegada */
static const Float:SPRINT_RACE_POS[MAX_SPRINTRACE_POS][3] = {
    {1846.5231,-1366.7672,12.9625},
	{1820.0952,-1828.6703,12.9792},
	{1682.6759,-2163.8623,17.0619},
	{1530.0300,-1734.9821,12.9484},
	{1366.6411,-1397.9254,12.9656},
	{1020.7272,-1141.5991,23.2214},
	{1301.4172,-927.4117,39.0356},
	{898.4853,-761.1699,97.4632},
	{270.0749,-1115.5090,78.7906},
	{94.2488,-1514.7880,6.0249},
	{520.7662,-1260.1526,15.6716},
	{484.5140,-1501.8690,19.9247},
	{784.0887,-1676.9086,12.8284},
	{1079.4280,-2342.4229,11.9586},
	{1722.7888,-2687.0054,5.4470},
	{2391.5979,-2665.8567,13.0817},
	{2763.1636,-2458.6868,13.0951},
	{2836.0371,-1969.0796,10.5005},
	{2781.3474,-1045.8680,36.6520},
	{1599.3545,-1342.5320,29.6871},
	{2314.8547,-1661.9110,13.7055},
	{2592.1982,-1561.0543,8.4551},
	{2581.3362,-2180.7651,-0.6541},
	{1923.7242,-1840.4707,3.5495},
	{1617.0505,-1642.9298,13.0261},
	{1170.7081,-1570.0011,12.8763},
	{367.8909,-2038.0934,7.2342}
};

//=============================RESET VARIABLES==================================


resetSprintRace(playerid)
{
	SprintRaceOffer[playerid] = 999;
	SprintRaceOpponent[playerid] = 999;
	SprintRaceBet[playerid] = 0;
	SprintRaceCountdownSecs[playerid] = 11;
}

deleteAbandonedSprintRace(playerid)
{
	new winnerid = SprintRaceOpponent[playerid];
	
	if(winnerid != 999)
	{
	    if(SprintRaceOpponent[winnerid] == playerid)
	    {
			SendClientMessage(winnerid, COLOR_YELLOW2, "Tu contricante ha abandonado ((Desconectado)) la carrera, ganas la carrera.");
			GivePlayerCash(winnerid, SprintRaceBet[winnerid] * 2);
		    SendFMessage(playerid, COLOR_WHITE, "El organizador te entrega tus $%d de la carrera!", SprintRaceBet[winnerid] * 2);
		    SprintRaceOpponent[playerid] = 999;
		    SprintRaceOpponent[winnerid] = 999;
		    SprintRaceBet[winnerid] = 0;
		    SprintRaceBet[playerid] = 0;
		    DisablePlayerRaceCheckpoint(winnerid);
		}
	}
}

deleteFinishedSprintRace(playerid)
{
	new racerid = SprintRaceOpponent[playerid];
	
    if(racerid != 999)
	{
	    if(SprintRaceOpponent[racerid] == playerid)
	    {
		    if(racerid != INVALID_PLAYER_ID)
		    {
		        if(SprintRaceBet[racerid] == SprintRaceBet[playerid])
		        {
		            GameTextForPlayer(playerid, "Has ganado la carrera!", 1000, 3);
		            GameTextForPlayer(racerid, "Has perdido la carrera!", 1000, 3);
		            DisablePlayerRaceCheckpoint(playerid);
		            DisablePlayerRaceCheckpoint(racerid);
		    		GivePlayerCash(playerid, SprintRaceBet[racerid] * 2);
				    SendFMessage(playerid, COLOR_WHITE, "El organizador te entrega tus $%d de la carrera!", SprintRaceBet[racerid] * 2);
				    SendFMessage(racerid, COLOR_WHITE, "El organizador se queda con tus $%d de la carrera y se lo reparte al ganador!", SprintRaceBet[racerid]);
				    SprintRaceOpponent[playerid] = 999;
		 			SprintRaceOpponent[racerid] = 999;
				    SprintRaceBet[playerid] = 0;
				    SprintRaceBet[racerid] = 0;
				}
			}
		}
	}
}

//==============================SISTEMA DE PICADAS==============================

startSprintRaceChallenge(playerid)
{
	new challengerid = SprintRaceOffer[playerid],
	    moneyBet = SprintRaceBet[playerid];
	
    if(SprintRaceOpponent[playerid] != 999)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Ya estás en una carrera!");
	if(challengerid == 999 || challengerid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha desafiado a una carrera de sprint / Jugador inválido.");
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, 2337.5864,-1245.0068,22.5000))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Para aceptar un desafío, debes estar en el punto de reunión de corredores conocido como 'El Sótano'");
 	if(SprintRaceOpponent[playerid] != 999 || SprintRaceOpponent[challengerid] != 999)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Alguno de los dos está en una carrera!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || GetPlayerState(challengerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ambos deben estar de conductor en el auto con el cual correrán!");
	if(GetPlayerCash(playerid) < moneyBet || GetPlayerCash(challengerid) < moneyBet)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Alguno de los dos no tiene esa cantidad de efectivo para apostar!");
	if(!ProxDetectorS(10.0, playerid, challengerid))
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar cerca del otro corredor.");

	new content[128],
	    randomPos = random(MAX_SPRINTRACE_POS);
	    
	format(content, sizeof(content), "ha aceptado el desafío de %s a una carrera sprint por $%d.", GetPlayerNameEx(challengerid), moneyBet);
	PlayerActionMessage(playerid, 15.0, content);
	SprintRaceOpponent[playerid] = challengerid;
	SprintRaceOpponent[challengerid] = playerid;
	SprintRaceOffer[playerid] = 999;
	SprintRaceBet[challengerid] = moneyBet;
	TogglePlayerControllable(playerid, false);
	TogglePlayerControllable(challengerid, false);
	SendClientMessage(playerid, COLOR_WHITE, "Le entregas al organizador la suma acordada");
	SendClientMessage(challengerid, COLOR_WHITE, "Le entregas al organizador la suma acordada");
	GivePlayerCash(playerid, -moneyBet);
	GivePlayerCash(challengerid, -moneyBet);
	SetPlayerRaceCheckpoint(playerid, 1, SPRINT_RACE_POS[randomPos][0], SPRINT_RACE_POS[randomPos][1], SPRINT_RACE_POS[randomPos][2], 0.0, 0.0, 0.0, 4.0);
	SetPlayerRaceCheckpoint(challengerid, 1, SPRINT_RACE_POS[randomPos][0], SPRINT_RACE_POS[randomPos][1], SPRINT_RACE_POS[randomPos][2], 0.0, 0.0, 0.0, 4.0);
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "La carrera comienza en 10 segundos. Se ha marcado la ubicación de la meta en tu GPS. Preparate!");
	SendClientMessage(challengerid, COLOR_LIGHTGREEN, "La carrera comienza en 10 segundos. Se ha marcado la ubicación de la meta en tu GPS. Preparate!");
	SprintRaceTimer[challengerid] = SetTimerEx("SprintRaceCountdown", 1000, 1, "ii", challengerid, playerid);
	return 1;
}

//---------------------------SISTEMA DE PICADAS---------------------------------
//---------------------------SISTEMA DE PICADAS---------------------------------

forward SprintRaceCancelOffer(playerid);
public SprintRaceCancelOffer(playerid)
{
	if(SprintRaceOffer[playerid] != 999)
	{
	    SprintRaceOffer[playerid] = 999;
		SprintRaceBet[playerid] = 0;
	}
	return 1;
}

forward SprintRaceCountdown(racerid, racerid2);
public SprintRaceCountdown(racerid, racerid2)
{
    SprintRaceCountdownSecs[racerid] --;
	if (SprintRaceCountdownSecs[racerid] > 0)
	{
 		new sprintRaceCountdownString[8];
		format(sprintRaceCountdownString, sizeof(sprintRaceCountdownString), "%d", SprintRaceCountdownSecs[racerid]);
 		PlayerPlaySound(racerid, 1056, 0.0, 0.0, 0.0);
 		PlayerPlaySound(racerid2, 1056, 0.0, 0.0, 0.0);
		GameTextForPlayer(racerid, sprintRaceCountdownString, 500, 3);
		GameTextForPlayer(racerid2, sprintRaceCountdownString, 500, 3);
	}
	if(SprintRaceCountdownSecs[racerid] == 0)
	{
		GameTextForPlayer(racerid, "YA!!!", 500, 3);
		GameTextForPlayer(racerid2, "YA!!!", 500, 3);
		PlayerPlaySound(racerid, 1057, 0.0, 0.0, 0.0);
		PlayerPlaySound(racerid2, 1057, 0.0, 0.0, 0.0);
		TogglePlayerControllable(racerid, true);
		TogglePlayerControllable(racerid2, true);
		SprintRaceCountdownSecs[racerid] = 11;
		KillTimer(SprintRaceTimer[racerid]);
	}
	return 1;
}

CMD:desafiarpicada(playerid, params[])
{
	new racerid, moneyBet;

	if(sscanf(params, "ii", racerid, moneyBet))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /desafiarpicada [ID/Jugador] [dinero]");
    if(!IsPlayerInRangeOfPoint(playerid, 20.0, 2337.5864,-1245.0068,22.5000))
    	return SendClientMessage(playerid, COLOR_WHITE, "Para desafiar a alguien, debes ir al punto de encuentro de corredores conocido como 'El Sotano'.");
 	if(racerid == INVALID_PLAYER_ID || racerid == playerid)
 	    return SendClientMessage(playerid, COLOR_WHITE, "Jugador inválido.");
	if(SprintRaceOpponent[playerid] != 999 || SprintRaceOpponent [racerid] != 999)
	    return SendClientMessage(playerid, COLOR_WHITE, "Alguno de los dos está en una carrera!");
	if(SprintRaceOffer[playerid] != 999)
 	    return SendClientMessage(playerid, COLOR_WHITE, "Ya tienes un desafío pendiente!");
	if(SprintRaceOffer[racerid] != 999)
 	    return SendClientMessage(playerid, COLOR_WHITE, "El sujeto está con otro desafío en este instante, aguarda.");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || GetPlayerState(racerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_WHITE, "Ambos deben estar de conductor en el auto con el cual correrán!");
	if(moneyBet < 500)
 		return SendClientMessage(playerid, COLOR_WHITE, "La apuesta mínima es de $500.");
	if(GetPlayerCash(playerid) < moneyBet)
 		return SendClientMessage(playerid, COLOR_WHITE, "No tienes esa cantidad de dinero para apostar!");
	if(!ProxDetectorS(10.0, playerid, racerid))
  	    return SendClientMessage(playerid, COLOR_WHITE, "El jugador que desafiaste no está cerca tuyo.");

	SendFMessage(racerid, COLOR_LIGHTBLUE, "%s te ha desafiado a una carrera por $%d. La oferta termina en 10 segundos. Usa /aceptar picada si lo deseas.", GetPlayerNameEx(playerid), moneyBet);
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Has desafiado a %s a una carrera por $%d. La oferta termina en 10 segundos. Espera su respuesta.", GetPlayerNameEx(racerid), moneyBet);
	SprintRaceOffer[racerid] = playerid;
	SprintRaceBet[racerid] = moneyBet;
	SetTimerEx("SprintRaceCancelOffer", 10000, false, "i", racerid);
	return 1;
}
