#if defined _marp_container_included
	#endinput
#endif
#define _marp_container_included

////////////////////////////////////////////////////////////////////////////////
/*
		ESTRUCTURA DE UN CONTENEDOR USANDO VECTORES DINAMICOS
	 	 _______________________________________________________
	   	|    |    |    |    |    |    |    |    |    |    |    |
		| 0  | 1  | 2  | 3  | 4  | 5  |  6 | 7  | 8  | 9  | ...|
	    |    |    |    |    |    |    |    |    |    |    |    |
     	|____|____|____|____|____|____|____|____|____|____|____|

      0: SQLID del contenedor
      1: Mínimo espacio de item aceptado
      2: Espacio total del contenedor
      3: Espacio usado del contenedor
      4: Item1
      5: Param1
      6: Item2
      7: Param2
      8: Item3
      9: Param3
      ...
*/
////////////////////////////////////////////////////////////////////////////////

#define CONTAINER_TYPE_TRUNK     		1
#define CONTAINER_TYPE_INV  	   		2
#define CONTAINER_TYPE_POCKET    		3
#define CONTAINER_TYPE_HOUSE    		4
#define CONTAINER_TYPE_ITEM      		5

#define CONTAINER_INDEX_SQLID			0
#define CONTAINER_INDEX_MIN_ITEM_SPACE  1
#define CONTAINER_INDEX_TOTAL_SPACE 	2
#define CONTAINER_INDEX_USED_SPACE   	3

enum ContainerSelectionInfo {
	csId,
	csType,
	csOriginalId
}

new Container_Selection[MAX_PLAYERS][ContainerSelectionInfo];

//==============================================================================

ResetContainerSelection(playerid)
{
   	Container_Selection[playerid][csId] = 0;
	Container_Selection[playerid][csType] = 0;
	Container_Selection[playerid][csOriginalId] = 0;
}

//==============================================================================

Container_Load(container_sqlid)
{
	new query[128];
	new container_id = vector_create();

	vector_push_back(container_id, container_sqlid); // Guarda la sqlid de si mismo.
	vector_push_back(container_id, 0); // Inicializamos donde se va a guardar el espacio mínimo por item.
	vector_push_back(container_id, 0); // Inicializamos donde se va a guardar el espacio total del contenedor.
	vector_push_back(container_id, 0); // Inicializamos donde se va a guardar el espacio usado del contenedor.

 	format(query, sizeof(query), "SELECT * FROM `containers` WHERE container = %d LIMIT 1", container_sqlid);
	mysql_function_query(dbHandle, query, true, "OnContainerDataLoad", "i", container_id);

 	format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE container = %d", container_sqlid);
	mysql_function_query(dbHandle, query, true, "OnContainerSlotsLoad", "i", container_id);

	return container_id;
}

//==============================================================================

forward OnContainerDataLoad(container_id);
public OnContainerDataLoad(container_id)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows)
	{
		cache_get_field_content(0, "MinItemSpace", result); vector_set(container_id, CONTAINER_INDEX_MIN_ITEM_SPACE, strval(result));
		cache_get_field_content(0, "TotalSpace", result); 	vector_set(container_id, CONTAINER_INDEX_TOTAL_SPACE, strval(result));
		cache_get_field_content(0, "UsedSpace", result); 	vector_set(container_id, CONTAINER_INDEX_USED_SPACE, strval(result));
	}
	return 1;
}

//==============================================================================

forward OnContainerSlotsLoad(container_id);
public OnContainerSlotsLoad(container_id)
{
	new rows,
		fields,
		result[32];

	cache_get_data(rows, fields);

	if(rows)
	{
	    for(new i = 0; i < rows; i++)
	    {
			cache_get_field_content(i, "Item", result); 	vector_push_back(container_id, strval(result));
			cache_get_field_content(i, "Amount", result); 	vector_push_back(container_id, strval(result));
		}
	}
	return 1;
}

//==============================================================================

stock Item_GetOccupiedSpace(item, param = 0)
{
	// if(space depende de parametro && param != 0)
	// 		return Items[itemid][iSpace] * param
	// else
	//      return Items[itemid][iSpace]
	return 65;
}

//==============================================================================

Container_Create(total_space, min_item_space, &container_id, &container_sqlid)
{
	if(total_space > 0) // Espacio válido
	{
		new query[128];

		format(query, sizeof(query), "INSERT INTO containers (MinItemSpace, TotalSpace) VALUES (%d, %d)", min_item_space, total_space);
		mysql_function_query(dbHandle, query, false, "", "");

		container_sqlid = cache_insert_id(dbHandle);
		SendFMessage(0, -1, "[DEBUG] referenced container_sqlid = %d", container_sqlid);

		container_id = vector_create();

		SendFMessage(0, -1, "[DEBUG] referenced container_id = %d", container_id);

  		vector_push_back(container_id, container_sqlid); // Su propia sqlid
		vector_push_back(container_id, min_item_space); // Minimo espacio por item que permite
		vector_push_back(container_id, total_space); // Espacio total
		vector_push_back(container_id, 0); // Espacio usado
		return 1;
	}

	return 0;
}

//==============================================================================

Container_Destroy(id, container_sqlid)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    new query[128];

	    format(query, sizeof(query), "DELETE FROM `containers` WHERE `container` = %d", container_sqlid);
	    mysql_function_query(dbHandle, query, false, "", "");

	    SendFMessage(0, -1, "[DEBUG] Borrando id %d con sqlid %d de containers", id, container_sqlid);

	    format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `container` = %d", container_sqlid);
	    mysql_function_query(dbHandle, query, false, "", "");

	    SendFMessage(0, -1, "[DEBUG] Borrando id %d con sqlid %d de slots_info", id, container_sqlid);

		vector_destroy(id);

		SendFMessage(0, -1, "[DEBUG] Borrando vector id %d", id);

		return 1;
	}

	return 0;
}

//==============================================================================

Container_AddUsedSpace(id, space)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
		vector_set(id, CONTAINER_INDEX_USED_SPACE, vector_get(id, CONTAINER_INDEX_USED_SPACE) + space);
		
		new query[128];

		format(query, sizeof(query), "UPDATE containers SET UsedSpace = %d WHERE container = %d", Container_GetUsedSpace(id), Container_GetSQLID(id));
		mysql_function_query(dbHandle, query, false, "", "");
		
		return 1;
	}

	return 0;
}

//==============================================================================

Container_GetTotalSpace(id)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_TOTAL_SPACE);

	return 0;
}

//==============================================================================

Container_GetUsedSpace(id)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_USED_SPACE);

	return 99999;
}

//==============================================================================

Container_GetElementsAmount(id)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return (vector_size(id) - 4) / 2;

	return 99999;
}

//==============================================================================

Container_GetSQLID(id)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_SQLID);

	return 0;
}

//==============================================================================

stock Container_SlotToVecIndex(container_slot)
{
	return (container_slot + 2) * 2;
}

//==============================================================================

stock Container_VecIndexToSlot(vec_index)
{
	return (vec_index - 4) / 2;
}

//==============================================================================

Container_AddItemAndParam(id, item, param)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
		if(Container_GetUsedSpace(id) + Item_GetOccupiedSpace(item, param) > Container_GetTotalSpace(id)) // No hay espacio para meter el peso del item
		    return 0;

		vector_push_back(id, item);
		vector_push_back(id, param);

		Container_AddUsedSpace(id, Item_GetOccupiedSpace(item, param));

		Container_UpdateOpenedDialogs(id);

 		new query[150];

		format(query, sizeof(query), "INSERT INTO slots_info (container, Item, Amount) VALUES (%d, %d, %d)", Container_GetSQLID(id), item, param);
		mysql_function_query(dbHandle, query, false, "", "");
		return 1;
	}

	return 0;
}

//==============================================================================

Container_TakeItem(id, slot, &item, &param)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    if(slot < 0 || slot >= Container_GetElementsAmount(id)) // Slot inválido
	        return 0;

		new vec_index = Container_SlotToVecIndex(slot);

		item = vector_get(id, vec_index);
	    param = vector_get(id, vec_index + 1);

		vector_remove(id, vec_index);
		vector_remove(id, vec_index);

		Container_AddUsedSpace(id, -Item_GetOccupiedSpace(item, param));

		Container_UpdateOpenedDialogs(id);

 		new query[150];

		format(query, sizeof(query), "DELETE FROM slots_info WHERE container = %d AND Item = %d AND Amount = %d LIMIT 1", Container_GetSQLID(id), item, param);
		mysql_function_query(dbHandle, query, false, "", "");
		return 1;
	}

	return 0;
}

//==============================================================================

Container_UpdateOpenedDialogs(id)
{
	foreach(new i : Player)
	{
	    if(Container_Selection[i][csId] == id && Dialog_Opened(i)) // Si tiene abierto el dialog de ese contenedor
	    {
	        Dialog_Close(i);
	        Container_Show(Container_Selection[i][csOriginalId], Container_Selection[i][csType], id, i);
		}
	}
}

//==============================================================================

Container_Show(origid, type, id, playerid)
{
	if(vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
		new string1[128],
		    string2[3500] = "";

		new vsize = vector_size(id),
		    slot = 0;

		for(new i=4; i<vsize; i+=2)
		{
		    format(string2, sizeof(string2), "%s%d - Item: %d\tParam: %d\n", string2, slot, vector_get(id, i), vector_get(id, i+1));
            slot++;
		}
		format(string1, sizeof(string1), "Contenedor * Espacio: usado %du - libre %du", Container_GetUsedSpace(id), Container_GetTotalSpace(id) - Container_GetUsedSpace(id));
		Dialog_Show(playerid, DLG_SHOW_CONTAINERS, DIALOG_STYLE_TABLIST, string1, string2, "Tomar", "Cerrar");

		Container_Selection[playerid][csId] = id;
		Container_Selection[playerid][csType] = type; // Para saber si es casa, etc, y saber luego comprobar distancias, q esté abierto, etc
		Container_Selection[playerid][csOriginalId] = origid; // Para saber sobre cual id de casa, auto, etc hay que comprobar
		// para saber después que item agarró, te fiajs con el slot (listitem), y no hace falta mas quilombo porque siempre va a estar actualizado gracias a updateopeneddialogs
		return 1;
	}

	return 0;
}

//==============================================================================

Dialog:DLG_SHOW_CONTAINERS(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	    SendFMessage(playerid, COLOR_WHITE, "Vector ID %d, Tipo %d e id original es %d", Container_Selection[playerid][csId], Container_Selection[playerid][csType], Container_Selection[playerid][csOriginalId]);
        SendFMessage(playerid, COLOR_WHITE, "Seleccionó del slot %d el item: %d, param: %d", listitem, vector_get(Container_Selection[playerid][csId], Container_SlotToVecIndex(listitem)), vector_get(Container_Selection[playerid][csId], Container_SlotToVecIndex(listitem)+1));
        new item, param;
		if(!Container_TakeItem(Container_Selection[playerid][csId], listitem, item, param))
	        SendClientMessage(playerid, COLOR_WHITE, "Vacio / slot inválido");
		SendFMessage(playerid, -1, "response con item %d y param %d", item, param);
	}
	else
	{
		SendClientMessage(playerid, -1, "no response");
	}
	ResetContainerSelection(playerid);
	return 1;
}

//==============================================================================

CMD:arm2(playerid, params[])
{
	new cmd[32],
	    slot;

	new houseid = GetPlayerHouse(playerid);
	
	if(sscanf(params, "s[32]I(-1)", cmd, slot))
	    return SendClientMessage(playerid, COLOR_WHITE, "/arm [cmd]   - cmds: tomar, guardar , ver");

	if(!strcmp("guardar", cmd, true))
	{
	    new item = 1+random(500),
	        param = 1+random(4000);

	    if(!Container_AddItemAndParam(House[houseid][ContainerID], item, param))
	        return SendClientMessage(playerid, COLOR_WHITE, "Máximo de espacio alcanzado");

	    SendFMessage(playerid, COLOR_WHITE, "Guardando item %d, param %d", item, param);
	}
	else if(!strcmp("tomar", cmd, true))
	{
	    new item, param;
	    if(!Container_TakeItem(House[houseid][ContainerID], slot, item, param))
	        return SendClientMessage(playerid, COLOR_WHITE, "Vacio / slot inválido");

        SendFMessage(playerid, COLOR_WHITE, "Tomando item %d, param %d", item, param);
	}
	else if(!strcmp("ver", cmd, true))
	{
	    if(!Container_Show(houseid, CONTAINER_TYPE_HOUSE, House[houseid][ContainerID], playerid))
	        return SendClientMessage(playerid, COLOR_WHITE, "Vacio");
	    SendClientMessage(playerid, COLOR_WHITE, "Mostrando");
	}
	return 1;
}

//==============================================================================

CMD:containerdebug(playerid, params[])
{
	new hid;
	
	if(sscanf(params, "I(1)", hid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /containerdebug [houseid[");

	SendFMessage(playerid, -1, "House[ContainerID] = %d, House[ContainerSQLID] = %d", House[hid][ContainerID], House[hid][ContainerSQLID]);
	SendFMessage(playerid, -1, "container inicializo con total: %d, used: %d", vector_get(House[hid][ContainerID], CONTAINER_INDEX_TOTAL_SPACE), vector_get(House[hid][ContainerID], CONTAINER_INDEX_USED_SPACE));
    SendFMessage(playerid, -1, "container inicializo con sqlid: %d, minimo item space: %d", vector_get(House[hid][ContainerID], CONTAINER_INDEX_SQLID), vector_get(House[hid][ContainerID], CONTAINER_INDEX_MIN_ITEM_SPACE));
	SendFMessage(playerid, -1, "last sqlid: %d", cache_insert_id(dbHandle));
	return 1;
}

