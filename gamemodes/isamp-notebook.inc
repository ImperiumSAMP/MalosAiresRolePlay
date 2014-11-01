#if defined _isamp_notebook_included
	#endinput
#endif
#define _isamp_notebook_included

//===========================SISTEMA DE AGENDAS=================================

//===============================CONSTANTES=====================================

#define MAX_NOTEBOOK_CONTACTS       15
#define DLG_NOTEBOOK				10025

//===============================DATA STORAGE===================================

enum contactInfo {
	cNumber,
	cNote[30]
};

new playerNotebook[MAX_PLAYERS][MAX_NOTEBOOK_CONTACTS][contactInfo];

//==========================IMPLEMENTACION DE FUNCIONES=========================

bool:AddNotebookContact(playerid, number, const contact[])
{
	if(IsPlayerConnected(playerid))
	{
		for(new i = 0; i < MAX_NOTEBOOK_CONTACTS; i++)
		{
		    if(playerNotebook[playerid][i][cNumber] == 0)
		    {
		        playerNotebook[playerid][i][cNumber] = number;
		        strmid(playerNotebook[playerid][i][cNote], contact, 0, strlen(contact));
				//SaveNotebookSlot(playerid, i);
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
     		strmid(playerNotebook[playerid][slot][cNote], " ", 0, strlen(" "));
			//SaveNotebookSlot(playerid, slot);
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
				format(str, sizeof(str), "%s[%d] %s - %d/n", str, i, playerNotebook[playerid][i][cNote], playerNotebook[playerid][i][cNumber]);
		}
		if(!strcmp("", str, true))
		    format(str, sizeof(str), "No hay contactos agregados.");
		ShowPlayerDialog(playerid, DLG_NOTEBOOK, DIALOG_STYLE_LIST, "Contactos", str, "Cerrar", "");
	}
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
	    SendFMessage(playerid, COLOR_YELLOW, "[%d][%d] cNote = %s", id, i, playerNotebook[id][i][cNote]);
	}
	return 1;
}

//====================================COMANDOS==================================

CMD:agenda(playerid, params[])
{
	new cmd[20], param1, param2[30];

	if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes un telefono con agenda de contactos!");
	if(sscanf(params, "s[20]", cmd))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [ver - agregar - borrar]");

	if(!strcmp("agregar", cmd, true))
	{
  		if(sscanf(params, "s[20]is[30]", cmd, param1, param2))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda agregar [numero] [descripción] (hasta 29 caracteres)");
		if(param1 == 0 || sizeof(param2) >= 30)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El numero no puede ser 0 (cero) / Solo puedes usar una descripción de hasta 29 caracteres.");
		if(AddNotebookContact(playerid, param1, param2))
		    return SendClientMessage(playerid, COLOR_WHITE, "Contacto agregado. Utiliza '/agenda ver' para ver con mas detalle tu agenda.");
		else
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes mas espacio en tu agenda y no se pudo agregar el contacto.");
	}
	else if(strcmp("borrar", cmd, false) != 0)
	{
		if(sscanf(params, "s[20]i", cmd, param1))
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda borrar [slot]");
		if(param1 < 0 || param1 >= MAX_NOTEBOOK_CONTACTS)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido. Mas info en '/agenda ver'.");

		if(DeleteNotebookContact(playerid, param1))
			return SendClientMessage(playerid, COLOR_WHITE, "Has borrado el contacto del slot indicado.");
		else
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Ese slot está vacio.");
	}
	else if(strcmp("ver", cmd, false) != 0)
	{
	    ShowNotebook(playerid);
	}
	else
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /agenda [ver - agregar - borrar]");
	return 1;
}
