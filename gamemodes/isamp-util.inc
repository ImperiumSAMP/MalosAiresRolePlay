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
#define COLOR_ADMINDUTY         0xF3280084
//
#define COLOR_EVENT             0x4F76F7FF
#define COLOR_ADMINQUESTION     0xFF0000BB
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
#define COLOR_DO1 				0xFFAD98FF
#define COLOR_DO2 				0xFFAD98FF
#define COLOR_DO3 				0xFFAD98FF
#define COLOR_DO4 				0xFFAD98FF
#define COLOR_DO5     			0xFFAD98FF
#define COLOR_ACT1 				0xBE85D8FF
#define COLOR_ACT2 				0xBE85D8D9
#define COLOR_ACT3 				0xBE85D8BB
#define COLOR_ACT4 				0xBE85D895
#define COLOR_ACT5 				0xBE85D86C
#define COLOR_GREY     			0xC8C8C8FF
#define COLOR_GREEN 			0x33AA33AA
#define COLOR_RED 				0xE44A4AFF
#define COLOR_BLUE              0x0000BBAA
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
#define COLOR_DEEPWHITE			0xFFFFFFFF
#define COLOR_FADE1 			0xE6E6E6E6
#define COLOR_FADE2 			0xC8C8C8C8
#define COLOR_FADE3 			0xAAAAAAAA
#define COLOR_FADE4 			0x8C8C8C8C
#define COLOR_FADE5 			0x6E6E6E6E
#define COLOR_FADEG1 			0xE60000E6
#define COLOR_FADEG2 			0xD20000D2
#define COLOR_FADEG3 			0xBE0000BE
#define COLOR_FADEG4 			0xAA0000AA
#define COLOR_FADEG5 			0x96000096
#define COLOR_PURPLE 			0xC2A2DAAA
#define COLOR_DBLUE 			0x2641FEAA
#define COLOR_ALLDEPT 			0xFF8282AA
#define COLOR_NEWS 				0xFFA500AA
#define COLOR_OOC 				0xE0FFFFAA
#define COLOR_NEWOOC 			0x0080FFAA
#define COLOR_ADVERTISMENT      0xEEBC00FF
#define COLOR_ADMINREAD         0x00B400DC

//SKINS
#define SKINS_M_1    129
#define SKINS_M_2    69
#define SKINS_F_1    55
#define SKINS_F_2    25

// Disables.
#define DISABLE_NONE            0
#define DISABLE_FREEZE          1
#define DISABLE_TAZER           2
#define DISABLE_DYING           3
#define DISABLE_STEALING        4
#define DISABLE_DEATHBED        5
#define DISABLE_HEALING         6

// Jails
#define JAIL_NONE           	0
#define JAIL_IC_PMA         	1
#define JAIL_OOC            	2
#define JAIL_IC_PRISON     		3
#define JAIL_IC_GOB         	4

//====[TIPOS DE LOGS]===========================================================
#define LOG_ADMIN            	1
#define LOG_MONEY            	2
#define LOG_CHAT                3

new SkinRegMale[18][1] = {
	{3},{6},{4},{7},{15},{19},{20},{22},{23},{26},{30},{32},{35},{36},{37},{38},{43},{44}
};

new SkinRegFemale[12][1] = {
	{40},{41},{54},{56},{69},{89},{91},{157},{191},{192},{193},{194}
};

new maleSkins1[SKINS_M_1] = {
	1,2,4,5,6,7,8,14,15,16,18,19,21,22,23,26,27,28,29,30,
	32,35,36,37,42,44,45,47,48,49,50,51,52,58,60,62,66,67,72,73,
	78,79,80,81,86,94,95,96,97,101,102,103,104,105,106,107,108,109,110,114,
	115,116,173,174,175,121,122,128,132,133,134,135,136,137,142,143,144,146,149,154,
	155,156,158,159,160,161,162,167,168,170,176,179,180,181,182,183,188,200,202,206,
	209,210,212,213,220,222,229,230,234,235,236,239,241,242,250,252,260,261,262,264,
	268,269,271,273,289,291,292,293,297
};

new maleSkins2[SKINS_M_2] = {
	3,17,20,24,25,33,34,43,46,57,
	59,61,68,82,83,84,98,100,111,112,
	113,117,118,119,120,123,124,125,126,127,
	147,153,163,164,165,166,171,177,184,185,
	186,187,189,203,204,208,217,221,223,227,
	228,240,247,248,249,253,254,255,258,259,
	272,290,294,295,296,299,303,304,305
};

new femaleSkins1[SKINS_F_1] = {
	10,13,31,38,39,41,53,54,56,63,
	64,65,69,75,77,87,88,89,90,129,
	130,131,138,139,140,145,151,152,157,178,
	190,191,192,193,195,196,197,198,201,205,
	207,218,226,231,232,237,238,243,244,245,
	246,251,256,257,298
};

new femaleSkins2[SKINS_F_2] = {
	9,11,12,40,55,76,85,91,93,141,
	148,150,169,172,194,199,211,214,215,216,
	219,224,225,233,263
};

//Enums
enum sInfo {
	sVehiclePricePercent,
	sPlayersRecord,
	svLevelExp,
	sDrugRawMats
};
new ServerInfo[sInfo];

new Choice[MAX_PLAYERS],
	Mobile[MAX_PLAYERS],
	bool:AdminDuty[MAX_PLAYERS],
	bool:AdminPMsEnabled[MAX_PLAYERS],
	bool:AdminWhispersEnabled[MAX_PLAYERS],
	bool:AdminFactionEnabled[MAX_PLAYERS],
	bool:AdminSMSEnabled[MAX_PLAYERS],
	bool:Admin911Enabled[MAX_PLAYERS];
	
// Sistema de toggle
new bool:PhoneEnabled[MAX_PLAYERS],
	bool:PMsEnabled[MAX_PLAYERS],
	bool:NewsEnabled[MAX_PLAYERS],
	bool:NicksEnabled[MAX_PLAYERS],
	bool:RadioEnabled[MAX_PLAYERS],
	bool:FactionEnabled[MAX_PLAYERS],
	bool:TalkAnimEnabled[MAX_PLAYERS],
	bool:HudEnabled[MAX_PLAYERS],
	bool:AdminEnabled[MAX_PLAYERS];

// sistema de mascaras
new bool:usingMask[MAX_PLAYERS];
