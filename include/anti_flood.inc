#include <a_samp>
#define IP_LIMIT 10 // = Max connections from one single IP
#define SAME_IP_CONNECT 12 // = The number of connects from the same IP before banning the flooder
new Same_IP=0,Join_Stamp,ban_s[25],exceed=0;
#define Time_Limit 3500 // = The time span between connects, adjust it to your own specifications

forward AntiFlood(playerid);

public AntiFlood(playerid)
{
	new ConnIP[16];
	new compare_IP[16];
	new number_IP = 0;

	if(IsPlayerNPC(playerid)) {
                new server_IP[16];
                format(server_IP, 16, "127.0.0.1");
 
                if(strcmp(ConnIP,server_IP,true) != 0) {
                    Ban(playerid); // Ban is the safest thing here, as if you kick, they can still flood you with endless connections
                    return 0;
                }
        }

	GetPlayerIp(playerid,ConnIP,16);

	for(new i=0; i<MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i)) {
		    GetPlayerIp(i,compare_IP,16);
		    if(!strcmp(compare_IP,ConnIP)) number_IP++;
		}
	}
	if((GetTickCount() - Join_Stamp) < Time_Limit)
	    exceed=1;
	else
	    exceed=0;
 	if(strcmp(ban_s, ConnIP, false) == 0 && exceed == 1 )
 	{
 	    Same_IP++;
 	    if(Same_IP > SAME_IP_CONNECT)
 	    {
	   		Ban(playerid);
 			Same_IP=0;
 	    }
 	}
 	else
 	{
 		Same_IP=0;
	}
	if(number_IP > IP_LIMIT)
	    Kick(playerid);
	GetStampIP(playerid);
	return 1;

}
stock GetStampIP(playerid){
	new S_IP[16];
	Join_Stamp=GetTickCount();
	GetPlayerIp(playerid,S_IP,16);
	format(ban_s, 16, "%s", S_IP);
}
