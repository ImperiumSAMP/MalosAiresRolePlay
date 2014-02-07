#if defined _isamp_vehicles_included
	#endinput
#endif
#define _isamp_vehicles_included

#include "isamp-util.inc"
#include "isamp-database.inc"
#include "isamp-inventory.inc"
#include "isamp-players.inc"

/**
* Isamp Vehicles functions and defines
**/

//Defines
#define MAX_VEH                 1001
#define MAX_RENTCAR             20

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

#define TRUNK_MAX_SLOTS         5

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
	VehOwnerSlot,
 	Float:VehHP, // Reemplazar VehDamaged?
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
	VehCocaine
};
new VehicleInfo[MAX_VEH][Cars];

enum RCars {
	vrID,
	vrRented,
	vrTime,
	vrOwnerSQLID,
};
new RentCar[MAX_RENTCAR][RCars];

enum Trunks {
	trunk0[16],
	trunk1[16],
	trunk2[16],
	trunk3[16],
};
new TrunkInfo[MAX_VEH][Trunks];

//Forwards
forward IsAPlane(vehicleid);
forward IsAHelicopter(vehicleid);
forward IsVehicleOccupied(vehicleid);
forward IsABike(vehicleid);

//Timers
forward respawnVeh(vehicleid);

//====[VEHICLE MISC FUNCTIONS]=====================

VehTypeName(type) {
    new name[32];
    switch(type) {
        case 0: format(name, 32, "ninguno");
		case 1: format(name, 32, "venta");
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

GetVehicleName(vehicleid) {
	new name[32];
	switch(GetVehicleModel(vehicleid)) {
	   case 400: format(name,32,"Landstalker");
	   case 401: format(name,32,"Bravura");
	   case 402: format(name,32,"Buffalo");
	   case 403: format(name,32,"Linerunner");
	   case 404: format(name,32,"Perenniel");
	   case 405: format(name,32,"Sentinel");
	   case 406: format(name,32,"Dumper");
	   case 407: format(name,32,"Firetruck");
	   case 408: format(name,32,"Trashmaster");
	   case 409: format(name,32,"Stretch");
	   case 410: format(name,32,"Manana");
	   case 411: format(name,32,"Infernus");
	   case 412: format(name,32,"Voodoo");
	   case 413: format(name,32,"Pony");
	   case 414: format(name,32,"Mule");
	   case 415: format(name,32,"Cheetah");
	   case 416: format(name,32,"Ambulance");
	   case 417: format(name,32,"Leviathan");
	   case 418: format(name,32,"Moonbeam");
	   case 419: format(name,32,"Esperanto");
	   case 420: format(name,32,"Taxi");
	   case 421: format(name,32,"Washington");
	   case 422: format(name,32,"Bobcat");
	   case 423: format(name,32,"Mr Whoopee");
	   case 424: format(name,32,"BF Injection");
	   case 425: format(name,32,"Hunter");
	   case 426: format(name,32,"Premier");
	   case 427: format(name,32,"Enforcer");
	   case 428: format(name,32,"Securicar");
	   case 429: format(name,32,"Banshee");
	   case 430: format(name,32,"Predator");
	   case 431: format(name,32,"Bus");
	   case 432: format(name,32,"Rhino");
	   case 433: format(name,32,"Barracks");
	   case 434: format(name,32,"Hotknife");
	   case 435: format(name,32,"Article Trailer");
	   case 436: format(name,32,"Previon");
	   case 437: format(name,32,"Coach");
	   case 438: format(name,32,"Cabbie");
	   case 439: format(name,32,"Stallion");
	   case 440: format(name,32,"Rumpo");
	   case 441: format(name,32,"RC Bandit");
	   case 442: format(name,32,"Romero");
	   case 443: format(name,32,"Packer");
	   case 444: format(name,32,"Monster");
	   case 445: format(name,32,"Admiral");
	   case 446: format(name,32,"Squallo");
	   case 447: format(name,32,"Seasparrow");
	   case 448: format(name,32,"Pizzaboy");
	   case 449: format(name,32,"Tram");
	   case 450: format(name,32,"Article Trailer 2");
	   case 451: format(name,32,"Turismo");
	   case 452: format(name,32,"Speeder");
	   case 453: format(name,32,"Reefer");
	   case 454: format(name,32,"Tropic");
	   case 455: format(name,32,"Flatbed");
	   case 456: format(name,32,"Yankee");
	   case 457: format(name,32,"Caddy");
	   case 458: format(name,32,"Solair");
	   case 459: format(name,32,"Berkley's RC Van");
	   case 460: format(name,32,"Skimmer");
	   case 461: format(name,32,"PCJ-600");
	   case 462: format(name,32,"Faggio");
	   case 463: format(name,32,"Freeway");
	   case 464: format(name,32,"RC Baron");
	   case 465: format(name,32,"RC Raider");
	   case 466: format(name,32,"Glendale");
	   case 467: format(name,32,"Oceanic");
	   case 468: format(name,32,"Sanchez");
	   case 469: format(name,32,"Sparrow");
	   case 470: format(name,32,"Patriot");
	   case 471: format(name,32,"Quad");
	   case 472: format(name,32,"Coastguard");
	   case 473: format(name,32,"Dinghy");
	   case 474: format(name,32,"Hermes");
	   case 475: format(name,32,"Sabre");
	   case 476: format(name,32,"Rustler");
	   case 477: format(name,32,"ZR-350");
	   case 478: format(name,32,"Walton");
	   case 479: format(name,32,"Regina");
	   case 480: format(name,32,"Comet");
	   case 481: format(name,32,"BMX");
	   case 482: format(name,32,"Burrito");
	   case 483: format(name,32,"Camper");
	   case 484: format(name,32,"Marquis");
	   case 485: format(name,32,"Baggage");
	   case 486: format(name,32,"Dozer");
	   case 487: format(name,32,"Maverick");
	   case 488: format(name,32,"SAN News Maverick");
	   case 489: format(name,32,"Rancher");
	   case 490: format(name,32,"FBI Rancher");
	   case 491: format(name,32,"Virgo");
	   case 492: format(name,32,"Greenwood");
	   case 493: format(name,32,"Jetmax");
	   case 494: format(name,32,"Hotring Racer");
	   case 495: format(name,32,"Sandking");
	   case 496: format(name,32,"Blista Compact");
	   case 497: format(name,32,"Police Maverick");
	   case 498: format(name,32,"Boxville");
	   case 499: format(name,32,"Benson");
	   case 500: format(name,32,"Mesa");
	   case 501: format(name,32,"RC Goblin");
	   case 502: format(name,32,"Hotring Racer");
	   case 503: format(name,32,"Hotring Racer");
	   case 504: format(name,32,"Bloodring Banger");
	   case 505: format(name,32,"Rancher");
	   case 506: format(name,32,"Super GT");
	   case 507: format(name,32,"Elegant");
	   case 508: format(name,32,"Journey");
	   case 509: format(name,32,"Bike");
	   case 510: format(name,32,"Mountain Bike");
	   case 511: format(name,32,"Beagle");
	   case 512: format(name,32,"Cropduster");
	   case 513: format(name,32,"Stuntplane");
	   case 514: format(name,32,"Tanker");
	   case 515: format(name,32,"Roadtrain");
	   case 516: format(name,32,"Nebula");
	   case 517: format(name,32,"Majestic");
	   case 518: format(name,32,"Buccaneer");
	   case 519: format(name,32,"Shamal");
	   case 520: format(name,32,"Hydra");
	   case 521: format(name,32,"FCR-900");
	   case 522: format(name,32,"NRG-500");
	   case 523: format(name,32,"HPV1000");
	   case 524: format(name,32,"Cement Truck");
	   case 525: format(name,32,"Towtruck");
	   case 526: format(name,32,"Fortune");
	   case 527: format(name,32,"Cadrona");
	   case 528: format(name,32,"FBI Truck");
	   case 529: format(name,32,"Willard");
	   case 530: format(name,32,"Forklift");
	   case 531: format(name,32,"Tractor");
	   case 532: format(name,32,"Combine Harvester");
	   case 533: format(name,32,"Feltzer");
	   case 534: format(name,32,"Remington");
	   case 535: format(name,32,"Slamvan");
	   case 536: format(name,32,"Blade");
	   case 537: format(name,32,"Freight");
	   case 538: format(name,32,"Brownstreak");
	   case 539: format(name,32,"Vortex");
	   case 540: format(name,32,"Vincent");
	   case 541: format(name,32,"Bullet");
	   case 542: format(name,32,"Clover");
	   case 543: format(name,32,"Sadler");
	   case 544: format(name,32,"Firetruck LA");
	   case 545: format(name,32,"Hustler");
	   case 546: format(name,32,"Intruder");
	   case 547: format(name,32,"Primo");
	   case 548: format(name,32,"Cargobob");
	   case 549: format(name,32,"Tampa");
	   case 550: format(name,32,"Sunrise");
	   case 551: format(name,32,"Merit");
	   case 552: format(name,32,"Utility Van");
	   case 553: format(name,32,"Nevada");
	   case 554: format(name,32,"Yosemite");
	   case 555: format(name,32,"Windsor");
	   case 556: format(name,32,"Monster A");
	   case 557: format(name,32,"Monster B");
	   case 558: format(name,32,"Uranus");
	   case 559: format(name,32,"Jester");
	   case 560: format(name,32,"Sultan");
	   case 561: format(name,32,"Stratum");
	   case 562: format(name,32,"Elegy");
	   case 563: format(name,32,"Raindance");
	   case 564: format(name,32,"RC Tiger");
	   case 565: format(name,32,"Flash");
	   case 566: format(name,32,"Tahoma");
	   case 567: format(name,32,"Savanna");
	   case 568: format(name,32,"Bandito");
	   case 569: format(name,32,"Freight Flat Trailer");
	   case 570: format(name,32,"Streak Trailer");
	   case 571: format(name,32,"Kart");
	   case 572: format(name,32,"Mower");
	   case 573: format(name,32,"Dune");
	   case 574: format(name,32,"Sweeper");
	   case 575: format(name,32,"Broadway");
	   case 576: format(name,32,"Tornado");
	   case 577: format(name,32,"AT400");
	   case 578: format(name,32,"DFT-30");
	   case 579: format(name,32,"Huntley");
	   case 580: format(name,32,"Stafford");
	   case 581: format(name,32,"BF-400");
	   case 582: format(name,32,"Newsvan");
	   case 583: format(name,32,"Tug");
	   case 584: format(name,32,"Petrol Trailer");
	   case 585: format(name,32,"Emperor");
	   case 586: format(name,32,"Wayfarer");
	   case 587: format(name,32,"Euros");
	   case 588: format(name,32,"Hotdog");
	   case 589: format(name,32,"Club");
	   case 590: format(name,32,"Freight Box Trailer");
	   case 591: format(name,32,"Article Trailer 3");
	   case 592: format(name,32,"Andromada");
	   case 593: format(name,32,"Dodo");
	   case 594: format(name,32,"RC Cam");
	   case 595: format(name,32,"Launch");
	   case 596: format(name,32,"Police Car (LSPD)");
	   case 597: format(name,32,"Police Car (SFPD)");
	   case 598: format(name,32,"Police Car (LVPD)");
	   case 599: format(name,32,"Police Ranger");
	   case 600: format(name,32,"Picador");
	   case 601: format(name,32,"S.W.A.T.");
	   case 602: format(name,32,"Alpha");
	   case 603: format(name,32,"Phoenix");
	   case 604: format(name,32,"Glendale Shit");
	   case 605: format(name,32,"Sadler Shit");
	   case 606: format(name,32,"Baggage Trailer A");
	   case 607: format(name,32,"Baggage Trailer B");
	   case 608: format(name,32,"Tug Stairs Trailer");
	   case 609: format(name,32,"Boxville");
	   case 610: format(name,32,"Farm Trailer");
	   case 611: format(name,32,"Utility Trailer");
	}
	return name;
}

GetVehiclePrice(vehicleid, priceperc) {
	new price;
	new model = GetVehicleModel(vehicleid);
	switch(model)
	{
		case 400: price = 70000;
		case 401: price = 31000;
		case 402: price = 500000;
		case 403: price = 455800;
		case 404: price = 28900;
		case 405: price = 68300;
		case 406: price = 853700;
		case 407: price = 311800;
		case 408: price = 280000;
		case 409: price = 406000;
		case 410: price = 26300;
		case 411: price = 990500;
		case 412: price = 69100;
		case 413: price = 105100;
		case 414: price = 98200;
		case 415: price = 750400;
		case 416: price = 550100;
		case 417: price = 910000;
		case 418: price = 80400;
		case 419: price = 58000;
		case 420: price = 86000;
		case 421: price = 75100;
		case 422: price = 35800;
		case 423: price = 98800;
		case 424: price = 65100;
		case 426: price = 80500;
		case 428: price = 400000;
		case 429: price = 595000;
		case 431: price = 592000;
		case 434: price = 384000;
		case 436: price = 39000;
		case 437: price = 599000;
		case 438: price = 79000;
		case 439: price = 65000;
		case 440: price = 95000;
		case 442: price = 105000;
		case 443: price = 428000;
		case 444: price = 675000;
		case 445: price = 61000;
		case 446: price = 775000;
		case 448: price = 25000;
		case 451: price = 1050000;
		case 452: price = 755000;
		case 453: price = 480000;
		case 454: price = 830000;
		case 455: price = 180000;
		case 456: price = 155000;
		case 457: price = 85000;
		case 458: price = 80000;
		case 459: price = 90000;
		case 460: price = 405000;
		case 461: price = 75000;
		case 462: price = 9000;
		case 463: price = 70000;
		case 466: price = 45000;
		case 467: price = 41000;
		case 468: price = 55000;
		case 469: price = 415000;
		case 470: price = 315000;
		case 471: price = 30000;
		case 473: price = 55000;
		case 474: price = 61000;
		case 475: price = 90000;
		case 477: price = 625000;
		case 478: price = 25000;
		case 479: price = 65000;
		case 480: price = 400000;
		case 481: price = 7000;
		case 482: price = 95000;
		case 483: price = 50000;
		case 484: price = 485000;
		case 485: price = 40000;
		case 486: price = 500000;
		case 487: price = 1200000;
		case 489: price = 105000;
		case 491: price = 55000;
		case 492: price = 60000;
		case 493: price = 770000;
		case 494: price = 1500000;
		case 495: price = 1300000;
		case 496: price = 100500;
		case 498: price = 80000;
		case 499: price = 70000;
		case 500: price = 60000;
		case 502: price = 1500000;
		case 503: price = 1500000;
		case 504: price = 200000;
		case 505: price = 105000;
		case 506: price = 700000;
		case 507: price = 80000;
		case 508: price = 180000;
		case 509: price = 2500;
		case 510: price = 10000;
		case 511: price = 415000;
		case 512: price = 400000;
		case 513: price = 420000;
		case 514: price = 440000;
		case 515: price = 485000;
		case 516: price = 47500;
		case 517: price = 60000;
		case 518: price = 45000;
		case 519: price = 1500000;
		case 521: price = 80000;
		case 522: price = 575000;
		case 524: price = 130000;
		case 525: price = 90000;
		case 526: price = 55000;
		case 527: price = 41000;
		case 529: price = 50000;
		case 530: price = 90000;
		case 531: price = 40000;
		case 532: price = 600000;
		case 533: price = 110000;
		case 534: price = 86000;
		case 535: price = 90000;
		case 536: price = 95000;
		case 539: price = 1550000;
		case 540: price = 60000;
		case 541: price = 850000;
		case 542: price = 40000;
		case 543: price = 30000;
		case 545: price = 325000;
		case 546: price = 65000;
		case 547: price = 50000;
		case 549: price = 50000;
		case 550: price = 85000;
		case 551: price = 110000;
		case 552: price = 230000;
		case 553: price = 1250000;
		case 554: price = 90000;
		case 555: price = 150000;
		case 556: price = 700000;
		case 557: price = 680000;
		case 558: price = 350000;
		case 559: price = 500000;
		case 560: price = 575000;
		case 561: price = 200000;
		case 562: price = 495000;
		case 563: price = 1350000;
		case 565: price = 375000;
		case 566: price = 90000;
		case 567: price = 85000;
		case 568: price = 40000;
		case 571: price = 25000;
		case 572: price = 15000;
		case 573: price = 250000;
		case 575: price = 85000;
		case 576: price = 68000;
		case 577: price = 3500000;
		case 578: price = 190000;
		case 579: price = 135000;
		case 580: price = 95000;
		case 581: price = 60000;
		case 583: price = 25000;
		case 585: price = 45000;
		case 586: price = 50000;
		case 587: price = 400000;
		case 588: price = 90000;
		case 589: price = 150000;
		case 592: price = 3500000;
		case 593: price = 525000;
		case 595: price = 725000;
		case 600: price = 40000;
	    case 602: price = 350000;
		case 603: price = 500000;
		case 604: price = 22000;
		case 605: price = 19000;
		case 609: price = 85000;
		default: price = 0;
	}
	price = price / 100 * priceperc;
	return price;
}

stock GetVehicleType(vehicleid) {
	new
		type = 0;

	switch(GetVehicleModel(vehicleid)) {
		case 416,602,485,568,429,499,424,536,496,504,422,609,498,401,575,518,402,
		541,482,431,438,457,527,483,524,415,542,5689,480,596,599,597,598,578,486,
		507,562,585,427,419,587,490,528,533,544,407,565,455,530,526,466,604,492,
		474,434,502,503,494,579,545,411,546,559,508,571,400,403,517,410,551,500,
		418,572,423,516,582,467,404,514,603,445,600,413,426,436,547,489,441,594,564,
		515,479,534,505,442,440,475,543,605,495,567,428,405,535,458,580,439,561,
		409,560,550,506,601,574,566,549,420,459,576,583,451,558,552,540,491,412,
		478,421,529,555,456,554,477,589,470: type = VTYPE_CAR;

		case 581,523,462,521,463,522,461,448,468,586: type = VTYPE_BIKE;

		case 509,481,510: type = VTYPE_BMX;

		case 471: type = VTYPE_QUAD;

		case 472,473,493,595,484,430,453,452,446,454: type = VTYPE_SEA;
		
		case 548,425,417,487,497,563,501,465,447,469,488: type = VTYPE_HELI;

		case 592,577,511,512,593,520,553,464,476,519,460,513,539: type = VTYPE_PLANE;

		case 588,437,532,433,414,443,432,525,531,408: type = VTYPE_HEAVY;

		case 406,573,444,556,557: type = VTYPE_MONSTER;

		case 435,450,591,606,607,610,584,608,611: type = VTYPE_TRAILER;

		case 590,569,537,538,570,449: type = VTYPE_TRAIN;
	}
	return type;
}

public respawnVeh(vehicleid) {
	SetVehicleToRespawn(vehicleid);
	return 1;
}

//====[VEHICLE GLOBAL VARIABLES]=====================
new vlocked,
	LastVeh[MAX_PLAYERS],
	bool:OfferingVehicle[MAX_PLAYERS],
	VehicleOfferPrice[MAX_PLAYERS],
	VehicleOffer[MAX_PLAYERS],
	VehicleOfferID[MAX_PLAYERS],
	CarWindowStatus[MAX_VEH],
	ShowFuel[MAX_PLAYERS];

//====[VEHICLE DAO FUNCTIONS | DYNAMIC CAR SYSTEM]=====================

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

resetVehicle(id) {
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
    VehicleInfo[id][VehOwnerSlot]	= 0;
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
	resetTrunk(id);
	return 1;
}

SaveVehicle(id) {
	if(dontsave) return 1;

    new
		query[1024];

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

	format(query,sizeof(query),"UPDATE vehicles SET VehModel=%d,VehPosX=%f,VehPosY=%f,VehPosZ=%f,VehAngle=%f,VehColor1=%d,VehColor2=%d,VehFaction=%d,VehJob=%d,VehDamage1=%d,VehDamage2=%d,VehDamage3=%d,VehDamage4=%d,VehType=%d,VehOwnerID=%d,VehLocked=%d,VehEngine=%d,VehBonnet=%d,VehBoot=%d,VehLights=%d,VehOwnerSlot=%d,VehFuel=%d,VehHP=%f,VehTrunkSlot0='%s',VehTrunkSlot1='%s',VehTrunkSlot2='%s',VehTrunkSlot3='%s',VehPlate='%s',VehOwnerName='%s'",
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
	    VehicleInfo[id][VehOwnerSlot],
	    VehicleInfo[id][VehFuel],
		VehicleInfo[id][VehHP],
		TrunkInfo[id][trunk0],
		TrunkInfo[id][trunk1],
		TrunkInfo[id][trunk2],
		TrunkInfo[id][trunk3],
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

//============[VEHICLE BUSINESS LOGIC]====================================================
SetEngine(vehicleid, status)
{
    GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	switch(status)
	{
	    case 0: // Apagar.
	    {
         	if(VehicleInfo[vehicleid][VehEngine] == 1)
         	{
         	    VehicleInfo[vehicleid][VehEngine] = 0;
         	}
         	else return 0;
	    }
	    case 1: // Encender.
		{
		  	if(VehicleInfo[vehicleid][VehEngine] != 1)
         	{
         	    VehicleInfo[vehicleid][VehEngine] = 1;
         	}
         	else return 0;
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

//============[VEHICLE EVENT HANDLERS]====================================================

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
            VehicleInfo[vehicleid][VehBonnet] = 0;
 			VehicleInfo[vehicleid][VehBoot] = 0;
		}
        case VEH_FACTION: {
            VehicleInfo[vehicleid][VehBonnet] = 0;
 			VehicleInfo[vehicleid][VehBoot] = 0;
		}
		default: {
		    //SetVehiclePos(vehicleid, VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ]);
		}
	}
	return 1;
}

//============[VEHICLE COMMANDS]====================================================
//[CMD_VEHICULOS]
CMD:mal(playerid, params[]) {
 	cmd_maletero(playerid, params);
	return 1;
}

CMD:maletero(playerid, params[]) {
	new
	    vehicleid,
	    itemid,
	    param,
	    returnstr[32],
	    returnid2,
	    text[128];

    vehicleid = GetClosestVehicle(playerid, 5.0);
    if(IsPlayerInAnyVehicle(playerid))
       	return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes salir del vehículo primero!");
    if(vehicleid == INVALID_VEHICLE_ID)
       	return SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún vehículo cerca tuyo.");
    if(GetVehicleType(vehicleid) != VTYPE_CAR)
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene maletero!");
	if(VehicleInfo[vehicleid][VehBoot] != 1 && !AdminDuty[playerid])
	   	return SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero está cerrado!");
        
    if(sscanf(params, "s[128]S(null)[32]I(-1)", text, returnstr, returnid2)) {
        SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero [comando]");
    	SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Comandos: ver - tomar [slot de item] - guardar [slot, opcional] - guardardroga [tipo] [cantidad] - tomardroga [tipo] [cantidad]");
		SendClientMessage(playerid, COLOR_WHITE, "|---------------- Maletero ----------------|");
		for(new i = 0; i < TRUNK_MAX_SLOTS-1; i++) {
            itemid = getTrunkItem(vehicleid, i);
            param = getTrunkParam(vehicleid, i);
            if(getTrunkItemType(vehicleid, i) == ITEM_WEAPON) {
            	SendFMessage(playerid, COLOR_WHITE, " - %d- Arma: %s - Munición: %d", i, itemName[itemid], param);
			} else if(getTrunkItemType(vehicleid, i) == ITEM_OTHER) {
                SendFMessage(playerid, COLOR_WHITE, " - %d- Item: %s - Cantidad: %d", i, itemName[itemid], param);
			} else {
			    SendFMessage(playerid, COLOR_WHITE, " - %d- Nada", i);
			}
        }
    	SendClientMessage(playerid, COLOR_WHITE, " ------------------------------------------------");
		if(VehicleInfo[vehicleid][VehMarijuana] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Marihuana: %d gramos.", VehicleInfo[vehicleid][VehMarijuana]);
		}
		if(VehicleInfo[vehicleid][VehLSD] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - LSD: %d dosis.", VehicleInfo[vehicleid][VehLSD]);
		}
		if(VehicleInfo[vehicleid][VehEcstasy] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Extasis: %d dosis.", VehicleInfo[vehicleid][VehEcstasy]);
		}
		if(VehicleInfo[vehicleid][VehCocaine] > 0) {
		    SendFMessage(playerid, COLOR_WHITE, " - Cocaína: %d gramos.", VehicleInfo[vehicleid][VehCocaine]);
		}
        SendClientMessage(playerid, COLOR_WHITE, "|------------------------------------------------|");
	} else {
		if(strcmp(text,"ver",true) == 0) {
			SendClientMessage(playerid, COLOR_YELLOW2, "Utiliza (/mal)etero solo.");
	    } else if(strcmp(text, "guardardroga", true) == 0) {
			if(SellingDrugs[playerid])
			    return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes utilizarlo mientras vendes drogas.");
			    
            if(strcmp(returnstr, "marihuana", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");
                
                if(PlayerInfo[playerid][pMarijuana] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pMarijuana] -= returnid2;
                VehicleInfo[vehicleid][VehMarijuana] += returnid2;
                PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            } else if(strcmp(returnstr, "lsd", true) == 0) {
    			if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(PlayerInfo[playerid][pLSD] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pLSD] -= returnid2;
             	VehicleInfo[vehicleid][VehLSD] += returnid2;
             	PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            } else if(strcmp(returnstr, "extasis", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(PlayerInfo[playerid][pEcstasy] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pEcstasy] -= returnid2;
                VehicleInfo[vehicleid][VehEcstasy] += returnid2;
                PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            } else if(strcmp(returnstr, "cocaina", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(PlayerInfo[playerid][pCocaine] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pCocaine] -= returnid2;
                VehicleInfo[vehicleid][VehCocaine] += returnid2;
                PlayerActionMessage(playerid, 15.0, "guarda un paquete sospechoso dentro de su vehículo.");
            } else {
                SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero guardardroga [tipo] [cantidad]");
           		SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
            }
	    } else if(strcmp(text, "tomardroga", true) == 0) {
	       	if(strcmp(returnstr, "marihuana", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

                if(VehicleInfo[vehicleid][VehMarijuana] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pMarijuana] += returnid2;
                VehicleInfo[vehicleid][VehMarijuana] -= returnid2;
                PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            } else if(strcmp(returnstr, "lsd", true) == 0) {
    			if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(VehicleInfo[vehicleid][VehLSD] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pLSD] += returnid2;
             	VehicleInfo[vehicleid][VehLSD] -= returnid2;
             	PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            } else if(strcmp(returnstr, "extasis", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(VehicleInfo[vehicleid][VehEcstasy] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pEcstasy] += returnid2;
                VehicleInfo[vehicleid][VehEcstasy] -= returnid2;
                PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            } else if(strcmp(returnstr, "cocaina", true) == 0) {
                if(returnid2 <= 0 || returnid2 > 5000)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "La cantidad no debe ser menor a 0 o mayor que 5000.");

            	if(VehicleInfo[vehicleid][VehCocaine] < returnid2)
                    return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes esa cantidad.");

				PlayerInfo[playerid][pCocaine] += returnid2;
                VehicleInfo[vehicleid][VehCocaine] -= returnid2;
                PlayerActionMessage(playerid, 15.0, "toma un paquete sospechoso de su vehículo.");
            } else {
                SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/mal)etero tomardroga [tipo] [cantidad]");
           		SendClientMessage(playerid, COLOR_YELLOW2, "Tipos: marihuana - lsd - extasis - cocaina");
            }
	    } else if(strcmp(text, "tomar", true) == 0) {
	        if(getTrunkItemType(vehicleid, strval(returnstr)) == ITEM_WEAPON) {
	            GivePlayerWeapon(playerid, getTrunkItem(vehicleid, strval(returnstr)), getTrunkParam(vehicleid, strval(returnstr)));
				setTrunkItem(vehicleid, strval(returnstr), 0);
	        } else {
	            SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
	        }
	    } else if(strcmp(text, "guardar", true) == 0) {
    		if(PlayerInfo[playerid][pHealth] < 25)
				return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes usar este comando agonizando");
	        if(PlayerInfo[playerid][pLevel] >= 3) {
		        if(GetPVarInt(playerid, "cantSaveItems") == 0) {
			        if(GetPlayerWeapon(playerid) >= 1 && GetPlayerWeapon(playerid) <= 15 || GetPlayerWeapon(playerid) >= 16 && GetPlayerWeapon(playerid) <= 38 || GetPlayerWeapon(playerid) == 41 || GetPlayerWeapon(playerid) == 43) {
						if(returnid2 == -1) {
							new validslot = -1;
							if(isPlayerCopOnDuty(playerid)) {
				                SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes hacer esto en servicio!");
				                return 1;
							}
							for(new i = 0; i < TRUNK_MAX_SLOTS-1; i++) {
							    if(getTrunkItemType(vehicleid, i) == ITEM_NONE) {
									validslot = i;
									break;
							    }
							}
							if(validslot > -1) {
							    SetPVarInt(playerid, "cantSaveItems", 1);
							    SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
								setTrunkItem(vehicleid, validslot, GetPlayerWeapon(playerid));
								setTrunkParam(vehicleid, validslot, GetPlayerAmmo(playerid));
								RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));
							} else {
				            	SendClientMessage(playerid, COLOR_YELLOW2, "¡El maletero se encuentra lleno!");
				        	}
			        	} else if(returnid2 > -1 && returnid2 < TRUNK_MAX_SLOTS) {
			        	    if(getTrunkItemType(vehicleid, returnid2) == ITEM_NONE) {
			        	        SetPVarInt(playerid, "cantSaveItems", 1);
							    SetTimerEx("cantSaveItems", 2000, false, "i", playerid);
			        	        setTrunkItem(vehicleid, returnid2, GetPlayerWeapon(playerid));
								setTrunkParam(vehicleid, returnid2, GetPlayerAmmo(playerid));
								RemovePlayerWeapon(playerid, GetPlayerWeapon(playerid));
			        	    } else {
	                            SendClientMessage(playerid, COLOR_YELLOW2, "Ya tienes un item en ese hueco.");
							}
			        	} else {
			        	    SendFMessage(playerid, COLOR_YELLOW2, "¡El valor no debe ser menor de 0 o mayor de %d!", TRUNK_MAX_SLOTS-1);
			        	}
			        } else {
						SendClientMessage(playerid, COLOR_YELLOW2, "¡Item inválido o inexistente!");
					}
				} else {
			   		SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes esperar un tiempo antes de volver a guardar un item!");
			   	}
	        } else {
				SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes ser al menos nivel 3 para utilizar este comando!");
			}
	    }
	}
	return 1;
}

CMD:usarbidon(playerid, params[]) {
	new
	    gasAmount,
		validslot = -1,
		refillAmount,
		vehicleid;

	if(IsPlayerInAnyVehicle(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar fuera del vehículo.");

	for(new i = 0; i < INV_MAX_SLOTS; i++) {
	    if(getInvItem(playerid, i) == 48) {
	        gasAmount = getInvParam(playerid, i);
	    	if(gasAmount > 0) {
	    	    validslot = i;
	    	    break;
			}
	    }
	}
	vehicleid = GetClosestVehicle(playerid, 4.0);
	if(validslot == -1) {
		SendClientMessage(playerid, COLOR_YELLOW2, "Debes tener un bidón con algo de combustible para utilizar este comando.");
	} else if(vehicleid != INVALID_VEHICLE_ID) {
		TogglePlayerControllable(playerid, false);
        refillAmount = 100 - VehicleInfo[vehicleid][VehFuel];
        if(refillAmount >= gasAmount) {
            SetPVarInt(playerid, "fuelCarWithCan", SetTimerEx("fuelCarWithCan", 6000, false, "iii", playerid, vehicleid, VehicleInfo[vehicleid][VehFuel] += gasAmount));
            GameTextForPlayer(playerid, "~w~Llenando tanque", 6000, 4);
			setInvParam(playerid, validslot, 0);
			PlayerActionMessage(playerid, 15.0, "abre la tapa del tanque y vacía todo el contenido del bidón dentro.");
            SendFMessage(playerid, COLOR_WHITE, "Has vaciado el bidón, tu vehículo ahora tiene un %d por ciento de combustible.", VehicleInfo[vehicleid][VehFuel]);
        } else {
            SetPVarInt(playerid, "fuelCarWithCan", SetTimerEx("fuelCarWithCan", 6000, false, "iii", playerid, vehicleid, 100));
            GameTextForPlayer(playerid, "~w~Llenando tanque", 6000, 4);
            setInvParam(playerid, validslot, gasAmount - refillAmount);
            PlayerActionMessage(playerid, 15.0, "abre la tapa del tanque y vacía parte del bidón dentro.");
            SendFMessage(playerid, COLOR_WHITE, "Has llenado el tanque de tu vehículo tu bidón ahora tiene un %d por ciento de combustible.", getInvParam(playerid, validslot));
        }
	} else {
	    SendClientMessage(playerid, COLOR_YELLOW2, "No hay ningún vehículo cerca tuyo.");
	}
	return 1;
}

CMD:veh(playerid, params[]) {
	cmd_vehiculo(playerid, params);
	return 1;
}

CMD:vehiculo(playerid,params[]) {
	new
	    playerName[24],
		text[128],
		targetid,
		extraparam,
		Float:x,
		Float:y,
		Float:z,
		Float:angle,
		vehicleid,
		vehicleid2,
		vehicleid3,
		price;

	if(sscanf(params, "s[128]I(-1)I(-1)I(-1)", text, targetid, vehicleid3, extraparam)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/veh)iculo [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Comandos]: comprar [color1] [color2] - vender - vendera [ID jugador] [ID vehículo] [dinero] - estacionar - puertas - luces - mal - capot");
	} else if(strcmp(text, "comprar", true) == 0) {
		vehicleid = GetPlayerVehicleID(playerid);
		price = GetVehiclePrice(vehicleid, ServerInfo[sVehiclePricePercent]);
		if(!IsPlayerInAnyVehicle(playerid)) {
		    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No te encuentras en ningún vehículo!");
		} else if(VehicleInfo[vehicleid][VehType] != VEH_DEALERSHIP && VehicleInfo[vehicleid][VehType] != VEH_DEALERSHIP2) {
		    SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes comprar un vehículo que no está a la venta!");
		} else if(PlayerInfo[playerid][pVeh1] != 0 && PlayerInfo[playerid][pVeh2] != 0) {
			SendClientMessage(playerid, COLOR_YELLOW2, "No puedes tener más de dos vehículos.");
		} else if(price <= GetPlayerCash(playerid)) {
			new color1 = targetid;
		    new color2 = vehicleid3;
			if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
			    return SendClientMessage(playerid, COLOR_YELLOW2, "Ingresa colores válidos (0-255). ((Si no sabes los colores, busca en la wiki de SAMP; 0=negro, 1=blanco.))");
			    
		    for(new vid = 1; vid < MAX_VEH; vid++) {
				if(VehicleInfo[vid][VehType] == VEH_NONE) {
				    vehicleid2 = vid;
				    break;
				}
		    }
		    
		    GivePlayerCash(playerid, -price);
		    GetPlayerName(playerid, playerName, sizeof(playerName));
		    
		    VehicleInfo[vehicleid2][VehType] = VEH_OWNED;
			VehicleInfo[vehicleid2][VehOwnerSQLID] = PlayerInfo[playerid][pID];
			VehicleInfo[vehicleid2][VehOwnerName] = playerName;
			VehicleInfo[vehicleid2][VehColor1] = color1;
			VehicleInfo[vehicleid2][VehColor2] = color2;
			VehicleInfo[vehicleid2][VehModel] = VehicleInfo[vehicleid][VehModel];
			if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP) {
				VehicleInfo[vehicleid2][VehPosX] = 2127.6501;
				VehicleInfo[vehicleid2][VehPosY] = -1117.1167;
				VehicleInfo[vehicleid2][VehPosZ] = 24.9961;
				VehicleInfo[vehicleid2][VehAngle] = 251.4242;
			} else if(VehicleInfo[vehicleid][VehType] == VEH_DEALERSHIP2) {
				VehicleInfo[vehicleid2][VehPosX] = 553.4331;
				VehicleInfo[vehicleid2][VehPosY] = -1250.9829;
				VehicleInfo[vehicleid2][VehPosZ] = 16.5953;
				VehicleInfo[vehicleid2][VehAngle] = 300.7206;
			}
			
			VehicleInfo[vehicleid2][VehFuel] = 100;
			
			SendClientMessage(playerid, COLOR_YELLOW2, "¡Felicidades, has comprado este vehículo!");
			SendClientMessage(playerid, COLOR_WHITE, "Estacionalo con '(/veh)iculo estacionar' fuera de la consecionaria, de no hacerlo podrá ser incautado.");
			if(PlayerInfo[playerid][pVeh1] == 0) {
				PlayerInfo[playerid][pVeh1] = vehicleid2;
				VehicleInfo[vehicleid2][VehOwnerSlot] = 1;
			} else {
			    PlayerInfo[playerid][pVeh2] = vehicleid2;
			    VehicleInfo[vehicleid2][VehOwnerSlot] = 2;
			}
			
		    DestroyVehicle(vehicleid2);
	     	vehicleid2 = CreateVehicle(VehicleInfo[vehicleid2][VehModel], VehicleInfo[vehicleid2][VehPosX], VehicleInfo[vehicleid2][VehPosY], VehicleInfo[vehicleid2][VehPosZ], VehicleInfo[vehicleid2][VehAngle], VehicleInfo[vehicleid2][VehColor1], VehicleInfo[vehicleid2][VehColor2], -1);
			PutPlayerInVehicle(playerid, vehicleid2, 0);
		    SaveVehicle(vehicleid2);
		} else {
			SendClientMessage(playerid,COLOR_YELLOW2,"* Vendedor: ¡vuelve cuando tengas el dinero suficiente!");
		}
	} else if(strcmp(text,"vender",true) == 0) {
	    vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid))	{
		} else if(!IsAtDealership(playerid)) {
		    SendClientMessage(playerid, COLOR_YELLOW2, "¡No puedes vender un vehículo en cualquier lugar!");
		} else if(PlayerInfo[playerid][pVeh1] == vehicleid || PlayerInfo[playerid][pVeh2] == vehicleid)	{
			Choice[playerid] = CHOICE_CARSELL;
			SendClientMessage(playerid, COLOR_FADE1, "Empleado: ¿estás seguro de que quieres vender tu vehículo?");
            SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "Presiona 'Y' para aceptar o 'N' para cancelar.");
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡No podés vender un vehículo que no te pertenece!");
		}
	} else if(strcmp(text,"vendera",true) == 0) {
	    vehicleid = vehicleid3;
	    
	    // Controlamos que no esté vendiendo un vehículo.
	    if(OfferingVehicle[playerid])
	        return SendClientMessage(playerid, COLOR_YELLOW2, "Ya estás vendiendo un vehículo.");

	    // ¿Vehículo existente?
		if(vehicleid <= 0 || vehicleid > MAX_VEH - 1)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "La ID del vehículo es inválida.");
		
		// ¿Objetivo correcto?
		if(targetid == INVALID_PLAYER_ID)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "La ID de jugador indicada es inválida o se encuentra desconectado.");

		// Controlamos que el precio haya sido ingresado y esté dentro de los límites.
	    if(extraparam < 0 || extraparam > 10000000)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "El precio no puede ser menor a $0 ni mayor a $10,000,000.");

		// ¿El vehículo tiene dueño?
		if(VehicleInfo[vehicleid][VehType] != VEH_OWNED)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no puede ser vendido.");
		    
		// Nos aseguramos que el vehículo al que está subido el jugador le pertenece.
		if(PlayerInfo[playerid][pVeh1] != vehicleid && PlayerInfo[playerid][pVeh2] != vehicleid)
		    return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no te pertenece.");
		    
		if(GetDistanceBetweenPlayers(playerid, targetid) > 4.0)
			return SendClientMessage(playerid, COLOR_YELLOW2, "La persona se encuentra demasiado lejos.");

        OfferingVehicle[playerid] = true;
        VehicleOfferPrice[targetid] = extraparam;
		VehicleOffer[targetid] = playerid;
		VehicleOfferID[targetid] = vehicleid;
		SendFMessage(playerid, COLOR_LIGHTBLUE, "Le has ofrecido las llaves de un %s a %s por $%d.", GetVehicleName(vehicleid), GetPlayerNameEx(targetid), extraparam);
		SendFMessage(targetid, COLOR_LIGHTBLUE, "%s te ha ofrecido un %s por $%d.", GetPlayerNameEx(playerid), GetVehicleName(vehicleid), extraparam);
		SendClientMessage(targetid, COLOR_LIGHTBLUE, "Utiliza '/aceptar vehiculo' para aceptar la oferta o '/cancelar vehiculo' para cancelar.");
        SetPVarInt(targetid, "CancelVehicleTransfer", SetTimerEx("CancelVehicleTransfer", 30 * 1000, 0, "ii", targetid, 1));
	} else if(strcmp(text, "estacionar", true) == 0) {
	    vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) {
			return 1;
		}
		if(IsAtDealership(playerid)) {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "¡No puedes estacionar un vehículo en la consecionaria!");
			return 1;
		}
		if(PlayerInfo[playerid][pVeh1] == vehicleid || PlayerInfo[playerid][pVeh2] == vehicleid) {
		
		    new Float:vehicleHealth;
			GetVehicleHealth(vehicleid, vehicleHealth);
			if(vehicleHealth < 700.0)
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
			
			SendClientMessage(playerid,COLOR_ADMINCMD, "{878EE7}[INFO]:{C8C8C8} vehículo estacionado correctamente.");
		} else {
			SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no te pertenece!");
		}
	} else if(strcmp(text,"puertas",true) == 0) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
		{
		    vehicleid = GetPlayerVehicleID(playerid);
            if(GetVehicleType(vehicleid) == VTYPE_BMX || GetVehicleType(vehicleid) == VTYPE_BIKE || GetVehicleType(vehicleid) == VTYPE_QUAD)
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no tiene puertas.");

			if( vehicleid != PlayerInfo[playerid][pVeh1] && vehicleid != PlayerInfo[playerid][pVeh2] && !AdminDuty[playerid] )
			{
   				if( VehicleInfo[vehicleid][VehType] == VEH_FACTION && PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][VehFaction] )
				{

				} else
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
			}

	   		if(VehicleInfo[vehicleid][VehLocked] != 1)
	   		{
				PlayerActionMessage(playerid,15.0, "ha asegurado las puertas del vehículo.");
				VehicleInfo[vehicleid][VehLocked] = 1;
			} else
				{
					PlayerActionMessage(playerid,15.0, "ha destrabado las puertas del vehículo.");
					VehicleInfo[vehicleid][VehLocked] = 0;
				}
		} else
		{
   			vehicleid = GetClosestVehicle(playerid, 10.0);
   			if(vehicleid == INVALID_VEHICLE_ID)
			   	return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo!");
			GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
	  		if(GetVehicleType(vehicleid) == VTYPE_BMX || GetVehicleType(vehicleid) == VTYPE_BIKE || GetVehicleType(vehicleid) == VTYPE_QUAD)
		    	return SendClientMessage(playerid, COLOR_YELLOW2, "Este vehículo no tiene puertas.");

			if( vehicleid != PlayerInfo[playerid][pVeh1] && vehicleid != PlayerInfo[playerid][pVeh2] && !AdminDuty[playerid] )
			{
				if( VehicleInfo[vehicleid][VehType] == VEH_FACTION && PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][VehFaction] )
				{

				} else
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
			}

	   		if(VehicleInfo[vehicleid][VehLocked] != 1)
	   		{
				PlayerActionMessage(playerid,15.0, "ha asegurado las puertas del vehículo.");
				VehicleInfo[vehicleid][VehLocked] = 1;
			} else
				{
					PlayerActionMessage(playerid,15.0, "ha destrabado las puertas del vehículo.");
					VehicleInfo[vehicleid][VehLocked] = 0;
				}
		}
	} else if(strcmp(text, "luces", true) == 0) {
		vehicleid = GetPlayerVehicleID(playerid);
		if(IsPlayerInAnyVehicle(playerid)) {
		    GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
			if(VehicleInfo[vehicleid][VehLights] != 1) {
			VehicleInfo[vehicleid][VehLights] = 1;
			GameTextForPlayer(playerid, "~w~Luces encendidas", 1000, 1);
			} else {
			    VehicleInfo[vehicleid][VehLights] = 0;
			    GameTextForPlayer(playerid, "~w~Luces apagadas", 1000, 1);
			}
			SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
		} else {
		    SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar adentro de un vehículo.");
		}
    } else if (strcmp(text, "mal", true) == 0)
			{
   				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar de pie.");
			        
				vehicleid = GetClosestVehicle(playerid, 5.0);
	   			if(vehicleid == INVALID_VEHICLE_ID)
	   			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo!");

	   			GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
		  		if(GetVehicleType(vehicleid) != VTYPE_CAR)
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene maletero!");
					
                if( vehicleid != PlayerInfo[playerid][pVeh1] && vehicleid != PlayerInfo[playerid][pVeh2] && !AdminDuty[playerid] )
				{
				    if( VehicleInfo[vehicleid][VehType] == VEH_FACTION && PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][VehFaction] )
					{

					} else
						return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
				}

				if(VehicleInfo[vehicleid][VehBoot] != 1)
			    {
		    		PlayerActionMessage(playerid,15.0,"ha abierto el maletero del vehículo.");
					VehicleInfo[vehicleid][VehBoot] = 1;
				} else
					{
						PlayerActionMessage(playerid,15.0,"ha cerrado el maletero del vehículo.");
						VehicleInfo[vehicleid][VehBoot] = 0;
					}
        		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
			}
	  else if (strcmp(text, "capot", true) == 0)
			{
   				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			        return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar de pie.");
			        
				vehicleid = GetClosestVehicle(playerid, 5.0);
	   			if(vehicleid == INVALID_VEHICLE_ID)
	   			    return SendClientMessage(playerid, COLOR_YELLOW2, "¡No hay ningún vehículo cerca tuyo!");

	   			GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
		  		if(GetVehicleType(vehicleid) != VTYPE_CAR)
					return SendClientMessage(playerid, COLOR_YELLOW2, "¡Este vehículo no tiene capot!");

                if( vehicleid != PlayerInfo[playerid][pVeh1] && vehicleid != PlayerInfo[playerid][pVeh2] && !AdminDuty[playerid] )
				{
				    if( VehicleInfo[vehicleid][VehType] == VEH_FACTION && PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][VehFaction] )
					{

					} else
						return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes las llaves de este vehículo!");
				}

				if(VehicleInfo[vehicleid][VehBonnet] != 1)
			    {
		    		PlayerActionMessage(playerid,15.0,"ha abierto el capot del vehículo.");
					VehicleInfo[vehicleid][VehBonnet] = 1;
				} else
					{
						PlayerActionMessage(playerid,15.0,"ha cerrado el capot del vehículo.");
						VehicleInfo[vehicleid][VehBonnet] = 0;
					}
        		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm], vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
			}
	return 1;
}



// Admin commands
//[CMD_A6]

CMD:avinfo(playerid, params[]) {
	new
		Float:hp,
	    id;

    if(PlayerInfo[playerid][pAdmin] < 2) return 1;
	if(sscanf(params, "d", id)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avinfo [idauto]");
	} else if(id >= 1 && id < MAX_VEH) {
	    GetVehicleHealth(id, hp);
	    SendFMessage(playerid, COLOR_WHITE, "|---- Auto %d [vid %d] ----|", id, VehicleInfo[id][VehSQLID]);
	    SendFMessage(playerid, COLOR_WHITE, "- Tipo: %d (%s)", VehicleInfo[id][VehType], VehTypeName(VehicleInfo[id][VehType]));
	    SendFMessage(playerid, COLOR_WHITE, "- Modelo: %d", VehicleInfo[id][VehModel]);
	    SendFMessage(playerid, COLOR_WHITE, "- Colores: %d-%d", VehicleInfo[id][VehColor1], VehicleInfo[id][VehColor2]);
	   	SendFMessage(playerid, COLOR_WHITE, "- Faccion: %d", VehicleInfo[id][VehFaction]);
	   	SendFMessage(playerid, COLOR_WHITE, "- Empleo: %d", VehicleInfo[id][VehJob]);
	   	SendFMessage(playerid, COLOR_WHITE, "- Dueño: %s pid: %d - slot: %d", VehicleInfo[id][VehOwnerName], VehicleInfo[id][VehOwnerSQLID], VehicleInfo[id][VehOwnerSlot]);
	   	SendFMessage(playerid, COLOR_WHITE, "- Patente: %s", VehicleInfo[id][VehPlate]);
	   	SendFMessage(playerid, COLOR_WHITE, "- HP: %f - HP2: %f", hp, VehicleInfo[id][VehHP]);
	   	SendFMessage(playerid, COLOR_WHITE, "- Gasolina: %d", VehicleInfo[id][VehFuel]);
		SendFMessage(playerid, COLOR_WHITE, "- Cerrado: %d", VehicleInfo[id][VehLocked]);
	} else {
	    SendClientMessage(playerid, COLOR_YELLOW2, "Auto inexistente.");
	}
	return 1;
}

CMD:aventrar(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;
	new vehid;
    if(sscanf(params, "i", vehid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /aventrar [idvehiculo]");
	if(vehid != INVALID_VEHICLE_ID && VehicleInfo[vehid][VehType] != 0) {
			PutPlayerInVehicle(playerid, vehid, 0);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
		}
	return 1;
}

CMD:avrespawn(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;
	new vehid;
    if(sscanf(params, "i", vehid))
		return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /avrespawn [idvehiculo]");
	if(vehid != INVALID_VEHICLE_ID && VehicleInfo[vehid][VehType] != 0) {
			SetVehicleToRespawn(vehid);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
		}
	return 1;
}

CMD:avrespawnall(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 3)
		return 1;
	for(new i = 1;i<MAX_VEH;i++) {
		    if(IsVehicleOccupied(i) == 0) {
		        SetVehicleToRespawn(i);
		    }
		}
	new string[128];
	format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} todos los vehículos desocupados han sido respawneados por %s.", GetPlayerNameEx(playerid));
	SendClientMessageToAll(COLOR_ADMINCMD, string);
	return 1;
}

CMD:av(playerid, params[]) {
	cmd_avehiculo(playerid, params);
	return 1;
}

CMD:avehiculo(playerid, params[]) {
	new
		text[128],
		string[128],
		returnid,
		returnid2;

	if(PlayerInfo[playerid][pAdmin] < 20) return 1;

	if(sscanf(params, "s[128]I(-1)I(-1)", text, returnid, returnid2)) {
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/av)ehiculo [comando]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "[Comandos]: /avinfo - estacionar - tipo [tipo] - modelo [IDmodelo] - color [color1] [color2] - faccion [idfaccion] - empleo [idempleo]");
		SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "traer [idvehiculo] - motor - nitro - motorgral [1=on - 0=off]");
       	SendClientMessage(playerid,	COLOR_LIGHTYELLOW2,	"{878EE7}[INFO]:{C8C8C8} para 'eliminar' un vehículo utiliza '/av tipo 0', si éste estaba asociado a un personaje");
        SendClientMessage(playerid,	COLOR_LIGHTYELLOW2,	"{C8C8C8}el vehículo será eliminado de su cuenta.");
	} else if(strcmp(text,"estacionar",true) == 0) {
		new
			vehicleid = GetPlayerVehicleID(playerid),
			Float:x,
			Float:y,
			Float:z,
			Float:a;

	    if(!IsPlayerInAnyVehicle(playerid)) {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
			return 1;
		}
		GetVehiclePos(vehicleid, x, y, z);
		GetVehicleZAngle(vehicleid, a);
		VehicleInfo[vehicleid][VehPosX] = x;
		VehicleInfo[vehicleid][VehPosY] = y;
		VehicleInfo[vehicleid][VehPosZ] = z;
		VehicleInfo[vehicleid][VehAngle] = a;
		SaveVehicle(vehicleid);
		
		DestroyVehicle(vehicleid);
	    CreateVehicle(VehicleInfo[vehicleid][VehModel], VehicleInfo[vehicleid][VehPosX], VehicleInfo[vehicleid][VehPosY], VehicleInfo[vehicleid][VehPosZ], VehicleInfo[vehicleid][VehAngle], VehicleInfo[vehicleid][VehColor1], VehicleInfo[vehicleid][VehColor2], -1);
    	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][VehPlate]);
		SetVehicleToRespawn(vehicleid);
		UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][VehDamage1], VehicleInfo[vehicleid][VehDamage2], VehicleInfo[vehicleid][VehDamage3], VehicleInfo[vehicleid][VehDamage4]);
		SetVehicleHealth(vehicleid, VehicleInfo[vehicleid][VehHP]);
		PutPlayerInVehicle(playerid, vehicleid, 0);
		
	    format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} vehículo %d estacionado correctamente.", vehicleid);
	    SendClientMessage(playerid,COLOR_ADMINCMD, string);
	} else if(strcmp(text,"tipo",true) == 0) {
		if(IsPlayerInAnyVehicle(playerid)) {
			new
				vehicleid = GetPlayerVehicleID(playerid),
				pconnected = 0;

			if(returnid == -1) return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/av)ehiculo tipo [idtipo]");
			if(VehicleInfo[vehicleid][VehType] == VEH_RENT) {
				for(new i = 1; i < MAX_RENTCAR; i++) {
				    if(RentCar[i][vrID] == vehicleid){
                    	RentCar[i][vrID] = 0;
                    	RentCar[i][vrOwnerSQLID] = -1;
                    	RentCar[i][vrTime] = 0;
                    	RentCar[i][vrRented] = 0;
                    }
				}
			} else if(VehicleInfo[vehicleid][VehType] == VEH_OWNED) {
 			    foreach(new i : Player)	{
					if(PlayerInfo[i][pVeh1] == vehicleid) {
					    PlayerInfo[i][pVeh1] = 0;
					    pconnected = 1;
					} else if(PlayerInfo[i][pVeh2] == vehicleid) {
					    PlayerInfo[i][pVeh2] = 0;
					    pconnected = 1;
					}
				}
				if(pconnected == 0)	{
				    if(VehicleInfo[vehicleid][VehOwnerSlot] == 1) {
				        format(string, sizeof(string), "UPDATE accounts SET pVeh1 = 0 WHERE Id = %d AND pVeh1 = %d", VehicleInfo[vehicleid][VehOwnerSQLID], vehicleid);
						mysql_function_query(dbHandle, string, false, "", "");
				    } else if(VehicleInfo[vehicleid][VehOwnerSlot] == 2) {
				        format(string, sizeof(string), "UPDATE accounts SET pVeh2 = 0 WHERE Id = %d AND pVeh2 = %d", VehicleInfo[vehicleid][VehOwnerSQLID], vehicleid);
						mysql_function_query(dbHandle, string, false, "", "");
					}
				}
			}
			
			/*if(returnid == VEH_RENT) {
				new available = -1;
				for(new i = 1; i < MAX_RENTCAR; i++) {
				    if(RentCar[i][vrID] < 1) {
                    	RentCar[i][vrID] = vehicleid;
                    	RentCar[i][vrOwnerSQLID] = -1;
                    	RentCar[i][vrTime] = 0;
                    	RentCar[i][vrRented] = 0;
                    	available = i;
                    }
				}
				if(available == -1)
				    return SendClientMessage(playerid, COLOR_YELLOW2, "No se pueden poner más vehículos de renta.");
			}*/
			if(returnid == VEH_NONE) {
				resetVehicle(vehicleid);
			}

            VehicleInfo[vehicleid][VehType] = returnid;
		    format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el tipo del vehículo %d ha sido ajustado a %d.", vehicleid, returnid);
		    SendClientMessage(playerid,COLOR_ADMINCMD, string);
    		SaveVehicle(vehicleid);
    		SetVehicleToRespawn(vehicleid);
			if(returnid != VEH_NONE && returnid != VEH_CREATED) PutPlayerInVehicle(playerid, vehicleid, 0);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text, "modelo", true) == 0) {
		new
			vehicleid = GetPlayerVehicleID(playerid),
			Float:cx,
			Float:cy,
			Float:cz,
			Float:angle;

	    if(returnid == -1) return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} (/aveh)iculo modelo [idmodelo]");

		if(IsPlayerInAnyVehicle(playerid)) {
			if(returnid > 399 && returnid < 612) {
				VehicleInfo[vehicleid][VehModel] = returnid;
			    format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el modelo del vehículo %d ha sido cambiado a %d.", vehicleid, returnid);
			    SendClientMessage(playerid,COLOR_ADMINCMD, string);
				GetVehiclePos(vehicleid,cx,cy,cz);
				GetVehicleZAngle(vehicleid, angle);
				DestroyVehicle(vehicleid);
				CreateVehicle(VehicleInfo[vehicleid][VehModel],VehicleInfo[vehicleid][VehPosX],VehicleInfo[vehicleid][VehPosY],VehicleInfo[vehicleid][VehPosZ],VehicleInfo[vehicleid][VehAngle],VehicleInfo[vehicleid][VehColor1],VehicleInfo[vehicleid][VehColor2], -1);
				PutPlayerInVehicle(playerid,vehicleid,0);
				SetVehiclePos(vehicleid, cx, cy, cz);
 				SetVehicleZAngle(vehicleid, angle);
			    SaveVehicle(vehicleid);
		    } else {
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de model incorrecta, debe estar en el rango de 400-611.");
			}
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text,"color",true) == 0) {
	    new
			vehicleid = GetPlayerVehicleID(playerid),
			Float:cx,
			Float:cy,
			Float:cz,
			Float:angle;

		if(IsPlayerInAnyVehicle(playerid)) {
			if(returnid < 0 || returnid > 255 || returnid2 < 0 || returnid2 > 255) { SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} colores válidos: 0-255."); return 1; }

			VehicleInfo[vehicleid][VehColor1] = returnid;
			VehicleInfo[vehicleid][VehColor2] = returnid2;
   			format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el color del vehículo %d ha sido ajustado a %d-%d.", vehicleid, returnid, returnid2);
		    SendClientMessage(playerid,COLOR_ADMINCMD, string);
			GetVehiclePos(vehicleid,cx,cy,cz);
			GetVehicleZAngle(vehicleid, angle);
			DestroyVehicle(vehicleid);
			CreateVehicle(VehicleInfo[vehicleid][VehModel],VehicleInfo[vehicleid][VehPosX],VehicleInfo[vehicleid][VehPosY],VehicleInfo[vehicleid][VehPosZ],VehicleInfo[vehicleid][VehAngle],VehicleInfo[vehicleid][VehColor1],VehicleInfo[vehicleid][VehColor2], -1);
			PutPlayerInVehicle(playerid,vehicleid,0);
			SetVehiclePos(vehicleid, cx, cy, cz);
			SetVehicleZAngle(vehicleid, angle);
		    SaveVehicle(vehicleid);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text,"faccion",true) == 0) {
	    new
			vehicleid = GetPlayerVehicleID(playerid);

		if(IsPlayerInAnyVehicle(playerid)) {
			if(returnid < 11 || 255) {
				VehicleInfo[vehicleid][VehFaction] = returnid;
			    format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} la facción del vehículo %d ha sido ajustada a %d.", vehicleid, returnid);
			    SendClientMessage(playerid,COLOR_ADMINCMD, string);
			    SaveVehicle(vehicleid);
		    } else {
				SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{878EE7}[INFO]:{C8C8C8} ID de facción inválida.");
			}
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text,"empleo",true) == 0) {
	    new
			vehicleid = GetPlayerVehicleID(playerid);

		if(IsPlayerInAnyVehicle(playerid)) {
			VehicleInfo[vehicleid][VehJob] = returnid;
		    format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} el empleo del vehículo %d ha sido ajustado a %d.", vehicleid, returnid);
		    SendClientMessage(playerid,COLOR_ADMINCMD, string);
		    SaveVehicle(vehicleid);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text,"nitro",true) == 0) {
	    new
			vehicleid = GetPlayerVehicleID(playerid);

		if(IsPlayerInAnyVehicle(playerid)) {
        	AddVehicleComponent(vehicleid, 1010);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
	} else if(strcmp(text,"entrar",true) == 0) {
	    if(returnid != INVALID_VEHICLE_ID && VehicleInfo[returnid][VehType] != 0) {
			PutPlayerInVehicle(playerid, returnid, 0);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
		}
	} else if(strcmp(text,"traer",true) == 0) {
		new
			Float:x,
			Float:y,
			Float:z,
			Float:angle;

	    if(returnid != INVALID_VEHICLE_ID) {
	        GetPlayerPos(playerid, x,y,z);
			GetPlayerFacingAngle(playerid, angle);
	        SetVehiclePos(returnid, x, y + 3.5, z);
	        SetVehicleZAngle(returnid, angle);
			//PutPlayerInVehicle(playerid,id,0);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
		}
	} else if(strcmp(text,"respawn",true) == 0) {
		if(returnid != INVALID_VEHICLE_ID && VehicleInfo[returnid][VehType] != 0) {
			SetVehicleToRespawn(returnid);
		} else {
			SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{FF4600}[Error]:{C8C8C8} ID de vehículo inválida.");
		}
	} else if(strcmp(text,"respawnall",true) == 0) {
		for(new i = 1;i<MAX_VEH;i++) {
		    if(IsVehicleOccupied(i) == 0) {
		        SetVehicleToRespawn(i);
		    }
		}
		format(string, sizeof(string), "{878EE7}[INFO]:{C8C8C8} todos los vehículos desocupados han sido respawneados por %s.", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_ADMINCMD, string);
	} else if(strcmp(text,"motor",true) == 0) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new vehicleid = GetPlayerVehicleID(playerid);
			GetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][VehEngine], VehicleInfo[vehicleid][VehLights], VehicleInfo[vehicleid][VehAlarm],vlocked, VehicleInfo[vehicleid][VehBonnet], VehicleInfo[vehicleid][VehBoot], VehicleInfo[vehicleid][VehObjective]);
		    if(VehicleInfo[vehicleid][VehEngine] != 1) {
				SetEngine(vehicleid, 1);
			} else {
				SetEngine(vehicleid, 0);
			}
		} else {
		    SendClientMessage(playerid,COLOR_LIGHTYELLOW2,"{FF4600}[Error]:{C8C8C8} debes estar en un vehículo para utilizar este comando.");
		}
 	}
	return 1;
}
