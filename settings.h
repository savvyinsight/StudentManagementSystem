#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings
{
public:
    static Settings& instance();
    QSettings& getQSettings() {return settings;}

    // Database settings
    QString getDatabasePath() const;
    void setDatabasePath(const QString& path);

    // Login settings
    bool getCacheEnabled() const;
    void setCacheEnabled(bool enabled);
    QString getLastUser() const;
    void setLastUser(const QString& user);

private:
    Settings();
    QSettings settings;

    // Prevent copying
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};

#endif // SETTINGS_H
