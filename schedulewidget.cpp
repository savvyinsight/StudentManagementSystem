#include "schedulewidget.h"
#include "ui_schedulewidget.h"

#include <QComboBox>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QHeaderView>
#include <QBoxLayout>
#include <QSqlQuery>
#include<QMessageBox>
#include<QFormLayout>
#include<QTimeEdit>
#include<QSqlError>
#include <QTableWidgetItem>

int customWeekNumber(const QDate &date)
{
    QDate startOfYear(date.year(),1,1);
    int dayOfWeek = startOfYear.dayOfWeek();
    int days = startOfYear.daysTo(date);
    int week = (days + dayOfWeek -1)/7 + 1;
    return week;
}

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleWidget)
{
    ui->setupUi(this);

    setupUI();

    int currentYear = QDate::currentDate().year();
    int currentWeek = customWeekNumber(QDate::currentDate());

    yearComboBox->setCurrentText(QString::number(currentYear));
    weekComboBox->setCurrentText(QString("Week %1").arg(currentWeek));

    loadSchedule();

}

ScheduleWidget::~ScheduleWidget()
{
    delete ui;
}

void ScheduleWidget::setupUI() {
    // Create main vertical layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Create horizontal layout for date selection controls
    QHBoxLayout* dateLayout = new QHBoxLayout();

    // Initialize year and week combo boxes
    yearComboBox = new QComboBox(this);
    weekComboBox = new QComboBox(this);

    // Populate year combo box (from 2020 to current year + 5)
    int currentYear = QDate::currentDate().year();
    for (int year = 2020; year <= currentYear + 5; ++year) {
        yearComboBox->addItem(QString::number(year), year);
    }

    // Populate week combo box (weeks 1-52)
    for (int week = 1; week <= 52; ++week) {
        weekComboBox->addItem(QString("Week %1").arg(week), week);
    }

    // Create label to display date range
    dateRangeLabel = new QLabel(this);

    // Create week navigation buttons
    QPushButton* prevWeekBtn = new QPushButton("Previous Week", this);
    QPushButton* nextWeekBtn = new QPushButton("Next Week", this);
    prevWeekBtn->setFixedWidth(200);
    nextWeekBtn->setFixedWidth(200);

    // Add widgets to date layout
    dateLayout->addWidget(new QLabel("Year:", this));
    dateLayout->addWidget(yearComboBox);
    dateLayout->addWidget(new QLabel("Week:", this));
    dateLayout->addWidget(weekComboBox);
    dateLayout->addWidget(dateRangeLabel);
    dateLayout->addStretch();

    // Create table widget for schedule display
    tableWidget = new QTableWidget(this);
    tableWidget->setAlternatingRowColors(true);  // Alternate row colors for better readability
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // Allow single selection only
    setupTable();  // Configure table headers and structure

    // Create action buttons
    addButton = new QPushButton("Add Course", this);
    deleteButton = new QPushButton("Delete Course", this);
    addButton->setFixedWidth(200);
    deleteButton->setFixedWidth(200);

    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();  // Add stretch before buttons for centering
    buttonLayout->addWidget(prevWeekBtn);
    buttonLayout->addWidget(nextWeekBtn);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();  // Add stretch after buttons for centering

    // Add all layouts to main layout
    mainLayout->addLayout(dateLayout);
    mainLayout->addWidget(tableWidget);  // Note: Changed from tableView to tableWidget for consistency
    mainLayout->addLayout(buttonLayout);

    // Set the main layout for the widget
    setLayout(mainLayout);

    // Connect signals to slots
    connect(yearComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ScheduleWidget::loadSchedule);
    connect(weekComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ScheduleWidget::loadSchedule);
    connect(addButton, &QPushButton::clicked, this, &ScheduleWidget::addCourse);
    connect(deleteButton, &QPushButton::clicked, this, &ScheduleWidget::deleteCourse);
    connect(prevWeekBtn, &QPushButton::clicked, this, &ScheduleWidget::showPreviousWeek);
    connect(nextWeekBtn, &QPushButton::clicked, this, &ScheduleWidget::showNextWeek);
    connect(tableWidget, &QTableWidget::itemChanged, this, &ScheduleWidget::handleItemChanged);
}

void ScheduleWidget::setupTable() {
    // Define the days of the week
    QStringList days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    // Define the time slots
    times = { "Morning 1", "Morning 2", "Afternoon 1", "Afternoon 2", "Evening 1", "Evening 2" };

    // Set the number of rows (days) and columns (time slots) in the table
    tableWidget->setRowCount(days.count());
    tableWidget->setColumnCount(times.count());

    // Get the currently selected year and week from combo boxes
    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();

    // Calculate the date range for the selected week
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate startDate = weekRange.first;

    // Prepare vertical headers that will show both day name and date
    QStringList verticalHeaders;
    for (int i = 0; i < days.count(); ++i) {
        // Calculate date for each day of the week
        QDate currentDate = startDate.addDays(i);
        // Format header as "DayName\nMM/DD"
        verticalHeaders.append(QString("%1\n%2").arg(days[i]).arg(currentDate.toString("MM/dd")));
    }

    // Set the headers for the table
    tableWidget->setVerticalHeaderLabels(verticalHeaders);
    tableWidget->setHorizontalHeaderLabels(times);

    // Configure header resize behavior
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set edit triggers - allow editing on double click or when edit key is pressed
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
}


// Function to calculate the start and end dates of a given week in a year
QPair<QDate, QDate> ScheduleWidget::getWeekRange(int year, int week) {
    // Start with January 1st of the given year
    QDate startDate(year, 1, 1);

    // Calculate how many days to subtract to get to the previous Monday
    // (Qt::Monday is 1, so if dayOfWeek() is Wednesday (3), daysToSubtract is 2)
    int daysToSubtract = startDate.dayOfWeek() - Qt::Monday;

    // Adjust the start date to the beginning of the week (Monday)
    if (daysToSubtract > 0) {
        startDate = startDate.addDays(-daysToSubtract);
    }

    // Calculate the start of the requested week by adding (week-1)*7 days
    QDate weekStart = startDate.addDays((week - 1) * 7);

    // The end of the week is 6 days after the start (Sunday)
    QDate weekEnd = weekStart.addDays(6);

    // Return the pair of dates (Monday to Sunday)
    return qMakePair(weekStart, weekEnd);
}


void ScheduleWidget::loadSchedule()
{
    // Block signals to prevent itemChanged signals during data loading
    tableWidget->blockSignals(true);
    // Clear existing table contents
    tableWidget->clearContents();

    // Get currently selected year and week
    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();

    // Calculate date range for the selected week
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate startDate = weekRange.first;
    QDate endDate = weekRange.second;

    // Update date range label (format: "yyyy-MM-dd to yyyy-MM-dd")
    dateRangeLabel->setText(startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd"));

    // Initialize 2D vector to store courses (7 days x number of time slots)
    QVector<QVector<QString>> courses(7, QVector<QString>(times.count(), ""));

    // Prepare database query to get scheduled courses for this week
    QSqlQuery query;
    query.prepare("SELECT date, time, course_name FROM schedule WHERE date BETWEEN ? AND ?");
    query.addBindValue(startDate.toString("yyyy-MM-dd"));
    query.addBindValue(endDate.toString("yyyy-MM-dd"));

    if (query.exec()) {
        // Process each returned record
        while (query.next()) {
            QDate date = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
            QString time = query.value(1).toString();

            // Calculate day index (0-6) and time index
            int dayIndex = startDate.daysTo(date);
            int timeIndex = times.indexOf(time);

            // Store course name if indices are valid
            if (dayIndex >= 0 && dayIndex < 7 && timeIndex != -1) {
                courses[dayIndex][timeIndex] = query.value(2).toString();
            }
        }
    }

    // Populate the table widget with course data
    for (int day = 0; day < 7; ++day) {
        for (int time = 0; time < times.count(); ++time) {
            QTableWidgetItem* item = new QTableWidgetItem(courses[day][time]);
            item->setTextAlignment(Qt::AlignCenter);  // Center-align text
            tableWidget->setItem(day, time, item);
        }
    }

    // Re-enable signals after loading is complete
    tableWidget->blockSignals(false);
}

void ScheduleWidget::addCourse() {
    int dayIndex = tableWidget->currentRow();
    int timeIndex = tableWidget->currentColumn();

    // Validate selection (tr() for translatable strings)
    if (dayIndex == -1 || timeIndex == -1) {
        QMessageBox::warning(this, tr("Error"), tr("Please select a time slot first!"));
        return;
    }

    // Check if time slot is occupied
    if (!tableWidget->item(dayIndex, timeIndex)->text().isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("This time slot is already occupied!"));
        return;
    }

    // Create dialog with translatable strings
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Add Course"));
    QFormLayout layout(&dialog);

    // Student name combo
    QComboBox nameCombo;
    QSqlQuery nameQuery(tr("SELECT name FROM studentInfo"));
    while (nameQuery.next()) {
        nameCombo.addItem(nameQuery.value(0).toString());
    }

    // Time presets - using QTime for culture-neutral times
    QMap<int, QTime> timePresets = {
        {0, QTime(9, 0)},  // Morning 1 (9:00)
        {1, QTime(11, 0)}, // Morning 2 (11:00)
        {2, QTime(14, 0)}, // Afternoon 1 (14:00)
        {3, QTime(16, 0)}, // Afternoon 2 (16:00)
        {4, QTime(19, 0)}, // Evening 1 (19:00)
        {5, QTime(21, 0)}   // Evening 2 (21:00)
    };

    // Time edit with locale-aware formatting
    QTimeEdit timeEdit;
    timeEdit.setDisplayFormat("HH:mm"); // 24-hour format for consistency
    timeEdit.setTime(timePresets.value(timeIndex));

    // Add controls with translated labels
    layout.addRow(tr("Student Name:"), &nameCombo);
    layout.addRow(tr("Course Time:"), &timeEdit);

    // Buttons with translations
    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttons.button(QDialogButtonBox::Ok)->setText(tr("Confirm"));
    buttons.button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    layout.addRow(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) return;

    // Culture-neutral data storage format (Name,ISO Time)
    QString courseName = QString("%1,%2")
                             .arg(nameCombo.currentText())
                             .arg(timeEdit.time().toString(Qt::ISODate));

    // Get date info using system locale for display
    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate currentDate = weekRange.first.addDays(dayIndex);
    QString timeSlot = times[timeIndex]; // Original identifier from translation

    // Database operation (culture-neutral ISO dates)
    QSqlQuery query;
    query.prepare(tr("INSERT INTO schedule (date, time, course_name) VALUES (?, ?, ?)"));
    query.addBindValue(currentDate.toString(Qt::ISODate));
    query.addBindValue(timeSlot);
    query.addBindValue(courseName);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Failed to add course: %1").arg(query.lastError().text()));
    } else {
        loadSchedule();
    }
}

void ScheduleWidget::handleItemChanged(QTableWidgetItem* item)
{
    // Block signals to prevent recursive calls during data reload
    tableWidget->blockSignals(true);

    // Get the changed item's position and new value
    int day = item->row();
    int timeSlot = item->column();
    QString newCourse = item->text().trimmed();

    // Get current date range
    int year = yearComboBox->currentData().toInt();
    int week = weekComboBox->currentData().toInt();
    QPair<QDate, QDate> weekRange = getWeekRange(year, week);
    QDate date = weekRange.first.addDays(day);
    QString time = times[timeSlot];

    QSqlQuery query;
    if (newCourse.isEmpty()) {
        // Delete course if cell was cleared
        query.prepare(tr("DELETE FROM schedule WHERE date = ? AND time = ?"));
        query.addBindValue(date.toString(Qt::ISODate));  // Use ISO date format
        query.addBindValue(time);
    }
    else {
        // Use REPLACE to update or insert
        query.prepare(tr("INSERT OR REPLACE INTO schedule (date, time, course_name) VALUES (?, ?, ?)"));
        query.addBindValue(date.toString(Qt::ISODate));
        query.addBindValue(time);
        query.addBindValue(newCourse);
    }

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Operation failed: %1").arg(query.lastError().text()));
        // Reload data to restore previous state
        loadSchedule();
    }

    // Re-enable signals
    tableWidget->blockSignals(false);
}

void ScheduleWidget::deleteCourse()
{
    // Create confirmation dialog with translated text
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle(tr("Confirm Deletion"));
    confirmBox.setText(tr("Are you sure you want to delete this record?"));

    // Add translated buttons
    QPushButton* yesButton = confirmBox.addButton(tr("Confirm"), QMessageBox::YesRole);
    QPushButton* noButton = confirmBox.addButton(tr("Cancel"), QMessageBox::NoRole);

    // Original logic preserved:
    confirmBox.setDefaultButton(noButton);
    confirmBox.exec();

    if (confirmBox.clickedButton() == yesButton) {
        int dayIndex = tableWidget->currentRow();
        int timeIndex = tableWidget->currentColumn();

        if (dayIndex == -1 || timeIndex == -1) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("Please select a time slot first!"));
            return;
        }

        QTableWidgetItem* item = tableWidget->item(dayIndex, timeIndex);
        if (!item || item->text().isEmpty()) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("No course in this time slot!"));
            return;
        }

        int year = yearComboBox->currentData().toInt();
        int week = weekComboBox->currentData().toInt();
        QPair<QDate, QDate> weekRange = getWeekRange(year, week);
        QDate currentDate = weekRange.first.addDays(dayIndex);
        QString time = times[timeIndex];

        QSqlQuery query;
        query.prepare(tr("DELETE FROM schedule WHERE date = ? AND time = ?"));
        query.addBindValue(currentDate.toString("yyyy-MM-dd"));
        query.addBindValue(time);

        if (!query.exec()) {
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("Deletion failed: %1").arg(query.lastError().text()));
        } else {
            loadSchedule();
        }
    }
}


void ScheduleWidget::showPreviousWeek()
{
    int currentWeek = weekComboBox->currentIndex();
    int currentYear = yearComboBox->currentIndex();

    // If not the first week of the year, just go to previous week
    if (currentWeek > 0) {
        weekComboBox->setCurrentIndex(currentWeek - 1);
    }
    else {
        // If it's the first week, go to last week of previous year
        if (yearComboBox->currentIndex() > 0) {
            yearComboBox->setCurrentIndex(currentYear - 1);
            // Jump to last week (week 51) of the previous year
            weekComboBox->setCurrentIndex(51);
        }
        // Else: already at earliest year/week, do nothing
    }
}

void ScheduleWidget::showNextWeek()
{
    int currentWeek = weekComboBox->currentIndex();
    int currentYear = yearComboBox->currentIndex();

    // If not the last week of the year, just go to next week
    if (currentWeek < 51) {
        weekComboBox->setCurrentIndex(currentWeek + 1);
    }
    else {
        // If it's the last week, go to first week of next year
        if (yearComboBox->currentIndex() < yearComboBox->count() - 1) {
            yearComboBox->setCurrentIndex(currentYear + 1);
            // Jump to first week (week 0) of the next year
            weekComboBox->setCurrentIndex(0);
        }
        // Else: already at latest year/week, do nothing
    }
}




