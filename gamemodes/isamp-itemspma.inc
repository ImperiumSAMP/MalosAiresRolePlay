#if defined _isamp_itemspma_included
	#endinput
#endif
#define _isamp_itemspma_included

//=================================DEFINES======================================

#define MAX_PLAYER_CONE 		10
#define MAX_PLAYER_BARRICATE  	5
#define PMA_CONE_ITEM      		1
#define PMA_BARRICATE_ITEM    	2

//==================================NEWS========================================

new PlayerCantConos[MAX_PLAYERS];
new Conos[MAX_PLAYERS][MAX_PLAYER_CONE];
new PlayerCantBarricadas[MAX_PLAYERS];
new Barricadas[MAX_PLAYERS][MAX_PLAYER_BARRICATE];

//=============================RESET VARIABLES==================================

resetAuxiliarItemsPMA(playerid)
{
	PlayerCantConos[playerid] = 0;
	PlayerCantBarricadas[playerid] = 0;
}

deleteAuxiliarItemsPMA(playerid, item)
{
	new cant;
	switch (item)
	{
	    case PMA_CONE_ITEM:
	    {
	        cant = PlayerCantConos[playerid];
			if(cant > 0)
			{
				for(new b = 0; b < cant; b++)
				{
					DestroyDynamicObject(Conos[playerid][b]);
				}
				PlayerCantConos[playerid] = 0;
			}
		}
		case PMA_BARRICATE_ITEM:
		{
		    cant = PlayerCantBarricadas[playerid];
			if(cant > 0)
			{
				for(new b = 0; b < cant; b++)
				{
					DestroyDynamicObject(Barricadas[playerid][b]);
				}
				PlayerCantBarricadas[playerid] = 0;
			}
		}
	}
}

//=======================SISTEMA DE CONOS PARA LA PMA===========================

CMD:cono(playerid,params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	SendClientMessage(playerid, COLOR_YELLOW2, "Menú de conos policiales: /cponer /cquitar /cquitartodo.");
	return 1;
}


CMD:cponer(playerid,params[])
{
	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en servicio.");

    if(PlayerInfo[playerid][pRank] > 7)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente!");

   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");

    new cant;
	cant = PlayerCantConos[playerid];
	if( cant >= MAX_PLAYER_CONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya pusiste suficientes conos [MAX 10], quita algunos! (/cquitar) (cquitartodo).");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	cant++;
	Conos[playerid][cant-1] = CreateDynamicObject(1238, x, y, z-0.7, 0.0, 0.0, 0.0);
	SetPlayerPosFindZ(playerid, x, y-0.7, z);
	PlayerActionMessage(playerid, 15.0, "ubica un cono policial.");
	PlayerCantConos[playerid] = cant;

	return 1;
}

CMD:cquitar(playerid,params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en servicio.");

    if(PlayerInfo[playerid][pRank] > 7)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente!");

   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");

    new cant = PlayerCantConos[playerid];
	if(cant > 0)
    {
    	DestroyDynamicObject(Conos[playerid][cant-1]);
		PlayerCantConos[playerid] = cant - 1;
        PlayerActionMessage(playerid, 15.0, "retira un cono policial.");
	}
	else
		return SendClientMessage(playerid, COLOR_YELLOW2, "No has puesto conos!");

	return 1;
}

CMD:cquitartodo(playerid, params[])
{
    if( (PlayerInfo[playerid][pFaction] == FAC_PMA && CopDuty[playerid] == 1 && PlayerInfo[playerid][pRank] < 8 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) || AdminDuty[playerid] )
    {
		if( (PlayerInfo[playerid][pRank] == 1) || AdminDuty[playerid] )
		{
		    for(new i = 0; i < MAX_PLAYERS; i++)
		    {
		        deleteAuxiliarItemsPMA(i, PMA_CONE_ITEM);
			}
			SendFactionMessage(FAC_PMA, COLOR_FACTIONCHAT, "(( [AVISO OOC]: El comisario ha quitado todos los conos puestos por la facción. ))");
		} else
		    {
				deleteAuxiliarItemsPMA(playerid, PMA_CONE_ITEM);
				SendClientMessage(playerid, COLOR_WHITE, "Retiras cualquier cono que hayas puesto.");
			}
	} else
		if (PlayerInfo[playerid][pFaction] == FAC_PMA)
			SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener al menos rango de oficial, estar en servicio y de pie.");
	return 1;
}

//=====================SISTEMA DE BARRICADAS DE LA PMA==========================

CMD:barricada(playerid,params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	SendClientMessage(playerid, COLOR_YELLOW2, "Menú de barricadas policiales: /bponer /bquitar /bquitartodo.");
	return 1;
}


CMD:bponer(playerid,params[])
{
	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en servicio.");

    if(PlayerInfo[playerid][pRank] > 7)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente!");

   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");

    new cant;
	cant = PlayerCantBarricadas[playerid];
	if( cant >= MAX_PLAYER_BARRICATE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya pusiste suficientes barricadas [MAX 5], quita algunas! (/bquitar) (bquitartodo).");
	new Float:x, Float:y, Float:z, Float:facingAngle;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, facingAngle);
	cant++;
	Barricadas[playerid][cant-1] = CreateDynamicObject(1459, x, y, z-0.7, 0.0, 0.0, facingAngle);
	SetPlayerPosFindZ(playerid, x, y-0.7, z);
	PlayerActionMessage(playerid, 15.0, "ubica una barricada policial.");
	PlayerCantBarricadas[playerid] = cant;

	return 1;
}

CMD:bquitar(playerid,params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
        return 1;

	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No estás en servicio.");

    if(PlayerInfo[playerid][pRank] > 7)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente!");

   	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que estar a pie.");

    new cant = PlayerCantBarricadas[playerid];
	if(cant > 0)
    {
    	DestroyDynamicObject(Barricadas[playerid][cant-1]);
		PlayerCantBarricadas[playerid] = cant - 1;
        PlayerActionMessage(playerid, 15.0, "retira una barricada policial.");
	}
	else
		return SendClientMessage(playerid, COLOR_YELLOW2, "No has puesto barricadas!");

	return 1;
}

CMD:bquitartodo(playerid, params[])
{
    if( (PlayerInfo[playerid][pFaction] == FAC_PMA && CopDuty[playerid] == 1 && PlayerInfo[playerid][pRank] < 8 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) || AdminDuty[playerid] )
    {
		if( (PlayerInfo[playerid][pRank] == 1) || AdminDuty[playerid] )
		{
		    for(new i = 0; i < MAX_PLAYERS; i++)
		    {
      			deleteAuxiliarItemsPMA(i, PMA_BARRICATE_ITEM);
			}
			SendFactionMessage(FAC_PMA, COLOR_FACTIONCHAT, "(( [AVISO OOC]: El comisario ha quitado todas las barricadas puestas por la facción. ))");
		} else
		    {
				deleteAuxiliarItemsPMA(playerid, PMA_BARRICATE_ITEM);
				SendClientMessage(playerid, COLOR_YELLOW2, "Retiras cualquier barricada que hayas puesto.");
			}
	} else
		if (PlayerInfo[playerid][pFaction] == FAC_PMA)
			SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener al menos rango de oficial, estar en servicio y de pie.");
	return 1;
}
