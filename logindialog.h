#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}
class QLineEdit;
class QPushButton;
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

    void loginDialogFunc();
    void checkAndCreateInitialUser();
    void onLoginButtonClicked();
    bool loadCredentials(QString& username, QString& password);
    QString encryptPassword(const QString& password);
    QString decryptPassword(const QString& encryptedPassword);
    bool validateUser(const QString& username, const QString& password);
    void saveCredentials(const QString& username, const QString& password);
    QString hashPassword(const QString& password);
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QPushButton*loginButton;
    QPushButton* cancelButton;
};

#endif // LOGINDIALOG_H
