#if defined _marp_actors_included
	#endinput
#endif
#define _marp_actors_included

enum e_ServerActor {
	eSQLID,
	eNick[128],
	eDescription[128],
	eInt,
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
			{
			    printf("[ERROR DE CARGA DE ACTORES]: interrumpida la carga por alcanzar el límite de actores creados en el row %i de %i.", i, rows);
			    return 1;
			}
			
			SetActorHealth(actorid, 100.0);
			SetActorInvulnerable(actorid, 1);
			
            cache_get_field_content(i, "id", result);
			ServerActor[actorid][eSQLID] = strval(result);
            
			cache_get_field_content(i, "interior", result);
			ServerActor[actorid][eInt] = strval(result);
			
	        cache_get_field_content(i, "vworld", result);
			vworld = strval(result);
			SetActorVirtualWorld(actorid, vworld);

			cache_get_field_content(i, "description", ServerActor[actorid][eDescription], 1, 128);

			cache_get_field_content(i, "animlib", animlib, 1, 32);
			if(strcmp(animlib, "none", true) != 0)
		    {
		        cache_get_field_content(i, "animname", animname, 1, 32);
		        cache_get_field_content(i, "animloop", result);
		        ApplyActorAnimation(actorid, animlib, animname, 4.1, strval(result), 0, 0, 1, 0);
			}

			cache_get_field_content(i, "nick", ServerActor[actorid][eNick], 1, 128);
		    if(strcmp(ServerActor[actorid][eNick], "none", true) != 0)
		    {
				ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(ServerActor[actorid][eNick], COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld);
				ServerActor[actorid][eUsesLabel] = 1;
			}
		}
	}
	return 1;
}

CMD:aanombre(playerid, params[])
{
	new actorid,
	    str[128],
		charpos;

	if(sscanf(params, "is[128]", actorid, str))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aanombre [id de actor] [nombre]. El caracter '_' (guión bajo) es bajada de linea, solo una vez.");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	charpos = strfind(str, "_", true);
	if(charpos != -1)
	    str[charpos] = 10; // Codigo decimal para el caracter 'bajada de linea' en el codigo ASCII.
	
	format(ServerActor[actorid][eNick], 128, "%s", str);
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado el nombre del actor %d a '%s'.", actorid, str);
	
	if(ServerActor[actorid][eUsesLabel] && IsValidDynamic3DTextLabel(ServerActor[actorid][eLabelID]))
	{
		UpdateDynamic3DTextLabelText(ServerActor[actorid][eLabelID], COLOR_WHITE, str);
	}
	else
	{
	    new Float:pos[3];
	    GetActorPos(actorid, pos[0], pos[1], pos[2]);
		ServerActor[actorid][eLabelID] = CreateDynamic3DTextLabel(str, COLOR_WHITE, pos[0], pos[1], pos[2] + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetActorVirtualWorld(actorid));
		ServerActor[actorid][eUsesLabel] = 1;
	}
	
	format(str, sizeof(str), "UPDATE actors SET nick = '%s' WHERE id = %d", ServerActor[actorid][eNick], ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, str, false, "", "");
	return 1;
}

CMD:aadesc(playerid, params[])
{
	new actorid,
	    str[128];

	if(sscanf(params, "is[128]", actorid, str))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aadesc [id de actor] [descripción ooc]");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");

	format(ServerActor[actorid][eDescription], 128, "%s", str);
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado la descripción OOC del actor %d a '%s'.", actorid, str);

	format(str, sizeof(str), "UPDATE actors SET description = '%s' WHERE id = %d", ServerActor[actorid][eDescription], ServerActor[actorid][eSQLID]);
	mysql_function_query(dbHandle, str, false, "", "");
	return 1;
}

CMD:aacrear(playerid, params[])
{
	new skin,
		desc[128];

	if(sscanf(params, "is[128]", skin, desc))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aacrear [id skin] [descripción OOC] (hasta 128 caracteres)");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "La descripción OOC sirve unicamente para identificar al actor en la DB, y no se mostrará in-game. Ej: 'NPC PMA en escaleras del exterior de la comisaría'.");
		return 1;
	}
	if(skin < 1 || skin > 311)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa una ID de skin válida (1-311).");

	new Float:pos[3],
	    Float:angle,
	    vworld = GetPlayerVirtualWorld(playerid),
	    interior = GetPlayerInterior(playerid),
	    actorid;

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, angle);

	actorid = CreateActor(skin, pos[0], pos[1], pos[2], angle);

	if(actorid == INVALID_ACTOR_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "[ERROR]: máximo de actores en el servidor alcanzado (1000). Reportar a un scripter.");

	SetActorVirtualWorld(actorid, vworld);
	SetActorHealth(actorid, 100.0);
	SetActorInvulnerable(actorid, 1);
	
	ServerActor[actorid][eInt] = interior;
	
	SetPlayerPos(playerid, pos[0] + 0.7, pos[1], pos[2]);
	
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: actor id %d creado correctamente en el mundo virtual %d.", actorid, vworld);
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: la descripción OOC es '%s'.", desc);

	new query[350];
	
	format(query, sizeof(query), "INSERT INTO actors (skin, x, y, z, angle, vworld, interior, nick, description, animlib, animname) VALUES (%d, %f, %f, %f, %f, %d, %d, 'none', '%s', 'none', 'none')", skin, pos[0], pos[1], pos[2], angle, vworld, interior, desc);
	mysql_function_query(dbHandle, query, true, "GetInsertedActorSqlid", "i", actorid);
	return 1;
}

forward GetInsertedActorSqlid(actorid);
public GetInsertedActorSqlid(actorid)
{
    ServerActor[actorid][eSQLID] = cache_insert_id(dbHandle);
    return 1;
}

CMD:aaanim(playerid, params[])
{
	new animlib[32],
		animname[32],
		animloop,
		actorid;

	if(sscanf(params, "iis[32] s[32]", actorid, animloop, animlib, animname))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aaanim [id de actor] [loop de anim] [librería de anim] [nombre de anim] (ver en 'wiki.sa-mp.com/wiki/Animations')");
	if(!IsValidActor(actorid) || ServerActor[actorid][eSQLID] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Actor inválido o no existe.");
	if(animloop < 0 || animloop > 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "En el campo 'loop de anim' elija el valor 1 o 0.");

	if(animloop)
		ApplyActorAnimation(actorid, animlib, animname, 4.1, 1, 0, 0, 1, 0);
	else
	    ApplyActorAnimation(actorid, animlib, animname, 4.1, 0, 0, 0, 1, 1);
	    
	SendFMessage(playerid, COLOR_WHITE, "[INFO]: has seteado la animación del actor %d a la '%s' de la librería '%s' con loop en %d.", actorid, animname, animlib, animloop);

	new query[128];
	
	format(query, sizeof(query), "UPDATE actors SET animlib = '%s', animname = '%s', animloop = %d WHERE id = %d", animlib, animname, animloop, ServerActor[actorid][eSQLID]);
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
		    if(GetPlayerVirtualWorld(playerid) == GetActorVirtualWorld(i))
		    {
			    if(IsPlayerInRangeOfPoint(playerid, 1.0, apos[0], apos[1], apos[2]))
			    {
			        SendFMessage(playerid, COLOR_WHITE, "La id del actor cercano es %d.", i);
			        return 1;
				}
			}
		}
	}
	
	SendClientMessage(playerid, COLOR_WHITE, "No se ha encontrado ningún actor válido cerca tuyo (1.0 unidades SAMP de cercanía).");
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
	SetPlayerVirtualWorld(playerid, GetActorVirtualWorld(actorid));
	SetPlayerInterior(playerid, ServerActor[actorid][eInt]);
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
    ServerActor[actorid][eInt] = 0;
    format(ServerActor[actorid][eNick], 128, "%s", "");
    format(ServerActor[actorid][eDescription], 128, "%s", "");
	return 1;
}
