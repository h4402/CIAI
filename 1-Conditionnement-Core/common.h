#ifndef _COMMON_H_
#define _COMMON_H_

#include <semLib.h>

#define DEFAULT_STACK_SIZE 1000

#define DEFAULT_PROBA_PIECE_DEFECT_SUR_1000 10

#define PRIO_REMPLIR_CARTON 42
#define PRIO_PRESENCE_CARTON 42
#define PRIO_PRESENCE_PALETTE 42
#define PRIO_PRESENCE_PIECE 42
#define PRIO_GESTION_ERREUR 42
#define PRIO_GESTION_ARRET_URGENCE 42
#define PRIO_REMPLIR_PALETTE 42

#define MAX_PRESENCE_CARTON 42
#define MAX_PRESENCE_PALETTE 42
#define MAX_ETIQUETTE 42

#define Boolean int

typedef struct {
	int nbALarrache;
} Carton;

typedef struct {
	int nbALarrache;
} Palette;

typedef struct {
	int numLot;
	int nbPiece;
	int codeOp;
	int time;
	int nbPieceDefect;
} Etiquette;

typedef struct {
	int x;
	int y;
	int z;
} Dimension;

typedef struct {
	Dimension dim;
	Boolean bon;
} Piece;

/* Simulation */

extern void taskPresCart(MSQ_ID BalPresCart);

extern void taskPresPalette(MSQ_ID BalPresPal);

extern void taskPresPiece(int probaSurMille);

extern void taskImprimante(MSQ_ID BalImp);

/* Vrai */

extern void handlerCapteurDim(Dimension dim);

extern void taskRempCart(MSQ_ID BalPresCart, MSQ_ID BalImp, SEM_ID SemLongFileAttente);

extern void taskGestErreur();

extern void handlerArretUrgence();

extern void taskGestArrUrg();

extern void envoieErreur();

extern void taskRempPal(MSQ_ID BalPresPal, SEM_ID SemLongFileAttente);

extern void envoieMessage();

static int LongFilAttente;

static int ClapetOuvert;

SEM_ID SemErrTraitee;

SEM_ID SemArrUrgence;

#endif
