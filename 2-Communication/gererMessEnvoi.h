#if ! defined ( MESSENV_H_ )
#define MESSENV_H_

#define BAL_MSG_TIMEOUT 5

#include "protocole.h"

int gererMessEnvoi(MSG_Q_ID balEnvoi, MSG_Q_ID balJournal, MSG_Q_ID balMessages);

#endif //MESSENV
