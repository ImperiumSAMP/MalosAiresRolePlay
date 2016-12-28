#if defined _marp_tutorial_included
	#endinput
#endif
#define _marp_tutorial_included

#define DLG_TUT1         		10002

new Text:TutTDBackground,
    PlayerText:TutTD_Text[MAX_PLAYERS][8];
    
PlayerStartTutorial(playerid)
{
	TogglePlayerSpectating(playerid, true);
	SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 200, false, "ii", playerid, 1));
    SetPlayerHealthEx(playerid, 100.00);
    PlayerInfo[playerid][pArmour] = 0.0;
}

forward tutorial(playerid, step);
public tutorial(playerid, step)
{
	for(new i = 0; i < 7; i++)
	{
	    PlayerTextDrawShow(playerid, TutTD_Text[playerid][i]);
	    PlayerTextDrawSetString(playerid, TutTD_Text[playerid][i], " ");
	}
	TextDrawShowForPlayer(playerid, TutTDBackground);

	switch(step)
	{
	    case 1:
		{
	        for(new i = 0; i < 32; i++)
			{
	            SendClientMessage(playerid, COLOR_WHITE, " ");
	        }

	    	SetPlayerCameraPos(playerid, 1466.869506, -1575.771972, 109.123466);
			SetPlayerCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196);
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Bienvenido a Los Santos Roleplay Lat");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~El breve tutorial a continuacion te guiara por los conceptos basicos del RolePlay.");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~w~Al finalizar deberas responder con verdadero o falso una serie de preguntas para asegurarnos que lo hayas entendido correctamente.");
			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 2:
		{
			InterpolateCameraPos(playerid, 1466.869506, -1575.771972, 109.123466, 1481.400268, -1576.889038, 90.823272, 3000, 1);
			InterpolateCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196, 1481.267700, -1580.246704, 88.653373, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Concepto de RolePlay:~w~ LSRP Lat es un servidor basado en la ciudad ficticia de Los Santos. Dentro");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~de un juego de rol tu personaje debe actuar como lo haria un humano en la vida real, es decir, se debe");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~w~comportar como una persona comun y corriente que vive dentro de un mundo PARALELO.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~w~Recuerda los siguientes terminos:");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~OOC:~w~ fuera del personaje en ingles (/b, /gooc).");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~IC:~w~ dentro del personaje (local, /gritar).");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
		case 3:
		{
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~b~~h~~h~Normas basicas a respetar:");
            PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~w~Lo siguiente esta prohibido y sera sancionado dentro del servidor.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~MetaGaming [MG]:~w~ utilizar informacion ~b~OOC~w~ dentro de un canal ~b~IC~w~.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~w~Ejemplo: nombrar a otro personaje solo con verle el tag encima de su cabeza en vez de preguntarselo.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~DeathMatch [DM]:~w~ agredir fisicamente a otro personaje sin ninguna razon rolera.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~PowerGaming [PG]:~w~ realizar hazanas imposibles, como arrojarse de un precipicio y salir ileso o");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][6], "~w~forzar el rol de otro personaje. Es posible caer de dicho precipicio si el hecho es roleado correctamente.");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][7], "~w~Si ves a otra persona incumpliendo con las normas utiliza ~b~~h~~h~~h~~h~/reportar");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 4:
		{
	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
	    	SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 5:
		{
	    	InterpolateCameraPos(playerid, 1481.400268, -1576.889038, 90.823272, 1494.139770, -1643.703613, 60.716976, 3000, 1);
			InterpolateCameraLookAt(playerid, 1481.267700, -1580.246704, 88.653373, 1497.297119, -1644.638916, 58.446140, 3000, 1);

	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
	        PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 6:
		{
	    	InterpolateCameraPos(playerid, 1494.139770, -1643.703613, 60.716976, 1288.580200, -1241.240356, 95.973281, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1497.297119, -1644.638916, 58.446140, 1285.706665, -1243.337768, 94.144744, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 1288.580200, -1241.240356, 95.973281, 1211.487670, -1293.440307, 27.860240, 3000, 1);
			InterpolateCameraLookAt(playerid, 1285.706665, -1243.337768, 94.144744, 1208.612304, -1295.868041, 26.504356, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 7:
		{
	        InterpolateCameraPos(playerid, 1211.487670, -1293.440307, 27.860240, 1892.619873, -1798.850219, 68.025955, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1208.612304, -1295.868041, 26.504356, 1889.938354, -1801.596801, 66.900779, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 1892.619873, -1798.850219, 68.025955, 1830.553344, -1882.067016, 33.868297, 3000, 1);
			InterpolateCameraLookAt(playerid, 1889.938354, -1801.596801, 66.900779, 1827.444335, -1883.833740, 32.075828, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 8:
		{
	    	InterpolateCameraPos(playerid, 1830.553344, -1882.067016, 33.868297, 2217.920654, -2129.320312, 59.432971, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 1827.444335, -1883.833740, 32.075828, 2218.117675, -2133.008789, 57.897941, 3000, CAMERA_CUT);
			InterpolateCameraPos(playerid, 2217.920654, -2129.320312, 59.432971, 2246.860839, -2233.512207, 23.764274, 3000, 1);
			InterpolateCameraLookAt(playerid, 2218.117675, -2133.008789, 57.897941, 2243.064697, -2232.351562, 23.272230, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 9:
		{
	    	InterpolateCameraPos(playerid, 2246.860839, -2233.512207, 23.764274, 60.416469, -198.172134, 64.205131, 3000, CAMERA_CUT);
			InterpolateCameraLookAt(playerid, 2243.064697, -2232.351562, 23.272230, 58.964233, -194.497375, 63.582897, 3000, CAMERA_CUT);
	    	InterpolateCameraPos(playerid, 60.416469, -198.172134, 64.205131, -37.132026, 123.020172, 33.543777, 5000, 1);
			InterpolateCameraLookAt(playerid, 58.964233, -194.497375, 63.582897, -37.137905, 119.544448, 31.564058, 5000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~ - granjero");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 10:
		{
	    	SetPlayerCameraPos(playerid, 1466.869506, -1575.771972, 109.123466);
			SetPlayerCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196);
			InterpolateCameraPos(playerid, 1466.869506, -1575.771972, 109.123466, 1481.400268, -1576.889038, 90.823272, 3000, 1);
			InterpolateCameraLookAt(playerid, 1470.403442, -1574.002441, 109.740196, 1481.267700, -1580.246704, 88.653373, 3000, 1);

			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][0], "~w~En la ciudad de Los Santos, hay una gran cantidad de empleos y roles disponibles. Como por ejemplo...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][1], "~b~~h~~h~ - oficial de policia");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][2], "~b~~h~~h~ - paramedico");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][3], "~b~~h~~h~ - taxista");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][4], "~b~~h~~h~ - camionero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][5], "~b~~h~~h~ - granjero");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][6], "~b~~h~~h~ - entre muchos otros...");
			PlayerTextDrawSetString(playerid, TutTD_Text[playerid][7], "~w~Pero tambien puedes crear los tuyos contratando a otras personas o trabajando para ellas.");

			SetPVarInt(playerid, "tutTimer", SetTimerEx("tutorial", 15000, false, "ii", playerid, step + 1));
	    }
	    case 11:
		{
			for(new i = 0; i < 7; i++)
			{
			    PlayerTextDrawHide(playerid, TutTD_Text[playerid][i]);
			}
			TextDrawHideForPlayer(playerid, TutTDBackground);
	        ShowPlayerDialog(playerid, DLG_TUT1, DIALOG_STYLE_LIST, "Escoge una forma válida para averiguar el nombre de un personaje", "Le pregunto por un canal IC\nLe pregunto discretamente por un canal OOC\nLe pregunto por facebook\nLe pregunto roleramente por /b\nLe robo la billetera", "Siguiente", "");
		}
	}
	return 1;
}



CMD:tutorial(playerid, params[])
{
	new targetID;

	if(sscanf(params, "u", targetID))
	    return SendClientMessage(playerid, COLOR_LIGHTYELLOW2, "{5CCAF1}[Sintaxis]:{C8C8C8} /tutorial [ID-Jugador]");

	PlayerInfo[targetID][pTutorial] = 0;
	KickPlayer(targetID, GetPlayerNameEx(playerid), "rehacer el tutorial");
	return 1;
}
