#include "gererMessRec.h"

int gererMessRec(MSG_Q_ID balReception, MSG_Q_ID balCommande, MSG_Q_ID balResErreur)
{
	char buff[32];
	MessCommande messComm;
	int nb;
	UINT8 type;
	
	for(;;)
	{
		memset(buff, 0, 32);
		nb = msgQReceive(balReception, buff, SIZE_BUFF, WAIT_FOREVER);
		FAIL(nb)
		
		type = (UINT8)buff[1];
		switch(type)
		{
			case 1:
				messConf = (MessConf)(*(buff+1));
				nbProd.pieceParCartons = messConf.pieceParCarton;
				nbProd.cartonParPalette = messConf.cartonParPalette;
				nbProd.maxPieceRebut = messConf.maxPieceRebut;
				break;
			case 2:
				messProd = (MessProd)(*(buff+1));
				nbProd.nbLot1 = messProd.nbLot1;
				nbProd.nbLot2 = messProd.nbLot2;
				nbProd.nbType1 = messProd.nbType1;
				nbProd.nbType2 = messProd.nbType2;
				nbProd.nbOp = messProd.codeOp;
				semGive(semProd);
				break;
			case 3:
				messComm = (MessCommande)(*(buff+1));
				FAIL(msgQSend(balCommande, (char*)&messComm, sizeof(messComm), WAIT_FOREVER, MSG_PRI_NORMAL))
				break;
			case 4:
				messErr = (MessErr)(*(buff+1));
				FAIL(msgQSend(balCommande, (char*)&messErr, sizeof(messErr), WAIT_FOREVER, MSG_PRI_NORMAL))
				break;
		}	
	}
}
