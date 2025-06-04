#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>

namespace Ui {
class ScheduleWidget;
}

class QTableWidget;
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidgetItem;
class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleWidget(QWidget *parent = nullptr);
    ~ScheduleWidget();

private:
    void setupUI();
    void setupTable();
    void loadSchedule();
    void addCourse();
    void handleItemChanged(QTableWidgetItem* item);
    void deleteCourse();
    QPair<QDate, QDate> getWeekRange(int year, int week);
    QTableWidget *tableWidget;
    QComboBox *yearComboBox;
    QComboBox *weekComboBox;
    QLabel *dateRangeLabel;//Label showing the date range
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *prevWeekButton;
    QPushButton *nextWeekButton;

    //Course data storage structure: key is (year,week), value is schedule data
    QMap<QPair<int,int>, QVector<QVector<QString>>> scheduleData;
    QStringList times; //Morning1 ,Morning2


    Ui::ScheduleWidget *ui;
};

#endif // SCHEDULEWIDGET_H
