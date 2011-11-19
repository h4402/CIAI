#ifndef WIDGETCOMM_H
#define WIDGETCOMM_H

#include <QtGui/QWidget>
#include "ciaiProtocol.h"

namespace Ui {
    class WidgetComm;
}

class WidgetComm : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(widgetComm)
public:
    explicit WidgetComm(unsigned int numCom, unsigned int nbT1,
                            unsigned int nbT2, unsigned short noQuai,
                            char dest[10], QWidget *parent = 0);
    virtual ~WidgetComm();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::WidgetComm *m_ui;
    MsgExpOrd commande;
};

#endif // WIDGETCOMM_H
