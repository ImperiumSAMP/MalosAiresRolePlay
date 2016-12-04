#if defined _marp_streamings_included
	#endinput
#endif
#define _marp_streamings_included

//===============================CONSTANTES=====================================

#define RADIO_TYPE_NONE         0
#define RADIO_TYPE_VEH          1
#define RADIO_TYPE_SPEAKER      2
#define RADIO_TYPE_HOUSE        3
#define RADIO_TYPE_BIZ          4
#define RADIO_TYPE_BLD          5

//==================================DATA========================================

new SERVER_RADIOS[][128] = {

/*0*/	"NONE",
/*1*/	"http://buecrplb01.cienradios.com.ar/Mitre790.mp3",
/*2*/	"http://buecrplb01.cienradios.com.ar/Palermo_2.mp3",
/*3*/	"http://buecrplb01.cienradios.com.ar/fm979.mp3",
/*4*/	"http://buecrplb01.cienradios.com.ar/la100_mdq.mp3",
/*5*/	"http://s_mobile.cienradios.com/la100.mp3",
/*6*/	"http://s_mobile.cienradios.com/Hot_100_Nacional_48.mp3",
/*7*/	"http://s_mobile.cienradios.com/Grandes_Del_Rock_48.mp3",
/*8*/	"http://s_mobile.cienradios.com/AC_DC_y_Artistas_Relacionados_48.mp3",
/*9*/	"http://s_mobile.cienradios.com/Bachata_48.mp3",
/*10*/	"http://stream.electroradio.ch:26630",
/*11*/	"http://s_mobile.cienradios.com/Bailando_Electro_48.mp3",
/*12*/	"http://s_mobile.cienradios.com/Fiesta_Dance_48.mp3",
/*13*/	"http://s_mobile.cienradios.com/Hot_100_Reggaeton_48.mp3",
/*14*/	"http://streaming.radionomy.com/MIXLA128KB",
/*15*/	"http://streaming.radionomy.com/CTRMAN",
/*16*/	"http://s_mobile.cienradios.com/Cumbia_48.mp3",
/*17*/	"http://s_mobile.cienradios.com/Cuarteto_48.mp3",
/*18*/	"http://s_mobile.cienradios.com/Folklore_48.mp3",
/*19*/  "http://streamcasthd.com:26353/"

};

enum e_streaming {
	e_id,
	e_type,
};

new player_streaming[MAX_PLAYERS][e_streaming];

stock Radio_GetId(playerid)
{
	return player_streaming[playerid][e_id];
}
	
stock Radio_GetType(playerid)
{
	return player_streaming[playerid][e_type];
}

Radio_IsOn(playerid)
{
	return (player_streaming[playerid][e_id] && player_streaming[playerid][e_type]);
}

Radio_IsOnType(playerid, type)
{
	return (player_streaming[playerid][e_id] && player_streaming[playerid][e_type] == type);
}

Radio_GetAmount()
{
	return sizeof(SERVER_RADIOS);
}

Radio_Set(playerid, id, type)
{
	player_streaming[playerid][e_id] = id;
	player_streaming[playerid][e_type] = type;
	PlayAudioStreamForPlayer(playerid, SERVER_RADIOS[id]);
}

Radio_SetEx(playerid, id, type, Float:x, Float:y, Float:z, Float:radius)
{
	player_streaming[playerid][e_id] = id;
	player_streaming[playerid][e_type] = type;
	PlayAudioStreamForPlayer(playerid, SERVER_RADIOS[id], x, y, z, radius, 1);
}

Radio_Stop(playerid)
{
	Radio_Reset(playerid);
    StopAudioStreamForPlayer(playerid);
}

Radio_Reset(playerid)
{
	player_streaming[playerid][e_id] = 0;
	player_streaming[playerid][e_type] = 0;
}
