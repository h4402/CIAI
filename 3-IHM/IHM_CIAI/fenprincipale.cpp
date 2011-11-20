#include "fenprincipale.h"
#include "fencommande.h"
#include "fenconfig.h"
#include "widgetcommande.h"
#include "ui_fenprincipale.h"
#include "communication.h"

FenPrincipale::FenPrincipale(QWidget *parent)
    : QWidget(parent), ui(new Ui::FenPrincipale),nbT1toBuild(0),nbT2toBuild(0),cannal(new Communication(PROTO_ADDR,this,PROTO_PORT))
{
    ui->setupUi(this);
    connect(ui->bNewCom,SIGNAL(clicked()),this,SLOT(nouvelleCommande()));
    connect(ui->bRunProd,SIGNAL(clicked()),this,SLOT(configurerProduction()));

    //Reception
    connect(cannal,SIGNAL(ecrireLog(QString)),this,SLOT(ecrireLog(QString)));
    connect(cannal,SIGNAL(paletteComplete(int)),this,SLOT(paletteComplete(int)));
    connect(cannal,SIGNAL(updateFileAttenteCartons(int)),this,
            SLOT(updateFileAttenteCartons(int)));
    connect(cannal,SIGNAL(receptionEtatCommande(quint16,bool)),this,
            SLOT(updateEtatCommande(quint16,bool)));
    connect(cannal,SIGNAL(receptionErreur(errorsType)),this,
            SLOT(gererErreur(errorsType)));

    //Emission
    connect(this,SIGNAL(envoyerConfig(quint16,quint16,quint16)),cannal,
            SLOT(envoyerConfig(quint16,quint16,quint16)));
    connect(this,SIGNAL(envoyerProduction(quint16,quint16,quint16,quint16,const char*)),
            cannal,SLOT(envoyerProduction(quint16,quint16,quint16,quint16,const char*)));
    connect(this,SIGNAL(envoyerExpedition(quint16,quint16,quint16,quint8,const char*)),
            cannal,SLOT(envoyerExpedition(quint16,quint16,quint16,quint8,const char*)));
    connect(this,SIGNAL(traiterErreur(errorsType,bool)),cannal,
            SLOT(traiterErreur(errorsType,bool)));
}

FenPrincipale::~FenPrincipale()
{
    cannal->deleteLater();
    delete ui;
}

void FenPrincipale::nouvelleCommande()
{
    FenCommande *wCommande = new FenCommande(this);
    wCommande->show();
}

void FenPrincipale::ajouterCommande(int nNbT1, int nNbT2, int nbQuai, QString destinataire)
{
    static int lastComm = 0;
    lastComm++;
    nbT1toBuild += nNbT1;
    nbT2toBuild += nNbT2;
    destinataire.truncate(10);
    WidgetCommande *newCommande = new WidgetCommande(lastComm,
                                     nNbT1, nNbT2, nbQuai,
                                     destinataire.toAscii().constData(),
                                     this);
    ui->tComm->addWidget(newCommande);
}

void FenPrincipale::configurerProduction()
{
    FenConfig *wConfig = new FenConfig(this, this->nbT1toBuild, this->nbT2toBuild);
    wConfig->show();
}

void FenPrincipale::lancerProduction(int codeOp, int nbPieceParCarton, int nbCartonParPalette)
{
    this->ui->bNewCom->hide();
    this->ui->bRunProd->hide();
    this->ui->bExpCom->hide();
    // + partie communication avec l'application
}

void FenPrincipale::ecrireLog(QString toLog)
{
    ui->tLog->insertHtml(toLog+"<br />");
}


void FenPrincipale::gererErreur(errorsType numErr)
{

}

void FenPrincipale::updateEtatCommande(quint16 numCommande, bool expediee)
{

}

void FenPrincipale::updateFileAttenteCartons(int nb)
{

}

void FenPrincipale::paletteComplete(int numLot)
{

}

