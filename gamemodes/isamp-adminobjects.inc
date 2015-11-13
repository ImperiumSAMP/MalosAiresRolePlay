#if defined _isamp_admin_objects
	#endinput
#endif
#define _isamp_admin_objects

//===============================ADMIN OBJECTS SYSTEM====================================

//================================CONSTANTES====================================
#define MAX_ADMIN_OBJECTS       500
//new adminServerObjectsCant = 0;
//new adminServerObjects[MAX_ADMIN_OBJECTS];

enum adminObjectInfo {
    logid,
    objectadmin,
	SelectObjects = 0,
    IDobject,
	bool:Odelete,
	bool:Oinsert,
	bool:Oupdate,
	bool:Oloaded,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:RotX,
	Float:RotY,
	Float:RotZ,
	Interior,
	Vworld
};

new ObjectsAdminsInfo[MAX_PLAYERS][MAX_ADMIN_OBJECTS][adminObjectInfo];
new ObjectsAdmins[MAX_ADMIN_OBJECTS][adminObjectInfo];


//===============================DATA STORAGE===================================
//======================CABECERA DE FUNCIONES PUBLICAS==========================
//================================FUNCIONES=====================================
/*DeleteAdminObject(objectadmin)
{	
	DestroyDynamicObject(objectadmin);
	SendFMessage(playerid, COLOR_ADMINCMD,"[DEBUG]: Has borrado el objeto id numero %d" , objectadmin);
}*/
CMD:aeditobjeto(playerid,params[])
{
    new object;
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(sscanf(params, "d", object))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aeditobjeto [idobjeto]");
	EditAdminObject(playerid, object);
    return 1;
}

EditAdminObject(playerid, object)
{   
    new query[128];
	
	if(object < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de objeto inv�lida.");
	format(query, sizeof(query),"SELECT * FROM `log_objects` WHERE `logid` = %d LIMIT 1", object);
	mysql_function_query(dbHandle, query, true, "OnObjectDataLoad", "i", object);
    EditDynamicObject(playerid, ObjectsAdminsInfo[playerid][object][SelectObjects]);
	ObjectsAdminsInfo[playerid][object][Oupdate] = true;
	SendFMessage(playerid, COLOR_ADMINCMD, "Ahora puedes editar el objeto id %d", object);
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL)
	{
	    ObjectsAdminsInfo[playerid][objectadmin][IDobject] = objectid;
	    ObjectsAdminsInfo[playerid][objectadmin][PosX] = x;
	    ObjectsAdminsInfo[playerid][objectadmin][PosY] = y;
	    ObjectsAdminsInfo[playerid][objectadmin][PosZ] = z;
	    ObjectsAdminsInfo[playerid][objectadmin][RotX] = rx;
	    ObjectsAdminsInfo[playerid][objectadmin][RotY] = ry;
	    ObjectsAdminsInfo[playerid][objectadmin][RotZ] = rz;
		SetDynamicObjectPos(ObjectsAdminsInfo[playerid][objectadmin][IDobject], ObjectsAdminsInfo[playerid][objectadmin][PosX], ObjectsAdminsInfo[playerid][objectadmin][PosY], ObjectsAdminsInfo[playerid][objectadmin][PosZ]);
	    SetDynamicObjectRot(ObjectsAdminsInfo[playerid][objectadmin][IDobject],ObjectsAdminsInfo[playerid][objectadmin][RotX], ObjectsAdminsInfo[playerid][objectadmin][RotY], ObjectsAdminsInfo[playerid][objectadmin][RotZ]);
		saveObjects(playerid, objectadmin);
	}
}


//================================COMANDOS======================================


CMD:aobjetoquitar(playerid, params[])
{
    new object;
	if(PlayerInfo[playerid][pAdmin] < 2)
        return 1;
	if(sscanf(params, "d", object))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjetoquitar [idobjeto]");
	if(object < 1 || object >= MAX_ADMIN_OBJECTS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de objeto inv�lida.");
	ObjectsAdminsInfo[playerid][object][Odelete] = true;
	DestroyDynamicObject(ObjectsAdminsInfo[playerid][object][logid]);
	saveObjects(playerid,object);
	SendFMessage(playerid, COLOR_ADMINCMD,"[DEBUG]: Has borrado el objeto id numero %d" , object);
    //DeleteAdminObject(object);
	return 1;
}

CMD:aobjeto(playerid,params[])
{
    new object, objectid, Float:x, Float:y, Float:z, Float:facingAngle, interior, virtualWorld;
	
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
    if(sscanf(params, "d", objectid))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjeto [ID-OBJETO] (/ainfoobjetos)");
	
	for(new i = 1; i < MAX_ADMIN_OBJECTS; i++)
	{
	    if(!ObjectsAdminsInfo[playerid][i][Oloaded])
		{
	        ObjectsAdminsInfo[playerid][i][Oloaded] = true;
			object = i;
			break;
		}
	}
	
	ObjectsAdminsInfo[playerid][object][Interior] = GetPlayerInterior(playerid);
	ObjectsAdminsInfo[playerid][object][Vworld] = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, ObjectsAdminsInfo[playerid][object][PosX], ObjectsAdminsInfo[playerid][object][PosY], ObjectsAdminsInfo[playerid][object][PosZ]);
	GetPlayerFacingAngle(playerid, facingAngle);
	ObjectsAdminsInfo[playerid][object][Oinsert] = true; 
	ObjectsAdminsInfo[playerid][object][SelectObjects] = CreateDynamicObject(objectid, ObjectsAdminsInfo[playerid][object][PosX], ObjectsAdminsInfo[playerid][object][PosY], ObjectsAdminsInfo[playerid][object][PosZ], 0.0, 0.0, facingAngle);
	ObjectsAdminsInfo[playerid][object][IDobject] = objectid;
	//ObjectsLog(object, objectid, x, y, z, interior, virtualWorld);
	saveObjects(playerid,object);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Has puesto un objeto, para editarlo pon /aeditobjeto");
    return 1;
}


SaveObjectsAdmin(playerid)
{
  	new id = 1;

    if(dontsave)
		return 1;

	while(id < MAX_ADMIN_OBJECTS)
	{
	    ObjectsAdmins[id][Oupdate] = true;
	    saveObjects(playerid,id);
		id++;
	}
    print("[INFO]: objetos guardados.");
	return 1;
}

stock saveObjects(playerid,id) {
    new
		query[1024];

	if(dontsave)
		return 1;

	if(ObjectsAdminsInfo[playerid][id][Odelete]) {
	    format(query, sizeof(query), "DELETE FROM `log_objects` WHERE `logid` = %d", id);
	    mysql_function_query(dbHandle, query, false, "", "");
		ObjectsAdminsInfo[playerid][id][Odelete] = false;
		ObjectsAdminsInfo[playerid][id][Oloaded] = false;
	} else if(ObjectsAdminsInfo[playerid][id][Oinsert]) {
		format(query, sizeof(query), "INSERT INTO `log_objects` (logid, Id, PosX, PosY, PosZ, Interior, Vworld, SelectObjects)");
		format(query, sizeof(query), "%s VALUES (%d, %d, %f, %f, %f, %d, %d, %d)",
			query,
			id,
			ObjectsAdminsInfo[playerid][id][IDobject],
			ObjectsAdminsInfo[playerid][id][PosX],
			ObjectsAdminsInfo[playerid][id][PosY],
			ObjectsAdminsInfo[playerid][id][PosZ],
			ObjectsAdminsInfo[playerid][id][Interior],
			ObjectsAdminsInfo[playerid][id][Vworld],
			ObjectsAdminsInfo[playerid][id][SelectObjects]
		);
		mysql_function_query(dbHandle, query, false, "", "");
		ObjectsAdminsInfo[playerid][id][Oinsert] = false;
	} else if(ObjectsAdminsInfo[playerid][id][Oupdate]) {
		format(query, sizeof(query), "UPDATE `log_objects` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = %d, `VWorld` = %d, `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f' WHERE `logid`=%d",
			ObjectsAdminsInfo[playerid][id][PosX],
			ObjectsAdminsInfo[playerid][id][PosY],
			ObjectsAdminsInfo[playerid][id][PosZ],
			ObjectsAdminsInfo[playerid][id][Interior],
			ObjectsAdminsInfo[playerid][id][Vworld],
			ObjectsAdminsInfo[playerid][id][RotX],
			ObjectsAdminsInfo[playerid][id][RotY],
			ObjectsAdminsInfo[playerid][id][RotZ],
			id	
		);
		mysql_function_query(dbHandle, query, false, "", "");
		ObjectsAdminsInfo[playerid][id][Oupdate] = false;
	}
	return 1;
}

forward OnObjectDataLoad(playerid, id);
public OnObjectDataLoad(playerid, id) {
   	new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows) {
	    cache_get_field_content(0, "logid", result); 		        id = strval(result);
		cache_get_field_content(0, "IDobject", result); 		    ObjectsAdminsInfo[playerid][id][IDobject] 		= strval(result);
  		cache_get_field_content(0, "Interior", result); 		    ObjectsAdminsInfo[playerid][id][Interior] 		= strval(result);
  		cache_get_field_content(0, "Vworld", result); 			    ObjectsAdminsInfo[playerid][id][Vworld]			= strval(result);
		cache_get_field_content(0, "SelectObjects", result); 	    ObjectsAdminsInfo[playerid][id][SelectObjects]	= strval(result);
		cache_get_field_content(0, "PosX", result); 		        ObjectsAdminsInfo[playerid][id][PosX]  			= floatstr(result);
		cache_get_field_content(0, "PosY", result); 			    ObjectsAdminsInfo[playerid][id][PosY] 	 		= floatstr(result);
		cache_get_field_content(0, "PosZ", result); 			    ObjectsAdminsInfo[playerid][id][PosZ] 			= floatstr(result);
		cache_get_field_content(0, "RotX", result); 		        ObjectsAdminsInfo[playerid][id][RotX] 		    = floatstr(result);
		cache_get_field_content(0, "RotY", result); 		        ObjectsAdminsInfo[playerid][id][RotY] 		    = floatstr(result);
		cache_get_field_content(0, "RotZ", result); 		        ObjectsAdminsInfo[playerid][id][RotZ] 		    = floatstr(result);
		CreateDynamicObject(ObjectsAdminsInfo[playerid][id][IDobject], ObjectsAdminsInfo[playerid][id][PosX], ObjectsAdminsInfo[playerid][id][PosY], ObjectsAdminsInfo[playerid][id][PosZ], ObjectsAdminsInfo[playerid][id][RotX], ObjectsAdminsInfo[playerid][id][RotY], ObjectsAdminsInfo[playerid][id][RotZ]);
        SetDynamicObjectPos(ObjectsAdminsInfo[playerid][id][IDobject], ObjectsAdminsInfo[playerid][id][PosX], ObjectsAdminsInfo[playerid][id][PosY], ObjectsAdminsInfo[playerid][id][PosZ]);
	    SetDynamicObjectRot(ObjectsAdminsInfo[playerid][id][IDobject],ObjectsAdminsInfo[playerid][id][RotX], ObjectsAdminsInfo[playerid][id][RotY], ObjectsAdminsInfo[playerid][id][RotZ]);
		ObjectsAdminsInfo[playerid][id][Oloaded] = true;
	} else {
	    ObjectsAdminsInfo[playerid][id][Oloaded] = false;
	}
	return 1;
}

stock LoadObjects() {
	new
		query[128],
		odid = 1;

	while(odid < MAX_ADMIN_OBJECTS) {
		format(query, sizeof(query),"SELECT * FROM `log_objects` WHERE `logid` = %d LIMIT 1", odid);
		mysql_function_query(dbHandle, query, true, "OnObjectDataLoad", "i", odid);
		odid++;
	}
	print("[INFO]: objetos cargados.");
	return 1;
}

/*stock ObjectsLog(logid, objectid, PosOX, PosOY, PosOZ, ObjInterior, ObjVworld)
{
	new query[512];
      

	format(query, sizeof(query), "INSERT INTO `log_objects` (logid, Id, PosX, PosY, PosZ, Interior, Vworld) VALUES (%d, %d, %f, %f, %f, %d, %d)",
	    logid,
		objectid,
		PosOX,
		PosOY,
		PosOZ,
		ObjInterior,
		ObjVworld
	);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}*/

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