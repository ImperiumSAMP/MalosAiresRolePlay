#if defined _marp_actors_included
	#endinput
#endif
#define _marp_actors_included

enum e_ServerActor {
	eSQLID,
	Text3D:eLabelID
};

new ServerActor[MAX_ACTORS][e_ServerActor];

LoadServerActors()
{
	mysql_function_query(dbHandle, "SELECT * FROM actors LIMIT 1000", true, "OnActorDataLoad", "");
}

forward OnActorDataLoad();
public OnActorDataLoad()
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows)
	{
	    new Float:pos[3],
			Float:angle,
			vworld,
			skin,
			actorid,
			description[128],
			animname[32],
			animlib[32];

		for(new i = 0; i < rows; i++)
	    {
			cache_get_field_content(i, "skin", result); 	skin = strval(result);
			cache_get_field_content(i, "x", result); 		pos[0] = floatstr(result);
			cache_get_field_content(i, "y", result); 		pos[1] = floatstr(result);
	        cache_get_field_content(i, "z", result); 		pos[2] = floatstr(result);
			cache_get_field_content(i, "angle", result); 	angle = floatstr(result);
			
			actorid = CreateActor(skin, pos[0], pos[1], pos[2], angle);
			
			if(actorid == INVALID_ACTOR_ID)
			    return 1;
			    
	        cache_get_field_content(i, "vworld", result); 	vworld = strval(result);
			SetActorVirtualWorld(actorid, vworld);
			
			SetActorHealth(actorid, 100.0);
			SetActorInvulnerable(actorid, 1);

			cache_get_field_content(i, "animlib", animlib, 1, 32);
			if(strcmp(animlib, "none", true) != 0)
		    {
		        cache_get_field_content(i, "animname", animname, 1, 32);
		        ApplyActorAnimation(actorid, animlib, animname, 4.1, 1, 0, 0, 0, 0);
			}

			cache_get_field_content(i, "description", description, 1, 128);
			    
		    if(strcmp(description, "none", true) != 0)
				ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(description, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld);
		}
	}
	return 1;
}

CMD:aacrear(playerid, params[])
{
	new skin, description[128];

	if(sscanf(params, "iS(none)[128]", skin, description))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aactor [skin] [nombre y descripción (opcional)] ('\n' es bajada de linea, sin comillas)");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Ejemplo]:{C8C8C8} /aactor 280 Lopez - PMA'\n'Garito de estacionamiento");
		return 1;
	}
	if(skin < 1 || skin > 311)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa una ID de skin válida (1-311).");


	new Float:pos[3],
	    Float:angle,
	    vworld = GetPlayerVirtualWorld(playerid),
	    actorid;

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, angle);

	actorid = CreateActor(skin, pos[0], pos[1], pos[2], angle);

	if(actorid == INVALID_ACTOR_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "[ERROR]: máximo de actores en el servidor alcanzado (1000). Reportar a la administración");

	SetActorVirtualWorld(actorid, vworld);
	SetActorHealth(actorid, 100.0);
	SetActorInvulnerable(actorid, 1);

	if(strcmp(description, "none", true) != 0)
	{
		format(description, sizeof(description), "%s", description);
		ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(description, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld);
	}
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: actor id %d creado correctamente en el mundo virtual %d.", actorid, vworld);

	new query[256];

	format(query, sizeof(query), "INSERT INTO actors (skin, x, y, z, angle, vworld, description, animlib, animname) VALUES (%d, %f, %f, %f, %f, %d, '%s', 'none', 'none')", skin, pos[0], pos[1], pos[2], angle, vworld, description);
	mysql_function_query(dbHandle, query, true, "GetInsertedActorId", "d", GetVariableAddress(ServerActor[actorid][eSQLID]));

	return 1;
}

CMD:aaanim(playerid, params[])
{
	new animlib[32],
		animname[32],
		actorid;

	if(sscanf(params, "is[32] s[32]", actorid, animlib, animname))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aaanim [id de actor] [librería de anim] [nombre de anim] (se buscan en https://wiki.sa-mp.com/wiki/Animations)");

	new actorpool = GetActorPoolSize();
	
	if(actorid < 0 || actorid > actorpool || !IsValidActor(actorid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	if(ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	    
	ApplyActorAnimation(actorid, animlib, animname, 4.1, 1, 0, 0, 0, 0);
	
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado la animación del actor %d a la de la librería %d, de nombre %d.", actorid, animlib, animname);

	new query[128];
	
	format(query, sizeof(query), "UPDATE actors SET animlib = '%s', animname = '%s' WHERE id = %d", animlib, animname, ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, query, false, "", "");

	return 1;
}

forward GetInsertedActorId(store_in_address);
public GetInsertedActorId(store_in_address)
{
    @ptr[store_in_address] = cache_insert_id(dbHandle);
    return 1;
}

CMD:aagetid(playerid, params[])
{
	new actorpool = GetActorPoolSize(),
	    Float:apos[3];
	
	for(new i = 0; i <= actorpool; i++)
	{
		if(IsValidActor(i) && ServerActor[i][eSQLID] > 0)
		{
		    GetActorPos(i, apos[0], apos[1], apos[2]);
		    if(IsPlayerInRangeOfPoint(playerid, 2.0, apos[0], apos[1], apos[2]))
		    {
		        SendFMessage(playerid, COLOR_WHITE, "La id del actor cercano es %d.", i);
		        return 1;
			}
		}
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "No se ha encontrado ningún actor válido cerca tuyo (2.0 unidades SAMP de cercanía).");
	return 1;
}

CMD:aaborrar(playerid, params[])
{
	new actorid;

	if(sscanf(params, "i", actorid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aaborrar [id de actor]");

	new actorpool = GetActorPoolSize();

	if(actorid < 0 || actorid > actorpool || !IsValidActor(actorid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	if(ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	DestroyActor(actorid);

	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has borrado el actor %d.", actorid);
    
	new query[128];

	format(query, sizeof(query), "DELETE FROM actors WHERE id = %d", ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, query, false, "", "");

	if(IsValidDynamic3DTextLabel(ServerActor[actorid][eLabelID]))
		DestroyDynamic3DTextLabel(ServerActor[actorid][eLabelID]);

    ServerActor[actorid][eSQLID] = 0;
	return 1;
}
