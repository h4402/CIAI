#include "gererMessEnvoi.h"
#include <string.h>
#include <sysLib.h>

int gererMessEnvoi(MSG_Q_ID balEnvoi, MSG_Q_ID balJournal, MSG_Q_ID balMessages)
{
	
	char buff[1000];
	char env[32];
	char envJournal[64];
	MsgErrSign messErr;
	MsgExpRes messExp;
	int finProd;
	
	int nb;
	UINT8 type;
	
	finProd = 0;
	
	for(;;)
	{
		nb = msgQReceive(balMessages, buff, SIZE_BUFF, sysClkRateGet()*BAL_MSG_TIMEOUT);
		FAIL(nb)
		if(nb != ERROR)
		{
			
			type = (UINT8)buff[1];
			
			if(type < 9)
			{
				messErr.errNo = type;
				memcpy(env+1, &messErr, sizeof(MsgErrSign));
				env[1] = (UINT8)10;
				
				memcpy(envJournal+(1 + sizeof(time_t)), &messErr, sizeof(MsgErrSign));
				memcpy(envJournal+1, buff+1, sizeof(time_t));
				envJournal[1] = (UINT8)10;
				
				FAIL(msgQSend(balJournal, env, sizeof(time_t)+sizeof(MsgErrSign)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				FAIL(msgQSend(balEnvoi, env, sizeof(MsgErrSign)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
			else if(type == 11)
			{
				env[1] = (UINT8)type;
				
				memcpy(envJournal+(1 + sizeof(time_t)), &messErr, sizeof(MsgErrSign));
				memcpy(envJournal+1, buff+1, sizeof(time_t));
				envJournal[1] = (UINT8)type;
				
				FAIL(msgQSend(balJournal, env, sizeof(time_t)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
			else if(type == 12)
			{
				messExp = (MsgExpRes)(*(buff+1+sizeof(time_t)));
				
				memcpy(env+1, &messExp, sizeof(MsgExpRes));
				env[1] = (UINT8)12;
				
				memcpy(envJournal+(1 + sizeof(time_t)), &messExp, sizeof(MsgExpRes));
				memcpy(envJournal+1, buff+1, sizeof(time_t));
				envJournal[1] = (UINT8)12;
				
				FAIL(msgQSend(balJournal, env, sizeof(time_t)+sizeof(MsgExpRes)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				FAIL(msgQSend(balEnvoi, env, sizeof(MsgExpRes)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
			else if(type == 13)
			{
				finProd = 1;
			}
			else
			{
				env[1] = (UINT8)type;
				FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
		}
		else
		{
			env[1] = (UINT8)13;
			FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
		}
	}
}
