#if defined _isamp_slotsystem_included
	#endinput
#endif
#define _isamp_slotsystem_included

//=============================SISTEMA DE SLOTS=================================

//===============================FUNCIONES======================================

forward OnSlotsInfoDataLoad(type, id);
forward LoadTrunksSlotsInfo();

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock LoadTrunksSlotsInfo() {
	new
		query[128],
		id = 1;

	while(id < MAX_VEH) {
	    format(query, sizeof(query), "SELECT * FROM `slots_info` WHERE `Type`= %d AND `Id` = %d", SLOT_TYPE_TRUNK, id);
  		mysql_function_query(dbHandle, query, true, "OnSlotsInfoDataLoad", "ii", SLOT_TYPE_TRUNK, id);
		id++;
	}
	return 1;
}

public OnSlotsInfoDataLoad(type, id) {
   	new
   	    result[128],
		rows,
		fields,
		aux = 0, // Desde el primer registro obtenido que se almacena en posicion cero dentro de los resultados
		slot;

	cache_get_data(rows, fields);

	if(rows) {
	    switch(type) {
			case SLOT_TYPE_TRUNK: {
				while(aux < rows) {
			    	cache_get_field_content(aux, "Slot", result); slot = strval(result);
					cache_get_field_content(aux, "Item", result); TrunkInfo[id][slot][Item] = strval(result);
					cache_get_field_content(aux, "Amount", result); TrunkInfo[id][slot][Amount] = strval(result);
					aux ++;
				}
			}
		}
	}
	return 1;
}

stock SaveSlotInfo(type, id, slot)
{
    new query[256];

	if(dontsave)
		return 1;

	switch(type)
	{
		case SLOT_TYPE_TRUNK:
  		{
			if(TrunkInfo[id][slot][Item] > 0) // Si el llamado a esta funcion fue porque guardo un arma, guardamos el registro (antes inexistente en db por estar vacio)
		 	{
				format(query, sizeof(query), "INSERT INTO `slots_info` (Type, Id, Slot, Item, Amount) VALUES (%d, %d, %d, %d, %d)",
					type,
					id,
					slot,
					TrunkInfo[id][slot][Item],
					TrunkInfo[id][slot][Amount]
				);
			} else // Caso contrario, si tomaron el arma, entonces el registro existia en DB ya que no era vacio, por ende lo borramos
			    {
		 	   		format(query, sizeof(query), "DELETE FROM `slots_info` WHERE `Type`= %d AND `Id` = %d AND `Slot` = %d",
				    	type,
				    	id,
				    	slot
					);
				}
		}
	}
  	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}
