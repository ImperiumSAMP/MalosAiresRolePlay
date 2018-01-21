#if defined _marp_furnitures_included
	#endinput
#endif
#define _marp_furnitures_included
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                     SISTEMA DE MUEBLES BY JBracone                         //
//                      	HECHO PARA PHEEK.NET                              //
//                            2017 v.0.1 beta                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#define MAX_HOUSE_FURNITURES			200
#define MAX_FURNITURE_TOTAL_OBJECTS     10000

/*-------------------DEFINES CATALOGOS----------------------------------------*/
#define CATALOG_OWN_FURN            	1000
#define CATALOG_MESAS_SILLAS			1001
#define CATALOG_CAMAS_MESAS_ARM     	1002
#define CATALOG_ILUMINACION         	1003
#define CATALOG_FRAMES                  1004
#define CATALOG_BATH                    1005
#define CATALOG_CONSTRUCTION            1006
#define CATALOG_KITCHEN                 1007
#define CATALOG_ELECTRONICS             1008
#define CATALOG_ENTERTAINMENT           1009
#define CATALOG_MISC                    1010

#define DLG_ITEM_M_MESAS_SILLAS     	0
#define DLG_ITEM_M_CAMAS_MESAS_ARM		1
#define DLG_ITEM_M_ILUMINACION			2
#define DLG_ITEM_M_FRAMES               3
#define DLG_ITEM_M_BATH                 4
#define DLG_ITEM_M_CONSTRUCTION         5
#define DLG_ITEM_M_KITCHEN              6
#define DLG_ITEM_M_ELECTRONICS          7
#define DLG_ITEM_M_ENTERTAINMENT        8
#define DLG_ITEM_M_MISC                 9

#define DLG_ITEM_OWN_EDIT               0
#define DLG_ITEM_OWN_DELETE             1
#define DLG_ITEM_OWN_PACKING            2

#define DB_FURNITURE_UPDATE 			1
#define DB_FURNITURE_CREATE 			2
#define DB_FURNITURE_DELETE 			3


//===================================FORWARDS===================================
forward CreateFurnitureObject(playerid, modelid);
forward EditarMueble(playerid, objectid);

enum hFurnitureInfo {
	fObjectID,
	fObjectModel,
	Float:fX,
	Float:fY,
	Float:fZ,
	Float:fRX,
	Float:fRY,
	Float:fRZ,
};



new totalFurnitureObjects;
new HouseFurnitures[MAX_HOUSES][MAX_HOUSE_FURNITURES][hFurnitureInfo];
new furnitureObjectSelection[MAX_PLAYERS],
	furniturePriceObjectSelection[MAX_PLAYERS];
new currentFurnitureEdit[MAX_PLAYERS];
new OwnFurnitureSelected[MAX_PLAYERS];

enum FurnitureInfo
{
	fName[45],
	ObjectModel,
	Price
	//si es necesario, agregar la zPos para una mejor visualización de c/ mueble
};
stock loadFurn(playerid) {
	Catalogo_CreateTextdraws(playerid);
	furnitureObjectSelection[playerid] = 0;
	furniturePriceObjectSelection[playerid] = 0;
	totalFurnitureObjects = 0;
	OwnFurnitureSelected[playerid] = 0;
}

new const M_Mesas_Sillas[][FurnitureInfo] =
{
	/*0*/ {"Mesa cuadrada madera oscura", 1433, 600},
	/*1*/ {"Mesa cuadrada madera oscura 2", 1516, 550},
	/*2*/ {"Mesa café redonda vidrio", 1827, 450},
	/*3*/ {"Mesa cuadrada Bar madera clara 1", 2635, 550},
	/*4*/ {"Mesa rectangular Bar madera clara 1", 2637, 750},
	/*5*/ {"Mesa cuadrada Bar madera clara 2", 2644, 550},
	/*6*/ {"Mesa hexagonal Bar madera oscura", 2725, 600},
	/*7*/ {"Mesa rectangular Bar madera clara 2", 2747, 750},
	/*8*/ {"Mesa rectangular roja", 2762, 600},
	/*9*/ {"Mesa cuadrada roja", 2763, 450},
	/*10*/{"Mesa cuadrada mantel rojo", 2764, 450},
	/*11*/{"Mesa rectangular lujo madera oscura", 2357, 1200},
	/*12*/{"Mesa rectangular redondeada oscura 1", 2119, 550},
	/*13*/{"Mesa ovalada marmol blanco", 2118, 650},
	/*14*/{"Mesa rectangular tres patas madera", 2117, 600},
	/*15*/{"Mesa rectangular clara 1", 2116, 500},
	/*16*/{"Mesa rectangular clara 2", 2115, 500},
	/*17*/{"Mesa cuadrada madera oscura 3", 2112, 550},
	/*18*/{"Mesa redonda madera oscura", 2111, 600},
	/*19*/{"Mesa rectangular oscura", 2110, 550},
	/*20*/{"Mesa redonda madera clara", 2109, 500},
	/*21*/{"Mesa redonda lujo vidrio", 2086, 700},
	/*22*/{"Mesa rectangular vidrio", 2085, 600},
	/*23*/{"Mesa ovalada madera oscura", 2080, 600},
	/*24*/{"Mesa rectangular redondeada oscura 2", 2032, 575},
	/*25*/{"Mesa ovalada clara", 2031, 500},
	/*26*/{"Mesa redonda marmol blanco", 2030, 600},
	/*27*/{"Mesa rectangular clara 3", 2029, 550},
	/*28*/{"Mesa blanca y roja", 1770, 400},
	/*29*/{"Mesa rectangular redondeada oscura 3", 1737, 575},
	/*30*/{"Juego mesa c/4 sillas rojas", 1968, 1300},
	/*31*/{"Juego mesa c/2 sillas rojas", 1969, 1000},
	/*32*/{"Juego mesa c/2 sillones resto 1", 1970, 1500},
	/*33*/{"Juego mesa c/2 sillones resto 2", 2027, 1850},
	/*34*/{"Juego mesa redonda c/3 sillas rojas", 1432, 800},
	/*35*/{"Juego mesa cuadrada c/4 sillas 1", 1594, 850},
	/*36*/{"Juego mesa cuadrada c/4 sillas 2", 1679, 850},
	/*37*/{"Juego mesa redonda c/3 sillas beige", 1825, 1100},
	/*38*/{"Juego mesa redonda c/2 sillas bar 1", 2799, 1000},
	/*39*/{"Juego mesa redonda c/2 sillas bar 2", 2802, 1000},
    /*40*/{"Juego mesa cuadrada c/4 sillas 3", 643, 750},
	/*41*/{"Silla oficina sin a/brazos", 1663, 250},
	/*42*/{"Silla oficina con a/brazos", 1671, 300},
	/*43*/{"Silla oficina 1", 1714, 400},
	/*44*/{"Silla oficina 2", 1715, 300},
	/*45*/{"Silla madera beige", 1720, 250},
	/*46*/{"Silla metal negra 1", 1721, 175},
	/*47*/{"Silla metal negra 2", 1722, 175},
	/*48*/{"Silla madera lujo", 1739, 300},
	/*49*/{"Sila oficina 3", 1806, 225},
	/*50*/{"Silla metal", 1810, 75},
	/*51*/{"Silla madera oscura 1", 1811, 250},
	/*52*/{"Silla madera oscura 2", 2079, 225},
	/*53*/{"Mesedora antigua", 2096, 150},
	/*54*/{"Silla madera oscura 3", 2120, 200},
	/*55*/{"Silla roja simple", 2121, 100},
	/*56*/{"Silla blanca", 2123, 175},
	/*57*/{"Silla madera clara", 2124, 225},
	/*58*/{"Taburete rojo", 2125, 200},
	/*59*/{"Silla madera oscura 4", 2309, 250},
	/*60*/{"Silla madera oscura 5", 2310, 250},
    /*61*/{"Silla de tattoo", 2343, 550},
	/*62*/{"Silla oficina 4", 2356, 225},
	/*63*/{"Silla madera oscura 6", 2636, 250},
	/*64*/{"Sillon doble resto rojo 1", 2638, 850},
	/*65*/{"Sillon simple resto rojo", 2639, 750},
	/*66*/{"Silla negra 1", 2724, 200},
	/*67*/{"Sillon doble resto rojo 2", 2746, 850},
	/*68*/{"Sillon simple resto rojo 2", 2748, 750},
	/*69*/{"Silla negra 2", 2776, 200},
	/*70*/{"Silla negra 3", 2777, 200},
	/*71*/{"Silla roja cuadriculada 1", 2788, 150},
	/*72*/{"Silla roja cuadriculada 2", 2807, 150},
	/*73*/{"Sillon simple resto rojo 3", 2808, 750},
	/*74*/{"Mesa carrete de soga rústica", 933, 75}
};

/*----------------------------------------------------------------------------*/

new const M_Camas_Mesas_Arm[][FurnitureInfo] =
{
    /*0*/ {"Cama 2 plazas rosa", 1700, 800},
	/*1*/ {"Cama 2 plazas beige 1", 1701, 850},
	/*2*/ {"Cama 2 plazas beige 2", 1725, 850},
	/*3*/ {"Cama 2 plazas rayada", 1745, 900},
	/*4*/ {"Catre c/ colchón 1", 1771, 350},
	/*5*/ {"Colchón rayado 1", 1793, 500},
	/*6*/ {"Cama 2 plazas madera cuadros", 1794, 750},
	/*7*/ {"Cama 2 plazas sin almohada rayada", 1795, 600},
	/*8*/ {"Cama 1 plaza madera cuadros", 1796, 500},
	/*9*/ {"Cama 2 plazas madera oscura 1", 1797, 900},
    /*10*/{"Cama 2 plazas c/ almohada rayada", 1798, 700},
	/*11*/{"Cama 2 plazas oscura y amarilla", 1799, 800},
	/*12*/{"Cadre c/ colchón 2", 1800, 350},
	/*13*/{"Cama 2 plazas metal c/ colchón", 1801, 525},
	/*14*/{"Cama 2 plazas madera 1", 1802, 650},
	/*15*/{"Cama 2 plazas madera 2", 1803, 700},
	/*16*/{"Cama madera plegable s/ colchón", 1804, 300},
	/*17*/{"Cama 1 plaza baja metal", 1812, 400},
	/*18*/{"Cama 2 plazas madera oscura 2", 2090, 900},
	/*19*/{"Cama 2 plazas c/ mesas madera clara", 2298, 1350},
    /*20*/{"Cama 2 plazas oscura y blanca", 2299, 800},
    /*21*/{"Cama 2 plazas c/ estanteria 1", 2300, 1400},
	/*22*/{"Cama 2 plazas c/ estanteria 2", 2301, 1100},
	/*23*/{"Cama 2 plazas madera oscura 3", 2302, 750},
	/*24*/{"Juego 2 camas 2P Hotel c/ mesas", 2565, 2050},
	/*25*/{"Cama 2 plazas blanca c/ mesas", 2566, 1500},
	/*26*/{"Somier 2 plazas c/ mesas", 2575, 1400},
	/*27*/{"Cama 2,5 plazas cebra", 14446, 1000},
	/*28*/{"Colchón rayado 2", 14861, 350},
	/*29*/{"Cama 2 plazas madera clara 1", 14866, 750},
    /*30*/{"Colchón rayado 3", 14880, 350},
	/*31*/{"Mesa de luz blanca ", 2331, 250},
	/*32*/{"Mesa de luz doble blanca", 2333, 350},
	/*33*/{"Cama 2 plazas c/ estanteria 3", 2563, 1400},
	/*34*/{"Juego 2 camas 2P Hotel c/ estanteria", 2564, 1950},
	/*35*/{"Cómoda madera clara 1", 2323, 650},
	/*36*/{"Armario 2 puertas madera clara 1", 2330, 750},
	/*37*/{"Armario grande c/ televisor", 2091, 800},
	/*38*/{"Armario grande 2 puertas", 14556, 850},
	/*39*/{"Mesa de luz madera clara 1", 1740, 300},
    /*40*/{"Cómoda madera clara 2", 911, 400},
    /*41*/{"Cómoda madera clara 3", 912, 300},
	/*42*/{"Cómoda madera clara 4", 913, 350},
	/*43*/{"Cómoda madera clara 5", 1741, 500},
	/*44*/{"Cómoda madera clara 6", 1743, 650},
	/*45*/{"Mesa de luz 4 cajones", 2021, 350},
	/*46*/{"Cómoda madera clara 7", 2087, 450},
	/*47*/{"Armario 2 puertas madera clara 2", 2088, 700},
	/*48*/{"Cómoda madera oscura 1", 2089, 500},
	/*49*/{"Cómoda madera clara 8", 2094, 600},
    /*50*/{"Mesa de luz madera clara 2", 2095, 300},
	/*51*/{"Aparador doble c/ estanteria", 2204, 1000},
	/*52*/{"Cómoda simple madera clara", 2306, 350},
	/*53*/{"Armario simple madera clara 1", 2307, 550},
	/*54*/{"Mesa de luz madera clara 3", 2328, 300},
	/*55*/{"Armario simple madera clara 2", 2329, 550},
	/*56*/{"Armario medio oriente", 2025, 850},
	/*57*/{"Placard 11 puertas 9 cajones grande", 14867, 2100},
	/*58*/{"Aparador c/ detalles madera clara", 2562, 650},
	/*59*/{"Aparador c/ detalles madera oscura", 2568, 800},
	/*60*/{"Armario y cajonera c/ detalles", 2573, 1050},
	/*61*/{"Cajonera y aparador madera clara", 2574, 950},
	/*62*/{"Armario y cajonera madera oscura", 2576, 1100}
};

/*----------------------------------------------------------------------------*/

new const M_Iluminacion[][FurnitureInfo] =
{
	/*0*/ {"Aplique de pared simple", 921, 75},
	/*1*/ {"Juego 3 lámparas techo redondas", 938, 300},
	/*2*/ {"Luz moderna de techo redonda 1", 957, 150},
	/*3*/ {"Aplique de pared mimbre", 1731, 125},
	/*4*/ {"Lámpara de techo estilo oriente", 1734, 100},
	/*5*/ {"Lámpara de techo tubo 1", 1893, 115},
	/*6*/ {"Lámpara de pie 1", 2069, 175},
	/*7*/ {"Lámpara de mesa 1", 2070, 125},
	/*8*/ {"Lámpara de pie moderna 1", 2071, 200},
	/*9*/ {"Lámpara de pie moderna 2", 2072, 200},
	/*10*/{"Lámpara de techo mimbre", 2073, 125},
	/*11*/{"Foco de techo 1", 2074, 75},
	/*12*/{"Lámpara de techo tubo 2", 2075, 150},
	/*13*/{"Lámpara de techo redonda", 2076, 150},
	/*14*/{"Lámpara de mesa 2", 2077, 145},
	/*15*/{"Lámpara de mesa gris 1", 2105, 150},
	/*16*/{"Lámpara de mesa gris 2", 2106, 150},
	/*17*/{"Lámpara de mesa 3", 2107, 135},
	/*18*/{"Lámpara de pie madera", 2108, 175},
	/*19*/{"Lámpara de pie moderna 3", 2239, 225},
	/*20*/{"Lámpara de pie estilo oriente", 2176, 550},
	/*21*/{"Luz moderna de techo redonda 2", 2740, 175},
	/*22*/{"Aplique de pared común", 3785, 100},
	/*23*/{"Ventilador c/ lámpara", 16780, 650},
	/*24*/{"Juego 6 lámparas techo cuadradas", 18075, 950},
	/*25*/{"Pin Led Blanco", 19143, 350},
	/*26*/{"Pin Led Rojo", 19144, 350},
	/*27*/{"Pin Led Verde", 19145, 350},
	/*28*/{"Pin Led Azul", 19146, 350},
	/*29*/{"Pin Led Amarillo", 19147, 350},
	/*30*/{"Pin Led Rosa", 19148, 350},
	/*31*/{"Pin Led Celeste", 19149, 350},
	/*32*/{"Reflector Blanco 1", 19279, 450},
	/*33*/{"Reflector Blanco 2", 19280, 450},
	/*34*/{"Lámpara de techo colgante", 945, 150},
	/*35*/{"Lámpara de mesa 4", 2196, 125},
	/*36*/{"Lámpara de lava", 2238, 200},
	/*37*/{"Lámpara de mesa estilo oriente 1", 2726, 300},
	/*38*/{"Lámpara de mesa estilo oriente 2", 3534, 250},
	/*39*/{"Poste de luz diversidad", 3853, 500},
	/*40*/{"Neón Rojo", 18647, 400},
	/*41*/{"Neón Azul", 18648, 400},
	/*42*/{"Neón Verde", 18649, 400},
	/*43*/{"Neón Amarillo", 18650, 400},
	/*44*/{"Neón Rosa", 18651, 400},
	/*45*/{"Neón Blanco", 18652, 400},
	/*46*/{"Antorcha", 3525, 250},
	/*47*/{"Lámpara de lava verde", 2976, 500},
	/*48*/{"Juego 4 candelabros", 14629, 1000}
};

/*----------------------------------------------------------------------------*/

new const M_Bath[][FurnitureInfo] =
{
	/*0*/{"Alfombra 1", 1640, 150},
	/*1*/{"Alfombra 2", 1641, 150},
	/*2*/{"Alfombra 3", 1642, 150},
	/*3*/{"Alfombra 4", 1643, 150},
	/*4*/{"Alfombra 5", 2631, 175},
	/*5*/{"Alfombra 6", 2632, 175},
	/*6*/{"Alfombra 7", 2817, 200},
	/*7*/{"Alfombra 8", 2818, 200},
	/*8*/{"Espejo 1", 1846, 300},
	/*9*/{"Inodoro 1", 2514, 750},
	/*10*/{"Inodoro 2", 2521, 700},
	/*11*/{"Inodoro 3", 2525, 850},
	/*12*/{"Inodoro 4", 2528, 800},
	/*13*/{"Inodoro 5", 2738, 700},
	/*14*/{"Lavabo 1", 2515, 500},
	/*15*/{"Lavabo 2", 2518, 550},
	/*16*/{"Lavabo 3", 2523, 650},
	/*17*/{"Lavabo 4", 2524, 600},
	/*18*/{"Lavabo 5", 2739, 500},
	/*19*/{"Lavabo 6", 11709, 900},
	/*20*/{"Bañadera 1", 2516, 1000},
	/*21*/{"Bañadera 2", 2519, 1000},
	/*22*/{"Bañadera 3", 2526, 1300},
	/*23*/{"Ducha 1", 2517, 800},
	/*24*/{"Ducha 2", 2520, 850},
	/*25*/{"Ducha 3", 2527, 900},
	/*26*/{"Acondicionador", 2709, 50},
	/*27*/{"Loción de sol", 1644, 75},
	/*28*/{"Dispenser de jabón", 2741, 200},
	/*29*/{"Secador de manos", 2742, 300},
	/*30*/{"Acondicionador de cabello", 2749, 80},
	/*31*/{"Secador de pelo", 2750, 350},
	/*32*/{"Crema facial", 2751, 100},
	/*33*/{"Shampoo", 2752, 75},
	/*34*/{"Papel higiénico", 19873, 50},
	/*35*/{"Jabón", 19874, 35},
	/*36*/{"Cortina y grifería de baño 1", 14481, 400},
	/*37*/{"Cortina y griferia de baño 2", 14494, 400},
	/*38*/{"Cortina y revestimento de bañadera 1", 2522, 500},
	/*39*/{"Barral c/ toallas", 11707, 250}
};

/*----------------------------------------------------------------------------*/

new const M_Construction[][FurnitureInfo] =
{
/*0*/{"Pared mediana franja 1", 19368, 300},
/*1*/{"Pared mediana franja 2", 19367, 300},
/*2*/{"Pared mediana madera 1", 19366, 400},
/*3*/{"Pared mediana marron 1", 19370, 350},
/*4*/{"Pared mediana gris 1", 19362, 250},
/*5*/{"Pared mediana franja 3", 19369, 300},
/*6*/{"Pared mediana madera 2", 19376, 400},
/*7*/{"Pared mediana gris 2", 19371, 300},
/*8*/{"Pared mediana gris 3", 19372, 250},
/*9*/{"Pared mediana g.c/franja", 19464, 400},
/*10*/{"Pared mediana verde", 19373, 350},
/*11*/{"Pared mediana madera 3", 19375, 400},
/*12*/{"Pared mediana gris 4", 19377, 250},
/*13*/{"Pared mediana madera 4", 19378, 350},
/*14*/{"Pared mediana marron 2", 19379, 300},
/*15*/{"Pared mediana gris 5", 19380, 200},
/*16*/{"Pared mediana verde 2", 19381, 350},
/*17*/{"Pared mediana cemento 1", 19365, 300},
/*18*/{"Pared mediana gris 6", 19355, 200},
/*19*/{"Pared mediana cemento 2", 19364, 350},
/*20*/{"Pared mediana doble 1", 19353, 500},
/*21*/{"Pared mediana oscura", 19354, 450},
/*22*/{"Pared mediana madera 5", 19356, 400},
/*23*/{"Pared mediana crema", 19357, 300},
/*24*/{"Pared mediana doble 2", 19358, 500},
/*25*/{"Pared mediana gris 7", 19359, 350},
/*26*/{"Pared mediana madera 6", 19360, 400},
/*27*/{"Pared mediana doble 3", 19361, 500},
/*28*/{"Pared mediana gris 8", 19363, 350},
/*29*/{"Pared chica madera 1", 19433, 300},
/*30*/{"Pared chica cemento 1", 19437, 200},
/*31*/{"Pared chica cemento 2", 19438, 200},
/*32*/{"Pared chica madera 2", 19439, 200},
/*33*/{"Pared chica gris 1", 19440, 200},
/*34*/{"Pared chica gris 2", 19441, 200},
/*35*/{"Pared chica gris 3", 19442, 200},
/*35*/{"Pared chica marron 1", 19943, 250},
/*35*/{"Pared chica gris 4", 19444, 200},
/*36*/{"Pared chica oscura 1", 19436, 250},
/*37*/{"Pared chica gris 5", 19435, 200},
/*38*/{"Pared chica doble 1", 19434, 300},
/*39*/{"Pared chica doble 2", 19426, 300},
/*40*/{"Pared chica oscura 1", 19427, 250},
/*41*/{"Pared chica gris 6", 19428, 200},
/*42*/{"Pared chica marron 3", 19429, 250},
/*43*/{"Pared chica gris 7", 19430, 200},
/*44*/{"Pared chica doble 3", 19431, 300},
/*44*/{"Pared chica gris 8", 19432, 250},
/*45*/{"Pared grande gris 1", 19447, 750},
/*46*/{"Pared grande cemento 1", 19456, 800},
/*47*/{"Pared grande marron 1", 19462, 800},
/*48*/{"Pared grande cemento 2", 19463, 800},
/*49*/{"Pared grande gris 2", 19455, 750},
/*50*/{"Pared grande doble 1", 19445, 850},
/*51*/{"Pared grande oscura", 19446, 800},
/*52*/{"Pared grande cemento 3", 19457, 750},
/*53*/{"Pared grande madera 1", 19448, 800},
/*54*/{"Pared grande gris 3", 19449, 750},
/*55*/{"Pared grande doble 2", 19450, 850},
/*56*/{"Pared grande gris 4", 19451, 750},
/*57*/{"Pared grande madera 2", 19452, 850},
/*58*/{"Pared grande doble 2", 19453, 900},
/*59*/{"Pared grande gris 5", 19454, 750},
/*60*/{"Pared grande madera 3", 19458, 800},
/*61*/{"Pared grande gris 6", 19461, 750},
/*62*/{"Pared grande cemento 4", 19460, 800},
/*63*/{"Pared grande cemento 5", 19459, 800},
/*64*/{"Pared hueco puerta gris 1", 19387, 400},
/*65*/{"Pared hueco puerta gris 2", 19392, 400},
/*66*/{"Pared hueco puerta franja 1", 19395, 450},
/*67*/{"Pared hueco puerta franja 2", 19389, 450},
/*68*/{"Pared hueco puerta doble 1", 19390, 500},
/*69*/{"Pared hueco puerta gris 3", 19391, 400},
/*70*/{"Pared hueco puerta cemento 1", 19393, 450},
/*71*/{"Pared hueco puerta cemento 2", 19394, 450},
/*72*/{"Pared hueco puerta franja 3", 19395, 450},
/*73*/{"Pared hueco puerta franja 4", 19389, 450},
/*74*/{"Pared hueco puerta doble 2", 19390, 500},
/*75*/{"Pared hueco puerta gris 4", 19391, 400},
/*76*/{"Pared hueco puerta cemento 3", 19393, 450},
/*77*/{"Pared hueco puerta cemento 4", 19394, 450},
/*78*/{"Pared hueco puerta franja 5", 19397, 450},
/*79*/{"Pared hueco puerta franja 6", 19396, 450},
/*80*/{"Pared hueco puerta gris 5", 19398, 400},
/*81*/{"Pared hueco puerta doble 3", 19388, 450},
/*82*/{"Pared hueco puerta gris 6", 19385, 400},
/*83*/{"Pared hueco puerta chica 1", 19465, 400},
/*84*/{"Pared hueco puerta doble 4", 19383, 500},
/*85*/{"Pared hueco puerta oscura 1", 19384, 500},
/*86*/{"Pared hueco puerta madera 1", 19386, 450},
/*87*/{"Pared hueco ventana gris 1", 19411, 400},
/*88*/{"Pared hueco ventana oscura 1", 19400, 450},
/*89*/{"Pared hueco ventana gris 2", 19401, 400},
/*90*/{"Pared hueco ventana madera 1", 19402, 450},
/*91*/{"Pared hueco ventana gris 3", 19403, 400},
/*92*/{"Pared hueco ventana gris 4", 19405, 450},
/*93*/{"Pared hueco ventana doble 1", 19404, 500},
/*94*/{"Pared hueco ventana madera 2", 19406, 500},
/*95*/{"Pared hueco ventana doble 2", 19407, 500},
/*96*/{"Pared hueco ventana gris 5", 19416, 400},
/*97*/{"Pared hueco ventana gris 6", 19408, 400},
/*98*/{"Pared hueco ventana oscura 2", 19409, 450},
/*99*/{"Pared hueco ventana cemento 1", 19410, 450},
/*100*/{"Pared hueco ventana madera 3", 19412, 500},
/*101*/{"Pared hueco ventana franja 1", 19414, 450},
/*102*/{"Pared hueco ventana franja 2", 19415, 450},
/*103*/{"Pared hueco ventana gris 7", 19417, 400},
/*104*/{"Pared hueco ventana franja 3", 19413, 450},
/*105*/{"Puerta Zip", 2875, 300},
/*106*/{"Puerta malla 1", 2664, 300},
/*107*/{"Puerta Train Hard", 2876, 300},
/*108*/{"Puerta verde 1", 1492, 250},
/*109*/{"Puerta reja 1", 19302, 200},
/*110*/{"Puerta malla 2", 14819, 300},
/*111*/{"Puerta D", 2879, 300},
/*112*/{"Puerta c/reja", 3061, 350},
/*113*/{"Puerta reja 2", 19303, 200},
/*114*/{"Puerta local 1", 1532, 300},
/*115*/{"Puerta depto", 19860, 350},
/*116*/{"Puerta verde 2", 2911, 250},
/*117*/{"Puerta amarilla 1", 1507, 350},
/*118*/{"Puerta azul 1", 1505, 350},
/*119*/{"Puerta malla 3", 1493, 300},
/*120*/{"Puerta malla 4", 1495, 300},
/*121*/{"Puerta bordo 1", 2678, 350},
/*122*/{"Puerta local 2", 2948, 300},
/*123*/{"Puerta azul 2", 2947, 350},
/*124*/{"Puerta triple", 2946, 350},
/*125*/{"Puerta escotilla", 2944, 650},
/*126*/{"Puerta bordo 2", 2959, 350},
/*127*/{"Puerta seguridad 1", 3109, 400},
/*128*/{"Puerta bordo 3", 3029, 350},
/*129*/{"Puerta azul 3", 3062, 400},
/*130*/{"Puerta baño H", 2878, 350},
/*131*/{"Puerta malla 5", 2873, 300},
/*132*/{"Puerta oscura 1", 1566, 400},
/*133*/{"Puerta c/vidrio 1", 1569, 450},
/*134*/{"Puerta madera 1", 2877, 350},
/*135*/{"Puerta madera 2", 19802, 350},
/*136*/{"Puerta escotilla 2", 19799, 650},
/*137*/{"Puerta oscura 2", 13360, 400},
/*138*/{"Puerta azul 4", 19875, 400},
/*139*/{"Puerta madera 3", 14638, 350},
/*140*/{"Puerta c/ventana 1", 19857, 400},
/*141*/{"Puerta verde 3", 19858, 350},
/*142*/{"Puerta c/vidrio 2", 19859, 450},
/*143*/{"Puerta madera 3", 977, 350},
/*144*/{"Puerta salmon", 1535, 250},
/*145*/{"Puerta escotilla 3", 2634, 650},
/*146*/{"Puerta local 3", 1561, 350},
/*147*/{"Puerta local 4", 1560, 350},
/*148*/{"Puerta c/vidrio 3", 1557, 450},
/*149*/{"Puerta oscura 2", 1556, 400},
/*150*/{"Puerta oscura 3", 1555, 400},
/*151*/{"Puerta local 5", 1538, 350},
/*152*/{"Puerta gris 1", 1537, 350},
/*153*/{"Puerta c/vidrio 4", 1536, 450},
/*154*/{"Puerta gris 2", 1533, 350},
/*155*/{"Puerta c/ventana 2", 1523, 400},
/*156*/{"Puerta local 6", 1522, 350},
/*157*/{"Puerta gris 3", 1506, 350},
/*158*/{"Puerta roja 1", 1504, 400},
/*159*/{"Puerta madera 4", 1502, 350},
/*160*/{"Puerta doble 1", 1501, 350},
/*161*/{"Puerta c/vidrio 5", 1500, 400},
/*162*/{"Puerta seguridad 2", 1499, 400},
/*163*/{"Puerta c/ventana 3", 1494, 400},
/*164*/{"Puerta seguridad 3", 1497, 500},
/*165*/{"Puerta seguridad 4", 1496, 400},
/*166*/{"Puerta oscura 4", 1494, 350},
/*167*/{"Puerta marron 1", 1491, 400},
/*168*/{"Puerta oscura 5", 3093, 350},
/*169*/{"Puerta seguridad 5", 2949, 400},
/*170*/{"Puerta azul 5", 2970, 300},
/*172*/{"Cristal 1", 19466, 400},
/*173*/{"Cristal 2", 19325, 600},
/*174*/{"Conjunto ventanas", 18072, 1000},
/*175*/{"Cristal 3", 3032, 400},
/*176*/{"Ventana c/marco", 3034, 500}
};

/*----------------------------------------------------------------------------*/

new const M_Frames[][FurnitureInfo] =
{
	/*0*/{"Cuadro 1", 2254, 125},
	/*1*/{"Cuadro 2", 2255, 225},
	/*2*/{"Cuadro 3", 2256, 300},
	/*3*/{"Cuadro 4", 2257, 400},
	/*4*/{"Cuadro 5", 2258, 350},
	/*5*/{"Cuadro 6", 2259, 275},
	/*6*/{"Cuadro 7", 2260, 300},
	/*7*/{"Cuadro 8", 2261, 325},
	/*8*/{"Cuadro 9", 2262, 350},
	/*9*/{"Cuadro 10", 2263, 250},
	/*10*/{"Cuadro 11", 2264, 275},
	/*11*/{"Cuadro 12", 2265, 250},
	/*12*/{"Cuadro 13", 2266, 300},
	/*13*/{"Cuadro 14", 2267, 450},
	/*14*/{"Cuadro 15", 2268, 200},
	/*15*/{"Cuadro 16", 2269, 300},
	/*16*/{"Cuadro 17", 2270, 350},
	/*17*/{"Cuadro 18", 2271, 250},
	/*18*/{"Cuadro 19", 2272, 225},
	/*19*/{"Cuadro 21", 2273, 200},
	/*20*/{"Cuadro 22", 2274, 150},
	/*21*/{"Cuadro 23", 2275, 175},
	/*22*/{"Cuadro 24", 2276, 250},
	/*23*/{"Cuadro 25", 2277, 225},
	/*24*/{"Cuadro 26", 2278, 150},
	/*25*/{"Cuadro 27", 2279, 200},
	/*26*/{"Cuadro 28", 2280, 200},
	/*27*/{"Cuadro 29", 2281, 200},
	/*28*/{"Cuadro 30", 2282, 250},
	/*29*/{"Cuadro 31", 2283, 275},
	/*30*/{"Cuadro 32", 2284, 200},
	/*31*/{"Cuadro 33", 2285, 225},
	/*32*/{"Cuadro 34", 2286, 350},
	/*33*/{"Cuadro 35", 2287, 225},
	/*34*/{"Cuadro 36", 2288, 200},
	/*35*/{"Cuadro 37", 2289, 300},
	/*36*/{"Plano Calígula", 3111, 500},
	/*37*/{"Mapa c/ relieve", 19164, 1000},
	/*38*/{"Mapa grande 1", 19165, 750},
	/*39*/{"Mapa grande 2", 19166, 700},
	/*40*/{"Mapa pequeño", 19167, 500},
	/*41*/{"Mapa grande 1er cuadrante", 19168, 800},
	/*42*/{"Mapa grande 2do cuadrante", 19169, 800},
	/*43*/{"Mapa grande 3er cuadrante", 19170, 800},
	/*44*/{"Mapa grande 4to cuadrante", 19171, 800},
	/*45*/{"Cuadro 38", 19172, 1000},
	/*46*/{"Cuadro 39", 19173, 750},
	/*47*/{"Cuadro 40", 19174, 1000},
	/*48*/{"Cuadro 41", 19175, 1000},
	/*49*/{"Vinilo rosa", 1960, 200},
	/*50*/{"Vinilo verde", 1961, 200},
	/*51*/{"Vinilo azul", 1962, 200},
	/*52*/{"Disco de oro", 19617, 500},
	/*53*/{"Bandera LS 1", 2047, 150},
	/*54*/{"Bandera cruz", 2048, 200},
	/*55*/{"Poster punteria 1", 2049, 150},
	/*56*/{"Poster punteria 2", 2050, 150},
	/*57*/{"Poster punteria 3", 2051, 150},
	/*58*/{"Poster armas", 2055, 200},
	/*59*/{"Poster tiro al blanco", 2056, 100},
	/*60*/{"Red estilo camo", 2068, 500},
	/*61*/{"Bandera USA 1", 2614, 400},
	/*62*/{"Poster 1", 2655, 150},
	/*63*/{"Poster Pro Laps", 2656, 175},
	/*64*/{"Poster Feel the burn", 2657, 175},
	/*65*/{"Poster Homeys Suburban", 2658, 150},
	/*66*/{"Poster Bobo 1", 2659, 200},
	/*67*/{"Poster Mercury", 2660, 150},
	/*68*/{"Poster Heat U", 2661, 150},
	/*69*/{"Poster Bobo 2", 2662, 150},
	/*70*/{"Titulo", 2684, 100},
	/*71*/{"Poster Base 5 tipo 1", 2691, 250},
	/*72*/{"Poster Base 5 tipo 2", 2695, 150},
	/*73*/{"Poster Base 5 tipo 3", 2696, 150},
	/*74*/{"Poster Train Hard", 2697, 150},
	/*75*/{"Pizarra blanca", 19805, 500},
	/*76*/{"Herramientas colgadas", 19815, 800},
	/*77*/{"Gigantografía Heat U", 8332, 3000},
	/*78*/{"Fotografias UFO", 16155, 800},
	/*79*/{"Mascara demonio", 11704, 500},
	/*80*/{"Cruz madera", 11712, 300},
	/*81*/{"Soporte de extintor", 11713, 450},
	/*82*/{"Reloj Sprunk Beer", 19825, 150},
	/*83*/{"Cartel Staff Only", 19810, 100},
	/*84*/{"Abanico Oriental", 19591, 300},
	/*85*/{"Espada Oriental", 19590, 450},
	/*86*/{"Katana de Pared", 19590, 2500}
};

/*----------------------------------------------------------------------------*/

new const M_Kitchen[][FurnitureInfo] =
{
    /*0*/{"Parrilla", 1481, 700},
	/*1*/{"Botella 1", 1486, 40},
	/*2*/{"Botella 2", 1488, 75},
	/*3*/{"Botella 3", 1511, 75},
	/*4*/{"Botella 4", 1512, 90},
	/*5*/{"Botella 5", 1520, 60},
	/*6*/{"Canillas Bar", 1541, 180},
	/*7*/{"Botella 6", 1543, 35},
	/*8*/{"Botella 7", 1544, 40},
	/*9*/{"Canillas Sprunk", 1545, 200},
	/*10*/{"Lata Sprunk", 1546, 25},
	/*11*/{"Alfombra Antideslizante Pissh", 1547, 150},
	/*12*/{"Alfombra Antideslizante Gold", 1548, 200},
	/*13*/{"Gran Botella", 1551, 100},
	/*14*/{"Copa", 1667, 15},
	/*15*/{"Botella 8", 1668, 50},
	/*16*/{"Set Sobremesa 1", 1670, 150},
	/*17*/{"Sprunk Machine", 1775, 1000},
	/*18*/{"Heladera desgastada", 1780, 650},
	/*19*/{"Dispenser agua 1", 1808, 850},
	/*20*/{"Botella 9", 1950, 45},
	/*21*/{"Dispensador de bebidas", 1977, 1100},
	/*22*/{"Dispenser agua 2", 2002, 950},
	/*23*/{"Mesada madera y blanca 1", 2013, 850},
	/*24*/{"Mesada madera y blanca 2", 2014, 650},
	/*25*/{"Mesada madera y blanca 3", 2015, 650},
	/*26*/{"Mesada madera y blanca 4", 2016, 650},
	/*27*/{"Horno madera y blanca", 2017, 1000},
	/*28*/{"Lavadora madera y blanca", 2018, 900},
	/*29*/{"Mesada madera y blanca esquina", 2022, 750},
	/*30*/{"Alacena mesada roja doble", 2127, 950},
	/*31*/{"Alacena mesada roja simple", 2128, 750},
	/*32*/{"Mesada roja 1", 2129, 650},
	/*33*/{"Mesada roja 2", 2130, 700},
	/*34*/{"Horno mesada roja", 2294, 1000},
	/*35*/{"Mesada roja esquina", 2304, 800},
	/*36*/{"Mesada blanca 1", 2133, 700},
	/*37*/{"Mesada blanca 2", 2134, 700},
	/*38*/{"Alacena mesada blanca simple", 2141, 800},
	/*39*/{"Alacena mesada blanca doble", 2131, 1000},
	/*40*/{"Mesada blanca 3", 2132, 750},
	/*41*/{"Mesada blanca 4", 2339, 700},
	/*42*/{"Mesada blanca 5", 2340, 700},
	/*43*/{"Mesada blanca esquina", 2341, 800},
	/*44*/{"Horno Set Deluxe", 2135, 1300},
	/*45*/{"Mesada Set Deluxe 1", 2136, 1100},
	/*46*/{"Lavadora Set Deluxe", 2303, 1200},
	/*47*/{"Mesada Set Deluxe 2", 2137, 1000},
	/*48*/{"Mesada Set Deluxe esquina", 2305, 1100},
	/*49*/{"Mesada Set Deluxe 3", 2138, 1000},
	/*50*/{"Mesada Set Deluxe 4", 2139, 900},
	/*51*/{"Alacena mesada Set Deluxe", 2140, 1050},
	/*52*/{"Mesada buena calidad 2", 2152, 900},
	/*53*/{"Alacena mesada buena calidad", 2153, 950},
	/*54*/{"Mesada buena calidad 3", 2154, 1000},
	/*55*/{"Mesada buena calidad 4", 2155, 900},
	/*56*/{"Mesada buena calidad 1", 2151, 900},
	/*57*/{"Mesada madera y verde 1", 2157, 550},
	/*58*/{"Alacena mesada madera y verde", 2158, 750},
	/*59*/{"Mesada madera y verde 2", 2159, 500},
	/*60*/{"Mesada madera y verde 3", 2160, 550},
	/*61*/{"Mesada madera y verde 4", 2156, 550},
	/*62*/{"Mesada madera y verde 5", 2334, 550},
	/*63*/{"Mesada madera y verde 6", 2335, 550},
	/*64*/{"Mesada madera y verde 7", 2336, 750},
	/*65*/{"Lavadora mesada madera y verde", 2337, 750},
	/*66*/{"Mesada madera y verde esquina", 2338, 650},
	/*67*/{"Horno ordinario", 2144, 600},
	/*68*/{"Lavadora mesada madera ordinaria", 2143, 700},
	/*69*/{"Alacena mesada madera ordinaria simple", 2145, 650},
	/*70*/{"Mesada madera ordinaria 1", 2142, 450},
	/*71*/{"Bandeja comida 1", 2222, 100},
	/*72*/{"Bandeja comida 2", 2223, 100},
	/*73*/{"Bandeja comida 3", 2221, 100},
	/*74*/{"Heladera ordinaria", 2147, 700},
	/*75*/{"Microondas 1", 2149, 550},
	/*76*/{"Conjunto bebida 1", 2342, 50},
	/*77*/{"Frizzer 1", 2360, 900},
	/*78*/{"Frizzer 2", 2361, 1000},
	/*79*/{"Freidora", 2415, 950},
	/*80*/{"Horno industrial", 2417, 1100},
	/*81*/{"Separador hamburguesas", 2416, 800},
	/*82*/{"Mesada industrial 1", 2418, 950},
	/*83*/{"Mesada industrial 2", 2419, 950},
	/*84*/{"Barra metalizada sec. esquina", 2423, 700},
	/*85*/{"Barra metalizada sec. 1", 2424, 600},
	/*86*/{"Dispenser Sprunk 1", 2425, 500},
	/*87*/{"Horno electrico", 2426, 700},
	/*88*/{"Dispenser Sprunk 2", 2427, 600},
	/*89*/{"Barra madera deluxe sec. esquina", 2434, 800},
	/*90*/{"Barra madera deluxe sec. 1", 2435, 700},
	/*91*/{"Barra negra azulejos sec. 1", 2439, 650},
	/*92*/{"Barra negra azulejos sec. esquina", 2440, 750},
	/*93*/{"Barra gris azulejos sec. 1", 2441, 650},
	/*94*/{"Barra gris azulejos sec. esquina", 2442, 750},
	/*95*/{"Barra gris azulejos sec. esquina interior", 2444, 750},
	/*96*/{"Barra gris azulejos sec. 2", 2445, 650},
	/*97*/{"Barra roja sec. 1", 2446, 550},
	/*98*/{"Barra roja sec. 2", 2447, 550},
	/*99*/{"Barra roja sec. 3", 2448, 700},
	/*100*/{"Barra roja sec. 4", 2449, 750},
	/*101*/{"Barra roja sec. esquina", 2450, 750},
	/*102*/{"Plancha industrial", 2451, 1050},
	/*103*/{"Heladera exhibidora Sprunk doble", 2452, 1500},
	/*104*/{"Heladera exhibidora Sprunk", 2443, 1100},
	/*105*/{"Exhibidor pizzas", 2453, 150},
	/*106*/{"Barra azulejos coloridos sec. esquina", 2454, 700},
	/*107*/{"Barra azulejos coloridos sec. 1", 2455, 600},
	/*108*/{"Barra azulejos coloridos sec. 2", 2456, 800},
	/*109*/{"Vaso Burguer Shot", 2647, 30},
	/*110*/{"Conjunto bebida 2", 2683, 50},
	/*111*/{"Caja hamburguesa", 2768, 20},
	/*112*/{"Sandwich", 2769, 30},
	/*113*/{"Bolsa de carne 1", 2803, 150},
	/*114*/{"Carne 1", 2804, 80},
	/*115*/{"Bolsa de carne 2", 2805, 180},
	/*116*/{"Carne 2", 2806, 100},
	/*117*/{"Platos sucios 1", 2812, 30},
	/*118*/{"Caja de pizza", 2814, 15},
	/*119*/{"Platos sucios 2", 2820, 25},
	/*120*/{"Caja de cereal 1", 2821, 20},
	/*121*/{"Vajilla 1", 2822, 45},
	/*122*/{"Conjunto comida 1", 2823, 40},
	/*123*/{"Platos sucios 3", 2829, 35},
	/*124*/{"Platos sucios 4", 2830, 30},
	/*125*/{"Platos sucios 5", 2831, 45},
	/*126*/{"Platos sucios 6", 2832, 45},
	/*127*/{"Conjunto comida 2", 2837, 15},
	/*128*/{"Conjunto comida 3", 2838, 30},
	/*129*/{"Conjunto comida 4", 2839, 25},
	/*130*/{"Conjunto comida 5", 2840, 50},
	/*131*/{"Platos sucios 7", 2848, 35},
	/*132*/{"Platos sucios 8", 2849, 30},
	/*133*/{"Platos sucios 9", 2850, 15},
	/*134*/{"Platos sucios 10", 2851, 20},
	/*135*/{"Cajas de leche", 2856, 10},
	/*136*/{"Conjunto comida 6", 2857, 15},
	/*137*/{"Conjunto comida 7", 2858, 25},
	/*138*/{"Conjunto comida 8", 2859, 15},
	/*139*/{"Conjunto comida 9", 2860, 20},
	/*140*/{"Conjunto comida 10", 2861, 25},
	/*141*/{"Vajilla 2", 2862, 55},
	/*142*/{"Vajilla 3", 2863, 45},
	/*143*/{"Vajilla 4", 2864, 40},
	/*144*/{"Vajilla 5", 2865, 55},
	/*145*/{"Conjunto comida 11", 2866, 25},
	/*146*/{"Conjunto comida 12", 2867, 20},
	/*147*/{"Vasija recipiente", 2870, 80},
	/*148*/{"Hamburguesa", 2880, 15},
	/*149*/{"Conjunto Ollas", 11090, 850},
	/*150*/{"Tacho de basura", 11706, 110},
	/*151*/{"Tenedor", 11715, 25},
	/*152*/{"cuchillo", 11716, 25},
	/*153*/{"Olla 1", 11718, 50},
	/*154*/{"Olla 2", 11719, 50},
	/*155*/{"Condimentos 1", 11722, 15},
	/*156*/{"Condimentos 2", 11723, 15},
	/*157*/{"Cafetera", 11743, 400},
	/*158*/{"Plato individual", 11744, 20},
	/*159*/{"Set cocina con ventanas", 14472, 7000},
	/*160*/{"Set Mesada 1", 15036, 6500},
	/*161*/{"Juego competo de barra", 16151, 4000},
	/*162*/{"Calabaza", 19320, 300},
	/*163*/{"Pancho", 19346, 50},
	/*164*/{"Gran torta", 19525, 350},
	/*165*/{"Caldero", 19527, 400},
	/*166*/{"Bandeja de carne", 19560, 50},
	/*167*/{"Cereal 1", 19561, 30},
	/*168*/{"Cereal 2", 19562, 30},
	/*169*/{"Jugo 1", 19563, 25},
	/*170*/{"Jugo 2", 19564, 25},
	/*171*/{"Caja de helado ", 19565, 50},
	/*172*/{"Caja de merluza", 19566, 60},
	/*173*/{"Pote de helado 1", 19567, 50},
	/*174*/{"Pote de helado 2", 19568, 50},
	/*175*/{"Leche 1", 19569, 30},
	/*176*/{"Botella de leche", 19570, 25},
	/*177*/{"Pack de cervezas", 19572, 80},
	/*178*/{"Carbon", 19573, 50},
	/*179*/{"Naranja", 19574, 10},
	/*180*/{"Manzana roja", 19575, 10},
	/*181*/{"Manzana verde", 19576, 10},
	/*182*/{"Tomate", 19577, 15},
	/*183*/{"Banana", 19578, 15},
	/*184*/{"Pan", 19579, 10},
	/*185*/{"Pizza", 19580, 15},
	/*186*/{"Sarten", 19581, 50},
	/*187*/{"Pedazo de carne", 19582, 60},
	/*188*/{"Cuchillo de cocina", 19583, 55},
	/*189*/{"Olla 4", 19584, 70},
	/*190*/{"Cacerola", 19585, 60},
	/*191*/{"Espatula", 19586, 55},
	/*192*/{"Caja de manzanas rojas", 19636, 110},
	/*193*/{"Caja de manzanas verdes", 19637, 110},
	/*194*/{"Caja de naranjas", 19638, 110},
	/*195*/{"Caja vacia", 19639, 80},
	/*196*/{"Barril de cerveza", 19812, 500},
	/*197*/{"Botella 10", 19820, 60},
	/*198*/{"Botella 11", 19821, 65},
	/*199*/{"Botella 12", 19822, 70},
	/*200*/{"Licuadora", 19830, 550},
	/*201*/{"Parrilla roja", 19831, 850},
	/*202*/{"Jamón de cerdo", 19847, 150},
	/*203*/{"Bife de cerdo", 19882, 100},
	/*204*/{"Tostada", 19883, 15},
	/*205*/{"Cocina blanca", 19915, 1000},
	/*206*/{"Heladera moderna", 19916, 1200},
	/*207*/{"Cocina modular", 19923, 1500},
	/*208*/{"Estractor", 19924, 600},
	/*209*/{"Mesada madera oscura esquina 1", 19925, 700},
	/*210*/{"Mesada madera oscura 1", 19926, 850},
	/*211*/{"Mesada madera oscura 2", 19927, 850},
	/*212*/{"Mesada madera oscura 3", 19928, 700},
	/*213*/{"Mesada madera oscura 4", 19929, 850},
	/*214*/{"Mesada madera oscura 5", 19930, 700},
	/*215*/{"Mesada madera oscura 6", 19931, 700},
	/*216*/{"Alacena mesada madera oscura 1", 19932, 950},
	/*217*/{"Alacena mesada madera oscura 2", 19937, 900},
	/*218*/{"Alacena mesada madera oscura 3", 19934, 700},
	/*219*/{"Alacena mesada madera oscura 4", 19935, 700},
	/*220*/{"Mesada madera oscura esquina 2", 19936, 700},
	/*221*/{"Mesada s/ bajo mesada madera oscura 1", 19940, 650},
	/*222*/{"Mesada s/ bajo mesada madera oscura 2", 19938, 450},
	/*223*/{"Mesada s/ bajo mesada madera oscura 3", 19939, 550},
	/*224*/{"Horno moderno", 19933, 1200},
	/*225*/{"Vajilla 5", 19993, 30}
};

/*----------------------------------------------------------------------------*/

new const M_Electronics[][FurnitureInfo] =
{
	/*0*/{"TV normal 1", 1518, 800},
	/*1*/{"TV antigua 1", 1747, 500},
	/*2*/{"TV antigua 2", 1748, 450},
	/*3*/{"TV cuadrada 1", 1749, 650},
	/*4*/{"TV antigua 3", 1750, 500},
	/*5*/{"TV antigua 4", 1751, 550},
	/*6*/{"TV normal 2", 1752, 850},
	/*7*/{"TV antigua 5", 1781, 500},
	/*8*/{"TV normal 3", 1786, 1000},
	/*9*/{"TV normal 4", 1791, 700},
	/*10*/{"TV normal curved", 1792, 900},
	/*11*/{"TV Supersonicos", 2224, 850},
	/*12*/{"Mueble con TV y video 1", 2296, 1500},
	/*13*/{"Mueble con TV y video 2", 2297, 1200},
	/*14*/{"TV y video", 2595, 800},
	/*15*/{"TV c/ soporte pared", 2596, 650},
	/*16*/{"Carro c/ TV y video", 14532, 700},
	/*17*/{"LED TV grande", 19786, 5000},
	/*18*/{"LED TV mediano", 19787, 3500},
	/*19*/{"TV c/ mesa", 1717, 1000},
	/*20*/{"Video blanca 1", 1782, 370},
	/*21*/{"Video negra 1", 1783, 500},
	/*22*/{"Video blanca 2", 1785, 450},
	/*23*/{"Video negra 2", 1787, 500},
	/*24*/{"Video negra 3", 1788, 550},
	/*25*/{"Video negra 4", 1790, 600},
	/*26*/{"PC 1", 2190, 800},
	/*27*/{"Notebook 1", 19893, 3000},
	/*28*/{"Notebook 2", 19894, 3000},
	/*29*/{"Parlante gris", 1840, 350},
	/*30*/{"Parlante columna negro y amarillo", 2229, 800},
	/*31*/{"Parlante columna estilo clasico", 2230, 700},
	/*32*/{"Parlante estilo clasico", 2231, 650},
	/*33*/{"Parlante deluxe negro", 2232, 950},
	/*34*/{"Parlante columna blanco", 2233, 750},
	/*35*/{"Potencias Stereo 1", 1809, 500},
	/*36*/{"Equipo de musica 1", 2099, 1000},
	/*37*/{"Equipo de musica 2", 2100, 1050},
	/*38*/{"Equipo de musica portatil 1", 2102, 500},
	/*39*/{"Equipo de musica portatil 2", 2103, 550},
	/*40*/{"Potencias encolumnadas", 2104, 700},
	/*41*/{"Mesa con potencias", 2225, 500},
	/*42*/{"Equipo de musica portatil 3", 2226, 600},
	/*43*/{"Pilar con potencias", 2227, 450},
	/*44*/{"Identificador de seguridad 1", 2886, 500},
	/*45*/{"Identificador de seguridad 2", 2922, 450},
	/*46*/{"Teclado", 19808, 100},
	/*47*/{"Telefono fijo", 19807, 200},
	/*48*/{"Enchufes 1", 19813, 50},
	/*49*/{"Enchufes 2", 19814, 50},
	/*50*/{"Tecla de luz 1", 19826, 75},
	/*51*/{"Tecla de luz 2", 19827, 75},
	/*52*/{"Tecla de luz 3", 19828, 75},
	/*53*/{"Caja registradora 1", 1514, 600},
	/*54*/{"Caja registradora 2", 2422, 700},
	/*55*/{"Auriculares blancos", 19421, 200},
	/*56*/{"Auriculares negros", 19422, 200},
	/*57*/{"Auriculares rosas", 19423, 200},
	/*58*/{"Auriculares azules", 19424, 200},
	/*59*/{"Microfono", 19610, 500},
	/*60*/{"Pie de microfono", 19611, 100},
	/*61*/{"Radar", 16782, 900},
	/*62*/{"Consola de control", 9819, 6500},
	/*63*/{"Amplificador 1", 19612, 1000},
	/*64*/{"Amplificador 2", 19613, 1500},
	/*65*/{"Amplificador 3", 19614, 1250},
	/*66*/{"Amplificador 4", 19615, 950},
	/*67*/{"Amplificador 5", 19616, 1300},
	/*68*/{"Cámara de fotos", 19623, 400},
	/*69*/{"Ordenador mecanico", 19903, 1000},
	/*70*/{"Fotocopiadora 1", 2202, 1050},
	/*71*/{"Fotocopiadora 2", 2186, 1000}
};

/*----------------------------------------------------------------------------*/

new const M_Entertainment[][FurnitureInfo] =
{
	/*0*/{"Bolsa Boxeo",1985 ,500},
	/*1*/{"Disco 5kg",1945 ,320},
	/*2*/{"Colchoneta Roja",2631 ,250},
	/*3*/{"Colchoneta Verde",2632 ,250},
	/*4*/{"Caminadora",2627 ,1900},
	/*5*/{"Multifuncion",2628 ,1500},
	/*6*/{"Bench Press",2629 ,950},
	/*7*/{"Bicicleta fija",2630 ,800},
	/*8*/{"GymLocker Abierto",11730 ,600},
	/*9*/{"GymLocker Cerrado",11729 ,600},
	/*10*/{"Tragamonedas 1",1835 ,1700},
	/*11*/{"Tragamonedas",1838 ,1700},
	/*12*/{"Stack Fichas",1879 ,100},
	/*13*/{"Stack Fichas 2",1880 ,100},
	/*14*/{"Ficha 1",1861 ,70},
	/*15*/{"Ficha 2",1862 ,70},
	/*16*/{"Mesa Blackjack",2188 ,1000},
	/*17*/{"Mesa de Poker",19474 ,1100},
	/*18*/{"Mesa con Ruleta",19478 ,1300},
	/*19*/{"Maquina Arcade",2779 ,1700},
	/*20*/{"Mesa de Pool",2964 ,1100},
	/*21*/{"Mesa Pool y Palos",14651 ,1250},
	/*22*/{"Palo de pool",338 ,200},
	/*23*/{"Palo de pool 2",3004 ,200},
	/*24*/{"Pelota pool",3106 ,200},
	/*25*/{"Pelota pool 2",3105 ,70},
	/*26*/{"Pelota pool 3",3003 ,70},
	/*27*/{"Pelota pool 4",3002 ,70},
	/*28*/{"Pelota pool 5",3000 ,70},
	/*29*/{"Triangulo pool",2965 ,100},
	/*30*/{"Guante Boxeo",19556 ,250},
	/*31*/{"Pelota de Golf",1974 ,60},
	/*32*/{"Bate Baseball",19914 ,200},
	/*33*/{"Replica M4",2035 ,3200},
	/*34*/{"Replica SMG",2035 ,2900},
	/*34*/{"Replica Revolver",2034 ,1000},
	/*36*/{"Replica Sniper",2036 ,3500},
	/*37*/{"Replica Rifle",357 ,3000},
	/*38*/{"Espada Japonesa",19590 ,890},
	/*39*/{"Caja logo armas",3014 ,350},
	/*40*/{"Caña de pesca",18632 ,200},
	/*41*/{"Guitarra 1",19317 ,1200},
	/*42*/{"Guitarra 2",19318 ,1200},
	/*43*/{"Guitarra 3",19319 ,1200},
	/*44*/{"Tablero de Basket", 3497, 650},
	/*45*/{"Bateria", 19609, 4000},
	/*46*/{"Escenario", 19608, 5000},
	/*47*/{"Skate", 19878, 250},
	/*48*/{"Bola de boliche", 19159, 750},
	/*49*/{"Arbol de Navidad", 19076, 950},
	/*50*/{"Pelota de Basket", 1946, 150},
	/*51*/{"Pelota de playa", 1598, 100},
	/*52*/{"Tablero de Basket con pie", 3496, 860}
};

/*----------------------------------------------------------------------------*/

new const M_Misc[][FurnitureInfo] =
{
	/*0*/{"Esposas", 11749, 150},
	/*1*/{"Celular 1", 18872, 700},
	/*2*/{"Celular 2", 18874, 700},
	/*3*/{"Celular 3", 18870, 700},
	/*4*/{"Candado", 19804, 150},
	/*5*/{"Picana", 18642, 300},
	/*6*/{"Crucifijo", 11712, 150},
	/*7*/{"Estanteria herramientas",19899 ,700},
	/*8*/{"Walkie takie", 19942, 400},
	/*9*/{"Balas", 2061, 700},
	/*10*/{"Maletin", 1210, 800},
	/*11*/{"Leña", 19632, 250},
	/*12*/{"Matafuegos", 2690, 450},
	/*13*/{"Mochila Viaje", 19559 , 400},
	/*14*/{"Garrafa", 918, 300},
	/*15*/{"Basurero 1", 1359, 215},
	/*16*/{"Basurero 2", 1330, 215},
	/*17*/{"Silla de ruedas", 932, 850},
	/*18*/{"Caja Regalo", 19054, 150},
	/*19*/{"Rollo cable", 933, 370},
	/*20*/{"Mapa de la ciudad", 19167, 100},
	/*21*/{"Paquete Naranja", 1576, 450},
	/*22*/{"Bolsa negra", 1264, 200},
	/*23*/{"Mochila paracaidas", 1310, 560},
	/*24*/{"Caja Regalo 2", 19056, 200},
	/*25*/{"Servidor", 3388, 950},
	/*26*/{"Cajas",1438 ,300},
	/*27*/{"Cajas 2",3006 ,300},
	/*28*/{"Cajas grandes",2971 ,370},
	/*29*/{"Piso disco",19129 ,2000},
	/*30*/{"Bandera Roja",19306 ,250},
	/*31*/{"Bandera azul",19307 ,250},
	/*32*/{"Kit Herramientas pared",19815 ,450},
	/*33*/{"Tarjeta",1581 ,70},
	/*34*/{"Chaleco Reflect",19904 ,310},
	/*35*/{"Caja cervezas",19572 ,150},
	/*36*/{"Controlador",19273 ,700},
	/*37*/{"Bidon",1650 ,250},
	/*38*/{"Destornillador",18644 ,100},
	/*39*/{"Chaleco antibalas",1242 ,3200},
	/*40*/{"Luz amarilla",19143 ,990},
	/*41*/{"Luz Verde",19145 ,990},
	/*42*/{"Luz Violeta",19153 ,990},
	/*43*/{"Luz Roja",19148 ,990},
	/*44*/{"Luz Azul",19146 ,990},
	/*45*/{"Paquete verde",1578 ,450},
	/*46*/{"Paquete azul",1579 ,450},
	/*47*/{"Paquete rojo",1580 ,450},
	/*48*/{"Paquete blanco",1575 ,450},
	/*49*/{"Caja armas cerrada",3791 ,1200},
	/*50*/{"Caja armas vacia",3788 ,1200},
	/*51*/{"Carrito",1572 ,300},
	/*52*/{"Botiquin",11738 ,550},
	/*53*/{"Mini botiquin",11736 ,300},
	/*54*/{"Replica billetes",1212 ,800},
	/*55*/{"Destornillador",18644 ,90},
	/*56*/{"Martillo",18635 ,90},
	/*57*/{"Martillo 2",19631 ,90},
	/*58*/{"Caja de herramientas",19921 ,600}
};

/*----------------------------------------------------------------------------*/

enum BoxInfo {
	PlayerText:bBoxTD,
	PlayerText:bDescTD,
	bModel,
	bDesc[32]
}

enum CatalogoInfo {
	PlayerText:cTitleTD,
	PlayerText:cPageTD,
	PlayerText:cPreviousTD,
	PlayerText:cNextTD,
	PlayerText:cBackgroundTD,
	PlayerText:cCloseTD,
	cID,
	cTitle[64],
	cTotalElements,
	cCurrentPage,
	cTotalPages
}

new Catalogo[MAX_PLAYERS][CatalogoInfo],
	Catalogo_Box[MAX_PLAYERS][10][BoxInfo];


Catalogo_CreateTextdraws(playerid)
{
	// Fondo
	Catalogo[playerid][cBackgroundTD] = CreatePlayerTextDraw(playerid, 78.000000, 118.000000, "box");
	PlayerTextDrawLetterSize(playerid, Catalogo[playerid][cBackgroundTD], 0.000000, 23.850000);
	PlayerTextDrawTextSize(playerid, Catalogo[playerid][cBackgroundTD], 552.000000, 0.000000);
	PlayerTextDrawUseBox(playerid, Catalogo[playerid][cBackgroundTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo[playerid][cBackgroundTD], -926365666);
	// Título
	Catalogo[playerid][cTitleTD] = CreatePlayerTextDraw(playerid, 314.500000, 97.000000, "Titulo de prueba");
	PlayerTextDrawLetterSize(playerid, Catalogo[playerid][cTitleTD], 0.640999, 2.702500);
	PlayerTextDrawAlignment(playerid, Catalogo[playerid][cTitleTD], 2);
	PlayerTextDrawSetOutline(playerid, Catalogo[playerid][cTitleTD], 1);
	PlayerTextDrawFont(playerid, Catalogo[playerid][cTitleTD], 0);
	// Siguiente
	Catalogo[playerid][cNextTD] = CreatePlayerTextDraw(playerid, 523.000000, 310.000000, "LD_beat:right");
	PlayerTextDrawTextSize(playerid, Catalogo[playerid][cNextTD], 25.500000, 21.312500);
	PlayerTextDrawFont(playerid, Catalogo[playerid][cNextTD], 4);
	PlayerTextDrawSetSelectable(playerid, Catalogo[playerid][cNextTD], true);
    // Anterior
	Catalogo[playerid][cPreviousTD] = CreatePlayerTextDraw(playerid, 85.000000, 310.000000, "LD_beat:left");
	PlayerTextDrawLetterSize(playerid, Catalogo[playerid][cPreviousTD], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, Catalogo[playerid][cPreviousTD], 25.500000, 21.312500);
	PlayerTextDrawFont(playerid, Catalogo[playerid][cPreviousTD], 4);
	PlayerTextDrawSetSelectable(playerid, Catalogo[playerid][cPreviousTD], true);
	// Página actual
	Catalogo[playerid][cPageTD] = CreatePlayerTextDraw(playerid, 314.500000, 312.000000, "Pagina 1 de 20");
	PlayerTextDrawLetterSize(playerid, Catalogo[playerid][cPageTD], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, Catalogo[playerid][cPageTD], 2);
	PlayerTextDrawColor(playerid, Catalogo[playerid][cPageTD], 255);
	PlayerTextDrawFont(playerid, Catalogo[playerid][cPageTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo[playerid][cPageTD], 0);
	// Boton de cerrar
	Catalogo[playerid][cCloseTD] = CreatePlayerTextDraw(playerid, 506.000000, 118.0, "Cerrar");
	PlayerTextDrawLetterSize(playerid, Catalogo[playerid][cCloseTD], 0.289499, 0.668127);
	PlayerTextDrawTextSize(playerid, Catalogo[playerid][cCloseTD], 552.5, 9.0);
	PlayerTextDrawUseBox(playerid, Catalogo[playerid][cCloseTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo[playerid][cCloseTD], 255);
	PlayerTextDrawSetShadow(playerid, Catalogo[playerid][cCloseTD], 0);
	PlayerTextDrawBackgroundColor(playerid, Catalogo[playerid][cCloseTD], 255);
	PlayerTextDrawFont(playerid, Catalogo[playerid][cCloseTD], 2);
	PlayerTextDrawSetSelectable(playerid, Catalogo[playerid][cCloseTD], true);
	// Box 0
	Catalogo_Box[playerid][0][bBoxTD] = CreatePlayerTextDraw(playerid, 80.000000, 126.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][0][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][0][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][0][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][0][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][0][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 1
	Catalogo_Box[playerid][1][bBoxTD] = CreatePlayerTextDraw(playerid, 175.000000, 126.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][1][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][1][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][1][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][1][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][1][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 2
	Catalogo_Box[playerid][2][bBoxTD] = CreatePlayerTextDraw(playerid, 270.000000, 126.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][2][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][2][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][2][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][2][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][2][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 3
	Catalogo_Box[playerid][3][bBoxTD] = CreatePlayerTextDraw(playerid, 365.000000, 126.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][3][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][3][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][3][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][3][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][3][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 4
	Catalogo_Box[playerid][4][bBoxTD] = CreatePlayerTextDraw(playerid, 460.000000, 126.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][4][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][4][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][4][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][4][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][4][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 5
	Catalogo_Box[playerid][5][bBoxTD] = CreatePlayerTextDraw(playerid, 80.000000, 219.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][5][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][5][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][5][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][5][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][5][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 6
	Catalogo_Box[playerid][6][bBoxTD] = CreatePlayerTextDraw(playerid, 175.000000, 219.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][6][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][6][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][6][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][6][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][6][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 7
	Catalogo_Box[playerid][7][bBoxTD] = CreatePlayerTextDraw(playerid, 270.000000, 219.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][7][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][7][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][7][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][7][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][7][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 8
	Catalogo_Box[playerid][8][bBoxTD] = CreatePlayerTextDraw(playerid, 365.000000, 219.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][8][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][8][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][8][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][8][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][8][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
    // Box 9
	Catalogo_Box[playerid][9][bBoxTD] = CreatePlayerTextDraw(playerid, 460.000000, 219.000000, " ");
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][9][bBoxTD], 90.000000, 90.000000);
	PlayerTextDrawBackgroundColor(playerid, Catalogo_Box[playerid][9][bBoxTD], 6921529);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][9][bBoxTD], 5);
	PlayerTextDrawSetSelectable(playerid, Catalogo_Box[playerid][9][bBoxTD], true);
	PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][9][bBoxTD], 10.000000, 0.000000, 230.000000, 1.400000);
	// Desc 0
	Catalogo_Box[playerid][0][bDescTD] = CreatePlayerTextDraw(playerid, 125.000000, 204.875000, "$1000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][0][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][0][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][0][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][0][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][0][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][0][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][0][bDescTD], 0);
	// Desc 1
	Catalogo_Box[playerid][1][bDescTD] = CreatePlayerTextDraw(playerid, 220.000000, 204.875000, "$2000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][1][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][1][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][1][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][1][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][1][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][1][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][1][bDescTD], 0);
	// Desc 2
	Catalogo_Box[playerid][2][bDescTD] = CreatePlayerTextDraw(playerid, 315.000000, 204.875000, "$3000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][2][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][2][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][2][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][2][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][2][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][2][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][2][bDescTD], 0);
    // Desc 3
	Catalogo_Box[playerid][3][bDescTD] = CreatePlayerTextDraw(playerid, 410.000000, 204.875000, "$4000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][3][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][3][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][3][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][3][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][3][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][3][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][3][bDescTD], 0);
    // Desc 4
	Catalogo_Box[playerid][4][bDescTD] = CreatePlayerTextDraw(playerid, 505.000000, 204.875000, "$5000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][4][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][4][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][4][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][4][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][4][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][4][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][4][bDescTD], 0);
    // Desc 5
	Catalogo_Box[playerid][5][bDescTD] = CreatePlayerTextDraw(playerid, 125.000000, 298.062500, "$6000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][5][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][5][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][5][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][5][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][5][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][5][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][5][bDescTD], 0);
    // Desc 6
	Catalogo_Box[playerid][6][bDescTD] = CreatePlayerTextDraw(playerid, 220.000000, 298.062500, "$7000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][6][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][6][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][6][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][6][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][6][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][6][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][6][bDescTD], 0);
    // Desc 7
	Catalogo_Box[playerid][7][bDescTD] = CreatePlayerTextDraw(playerid, 315.000000, 298.062500, "$8000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][7][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][7][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][7][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][7][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][7][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][7][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][7][bDescTD], 0);
    // Desc 8
	Catalogo_Box[playerid][8][bDescTD] = CreatePlayerTextDraw(playerid, 410.000000, 298.062500, "$9000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][8][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][8][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][8][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][8][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][8][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][8][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][8][bDescTD], 0);
    // Desc 9
	Catalogo_Box[playerid][9][bDescTD] = CreatePlayerTextDraw(playerid, 505.000000, 298.062500, "$10000");
	PlayerTextDrawLetterSize(playerid, Catalogo_Box[playerid][9][bDescTD], 0.198499, 1.039999);
	PlayerTextDrawTextSize(playerid, Catalogo_Box[playerid][9][bDescTD], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, Catalogo_Box[playerid][9][bDescTD], 2);
	PlayerTextDrawUseBox(playerid, Catalogo_Box[playerid][9][bDescTD], 1);
	PlayerTextDrawBoxColor(playerid, Catalogo_Box[playerid][9][bDescTD], 90);
	PlayerTextDrawFont(playerid, Catalogo_Box[playerid][9][bDescTD], 2);
	PlayerTextDrawSetShadow(playerid, Catalogo_Box[playerid][9][bDescTD], 0);
}

Catalogo_SetID(playerid, id)
{
    Catalogo[playerid][cID] = id;
}

Catalogo_GetID(playerid)
{
    return Catalogo[playerid][cID];
}

Catalogo_SetBoxModel(playerid, box, model)
{
	Catalogo_Box[playerid][box][bModel] = model;
    PlayerTextDrawSetPreviewModel(playerid, Catalogo_Box[playerid][box][bBoxTD], model);
    new rand = random(361);
    PlayerTextDrawSetPreviewRot(playerid, Catalogo_Box[playerid][box][bBoxTD], -10.0, 0.0, rand, 1.0);
}

Catalogo_SetBoxDesc(playerid, box, desc[])
{
    format(Catalogo_Box[playerid][box][bDesc], 32, "%s", desc);
    PlayerTextDrawSetString(playerid, Catalogo_Box[playerid][box][bDescTD], desc);
}

Catalogo_SetTitle(playerid, title[])
{
	format(Catalogo[playerid][cTitle], 64, "%s", title);
	PlayerTextDrawSetString(playerid, Catalogo[playerid][cTitleTD], title);
}

Catalogo_SetTotalElements(playerid, elements)
{
    Catalogo[playerid][cTotalElements] = elements;
}

Catalogo_GetTotalElements(playerid)
{
	return Catalogo[playerid][cTotalElements];
}

Catalogo_SetTotalPages(playerid, pages)
{
	new string[32];
	Catalogo[playerid][cTotalPages] = pages;
	format(string, 32, "Pagina %d de %d", Catalogo_GetCurrentPage(playerid), pages);
	PlayerTextDrawSetString(playerid, Catalogo[playerid][cPageTD], string);
}

Catalogo_SetCurrentPage(playerid, page)
{
	new string[32];
	Catalogo[playerid][cCurrentPage] = page;
	format(string, 32, "Página %d de %d", page, Catalogo_GetTotalPages(playerid));
	PlayerTextDrawSetString(playerid, Catalogo[playerid][cPageTD], string);
}

Catalogo_GetCurrentPage(playerid)
{
	return Catalogo[playerid][cCurrentPage];
}

Catalogo_GetTotalPages(playerid)
{
	return Catalogo[playerid][cTotalPages];
}

Catalogo_ShowForPlayer(playerid)
{
    PlayerTextDrawShow(playerid, Catalogo[playerid][cTitleTD]);
    PlayerTextDrawShow(playerid, Catalogo[playerid][cPageTD]);
    PlayerTextDrawShow(playerid, Catalogo[playerid][cPreviousTD]);
    PlayerTextDrawShow(playerid, Catalogo[playerid][cNextTD]);
    PlayerTextDrawShow(playerid, Catalogo[playerid][cBackgroundTD]);
    PlayerTextDrawShow(playerid, Catalogo[playerid][cCloseTD]);
    for(new i = 0; i < 10; i++)
    {
        if(Catalogo_Box[playerid][i][bModel] != 0)
        {
        	PlayerTextDrawShow(playerid, Catalogo_Box[playerid][i][bBoxTD]);
        	PlayerTextDrawShow(playerid, Catalogo_Box[playerid][i][bDescTD]);
		}
    }
}

Catalogo_HideForPlayer(playerid)
{
    PlayerTextDrawHide(playerid, Catalogo[playerid][cTitleTD]);
    PlayerTextDrawHide(playerid, Catalogo[playerid][cPageTD]);
    PlayerTextDrawHide(playerid, Catalogo[playerid][cPreviousTD]);
    PlayerTextDrawHide(playerid, Catalogo[playerid][cNextTD]);
    PlayerTextDrawHide(playerid, Catalogo[playerid][cBackgroundTD]);
    PlayerTextDrawHide(playerid, Catalogo[playerid][cCloseTD]);
    for(new i = 0; i < 10; i++)
    {
        PlayerTextDrawHide(playerid, Catalogo_Box[playerid][i][bBoxTD]);
        PlayerTextDrawHide(playerid, Catalogo_Box[playerid][i][bDescTD]);
    }
}

// PUEDE PSARLE X PARAMENTRO UN ARRAY QUE CONTENGA LAS POSICIONES ORDENADAS DEL ARRAY DE ITEMS, Y DE AHI SACAR MODELO Y PRECIO

Mesas_Sillas_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_MESAS_SILLAS);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Mesas_Sillas));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Mesas y Sillas");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Mesas_Sillas[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Mesas_Sillas[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Camas_Mesas_Arm_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_CAMAS_MESAS_ARM);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Camas_Mesas_Arm));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Mobiliario Dormitorio");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Camas_Mesas_Arm[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Camas_Mesas_Arm[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Iluminacion_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_ILUMINACION);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Iluminacion));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Iluminacion");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Iluminacion[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Iluminacion[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Frames_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_FRAMES);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Frames));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Cuadros y otros");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Frames[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Frames[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Bath_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_BATH);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Bath));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Baño y Fontaneria");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Bath[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Bath[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Construction_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_CONSTRUCTION);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Construction));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Construccion");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Construction[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Construction[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Kitchen_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_KITCHEN);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Kitchen));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Cocina");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Kitchen[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Kitchen[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Electronics_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_ELECTRONICS);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Electronics));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Electronica");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Electronics[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Electronics[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Entertainment_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_ENTERTAINMENT);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Entertainment));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Entretenimiento");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Entertainment[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Entertainment[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

Misc_ShowCatalogPage(playerid, page)
{
    new string[32],
        furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_MISC);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, sizeof(M_Misc));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Miscelaneos");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, M_Misc[furnitureArrayPos][ObjectModel]);
			format(string, sizeof(string), "$%d", M_Misc[furnitureArrayPos][Price]);
			Catalogo_SetBoxDesc(playerid, i, string);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}

/*------------------------------------------------------------------------------*/

stock CreateFurnitureObject(playerid, modelid)
{
	new objectid = modelid;
	new Float:x,
	    Float:y,
	    Float:z,
		HouseID;
    HouseID = GetPlayerHouse(playerid);
	GetPlayerPos(playerid, x, y, z);

	new j = -1;
	for(new i = 0; i < MAX_HOUSE_FURNITURES; i++)
	{
	    if(HouseFurnitures[HouseID][i][fObjectModel] == 0)
	    {
 			j = i;
		 	break;
		}
	}
	if(j == -1)
	    return SendClientMessage(playerid, -1, "[ERROR] Has alcanzado el máximo de objetos permitidos en tu casa");
	HouseFurnitures[HouseID][j][fObjectModel] = objectid;
	HouseFurnitures[HouseID][j][fX] = x+2;
	HouseFurnitures[HouseID][j][fY] = y;
	HouseFurnitures[HouseID][j][fZ] = z;
	HouseFurnitures[HouseID][j][fRX] = 0.0;
	HouseFurnitures[HouseID][j][fRY] = 0.0;
	HouseFurnitures[HouseID][j][fRZ] = 0.0;
	HouseFurnitures[HouseID][j][fObjectID] = CreateDynamicObject(objectid, x+1, y, z, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	totalFurnitureObjects ++;
	furnitureObjectSelection[playerid] = 0;
	furniturePriceObjectSelection[playerid] = 0;
	SendClientMessage(playerid, -1, "¡Mueble comprado! Camina para cargar el objeto y espera unos segundos para poder editarlo.");
	new Float: Px,
		Float: Py,
		Float: Pz;
	GetPlayerPos(playerid, Px, Py, Pz);
	SetPlayerPos(playerid, Px+0.05, Py, Pz);
	currentFurnitureEdit[playerid] = j;
	
	SaveFurniture(HouseID, j, DB_FURNITURE_CREATE);
	
 	SetTimerEx("EditarMueble", 2000, false, "ii", playerid, HouseFurnitures[HouseID][j][fObjectID]);
 	return 1;
}

public EditarMueble(playerid, objectid)
{
    EditDynamicObject(playerid, objectid);
    //aca se deberia guardar las cosas, supongo
    return 1;
}

Furniture_GetTotalElements(houseid)// Devuelve la cantidad de muebles que tiene el array (Se supone que gracias a Furniture_DeleteFromHouse todas las posiciones anteriores al último elemento están ocupadas)
{
	for(new i = (MAX_HOUSE_FURNITURES - 1); i >= 0; i--) // Desde la ultima posición
	{
	    if(HouseFurnitures[houseid][i][fObjectID] != 0) // Buscamos el último elemento. Retornamos slot + 1 (Pq es cantidad de elementos)
		{
		    return i + 1;
		}
	}
	return 0;
}

//==============================================================================

// Quita un mueble del array, reemplazandolo en su lugar con el de la última posición (ninguno en caso de ser el único elemento existente)

Furniture_DeleteFromHouse(houseid, slot)
{
    DestroyDynamicObject(HouseFurnitures[houseid][slot][fObjectID]);

	HouseFurnitures[houseid][slot][fObjectID] = 0;
	HouseFurnitures[houseid][slot][fObjectModel] = 0;
	HouseFurnitures[houseid][slot][fX] = 0.0;
	HouseFurnitures[houseid][slot][fY] = 0.0;
	HouseFurnitures[houseid][slot][fZ] = 0.0;
	HouseFurnitures[houseid][slot][fRX] = 0.0;
	HouseFurnitures[houseid][slot][fRY] = 0.0;
	HouseFurnitures[houseid][slot][fRZ] = 0.0;

   	new lastElementPos = Furniture_GetTotalElements(houseid) - 1;
   	if(lastElementPos > 0 && lastElementPos > slot)
    {
	    HouseFurnitures[houseid][slot][fObjectID] = HouseFurnitures[houseid][lastElementPos][fObjectID];
		HouseFurnitures[houseid][slot][fObjectModel] = HouseFurnitures[houseid][lastElementPos][fObjectModel];
		HouseFurnitures[houseid][slot][fX] = HouseFurnitures[houseid][lastElementPos][fX];
		HouseFurnitures[houseid][slot][fY] = HouseFurnitures[houseid][lastElementPos][fY];
		HouseFurnitures[houseid][slot][fZ] = HouseFurnitures[houseid][lastElementPos][fZ];
		HouseFurnitures[houseid][slot][fRX] = HouseFurnitures[houseid][lastElementPos][fRX];
		HouseFurnitures[houseid][slot][fRY] = HouseFurnitures[houseid][lastElementPos][fRY];
		HouseFurnitures[houseid][slot][fRZ] = HouseFurnitures[houseid][lastElementPos][fRZ];
		
		SaveFurniture(houseid, slot, DB_FURNITURE_UPDATE);

		HouseFurnitures[houseid][lastElementPos][fObjectID] = 0;
		HouseFurnitures[houseid][lastElementPos][fObjectModel] = 0;
		HouseFurnitures[houseid][lastElementPos][fX] = 0.0;
		HouseFurnitures[houseid][lastElementPos][fY] = 0.0;
		HouseFurnitures[houseid][lastElementPos][fZ] = 0.0;
		HouseFurnitures[houseid][lastElementPos][fRX] = 0.0;
		HouseFurnitures[houseid][lastElementPos][fRY] = 0.0;
		HouseFurnitures[houseid][lastElementPos][fRZ] = 0.0;
		
		SaveFurniture(houseid, lastElementPos, DB_FURNITURE_DELETE);
		
		totalFurnitureObjects --;
	}
	else SaveFurniture(houseid, slot, DB_FURNITURE_DELETE);
}

//==============================================================================

Furniture_ShowListPage(playerid, houseid, page)
{
    new furnitureArrayPos;

    Catalogo_SetID(playerid, CATALOG_OWN_FURN);
    Catalogo_SetCurrentPage(playerid, page);
    Catalogo_SetTotalElements(playerid, Furniture_GetTotalElements(houseid));
    Catalogo_SetTotalPages(playerid, floatround(float(Catalogo_GetTotalElements(playerid)) / 10.0, floatround_ceil));
    Catalogo_SetTitle(playerid, "Muebles comprados en esta casa");

	for(new i = 0; i < 10; i++)
	{
	    furnitureArrayPos = Catalogo_GetCurrentPage(playerid) * 10 - 10 + i;
	    if(furnitureArrayPos < Catalogo_GetTotalElements(playerid)) // Mientras no se pase del máximo de elementos
	    {
		    Catalogo_SetBoxModel(playerid, i, HouseFurnitures[houseid][furnitureArrayPos][fObjectModel]);
		}
		else // Si se pasó, le seteamos el modelo en 0, que despues la funcion para mostrarlo detecta que está en 0 y no lo muestra.
		{
			Catalogo_SetBoxModel(playerid, i, 0);
		}
	}
}
/*----------------------------------------------------------------------------*/
/*--------------------------------  COMANDOS  --------------------------------*/
/*----------------------------------------------------------------------------*/
CMD:muebles(playerid, params[])
{
	new houseid = GetPlayerHouse(playerid);
	if( (House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
	{
    	Furniture_ShowListPage(playerid, houseid, 1);
    	Catalogo_ShowForPlayer(playerid);
		SelectTextDraw(playerid, 0xFFE501FF);
    	return 1;
    }
    else return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en tu casa!");
}

CMD:comprarmuebles(playerid, params[])
{
	//PlayAudioStreamForPlayer(playerid,"http://dc650.4shared.com/img/5562913937/a6b49639/dlink__2Fdownload_2FkRoZHNJLba_3Ftsid_3D20150420-235347-f8a4858b_26lgfp_3D1000_26dsid_3Dce979u.6e3c0918c61269340eff42aa3dddf03f_26sbsr_3D889f06312caa8a620d22a49a5b1c40ed35ae3f5bc94a3861/preview.mp3");
	new houseid = GetPlayerHouse(playerid);
    if( (House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
	{
		PlayAudioStreamForPlayer(playerid, "http://fileserver.pheek.net/marp/radio/buy.mp3");
    	Dialog_Show(playerid, Dlg_Furniture, DIALOG_STYLE_LIST, "Categorias",
			"Mesas y Sillas\n\
			Camas Mesas de Luz y Armarios\n\
			Iluminacion\n\
			Cuadros y otros\n\
			Baño y Fontaneria\n\
			Construccion\n\
			Cocina\n\
			Electronica\n\
			Entretenimiento\n\
			Miscelaneos",
			"Aceptar", "Salir");
		return 1;
	}
	else
		return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en tu casa!");
}

Dialog:Dlg_Furniture(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
	    	case DLG_ITEM_M_MESAS_SILLAS: Mesas_Sillas_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_CAMAS_MESAS_ARM: Camas_Mesas_Arm_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_ILUMINACION: Iluminacion_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_FRAMES: Frames_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_BATH: Bath_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_CONSTRUCTION: Construction_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_KITCHEN: Kitchen_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_ELECTRONICS: Electronics_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_ENTERTAINMENT: Entertainment_ShowCatalogPage(playerid, 1);
	    	case DLG_ITEM_M_MISC: Misc_ShowCatalogPage(playerid, 1);
		}
		Catalogo_ShowForPlayer(playerid);
		SelectTextDraw(playerid, 0xFFE501FF);
	}
	return 1;
}

Dialog:Dlg_Furniture_Buy(playerid, response, listitem, inputtext[])
{
	if(response)
	{
    	if(totalFurnitureObjects == MAX_FURNITURE_TOTAL_OBJECTS)
        	return SendClientMessage(playerid, -1, "[ERROR] SE HA ALCANZADO EL MÁXIMO DE MUEBLES PERMITIDOS, REPORTAR AL STAFF");
		if(GetPlayerCash(playerid) < furniturePriceObjectSelection[playerid])
			return SendClientMessage(playerid, COLOR_YELLOW2, "¡No tienes el dinero suficiente!");
		GivePlayerCash(playerid, -furniturePriceObjectSelection[playerid]);
		CreateFurnitureObject(playerid, furnitureObjectSelection[playerid]);
		return 1;
	}
	else
		return cmd_comprarmuebles(playerid, "");
}

Dialog:Dlg_Furniture_Own_Option(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
		    case DLG_ITEM_OWN_EDIT: EditarMueble(playerid, furnitureObjectSelection[playerid]);
		    case DLG_ITEM_OWN_DELETE: Dialog_Show(playerid, Dlg_Furniture_Delete, DIALOG_STYLE_MSGBOX, "CONFIRME SU OPCION", "¿Está seguro que desea eliminar este mueble?", "Eliminar", "Cancelar");
		    case DLG_ITEM_OWN_PACKING: PackingFurniture(playerid, GetPlayerHouse(playerid), OwnFurnitureSelected[playerid]);
		}
	}
	return 1;
}

Dialog:Dlg_Furniture_Delete(playerid, response, listitem, inputtext[])
{
	if(response)
    {
        Furniture_DeleteFromHouse(GetPlayerHouse(playerid), OwnFurnitureSelected[playerid]);
        SendClientMessage(playerid, -1, "Mueble borrado.");
	}
	return 1;
}


stock PackingFurniture(playerid, houseid, fIndex)
{
	if(!BothFreeHands(playerid))
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Debes tener las dos manos vacías!");
    SetHandItemAndParam(playerid, HAND_RIGHT, ITEM_ID_FURNITURE_BOX, HouseFurnitures[houseid][fIndex][fObjectModel]);
	Furniture_DeleteFromHouse(houseid, fIndex);
	return 1;
}

stock UnpackingFurniture(playerid)
{
	CreateFurnitureObject(playerid, GetHandParam(playerid, HAND_RIGHT));
	SetHandItemAndParam(playerid, HAND_RIGHT, 0, 0);
	return 1;
}

CMD:desempaquetar(playerid, params[])
{
    new houseid = GetPlayerHouse(playerid);
    if( (House[houseid][OwnerSQLID] == PlayerInfo[playerid][pID]) || AdminDuty[playerid])
	{
	    if(GetHandItem(playerid, HAND_RIGHT) != ITEM_ID_FURNITURE_BOX)
	        return SendClientMessage(playerid, COLOR_YELLOW2, "No tienes un mueble en tus manos");
	    UnpackingFurniture(playerid);
	    return 1;
	}
	else return SendClientMessage(playerid, COLOR_YELLOW2, "¡No estás en tu casa!");
}

/*============================================================================*/


SaveFurniture(houseid, indexid, option)
{
	if(dontsave || House[houseid][Created] == 0 || indexid < 0)
		return 0;

	switch(option)
	{
		case DB_FURNITURE_UPDATE:
		{
		    new query[256];
		    
			format(query, sizeof(query), "UPDATE furnitures SET objectmodel=%d, xpos=%f, ypos=%f, zpos=%f, xrot=%f, yrot=%f, zrot=%f WHERE houseid=%d AND indexid=%d LIMIT 1",
				HouseFurnitures[houseid][indexid][fObjectModel],
				HouseFurnitures[houseid][indexid][fX],
				HouseFurnitures[houseid][indexid][fY],
				HouseFurnitures[houseid][indexid][fZ],
				HouseFurnitures[houseid][indexid][fRX],
				HouseFurnitures[houseid][indexid][fRY],
				HouseFurnitures[houseid][indexid][fRZ],
				houseid,
				indexid
			);
			
			mysql_function_query(dbHandle, query, false, "", "");
  		}
		
		case DB_FURNITURE_CREATE:
		{
		    new query[256];
		    
			format(query, sizeof(query), "INSERT INTO furnitures (houseid, indexid, objectmodel, xpos, ypos, zpos, xrot, yrot, zrot) VALUES (%d, %d, %d, %f, %f, %f, %f, %f, %f)",
				houseid,
				indexid,
				HouseFurnitures[houseid][indexid][fObjectModel],
				HouseFurnitures[houseid][indexid][fX],
				HouseFurnitures[houseid][indexid][fY],
				HouseFurnitures[houseid][indexid][fZ],
				HouseFurnitures[houseid][indexid][fRX],
				HouseFurnitures[houseid][indexid][fRY],
				HouseFurnitures[houseid][indexid][fRZ]
			);
			
			mysql_function_query(dbHandle, query, false, "", "");
		}
		
		case DB_FURNITURE_DELETE:
		{
		    new query[128];
		    
			format(query, sizeof(query), "DELETE FROM furnitures WHERE houseid=%d AND indexid=%d LIMIT 1",
				houseid,
				indexid
			);
			
			mysql_function_query(dbHandle, query, false, "", "");
		}

		default:
			return 0;
	}
	return 1;
}

LoadFurnitures()
{
	new query[64];
	
	for(new houseid = 1; houseid < MAX_HOUSES; houseid++)
	{
	    format(query, sizeof(query), "SELECT * FROM furnitures WHERE houseid=%d LIMIT %d", houseid, MAX_HOUSE_FURNITURES);
		mysql_function_query(dbHandle, query, true, "OnFurnituresDataLoad", "i", houseid);
	}
	return 1;
}

forward OnFurnituresDataLoad(houseid);
public OnFurnituresDataLoad(houseid)
{
   	new rows,
		fields;

	cache_get_data(rows, fields);

	if(rows)
	{
		new indexid;
	    for(new row = 0; row < rows; row++)
		{
			indexid = cache_get_field_content_int(row, "indexid");
			HouseFurnitures[houseid][indexid][fObjectModel] = cache_get_field_content_int(row, "objectmodel");
			HouseFurnitures[houseid][indexid][fX] = cache_get_field_content_float(row, "xpos");
	        HouseFurnitures[houseid][indexid][fY] = cache_get_field_content_float(row, "ypos");
	        HouseFurnitures[houseid][indexid][fZ] = cache_get_field_content_float(row, "zpos");
	        HouseFurnitures[houseid][indexid][fRZ] = cache_get_field_content_float(row, "xrot");
	        HouseFurnitures[houseid][indexid][fRY] = cache_get_field_content_float(row, "yrot");
	        HouseFurnitures[houseid][indexid][fRZ] = cache_get_field_content_float(row, "zrot");
			HouseFurnitures[houseid][indexid][fObjectID] = CreateDynamicObject(HouseFurnitures[houseid][indexid][fObjectModel], HouseFurnitures[houseid][indexid][fX], HouseFurnitures[houseid][indexid][fY], HouseFurnitures[houseid][indexid][fZ], HouseFurnitures[houseid][indexid][fRX], HouseFurnitures[houseid][indexid][fRY], HouseFurnitures[houseid][indexid][fRZ], House[houseid][InsideWorld]);
			totalFurnitureObjects++;
	    }
    }
	return 1;
}
