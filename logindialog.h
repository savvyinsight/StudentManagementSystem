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
    QString hashPassword(const QString& password);
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QPushButton*loginButton;
    QPushButton* cancelButton;
};

#endif // LOGINDIALOG_H
