#include "initServer.h"
#include "envoi.h"
#include "reception.h"

/* ###### Tache d'initialisation du coté serveur de l'application ###### */

int initServer(MSG_Q_ID balEnvoi, MSG_Q_ID balReception)
{
	int sock, sockC;
	
	struct sockaddr_in saddr, caddr;
	int size_addr;
	size_addr = sizeof(struct sockaddr_in);
	
	/*Création de la socket*/	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	FAIL(sock)
		
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_addr.s_addr = inet_addr(PROTO_ADDR);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PROTO_PORT);
	
	puts(inet_ntoa(saddr.sin_addr));
	
	FAIL(bind(sock,(struct sockaddr *)&saddr, sizeof(saddr)))
	
	FAIL(listen(sock, 1))
	
	sockC = accept(sock, (struct sockaddr *)&caddr, &size_addr);
	FAIL(sockC)
	puts("accepted");
	
	/*Création de la tache Reception en liaison avec la socket*/
	receptionId =  taskSpawn("Reception", PRIORITY,  0, STACK_SIZE, (FUNCPTR)reception, (int)balReception , sockC,0,0,0,0,0,0,0,0);
	/*Création de la tache Envoi en liaison avec la socket*/
	envoiId =  taskSpawn("Envoi", PRIORITY,  0, STACK_SIZE, (FUNCPTR)envoi, (int)balEnvoi , sockC,0,0,0,0,0,0,0,0);
}
