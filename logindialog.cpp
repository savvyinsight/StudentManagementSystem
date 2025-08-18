#include "logindialog.h"
#include "ui_logindialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include "Settings.h"
#include <QMessageBox>
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
        QString hashedInitialPassword = hashPassword(initialPassword);
        query.prepare("INSERT INTO users (username, password) VALUES(:username, :password)");
        query.bindValue(":username", initialUsername);
        query.bindValue(":password", hashedInitialPassword);

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
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &LoginDialog::reject);

    // Try to load cached credentials
    QString cachedUsername, cachedPassword;
    if (loadCredentials(cachedUsername, cachedPassword)) {
        usernameLineEdit->setText(cachedUsername);
        passwordLineEdit->setText(cachedPassword);
    }
}

QString LoginDialog::hashPassword(const QString& password){
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes,QCryptographicHash::Sha256);
    return QString(hashBytes.toHex());
}

bool LoginDialog::loadCredentials(QString& username, QString& password)
{
    QSettings& settings = Settings::instance().getQSettings();
    username = settings.value("Login/Username").toString();
    QString encryptedPassword = settings.value("Login/EncryptedPassword").toString();

    if (!username.isEmpty() && !encryptedPassword.isEmpty()) {
        password = decryptPassword(encryptedPassword);
        return true;
    }
    return false;
}

// Use a more secure key derivation approach in production
const QByteArray encryptionKey = "your_secure_encryption_key_here!";

QString LoginDialog::encryptPassword(const QString& password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray encryptedBytes;
    encryptedBytes.reserve(passwordBytes.size());

    for (int i = 0; i < passwordBytes.size(); ++i) {
        encryptedBytes.append(passwordBytes[i] ^ encryptionKey[i % encryptionKey.size()]);
    }
    return QString::fromLatin1(encryptedBytes.toBase64());
}

QString LoginDialog::decryptPassword(const QString& encryptedPassword)
{
    QByteArray encryptedBytes = QByteArray::fromBase64(encryptedPassword.toLatin1());
    QByteArray decryptedBytes;
    decryptedBytes.reserve(encryptedBytes.size());

    for (int i = 0; i < encryptedBytes.size(); ++i) {
        decryptedBytes.append(encryptedBytes[i] ^ encryptionKey[i % encryptionKey.size()]);
    }
    return QString::fromUtf8(decryptedBytes);
}

void LoginDialog::onLoginButtonClicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this,
                             tr("Login Failed"),
                             tr("Username and password cannot be empty."));
        return;
    }

    if (validateUser(username, password)) {
        saveCredentials(username, password);
        Settings::instance().setLastUser(username);
        accept();
    } else {
        QMessageBox::warning(this,
                             tr("Login Failed"),
                             tr("Invalid username or password."));
    }
}

bool LoginDialog::validateUser(const QString& username, const QString& password)
{
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("SELECT 1 FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        qWarning() << tr("Database query error:") << query.lastError().text();
        return false;
    }
    return query.next();
}

void LoginDialog::saveCredentials(const QString& username, const QString& password)
{
    //Store the username and the encrypted password
    QSettings& settings = Settings::instance().getQSettings();
    settings.setValue("Login/Username", username);
    settings.setValue("Login/EncryptedPassword", encryptPassword(password));
}

// QString LoginDialog::hashPassword(const QString& password)
// {
//     QByteArray passwordBytes = password.toUtf8();
//     QByteArray salt = "fixed_salt_should_be_random_in_production"; // Use random salt in production
//     QByteArray saltedPassword = salt + passwordBytes;

//     QByteArray hashBytes = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256);
//     return QString(hashBytes.toHex());
// }
