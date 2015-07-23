#if defined _isamp_players_included
	#endinput
#endif
#define _isamp_players_included


//====[ENUMS AND PLAYERS ARRAY]=====================================

enum pInfo {
	pID,
	pName[24],
	pKey[128],
	pIP[16],
	pLevel,
	pAdmin,
	pAccountBlocked,
	pTutorial,
	pRegStep,
	pSex,
	pAge,
	pExp,
	pCash,
	pBank,
	pSkin,
	pJob,
	pJobTime,
	pJobAllowed, // Si tiene job de facción no lo puede dejar.
	pPlayingHours,
	pLastConnected[25],
	pPayCheck,
	pFaction,
	pRank,
	pHouseKey,
	pBizKey,
	pWarnings,
	pCarLic,
	pFlyLic,
	pWepLic,
	pPhoneNumber,
	pPhoneC,//Phone Company (Business ID)
	pPhoneBook,
	pListNumber,
	pJailed,
	pJailTime,
	Float:pX,
	Float:pY,
	Float:pZ,
	Float:pA,
	pInterior,
	pVirtualWorld,
	pVeh1,
	pVeh2,
	pHospitalized,
	Float:pHealth,
	Float:pArmour,
	pSpectating,
	pWantedLevel,
	pCantWork,
	pAccusedOf[64],
	pAccusedBy[24],
 	pMuteB,
	pRentCarID,
	pRentCarRID,
	pFightStyle,
	pMask,
	
	pThirst,
	pHunger,
	
	Float:pAdictionPercent,
	pAdictionAbstinence,
	pMarijuana,
	pLSD,
	pEcstasy,
	pCocaine,
	
	pTakeInputs,
	
	pHouseKeyIncome,
	pRolePoints,
	
	pContainerSQLID,
	pContainerID,
};

new PlayerInfo[MAX_PLAYERS][pInfo];

// Inmunidad al anticheat
new antiCheatImmunity[MAX_PLAYERS];

stock getPlayerMysqlId(playerid){
	return PlayerInfo[playerid][pID];
}
