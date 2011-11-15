#include "reception.h"

int reception(MSG_Q_ID balReception, int sock)
{
	char buff[32];
	MessCommande messComm;
	int nb, total, messSize;
	UINT8 type;
	
	memset(buff, 0, 32);
	total = 0;
	messSize = 0;
	
	for(;;)
	{
		nb = recv(sock, buff, 32, 0);
		FAIL(nb)
		total += nb;
		
		if(nb >= 1 && init == 0)/*Si on a assez de données on lit le type du message*/
		{
			type = (UINT8)buff[1];
			switch(type)/*On connait le type du message on défini la taille du message*/
			{
				case 1:
					messSize = sizeof(MessConfig)+1);
					break;
				case 2:
					messSize = sizeof(MessOrdreProd)+1);
					break;
				case 3:
					messSize = sizeof(MessCommande)+1);
					break;
				case 4:
					messSize = sizeof(MessErr)+1);
					break;
			}
		}
		if(messSize != 0 && total = messSize)/*Si le message est complet on envoie dans la bonne BAL*/
		{
			puts("recv");
			FAIL(msgQSend(balReception, buff, total, WAIT_FOREVER, MSG_PRI_NORMAL))
			total = 0;
			messSize = 0;
			memset(buff, 0, 32);	
		}
	}
}
