#if defined _marp_skillguns_included
	#endinput
#endif
#define _marp_skillguns_included

//=================================DEFINES======================================
#define MAX_OBJECT_POS      10 //Maximo de pos definidas
#define MAX_SKILL_OBJECT    30 //Maximo de creación de objetos
#define SKILLS_START            	1
#define SKILLS_UPDATE             	2

//==================================NEWS========================================
new trainningshot[MAX_PLAYERS] = 0;
new skillvalue = 0;
new skillobject[MAX_SKILL_OBJECT] = 0;
new SkillCount[MAX_PLAYERS] = 0;
new ShootCount[MAX_PLAYERS] = 0;
new SkillObjCounter = 0;
new SkillTimerCount = 0;
new SkillGun[MAX_PLAYERS] = 0;
new TimerSkills[MAX_PLAYERS];

//==================================FORWARDS========================================
forward OnSkillsGunsJDataLoad(playerid);
forward SkillsGuns(playerid, type);
forward Results9mm(playerid);
forward ResultsDeagle(playerid);
forward ResultsShotgun(playerid);
forward ResultsSkillsGun(playerid);
forward SkillsDynamicObjectsLevelOne(playerid);
forward SkillsDynamicObjectsLevelTwo(playerid);
forward SkillsDynamicObjectsLevelThree(playerid);
forward TimeForTrainning(playerid);
//==================================ENUM========================================
enum SkillGunsInfo {
	pName[24],
	pSkillLevel9mm,
	pSkillLevelDeagle,
	pSkillLevelShotgun,
	pSkillLevelTimer9mm,
	pSkillLevelTimerDeagle,
	pSkillLevelTimerShotgun,
	pFirstTraining,
};

new SkillsInfo[MAX_PLAYERS][SkillGunsInfo];

static const Float:SKILL_OBJECT_POSLEVEL1[MAX_OBJECT_POS][3] = {
    {289.7941,-127.3995,1004.0625},
	{289.7941,-132.3995,1004.0625},
	{289.7941,-134.3995,1004.0625},
	{289.7941,-137.3995,1004.0625},
	{289.7941,-135.3995,1004.0625},
	{289.7941,-133.3995,1004.0625},
	{289.7941,-131.3995,1004.0625},
	{289.7941,-129.3995,1004.0625},
	{289.7941,-138.3995,1004.0625},
	{289.7941,-136.3995,1004.0625}

};
static const Float:SKILL_OBJECT_POSLEVEL2[MAX_OBJECT_POS][3] = {
    {282.7941,-127.3995,1004.0625},
	{282.7941,-132.3995,1004.0625},
	{282.7941,-134.3995,1004.0625},
	{282.7941,-137.3995,1004.0625},
	{282.7941,-135.3995,1004.0625},
	{282.7941,-133.3995,1004.0625},
	{282.7941,-131.3995,1004.0625},
	{282.7941,-129.3995,1004.0625},
	{282.7941,-138.3995,1004.0625},
	{282.7941,-136.3995,1004.0625}

};
static const Float:SKILL_OBJECT_POSLEVEL3[MAX_OBJECT_POS][3] = {
    {275.7941,-127.3995,1004.0625},
	{275.7941,-132.3995,1004.0625},
	{275.7941,-134.3995,1004.0625},
	{275.7941,-137.3995,1004.0625},
	{275.7941,-135.3995,1004.0625},
	{275.7941,-133.3995,1004.0625},
	{275.7941,-131.3995,1004.0625},
	{275.7941,-129.3995,1004.0625},
	{275.7941,-138.3995,1004.0625},
	{275.7941,-136.3995,1004.0625}

};

//==================================RESETEO DE VARIABLES========================================
stock ResetSkillsGunsVariables(playerid){
	
	SkillsInfo[playerid][pName] = "BUGBUGBUGBUGBUGBUGBUGBU";
	SkillsInfo[playerid][pSkillLevel9mm] = 0;
	SkillsInfo[playerid][pSkillLevelDeagle] = 0;
	SkillsInfo[playerid][pSkillLevelShotgun] = 0;
	SkillsInfo[playerid][pSkillLevelTimer9mm] = 0;
	SkillsInfo[playerid][pSkillLevelTimerDeagle] = 0;
	SkillsInfo[playerid][pSkillLevelTimerShotgun] = 0;
	SkillsInfo[playerid][pFirstTraining] = 0;
	trainningshot[playerid] = 0; //Seteo la variable que me dice si esta haciendo el entrenamiento en 0
	SkillCount[playerid] = 0; //Seteo la variable de contador de objetos destruidos por playerid en 0
	SkillGun[playerid] = 0; //Seteo en 0 la variable que indica el arma que elige para hacer el entrenamiento
	ShootCount[playerid] = 0;
}

stock ResetSkillsGunsGlobalVariables(playerid){
	
	if (trainningshot[playerid] == 1)//Si esta en el sistema de skills le borro el arma cuando se desconecta
	{
		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); 
		trainningshot[playerid] = 0;
		skillvalue = 0; //Seteo la variable que verifica si alguien esta haciendo el entrenamiento(para que otro no pueda hacerlo a la vez) en 0
		SkillTimerCount = 0; //Seteo en 0 la variable  que cuenta los objetos para poder frenar el timer y terminar el sistema
		SkillObjCounter = 0; //Seteo en 0 la variable contadora de objetos que tiene un maximo de 11.. si no se reseta la variable llega a 11 y se cuelga el sist ahi
	}
}

//==================================CARGAS POR DATABASE========================================
stock loadSkillsGunsData(playerid,MysqlID){
	new		
		query[256];

    format(query, sizeof(query), "SELECT * FROM `skills_guns` WHERE accountid=%d", MysqlID);
	mysql_function_query(dbHandle, query, true, "OnSkillsGunsJDataLoad", "i", playerid);
	return 1;
}

public OnSkillsGunsJDataLoad(playerid) {
	new
		rows,
		fields,
		result[32];
	
	cache_get_data(rows, fields);
	if(rows)
	{	
		cache_get_field_content(0, "pSkillLevel9mm", result); 		    SkillsInfo[playerid][pSkillLevel9mm] 			= strval(result);
		cache_get_field_content(0, "pSkillLevelDeagle", result);		SkillsInfo[playerid][pSkillLevelDeagle] 		= strval(result);
		cache_get_field_content(0, "pSkillLevelShotgun", result);		SkillsInfo[playerid][pSkillLevelShotgun]		= strval(result);
		cache_get_field_content(0, "pSkillLevelTimer9mm", result); 		SkillsInfo[playerid][pSkillLevelTimer9mm]		= strval(result);
		cache_get_field_content(0, "pSkillLevelTimerDeagle", result); 	SkillsInfo[playerid][pSkillLevelTimerDeagle]	= strval(result);
		cache_get_field_content(0, "pSkillLevelTimerShotgun", result); 	SkillsInfo[playerid][pSkillLevelTimerShotgun]	= strval(result);
		cache_get_field_content(0, "pFirstTraining", result); 			SkillsInfo[playerid][pFirstTraining] 			= strval(result);
	}
}

public SkillsGuns(playerid, type) {
 	new playerName[24],
 		query[512];
 
 	GetPlayerName(playerid, playerName, 24);
 	mysql_real_escape_string(playerName, playerName, 1, sizeof(playerName));
 	
	if (type == SKILLS_START)
	{
		format(query, sizeof(query), "INSERT INTO `skills_guns` (accountid, pName, pSkillLevel9mm, pSkillLevelDeagle, pSkillLevelShotgun, pSkillLevelTimer9mm, pSkillLevelTimerDeagle, pSkillLevelTimerShotgun, pFirstTraining) VALUES (%d, '%s', %d, %d, %d, %d, %d, %d, %d)",
			PlayerInfo[playerid][pID],
			playerName,
			SkillsInfo[playerid][pSkillLevel9mm],
			SkillsInfo[playerid][pSkillLevelDeagle],
			SkillsInfo[playerid][pSkillLevelShotgun],
			SkillsInfo[playerid][pSkillLevelTimer9mm],
			SkillsInfo[playerid][pSkillLevelTimerDeagle],
			SkillsInfo[playerid][pSkillLevelTimerShotgun],
			SkillsInfo[playerid][pFirstTraining]
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}
	else if (type == SKILLS_UPDATE)
	{
		format(query, sizeof(query), "UPDATE `skills_guns` SET pSkillLevel9mm=%d,pSkillLevelDeagle=%d,pSkillLevelShotgun=%d,pSkillLevelTimer9mm=%d,pSkillLevelTimerDeagle=%d,pSkillLevelTimerShotgun=%d,pFirstTraining=%d WHERE `accountid`=%d",
			SkillsInfo[playerid][pSkillLevel9mm],
			SkillsInfo[playerid][pSkillLevelDeagle],
			SkillsInfo[playerid][pSkillLevelShotgun],
			SkillsInfo[playerid][pSkillLevelTimer9mm],
			SkillsInfo[playerid][pSkillLevelTimerDeagle],
			SkillsInfo[playerid][pSkillLevelTimerShotgun],
			SkillsInfo[playerid][pFirstTraining],
			getPlayerMysqlId(playerid)
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}
 	return 1;
}
 
 //==================================FUNCIONES========================================
 public TimeForTrainning(playerid){

	if(SkillGun[playerid] == 22)//Si quiere realizar el de 9mm
	{
		if(SkillsInfo[playerid][pSkillLevel9mm] < 40) //Si es lvl 1 con 9mm setea el timer level 1 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelOne", 3000, true, "i", playerid);
		}
		else if(SkillsInfo[playerid][pSkillLevel9mm] >= 40 && SkillsInfo[playerid][pSkillLevel9mm] < 900) //Si es lvl 2 con 9mm setea el timer level 2 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelTwo", 2000, true, "i", playerid);	
		}
		else if(SkillsInfo[playerid][pSkillLevel9mm] >= 900) //Si es lvl 3 con 9mm setea el timer level 3 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelThree", 1300, true, "i", playerid);			
		}
	}
	else if(SkillGun[playerid] == 24) //Si quere realizar el de Deagle
	{
		if(SkillsInfo[playerid][pSkillLevelDeagle] < 200) //Si es lvl 1 con deagle setea el timer level 1 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelOne", 3000, true, "i", playerid);
		}
		else if(SkillsInfo[playerid][pSkillLevelDeagle] >= 200 && SkillsInfo[playerid][pSkillLevelDeagle] < 900) //Si es lvl 2 con deagle setea el timer level 2 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelTwo", 2000, true, "i", playerid);	
		}
		else if(SkillsInfo[playerid][pSkillLevelDeagle] >= 900)//Si es lvl 3 con deagle setea el timer level 3 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelThree", 1300, true, "i", playerid);		
		}
	}
	else if(SkillGun[playerid] == 25)
	{
		if(SkillsInfo[playerid][pSkillLevelShotgun] < 200) //Si es lvl 1 con escopeta setea el timer level 1 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelOne", 3000, true, "i", playerid);
		}
		else if(SkillsInfo[playerid][pSkillLevelShotgun] >= 200 && SkillsInfo[playerid][pSkillLevelShotgun] < 900) //Si es lvl 2 con escopeta setea el timer level 2 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelTwo", 2000, true, "i", playerid);	
		}
		else if(SkillsInfo[playerid][pSkillLevelShotgun] >= 900) //Si es lvl 3 con escopeta setea el timer level 3 de dificultad
		{
		TimerSkills[playerid] = SetTimerEx("SkillsDynamicObjectsLevelThree", 1200, true, "i", playerid);		
		}
	}
	SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Los objetos estan a punto de salir... ¡Preparate!");
	skillvalue = 1;
	trainningshot[playerid] = 1;
}

public SkillsDynamicObjectsLevelOne(playerid) {
	new randomPos = random(MAX_OBJECT_POS),
		randomPosMove1 = random(3),
		randomPosMove2 = random(5),
		randomPosMove3 = random(1);
		
    if (SkillTimerCount != 0)
        DestroyDynamicObject(skillobject[SkillObjCounter-1]); //Borra el objeto desp de los X segundos del timer (-1 por que cuando lo crea suma la variable del contador, por lo cual para borrar el creado hay que restarle 1)
	
    skillobject[SkillObjCounter] = CreateDynamicObject(1588,SKILL_OBJECT_POSLEVEL1[randomPos][0],SKILL_OBJECT_POSLEVEL1[randomPos][1],SKILL_OBJECT_POSLEVEL1[randomPos][2], 0.0, 0.0, 0);//Creacion de objeto dinamico, posiciones segun el SKILL_OBJECT_POSLEVEL1
    MoveDynamicObject(skillobject[SkillObjCounter], (SKILL_OBJECT_POSLEVEL1[randomPos][0])+randomPosMove1, (SKILL_OBJECT_POSLEVEL1[randomPos][1])-randomPosMove2, (SKILL_OBJECT_POSLEVEL1[randomPos][2])+randomPosMove3, 2.00);//Movimiento del objeto
    SkillObjCounter++;        //Suma del contador de objeto
    Streamer_Update(playerid); //Update de streamer por que sino cuando los objetos se creaban solo los veias si te movias ya que los objetos dinamicos se actualizan solo cuando te moves, por eso forzamos la actualizacion poniendo el Streamer_Update
    if(SkillTimerCount == 9)    //Condicion de que si la variable es igual que el maximo de objetos dejamos de llamar al timer SkillsDynamicObjects para que deje de crear objetos. (TUVE QUE PONER EL NUMERO POR QUE SINO NO FUNCABA LA FUNCION CUANDO TENIA QUE ENTRAR EN EL IF)
    {
		SetTimerEx("ResultsSkillsGun", 3000, false, "i", playerid);//Luego de que llega al maximo de objetos llama a la función que muestra los resultados del "entrenamiento" luego de 4 segundos.
        KillTimer(TimerSkills[playerid]);
    }
    else
    {
        SkillTimerCount++;
    }
    return 1;
}

public SkillsDynamicObjectsLevelTwo(playerid) {
	new randomPos = random(MAX_OBJECT_POS),
		randomPosMove1 = random(3),
		randomPosMove2 = random(5),
		randomPosMove3 = random(2);
		
    if (SkillTimerCount != 0)
        DestroyDynamicObject(skillobject[SkillObjCounter-1]); //Borra el objeto desp de los X segundos del timer (-1 por que cuando lo crea suma la variable del contador, por lo cual para borrar el creado hay que restarle 1)
	
    skillobject[SkillObjCounter] = CreateDynamicObject(1588,SKILL_OBJECT_POSLEVEL2[randomPos][0],SKILL_OBJECT_POSLEVEL2[randomPos][1],SKILL_OBJECT_POSLEVEL2[randomPos][2], 0.0, 0.0, 0);//Creacion de objeto dinamico, posiciones segun el SKILL_OBJECT_POSLEVEL2
    MoveDynamicObject(skillobject[SkillObjCounter], (SKILL_OBJECT_POSLEVEL2[randomPos][0])+randomPosMove1, (SKILL_OBJECT_POSLEVEL2[randomPos][1])-randomPosMove2, (SKILL_OBJECT_POSLEVEL2[randomPos][2])+randomPosMove3, 4.00);//Movimiento del objeto
    SkillObjCounter++;        //Suma del contador de objeto
    Streamer_Update(playerid); //Update de streamer por que sino cuando los objetos se creaban solo los veias si te movias ya que los objetos dinamicos se actualizan solo cuando te moves, por eso forzamos la actualizacion poniendo el Streamer_Update
    if(SkillTimerCount == 19)    //Condicion de que si la variable es igual que el maximo de objetos dejamos de llamar al timer SkillsDynamicObjects para que deje de crear objetos. (TUVE QUE PONER EL NUMERO POR QUE SINO NO FUNCABA LA FUNCION CUANDO TENIA QUE ENTRAR EN EL IF)
    {
		SetTimerEx("ResultsSkillsGun", 2000, false, "i", playerid);//Luego de que llega al maximo de objetos llama a la función que muestra los resultados del "entrenamiento" luego de 4 segundos.
        KillTimer(TimerSkills[playerid]);
    }
    else
    {
        SkillTimerCount++;
    }
    return 1;
}

public SkillsDynamicObjectsLevelThree(playerid) {
	new randomPos = random(MAX_OBJECT_POS),
		randomPosMove1 = random(3),
		randomPosMove2 = random(5),
		randomPosMove3 = random(2);
		
    if (SkillTimerCount != 0)
        DestroyDynamicObject(skillobject[SkillObjCounter-1]); //Borra el objeto desp de los X segundos del timer (-1 por que cuando lo crea suma la variable del contador, por lo cual para borrar el creado hay que restarle 1)
	
    skillobject[SkillObjCounter] = CreateDynamicObject(1588,SKILL_OBJECT_POSLEVEL3[randomPos][0],SKILL_OBJECT_POSLEVEL3[randomPos][1],SKILL_OBJECT_POSLEVEL3[randomPos][2], 0.0, 0.0, 0);//Creacion de objeto dinamico, posiciones segun el SKILL_OBJECT_POSLEVEL3
    MoveDynamicObject(skillobject[SkillObjCounter], (SKILL_OBJECT_POSLEVEL3[randomPos][0])+randomPosMove1, (SKILL_OBJECT_POSLEVEL3[randomPos][1])-randomPosMove2, (SKILL_OBJECT_POSLEVEL3[randomPos][2])+randomPosMove3, 5.00);//Movimiento del objeto
    SkillObjCounter++;        //Suma del contador de objeto
    Streamer_Update(playerid); //Update de streamer por que sino cuando los objetos se creaban solo los veias si te movias ya que los objetos dinamicos se actualizan solo cuando te moves, por eso forzamos la actualizacion poniendo el Streamer_Update
	if(SkillGun[playerid] == 22)
	{
		if(ShootCount[playerid] >= 14)
		{
			SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
			GivePlayerGun(playerid, 22, 40);//Le volvemos a setear una 9mm con 40 balas cuando disparó 16 veces para evitar que no puedan hacer el entrenamiento perfecto por culpa de la animación de recarga de arma cuando llega a la ultima bala del cargador
			ShootCount[playerid] = 0;
		}
	}
	else if(SkillGun[playerid] == 24)
	{
		if(ShootCount[playerid] >= 7)
		{
			SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
			GivePlayerGun(playerid, 24, 15);////Le volvemos a setear una Deagle con 15 balas cuando disparó 6 por que por la velocidad del sistema pierden 1 objeto cuando hace la animación de recarga de arma, entonces lo evitamos.
			ShootCount[playerid] = 0;
		}
	}
    if(SkillTimerCount == 29)    //Condicion de que si la variable es igual que el maximo de objetos dejamos de llamar al timer SkillsDynamicObjects para que deje de crear objetos. (TUVE QUE PONER EL NUMERO POR QUE SINO NO FUNCABA LA FUNCION CUANDO TENIA QUE ENTRAR EN EL IF)
    {
		SetTimerEx("ResultsSkillsGun", 1300, false, "i", playerid);//Luego de que llega al maximo de objetos llama a la función que muestra los resultados del "entrenamiento" luego de 4 segundos.
        KillTimer(TimerSkills[playerid]);
    }
    else
    {
        SkillTimerCount++;
    }
    return 1;
}

public ResultsSkillsGun(playerid) {
	
	DestroyDynamicObject(skillobject[SkillObjCounter-1]);//Borramos el ultimo objeto creado por el sistema.
	if(SkillGun[playerid] == 22) //si esta haciendo el entrenamiento con una 9mm
	{
		Results9mm(playerid);
	}
	else if(SkillGun[playerid] == 24)//Si esta haciendo el entramiento con deagle
	{
		ResultsDeagle(playerid);
	}
	else if (SkillGun[playerid] == 25) // Si esta haciendo el entrenamiento con escopeta
	{
		ResultsShotgun(playerid);
	}
	return 1;
}

public Results9mm(playerid) {
	
	if(SkillsInfo[playerid][pSkillLevel9mm] < 40)
	{
		if(SkillCount[playerid] == 10)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 3;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] >=7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 2;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] < 7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevel9mm] >= 40)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que ya es momento ...");
			SendClientMessage(playerid, COLOR_WHITE, "de pasar al siguiente nivel y de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 40);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevel9mm] >= 40 && SkillsInfo[playerid][pSkillLevel9mm] < 900)
	{
		if(SkillCount[playerid] == 20)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 43;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 35;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] < 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevel9mm] >= 900)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que es momento...");
			SendClientMessage(playerid, COLOR_WHITE, "de pasar al siguiente nivel y de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 900);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevel9mm] >= 900)
	{
		if(SkillCount[playerid] == 30)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 8;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevel9mm] += 4;
			SkillsInfo[playerid][pSkillLevelTimer9mm] = 60 * 60;
		}
		else if (SkillCount[playerid] < 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevel9mm] >= 1000)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y puedo decir que eres ...");
			SendClientMessage(playerid, COLOR_WHITE, "de los mejores tiradores con 9mm creo que es innecesario que continuemos entrenando tu punteria con la 9mm...");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 999);
		}
	}
	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); //Borro el arma creada por el sistema.
	trainningshot[playerid] = 0; //Seteo la variable que me dice si esta haciendo el entrenamiento en 0
	SkillCount[playerid] = 0; //Seteo la variable de contador de objetos destruidos por playerid en 0
	skillvalue = 0; //Seteo la variable que verifica si alguien esta haciendo el entrenamiento(para que otro no pueda hacerlo a la vez) en 0
	SkillTimerCount = 0; //Seteo en 0 la variable  que cuenta los objetos para poder frenar el timer y terminar el sistema
	SkillGun[playerid] = 0;
	ShootCount[playerid] = 0;
	SkillObjCounter = 0;
	if(SkillsInfo[playerid][pFirstTraining] != 0) //Si ya realizo el entrenamiento por lo menos 1 vez entra en el if, sino se va al else
	{
		SkillsGuns(playerid,SKILLS_UPDATE);
	}
	else
	{
		SkillsInfo[playerid][pFirstTraining] = 1;
		SkillsGuns(playerid,SKILLS_START);
	}
	return 1;
}

public ResultsDeagle(playerid) {
	
	if(SkillsInfo[playerid][pSkillLevelDeagle] < 200)
	{
		if(SkillCount[playerid] == 10)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 13;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] >=7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 10;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] < 7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelDeagle] >= 200)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que es momento ...");
			SendClientMessage(playerid, COLOR_WHITE, "de pasar al siguiente nivel y de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 200);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevelDeagle] >= 200 && SkillsInfo[playerid][pSkillLevelDeagle] < 900)
	{
		if(SkillCount[playerid] == 20)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 30;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 24;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] < 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelDeagle] >= 900)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que ya momento...");
			SendClientMessage(playerid, COLOR_WHITE, "de pasar al siguiente nivel y de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 900);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevelDeagle] >= 900)
	{
		if(SkillCount[playerid] == 30)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 6;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelDeagle] += 3;
			SkillsInfo[playerid][pSkillLevelTimerDeagle] = 60 * 60;
		}
		else if (SkillCount[playerid] < 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelDeagle] >= 1000)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y puedo decir que eres de...");
			SendClientMessage(playerid, COLOR_WHITE, "los mejores tiradores con Deagle, creo que es innecesario que continuemos entrenando tu punteria con la Deagle...");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
		}
	}
	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); //Borro el arma creada por el sistema.
	trainningshot[playerid] = 0; //Seteo la variable que me dice si esta haciendo el entrenamiento en 0
	SkillCount[playerid] = 0; //Seteo la variable de contador de objetos destruidos por playerid en 0
	skillvalue = 0; //Seteo la variable que verifica si alguien esta haciendo el entrenamiento(para que otro no pueda hacerlo a la vez) en 0
	SkillTimerCount = 0; //Seteo en 0 la variable  que cuenta los objetos para poder frenar el timer y terminar el sistema
	SkillGun[playerid] = 0;
	ShootCount[playerid] = 0;
	SkillObjCounter = 0;
	if(SkillsInfo[playerid][pFirstTraining] != 0) //Si ya realizo el entrenamiento por lo menos 1 vez entra en el if, sino se va al else
		SkillsGuns(playerid,SKILLS_UPDATE);
	else
	{
		SkillsInfo[playerid][pFirstTraining] = 1;
		SkillsGuns(playerid,SKILLS_START);
	}
	return 1;
}

public ResultsShotgun(playerid) {
	
	if(SkillsInfo[playerid][pSkillLevelShotgun] < 200)
	{
		if(SkillCount[playerid] == 10)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 13;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] >=7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 10;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] < 7)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelShotgun] >= 200)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que ya es momento de...");
			SendClientMessage(playerid, COLOR_WHITE, "pasar al siguiente nivel y de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 200);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevelShotgun] >= 200 && SkillsInfo[playerid][pSkillLevelShotgun] < 900)
	{
		if(SkillCount[playerid] == 20)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 30;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 24;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] < 14)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelShotgun] >= 900)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y considero que ya es momento de...");
			SendClientMessage(playerid, COLOR_WHITE, "pasar al siguiente nively de aumentar la dificultad de ésto. Puedes volver en una hora para seguir entrenando.");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 900);
		}
	}
	else if(SkillsInfo[playerid][pSkillLevelShotgun] >= 900)
	{
		if(SkillCount[playerid] == 30)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¡Wow! Que punteria.. le haz dado a todos los blancos eso es un plus que voy a anotar en mi cuaderno...");
			SendClientMessage(playerid, COLOR_WHITE, "Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 4;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] >= 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Haz realizado el entrenamiento satisfactoriamente. Puedes volver en una hora para seguir entrenando.");
			SkillsInfo[playerid][pSkillLevelShotgun] += 3;
			SkillsInfo[playerid][pSkillLevelTimerShotgun] = 60 * 60;
		}
		else if (SkillCount[playerid] < 21)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: ¿Qué ha pasado tio, un mal día? no te preocupes, puedes volver a intentarlo pero debes...");
			SendClientMessage(playerid, COLOR_WHITE, "volver a pagarme que las balas no me salen gratis cabrón.");
		}
		if(SkillsInfo[playerid][pSkillLevelShotgun] >= 1000)
		{
			SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Felicidades, despues de largos entrenamientos haz mejorado tu puntería y puedo decir que eres de ...");
			SendClientMessage(playerid, COLOR_WHITE, "los mejores tiradores con Escopeta creo que es innecesario que continuemos entrenando tu punteria con la Escopeta...");
			SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
		}
	}
	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); //Borro el arma creada por el sistema.
	trainningshot[playerid] = 0; //Seteo la variable que me dice si esta haciendo el entrenamiento en 0
	SkillCount[playerid] = 0; //Seteo la variable de contador de objetos destruidos por playerid en 0
	skillvalue = 0; //Seteo la variable que verifica si alguien esta haciendo el entrenamiento(para que otro no pueda hacerlo a la vez) en 0
	SkillTimerCount = 0; //Seteo en 0 la variable  que cuenta los objetos para poder frenar el timer y terminar el sistema
	SkillGun[playerid] = 0;
	ShootCount[playerid] = 0;
	SkillObjCounter = 0;
	if(SkillsInfo[playerid][pFirstTraining] != 0) //Si ya realizo el entrenamiento por lo menos 1 vez entra en el if, sino se va al else
		SkillsGuns(playerid,SKILLS_UPDATE);
	else
	{
		SkillsInfo[playerid][pFirstTraining] = 1;
		SkillsGuns(playerid,SKILLS_START);
	}
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z){
	if (skillvalue == 1)
	{
		if(SkillGun[playerid] == weaponid) // Verifica que coincida el arma que eligio para hacer el sistema con el arma que está rompiendo los objetos
		{
			SkillCount[playerid] ++;
		}
	}
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ){
	if(skillvalue == 1)
	{
		if(trainningshot[playerid] == 1)
		{
			if(SkillGun[playerid] == weaponid)
			{
				ShootCount[playerid] += 1;
			}
		}
	}
}

stock updateSkillTimerCounters(playerid){
	if(SkillsInfo[playerid][pSkillLevelTimer9mm] > 0)
		SkillsInfo[playerid][pSkillLevelTimer9mm]--;
	
	if(SkillsInfo[playerid][pSkillLevelTimerDeagle] > 0)
		SkillsInfo[playerid][pSkillLevelTimerDeagle]--;
	
	if(SkillsInfo[playerid][pSkillLevelTimerShotgun] > 0)
		SkillsInfo[playerid][pSkillLevelTimerShotgun]--;
}

 stock isPlayerInTrainning(playerid){
	return trainningshot[playerid];
}
//==================================COMANDOS========================================
CMD:entrenamientodetiro(playerid, params[]){
	new selectid;

	if(sscanf(params, "d", selectid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /entrenamientodetiro [ID-Arma] (22.9mm 24.Deagle 25.Escopeta 33.Rifle)");
	if(GetPlayerCash(playerid) < 500)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "No tienes el dinero suficiente para realizar el entrenamiento ($500)");
	if(skillvalue == 1)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Alguien está realizando el entrenamiento, debes aguardar a que termine para poder realizarlo tu");
	if(selectid != 22 && selectid != 24 && selectid != 25)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, " Tienes que ingresar un id de arma válido (22 para la 9mm, 24 para la Deagle o 25 para la Escopeta");
	if(GetHandItem(playerid, HAND_RIGHT) != 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener la mano derecha libre.");

	if(PlayerInfo[playerid][pFaction] == FAC_PMA)
		SendClientMessage(playerid, COLOR_YELLOW2, "No puedes realizar el entrenamiento de tiro siendo policia, ya que tus entrenamientos los dicta el comisario");
	if(selectid == 22)//Si quiere realizar el de 9mm
	{
		if(SkillsInfo[playerid][pSkillLevelTimer9mm] != 0)
		{
			SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a realizar el entrenamiento con 9mm.", SkillsInfo[playerid][pSkillLevelTimer9mm] / 60);
			return 1;
		}
	}
	else if(selectid == 24)//Si quiere realizar el de Deagle
	{
		if(SkillsInfo[playerid][pSkillLevelTimerDeagle] != 0)
		{
			SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a realizar el entrenamiento con Deagle.", SkillsInfo[playerid][pSkillLevelTimerDeagle] / 60);
			return 1;
		}
	}
	else if(selectid == 25)//Si quiere realizar el de Escopeta
	{
		if(SkillsInfo[playerid][pSkillLevelTimerShotgun] != 0)
		{
			SendFMessage(playerid, COLOR_YELLOW2, "Debes esperar %d minutos antes de volver a realizar el entrenamiento con Escopeta.", SkillsInfo[playerid][pSkillLevelTimerShotgun] / 60);
			return 1;
		}
	}
	SkillGun[playerid] = selectid;
    GivePlayerGun(playerid, selectid, 35);
	GivePlayerCash(playerid, -500);
	if(SkillsInfo[playerid][pFirstTraining] == 0) //Si es la primera vez que realiza el entrenamiento.
	{
		SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Bienvenido, te explicaré como van a ser las etapas de entrenamiento mientras vengas a practicar tu puntería en éste local..");
		SendClientMessage(playerid, COLOR_WHITE, "cada vez que realices la prueba anotaré la cantidad de blancos que le haz dado, cuando considere que estás capacitado...");
		SendClientMessage(playerid, COLOR_WHITE, "para pasar al siguiente nivel aumentará la distancia y dificultad. No mucho mas, preparate que en menos de 15 segundos...");
		SendClientMessage(playerid, COLOR_WHITE, "comenzaran a aparecer los blancos, procura dispararles a todos.. Buena suerte.");
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "Profesor de tiro: Excelente, aquí tienes tu arma con las balas cargadas. Preparate cerca del poligono de tiro...");
		SendClientMessage(playerid, COLOR_WHITE, "dentro de 15 segundos comenzaran a aparecer los objetos moviendose por todos lados, procura dispararles a todos.. Buena suerte.");
	}
	SetTimerEx("TimeForTrainning", 15000, false, "i", playerid);
	return 1;
}

	
	
	
	
