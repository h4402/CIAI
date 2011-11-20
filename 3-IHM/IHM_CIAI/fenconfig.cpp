#include "fenconfig.h"
#include "ui_fenconfig.h"

FenConfig::FenConfig(int nbT1, int nbT2, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::FenConfig),
    wPrincipale(principale)
{
    m_ui->setupUi(this);
    m_ui->nNbT1->setValue(nbT1);
    m_ui->nNbT2->setValue(nbT2);
    connect(m_ui->bOk,SIGNAL(clicked()),this,SLOT(validerConfig()));
    connect(m_ui->bCancel,SIGNAL(clicked()),this,SLOT(deleteLater()));
}

void FenConfig::validerConfig()
{
    //TODO : mettre à jour.
    emit envoyerConfig(m_ui->nbPPCarton->value(),m_ui->nbCPalette->value(),5);
    this->close();
}

FenConfig::~FenConfig()
{
    delete m_ui;
}

void FenConfig::changeEvent(QEvent *e)
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
