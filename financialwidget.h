#ifndef FINANCIALWIDGET_H
#define FINANCIALWIDGET_H

#include <QWidget>

namespace Ui {
class FinancialWidget;
}

class QChartView;
class QTableWidget;
class QComboBox;
class QPushButton;
class QDateEdit;

class FinancialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FinancialWidget(QWidget *parent = nullptr);
    ~FinancialWidget();

private:
    void setupUI();
    void loadFinancialRecords();
    void populateStudentComboBox();
    QChartView* pieChartView;
    QTableWidget* tableWidget;
    QComboBox* studentComboBox;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* editButton;
    QChartView* chartView;
    QDateEdit* startDateEdit;
    QDateEdit* endDateEdit;
    Ui::FinancialWidget *ui;
};

#endif // FINANCIALWIDGET_H
