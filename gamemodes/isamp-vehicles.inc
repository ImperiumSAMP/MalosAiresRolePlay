#if defined _isamp_vehicles_included
	#endinput
#endif
#define _isamp_vehicles_included

/**
* Isamp Vehicles functions and defines
**/

//Defines
#define MAX_VEH                 1001
#define MAX_RENTCAR             20

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
	new model = GetVehicleModel(vehicleid);
	new price;
	if(model == 400) price = 70000;
	else if(model == 401) price = 31000;
	else if(model == 402) price = 500000;
	else if(model == 403) price = 455800;
	else if(model == 404) price = 28900;
	else if(model == 405) price = 68300;
	else if(model == 406) price = 853700;
	else if(model == 407) price = 311800;
	else if(model == 408) price = 280000;
	else if(model == 409) price = 406000;
	else if(model == 410) price = 26300;
	else if(model == 411) price = 990500;
	else if(model == 412) price = 69100;
	else if(model == 413) price = 105100;
	else if(model == 414) price = 98200;
	else if(model == 415) price = 750400;
	else if(model == 416) price = 550100;
	else if(model == 417) price = 910000;
	else if(model == 418) price = 80400;
	else if(model == 419) price = 58000;
	else if(model == 420) price = 86000;
	else if(model == 421) price = 75100;
	else if(model == 422) price = 35800;
	else if(model == 423) price = 98800;
	else if(model == 424) price = 65100;
	else if(model == 426) price = 80500;
	else if(model == 428) price = 400000;
	else if(model == 429) price = 595000;
	else if(model == 431) price = 592000;
	else if(model == 434) price = 384000;
	else if(model == 436) price = 39000;
	else if(model == 437) price = 599000;
	else if(model == 438) price = 79000;
	else if(model == 439) price = 65000;
	else if(model == 440) price = 95000;
	else if(model == 442) price = 105000;
	else if(model == 443) price = 428000;
	else if(model == 444) price = 675000;
	else if(model == 445) price = 61000;
	else if(model == 446) price = 775000;
	else if(model == 448) price = 25000;
	else if(model == 451) price = 1050000;
	else if(model == 452) price = 755000;
	else if(model == 453) price = 480000;
	else if(model == 454) price = 830000;
	else if(model == 455) price = 180000;
	else if(model == 456) price = 155000;
	else if(model == 457) price = 85000;
	else if(model == 458) price = 80000;
	else if(model == 459) price = 90000;
	else if(model == 460) price = 405000;
	else if(model == 461) price = 75000;
	else if(model == 462) price = 9000;
	else if(model == 463) price = 70000;
	else if(model == 466) price = 45000;
	else if(model == 467) price = 41000;
	else if(model == 468) price = 55000;
	else if(model == 469) price = 415000;
	else if(model == 470) price = 315000;
	else if(model == 471) price = 30000;
	else if(model == 473) price = 55000;
	else if(model == 474) price = 61000;
	else if(model == 475) price = 90000;
	else if(model == 477) price = 625000;
	else if(model == 478) price = 25000;
	else if(model == 479) price = 65000;
	else if(model == 480) price = 400000;
	else if(model == 481) price = 7000;
	else if(model == 482) price = 95000;
	else if(model == 483) price = 50000;
	else if(model == 484) price = 485000;
	else if(model == 485) price = 40000;
	else if(model == 486) price = 500000;
	else if(model == 487) price = 1200000;
	else if(model == 489) price = 105000;
	else if(model == 491) price = 55000;
	else if(model == 492) price = 60000;
	else if(model == 493) price = 770000;
	else if(model == 494) price = 1500000;
	else if(model == 495) price = 1300000;
	else if(model == 496) price = 100500;
	else if(model == 498) price = 80000;
	else if(model == 499) price = 70000;
	else if(model == 500) price = 60000;
	else if(model == 502) price = 1500000;
	else if(model == 503) price = 1500000;
	else if(model == 504) price = 200000;
	else if(model == 505) price = 105000;
	else if(model == 506) price = 700000;
	else if(model == 507) price = 80000;
	else if(model == 508) price = 180000;
	else if(model == 509) price = 2500;
	else if(model == 510) price = 10000;
	else if(model == 511) price = 415000;
	else if(model == 512) price = 400000;
	else if(model == 513) price = 420000;
	else if(model == 514) price = 440000;
	else if(model == 515) price = 485000;
	else if(model == 516) price = 47500;
	else if(model == 517) price = 60000;
	else if(model == 518) price = 45000;
	else if(model == 519) price = 1500000;
	else if(model == 521) price = 80000;
	else if(model == 522) price = 575000;
	else if(model == 524) price = 130000;
	else if(model == 525) price = 90000;
	else if(model == 526) price = 55000;
	else if(model == 527) price = 41000;
	else if(model == 529) price = 50000;
	else if(model == 530) price = 90000;
	else if(model == 531) price = 40000;
	else if(model == 532) price = 600000;
	else if(model == 533) price = 110000;
	else if(model == 534) price = 86000;
	else if(model == 535) price = 90000;
	else if(model == 536) price = 95000;
	else if(model == 539) price = 1550000;
	else if(model == 540) price = 60000;
	else if(model == 541) price = 850000;
	else if(model == 542) price = 40000;
	else if(model == 543) price = 30000;
	else if(model == 545) price = 325000;
	else if(model == 546) price = 65000;
	else if(model == 547) price = 50000;
	else if(model == 549) price = 50000;
	else if(model == 550) price = 85000;
	else if(model == 551) price = 110000;
	else if(model == 552) price = 230000;
	else if(model == 553) price = 1250000;
	else if(model == 554) price = 90000;
	else if(model == 555) price = 150000;
	else if(model == 556) price = 700000;
	else if(model == 557) price = 680000;
	else if(model == 558) price = 350000;
	else if(model == 559) price = 500000;
	else if(model == 560) price = 575000;
	else if(model == 561) price = 200000;
	else if(model == 562) price = 495000;
	else if(model == 563) price = 1350000;
	else if(model == 565) price = 375000;
	else if(model == 566) price = 90000;
	else if(model == 567) price = 85000;
	else if(model == 568) price = 40000;
	else if(model == 571) price = 25000;
	else if(model == 572) price = 15000;
	else if(model == 573) price = 250000;
	else if(model == 575) price = 85000;
	else if(model == 576) price = 68000;
	else if(model == 577) price = 3500000;
	else if(model == 578) price = 190000;
	else if(model == 579) price = 135000;
	else if(model == 580) price = 95000;
	else if(model == 581) price = 60000;
	else if(model == 583) price = 25000;
	else if(model == 585) price = 45000;
	else if(model == 586) price = 50000;
	else if(model == 587) price = 400000;
	else if(model == 588) price = 90000;
	else if(model == 589) price = 150000;
	else if(model == 592) price = 3500000;
	else if(model == 593) price = 525000;
	else if(model == 595) price = 725000;
	else if(model == 600) price = 40000;
    else if(model == 602) price = 350000;
	else if(model == 603) price = 500000;
	else if(model == 604) price = 22000;
	else if(model == 605) price = 19000;
	else if(model == 609) price = 85000;
	else return 0;
	price = price / 100 * priceperc;
	return price;
}
