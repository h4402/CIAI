#include "TacheReelles.h"

/**
 * Tâches réelles de l'application
 */


void taskRempCart() 
{
	
	int nbCarton = 0;
	int file = 0;
	Piece p;
	MsgErrSign err;
	MsgFin msg;
	for (;;) 
	{
		Carton c;
		int i = 0;
		if (msgQReceive(BalPresCart,(char *)&c,sizeof(Carton), TIMEOUT_CART) == ERROR)
		{
			err.errNo = ERR_ABS_CARTON;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}
		 
		semTake(SemLongFileAttente, WAIT_FOREVER);
		file = LongFileAttente;
		semGive(SemLongFileAttente);
		if(file >= MAX_CARTON_ATTENTE) 
		{
			err.errNo = ERR_FILE_CARTONS;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}
		
		for(;;)
		{
			
			if (msgQReceive(BalPresPie,(char *)&p,sizeof(Piece), TIMEOUT_PIE) == ERROR)
			{
				err.errNo = ERR_NOT_ENOUGHT;
				err.temps = time(NULL);
				procEnvoiErreur(err);
			}
			else
			{
				if(i == 0) 
				{
					if(p.type == Piece_1)
						c.numLot = nbProd.numLot1;
					else
						c.numLot = nbProd.numLot2;
					c.nbPiece = 0;
					c.nbPieceDefect = 0;
					c.temps = time(NULL); 
					i += 1;
				}
				if(p.bon)
				{
					c.nbPiece += 1;
					if(c.nbPiece >= nbProd.nbPieceParCarton)
					{
						break;
					}
				}
				else
				{
					c.nbPieceDefect += 1;
					if (c.nbPieceDefect >= nbProd.seuilDefectParCarton)
					{
						err.errNo = ERR_PIECES_RATE;
						err.temps = time(NULL);
						procEnvoiErreur(err);
					}
				}
			}
		}
		
		if(nbCarton <= nbProd.nbCartonParPalette*nbProd.nbPalettes1)
		{
			c.type = Piece_1;
		}
		else 
		{
			c.type = Piece_2;
		}
		
		/* Le carton est fait */
		
		msg.paletteOuCarton = CARTON;
		msg.temps = time(NULL);
		
		procEnvoiMessage(msg);
		
		nbCarton += 1;
		
		semTake(SemLongFileAttente, WAIT_FOREVER);
		LongFileAttente += 1;
		semGive(SemLongFileAttente);
	}

}

void taskRempPal()
{
	int nbPalette = 0;
	int nbCarton = 0;
	MsgErrSign err;
	int attente = 0;
	MsgFin msg;
	int nbPalTotale = 0;
	int j = 0;
	semTake(SemInitProd, WAIT_FOREVER);
	nbPalTotale = nbProd.nbPalettes1 + nbProd.nbPalettes2;
	semGive(SemInitProd);
	semTake(SemFinProd, WAIT_FOREVER);
	for(j = 0;j < nbPalTotale;j++)
	{
		
		int i = 0;
		if (semTake(SemPresPal, TIMEOUT_PAL) == ERROR)
		{
			err.errNo = ERR_ABS_PALETTE;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}

		for(;;)
		{
			
			semTake(SemLongFileAttente, WAIT_FOREVER);
			if(LongFileAttente > 0)
			{
				LongFileAttente -= 1;
				semGive(SemLongFileAttente);
				if(nbCarton >= nbProd.nbCartonParPalette)
				{
					nbPalette += 1;
					nbCarton = 0;
					break;
				}
			}
			else
			{
				semGive(SemLongFileAttente);
			}
		}

		/* Palette est faite */
		
		msg.paletteOuCarton = PALETTE;
		msg.temps = time(NULL);
		
		semTake(SemNbPal, WAIT_FOREVER);
		if (nbPalette < nbProd.nbPalettes1)
		{
			/* Palette 1 est faite */
			msg.numLot = nbProd.numLot1;
			nbPal.nbPal1 += 1;
		}
		else
		{
			/* Palette 2 est faite */
			msg.numLot = nbProd.numLot2;
			nbPal.nbPal2 += 1;
		}
		semGive(SemNbPal);
		
		procEnvoiMessage(msg);
		
	}
	semGive(SemFinProd);
}


void taskGestArrUrg(int idRempCart, int idRempPal)
{
	MsgErrSign msg; 
	msg.errNo = ERR_AU;
	msg.temps = time(NULL);
	/* On prend le jeton du semaphore AU */
	semTake(SemArrUrgence,WAIT_FOREVER);
	
	/* On stoppe les taches de remplissage */
	taskSuspend(idRempCart);
	taskSuspend(idRempPal);
	
	
	procEnvoiErreur(msg);
	
	/* TODO : checker si on continue bien les taches */
	taskResume(idRempCart);
	taskResume(idRempPal);
}


/**
 * Procédures globales d'envoi de message
 */

void procEnvoiMessage(MsgFin msgFin)
{
	// C'est tout
	msgQSend(BalMessages, (char*)&msgFin, sizeof(MsgFin), NO_WAIT, MSG_PRI_NORMAL);
}

void procEnvoiErreur(MsgErrSign err)
{
	ClapetOuvert = 0;
	msgQSend(BalMessages, (char*)&err, sizeof(MsgErrSign),NO_WAIT,MSG_PRI_NORMAL);
	semTake(SemErrTraitee,WAIT_FOREVER);
}




