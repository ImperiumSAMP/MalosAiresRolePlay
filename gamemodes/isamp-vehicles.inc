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
#define	VEH_DEALERSHIP 			1	// De venta.
#define	VEH_OWNED				2	// Personal.
#define	VEH_FACTION				3	// Facción.
#define	VEH_SCHOOL				4	// Escuela de manejo.
#define	VEH_CREATED				5	// Creado por un administrador, desaparece a los 15 minutos.
#define	VEH_JOB					6	// Empleo.
#define	VEH_RENT                7
#define	VEH_DEALERSHIP2 		8	// De venta, GROTTI.
#define	VEH_SHIPYARD     		10  // Astilleros

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
	VehRadio
};
new VehicleInfo[MAX_VEH][Cars];

enum RCars {
	rVehicleID,
	rRented,
	rTime,
	rOwnerSQLID,
};
new RentCarInfo[MAX_RENTCAR][RCars];

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
 	mTrunkSlots
};

static const CarModels[][CarModelInfo] = {

/*400*/	{"Landstalker", VTYPE_CAR, 70000, 4},
/*401*/	{"Bravura", VTYPE_CAR, 31000, 2},
/*402*/	{"Buffalo", VTYPE_CAR, 500000, 2},
/*403*/	{"Linerunner", VTYPE_CAR, 455800, 4},
/*404*/	{"Perenniel", VTYPE_CAR, 28900, 4},
/*405*/	{"Sentinel", VTYPE_CAR, 68300, 4},
/*406*/	{"Dumper", VTYPE_MONSTER, 853700, 0},
/*407*/	{"Firetruck", VTYPE_HEAVY, 311800, 0},
/*408*/	{"Trashmaster", VTYPE_HEAVY, 280000, 0},
/*409*/	{"Stretch", VTYPE_CAR, 550000, 4},
/*410*/	{"Manana", VTYPE_CAR, 26300, 2},
/*411*/	{"Infernus", VTYPE_CAR, 990500, 2},
/*412*/	{"Voodoo", VTYPE_CAR, 69100, 4},
/*413*/	{"Pony", VTYPE_CAR, 105100, 6},
/*414*/	{"Mule", VTYPE_HEAVY, 98200, 8},
/*415*/	{"Cheetah", VTYPE_CAR, 750400, 2},
/*416*/	{"Ambulance", VTYPE_CAR, 550100, 4},
/*417*/	{"Leviathan", VTYPE_HELI, 910000, 6},
/*418*/	{"Moonbeam", VTYPE_CAR, 80400, 4},
/*419*/	{"Esperanto", VTYPE_CAR, 58000, 2},
/*420*/	{"Taxi", VTYPE_CAR, 86000, 4},
/*421*/	{"Washington", VTYPE_CAR, 75100, 4},
/*422*/	{"Bobcat", VTYPE_CAR, 35800, 6},
/*423*/	{"Mr Whoopee", VTYPE_CAR, 98800, 0},
/*424*/	{"BF Injection", VTYPE_CAR, 65100, 0},
/*425*/	{"Hunter", VTYPE_HELI, 10000000, 0},
/*426*/	{"Premier", VTYPE_CAR, 80500, 4},
/*427*/	{"Enforcer", VTYPE_CAR, 400000, 8},
/*428*/	{"Securicar", VTYPE_CAR, 400000, 8},
/*429*/	{"Banshee", VTYPE_CAR, 595000, 2},
/*430*/	{"Predator", VTYPE_SEA, 1000000, 2},
/*431*/	{"Bus", VTYPE_CAR, 592000, 0},
/*432*/	{"Rhino", VTYPE_HEAVY, 10000000, 0},
/*433*/	{"Barracks", VTYPE_HEAVY, 400000, 8},
/*434*/	{"Hotknife", VTYPE_CAR, 384000, 0},
/*435*/	{"Article Trailer", VTYPE_TRAILER, 150000, 10},
/*436*/	{"Previon", VTYPE_CAR, 39000, 2},
/*437*/	{"Coach", VTYPE_HEAVY, 599000, 0},
/*438*/	{"Cabbie", VTYPE_CAR, 79000, 4},
/*439*/	{"Stallion", VTYPE_CAR, 65000, 2},
/*440*/ {"Rumpo", VTYPE_CAR, 95000, 6},
/*441*/	{"RC Bandit", VTYPE_CAR, 500000, 0},
/*442*/	{"Romero", VTYPE_CAR, 105000, 4},
/*443*/	{"Packer", VTYPE_HEAVY, 428000, 0},
/*444*/	{"Monster", VTYPE_MONSTER, 675000, 0},
/*445*/	{"Admiral", VTYPE_CAR, 61000, 4},
/*446*/	{"Squallo", VTYPE_SEA, 775000, 2},
/*447*/	{"Seasparrow", VTYPE_HELI, 2000000, 0},
/*448*/	{"Pizzaboy", VTYPE_BIKE, 25000, 0},
/*449*/	{"Tram", VTYPE_TRAIN, 500000, 0},
/*450*/	{"Article Trailer 2", VTYPE_TRAILER, 150000, 10},
/*451*/	{"Turismo", VTYPE_CAR, 1050000, 2},
/*452*/	{"Speeder", VTYPE_SEA, 755000, 2},
/*453*/	{"Reefer", VTYPE_SEA, 480000, 8},
/*454*/	{"Tropic", VTYPE_SEA, 830000, 6},
/*455*/	{"Flatbed", VTYPE_CAR, 180000, 8},
/*456*/	{"Yankee", VTYPE_CAR, 155000, 8},
/*457*/	{"Caddy", VTYPE_CAR, 85000, 0},
/*458*/	{"Solair", VTYPE_CAR, 80000, 4},
/*459*/	{"Berkley's RC Van", VTYPE_CAR, 90000, 6},
/*460*/	{"Skimmer", VTYPE_PLANE, 405000, 0},
/*461*/	{"PCJ-600", VTYPE_BIKE, 75000, 0},
/*462*/	{"Faggio", VTYPE_BIKE, 9000, 0},
/*463*/	{"Freeway", VTYPE_BIKE, 70000, 0},
/*464*/	{"RC Baron", VTYPE_PLANE, 500000, 0},
/*465*/	{"RC Raider", VTYPE_HELI, 500000, 0},
/*466*/	{"Glendale", VTYPE_CAR, 45000, 4},
/*467*/	{"Oceanic", VTYPE_CAR, 41000, 4},
/*468*/	{"Sanchez", VTYPE_BIKE, 55000, 0},
/*469*/	{"Sparrow", VTYPE_HELI, 415000, 0},
/*470*/	{"Patriot", VTYPE_CAR, 315000, 4},
/*471*/	{"Quad", VTYPE_QUAD, 30000, 0},
/*472*/	{"Coastguard", VTYPE_SEA, 150000, 2},
/*473*/	{"Dinghy", VTYPE_SEA, 55000, 0},
/*474*/	{"Hermes", VTYPE_CAR, 61000, 2},
/*475*/	{"Sabre", VTYPE_CAR, 90000, 2},
/*476*/	{"Rustler", VTYPE_PLANE, 1500000, 0},
/*477*/	{"ZR-350", VTYPE_CAR, 625000, 2},
/*478*/	{"Walton", VTYPE_CAR, 25000, 4},
/*479*/	{"Regina", VTYPE_CAR, 65000, 4},
/*480*/	{"Comet", VTYPE_CAR, 400000, 2},
/*481*/	{"BMX", VTYPE_BMX, 7000, 0},
/*482*/	{"Burrito", VTYPE_CAR, 95000, 6},
/*483*/	{"Camper", VTYPE_CAR, 50000, 4},
/*484*/	{"Marquis", VTYPE_SEA, 485000, 4},
/*485*/	{"Baggage", VTYPE_CAR, 40000, 0},
/*486*/	{"Dozer", VTYPE_CAR, 500000, 0},
/*487*/	{"Maverick", VTYPE_HELI, 1200000, 4},
/*488*/	{"SAN News Maverick", VTYPE_HELI, 1200000, 2},
/*489*/	{"Rancher", VTYPE_CAR, 105000, 4},
/*490*/	{"FBI Rancher", VTYPE_CAR, 150000, 4},
/*491*/	{"Virgo", VTYPE_CAR, 55000, 2},
/*492*/	{"Greenwood", VTYPE_CAR, 60000, 4},
/*493*/	{"Jetmax", VTYPE_SEA, 770000, 2},
/*494*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0},
/*495*/	{"Sandking", VTYPE_CAR, 1000000, 4},
/*496*/	{"Blista Compact", VTYPE_CAR, 100500, 2},
/*497*/	{"Police Maverick", VTYPE_HELI, 1500000, 4},
/*498*/	{"Boxville", VTYPE_CAR, 80000, 8},
/*499*/	{"Benson", VTYPE_CAR, 70000, 8},
/*500*/	{"Mesa", VTYPE_CAR, 60000, 2},
/*501*/	{"RC Goblin", VTYPE_HELI, 500000, 0},
/*502*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0},
/*503*/	{"Hotring Racer", VTYPE_CAR, 1000000, 0},
/*504*/	{"Bloodring Banger", VTYPE_CAR, 200000, 0},
/*505*/	{"Rancher", VTYPE_CAR, 105000, 4},
/*506*/	{"Super GT", VTYPE_CAR, 700000, 2},
/*507*/	{"Elegant", VTYPE_CAR, 80000, 4},
/*508*/	{"Journey", VTYPE_CAR, 180000, 6},
/*509*/ {"Bike", VTYPE_BMX, 2500, 0},
/*510*/	{"Mountain Bike", VTYPE_BMX, 10000, 0},
/*511*/	{"Beagle", VTYPE_PLANE, 415000, 4},
/*512*/	{"Cropduster", VTYPE_PLANE, 400000, 0},
/*513*/	{"Stuntplane", VTYPE_PLANE, 420000, 0},
/*514*/	{"Tanker", VTYPE_CAR, 440000, 4},
/*515*/	{"Roadtrain", VTYPE_CAR, 485000, 4},
/*516*/	{"Nebula", VTYPE_CAR, 47500, 4},
/*517*/	{"Majestic", VTYPE_CAR, 60000, 2},
/*518*/	{"Buccaneer", VTYPE_CAR, 45000, 2},
/*519*/	{"Shamal", VTYPE_PLANE, 1500000, 6},
/*520*/	{"Hydra", VTYPE_PLANE, 10000000, 0},
/*521*/	{"FCR-900", VTYPE_BIKE, 80000, 0},
/*522*/	{"NRG-500", VTYPE_BIKE, 575000, 0},
/*523*/	{"HPV1000", VTYPE_BIKE, 100000, 0},
/*524*/	{"Cement Truck", VTYPE_CAR, 130000, 0},
/*525*/	{"Towtruck", VTYPE_HEAVY, 90000, 0},
/*526*/	{"Fortune", VTYPE_CAR, 55000, 2},
/*527*/	{"Cadrona", VTYPE_CAR, 41000, 2},
/*528*/	{"FBI Truck", VTYPE_CAR, 250000, 2},
/*529*/	{"Willard", VTYPE_CAR, 50000, 4},
/*530*/	{"Forklift", VTYPE_CAR, 90000, 0},
/*531*/	{"Tractor", VTYPE_HEAVY, 40000, 0},
/*532*/	{"Combine Harvester", VTYPE_HEAVY, 600000, 0},
/*533*/	{"Feltzer", VTYPE_CAR, 110000, 2},
/*534*/	{"Remington", VTYPE_CAR, 86000, 4},
/*535*/	{"Slamvan", VTYPE_CAR, 90000, 4},
/*536*/	{"Blade", VTYPE_CAR, 95000, 2},
/*537*/	{"Freight", VTYPE_TRAIN, 2000000, 0},
/*538*/	{"Brownstreak", VTYPE_TRAIN, 2000000, 0},
/*539*/	{"Vortex", VTYPE_SEA, 1550000, 0},
/*540*/	{"Vincent", VTYPE_CAR, 60000, 4},
/*541*/	{"Bullet", VTYPE_CAR, 850000, 2},
/*542*/	{"Clover", VTYPE_CAR, 40000, 2},
/*543*/	{"Sadler", VTYPE_CAR, 30000, 6},
/*544*/	{"Firetruck LA", VTYPE_CAR, 400000, 0},
/*545*/	{"Hustler", VTYPE_CAR, 325000, 2},
/*546*/	{"Intruder", VTYPE_CAR, 65000, 4},
/*547*/	{"Primo", VTYPE_CAR, 50000, 4},
/*548*/	{"Cargobob", VTYPE_HELI, 1600000, 6},
/*549*/	{"Tampa", VTYPE_CAR, 50000, 4},
/*550*/	{"Sunrise", VTYPE_CAR, 85000, 4},
/*551*/	{"Merit", VTYPE_CAR, 110000, 4},
/*552*/	{"Utility Van", VTYPE_CAR, 230000, 4},
/*553*/	{"Nevada", VTYPE_PLANE, 1250000, 6},
/*554*/	{"Yosemite", VTYPE_CAR, 90000, 6},
/*555*/	{"Windsor", VTYPE_CAR, 150000, 2},
/*556*/	{"Monster A", VTYPE_MONSTER, 700000, 0},
/*557*/	{"Monster B", VTYPE_MONSTER, 700000, 0},
/*558*/	{"Uranus", VTYPE_CAR, 350000, 2},
/*559*/	{"Jester", VTYPE_CAR, 500000, 2},
/*560*/	{"Sultan", VTYPE_CAR, 575000, 4},
/*561*/	{"Stratum", VTYPE_CAR, 200000, 4},
/*562*/	{"Elegy", VTYPE_CAR, 495000, 2},
/*563*/	{"Raindance", VTYPE_HELI, 1350000, 4},
/*564*/	{"RC Tiger", VTYPE_CAR, 500000, 0},
/*565*/	{"Flash", VTYPE_CAR, 375000, 2},
/*566*/	{"Tahoma", VTYPE_CAR, 90000, 4},
/*567*/	{"Savanna", VTYPE_CAR, 85000, 4},
/*568*/	{"Bandito", VTYPE_CAR, 40000, 0},
/*569*/	{"Freight Flat Trailer", VTYPE_TRAIN, 500000, 0},
/*570*/	{"Streak Trailer", VTYPE_TRAIN, 1000000, 0},
/*571*/	{"Kart", VTYPE_CAR, 25000, 0},
/*572*/	{"Mower", VTYPE_CAR, 15000, 0},
/*573*/	{"Dune", VTYPE_MONSTER, 1000000, 6},
/*574*/	{"Sweeper", VTYPE_CAR, 50000, 0},
/*575*/	{"Broadway", VTYPE_CAR, 85000, 2},
/*576*/	{"Tornado", VTYPE_CAR, 68000, 2},
/*577*/	{"AT400", VTYPE_PLANE, 3500000, 6},
/*578*/	{"DFT-30", VTYPE_CAR, 190000, 2},
/*579*/	{"Huntley", VTYPE_CAR, 135000, 4},
/*580*/	{"Stafford", VTYPE_CAR, 95000, 4},
/*581*/	{"BF-400", VTYPE_BIKE, 60000, 0},
/*582*/	{"Newsvan", VTYPE_CAR, 125000, 4},
/*583*/	{"Tug", VTYPE_CAR, 25000, 0},
/*584*/	{"Petrol Trailer", VTYPE_TRAILER, 300000, 0},
/*585*/	{"Emperor", VTYPE_CAR, 45000, 4},
/*586*/	{"Wayfarer", VTYPE_BIKE, 50000, 0},
/*587*/	{"Euros", VTYPE_CAR, 400000, 2},
/*588*/	{"Hotdog", VTYPE_HEAVY, 90000, 0},
/*589*/	{"Club", VTYPE_CAR, 150000, 2},
/*590*/	{"Freight Box Trailer", VTYPE_TRAIN, 350000, 0},
/*591*/	{"Article Trailer 3", VTYPE_TRAILER, 200000, 10},
/*592*/	{"Andromada", VTYPE_PLANE, 3500000, 10},
/*593*/	{"Dodo", VTYPE_PLANE, 525000, 2},
/*594*/	{"RC Cam", VTYPE_CAR, 500000, 0},
/*595*/	{"Launch", VTYPE_SEA, 725000, 2},
/*596*/	{"Police Car (LSPD)", VTYPE_CAR, 100000, 4},
/*597*/	{"Police Car (SFPD)", VTYPE_CAR, 100000, 4},
/*598*/	{"Police Car (LVPD)", VTYPE_CAR, 100000, 4},
/*599*/	{"Police Ranger", VTYPE_CAR, 135000, 4},
/*600*/	{"Picador", VTYPE_CAR, 40000, 4},
/*601*/	{"S.W.A.T.", VTYPE_CAR, 450000, 0},
/*602*/	{"Alpha", VTYPE_CAR, 350000, 2},
/*603*/	{"Phoenix", VTYPE_CAR, 500000, 2},
/*604*/	{"Glendale Shit", VTYPE_CAR, 22000, 4},
/*605*/	{"Sadler Shit", VTYPE_CAR, 19000, 4},
/*606*/	{"Baggage Trailer A", VTYPE_TRAILER, 50000, 0},
/*607*/	{"Baggage Trailer B", VTYPE_TRAILER, 50000, 0},
/*608*/	{"Tug Stairs Trailer", VTYPE_TRAILER, 50000, 0},
/*609*/	{"Boxville", VTYPE_CAR, 85000, 8},
/*610*/	{"Farm Trailer", VTYPE_TRAILER, 75000, 0},
/*611*/	{"Utility Trailer", VTYPE_TRAILER, 75000, 0}

};

GetVehicleMaxTrunkSlots(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return CarModels[modelid-400][mTrunkSlots];
}

GetVehicleModelTrunkSlots(modelid)
{
	if(modelid < 400 || modelid > 611)
		return 0;

	return CarModels[modelid-400][mTrunkSlots];
}

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

GetVehicleType(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if(modelid == 0)
		return 0;

	return CarModels[modelid-400][mType];
}

VehTypeName(type) {
    new name[32];
    switch(type) {
        case 0: format(name, 32, "ninguno");
		case 1,8,10: format(name, 32, "venta");
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

stock getVehicleJob(vehid) {
	return VehicleInfo[vehid][VehJob];
}

stock getVehicleType(vehid) {
	return VehicleInfo[vehid][VehType];
}

stock getVehicleDescription(vehicleid){
	new vehdesc[64];
	format(vehdesc,64, "%s de %s",GetVehicleName(vehicleid),VehicleInfo[vehicleid][VehOwnerName]);
	return vehdesc;
}

public respawnVeh(vehicleid) {
	SetVehicleToRespawn(vehicleid);
	return 1;
}

//========================[VEHICLE GLOBAL VARIABLES]============================

new vlocked,
	LastVeh[MAX_PLAYERS],
	bool:OfferingVehicle[MAX_PLAYERS],
	VehicleOfferPrice[MAX_PLAYERS],
	VehicleOffer[MAX_PLAYERS],
	VehicleOfferID[MAX_PLAYERS],
	CarWindowStatus[MAX_VEH],
	bool:startingEngine[MAX_PLAYERS];

//=============[VEHICLE DAO FUNCTIONS | DYNAMIC CAR SYSTEM]=====================

stock LoadVehicles() {
	new
		query[128],
		vehicleID = 1;

	while(vehicleID < MAX_VEH) {
	    format(query, sizeof(query), "SELECT * FROM `vehicles` WHERE `VehSQLID` = %d LIMIT 1", vehicleID);
		mysql_function_query(dbHandle, query, true, "OnVehicleDataLoad", "i", vehicleID);
		CarWindowStatus[vehicleID] = 1;
		vehicleID++;
	}
	return 1;
}

resetVehicle(id)
{
    VehicleInfo[id][VehType]        = 0;
    VehicleInfo[id][VehModel] 		= 411;
    VehicleInfo[id][VehPosX] 		= 9999;
    VehicleInfo[id][VehPosY] 		= 9999;
    VehicleInfo[id][VehPosZ] 		= 9999;
    VehicleInfo[id][VehAngle] 		= 0;
    VehicleInfo[id][VehColor1]		= 0;
    VehicleInfo[id][VehColor2]		= 0;
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
    VehicleInfo[id][VehMarijuana]	= 0;
    VehicleInfo[id][VehLSD]			= 0;
    VehicleInfo[id][VehEcstasy]		= 0;
    VehicleInfo[id][VehCocaine]		= 0;
	VehicleInfo[id][VehHP]			= 100;
	VehicleInfo[id][VehPlate]		= "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	VehicleInfo[id][VehOwnerName]	= "XXXXXXXXXXXXXXXXXXXXXXX";
	for(new i = 0; i < 14; i++) {
        VehicleInfo[id][VehCompSlot][i] = 0;
	}
	ResetTrunk(id);
	return 1;
}

SaveVehicle(id)
{
	if(dontsave)
		return 1;

    new query[1024];

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

	format(query,sizeof(query),"UPDATE vehicles SET VehModel=%d,VehPosX=%f,VehPosY=%f,VehPosZ=%f,VehAngle=%f,VehColor1=%d,VehColor2=%d,VehFaction=%d,VehJob=%d,VehDamage1=%d,VehDamage2=%d,VehDamage3=%d,VehDamage4=%d,VehType=%d,VehOwnerID=%d,VehLocked=%d,VehEngine=%d,VehBonnet=%d,VehBoot=%d,VehLights=%d,VehFuel=%d,VehHP=%f,VehPlate='%s',VehOwnerName='%s'",
		VehicleInfo[id][VehModel],
	    VehicleInfo[id][VehPosX],
	    VehicleInfo[id][VehPosY],
	    VehicleInfo[id][VehPosZ],
	    VehicleInfo[id][VehAngle],
	    VehicleInfo[id][VehColor1],
	    VehicleInfo[id][VehColor2],
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
		VehicleInfo[id][VehHP],
		VehicleInfo[id][VehPlate],
		VehicleInfo[id][VehOwnerName]
	);
	
	format(query,sizeof(query),"%s,VehCompSlot0=%d,VehCompSlot1=%d,VehCompSlot2=%d,VehCompSlot3=%d,VehCompSlot4=%d,VehCompSlot5=%d,VehCompSlot6=%d,VehCompSlot7=%d,VehCompSlot8=%d,VehCompSlot9=%d,VehCompSlot10=%d,VehCompSlot11=%d,VehCompSlot12=%d,VehCompSlot13=%d,VehMarijuana=%d,VehLSD=%d,VehEcstasy=%d,VehCocaine=%d WHERE `VehSQLID` = %d",
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
	printf("[INFO]: vehículos guardados.");
	return 1;
}

//====[VEHICLE CHECK FUNCTIONS]=================================================
public IsVehicleOccupied(vehicleid)
{
	foreach(new i : Player)
	{
		if(IsPlayerInVehicle(i,vehicleid)) return 1;
	}
	return 0;
}
public IsAPlane(vehicleid)
{   new model = GetVehicleModel(vehicleid);
	if(model == 592 || model == 577 || model == 511 || model == 512 || model == 593 || model == 520 || model == 553 || model == 476 || model == 519 || model == 460 || model == 513)
	{
		return 1;
	}
	return 0;
}
public IsAHelicopter(vehicleid)
{   new model = GetVehicleModel(vehicleid);
	if(model == 548 || model == 417 || model == 487 || model == 488 || model == 497 || model == 563 || model == 447 || model == 469)
	{
		return 1;
	}
	return 0;
}
public IsABike(vehicleid)
{   new model = GetVehicleModel(vehicleid);
	if(model == 581 || model == 509 || model == 481 || model == 462 || model == 521 || model == 463 || model == 510 || model == 522 || model == 461 || model == 448 || model == 471 || model == 468 || model == 586)
	{
		return 1;
	}
	return 0;
}

//===========================[VEHICLE BUSINESS LOGIC]===========================

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

public OnVehicleStreamIn(vehicleid, forplayerid) {
    return 1;
}

public OnVehicleSpawn(vehicleid) {
	switch(VehicleInfo[vehicleid][VehType]) {
	    case VEH_NONE: {
	    	SetVehiclePos(vehicleid, 9999.0, 9999.0, 0.0);
	    }
	    case VEH_CREATED: {
		    VehicleInfo[vehicleid][VehType] = VEH_NONE;
		    SetVehiclePos(vehicleid, 9999.0, 9999.0, 0.0);
		}
		case VEH_OWNED: {
		    UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][VehDamage1], VehicleInfo[vehicleid][VehDamage2], VehicleInfo[vehicleid][VehDamage3], VehicleInfo[vehicleid][VehDamage4]);
 			for(new i = 0; i < 14; i++) {
 			    if(VehicleInfo[vehicleid][VehCompSlot][i] != 0) {
 			    	AddVehicleComponent(vehicleid, VehicleInfo[vehicleid][VehCompSlot][i]);
				}
 			}
		}
        case VEH_FACTION: {
		}
		default: {
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

stock TakeItemFromTrunk(playerid, playerhand, vehicleid, trunkslot)
{
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
  		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
 	if(PlayerInfo[playerid][pHealth] < 25)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
		
	new	itemid = GetTrunkItem(vehicleid, trunkslot),
		itemparam = GetTrunkParam(vehicleid, trunkslot),
		str[128];
		
	if(itemid <= 0)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
	if(GetHandItem(playerid, playerhand) != 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tomar el item ya que tienes la mano ocupada.");

	SetHandItemAndParam(playerid, playerhand, itemid, itemparam); // Creación lógica y grafica en la mano.
	SetTrunkItemAndParam(vehicleid, trunkslot, 0, 0);
	format(str, sizeof(str), "toma un/a %s del maletero.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
	format(str, sizeof(str), "tomar %d %s slot %d", itemparam, GetItemName(itemid), trunkslot);
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", str);
	return 1;
}

stock SaveItemOnTrunk(playerid, playerhand, vehicleid, trunkslot)
{
	if(GetPVarInt(playerid, "disabled") != DISABLE_NONE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo en este momento.");
    if(PlayerInfo[playerid][pHealth] < 25)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
	if(GetHandItem(playerid, playerhand) == WEAPON_SILENCED && isPlayerUsingTazer(playerid))
   		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el tazer.");
	if(GetPVarInt(playerid, "cantSaveItems") == 1)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a interactuar con otro item!");
	if(GetHandItem(playerid, playerhand) == ITEM_ID_TELEFONO_CELULAR)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes hacerlo con el teléfono.");
		
	new itemid = GetHandItem(playerid, playerhand),
	    itemparam = GetHandParam(playerid, playerhand),
		validslot,
		str[128];

	if(itemid == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes nada en esa mano para guardar.");

	if(trunkslot == -1) // Si no eligió donde guardarlo
	{
		validslot = SearchTrunkFreeSlot(vehicleid);
		if(validslot == -1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero se encuentra lleno!");
 	} else // Si nos dijo donde guardarlo
	 	{
	 	    validslot = trunkslot;
			if(validslot < 0 || validslot >= GetVehicleMaxTrunkSlots(vehicleid))
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Slot inválido.");
	   		if(GetTrunkItem(vehicleid, validslot) != 0)
				return SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un item en ese slot.");
		}
		
	SetTrunkItemAndParam(vehicleid, validslot, itemid, itemparam);
	SetHandItemAndParam(playerid, playerhand, 0, 0); // Borrado lógico y grafico.
	format(str, sizeof(str), "guarda un/a %s en el maletero.", GetItemName(itemid));
	PlayerActionMessage(playerid, 15.0, str);
  	SetPVarInt(playerid, "cantSaveItems", 1);
	SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
	format(str, sizeof(str), "guardar %d %s slot %d", itemparam, GetItemName(itemid), trunkslot);
	VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", str);
	return 1;
}

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
    if(GetVehicleMaxTrunkSlots(vehicleid) == 0)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene maletero!");
	if(VehicleInfo[vehicleid][VehBoot] != 1 && !AdminDuty[playerid])
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero está cerrado!");
        
    if(sscanf(params, "s[32]S(-1)[32]I(-1)", cmd, returnstr, returnid2))
	{
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero [comando]");
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomar/tomari [slot de item] - guardar/guardari [slot (opcional)] - guardardroga [tipo] [cant]");
     	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Comandos]:{C8C8C8} tomardroga [tipo] [cant] - guardardinero [cant] - tomardinero [slot de item]");
		PrintTrunkForPlayer(vehicleid, playerid);
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
	
	if(strcmp(cmd, "guardardroga", true) == 0)
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
	else if(strcmp(cmd, "guardardinero", true) == 0)
	{
		if(PlayerInfo[playerid][pHealth] < 25)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
	    new amount = strval(returnstr);
	    if(amount < 1 || amount > 250000)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes guardar menos de $1 ni más de $250.000 por slot.");
		if(GetPlayerCash(playerid) < amount)
			return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad de efectivo.");

		new validslot = SearchTrunkFreeSlot(vehicleid);
		if(validslot == -1)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero se encuentra lleno!");
			
		SetPVarInt(playerid, "cantSaveItems", 1);
		SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
		SetTrunkItemAndParam(vehicleid, validslot, 51, amount);
		GivePlayerCash(playerid, -amount);
		VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
	}
	else if(strcmp(cmd, "tomardinero", true) == 0)
	{

		new slot = strval(returnstr);
        if(GetTrunkItem(vehicleid, slot) != 51)
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
			
		GivePlayerCash(playerid, GetTrunkParam(vehicleid, slot));
		SetTrunkItemAndParam(vehicleid, slot, 0, 0);
		VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/mal", params);
    }
	else if(strcmp(cmd, "tomar", true) == 0)
	{
		TakeItemFromTrunk(playerid, HAND_RIGHT, vehicleid, strval(returnstr));
    }
	else if(strcmp(cmd, "tomari", true) == 0)
	{
		TakeItemFromTrunk(playerid, HAND_LEFT, vehicleid, strval(returnstr));
    }
	else if(strcmp(cmd, "guardar", true) == 0)
	{
		SaveItemOnTrunk(playerid, HAND_RIGHT, vehicleid, strval(returnstr));
    }
	else if(strcmp(cmd, "guardari", true) == 0)
	{
		SaveItemOnTrunk(playerid, HAND_LEFT, vehicleid, strval(returnstr));
    }
	return 1;
}

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
	if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP || VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP2 || VehicleInfo[vehicleid][VehType] == VEH_SHIPYARD)
	    return 1;
	if(VehicleInfo[vehicleid][VehFuel] < 1)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo no tiene combustible.");
	if(VehicleInfo[vehicleid][VehType] == VEH_OWNED && !playerHasCarKey(playerid, vehicleid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_FACTION && VehicleInfo[vehicleid][VehFaction] != PlayerInfo[playerid][pFaction])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehType] == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(jobRequiresVehicle(VehicleInfo[vehicleid][VehJob]))
	    return SendClientMessage(playerid, COLOR_WHITE, "Para encender este vehículo utiliza /trabajar.");
	if(VehicleInfo[vehicleid][VehJob] != 0 && PlayerInfo[playerid][pJob] != VehicleInfo[vehicleid][VehJob])
	    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes las llaves.");
	if(VehicleInfo[vehicleid][VehHP] < 500)
 	{
	    PlayerActionMessage(playerid, 15.0, "intenta encender el motor del vehículo pero se encuentra dañado.");
	    SendClientMessage(playerid, COLOR_YELLOW2, "El vehículo se encuentra averiado.");
	    return 1;
	}
	
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

//==========================COMANDOS DE VEHICULOS===============================

CMD:veh(playerid, params[])
{
	cmd_vehiculo(playerid, params);
	return 1;
}

CMD:vehiculo(playerid, params[])
{
	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "===========================[COMANDOS DE VEHÍCULOS]===========================");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/vehcomprar [color1] [color2] - /vehvender - /vehvendera [ID/Jugador] [ID vehículo] [precio] - /vehestacionar");
    SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "/vehpuertas - /vehluces - /vehmal - /vehcapot");
	return 1;
}

CMD:vehcomprar(playerid, params[])
{
	new playerName[MAX_PLAYER_NAME], color1, color2, vehicleid, price, newveh = -1;

	if(sscanf(params, "ii", color1, color2))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /vehcomprar [color1] [color2]");
	if(!IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en ningún vehículo!");
	vehicleid = GetPlayerVehicleID(playerid);
	if(VehicleInfo[vehicleid][VehType] != VEH_DEALERSHIP && VehicleInfo[vehicleid][VehType] != VEH_DEALERSHIP2 && VehicleInfo[vehicleid][VehType] != VEH_SHIPYARD)
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes comprar un vehículo que no está a la venta!");
	//if(PlayerInfo[playerid][pVeh1] != 0 && PlayerInfo[playerid][pVeh2] != 0)
	if(getPlayerFreeKeySlots(playerid) < 1)
		return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes espacio en tu llavero para más vehículos.");
	price = GetVehiclePrice(vehicleid, ServerInfo[sVehiclePricePercent]);
    if(GetPlayerCash(playerid) < price)
        return SendClientMessage(playerid, COLOR_YELLOW2,"* Vendedor: ¡Vuelve cuando tengas el dinero suficiente!");
	if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
		return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa colores válidos (0-255). Si no conoces los colores, busca en la wiki de SAMP; 0: Negro, 1: Blanco.");

	for(new vid = 1; vid < MAX_VEH; vid++)
	{
		if(VehicleInfo[vid][VehType] == VEH_NONE)
		{
		    newveh = vid;
		    break;
		}
    }
    if(newveh == -1) // Si no encontró ningun auto de tipo VEH_NONE es pq ya no hay mas lugar dentro de los MAX_VEH
		return SendClientMessage(playerid, COLOR_YELLOW2, "[OOC]: No hay mas espacio para autos en el servidor. REPORTAR A UN ADMIN.");

	GivePlayerCash(playerid, -price);
 	GetPlayerName(playerid, playerName, sizeof(playerName));
	VehicleInfo[newveh][VehType] = VEH_OWNED;
	VehicleInfo[newveh][VehOwnerSQLID] = PlayerInfo[playerid][pID];
	VehicleInfo[newveh][VehOwnerName] = playerName;
	VehicleInfo[newveh][VehColor1] = color1;
	VehicleInfo[newveh][VehColor2] = color2;
	VehicleInfo[newveh][VehModel] = VehicleInfo[vehicleid][VehModel];
	format(VehicleInfo[newveh][VehPlate], 32, "%c%c%c-%d%d%d",65+random(26),65+random(26),65+random(26),random(10),random(10),random(10));
	
	if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP)
	{
		VehicleInfo[newveh][VehPosX] = 2127.6501;
		VehicleInfo[newveh][VehPosY] = -1117.1167;
		VehicleInfo[newveh][VehPosZ] = 24.9961;
		VehicleInfo[newveh][VehAngle] = 251.4242;
	}
	else if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP2)
	{
		VehicleInfo[newveh][VehPosX] = 553.4331;
		VehicleInfo[newveh][VehPosY] = -1250.9829;
		VehicleInfo[newveh][VehPosZ] = 16.5953;
		VehicleInfo[newveh][VehAngle] = 300.7206;
	}
	else if(VehicleInfo[vehicleid][VehType] == VEH_SHIPYARD)
	{
		VehicleInfo[newveh][VehPosX] = 2963.1904;
		VehicleInfo[newveh][VehPosY] = -2090.9250;
		VehicleInfo[newveh][VehPosZ] = 0.6618;
		VehicleInfo[newveh][VehAngle] = 176.0365;
	}
	VehicleInfo[newveh][VehFuel] = 100;
	SendClientMessage(playerid, COLOR_YELLOW2, "¡Felicidades, has comprado este vehículo!");
	SendClientMessage(playerid, COLOR_WHITE, "Estacionalo con '/vehestacionar' fuera de la consecionaria, de no hacerlo podrá ser incautado.");
	/*if(PlayerInfo[playerid][pVeh1] == 0) {
		PlayerInfo[playerid][pVeh1] = newveh;
		VehicleInfo[newveh][VehOwnerSlot] = 1;
	} else {
	    PlayerInfo[playerid][pVeh2] = newveh;
	    VehicleInfo[newveh][VehOwnerSlot] = 2;
	}*/
	
 	DestroyVehicle(newveh);
	newveh = CreateVehicle(VehicleInfo[newveh][VehModel], VehicleInfo[newveh][VehPosX], VehicleInfo[newveh][VehPosY], VehicleInfo[newveh][VehPosZ], VehicleInfo[newveh][VehAngle], VehicleInfo[newveh][VehColor1], VehicleInfo[newveh][VehColor2], -1);
	
	addKeyToPlayer(playerid,newveh,playerid);
	PutPlayerInVehicle(playerid, newveh, 0);
	SaveVehicle(newveh);
	VehicleLog(newveh, playerid, INVALID_PLAYER_ID, "/vehcomprar", params);
	return 1;
}

CMD:vehvender(playerid, params[])
{
	new vehicleid;

	if(!IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en ningún vehículo!");
	if(!IsAtDealership(playerid))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes vender un vehículo en cualquier lugar. Debes ir a una consecionaria!");
	vehicleid = GetPlayerVehicleID(playerid);
    if(!playerOwnsCar(playerid,vehicleid))
        return SendClientMessage(playerid, COLOR_YELLOW2, "¡No podés vender un vehículo que no te pertenece!");

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
	if(IsAtDealership(playerid))
 		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes estacionar un vehículo en la consecionaria!");
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
		 	(vehicleType == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid) )
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
		 	(vehicleType == VEH_RENT && PlayerInfo[playerid][pRentCarID] != vehicleid) )
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
	if(PlayerInfo[playerid][pAdmin] >= 20) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[LVL 20]{C8C8C8} /avtipo - /avmodelo - /avcolor - /avfaccion - /avempleo - /avhp - /avnitro - /avcrear - /avcrearperma");
		SendClientMessage(playerid,	COLOR_LIGHTYELLOW2,	"{878EE7}[INFO]:{C8C8C8} para 'eliminar' un vehículo utiliza '/avtipo 0', si éste estaba asociado a un personaje el...");
	 	SendClientMessage(playerid,	COLOR_LIGHTYELLOW2,	"{C8C8C8}...vehículo será eliminado de su cuenta. Si no estas seguro de los tipos, consulta a un scripter y NO uses el comando.");
	}
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
 			VehicleLog(i, playerid, INVALID_PLAYER_ID, "/avrespawnall", params);
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
		VehicleLog(c, playerid, INVALID_PLAYER_ID, "/avfuelcars", params);
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
		VehicleLog(c, playerid, INVALID_PLAYER_ID, "/avfixcars", params);
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
	ResetTrunk(vehicleid);
	for(new i = 0; i < 14; i++) {
 	    VehicleInfo[vehicleid][VehCompSlot][i] = 0;
 	}
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
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avtipo [idtipo]");
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

	if(type == VEH_NONE)
		resetVehicle(vehicleid);

    VehicleInfo[vehicleid][VehType] = type;
    SendFMessage(playerid, COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} el tipo del vehículo %d ha sido ajustado a %d.", vehicleid, type);
	SaveVehicle(vehicleid);
	SetVehicleToRespawn(vehicleid);
	if(type != VEH_NONE && type != VEH_CREATED)
		PutPlayerInVehicle(playerid, vehicleid, 0);
    VehicleLog(vehicleid, playerid, INVALID_PLAYER_ID, "/avtipo", params);
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
			SendClientMessage(playerid,COLOR_RED,"{878EE7}[INFO]:{C8C8C8} vehículo creado correctamente (desaparecerá luego de 5 minutos sin utilizar).");
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
			SendClientMessage(playerid,COLOR_RED,"{878EE7}[INFO]:{C8C8C8} vehículo creado correctamente (no desaparecerá hasta que sea eliminado o reinicie el servidor).");
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
	if(vhp < 500 || vhp > 10000)
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} Solo valores comprendidos en intervalo (500 - 10000).");

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
