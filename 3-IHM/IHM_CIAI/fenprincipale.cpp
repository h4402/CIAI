#include "fenprincipale.h"
#include "fencommande.h"
#include "fenconfig.h"
#include "widgetcommande.h"
#include "ui_fenprincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent)
    : QWidget(parent), ui(new Ui::FenPrincipale)
{
    ui->setupUi(this);
    this->nbT1 = 0;
    this->nbT2 = 0;
    connect(ui->bNewCom,SIGNAL(clicked()),this,SLOT(nouvelleCommande()));
    connect(ui->bRunProd,SIGNAL(clicked()),this,SLOT(configurerProduction()));
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
    nbT1 += nNbT1;
    nbT2 += nNbT2;
    destinataire.truncate(10);
    WidgetCommande *newCommande = new WidgetCommande(lastComm,
                                     nNbT1, nNbT2, nbQuai,
                                     destinataire.toAscii().constData(),
                                     this);
    ui->tComm->addWidget(newCommande);
}

void FenPrincipale::configurerProduction()
{
    FenConfig *wConfig = new FenConfig(this, this->nbT1, this->nbT2);
    wConfig->show();
}

void FenPrincipale::lancerProduction(int codeOp, int nbPieceParCarton, int nbCartonParPalette)
{
    this->ui->bNewCom->hide();
    this->ui->bRunProd->hide();
    this->ui->bExpCom->hide();
    // + partie communication avec l'application
}


FenPrincipale::~FenPrincipale()
{
    delete ui;
}

