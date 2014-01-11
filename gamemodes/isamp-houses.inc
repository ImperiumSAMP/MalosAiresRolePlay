#if defined _isamp_houses_included
	#endinput
#endif
#define _isamp_houses_included

#define MAX_HOUSES              200

enum HouseSystem {
	Description[128],
	Owner[MAX_PLAYER_NAME],
	Float:EntranceX,
	Float:EntranceY,
	Float:EntranceZ,
	EntranceInterior,
	Float:EntranceAngle,
	Float:ExitX,
	Float:ExitY,
	Float:ExitZ,
	ExitInterior,
	Float:ExitAngle,
	Owned,
	Rentable,
	RentCost,
	InsideWorld,
	HousePrice,
	Materials,
	Drugs,
	Money,
	Locked,
	hEntrancePickup,
	hExitPickup,
	Text3D:hEntranceLabel,
	Text3D:hExitLabel,
};

new House[MAX_HOUSES][HouseSystem];
