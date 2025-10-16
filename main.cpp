#include "mainwindow.h"
#include "databasemanager.h"
#include "logindialog.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBaseManager::instance();

    // use and load qss file
    QFile styleFile(":/style/qss.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&styleFile);
        QString styleSheet = in.readAll();
        a.setStyleSheet(styleSheet);
        styleFile.close();
        qDebug() << "Style sheet loaded successfully";
    } else {
        qWarning() << "Failed to load style sheet:" << styleFile.errorString();
    }

    LoginDialog login;
    if(login.exec()==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }
    return 0;
}
