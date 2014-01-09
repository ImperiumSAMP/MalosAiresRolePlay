/*

*/

#include <a_samp>
#include <sscanf2>
#include <zcmd>
#include <streamer>
#include <foreach>
//#include <mapandreas>

#define COLOR_YELLOW2 			0xF5DEB3AA
#define PRESSED(%0) 			(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define HOLDING(%0) 			((newkeys & (%0)) == (%0))
#define RELEASED(%0) 			(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define SendFMessage(%0,%1,%2,%3)    do{new _str[150]; format(_str,150,%2,%3); SendClientMessage(%0,%1,_str);}while(FALSE)
#define SendFMessageToAll(%1,%2,%3)  do{new _str[190]; format(_str,150,%2,%3); SendClientMessageToAll(%1,_str);}while(FALSE)

/* ---- Forwards. ---- */

forward t_maintimer();

/* ---- FS template. ---- */

new bool:FALSE = false;
new fsTimer[1];

/* ---- FS specific variables.  ----*/

enum e_ballData {
	bool:ballActive,
	ballOwnerID,
	ballInactiveTime,
	ballObject
};
new ballData[64][e_ballData];

#define MAX_SOCCER_AREAS 1
new bool:soccerEnabled = true;
new soccerArea[MAX_SOCCER_AREAS];
new bool:soccerAreaInUse[MAX_SOCCER_AREAS] = {
	false
};
new soccerAreaBall[2] = {-1, -1};
new Float:soccerAreaCenter[MAX_SOCCER_AREAS][3] = {
	{2290.5608, -1528.3632, 25.9649}
};

/* ---- Start. ---- */

public OnFilterScriptInit() {
	print("\n--------------------------------------");
	print(" Soccer FilterScript by Krizzen");
	print("--------------------------------------\n");
	
	//MapAndreas_Init(MAP_ANDREAS_MODE_FULL);
	
	fsTimer[0] = SetTimer("t_maintimer", 1000, 1);
	
    soccerArea[0] = CreateDynamicRectangle(2281.1572, -1513.6139, 2299.4778, -1542.3616, 0, 0, -1);
    
   	CreateDynamicObject(1897, 2288.47900, -1542.28320, 27.01570,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(1897, 2292.65015, -1542.26318, 27.01570,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1897, 2291.65771, -1542.28796, 27.99540,   90.00000, 90.00000, 0.00000);
	CreateDynamicObject(1897, 2292.65015, -1513.59460, 27.01570,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(1897, 2291.63965, -1513.61877, 27.99540,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(1897, 2289.47974, -1513.59802, 27.99540,   90.00000, 0.00000, -90.00000);
	CreateDynamicObject(3819, 2303.08521, -1538.06360, 26.65070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3819, 2303.08521, -1528.08044, 26.65070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3819, 2303.08521, -1517.79102, 26.65070,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3819, 2295.28467, -1546.02380, 26.87017,   0.00000, 0.00000, -89.82000);
	CreateDynamicObject(3819, 2285.48389, -1546.02405, 26.87020,   0.00000, 0.00000, -89.82000);
	CreateDynamicObject(3819, 2277.23022, -1517.86804, 26.87020,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(3819, 2277.23022, -1528.06921, 26.87020,   0.00000, 0.00000, -179.82001);
	CreateDynamicObject(3819, 2277.23022, -1538.14465, 26.87020,   0.00000, 0.00000, -179.82001);
	CreateDynamicObject(19373, 2298.95288, -1514.56702, 25.79549,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1512.35999, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1515.56897, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1518.76880, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1521.96899, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1525.16992, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1528.35986, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1531.56995, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1534.78003, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1537.98987, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1541.19995, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1544.41003, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.27417, -1547.62000, 25.60050,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19372, 2304.48169, -1549.22913, 23.97600,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(19373, 2295.45288, -1514.56702, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1514.56702, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1514.56702, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1514.56702, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1514.56702, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1517.77734, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1520.98804, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2118, 2298.30615, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1524.19995, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1530.62000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1533.82996, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1537.04004, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1540.25000, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2298.95288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2295.45288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2291.95288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2288.45288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(19373, 2281.45288, -1541.34998, 25.79500,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2118, 2281.22803, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2282.36792, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2283.50781, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2284.64771, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2285.78784, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2286.92773, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2288.08545, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2289.22534, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2290.36548, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2291.50562, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2292.64575, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2293.78589, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2294.92578, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2296.06592, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2297.20605, -1512.83240, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2298.30615, -1512.83240, 25.39100,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2297.20605, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2296.06592, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2294.92578, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2293.78589, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2292.64575, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2291.50562, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2290.36548, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2289.22534, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2288.08545, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2286.92773, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2285.78784, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2284.64771, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2283.50781, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2282.36792, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2298.30615, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2297.20605, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2296.06592, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2294.92578, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2293.78589, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2292.64575, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2291.50562, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2290.36548, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2289.22534, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2288.08545, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2286.92773, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(19373, 2284.95288, -1527.41003, 25.79550,   0.00000, 90.00000, 0.00000);
	CreateDynamicObject(2118, 2285.78784, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2284.64771, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2283.50781, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2282.36792, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2281.22803, -1541.50623, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2281.22803, -1527.60449, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2280.44312, -1514.64441, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1515.78442, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1516.92444, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1518.06445, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1519.20435, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1520.34436, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1521.48438, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1522.62439, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1523.76440, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1524.90454, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1526.04285, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1527.18274, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1528.32275, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1529.48267, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1530.62268, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1531.76270, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1532.90271, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1534.04272, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1535.18274, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1536.32275, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1537.46265, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1538.60254, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1539.74255, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1540.88245, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1542.02246, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2280.44312, -1542.22253, 25.39020,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1514.64441, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1515.78442, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1516.92444, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1518.06445, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1519.20435, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1520.34436, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1521.48438, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1522.62439, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1523.74316, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1524.90454, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1526.04285, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1527.18274, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1528.32275, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1529.48267, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1530.62268, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1531.76270, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1532.90271, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1534.04272, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1535.18274, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1536.32275, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1537.46265, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1538.60254, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1539.74255, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1540.88245, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1542.02246, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2298.60815, -1542.22253, 25.39020,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2292.63672, -1542.16272, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2292.63672, -1541.04272, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2286.92944, -1542.18945, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2286.92944, -1541.04272, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2287.71704, -1539.22998, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2288.85693, -1539.22998, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2289.99683, -1539.22998, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2291.13672, -1539.22998, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2292.27686, -1539.22998, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2286.92944, -1514.69495, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2286.92944, -1515.83142, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2292.63672, -1514.69495, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2292.63672, -1515.83142, 25.39110,   90.00000, 0.00000, 90.00000);
	CreateDynamicObject(2118, 2292.27222, -1515.10547, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2291.13208, -1515.10547, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2289.99219, -1515.10547, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2288.85205, -1515.10547, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2118, 2287.73218, -1515.10547, 25.39110,   90.00000, 0.00000, 0.00000);
	CreateDynamicObject(2830, 2290.56323, -1528.36804, 25.88490,   180.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1547.62000, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1544.41003, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1541.19995, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1537.98987, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1534.78003, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1531.56995, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1528.35986, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1525.16992, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1521.96899, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1518.76880, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1515.56897, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19372, 2306.00195, -1512.35999, 23.97650,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1897, 2289.45825, -1542.26196, 27.99540,   90.00000, 90.00000, 180.00000);
	CreateDynamicObject(1897, 2288.47900, -1513.61768, 27.01570,   0.00000, 0.00000, 90.00000);
	return 1;
}

public OnFilterScriptExit() {
	for(new i = 0; i < sizeof(ballData); i++) {
		if(ballData[i][ballActive]) {
			DestroyObject(ballData[i][ballObject]);
		}
	}
	KillTimer(fsTimer[0]);
    //MapAndreas_Unload();
	return 1;
}	

public OnPlayerConnect(playerid) {
    RemoveBuildingForPlayer(playerid, 946, 2290.6406, -1541.6094, 28.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 946, 2290.6406, -1541.6094, 28.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 946, 2290.5781, -1514.2734, 28.0469, 0.25);
	RemoveBuildingForPlayer(playerid, 1297, 2305.5859, -1544.1797, 27.2188, 0.25);
	RemoveBuildingForPlayer(playerid, 946, 2316.9375, -1541.6094, 26.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 946, 2316.9375, -1514.2734, 26.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1297, 2327.4063, -1544.1797, 27.2188, 0.25);
	return 1;
}

public t_maintimer() {
	if(soccerEnabled) {
		for(new i = 0; i < MAX_SOCCER_AREAS; i++) {
		    if(soccerAreaInUse[i]) {
		        new Float:ballPos[3];
				GetObjectPos(ballData[i][ballObject], ballPos[0], ballPos[1], ballPos[2]);
				if(!IsPointInDynamicArea(soccerArea[i], ballPos[0], ballPos[1], ballPos[2])) {
			  		StopObject(ballData[i][ballObject]);
			  		SetObjectPos(ballData[i][ballObject], soccerAreaCenter[i][0], soccerAreaCenter[i][1], soccerAreaCenter[i][2]);
					foreach(new p : Player) {
						if(IsPlayerInDynamicArea(p, soccerArea[i])) {
					 		GameTextForPlayer(p, "Fuera!", 3000, 1);
                            PlayerPlaySound(p, 3200, 0.0, 0.0, 0.0);
						}
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(soccerEnabled) {
		if(PRESSED(KEY_SECONDARY_ATTACK | KEY_SPRINT)) {
			cmd_patear(playerid, "2");
		} else if(PRESSED(KEY_SECONDARY_ATTACK)) {
			cmd_patear(playerid, "1");
		}
	}
	return 1;
}

stock Float:mod(Float:a, Float:b) {
    while(a > b)
        a -= b;
    return a;
}

stock Float:GetDistance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2) {
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

CMD:pelotest(playerid, params[]) {
	new
		bool:noball = true,
		bool:noarea = true;

    if(!soccerEnabled) return 1;
		
	if(GetPVarInt(playerid, "admin") <= 0) return 1;

	for(new i = 0; i < sizeof(ballData); i++) {
		if(!ballData[i][ballActive]) {
		    for(new a = 0; a < MAX_SOCCER_AREAS; a++) {
                if(IsPlayerInDynamicArea(playerid, soccerArea[a])) {
                    if(!soccerAreaInUse[a]) {
                        soccerAreaInUse[a] = true;
                        soccerAreaBall[a] = i;
                        ballData[i][ballActive] = true;
					    ballData[i][ballObject] = CreateObject(2114, soccerAreaCenter[i][0], soccerAreaCenter[i][1], soccerAreaCenter[i][2], 0, 0, 0);
                        noarea = false;
						break;
                    } else {
                        return SendClientMessage(playerid, COLOR_YELLOW2, "La cancha ya se encuentra en uso, puedes pedir permiso para jugar o esperar a que termine el partido.");
                    }
                }
			}

			if(noarea) return SendClientMessage(playerid, COLOR_YELLOW2, "Debes estar en una cancha de football para utilizar este comando.");

		    noball = false;
			break;
		}
	}

	if(noball) {
	    return SendClientMessage(playerid, COLOR_YELLOW2, "Se ha llegado al límite de pelotas en el servidor, espera un rato y vuelve a intentarlo.");
	}
	return 1;
}

CMD:patear(playerid, params[]) {
	if(!soccerEnabled) return 1;

    new Float:tempAngle, Float:tempPos[3], Float:dist, Float:speed, type;
    GetPlayerPos(playerid, tempPos[0], tempPos[1], tempPos[2]);
	if(sscanf(params, "d", type)) {
	} else {
	    if(type < 1 || type > 2)
	        return 1;

		if(type == 2) {
		    speed = 7.5;
			dist = 7.0;
		} else {
		    speed = 4.5;
			dist = 2.0;
		}

	    for(new i = 0; i < 64; i++) {
	    	new Float:ballPos[3];
			GetObjectPos(ballData[i][ballObject], ballPos[0], ballPos[1], ballPos[2]);
			if(ballData[i][ballActive] && GetDistance(ballPos[0], ballPos[1], ballPos[2], tempPos[0], tempPos[1], tempPos[2]) <= 1.5) {
				GetPlayerFacingAngle(playerid, tempAngle);
			    MoveObject(ballData[i][ballObject], ballPos[0] + dist * floatcos(mod((180 + (tempAngle - 90)), 360), degrees), ballPos[1] +  dist * floatsin(mod((180 + (tempAngle - 90)), 360), degrees), ballPos[2], speed);
				if(type == 2) {
			    	ApplyAnimation(playerid,"FIGHT_D","FightD_G",4.1,0,0,0,0,800,1);
			    }
				break;
			}
		}
	}
	return 1;
}

CMD:gotopelota(playerid, params[]) {
    if(!soccerEnabled) return 1;

	if(GetPVarInt(playerid, "admin") <= 0) return 1;

	new ballID;

	if(sscanf(params, "d", ballID)) {
	} else {
	    new Float:ballPos[3];
		GetObjectPos(ballData[ballID][ballObject], ballPos[0], ballPos[1], ballPos[2]);
	    SetPlayerPos(playerid, ballPos[0], ballPos[1], ballPos[2] + 2);
	}
	return 1;
}
