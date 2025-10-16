/********************************************************************************
** Form generated from reading UI file 'systemsetting.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETTING_H
#define UI_SYSTEMSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemSetting
{
public:

    void setupUi(QWidget *SystemSetting)
    {
        if (SystemSetting->objectName().isEmpty())
            SystemSetting->setObjectName("SystemSetting");
        SystemSetting->resize(400, 300);

        retranslateUi(SystemSetting);

        QMetaObject::connectSlotsByName(SystemSetting);
    } // setupUi

    void retranslateUi(QWidget *SystemSetting)
    {
        SystemSetting->setWindowTitle(QCoreApplication::translate("SystemSetting", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemSetting: public Ui_SystemSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETTING_H
