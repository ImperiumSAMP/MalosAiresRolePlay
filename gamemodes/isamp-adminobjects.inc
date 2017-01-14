#if defined _isamp_admin_objects
	#endinput
#endif
#define _isamp_admin_objects

//===============================ADMIN OBJECTS SYSTEM====================================

//================================CONSTANTES====================================
#define MAX_ADMIN_OBJECTS       1000
#define OBJECT_CREATE             	1
#define OBJECT_UPDATE             	2
#define OBJECT_DELETE           	3

//==============================ENUM Y NEWS===================================
enum adminObjectInfo {
    logid,
    objectadmin,
	SelectObjects,
    IDobject,
	bool:oLoaded,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:RotX,
	Float:RotY,
	Float:RotZ,
	Interior,
	Vworld
};

new ObjectsAdminsInfo[MAX_ADMIN_OBJECTS][adminObjectInfo];
new EditedObjectID[MAX_PLAYERS];
new PlayerText3D:PlayerTextIdObject[MAX_ADMIN_OBJECTS];
new ShowIdObjects[MAX_PLAYERS];
//======================CARGAS POR DB Y SIMILARES==========================
forward OnObjectDataLoad(id, option); 
public OnObjectDataLoad(id, option) { //Dos options.. la 1 es para la carga de objetos cuando inicia el servidor, la 2 es para la edicion de objetos cuando el player usa el CMD: /aeditobjeto
   	new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

	if(option == 1)
	{
		if(rows) 
		{
			cache_get_field_content(0, "IDobject", result); 		    ObjectsAdminsInfo[id][IDobject] 		= strval(result);
			cache_get_field_content(0, "Interior", result); 		    ObjectsAdminsInfo[id][Interior] 		= strval(result);
			cache_get_field_content(0, "Vworld", result); 			    ObjectsAdminsInfo[id][Vworld]			= strval(result);
			cache_get_field_content(0, "SelectObjects", result); 	    ObjectsAdminsInfo[id][SelectObjects]	= strval(result);
			cache_get_field_content(0, "PosX", result); 		        ObjectsAdminsInfo[id][PosX]  			= floatstr(result);
			cache_get_field_content(0, "PosY", result); 			    ObjectsAdminsInfo[id][PosY] 	 		= floatstr(result);
			cache_get_field_content(0, "PosZ", result); 			    ObjectsAdminsInfo[id][PosZ] 			= floatstr(result);
			cache_get_field_content(0, "RotX", result); 		        ObjectsAdminsInfo[id][RotX] 		    = floatstr(result);
			cache_get_field_content(0, "RotY", result); 		        ObjectsAdminsInfo[id][RotY] 		    = floatstr(result);
			cache_get_field_content(0, "RotZ", result); 		        ObjectsAdminsInfo[id][RotZ] 		    = floatstr(result);
			ObjectsAdminsInfo[id][SelectObjects] = CreateDynamicObject(ObjectsAdminsInfo[id][IDobject], ObjectsAdminsInfo[id][PosX], ObjectsAdminsInfo[id][PosY], ObjectsAdminsInfo[id][PosZ], ObjectsAdminsInfo[id][RotX], ObjectsAdminsInfo[id][RotY], ObjectsAdminsInfo[id][RotZ]);
			saveObjects(id, OBJECT_UPDATE); //Updateamos valores por si se agregaron mapeos en el include de mapeos o por si se borro algun objeto para que cuando se reinicie se acomoden todos los id sin saltear ninguno.
			ObjectsAdminsInfo[id][oLoaded] = true;
		} 
		else 
		{
			ObjectsAdminsInfo[id][oLoaded] = false;
		}
	}
	else if(option == 2)
	{
		if(rows) 
		{
			cache_get_field_content(0, "IDobject", result); 		    ObjectsAdminsInfo[id][IDobject] 		= strval(result);
			cache_get_field_content(0, "Interior", result); 		    ObjectsAdminsInfo[id][Interior] 		= strval(result);
			cache_get_field_content(0, "Vworld", result); 			    ObjectsAdminsInfo[id][Vworld]			= strval(result);
			cache_get_field_content(0, "SelectObjects", result); 	    ObjectsAdminsInfo[id][SelectObjects]	= strval(result);
			cache_get_field_content(0, "PosX", result); 		        ObjectsAdminsInfo[id][PosX]  			= floatstr(result);
			cache_get_field_content(0, "PosY", result); 			    ObjectsAdminsInfo[id][PosY] 	 		= floatstr(result);
			cache_get_field_content(0, "PosZ", result); 			    ObjectsAdminsInfo[id][PosZ] 			= floatstr(result);
			cache_get_field_content(0, "RotX", result); 		        ObjectsAdminsInfo[id][RotX] 		    = floatstr(result);
			cache_get_field_content(0, "RotY", result); 		        ObjectsAdminsInfo[id][RotY] 		    = floatstr(result);
			cache_get_field_content(0, "RotZ", result); 		        ObjectsAdminsInfo[id][RotZ] 		    = floatstr(result);
			ObjectsAdminsInfo[id][oLoaded] = true;
		} 
		else 
		{
			ObjectsAdminsInfo[id][oLoaded] = false;
		}
	}
	return 1;
}

stock loadObjects() {
	new
		query[128],
		i = 1;
		
	while(i < MAX_ADMIN_OBJECTS) {
		format(query, sizeof(query),"SELECT * FROM `log_objects` WHERE `logid` = %d", i);
		mysql_function_query(dbHandle, query, true, "OnObjectDataLoad", "ii", i,1);
		i++;
	}
	return 1;
}
stock saveObjects(id, option) {
    new
		query[1024];

	if(dontsave)
		return 1;

	if(option == OBJECT_DELETE) {
	    format(query, sizeof(query), "DELETE FROM `log_objects` WHERE `logid` = %d", id);
	    mysql_function_query(dbHandle, query, false, "", "");
		ObjectsAdminsInfo[id][oLoaded] = false;
	} else if(option == OBJECT_CREATE) {
		format(query, sizeof(query), "INSERT INTO `log_objects` (logid, IDobject, PosX, PosY, PosZ, Interior, Vworld, SelectObjects)");
		format(query, sizeof(query), "%s VALUES (%d, %d, %f, %f, %f, %d, %d, %d)",
			query,
			id,
			ObjectsAdminsInfo[id][IDobject],
			ObjectsAdminsInfo[id][PosX],
			ObjectsAdminsInfo[id][PosY],
			ObjectsAdminsInfo[id][PosZ],
			ObjectsAdminsInfo[id][Interior],
			ObjectsAdminsInfo[id][Vworld],
			ObjectsAdminsInfo[id][SelectObjects]
		);
		mysql_function_query(dbHandle, query, false, "", "");
	} else if (option == OBJECT_UPDATE){
	
		format(query, sizeof(query), "UPDATE `log_objects` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `Interior` = %d, `VWorld` = %d, `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f',`SelectObjects` = %d WHERE `logid`= %d",
			ObjectsAdminsInfo[id][PosX],
			ObjectsAdminsInfo[id][PosY],
			ObjectsAdminsInfo[id][PosZ],
			ObjectsAdminsInfo[id][Interior],
			ObjectsAdminsInfo[id][Vworld],
			ObjectsAdminsInfo[id][RotX],
			ObjectsAdminsInfo[id][RotY],
			ObjectsAdminsInfo[id][RotZ],
			ObjectsAdminsInfo[id][SelectObjects],
			id
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}
	return 1;
}
//================================FUNCIONES=====================================
EditAdminObject(playerid, object)
{   
    new query[128];
	
	if(object < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de objeto inválida.");
	EditedObjectID[playerid] = 0;
	format(query, sizeof(query),"SELECT * FROM `log_objects` WHERE `logid` = %d", object);
	mysql_function_query(dbHandle, query, true, "OnObjectDataLoad", "ii", object, 2);//Cargo las variables del objeto que voy a editar. Las que edite van a ser sobreescribidas. Le pongo la opción 2 que es la de edición de objeto
    EditDynamicObject(playerid, ObjectsAdminsInfo[object][SelectObjects]); //El objeto se maneja con la variable SelectObjects ya que es la que almacena el ID del objeto creado en el juego.
	SendFMessage(playerid, COLOR_ADMINCMD, "Ahora puedes editar el objeto id %d", object);
	EditedObjectID[playerid] = object;
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response)
	{
	    ObjectsAdminsInfo[EditedObjectID[playerid]][PosX] = x;
	    ObjectsAdminsInfo[EditedObjectID[playerid]][PosY] = y;
	    ObjectsAdminsInfo[EditedObjectID[playerid]][PosZ] = z;
	    ObjectsAdminsInfo[EditedObjectID[playerid]][RotX] = rx;
	    ObjectsAdminsInfo[EditedObjectID[playerid]][RotY] = ry;
	    ObjectsAdminsInfo[EditedObjectID[playerid]][RotZ] = rz;
		SetDynamicObjectPos(objectid, ObjectsAdminsInfo[EditedObjectID[playerid]][PosX], ObjectsAdminsInfo[EditedObjectID[playerid]][PosY], ObjectsAdminsInfo[EditedObjectID[playerid]][PosZ]);
	    SetDynamicObjectRot(objectid, ObjectsAdminsInfo[EditedObjectID[playerid]][RotX], ObjectsAdminsInfo[EditedObjectID[playerid]][RotY], ObjectsAdminsInfo[EditedObjectID[playerid]][RotZ]);
		saveObjects(EditedObjectID[playerid], OBJECT_UPDATE);
	}
}


//================================COMANDOS======================================
CMD:aobjeto(playerid,params[])
{
    new  objectid, id;
	
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
    if(sscanf(params, "d", objectid))
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjeto [ID-OBJETO] (/ainfoobjetos)");
		
	for(new i = 1; i < MAX_ADMIN_OBJECTS; i++) {
		if(!ObjectsAdminsInfo[i][oLoaded]) { //Chequeamos el primer id libre para usar.
			ObjectsAdminsInfo[i][oLoaded] = true;
			id = i;
			break;
		}
	}
	
	ObjectsAdminsInfo[id][Interior] = GetPlayerInterior(playerid);
	ObjectsAdminsInfo[id][Vworld] = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, ObjectsAdminsInfo[id][PosX], ObjectsAdminsInfo[id][PosY], ObjectsAdminsInfo[id][PosZ]);
	ObjectsAdminsInfo[id][SelectObjects] = CreateDynamicObject(objectid, ObjectsAdminsInfo[id][PosX], ObjectsAdminsInfo[id][PosY], ObjectsAdminsInfo[id][PosZ], 0.0, 0.0, 0.0);
	ObjectsAdminsInfo[id][IDobject] = objectid;
	saveObjects(id, OBJECT_CREATE);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Has puesto un objeto, para editarlo pon /aeditobjeto");
    return 1;
}

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

CMD:aobjetoquitar(playerid, params[])
{
    new object;
	if(PlayerInfo[playerid][pAdmin] < 2)
        return 1;
	if(sscanf(params, "d", object))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjetoquitar [idobjeto]");
	if(object < 1 || object >= MAX_ADMIN_OBJECTS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El objeto no puede ser menor que 1 ni mayor que el maximo definido de objetos(1000).");
	if(!ObjectsAdminsInfo[object][oLoaded])
		return SendClientMessage(playerid, COLOR_YELLOW2, "El id de objeto que quieres borrar no está creado actualmente en la database.");
	DestroyDynamicObject(ObjectsAdminsInfo[object][SelectObjects]);
	saveObjects(object, OBJECT_DELETE);
	SendFMessage(playerid, COLOR_ADMINCMD,"[DEBUG]: Has borrado el objeto id numero %d" , object);
	return 1;
}

CMD:aomostrarid(playerid, params[]) {
	new string[128];
	
	if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(ShowIdObjects[playerid] == 1)
		return SendClientMessage(playerid, COLOR_WHITE, "Tienes que ocultar los id para volver a mostrarlos (/aoocultarid)");
	for(new i = 1; i < MAX_ADMIN_OBJECTS; i++)	{
		if(PlayerToPoint(15.0, playerid, ObjectsAdminsInfo[i][PosX], ObjectsAdminsInfo[i][PosY], ObjectsAdminsInfo[i][PosZ])) {
			valstr(string,i);
			PlayerTextIdObject[i] = CreatePlayer3DTextLabel(playerid,string,COLOR_WHITE,ObjectsAdminsInfo[i][PosX],ObjectsAdminsInfo[i][PosY],ObjectsAdminsInfo[i][PosZ]+ 0.75,15.0);
		}
	}
	SendClientMessage(playerid,COLOR_WHITE, "Puedes ver las ids de los objetos creados en tu area(distancia limitada)");
	ShowIdObjects[playerid] = 1;
	return 1;
}

CMD:aoocultarid(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
	if(ShowIdObjects[playerid] == 0)
		return SendClientMessage(playerid, COLOR_WHITE, "No tienes id de objetos para ocultar ya que no usaste el comando /aomostrarid");
	for(new i = 1; i < MAX_ADMIN_OBJECTS; i++)	{
		DeletePlayer3DTextLabel(playerid, PlayerTextIdObject[i]);
	}
	ShowIdObjects[playerid] = 0;
	return 1;
}

CMD:aobjetotele(playerid, params[]) {
	new object;
	if(sscanf(params, "i", object))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aobjetotele [IDobjeto]");
	if(object < 1 || object >= MAX_ADMIN_OBJECTS)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El objeto no puede ser menor que 1 ni mayor que el maximo definido de objetos(1000).");
	if(!ObjectsAdminsInfo[object][oLoaded])
		return SendClientMessage(playerid, COLOR_YELLOW2, "El id de objeto que quieres telepearte no está creado actualmente en la database.");

	SetPlayerPos(playerid, ObjectsAdminsInfo[object][PosX], ObjectsAdminsInfo[object][PosY], ObjectsAdminsInfo[object][PosZ]);
	SetPlayerInterior(playerid, ObjectsAdminsInfo[object][Interior]);
	return 1;
}


CMD:ainfoobjetos(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2)
		return 1;
    SendClientMessage(playerid, COLOR_RED, "[ID objetos útiles]:");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1280: banco para sentarse - 1223: poste de luz chico - 1840: parlante - 1839: equipo de mÃºsica - 16151: barra de tragos ");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1551: botella de bebida - 1455 :vaso - 3027: porro - 2632: colchoneta de playa - 2290: sillones triples marrones - 2896,19339: ataud");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "18077: sillas para una barra- 1432: juego de 3 sillas con mesa - 1212:fajos de dinero - 3860: puestos de feria - 14673: motosierra consolador");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "1428: escalera sola corta - 1437: escalera sola larga - 3092: policÃ­a colgado muerto - 2968: caja de cartÃ³n sola - 1439: conteiner de basura");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "3007, 3008, 3009, 3010, 3011, 3012: partes del cuerpo de un policÃ­a - 1264: bolsa de basura - 3594: auto destruido");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "982,983,984: rejas(dif.tamaÃ±o) - 1503: rampa  - 18761: entrada de inicio de carreras - 19076: pino de navidad - 19129: piso a cuadro de colores");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "19143 a 19156: luces para boliches - 19334: globo aerostÃ¡tico - 19473: planta de marihuana sola - 13623: cÃ­rculo de reja(GIGANTE)");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "978-979: Barrera fija");
	return 1;
}