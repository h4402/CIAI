#ifndef _TACHE_SIMU_H_
#define _TACHE_SIMU_H_

#include "common.h"

void taskPresPiece(int probaSurMille, int tempsEntrePiece);

void taskPresCarton(int tempsEntreCarton);

void taskPresPalette(int tempsEntrePalette);

void taskImprimante();

// TODO : (dans la simulation) est-ce que l'arret d'urgence survient de temps en temps, ou bien
// doit-on l'actionner nous-meme (plus probable)
void taskSimuArretUrgence();


#endif
