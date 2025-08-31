#include "FinancialDAO.h"
#include <QSqlQuery>
#include <QVariant>
QList<FinancialRecord> FinancialDAO::fetchAll() {
    QList<FinancialRecord> records;
    QSqlQuery query("SELECT id, type, amount, date FROM financial");
    while(query.next()) {
        FinancialRecord record;
        record.id = query.value(0).toInt();
        record.type = query.value(1).toString();
        record.amount = query.value(2).toDouble();
        record.date = query.value(3).toString();
        records.append(record);
    }
    return records;
}
bool FinancialDAO::insert(const FinancialRecord &record) {
    QSqlQuery query;
    query.prepare("INSERT INTO financial (type, amount, date) VALUES (?, ?, ?)");
    query.addBindValue(record.type);
    query.addBindValue(record.amount);
    query.addBindValue(record.date);
    return query.exec();
}
bool FinancialDAO::update(const FinancialRecord &record) {
    QSqlQuery query;
    query.prepare("UPDATE financial SET type = ?, amount = ?, date = ? WHERE id = ?");
    query.addBindValue(record.type);
    query.addBindValue(record.amount);
    query.addBindValue(record.date);
    query.addBindValue(record.id);
    return query.exec();
}
bool FinancialDAO::remove(int recordId) {
    QSqlQuery query;
    query.prepare("DELETE FROM financial WHERE id = ?");
    query.addBindValue(recordId);
    return query.exec();
}
