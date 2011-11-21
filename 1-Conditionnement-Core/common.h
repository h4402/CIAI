#ifndef _COMMON_H_
#define _COMMON_H_

#include <semLib.h>
#include <msgQLib.h>
#include <wdLib.h>
#include <time.h>
#include <string.h>
#include <taskLib.h>
#include <sysLib.h>
#include <stdlib.h>

/**
 * Taille des pieces.
 */
#define X 5
#define Y 5
#define Z 5

#define TIMEOUT_CART 42
#define TIMEOUT_PIE 42
#define TIMEOUT_PAL 42
#define TIMEOUT_FIL 42

#define MAX_CARTON_ATTENTE 10
#define DEFAULT_STACK_SIZE 1000
#define DEFAULT_PRIO 42

#define MAX_PRESENCE_PIECE 100

#define DEFAULT_PROBA_PIECE_DEFECT_SUR_1000 10

/* En secondes */
#define TEMPS_ENTRE_CARTON 10
#define TEMPS_ENTRE_PALETTE 10
#define TEMPS_ENTRE_PIECE 10

/* Priorite de chaque tache */
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
 * Definitions de types.
 */
#define Boolean int

/**
 * Structures de Boites aux Lettres
 * et de toutes les donnees manipulees.
 */

/**
 * Message d'erreurs.
 */
typedef enum {
	ERR_UNKNOWN,
	ERR_ABS_CARTON,
	ERR_PIECES_RATE,
	ERR_PRINTER,
	ERR_ABS_PALETTE,
	ERR_FILE_CARTONS,
	ERR_AU,
	ERR_NOT_ENOUGHT,
	ERR_PASTIQ
}errorsType;/* Sera caste en UINT8 */

/**
 * Message de succes.
 */
typedef enum {
	MSG_UNKNOWN,
	MSG_PROD_CFG,
	MSG_PROD_ORD,
	MSG_EXP_ORD,
	MSG_ERR_SOLV,
	MSG_ERR_SIGN,
	MSG_PAL_PLEINE,
	MSG_EXP_RES,
	MSG_END_OF_PROD,/* Pas de datagramme associe */
	MSG_CART_PLUS, /* Carton plein */
	MSG_CART_MOINS /* Carton sur palette */
}msgTypes;/* Sera caste en UINT8 */
 
typedef enum {
	Piece_1,
	Piece_2
} TypePiece;

typedef struct {
	UINT16 nbPieceParCarton;
	UINT16 nbCartonParPalette;
	UINT16 nbPalettes1;
	UINT16 nbPalettes2;
	UINT16 seuilDefectParCarton;
	UINT16 numLot1;
	UINT16 numLot2;
	char numOp[5];
} Prod;

typedef struct {
	int numLot;
	TypePiece type;
	int nbPiece;
	int codeOp;
	time_t temps;
	int nbPieceDefect;
} Carton;

typedef struct {
	int x;
	int y;
	int z;
} Dimension;

typedef struct {
	Dimension dim;
	Boolean bon;
} Piece;

typedef struct
{
	UINT8 errNo;
	UINT8 reprise;
}MsgErrSolv;

typedef struct
{
	UINT8 errNo;
	time_t temps;
}MsgErrSign;

typedef enum {
	PALETTE,
	CARTON
} TypeMessage;

typedef struct
{
	UINT8 paletteOuCarton; /* Carton ou palette */
	time_t temps;
	UINT16 numLot;
}MsgFin;

typedef struct {
	int nbPal1;
	int nbPal2;
} NbPal;

/**
 * Zone de memoire partagees.
 */
static int LongFileAttente;

static Boolean ClapetOuvert;

static Prod nbProd;

static NbPal nbPal; 

/**
 * Constantes pratiques pour parametrer le programme.
 */

/**
 * Memoires partagees globales
 */

MSG_Q_ID BalPresPie;

MSG_Q_ID BalMessages;

MSG_Q_ID BalPresCart;

MSG_Q_ID BalPresPal;

MSG_Q_ID BalImp;

/**
 * Semaphores partages.
 * Ces semaphores sont globaux car ils sont utilises
 * par des procedures qui peuvent etre appelees par
 * toutes les taches, nous ne les passons donc pas en parametres.
 */
SEM_ID SemErrTraitee;

SEM_ID SemArrUrgence;

SEM_ID SemInitProd;

SEM_ID SemLongFileAttente;

SEM_ID SemPresPal;

SEM_ID SemNbPal;

SEM_ID SemFinProd;

SEM_ID SemPresCart;

#endif
