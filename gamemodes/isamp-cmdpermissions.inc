#if defined _cmdpermissions_included
	#endinput
#endif
#define _cmdpermissions_included

/**
* Isamp CmdPermissions by Nevermore
* This script implements a configurable permission system
**/

new const MAP_CMD_PERMISSIONS = 0;


stock checkCmdPermission(cmdstring[], level)
{
    new i=0;
    while(cmdstring[i]!=0){ 
        cmdstring[i]=tolower(cmdstring[i]);
        i++;
    }

    if(map_contains(MAP_CMD_PERMISSIONS,cmdstring)){
        return map_get(MAP_CMD_PERMISSIONS,cmdstring)<=level;
    }
    
	return 1;
}


stock setCmdPermission(cmdstring[],level){	
    new query[128];
    
	if(map_contains(MAP_CMD_PERMISSIONS,cmdstring))
	    map_remove(MAP_CMD_PERMISSIONS,cmdstring);
	    
	map_insert(MAP_CMD_PERMISSIONS,cmdstring,level);
	format(query, sizeof(query),"INSERT INTO commands (command,level) values('%s',%d) ON DUPLICATE KEY UPDATE level=values(level)",cmdstring,level);
	mysql_function_query(dbHandle,query,false,"","");
	return 0;
}

stock loadCmdPermissions(){
	mysql_function_query(dbHandle, "SELECT * FROM commands", true, "OnCmdListRecovered", "", "");
}

forward OnCmdListRecovered();
public OnCmdListRecovered(){
	new fields,i,command[32],result[128],cmdcount,level;
	cache_get_data(cmdcount, fields);
	map_clear(MAP_CMD_PERMISSIONS);
	for(i=0;i<cmdcount;i++){
		cache_get_field_content(i, "command", command);
		cache_get_field_content(i, "level", result); level = strval(result);
	    map_insert(MAP_CMD_PERMISSIONS,command,level);
	}
	return 1;
}

CMD:nivelcomando(playerid,params[]){
	new cmdstring[64];
	new level;

	if(!sscanf(params,"s[64]i",cmdstring,level) && cmdstring[0]=='/')
		setCmdPermission(cmdstring,level);
	else
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /nivelcomando /[comando] [nivel]");
	
	return 1;
}
