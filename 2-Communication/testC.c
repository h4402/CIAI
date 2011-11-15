#include "initServer.h"

#define MAX_MESSAGES 200

int main()
{
	int initServerId, nb;
	char buff[SIZE_BUFF];
	MSG_Q_ID balEnvoi, balReception;
	balEnvoi = msgQCreate(MAX_MESSAGES, SIZE_BUFF, MSG_Q_FIFO);
	balReception = msgQCreate(MAX_MESSAGES, SIZE_BUFF, MSG_Q_FIFO);
    
	initServerId =  taskSpawn("initServer", PRIORITY,  0, STACK_SIZE, (FUNCPTR)initServer, (int)balEnvoi, (int)balReception ,0,0,0,0,0,0,0,0);
	
	nb = msgQReceive(balReception, buff, SIZE_BUFF, WAIT_FOREVER);
	FAIL(nb)
	puts(buff);
	
	FAIL(msgQSend(balEnvoi, "Plop\n", 6, WAIT_FOREVER, MSG_PRI_NORMAL))
	
	exit(0);
}
