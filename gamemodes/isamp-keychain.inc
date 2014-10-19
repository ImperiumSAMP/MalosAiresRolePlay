#if defined _keychain_included
	#endinput
#endif
#define _keychain_included

/**
* Isamp KeyChain by Nevermore
* This script implements a keychain where user can store borrowed car keys
**/

#define MAX_PLAYER_KEYS 10

enum tCarKey {
	ckKeyId,
	ckOwner,
	ckCarSqlId
};


new playerKeys[MAX_PLAYERS][MAX_PLAYER_KEYS][tCarKey];
new playerKeyCount[MAX_PLAYERS];

stock updateCarOwnerName(playerid)
{
	new vehicleid;

	for(new i = 0; i < playerKeyCount[playerid]; i++)
	{
		vehicleid = playerKeys[playerid][i][ckCarSqlId];
		if(playerKeys[playerid][i][ckOwner] == getPlayerMysqlId(playerid)) // Dueño
		{
			format(VehicleInfo[vehicleid][VehOwnerName], MAX_PLAYER_NAME, "%s", GetPlayerNameEx(playerid));
			SaveVehicle(vehicleid);
		}
	}
}

stock calculateVehiclesTaxes(playerid)
{
	new tax = 0;
	
	for(new i = 0; i < playerKeyCount[playerid]; i++)
	{
		if(playerKeys[playerid][i][ckOwner] == getPlayerMysqlId(playerid)) // Dueño
			tax += GetVehiclePrice(playerKeys[playerid][i][ckCarSqlId], 1) / 4;
   	}
	return tax;
}

stock GetPlayerOwnedCarsAmount(playerid)
{
	new aux = 0;

	for(new i = 0; i < playerKeyCount[playerid]; i++)
	{
		if(playerKeys[playerid][i][ckOwner] == getPlayerMysqlId(playerid))
			aux ++;
	}
 	return aux;
}

stock playerHasCarKey(playerid, carId)
{
	for(new i = 0; i < playerKeyCount[playerid]; i++)
	{
		if(playerKeys[playerid][i][ckCarSqlId] == carId)
			return true;
	}
	return false;
}

stock playerOwnsCar(playerid, carId)
{
	for(new i = 0; i < playerKeyCount[playerid]; i++)
	{
		if(playerKeys[playerid][i][ckCarSqlId] == carId)
			return playerKeys[playerid][i][ckOwner] == getPlayerMysqlId(playerid);
	}
	return false;
}

stock addKeyToPlayer(playerid,carId,ownerId){	
	new carKey[tCarKey];
	carKey[ckCarSqlId]=getVehicleSqlId(carId);
	carKey[ckOwner]=getPlayerMysqlId(ownerId);
	playerKeys[playerid][playerKeyCount[playerid]++]=carKey;
	savePlayerCarKeys(playerid);
	return true;
}

stock getPlayerFreeKeySlots(playerid) {
	return MAX_PLAYER_KEYS-playerKeyCount[playerid];
}

stock removeKeyFromPlayer(playerid, carId){
	deleteCarKeyByPlayerAndCar(playerid,getVehicleSqlId(carId));
}

stock loadPlayerCarKeys(playerid){
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `carkeys` WHERE accountId = %d", getPlayerMysqlId(playerid));
	mysql_function_query(dbHandle, query, true, "OnKeyListRecovered", "i", playerid);
}

forward OnKeyListRecovered(playerid);
public OnKeyListRecovered(playerid){
	new fields,i,result[128];
	cache_get_data(playerKeyCount[playerid], fields);
	for(i=0;i<playerKeyCount[playerid];i++){
		cache_get_field_content(i, "keyId", result); playerKeys[playerid][i][ckKeyId] = strval(result);
		cache_get_field_content(i, "vehId", result); playerKeys[playerid][i][ckCarSqlId] = strval(result);
		cache_get_field_content(i, "ownerId", result); playerKeys[playerid][i][ckOwner] = strval(result);
		//cache_get_field_content(i, "keyLabel", playerKeys[playerid][i][ckLabel],1,32);
	}
	return 1;
}

stock savePlayerCarKeys(playerid){
	new i;
	
	for(i=0;i<playerKeyCount[playerid];i++){
		if(playerKeys[playerid][i][ckKeyId]==0)
			insertCarKey(playerid,playerKeys[playerid][i],i);
		else
			updateCarKey(playerid,playerKeys[playerid][i]);
	}
}

forward OnKeyInserted(playerid,keyNum);
public OnKeyInserted(playerid,keyNum){
	playerKeys[playerid][keyNum][ckKeyId]=cache_insert_id();
}

stock insertCarKey(playerid, newKey[tCarKey], keyNum){
	new query[128];	
	format(query,sizeof(query),"INSERT INTO `carkeys` (`accountId`, `vehId`, `ownerId`) VALUES (%d, %d, %d)", getPlayerMysqlId(playerid), newKey[ckCarSqlId], newKey[ckOwner]);
  	mysql_function_query(dbHandle, query, true, "OnKeyInserted", "ii", playerid,keyNum);
}

stock updateCarKey(playerid, newKey[tCarKey]) {
	new query[128];	
	format(query,sizeof(query),"UPDATE `carkeys` SET `accountId` = %d, `vehId`=%d, `ownerId`=%d WHERE keyId=%d", getPlayerMysqlId(playerid), newKey[ckCarSqlId], newKey[ckOwner], newKey[ckKeyId]);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock reloadAllKeysForCar(vehicleid){
	foreach(new playerid : Player)
		if(playerHasCarKey(playerid,vehicleid))
			loadPlayerCarKeys(playerid);
}

stock deleteKeysForCar(carid){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE vehId=%d", carid);
  	mysql_function_query(dbHandle, query, true, "OnKeysDeleted", "i",carid);
}

stock deleteExtraKeysForCar(carid){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE vehId=%d and ownerId<>accountId", carid);
  	mysql_function_query(dbHandle, query, true, "OnKeysDeleted", "i",carid);
}

stock deleteCarKey(keyId) {
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE keyId=%d", keyId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

deleteCarKeyByPlayerAndCar(playerid, carSqlId){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE `accountId`= %d AND `vehId`=%d", getPlayerMysqlId(playerid), carSqlId);
  	mysql_function_query(dbHandle, query, true, "OnKeyDeleted", "i", playerid);	
}

forward OnKeyDeleted(playerid);
public OnKeyDeleted(playerid){
	loadPlayerCarKeys(playerid);
}

forward OnKeysDeleted(vehicleid);
public OnKeysDeleted(vehicleid){
	reloadAllKeysForCar(vehicleid);
}

stock listPlayerKeys(playerid){
	new i, line[64];
	
	if(playerKeyCount[playerid]==0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No tienes ninguna llave en tu llavero");

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}Posees las siguientes llaves:{C8C8C8}");
	
	for(i=0;i<playerKeyCount[playerid];i++){
		format(line,sizeof(line),"{5CCAF1}%d{C8C8C8} - %s [%d]",i+1,getVehicleDescription(playerKeys[playerid][i][ckCarSqlId]),playerKeys[playerid][i][ckCarSqlId]);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, line);
	}
	
	return 1;
}

stock playerGiveKeyToPlayer(playerid,keyid,user){
	new message[128],
		receiverName[MAX_PLAYER_NAME],
		vehicleid;
	
	if(keyid < 0 || keyid >= playerKeyCount[playerid]) //Me fijo que el tipo tenga llaves, sino revienta todo :D
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} Llave no válida.");
	
	if(user == INVALID_PLAYER_ID || user == playerid || !ProxDetectorS(2.0, playerid, user))
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} El usuario no es válido o se encuentra muy lejos.");
			
	vehicleid = playerKeys[playerid][keyid][ckCarSqlId];
	
	if(!playerOwnsCar(playerid,vehicleid))
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} El vehiculo no te pertenece.");
		
 	if(playerHasCarKey(user, vehicleid))
     	return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} El usuario ya posee una llave de este vehículo.");

	//Le doy la llave
	addKeyToPlayer(user,vehicleid,playerid);
	
	//Le cuento al mundo
	receiverName=GetPlayerNameEx(user);
	format(message,128,"entrega una llave a %s",receiverName);
	PlayerActionMessage(playerid, 15.0, message);
	SendFMessage(user, COLOR_WHITE, "¡Has recibido una llave del %s!", getVehicleDescription(vehicleid));
	SendFMessage(playerid,COLOR_LIGHTYELLOW2,"Le has dado una llave de tu %s a %s",GetVehicleName(vehicleid),receiverName);
	
	return 1;
}

stock printCarKeys(playerid,target) {
	new i;
	if(playerKeyCount[target]>0){
		SendClientMessage(playerid, COLOR_LIGHTYELLOW, "============================[Llaves]===========================");
		for(i=0;i<playerKeyCount[target];i++)
			SendFMessage(playerid, COLOR_WHITE,	"[%d] %s", playerKeys[target][i][ckCarSqlId],getVehicleDescription(playerKeys[target][i][ckCarSqlId]));		
	}
	return 1;	
}


CMD:llavero(playerid, params[])
{
	new
		subCmd[16],
		keyId,
		user;
	
	if(!sscanf(params, "s[16]", subCmd) && !strcmp(subCmd, "ver", true))
		return listPlayerKeys(playerid);

	else if(!sscanf(params, "s[16]i", subCmd, keyId) && !strcmp(subCmd, "desechar", true))
 	{
 	    new vehicleid = playerKeys[playerid][keyId-1][ckCarSqlId];
		if(playerOwnsCar(playerid, vehicleid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes desechar una llave del auto que eres dueño.");
		removeKeyFromPlayer(playerid, vehicleid);
		SendFMessage(playerid, COLOR_WHITE, "Has desechado la llave Nro %d", keyId);
	}
	
	else if(!sscanf(params, "s[16]iu", subCmd, keyId, user) && !strcmp(subCmd, "darcopia", true))
		return playerGiveKeyToPlayer(playerid, keyId-1, user);

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /llavero [comando]");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} ver - desechar [nroLlave] - darcopia [nroLlave] [ID/Jugador]");
	return 1;
}
