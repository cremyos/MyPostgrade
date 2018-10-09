/********************************************************************************
** Form generated from reading UI file 'cshowdata.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSHOWDATA_H
#define UI_CSHOWDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_CShowData
{
public:
    QLabel *label_class;
    QLCDNumber *lcdNumber;
    QTextBrowser *textBrowser;
    QLabel *label_Enable;
    QLabel *label_Disable;
    QCustomPlot *widget;
    QLabel *label;

    void setupUi(QWidget *CShowData)
    {
        if (CShowData->objectName().isEmpty())
            CShowData->setObjectName(QStringLiteral("CShowData"));
        CShowData->resize(834, 563);
        label_class = new QLabel(CShowData);
        label_class->setObjectName(QStringLiteral("label_class"));
        label_class->setGeometry(QRect(60, 60, 111, 51));
        lcdNumber = new QLCDNumber(CShowData);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(60, 150, 211, 51));
        textBrowser = new QTextBrowser(CShowData);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(40, 270, 261, 191));
        label_Enable = new QLabel(CShowData);
        label_Enable->setObjectName(QStringLiteral("label_Enable"));
        label_Enable->setGeometry(QRect(400, 100, 91, 81));
        label_Disable = new QLabel(CShowData);
        label_Disable->setObjectName(QStringLiteral("label_Disable"));
        label_Disable->setGeometry(QRect(570, 100, 121, 81));
        widget = new QCustomPlot(CShowData);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(319, 39, 241, 131));
        label = new QLabel(CShowData);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(420, 240, 71, 31));

        retranslateUi(CShowData);

        QMetaObject::connectSlotsByName(CShowData);
    } // setupUi

    void retranslateUi(QWidget *CShowData)
    {
        CShowData->setWindowTitle(QApplication::translate("CShowData", "CShowData", Q_NULLPTR));
        label_class->setText(QString());
        label_Enable->setText(QString());
        label_Disable->setText(QString());
        label->setText(QApplication::translate("CShowData", "\347\212\266\346\200\201\351\207\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CShowData: public Ui_CShowData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSHOWDATA_H
