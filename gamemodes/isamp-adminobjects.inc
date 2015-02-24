#if defined _isamp_admin_objects
	#endinput
#endif
#define _isamp_admin_objects

//===============================ADMIN OBJECTS SYSTEM====================================

//================================CONSTANTES====================================
#define MAX_ADMIN_OBJECTS       500
new adminServerObjectsCant = 0;
new adminServerObjects[MAX_ADMIN_OBJECTS];

enum adminObjectInfo {
    objectadmin,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:RotX,
	Float:RotY,
	Float:RotZ
}

new ObjectsAdminsInfo[MAX_PLAYERS][adminObjectInfo];


//===============================DATA STORAGE===================================
//======================CABECERA DE FUNCIONES PUBLICAS==========================
//================================FUNCIONES=====================================
DeleteAdminObject(playerid)
{
	if(adminServerObjectsCant > 0)
	{
		DestroyDynamicObject(adminServerObjects[adminServerObjectsCant-1]);
		adminServerObjectsCant --;
        SendClientMessage(playerid, COLOR_WHITE, "[DEBUG]: Has borrado el �ltimo objeto puesto por un administrador.");
	}
	
}

DeleteAllAdminObject(playerid)
{
	if(adminServerObjectsCant > 0)
	{
	    for(new i = 0; i < adminServerObjectsCant; i++) {
			DestroyDynamicObject(adminServerObjects[i]);
		}
		adminServerObjectsCant = 0;
		SendClientMessage(playerid, COLOR_WHITE, "[DEBUG]: Has borrado todos los objetos del servidor puestos por los administradores.");
	}
	
}

EditAdminObject(playerid)
{
	if(adminServerObjectsCant > 0)
	{
        EditDynamicObject(playerid, adminServerObjects[adminServerObjectsCant-1]);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Ahora puedes editar el ultimo objeto puesto por un administrador");
	}
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response)
	{
	    ObjectsAdminsInfo[playerid][objectadmin] = objectid;
	    ObjectsAdminsInfo[playerid][PosX] = x;
	    ObjectsAdminsInfo[playerid][PosY] = y;
	    ObjectsAdminsInfo[playerid][PosZ] = z;
	    ObjectsAdminsInfo[playerid][RotX] = rx;
	    ObjectsAdminsInfo[playerid][RotY] = ry;
	    ObjectsAdminsInfo[playerid][RotZ] = rz;
		SetDynamicObjectPos(ObjectsAdminsInfo[playerid][objectadmin], ObjectsAdminsInfo[playerid][PosX], ObjectsAdminsInfo[playerid][PosY], ObjectsAdminsInfo[playerid][PosZ]);
	    SetDynamicObjectRot(ObjectsAdminsInfo[playerid][objectadmin],ObjectsAdminsInfo[playerid][RotX], ObjectsAdminsInfo[playerid][RotY], ObjectsAdminsInfo[playerid][RotZ]);
	}
}


//================================COMANDOS======================================


CMD:aobjetoquitar(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 2)
        return 1;
    DeleteAdminObject(playerid);
	return 1;
}

CMD:aobjetosquitartodo(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 2)
        return 1;
    DeleteAllAdminObject(playerid);
	return 1;
}

CMD:aobjeto(playerid,params[])
{
    new object, Float:x, Float:y, Float:z, Float:facingAngle;
	
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(adminServerObjectsCant >= MAX_ADMIN_OBJECTS)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No hay mas espacio para objetos.");
    if(sscanf(params, "d", object))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjeto [ID-OBJETO] (/ainfoobjetos)");
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, facingAngle);
	adminServerObjectsCant ++;
	adminServerObjects[adminServerObjectsCant-1] = CreateDynamicObject(object, x, y, z, 0.0, 0.0, facingAngle);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Has puesto un objeto, para editarlo pon /aeditobjeto");
    return 1;
}

CMD:aeditobjeto(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	EditAdminObject(playerid);
    return 1;
}

CMD:ainfoobjetos(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
    SendClientMessage(playerid, COLOR_RED, "[ID objetos �tiles]:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1280: banco para sentarse - 1223: poste de luz chico - 1840: parlante - 1839: equipo de música - 16151: barra de tragos ");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1551: botella de bebida - 1455 :vaso - 3027: porro - 2632: colchoneta de playa - 2290: sillones triples marrones - 2896,19339: ataud");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "18077: sillas para una barra- 1432: juego de 3 sillas con mesa - 1212:fajos de dinero - 3860: puestos de feria - 14673: motosierra consolador");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1428: escalera sola corta - 1437: escalera sola larga - 3092: policía colgado muerto - 2968: caja de cartón sola - 1439: conteiner de basura");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "3007, 3008, 3009, 3010, 3011, 3012: partes del cuerpo de un policía - 1264: bolsa de basura - 3594: auto destruido");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "982,983,984: rejas(dif.tamaño) - 1503: rampa  - 18761: entrada de inicio de carreras - 19076: pino de navidad - 19129: piso a cuadro de colores");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "19143 a 19156: luces para boliches - 19334: globo aerostático - 19473: planta de marihuana sola - 13623: círculo de reja(GIGANTE)");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "978-979: Barrera fija");
	return 1;
}

