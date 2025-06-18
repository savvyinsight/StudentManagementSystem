/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <financialwidget.h>
#include <schedulewidget.h>
#include <studentinfowidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QToolButton *btnStudentinfo;
    QToolButton *btnSechedule;
    QToolButton *btnFinance;
    QToolButton *btnHonorWall;
    QToolButton *btnSystemset;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    StudentInfoWidget *pageStudentinfo;
    ScheduleWidget *pageSechedule;
    FinancialWidget *pageFinance;
    QWidget *pageHonor;
    QWidget *pageSystemsetting;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(964, 638);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/window.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(80, 0));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        btnStudentinfo = new QToolButton(widget);
        btnStudentinfo->setObjectName("btnStudentinfo");
        btnStudentinfo->setMinimumSize(QSize(110, 80));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/studentInfo.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnStudentinfo->setIcon(icon1);
        btnStudentinfo->setIconSize(QSize(80, 80));
        btnStudentinfo->setCheckable(true);
        btnStudentinfo->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnStudentinfo);

        btnSechedule = new QToolButton(widget);
        btnSechedule->setObjectName("btnSechedule");
        btnSechedule->setMinimumSize(QSize(110, 80));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/sechedule1.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSechedule->setIcon(icon2);
        btnSechedule->setIconSize(QSize(80, 80));
        btnSechedule->setCheckable(true);
        btnSechedule->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnSechedule);

        btnFinance = new QToolButton(widget);
        btnFinance->setObjectName("btnFinance");
        btnFinance->setMinimumSize(QSize(110, 80));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/Finance.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFinance->setIcon(icon3);
        btnFinance->setIconSize(QSize(80, 80));
        btnFinance->setCheckable(true);
        btnFinance->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnFinance);

        btnHonorWall = new QToolButton(widget);
        btnHonorWall->setObjectName("btnHonorWall");
        btnHonorWall->setMinimumSize(QSize(110, 80));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/Honor.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnHonorWall->setIcon(icon4);
        btnHonorWall->setIconSize(QSize(80, 80));
        btnHonorWall->setCheckable(true);
        btnHonorWall->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnHonorWall);

        btnSystemset = new QToolButton(widget);
        btnSystemset->setObjectName("btnSystemset");
        btnSystemset->setMinimumSize(QSize(110, 80));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/Setting.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSystemset->setIcon(icon5);
        btnSystemset->setIconSize(QSize(80, 80));
        btnSystemset->setCheckable(true);
        btnSystemset->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnSystemset);

        verticalSpacer = new QSpacerItem(20, 27, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMinimumSize(QSize(80, 80));
        pageStudentinfo = new StudentInfoWidget();
        pageStudentinfo->setObjectName("pageStudentinfo");
        stackedWidget->addWidget(pageStudentinfo);
        pageSechedule = new ScheduleWidget();
        pageSechedule->setObjectName("pageSechedule");
        stackedWidget->addWidget(pageSechedule);
        pageFinance = new FinancialWidget();
        pageFinance->setObjectName("pageFinance");
        stackedWidget->addWidget(pageFinance);
        pageHonor = new QWidget();
        pageHonor->setObjectName("pageHonor");
        stackedWidget->addWidget(pageHonor);
        pageSystemsetting = new QWidget();
        pageSystemsetting->setObjectName("pageSystemsetting");
        pushButton_5 = new QPushButton(pageSystemsetting);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(90, 130, 75, 24));
        stackedWidget->addWidget(pageSystemsetting);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnStudentinfo->setText(QCoreApplication::translate("MainWindow", "Student Info", nullptr));
        btnSechedule->setText(QCoreApplication::translate("MainWindow", "Cource Sechedule", nullptr));
        btnFinance->setText(QCoreApplication::translate("MainWindow", "Finance", nullptr));
        btnHonorWall->setText(QCoreApplication::translate("MainWindow", "Honor Wall", nullptr));
        btnSystemset->setText(QCoreApplication::translate("MainWindow", "System Setting", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
