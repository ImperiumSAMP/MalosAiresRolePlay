#if defined _isamp_items_included
	#endinput
#endif
#define _isamp_items_included

//==============================ITEM SYSTEM=====================================

//================================CONSTANTES====================================

#define ITEM_NONE               -1
#define ITEM_WEAPON             1
#define ITEM_OTHER              2
#define ITEM_TOY                3

#define ITEM_ID_CAMARA		    		43
#define ITEM_ID_MATERIALES      		47
#define ITEM_ID_BIDON		    		48
#define ITEM_ID_MATERIAPRIMA    		49
#define ITEM_ID_PRODUCTOS	    		50
#define ITEM_ID_DINERO          		51
#define ITEM_ID_SANDWICH	    		52
#define ITEM_ID_ALFAJOR		    		53
#define ITEM_ID_AGUAMINERAL     		54
#define ITEM_ID_MALETIN		    		55
#define ITEM_ID_CASCOCOMUN      		56
#define ITEM_ID_CASCOMOTOCROSS  		57
#define ITEM_ID_CASCOROJO       		58
#define ITEM_ID_CASCOBLANCO     		59
#define ITEM_ID_CASCOROSA       		60
#define ITEM_ID_REPUESTOAUTO    		61
#define ITEM_ID_BARRETA        			62
#define ITEM_ID_CASCO_OBRERO   			63
#define ITEM_ID_SOMBRERO_COWBOY_NEGRO	64
#define ITEM_ID_SOMBRERO_COWBOY_MARRON	65
#define ITEM_ID_SOMBRERO_COWBOY_BORDO	66
#define ITEM_ID_RELOJ_SWATCH			67
#define ITEM_ID_RELOJ_ROLEX				68
#define ITEM_ID_RELOJ_CASIO				69
#define ITEM_ID_RELOJ_SWISSARMY   		70
#define ITEM_ID_RELOJ_FESTINA   		71
#define ITEM_ID_SOMBRERO_ANTIGUO  		72
#define ITEM_ID_BIGOTE_FALSO1           73
#define ITEM_ID_BIGOTE_FALSO2   		74
#define ITEM_ID_SOMBRERO_BLANCO   		75
#define ITEM_ID_GORRO_ROJO    			76
#define ITEM_ID_GORRO_ESTAMPADO   		77
#define ITEM_ID_GORRO_NEGRO			  	78
#define ITEM_ID_GORRO_PLAYERO_NEGRO    	79
#define ITEM_ID_GORRO_PLAYERO_CUADROS 	80
#define ITEM_ID_GORRA_MILITAR			81
#define ITEM_ID_GORRA_GRIS_ESTAMPADA 	82
#define ITEM_ID_GORRA_BLANCA_ESTAMPADA 	83
#define ITEM_ID_ANTEOJO_DE_SOL			84
#define ITEM_ID_ANTEOJO_DEPORTIVO_NEGRO	85
#define ITEM_ID_ANTEOJO_DEPORTIVO_ROJO 	86
#define ITEM_ID_ANTEOJO_DEPORTIVO_AZUL 	87
#define ITEM_ID_ANTEOJO_RAYBAN_NEGRO	88
#define ITEM_ID_ANTEOJO_RAYBAN_AZUL 	89
#define ITEM_ID_ANTEOJO_RAYBAN_VIOLETA  90
#define ITEM_ID_ANTEOJO_RAYBAN_ROSA   	91
#define ITEM_ID_ANTEOJO_RAYBAN_ROJO     92
#define ITEM_ID_ANTEOJO_RAYBAN_NARANJA  93
#define ITEM_ID_ANTEOJO_RAYBAN_AMARILLO 94
#define ITEM_ID_ANTEOJO_RAYBAN_VERDE    95
#define ITEM_ID_GORRA_SIMPLE_NEGRA      96
#define ITEM_ID_GORRA_SIMPLE_AZUL       97
#define ITEM_ID_GORRA_SIMPLE_VERDE      98

#define BONE_ID_SPINE           1
#define BONE_ID_HEAD         	2
#define BONE_ID_LEFTHAND        5
#define BONE_ID_RIGHTHAND       6

#define INDEX_ID_HAND_LEFT      9
#define INDEX_ID_HAND_RIGHT     8
#define INDEX_ID_BACK           7
#define INDEX_ID_MASK        	6 

#define HAND_LEFT             	0
#define HAND_RIGHT              1

//==============================DATA STORAGE====================================

enum ItemInfo {
	Name[40],
	ParamName[20],
	Type,
	BasePrice,
	bool:InvAvailable,
	ObjectModel,
	Float:XPos, // Posicion para attachear en mano izquierda
	Float:YPos,
	Float:ZPos,
	Float:RxPos,
	Float:RyPos,
	Float:RzPos,
	AttachBone // Hueso donde se attachea si está equipado (no en la mano)
};

static const ServerItems[][ItemInfo] = {

/*0*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*1*/	{"Manopla", "Cantidad", ITEM_WEAPON, 40, true, 331, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*2*/	{"Palo de Golf", "Cantidad", ITEM_WEAPON, 60, false, 333, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*3*/	{"Macana", "Cantidad", ITEM_WEAPON, 300, true, 334, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*4*/	{"Navaja", "Cantidad", ITEM_WEAPON, 250, true, 335, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*5*/	{"Bate", "Cantidad", ITEM_WEAPON, 120, false, 336, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*6*/	{"Pala", "Cantidad", ITEM_WEAPON, 75, false, 337, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*7*/	{"Palo de pool", "Cantidad", ITEM_WEAPON, 60, false, 338, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*8*/	{"Katana", "Cantidad", ITEM_WEAPON, 6000, false, 339, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*9*/	{"Motosierra", "Cantidad", ITEM_WEAPON, 15000, false, 341, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*10*/	{"Consolador doble punta", "Cantidad", ITEM_WEAPON, 65, true, 321, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*11*/	{"Consolador", "Cantidad", ITEM_WEAPON, 50, true, 322, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*12*/	{"Vibrador", "Cantidad", ITEM_WEAPON, 70, true, 323, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*13*/	{"Vibrador plateado", "Cantidad", ITEM_WEAPON, 85, true, 324, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*14*/	{"Flores", "Cantidad", ITEM_WEAPON, 50, true, 325, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*15*/	{"Baston", "Cantidad", ITEM_WEAPON, 30, true, 326, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*16*/	{"Granada", "Cantidad", ITEM_WEAPON, 1000, true, 342, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*17*/	{"Granada de gas", "Cantidad", ITEM_WEAPON, 200, true, 343, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*18*/	{"Bomba molotov", "Cantidad", ITEM_WEAPON, 450, true, 344, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*19*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*20*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*21*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*22*/	{"Pistola 9mm", "Munición", ITEM_WEAPON, 35, true, 346, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*23*/	{"Pistola 9mm con silenciador", "Munición", ITEM_WEAPON, 75, true, 347, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*24*/	{"Pistola Desert Eagle", "Munición", ITEM_WEAPON, 150, true, 348, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*25*/	{"Escopeta", "Munición", ITEM_WEAPON, 70, false, 349, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*26*/	{"Escopeta recortada", "Munición", ITEM_WEAPON, 120, false, 350, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*27*/	{"Escopeta de combate", "Munición", ITEM_WEAPON, 200, false, 351, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*28*/	{"Uzi", "Munición", ITEM_WEAPON, 50, true, 352, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*29*/	{"Subfusil MP-5", "Munición", ITEM_WEAPON, 95, false, 353, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*30*/	{"Fusil AK-47", "Munición", ITEM_WEAPON, 170, false, 355, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*31*/	{"Fusil M4", "Munición", ITEM_WEAPON, 170, false, 356, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*32*/	{"Pistola semiautomatica TEC-9", "Munición", ITEM_WEAPON, 50, true, 372, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*33*/	{"Rifle de caza", "Munición", ITEM_WEAPON, 60, false, 357, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*34*/	{"Rifle de francotirador", "Munición", ITEM_WEAPON, 550, false, 358, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*35*/	{"RPG-7", "Munición", ITEM_WEAPON, 25000, false, 359, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*36*/	{"Lanzamisiles", "Munición", ITEM_WEAPON, 20000, false, 360, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*37*/	{"Lanzallamas", "Munición", ITEM_WEAPON, 15000, false, 361, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*38*/	{"Minigun", "Munición", ITEM_WEAPON, 0, false, 362, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*39*/	{"Carga C4", "Cantidad", ITEM_WEAPON, 15000, false, 363, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*40*/	{"Detonador", "Cantidad", ITEM_WEAPON, 1000, true, 364, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*41*/	{"Aerosol", "Contenido", ITEM_WEAPON, 50, true, 365, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*42*/	{"Matafuegos", "Contenido", ITEM_WEAPON, 250, false, 366, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*43*/	{"Cámara fotográfica", "Fotos", ITEM_WEAPON, 10, true, 367, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*44*/	{"Visión nocturna", "Cantidad", ITEM_WEAPON, 0, false, 368, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*45*/	{"Visión térmica", "Cantidad", ITEM_WEAPON, 0, false, 369, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*46*/	{"Paracaídas", "Cantidad", ITEM_WEAPON, 0, false, 371, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*47*/	{"Caja de materiales", "Cantidad", ITEM_OTHER, 45, false, 2040, 0.0, 0.074, 0.016, -85.2, 0.0, 0.0, 0},
/*48*/	{"Bidón de combustible", "Contenido", ITEM_OTHER, 50, false, 1650, 0.154, 0.028, -0.049, 0.0, -97.3, -156.3, 0},
/*49*/	{"Bolsa de materia prima", "Cantidad", ITEM_OTHER, 10, false, 2060, 0.0, 0.086, 0.155, 93.6, 0.0, 75.1, 0},
/*50*/	{"Productos", "Cantidad", ITEM_OTHER, 50, false, 2694, 0.0, 0.063, 0.182, -75.89, -0.6, 23.1, 0},
/*51*/	{"Dinero", "Cantidad", ITEM_OTHER, 1, false, 1212, 0.115, 0.039, 0.0, 1.9, -102.40, 10.8, 0},
/*52*/	{"Sandwich", "Cantidad", ITEM_OTHER, 20, true, 2769, 0.095, 0.047, -0.038, 0.0, -98.199, 0.0, 0},
/*53*/	{"Alfajor", "Cantidad", ITEM_OTHER, 10, true, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0},
/*54*/	{"Agua mineral", "Cantidad", ITEM_OTHER, 15, true, 1484, 0.125, 0.0, -0.125, 0.0, -114.299, 0.0, 0},
/*55*/	{"Maletín", "Dinero", ITEM_OTHER, 300, false, 1210, 0.301999, 0.082999, -0.012, 0.0, -90.599975, -0.9999, 0},
/*56*/  {"Casco Común", "Cantidad", ITEM_TOY, 350, false, 18645, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*57*/  {"Casco de Motocross", "Cantidad", ITEM_TOY, 400, false, 18976, 0.194, -0.032, -0.024, 68.8, 0.0, 174.1, 2},
/*58*/  {"Casco Rojo", "Cantidad", ITEM_TOY, 250, false, 18977, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*59*/  {"Casco Blanco", "Cantidad", ITEM_TOY, 250, false, 18978, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*60*/  {"Casco Rosa", "Cantidad", ITEM_TOY, 250, false, 18979, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*61*/  {"Repuesto de auto", "Cantidad", ITEM_OTHER, 75, false, 1135, 0.109, 0.072, 0.184, 98.6, 0.0, 0.0, 0},
/*62*/  {"Barreta", "Cantidad", ITEM_OTHER, 90, false, 18634, 0.108, 0.012, -0.109, -102.7, -135.4, 0.0, 0},
/*63*/  {"Casco de obrero", "Cantidad", ITEM_TOY, 30, false, 18638, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*64*/  {"Sombrero de cowboy negro", "Cantidad", ITEM_TOY, 200, false, 19096, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*65*/  {"Sombrero de cowboy marron", "Cantidad", ITEM_TOY, 200, false, 19095, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*66*/  {"Sombrero de cowboy bordó", "Cantidad", ITEM_TOY, 200, false, 19097, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*67*/  {"Reloj Swatch", "Cantidad", ITEM_TOY, 350, false, 19040, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6},
/*68*/  {"Reloj Rolex", "Cantidad", ITEM_TOY, 2500, false, 19042, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6},
/*69*/  {"Reloj Casio", "Cantidad", ITEM_TOY, 70, false, 19041, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6},
/*70*/  {"Reloj Swiss Army", "Cantidad", ITEM_TOY, 750, false, 19039, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6},
/*71*/  {"Reloj Festina", "Cantidad", ITEM_TOY, 1200, false, 19043, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6},
/*72*/  {"Sombrero antiguo", "Cantidad", ITEM_TOY, 200, false, 19352, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*73*/  {"Bigote falso 1", "Cantidad", ITEM_TOY, 10, false, 19351, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*74*/  {"Bigote falso 2", "Cantidad", ITEM_TOY, 10, false, 19350, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*75*/  {"Sombrero blanco", "Cantidad", ITEM_TOY, 250, false, 19488, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*76*/  {"Gorro rojo", "Cantidad", ITEM_TOY, 100, false, 19067, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*77*/  {"Gorro estampado", "Cantidad", ITEM_TOY, 150, false, 19068, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*78*/  {"Gorro negro", "Cantidad", ITEM_TOY, 100, false, 19069, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*79*/  {"Gorro playero negro", "Cantidad", ITEM_TOY, 100, false, 18967, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*80*/  {"Gorro playero a cuadros", "Cantidad", ITEM_TOY, 100, false, 18968, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*81*/  {"Gorra militar", "Cantidad", ITEM_TOY, 125, false, 18926, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*82*/  {"Gorra gris estampada", "Cantidad", ITEM_TOY, 125, false, 18929, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*83*/  {"Gorra blanca estampada", "Cantidad", ITEM_TOY, 125, false, 18933, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*84*/  {"Anteojos de sol", "Cantidad", ITEM_TOY, 50, false, 19033, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*85*/  {"Anteojos deportivos negros", "Cantidad", ITEM_TOY, 100, false, 19138, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*86*/  {"Anteojos deportivos rojos", "Cantidad", ITEM_TOY, 100, false, 19139, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*87*/  {"Anteojos deportivos azules", "Cantidad", ITEM_TOY, 100, false, 19140, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*88*/  {"Anteojos Rayban negros", "Cantidad", ITEM_TOY, 150, false, 19022, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*89*/  {"Anteojos Rayban azules", "Cantidad", ITEM_TOY, 150, false, 19023, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*90*/  {"Anteojos Rayban violetas", "Cantidad", ITEM_TOY, 150, false, 19024, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*91*/  {"Anteojos Rayban rosa", "Cantidad", ITEM_TOY, 150, false, 19025, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*92*/  {"Anteojos Rayban rojos", "Cantidad", ITEM_TOY, 150, false, 19026, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*93*/  {"Anteojos Rayban naranjas", "Cantidad", ITEM_TOY, 150, false, 19027, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*94*/  {"Anteojos Rayban amarillos", "Cantidad", ITEM_TOY, 150, false, 19028, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*95*/  {"Anteojos Rayban verdes", "Cantidad", ITEM_TOY, 150, false, 19029, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*96*/  {"Gorra simple negra", "Cantidad", ITEM_TOY, 150, false, 18941, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*97*/  {"Gorra simple azul", "Cantidad", ITEM_TOY, 150, false, 18942, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2},
/*98*/  {"Gorra simple verde", "Cantidad", ITEM_TOY, 150, false, 18943, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2}

};

//==============================FUNCIONES=======================================

forward bool:HasItemInvPermission(itemid); // Devuelve verdadero si el objeto entra en un inventario (si esta permitido). Falso si no lo está.
forward GetItemType(itemid); // Devuelve el tipo del item.
forward GetItemObjectModel(itemid); // Devuelve la id del modelo de objeto (visible) del item.
forward GetItemName(itemid); // Devuelve un string con el nombre del item.
forward GetItemParamName(itemid); // Devuelve un string con el nombre del parametro que le sigue al nombre del item.
forward GetItemPrice(itemid); // Devuelve el precio base unitario del item.
forward GetItemAttachBone(itemid);

forward Float:GetItemXPos(itemid); //Devuelve la posición X del objeto en BONE_ID_LEFTHAND.
forward Float:GetItemYPos(itemid); //Devuelve la posición Y del objeto en BONE_ID_LEFTHAND.
forward Float:GetItemZPos(itemid); //Devuelve la posición Z del objeto en BONE_ID_LEFTHAND.
forward Float:GetItemRxPos(itemid); //Devuelve la posición RX del objeto en BONE_ID_LEFTHAND.
forward Float:GetItemRyPos(itemid); //Devuelve la posición RY del objeto en BONE_ID_LEFTHAND.
forward Float:GetItemRzPos(itemid); //Devuelve la posición RZ del objeto en BONE_ID_LEFTHAND.

forward LoadHandItem(playerid, hand); // Crea el objeto visible en la mano del jugador (en INDEX_ID_HAND).
forward DeleteHandItem(playerid, hand); // Borra visualmente el objeto que tenga en la mano (de INDEX_ID_HAND).

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock Float:GetItemXPos(itemid)
{
	return ServerItems[itemid][XPos];
}

stock Float:GetItemYPos(itemid)
{
	return ServerItems[itemid][YPos];
}

stock Float:GetItemZPos(itemid)
{
	return ServerItems[itemid][ZPos];
}

stock Float:GetItemRxPos(itemid)
{
	return ServerItems[itemid][RxPos];
}

stock Float:GetItemRyPos(itemid)
{
	return ServerItems[itemid][RyPos];
}

stock Float:GetItemRzPos(itemid)
{
	return ServerItems[itemid][RzPos];
}

stock bool:HasItemInvPermission(itemid)
{
	return ServerItems[itemid][InvAvailable];
}

stock GetItemType(itemid)
{
	return ServerItems[itemid][Type];
}

stock GetItemObjectModel(itemid)
{
	return ServerItems[itemid][ObjectModel];
}

stock GetItemAttachBone(itemid)
{
	return ServerItems[itemid][AttachBone];
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

stock LoadHandItem(playerid, hand)
{
	new itemid = GetHandItem(playerid, hand);

	if(GetItemObjectModel(itemid) != 0)
	{
	    if(hand == HAND_RIGHT)
		{
			if(GetItemType(itemid) != ITEM_WEAPON)
				SetPlayerAttachedObject(playerid, INDEX_ID_HAND_RIGHT, GetItemObjectModel(itemid), BONE_ID_RIGHTHAND, GetItemXPos(itemid), GetItemYPos(itemid), GetItemZPos(itemid), GetItemRxPos(itemid), GetItemRyPos(itemid), GetItemRzPos(itemid), 1.0, 1.0, 1.0);
			else
			    GivePlayerWeapon(playerid, itemid, GetHandParam(playerid, HAND_RIGHT));
		}
		else
 			SetPlayerAttachedObject(playerid, INDEX_ID_HAND_LEFT, GetItemObjectModel(itemid), BONE_ID_LEFTHAND, GetItemXPos(itemid), GetItemYPos(itemid), GetItemZPos(itemid), GetItemRxPos(itemid), GetItemRyPos(itemid), GetItemRzPos(itemid), 1.0, 1.0, 1.0);
	}
	return 1;
}

stock DeleteHandItem(playerid, hand)
{
	if(hand == HAND_RIGHT)
	{
	    if(GetItemType(GetHandItem(playerid, hand)) != ITEM_WEAPON)
			RemovePlayerAttachedObject(playerid, INDEX_ID_HAND_RIGHT);
		else
		{
		    //======================[Inmunidad anticheat]=======================
		    if(antiCheatImmunity[playerid] != 0)
		        KillTimer(antiCheatImmunity[playerid]);
      		antiCheatImmunity[playerid] = SetTimerEx("AntiCheatImmunityTimer", 2000, false, "i", playerid);
      		//==================================================================
		    ResetPlayerWeapons(playerid);
		}
	}
	else
	    RemovePlayerAttachedObject(playerid, INDEX_ID_HAND_LEFT);
	return 1;
}

//================================COMANDOS======================================
