#include "gererMessEnvoi.h"
#include <string.h>
#include <sysLib.h>

/* ###### Tache de gestion des messages en envoi ###### */

int gererMessEnvoi(MSG_Q_ID balEnvoi, MSG_Q_ID balJournal, MSG_Q_ID balMessages)
{
	char buff[1000];
	char env[32];
	char envJournal[64];
	MsgErrSign messErr;
	MsgExpRes messExp;
	MsgPalPleine messPal;
	int finProd;
	time_t date;
	
	int nb;
	UINT8 type;
	
	finProd = 0;
	
	for(;;)
	{
		/* Lecture du message dans la boite au lettre "Messages" */
		nb = msgQReceive(balMessages, buff, SIZE_BUFF, sysClkRateGet()*BAL_MSG_TIMEOUT);
		FAIL(nb)
		if(nb != ERROR)
		{
			
			type = (UINT8)buff[1];
			buff +=1;
			
			memcpy(&date, buff, sizeof(time_t));
			buff += sizeof(time_t);
			
			/* Si c'est une erreur */
			if(type < 9)
			{
				messErr.errNo = type;
				memcpy(env+1, &messErr, sizeof(MsgErrSign));
				env[1] = (UINT8)MSG_ERR_SIGN;
				
				memcpy(envJournal+(1 + sizeof(time_t)), &messErr, sizeof(MsgErrSign));
				memcpy(envJournal+1, &date, sizeof(time_t));
				envJournal[1] = (UINT8)MSG_ERR_SIGN;
				
				/* Envoi du message dans la boite au lettre de "Journal" */
				FAIL(msgQSend(balJournal, env, sizeof(time_t)+sizeof(MsgErrSign)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				/* Envoi du message dans la boite au lettre "Envoi" */
				FAIL(msgQSend(balEnvoi, env, sizeof(MsgErrSign)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
			/* Si c'est une palette qui est pleine */
			else if(type == MSG_PAL_PLEINE)
			{
				env[1] = (UINT8)type;
				messPal.numLot = (UINT16)*buff;
				memcpy(env+1, &messPal, sizeof(MsgPalPleine));
				
				envJournal[1] = (UINT8)type;
				memcpy(envJournal+(1 + sizeof(time_t)), &messPal, sizeof(MsgPalPleine));
				memcpy(envJournal+1, &date, sizeof(time_t));
				
				/* Envoi du message dans la boite au lettre de "Journal" */
				FAIL(msgQSend(balJournal, env, sizeof(time_t)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				/* Envoi du message dans la boite au lettre "Envoi" */
				FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
			/* Si c'est un retour d'expedition */
			else if(type == MSG_EXP_RES)
			{
				messExp = (MsgExpRes)*buff;
				
				memcpy(env+1, &messExp, sizeof(MsgExpRes));
				env[1] = (UINT8)12;
				
				/* Envoi du message dans la boite au lettre "Envoi" */
				FAIL(msgQSend(balEnvoi, env, sizeof(MsgExpRes)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				
				/* Si l'expedition est reussie */
				if(messExp.reussite == 1)
				{
					memcpy(envJournal+(1 + sizeof(time_t)), &messExp, sizeof(MsgExpRes));
					memcpy(envJournal+1, &date, sizeof(time_t));
					envJournal[1] = (UINT8)12;
					
					/* Envoi du message dans la boite au lettre de "Journal" */
					FAIL(msgQSend(balJournal, env, sizeof(time_t)+sizeof(MsgExpRes)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
				}
			}
			/* Si c'est une fin de production */
			else if(type == MSG_END_OF_PROD)
			{
				finProd = 1;
			}
			/* Si c'est un carton plein ou un nouveau carton sur une palette */
			else
			{
				env[1] = (UINT8)type;
				
				/* Envoi du message dans la boite au lettre "Envoi" */
				FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
			}
		}
		else
		{
			/* Lorsque c'est une fin de production */
			env[1] = (UINT8)MSG_END_OF_PROD;
			
			/* Envoi du message dans la boite au lettre "Envoi" */
			FAIL(msgQSend(balEnvoi, env, 1, WAIT_FOREVER, MSG_PRI_NORMAL))
			memcpy(env+1, &date, sizeof(time_t);
			
			/* Envoi du message dans la boite au lettre de "Journal" */
			FAIL(msgQSend(balJournal, env, sizeof(time_t)+1, WAIT_FOREVER, MSG_PRI_NORMAL))
			
			/* Suppression des taches Reception et Envoi */
			taskDelete(envoiId);
			taskDelete(receptionId);
			
			exit(0);
		}
	}
}
