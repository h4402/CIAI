#include "common.h"


void handlerCapteurDim(Dimension dim) 
{	
	Piece p;
	/* TODO: Rajouter un Random */ /* the random is not made here, is made when you asign sizes to pieces*/
	/* see tachsimu, piecepret*/
	if (X == dim.x && Y == dim.y && Z == dim.z)
	{
		p.bon = TRUE;
	
	}
	else
	{
		p.bon = FALSE;
	}
	p.dim = dim;
	
	/* Voir ce qu'on donne dans la boite aux lettres */
	msgQSend(BalPresPie,(char *)&p,sizeof(Piece),WAIT_FOREVER, MSG_PRI_NORMAL);
	
}

/**
 * L'arret d'urgence est termine.
 */
void handlerArretUrgence()
{
	semGive(SemArrUrgence);
}
