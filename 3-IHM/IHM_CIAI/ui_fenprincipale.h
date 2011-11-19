/********************************************************************************
** Form generated from reading ui file 'fenprincipale.ui'
**
** Created: Wed 16. Nov 11:18:33 2011
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FENPRINCIPALE_H
#define UI_FENPRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenPrincipale
{
public:
    QLabel *lBackImage;
    QLabel *lCaptDim;
    QLabel *lCaptPresC;
    QLabel *lCaptImpr;
    QLabel *lEtatFile;
    QLabel *lCaptPresP;
    QLCDNumber *lcdFile;
    QTextEdit *tLog;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *boutonLayout;
    QPushButton *bRunProd;
    QPushButton *bNewCom;
    QPushButton *bExpCom;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *tComm;

    void setupUi(QWidget *FenPrincipale)
    {
        if (FenPrincipale->objectName().isEmpty())
            FenPrincipale->setObjectName(QString::fromUtf8("FenPrincipale"));
        FenPrincipale->resize(910, 703);
        lBackImage = new QLabel(FenPrincipale);
        lBackImage->setObjectName(QString::fromUtf8("lBackImage"));
        lBackImage->setGeometry(QRect(30, 50, 721, 211));
        lBackImage->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ihm.png")));
        lBackImage->setScaledContents(true);
        lCaptDim = new QLabel(FenPrincipale);
        lCaptDim->setObjectName(QString::fromUtf8("lCaptDim"));
        lCaptDim->setGeometry(QRect(110, 70, 31, 31));
        lCaptDim->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ok.png")));
        lCaptPresC = new QLabel(FenPrincipale);
        lCaptPresC->setObjectName(QString::fromUtf8("lCaptPresC"));
        lCaptPresC->setGeometry(QRect(220, 70, 31, 31));
        lCaptPresC->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ok.png")));
        lCaptImpr = new QLabel(FenPrincipale);
        lCaptImpr->setObjectName(QString::fromUtf8("lCaptImpr"));
        lCaptImpr->setGeometry(QRect(330, 70, 31, 31));
        lCaptImpr->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ok.png")));
        lEtatFile = new QLabel(FenPrincipale);
        lEtatFile->setObjectName(QString::fromUtf8("lEtatFile"));
        lEtatFile->setGeometry(QRect(510, 70, 31, 31));
        lEtatFile->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ok.png")));
        lCaptPresP = new QLabel(FenPrincipale);
        lCaptPresP->setObjectName(QString::fromUtf8("lCaptPresP"));
        lCaptPresP->setGeometry(QRect(690, 10, 31, 31));
        lCaptPresP->setPixmap(QPixmap(QString::fromUtf8(":/images/ressources/ok.png")));
        lcdFile = new QLCDNumber(FenPrincipale);
        lcdFile->setObjectName(QString::fromUtf8("lcdFile"));
        lcdFile->setGeometry(QRect(500, 160, 41, 23));
        lcdFile->setNumDigits(2);
        tLog = new QTextEdit(FenPrincipale);
        tLog->setObjectName(QString::fromUtf8("tLog"));
        tLog->setGeometry(QRect(50, 290, 701, 121));
        tLog->setReadOnly(true);
        horizontalLayoutWidget = new QWidget(FenPrincipale);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(160, 640, 491, 41));
        boutonLayout = new QHBoxLayout(horizontalLayoutWidget);
        boutonLayout->setSpacing(6);
        boutonLayout->setMargin(11);
        boutonLayout->setObjectName(QString::fromUtf8("boutonLayout"));
        boutonLayout->setContentsMargins(0, 0, 0, 0);
        bRunProd = new QPushButton(horizontalLayoutWidget);
        bRunProd->setObjectName(QString::fromUtf8("bRunProd"));

        boutonLayout->addWidget(bRunProd);

        bNewCom = new QPushButton(horizontalLayoutWidget);
        bNewCom->setObjectName(QString::fromUtf8("bNewCom"));

        boutonLayout->addWidget(bNewCom);

        bExpCom = new QPushButton(horizontalLayoutWidget);
        bExpCom->setObjectName(QString::fromUtf8("bExpCom"));

        boutonLayout->addWidget(bExpCom);

        verticalLayoutWidget = new QWidget(FenPrincipale);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 420, 701, 211));
        tComm = new QVBoxLayout(verticalLayoutWidget);
        tComm->setSpacing(6);
        tComm->setMargin(11);
        tComm->setObjectName(QString::fromUtf8("tComm"));
        tComm->setContentsMargins(0, 0, 0, 0);

        retranslateUi(FenPrincipale);

        QMetaObject::connectSlotsByName(FenPrincipale);
    } // setupUi

    void retranslateUi(QWidget *FenPrincipale)
    {
        FenPrincipale->setWindowTitle(QApplication::translate("FenPrincipale", "Gestion de production - Edition Pro 2011", 0, QApplication::UnicodeUTF8));
        lBackImage->setText(QString());
        lCaptDim->setText(QString());
        lCaptPresC->setText(QString());
        lCaptImpr->setText(QString());
        lEtatFile->setText(QString());
        lCaptPresP->setText(QString());
        bRunProd->setText(QApplication::translate("FenPrincipale", "Lancer production", 0, QApplication::UnicodeUTF8));
        bNewCom->setText(QApplication::translate("FenPrincipale", "Nouvelle commande", 0, QApplication::UnicodeUTF8));
        bExpCom->setText(QApplication::translate("FenPrincipale", "Exp\303\251dier commande", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FenPrincipale);
    } // retranslateUi

};

namespace Ui {
    class FenPrincipale: public Ui_FenPrincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
