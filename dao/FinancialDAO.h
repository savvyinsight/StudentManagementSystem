#pragma once
#include "model/FinancialRecord.h"
#include <QList>
class FinancialDAO {
public:
    QList<FinancialRecord> fetchAll();
    bool insert(const FinancialRecord &record);
    bool update(const FinancialRecord &record);
    bool remove(int recordId);
};
