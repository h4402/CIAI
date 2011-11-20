#ifndef CIAIPROTOCOL_H
#define CIAIPROTOCOL_H


#ifdef __cplusplus
#include <stdint.h>
#define UINT8 uint8_t
#define UINT16 uint16_t
#else
#include <sys/types.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
ERR_UNKNOWN,
ERR_ABS_CARTON,
ERR_PIECES_RATE,
ERR_PRINTER,
ERR_ABS_PALETTE,
ERR_FILE_CARTONS,
ERR_AU,
ERR_NOT_ENOUGHT,
ERR_PLASTIQ
}errorsType;/* Sera caste en UINT8 */

typedef enum {
MSG_UNKNOWN,
MSG_PROD_CFG,
MSG_PROD_ORD,
MSG_EXP_ORD,
MSG_ERR_SOLV,
MSG_ERR_SIGN,
MSG_PAL_PLEINE,
MSG_EXP_RES,
MSG_END_OF_PROD,/* Pas de datagramme associee */
MSG_CART_PLUS, /*Carton plein*/
MSG_CART_MOINS /*Carton sur palette*/
}msgTypes;/* Sera caste en UINT8 */

typedef struct
{
   UINT16 pieceParCarton;
   UINT16 cartonParPalette;
   UINT16 maxMauvais;
} MsgProdCfg;

typedef struct
{
       UINT16 numLot1;
       UINT16 nbLot1;
       UINT16 numLot2;
       UINT16 nbLot2;
       char opCode[5];
} MsgProdOrd;

typedef struct
{
   UINT16 numCom;
   UINT16 nbT1;
   UINT16 nbT2;
   UINT8 noQuai;
   char dest[10];
} MsgExpOrd;

typedef struct
{
   UINT8 errNo;
   UINT8 reprise;
} MsgErrSolv;

typedef struct
{
   UINT8 errNo;
} MsgErrSign;


typedef struct
{
   UINT8 numCom;
   UINT8 reussite;
} MsgExpRes;

typedef struct
{
   UINT8 numLot;
} MsgPalPleine;

#define FAIL(x) if(x == -1) {\
perror(#x);}

#define PROTO_PORT 9002
#define PROTO_ADDR "127.0.0.1"

#ifdef __cplusplus
}
#endif

#endif /* CIAIPROTOCOL_H */
 
