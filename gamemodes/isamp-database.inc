#if defined _isamp_database_included
	#endinput
#endif
#define _isamp_database_included


new 	
// No bajarle el tamaño o no funca.
 	MYSQL_HOST[256],
 	MYSQL_USER[256],
 	MYSQL_PASS[256],
 	MYSQL_DB[256],
	// Misc.
	bool:dontsave = false,
    bool:FALSE = false,
	dbHandle = 1;
	
// MySQL
forward MySQLUpdateInt(sqlplayerid,sqltable[],sqlvalname[],sqlupdateint);
forward MySQLUpdateFloat(sqlplayerid,sqltable[],sqlvalname[], Float:sqlupdateflo);
forward MySQLUpdateStr(sqlplayerid,sqltable[],sqlvalname[],sqlupdatestr[]);
forward MySQLUpdateDate(sqlplayerid,sqltable[],sqlvalname[],year,month,day,hour,minute,second);
forward MySQLConnect(sqlhost[], sqluser[], sqlpass[], sqldb[]);

stock loadMySQLcfg() {
	if(dini_Exists("isamp-data/db.cfg")) {
	    new sendcmd[128];
		MYSQL_HOST = dini_Get("isamp-data/db.cfg", "MYSQL_HOST");
		MYSQL_PASS = dini_Get("isamp-data/db.cfg", "MYSQL_PASS");
		MYSQL_USER = dini_Get("isamp-data/db.cfg", "MYSQL_USER");
		MYSQL_DB = dini_Get("isamp-data/db.cfg", "MYSQL_DB");
		format(sendcmd, sizeof(sendcmd), "password %s", dini_Get("isamp-data/db.cfg", "SERVER_PASSWORD"));
		SendRconCommand(sendcmd);
	} else {
		print("Error cargando la configuracion de la DB.");
	}
	return 1;
}

public MySQLUpdateDate(sqlplayerid,sqltable[],sqlvalname[],year,month,day,hour,minute,second) {
	new query[256];
	format(query, sizeof(query), "UPDATE `%s` SET `%s` = '%02d-%02d-%02d %02d:%02d:%02d' WHERE `Id`=%d",sqltable,sqlvalname, year, month, day, hour, minute, second, sqlplayerid);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

public MySQLUpdateInt(sqlplayerid,sqltable[],sqlvalname[],sqlupdateint) {
	new query[256];
	format(query,sizeof(query),"UPDATE `%s` SET `%s`=%d WHERE `Id` =%d",sqltable,sqlvalname,sqlupdateint,sqlplayerid);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

public MySQLUpdateFloat(sqlplayerid,sqltable[],sqlvalname[], Float:sqlupdateflo) {
	new query[256];
	format(query,sizeof(query),"UPDATE `%s` SET `%s`=%f WHERE `Id`=%d",sqltable,sqlvalname,sqlupdateflo,sqlplayerid);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

public MySQLUpdateStr(sqlplayerid,sqltable[],sqlvalname[],sqlupdatestr[]) {
	new query[256];
	mysql_real_escape_string(sqlupdatestr,sqlupdatestr);
	format(query,sizeof(query),"UPDATE `%s` SET `%s`='%s' WHERE `Id`=%d",sqltable,sqlvalname,sqlupdatestr,sqlplayerid);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}
