/********************************************************************************
** Form generated from reading ui file 'fenconfig.ui'
**
** Created: Wed 16. Nov 10:44:07 2011
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FENCONFIG_H
#define UI_FENCONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenConfig
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *opCode;
    QLabel *label_2;
    QSpinBox *nbPPCarton;
    QLabel *label;
    QSpinBox *nbCPalette;
    QLabel *label_6;
    QSpinBox *nNbT1;
    QLabel *label_5;
    QSpinBox *nNbT2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *bOk;
    QPushButton *bCancel;

    void setupUi(QWidget *FenConfig)
    {
        if (FenConfig->objectName().isEmpty())
            FenConfig->setObjectName(QString::fromUtf8("FenConfig"));
        FenConfig->resize(285, 205);
        formLayoutWidget = new QWidget(FenConfig);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 241, 131));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        opCode = new QLineEdit(formLayoutWidget);
        opCode->setObjectName(QString::fromUtf8("opCode"));
        opCode->setMaxLength(5);
        opCode->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, opCode);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        nbPPCarton = new QSpinBox(formLayoutWidget);
        nbPPCarton->setObjectName(QString::fromUtf8("nbPPCarton"));
        nbPPCarton->setAlignment(Qt::AlignCenter);
        nbPPCarton->setValue(10);

        formLayout->setWidget(1, QFormLayout::FieldRole, nbPPCarton);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        nbCPalette = new QSpinBox(formLayoutWidget);
        nbCPalette->setObjectName(QString::fromUtf8("nbCPalette"));
        nbCPalette->setAlignment(Qt::AlignCenter);
        nbCPalette->setValue(10);

        formLayout->setWidget(2, QFormLayout::FieldRole, nbCPalette);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        nNbT1 = new QSpinBox(formLayoutWidget);
        nNbT1->setObjectName(QString::fromUtf8("nNbT1"));
        nNbT1->setAlignment(Qt::AlignCenter);
        nNbT1->setMaximum(9999);
        nNbT1->setValue(100);

        formLayout->setWidget(3, QFormLayout::FieldRole, nNbT1);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        nNbT2 = new QSpinBox(formLayoutWidget);
        nNbT2->setObjectName(QString::fromUtf8("nNbT2"));
        nNbT2->setAlignment(Qt::AlignCenter);
        nNbT2->setMaximum(9999);
        nNbT2->setValue(100);

        formLayout->setWidget(4, QFormLayout::FieldRole, nNbT2);

        horizontalLayoutWidget = new QWidget(FenConfig);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 170, 158, 25));
        buttonLayout = new QHBoxLayout(horizontalLayoutWidget);
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        bOk = new QPushButton(horizontalLayoutWidget);
        bOk->setObjectName(QString::fromUtf8("bOk"));

        buttonLayout->addWidget(bOk);

        bCancel = new QPushButton(horizontalLayoutWidget);
        bCancel->setObjectName(QString::fromUtf8("bCancel"));

        buttonLayout->addWidget(bCancel);

        formLayoutWidget->raise();
        horizontalLayoutWidget->raise();
        bOk->raise();

        retranslateUi(FenConfig);
        QObject::connect(bCancel, SIGNAL(clicked()), FenConfig, SLOT(close()));

        QMetaObject::connectSlotsByName(FenConfig);
    } // setupUi

    void retranslateUi(QWidget *FenConfig)
    {
        FenConfig->setWindowTitle(QApplication::translate("FenConfig", "Configuration", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FenConfig", "Code op\303\251rateur :", 0, QApplication::UnicodeUTF8));
        opCode->setText(QApplication::translate("FenConfig", "AB123", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenConfig", "Nb pi\303\250ces/carton :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenConfig", "Nb cartons/palette :", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FenConfig", "Nombre de palettes de T1 :", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FenConfig", "Nombre de palettes de T2 :", 0, QApplication::UnicodeUTF8));
        bOk->setText(QApplication::translate("FenConfig", "OK", 0, QApplication::UnicodeUTF8));
        bCancel->setText(QApplication::translate("FenConfig", "Annuler", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FenConfig);
    } // retranslateUi

};

namespace Ui {
    class FenConfig: public Ui_FenConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENCONFIG_H
