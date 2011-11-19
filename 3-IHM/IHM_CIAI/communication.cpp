#include "communication.h"
#include "ciaiProtocol.h"
#include <QTcpSocket>
#include <QHostAddress>

Communication::Communication(const QString & address, QObject * parent, quint16 port) :
QObject(parent),mSocket(new QTcpSocket(this))
{

    mSocket->connectToHost(QHostAddress(address),port);
    if (mSocket->waitForConnected(2000))
    {
         qDebug("IHM connectée au serveur.");
    }
    else
    {
        qDebug("Erreur lors de la connection au serveur (timeout).");
    }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(nouvellesDonnees()));
}
//----------------------------------------------------------Envoi
//Fonction générique d'envoi de donnée.
void Communication::envoyerMsg(msgTypes type, const QByteArray & data)
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

//--------------------------------------------------------Reception
void Communication::nouvellesDonnees()
{
    QDataStream in(mSocket);
    static quint8 MsgType = 254;
    static int MsgLength = 0;

    //On ne connait pas encore la taille du message
    //On en recupere le type pour cela
    if (MsgType == 254)
    {
        if (mSocket->bytesAvailable() < (int)sizeof(quint8))
             return;

        in >> MsgType;
        MsgLength = datagramSize((msgTypes)MsgType);
    }

    //Pas de contenu au message
    if(MsgLength==0)
    {
        traiterDatagram((msgTypes)MsgType,NULL);
    }
    else
    {
        //On attent que le contenu arrive
        if (mSocket->bytesAvailable() < MsgLength)
            return;

        // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
        QByteArray messageRecu;
        in >> messageRecu;

        // On traite le message
        traiterDatagram((msgTypes)MsgType,&messageRecu);
    }


    // On remet la taille et le type du message à 0 pour pouvoir recevoir de futurs messages
    MsgType = 254;
    MsgLength = 0;

}

//--------------------------------------------------------------Communs
int Communication::datagramSize(msgTypes type)
{
    switch(type)
    {
    case MSG_UNKNOWN :
        return -1;
        break;
    case MSG_PROD_CFG :
        return sizeof(MsgProdCfg);
        break;
    case MSG_PROD_ORD :
        return sizeof(MsgProdOrd);
        break;
    case MSG_EXP_ORD :
        return sizeof(MsgExpOrd);
        break;
    case MSG_ERR_SOLV :
        return sizeof(MsgErrSolv);
        break;
    case MSG_ERR_SIGN :
        return sizeof(MsgErrSign);
        break;
    case MSG_PAL_PLEINE :
        return 0;
        break;
    case MSG_EXP_RES :
        return sizeof(MsgExpRes);
        break;
    case MSG_END_OF_PROD :
        return 0;
        break;
    case MSG_CART_PLUS :/*Carton plein*/
        return 0;
        break;
    case MSG_CART_MOINS :/*Carton sur palette*/
        return 0;
        break;
    }
    return -1;
}

void Communication::traiterDatagram(msgTypes type, QByteArray * data)
{
    switch(type)
    {
    case MSG_UNKNOWN :
        qDebug("Message de type inconnu reçu");
        break;
    case MSG_PROD_CFG :
        emit ecrireLog(tr("<strong>Erreur :</strong> Message de configuration de la production reçu. O_o"));
        qDebug("Erreur : Msg Prog Cfg recu");
        break;
    case MSG_PROD_ORD :
        emit ecrireLog(tr("<strong>Erreur :</strong> Ordre de production reçu. O_o"));
        qDebug("Erreur : Ordre de production reçu.");
        break;
    case MSG_EXP_ORD :
        emit ecrireLog(tr("<strong>Erreur :</strong> Ordre d'expédition reçu. O_o"));
        qDebug("Erreur : Ordre d'expédition reçu.");
        break;
    case MSG_ERR_SOLV :
        emit ecrireLog(tr("<strong>Erreur :</strong> Message de résolution d'erreur reçu. O_o"));
        qDebug("Erreur : Message de resolution d'erreur reçu.");
        break;
    case MSG_ERR_SIGN :
        emit receptionErreur((errorsType)((MsgErrSign*)(data->constData()))->errNo);
        break;
    case MSG_PAL_PLEINE :
        //TODO : faire un traitement plus complet.
        emit ecrireLog(tr("Une palette est maintenant complette"));
        break;
    case MSG_EXP_RES :
    {
        const MsgExpRes * msg = ((const MsgExpRes*)(data->constData()));
        emit receptionEtatCommande(msg->numCom,(bool) msg->reussite);
    }
        break;
    case MSG_END_OF_PROD :
        //TODO : faire un traitement plus complet.
        emit ecrireLog(tr("Production terminée."));
        break;
    case MSG_CART_PLUS :/*Carton plein*/
        //TODO : faire un traitement plus complet.
        emit ecrireLog(tr("Un carton en plus"));
        break;
    case MSG_CART_MOINS :/*Carton sur palette*/
        //TODO : faire un traitement plus complet.
        emit ecrireLog(tr("Un carton en moins."));
        break;
    default :
        qDebug("Message de type invalide reçu.");
        emit ecrireLog(tr("<strong>Données reçus ne pouvant être traités : </strong>")+(int) type
                       +tr(" \n, contenu :\n")+(*data));
    }
}


Communication::~Communication()
{
    mSocket->close();
    qDebug("IHM déconnecté du serveur.");
    mSocket->deleteLater();
}
