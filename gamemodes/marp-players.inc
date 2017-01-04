#if defined _marp_players_included
	#endinput
#endif
#define _marp_players_included


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
	pCurrentHouse,
	pCurrentBiz,
	pCurrentBuilding,
	pBizKey,
	pWarnings,
	pCarLic,
	pBikeLic,
	pFlyLic,
	pWepLic,
	pPhoneNumber,
	pPhoneC,
	pPhoneBook,
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

new PlayerInfo[MAX_PLAYERS][pInfo],
	gPlayerLogged[MAX_PLAYERS];

// Inmunidad al anticheat
new bool:antiCheatDisabled[MAX_PLAYERS];

stock getPlayerMysqlId(playerid){
	return PlayerInfo[playerid][pID];
}
