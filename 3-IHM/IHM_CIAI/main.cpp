#include <QtGui/QApplication>
#include "fenprincipale.h"
#include "fencommande.h"
#include "fenconfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenPrincipale wPrincipale;
    //FenConfig wConfig(&wPrincipale);
    wPrincipale.show();
    return app.exec();
}
