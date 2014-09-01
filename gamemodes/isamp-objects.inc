#if defined _isamp_objects_included
	#endinput
#endif
#define _isamp_objects_included

//=============================OBJECT SYSTEM====================================

#define MAX_SERVER_OBJECTS   500

//==============================DATA STORAGE====================================

enum ObjectsInfo {
	sItemID, //almacena la id de la tabla de objetos
	sAmount, //almacena la cantidad del objeto(parámetro para armas y etcétera)
	Float:sX, //coordenada X
	Float:sY, //coordenada Y
	Float:sZ, //coordenada Z
	sLastPlayerName[MAX_PLAYER_NAME], //Almacena el nombre del jugador que tiró el objeto ((futuro sist de investigación de huellas)
	sRealObject
};

new ServerObject[MAX_SERVER_OBJECTS][ObjectsInfo];

//==============================FUNCIONES=======================================

forward DropObject(playerid); //Deposita un objeto en el suelo y devuelve 1. Si el jugador no esta de pie retorna 0, en caso de error retorna -1
forward TakeObject(playerid); //Toma un objecto del suelo y devuelve 1. Si el jugador no pudo tomarlo retorna 0.
forward ResetObject(pos); //Resetea los valores del índice que se le indica.

//=======================IMPLEMENTACIÓN DE FUNCIONES============================


stock DropObject(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return 0;
	if(GetHandItem(playerid) != 0)
	{
	    new j = -1;
		new playerName[MAX_PLAYER_NAME];
		for(new i = 0; i < MAX_SERVER_OBJECTS; i++)
		{
			if(ServerObject[i][sItemID] == 0)
			{
				j = i;
				break;
			}
		}
		if(j == -1)
		{
		    SendClientMessage(playerid, COLOR_RED, "[ERROR] Se ha alcanzado el máximo de objetos permitidos, reportar a un administrador");
		    return -1;
		}
		ServerObject[j][sItemID] = GetHandItem(playerid);
		ServerObject[j][sAmount] = GetHandParam(playerid);
		GetPlayerName(playerid, playerName, sizeof(playerName));

		ServerObject[j][sLastPlayerName] = playerName;
		GetPlayerPos(playerid, ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ]);
		ServerObject[j][sZ] = ServerObject[j][sZ] - 0.7;
		SetHandItemAndParam(playerid, 0, 0);
		DeleteItemFromHand(playerid);
		ServerObject[j][sRealObject] = CreateDynamicObject(GetItemModelObject(ServerObject[j][sItemID]), ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ], 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		SendFMessage(playerid, COLOR_WHITE, "Has depositado un/a %s en el suelo", GetItemName(ServerObject[j][sItemID]) );
		ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock TakeObject(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	    return 0;
	}
	if(GetHandItem(playerid) != 0)
	{
		SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el objeto ya que tienes algo en tus manos.");
		return 0;
	}
	new j = -1;
	for(new i = 0; i < MAX_SERVER_OBJECTS; i++)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 1.4, ServerObject[i][sX], ServerObject[i][sY], ServerObject[i][sZ]) )
	    {
	        j = i;
			break;
		}
	}
	if(j == -1)
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningun objeto cerca tuyo.");
	    return 0;
	}
	SetHandItemAndParam(playerid, ServerObject[j][sItemID], ServerObject[j][sAmount]);
	LoadHandItem(playerid);
	SendFMessage(playerid, COLOR_WHITE, "Has agarrado un/a %s del suelo", GetItemName(ServerObject[j][sItemID]) );
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	ResetObject(j);
	return 1;
}
	
stock ResetObject(pos)
{
    ServerObject[pos][sItemID] = 0;
    ServerObject[pos][sAmount] = 0;
    ServerObject[pos][sX] = 0.0;
    ServerObject[pos][sY] = 0.0;
    ServerObject[pos][sZ] = 0.0;
    //ServerObject[pos][sLastPlayerName] = "NULL";
	DestroyDynamicObject(ServerObject[pos][sRealObject]);
	return 1;
}

//================================COMANDOS======================================

CMD:agarrarobjeto(playerid, params[])
{
	if(PlayerInfo[playerid][pHealth] < 25.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar un objeto agonizando.");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	TakeObject(playerid);
	return 1;
}
	

		
		

