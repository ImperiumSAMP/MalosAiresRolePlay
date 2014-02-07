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
	pDonateRank,
	pAccountBlocked,
	pTutorial,
	pRegStep,
	pSex,
	pAge,
	pExp,
	pCash,
	pBank,
	pSkin,
	pMaterials,
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
	pSpawnPoint,//If pSpawnPoint = 1, then the user will spawn at there normal place, if it's 0 then they will spawn at there home.
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
	pProducts,
	Float:pX,
	Float:pY,
	Float:pZ,
	Float:pA,
	pInterior,
	pVirtualWorld,
	pVeh1,
	pVeh2,
	pOrigin,
	pHospitalized,
	Float:pHealth,
	Float:pArmour,
	pSpectating,
	pPoints,
	pWantedLevel,
	pCantWork,
	pAccusedOf[64],
	pAccusedBy[24],
	
	pMuteB,
	pRentCarID,
	pRentCarRID,
	pCigarettes,
	pLighter,
	pFightStyle,
	pMask,
	
	Float:pAdictionPercent,
	pAdictionAbstinence,
	pMarijuana,
	pLSD,
	pEcstasy,
	pCocaine
};
new PlayerInfo[MAX_PLAYERS][pInfo];

enum Inv {
	inv0[16],
	inv1[16],
};

new InvInfo[MAX_PLAYERS][Inv];

stock getPlayerMysqlId(playerid){
	return PlayerInfo[playerid][pID];
}

stock isPlayerJailed(playerid){
	return PlayerInfo[playerid][pJailed];
}
