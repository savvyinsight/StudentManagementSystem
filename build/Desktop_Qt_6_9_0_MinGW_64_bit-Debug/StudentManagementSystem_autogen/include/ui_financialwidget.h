/********************************************************************************
** Form generated from reading UI file 'financialwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINANCIALWIDGET_H
#define UI_FINANCIALWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FinancialWidget
{
public:

    void setupUi(QWidget *FinancialWidget)
    {
        if (FinancialWidget->objectName().isEmpty())
            FinancialWidget->setObjectName("FinancialWidget");
        FinancialWidget->resize(400, 300);

        retranslateUi(FinancialWidget);

        QMetaObject::connectSlotsByName(FinancialWidget);
    } // setupUi

    void retranslateUi(QWidget *FinancialWidget)
    {
        FinancialWidget->setWindowTitle(QCoreApplication::translate("FinancialWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FinancialWidget: public Ui_FinancialWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINANCIALWIDGET_H
