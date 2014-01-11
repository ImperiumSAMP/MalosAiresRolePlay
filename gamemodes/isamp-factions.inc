#if defined _isamp_factions_included
	#endinput
#endif
#define _isamp_factions_included

//Defines
#define MAX_FACTIONS            20

//====[FACCIONES]===============================================================
#define FAC_NONE                0
#define FAC_PMA                 1 		// Policía Metropolitana.
#define FAC_HOSP                2
#define FAC_FORZ                3
#define FAC_CHIN                4
#define FAC_BERT                5
#define FAC_MAN                 6
#define FAC_MECH                7
#define FAC_RIV                	8
#define FAC_BOCA               	9
#define FAC_SIDE                10


//Enums
enum Factions {
	fName[50],
	fMaterials,
	fDrugs,
	fBank,
	fRank1[35],
	fRank2[35],
	fRank3[35],
	fRank4[35],
	fRank5[35],
	fRank6[35],
	fRank7[35],
	fRank8[35],
	fRank9[35],
	fRank10[35],
	fSkin1,
	fSkin2,
	fSkin3,
	fSkin4,
	fSkin5,
	fSkin6,
	fSkin7,
	fSkin8,
	fSkin9,
	fSkin10,
	fJoinRank,
	fUseSkins,
	fType,//For Government factions etc
	fRankAmount,
	fAllowJob,
	fMissionVeh,
};

new FactionInfo[MAX_FACTIONS][Factions];

