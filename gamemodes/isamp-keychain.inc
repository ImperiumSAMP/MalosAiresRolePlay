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

stock updateCarOwnerName(playerid){
	new i,vehicleid;

	for(i=0;i<playerKeyCount[playerid];i++){
		vehicleid=playerKeys[playerid][i][ckCarSqlId];
		if(playerOwnsCar(playerid,vehicleid))
		{
			format(VehicleInfo[vehicleid][VehOwnerName], 24, "%s", GetPlayerNameEx(playerid));
			SaveVehicle(vehicleid);
		}
	}
}

stock calculateVehiclesTaxes(playerid) {
	new tax=0,i;
	
	for(i=0;i<playerKeyCount[playerid];i++)
		tax += GetVehiclePrice(playerKeys[playerid][i][ckCarSqlId], 1) / 4;
	
	return tax;
}

stock playerHasCarKey(playerid,carId) {
	new i;
	for(i=0;i<playerKeyCount[playerid];i++)
		if(playerKeys[playerid][i][ckCarSqlId]==carId)
			return true;
	
	return false;
}

stock playerOwnsCar(playerid,carId){
	new i;
	for(i=0;i<playerKeyCount[playerid];i++)
		if(playerKeys[playerid][i][ckCarSqlId]==carId)
			return playerKeys[playerid][i][ckOwner]==getPlayerMysqlId(playerid);
	
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
	loadPlayerCarKeys(playerid);
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
			insertCarKey(getPlayerMysqlId(playerid),playerKeys[playerid][i],i);
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
	format(query,sizeof(query),"INSERT INTO `carkeys` (`accountId`, `vehId`, `ownerId`) VALUES (%d, %d, %d)", playerid, newKey[ckCarSqlId], newKey[ckOwner]);
  	mysql_function_query(dbHandle, query, true, "OnKeyInserted", "ii", playerid,keyNum);
}

stock updateCarKey(playerid, newKey[tCarKey]) {
	new query[128];	
	format(query,sizeof(query),"UPDATE `carkeys` SET `accountId` = %d, `vehId`=%d, `ownerId`=%d WHERE keyId=%d", playerid, newKey[ckCarSqlId], newKey[ckOwner], newKey[ckKeyId]);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock deleteKeysForCar(carid){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE vehId=%d", carid);
  	mysql_function_query(dbHandle, query, false, "", "");
}

stock deleteCarKey(keyId) {
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE keyId=%d", keyId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

deleteCarKeyByPlayerAndCar(playerid, carSqlId){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carkeys` WHERE `accountId`= %d AND `carId`=%d", getPlayerMysqlId(playerid), carSqlId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock listPlayerKeys(playerid){
	new i, line[64];
	
	if(playerKeyCount[playerid]==0)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No tienes ninguna llave en tu llavero");
	
	PlayerActionMessage(playerid, 15.0, "saca del bolisllo un manojo de llaves y revuelve entre las mismas...");
	
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}Posees las siguientes llaves:{C8C8C8}");
	
	for(i=0;i<playerKeyCount[playerid];i++){
		format(line,sizeof(line),"{5CCAF1}%d{C8C8C8} - %s",i+1,getVehicleDescription(playerKeys[playerid][i][ckCarSqlId]));
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, line);
	}
	
	return 1;
}

stock playerGiveKeyToPlayer(playerid,keyid,user){
	new message[128],
		receiverName[MAX_PLAYER_NAME],
		vehicleid;
	
	if(keyid < 0 || keyid >= playerKeyCount[playerid]) //Me fijo que el tipo tenga llaves, sino revienta todo :D
		return SendClientMessage(playerid, COLOR_YELLOW, "Llave no válida");
	
	if(user == INVALID_PLAYER_ID || user == playerid || !ProxDetectorS(2.0, playerid, user))
		return SendClientMessage(playerid, COLOR_YELLOW, "El usuario no es válido o se encuentra muy lejos");
			
	vehicleid=playerKeys[playerid][keyid][ckCarSqlId];
	
	if(!playerOwnsCar(playerid,vehicleid))
		return SendClientMessage(playerid, COLOR_YELLOW, "El vehiculo no te pertenece");
		
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

stock printCarKeys(playerid) {
	new i;
	if(playerKeyCount[playerid]>0){
		SendClientMessage(playerid, COLOR_LIGHTYELLOW, "============================[Llaves]===========================");
		for(i=0;i<playerKeyCount[playerid];i++)
			SendFMessage(playerid, COLOR_WHITE,	"%s", getVehicleDescription(playerKeys[playerid][i][ckCarSqlId]));		
	}
	return 1;	
}


CMD:llavero(playerid, params[]) {
	new subCmd[16],keyId,user;
	
	if(sscanf(params,"s[16]",subCmd)==0 && strcmp(subCmd,"ver",true)==0)
		return listPlayerKeys(playerid);
	else if(sscanf(params,"s[16]iu",subCmd,keyId,user)==0 && strcmp(subCmd,"darcopia",true)==0)			
		return playerGiveKeyToPlayer(playerid,keyId-1,user);

	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /llavero ver | {5CCAF1}[O]:{C8C8C8} /llavero darcopia [nroLlave] [ID/ParteDelNombre]");
	return 1;	
}
