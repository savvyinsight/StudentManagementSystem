#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>
class QLineEdit;
class QPushButton;
class QCheckBox;
class QTextEdit;
class QGridLayout;
namespace Ui {
class SystemSetting;
}

class SystemSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSetting(QWidget *parent = nullptr);
    ~SystemSetting();

private:
    Ui::SystemSetting *ui;

    void createUI();
    void browseDatabasePath();
    void loadSettings();
    void updatePassword();
    void saveSettings();
    bool validatePasswordChange();
    QLineEdit* dbPathEdit;
    QPushButton* browseBtn;
    QLineEdit* oldPwdEdit;
    QLineEdit* newPwdEdit;
    QLineEdit* confirmPwdEdit;
    QCheckBox* cacheCheckBox;
    QPushButton* saveBtn;
    QTextEdit* versionInfoEdit;
    QGridLayout* mainLayout;
};

#endif // SYSTEMSETTING_H
