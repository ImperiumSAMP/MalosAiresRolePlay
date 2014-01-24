#if defined _isamp_houses_included
	#endinput
#endif
#define _isamp_houses_included

#define MAX_HOUSES              200

enum HouseSystem {
	Description[128],
	Owner[MAX_PLAYER_NAME],
	Float:EntranceX,
	Float:EntranceY,
	Float:EntranceZ,
	EntranceInterior,
	Float:EntranceAngle,
	Float:ExitX,
	Float:ExitY,
	Float:ExitZ,
	ExitInterior,
	Float:ExitAngle,
	Owned,
	Rentable,
	RentCost,
	InsideWorld,
	HousePrice,
	Materials,
	Drugs,
	Money,
	Locked,
	hEntrancePickup,
	hExitPickup,
	Text3D:hEntranceLabel,
	Text3D:hExitLabel,
};

new House[MAX_HOUSES][HouseSystem];



//Admin commands
//====[CASAS]===================================================================
CMD:acasas(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 20) return 1;

	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[COMANDOS]:{C8C8C8} /ainfocasa - /acdisp - /acentrada - /acsalida - /acdesc - /actele - /acprecio - /acvender - /acinterior");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} para agregar una casa consulta con el comando '/acdisp' qué casa está disponible para ser añadida.");
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{C8C8C8}Deberás estar mirando hacia la puerta para que el ángulo de salida sea el correcto.");
	return 1;
}

CMD:ainfocasa(playerid, params[]) {
	new
	    id;

    if(PlayerInfo[playerid][pAdmin] < 2) return 1;

	if(sscanf(params, "d", id)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ainfocasa [idcasa]");
	} else if(id >= 1 && id < MAX_HOUSES) {
	    SendFMessage(playerid, COLOR_WHITE, "|---- Casa %d '%s' ----|", id, House[id][Description]);
	    SendFMessage(playerid, COLOR_WHITE, "- Tiene dueño: %d", House[id][Owned]);
	    SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s", House[id][Owner]);
	    SendFMessage(playerid, COLOR_WHITE, "- Rentable: %d", House[id][Rentable]);
	    SendFMessage(playerid, COLOR_WHITE, "- Costo de compra: $%d", House[id][HousePrice]);
	    SendFMessage(playerid, COLOR_WHITE, "- Costo de renta: $%d", House[id][RentCost]);
	    SendFMessage(playerid, COLOR_WHITE, "- Materiales: $%d", House[id][Materials]);
        SendFMessage(playerid, COLOR_WHITE, "- Drogas: %d", House[id][Drugs]);
	    SendFMessage(playerid, COLOR_WHITE, "- Dinero: %d", House[id][Money]);
	    SendFMessage(playerid, COLOR_WHITE, "- Cerrada: %d", House[id][Locked]);
	} else {
	    SendClientMessage(playerid, COLOR_YELLOW2, "Casa inexistente.");
	}
	return 1;
}

