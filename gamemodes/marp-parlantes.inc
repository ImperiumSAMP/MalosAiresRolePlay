#if defined _marp_parlantes_included
	#endinput
#endif
#define _marp_parlantes_included

//===============================CONSTANTES=====================================

#define VEC_TYPE_SPEAKER  			1000

#define VEC_INDEX_TYPE          0
#define VEC_INDEX_AREA          1
#define VEC_INDEX_OBJECT        2
#define VEC_INDEX_X             3
#define VEC_INDEX_Y             4
#define VEC_INDEX_Z             5
#define VEC_INDEX_VWORLD        6
#define VEC_INDEX_RADIO         7
#define VEC_INDEX_VOLUME        8

//==================================DATA========================================

static const SERVER_RADIOS[][128] = {

/*0*/	"NONE",
/*1*/	"http://buecrplb01.cienradios.com.ar/Mitre790.mp3",
/*2*/	"http://pub8.sky.fm/sky_classicrap?26d5dea1edd974aa0d4b8d94", //nueva
/*3*/	"http://pub8.sky.fm/sky_modernrock?26d5dea1edd974aa0d4b8d94", //nueva
/*4*/	"http://movidamix.com:8128/listen.pls",
/*5*/	"http://buecrplb01.cienradios.com.ar/Palermo_2.mp3",
/*6*/	"http://buecrplb01.cienradios.com.ar/fm979.mp3",
/*7*/	"http://buecrplb01.cienradios.com.ar/la100_mdq.mp3",
/*8*/	"http://pub3.sky.fm/sky_bossanova?26d5dea1edd974aa0d4b8d94", //nueva
/*9*/	"http://pub2.sky.fm/sky_tophits?26d5dea1edd974aa0d4b8d94", //nueva
/*10*/	"http://stream.electroradio.ch:26630",//nueva
/*11*/	"http://95.141.24.173:80/listen.pls",
/*12*/	"http://pub3.sky.fm:80/sky_modernblues?26d5dea1edd974aa0d4b8d94", // nueva
/*13*/	"http://serverstreamgroup.biz:8112/stream?type=.fl", //nueva
/*14*/	"http://streaming.radionomy.com/CUMBIAPARATODOSyCADENAMIX?type=flash", //nueva
/*15*/	"http://streaming.radionomy.com/CTRMAN", //radio CTR
/*16*/	"http://streaming.radionomy.com/MIXLA128KB" //juance

};

new SERVER_SPEAKERS;

//==============================IMPLEMENTACION==================================

InitializeServerSpeakers()
{
	SERVER_SPEAKERS = vector_create();
}

CreateSpeaker(Float:x, Float:y, Float:z, Float:angle, vworld, modelid, radio, volume = 45)
{
	new id = vector_create();

 	vector_push_back(id, VEC_TYPE_SPEAKER);
	vector_push_back(id, CreateDynamicSphere(x, y, z, volume, vworld));
	vector_push_back(id, CreateDynamicObject(modelid, x, y, z - 1, 0.0, 0.0, angle + 180, vworld));
	vector_push_back_float(id, x);
	vector_push_back_float(id, y);
	vector_push_back_float(id, z);
	vector_push_back(id, vworld);
	vector_push_back(id, radio);
	vector_push_back(id, volume);
	
	vector_push_back(SERVER_SPEAKERS, id);
	
	return id;
}

IsValidSpeaker(speaker_id)
{
	if(speaker_id > 0 && vector_size(speaker_id) > 8 && vector_get(speaker_id, VEC_INDEX_TYPE) == VEC_TYPE_SPEAKER)
		return 1;
	else
	    return 0;
}

DestroySpeaker(speaker_id)
{
	if(IsValidSpeaker(speaker_id))
	{
	    foreach(new i : Player)
		{
			if(IsPlayerInDynamicArea(i, vector_get(speaker_id, VEC_INDEX_AREA)))
			{
			    StopAudioStreamForPlayer(i);
			}
		}
		DestroyDynamicObject(vector_get(speaker_id, VEC_INDEX_OBJECT));
		DestroyDynamicArea(vector_get(speaker_id, VEC_INDEX_AREA));
		vector_destroy(speaker_id);
		vector_remove(SERVER_SPEAKERS, vector_find(SERVER_SPEAKERS, speaker_id));
		return 1;
	}
	return 0;
}

PlaySpeakerForPlayer(playerid, speaker_id)
{
	if(IsValidSpeaker(speaker_id))
	{
		PlayAudioStreamForPlayer(playerid, SERVER_RADIOS[vector_get(speaker_id, VEC_INDEX_RADIO)], vector_get_float(speaker_id, VEC_INDEX_X), vector_get_float(speaker_id, VEC_INDEX_Y), vector_get_float(speaker_id, VEC_INDEX_Z), vector_get(speaker_id, VEC_INDEX_VOLUME), 1);
	 	return 1;
	}
	return 0;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	//Busco el parlante que esté en esa área
	
	new vsize = vector_size(SERVER_SPEAKERS),
	    speaker_id;

	for(new i = 0; i < vsize; i++)
	{
	    speaker_id = vector_get(SERVER_SPEAKERS, i);
	    if(vector_get(speaker_id, VEC_INDEX_AREA) == areaid)
	    {
	        if(!hearingRadioStream[playerid])
	        {
			    PlaySpeakerForPlayer(playerid, speaker_id);
			}
		}
	}
	//======================================
	
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	//Busco el parlante que esté en esa área

	new vsize = vector_size(SERVER_SPEAKERS),
	    speaker_id;

	for(new i = 0; i < vsize; i++)
	{
	    speaker_id = vector_get(SERVER_SPEAKERS, i);
	    if(vector_get(speaker_id, VEC_INDEX_AREA) == areaid)
	    {
	        if(!hearingRadioStream[playerid])
	        {
			    StopAudioStreamForPlayer(playerid);
			}
		}
	}
	//======================================

	return 1;
}

//================================COMANDOS======================================

CMD:parlante(playerid, params[])
{
	new radio;

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /parlante [radio] (1-16). Se ubicará el equipo en el piso, reproduciendo la radio elegida.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
	if(GetHandItem(playerid, HAND_RIGHT) != ITEM_ID_PARLANTE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un equipo de música portátil en condiciones en tu mano derecha.");
	if(radio < 1 || radio > 16)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio válida: del 1 al 16.");

	new vsize = vector_size(SERVER_SPEAKERS),
	    speaker_id;

	for(new i = 0; i < vsize; i++)
	{
	    speaker_id = vector_get(SERVER_SPEAKERS, i);
	    if(IsPlayerInRangeOfPoint(playerid, vector_get(speaker_id, VEC_INDEX_VOLUME) * 2 + 20, vector_get_float(speaker_id, VEC_INDEX_X), vector_get_float(speaker_id, VEC_INDEX_Y), vector_get_float(speaker_id, VEC_INDEX_Z)))
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "[OOC]: Hay otro equipo de música activo en la cercanía, aléjate más o busca otro lugar");
	}

	new Float:px, Float:py, Float:pz, Float:pangle;
	GetPlayerPos(playerid, px, py, pz);
	GetPlayerFacingAngle(playerid, pangle);

	PlayerActionMessage(playerid, 15.0, "apoya un equipo portátil de música en el piso y lo prende.");
	ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
	SendClientMessage(playerid, COLOR_WHITE, "[INFO]: Has puesto un equipo de música prendido en el piso. Para levantarlo utiliza /tomarparlante.");
	CreateSpeaker(px, py, pz, pangle, GetPlayerVirtualWorld(playerid), GetItemObjectModel(GetHandItem(playerid, HAND_RIGHT)), radio);
	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	return 1;
}

CMD:tomarparlante(playerid, params[])
{
	new freehand = SearchFreeHand(playerid);
	if(freehand == -1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar ningún ítem.");

	new vsize = vector_size(SERVER_SPEAKERS),
	    speaker_id;

	for(new i = 0; i < vsize; i++)
	{
	    speaker_id = vector_get(SERVER_SPEAKERS, i);
	    if(GetPlayerVirtualWorld(playerid) == vector_get(speaker_id, VEC_INDEX_VWORLD))
	    {
		    if(IsPlayerInRangeOfPoint(playerid, 1.5, vector_get_float(speaker_id, VEC_INDEX_X), vector_get_float(speaker_id, VEC_INDEX_Y), vector_get_float(speaker_id, VEC_INDEX_Z)))
		    {
				DestroySpeaker(speaker_id);
				PlayerActionMessage(playerid, 15.0, "apaga el equipo de música y lo agarra.");
				ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0);
				SetHandItemAndParam(playerid, freehand, ITEM_ID_PARLANTE, 1);
				return 1;
			}
		}
	}
	SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún equipo de música activo cerca tuyo.");
	return 1;
}

