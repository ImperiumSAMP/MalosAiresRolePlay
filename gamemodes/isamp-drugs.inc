#if defined _isamp_drugs_included
	#endinput
#endif
#define _isamp_drugs_included

#define ADICTION_UPDATE_TIME    300 // tiempo cada cuanto se actualiza la adiccion, en segundos, 5 min
#define ADICTION_MARIJUANA 		0.10 // cuanto suma una dosis al total porcentual de adiccion a las drogas
#define ADICTION_LSD       		0.25
#define ADICTION_ECSTASY   		0.35
#define ADICTION_COCAINE   		0.50
#define ADICTION_REHAB_PRICE    14000
#define ADICTION_ABSTINENCE_MAX 36000 // tiempo maximo para que te pida consumir con el minimo porcentaje de adiccion, en segundos 10 horas


new
    /* Sistema de adiccion y drogas */
	RehabOffer[MAX_PLAYERS],
 	DrugOfferType[MAX_PLAYERS],
 	DrugOffer[MAX_PLAYERS],
	DrugOfferAmount[MAX_PLAYERS],
	bool:SellingDrugs[MAX_PLAYERS],
	bool:DrugEffectEcstasy[MAX_PLAYERS],
	bool:DrugEffectLSD[MAX_PLAYERS],
	bool:DrugEffectCocaine[MAX_PLAYERS],
	bool:DrugEffectMarijuana[MAX_PLAYERS];

stock bool:isPlayerSellingDrugs(playerid){
	return SellingDrugs[playerid];
}