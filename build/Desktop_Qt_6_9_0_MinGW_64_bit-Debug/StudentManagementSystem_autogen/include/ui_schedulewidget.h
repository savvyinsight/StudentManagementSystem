/********************************************************************************
** Form generated from reading UI file 'schedulewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEWIDGET_H
#define UI_SCHEDULEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleWidget
{
public:

    void setupUi(QWidget *ScheduleWidget)
    {
        if (ScheduleWidget->objectName().isEmpty())
            ScheduleWidget->setObjectName("ScheduleWidget");
        ScheduleWidget->resize(286, 230);

        retranslateUi(ScheduleWidget);

        QMetaObject::connectSlotsByName(ScheduleWidget);
    } // setupUi

    void retranslateUi(QWidget *ScheduleWidget)
    {
        ScheduleWidget->setWindowTitle(QCoreApplication::translate("ScheduleWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScheduleWidget: public Ui_ScheduleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEWIDGET_H
