#ifndef WIDGETCOMMANDE_H
#define WIDGETCOMMANDE_H

#include <QtGui/QWidget>
#include "ciaiProtocol.h"

namespace Ui {
    class WidgetCommande;
}

class WidgetCommande : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(WidgetCommande)
public:
    explicit WidgetCommande(unsigned int numCom, unsigned int nNbT1,
                            unsigned int nNbT2, unsigned short noQuai,
                            const char dest[10], QWidget *parent = 0);
    virtual ~WidgetCommande();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::WidgetCommande *m_ui;
    MsgExpOrd commande;
};

#endif // WIDGETCOMMANDE_H
