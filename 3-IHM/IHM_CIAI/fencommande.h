#ifndef FENCOMMANDE_H
#define FENCOMMANDE_H

#include <QtGui/QWidget>
#include "fenprincipale.h"

namespace Ui {
    class FenCommande;
}

class FenCommande : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(FenCommande)
public:
    explicit FenCommande(FenPrincipale *wPrincipale, QWidget *parent = 0);
    virtual ~FenCommande();

public slots:
    void validerCommande();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FenCommande *m_ui;
    FenPrincipale *wPrincipale;
};

#endif // FENCOMMANDE_H
