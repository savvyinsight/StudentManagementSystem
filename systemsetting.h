#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

// Qt widget and utility includes
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QTranslator>
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
    QComboBox* languageCombo;
    QComboBox* themeCombo;
    void onLanguageChanged(int index);
    void onThemeChanged(int index);
    QTranslator translator;
};

#endif // SYSTEMSETTING_H
