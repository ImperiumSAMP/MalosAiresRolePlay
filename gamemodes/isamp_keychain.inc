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
	tKeyId,
	tCarId,
	tIsOwnCar
};


new playerKeys[MAX_PLAYERS][MAX_PLAYER_KEYS][tCarKey];
new playerKeyCount[MAX_PLAYERS];

stock playerHasCarKey(playerid,carId) {}

stock loadPlayerCarKeys(playerid){}

stock savePlayerCarKeys(playerid){}

stock insertCarKey(playerid, pKey[tCarKey]){}

stock updateCarKey(playerid, pKey[tCarKey]) {}