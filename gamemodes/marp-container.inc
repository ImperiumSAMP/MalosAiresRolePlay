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

Container_Create(total_space, min_item_space, &container_id, &container_sqlid)
{
	if(total_space > 0) // Espacio válido
	{
		new query[128];

        new sqlid_address = GetVariableAddress(container_sqlid); // Guarda la dirección de memoria de la variable donde hay que guardar la SQLID creada con la query INSERT.

        container_id = vector_create();
        
		format(query, sizeof(query), "INSERT INTO containers (MinItemSpace, TotalSpace) VALUES (%d, %d)", min_item_space, total_space);
		mysql_function_query(dbHandle, query, true, "GetContainerInsertedId", "dd", container_id, sqlid_address);

  		vector_push_back(container_id, 0); // Reservado para su SQLID
		vector_push_back(container_id, min_item_space); // Minimo espacio por item que permite
		vector_push_back(container_id, total_space); // Espacio total
		vector_push_back(container_id, 0); // Espacio usado
		return 1;
	}

	return 0;
}

forward GetContainerInsertedId(container_id, address);
public GetContainerInsertedId(container_id, address)
{
	new last_id = cache_insert_id(dbHandle);
    @ptr[address] = last_id;
    vector_set(container_id, CONTAINER_INDEX_SQLID, last_id);
    return 1;
}

//==============================================================================

Container_Destroy(id, container_sqlid)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    new query[128];

	    format(query, sizeof(query), "DELETE FROM `containers` WHERE `container` = %d", container_sqlid);
	    mysql_function_query(dbHandle, query, false, "", "");

	    format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `container` = %d", container_sqlid);
	    mysql_function_query(dbHandle, query, false, "", "");

		vector_destroy(id);
		
		return 1;
	}

	return 0;
}

//==============================================================================

Container_AddUsedSpace(id, space)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
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
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
     return vector_get(id, CONTAINER_INDEX_TOTAL_SPACE);

	return 0;
}

//==============================================================================

stock Container_SetTotalSpace(id, total_space)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    vector_set(id, CONTAINER_INDEX_TOTALSPACE, total_space);

		new query[128];

		format(query, sizeof(query), "UPDATE containers SET TotalSpace = %d WHERE container = %d", total_space, Container_GetSQLID(id));
		mysql_function_query(dbHandle, query, false, "", "");

		return 1;
	}
	return 0;
}

//==============================================================================

Container_GetUsedSpace(id)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_USED_SPACE);

	return 99999;
}

//==============================================================================

Container_GetElementsAmount(id)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return (vector_size(id) - 4) / 2;

	return 99999;
}

//==============================================================================

Container_GetSQLID(id)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_SQLID);

	return 0;
}

//==============================================================================

Container_GetMinItemSpace(id)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	    return vector_get(id, CONTAINER_INDEX_MIN_ITEM_SPACE);

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

Container_Empty(id)
{
    if(id > 0 && vector_size(id) > 3)
    {
  		new query[128];

        new vec_sqlid = vector_get(id, CONTAINER_INDEX_SQLID);
		new vec_min_item_space = vector_get(id, CONTAINER_INDEX_MIN_ITEM_SPACE);
		new vec_total_space = vector_get(id, CONTAINER_INDEX_TOTAL_SPACE);
		
	    format(query, sizeof(query), "UPDATE containers SET UsedSpace = 0 WHERE container = %d", vec_sqlid);
		mysql_function_query(dbHandle, query, false, "", "");

	    format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `container` = %d", vec_sqlid);
	    mysql_function_query(dbHandle, query, false, "", "");
	    
		vector_clear(id);
		
		vector_push_back(id, vec_sqlid);
		vector_push_back(id, vec_min_item_space);
		vector_push_back(id, vec_total_space);
		vector_push_back(id, 0);
		
		return 1;
	}

	return 0;
}

//==============================================================================

Container_AddItemAndParam(id, item, param)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
		if(Container_GetUsedSpace(id) + GetItemSpace(item, param) > Container_GetTotalSpace(id)) // No hay espacio para meter el peso del item
		    return 0;

		vector_push_back(id, item);
		vector_push_back(id, param);

		Container_AddUsedSpace(id, GetItemSpace(item, param));

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
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    if(slot < 0 || slot >= Container_GetElementsAmount(id)) // Slot inválido
	        return 0;

		new vec_index = Container_SlotToVecIndex(slot);

		item = vector_get(id, vec_index);
	    param = vector_get(id, vec_index + 1);

		vector_remove(id, vec_index);
		vector_remove(id, vec_index);

		Container_AddUsedSpace(id, -GetItemSpace(item, param));

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
	foreach(new playerid : Player)
	{
	    if(Container_Selection[playerid][csId] == id && Dialog_Opened(playerid)) // Si tiene abierto el dialog de ese contenedor
	    {
	        Dialog_Close(playerid);
		    Container_Show(Container_Selection[playerid][csOriginalId], Container_Selection[playerid][csType], id, playerid);
		}
	}
}

//==============================================================================

Container_Show(origid, type, id, playerid)
{
	if(id > 0 && vector_size(id) > 3) // Está creado (tiene al menos los 3 elementos que se generan al crearlo)
	{
	    new string1[128];
	    
	    if(Container_GetElementsAmount(id) > 0)
	    {
			new string2[3500] = "";

			new vsize = vector_size(id),
			    slot = 0;

			for(new i=4; i<vsize; i+=2)
			{
			    format(string2, sizeof(string2), "%s%d - Item: %d\tParam: %d\n", string2, slot, vector_get(id, i), vector_get(id, i+1));
	            slot++;
			}
			format(string1, sizeof(string1), "Contenedor * Espacio: usado %du - libre %du", Container_GetUsedSpace(id), Container_GetTotalSpace(id) - Container_GetUsedSpace(id));
			Dialog_Show(playerid, DLG_SHOW_CONTAINER, DIALOG_STYLE_TABLIST, string1, string2, "Tomar", "Cerrar");

			Container_Selection[playerid][csId] = id;
			Container_Selection[playerid][csType] = type; // Para saber si es casa, etc, y saber luego comprobar distancias, q esté abierto, etc
			Container_Selection[playerid][csOriginalId] = origid; // Para saber sobre cual id de casa, auto, etc hay que comprobar
			// para saber después que item agarró, te fiajs con el slot (listitem), y no hace falta mas quilombo porque siempre va a estar actualizado gracias a updateopeneddialogs
		}
		else
		{
			format(string1, sizeof(string1), "Contenedor * Espacio: usado %du - libre %du", Container_GetUsedSpace(id), Container_GetTotalSpace(id) - Container_GetUsedSpace(id));
			Dialog_Show(playerid, DLG_SHOW_EMPTY_CONTAINER, DIALOG_STYLE_MSGBOX, string1, "Vacio", "Cerrar", "");
		}
		return 1;
	}

	return 0;
}

//==============================================================================

Dialog:DLG_SHOW_CONTAINER(playerid, response, listitem, inputtext[])
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
	new id;
	new type;
	
	if(sscanf(params, "iI(1)", type, id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /containerdebug [tipo] [houseid/vehicleid]");

	if(type == 1)
	{
		SendFMessage(playerid, -1, "Veh[ContainerID] = %d, Veh[ContainerSQLID] = %d", VehicleInfo[id][VehContainerID], VehicleInfo[id][VehContainerSQLID]);
		SendFMessage(playerid, -1, "container inicializo con total: %d, used: %d", Container_GetTotalSpace(VehicleInfo[id][VehContainerID]), Container_GetUsedSpace(VehicleInfo[id][VehContainerID]));
	    SendFMessage(playerid, -1, "container inicializo con sqlid: %d, minimo item space: %d", Container_GetSQLID(VehicleInfo[id][VehContainerID]), Container_GetMinItemSpace(VehicleInfo[id][VehContainerID]));
	}
	else if(type == 4)
	{
		SendFMessage(playerid, -1, "House[ContainerID] = %d, House[ContainerSQLID] = %d", House[id][ContainerID], House[id][ContainerSQLID]);
		SendFMessage(playerid, -1, "container inicializo con total: %d, used: %d", Container_GetTotalSpace(House[id][ContainerID]), Container_GetUsedSpace(House[id][ContainerID]));
	    SendFMessage(playerid, -1, "container inicializo con sqlid: %d, minimo item space: %d", Container_GetSQLID(House[id][ContainerID]), Container_GetMinItemSpace(House[id][ContainerID]));
	}
	return 1;
}
