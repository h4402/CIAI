#include "common.h"

#include "handler.h"
#include "TacheSimu.h"

/**
 * Prend le sémaphore d'init de la production lors du lancement.
 * Boucle infinie qui appelle le capteur dimensionnel
 * toutes les tempsEntrePieceSeconde.
 */
void taskPresPiece(int probaSurMille, int tempsEntrePiece) 
{
	int generatedNumber;
	semTake(SemInitProd, WAIT_FOREVER);
	
	/*im gessing that we are still going to generate pieces with the wrong sizes based on probaSurMille*/
	srand(time(NULL));/*placing a new seed for random generation*/
	
	
	
	for(;;) 
	{
		/*im going to asume that probaSurMille means that, if we have probaSUrMille = 5, every 5 good pieces*/
		/*we have a wrong one*/
		generatedNumber = rand() % 100000;/*i dont know how many times the for its gonna be executed, so i put
		a large amount of random numbers*/
		
		if(generatedNumber % probaSurMille == 0){/* bad piece :( */
			Dimension dim = {X+4,Y+2,Z+3}; /*doesnt matter*/
		}
		else{/* good piece :) */
			Dimension dim = {X,Y,Z};	
		}
		
		handlerCapteurDim(dim);
		taskDelay(sysClkRateGet()*tempsEntrePiece);
	}
}

/**
 * Initialise un carton et l'envoi dans la boite au lettres
 * pour la tache Presence carton.
 */
void taskPresCarton(int tempsEntreCarton) 
{
	Carton c;
	memset(&c, 0, sizeof(Carton));
	for(;;) 
	{	
		semGive(SemPresCart);
		/*msgQSend(BalPresCart,(char *)&c,sizeof(Carton),WAIT_FOREVER, MSG_PRI_NORMAL);*/
		taskDelay(sysClkRateGet()*tempsEntreCarton);
	}	
}

/**
 * Envoi un jeton dans le sémaphore pour indiquer qu'une 
 * nouvelle palette est arrivée toutes les temps secondes.
 */
void taskPresPalette(int tempsEntrePalette) 
{
	for(;;) 
	{	
		semGive(SemPresPal);
		taskDelay(sysClkRateGet()*tempsEntrePalette);
	}
}

/**
 * Vide la boite aux lettres des impressions.
 */
void taskImprimante()
{
	Carton imp;
	for(;;) 
	{	
		memset(&imp, 0, sizeof(Carton));
		msgQReceive(BalImp,(char *)&imp,sizeof(Carton),WAIT_FOREVER);
		
		/* Impression qui fait rien */
	}
}

/**
 * Appelle le handler d'AU.
 */
void taskSimuArretUrgence()
{
	handlerArretUrgence();
}
