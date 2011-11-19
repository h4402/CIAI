#include "common.h"

#include "TacheSimu.h"
#include "TacheReelles.h"

/* TODO: Boite aux lettre des messages logs
 *       Morceaux AnaBenj
 * 		 Attente
 *       Gérer prio
 */

int appli() {
	
	int idPresCart;
	int idPresPal;
	int idPresPie;
	int idImp;
	int idRempCart;
	int idRempPal;
	int idGestErr;
	int idGestArrUrg;

	/* ######################## Phase de création ########################*/
	
	memset(&nbProd, 0, sizeof(Prod));
	SemInitProd = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	
	memset(&nbPal, 0, sizeof(NbPal));
	SemNbPal = semBCreate(SEM_Q_FIFO, SEM_FULL);
	
	SemFinProd = semBCreate(SEM_Q_FIFO, SEM_FULL);
	
	/* =========================== Simulation ======================== */
	
	/* Simulation de Présence Carton */
	SemPresCart = semCCreate(SEM_Q_FIFO, 0);
	idPresCart = taskSpawn("presenceCarton", PRIO_PRESENCE_CARTON, 0, STACK_PRESENCE_CARTON,
			(FUNCPTR)taskPresCarton,TEMPS_ENTRE_CARTON, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de Présence Palette */
	SemPresPal = semCCreate(SEM_Q_FIFO, 0);
	idPresPal = taskSpawn("presencePalette", PRIO_PRESENCE_PALETTE, 0, STACK_PRESENCE_PALETTE,
			(FUNCPTR)taskPresPalette, TEMPS_ENTRE_PALETTE, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de l'envoi de pièce au capteur dimensionnel */
	BalPresPie = msgQCreate(MAX_PRESENCE_PIECE, sizeof(Piece), MSG_Q_FIFO);
	idPresPie = taskSpawn("presencePiece", PRIO_PRESENCE_PIECE, 0, STACK_PRESENCE_PIECE,
			(FUNCPTR)taskPresPiece, DEFAULT_PROBA_PIECE_DEFECT_SUR_1000, TEMPS_ENTRE_PIECE, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation d'impression qui va imprimer les messages de la BAL */
	BalImp = msgQCreate(MAX_ETIQUETTE, sizeof(Carton), MSG_Q_FIFO);
	idImp = taskSpawn("imprimante", PRIO_IMPRIMANTE, 0, STACK_IMPRIMANTE,
			(FUNCPTR)taskImprimante, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* ================================================================= */
	
	LongFileAttente = 0;
	SemLongFileAttente = semBCreate(SEM_Q_FIFO, SEM_FULL);
	
	/* Remplir Carton */
	idRempCart = taskSpawn("remplirCarton", PRIO_REMPLIR_CARTON, 0, STACK_REMPLIR_CARTON,
			(FUNCPTR)taskRempCart, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Remplir Palette */
	idRempPal = taskSpawn("remplirPalette", PRIO_REMPLIR_PALETTE, 0, STACK_PRESENCE_PALETTE,
			(FUNCPTR)taskRempPal, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	/* Gestion des erreurs standards */
	SemErrTraitee = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	idGestErr = taskSpawn("gestionErreur", PRIO_GESTION_ERREUR, 0, STACK_GESTION_ERREUR,
			(FUNCPTR)taskGestErreur, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Gestion de l'arret d'urgence */
	SemArrUrgence = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	idGestArrUrg = taskSpawn("gestionArretUrgence", PRIO_GESTION_ARRET_URGENCE, 0, STACK_GESTION_ARRET_URGENCE,
			(FUNCPTR)taskGestArrUrg, idRempCart, idRempPal, 0, 0, 0, 0, 0, 0, 0, 0);
	 
	/* ######################## Phase d'attente ########################*/
	 
		semTake(SemFinProd, WAIT_FOREVER);
		/* Faire quelque chose pour attendre. */
	
	/* ######################## Phase de suppression ########################*/
	
	taskDelete(idGestArrUrg);
	taskDelete(idGestErr);
	taskDelete(idRempPal);
	taskDelete(idRempCart);
	
	taskDelete(idImp);
	taskDelete(idPresPie);
	taskDelete(idPresPal);
	taskDelete(idPresCart);
	
	semDelete(SemArrUrgence);
	semDelete(SemErrTraitee);
	semDelete(SemLongFileAttente);	
	 
	msgQDelete(BalPresCart);
	msgQDelete(BalImp);
	msgQDelete(BalPresPal);
	
	return 0;
	
}
