#if ! defined ( INISER_H_ )
#define INISER_H_

#include <errno.h>
#include <types.h>
#include <socket.h>
#include <sockLib.h>
#include "inetLib.h" 
#include <stdio.h>
#include <selectLib.h>
#include "protocole.h"

#define FAIL(x) if(x == -1) {\
perror(#x);}

#define SIZE_BUFF 1000
#define PRIORITY 100
#define STACK_SIZE 2000

int receptionId, envoiId;

int initServer(MSG_Q_ID balEnvoi, MSG_Q_ID balReception);

#endif //INISER
