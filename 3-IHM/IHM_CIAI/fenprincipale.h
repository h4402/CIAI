#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtGui/QWidget>

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

private:
    Ui::FenPrincipale *ui;
    int nbT1;
    int nbT2;
};

#endif // FENPRINCIPALE_H
