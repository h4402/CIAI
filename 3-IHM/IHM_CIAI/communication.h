#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QTcpSocket>
#include "ciaiProtocol.h"

class Communication : public QObject
{
Q_OBJECT
public:
    Communication(const QString & address=PROTO_ADDR,QObject * parent = 0, quint16 port=PROTO_PORT);
    ~Communication();

public slots :
    void envoyerMsg(msgTypes type, const QByteArray & data);
    void envoyerConfig(quint16 pieceParCarton,
                       quint16 cartonParPalette,
                       quint16 maxMauvais);
    void envoyerProduction(quint16 numLot1,
                           quint16 nbPaletteT1,
                           quint16 numLot2,
                           quint16 nbPaletteT2,
                           const char * opCode);
    void envoyerExpedition(quint16 numCommande,
                           quint16 nbT1toBuild,
                           quint16 nbT2toBuild,
                           quint8 quai,
                           const char * destinataire);
    void traiterErreur(errorsType numErr,
                       bool reprise);
signals:
    void receptionErreur(errorsType numErr);
    void receptionEtatCommande(quint16 numCommande,
                               bool expediee);
    void updateFileAttenteCartons(int nb);
    void paletteComplete(int nLot);
    void ecrireLog(QString message);

protected slots:
    void nouvellesDonnees();
    void deconnexion();

protected :
    //methodes
    int datagramSize(msgTypes type);
    void traiterDatagram(msgTypes type, QByteArray * data);

    //attributs
    QTcpSocket * mSocket;
};

#endif // COMMUNICATION_H
