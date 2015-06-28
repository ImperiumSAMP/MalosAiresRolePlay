#if defined _isamp_objects_included
	#endinput
#endif
#define _isamp_objects_included

//=============================OBJECT SYSTEM====================================

#define MAX_SERVER_OBJECTS   	500
#define SERVER_OBJECT_LIFETIME  300 // En minutos
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

forward DropObject(playerid, playerhand); //Deposita un objeto en el suelo y devuelve 1. Si el jugador no esta de pie retorna 0, en caso de error retorna -1
forward TakeObject(playerid, playerhand); //Toma un objecto del suelo y devuelve 1. Si el jugador no pudo tomarlo retorna 0.
forward ResetObject(pos); //Resetea los valores del índice que se le indica.
forward ServerObjectsCleaningTimer(); // Limpia los objetos con mucho tiempo de vida
forward LookObject(playerid); // Permite al jugador examinar un objeto sin agarrarlo.
forward GetClosestObject(playerid); // Devuelve el index del objeto mas cercano. Retorna -1 si no hay un objeto cercano.

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

stock DropObject(playerid, playerhand)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	if(GetHandItem(playerid, playerhand) == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No ningún item para tirar en esa mano.");
	if(GetHandItem(playerid, playerhand) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
	if(GetPVarInt(playerid, "GrupoPaintball") != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
	if(GetHandItem(playerid, playerhand) == ITEM_ID_TELEFONO_CELULAR)
   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con tu teléfono");
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
	    return SendClientMessage(playerid, COLOR_RED, "[ERROR] Se ha alcanzado el máximo de objetos permitidos, reportar a un administrador.");

	ServerObject[j][sItemID] = GetHandItem(playerid, playerhand);
	ServerObject[j][sAmount] = GetHandParam(playerid, playerhand);
	GetPlayerName(playerid, ServerObject[j][sLastPlayerName], MAX_PLAYER_NAME);
	GetPlayerPos(playerid, ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ]);
	ServerObject[j][sZ] -= 0.7;
	SetHandItemAndParam(playerid, playerhand, 0, 0);
	ServerObject[j][sRealObject] = CreateDynamicObject(GetItemObjectModel(ServerObject[j][sItemID]), ServerObject[j][sX], ServerObject[j][sY], ServerObject[j][sZ], 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    ServerObject[j][sTimeLeft] = SERVER_OBJECT_LIFETIME;
	SendFMessage(playerid, COLOR_WHITE, "Has depositado un/a %s en el suelo.", GetItemName(ServerObject[j][sItemID]) );
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

stock GetClosestObject(playerid)
{
	for(new i = 0; i < MAX_SERVER_OBJECTS; i++)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 1.4, ServerObject[i][sX], ServerObject[i][sY], ServerObject[i][sZ]))
	        return i;
	}
	return -1;
}

stock LookObject(playerid)
{
	new object = GetClosestObject(playerid);
	
	if(object == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún objeto cerca tuyo.");

	SendFMessage(playerid, COLOR_WHITE, "Examinas el objeto y ves un/a: %s - %s: %d", GetItemName(ServerObject[object][sItemID]), GetItemParamName(ServerObject[object][sItemID]), ServerObject[object][sAmount]);
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

stock TakeObject(playerid, playerhand)
{
	if(PlayerInfo[playerid][pHealth] < 25.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar un objeto agonizando.");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	if(GetPVarInt(playerid, "GrupoPaintball") != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo mientras te encuentras jugando Paintball");
	if(GetHandItem(playerid, playerhand) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar nada ya que tienes un item en esa mano.");

	new object = GetClosestObject(playerid);
	if(object == -1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningun objeto cerca tuyo.");

	SetHandItemAndParam(playerid, playerhand, ServerObject[object][sItemID], ServerObject[object][sAmount]);
	SendFMessage(playerid, COLOR_WHITE, "Has agarrado un/a %s del suelo.", GetItemName(ServerObject[object][sItemID]));
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	ResetObject(object);
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

CMD:examinar(playerid, params[])
{
	if(PlayerInfo[playerid][pHealth] < 25.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes examinar un objeto agonizando.");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes estar a pie!");
	    
	LookObject(playerid);
	return 1;
}
