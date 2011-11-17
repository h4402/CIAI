#ifndef _TACHE_REELLES_H
#define _TACHE_REELLES_H

#include "common.h"

void taskRempCart();

void taskRempPal();

void taskGestArrUrg(int idRempCart, int idRempPal);
void procEnvoiMessage(MsgFin msgFin);

void procEnvoiErreur(MsgErrSign msgErr);

void taskGestErreur();

#endif
