#if defined _isamp_objects_included
	#endinput
#endif
#define _isamp_objects_included

//=============================OBJECT SYSTEM====================================

#define MAX_SERVER_OBJECTS   	500
#define SERVER_OBJECT_LIFETIME  240 // En minutos
#define SERVER_OBJECT_UPD_TIME  10 // Cada diez minutos

//==============================DATA STORAGE====================================

enum ObjectsInfo {
	sItemID, //almacena la id de la tabla de objetos
	sAmount, //almacena la cantidad del objeto(parámetro para armas y etcétera)
	Float:sX, //coordenada X
	Float:sY, //coordenada Y
	Float:sZ, //coordenada Z
	sLastPlayerName[MAX_PLAYER_NAME], //Almacena el nombre del jugador que tiró el objeto ((futuro sist de investigación de huellas)
	sRealObject,
	sTimeLeft
};

new ServerObject[MAX_SERVER_OBJECTS][ObjectsInfo];

//==============================FUNCIONES=======================================

forward DropObject(playerid); //Deposita un objeto en el suelo y devuelve 1. Si el jugador no esta de pie retorna 0, en caso de error retorna -1
forward TakeObject(playerid); //Toma un objecto del suelo y devuelve 1. Si el jugador no pudo tomarlo retorna 0.
forward ResetObject(pos); //Resetea los valores del índice que se le indica.
forward ServerObjectsCleaningTimer(); // Limpia los objetos con mucho tiempo de vida

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

public ServerObjectsCleaningTimer()
{
	for(new i = 0; i < MAX_SERVER_OBJECTS; i++)
	{
	    if(ServerObject[i][sItemID] > 0)
	    {
	        if(ServerObject[i][sTimeLeft] > 0)
	            ServerObject[i][sTimeLeft] -= SERVER_OBJECT_UPD_TIME;
			else
			    ResetObject(i);
		}
	}
	return 1;
}

stock DropObject(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	if(GetHandItem(playerid) == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tu mano.");
	    
 	new j = -1;
	for(new i = 0; i < MAX_SERVER_OBJECTS; i++)
	{
		if(ServerObject[i][sItemID] == 0)
		{
			j = i;
			break;
		}
	}
	if(j == -1)
	    return SendClientMessage(playerid, COLOR_RED, "[ERROR] Se ha alcanzado el máximo de objetos permitidos, reportar a un administrador");

	ServerObject[j][sItemID] = GetHandItem(playerid);
	ServerObject[j][sAmount] = GetHandParam(playerid);
	GetPlayerName(playerid, ServerObject[j][sLastPlayerName], MAX_PLAYER_NAME);
	GetPlayerPos(playerid, ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ]);
	ServerObject[j][sZ] -= 0.7;
	SetHandItemAndParam(playerid, 0, 0);
	DeleteHandItem(playerid);
	ServerObject[j][sRealObject] = CreateDynamicObject(GetItemObjectModel(ServerObject[j][sItemID]), ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ], 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    ServerObject[j][sTimeLeft] = SERVER_OBJECT_LIFETIME;
	SendFMessage(playerid, COLOR_WHITE, "Has depositado un/a %s en el suelo", GetItemName(ServerObject[j][sItemID]) );
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

stock TakeObject(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	if(GetHandItem(playerid) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el objeto ya que tienes algo en tus manos.");
		
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
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningun objeto cerca tuyo.");

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
    ServerObject[pos][sTimeLeft] = 0;
    strmid(ServerObject[pos][sLastPlayerName], "NULL", 0, strlen("NULL"), MAX_PLAYER_NAME);
	if(ServerObject[pos][sRealObject] > 0)
	{
		DestroyDynamicObject(ServerObject[pos][sRealObject]);
		ServerObject[pos][sRealObject] = 0;
	}
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
