#if defined _isamp_util_included
	#endinput
#endif
#define _isamp_util_included


//====[FUNCTION ALIASES AND SHORTCUTS DEFINITION]=====================================

#define TIMER:%1(%2) forward %1(%2); public %1(%2)

//COMIENZO lime de Never
#define ALIASFOR:%1(%2,%3);\
	forward cmd_%2(%3); \
	public cmd_%2(%3) \
	{ \
		return cmd_%1(%3); \
	}

//FIN lime de Never

#define SendFMessage(%0,%1,%2,%3)                               do{new _str[150]; format(_str,150,%2,%3); SendClientMessage(%0,%1,_str);}while(FALSE)
#define SendFMessageToAll(%1,%2,%3)                             do{new _str[190]; format(_str,150,%2,%3); SendClientMessageToAll(%1,_str);}while(FALSE)


//====[COLOR DEFINES]=================================================================
#define COLOR_FACTIONCHAT 		0x7BDDA5AA
#define COLOR_CORLEONE 			0x212121AA
#define COLOR_RIGHTHAND_DONS 	0xA10000AA
#define COLOR_BARZINI 			0x00FF00AA
#define COLOR_PATERNO 			0x800080AA
#define COLOR_TATTAGLIA 		0xD3D300AA
#define COLOR_STRACCI 			0x0FD9FAAA
#define COLOR_PMA				0x9FAAC7AA
#define COLOR_FBI 				0x191970AA
#define COLOR_NATIONALGUARD 	0x556B2FAA
#define COLOR_CIVILIAN 			0xFFFFFFAA

// Chat.
#define COLOR_GLOBALOOC         0x87CEFAFF
#define COLOR_AOOC              0x3CB371FF
#define COLOR_MP                0x5F9EA0FF
//
#define COLOR_EVENT             0x4F76F7FF
#define COLOR_ADMINQUESTION     0xFF9500AA
#define COLOR_ACHAT             0xE8934DFF
#define COLOR_LOCALMSG		 	0xEC5413AA
#define COLOR_ADMINCMD 			0x2EBFC7FF
#define COLOR_ADMINDUTY 		0x20AB66FF
#define COLOR_NOTLOGGED   		0x7F7272AA
#define	COLOR_MONEYBAR 			0x005800FF
#define COLOR_GRAD1 			0xB4B5B7FF
#define COLOR_GRAD2 			0xBFC0C2FF
#define COLOR_GRAD3 			0xCBCCCEFF
#define COLOR_GRAD4 			0xD8D8D8FF
#define COLOR_GRAD5 			0xE3E3E3FF
#define COLOR_DO1 				0x9BCE31FF
#define COLOR_DO2 				0x9BD033FF
#define COLOR_DO3 				0x9BD235FF
#define COLOR_DO4 				0x9BD437FF
#define COLOR_DO5 				0x9DD639FF
#define COLOR_ACT1 				0xBE85D8FF
#define COLOR_ACT2 				0xBE85D8D9
#define COLOR_ACT3 				0xBE85D8BB
#define COLOR_ACT4 				0xBE85D895
#define COLOR_ACT5 				0xBE85D86C
#define COLOR_GREY     			0xC8C8C8FF
#define COLOR_GREEN 			0x33AA33AA
#define COLOR_RED 				0xE44A4AFF
#define COLOR_DARKRED 			0xCD000000
#define COLOR_ANTICHEAT 		0xAA3333AA
#define COLOR_LIGHTRED 			0xFF6347AA
#define COLOR_LIGHTBLUE   		0x87CEFAFF
#define COLOR_LIGHTGREEN 		0x9ACD32AA
#define COLOR_LIGHTRED 			0xFF6347AA
#define COLOR_LIGHTBLUE2 		0x0080FFAA
#define COLOR_LIGHTORANGE 		0xFF8000FF
#define COLOR_DARKBROWN 		0xB36C42FF
#define COLOR_MEDIUMBLUE 		0x1ED5C7FF
#define COLOR_LIGHTYELLOW 		0xE0E377AA
#define COLOR_LIGHTYELLOW2 		0xE0EA64AA
#define COLOR_LIGHTYELLOW3 		0xFF6347AA
#define COLOR_DARKPURPLE 		0x5F56F8AA
#define COLOR_YELLOW 			0xFFFF00AA
#define COLOR_YELLOW2 			0xF5DEB3AA
#define COLOR_YELLOW3 			0xF5DEB3CC
#define COLOR_WHITE 			0xE0E0E0AA
#define COLOR_FADE1 			0xE6E6E6E6
#define COLOR_FADE2 			0xC8C8C8C8
#define COLOR_FADE3 			0xAAAAAAAA
#define COLOR_FADE4 			0x8C8C8C8C
#define COLOR_FADE5 			0x6E6E6E6E
#define COLOR_PURPLE 			0xC2A2DAAA
#define COLOR_DBLUE 			0x2641FEAA
#define COLOR_ALLDEPT 			0xFF8282AA
#define COLOR_NEWS 				0xFFA500AA
#define COLOR_OOC 				0xE0FFFFAA
#define COLOR_NEWOOC 			0x0080FFAA

//SKINS
#define SKINS_M_1    114
#define SKINS_M_2    39
#define SKINS_F_1    37
#define SKINS_F_2    14

// Disables.
#define DISABLE_NONE            0
#define DISABLE_FREEZE          1
#define DISABLE_TAZER           2
#define DISABLE_DYING           3
#define DISABLE_STEALING        4
#define DISABLE_DEATHBED        5



new validWeatherIDs[2] = {
	1,2/*,-3,4,5,6,7,9,10,11,12,13,14,15,17,18,20-*/
};

new SkinRegMale[18][1] = {
	{3},{6},{4},{7},{15},{19},{20},{22},{23},{26},{30},{32},{35},{36},{37},{38},{43},{44}
};

new SkinRegFemale[12][1] = {
	{40},{41},{54},{56},{69},{89},{91},{157},{191},{192},{193},{194}
};

new maleSkins1[SKINS_M_1] = {
	1,2,4,5,6,7,14,15,18,19,20,21,22,23,24,25,26,28,29,30,32,35,36,
	37,43,44,45,47,48,51,52,58,60,62,66,67,73,78,79,86,94,95,96,97,98,
	100,101,102,103,104,105,106,107,108,109,110,114,115,116,121,122,128,132,
	133,134,135,136,137,142,154,156,168,170,174,175,176,177,179,180,181,182,
	183,184,188,202,206,210,212,213,217,220,221,222,229,230,234,235,236,241,242,
	247,248,250,252,253,254,258,259,261,262,273,291,292,293
};

new maleSkins2[SKINS_M_2] = {
	3,17,49,57,59,61,68,72,111,112,113,117,118,119,120,123,124,125,126,127,147,153,
	163,164,165,166,171,185,186,187,208,223,227,228,272,294,295,296,299
};

new femaleSkins1[SKINS_F_1] = {
 	10,11,12,31,38,39,40,41,52,53,55,56,63,64,65,75,77,87,88,89,90,93,129,130,131,
 	138,139,140,151,152,190,191,195,207,211,225,298
};

new femaleSkins2[SKINS_F_2] = {
	12,76,91,141,150,169,172,192,194,214,215,216,219,224
};

//Enums
enum sInfo {
	sVehiclePricePercent,
	sHousePricePercent,
	sPlayersRecord,
	sMOTD[128],
	svLevelExp,
	sDrugRawMats
};
new ServerInfo[sInfo];

new Choice[MAX_PLAYERS];
