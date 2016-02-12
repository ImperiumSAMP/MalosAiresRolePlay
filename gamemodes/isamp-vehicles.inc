#if defined _isamp_vehicles_included
	#endinput
#endif
#define _isamp_vehicles_included

/**
* Isamp Vehicles functions and defines
**/

//Defines
#define MAX_VEH                 1001
#define MAX_RENTCAR             30

//====[TIPOS DE VEHICULOS]======================================================
#define	VEH_NONE				0	// Ninguno, no spawnea.
#define	VEH_STATIC				1	// Estaticos, como los CREATED pero se estacionan y no desaparecen. Para diversos usos.
#define	VEH_OWNED				2	// Personal.
#define	VEH_FACTION				3	// Facción.
#define	VEH_SCHOOL				4	// Escuela de manejo.
#define	VEH_CREATED				5	// Creado por un administrador, desaparece a los 15 minutos.
#define	VEH_JOB					6	// Empleo.
#define	VEH_RENT                7

#define VTYPE_CAR 				1
#define VTYPE_HEAVY 			2
#define VTYPE_MONSTER 			3
#define VTYPE_BIKE				4
#define VTYPE_QUAD 				5
#define VTYPE_BMX 				6
#define VTYPE_HELI 				7
#define VTYPE_PLANE 			8
#define VTYPE_SEA 				9
#define VTYPE_TRAILER 			10
#define VTYPE_TRAIN 			11
#define VTYPE_BOAT 				VTYPE_SEA
#define VTYPE_BICYCLE 			VTYPE_BMX

#define PRICE_GPS   			100
#define PRICE_VEHICLE_PAINTJOB  10000
#define PRICE_VEHICLE_MODS      2000

//CHOICES
// Selecciones.
#define CHOICE_NONE     		0
#define CHOICE_CARSELL          1


//Enums
enum Cars {
	VehSQLID,
	VehModel,
	Float:VehPosX,
	Float:VehPosY,
	Float:VehPosZ,
	Float:VehAngle,
	VehColor1,
	VehColor2,
	VehPaintjob,
	VehFaction,
	VehJob,
	VehType,
	VehOwnerSQLID,
	VehFuel,
	VehEngine,
	VehLights,
	VehAlarm,
	VehLocked,
	VehBonnet,
	VehBoot,
	VehObjective,
 	Float:VehHP,
 	VehPlate[32],
 	VehDamage1,
 	VehDamage2,
 	VehDamage3,
 	VehDamage4,
	VehOwnerName[MAX_PLAYER_NAME],
	VehCompSlot[14],
	VehMarijuana,
	VehLSD,
	VehEcstasy,
	VehCocaine,
	VehRadio,
	VehGNC,
	VehGNCTank,

	VehContainerSQLID,
	VehContainerID
	
};
new VehicleInfo[MAX_VEH][Cars];

enum RCars {
	rVehicleID,
	rRented,
	rTime,
	rOwnerSQLID,
};

new RentCarInfo[MAX_RENTCAR][RCars];

new paintjobPreviewTimer[MAX_PLAYERS];

//Forwards
forward IsAPlane(vehicleid);
forward IsAHelicopter(vehicleid);
forward IsVehicleOccupied(vehicleid);
forward IsABike(vehicleid);
forward FindGps(playerid);

//Timers
forward respawnVeh(vehicleid);

stock getVehicleSqlId(vehicleid){
	return VehicleInfo[vehicleid][VehSQLID];
}

//================================CONSTANTES====================================

#define MAX_TRUNK_SLOTS         10
#define SLOT_TYPE_TRUNK         2

//============================VARIABLES INTERNAS================================

new TrunkInfo[MAX_VEH][MAX_TRUNK_SLOTS][SlotInfo];

//============================TRUNK FUNCTIONS===================================

forward GetTrunkItem(trunkid, trunkslot); // Devuelve el nro de item del slot indicado del maletero del vehiculo. En caso de error retorna -1.
forward GetTrunkParam(trunkid, trunkslot); // Devuelve el parametro "cantidad" del slot indicado del maletero del vehiculo. En caso de error retorna -1.
forward SetTrunkItemAndParam(trunkid, trunkslot, itemid, param); // Setea item y cantidad en el slot indicado. Guardado instantaneo en la DB.
forward ResetTrunk(trunkid); // Borra todo slot del maletero del vehiculo y lo resetea a cero.
forward SearchTrunkForItem(trunkid, itemid); // Busca un item pasado por parametro dentro de un maletero. Si existe, devuelve el slot en el que está, sino retorna -1.
forward SearchTrunkFreeSlot(trunkid); // Busca por el primer slot vacio en el maletero y devuelve su posicion. De no haber espacio retorna -1.
forward PrintTrunkForPlayer(trunkid, targetid); // Imprime el maletero del vehiculo al jugador indicado.

//==================================TIMER=======================================
forward ChangeTire(playerid, vehicleid);

public ChangeTire(playerid, vehicleid)
{
	new panels, doors, lights;
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 0);
 	TogglePlayerControllable(playerid, true);
	return 1;
}

//==================VEHICLE TRUNK FUNCTIONS IMPLEMENTATION======================

stock GetTrunkItem(trunkid, trunkslot)
{
	if(trunkslot >= 0 && trunkslot < MAX_TRUNK_SLOTS)
		return TrunkInfo[trunkid][trunkslot][Item];
	else
		return -1;
}

stock GetTrunkParam(trunkid, trunkslot)
{
	if(trunkslot >= 0 && trunkslot < MAX_TRUNK_SLOTS)
		return TrunkInfo[trunkid][trunkslot][Amount];
	else
		return-1;
}

stock SetTrunkItemAndParam(trunkid, trunkslot, itemid, param)
{
	if(trunkslot >= 0 && trunkslot < MAX_TRUNK_SLOTS)
	{
	    if(GetTrunkItem(trunkid, trunkslot) > 0) // Si quiere sobreescribir el slot teniendo algo dentro
	    {
			TrunkInfo[trunkid][trunkslot][Item] = 0;
			TrunkInfo[trunkid][trunkslot][Amount] = 0;
			SaveSlotInfo(SLOT_TYPE_TRUNK, trunkid, trunkslot); // Borramos el anterior
		}
		if(itemid != 0)
		{
			TrunkInfo[trunkid][trunkslot][Item] = itemid;
			TrunkInfo[trunkid][trunkslot][Amount] = param;
			SaveSlotInfo(SLOT_TYPE_TRUNK, trunkid, trunkslot);
		}
	}
	return 1;
}

stock ResetTrunk(trunkid)
{
	for(new i = 0; i < MAX_TRUNK_SLOTS; i++)
	{
		if(TrunkInfo[trunkid][i][Item] > 0)
		{
			TrunkInfo[trunkid][i][Amount] = 0;
			TrunkInfo[trunkid][i][Item] = 0;
		    SaveSlotInfo(SLOT_TYPE_TRUNK, trunkid, i);
		}
	}
	return 1;
}

stock SearchTrunkForItem(trunkid, itemid)
{
	for(new i = 0; i < MAX_TRUNK_SLOTS; i++)
	{
		if(TrunkInfo[trunkid][i][Item] == itemid)
		    return i;
	}
	return -1;
}

stock SearchTrunkFreeSlot(trunkid)
{
	new trunkslots = GetVehicleMaxTrunkSlots(trunkid);
	
	for(new i = 0; i < trunkslots; i++)
	{
		if(TrunkInfo[trunkid][i][Item] == 0)
		    return i;
	}
	return -1;
}

stock PrintTrunkForPlayer(trunkid, targetid)
{
	new itemid, trunkslots = GetVehicleMaxTrunkSlots(trunkid);

 	SendClientMessage(targetid, COLOR_WHITE, "=======================[Maletero]======================");
	for(new i = 0; i < trunkslots; i++)
	{
		itemid = GetTrunkItem(trunkid, i);
	    if(itemid > 0)
			SendFMessage(targetid, COLOR_WHITE, " - %d- Item: %s - %s: %d", i, GetItemName(itemid), GetItemParamName(itemid), GetTrunkParam(trunkid, i));
	    else
	        SendFMessage(targetid, COLOR_WHITE, " - %d- Vacío", i);
	}
	return 1;
}

//==========================VEHICLE MISC FUNCTIONS==============================

enum CarModelInfo {
	mName[32],
	mType,
	mPrice,
 	mTrunkSlots,
 	mTrunkSpace
};

static const CarModels[][CarModelInfo] = {

/*400*/	{"Landstalker", VTYPE_CAR, 70000, 4, 200},
/*401*/	{"Bravura", VTYPE_CAR, 31000, 2, 100},
/*402*/	{"Buffalo", VTYPE_CAR, 500000, 2, 100},
/*403*/	{"Linerunner", VTYPE_CAR, 455800, 4, 200},
/*404*/	{"Perenniel", VTYPE_CAR, 28900, 4, 200},
/*405*/	{"Sentinel", VTYPE_CAR, 68300, 4, 200},
/*406*/	{"Dumper", VTYPE_MONSTER, 853700, 0, 0},
/*407*/	{"Firetruck", VTYPE_HEAVY, 311800, 0, 0},
/*408*/	{"Trashmaster", VTYPE_HEAVY, 280000, 0, 0},
/*409*/	{"Stretch", VTYPE_CAR, 550000, 4, 200},
/*410*/	{"Manana", VTYPE_CAR, 26300, 2, 100},
/*411*/	{"Infernus", VTYPE_CAR, 990500, 2, 100},
/*412*/	{"Voodoo", VTYPE_CAR, 69100, 4, 200},
/*413*/	{"Pony", VTYPE_CAR, 105100, 6, 300},
/*414*/	{"Mule", VTYPE_HEAVY, 98200, 8, 400},
/*415*/	{"Cheetah", VTYPE_CAR, 750400, 2, 100},
/*416*/	{"Ambulance", VTYPE_CAR, 550100, 4, 200},
/*417*/	{"Leviathan", VTYPE_HELI, 910000, 6, 300},
/*418*/	{"Moonbeam", VTYPE_CAR, 80400, 4, 200},
/*419*/	{"Esperanto", VTYPE_CAR, 58000, 2, 100},
/*420*/	{"Taxi", VTYPE_CAR, 86000, 4, 200},
/*421*/	{"Washington", VTYPE_CAR, 75100, 4, 200},
/*422*/	{"Bobcat", VTYPE_CAR, 35800, 6, 300},
/*423*/	{"Mr Whoopee", VTYPE_CAR, 98800, 0, 0},
/*424*/	{"BF Injection", VTYPE_CAR, 65100, 0, 0},
/*425*/	{"Hunter", VTYPE_HELI, 10000000, 0, 0},
/*426*/	{"Premier", VTYPE_CAR, 80500, 4, 200},
/*427*/	{"Enforcer", VTYPE_CAR, 400000, 8, 400},
/*428*/	{"Securicar", VTYPE_CAR, 400000, 8, 400},
/*429*/	{"Banshee", VTYPE_CAR, 595000, 2, 100},
/*430*/	{"Predator", VTYPE_SEA, 1000000, 2, 100},
/*431*/	{"Bus", VTYPE_CAR, 592000, 0, 0},
/*432*/	{"Rhino", VTYPE_HEAVY, 10000000, 0, 0},
/*433*/	{"Barracks", VTYPE_HEAVY, 400000, 8, 400},
/*434*/	{"Hotknife", VTYPE_CAR, 384000, 0, 0},
/*435*/	{"Article Trailer", VTYPE_TRAILER, 150000, 10, 500},
/*436*/	{"Previon", VTYPE_CAR, 39000, 2, 100},
/*437*/	{"Coach", VTYPE_HEAVY, 599000, 0, 0},
/*438*/	{"Cabbie", VTYPE_CAR, 79000, 4, 200},
/*439*/	{"Stallion", VTYPE_CAR, 65000, 2, 100},
/*440*/ {"Rumpo", VTYPE_CAR, 95000, 6, 300},
/*441*/	{"RC Bandit", VTYPE_CAR, 500000, 0, 0},
/*442*/	{"Romero", VTYPE_CAR, 105000, 4, 200},
/*443*/	{"Packer", VTYPE_HEAVY, 428000, 0, 0},
/*444*/	{"Monster", VTYPE_MONSTER, 675000, 0, 0},
/*445*/	{"Admiral", VTYPE_CAR, 61000, 4, 200},
/*446*/	{"Squallo", VTYPE_SEA, 425000, 2, 100},
/*447*/	{"Seasparrow", VTYPE_HELI, 2000000, 0, 0},
/*448*/	{"Pizzaboy", VTYPE_BIKE, 25000, 0, 0},
/*449*/	{"Tram", VTYPE_TRAIN, 500000, 0, 0},
/*450*/	{"Article Trailer 2", VTYPE_TRAILER, 150000, 10, 500},
/*451*/	{"Turismo", VTYPE_CAR, 1050000, 2, 100},
/*452*/	{"Speeder", VTYPE_SEA, 355000, 2, 100},
/*453*/	{"Reefer", VTYPE_SEA, 415000, 8, 400},
/*454*/	{"Tropic", VTYPE_SEA, 830000, 6, 300},
/*455*/	{"Flatbed", VTYPE_CAR, 180000, 8, 400},
/*456*/	{"Yankee", VTYPE_CAR, 155000, 8, 400},
/*457*/	{"Caddy", VTYPE_CAR, 85000, 0, 0},
/*458*/	{"Solair", VTYPE_CAR, 80000, 4, 200},
/*459*/	{"Berkley's RC Van", VTYPE_CAR, 90000, 6, 300},
/*460*/	{"Skimmer", VTYPE_PLANE, 405000, 0, 0},
/*461*/	{"PCJ-600", VTYPE_BIKE, 75000, 0, 0},
/*462*/	{"Faggio", VTYPE_BIKE, 9000, 0, 0},
/*463*/	{"Freeway", VTYPE_BIKE, 70000, 0, 0},
/*464*/	{"RC Baron", VTYPE_PLANE, 500000, 0, 0},
/*465*/	{"RC Raider", VTYPE_HELI, 500000, 0, 0},
/*466*/	{"Glendale", VTYPE_CAR, 45000, 4, 200},
/*467*/	{"Oceanic", VTYPE_CAR, 41000, 4, 200},
/*468*/	{"Sanchez", VTYPE_BIKE, 55000, 0, 0},
/*469*/	{"Sparrow", VTYPE_HELI, 415000, 0, 0},
/*470*/	{"Patriot", VTYPE_CAR, 315000, 4, 200},
/*471*/	{"Quad", VTYPE_QUAD, 30000, 0, 0},
/*472*/	{"Coastguard", VTYPE_SEA, 115000, 2, 100},
/*473*/	{"Dinghy", VTYPE_SEA, 55000, 0, 0},
/*474*/	{"Hermes", VTYPE_CAR, 61000, 2, 100},
/*475*/	{"Sabre", VTYPE_CAR, 90000, 2, 100},
/*476*/	{"Rustler", VTYPE_PLANE, 1500000, 0, 0},
/*477*/	{"ZR-350", VTYPE_CAR, 625000, 2, 100},
/*478*/	{"Walton", VTYPE_CAR, 25000, 4, 200},
/*479*/	{"Regina", VTYPE_CAR, 65000, 4, 200},
/*480*/	{"Comet", VTYPE_CAR, 400000, 2, 100},
/*481*/	{"BMX", VTYPE_BMX, 7000, 0, 0},
/*482*/	{"Burrito", VTYPE_CAR, 95000, 6, 300},
/*483*/	{"Camper", VTYPE_CAR, 50000, 4, 200},
/*484*/	{"Marquis", VTYPE_SEA, 485000, 4, 200},
/*485*/	{"Baggage", VTYPE_CAR, 40000, 0, 0},
/*486*/	{"Dozer", VTYPE_CAR, 500000, 0, 0},
/*487*/	{"Maverick", VTYPE_HELI, 1200000, 4, 200},
/*488*/	{"SAN News Maverick", VTYPE_HELI, 1200000, 2, 100},
/*489*/	{"Rancher", VTYPE_CAR, 105000, 4, 200},
/*490*/	{"FBI Rancher", VTYPE_CAR, 150000, 4, 200},
/*491*/	{"Virgo", VTYPE_CAR, 55000, 2, 100},
/*492*/	{"Greenwood", VTYPE_CAR, 60000, 4, 200},
/*493*/	{"Jetmax", VTYPE_SEA, 470000, 2, 100},
/*494*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0, 0},
/*495*/	{"Sandking", VTYPE_CAR, 1000000, 4, 200},
/*496*/	{"Blista Compact", VTYPE_CAR, 100500, 2, 100},
/*497*/	{"Police Maverick", VTYPE_HELI, 1500000, 4, 200},
/*498*/	{"Boxville", VTYPE_CAR, 80000, 8, 400},
/*499*/	{"Benson", VTYPE_CAR, 70000, 8, 400},
/*500*/	{"Mesa", VTYPE_CAR, 60000, 2, 100},
/*501*/	{"RC Goblin", VTYPE_HELI, 500000, 0, 0},
/*502*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0, 0},
/*503*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0, 0},
/*504*/	{"Bloodring Banger", VTYPE_CAR, 200000, 0, 0},
/*505*/	{"Rancher", VTYPE_CAR, 105000, 4, 200},
/*506*/	{"Super GT", VTYPE_CAR, 700000, 2, 100},
/*507*/	{"Elegant", VTYPE_CAR, 80000, 4, 200},
/*508*/	{"Journey", VTYPE_CAR, 180000, 6, 300},
/*509*/ {"Bike", VTYPE_BMX, 2500, 0, 0},
/*510*/	{"Mountain Bike", VTYPE_BMX, 10000, 0, 0},
/*511*/	{"Beagle", VTYPE_PLANE, 415000, 4, 200},
/*512*/	{"Cropduster", VTYPE_PLANE, 400000, 0, 0},
/*513*/	{"Stuntplane", VTYPE_PLANE, 420000, 0, 0},
/*514*/	{"Tanker", VTYPE_CAR, 440000, 4, 200},
/*515*/	{"Roadtrain", VTYPE_CAR, 485000, 4, 200},
/*516*/	{"Nebula", VTYPE_CAR, 47500, 4, 200},
/*517*/	{"Majestic", VTYPE_CAR, 60000, 2, 100},
/*518*/	{"Buccaneer", VTYPE_CAR, 45000, 2, 100},
/*519*/	{"Shamal", VTYPE_PLANE, 1500000, 6, 300},
/*520*/	{"Hydra", VTYPE_PLANE, 10000000, 0, 0},
/*521*/	{"FCR-900", VTYPE_BIKE, 110000, 0, 0},
/*522*/	{"NRG-500", VTYPE_BIKE, 775000, 0, 0},
/*523*/	{"HPV1000", VTYPE_BIKE, 100000, 0, 0},
/*524*/	{"Cement Truck", VTYPE_CAR, 285000, 0, 0},
/*525*/	{"Towtruck", VTYPE_HEAVY, 90000, 0, 0},
/*526*/	{"Fortune", VTYPE_CAR, 85000, 2, 100},
/*527*/	{"Cadrona", VTYPE_CAR, 41000, 2, 100},
/*528*/	{"FBI Truck", VTYPE_CAR, 250000, 2, 100},
/*529*/	{"Willard", VTYPE_CAR, 50000, 4, 200},
/*530*/	{"Forklift", VTYPE_CAR, 90000, 0, 0},
/*531*/	{"Tractor", VTYPE_HEAVY, 40000, 0, 0},
/*532*/	{"Combine Harvester", VTYPE_HEAVY, 600000, 0, 0},
/*533*/	{"Feltzer", VTYPE_CAR, 110000, 2, 100},
/*534*/	{"Remington", VTYPE_CAR, 86000, 4, 200},
/*535*/	{"Slamvan", VTYPE_CAR, 90000, 4, 200},
/*536*/	{"Blade", VTYPE_CAR, 95000, 2, 100},
/*537*/	{"Freight", VTYPE_TRAIN, 2000000, 0, 0},
/*538*/	{"Brownstreak", VTYPE_TRAIN, 2000000, 0, 0},
/*539*/	{"Vortex", VTYPE_SEA, 1550000, 0, 0},
/*540*/	{"Vincent", VTYPE_CAR, 60000, 4, 200},
/*541*/	{"Bullet", VTYPE_CAR, 850000, 2, 100},
/*542*/	{"Clover", VTYPE_CAR, 40000, 2, 100},
/*543*/	{"Sadler", VTYPE_CAR, 30000, 6, 300},
/*544*/	{"Firetruck LA", VTYPE_CAR, 400000, 0, 0},
/*545*/	{"Hustler", VTYPE_CAR, 325000, 2, 100},
/*546*/	{"Intruder", VTYPE_CAR, 65000, 4, 200},
/*547*/	{"Primo", VTYPE_CAR, 50000, 4, 200},
/*548*/	{"Cargobob", VTYPE_HELI, 1600000, 6, 300},
/*549*/	{"Tampa", VTYPE_CAR, 50000, 4, 200},
/*550*/	{"Sunrise", VTYPE_CAR, 85000, 4, 200},
/*551*/	{"Merit", VTYPE_CAR, 110000, 4, 200},
/*552*/	{"Utility Van", VTYPE_CAR, 230000, 4, 200},
/*553*/	{"Nevada", VTYPE_PLANE, 1250000, 6, 300},
/*554*/	{"Yosemite", VTYPE_CAR, 90000, 6, 300},
/*555*/	{"Windsor", VTYPE_CAR, 150000, 2, 100},
/*556*/	{"Monster A", VTYPE_MONSTER, 700000, 0, 0},
/*557*/	{"Monster B", VTYPE_MONSTER, 700000, 0, 0},
/*558*/	{"Uranus", VTYPE_CAR, 350000, 2, 100},
/*559*/	{"Jester", VTYPE_CAR, 500000, 2, 100},
/*560*/	{"Sultan", VTYPE_CAR, 575000, 4, 200},
/*561*/	{"Stratum", VTYPE_CAR, 200000, 4, 200},
/*562*/	{"Elegy", VTYPE_CAR, 495000, 2, 100},
/*563*/	{"Raindance", VTYPE_HELI, 1350000, 4, 200},
/*564*/	{"RC Tiger", VTYPE_CAR, 500000, 0, 0},
/*565*/	{"Flash", VTYPE_CAR, 375000, 2, 100},
/*566*/	{"Tahoma", VTYPE_CAR, 90000, 4, 200},
/*567*/	{"Savanna", VTYPE_CAR, 85000, 4, 200},
/*568*/	{"Bandito", VTYPE_CAR, 40000, 0, 0},
/*569*/	{"Freight Flat Trailer", VTYPE_TRAIN, 500000, 0, 0},
/*570*/	{"Streak Trailer", VTYPE_TRAIN, 1000000, 0, 0},
/*571*/	{"Kart", VTYPE_CAR, 25000, 0, 0},
/*572*/	{"Mower", VTYPE_CAR, 15000, 0, 0},
/*573*/	{"Dune", VTYPE_MONSTER, 1000000, 6, 300},
/*574*/	{"Sweeper", VTYPE_CAR, 50000, 0, 0},
/*575*/	{"Broadway", VTYPE_CAR, 85000, 2, 100},
/*576*/	{"Tornado", VTYPE_CAR, 68000, 2, 100},
/*577*/	{"AT400", VTYPE_PLANE, 3500000, 6, 300},
/*578*/	{"DFT-30", VTYPE_CAR, 190000, 2, 100},
/*579*/	{"Huntley", VTYPE_CAR, 250000, 4, 200},
/*580*/	{"Stafford", VTYPE_CAR, 95000, 4, 200},
/*581*/	{"BF-400", VTYPE_BIKE, 60000, 0, 0},
/*582*/	{"Newsvan", VTYPE_CAR, 125000, 4, 200},
/*583*/	{"Tug", VTYPE_CAR, 25000, 0, 0},
/*584*/	{"Petrol Trailer", VTYPE_TRAILER, 300000, 0, 0},
/*585*/	{"Emperor", VTYPE_CAR, 45000, 4, 200},
/*586*/	{"Wayfarer", VTYPE_BIKE, 50000, 0, 0},
/*587*/	{"Euros", VTYPE_CAR, 400000, 2, 100},
/*588*/	{"Hotdog", VTYPE_HEAVY, 90000, 0, 0},
/*589*/	{"Club", VTYPE_CAR, 150000, 2, 100},
/*590*/	{"Freight Box Trailer", VTYPE_TRAIN, 350000, 0, 0},
/*591*/	{"Article Trailer 3", VTYPE_TRAILER, 200000, 10, 500},
/*592*/	{"Andromada", VTYPE_PLANE, 3500000, 10, 500},
/*593*/	{"Dodo", VTYPE_PLANE, 525000, 2, 100},
/*594*/	{"RC Cam", VTYPE_CAR, 500000, 0, 0},
/*595*/	{"Launch", VTYPE_SEA, 725000, 2, 100},
/*596*/	{"Police Car (LSPD)", VTYPE_CAR, 100000, 4, 200},
/*597*/	{"Police Car (SFPD)", VTYPE_CAR, 100000, 4, 200},
/*598*/	{"Police Car (LVPD)", VTYPE_CAR, 100000, 4, 200},
/*599*/	{"Police Ranger", VTYPE_CAR, 135000, 4, 200},
/*600*/	{"Picador", VTYPE_CAR, 40000, 4, 200},
/*601*/	{"S.W.A.T.", VTYPE_CAR, 450000, 0, 0},
/*602*/	{"Alpha", VTYPE_CAR, 350000, 2, 100},
/*603*/	{"Phoenix", VTYPE_CAR, 500000, 2, 100},
/*604*/	{"Glendale Shit", VTYPE_CAR, 22000, 4, 200},
/*605*/	{"Sadler Shit", VTYPE_CAR, 19000, 4, 200},
/*606*/	{"Baggage Trailer A", VTYPE_TRAILER, 50000, 0, 0},
/*607*/	{"Baggage Trailer B", VTYPE_TRAILER, 50000, 0, 0},
/*608*/	{"Tug Stairs Trailer", VTYPE_TRAILER, 50000, 0, 0},
/*609*/	{"Boxville", VTYPE_CAR, 85000, 8, 400},
/*610*/	{"Farm Trailer", VTYPE_TRAILER, 75000, 0, 0},
/*611*/	{"Utility Trailer", VTYPE_TRAILER, 75000, 0, 0}

};

//==============================================================================

stock GetVehicleTrunkSpace(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return CarModels[modelid-400][mTrunkSpace];
}

stock GetVehicleModelTrunkSpace(modelid)
{
	if(modelid < 400 || modelid > 611)
		return 0;

	return CarModels[modelid-400][mTrunkSpace];
}

stock VehicleHasContainer(vehicleid)
{
	if(VehicleInfo[vehicleid][VehContainerSQLID] > 0 && VehicleInfo[vehicleid][VehContainerID] > 0)
	    return 1;
	return 0;
}

//==============================================================================

GetVehicleMaxTrunkSlots(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return CarModels[modelid-400][mTrunkSlots];
}

stock GetVehicleModelTrunkSlots(modelid)
{
	if(modelid < 400 || modelid > 611)
		return 0;

	return CarModels[modelid-400][mTrunkSlots];
}

//==============================================================================

GetVehicleName(vehicleid)
{
	new name[32] = "", modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return name;

	format(name, 32, "%s", CarModels[modelid-400][mName]);
	return name;
}

GetVehicleModelName(modelid)
{
	new name[32] = "";

	if(modelid < 400 || modelid > 611)
		return name;

	format(name, 32, "%s", CarModels[modelid-400][mName]);
	return name;
}

//==============================================================================

GetVehiclePrice(vehicleid, priceperc)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return (CarModels[modelid-400][mPrice] / 100 * priceperc);
}

GetVehicleModelPrice(modelid, priceperc)
{
	if(modelid < 400 || modelid > 611)
		return 0;

	return (CarModels[modelid-400][mPrice] / 100 * priceperc);
}

//==============================================================================

GetVehicleType(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return CarModels[modelid-400][mType];
}

//==============================================================================

VehTypeName(type)
{
    new name[32];
    
    switch(type)
	{
        case 0: format(name, 32, "ninguno");
		case 1: format(name, 32, "estático");
		case 2: format(name, 32, "personal");
		case 3: format(name, 32, "faccion");
		case 4: format(name, 32, "escuela");
		case 5: format(name, 32, "admin");
		case 6: format(name, 32, "empleo");
		case 7: format(name, 32, "renta");
		default: format(name, 32, "¡REPORTAR-BUG!");
    }
    return name;
}

stock getVehicleJob(vehid)
{
	return VehicleInfo[vehid][VehJob];
}

stock getVehicleType(vehid)
{
	return VehicleInfo[vehid][VehType];
}

stock getVehicleDescription(vehicleid)
{
	new vehdesc[64];
	format(vehdesc, 64, "%s de %s", GetVehicleName(vehicleid), VehicleInfo[vehicleid][VehOwnerName]);
	return vehdesc;
}

public respawnVeh(vehicleid)
{
	SetVehicleToRespawn(vehicleid);
	return 1;
}

stock Float:GetDistanceFromVehicle(playerid, vehicleid)
{
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return GetVehicleDistanceFromPoint(vehicleid, pos[0], pos[1], pos[2]);
}

//========================[VEHICLE GLOBAL VARIABLES]============================

new vlocked,
	LastVeh[MAX_PLAYERS],
	bool:OfferingVehicle[MAX_PLAYERS],
	VehicleOfferPrice[MAX_PLAYERS],
	VehicleOffer[MAX_PLAYERS],
	VehicleOfferID[MAX_PLAYERS],
	bool:startingEngine[MAX_PLAYERS];

//=============[VEHICLE DAO FUNCTIONS | DYNAMIC CAR SYSTEM]=====================

stock LoadVehicles()
{
	new query[128],
		vehicleID = 1;

	while(vehicleID < MAX_VEH)
	{
	    format(query, sizeof(query), "SELECT * FROM `vehicles` WHERE `VehSQLID` = %d LIMIT 1", vehicleID);
		mysql_function_query(dbHandle, query, true, "OnVehicleDataLoad", "i", vehicleID);
		vehicleID++;
	}
	return 1;
}

ResetVehicle(id)
{
    VehicleInfo[id][VehType]        = 0;
    VehicleInfo[id][VehModel] 		= 411;
    VehicleInfo[id][VehPosX] 		= 9999;
    VehicleInfo[id][VehPosY] 		= 9999;
    VehicleInfo[id][VehPosZ] 		= 9999;
    VehicleInfo[id][VehAngle] 		= 0;
    VehicleInfo[id][VehColor1]		= 0;
    VehicleInfo[id][VehColor2]		= 0;
    VehicleInfo[id][VehPaintjob]	= 3;
    VehicleInfo[id][VehFaction] 	= 0;
    VehicleInfo[id][VehJob]     	= 0;
    VehicleInfo[id][VehDamage1]		= 0;
    VehicleInfo[id][VehDamage2]		= 0;
    VehicleInfo[id][VehDamage3]		= 0;
    VehicleInfo[id][VehDamage4]		= 0;
    VehicleInfo[id][VehOwnerSQLID]	= 0;
    VehicleInfo[id][VehLocked]		= -1;
    VehicleInfo[id][VehEngine]		= -1;
    VehicleInfo[id][VehBonnet]		= -1;
    VehicleInfo[id][VehBoot]		= -1;
    VehicleInfo[id][VehLights]		= -1;
    VehicleInfo[id][VehFuel]		= 0;
    VehicleInfo[id][VehGNCTank]     = 0;
    VehicleInfo[id][VehGNC]         = 0;
    VehicleInfo[id][VehMarijuana]	= 0;
    VehicleInfo[id][VehLSD]			= 0;
    VehicleInfo[id][VehEcstasy]		= 0;
    VehicleInfo[id][VehCocaine]		= 0;
	VehicleInfo[id][VehHP]			= 100;
	VehicleInfo[id][VehPlate]		= "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	VehicleInfo[id][VehOwnerName]	= "XXXXXXXXXXXXXXXXXXXXXXX";
	for(new i = 0; i < 14; i++)
	{
        VehicleInfo[id][VehCompSlot][i] = 0;
	}
	
	if(VehicleHasContainer(id))
	{
	    Container_Empty(VehicleInfo[id][VehContainerID]);
        Container_SetTotalSpace(VehicleInfo[id][VehContainerID], GetVehicleModelTrunkSpace(VehicleInfo[id][VehModel]));
	}
 
	ResetTrunk(id);
	return 1;
}

SaveVehicle(id)
{
	if(dontsave)
		return 1;

    new query[1150];

    GetVehicleDamageStatus(id, VehicleInfo[id][VehDamage1], VehicleInfo[id][VehDamage2], VehicleInfo[id][VehDamage3], VehicleInfo[id][VehDamage4]);
	GetVehicleHealth(id, VehicleInfo[id][VehHP]);
    GetVehicleParamsEx(id, VehicleInfo[id][VehEngine], VehicleInfo[id][VehLights], VehicleInfo[id][VehAlarm], vlocked, VehicleInfo[id][VehBonnet], VehicleInfo[id][VehBoot], VehicleInfo[id][VehObjective]);
	// En caso de que el vehículo sea creado, se guarda como inexistente.
	if(VehicleInfo[id][VehType] == VEH_CREATED) {
        VehicleInfo[id][VehType] = VEH_NONE;
	}
	if(VehicleInfo[id][VehType] == VEH_NONE) {
		VehicleInfo[id][VehFaction] = 0;
 	}
 	VehicleInfo[id][VehEngine] = 0;

	format(query,sizeof(query),"UPDATE vehicles SET VehModel=%d,VehPosX=%f,VehPosY=%f,VehPosZ=%f,VehAngle=%f,VehColor1=%d,VehColor2=%d,VehPaintjob=%d,VehFaction=%d,VehJob=%d,VehDamage1=%d,VehDamage2=%d,VehDamage3=%d,VehDamage4=%d,VehType=%d,VehOwnerID=%d,VehLocked=%d,VehEngine=%d,VehBonnet=%d,VehBoot=%d,VehLights=%d,VehFuel=%d, VehGNC=%d, VehGNCTank=%d, VehHP=%f,VehPlate='%s',VehOwnerName='%s'",
		VehicleInfo[id][VehModel],
	    VehicleInfo[id][VehPosX],
	    VehicleInfo[id][VehPosY],
	    VehicleInfo[id][VehPosZ],
	    VehicleInfo[id][VehAngle],
	    VehicleInfo[id][VehColor1],
	    VehicleInfo[id][VehColor2],
	    VehicleInfo[id][VehPaintjob],
	    VehicleInfo[id][VehFaction],
	    VehicleInfo[id][VehJob],
	    VehicleInfo[id][VehDamage1],
	    VehicleInfo[id][VehDamage2],
	    VehicleInfo[id][VehDamage3],
	    VehicleInfo[id][VehDamage4],
	    VehicleInfo[id][VehType],
	    VehicleInfo[id][VehOwnerSQLID],
	    VehicleInfo[id][VehLocked],
	    VehicleInfo[id][VehEngine],
	    VehicleInfo[id][VehBonnet],
	    VehicleInfo[id][VehBoot],
	    VehicleInfo[id][VehLights],
	    VehicleInfo[id][VehFuel],
	    VehicleInfo[id][VehGNC],
	    VehicleInfo[id][VehGNCTank],
		VehicleInfo[id][VehHP],
		VehicleInfo[id][VehPlate],
		VehicleInfo[id][VehOwnerName]
	);
	
	format(query,sizeof(query),"%s,VehCompSlot0=%d,VehCompSlot1=%d,VehCompSlot2=%d,VehCompSlot3=%d,VehCompSlot4=%d,VehCompSlot5=%d,VehCompSlot6=%d,VehCompSlot7=%d,VehCompSlot8=%d,VehCompSlot9=%d,VehCompSlot10=%d,VehCompSlot11=%d,VehCompSlot12=%d,VehCompSlot13=%d,VehMarijuana=%d,VehLSD=%d,VehEcstasy=%d,VehCocaine=%d, VehContainerSQLID=%d WHERE `VehSQLID` = %d",
		query,
		VehicleInfo[id][VehCompSlot][0],
		VehicleInfo[id][VehCompSlot][1],
		VehicleInfo[id][VehCompSlot][2],
		VehicleInfo[id][VehCompSlot][3],
		VehicleInfo[id][VehCompSlot][4],
		VehicleInfo[id][VehCompSlot][5],
		VehicleInfo[id][VehCompSlot][6],
		VehicleInfo[id][VehCompSlot][7],
		VehicleInfo[id][VehCompSlot][8],
		VehicleInfo[id][VehCompSlot][9],
		VehicleInfo[id][VehCompSlot][10],
		VehicleInfo[id][VehCompSlot][11],
		VehicleInfo[id][VehCompSlot][12],
		VehicleInfo[id][VehCompSlot][13],
		VehicleInfo[id][VehMarijuana],
		VehicleInfo[id][VehLSD],
		VehicleInfo[id][VehEcstasy],
		VehicleInfo[id][VehCocaine],
		VehicleInfo[id][VehContainerSQLID],
		VehicleInfo[id][VehSQLID]
	);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

SaveVehicles() {
	new
		id = 1;
	while(id < MAX_VEH) {
        SaveVehicle(id);
        id++;
	}
	printf("[INFO] vehículos guardados.");
	return 1;
}

//==========================[VEHICLE CHECK FUNCTIONS]===========================

public IsVehicleOccupied(vehicleid)
{
	foreach(new i : Player)
	{
		if(IsPlayerInVehicle(i,vehicleid)) return 1;
	}
	return 0;
}

//==========================[VEHICLE BUSINESS LOGIC]============================

SetEngine(vehicleid, status)
{
    GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	switch(status)
	{
	    case 0: // Apagar.
	    {
         	if(VehicleInfo[vehicleid][VehEngine] == 1)
         	    VehicleInfo[vehicleid][VehEngine] = 0;
         	else
			 	return 0;
	    }
	    case 1: // Encender.
		{
		  	if(VehicleInfo[vehicleid][VehEngine] != 1)
			  VehicleInfo[vehicleid][VehEngine] = 1;
         	else
			 	return 0;
		}
	}
	SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], 0, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	return 1;
}

stock setVehicleRandomPlates() {
	new
		vid,
	    vehicleid,
		bool:alreadyExists = false;

    while(vehicleid < MAX_VEH) {
        format(VehicleInfo[vehicleid][VehPlate], 32, "%c%c%c-%d%d%d",65+random(26),65+random(26),65+random(26),random(10),random(10),random(10));
    	while(vid < vehicleid) {
			if(strcmp(VehicleInfo[vehicleid][VehPlate], VehicleInfo[vid][VehPlate], true, strlen(VehicleInfo[vid][VehPlate])) == 0) {
			    alreadyExists = true;
			    break;
			}
			vid++;
		}
		if(alreadyExists == true) {
		    alreadyExists = false;
		} else {
		    SaveVehicle(vehicleid);
		    vehicleid++;
		}
	}
	return 1;
}

//========================[VEHICLE EVENT HANDLERS]==============================

public OnVehicleStreamIn(vehicleid, forplayerid)
{
    return 1;
}

public OnVehicleSpawn(vehicleid)
{
	switch(VehicleInfo[vehicleid][VehType])
	{
	    case VEH_NONE:
		{
	    	SetVehiclePos(vehicleid, 9999.0, 9999.0, 0.0);
	    }
	    case VEH_CREATED:
		{
		    VehicleInfo[vehicleid][VehType] = VEH_NONE;
		    SetVehiclePos(vehicleid, 9999.0, 9999.0, 0.0);
		}
		case VEH_OWNED:
		{
		    UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][VehDamage1], VehicleInfo[vehicleid][VehDamage2], VehicleInfo[vehicleid][VehDamage3], VehicleInfo[vehicleid][VehDamage4]);
 			for(new i = 0; i < 14; i++)
	 		{
 			    if(VehicleInfo[vehicleid][VehCompSlot][i] != 0)
			 	{
 			    	AddVehicleComponent(vehicleid, VehicleInfo[vehicleid][VehCompSlot][i]);
				}
 			}
 			ChangeVehiclePaintjob(vehicleid, VehicleInfo[vehicleid][VehPaintjob]);
 			ChangeVehicleColor(vehicleid, VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2]);
		}
        case VEH_FACTION:
		{
		}
		default:
		{
		    //SetVehiclePos(vehicleid, VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ]);
		}
	}
	VehicleInfo[vehicleid][VehBonnet] = 0; // le cerramos el capot
	VehicleInfo[vehicleid][VehBoot] = 0; // Le cerramos el maletero
	VehicleInfo[vehicleid][VehRadio] = 0; // Le apagamos la radio
	return 1;
}

stock VehicleLog(vehicleid, playerid, targetid, command[], params[])
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

	format(query, sizeof(query), "INSERT INTO `log_vehicles` (VehID, pName, pID, tName, tID, Date, Command, Params) VALUES (%d, '%s', %d, '%s', %d, '%02d-%02d-%02d %02d:%02d:%02d', '%s', '%s')",
		vehicleid,
		playerName,
		PlayerInfo[playerid][pID],
		targetName,
		targetSQLID,
		year,
		month,
		day,
		hour,
		minute,
		second,
		command,
		params
	);
	mysql_function_query(dbHandle, query, false, "", "");
	return 1;
}

//=============================[VEHICLE COMMANDS]===============================

//============================[EXPERIMENTAL]====================================

CMD:mal(playerid, params[])
{
 	cmd_maletero(playerid, params);
	return 1;
}

CMD:maletero(playerid, params[])
{
	new vehicleid = GetClosestVehicle(playerid, 5.0),
		returnstr[32],
		returnid2,
		cmd[32];

    if(IsPlayerInAnyVehicle(playerid))
       	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes salir del vehículo primero!");
    if(vehicleid == INVALID_VEHICLE_ID)
       	return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún vehículo cerca tuyo.");
    if(GetVehicleTrunkSpace(vehicleid) == 0 || !VehicleHasContainer(vehicleid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene maletero!");
	if(VehicleInfo[vehicleid][VehBoot] != 1 && !AdminDuty[playerid])
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero está cerrado!");

    if(sscanf(params, "s[32]S(-1)[32]I(-1)", cmd, returnstr, returnid2))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero [comando]");
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} guardar - guardardroga [tipo] [cant] - tomardroga [tipo] [cant]");

		if(!Container_Show(vehicleid, CONTAINER_TYPE_TRUNK, VehicleInfo[vehicleid][VehContainerID], playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: Error al mostrar el contenedor del maletero. Reportar a un administador.");
			
	    SendClientMessage(playerid, COLOR_WHITE, "======================[MALETERO]=====================");
		if(VehicleInfo[vehicleid][VehMarijuana] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Marihuana: %d gramos.", VehicleInfo[vehicleid][VehMarijuana]);
		}
		if(VehicleInfo[vehicleid][VehLSD] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - LSD: %d dosis.", VehicleInfo[vehicleid][VehLSD]);
		}
		if(VehicleInfo[vehicleid][VehEcstasy] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Éxtasis: %d dosis.", VehicleInfo[vehicleid][VehEcstasy]);
		}
		if(VehicleInfo[vehicleid][VehCocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Cocaína: %d gramos.", VehicleInfo[vehicleid][VehCocaine]);
		}
       	SendClientMessage(playerid, COLOR_WHITE, "=====================================================");
       	return 1;
	}
	else if(strcmp(cmd, "guardardroga", true) == 0)
	{
        if(strcmp(returnstr, "marihuana", true) == 0)
		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
            if(PlayerInfo[playerid][pMarijuana] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pMarijuana] -= returnid2;
            VehicleInfo[vehicleid][VehMarijuana] += returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "lsd", true) == 0)
		{
			if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(PlayerInfo[playerid][pLSD] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pLSD] -= returnid2;
         	VehicleInfo[vehicleid][VehLSD] += returnid2;
         	SaveVehicle(vehicleid);
         	PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
         	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "extasis", true) == 0)
		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(PlayerInfo[playerid][pEcstasy] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pEcstasy] -= returnid2;
            VehicleInfo[vehicleid][VehEcstasy] += returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "cocaina", true) == 0)
		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(PlayerInfo[playerid][pCocaine] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pCocaine] -= returnid2;
            VehicleInfo[vehicleid][VehCocaine] += returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else
		{
            SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero guardardroga [tipo] [cantidad]");
       		SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
        }
    }
	else if(strcmp(cmd, "tomardroga", true) == 0)
	{
       	if(strcmp(returnstr, "marihuana", true) == 0)
 		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
            if(VehicleInfo[vehicleid][VehMarijuana] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pMarijuana] += returnid2;
            VehicleInfo[vehicleid][VehMarijuana] -= returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "lsd", true) == 0)
		{
			if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(VehicleInfo[vehicleid][VehLSD] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pLSD] += returnid2;
         	VehicleInfo[vehicleid][VehLSD] -= returnid2;
         	SaveVehicle(vehicleid);
         	PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
         	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "extasis", true) == 0)
		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(VehicleInfo[vehicleid][VehEcstasy] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pEcstasy] += returnid2;
            VehicleInfo[vehicleid][VehEcstasy] -= returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else if(strcmp(returnstr, "cocaina", true) == 0)
		{
            if(returnid2 <= 0 || returnid2 > 5000)
                return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
        	if(VehicleInfo[vehicleid][VehCocaine] < returnid2)
                return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

			PlayerInfo[playerid][pCocaine] += returnid2;
            VehicleInfo[vehicleid][VehCocaine] -= returnid2;
            SaveVehicle(vehicleid);
            PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
        }
		else
		{
            SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero tomardroga [tipo] [cantidad]");
       		SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
        }
	}
	else if(strcmp(cmd, "guardar", true) == 0)
	{

		if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
	    if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(GetHandItem(playerid, HAND_RIGHT) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
	   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
		if(GetPVarInt(playerid, "GrupoPaintball") != 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con un arma de Paintball");
		if(GetPVarInt(playerid, "cantSaveItems") == 1)
	 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
		if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_TELEFONO_CELULAR)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el teléfono.");

		new itemid = GetHandItem(playerid, HAND_RIGHT),
		    itemparam = GetHandParam(playerid, HAND_RIGHT),
			str[128];

		if(itemid == 0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");
		if(!Container_AddItemAndParam(VehicleInfo[vehicleid][VehContainerID], itemid, itemparam))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No hay suficiente espacio libre en el maletero / El ítem es demasiado chico para guardarse en un maletero.");

    	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0); // Borrado lógico y grafico.

		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
		
		format(str, sizeof(str), "guarda un/a %s en el maletero.", GetItemName(itemid));
		PlayerActionMessage(playerid, 15.0, str);
		
		format(str, sizeof(str), "guardar %d %s", itemparam, GetItemName(itemid));
		VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", str);
    }
	return 1;
}

Dialog:Dlg_Show_Trunk_Container(playerid, response, listitem, inputtext[])
{
	new vehicleid = Container_Selection[playerid][csOriginalId],
 		container_id = Container_Selection[playerid][csId];

	ResetContainerSelection(playerid);
	
	if(response)
	{
        new itemid,
            itemparam,
            str[128],
            free_hand = SearchFreeHand(playerid);

    	if(IsPlayerInAnyVehicle(playerid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "Debes salir del vehículo primero.");
	 	if(GetDistanceFromVehicle(playerid, vehicleid) > 5.0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo no está cerca tuyo.");
	    if(GetVehicleTrunkSpace(vehicleid) == 0 || !VehicleHasContainer(vehicleid))
			return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no tiene maletero.");
		if(VehicleInfo[vehicleid][VehBoot] != 1 && !AdminDuty[playerid])
		   	return SendClientMessage(playerid, COLOR_YELLOW2, "El maletero está cerrado.");
    	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		if(free_hand == -1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes agarrar el item ya que tienes ambas manos ocupadas.");

		if(Container_TakeItem(container_id, listitem, itemid, itemparam))
		{
			SetHandItemAndParam(playerid, free_hand, itemid, itemparam); // Creación lógica y grafica en la mano.

            SetPVarInt(playerid, "cantSaveItems", 1);
			SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
			
			format(str, sizeof(str), "toma un/a %s del maletero.", GetItemName(itemid));
			PlayerActionMessage(playerid, 15.0, str);

			format(str, sizeof(str), "tomar %d %s", itemparam, GetItemName(itemid));
			VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", str);
		}
		else
		{
	        SendClientMessage(playerid, COLOR_YELLOW2, "Maletero vacio o el slot es inválido.");
		}
	}
	return 1;
}

//===========================[FIN EXPERIMENTAL]=================================

CMD:usarbidon(playerid, params[])
{
	new gasAmount,
		refillAmount,
		vehicleid = GetClosestVehicle(playerid, 4.0),
		hand;

	if(IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar fuera del vehículo.");
	if(GetHandItem(playerid, HAND_RIGHT) == ITEM_ID_BIDON && GetHandParam(playerid, HAND_RIGHT) > 0)
	{
	    hand = HAND_RIGHT;
	    gasAmount = GetHandParam(playerid, HAND_RIGHT);
	}
	else if(GetHandItem(playerid, HAND_LEFT) == ITEM_ID_BIDON && GetHandParam(playerid, HAND_LEFT) > 0)
	{
	    hand = HAND_LEFT;
	    gasAmount = GetHandParam(playerid, HAND_LEFT);
	}
	else
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un bidón con algo de combustible en alguna de tus manos para utilizar este comando.");
	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún vehículo cerca tuyo.");
		
	TogglePlayerControllable(playerid, false);
    refillAmount = 100 - VehicleInfo[vehicleid][VehFuel];
    if(refillAmount >= gasAmount)
	{
        SetPVarInt(playerid, "fuelCarWithCan", SetTimerEx("fuelCarWithCan", 6000, false, "iii", playerid, vehicleid, VehicleInfo[vehicleid][VehFuel] + gasAmount));
        GameTextForPlayer(playerid, "~w~Llenando tanque", 6000, 4);
		SetHandItemAndParam(playerid, hand, ITEM_ID_BIDON, 0);
		PlayerActionMessage(playerid, 15.0, "abre la tapa del tanque y vacía todo el contenido del bidón dentro.");
  		SendFMessage(playerid, COLOR_WHITE, "Has vaciado el bidón. El tanque de tu vehículo ahora está lleno al (%d %%) con combustible.", VehicleInfo[vehicleid][VehFuel] + gasAmount);
	}
	else
	{
        SetPVarInt(playerid, "fuelCarWithCan", SetTimerEx("fuelCarWithCan", 6000, false, "iii", playerid, vehicleid, 100));
        GameTextForPlayer(playerid, "~w~Llenando tanque", 6000, 4);
        SetHandItemAndParam(playerid, hand, ITEM_ID_BIDON, gasAmount - refillAmount);
        PlayerActionMessage(playerid, 15.0, "abre la tapa del tanque y vacía parte del bidón dentro.");
        SendFMessage(playerid, COLOR_WHITE, "Has llenado el tanque de tu vehículo. Tu bidón ahora tiene (%d %%) de combustible.", GetHandParam(playerid, hand));
    }
	return 1;
}

CMD:lojack(playerid, params[])
{
	new
		vehicleid,
		Float: X,
		Float: Y,
		Float: Z;

	if(sscanf(params, "i", vehicleid))
		return SendClientMessage (playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /lojack [ID vehículo]");
    if(!playerOwnsCar(playerid, vehicleid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo no te pertenece.");
    if(PlayerInfo[playerid][pPhoneNumber] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Requieres de un telefono para utilizar el Lojack!");
	if(GetPlayerCash(playerid) < PRICE_GPS)
		return SendClientMessage (playerid, COLOR_YELLOW2, "No tienes dinero suficiente para rastrear el vehículo. ($100)");

	foreach(new i : Player)
	{
 		if(IsPlayerInVehicle(i, vehicleid))
   			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes localizar tu vehículo en este momento.");
	}

	GivePlayerCash(playerid, -PRICE_GPS);
	GetVehiclePos(vehicleid, X, Y, Z);
	SetPlayerCheckpoint (playerid, X, Y, Z, 3);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "¡Lograste rastrear el vehículo!");
	SetTimerEx("FindGps", 60 * 1000, false, "i", playerid);
	return 1;
}

public FindGps(playerid)
{
	DisablePlayerCheckpoint(playerid);
	return 1;
}

forward StartEngineTimer(playerid, vehicleid);
public StartEngineTimer(playerid, vehicleid)
{
    new vehid = GetPlayerVehicleID(playerid);
    if(vehid == vehicleid && VehicleInfo[vehicleid][VehEngine] != 1)
    {
	    SendClientMessage(playerid, COLOR_WHITE, "Has encendido el motor del vehículo.");
		SetEngine(vehicleid, 1);
	}
	startingEngine[playerid] = false;
}

CMD:motor(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un vehículo para utilizar este comando.");
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(startingEngine[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Te encuentras encendiendo el motor, espera...");
	if(VehicleInfo[vehicleid][VehType] == VEH_STATIC)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_OWNED && !playerHasCarKey(playerid, vehicleid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_FACTION && VehicleInfo[vehicleid][VehFaction] != PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_JOB)
	    return SendClientMessage(playerid, COLOR_WHITE, "Para encender este vehículo debes tener el empleo necesario y utilizar /trabajar.");
	if(VehicleInfo[vehicleid][VehHP] < 500)
 	{
	    PlayerActionMessage(playerid, 15.0, "intenta encender el motor del vehículo pero se encuentra dañado.");
	    SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo se encuentra averiado.");
	    return 1;
	}
	if(VehicleInfo[vehicleid][VehFuel] < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo no tiene combustible.");
	    
	if(VehicleInfo[vehicleid][VehEngine] != 1)
	{
		startingEngine[playerid] = true;
		SetTimerEx("StartEngineTimer", 2000, false, "ii", playerid, vehicleid);
		PlayerActionMessage(playerid, 15.0, "gira la llave y le da arranque al vehículo.");
		GameTextForPlayer(playerid, "~r~Encendiendo motor", 2000, 4);
	} else
	{
		PlayerActionMessage(playerid, 15.0, "apaga el motor del vehículo.");
		SetEngine(vehicleid, 0);
	}
	return 1;
}

CMD:ventanillas(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		vehSeat = GetPlayerVehicleSeat(playerid),
		winState[4];

	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en un vehículo para utilizar este comando.");
	if(GetVehicleType(vehicleid) != VTYPE_CAR)
	    return SendClientMessage(playerid, COLOR_YELLOW2,"Este vehículo no tiene ventanillas.");
	if(vehSeat < 0 || vehSeat > 3)
	    return SendClientMessage(playerid, COLOR_YELLOW2,"Tu lugar en el vehículo no tiene ventanilla.");
	    
	GetVehicleParamsCarWindows(vehicleid, winState[0], winState[1], winState[2], winState[3]);
    if(winState[vehSeat] == 0)
    {
        winState[vehSeat] = 1;
        PlayerActionMessage(playerid, 15.0, "cierra la ventanilla de su lado del vehículo.");
	}
	else
	{
	    winState[vehSeat] = 0;
		PlayerActionMessage(playerid, 15.0, "abre la ventanilla de su lado del vehículo.");
	}
	SetVehicleParamsCarWindows(vehicleid, winState[0], winState[1], winState[2], winState[3]);
	return 1;
}

//==========================COMANDOS DE VEHICULOS===============================

CMD:veh(playerid, params[])
{
	cmd_vehiculo(playerid, params);
	return 1;
}

CMD:vehiculo(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "===========================[COMANDOS DE VEHÍCULOS]===========================");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/vehvender - /vehvendera - /vehestacionar - /vehpuertas - /vehluces - /vehmal - /vehcapot");
	return 1;
}

CMD:vehvender(playerid, params[])
{
	new vehicleid, dealership = GetNearestDealership(playerid, 25.0);

	if(!IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en ningún vehículo!");
	vehicleid = GetPlayerVehicleID(playerid);
    if(!playerOwnsCar(playerid,vehicleid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No podés vender un vehículo que no te pertenece!");
    if(dealership == -1)
        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar cerca de una concesionaria para vender el vehículo.");
        
	Choice[playerid] = CHOICE_CARSELL;
	SendClientMessage(playerid, COLOR_FADE1, "Empleado: ¿estás seguro de que quieres vender tu vehículo?");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona 'Y' para aceptar o 'N' para cancelar.");
    return 1;
}

CMD:vehvendera(playerid, params[])
{
	new targetid, vehicleid, price;

	if(sscanf(params, "uii", targetid, vehicleid, price))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /vehvendera [ID/Jugador] [IDvehículo] [dinero]");
	if(OfferingVehicle[playerid])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Ya estás vendiendo un vehículo.");
	if(vehicleid <= 0 || vehicleid >= MAX_VEH)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "La ID del vehículo es inválida.");
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID || targetid == playerid)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "ID de jugador inválida.");
	if(price < 1 || price > 5000000)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $1 ni mayor a $5,000,000.");
	if(VehicleInfo[vehicleid][VehType] != VEH_OWNED)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no puede ser vendido.");
	if(!playerOwnsCar(playerid,vehicleid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no te pertenece.");
	if(GetDistanceBetweenPlayers(playerid, targetid) > 4.0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "La persona se encuentra demasiado lejos.");

	OfferingVehicle[playerid] = true;
 	VehicleOfferPrice[targetid] = price;
	VehicleOffer[targetid] = playerid;
	VehicleOfferID[targetid] = vehicleid;
	SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido las llaves de un %s a %s por $%d.", GetVehicleName(vehicleid), GetPlayerNameEx(targetid), price);
	SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te ha ofrecido un %s por $%d.", GetPlayerNameEx(playerid), GetVehicleName(vehicleid), price);
	SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/aceptar vehiculo' para aceptar la oferta o '/cancelar vehiculo' para cancelar.");
    SetPVarInt(targetid, "CancelVehicleTransfer", SetTimerEx("CancelVehicleTransfer", 30 * 1000, 0, "ii", targetid, 1));
	return 1;
}

CMD:vehestacionar(playerid, params[])
{
	new vehicleid, Float:vhealth, Float:x, Float:y, Float:z, Float:angle;

	if(!IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en ningún vehículo!");
	vehicleid = GetPlayerVehicleID(playerid);
	if( !playerHasCarKey(playerid, vehicleid) &&
		(PlayerInfo[playerid][pFaction] != VehicleInfo[vehicleid][VehFaction] || PlayerInfo[playerid][pRank] != 1) )
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no te pertenece!");
	GetVehicleHealth(vehicleid, vhealth);
	if(vhealth < 700.0)
	   	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡No puedes estacionar un vehículo en este estado! Debe estar en mejores condiciones.");

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, angle);
	VehicleInfo[vehicleid][VehPosX] = x;
	VehicleInfo[vehicleid][VehPosY] = y;
	VehicleInfo[vehicleid][VehPosZ] = z;
	VehicleInfo[vehicleid][VehAngle] = angle;
	SaveVehicle(vehicleid);
	DestroyVehicle(vehicleid);
    CreateVehicle(VehicleInfo[vehicleid][VehModel], VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], VehicleInfo[vehicleid][VehAngle], VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2], -1);
   	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][VehPlate]);
	SetVehicleToRespawn(vehicleid);
	UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][VehDamage1], VehicleInfo[vehicleid][VehDamage2], VehicleInfo[vehicleid][VehDamage3], VehicleInfo[vehicleid][VehDamage4]);
	SetVehicleHealth(vehicleid, VehicleInfo[vehicleid][VehHP]);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SendClientMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} vehículo estacionado correctamente.");
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/vehestacionar", params);
 	return 1;
}

CMD:vehpuertas(playerid, params[])
{
	new vehicleid, vehicleType;

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	    vehicleid = GetPlayerVehicleID(playerid);
	else
		vehicleid = GetClosestVehicle(playerid, 7.0);
	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo / Vehículo inválido!");
    GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(GetVehicleType(vehicleid) == VTYPE_BMX || GetVehicleType(vehicleid) == VTYPE_BIKE || GetVehicleType(vehicleid) == VTYPE_QUAD)
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no tiene puertas.");
	   	
	vehicleType = VehicleInfo[vehicleid][VehType];
	
	if(!AdminDuty[playerid])
	{
		if( (vehicleType != VEH_FACTION && vehicleType != VEH_RENT && vehicleType != VEH_OWNED && vehicleType != VEH_JOB) ||
		    (vehicleType == VEH_JOB && PlayerInfo[playerid][pJob] != VehicleInfo[vehicleid][VehJob]) ||
			(vehicleType == VEH_FACTION && PlayerInfo[playerid][pFaction] != VehicleInfo[vehicleid][VehFaction]) ||
			(vehicleType == VEH_OWNED && !playerHasCarKey(playerid,vehicleid)) ||
		 	(vehicleType == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
	}

	if(VehicleInfo[vehicleid][VehLocked] != 1)
	{
		PlayerActionMessage(playerid,15.0, "ha asegurado las puertas del vehículo.");
		VehicleInfo[vehicleid][VehLocked] = 1;
	}
	else
	{
		PlayerActionMessage(playerid,15.0, "ha destrabado las puertas del vehículo.");
		VehicleInfo[vehicleid][VehLocked] = 0;
	}
	return 1;
}

CMD:vehluces(playerid, params[])
{
	new vehicleid;

	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar adentro de un vehículo.");

	vehicleid = GetPlayerVehicleID(playerid);
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);

	if(VehicleInfo[vehicleid][VehLights] != 1)
	{
		VehicleInfo[vehicleid][VehLights] = 1;
		GameTextForPlayer(playerid, "~w~Luces encendidas", 1000, 1);
	}
	else
	{
	    VehicleInfo[vehicleid][VehLights] = 0;
	    GameTextForPlayer(playerid, "~w~Luces apagadas", 1000, 1);
	}
	SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	return 1;
}

CMD:vehmal(playerid, params[])
{
	new vehicleid, vehicleType;

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "Baja del vehículo, debes estar a pie.");
	vehicleid = GetClosestVehicle(playerid, 5.0);
	if(vehicleid == INVALID_VEHICLE_ID)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo!");
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(GetVehicleMaxTrunkSlots(vehicleid) == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene maletero!");
	vehicleType = VehicleInfo[vehicleid][VehType];
	if(!AdminDuty[playerid])
	{
		if( (vehicleType != VEH_FACTION && vehicleType != VEH_RENT && vehicleType != VEH_OWNED && vehicleType != VEH_JOB) ||
			(vehicleType == VEH_FACTION && PlayerInfo[playerid][pFaction] != VehicleInfo[vehicleid][VehFaction]) ||
			(vehicleType == VEH_OWNED && !playerHasCarKey(playerid,vehicleid)) ||
			(vehicleType == VEH_JOB && PlayerInfo[playerid][pJob] != VehicleInfo[vehicleid][VehJob]) ||
		 	(vehicleType == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
	}

	if(VehicleInfo[vehicleid][VehBoot] != 1)
    {
   		PlayerActionMessage(playerid, 15.0, "ha abierto el maletero del vehículo.");
		VehicleInfo[vehicleid][VehBoot] = 1;
		VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/vehmal", "abrir");
	} else
		{
			PlayerActionMessage(playerid, 15.0, "ha cerrado el maletero del vehículo.");
			VehicleInfo[vehicleid][VehBoot] = 0;
			VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/vehmal", "cerrar");
		}
	SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	return 1;
}

CMD:vehcapot(playerid, params[])
{
	new vehicleid, vehicleType;

 	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	 	return SendClientMessage(playerid, COLOR_YELLOW2, "Baja del vehículo, debes estar a pie.");
	vehicleid = GetClosestVehicle(playerid, 5.0);
	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo!");
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	if(GetVehicleType(vehicleid) != VTYPE_CAR)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene capot!");
	vehicleType = VehicleInfo[vehicleid][VehType];
 	if(!AdminDuty[playerid])
	{
		if( (vehicleType != VEH_FACTION && vehicleType != VEH_RENT && vehicleType != VEH_OWNED && vehicleType != VEH_JOB) ||
			(vehicleType == VEH_FACTION && PlayerInfo[playerid][pFaction] != VehicleInfo[vehicleid][VehFaction]) ||
			(vehicleType == VEH_OWNED && !playerHasCarKey(playerid,vehicleid)) ||
			(vehicleType == VEH_JOB && PlayerInfo[playerid][pJob] != VehicleInfo[vehicleid][VehJob]) ||
		 	(vehicleType == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid) )
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
	}

	if(VehicleInfo[vehicleid][VehBonnet] != 1)
    {
   		PlayerActionMessage(playerid,15.0,"ha abierto el capot del vehículo.");
		VehicleInfo[vehicleid][VehBonnet] = 1;
	}
	else
	{
		PlayerActionMessage(playerid,15.0,"ha cerrado el capot del vehículo.");
		VehicleInfo[vehicleid][VehBonnet] = 0;
	}
	SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	return 1;
}

	    
//=======================COMANDOS DE ADMIN PARA VEHICULOS=======================

CMD:av(playerid, params[])
{
	cmd_avehiculo(playerid, params);
	return 1;
}

CMD:avehiculo(playerid, params[])
{
  	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "==============================[COMANDOS DE ADMIN PARA VEHICULOS]==============================");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 2]{C8C8C8} /avmotor - /avinfo");
	if(PlayerInfo[playerid][pAdmin] >= 4) {
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 4]{C8C8C8} /avfix - /avfuel - /aventrar - /avtraer - /avrespawn - /avpatente - /avestacionar");
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 4]{C8C8C8} /avrespawnall - /avfuelcars - /avfixcars");
	}
	if(PlayerInfo[playerid][pAdmin] >= 20)
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 20]{C8C8C8} /avtipo - /avmodelo - /avcolor - /avfaccion - /avempleo - /avhp - /avnitro - /avcrear - /avcrearperma - /avowner");
	return 1;
}

CMD:avmotor(playerid, params[])
{
	new vehicleid;

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");

	vehicleid = GetPlayerVehicleID(playerid);
	GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
 	if(VehicleInfo[vehicleid][VehEngine] != 1)
		SetEngine(vehicleid, 1);
	else
		SetEngine(vehicleid, 0);
	return 1;
}

CMD:avinfo(playerid, params[])
{
	new Float:hp, id;

	if(sscanf(params, "d", id))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avinfo [idvehiculo]");
	if(id < 1 || id >= MAX_VEH)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Auto inexistente.");

  	GetVehicleHealth(id, hp);
  	SendFMessage(playerid, COLOR_WHITE, "=============== Auto %d [vid %d] ===============", id, VehicleInfo[id][VehSQLID]);
  	SendFMessage(playerid, COLOR_WHITE, "- Tipo: %d (%s)", VehicleInfo[id][VehType], VehTypeName(VehicleInfo[id][VehType]));
  	SendFMessage(playerid, COLOR_WHITE, "- Modelo: %d", VehicleInfo[id][VehModel]);
  	SendFMessage(playerid, COLOR_WHITE, "- Colores: %d-%d", VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2]);
 	SendFMessage(playerid, COLOR_WHITE, "- Faccion: %d", VehicleInfo[id][VehFaction]);
 	SendFMessage(playerid, COLOR_WHITE, "- Empleo: %d", VehicleInfo[id][VehJob]);
  	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s pid: %d", VehicleInfo[id][VehOwnerName], VehicleInfo[id][VehOwnerSQLID]);
  	SendFMessage(playerid, COLOR_WHITE, "- Patente: %s", VehicleInfo[id][VehPlate]);
	SendFMessage(playerid, COLOR_WHITE, "- HP: %f - HP2: %f", hp, VehicleInfo[id][VehHP]);
	SendFMessage(playerid, COLOR_WHITE, "- Gasolina: %d", VehicleInfo[id][VehFuel]);
	SendFMessage(playerid, COLOR_WHITE, "- Cerrado: %d", VehicleInfo[id][VehLocked]);
	return 1;
}

CMD:aventrar(playerid, params[])
{
	new vehicleid;

    if(sscanf(params, "i", vehicleid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aventrar [idvehiculo]");
	if(vehicleid == INVALID_VEHICLE_ID || vehicleid < 1 || vehicleid >= MAX_VEH || VehicleInfo[vehicleid][VehType] == VEH_NONE)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");

	PutPlayerInVehicle(playerid, vehicleid, 0);
	return 1;
}

CMD:avrespawn(playerid, params[])
{
	new vehicleid;

    if(sscanf(params, "i", vehicleid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avrespawn [idvehiculo]");
	if(vehicleid == INVALID_VEHICLE_ID || vehicleid < 1 || vehicleid >= MAX_VEH)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
    SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][VehPlate]);
	SetVehicleToRespawn(vehicleid);
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avrespawn", params);
	return 1;
}

CMD:avrespawnall(playerid, params[])
{

	for(new i = 1; i < MAX_VEH; i++)
	{
 		if(IsVehicleOccupied(i) == 0)
		{
		    SetVehicleNumberPlate(i, VehicleInfo[i][VehPlate]);
 			SetVehicleToRespawn(i);
		}
	}
	SendClientMessageToAll(COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} todos los vehículos desocupados han sido respawneados por un administrador.");
	return 1;
}

CMD:avtraer(playerid, params[])
{
	new Float:x, Float:y, Float:z, Float:angle, vehicleid;

	if(sscanf(params, "i", vehicleid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avtraer [idvehiculo]");
	if(vehicleid == INVALID_VEHICLE_ID || vehicleid < 1 || vehicleid >= MAX_VEH)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	SetVehiclePos(vehicleid, x, y + 3.5, z);
	SetVehicleZAngle(vehicleid, angle);
	return 1;
}

CMD:avfix(playerid, params[])
{
	new vehicleid;

	if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");

	vehicleid = GetPlayerVehicleID(playerid);
	RepairVehicle(vehicleid);
	VehicleInfo[vehicleid][VehHP] = 100;
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Vehículo reparado.");
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avfix", params);
	return 1;
}

CMD:avfuel(playerid, params[])
{
	new vehicleid;

	if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");

	vehicleid = GetPlayerVehicleID(playerid);
	VehicleInfo[vehicleid][VehFuel] = 100;
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Vehículo llenado con combustible.");
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avfuel", params);
	return 1;
}

CMD:avfuelcars(playerid, params[])
{

	for(new c = 0; c < MAX_VEH; c++)
	{
		VehicleInfo[c][VehFuel] = 100;
	}
	SendClientMessageToAll(COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} todos los vehículos han sido llenados con gasolina por un administrador.");
	return 1;
}

CMD:avfixcars(playerid, params[])
{
	for(new c = 0; c < MAX_VEH; c++)
	{
		RepairVehicle(c);
		VehicleInfo[c][VehHP] = 100;
	}
	SendClientMessageToAll(COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} todos los vehículos han sido reparados por un administrador.");
	return 1;
}

CMD:avnitro(playerid, params[])
{
	new vehicleid;

    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");

    vehicleid = GetPlayerVehicleID(playerid);
    AddVehicleComponent(vehicleid, 1010);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avnitro", params);
	return 1;
}

CMD:avempleo(playerid, params[])
{
	new vehicleid, jobid;

	if(sscanf(params, "i", jobid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avempleo [idempleo]");
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
    if(jobid < 0 || jobid > 8)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de empleo inválida.");

	vehicleid = GetPlayerVehicleID(playerid);
	VehicleInfo[vehicleid][VehJob] = jobid;
   	SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} el empleo del vehículo %d ha sido ajustado a %d.", vehicleid, jobid);
   	SaveVehicle(vehicleid);
   	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avempleo", params);
	return 1;
}

CMD:avfaccion(playerid, params[])
{
	new vehicleid, factionid;

	if(sscanf(params, "i", factionid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avfaccion [idfaccion]");
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
    if(factionid < 0 || factionid > 20)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de facción inválida.");

	vehicleid = GetPlayerVehicleID(playerid);
	VehicleInfo[vehicleid][VehFaction] = factionid;
   	SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} la facción del vehículo %d ha sido ajustada a %d.", vehicleid, factionid);
   	SaveVehicle(vehicleid);
   	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avfaccion", params);
	return 1;
}

CMD:avcolor(playerid, params[])
{
	new vehicleid, color1, color2, Float:cx, Float:cy, Float:cz, Float:angle;

	if(sscanf(params, "ii", color1, color2))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avcolor [color1] [color2]");
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
    if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} Ingresa colores válidos: 0-255.");

    vehicleid = GetPlayerVehicleID(playerid);
	VehicleInfo[vehicleid][VehColor1] = color1;
	VehicleInfo[vehicleid][VehColor2] = color2;
    SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} el color del vehículo %d ha sido ajustado a %d-%d.", vehicleid, color1, color2);
	GetVehiclePos(vehicleid, cx, cy, cz);
	GetVehicleZAngle(vehicleid, angle);
	DestroyVehicle(vehicleid);
	CreateVehicle(VehicleInfo[vehicleid][VehModel], VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], VehicleInfo[vehicleid][VehAngle], VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2], -1);
    SetVehicleToRespawn(vehicleid);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SetVehiclePos(vehicleid, cx, cy, cz);
	SetVehicleZAngle(vehicleid, angle);
    SaveVehicle(vehicleid);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avcolor", params);
	return 1;
}

CMD:avmodelo(playerid, params[])
{
	new vehicleid, modelid, Float:cx, Float:cy, Float:cz, Float:angle;

	if(sscanf(params, "i", modelid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avmodelo [idmodelo]");
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
    if(modelid < 400 || modelid > 611)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de modelo incorrecta, debe estar en el rango de 400-611.");

    vehicleid = GetPlayerVehicleID(playerid);
	VehicleInfo[vehicleid][VehModel] = modelid;
    SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} el modelo del vehículo %d ha sido cambiado a %d.", vehicleid, modelid);
	GetVehiclePos(vehicleid, cx, cy, cz);
	GetVehicleZAngle(vehicleid, angle);

	if(VehicleHasContainer(vehicleid))
	{
	    Container_Empty(VehicleInfo[vehicleid][VehContainerID]);
        Container_SetTotalSpace(VehicleInfo[vehicleid][VehContainerID], GetVehicleModelTrunkSpace(modelid));
	}
	else
	{
	    SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: El vehículo no tiene un contenedor asociado a su maletero. Reportar a un scripter.");
	}

	ResetTrunk(vehicleid);

	for(new i = 0; i < 14; i++)
	{
 	    VehicleInfo[vehicleid][VehCompSlot][i] = 0;
 	}
	VehicleInfo[vehicleid][VehPaintjob] = 3;
	DestroyVehicle(vehicleid);
	CreateVehicle(VehicleInfo[vehicleid][VehModel], VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], VehicleInfo[vehicleid][VehAngle], VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2], -1);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SetVehiclePos(vehicleid, cx, cy, cz);
	SetVehicleZAngle(vehicleid, angle);
    SaveVehicle(vehicleid);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avmodelo", params);
	return 1;
}

CMD:avtipo(playerid, params[])
{
	new vehicleid, type;

	if(sscanf(params, "i", type))
	{
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avtipo [ID tipo]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Tipos]:{C8C8C8} 0:Borrado - 1:Estático - 2:Personal - 3: Facción - 4:Licencia - 5:Creado - 6:Empleo - 7:Renta");
		return 1;
	}
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
	if(type < 0 || type > 10)
	    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de tipo incorrecta.");

	vehicleid = GetPlayerVehicleID(playerid);

	if(VehicleInfo[vehicleid][VehType] == VEH_RENT) // Si el auto a cambiar tipo tiene tipo renta, lo sacamos de la estructura que maneja los autos de renta
	{
		for(new i = 1; i < MAX_RENTCAR; i++)
		{
	    	if(RentCarInfo[i][rVehicleID] == vehicleid)
			{
               	RentCarInfo[i][rVehicleID] = 0;
               	RentCarInfo[i][rOwnerSQLID] = 0;
               	RentCarInfo[i][rTime] = 0;
               	RentCarInfo[i][rRented] = 0;
				break;
			}
		}
	}
	else if(VehicleInfo[vehicleid][VehType] == VEH_OWNED)
	{
		foreach(new i : Player)
		{
			if(playerHasCarKey(i,vehicleid)) 
				removeKeyFromPlayer(i,vehicleid);
		}
		deleteKeysForCar(vehicleid);
		VehicleInfo[vehicleid][VehOwnerSQLID] = 0;
        format(VehicleInfo[vehicleid][VehOwnerName], MAX_PLAYER_NAME, "%s", "XXXXXXXXX");
	}

	if(type == VEH_RENT)
	{
		new available = -1;
		for(new i = 1; i < MAX_RENTCAR; i++)
		{
		    if(RentCarInfo[i][rVehicleID] < 1)
			{
               	RentCarInfo[i][rVehicleID] = vehicleid;
               	RentCarInfo[i][rOwnerSQLID] = 0;
                RentCarInfo[i][rTime] = 0;
                RentCarInfo[i][rRented] = 0;
                available = i;
                break;
    		}
		}
		if(available == -1)
  			return SendClientMessage(playerid, COLOR_YELLOW2, "No se pueden poner más vehículos de renta.");
	}
	else if(type == VEH_NONE)
	{
		ResetVehicle(vehicleid);
	}

    VehicleInfo[vehicleid][VehType] = type;
    SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} el tipo del vehículo %d ha sido ajustado a %d.", vehicleid, type);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avtipo", params);
	if(type == VEH_STATIC)
	{
        cmd_avestacionar(playerid, "");
	}
	else
	{
		SaveVehicle(vehicleid);
		SetVehicleToRespawn(vehicleid);
		if(type != VEH_NONE && type != VEH_CREATED)
			PutPlayerInVehicle(playerid, vehicleid, 0);
	}
	return 1;
}

CMD:avestacionar(playerid, params[])
{
	new vehicleid, Float:cx, Float:cy, Float:cz, Float:angle;

    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");

    vehicleid = GetPlayerVehicleID(playerid);
	GetVehiclePos(vehicleid, cx, cy, cz);
	GetVehicleZAngle(vehicleid, angle);
	VehicleInfo[vehicleid][VehPosX] = cx;
	VehicleInfo[vehicleid][VehPosY] = cy;
	VehicleInfo[vehicleid][VehPosZ] = cz;
	VehicleInfo[vehicleid][VehAngle] = angle;
	SaveVehicle(vehicleid);

	DestroyVehicle(vehicleid);
 	CreateVehicle(VehicleInfo[vehicleid][VehModel], VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], VehicleInfo[vehicleid][VehAngle], VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2], -1);
	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][VehPlate]);
	SetVehicleToRespawn(vehicleid);
	UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][VehDamage1], VehicleInfo[vehicleid][VehDamage2], VehicleInfo[vehicleid][VehDamage3], VehicleInfo[vehicleid][VehDamage4]);
	SetVehicleHealth(vehicleid, VehicleInfo[vehicleid][VehHP]);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} vehículo %d estacionado correctamente.", vehicleid);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avestacionar", params);
	return 1;
}

CMD:avcrear(playerid, params[])
{
	new id = 1, Float:px, Float:py, Float:pz, Float:pa, modelid, color1, color2;

	if(sscanf(params, "iii", modelid, color1, color2))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avcrear [idmodelo] [color1] [color2]");
	if(modelid < 400 || modelid > 611)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de modelo incorrecta, debe estar en el rango de 400-611.");

	while(id < MAX_VEH)
	{
		if(VehicleInfo[id][VehType] == VEH_NONE)
		{
  			VehicleInfo[id][VehType] = VEH_CREATED;
			VehicleInfo[id][VehModel] = modelid;
			VehicleInfo[id][VehColor1] = color1;
			VehicleInfo[id][VehColor2] = color2;
			GetPlayerPos(playerid, px, py, pz);
			GetPlayerFacingAngle(playerid, pa);
			DestroyVehicle(id);
   			CreateVehicle(modelid, px, py, pz, pa, color1, color2, 300);
			PutPlayerInVehicle(playerid, id, 0);
			LastVeh[playerid] = id;
			SetEngine(id, 1);

			if(VehicleHasContainer(id))
			{
			    Container_Empty(VehicleInfo[id][VehContainerID]);
		        Container_SetTotalSpace(VehicleInfo[id][VehContainerID], GetVehicleModelTrunkSpace(modelid));
			}
			else
			{
			    SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: El vehículo no tiene un contenedor asociado a su maletero. Reportar a un scripter.");
			}
			
			SendClientMessage(playerid, COLOR_RED,"{878EE7}[INFO]:{C8C8C8} vehículo creado correctamente (desaparecerá luego de 5 minutos sin utilizar).");
            VehicleLog(id, playerid, INVALID_PLAYER_ID, "/avcrear", params);
			return 1;
		}
		id++;
	}
	return 1;
}

CMD:avcrearperma(playerid, params[])
{
	new id = 1, Float:px, Float:py, Float:pz, Float:pa, modelid, color1, color2;

	if(sscanf(params, "iii", modelid, color1, color2))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avcrearperma [idmodelo] [color1] [color2]");
	if(modelid < 400 || modelid > 611)
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de modelo incorrecta, debe estar en el rango de 400-611.");

	while(id < MAX_VEH)
	{
		if(VehicleInfo[id][VehType] == VEH_NONE)
		{
		  	VehicleInfo[id][VehType] = VEH_CREATED;
		  	VehicleInfo[id][VehModel] = modelid;
		  	VehicleInfo[id][VehColor1] = color1;
		  	VehicleInfo[id][VehColor2] = color2;
		  	GetPlayerPos(playerid, px, py, pz);
		  	GetPlayerFacingAngle(playerid, pa);
			DestroyVehicle(id);
  			CreateVehicle(modelid, px, py, pz, pa, color1, color2, 0);
			PutPlayerInVehicle(playerid, id, 0);
			LastVeh[playerid] = id;
			SetEngine(id, 1);
			
 			if(VehicleHasContainer(id))
			{
			    Container_Empty(VehicleInfo[id][VehContainerID]);
		        Container_SetTotalSpace(VehicleInfo[id][VehContainerID], GetVehicleModelTrunkSpace(modelid));
			}
			else
			{
			    SendClientMessage(playerid, COLOR_YELLOW2, "[SCRIPT ERROR]: El vehículo no tiene un contenedor asociado a su maletero. Reportar a un scripter.");
			}
			
			SendClientMessage(playerid,COLOR_RED,"{878EE7}[INFO]:{C8C8C8} vehículo creado correctamente (no desaparecerá hasta que sea eliminado o reinicie el servidor).");
            SendClientMessage(playerid,COLOR_RED,"{878EE7}[INFO]:{C8C8C8} Recuerda que siempre primero hay que setearle el tipo, y luego estacionarlo.");
			VehicleLog(id, playerid, INVALID_PLAYER_ID, "/avcrearperma", params);
			return 1;
		}
		id++;
	}
	return 1;
}

CMD:avhp(playerid, params[])
{
	new vehicleid, vhp;

    if(sscanf(params, "ii", vehicleid, vhp))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avhp [idvehiculo] [hp]");
	if(vehicleid < 1 || vehicleid >= MAX_VEH)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehiculo incorrecta.");
	if(vhp < 250 || vhp > 10000)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} Solo valores comprendidos en intervalo (250 - 10000).");

	SetVehicleHealth(vehicleid, float(vhp));
	// VehicleInfo[vehicleid][VehMaxHp] = float(vhp);
	SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} La vida del vehículo %d ha sido cambiada a %d.", vehicleid, vhp);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avhp", params);
	return 1;
}

CMD:avpatente(playerid, params[])
{
	new vehicleid, string[32];
	
    if(sscanf(params, "is[32]", vehicleid, string))
        return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avpatente [idvehiculo] [patente]");

	VehicleInfo[vehicleid][VehPlate] = string;
	SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} La patente del vehículo %d ha sido cambiada a %s.", vehicleid, string);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avpatente", params);
	return 1;
}

CMD:avowner(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
	    ownerid,
	    ownername[MAX_PLAYER_NAME];
	    
	if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
	
	if(getVehicleType(vehicleid) == VEH_OWNED)
	{
		if(sscanf(params, "u", ownerid))
        	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avowner [ID/Jugador]");
		if(!IsPlayerConnected(ownerid))
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Jugador no conectado.");
    	if(getPlayerFreeKeySlots(ownerid) < 1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "Error: el jugador no tiene más espacio en su llavero para otra llave.");

		// Borrado de llaves
		foreach(new i : Player)
		{
			if(playerHasCarKey(i, vehicleid))
				removeKeyFromPlayer(i, vehicleid);
		}
		deleteKeysForCar(vehicleid);
		
		// Nuevo dueño
		GetPlayerName(ownerid, VehicleInfo[vehicleid][VehOwnerName], MAX_PLAYER_NAME);
		VehicleInfo[vehicleid][VehOwnerSQLID] = PlayerInfo[ownerid][pID];
		addKeyToPlayer(ownerid, vehicleid, ownerid);
		SaveVehicle(vehicleid);
		SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} has borrado toda llave existente del vehículo y has hecho a %s dueño del %s (ID %d).", GetPlayerNameEx(ownerid), GetVehicleName(vehicleid), vehicleid);
		SendFMessage(ownerid, COLOR_WHITE, "[INFO]: El administrador %s te ha hecho dueño del vehículo %d (%s).", GetPlayerNameEx(playerid), vehicleid, GetVehicleName(vehicleid));
        VehicleLog(vehicleid, playerid, ownerid, "/avowner", "");
	}
	else
	{
    	if(sscanf(params, "s[24]", ownername))
        	return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avowner [Nombre] (máx 24 caracteres)");

		VehicleInfo[vehicleid][VehOwnerSQLID] = 0;
        format(VehicleInfo[vehicleid][VehOwnerName], MAX_PLAYER_NAME, "%s", ownername);
        SaveVehicle(vehicleid);
		SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} has puesto al vehículo %d (%s) a nombre de %s.", vehicleid, GetVehicleName(vehicleid), ownername);
        VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avowner", ownername);
	}
	return 1;
}
