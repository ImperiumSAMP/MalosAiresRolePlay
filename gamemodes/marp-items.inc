#if defined _marp_items_included
	#endinput
#endif
#define _marp_items_included

//==============================ITEM SYSTEM=====================================

//================================CONSTANTES====================================

#define ITEM_NONE               -1
#define ITEM_WEAPON             1
#define ITEM_OTHER              2
#define ITEM_TOY                3
#define ITEM_CONTAINER          4
#define ITEM_SPEAKER	        5

#define MAX_ITEMS               112

#define ITEM_ID_CAMARA		    		43
#define ITEM_ID_MATERIALES      		47
#define ITEM_ID_BIDON		    		48
#define ITEM_ID_MATERIAPRIMA    		49
#define ITEM_ID_PRODUCTOS	    		50
#define ITEM_ID_DINERO          		51
#define ITEM_ID_SANDWICH	    		52
#define ITEM_ID_ALFAJOR		    		53
#define ITEM_ID_AGUAMINERAL     		54
#define ITEM_ID_MALETINDINERO   		55
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
#define ITEM_ID_TELEFONO_CELULAR        99
#define ITEM_ID_ENCENDEDOR		        100
#define ITEM_ID_CIGARRILLOS             101
#define ITEM_ID_RADIO		            102
#define ITEM_ID_VALIJA		            103
#define ITEM_ID_MEDICCASE	            104
#define ITEM_ID_BOLSO		            105
#define ITEM_ID_MOCHILAGRANDE           106
#define ITEM_ID_MOCHILACHICA		    107
#define ITEM_ID_MOCHILAMEDIANA		    108
#define ITEM_ID_MALETIN				    109
#define ITEM_ID_PARLANTE			    110
#define ITEM_ID_CERVEZA                 111

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
	Float:LeftXPos, // Posicion para attachear en mano izquierda
	Float:LeftYPos,
	Float:LeftZPos,
	Float:LeftRxPos,
	Float:LeftRyPos,
	Float:LeftRzPos,
	Float:RightXPos, // Posicion para attachear en mano derecha
	Float:RightYPos,
	Float:RightZPos,
	Float:RightRxPos,
	Float:RightRyPos,
	Float:RightRzPos,
	AttachBone, // Hueso donde se attachea si está equipado (no en la mano)
	OccupiedSpace
};

static const ServerItems[MAX_ITEMS][ItemInfo] = {

/*0*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0},
/*1*/	{"Manopla", "Cantidad", ITEM_WEAPON, 40, true, 331, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 5},
/*2*/	{"Palo de Golf", "Cantidad", ITEM_WEAPON, 60, false, 333, 0.035, 0.074, 0.0, 153.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 20},
/*3*/	{"Macana", "Cantidad", ITEM_WEAPON, 300, true, 334, 0.017, 0.048, -0.13, 175.4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*4*/	{"Navaja", "Cantidad", ITEM_WEAPON, 250, true, 335, 0.0, 0.074, 0.0, 148.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 6},
/*5*/	{"Bate", "Cantidad", ITEM_WEAPON, 120, false, 336, 0.024, 0.017, -0.13, 157.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 25},
/*6*/	{"Pala", "Cantidad", ITEM_WEAPON, 75, false, 337, 0.032, 0.065, 0.0, 163.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 30},
/*7*/	{"Palo de pool", "Cantidad", ITEM_WEAPON, 60, false, 338, 0.04, 0.0, -0.182, 152.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 20},
/*8*/	{"Katana", "Cantidad", ITEM_WEAPON, 6000, false, 339, 0.022, 0.018, -0.123, 162.7, -1.6, -8.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 25},
/*9*/	{"Motosierra", "Cantidad", ITEM_WEAPON, 15000, false, 341, 0.0, 0.07, 0.0, 161.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 40},
/*10*/	{"Consolador doble punta", "Cantidad", ITEM_WEAPON, 65, true, 321, 0.0150, 0.080, 0.0, 155.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*11*/	{"Consolador", "Cantidad", ITEM_WEAPON, 50, true, 322, 0.014, 0.067, -0.034, 156.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*12*/	{"Vibrador", "Cantidad", ITEM_WEAPON, 70, true, 323, 0.019, 0.07, 0.0, 161.4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*13*/	{"Vibrador plateado", "Cantidad", ITEM_WEAPON, 85, true, 324, 0.008, 0.070, -0.036, 161.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*14*/	{"Flores", "Cantidad", ITEM_WEAPON, 50, true, 325, 0.0, 0.061, 0.0, 153.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*15*/	{"Baston", "Cantidad", ITEM_WEAPON, 30, true, 326, 0.027, 0.023, -0.112, 166.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 20},
/*16*/	{"Granada", "Cantidad", ITEM_WEAPON, 1000, true, 342, 0.046, 0.09, -0.017, 155.1, 2.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 6},
/*17*/	{"Granada de gas", "Cantidad", ITEM_WEAPON, 200, true, 343, 0.024, 0.084, -0.029, 161.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 6},
/*18*/	{"Bomba molotov", "Cantidad", ITEM_WEAPON, 450, true, 344, 0.038, 0.073, 0.0, 159.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*19*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0},
/*20*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0},
/*21*/	{"NULO", "NULO", ITEM_NONE, 0, false, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0},
/*22*/	{"Pistola 9mm", "Munición", ITEM_WEAPON, 35, true, 346, 0.009, 0.061, -0.025, 150.9, 8.6, -11.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 8},
/*23*/	{"Pistola 9mm con silenciador", "Munición", ITEM_WEAPON, 75, true, 347, 0.043, 0.06, -0.022, 160.0, -0.1, -9.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*24*/	{"Pistola Desert Eagle", "Munición", ITEM_WEAPON, 150, true, 348, 0.011, 0.058, 0.0, -178.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*25*/	{"Escopeta", "Munición", ITEM_WEAPON, 70, false, 349, 0.035, 0.081, 0.023, 154.4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 30},
/*26*/	{"Escopeta recortada", "Munición", ITEM_WEAPON, 120, false, 350, 0.026, 0.058, -0.023, 170.9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 20},
/*27*/	{"Escopeta de combate", "Munición", ITEM_WEAPON, 200, false, 351, 0.024, 0.059, -0.01, 172.9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 35},
/*28*/	{"Uzi", "Munición", ITEM_WEAPON, 50, true, 352, 0.024, 0.051, -0.022, 167.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*29*/	{"Subfusil MP-5", "Munición", ITEM_WEAPON, 95, false, 353, 0.03, 0.065, 0.0, 163.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 25},
/*30*/	{"Fusil AK-47", "Munición", ITEM_WEAPON, 170, false, 355, 0.057, 0.076, 0.014, 168.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 40},
/*31*/	{"Fusil M4", "Munición", ITEM_WEAPON, 170, false, 356, 0.031, 0.042, -0.021, 174.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 40},
/*32*/	{"Pistola semiautomatica TEC-9", "Munición", ITEM_WEAPON, 50, true, 372, 0.022, 0.067, 0.0, 168.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*33*/	{"Rifle de caza", "Munición", ITEM_WEAPON, 60, false, 357, 0.057, 0.083, -0.007, 168.1, 19.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 30},
/*34*/	{"Rifle de francotirador", "Munición", ITEM_WEAPON, 550, false, 358, 0.052, 0.086, 0.007, 150.1, 8.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 40},
/*35*/	{"RPG-7", "Munición", ITEM_WEAPON, 25000, false, 359, 0.004, 0.046, 0.0, 158.8, 9.5, -4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 50},
/*36*/	{"Lanzamisiles", "Munición", ITEM_WEAPON, 20000, false, 360, 0.023, 0.067, -0.006, 169.0, -7.2, -9.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 50},
/*37*/	{"Lanzallamas", "Munición", ITEM_WEAPON, 15000, false, 361, 0.017, 0.071, -0.019, 176.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 50},
/*38*/	{"Minigun", "Munición", ITEM_WEAPON, 0, false, 362, -0.039, 0.126, -0.079, -164.78, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 50},
/*39*/	{"Carga C4", "Cantidad", ITEM_WEAPON, 15000, false, 363, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 15},
/*40*/	{"Detonador", "Cantidad", ITEM_WEAPON, 1000, true, 364, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 4},
/*41*/	{"Aerosol", "Contenido", ITEM_WEAPON, 50, true, 365, 0.029, 0.059, -0.109, -177.1, -0.9, -21.9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 6},
/*42*/	{"Matafuegos", "Contenido", ITEM_WEAPON, 250, false, 366, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 25},
/*43*/	{"Cámara fotográfica", "Fotos", ITEM_WEAPON, 10, true, 367, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 8},
/*44*/	{"Visión nocturna", "Cantidad", ITEM_WEAPON, 0, false, 368, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*45*/	{"Visión térmica", "Cantidad", ITEM_WEAPON, 0, false, 369, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 10},
/*46*/	{"Paracaídas", "Cantidad", ITEM_WEAPON, 0, false, 371, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 50},
/*47*/	{"Caja de materiales", "Cantidad", ITEM_OTHER, 45, false, 2040, 0.0, 0.074, 0.016, -85.2, 0.0, 0.0, 0.0, 0.074, 0.016, -85.2, 0.0, 0.0, 0, 100},
/*48*/	{"Bidón de combustible", "Contenido", ITEM_OTHER, 50, false, 1650, 0.154, 0.028, -0.049, 0.0, -97.3, -156.3, 0.154, 0.028, -0.049, 0.0, -97.3, -156.3, 0, 70},
/*49*/	{"Bolsa de materia prima", "Cantidad", ITEM_OTHER, 10, false, 2060, 0.0, 0.086, 0.155, 93.6, 0.0, 75.1, 0.0, 0.086, 0.155, 93.6, 0.0, 75.1, 0, 60},
/*50*/	{"Productos", "Cantidad", ITEM_OTHER, 50, false, 2694, 0.0, 0.063, 0.182, -75.89, -0.6, 23.1, 0.0, 0.063, 0.182, -75.89, -0.6, 23.1, 0, 65},
/*51*/	{"Dinero", "Cantidad", ITEM_OTHER, 1, false, 1212, 0.115, 0.039, 0.0, 1.9, -102.40, 10.8, 0.115, 0.039, 0.0, 1.9, -102.40, 10.8, 0, 4},
/*52*/	{"Sándwich", "Cantidad", ITEM_OTHER, 20, true, 2769, 0.095, 0.047, -0.038, 0.0, -98.199, 0.0, 0.095, 0.047, -0.038, 0.0, -98.199, 0.0, 0, 6},
/*53*/	{"Alfajor", "Cantidad", ITEM_OTHER, 10, true, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 2},
/*54*/	{"Agua mineral", "Cantidad", ITEM_OTHER, 15, true, 1484, 0.125, 0.0, -0.125, 0.0, -114.299, 0.0, 0.04, 0.0, -0.047, 0.0, 0.0, 0.0, 0, 8},
/*55*/	{"Maletín de dinero", "$", ITEM_OTHER, 300, false, 1210, 0.302, 0.083, -0.012, 0.0, -90.599, -0.99, 0.302, 0.083, -0.012, 0.0, -90.599, -0.99, 0, 55},
/*56*/  {"Casco Común", "Cantidad", ITEM_TOY, 350, false, 18645, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 30},
/*57*/  {"Casco de Motocross", "Cantidad", ITEM_TOY, 400, false, 18976, 0.194, -0.032, -0.024, 68.8, 0.0, 174.1, 0.194, -0.032, -0.024, 68.8, 0.0, 174.1, 2, 35},
/*58*/  {"Casco Rojo", "Cantidad", ITEM_TOY, 250, false, 18977, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 30},
/*59*/  {"Casco Blanco", "Cantidad", ITEM_TOY, 250, false, 18978, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 30},
/*60*/  {"Casco Rosa", "Cantidad", ITEM_TOY, 250, false, 18979, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 30},
/*61*/  {"Repuesto de auto", "Cantidad", ITEM_OTHER, 35, false, 1135, 0.109, 0.072, 0.184, 98.6, 0.0, 0.0, 0.109, 0.072, 0.184, 98.6, 0.0, 0.0, 15},
/*62*/  {"Barreta", "Cantidad", ITEM_OTHER, 50, false, 18634, 0.108, 0.012, -0.109, -102.7, -135.4, 0.0, 0.08, 0.043, 0.206, 85.5, -5.5, 0.6, 0, 20},
/*63*/  {"Casco de obrero", "Cantidad", ITEM_TOY, 30, false, 18638, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 20},
/*64*/  {"Sombrero de cowboy negro", "Cantidad", ITEM_TOY, 200, false, 19096, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 25},
/*65*/  {"Sombrero de cowboy marron", "Cantidad", ITEM_TOY, 200, false, 19095, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 25},
/*66*/  {"Sombrero de cowboy bordó", "Cantidad", ITEM_TOY, 200, false, 19097, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 25},
/*67*/  {"Reloj Swatch", "Cantidad", ITEM_TOY, 350, false, 19040, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6, 2},
/*68*/  {"Reloj Rolex", "Cantidad", ITEM_TOY, 2500, false, 19042, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6, 2},
/*69*/  {"Reloj Casio", "Cantidad", ITEM_TOY, 70, false, 19041, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6, 2},
/*70*/  {"Reloj Swiss Army", "Cantidad", ITEM_TOY, 750, false, 19039, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6, 2},
/*71*/  {"Reloj Festina", "Cantidad", ITEM_TOY, 1200, false, 19043, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6, 2},
/*72*/  {"Sombrero antiguo", "Cantidad", ITEM_TOY, 200, false, 19352, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 25},
/*73*/  {"Bigote falso 1", "Cantidad", ITEM_TOY, 10, false, 19351, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 2},
/*74*/  {"Bigote falso 2", "Cantidad", ITEM_TOY, 10, false, 19350, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 2},
/*75*/  {"Sombrero blanco", "Cantidad", ITEM_TOY, 250, false, 19488, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 25},
/*76*/  {"Gorro rojo", "Cantidad", ITEM_TOY, 100, false, 19067, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*77*/  {"Gorro estampado", "Cantidad", ITEM_TOY, 150, false, 19068, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*78*/  {"Gorro negro", "Cantidad", ITEM_TOY, 100, false, 19069, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*79*/  {"Gorro playero negro", "Cantidad", ITEM_TOY, 100, false, 18967, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*80*/  {"Gorro playero a cuadros", "Cantidad", ITEM_TOY, 100, false, 18968, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*81*/  {"Gorra militar", "Cantidad", ITEM_TOY, 125, false, 18926, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*82*/  {"Gorra gris estampada", "Cantidad", ITEM_TOY, 125, false, 18929, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*83*/  {"Gorra blanca estampada", "Cantidad", ITEM_TOY, 125, false, 18933, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*84*/  {"Anteojos de sol", "Cantidad", ITEM_TOY, 50, false, 19033, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*85*/  {"Anteojos deportivos negros", "Cantidad", ITEM_TOY, 100, false, 19138, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*86*/  {"Anteojos deportivos rojos", "Cantidad", ITEM_TOY, 100, false, 19139, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*87*/  {"Anteojos deportivos azules", "Cantidad", ITEM_TOY, 100, false, 19140, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*88*/  {"Anteojos Rayban negros", "Cantidad", ITEM_TOY, 150, false, 19022, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*89*/  {"Anteojos Rayban azules", "Cantidad", ITEM_TOY, 150, false, 19023, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*90*/  {"Anteojos Rayban violetas", "Cantidad", ITEM_TOY, 150, false, 19024, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*91*/  {"Anteojos Rayban rosa", "Cantidad", ITEM_TOY, 150, false, 19025, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*92*/  {"Anteojos Rayban rojos", "Cantidad", ITEM_TOY, 150, false, 19026, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*93*/  {"Anteojos Rayban naranjas", "Cantidad", ITEM_TOY, 150, false, 19027, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*94*/  {"Anteojos Rayban amarillos", "Cantidad", ITEM_TOY, 150, false, 19028, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*95*/  {"Anteojos Rayban verdes", "Cantidad", ITEM_TOY, 150, false, 19029, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 6},
/*96*/  {"Gorra simple negra", "Cantidad", ITEM_TOY, 150, false, 18941, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*97*/  {"Gorra simple azul", "Cantidad", ITEM_TOY, 150, false, 18942, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*98*/  {"Gorra simple verde", "Cantidad", ITEM_TOY, 150, false, 18943, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 0.214, 0.063, 0.0, -93.4, 0.0, 0.0, 2, 15},
/*99*/  {"Telefono celular", "Cantidad", ITEM_OTHER, 1, false, 18868, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.097,0.031,-0.017,87.8,-177.3,-3.5, 0, 4},
/*100*/ {"Encendedor", "Usos", ITEM_OTHER, 15, true, 19998, 0.094, 0.039, -0.025, 0.000, -175.400, 0.000, 0.052, 0.031, 0.029, 0.000, 0.000, 0.000, 0, 1},
/*101*/ {"Cigarrillos", "Cantidad", ITEM_OTHER, 20, true, 19896, 0.108, 0.037, -0.046, 95.599, 17.200, 175.400, 0.057, 0.051, 0.035, -82.700, 0.000, -10.799, 0, 2},
/*102*/ {"Radio Walkie Talkie", "Cantidad", ITEM_OTHER, 400, true, 19942, 0.087, 0.047, -0.054, -14.599, -171.099, 0.000, 0.068, 0.033, 0.053, 0.000, 0.000, 0.000, 0, 4},
/*103*/ {"Valija", "Espacio", ITEM_CONTAINER, 400, false, 19624, 0.085, 0.000, -0.018, -2.199, -98.699, 37.400, 0.074, 0.013, 0.000, 0.000, -98.100, 0.000, 0, 75},
/*104*/ {"Botiquín médico", "Usos restantes", ITEM_OTHER, 400, false, 11738, 0.268, 0.022, -0.007, 0.000, -94.700, 12.699, 0.270, 0.022, 0.036, 0.000, -97.899, 0.000, 0, 45},
/*105*/ {"Bolso deportivo", "Espacio", ITEM_CONTAINER, 300, false, 11745, 0.198, -0.056, 0.055, 0.000, -99.399, -46.499, 0.214, -0.066, 0.014, 0.000, -99.799, 87.300, 0, 65},
/*106*/ {"Mochila grande", "Espacio", ITEM_CONTAINER, 550, false, 19559, 0.412, 0.066, 0.000, 0.000, -97.000, 24.599, 0.400, 0.049, 0.066, 0.000, -96.600, 0.000, 0, 55},
/*107*/ {"Mochila chica", "Espacio", ITEM_CONTAINER, 300, false, 3026, 0.504, 0.000, 0.000, 146.999, 0.000, -173.799, 0.473, -0.040, 0.000, -169.700, 0.000, -171.399, 0, 35},
/*108*/ {"Mochila mediana", "Espacio", ITEM_CONTAINER, 425, false, 371, 0.377, 0.022, 0.049, 0.000, -104.999, 26.500, 0.340, -0.004, 0.074, 0.000, -99.700, 0.000, 0, 45},
/*109*/ {"Maletín", "Espacio", ITEM_CONTAINER, 400, false, 1210, 0.3019, 0.0829, -0.012, 0.0, -90.5999, -0.9999, 0.3019, 0.0829, -0.012, 0.0, -90.5999, -0.9999, 0, 45},
/*110*/ {"Reproductor de música", "Cantidad", ITEM_SPEAKER, 550, false, 2102, 0.396, 0.000, 0.020, 0.000, -93.600, 8.399, 0.369, 0.021, 0.058, 0.000, -99.599, 0.000, 0, 50},
/*111*/ {"Cerveza", "Cantidad", ITEM_OTHER, 35, true, 1486, 0.125, 0.0, -0.125, 0.0, -114.299, 0.0, 0.04, 0.0, -0.047, 0.0, 0.0, 0.0, 0, 8}
};

//==============================FUNCIONES=======================================

forward bool:HasItemInvPermission(itemid); // Devuelve verdadero si el objeto entra en un inventario (si esta permitido). Falso si no lo está.
forward GetItemType(itemid); // Devuelve el tipo del item.
forward GetItemObjectModel(itemid); // Devuelve la id del modelo de objeto (visible) del item.
forward GetItemName(itemid); // Devuelve un string con el nombre del item.
forward GetItemParamName(itemid); // Devuelve un string con el nombre del parametro que le sigue al nombre del item.
forward GetItemPrice(itemid); // Devuelve el precio base unitario del item.
forward GetItemAttachBone(itemid);

forward Float:GetItemLeftXPos(itemid);
forward Float:GetItemLeftYPos(itemid);
forward Float:GetItemLeftZPos(itemid);
forward Float:GetItemLeftRxPos(itemid);
forward Float:GetItemLeftRyPos(itemid);
forward Float:GetItemLeftRzPos(itemid);

forward Float:GetItemRightXPos(itemid);
forward Float:GetItemRightYPos(itemid);
forward Float:GetItemRightZPos(itemid);
forward Float:GetItemRightRxPos(itemid);
forward Float:GetItemRightRyPos(itemid);
forward Float:GetItemRightRzPos(itemid);

forward LoadHandItem(playerid, hand); // Crea el objeto visible en la mano del jugador (en INDEX_ID_HAND).
forward DeleteHandItem(playerid, hand); // Borra visualmente el objeto que tenga en la mano (de INDEX_ID_HAND).

//=======================IMPLEMENTACIÓN DE FUNCIONES============================

stock Float:GetItemLeftXPos(itemid)
{
	return ServerItems[itemid][LeftXPos];
}

stock Float:GetItemLeftYPos(itemid)
{
    return ServerItems[itemid][LeftYPos];
}

stock Float:GetItemLeftZPos(itemid)
{
	return ServerItems[itemid][LeftZPos];
}

stock Float:GetItemLeftRxPos(itemid)
{
	return ServerItems[itemid][LeftRxPos];
}

stock Float:GetItemLeftRyPos(itemid)
{
	return ServerItems[itemid][LeftRyPos];
}

stock Float:GetItemLeftRzPos(itemid)
{
	return ServerItems[itemid][LeftRzPos];
}

stock Float:GetItemRightXPos(itemid)
{
	return ServerItems[itemid][RightXPos];
}

stock Float:GetItemRightYPos(itemid)
{
    return ServerItems[itemid][RightYPos];
}

stock Float:GetItemRightZPos(itemid)
{
	return ServerItems[itemid][RightZPos];
}

stock Float:GetItemRightRxPos(itemid)
{
	return ServerItems[itemid][RightRxPos];
}

stock Float:GetItemRightRyPos(itemid)
{
	return ServerItems[itemid][RightRyPos];
}

stock Float:GetItemRightRzPos(itemid)
{
	return ServerItems[itemid][RightRzPos];
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

stock GetItemSpace(itemid)
{
	return ServerItems[itemid][OccupiedSpace];
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
				SetPlayerAttachedObject(playerid, INDEX_ID_HAND_RIGHT, GetItemObjectModel(itemid), BONE_ID_RIGHTHAND, GetItemRightXPos(itemid), GetItemRightYPos(itemid), GetItemRightZPos(itemid), GetItemRightRxPos(itemid), GetItemRightRyPos(itemid), GetItemRightRzPos(itemid), 1.0, 1.0, 1.0);
			else
			{
   				//======================[Inmunidad anticheat]=======================
			    if(antiCheatImmunity[playerid] != 0)
			        KillTimer(antiCheatImmunity[playerid]);
	      		antiCheatImmunity[playerid] = SetTimerEx("AntiCheatImmunityTimer", 2000, false, "i", playerid);
	      		//==================================================================
			    GivePlayerWeapon(playerid, itemid, GetHandParam(playerid, HAND_RIGHT));
			    SetPlayerAmmo(playerid, itemid, GetHandParam(playerid, HAND_RIGHT));
			}
		}
		else
 			SetPlayerAttachedObject(playerid, INDEX_ID_HAND_LEFT, GetItemObjectModel(itemid), BONE_ID_LEFTHAND, GetItemLeftXPos(itemid), GetItemLeftYPos(itemid), GetItemLeftZPos(itemid), GetItemLeftRxPos(itemid), GetItemLeftRyPos(itemid), GetItemLeftRzPos(itemid), 1.0, 1.0, 1.0);
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
