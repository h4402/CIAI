#include "common.h"

void handlerCapteurDim(Dimension dim) 
{	
	
	/* Renvoi toujours un bon truc */
	Piece p;
	p.type = 0;
	p.bon = TRUE;
	p.dim = dim;
	
	/* Voir ce qu'on donne dans la boite aux lettres */
	msgQSend(BalPresPie,(char *)&p,sizeof(Piece),WAIT_FOREVER, MSG_PRI_NORMAL);
	
}


void handlerArretUrgence()
{
	semGive(SemLongFileAttente);
}
