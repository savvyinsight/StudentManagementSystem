#include "logindialog.h"
#include "ui_logindialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlError>
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    loginDialogFunc();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::checkAndCreateInitialUser()
{
    const QString initialUsername = "admin";
    const QString initialPassword = "admin123";

    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM users");

    if (query.next() && query.value(0).toInt() == 0) {
        // Table is empty, create initial user
        // QString hashedInitialPassword = hashPassword(initialPassword);
        // query.prepare("INSERT INTO users (username, password) VALUES(:username, :password)");
        // query.bindValue(":username", initialUsername);
        // query.bindValue(":password", hashedInitialPassword);

        if (!query.exec()) {
            qWarning() << tr("Failed to create initial user:") << query.lastError().text();
        }
    }
}

void LoginDialog::loginDialogFunc()
{
    checkAndCreateInitialUser(); // Check if database is empty, create initial user if needed

    // Window setup
    setWindowTitle(tr("Teaching Management System"));
    setWindowIcon(QIcon(":/icon/studentInfo.ico"));
    setFixedSize(260, 180);

    // Create widgets
    QLabel* usernameLabel = new QLabel(tr("Username:"), this);
    QLabel* passwordLabel = new QLabel(tr("Password:"), this);
    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton(tr("Login"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);

    // Layout
    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(usernameLabel, 0, 0);
    mainLayout->addWidget(usernameLineEdit, 0, 1);
    mainLayout->addWidget(passwordLabel, 1, 0);
    mainLayout->addWidget(passwordLineEdit, 1, 1);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout, 2, 0, 1, 2); // Span two columns

    // Connect signals and slots
    // connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &LoginDialog::reject);

    // Try to load cached credentials
    QString cachedUsername, cachedPassword;
    // if (loadCredentials(cachedUsername, cachedPassword)) {
    //     usernameLineEdit->setText(cachedUsername);
    //     passwordLineEdit->setText(cachedPassword);
    // }
}
