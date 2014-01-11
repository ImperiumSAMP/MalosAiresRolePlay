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
	ckCarSqlId,
	ckIsOwnCar
};


new playerKeys[MAX_PLAYERS][MAX_PLAYER_KEYS][tCarKey];
new playerKeyCount[MAX_PLAYERS];

stock playerHasCarKey(playerid,carSqlId) {
	new i;
	for(i=0;i<playerKeyCount[playerid];i++)
		if(playerKeys[playerid][i][ckCarSqlId]==carId)
			return true;
	
	return false;
}

stock playerOwnsCar(playerid,carSqlId){
	new i;
	for(i=0;i<playerKeyCount[playerid];i++)
		if(playerKeys[playerid][i][ckCarSqlId]==carSqlId)
			return playerKeys[playerid][i][ckIsOwnCar];
	
	return false;
}

stock addKeyToPlayer(playerid,carSqlId,isowncar){
	if(playerKeyCount[playerid]<MAX_PLAYER_KEYS){
		new carKey[tCarKey];
		carKey[ckCarSqlId]=carSqlId;
		carKey[ckIsOwnCar]=isowncar;
		playerKeys[playerid][playerKeyCount[playerid]++]=carKey;
		
		return true;
	}
	return false;
}

stock removeKeyFromPlayer(playerid, carSqlId){
	deleteCarKeyByPlayerAndCar(tCarKey,carSqlId);
	loadPlayerCarKeys(playerid);
}

stock loadPlayerCarKeys(playerid){
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `carKeys` WHERE accountId = %d", PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnKeyListRecovered", "i", playerid);
}

forward OnKeyListRecovered(playerid);
public OnKeyListRecovered(playerid){
	new fields,i,result[128];
	cache_get_data(playerKeyCount[playerid], fields);
	for(i=0;i<playerKeyCount[playerid];i++){
		cache_get_field_content(i, "keyId", result); playerKeys[playerid][i][ckKeyId] = strval(result);
		cache_get_field_content(i, "vehId", result); playerKeys[playerid][i][ckCarSqlId] = strval(result);
		cache_get_field_content(i, "isOwnCar", result); playerKeys[playerid][i][ckIsOwnCar] = strval(result);
	}
	return 1;
}

stock savePlayerCarKeys(playerid){
	new i;
	
	for(i=0;i<playerKeyCount[playerid];i++){
		if(playerKeys[playerid][i][ckKeyId]==0)
			playerKeys[playerid][i][ckKeyId]=insertCarKey(playerid,playerKeys[playerid][i]);
		else
			updateCarKey(playerid,playerKeys[playerid][i]);
	}
}

stock insertCarKey(playerid, pKey[tCarKey]){
	new query[128];	
	format(query,sizeof(query),"INSERT INTO `carKeys` (`accountId`, `vehId`, `isOwnCar`) VALUES (%d, %d, %d)", playerid, pKey[ckCarSqlId], pKey[ckIsOwnCar]);
  	mysql_function_query(dbHandle, query, false, "", "");
	return mysql_insert_id(dbHandle);
}

stock updateCarKey(playerid, pKey[tCarKey]) {
	new query[128];	
	format(query,sizeof(query),"UPDATE `carKeys` SET `accountId` = %d, `vehId`=%d, `isOwnCar`=%d WHERE keyId=%d", playerid, pKey[ckCarSqlId], pKey[ckIsOwnCar], pkey[ckKeyId]);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock deleteCarKey(keyId) {
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carKeys` WHERE keyId=%d", keyId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

deleteCarKeyByPlayerAndCar(playerid, carSqlId){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carKeys` WHERE `accountId`= %d AND `carId`=%d", PlayerInfo[playerid][pID], keyId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}