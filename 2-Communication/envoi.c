#include "envoi.h"

int envoi(MSG_Q_ID balEnvoi, int sock)
{
	char buff[SIZE_BUFF];
	int nb, nbSent, total;

	for(;;)
	{
		nb = msgQReceive(balEnvoi, buff, SIZE_BUFF, WAIT_FOREVER);
		FAIL(nb)
		
		total = nb;
		nbSent = 0;
		while(nbSent < total)
		{
			nb = send(sock, buff, nb, 0);
			FAIL(nb)
			nbSent += nb;
			buff += nb;
		}
		puts("sent");
	}
	
}
