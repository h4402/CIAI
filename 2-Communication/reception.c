#include "reception.h"

/* ###### Tache de reception des messages coté serveur depuis le coté client ###### */

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
		/* Reception du message de l'IHM */
		nb = recv(sock, buff, 32, 0);
		FAIL(nb)
		total += nb;
		
		/* Si on a assez de données, on lit le type du message */
		if(nb >= 1 && init == 0)
		{
			type = (UINT8)buff[1];
			/* On connait le type du message et on défini la taille du message */
			switch(type)
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
			/* Envoi du message dans la boite au lettre "Reception" */
			FAIL(msgQSend(balReception, buff, total, WAIT_FOREVER, MSG_PRI_NORMAL))
			total = 0;
			messSize = 0;
			memset(buff, 0, 32);	
		}
	}
}
