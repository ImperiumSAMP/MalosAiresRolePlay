#if defined _isamp_lojack_auto
	#endinput
#endif
#define _isamp_lojack_auto

#define GpsPrice    500
COMMAND:lojack(playerid, params[])
{
new vehicleid;                                            // Las variables que vamos a usar despues, vehicleid es para la id del auto en cuestión
new cash = GetPlayerCash(playerid);    // esta detecta directamente cuánta plata tiene el jugador (aunque no es estrictamente necesaria es mas entendible)
new Float: X, Float: Y, Float: Z; //Las pos son valores flotantes (llevan puntos y comas) creamos tres variables flotantes que almacenen las coordenadas, aunq se puede usar un array pero no cambia nada

if (sscanf(params, "d", vehicleid)) return SendClientMessage (playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /lojack [VehicleID]"); // la condicion chequea que no hayan sido introducidos correctamente los parametros completos, y de ser asi, retorna mandando el msj con la sintaxis
{
    if(!playerOwnsCar(playerid,vehicleid))
		return SendClientMessage(playerid, COLOR_RED, "{FF4600}[Error]:{C8C8C8} El vehiculo no te pertenece");
    if(PlayerInfo[playerid][pPhoneNumber] == 0)
	    return SendClientMessage(playerid, COLOR_YELLOW2, "¡Requieres de un telefono para utilizar el Lojack!");
	foreach(new rplayer : Player)
			{
			 if(IsPlayerInVehicle(rplayer,vehicleid)) 
			     return SendClientMessage(playerid, COLOR_YELLOW2, "No puedes localizar tu vehiculo en este momento.");	
			}
    if (cash < GpsPrice) return SendClientMessage (playerid, COLOR_GREY, "No tenés dinero suficiente para rastrear el vehículo. ($500)"); // esta parte es entendible supongo, la condicion indica q si la guita del jugador es menor ( < ) a 500, el costo de rastreo, retorna mandando el msj de que necesitas $500
    {
        GivePlayerCash (playerid, -GpsPrice);     // resta al jugador el costo de rastreo, $500
        GetVehiclePos (vehicleid, X, Y, Z); // consigue la posicion de vehicleid, la id del auto a localizar
        SetPlayerCheckpoint (playerid, X, Y, Z, 3);     // crea el checkpoint, en la posicion, 3 es el tamaño
        SendClientMessage (playerid, COLOR_GREY, "¡Lograste rastrear el vehículo!");    // manda msj
        SetTimerEx ("findgps", 240000, false, "d", playerid); // esto crea un timer de 4 minutos (se mide en milisegs, 240000 = 240 segundos),total cuando llegas al checkpoint y lo sobrepasas desaparece, creamos esto para evitar bugs y q despues de un tiempo desaparezca.
    }
}
return 1;
}

forward findgps (playerid); // declaracion de la funcion (fingps, el nombre de la funcion del timer)
public findgps (playerid)
{
DisablePlayerCheckpoint(playerid); // indica que pasados los 4 minutos, es eliminado el checkpoint.
return 1;
}

