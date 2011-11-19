#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QTcpSocket>
#include "ciaiProtocol.h"

class Communication : public QObject
{
Q_OBJECT
public:
    Communication(const QHostAddress & address, quint16 port=9002,QObject * parent = 0);

public slots :
    void envoyerMsg(quint8 type, const char * data);
    void envoyerConfig(quint16 pieceParCarton,
                       quint16 cartonParPalette,
                       quint16 maxMauvais);
    void envoyerProduction(quint16 numLot1,
                           quint16 nbPaletteT1,
                           quint16 numLot2,
                           quint16 nbPaletteT2,
                           const char * opCode);
    void envoyerExpedition(quint16 numCommande,
                           quint16 nbT1,
                           quint16 nbT2,
                           quint8 quai,
                           const char * destinataire);
    void traiterErreur(errorsType numErr,
                       bool reprise);
signals:
    void receptionErreur(errorsType numErr);
    void receptionEtatCommande(quint16 numCommande,
                               bool expediee);
    void ecrireLog(QString message);

protected slots:
    void nouvellesDonnees();

protected :
    QTcpSocket socket;
};

#endif // COMMUNICATION_H
