#ifndef FENCONFIG_H
#define FENCONFIG_H

#include <QtGui/QWidget>
#include "fenprincipale.h"

namespace Ui {
    class FenConfig;
}

class FenConfig : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(FenConfig)
public:
    explicit FenConfig(FenPrincipale *principale, int nbT1, int nbT2, QWidget *parent = 0);
    virtual ~FenConfig();

public slots:
    void validerConfig();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FenConfig *m_ui;
    FenPrincipale *wPrincipale;
};

#endif // FENCONFIG_H
