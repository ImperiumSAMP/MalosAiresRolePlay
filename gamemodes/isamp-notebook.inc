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
	cName[30]
};

new playerNotebook[MAX_PLAYERS][MAX_NOTEBOOK_CONTACTS][contactInfo];

//==================================FUNCIONES===================================

forward OnNotebookDataLoad(playerid);
forward SaveNotebookContact(playerid, contactslot, option);

//==========================IMPLEMENTACION DE FUNCIONES=========================

bool:AddNotebookContact(playerid, number, const contact[])
{
	if(IsPlayerConnected(playerid))
	{
		for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
		{
		    if(playerNotebook[playerid][i][cNumber] == 0)
		    {
		        new str[30];
		        strmid(str, contact, 0, strlen(contact));
		        mysql_real_escape_string(str, str);
		        playerNotebook[playerid][i][cNumber] = number;
		        strmid(playerNotebook[playerid][i][cName], str, 0, strlen(str));
				SaveNotebookContact(playerid, i, CONTACT_CREATE);
				return true;
			}
		}
	}
	return false;
}

bool:DeleteNotebookContact(playerid, slot)
{
	if(IsPlayerConnected(playerid) && slot >= 0 && slot < MAX_NOTEBOOK_CONTACTS)
	{
 		if(playerNotebook[playerid][slot][cNumber] != 0)
   		{
     		playerNotebook[playerid][slot][cNumber] = 0;
     		strmid(playerNotebook[playerid][slot][cName], " ", 0, strlen(" "));
			SaveNotebookContact(playerid, slot, CONTACT_DELETE);
			return true;
		}
	}
	return false;
}

ShowNotebook(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new str[1000] = "";
	    
	    for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
	    {
	        if(playerNotebook[playerid][i][cNumber] != 0)
				format(str, sizeof(str), "%s[%d] %s - %d\n", str, i, playerNotebook[playerid][i][cName], playerNotebook[playerid][i][cNumber]);
		}
		if(!strcmp("", str, true))
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
			cache_get_field_content(aux, "Name",                playerNotebook[playerid][slot][cName], 1, 30);
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
		format(query, sizeof(query), "INSERT INTO `contacts_info` (`pId`, `Slot`, `Number`, `Name`) VALUES (%d, %d, %d, %s)",
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
	new cmd[20], param1, param2[30];

	if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un telefono con agenda de contactos!");
	if(sscanf(params, "s[20]I(-1)S(-1)[30]", cmd, param1, param2))
	{
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [comando]");
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} ver - agregar [numero] [nombre] - borrar [slot]");
	    return 1;
	}
	if(!strcmp("agregar", cmd, true))
	{
	    if(strval(param2) == -1)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda agregar [numero] [nombre]");
		if(param1 < 0 || strlen(param2) >= 30)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El numero no puede ser menor a 0 / Solo puedes usar una descripción de hasta 29 caracteres.");
		if(AddNotebookContact(playerid, param1, param2))
		    return SendClientMessage(playerid, COLOR_WHITE, "Contacto agregado. Utiliza '/agenda ver' para ver con mas detalle tu agenda.");
		else
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes mas espacio en tu agenda y no se pudo agregar el contacto.");
	}
	else if(!strcmp("borrar", cmd, true))
	{
		if(param1 < 0 || param1 >= MAX_NOTEBOOK_CONTACTS)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido. Mas info en '/agenda ver'.");
		if(DeleteNotebookContact(playerid, param1))
			return SendClientMessage(playerid, COLOR_WHITE, "Has borrado el contacto del slot indicado.");
		else
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido. Mas info en '/agenda ver'.");
	}
	else if(!strcmp("ver", cmd, true))
	{
	    ShowNotebook(playerid);
	}
	else
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [ver - agregar - borrar]");
	return 1;
}
