#if defined _isamp_notebook_included
	#endinput
#endif
#define _isamp_notebook_included

//===========================SISTEMA DE AGENDAS=================================

//===============================CONSTANTES=====================================

#define MAX_NOTEBOOK_CONTACTS       15
#define DLG_NOTEBOOK				10025

#define CONTACT_CREATE              1
#define CONTACT_DELETE              2

//===============================DATA STORAGE===================================

enum contactInfo {
	cNumber,
	cName[32]
};

new playerNotebook[MAX_PLAYERS][MAX_NOTEBOOK_CONTACTS][contactInfo];

//==================================FUNCIONES===================================

forward OnNotebookDataLoad(playerid);
forward SaveNotebookContact(playerid, contactslot, option);

//==========================IMPLEMENTACION DE FUNCIONES=========================

ShowNotebook(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new aux, str[1000] = "";
	    
	    for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
	    {
	        if(playerNotebook[playerid][i][cNumber] != 0)
	        {
				format(str, sizeof(str), "%s[%d] %s - %d\n", str, i, playerNotebook[playerid][i][cName], playerNotebook[playerid][i][cNumber]);
				aux = 1;
			}
		}
		if(aux != 1)
		    format(str, sizeof(str), "No hay contactos agregados.");
		ShowPlayerDialog(playerid, DLG_NOTEBOOK, DIALOG_STYLE_LIST, "Contactos", str, "Cerrar", "");
	}
}

ResetNotebookContacts(playerid)
{
	for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
	{
	    playerNotebook[playerid][i][cNumber] = 0;
	    strmid(playerNotebook[playerid][i][cName], " ", 0, strlen(" "));
	}
}

LoadNotebookContacts(playerid)
{
	new query[128];
	
	ResetNotebookContacts(playerid);
	format(query, sizeof(query), "SELECT * FROM `contacts_info` WHERE `pId`=%d", PlayerInfo[playerid][pID]);
	mysql_function_query(dbHandle, query, true, "OnNotebookDataLoad", "i", playerid);
	return 1;
}

public OnNotebookDataLoad(playerid)
{
	new result[128],
	   	rows,
	   	fields,
	   	aux = 0,
	   	slot;

	cache_get_data(rows, fields);

	if(rows)
	{
	    while(aux < rows)
	    {
			cache_get_field_content(aux, "Slot", result); 		slot = strval(result);
			cache_get_field_content(aux, "Name",                playerNotebook[playerid][slot][cName], 1, 32);
			cache_get_field_content(aux, "Number", result); 	playerNotebook[playerid][slot][cNumber] = strval(result);
			aux ++;
		}
	}
	return 1;
}

public SaveNotebookContact(playerid, contactslot, option)
{
	new query[256];

	if(option == CONTACT_CREATE)
	{
		format(query, sizeof(query), "INSERT INTO `contacts_info` (`pId`, `Slot`, `Number`, `Name`) VALUES (%d, %d, %d, '%s')",
			PlayerInfo[playerid][pID],
			contactslot,
			playerNotebook[playerid][contactslot][cNumber],
			playerNotebook[playerid][contactslot][cName]
		);
	}
	else if(option == CONTACT_DELETE)
	{
		format(query, sizeof(query), "DELETE FROM `contacts_info` WHERE `pId`=%d AND `Slot`=%d",
			PlayerInfo[playerid][pID],
			contactslot
		);
	}
    mysql_function_query(dbHandle, query, false, "", "");
    return 1;
}

//============================DEBUG DE VARIABLES================================

CMD:notebookdebug(playerid, params[])
{
	new id;
	
	if(PlayerInfo[playerid][pAdmin] < 20)
	    return 1;
	if(sscanf(params, "u", id))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /notebookdebug [ID/Jugador]");
	if(id < 0 || id >= MAX_PLAYERS)
        return SendClientMessage(playerid, COLOR_YELLOW2, "ID invalida.");

	for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
	{
	    SendFMessage(playerid, COLOR_YELLOW, "[%d][%d] cNumber = %d", id, i, playerNotebook[id][i][cNumber]);
	    SendFMessage(playerid, COLOR_YELLOW, "[%d][%d] cName = %s", id, i, playerNotebook[id][i][cName]);
	}
	return 1;
}

//====================================COMANDOS==================================

CMD:agenda(playerid, params[])
{
	new cmd[32], param1, param2[32];

	if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un telefono con agenda de contactos!");
	if(sscanf(params, "s[32]I(-1)S(-1)[32]", cmd, param1, param2))
	{
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [comando]");
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} ver - agregar [numero] [nombre] - borrar [slot]");
	    return 1;
	}
	
	if(!strcmp("agregar", cmd, true))
	{
	    if(strval(param2) == -1)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda agregar [numero] [nombre]");
		if(param1 < 0 || strlen(param2) >= 32)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El numero no puede ser menor a 0 / Solo puedes usar una descripción de hasta 30 caracteres.");
		for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
		{
		    if(playerNotebook[playerid][i][cNumber] == 0)
		    {
		        mysql_real_escape_string(param2, param2);
		        strmid(playerNotebook[playerid][i][cName], param2, 0, strlen(param2), 32);
		        playerNotebook[playerid][i][cNumber] = param1;
				SaveNotebookContact(playerid, i, CONTACT_CREATE);
				SendClientMessage(playerid, COLOR_WHITE, "Contacto agregado. Utiliza '/agenda ver' para ver con mas detalle tu agenda.");
				return 1;
			}
		}
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes mas espacio en tu agenda y no se pudo agregar el contacto.");
	}
	
	else if(!strcmp("borrar", cmd, true))
	{
		if(param1 < 0 || param1 >= MAX_NOTEBOOK_CONTACTS)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido. Mas info en '/agenda ver'.");
 		if(playerNotebook[playerid][param1][cNumber] == 0)
 		    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido. Mas info en '/agenda ver'.");

 		playerNotebook[playerid][param1][cNumber] = 0;
 		strmid(playerNotebook[playerid][param1][cName], " ", 0, strlen(" "));
		SaveNotebookContact(playerid, param1, CONTACT_DELETE);
		SendClientMessage(playerid, COLOR_WHITE, "Has borrado el contacto del slot indicado.");
		return 1;
	}
	
	else if(!strcmp("ver", cmd, true))
	{
	    ShowNotebook(playerid);
	}
	
	else
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [ver - agregar - borrar]");

	return 1;
}
