#if defined _isamp_antirespawn_autos
#endinput
#endif 
#define _isamp_antirespawn_autos

forward VHealth();
public VHealth() // public y forward del timer
{
for (new v = 0; v < MAX_VEHICLES; v++) // creamos un loop que recorre el maximo de vehiculos definidos
{
	new Float: Z_angle;
    new Float:vHealth;
    GetVehicleHealth (v, vHealth);           // comprobamos la vida de los autos loopeados
    if (vHealth < 400)  // si es menor a 400, le setea la misma vida
        {
         SetVehicleHealth (v, 400);
		 GetVehicleZAngle(v, Z_angle);
         SetVehicleZAngle(v, Z_angle + 0.1); //con esto el vehiculo si esta dado vuelta, vuelve a ponerse como debe.


         }
    }
}