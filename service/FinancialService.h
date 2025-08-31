
#pragma once
#include <QObject>
#include <QList>
#include <QtConcurrent>
#include <QFutureWatcher>
#include "dao/FinancialDAO.h"
#include "model/FinancialRecord.h"

class FinancialService : public QObject {
    Q_OBJECT
public:
    explicit FinancialService(QObject *parent = nullptr);
    QList<FinancialRecord> getAllRecords();
    bool addRecord(const FinancialRecord &record);
    bool updateRecord(const FinancialRecord &record);
    bool deleteRecord(int recordId);
    // 异步/网络接口预留
    void fetchRecordsAsync();
    void syncRecordsToCloud();
signals:
    void recordsFetched(const QList<FinancialRecord>& records);
private:
    FinancialDAO m_financialDao;
};
