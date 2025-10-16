/********************************************************************************
** Form generated from reading UI file 'honorwallwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HONORWALLWIDGET_H
#define UI_HONORWALLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HonorWallWidget
{
public:

    void setupUi(QWidget *HonorWallWidget)
    {
        if (HonorWallWidget->objectName().isEmpty())
            HonorWallWidget->setObjectName("HonorWallWidget");
        HonorWallWidget->resize(400, 300);

        retranslateUi(HonorWallWidget);

        QMetaObject::connectSlotsByName(HonorWallWidget);
    } // setupUi

    void retranslateUi(QWidget *HonorWallWidget)
    {
        HonorWallWidget->setWindowTitle(QCoreApplication::translate("HonorWallWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HonorWallWidget: public Ui_HonorWallWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HONORWALLWIDGET_H
