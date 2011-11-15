#include "initServer.h"
#include "envoi.h"
#include "reception.h"

int initServer(MSG_Q_ID balEnvoi, MSG_Q_ID balReception)
{
	int receptionId, envoiId, sock, sockC;
	
	struct sockaddr_in saddr, caddr;
	int size_addr;
	size_addr = sizeof(struct sockaddr_in);
		
	sock = socket(AF_INET, SOCK_STREAM, 0);
	FAIL(sock)
		
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	
	puts(inet_ntoa(saddr.sin_addr));
	
	FAIL(bind(sock,  (struct sockaddr *)&saddr, sizeof(saddr)))
	
	FAIL(listen(sock, 1))
	
	sockC = accept(sock, (struct sockaddr *)&caddr, &size_addr);
	FAIL(sockC)
	puts("accepted");
	
	receptionId =  taskSpawn("Reception", PRIORITY,  0, STACK_SIZE, (FUNCPTR)reception, (int)balReception , sockC,0,0,0,0,0,0,0,0);
	envoiId =  taskSpawn("Envoi", PRIORITY,  0, STACK_SIZE, (FUNCPTR)envoi, (int)balEnvoi , sockC,0,0,0,0,0,0,0,0);
}
