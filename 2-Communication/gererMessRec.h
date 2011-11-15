#if ! defined ( MESSREC_H_ )
#define MESSREC_H_

#define FAIL(x) if(x == -1) {\
perror(#x);}

int gererMessRec(MSG_Q_ID balReception, MSG_Q_ID balCommande, MSG_Q_ID balResErreur);

#endif //MESSREC
