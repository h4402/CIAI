#include "widgetcommande.h"
#include "ui_widgetcommande.h"
#include <cstring>

WidgetCommande::WidgetCommande(unsigned int numCom, unsigned int nNbT1,
                            unsigned int nNbT2, unsigned short noQuai,
                            const char dest[10], QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::WidgetCommande)
{
    m_ui->setupUi(this);
    m_ui->nNoComm->setText(QString::number(numCom));
    m_ui->nNbT1->setText(QString::number(nNbT1));
    m_ui->nNbT2->setText(QString::number(nNbT2));

    commande.numCom = numCom;
    commande.nbT1 = nNbT1;
    commande.nbT2 = nNbT2;
    commande.noQuai = noQuai;
    strcpy(commande.dest,dest);
}

WidgetCommande::~WidgetCommande()
{
    delete m_ui;
}

void WidgetCommande::changeEvent(QEvent *e)
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
