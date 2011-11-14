#include <taskLib.h>
#include <semLib.h>
#include <msqLib.h>
#include <wdLib.h>

#include "common.h"

/* TODO: Boite aux lettre des messages logs
 *       Morceaux AnaBenj
 * 		 Attente
 *       Gérer prio
 *       Structure Palette
 *       Ce qu'il y a dans les fonctions!
 */

int appli() {

	/* ######################## Phase de création ########################*/
	
	/* =========================== Simulation ======================== */
	
	/* Simulation de Présence Carton */
	MSQ_ID BalPresCart = msgQCreate(MAX_PRESENCE_CARTON, sizeof(Carton), MSG_Q_FIFO);
	int idPresCart = taskSpawn("presenceCarton", PRIO_PRESENCE_CARTON, 0, STACK_PRESENCE_CARTON,
		    taskPresCart, BalPresCart, TEMPS_ENTRE_CARTON, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de Présence Palette */
	MSQ_ID BalPresPal = msgQCreate(MAX_PRESENCE_PALETTE, sizeof(Palette), MSG_Q_FIFO);
	int idPresPal = taskSpawn("presencePalette", PRIO_PRESENCE_PALETTE, 0, STACK_PRESENCE_PALETTE,
			taskPresPalette, BalPresPal, TEMPS_ENTRE_PALETTE, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de l'envoi de pièce au capteur dimensionnel */
	int idPresPie = taskSpawn("presencePiece", PRIO_PRESENCE_PIECE, 0, STACK_PRESENCE_PIECE,
			taskPresPiece, DEFAULT_PROBA_PIECE_DEFECT_SUR_1000, TEMPS_ENTRE_PIECE, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation d'impression qui va imprimer les messages de la BAL */
	MSQ_ID BalImp = msgQCreate(MAX_ETIQUETTE, sizeof(Carton), MSG_Q_FIFO);
	int idImp = taskSpawn("imprimante", PRIO_IMPRIMANTE, 0, STACK_IMPRIMANTE,
			taskImprimante, BalImp, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* ================================================================= */
	
	LongFilAttente = 0;
	SEM_ID SemLongFileAttente = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
	
	/* Remplir Carton */
	WDOG_ID wdCart = wdCreate();
	int idRempCart = taskSpawn("remplirCarton", PRIO_REMPLIR_CARTON, 0, STACK_REMPLIR_CARTON,
			taskRempCart, BalPresCart, BalImp, SemLongFileAttente, wdCart, 0, 0, 0, 0, 0, 0);
	
	/* Remplir Palette */
	int idRempPal = taskSpawn("remplirPalette", PRIO_REMPLIR_PALETTE, 0, STACK_PRESENCE_PALETTE,
			taskRempPal, BalPresPal, SemLongFileAttente, 0, 0, 0, 0, 0, 0, 0, 0);

	/* Gestion des erreurs standards */
	SemErrTraitee = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	int idGestErr = taskSpawn("gestionErreur", PRIO_GESTION_ERREUR, 0, STACK_GESTION_ERREUR,
			taskGestErreur, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Gestion de l'arret d'urgence */
	SemArrUrgence = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	int idGestArrUrg = taskSpawn("gestionArretUrgence", PRIO_GESTION_ARRET_URGENCE, 0, STACK_GESTION_ARRET_URGENCE,
			taskGestArrUrg, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	 
	/* ######################## Phase d'attente ########################*/
	 
		/* Faire quelque chose pour attendre. */
	
	/* ######################## Phase de suppression ########################*/
	 
	wdDelete(wdCart);
	
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
	
	msqQdelete(BalPresCart);
	msqQdelete(BalImp);
	msqQdelete(BalPresPal);
	
	return 0;
	
}
