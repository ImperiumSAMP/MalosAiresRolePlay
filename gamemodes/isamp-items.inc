#if defined _isamp_items_included
	#endinput
#endif
#define _isamp_items_included

//==============================ITEM SYSTEM=====================================

#define ITEM_NONE               -1
#define ITEM_WEAPON             1
#define ITEM_OTHER              2
#define ITEM_STORABLE           3

#define ITEM_ID_CAMARA		    43
#define ITEM_ID_MATERIALES      47
#define ITEM_ID_BIDON		    48
#define ITEM_ID_MATERIAPRIMA    49
#define ITEM_ID_PRODUCTOS	    50
#define ITEM_ID_DINERO    		51
#define ITEM_ID_SANDWICH	    52
#define ITEM_ID_ALFAJOR		    53
#define ITEM_ID_AGUAMINERAL     54
#define ITEM_ID_MALETIN		    55
#define ITEM_ID_CASCOCOMUN      56
#define ITEM_ID_CASCOMOTOCROSS  57
#define ITEM_ID_CASCOROJO       58
#define ITEM_ID_CASCOBLANCO     59
#define ITEM_ID_CASCOROSA       60

//==============================DATA STORAGE====================================

enum ItemInfo {
	Name[40],
	ParamName[20],
	Type,
	BasePrice,
	bool:InvAvailable
};

static const ServerItems[][ItemInfo] = {

/*0*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*1*/	{"Manopla", "Cantidad", ITEM_WEAPON, 190, true},
/*2*/	{"Palo de Golf", "Cantidad", ITEM_WEAPON, 220, false},
/*3*/	{"Macana", "Cantidad", ITEM_WEAPON, 300, true},
/*4*/	{"Navaja", "Cantidad", ITEM_WEAPON, 250, true},
/*5*/	{"Bate", "Cantidad", ITEM_WEAPON, 250, false},
/*6*/	{"Pala", "Cantidad", ITEM_WEAPON, 300, false},
/*7*/	{"Palo de pool", "Cantidad", ITEM_WEAPON, 300, false},
/*8*/	{"Katana", "Cantidad", ITEM_WEAPON, 6000, false},
/*9*/	{"Motosierra", "Cantidad", ITEM_WEAPON, 15000, false},
/*10*/	{"Consolador doble punta", "Cantidad", ITEM_WEAPON, 150, true},
/*11*/	{"Consolador", "Cantidad", ITEM_WEAPON, 120, true},
/*12*/	{"Vibrador", "Cantidad", ITEM_WEAPON, 140, true},
/*13*/	{"Vibrador plateado", "Cantidad", ITEM_WEAPON, 120, true},
/*14*/	{"Flores", "Cantidad", ITEM_WEAPON, 50, true},
/*15*/	{"Baston", "Cantidad", ITEM_WEAPON, 200, true},
/*16*/	{"Granada", "Cantidad", ITEM_WEAPON, 1000, true},
/*17*/	{"Granada de gas", "Cantidad", ITEM_WEAPON, 200, true},
/*18*/	{"Bomba molotov", "Cantidad", ITEM_WEAPON, 450, true},
/*19*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*20*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*21*/	{"NULO", "NULO", ITEM_NONE, 0, false},
/*22*/	{"Pistola 9mm", "Munición", ITEM_WEAPON, 35, true},
/*23*/	{"Pistola 9mm con silenciador", "Munición", ITEM_WEAPON, 75, true},
/*24*/	{"Pistola Desert Eagle", "Munición", ITEM_WEAPON, 150, true},
/*25*/	{"Escopeta", "Munición", ITEM_WEAPON, 70, false},
/*26*/	{"Escopeta recortada", "Munición", ITEM_WEAPON, 120, false},
/*27*/	{"Escopeta de combate", "Munición", ITEM_WEAPON, 200, false},
/*28*/	{"Uzi", "Munición", ITEM_WEAPON, 50, true},
/*29*/	{"Subfusil MP-5", "Munición", ITEM_WEAPON, 95, false},
/*30*/	{"Fusil AK-47", "Munición", ITEM_WEAPON, 170, false},
/*31*/	{"Fusil M4", "Munición", ITEM_WEAPON, 170, false},
/*32*/	{"Pistola semiautomatica TEC-9", "Munición", ITEM_WEAPON, 50, true},
/*33*/	{"Rifle de caza", "Munición", ITEM_WEAPON, 60, false},
/*34*/	{"Rifle de francotirador", "Munición", ITEM_WEAPON, 550, false},
/*35*/	{"RPG-7", "Munición", ITEM_WEAPON, 25000, false},
/*36*/	{"Lanzamisiles", "Munición", ITEM_WEAPON, 20000, false},
/*37*/	{"Lanzallamas", "Munición", ITEM_WEAPON, 15000, false},
/*38*/	{"Minigun", "Munición", ITEM_WEAPON, 0, false},
/*39*/	{"Carga C4", "Cantidad", ITEM_WEAPON, 15000, false},
/*40*/	{"Detonador", "Cantidad", ITEM_WEAPON, 1000, true},
/*41*/	{"Aerosol", "Contenido", ITEM_WEAPON, 50, true},
/*42*/	{"Matafuegos", "Contenido", ITEM_WEAPON, 250, false},
/*43*/	{"Cámara fotográfica", "Fotos", ITEM_WEAPON, 20, true},
/*44*/	{"Visión nocturna", "Cantidad", ITEM_WEAPON, 0, false},
/*45*/	{"Visión térmica", "Cantidad", ITEM_WEAPON, 0, false},
/*46*/	{"Paracaídas", "Cantidad", ITEM_WEAPON, 0, false},
/*47*/	{"Caja de materiales", "Cantidad", ITEM_OTHER, 45, false},
/*48*/	{"Bidón de combustible", "Contenido", ITEM_OTHER, 120, false},
/*49*/	{"Bolsa de materia prima", "Cantidad", ITEM_OTHER, 10, false},
/*50*/	{"Productos", "Cantidad", ITEM_OTHER, 50, false},
/*51*/	{"Dinero", "Cantidad", ITEM_OTHER, 1, false},
/*52*/	{"Sandwich", "Cantidad", ITEM_OTHER, 60, true},
/*53*/	{"Alfajor", "Cantidad", ITEM_OTHER, 30, true},
/*54*/	{"Agua mineral", "Cantidad", ITEM_OTHER, 40, true},
/*55*/	{"Maletín", "Dinero", ITEM_OTHER, 500, false},
/*56*/  {"Casco Común", "Cantidad", ITEM_OTHER, 650, false}, //objectid 18645
/*57*/  {"Casco de Motocross", "Cantidad", ITEM_OTHER, 1150, false}, //objectid 18976
/*58*/  {"Casco Rojo", "Cantidad", ITEM_OTHER, 560, false}, //objectid 18977
/*59*/  {"Casco Blanco", "Cantidad", ITEM_OTHER, 560, false}, //objectid 18978
/*60*/  {"Casco Rosa", "Cantidad", ITEM_OTHER, 700, false} //objectid 18979

};

//==============================FUNCIONES=======================================

forward bool:HasItemInvPermission(itemid); // Devuelve verdadero si el objeto entra en un inventario (si esta permitido). Falso si no lo está.
forward GetItemType(itemid); // Devuelve el tipo del item.
forward GetItemName(itemid); // Devuelve un string con el nombre del item.
forward GetItemParamName(itemid); // Devuelve un string con el nombre del parametro que le sigue al nombre del item.
forward GetItemPrice(itemid); // Devuelve el precio base unitario del item.
forward GiveItemHandToHand(playerid, targetid, itemid); // Si el item es visible, lo borra de la mano del jugador X y lo crea para la mano del jugador Y.
forward LoadHandItem(playerid); // Crea el objeto visible que el usuario tenga en el modelo logico de la mano.
forward LoadVisibleItemsForPlayer(playerid); // Crea los objetos visibles y que estén en el inventario/equipados (no en mano).
forward DeleteItemForPlayer(playerid, itemid); // Borra el item visible que no está en la mano del jugador seleccionado.
forward DeleteItemFromHand(playerid); // Borra visualmente el objeto que tenga en la mano (por default index 6)

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock bool:HasItemInvPermission(itemid)
{
	return ServerItems[itemid][InvAvailable];
}

stock GetItemType(itemid)
{
	return ServerItems[itemid][Type];
}

stock GetItemName(itemid)
{
	new str[40];
	format(str, sizeof(str), "%s" , ServerItems[itemid][Name]);
	return str;
}

stock GetItemParamName(itemid)
{
    new str[20];
    format(str, sizeof(str), "%s" , ServerItems[itemid][ParamName]);
	return str;
}

stock GetItemPrice(itemid)
{
	return ServerItems[itemid][BasePrice];
}

stock GiveItemHandToHand(playerid, targetid, itemid)
{
	switch(itemid)
	{
		case ITEM_ID_CASCOCOMUN: GiveHelmetHandToHand(playerid, targetid, ITEM_ID_CASCOCOMUN);
		case ITEM_ID_CASCOMOTOCROSS: GiveHelmetHandToHand(playerid, targetid, ITEM_ID_CASCOMOTOCROSS);
		case ITEM_ID_CASCOROJO: GiveHelmetHandToHand(playerid, targetid, ITEM_ID_CASCOROJO);
		case ITEM_ID_CASCOBLANCO: GiveHelmetHandToHand(playerid, targetid, ITEM_ID_CASCOBLANCO);
		case ITEM_ID_CASCOROSA: GiveHelmetHandToHand(playerid, targetid, ITEM_ID_CASCOROSA);
		case ITEM_ID_MALETIN: GiveBriefCaseHandToHand(playerid, targetid);
		case ITEM_ID_BIDON: GiveGasCanHandToHand(playerid, targetid);
	}
	return 1;
}

stock LoadHandItem(playerid)
{
	switch(GetHandItem(playerid))
	{
		case ITEM_ID_CASCOCOMUN: HelmetToHand(playerid, ITEM_ID_CASCOCOMUN);
		case ITEM_ID_CASCOMOTOCROSS: HelmetToHand(playerid, ITEM_ID_CASCOMOTOCROSS);
		case ITEM_ID_CASCOROJO: HelmetToHand(playerid, ITEM_ID_CASCOROJO);
		case ITEM_ID_CASCOBLANCO: HelmetToHand(playerid, ITEM_ID_CASCOBLANCO);
		case ITEM_ID_CASCOROSA: HelmetToHand(playerid, ITEM_ID_CASCOROSA);
		case ITEM_ID_MALETIN: BriefCaseToHand(playerid);
		case ITEM_ID_BIDON: GasCanToHand(playerid);
	}
	return 1;
}

stock DeleteItemFromHand(playerid)
{
	RemovePlayerAttachedObject(playerid, 6);
	return 1;
}

stock LoadVisibleItemsForPlayer(playerid)
{
	HelmetToHead(playerid, ITEM_ID_CASCOCOMUN);
    HelmetToHead(playerid, ITEM_ID_CASCOMOTOCROSS);
    HelmetToHead(playerid, ITEM_ID_CASCOROJO);
    HelmetToHead(playerid, ITEM_ID_CASCOBLANCO);
    HelmetToHead(playerid, ITEM_ID_CASCOROSA);
	return 1;
}

stock DeleteItemForPlayer(playerid, itemid)
{
    switch(itemid)
    {
		case ITEM_ID_CASCOCOMUN: DeleteItemFromHead(playerid);
		case ITEM_ID_CASCOMOTOCROSS: DeleteItemFromHead(playerid);
		case ITEM_ID_CASCOROJO: DeleteItemFromHead(playerid);
		case ITEM_ID_CASCOBLANCO: DeleteItemFromHead(playerid);
		case ITEM_ID_CASCOROSA: DeleteItemFromHead(playerid);
		default: return 1;
	}
	return 1;
}

//===============================GASCAN=========================================

stock GasCanToHand(playerid)
{
    SetPlayerAttachedObject(playerid, 6, 1650, 5, 0.301999, 0.082999, -0.012000, 0.000000, -90.599975, -0.999999, 1.000000, 1.000000, 1.000000);
    return 1;
}

stock GiveGasCanHandToHand(playerid, targetid)
{
	DeleteItemFromHand(playerid);
	GasCanToHand(targetid);
	return 1;
}
