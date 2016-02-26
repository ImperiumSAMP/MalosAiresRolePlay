#if defined _isamp_animations_included
	#endinput
#endif
#define _isamp_animations_included

//--------------------------------ANIMACIONES-----------------------------------
//--------------------------------ANIMACIONES-----------------------------------

CMD:anim(playerid, params[]) {
	cmd_animaciones(playerid, params);
	return 1;
}

CMD:animaciones(playerid, params[])
{
    SendClientMessage(playerid, COLOR_LIGHTYELLOW, "[Animaciones]:");
	SendClientMessage(playerid, COLOR_GREY, "/acabar - /acomer - /afumar - /alentar - /alpiso - /apoyarse - /apreton - /apuntar - /arrastrarse");
	SendClientMessage(playerid, COLOR_GREY, "/arrojar - /aspirar - /bailar - /barman - /bate - /besar - /bomba - /bondi - /borracho - /caminar");
	SendClientMessage(playerid, COLOR_GREY, "/cbrazos - /chasis - /chocado - /chupala - /crack - /cubrirse - /dealer - /dormir - /enojado");
	SendClientMessage(playerid, COLOR_GREY, "/entregar - /geofanims - /hablar - /levantarbrazos - /manosarriba - /mear - /mirar - /muerte");
	SendClientMessage(playerid, COLOR_GREY, "/nockeado - /oral - /orar - /pagando - /paja - /pasartarjeta - /pudrete - /quebrar - /quepaso");
	SendClientMessage(playerid, COLOR_GREY, "/rapear - /reanimar - /reir - /saltar - /sentarse - /sentarsenigga - /taichi - /tantear - /taxi");
	SendClientMessage(playerid, COLOR_GREY, "/tirarse - /vigilar - /abeber - /estirarse - /ponermascara - /codazo - /lavarmanos - /pesas");
	SendClientMessage(playerid, COLOR_GREY, "/teclear - /rodar - /cansado - /brazoventanilla /noanim");
	return 1;
}

CMD:noanim(playerid, params[]) {
	new animlib[32];
	new animname[32];
	new msg[128];
 	GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
 	format(msg, 128, "%s %s", animlib, animname);
 	if(!strcmp(msg,"PED FALL_FALL"))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar el comando en este momento!");
	else if(!strcmp(msg,"PED FALL_BACK"))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar el comando en este momento!");
	else if(!strcmp(msg,"PED FALL_FRONT"))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar el comando en este momento!");
    else if(!strcmp(msg,"PED FALL_GLIDE"))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar el comando en este momento!");
	if(GetPVarInt(playerid, "disabled") == DISABLE_NONE && GetPlayerState(playerid) == 1) {
		ClearAnimations(playerid);
		TogglePlayerControllable(playerid, 1);
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	}
	return 1;
}


CMD:muerte(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /muerte [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "KNIFE", "knife_hit_3", 4.1, 0, 1, 1, 1, 1, 1);
	}
	return 1;
}

CMD:levantarbrazos(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /levantarbrazos [1-3]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "GHANDS", "gsign2", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimation(playerid, "GHANDS", "GSIGN1", 4.1, 1, 0, 0, 0, 0); // /levantarbrazos
	}
	return 1;
}

CMD:hablar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /hablar [1-4]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "GHANDS", "gsign5", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkF", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimation(playerid, "MISC", "Idle_Chat_02", 4.1, 1, 0, 0, 0, 0, 0); // PRUEBA
		case 4: ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.0, 1, 1, 1, 0, 0); // PRUEBA PARAMETROS
 	}
 	return 1;
}

CMD:chasis(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /chasis [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "CAR", "Fixn_Car_Out", 4.1, 0, 1, 1, 1, 1, 1);
	}
	return 1;
}

CMD:bondi(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "PED", "abseil", 4.1, 0, 0, 0, 1, 0);
	return 1;
}

CMD:saltar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "DODGE", "Crush_Jump", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:apoyarse(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /apoyarse [1-4]");
 	switch(anim)
 	{
    	case 1: ApplyAnimation(playerid, "MISC", "Plyrlean_loop", 4.1, 0, 0, 0, 1, 0);
    	case 2: ApplyAnimation(playerid, "GANGS", "LEANIDLE", 4.0, 0, 0, 0, 1, 0); // /apoyarse
    	case 3: ApplyAnimation(playerid, "GANGS", "LEANIN", 4.0, 0, 0, 0, 1, 0); // /apoyarse3 ApplyAnimation(playerid, "GANGS", "LEANOUT", 4.0, 0, 0, 0, 1, 0); // /dejardeapoyarse
    	case 4: ApplyAnimation(playerid, "LOWRIDER", "F_SMKLEAN_LOOP", 4.0, 1, 0, 0, 1, 0); // /apoyarse4
	}
    return 1;
}

CMD:cbrazos(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /cbrazos [1-5]");
 	switch(anim)
 	{
        case 1: ApplyAnimation(playerid, "OTB", "WTCHRACE_LOOP", 4.0, 1, 0, 0, 0, 0); // /cbrazos
		case 2: ApplyAnimation(playerid, "COP_AMBIENT", "COPLOOK_IN", 4.0, 0, 0, 0, 1, 0); // nueva
		case 3: ApplyAnimation(playerid, "COP_AMBIENT", "COPLOOK_NOD", 4.0, 0, 0, 0, 1, 0); // nueva ApplyAnimation(playerid, "COP_AMBIENT", "COPLOOK_OUT", 4.0, 0, 0, 0, 1, 0); //salir de esta anim
		case 4: ApplyAnimation(playerid, "GRAFFITI", "GRAFFITI_CHKOUT", 4.0, 0, 0, 0, 0, 0); // /cbrazos
		case 5: ApplyAnimation(playerid, "GRAVEYARD", "PRST_LOOPA", 4.0, 0, 0, 0, 1, 0); // /cbrazos2
	}
    return 1;
}

CMD:alpiso(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /alpiso [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "PED", "getup_front", 4.1, 0, 0, 0, 0, 0, 0);
	}
	return 1;
}

CMD:vigilar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "PED", "Gun_2_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:caminar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
 	new animid;
	if(sscanf(params, "d", animid))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /caminar [1-13]");
	switch(animid)
	{
		case 1: ApplyAnimation(playerid, "WUZI", "WUZI_WALK", 4.1, 1, 1, 1, 1, 1, 1); // /caminar
		case 2: ApplyAnimation(playerid, "PED", "WALK_fat", 4.1, 1, 1, 1, 1, 1, 1);
		case 3: ApplyAnimation(playerid, "PED", "WALK_fatold", 4.1, 1, 1, 1, 1, 1, 1);
		case 4: ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
		case 5: ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
		case 6: ApplyAnimation(playerid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 1, 1);
		case 7: ApplyAnimation(playerid, "PED", "WALK_wuzi", 4.1, 1, 1, 1, 1, 1, 1);
		case 8: ApplyAnimation(playerid, "PED", "WOMAN_walkold", 4.1, 1, 1, 1, 1, 1, 1);
		case 9: ApplyAnimation(playerid, "PED", "WOMAN_walkpro", 4.1, 1, 1, 1, 1, 1, 1);
		case 10: ApplyAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
		case 11: ApplyAnimation(playerid, "PED", "WOMAN_walkshop", 4.1, 1, 1, 1, 1, 1, 1);
		case 12: ApplyAnimation(playerid, "PED", "WALK_shuffle", 4.1, 1, 1, 1, 1, 1, 1);
		case 13: ApplyAnimation(playerid, "MUSCULAR", "MUSCLEWALK", 4.1, 1, 1, 1, 1, 1, 1); // /caminar
		default: SendClientMessage(playerid, 0xFFFFFFAA, "[Sintaxis]: /caminar [1-13]");
	}
	return 1;
}

CMD:afumar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
 	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
 	new animid;
	if(sscanf(params, "d", animid))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /afumar [1-3]");
	switch(animid)
	{
		case 1: ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.1, 0, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 1, 1, 1, 1, 1);
		case 3: ApplyAnimation(playerid, "SMOKING", "M_smk_out", 4.1, 0, 1, 1, 1, 1, 1);
	}
	return 1;
}

CMD:bomba(playerid, params[])
{
	if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "BOMBER", "BOM_PLANT", 4.0, 0, 0, 0, 0, 0); // nueva
    return 1;
}

CMD:bate(playerid, params[])
{
    if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "CRACK", "BBALBAT_IDLE_02", 4.0, 1, 0, 0, 0, 0); // nuevo bate
	return 1;
}

CMD:sentarse(playerid, params[])
{
    if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
   	new anim;
   	if(sscanf(params, "d", anim))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /sentarse [1-9]");
	switch(anim)
	{
  		case 1:	ApplyAnimation(playerid, "BEACH", "bather", 4.1,0,0,0,1,0);
  		case 2: ApplyAnimation(playerid, "BEACH", "Lay_Bac_Loop", 4.1,0,0,0,1,0);
  		case 3: ApplyAnimation(playerid, "BEACH", "ParkSit_W_loop", 4.1,0,0,0,1,0);
		case 4: ApplyAnimation(playerid, "BEACH", "SitnWait_loop_W", 4.1,0,0,0,1,0);
  		case 5:	ApplyAnimation(playerid, "BEACH", "ParkSit_M_loop", 4.1,0,0,0,1,0);
  		case 6: ApplyAnimation(playerid, "PED", "SEAT_down", 4.1,0,0,0,1,0);
  		case 7: ApplyAnimation(playerid, "ATTRACTORS", "STEPSIT_IN", 4.1,0,0,0,1,0); // Nueva ApplyAnimation(playerid, "ATTRACTORS", "STEPSIT_OUT", 4.0, 0, 0, 0, 0, 0); // PARARSE DE LEVANTARSE
  		case 8: ApplyAnimation(playerid, "FOOD", "FF_SIT_IN_L", 4.0, 0, 0, 0, 1, 0); // /sentarse ApplyAnimation(playerid, "FOOD", "FF_SIT_OUT_L_180", 4.0, 0, 0, 0, 0, 0); // /salirsentarse1
  		case 9: ApplyAnimation(playerid, "FOOD", "FF_SIT_IN_R", 4.0, 0, 0, 0, 1, 0); // sentarse ApplyAnimation(playerid, "FOOD", "FF_SIT_OUT_R_180", 4.0, 0, 0, 0, 0, 0); // /salirsentarse2
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /sentarse [1-9]");
 	}
 	return 1;
}

CMD:barman(playerid, params[])
{
	if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
   	new animid;
   	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /barman [1-3]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "BAR", "Barcustom_get", 4.0, 0, 0, 0, 0, 0);
  		case 2:	ApplyAnimation(playerid, "BAR", "Barcustom_loop", 4.0, 0, 0, 0, 0, 0);
  		case 3:	ApplyAnimation(playerid, "BAR", "Barserve_ give", 4.0, 0, 0, 0, 0, 0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /barman [1-3]");
 	}
 	return 1;
}

CMD:besar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /besar [1-6]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.0, 0, 0, 0, 0, 0);
  		case 2:	ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.0, 0, 0, 0, 0, 0);
  		case 3:	ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.0, 0, 0, 0, 0, 0);
		case 4: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
  		case 5:	ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
  		case 6:	ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /besar [1-6]");
 	}
 	return 1;
}

CMD:arrojar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "GRENADE", "WEAPON_throw", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:apreton(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /apreton [1-7]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
  		case 2:	ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
  		case 3:	ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
		case 4:	ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
  		case 5:	ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
  		case 6:	ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0);
  		case 7:	ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /apreton [1-7]");
 	}
 	return 1;
}

CMD:entregar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /entregar [1-2]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "GANGS", "DEALER_IDLE", 4.0, 0, 0, 0, 0, 0);
  		case 2:	ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /entregar [1-2]");
 	}
 	return 1;
}

CMD:oral(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /oral [1-6]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.0, 0, 0, 0, 0, 0);
  		case 2:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 0, 0, 0, 0, 0);
   		case 3:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, 0, 0, 0, 0, 0);
  		case 4:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.0, 0, 0, 0, 0, 0);
  		case 5:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.0, 0, 0, 0, 0, 0);
   		case 6:	ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, 0, 0, 0, 0, 0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /oral [1-6]");
 	}
 	return 1;
}

CMD:paja(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PAULNMAC", "wank_in", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:acabar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PAULNMAC", "wank_out",4.1,0,1,1,1,1);
	return 1;
}

CMD:geofanims(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /geofanims [1-7]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "PED", "swat_run", 4.1,0,1,1,1,0);
  		case 2:	ApplyAnimation(playerid, "POLICE", "Door_Kick", 4.1,0,1,1,1,0);
   		case 3:	ApplyAnimation(playerid, "SWAT", "swt_breach_01", 4.1,0,1,1,1,0);
  		case 4:	ApplyAnimation(playerid, "SWAT", "swt_breach_02", 4.1,0,1,1,1,0);
  		case 5:	ApplyAnimation(playerid, "SWAT", "swt_breach_03",4.1,0,1,1,1,0);
   		case 6:	ApplyAnimation(playerid, "SWAT", "swt_vnt_01",4.1,0,1,1,1,0);
  		case 7:	ApplyAnimation(playerid, "SWAT", "swt_vnt_02",4.1,0,1,1,1,0);
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /geofanims [1-7]");
 	}
 	return 1;
}

CMD:bailar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new animid;
	if(sscanf(params, "d", animid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /bailar [1-10]");
	switch(animid)
	{
  		case 1:	ApplyAnimation(playerid, "DANCING", "dnce_M_a",  4.0, 1, 0, 0, 0, 0);
   		case 2:	ApplyAnimation(playerid, "DANCING", "dnce_M_b",  4.0, 1, 0, 0, 0, 0);
  		case 3:	ApplyAnimation(playerid, "DANCING", "dnce_M_c",  4.0, 1, 0, 0, 0, 0);
  		case 4:	ApplyAnimation(playerid, "DANCING", "dnce_M_d",  4.0, 1, 0, 0, 0, 0);
   		case 5:	ApplyAnimation(playerid, "DANCING", "dnce_M_e",  4.0, 1, 0, 0, 0, 0);
        case 6:	ApplyAnimation(playerid, "DANCING", "dance_loop",  4.0, 1, 0, 0, 0, 0);
        case 7: ApplyAnimation(playerid, "DANCING", "DAN_DOWN_A", 4.0, 1, 1, 1, 0, 0); // /bailar7
        case 8: ApplyAnimation(playerid, "DANCING", "DAN_LOOP_A", 4.0, 1, 1, 1, 0, 0); // bailar8
        case 9: ApplyAnimation(playerid, "DANCING", "DAN_RIGHT_A", 4.0, 1, 1, 1, 0, 0); // bailar9
        case 10: ApplyAnimation(playerid, "DANCING", "DAN_UP_A", 4.0, 1, 1, 1, 0, 0); // bailar10
  		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /bailar [1-10]");
 	}
 	return 1;
}

CMD:pudrete(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PED", "fucku",4.1,0,1,1,0,0);
	return 1;
}

CMD:manosarriba(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PED", "handsup",4.0 , 0, 1, 1, 1, 0);
	return 1;
}

CMD:apuntar(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /apuntar [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat",4.1, 0, 1, 1, 1, 0);
		case 2: ApplyAnimation(playerid, "PED", "ARRESTGUN", 4.0, 0, 0, 0, 1, 0); // /apuntar
	}
	return 1;
}

CMD:crack(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /crack [1-5]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "CRACK", "CRCKDETH1", 4.0, 0, 0, 0, 1, 0); // /crack1
		case 2: ApplyAnimation(playerid, "CRACK", "CRCKDETH2", 4.0, 0, 0, 0, 1, 0); // /crack2
		case 3: ApplyAnimation(playerid, "CRACK", "CRCKDETH3", 4.0, 0, 0, 0, 1, 0); // /crack3
		case 4: ApplyAnimation(playerid, "CRACK", "CRCKDETH4", 4.0, 0, 0, 0, 1, 0); // /crack4
		case 5: ApplyAnimation(playerid, "CRACK", "CRCKIDLE2", 4.0, 0, 0, 0, 1, 0); // /crack5
	}
	return 1;
}

CMD:sentarsenigga(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /sentarsenigga [1-2]");
	switch(anim)
	{
	    case 1: ApplyAnimation(playerid, "CRACK", "CRCKIDLE1", 4.0, 0, 0, 0, 1, 0); // /sentarsenigga
	    case 2: ApplyAnimation(playerid, "CRACK", "CRCKIDLE3", 4.0, 0, 0, 0, 1, 0); // /sentarsenigga
	}
	return 1;
}

CMD:tirarse(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /tirarse [1-2]");
	switch(anim)
	{
	    case 1:	ApplyAnimation(playerid, "CRACK", "CRCKIDLE4", 4.0, 0, 0, 0, 1, 0); // /tirarse
	    case 2: ApplyAnimation(playerid, "PED", "EV_DIVE", 4.0, 0, 1, 1, 1, 0); // /tirarse
	}
	return 1;
}

CMD:dealer(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dealer [1-4]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE", 4.0, 0, 1, 1, 1, 0); // /dealer
		case 2: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_01", 4.0, 0, 1, 1, 1, 0); // /dealer2
		case 3: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_02", 4.0, 0, 1, 1, 1, 0); // /dealer3
		case 4: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_03", 4.0, 0, 1, 1, 1, 0); // /dealer4
	}
	return 1;
}

CMD:pagando(playerid, params[])
{
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "DEALER", "SHOP_PAY", 4.0, 0, 1, 1, 0, 0); // /pagar
    return 1;
}

CMD:acomer(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /acomer [1-3]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "FOOD", "EAT_BURGER", 4.0, 0, 1, 1, 0, 0); // /acomer1
		case 2: ApplyAnimation(playerid, "FOOD", "EAT_CHICKEN", 4.0, 0, 1, 1, 0, 0); // /acomer2
		case 3: ApplyAnimation(playerid, "FOOD", "EAT_PIZZA", 4.0, 0, 1, 1, 0, 0); // /acomer3
	}
	return 1;
}

CMD:orar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "GRAVEYARD", "MRNM_LOOP", 4.0, 0, 0, 0, 1, 0); // /orar
	return 1;
}

CMD:pasartarjeta(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "HEIST9", "USE_SWIPECARD", 4.0, 0, 0, 0, 0, 0); // /pasartarjeta
    return 1;
}



CMD:dormir(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /dormir [1-4]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "INT_HOUSE", "BED_IN_L", 4.0, 0, 0, 0, 1, 0); // /dormir1
		case 2: ApplyAnimation(playerid, "INT_HOUSE", "BED_OUT_L", 4.0, 0, 0, 0, 0, 0); // /dejardedormir1
		case 3: ApplyAnimation(playerid, "INT_HOUSE", "BED_IN_R", 4.0, 0, 0, 0, 1, 0); // /dormir2
		case 4: ApplyAnimation(playerid, "INT_HOUSE", "BED_OUT_R", 4.0, 0, 0, 0, 0, 0); // /dejardedormir2
	}
	return 1;
}

CMD:mirar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /mirar [1-3]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "INT_SHOP", "SHOP_LOOKA", 4.0, 1, 0, 0, 0, 0); // /mirar
		case 2: ApplyAnimation(playerid, "INT_SHOP", "SHOP_LOOP", 4.0, 1, 0, 0, 0, 0); // /mirar2
		case 3: ApplyAnimation(playerid, "INT_SHOP", "SHOP_OUT", 4.0, 0, 0, 0, 0, 0); // /dejardemirar
	}
	return 1;
}

CMD:rapear(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /rapear [1-3]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "LOWRIDER", "RAP_A_LOOP", 4.0, 1, 0, 0, 1, 0); // /rap1
		case 2: ApplyAnimation(playerid, "LOWRIDER", "RAP_B_LOOP", 4.0, 1, 0, 0, 1, 0); // /rap2
		case 3: ApplyAnimation(playerid, "LOWRIDER", "RAP_C_LOOP", 4.0, 1, 0, 0, 1, 0); // /rap3
	}
	return 1;
}

CMD:chocado(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "MD_CHASE", "CARHIT_TUMBLE", 4.0, 0, 1, 1, 1, 0); // /chocado
	return 1;
}

CMD:taxi(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /taxi [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "MISC", "HIKER_POSE_L", 4.0, 1, 0, 0, 0, 0); // /taxi1
		case 2: ApplyAnimation(playerid, "MISC", "HIKER_POSE", 4.0, 1, 0, 0, 0, 0); // /taxi2
	}
	return 1;
}

CMD:quebrar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "MISC", "PLUNGER_01", 4.0, 0, 1, 1, 0, 0); // /quebrar
    return 1;
}

CMD:quepaso(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "MISC", "PLYR_SHKHEAD", 4.0, 0, 1, 1, 0, 0); // /quepaso
	return 1;
}

CMD:chupala(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "MISC", "SCRATCHBALLS_01", 4.0, 0, 1, 1, 0, 0); // /chupala
	return 1;
}

CMD:borracho(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /borracho [1-3]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1);
		case 2: ApplyAnimation(playerid, "PAULNMAC", "PNM_LOOP_A", 4.0, 1, 0, 0, 0, 0); // /borracho
		case 3: ApplyAnimation(playerid, "PAULNMAC", "PNM_LOOP_B", 4.0, 1, 0, 0, 0, 0); // /borracho2
	}
	return 1;
}

CMD:taichi(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "PARK", "TAI_CHI_LOOP", 4.0, 1, 0, 0, 0, 0); // /taichi
    return 1;
}


CMD:mear(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /mear [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PAULNMAC", "PISS_LOOP", 4.0, 1, 0, 0, 0, 0); // /mear
		case 2: ApplyAnimation(playerid, "PAULNMAC", "PISS_OUT", 4.0, 0, 0, 0, 0, 0); // /nomear
	}
	return 1;
}

CMD:reanimar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "MEDIC", "CPR", 4.0, 0, 0, 0, 0, 0); // /reanimar
	return 1;
}

CMD:cubrirse(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PED", "COWER", 4.0, 0, 0, 0, 1, 0); // /cubrirse
	return 1;
}

CMD:nockeado(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PED", "KO_SHOT_FACE", 4.0, 0, 1, 1, 1, 0); // /nockeado1
	return 1;
}

CMD:aspirar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "PED", "PASS_SMOKE_IN_CAR", 4.0, 0, 1, 1, 0, 0); // /aspirar
	return 1;
}

CMD:reir(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "RAPPING", "LAUGH_01", 4.0, 0, 1, 1, 0, 0); // /reir
	return 1;
}

CMD:enojado(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /enojado [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 1, 1, 0, 0); // /enojado
		case 2:ApplyAnimation(playerid, "RIOT", "RIOT_CHANT", 4.0, 0, 1, 1, 0, 0); // /enojado2
	}
	return 1;
}

CMD:alentar(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /alentar [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "RIOT", "RIOT_PUNCHES", 4.0, 1, 1, 1, 0, 0); // /alentar
		case 2: ApplyAnimation(playerid, "RIOT", "RIOT_SHOUT", 4.0, 0, 1, 1, 0, 0); // /alentar2
	}
	return 1;
}

CMD:tantear(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "SWEET", "SWEET_ASS_SLAP", 4.0, 0, 0, 0, 0, 0); // /tantear
	return 1;
}

CMD:arrastrarse(playerid, params[])
{
	if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.0, 1, 1, 1, 0, 0); // /arrastrarse
	return 1;
}

CMD:cansado(playerid, params[]){
    if(GetPlayerState(playerid) !=1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /cansado [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PED", "IDLE_tired", 4.0, 0, 0, 0, 1, 0, 1); // /cansado1
		case 2: ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.0, 0, 0, 0, 1, 0, 1); // /cansado2
		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /cnsado [1-2]");
	}
	return 1;
}

CMD:rodar(playerid, params[]){
	if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /rodar [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PED", "Crouch_Roll_L", 3.5, 0, 1, 1, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "PED", "Crouch_Roll_R", 3.5, 0, 1, 1, 0, 0, 1);
		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /rodar [1-2]");
	}
	return 1;
}

CMD:teclear(playerid, params[]){
	if(GetPlayerState(playerid) != 1) return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /teclear [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4, 1, 0, 0, 1, 0, 1);
		case 2: ApplyAnimation(playerid, "INT_OFFICE", "OFF_Sit_Bored_Loop", 4, 1, 0, 0, 1, 0, 1);
		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /teclear [1-2]");
	}
	return 1;
}

CMD:brazoventanilla(playerid, params[]){
	if(GetPlayerState(playerid) != 2 && GetPlayerState(playerid) != 3)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo dentro de un vehículo!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /brazoventanilla [1-5]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "CAR", "Sit_relaxed", 4, 0, 0, 0, 1, 0, 1); // /loeraider1
		case 2: ApplyAnimation(playerid, "CAR", "Tap_hand", 4, 1, 0, 0, 1, 0, 1); // /loeraider2
		case 3: ApplyAnimation(playerid, "LOWRIDER", "lrgirl_idle_to_l0", 4.0, 0, 0, 0, 1, 0, 1); // /loerider3
		case 4: ApplyAnimation(playerid, "LOWRIDER", "lrgirl_idleloop", 4.0, 0, 0, 0, 1, 0, 1); // /loerider4
		case 5: ApplyAnimation(playerid, "LOWRIDER", "lrgirl_l0_loop", 4.0, 0, 0, 0, 1, 0, 1); // /loerider5
		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /brazoventanilla [1-5]");
	}
	return 1;
}

CMD:pesas(playerid, params[]){
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	new anim;
	if(sscanf(params, "d", anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /pesas [1-8]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "benchpress", "gym_bp_geton", 4.5, 0, 1, 1, 1, 0, 1); // /pesas1
		case 2: ApplyAnimation(playerid, "benchpress", "gym_bp_up_smooth", 4.5, 0, 1, 1, 1, 0, 1); // /pesas2
		case 3: ApplyAnimation(playerid, "benchpress", "gym_bp_down", 4.5, 0, 1, 1, 1, 0, 1); // /pesas3
		case 4: ApplyAnimation(playerid, "benchpress", "gym_bp_getoff", 4.5, 0, 1, 1, 0, 0, 1); // /pesas4
		case 5: ApplyAnimation(playerid, "Freeweights", "gym_free_pickup", 4.5, 0, 1, 1, 1, 0, 1); // pesas5
		case 6: ApplyAnimation(playerid, "Freeweights", "gym_free_up_smooth", 4.5, 0, 1, 1, 1, 0, 1); // pesas6
        case 7: ApplyAnimation(playerid, "Freeweights", "gym_free_down", 4.5, 0, 1, 1, 1, 0, 1); // pesas7
        case 8: ApplyAnimation(playerid, "Freeweights", "gym_free_putdown", 4.5, 0, 1, 1, 0, 0, 1); // pesas8
        default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /pesas [1-8]");
	}
	return 1;
}

CMD:lavarmanos(playerid, params[]){
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
	ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.5, 0, 1, 1, 0, 0, 1); // /lavarmanos1
	return 1;
}

CMD:codazo(playerid, params[])
{
    if(GetPlayerState(playerid) !=1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "PED", "GUN_BUTT", 4.5, 0, 1, 1, 0, 0, 1);
    return 1;
}

CMD:ponermascara(playerid, params[])
{
    if(GetPlayerState(playerid) !=1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.5, 0, 0, 0, 0, 0, 1);
    return 1;
}

CMD:chau(playerid, params[])
{
	if(GetPlayerState(playerid) !=1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    new anim;
    if(sscanf(params,"i",anim))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /chau [1-2]");
	switch(anim)
	{
		case 1: ApplyAnimation(playerid, "PED", "endchat_01", 4.1, 0, 1, 1, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "PED", "endchat_03", 4.1, 0, 1, 1, 0, 0, 0);
		default: SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /chau [1-2]");
	}
	return 1;
}

CMD:estirarse(playerid, params[])
{
    if(GetPlayerState(playerid) !=1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "PLAYIDLES", "stretch", 4.5, 0, 1, 1, 0, 0, 1);
    return 1;
}

CMD:abeber(playerid, params[])
{
    if(GetPlayerState(playerid) !=1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Solo puedes utilizarlo de pie!");
    if(GetPVarInt(playerid, "disabled") != DISABLE_NONE) return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes utilizar esto estando incapacitado/congelado!");
    ApplyAnimation(playerid, "BAR", "dnk_stndF_loop", 4.5, 0, 1, 1, 0, 0, 1);
    return 1;
}
//-----------------------------FIN ANIMACIONES----------------------------------
//-----------------------------FIN ANIMACIONES----------------------------------
