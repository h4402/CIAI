#ifndef _TACHE_REELLES_H
#define _TACHE_REELLES_H

#include "common.h"

/**
 * Recupère des cartons et des pièces et les rempli
 * pour les placer dans la file d'attente.
 */
void taskRempCart();

/**
 * Récupère des cartons de la file d'attente, et
 * les place sur des palettes.
 */
void taskRempPal();

/**
 * Tache qui arrete la production lors d'un arret d'urgence.
 */
void taskGestArrUrg();

/**
 * Tache qui gère les petites erreurs et le message de résolution de l'IHM.
 */
void taskGestErreur();

/**
 * Envoi un message de réussite à la BAL de com.
 */
void procEnvoiMessage(MsgFin msgFin);

/**
 * Envoi un message d'erreur à la BAL de com.
 */
void procEnvoiErreur(MsgErrSign msgErr);

#endif
