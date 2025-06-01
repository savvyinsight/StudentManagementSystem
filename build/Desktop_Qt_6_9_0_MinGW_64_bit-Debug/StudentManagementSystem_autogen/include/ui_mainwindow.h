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
    QWidget *pageStudentinfo;
    QPushButton *pushButton;
    QWidget *pageSechedule;
    QPushButton *pushButton_2;
    QWidget *pageHonor;
    QPushButton *pushButton_3;
    QWidget *pageFinance;
    QPushButton *pushButton_4;
    QWidget *pageSystemsetting;
    QPushButton *pushButton_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(667, 617);
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
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/NGR/Desktop/book.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnStudentinfo->setIcon(icon);
        btnStudentinfo->setIconSize(QSize(80, 80));
        btnStudentinfo->setCheckable(true);
        btnStudentinfo->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnStudentinfo);

        btnSechedule = new QToolButton(widget);
        btnSechedule->setObjectName("btnSechedule");
        btnSechedule->setMinimumSize(QSize(110, 80));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/sechedule1.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSechedule->setIcon(icon1);
        btnSechedule->setIconSize(QSize(80, 80));
        btnSechedule->setCheckable(true);
        btnSechedule->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnSechedule);

        btnFinance = new QToolButton(widget);
        btnFinance->setObjectName("btnFinance");
        btnFinance->setMinimumSize(QSize(110, 80));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/money-box.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFinance->setIcon(icon2);
        btnFinance->setIconSize(QSize(80, 80));
        btnFinance->setCheckable(true);
        btnFinance->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnFinance);

        btnHonorWall = new QToolButton(widget);
        btnHonorWall->setObjectName("btnHonorWall");
        btnHonorWall->setMinimumSize(QSize(110, 80));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/rewards.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnHonorWall->setIcon(icon3);
        btnHonorWall->setIconSize(QSize(80, 80));
        btnHonorWall->setCheckable(true);
        btnHonorWall->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(btnHonorWall);

        btnSystemset = new QToolButton(widget);
        btnSystemset->setObjectName("btnSystemset");
        btnSystemset->setMinimumSize(QSize(110, 80));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/tool.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnSystemset->setIcon(icon4);
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
        pageStudentinfo = new QWidget();
        pageStudentinfo->setObjectName("pageStudentinfo");
        pushButton = new QPushButton(pageStudentinfo);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(90, 90, 75, 24));
        stackedWidget->addWidget(pageStudentinfo);
        pageSechedule = new QWidget();
        pageSechedule->setObjectName("pageSechedule");
        pushButton_2 = new QPushButton(pageSechedule);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(90, 140, 75, 24));
        stackedWidget->addWidget(pageSechedule);
        pageHonor = new QWidget();
        pageHonor->setObjectName("pageHonor");
        pushButton_3 = new QPushButton(pageHonor);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(90, 100, 75, 24));
        stackedWidget->addWidget(pageHonor);
        pageFinance = new QWidget();
        pageFinance->setObjectName("pageFinance");
        pushButton_4 = new QPushButton(pageFinance);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(60, 70, 75, 24));
        stackedWidget->addWidget(pageFinance);
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

        stackedWidget->setCurrentIndex(4);


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
        pushButton->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
