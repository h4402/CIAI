#include "TacheReelles.h"

/**
 * Tâches réelles de l'application
 */

/**
 * Récupère des cartons et des pièces 
 * respectivement dans un sémaphore et dans une BAL.
 * Incrémente ensuite le compte de la file d'attente.
 */
/**
 * Pour le cas d'erreur, si on reprend comme prévu, tout est bon,
 * si on doit jeter le carton, alors on doit mettre un booleen a vrai,
 * sortir de la boucle qui remplir le carton, ne pas effectuer les
 * truc pour la fin de carton, décrémenter i, puis reprendre en début de boucle.
 */
void taskRempCart() 
{
	int file = 0;
	Piece p;
	MsgErrSign err;
	MsgFin msg;
	int i;
	int nbCarton = 0;
	int nbCartonMax;
	
	semTake(SemInitProd, WAIT_FOREVER);
	nbCartonMax = nbProd.nbCartonParPalette*nbProd.nbPalettes1 + nbProd.nbCartonParPalette*nbProd.nbPalettes2;
	semGive(SemInitProd);
	
	/* 
	 * TODO : lire l'état de l'imprimante ?
	 * TODO : Envoyer une erreur si elle est en panne.
	 */

	
	/* Boucle qui va remplir le bon nombre de cartons. */
	for (i = 0; i < nbCartonMax; i++) 
	{
		Carton c;
		memset(&c, 0, sizeof(Carton));
		
		/* Récupère un carton. */
		if (semTake(SemPresCart, TIMEOUT_CART) == ERROR)
		{
			/* Erreur: Pas de Carton */
			err.errNo = ERR_ABS_CARTON;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}
		
		/* Récupère la taille de la file d'attente. */
		semTake(SemLongFileAttente, WAIT_FOREVER);
		file = LongFileAttente;
		semGive(SemLongFileAttente);
		if(file >= MAX_CARTON_ATTENTE) 
		{
			/* Pas de place dans la file d'attente: Erreur */
			err.errNo = ERR_FILE_CARTONS;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}
		
		/* Boucle qui va remplir un carton. */
		for(;;)
		{
			/* On récupère une pièce. */
			if (msgQReceive(BalPresPie,(char *)&p,sizeof(Piece), TIMEOUT_PIE) == ERROR)
			{
				/* Erreur pas de pièces. */
				err.errNo = ERR_NOT_ENOUGHT;
				err.temps = time(NULL);
				procEnvoiErreur(err);
			}
			else
			{
				/* On vérifie si la pièce est bonne ici 
				 * (selon les informations du capteur dimensionnel)
				 * on triche un peu mais c'est pour facilité le comptage
				 * des pièces defectueuses par carton...
				 */
				if(p.bon)
				{
					c.nbPiece += 1;
					if(c.nbPiece >= nbProd.nbPieceParCarton)
					{
						/* On a fini de remplir le carton. */
						break;
					}
				}
				else
				{
					c.nbPieceDefect += 1;
					if (c.nbPieceDefect >= nbProd.seuilDefectParCarton)
					{
						/* Trop de pièces defectueuses. */
						err.errNo = ERR_PIECES_RATE;
						err.temps = time(NULL);
						procEnvoiErreur(err);
					}
				}
			}
		}
		
		/* Le carton est fait */
		
		/* On fini l'étiquette. */
		c.temps = time(NULL);
		if (nbCarton <= nbProd.nbCartonParPalette*nbProd.nbPalettes1)
		{
			c.type = Piece_1;
			c.numLot = nbProd.numLot1;
		}
		else 
		{
			c.type = Piece_2;
			c.numLot = nbProd.numLot2;
		}
		
		/* On imprime. */
		msgQSend(BalImp,(char *)&c,sizeof(Carton), WAIT_FOREVER, MSG_PRI_NORMAL);
		
		/* On envoi le message à la com. */
		msg.paletteOuCarton = CARTON;
		msg.temps = time(NULL);
		procEnvoiMessage(msg);
		
		/* On ajoute le carton à la file. */
		semTake(SemLongFileAttente, WAIT_FOREVER);
		LongFileAttente += 1;
		semGive(SemLongFileAttente);
	
	}

}

/**
 * Décrémente la file d'attente,
 * Créer des palettes avec des cartons.
 */
void taskRempPal()
{
	int nbPalette = 0;
	int nbCarton = 0;
	MsgErrSign err;
	MsgFin msg;
	int nbPalTotale = 0;
	int i;
	
	/* On récupère le nombre de palette à préparer. */
	semTake(SemInitProd, WAIT_FOREVER);
	nbPalTotale = nbProd.nbPalettes1 + nbProd.nbPalettes2;
	semGive(SemInitProd);
	
	/* Sémaphore qui signalera la fin de l'application. */
	semTake(SemFinProd, WAIT_FOREVER);
	
	/* On produit toutes les palettes. */
	for(i = 0;i < nbPalTotale;i++)
	{
		/* On récupère une palettte. */
		if (semTake(SemPresPal, TIMEOUT_PAL) == ERROR)
		{
			/* Erreur: Pas de palette. */
			err.errNo = ERR_ABS_PALETTE;
			err.temps = time(NULL);
			procEnvoiErreur(err);
		}

		/* On remplit une palette de cartons. */
		for(;;)
		{
			/* On prend un carton. */
			semTake(SemLongFileAttente, WAIT_FOREVER);
			if(LongFileAttente > 0)
			{
				LongFileAttente -= 1;
				semGive(SemLongFileAttente);
				if(nbCarton >= nbProd.nbCartonParPalette)
				{
					/* On a fini de remplir la palette. */
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

		/* La palette est faite */
		
		/* On crée un message. */
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
		/* On envoi le message. */
		procEnvoiMessage(msg);
		
		nbCarton = 0;
		
	}
	/* Toutes les palettes sont finies, on dit qu'on a terminé l'appli. */
	semGive(SemFinProd);
}

/**
 * Tache qui va bloquer les taches de production dans 
 * le cas d'un arret d'urgence. L'erreur d'AU est traitée comme une 
 * erreur normale.
 */
void taskGestArrUrg()
{
	MsgErrSign msg; 
	msg.errNo = ERR_AU;
	for (;;)
	{
		/* On prend le jeton du semaphore AU */
		semTake(SemArrUrgence,WAIT_FOREVER);
		msg.temps = time(NULL);
		procEnvoiErreur(msg);
	}
}

/**
 * Procédures globales d'envoi de message
 */

/**
 * Envoi un message dans la boite.
 */
void procEnvoiMessage(MsgFin msgFin)
{
	msgQSend(BalMessages, (char*)&msgFin, sizeof(MsgFin), NO_WAIT, MSG_PRI_NORMAL);
}

/**
 * Envoi une erreur dans la boite.
 */
void procEnvoiErreur(MsgErrSign err)
{
	ClapetOuvert = FALSE;
	msgQSend(BalMessages, (char*)&err, sizeof(MsgErrSign),NO_WAIT,MSG_PRI_NORMAL);
	semTake(SemErrTraitee,WAIT_FOREVER);
	
	/* TODO: réouvrir le clapet? 
	 * Dire si on fait un reprise ou pas?*/
}




