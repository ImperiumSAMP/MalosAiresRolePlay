#if defined _marp_lifts_included
	#endinput
#endif
#define _marp_lifts_included

#define DOOR_RIGHT      		0
#define DOOR_LEFT       		1

#define MAX_LIFTS         		4
#define MAX_LIFT_FLOORS    		20

#define LIFT_STATE_IDLE    	 	1
#define LIFT_STATE_MOVING   	2
#define LIFT_STATE_WAITING    	3

#define DLG_LIFT                10500

enum LiftInfo {
	eLiftObjectID,
	eRDoorObjectID,
	eLDoorObjectID,

	eTotalFloors,
	eCurrentFloor,
	eState,

	Float:eLX,
	Float:eLY,
	Float:eLZ,
    Float:eLRZ,

    Float:eFDX,
    Float:eFDY,

    Float:eRODOFFX,
    Float:eRODOFFY,

    Float:eOSX,
    Float:eOSY,
    Float:eOSZ,

    Float:eOLX,
    Float:eOLY,

    Float:eILX,
    Float:eILY,
    Float:eILZ
};

new Lift[MAX_LIFTS][LiftInfo] = {
								//  Objects IDS     Tot Curr State		Base ascensor X, Y, Z, RZ						Floor Doors	X, Y      			Open Right OFF X, Y    	Outside Switch X, Y, Z                  Outside Label X, Y              Inside Label X, Y, Z
/*LS al lado de hospital ID 0*/	{0, 0, 0,		11, 0, 1, 			1181.60986, -1180.54895, 20.93880, 0.0, 			1181.32300, -1180.54895, 		0.0, -1.2601, 			1179.27429, -1183.02173, 20.58120,      1179.21130, -1183.02173,        1179.9489, -1182.4466, 20.5602},
/*Torre Bracone&Mercier ID 1*/	{0, 0, 0, 		7, 0, 1,			1470.77930, -1356.14099, 51.44730, 0.0, 			1470.66660, -1356.14099,		0.0, -1.2601,			1468.6266, -1353.9854, 51.0897,			1468.56360, -1353.98540,		1469.1183, -1358.0386, 51.0687},
/*LS frente a glenpark ID 2*/   {0, 0, 0,       20, 0, 1,           1786.67810, -1303.45947, 14.57099, -90.0,          	1786.67110, -1303.15950,        -1.1340, 0.0,           1784.1056, -1301.1211, 13.9158,         1784.1056, -1301.0371,          1784.8063, -1301.7916, 14.0705},
/*LS Beach - Rodeo ID 3*/       {0, 0, 0,       14, 0, 1,           287.942413, -1609.34106, 18.755348, 80.0,           287.942413, -1609.54410,        1.1970, -0.20696,       290.1046, -1612.0692, 18.2986,          290.0626, -1612.1532,           289.4880, -1611.2905, 18.2566}
};

new Float:Lift_FloorZOffsets[MAX_LIFTS][MAX_LIFT_FLOORS] = {
    {0.0, 13.65860, 18.8456, 24.0407, 29.2484, 34.4475, 39.6503, 44.8404, 50.0471, 55.2548, 60.4425},
    {0.0, 55.2872, 65.0797, 74.8722, 84.6647, 94.4572, 104.24971},
    {0.0, 8.5479, 13.99945, 19.45100, 24.90255, 30.35410, 35.80565, 41.25720, 46.70875, 52.16030, 57.61185, 63.06340, 68.51495, 73.96650, 79.41805, 84.86960, 90.32115, 95.77270, 101.22425, 106.67580},
    {0.0, 15.06972, 29.13073, 33.63073, 38.13073, 42.63073, 47.13073, 51.63073, 56.13073, 60.63073, 65.13073, 69.63073, 74.13073, 78.63073}
};

new Lift_FloorNames[MAX_LIFTS][MAX_LIFT_FLOORS][24] = {
	{"Garage", "Planta Baja", "1º Piso", "2º Piso", "3º Piso", "4º Piso", "5º Piso", "6º Piso", "7º Piso", "8º Piso", "9º Piso", "", "", "", "", "", "", "", "", ""},
	{"Planta Baja", "6º Piso", "7º Piso", "8º Piso", "9º Piso", "10º Piso", "11º Piso", "", "", "", "", "", "", "", "", "", "", "", "", ""},
	{"Planta Baja", "1º Piso", "2º Piso", "3º Piso", "4º Piso", "5º Piso", "6º Piso", "7º Piso", "8º Piso", "9º Piso", "10º Piso", "11º Piso", "12º Piso", "13º Piso", "14º Piso", "15º Piso", "16º Piso", "17º Piso", "18º Piso", "19º Piso"},
    {"Garage", "Planta Baja", "1º Piso", "2º Piso", "3º Piso", "4º Piso", "5º Piso", "6º Piso", "7º Piso", "8º Piso", "9º Piso", "10º Piso", "11º Piso", "12º Piso", "", "", "", "", "", ""}
};

new Lift_FloorDoors[MAX_LIFTS][MAX_LIFT_FLOORS][2];

new Text3D:Lift_InsideLabel[MAX_LIFTS];

new Lift_PlayerRequested[MAX_PLAYERS];

Lift_CreateAll()
{
	for(new i = 0; i < MAX_LIFTS; i++)
		Lift_CreateObjects(i);
}

Lift_CreateObjects(liftid)
{
	// Ascensor
    Lift[liftid][eLiftObjectID] = CreateObject(18755, Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 0.0, 0.0, Lift[liftid][eLRZ]);

	// Puertas del ascensor abiertas
	Lift[liftid][eRDoorObjectID] = CreateObject(18756, Lift[liftid][eLX] + Lift[liftid][eRODOFFX], Lift[liftid][eLY] + Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 0.0, 0.0, Lift[liftid][eLRZ]);
    Lift[liftid][eLDoorObjectID] = CreateObject(18757, Lift[liftid][eLX] - Lift[liftid][eRODOFFX], Lift[liftid][eLY] - Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 0.0, 0.0, Lift[liftid][eLRZ]);
	// Inside label para el interior del ascensor
    Lift_InsideLabel[liftid] = CreateDynamic3DTextLabel("Presiona 'Y' para\nusar el ascensor", COLOR_YELLOW2, Lift[liftid][eILX], Lift[liftid][eILY], Lift[liftid][eILZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);

	// Varios
	for(new i = 0; i < Lift[liftid][eTotalFloors]; i++)
	{
 		// Puertas de cada piso
	    if(i == Lift[liftid][eCurrentFloor]) // Si es posición inicial, las creamos abiertas
	    {
			Lift_FloorDoors[liftid][i][DOOR_RIGHT] = CreateObject(18756, Lift[liftid][eFDX] + Lift[liftid][eRODOFFX], Lift[liftid][eFDY] + Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][i], 0.0, 0.0, Lift[liftid][eLRZ]);
        	Lift_FloorDoors[liftid][i][DOOR_LEFT] = CreateObject(18757, Lift[liftid][eFDX] - Lift[liftid][eRODOFFX], Lift[liftid][eFDY] - Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][i], 0.0, 0.0, Lift[liftid][eLRZ]);
	    }
	    else
	    {
		    Lift_FloorDoors[liftid][i][DOOR_RIGHT] = CreateObject(18756, Lift[liftid][eFDX], Lift[liftid][eFDY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][i], 0.0, 0.0, Lift[liftid][eLRZ]);
	        Lift_FloorDoors[liftid][i][DOOR_LEFT] = CreateObject(18757, Lift[liftid][eFDX], Lift[liftid][eFDY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][i], 0.0, 0.0, Lift[liftid][eLRZ]);
		}
		// Interruptor de cada piso
		CreateDynamicObject(19826, Lift[liftid][eOSX], Lift[liftid][eOSY], Lift[liftid][eOSZ] + Lift_FloorZOffsets[liftid][i], 0.0, 0.0, Lift[liftid][eLRZ] - 90.0);
		// Outside label de cada piso
		CreateDynamic3DTextLabel("Presiona 'Y' para\nllamar al ascensor", COLOR_YELLOW2, Lift[liftid][eOLX], Lift[liftid][eOLY], Lift[liftid][eOSZ] + Lift_FloorZOffsets[liftid][i], 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	}
}

forward Lift_SetState(liftid, liftstate);
public Lift_SetState(liftid, liftstate)
{
    Lift[liftid][eState] = liftstate;
    return 1;
}

forward Lift_MoveToFloor(liftid, floor);
public Lift_MoveToFloor(liftid, floor)
{
    if(liftid >= 0 && liftid < MAX_LIFTS && floor >= 0 && floor < Lift[liftid][eTotalFloors])
	{
	    // Borramos la inside label
	    DestroyDynamic3DTextLabel(Lift_InsideLabel[liftid]);
	    // Movemos el ascensor
		MoveObject(Lift[liftid][eLiftObjectID], Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 3.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		// Movemos las puertas del ascensor
		MoveObject(Lift[liftid][eRDoorObjectID], Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 3.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		MoveObject(Lift[liftid][eLDoorObjectID], Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 3.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		Lift[liftid][eCurrentFloor] = floor;
		Lift[liftid][eState] = LIFT_STATE_MOVING;
		return 1;
	}
	return 0;
}

Lift_OpenLiftDoors(liftid)
{
	if(liftid >= 0 && liftid < MAX_LIFTS)
    {
        if(Lift[liftid][eState] != LIFT_STATE_MOVING)
        {
			MoveObject(Lift[liftid][eRDoorObjectID], Lift[liftid][eLX] + Lift[liftid][eRODOFFX], Lift[liftid][eLY] + Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
			MoveObject(Lift[liftid][eLDoorObjectID], Lift[liftid][eLX] - Lift[liftid][eRODOFFX], Lift[liftid][eLY] - Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
            return 1;
		}
	}
	return 0;
}

Lift_CloseLiftDoors(liftid)
{
	if(liftid >= 0 && liftid < MAX_LIFTS)
    {
		MoveObject(Lift[liftid][eRDoorObjectID], Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		MoveObject(Lift[liftid][eLDoorObjectID], Lift[liftid][eLX], Lift[liftid][eLY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][Lift[liftid][eCurrentFloor]], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		return 1;
	}
	return 0;
}

Lift_OpenFloorDoors(liftid, floor)
{
	if(liftid >= 0 && liftid < MAX_LIFTS && floor >= 0 && floor < Lift[liftid][eTotalFloors])
	{
	    MoveObject(Lift_FloorDoors[liftid][floor][DOOR_RIGHT], Lift[liftid][eFDX] + Lift[liftid][eRODOFFX], Lift[liftid][eFDY] + Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
	    MoveObject(Lift_FloorDoors[liftid][floor][DOOR_LEFT], Lift[liftid][eFDX] - Lift[liftid][eRODOFFX], Lift[liftid][eFDY] - Lift[liftid][eRODOFFY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		return 1;
	}
	return 0;
}

Lift_CloseFloorDoors(liftid, floor)
{
	if(liftid >= 0 && liftid < MAX_LIFTS && floor >= 0 && floor < Lift[liftid][eTotalFloors])
	{
	    MoveObject(Lift_FloorDoors[liftid][floor][DOOR_RIGHT], Lift[liftid][eFDX], Lift[liftid][eFDY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
	    MoveObject(Lift_FloorDoors[liftid][floor][DOOR_LEFT], Lift[liftid][eFDX], Lift[liftid][eFDY], Lift[liftid][eLZ] + Lift_FloorZOffsets[liftid][floor], 1.0, 0.0, 0.0, Lift[liftid][eLRZ]);
		return 1;
	}
	return 0;
}

Lift_OnDialogResponse(playerid, response, listitem)
{
	if(response)
	    return 1;
	if(!Lift_PlayerRequested[playerid])
	    return 1;
	if(Lift[Lift_PlayerRequested[playerid]][eCurrentFloor] == listitem)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "El ascensor se encuentra actualmente en ese piso o en viaje hacia el mismo.");
	if(Lift[Lift_PlayerRequested[playerid]][eState] != LIFT_STATE_IDLE)
		return SendClientMessage(playerid, COLOR_YELLOW2, "El ascensor se encuentra actualmente en uso o en espera, aguarda un momento.");

	Lift_CloseFloorDoors(Lift_PlayerRequested[playerid], Lift[Lift_PlayerRequested[playerid]][eCurrentFloor]);
	Lift_CloseLiftDoors(Lift_PlayerRequested[playerid]);
	Lift[Lift_PlayerRequested[playerid]][eState] = LIFT_STATE_MOVING;
	Lift[Lift_PlayerRequested[playerid]][eCurrentFloor] = listitem;
	SetTimerEx("Lift_MoveToFloor", 2000, false, "ii", Lift_PlayerRequested[playerid], listitem);
	new string[128];
	format(string, 128, "Has seleccionado ir a '%s'.", Lift_FloorNames[Lift_PlayerRequested[playerid]][listitem]);
    SendClientMessage(playerid, COLOR_WHITE, string);
    Lift_PlayerRequested[playerid] = 0;
	return 1;
}

Lift_OnPlayerPressY(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid))
    {
        for(new i = 0; i < MAX_LIFTS; i++)
        {
            for(new f = 0; f < Lift[i][eTotalFloors]; f++)
            {
                if(IsPlayerInRangeOfPoint(playerid, 0.75, Lift[i][eILX], Lift[i][eILY], Lift[i][eILZ] + Lift_FloorZOffsets[i][f]))
                {
                    new string[256];
                    for(new n = 0; n < Lift[i][eTotalFloors]; n++)
                    	format(string, sizeof(string), "%s\n%s", string, Lift_FloorNames[i][n]);
                    ShowPlayerDialog(playerid, DLG_LIFT, DIALOG_STYLE_LIST, "Selecciona el piso que deseas:", string ,"Ir", "Cancelar");
					Lift_PlayerRequested[playerid] = i;
					return 1;
                }
                if(IsPlayerInRangeOfPoint(playerid, 0.75, Lift[i][eOLX], Lift[i][eOLY], Lift[i][eOSZ] + Lift_FloorZOffsets[i][f]))
                {
					if(Lift[i][eCurrentFloor] == f)
					    return SendClientMessage(playerid, COLOR_YELLOW2, "El ascensor se encuentra actualmente en tu piso o en viaje hacia tu piso.");
					if(Lift[i][eState] == LIFT_STATE_MOVING)
						return SendClientMessage(playerid, COLOR_YELLOW2, "El ascensor se encuentra actualmente en uso, espera un momento a que se desocupe.");

					Lift_CloseFloorDoors(i, Lift[i][eCurrentFloor]);
					Lift_CloseLiftDoors(i);
	    			Lift[i][eState] = LIFT_STATE_MOVING;
				    Lift[i][eCurrentFloor] = f;
				    SetTimerEx("Lift_MoveToFloor", 2000, false, "ii", i, f);
				    SendClientMessage(playerid, COLOR_WHITE, "Has llamado al ascensor, aguarda hasta que llegue a tu ubicación.");
					return 1;
				}
			}
		}
	}
	return 0;
}

Lift_OnObjectMoved(objectid)
{
	for(new i = 0; i < MAX_LIFTS; i++)
 	{
 	    if(objectid == Lift[i][eLiftObjectID])
 	    {
 	    	Lift_InsideLabel[i] = CreateDynamic3DTextLabel("Presiona 'Y' para\nusar el ascensor", COLOR_YELLOW2, Lift[i][eILX], Lift[i][eILY], Lift[i][eILZ] + Lift_FloorZOffsets[i][Lift[i][eCurrentFloor]], 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
			Lift[i][eState] = LIFT_STATE_WAITING;
   			SetTimerEx("Lift_SetState", 3000, false, "ii", i, LIFT_STATE_IDLE);
			Lift_OpenLiftDoors(i);
			Lift_OpenFloorDoors(i, Lift[i][eCurrentFloor]);
			return 1;
		}
	}
	return 0;
}
