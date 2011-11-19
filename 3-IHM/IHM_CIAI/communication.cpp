#include "communication.h"
#include "ciaiProtocol.h"
#include <QTcpSocket>

Communication::Communication(const QHostAddress & address, quint16 port, QObject * parent)
{

}

void Communication::envoyerMsg(quint8 type, const char * data)
{

}

void Communication::envoyerConfig(quint16 pieceParCarton,
                   quint16 cartonParPalette,
                   quint16 maxMauvais)
{

}

void Communication::envoyerProduction(quint16 numLot1,
                       quint16 nbPaletteT1,
                       quint16 numLot2,
                       quint16 nbPaletteT2,
                       const char * opCode)
{

}

void Communication::envoyerExpedition(quint16 numCommande,
                       quint16 nbT1,
                       quint16 nbT2,
                       quint8 quai,
                       const char * destinataire)
{

}

void Communication::traiterErreur(errorsType numErr,
                   bool reprise)
{

}

void receptionErreur(errorsType numErr)
{
    //afficher une boîte de dialogue
}

void receptionEtatCommande(quint16 numCommande,
                           bool expediee)
{

}

void ecrireLog(QString message)
{

}

void nouvellesDonnees()
{

}
