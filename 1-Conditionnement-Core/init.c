#include <taskLib.h>
#include <semLib.h>

#include "common.h"

/* TODO: Mettre des stacks size specifiques */
/* TODO: Définir des bonnes structures */
/* TODO: Boite aux lettre des messages logs */
/* TODO: Watchdog piece manquante... *

int main() {
	
	/* =========================== Simulation ======================== */
	
	/* Simulation de Présence Carton */
	MSQ_ID BalPresCart = msgQCreate(MAX_PRESENCE_CARTON, sizeof(Carton), MSG_Q_FIFO);
	int idPresCart = taskSpawn("presenceCarton", PRIO_PRESENCE_CARTON, 0, DEFAULT_STACK_SIZE,
		    taskPresCart, BalPresCart, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de Présence Palette */
	MSQ_ID BalPresPal = msgQCreate(MAX_PRESENCE_PALETTE, sizeof(Palette), MSG_Q_FIFO);
	int idPresPal = taskSpawn("presencePalette", PRIO_PRESENCE_PALETTE, 0, DEFAULT_STACK_SIZE,
			taskPresPalette, BalPresPal, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation de l'envoi de pièce au capteur dimensionnel */
	int idPresPie = taskSpawn("presencePiece", PRIO_PRESENCE_PIECE, 0, DEFAULT_STACK_SIZE,
				taskPresPiece, DEFAULT_PROBA_PIECE_DEFECT_SUR_1000, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Simulation d'impression qui va imprimer les messages de la BAL */
	MSQ_ID BalImp = msgQCreate(MAX_ETIQUETTE, sizeof(Etiquette), MSG_Q_FIFO);
	int idImp = taskSpawn("imprimante", PRIO_IMPRIMANTE, 0, DEFAULT_STACK_SIZE,
					taskImprimante, BalImp, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* ================================================================= */
	
	LongFilAttente = 0;
	SEM_ID SemLongFileAttente = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
	
	/* Remplir Carton */
	int idRempCart = taskSpawn("remplirCarton", PRIO_REMPLIR_CARTON, 0, DEFAULT_STACK_SIZE,
		taskRempCart, BalPresCart, BalImp, SemLongFileAttente, 0, 0, 0, 0, 0, 0, 0);
	
	/* Remplir Palette */
	int idRempPal = taskSpawn("remplirPalette", PRIO_REMPLIR_PALETTE, 0, DEFAULT_STACK_SIZE,
		taskRempPal, BalPresPal, SemLongFileAttente, 0, 0, 0, 0, 0, 0, 0, 0);

	/* Gestion des erreurs standards */
	SemErrTraitee = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	int idGestErr = taskSpawn("gestionErreur", PRIO_GESTION_ERREUR, 0, DEFAULT_STACK_SIZE,
			taskGestErreur, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* Gestion de l'arret d'urgence */
	SemArrUrgence = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
	int idGestArrUrg = taskSpawn("gestionArretUrgence", PRIO_GESTION_ARRET_URGENCE, 0, DEFAULT_STACK_SIZE,
			taskGestArrUrg, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	/* TODO Ajouter taches faites par Anabenj:
	 *    -- Conditionner commande
	 *    -- Communication
	 *    -- Gérer messages
	 *    -- Gérer Journal de bord
	 */  
	
	return 0;
	
}
