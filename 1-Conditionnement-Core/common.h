#ifndef _COMMON_H_
#define _COMMON_H_

#include <semLib.h>
#include <msqLib.h>
#include <wdLib.h>

/**
 * Définitions de types.
 */
#define TRUE 1
#define FALSE 0
 
#define Boolean int

/**
 * Structures de Boites aux Lettres
 * et de toutes les données manipulées.
 */
 
enum TypePiece {
	Piece_1,
	Piece_2
};

typedef struct {
	int numLot;
	TypePiece type;
	int nbPiece;
	int codeOp;
	int time;
	int nbPieceDefect;
} Carton;

/* TODO: Quoi mettre? */
typedef struct {
	int nbALarrache;
} Palette;

typedef struct {
	int x;
	int y;
	int z;
} Dimension;

typedef struct {
	TypePiece type;
	Dimension dim;
	Boolean bon;
} Piece;

/**
 * Constantes pratiques pour paramétrer le programme.
 */
#define DEFAULT_STACK_SIZE 1000
#define DEFAULT_PRIO 42

#define DEFAULT_PROBA_PIECE_DEFECT_SUR_1000 10

/* En secondes */
#define TEMPS_ENTRE_CARTON 10
#define TEMPS_ENTRE_PALETTE 10
#define TEMPS_ENTRE_PIECE 10

/* Priorité de chaque tache */
#define PRIO_REMPLIR_CARTON DEFAULT_PRIO
#define PRIO_PRESENCE_CARTON DEFAULT_PRIO
#define PRIO_PRESENCE_PALETTE DEFAULT_PRIO
#define PRIO_PRESENCE_PIECE DEFAULT_PRIO
#define PRIO_GESTION_ERREUR DEFAULT_PRIO
#define PRIO_GESTION_ARRET_URGENCE DEFAULT_PRIO
#define PRIO_REMPLIR_PALETTE DEFAULT_PRIO
#define PRIO_IMPRIMANTE DEFAULT_PRIO

/* Taille de la pile de chaque tache */
#define STACK_REMPLIR_CARTON DEFAULT_STACK_SIZE
#define STACK_PRESENCE_CARTON DEFAULT_STACK_SIZE
#define STACK_PRESENCE_PALETTE DEFAULT_STACK_SIZE
#define STACK_PRESENCE_PIECE DEFAULT_STACK_SIZE
#define STACK_GESTION_ERREUR DEFAULT_STACK_SIZE
#define STACK_GESTION_ARRET_URGENCE DEFAULT_STACK_SIZE
#define STACK_REMPLIR_PALETTE DEFAULT_STACK_SIZE
#define STACK_IMPRIMANTE DEFAULT_STACK_SIZE

/* Taille des BAL. */
#define MAX_PRESENCE_CARTON 42
#define MAX_PRESENCE_PALETTE 42
#define MAX_ETIQUETTE 42

/**
 *  Taches spécifiques à la simulation 
 */
extern void taskPresCart(MSQ_ID BalPresCart);

extern void taskPresPalette(MSQ_ID BalPresPal);

extern void taskPresPiece(int probaSurMille);

extern void taskImprimante(MSQ_ID BalImp);

/** 
 * Taches Réélles 
 */
extern void taskRempCart(MSQ_ID BalPresCart, MSQ_ID BalImp, SEM_ID SemLongFileAttente, WDOG_ID wdCart);

extern void taskGestErreur();

extern void taskGestArrUrg();

extern void taskRempPal(MSQ_ID BalPresPal, SEM_ID SemLongFileAttente);

/**
 * Handler rééels (utilisés en simulation dans notre application.
 */
 
extern void handlerCapteurDim(Dimension dim);

extern void handlerArretUrgence();

/**
 * Autres procédures (pour éviter la redondance de code).
 */

extern void envoieMessage();

extern void envoieErreur();

/**
 * Zone de mémoire partagées.
 */
static int LongFilAttente;

static Boolean ClapetOuvert;

/**
 * Sémaphores partagés.
 * Ces sémaphores sont globaux car ils sont utilisés
 * par des procédures qui peuvent être appelées par
 * toutes les taches, nous ne les passons donc pas en paramètres.
 */
SEM_ID SemErrTraitee;

SEM_ID SemArrUrgence;

#endif
