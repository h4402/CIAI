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
        emit ecrireLog(tr("L'application n'a pas pu se connecter au serveur."));
        qDebug("Erreur lors de la connection au serveur (timeout).");
    }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(nouvellesDonnees()));
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(deconnexion()));
}



Communication::~Communication()
{
    mSocket->close();
    qDebug("IHM déconnecté du serveur.");
    mSocket->deleteLater();
}

//----------------------------------------------------------Envoi
//Fonction générique d'envoi de donnée.
void Communication::envoyerMsg(msgTypes type, const QByteArray & data)
{
    quint8 typeToSend(type);
    mSocket->write((const char *)&typeToSend,sizeof(quint8));
    mSocket->write(data);
}

void Communication::envoyerConfig(quint16 pieceParCarton,
                   quint16 cartonParPalette,
                   quint16 maxMauvais)
{
    MsgProdCfg msg;
    msg.pieceParCarton=pieceParCarton;
    msg.cartonParPalette=cartonParPalette;
    msg.maxMauvais=maxMauvais;
    QByteArray data((const char *)&msg,sizeof(MsgProdCfg));
    envoyerMsg(MSG_PROD_CFG,data);
}

void Communication::envoyerProduction(quint16 numLot1,
                       quint16 nbPaletteT1,
                       quint16 numLot2,
                       quint16 nbPaletteT2,
                       const char * opCode)
{
    MsgProdOrd msg;
    msg.numLot1=numLot1;
    msg.nbLot1=nbPaletteT1;
    msg.numLot2=numLot2;
    msg.nbLot2=nbPaletteT2;
    strcpy(msg.opCode,opCode);
    QByteArray data((const char *)&msg,sizeof(MsgProdOrd));
    envoyerMsg(MSG_PROD_ORD,data);
}

void Communication::envoyerExpedition(quint16 numCommande,
                       quint16 nbT1,
                       quint16 nbT2,
                       quint8 quai,
                       const char * destinataire)
{
    MsgExpOrd msg;
    msg.numCom=numCommande;
    msg.nbT1toBuild=nbT1;
    msg.nbT2toBuild=nbT2;
    msg.noQuai=quai;
    strcpy(msg.dest,destinataire);
    QByteArray data( (const char *)&msg,sizeof(MsgExpOrd));
    envoyerMsg(MSG_EXP_ORD,data);
}

void Communication::traiterErreur(errorsType numErr,
                   bool reprise)
{
    MsgErrSolv msg;
    msg.errNo=(UINT8)numErr;
    msg.reprise=(UINT8)reprise;
    QByteArray data( (const char *)&msg,sizeof(MsgErrSolv));
    envoyerMsg(MSG_ERR_SOLV,data);
}

//--------------------------------------------------------Reception
void Communication::nouvellesDonnees()
{
    static quint8 MsgType = 254;
    static int MsgLength = 0;

    do
    {

        //On ne connait pas encore la taille du message
        //On en recupere le type pour cela
        if (MsgType == 254)
        {
            if (mSocket->bytesAvailable() < (int)sizeof(quint8))
                 return;
            mSocket->read((char *) &MsgType,(int)sizeof(quint8));
            MsgLength = datagramSize((msgTypes)MsgType);
        }

        //Pas de contenu au message
        if(MsgLength==0)
        {
            traiterDatagram((msgTypes)MsgType,NULL);
        }
        else
        {
            //On attend que le contenu arrive
            if (mSocket->bytesAvailable() < MsgLength)
                return;

            // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
            QByteArray messageRecu;
            if(MsgLength==-1)
            {
                messageRecu = mSocket->readLine();
            }
            else
            {
                messageRecu = mSocket->read(MsgLength);
            }

            // On traite le message
            traiterDatagram((msgTypes)MsgType,&messageRecu);
        }


        // On remet la taille et le type du message à 0 pour pouvoir recevoir de futurs messages
        MsgType = 254;
        MsgLength = 0;
    } while(mSocket->bytesAvailable()>0);//S'il reste des données à lire, on recommence.

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
        return sizeof(MsgPalPleine);
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
    //__________________________Messages NE pouvant PAS êtres reçus___________________________

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
    //____________________________Messages POUVANT êtres reçus________________________________

    case MSG_ERR_SIGN :
        emit receptionErreur((errorsType)((MsgErrSign*)(data->constData()))->errNo);
        break;
    case MSG_PAL_PLEINE :
        emit paletteComplete((quint16)((MsgPalPleine*)(data->constData()))->numLot);
        break;
    case MSG_EXP_RES :
    {
        //nouveau contexte a cause de la création d'une variable dans le switch
        //(problème de portée)
        const MsgExpRes * msg = ((const MsgExpRes*)(data->constData()));
        emit receptionEtatCommande(msg->numCom,(bool) msg->reussite);
    }
        break;
    case MSG_END_OF_PROD :
        //TODO : faire un traitement plus complet.
        emit ecrireLog(tr("Production terminée."));
        break;
    case MSG_CART_PLUS :/*Carton plein*/
        emit updateFileAttenteCartons(1);
        break;
    case MSG_CART_MOINS :/*Carton sur palette*/
        emit updateFileAttenteCartons(-1);
        break;
    default :
        qDebug("Message de type invalide reçu.");
        emit ecrireLog(tr("<strong>Données reçus ne pouvant être traités : </strong>")
                       +(int) type
                       +tr(" <br /> contenu : <br />")+(*data));
    }
}

void Communication::deconnexion()
{
    qDebug("Le serveur s'est déconnecté.");
    emit ecrireLog(tr("<strong> Erreur : </strong> l'application n'est plus connecté."));
}
