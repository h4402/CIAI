#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtGui/QWidget>
#include "communication.h"

namespace Ui
{
    class FenPrincipale;
}

class FenPrincipale : public QWidget
{
    Q_OBJECT

public:
    FenPrincipale(QWidget *parent = 0);
    void lancerProduction(int codeOp, int nbPieceParCarton, int nbCartonParPalette);
    void ajouterCommande(int nbT1, int nbT2, int nbQuai, QString destinataire);
    ~FenPrincipale();

protected slots:
    void nouvelleCommande();
    void configurerProduction();
    void ecrireLog(QString toLog);

private:
    Ui::FenPrincipale *ui;
    int nbT1;
    int nbT2;
    Communication * cannal;
};

#endif // FENPRINCIPALE_H
