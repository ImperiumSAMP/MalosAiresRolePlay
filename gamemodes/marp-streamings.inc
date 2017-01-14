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
/*1*/	"http://radio.revoltparty.org:9000/dnb",
/*2*/	"http://82.163.78.59:8066/",
/*3*/	"http://camon01.dehost24.eu:9990/",
/*4*/	"http://buecrplb01.cienradios.com.ar/la100_mdq.mp3",
/*5*/	"http://camon01.dehost24.eu:9996/",
/*6*/	"http://listen.shoutcast.com/hot977fm.m3u",
/*7*/	"http://hemnos.cdnstream.com/1442_128",
/*8*/	"https://stream.radio.co/s1b65fa6d5/listen",
/*9*/	"http://radio.ohmylatino.com/bachata.mp3",
/*10*/	"http://107.182.234.82:8300/",
/*11*/	"http://s_mobile.cienradios.com/779_Cumbia_48.mp3",
/*12*/	"http://107.182.234.82:8218/",
/*13*/	"http://hestia2.cdnstream.com/1249_128",
/*14*/	"http://listen.radionomy.com/flameonradioclassichiphopnow.m3u",
/*15*/	"http://www.wohradio.com:27015/listen.pls",
/*16*/	"http://212.83.150.15:8022/",
/*17*/	"http://streaming.radio.co/s258f7b690/listen",
/*18*/	"http://s_mobile.cienradios.com/675_Hot_100_Reggaeton_48.mp3",
/*19*/  "http://s1.streamaudio.de:8000/destroy-society-radio",
/*20*/	"http://centova.orsradio.com:8052/",
/*21*/	"http://yp.shoutcast.com/sbin/tunein-station.pls?id=192203",
/*22*/	"http://cc.net2streams.com:8557/",
/*23*/	"http://usa14.fastcast4u.com:5072/",
/*24*/	"http://s_mobile.cienradios.com/575_80_Nacional_48.mp3",
/*25*/	"http://s_mobile.cienradios.com/784_Viejitos_Piolas_48.mp3",
/*26*/	"http://s_mobile.cienradios.com/1124_Trending_Topic_48.mp3",
/*27*/	"http://listen.radionomy.com/RadioOlympia-dot-org.m3u",
/*28*/	"http://vpr.net/vpr_files/stream_playlists/vprclassicalhigh.pls",
/*29*/	"http://184.173.142.117:7128/stream",
/*30*/	"http://107.182.234.82:8194/",
/*31*/	"http://djboyradio.streamguys1.com/alligator-records.mp3",
/*32*/	"http://37.251.146.169:7800/stream?1465938594190.mp3",
/*33*/	"http://listen.radionomy.com/canazed",
/*34*/	"http://192.99.8.192:2762/stream/;*.mp3",
/*35*/	"http://yp.shoutcast.com/sbin/tunein-station.pls?id=143365",
/*36*/	"http://yp.shoutcast.com/sbin/tunein-station.pls?id=1034744",
/*37*/	"http://streams.bigfm.de/bigfm-reggaevibes-128-mp3",
/*38*/  "http://live3.istoikona.net:8152/live",
/*39*/	"http://50.7.77.115:8199/stream",
/*40*/  "http://streaming.radionomy.com/ChicanoRap-TalkBox-FunkRadio"

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
