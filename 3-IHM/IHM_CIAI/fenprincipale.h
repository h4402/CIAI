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
    void ajouterCommande(int nbT1toBuild, int nbT2toBuild, int nbQuai, QString destinataire);
    ~FenPrincipale();

protected slots:
    void nouvelleCommande();
    void configurerProduction();
    void ecrireLog(QString toLog);

    void gererErreur(errorsType numErr);
    void updateEtatCommande(quint16 numCommande, bool expediee);
    void updateFileAttenteCartons(int nb);
    void paletteComplete(int numLot);

signals:
    void envoyerConfig(quint16 pieceParCarton,
                       quint16 cartonParPalette,
                       quint16 maxMauvais);
    void envoyerProduction(quint16 numLot1,
                           quint16 nbPaletteT1,
                           quint16 numLot2,
                           quint16 nbPaletteT2,
                           const char * opCode);
    void envoyerExpedition(quint16 numCommande,
                           quint16 nbT1toBuild,
                           quint16 nbT2toBuild,
                           quint8 quai,
                           const char * destinataire);
    void traiterErreur(errorsType numErr,
                       bool reprise);

private:
    Ui::FenPrincipale *ui;

    int numLot1;
    int nbT1toBuild;
    int nbT1Built;
    int numLot2;
    int nbT2toBuild;
    int nbT2Built;

    int longFileCartons;
    Communication * cannal;
};

#endif // FENPRINCIPALE_H
