#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QButtonGroup>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QButtonGroup *btnGro = new QButtonGroup(this);
    btnGro->addButton(ui->btnStudentinfo,0);
    btnGro->addButton(ui->btnSechedule,1);
    btnGro->addButton(ui->btnFinance,2);
    btnGro->addButton(ui->btnHonorWall,3);
    btnGro->addButton(ui->btnSystemset,4);

    connect(btnGro,&QButtonGroup::idClicked,ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    btnGro->button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
