/********************************************************************************
** Form generated from reading UI file 'fencommande.ui'
**
** Created: Sat Nov 19 17:39:23 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENCOMMANDE_H
#define UI_FENCOMMANDE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenCommande
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *nNbT1;
    QLabel *label_2;
    QSpinBox *nNbT2;
    QLabel *label_3;
    QComboBox *cNumQuai;
    QLabel *label_4;
    QLineEdit *tCodeClient;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *bOk;
    QPushButton *bCancel;

    void setupUi(QWidget *FenCommande)
    {
        if (FenCommande->objectName().isEmpty())
            FenCommande->setObjectName(QString::fromUtf8("FenCommande"));
        FenCommande->setWindowModality(Qt::ApplicationModal);
        FenCommande->resize(247, 191);
        formLayoutWidget = new QWidget(FenCommande);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 208, 111));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nNbT1 = new QSpinBox(formLayoutWidget);
        nNbT1->setObjectName(QString::fromUtf8("nNbT1"));
        nNbT1->setAlignment(Qt::AlignCenter);
        nNbT1->setValue(0);

        formLayout->setWidget(0, QFormLayout::FieldRole, nNbT1);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        nNbT2 = new QSpinBox(formLayoutWidget);
        nNbT2->setObjectName(QString::fromUtf8("nNbT2"));
        nNbT2->setAlignment(Qt::AlignCenter);
        nNbT2->setValue(0);

        formLayout->setWidget(1, QFormLayout::FieldRole, nNbT2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cNumQuai = new QComboBox(formLayoutWidget);
        cNumQuai->setObjectName(QString::fromUtf8("cNumQuai"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cNumQuai);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        tCodeClient = new QLineEdit(formLayoutWidget);
        tCodeClient->setObjectName(QString::fromUtf8("tCodeClient"));
        tCodeClient->setMaxLength(9);
        tCodeClient->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(3, QFormLayout::FieldRole, tCodeClient);

        horizontalLayoutWidget = new QWidget(FenCommande);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 140, 158, 31));
        buttonLayout = new QHBoxLayout(horizontalLayoutWidget);
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        bOk = new QPushButton(horizontalLayoutWidget);
        bOk->setObjectName(QString::fromUtf8("bOk"));

        buttonLayout->addWidget(bOk);

        bCancel = new QPushButton(horizontalLayoutWidget);
        bCancel->setObjectName(QString::fromUtf8("bCancel"));

        buttonLayout->addWidget(bCancel);


        retranslateUi(FenCommande);
        QObject::connect(bCancel, SIGNAL(clicked()), FenCommande, SLOT(close()));

        QMetaObject::connectSlotsByName(FenCommande);
    } // setupUi

    void retranslateUi(QWidget *FenCommande)
    {
        FenCommande->setWindowTitle(QApplication::translate("FenCommande", "Nouvelle commande", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenCommande", "Nombre de palettes de T1 :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenCommande", "Nombre de palettes de T2 :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FenCommande", "Num\303\251ro de quai :", 0, QApplication::UnicodeUTF8));
        cNumQuai->clear();
        cNumQuai->insertItems(0, QStringList()
         << QApplication::translate("FenCommande", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenCommande", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenCommande", "3", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("FenCommande", "Code client :", 0, QApplication::UnicodeUTF8));
        bOk->setText(QApplication::translate("FenCommande", "OK", 0, QApplication::UnicodeUTF8));
        bCancel->setText(QApplication::translate("FenCommande", "Annuler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenCommande: public Ui_FenCommande {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENCOMMANDE_H
