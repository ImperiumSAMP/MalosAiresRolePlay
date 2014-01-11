#if defined _isamp_business_included
	#endinput
#endif
#define _isamp_business_included

#define MAX_BUSINESS	        100

// Mensajes del sistema.
#define BUSINESS_TYPES 			"1: Restaurant - 2: Sucursal telefónica - 3: 24-7 - 4: Ammunation - 5: Publicidad - 6: Tienda de ropa urbana - 7: Bar/Club - 8: Tienda de ropa fina"
#define BUSINESS_TYPES2 		" "


//Enums
enum BusinessSystem {
	bID,
	bName[128],
	bOwner[MAX_PLAYER_NAME],
	bOwnerSQLID,
	Float:bOutsideX,
	Float:bOutsideY,
	Float:bOutsideZ,
	Float:bOutsideAngle,
	Float:bInsideX,
	Float:bInsideY,
	Float:bInsideZ,
	Float:bInsideAngle,
	bOutsideInt,
	bInsideInt,
	bEnterable,
	bPrice,
	bEntranceFee,
	bTill,
	bLocked,
	bType,
	bProducts,
	// Datos temporales.
	bool:bLoaded,
	bool:bInsert,
	bool:bDelete,
	bInsideWorld,
	bOutsidePickup,
	bInsidePickup,
	Text3D:bOutsideLabel,
	Text3D:bInsideLabel,
}
new Business[MAX_BUSINESS][BusinessSystem];