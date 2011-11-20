#include "envoi.h"

/* ###### Tache d'envoi des messages coté serveur vers coté client ###### */

int envoi(MSG_Q_ID balEnvoi, int sock)
{
	char buff[SIZE_BUFF];
	int nb, nbSent, total;
	char* sending = (char *) buff[0];
	
	for(;;)
	{
		/* Recuperation des messages de la boite au lettre "Envoi" */
		nb = msgQReceive(balEnvoi, buff, SIZE_BUFF, WAIT_FOREVER);
		FAIL(nb)
		
		total = nb;
		nbSent = 0;
		while(nbSent < total)
		{
			/* Envoi du message vers l'IHM*/
			nb = send(sock, sending, nb, 0);
			FAIL(nb)
			nbSent += nb;
			sending += nb;
		}
		puts("sent");
	}
	
}
