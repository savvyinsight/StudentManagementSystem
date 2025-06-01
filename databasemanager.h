#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    static DataBaseManager& instance();
    bool openDatabase(const QString& path);
    void closeDatabase();
    QString getDatabasePath() const;
    void setDatabasePath(const QString& path);
    ~DataBaseManager();
private:
    explicit DataBaseManager(QObject *parent = nullptr);
    QSqlDatabase db;
    QString dbPath = "D:/project/QTProject/StudentManagementSystem/sqllite/mydatabase.db";

signals:
};

#endif // DATABASEMANAGER_H
