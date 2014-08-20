#if defined _isamp_maletin_included
	#endinput
#endif
#define _isamp_maletin_included
new ConM[MAX_PLAYERS];
#define MAX_DINERO_MALETIN 100000


stock CrearMaletinTodos()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        CrearMaletinEx(i);
	}
	return 1;
}

stock BorrarMaletinTodos()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        BorrarMaletinEx(i);
	}
	return 1;
}

stock BorrarMaletinEx(playerid)
{
	RemovePlayerAttachedObject(playerid, 7);
	return 1;
}


stock CrearMaletinEx(playerid)
{
	ConM[playerid] = 1;
	SetPlayerAttachedObject(playerid,7,1210,5,0.301999,0.082999,-0.012000,0.000000,-90.599975,-0.999999,1.000000,1.000000,1.000000);
	return 1;
}

stock Tienemaletin(playerid)
{
	return ConM[playerid];
}

////Aca terminan los Stocks

///Aca comienza el sistema de maletin
CMD:dmaletin(playerid, params[])
{
    new Cash = GetPlayerMoney(playerid), amount;
    new str[100];
    if (sscanf (params, "d", amount)) return SendClientMessage (playerid, COLOR_RED, "{5CCAF1}[Sintaxis]:{C8C8C8} /dmaletin (Monto)");
    {
        if (amount > MAX_DINERO_MALETIN) return SendClientMessage (playerid, COLOR_GREY, "No podés depositar más de $100000 en el maletín.");
        if (PlayerInfo[playerid][pBriefcaseCash] == MAX_DINERO_MALETIN) return SendClientMessage (playerid, COLOR_WHITE, "El maletín está lleno, no podés depositar más dinero en él.");
        if(PlayerInfo[playerid][pBriefcaseObject] == 0) return SendClientMessage(playerid, COLOR_GREY, "No tenés un maletín en tu mano, compralo en algún 24-7");
        {      
            if(amount + PlayerInfo[playerid][pBriefcaseCash] > MAX_DINERO_MALETIN) return SendClientMessage(playerid, COLOR_WHITE, "No podés depositar más de $100000 en el maletín.");
                
            if (Cash >= amount && amount > 0) {
                    GivePlayerMoney(playerid, -amount);
                    PlayerInfo[playerid][pBriefcaseCash] += amount;
                    format (str, sizeof(str), "Depositaste $%d en tu maletín.", amount);
                    SendClientMessage (playerid, COLOR_GREY, str);
					SaveAccount(playerid);
                    } else {
                    SendClientMessage (playerid, COLOR_GREY, "No tenés esa cantidad de dinero.");
            }
        }
    }
    return 1;
	}

CMD:maletin (playerid, params[])
{
new str[100];
if(PlayerInfo[playerid][pBriefcaseObject] == 0) return SendClientMessage(playerid, COLOR_GREY, "No tenés un maletín en tu mano, compralo en algún 24-7");
format(str, sizeof(str), "El maletin contiene $%d", PlayerInfo[playerid][pBriefcaseCash]); 
SendClientMessage (playerid, -1, str);

return 1;
}

CMD:rmaletin (playerid, params[]){
    new
    cash = PlayerInfo[playerid][pBriefcaseCash],
    amount,
    str[90];
    if (sscanf (params, "d", amount))
    return SendClientMessage (playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /rmaletin [monto]");
    {
        if(PlayerInfo[playerid][pBriefcaseObject] == 0) return SendClientMessage(playerid, COLOR_GREY, "No tenés un maletín en tu mano, compralo en algún 24-7");
        {
			if(amount <= 0 || amount > cash) return SendClientMessage (playerid, COLOR_GREY, "Cantidad de dinero inválida.");
            {
                GivePlayerMoney(playerid, amount);
                PlayerInfo[playerid][pBriefcaseCash] -= amount;
                format (str, sizeof(str), "Retiraste $%d de tu maletín.", amount);
                SendClientMessage (playerid, COLOR_GREY, str);
				SaveAccount(playerid);
            }
        }
    }
    return 1;
}
CMD:darmaletin(playerid, params[])
{
new
 targetid;
if(sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_GREY, "{5CCAF1}[Sintaxis]:{C8C8C8} /darmaletin [id/ParteDelNombre]");
if(PlayerInfo[playerid][pBriefcaseObject] == 0) return SendClientMessage(playerid, COLOR_GREY, "No tenés un maletín en tu mano, compralo en algún 24-7");
if(PlayerInfo[targetid][pBriefcaseObject] == 1) return SendClientMessage(playerid, COLOR_GREY, "El sujeto ya tiene un maletin en su mano.");
if(IsPlayerConnected(targetid) && targetid != INVALID_PLAYER_ID && PlayerInfo[targetid][pBriefcaseObject] == 0){
   PlayerPlayerActionMessage(playerid, targetid, 15.0, "le entregó un maletín a");
   PlayerInfo[targetid][pBriefcaseCash]= PlayerInfo[playerid][pBriefcaseCash];
   BorrarMaletinEx(playerid);
   CrearMaletinEx(targetid);
   PlayerInfo[targetid][pBriefcaseObject] = 1;
   PlayerInfo[playerid][pBriefcaseCash] = 0;
   PlayerInfo[playerid][pBriefcaseObject] = 0;
   SaveAccount(playerid);
  } else {
  SendClientMessage(playerid, COLOR_GREY, "Jugador no conectado o inválido.");
  }
return 1;
}

CMD:desecharmaletin(playerid, params[])
{
if(PlayerInfo[playerid][pBriefcaseObject] == 0) return SendClientMessage(playerid, COLOR_GREY, "No tenés un maletín en tu mano, compralo en algún 24-7");
PlayerInfo[playerid][pBriefcaseCash] = 0;
PlayerInfo[playerid][pBriefcaseObject] = 0;
BorrarMaletinEx(playerid);
SendClientMessage(playerid, -1, "Desechaste tu maletín.");
SaveAccount(playerid);
return 1;
}















