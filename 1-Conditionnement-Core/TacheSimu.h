#ifndef _TACHE_SIMU_H_
#define _TACHE_SIMU_H_

#include "common.h"

/**
 * Tache qui envoi des pieces au capteur dimensionnel
 * toutes les tempsEntrePieceSecondes.
 */
void taskPresPiece(int probaSurMille, int tempsEntrePiece);

/**
 * Envoi des cartons dans remplirCarton.
 */
void taskPresCarton(int tempsEntreCarton);

/**
 * Envoi des palettes dans remplirPalette.
 */
void taskPresPalette(int tempsEntrePalette);

/**
 * Récupère les étiquettes à imprimer.
 */
void taskImprimante();

/**
 * Est activée lors d'un arrêt d'urgence.
 */
void taskSimuArretUrgence();

#endif
