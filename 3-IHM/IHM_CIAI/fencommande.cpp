#include "fencommande.h"
#include "fenprincipale.h"
#include "ui_fencommande.h"

FenCommande::FenCommande(FenPrincipale *principale, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::FenCommande),
    wPrincipale(principale)
{
    m_ui->setupUi(this);
    connect(m_ui->bCancel,SIGNAL(clicked()),this,
                                    SLOT(deleteLater()));
    connect(m_ui->bOk,SIGNAL(clicked()),this,
                                    SLOT(validerCommande()));
}

FenCommande::~FenCommande()
{
    delete m_ui;
}

void FenCommande::validerCommande()
{
    int nbT1 = m_ui->nNbT1->value();
    int nbT2 = m_ui->nNbT2->value();

    bool goodContent = false;
    int nbQuai = m_ui->cNumQuai->currentText().toInt(&goodContent,10);

    QString destinataire(m_ui->tCodeClient->text());

    if(goodContent)
    {
        wPrincipale->ajouterCommande(nbT1, nbT2, nbQuai,
                                                    destinataire);
        this->deleteLater();
    }
    else
    {
        //TODO: Signaler l'erreur
    }
}

void FenCommande::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
