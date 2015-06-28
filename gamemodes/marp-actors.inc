#if defined _marp_actors_included
	#endinput
#endif
#define _marp_actors_included

enum e_ServerActor {
	eSQLID,
	eName[64],
	eDescription[64],
	eUsesLabel,
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
			animname[32],
			animlib[32],
			str[128];

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

            cache_get_field_content(i, "id", result); 	ServerActor[actorid][eSQLID] = strval(result);
            
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

			cache_get_field_content(i, "nick", ServerActor[actorid][eName], 1, 64);
            cache_get_field_content(i, "description", ServerActor[actorid][eDescription], 1, 64);
            
		    if(strcmp(ServerActor[actorid][eName], "none", true) != 0 || strcmp(ServerActor[actorid][eDescription], "none", true) != 0)
		    {
		        if(strcmp(ServerActor[actorid][eName], "none", true) == 0)
		            format(ServerActor[actorid][eName], 64, "%s", "");
		            
		        if(strcmp(ServerActor[actorid][eDescription], "none", true) == 0)
		            format(ServerActor[actorid][eDescription], 64, "%s", "");
		            
		        format(str, sizeof(str), "%s\n%s", ServerActor[actorid][eName], ServerActor[actorid][eDescription]);
				ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(str, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld);
				ServerActor[actorid][eUsesLabel] = 1;
			}
		}
	}
	return 1;
}

CMD:aanombre(playerid, params[])
{
	new actorid,
	    actorname[64];

	if(sscanf(params, "is[64]", actorid, actorname))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aanombre [id de actor] [nombre]");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	format(ServerActor[actorid][eName], 64, "%s", actorname);
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado el nombre del actor %d a '%s'.", actorid, actorname);

	new str[128];
	format(str, sizeof(str), "%s\n%s", ServerActor[actorid][eName], ServerActor[actorid][eDescription]);
	
	if(ServerActor[actorid][eUsesLabel] && IsValidDynamic3DTextLabel(ServerActor[actorid][eLabelID]))
	{
		UpdateDynamic3DTextLabelText(ServerActor[actorid][eLabelID], COLOR_WHITE, str);
	}
	else
	{
	    new Float:pos[3];
	    GetActorPos(actorid, pos[0], pos[1], pos[2]);
		ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(str, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetActorVirtualWorld(actorid));
		ServerActor[actorid][eUsesLabel] = 1;
	}
	
	format(str, sizeof(str), "UPDATE actors SET nick = '%s' WHERE id = %d", actorname, ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, str, false, "", "");
	return 1;
}

CMD:aadesc(playerid, params[])
{
	new actorid,
	    actordesc[64];

	if(sscanf(params, "is[64]", actorid, actordesc))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aanombre [id de actor] [descripción]");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	format(ServerActor[actorid][eDescription], 64, "%s", actordesc);
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado la descripción del actor %d a '%s'.", actorid, actordesc);

	new str[128];
	format(str, sizeof(str), "%s\n%s", ServerActor[actorid][eName], ServerActor[actorid][eDescription]);

	if(ServerActor[actorid][eUsesLabel] && IsValidDynamic3DTextLabel(ServerActor[actorid][eLabelID]))
	{
		UpdateDynamic3DTextLabelText(ServerActor[actorid][eLabelID], COLOR_WHITE, str);
	}
	else
	{
	    new Float:pos[3];
	    GetActorPos(actorid, pos[0], pos[1], pos[2]);
		ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(str, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetActorVirtualWorld(actorid));
		ServerActor[actorid][eUsesLabel] = 1;
	}

	format(str, sizeof(str), "UPDATE actors SET description = '%s' WHERE id = %d", actordesc, ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, str, false, "", "");
	return 1;
}

CMD:aacrear(playerid, params[])
{
	new skin;

	if(sscanf(params, "i", skin))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aactor [skin]");
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
	
	SetPlayerPos(playerid, pos[0] + 0.7, pos[1], pos[2]);
	
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: actor id %d creado correctamente en el mundo virtual %d.", actorid, vworld);

	new query[256];
	
	format(query, sizeof(query), "INSERT INTO actors (skin, x, y, z, angle, vworld, nick, description, animlib, animname) VALUES (%d, %f, %f, %f, %f, %d, 'none', 'none', 'none', 'none')", skin, pos[0], pos[1], pos[2], angle, vworld);
	mysql_function_query(dbHandle, query, true, "GetInsertedActorId", "d", GetVariableAddress(ServerActor[actorid][eSQLID]));
	return 1;
}

forward GetInsertedActorId(store_in_address);
public GetInsertedActorId(store_in_address)
{
    @ptr[store_in_address] = cache_insert_id(dbHandle);
    return 1;
}

CMD:aaanim(playerid, params[])
{
	new animlib[32],
		animname[32],
		actorid;

	if(sscanf(params, "is[32] s[32]", actorid, animlib, animname))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aaanim [id de actor] [librería de anim] [nombre de anim] (se buscan en https://wiki.sa-mp.com/wiki/Animations)");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	    
	ApplyActorAnimation(actorid, animlib, animname, 4.1, 1, 0, 0, 0, 0);
	
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado la animación del actor %d a la '%s' de la librería '%s'.", actorid, animname, animlib);

	new query[128];
	
	format(query, sizeof(query), "UPDATE actors SET animlib = '%s', animname = '%s' WHERE id = %d", animlib, animname, ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, query, false, "", "");
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

CMD:aatele(playerid, params[])
{
	new actorid,
	    Float:pos[3];
	
	if(sscanf(params, "i", actorid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aatele [id de actor]");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	
	GetActorPos(actorid, pos[0], pos[1], pos[2]);
	SetPlayerPos(playerid, pos[0] + 0.7, pos[1], pos[2]);
	return 1;
}

CMD:aaborrar(playerid, params[])
{
	new actorid;

	if(sscanf(params, "i", actorid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aaborrar [id de actor]");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	DestroyActor(actorid);

	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has borrado el actor %d correctamente.", actorid);
    
	new query[128];

	format(query, sizeof(query), "DELETE FROM actors WHERE id = %d", ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, query, false, "", "");

	if(ServerActor[actorid][eUsesLabel] && IsValidDynamic3DTextLabel(ServerActor[actorid][eLabelID]))
		DestroyDynamic3DTextLabel(ServerActor[actorid][eLabelID]);

    ServerActor[actorid][eUsesLabel] = 0;
    ServerActor[actorid][eSQLID] = 0;
    format(ServerActor[actorid][eName], 64, "%s", "");
    format(ServerActor[actorid][eDescription], 64, "%s", "");
	return 1;
}
