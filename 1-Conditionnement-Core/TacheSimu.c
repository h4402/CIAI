#include "common.h"

#include "handler.h"
#include "TacheSimu.h"

#define X 5
#define Y 5
#define Z 5

/**
 * Prend le sémaphore d'init de la production lors du lancement.
 * Boucle infinie qui appelle le capteur dimensionnel
 * toutes les tempsEntrePieceSeconde.
 */
void taskPresPiece(int probaSurMille, int tempsEntrePiece) 
{
	semTake(SemInitProd, WAIT_FOREVER);
	for(;;) 
	{
		Dimension dim = {X,Y,Z};
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
