#include "common.h"

#include "handler.h"
#include "TacheSimu.h"

#define X 5
#define Y 5
#define Z 5

void taskPresPiece(int probaSurMille, int tempsEntrePiece) {
	semTake(SemInitProd, WAIT_FOREVER);
	for(;;) {
		Dimension dim = {X,Y,Z};
		handlerCapteurDim(dim);
		taskDelay(sysClkRateGet()*tempsEntrePiece);
	}
}

void taskPresCarton(int tempsEntreCarton) 
{
	Carton c;
	memset(&c, 0, sizeof(Carton));
	for(;;) 
	{	
		msgQSend(BalPresCart,(char *)&c,sizeof(Carton),WAIT_FOREVER, MSG_PRI_NORMAL);
		taskDelay(sysClkRateGet()*tempsEntreCarton);
	}	
}

void taskPresPalette(int tempsEntrePalette) 
{
	for(;;) 
	{	
		semGive(SemPresPal);
		taskDelay(sysClkRateGet()*tempsEntrePalette);
	}
}

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

// TODO : (dans la simulation) est-ce que l'arret d'urgence survient de temps en temps, ou bien
// doit-on l'actionner nous-meme (plus probable)
void taskSimuArretUrgence()
{
	handlerArretUrgence();
}
