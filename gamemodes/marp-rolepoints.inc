#if defined _marp_rolepoints_included
	#endinput
#endif
#define _marp_rolepoints_included

#define MAX_LISTED_ROLEPOINTS 		10

CMD:darpuntoderol(playerid, params[])
{
	new targetid, reason[80], string[128];
	
	if(sscanf(params, "us[80]", targetid, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /darpuntoderol [ID/Jugador] [Razón] (MAX: 80 caracteres)");
    if(!IsPlayerConnected(targetid) || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
		
	format(string, sizeof(string), "El administrador %s le ha dado un punto de rol a %s. Razón: %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), reason);
	AdministratorMessage(COLOR_ADMINCMD, string, 2);
	format(string, sizeof(string), "El administrador %s te ha otorgado un punto de rol. Razón: %s.", GetPlayerNameEx(playerid), reason);
	SendClientMessage(targetid, COLOR_LIGHTYELLOW2, string);
	
	PlayerInfo[targetid][pRolePoints]++;
	format(string, sizeof(string), "INSERT INTO role_points (pID, pName, Amount, Reason, Date, adminID, adminName) VALUES (%d, '%s', 1, '%s', CURRENT_TIMESTAMP, %d, '%s')",
	    PlayerInfo[targetid][pID],
	    PlayerInfo[targetid][pName],
	    reason,
	    PlayerInfo[playerid][pID],
	    PlayerInfo[playerid][pName]
	);
	return 1;
}

CMD:quitarpuntoderol(playerid, params[])
{
	new targetid, reason[80], string[128], query[350];

	if(sscanf(params, "us[80]", targetid, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /quitarpuntoderol [ID/Jugador] [Razón] (MAX: 80 caracteres)");
    if(!IsPlayerConnected(targetid) || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
	if(PlayerInfo[targetid][pRolePoints] <= 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador seleccionado no tiene ningún puntos de rol para quitar.");
        
	format(string, sizeof(string), "El administrador %s le ha quitado un punto de rol a %s. Razón: %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), reason);
	AdministratorMessage(COLOR_ADMINCMD, string, 2);
	format(string, sizeof(string), "El administrador %s te ha quitado un punto de rol. Razón: %s.", GetPlayerNameEx(playerid), reason);
	SendClientMessage(targetid, COLOR_LIGHTYELLOW2, string);

	PlayerInfo[targetid][pRolePoints]--;
	format(query, sizeof(query), "INSERT INTO role_points (pID, pName, Amount, Reason, Date, adminID, adminName) VALUES (%d, '%s', -1, '%s', CURRENT_TIMESTAMP, %d, '%s')",
	    PlayerInfo[targetid][pID],
	    PlayerInfo[targetid][pName],
	    reason,
	    PlayerInfo[playerid][pID],
	    PlayerInfo[playerid][pName]
	);
	return 1;
}

CMD:verpuntosderol(playerid, params[])
{
    new targetid, query[128];
    
	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /verpuntosderol [ID/Jugador]");
    if(!IsPlayerConnected(targetid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inválido.");
		
	format(query, sizeof(query), "SELECT * FROM role_points WHERE pID = %d LIMIT %d", PlayerInfo[targetid][pID], MAX_LISTED_ROLEPOINTS);
 	mysql_function_query(dbHandle, query, true, "ShowRolePoints", "ii", targetid, playerid);
 	return 1;
}

forward ShowRolePoints(ofplayerid, toplayerid);
public ShowRolePoints(ofplayerid, toplayerid)
{
   	new result[80],
		rows,
		fields,
		string[144],
		aux = 0;
		
	cache_get_data(rows, fields);

    if(rows)
    {
        format(string, sizeof(string), "[Ultimos %d puntos de rol otorgados/quitados a %s]", rows, GetPlayerNameEx(ofplayerid));
        SendClientMessage(toplayerid, COLOR_YELLOW2, string);
    	while(aux < rows)
	    {
     		cache_get_field_content(aux, "Amount", result);
     		format(string, sizeof(string), "- Cantidad: %s", result);
     		cache_get_field_content(aux, "Date", result);
     		format(string, sizeof(string), "%s - Fecha: %s", string, result);
     		cache_get_field_content(aux, "adminName", result);
     		format(string, sizeof(string), "%s - Por: %s", string, result);
     		cache_get_field_content(aux, "Reason", result);
     		format(string, sizeof(string), "%s - Razón: %s", string, result);
     		SendClientMessage(toplayerid, COLOR_WHITE, string);
     		aux++;
		}
	}
	else
	{
        format(string, sizeof(string), "No se encontraron puntos de rol para el personaje %s.", GetPlayerNameEx(ofplayerid));
        SendClientMessage(toplayerid, COLOR_YELLOW2, result);
	}
	return 1;
}
