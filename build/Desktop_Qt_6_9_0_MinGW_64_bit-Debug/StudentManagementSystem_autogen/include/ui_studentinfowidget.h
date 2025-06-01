/********************************************************************************
** Form generated from reading UI file 'studentinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTINFOWIDGET_H
#define UI_STUDENTINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentInfoWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *btnAddStudent;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnDelItem;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnDelStudent;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *StudentInfoWidget)
    {
        if (StudentInfoWidget->objectName().isEmpty())
            StudentInfoWidget->setObjectName("StudentInfoWidget");
        StudentInfoWidget->resize(731, 526);
        horizontalLayout = new QHBoxLayout(StudentInfoWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(StudentInfoWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName("tableWidget");

        horizontalLayout->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnAddStudent = new QPushButton(StudentInfoWidget);
        btnAddStudent->setObjectName("btnAddStudent");

        verticalLayout->addWidget(btnAddStudent);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnDelItem = new QPushButton(StudentInfoWidget);
        btnDelItem->setObjectName("btnDelItem");

        verticalLayout->addWidget(btnDelItem);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        btnDelStudent = new QPushButton(StudentInfoWidget);
        btnDelStudent->setObjectName("btnDelStudent");

        verticalLayout->addWidget(btnDelStudent);

        verticalSpacer_4 = new QSpacerItem(20, 208, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(StudentInfoWidget);

        QMetaObject::connectSlotsByName(StudentInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *StudentInfoWidget)
    {
        StudentInfoWidget->setWindowTitle(QCoreApplication::translate("StudentInfoWidget", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("StudentInfoWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("StudentInfoWidget", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("StudentInfoWidget", "SEX", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("StudentInfoWidget", "BRITH DAY", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("StudentInfoWidget", "ADD TIME", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("StudentInfoWidget", "STUDY GOAL", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("StudentInfoWidget", "CURRENT PROGRESS", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("StudentInfoWidget", "PHOTO", nullptr));
        btnAddStudent->setText(QCoreApplication::translate("StudentInfoWidget", "ADD STUDENT", nullptr));
        btnDelItem->setText(QCoreApplication::translate("StudentInfoWidget", "DEL ITEM", nullptr));
        btnDelStudent->setText(QCoreApplication::translate("StudentInfoWidget", "DEL STUDENT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentInfoWidget: public Ui_StudentInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTINFOWIDGET_H
