#include "widgetcomm.h"
#include "ui_widgetcomm.h"

WidgetComm::WidgetComm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::WidgetComm)
{
    m_ui->setupUi(this);
}

WidgetComm::~WidgetComm()
{
    delete m_ui;
}

void WidgetComm::changeEvent(QEvent *e)
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
