#include "gererMessRec.h"

/* ###### Tache de gestion des messages en envoi ###### */

int gererMessRec(MSG_Q_ID balReception, MSG_Q_ID balCommande, MSG_Q_ID balResErreur)
{
	char buff[32];
	MsgExpOrd messComm;
	MsgProdCfg messConf;
	MsgProdOrd messProd;
	MsgErrSolv messErr;
	int nb;
	UINT8 type;
	
	for(;;)
	{
		memset(buff, 0, 32);
		/* Lecture du message dans la boite au lettre "Reception" */
		nb = msgQReceive(balReception, buff, SIZE_BUFF, WAIT_FOREVER);
		FAIL(nb)
		
		type = (UINT8)buff[1];
		buff +=1;
		/* On connait le type du message et on défini la taille du message */
		switch(type)
		{
			/* Si c'est une configuration de production */
			case MSG_PROD_CFG:
				messConf = (MsgProdCfg)*buff;
				nbProd.nbPieceParCarton = messConf.pieceParCarton;
				nbProd.nbCartonParPalette = messConf.cartonParPalette;
				nbProd.seuilDefectParCarton = messConf.maxMauvais;
				break;
			/* Si c'est un ordre de production */	
			case MSG_PROD_ORD:
				messProd = (MsgProdOrd)*buff;
				nbProd.numLot1 = messProd.numLot1;
				nbProd.numLot2 = messProd.numLot2;
				nbProd.nbPalettes1 = messProd.nbLot1;
				nbProd.nbPalettes2 = messProd.nbLot2;
				strcpy(nbProd.numOp, messProd.opCode);
				semGive(semProd);
				break;
			/* Si c'est un ordre d'expedition */	
			case MSG_EXP_ORD:
				messComm = (MsgExpOrd)*buff;
				/* Envoi du message dans la boite au lettre de "Commande" */
				FAIL(msgQSend(balCommande, (char*)&messComm, sizeof(messComm), WAIT_FOREVER, MSG_PRI_NORMAL))
				break;
			/* Si c'est une resolution d'erreur */	
			case MSG_ERR_SOLV:
				messErr = (MessErr)*buff;
				/* Envoi du message dans la boite au lettre de "Resolution d'erreur" */
				FAIL(msgQSend(balResErreur, (char*)&messErr, sizeof(messErr), WAIT_FOREVER, MSG_PRI_NORMAL))
				break;
			default:
				puts("Unknown Message detected");
				break;
		}	
	}
}
