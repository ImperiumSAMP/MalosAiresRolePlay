#if defined _isamp_drugs_included
	#endinput
#endif
#define _isamp_drugs_included

new DrugOfferType[MAX_PLAYERS],
 	DrugOffer[MAX_PLAYERS],
	DrugOfferPrice[MAX_PLAYERS],
	DrugOfferAmount[MAX_PLAYERS],
	bool:SellingDrugs[MAX_PLAYERS];

stock isPlayerSellingDrugs(playerid){
	return SellingDrugs[playerid];
}