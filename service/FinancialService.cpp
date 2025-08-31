#include "FinancialService.h"
// QtConcurrent 头文件
#include <QtConcurrent>
#include <QFutureWatcher>
FinancialService::FinancialService(QObject *parent) : QObject(parent) {}
QList<FinancialRecord> FinancialService::getAllRecords() { return m_financialDao.fetchAll(); }
bool FinancialService::addRecord(const FinancialRecord &record) { return m_financialDao.insert(record); }
bool FinancialService::updateRecord(const FinancialRecord &record) { return m_financialDao.update(record); }
bool FinancialService::deleteRecord(int recordId) { return m_financialDao.remove(recordId); }
void FinancialService::fetchRecordsAsync() {
	// 使用 QtConcurrent 异步查询
	QFutureWatcher<QList<FinancialRecord>>* watcher = new QFutureWatcher<QList<FinancialRecord>>(this);
	connect(watcher, &QFutureWatcher<QList<FinancialRecord>>::finished, this, [this, watcher]() {
		emit recordsFetched(watcher->result());
		watcher->deleteLater();
	});
	watcher->setFuture(QtConcurrent::run([this]() {
		return m_financialDao.fetchAll();
	}));
}
void FinancialService::syncRecordsToCloud() { /* TODO: 网络实现 */ }
