#if defined _isamp_npc_included
	#endinput
#endif
#define _isamp_npc_included

//=================================DEFINES======================================

//==================================NEWS========================================

new
	ColectivoAmarilloIda = 24,
	ColectivoAmarilloVuelta = 25,
	ColectivoRojoIda = 21,
    ColectivoRojoVuelta = 23,
    ColectivoVerdeIda = 26,
    ColectivoVerdeVuelta = 27;

//=============================RESET VARIABLES==================================

//=============================SISTEMA DE NPCS==================================

stock LoadNPCS()
{
	ConnectNPC("NPCColAmarilloIda", "LineaAmarillaIda");
	ConnectNPC("NPCColAmarilloVuelta", "LineaAmarillaVuelta");
	ConnectNPC("NPCColRojoIda", "LineaRojaIda");
	ConnectNPC("NPCColRojoVuelta", "LineaRojaVuelta");
	ConnectNPC("NPCColVerdeIda", "LineaVerdeIda");
	ConnectNPC("NPCColVerdeVuelta", "LineaVerdeVuelta");
}

forward SetNPCInVehicle(playerid, vehicleid);
public SetNPCInVehicle(playerid, vehicleid)
{
    PutPlayerInVehicle(playerid, vehicleid, 0);
    return 1;
}

spawnNPC(playerid)
{
	new npcname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, npcname, sizeof(npcname));
	
	if(!strcmp(npcname, "NPCColAmarilloIda", true))
	{
	    SetPlayerSkin(playerid, 253);
	    SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
	    SetTimerEx("SetNPCInVehicle", 1000, false, "ii", playerid, ColectivoAmarilloIda);
	} else
    if(!strcmp(npcname, "NPCColRojoIda", true))
    {
   		SetPlayerSkin(playerid, 253);
   		SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
   		SetTimerEx("SetNPCInVehicle", 30000, false, "ii", playerid, ColectivoRojoIda);
    } else
    if(!strcmp(npcname, "NPCColVerdeIda", true))
    {
   		SetPlayerSkin(playerid, 253);
   		SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
   		SetTimerEx("SetNPCInVehicle", 60000, false, "ii", playerid, ColectivoVerdeIda);
    } else
    if(!strcmp(npcname, "NPCColAmarilloVuelta", true))
    {
   		SetPlayerSkin(playerid, 253);
   		SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
   		SetTimerEx("SetNPCInVehicle", 90000, false, "ii", playerid, ColectivoAmarilloVuelta);
    } else
    if(!strcmp(npcname, "NPCColRojoVuelta", true))
    {
   		SetPlayerSkin(playerid, 253);
   		SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
   		SetTimerEx("SetNPCInVehicle", 120000, false, "ii", playerid, ColectivoRojoVuelta);
    } else
    if(!strcmp(npcname, "NPCColVerdeVuelta", true))
    {
   		SetPlayerSkin(playerid, 253);
   		SetPlayerPos(playerid, 1950.0131, 1782.1285, 18.9046);
   		SetTimerEx("SetNPCInVehicle", 150000, false, "ii", playerid, ColectivoVerdeVuelta);
    }
}
