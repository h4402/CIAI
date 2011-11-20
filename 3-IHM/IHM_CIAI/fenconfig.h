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
    explicit FenConfig(int nbT1toBuild, int nbT2toBuild, QWidget *parent = 0);
    virtual ~FenConfig();

public slots:
    void validerConfig();

signals:
    void envoyerConfig(quint16 pieceParCarton,
                       quint16 cartonParPalette,
                       quint16 maxMauvais);
    void envoyerProduction(quint16 numLot1,
                           quint16 nbPaletteT1,
                           quint16 numLot2,
                           quint16 nbPaletteT2,
                           const char * opCode);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FenConfig *m_ui;
};

#endif // FENCONFIG_H
