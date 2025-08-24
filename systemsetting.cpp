#include "systemsetting.h"
#include "ui_systemsetting.h"
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include "settings.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QSqlError>

SystemSetting::SystemSetting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SystemSetting)
{
    ui->setupUi(this);
    setFixedSize(400,600);
    createUI();

    loadSettings();
}

SystemSetting::~SystemSetting()
{
    delete ui;
}


void SystemSetting::createUI(){
    dbPathEdit = new QLineEdit(this);
    browseBtn = new QPushButton(tr("Browse..."),this);
    oldPwdEdit = new QLineEdit(this);
    newPwdEdit = new QLineEdit(this);
    confirmPwdEdit = new QLineEdit(this);
    cacheCheckBox = new QCheckBox(tr("Remember Login Info"),this);
    saveBtn = new QPushButton(tr("Save"),this);
    versionInfoEdit = new QTextEdit(this);

    oldPwdEdit->setEchoMode(QLineEdit::Password);
    newPwdEdit->setEchoMode(QLineEdit::Password);
    confirmPwdEdit->setEchoMode(QLineEdit::Password);

    versionInfoEdit->setPlainText(tr("Student Management System 1.0\nDev Environmnt ：QTC++6.6，QtCreator12.0.2，Win10"));
    versionInfoEdit->setReadOnly(true);

    mainLayout =new QGridLayout(this);
    mainLayout->addWidget(new QLabel(tr("DataBase Path: "),this));
    mainLayout->addWidget(dbPathEdit,0,1);
    mainLayout->addWidget(browseBtn,0,2);
    mainLayout->addWidget(new QLabel(tr("Old Password: "),this),1,0);
    mainLayout->addWidget(oldPwdEdit,1,1,1,2);
    mainLayout->addWidget(new QLabel(tr("new Password: "),this),2,0);
    mainLayout->addWidget(newPwdEdit,2,1,1,2);
    mainLayout->addWidget(new QLabel(tr("Confirm Password: "),this),3,0);
    mainLayout->addWidget(confirmPwdEdit,3,1,1,2);
    mainLayout->addWidget(cacheCheckBox,4,0,1,3);
    mainLayout->addWidget(saveBtn,5,1,1,2);
    mainLayout->addWidget(versionInfoEdit,6,0,1,3);
    setLayout(mainLayout);
    connect(browseBtn,&QPushButton::clicked,this,&SystemSetting::browseDatabasePath);
    connect(saveBtn,&QPushButton::clicked,this,&SystemSetting::saveSettings);
}

void SystemSetting::browseDatabasePath()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Select Database File"),"","SQLite Databases (*.db *.sqlite)");
    if(!path.isEmpty()) dbPathEdit->setText(path);
}

void SystemSetting::loadSettings()
{
    dbPathEdit->setText(Settings::instance().getDatabasePath());
    cacheCheckBox->setChecked(Settings::instance().getCacheEnabled());
}

void SystemSetting::updatePassword()
{
    if (!validatePasswordChange()) return;

    QString newHash = QString(QCryptographicHash::hash(
                                  newPwdEdit->text().toUtf8(),
                                  QCryptographicHash::Sha256
                                  ).toHex());

    QSqlQuery query;
    query.prepare("UPDATE users SET password = ? WHERE username = ?");
    query.addBindValue(newHash);
    query.addBindValue(Settings::instance().getLastUser());

    if (!query.exec()) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Password update failed: %1")+query.lastError().text());
        return;
    }

    QMessageBox::information(this,
                             tr("Success"),
                             tr("Password updated successfully"));
}

void SystemSetting::saveSettings()
{
    QString newDbPath = dbPathEdit->text();
    Settings::instance().setDatabasePath(newDbPath);
    Settings::instance().setCacheEnabled(cacheCheckBox->isChecked());

    if (!newPwdEdit->text().isEmpty()) {
        updatePassword();
    }

    if (newDbPath != Settings::instance().getDatabasePath()) {
        QMessageBox::information(this,
                                 tr("Information"),
                                 tr("Database path changes will take effect after restart"));
    }
}

bool SystemSetting::validatePasswordChange()
{
    if (newPwdEdit->text() != confirmPwdEdit->text()) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("New password and confirmation password do not match"));
        return false;
    }

    QString currentUser = Settings::instance().getLastUser();
    if (currentUser.isEmpty()) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Current user not found"));
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(currentUser);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Database query failed: %1")+query.lastError().text());
        return false;
    }

    QString storedHash = query.value(0).toString();
    QString inputHash = QString(QCryptographicHash::hash(
                                    oldPwdEdit->text().toUtf8(),
                                    QCryptographicHash::Sha256
                                    ).toHex());

    if (storedHash != inputHash) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Old password is incorrect"));
        return false;
    }

    return true;
}
