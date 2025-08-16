#include "settings.h"

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

Settings::Settings() : settings("config.ini", QSettings::IniFormat)
{
}

// Database settings implementation
QString Settings::getDatabasePath() const
{
    return settings.value("Database/Path", "users.db").toString();
}

void Settings::setDatabasePath(const QString& path)
{
    settings.setValue("Database/Path", path);
}

// Login settings implementation
bool Settings::getCacheEnabled() const
{
    return settings.value("Login/CacheEnabled", true).toBool();
}

void Settings::setCacheEnabled(bool enabled)
{
    settings.setValue("Login/CacheEnabled", enabled);
}

QString Settings::getLastUser() const
{
    return settings.value("Login/LastUser", "").toString();
}

void Settings::setLastUser(const QString& user)
{
    settings.setValue("Login/LastUser", user);
}
