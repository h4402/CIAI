/********************************************************************************
** Form generated from reading UI file 'widgetcommande.ui'
**
** Created: Sat Nov 19 17:39:23 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCOMMANDE_H
#define UI_WIDGETCOMMANDE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetCommande
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *nNoComm;
    QLabel *nNbT1;
    QLabel *nNbT2;
    QPushButton *bSend;

    void setupUi(QWidget *WidgetCommande)
    {
        if (WidgetCommande->objectName().isEmpty())
            WidgetCommande->setObjectName(QString::fromUtf8("WidgetCommande"));
        WidgetCommande->resize(717, 55);
        horizontalLayoutWidget = new QWidget(WidgetCommande);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 691, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nNoComm = new QLabel(horizontalLayoutWidget);
        nNoComm->setObjectName(QString::fromUtf8("nNoComm"));

        horizontalLayout->addWidget(nNoComm);

        nNbT1 = new QLabel(horizontalLayoutWidget);
        nNbT1->setObjectName(QString::fromUtf8("nNbT1"));

        horizontalLayout->addWidget(nNbT1);

        nNbT2 = new QLabel(horizontalLayoutWidget);
        nNbT2->setObjectName(QString::fromUtf8("nNbT2"));

        horizontalLayout->addWidget(nNbT2);

        bSend = new QPushButton(horizontalLayoutWidget);
        bSend->setObjectName(QString::fromUtf8("bSend"));

        horizontalLayout->addWidget(bSend);


        retranslateUi(WidgetCommande);

        QMetaObject::connectSlotsByName(WidgetCommande);
    } // setupUi

    void retranslateUi(QWidget *WidgetCommande)
    {
        WidgetCommande->setWindowTitle(QApplication::translate("WidgetCommande", "Form", 0, QApplication::UnicodeUTF8));
        nNoComm->setText(QApplication::translate("WidgetCommande", "no Comm", 0, QApplication::UnicodeUTF8));
        nNbT1->setText(QApplication::translate("WidgetCommande", "nbT1", 0, QApplication::UnicodeUTF8));
        nNbT2->setText(QApplication::translate("WidgetCommande", "nbT2", 0, QApplication::UnicodeUTF8));
        bSend->setText(QApplication::translate("WidgetCommande", "Exp\303\251dier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetCommande: public Ui_WidgetCommande {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCOMMANDE_H
