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

stock updateCarOwnerName(playerid,name[]){
	new i,vehicleid;

	for(i=0;i<playerKeyCount[playerid];i++){
		vehicleid=playerKeys[playerid][i][ckCarSqlId];
		if(VehicleInfo[vehicleid][VehOwnerSQLID] == getPlayerMysqlId(playerid))
		{
			memcpy(VehicleInfo[vehicleid][VehOwnerName], name,0,MAX_PLAYER_NAME);
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
	format(query,sizeof(query),"INSERT INTO `carkeys` (`accountId`, `vehId`, `ownerId`) VALUES (%d, %d, %d,'%s')", playerid, newKey[ckCarSqlId], newKey[ckOwner]);
  	mysql_function_query(dbHandle, query, true, "OnKeyInserted", "ii", playerid,keyNum);
}

stock updateCarKey(playerid, newKey[tCarKey]) {
	new query[128];	
	format(query,sizeof(query),"UPDATE `carKeys` SET `accountId` = %d, `vehId`=%d, `ownerId`=%d WHERE keyId=%d", playerid, newKey[ckCarSqlId], newKey[ckOwner], newKey[ckKeyId]);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock deleteKeysForCar(carid){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carKeys` WHERE vehId=%d", carid);
  	mysql_function_query(dbHandle, query, false, "", "");
}

stock deleteCarKey(keyId) {
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carKeys` WHERE keyId=%d", keyId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

deleteCarKeyByPlayerAndCar(playerid, carSqlId){
	new query[128];	
	format(query,sizeof(query),"DELETE FROM `carKeys` WHERE `accountId`= %d AND `carId`=%d", getPlayerMysqlId(playerid), carSqlId);
  	mysql_function_query(dbHandle, query, false, "", "");	
}

stock listPlayerKeys(playerid){
	new i, line[64];
	
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}Posees las siguientes llaves:{C8C8C8}");
	
	for(i=0;i<playerKeyCount[playerid];i++){
		format(line,sizeof(line),"{5CCAF1}%d{C8C8C8} - %s",i+1,getVehicleDescription(playerKeys[playerid][i][ckCarSqlId]));
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, line);
	}
}

stock playerGiveKeyToPlayer(playerid,keyid,user){
	return 0;
}

stock printCarKeys(playerid) {
	new i;
	if(playerKeyCount[playerid]>0){
		SendClientMessage(playerid, COLOR_LIGHTYELLOW, "============================[Llaves]===========================");
		for(i=0;i<playerKeyCount[playerid];i++)
			SendFMessage(playerid, COLOR_WHITE,	"%s", getVehicleDescription(playerKeys[playerid][i][ckCarSqlId]));		
	}
	return 0;	
}


CMD:llaves(playerid, params[]) {
	new subCmd[16],keyId,user;
	
	if(sscanf(params,"s[16]",subCmd)==0)
	{
		if(strcmp(subCmd,"listar",true)==0) 
		{
			listPlayerKeys(playerid);
			return 1;
		} else {
			if(strcmp(subCmd,"dar")==0)
			{
				if(sscanf(params,"s[16]iu",subCmd,keyId,user)==0)
				{
					playerGiveKeyToPlayer(playerid,keyId,user);
					return 1;
				}
			}
		}
	}
	
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /llaves listar | {5CCAF1}[O]:{C8C8C8} /llaves dar [IDLlave] [ID/ParteDelNombre]");
	
	return 1;	
}
