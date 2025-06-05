#include "databasemanager.h"

#include<QSqlError>

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    openDatabase(dbPath);
}


DataBaseManager::~DataBaseManager()
{
    closeDatabase();
}

DataBaseManager &DataBaseManager::instance()
{
    static DataBaseManager instance;
    return instance;
}

bool DataBaseManager::openDatabase(const QString &path)
{

    db.setDatabaseName(path);
    if (db.open()){
        qDebug()<<"Can't open Database："<<db.lastError().text();
        return false;
    }
    qDebug()<<"Data base open seccessful!";
    return true;
}

void DataBaseManager::closeDatabase()
{
    if (db.isOpen()){
        db.close();
    }
}

QString DataBaseManager::getDatabasePath() const
{
    return dbPath;
}

void DataBaseManager::setDatabasePath(const QString &path)
{
    if (path  != dbPath){
        dbPath = path;
        closeDatabase();
        openDatabase(path);
    }
}
