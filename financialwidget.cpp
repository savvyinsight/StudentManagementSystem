#include "financialwidget.h"
#include "ui_financialwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

// QChartView is not in core module, so we need to add it CMakeLists.txt
// find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts)
// find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)
// target_link_libraries(StudentManagementSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql Qt6::Charts)

#include <QChartView>
#include <QLabel>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSqlQuery>
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QSqlError>
#include <QPieSeries>
#include <QPieSlice>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>

FinancialWidget::FinancialWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FinancialWidget)
{
    ui->setupUi(this);
    setupUI();
    populateStudentComboBox();
}

FinancialWidget::~FinancialWidget()
{
    delete ui;
}


// This function is used to set up the user interface for the FinancialWidget class.
// It's responsible for creating and arranging various UI components.
void FinancialWidget::setupUI()
{

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();
    QHBoxLayout* middleLayout = new QHBoxLayout();
    chartView = new QChartView();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout, 60);
    mainLayout->addWidget(chartView, 40);

    // ================= Top section for filter conditions and buttons layout =================
    // Add a label for "Student Name" to the topLayout.
    topLayout->addWidget(new QLabel(tr("Student Name:"), this));
    // Create a QComboBox for selecting student names and add it to the topLayout.
    studentComboBox = new QComboBox(this);
    topLayout->addWidget(studentComboBox);

    topLayout->addWidget(new QLabel(tr("Start Date:"), this));
 // Create a QDateEdit with the date set to one month ago from the current date.
    startDateEdit = new QDateEdit(QDate::currentDate().addMonths(-1));
    startDateEdit->setCalendarPopup(true);
    topLayout->addWidget(startDateEdit);

    topLayout->addWidget(new QLabel(tr("End Date:"), this));
    endDateEdit = new QDateEdit(QDate::currentDate());
    endDateEdit->setCalendarPopup(true);
    topLayout->addWidget(endDateEdit);

    addButton = new QPushButton(tr("Add"));
    deleteButton = new QPushButton(tr("Delete"));
    editButton = new QPushButton(tr("Edit"));
    topLayout->addWidget(addButton);
    topLayout->addWidget(deleteButton);
    topLayout->addWidget(editButton);
    topLayout->addStretch();

    // Main content layout
    tableWidget = new QTableWidget();
    tableWidget->setFixedWidth(550);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setAlternatingRowColors(true);
    QStringList header = QStringList() << tr("ID") << tr("Student Name") << tr("Payment Date") << tr("Amount") << tr("Payment Type") << tr("Remarks");
    tableWidget->setColumnCount(header.count());
    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->setColumnHidden(0, true);
    middleLayout->addWidget(tableWidget);

    pieChartView = new QChartView();
    middleLayout->addWidget(pieChartView);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(200); // Ensure minimum height

    // Connections
    connect(addButton, &QPushButton::clicked, this, &FinancialWidget::addRecord);
    // connect(deleteButton, &QPushButton::clicked, this, &FinancialWidget::deleteRecord);
    // connect(editButton, &QPushButton::clicked, this, &FinancialWidget::editRecord);
    connect(studentComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &FinancialWidget::loadFinancialRecords);
    connect(startDateEdit, &QDateEdit::dateChanged, this, &FinancialWidget::loadFinancialRecords);
    connect(endDateEdit, &QDateEdit::dateChanged, this, &FinancialWidget::loadFinancialRecords);
}

void FinancialWidget::loadFinancialRecords()
{
    tableWidget->setRowCount(0);

    QString studentId = studentComboBox->currentData().toString();
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();

    QString queryStr = QString(
                           "SELECT fr.id, s.name, fr.payment_date, fr.amount, fr.payment_type, fr.notes "
                           "FROM financialRecords fr "
                           "JOIN studentInfo s ON fr.student_id = s.id "
                           "WHERE fr.payment_date BETWEEN '%1' AND '%2' %3"
                           ).arg(startDate.toString("yyyy-MM-dd"),
                                endDate.toString("yyyy-MM-dd"),
                                (studentId != "-1") ? QString("AND fr.student_id = '%1'").arg(studentId) : "");

    QSqlQuery query(queryStr);

    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(row, col, item);
        }
    }

    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    updateChart(); // Update the line chart below
    updatePieChart(); // Update the pie chart on the right
}

void FinancialWidget::populateStudentComboBox()
{
    studentComboBox->clear();
    studentComboBox->addItem(tr("All Students"), QVariant("-1")); // "-1" represents all students

    QSqlQuery query(tr("SELECT id, name FROM studentInfo"));
    while (query.next()) {
        QString id = query.value(0).toString(); // id is of QString type
        QString name = query.value(1).toString();
        studentComboBox->addItem(name, QVariant(id));
    }
}

void FinancialWidget::addRecord()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Payment Record");
    QFormLayout form(&dialog);

    // Student name combo box
    QComboBox* studentNameComboBox = new QComboBox(&dialog);
    QSqlQuery query("SELECT id, name FROM studentInfo");
    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        studentNameComboBox->addItem(name, QVariant(id)); // Associate student ID with name
    }

    QDateEdit* paymentDateEdit = new QDateEdit(&dialog);
    paymentDateEdit->setDate(QDate::currentDate()); // Set default value to current date
    paymentDateEdit->setCalendarPopup(true); // Allow calendar popup

    QLineEdit* amountEdit = new QLineEdit(&dialog);
    QLineEdit* feeTypeEdit = new QLineEdit(&dialog);
    QLineEdit* remarkEdit = new QLineEdit(&dialog);

    form.addRow("Student Name:", studentNameComboBox);
    form.addRow("Payment Date:", paymentDateEdit);
    form.addRow("Amount:", amountEdit);
    form.addRow("Payment Type:", feeTypeEdit);
    form.addRow("Remarks:", remarkEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    buttonBox.button(QDialogButtonBox::Ok)->setText("Confirm");
    buttonBox.button(QDialogButtonBox::Cancel)->setText("Cancel");
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString studentId = studentNameComboBox->currentData().toString();
        QString paymentDate = paymentDateEdit->date().toString("yyyy-MM-dd");
        double amount = amountEdit->text().toDouble();
        QString feeType = feeTypeEdit->text();
        QString remark = remarkEdit->text();

        // Prepare SQL query
        QSqlQuery query;
        query.prepare("INSERT INTO financialRecords (student_id, payment_date, amount, payment_type, notes) "
                      "VALUES (:student_id, :payment_date, :amount, :payment_type, :notes)");
        query.bindValue(":student_id", studentId);
        query.bindValue(":payment_date", paymentDate);
        query.bindValue(":amount", amount);
        query.bindValue(":payment_type", feeType);
        query.bindValue(":notes", remark);

        // Execute SQL query
        if (query.exec()) {
            qDebug() << "Record added successfully!";
            loadFinancialRecords(); // Refresh the table
        } else {
            qDebug() << "Failed to add record: " << query.lastError().text();
        }
    }
}

void FinancialWidget::updatePieChart()
{
    QString studentId = studentComboBox->currentData().toString();
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();

    QString queryStr = QString(
                           "SELECT payment_type, SUM(amount) "
                           "FROM financialRecords "
                           "WHERE payment_date BETWEEN '%1' AND '%2' %3 "
                           "GROUP BY payment_type")
                           .arg(startDate.toString("yyyy-MM-dd"))
                           .arg(endDate.toString("yyyy-MM-dd"))
                           .arg(studentId!= "-1"? QString("AND student_id = '%1'").arg(studentId) : "");

    QSqlQuery query(queryStr);

    QPieSeries* series = new QPieSeries();

    while (query.next()) {
        QString type = query.value(0).toString();
        qreal value = query.value(1).toDouble();

        if (value > 0) {
            //QString legendLabel = QString("%1<br>%2 Yuan").arg(type).arg(value);
            QString legendLabel = QString("%1 %2 CNY").arg(type).arg(value);
            QPieSlice* slice = new QPieSlice(legendLabel, value);
            slice->setLabelVisible(false);
            series->append(slice);
        }
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Payment Type Distribution"));

    // Legend settings
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBrush(QBrush(Qt::white));
    chart->legend()->setLabelColor(Qt::black);
    chart->legend()->setContentsMargins(10, 10, 10, 10);

    // Pie chart size
    series->setPieSize(0.75);

    if (pieChartView->chart()) {
        delete pieChartView->chart();
    }
    pieChartView->setChart(chart);

    // Force repaint
    pieChartView->repaint();
}


void FinancialWidget::updateChart()
{
    // 1. Get and validate date range
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    if (startDate > endDate) {
        std::swap(startDate, endDate);
        startDateEdit->setDate(startDate);
        endDateEdit->setDate(endDate);
    }

    // 2. Construct a safe SQL query
    QString studentId = studentComboBox->currentData().toString();
    QString queryStr = QString("SELECT DATE(payment_date) AS day, SUM(amount) AS total "
                               "FROM financialRecords "
                               "WHERE payment_date BETWEEN :startDate AND :endDate "
                               "%1 GROUP BY day ORDER BY day")
                           .arg(studentId != "-1"? "AND student_id = :studentId" : "");
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":startDate", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":endDate", endDate.toString("yyyy-MM-dd"));
    if (studentId != "-1") query.bindValue(":studentId", studentId);
    if (!query.exec()) qCritical() << "[SQL Error]" << query.lastError().text();

    // 3. Process query data
    QMap<QDate, qreal> dayData;
    qreal maxAmount = 0;
    while (query.next()) {
        QDate day = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
        if (!day.isValid()) continue;
        qreal amount = query.value(1).toDouble();
        dayData[day] = amount;
        if (amount > maxAmount) maxAmount = amount;
    }

    // 4. Create chart series
    QLineSeries* series = new QLineSeries();
    series->setName(QObject::tr("Sales Amount"));
    QPen pen(Qt::blue);
    series->setPen(pen);
    QDate currentDate = startDate;
    while (currentDate <= endDate) {
        qreal value = dayData.value(currentDate, 0.0);
        series->append(currentDate.startOfDay().toMSecsSinceEpoch(), value);
        currentDate = currentDate.addDays(1);
    }

    // 5. Configure axes
    QChart* chart = new QChart();
    chart->addSeries(series);
    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText(QObject::tr("Date"));
    axisX->setRange(startDate.startOfDay(), endDate.startOfDay());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText(QObject::tr("Amount (Yuan)"));
    axisY->setLabelFormat("%.0f");
    axisY->setTickInterval(10);
    axisY->setRange(0, std::ceil(maxAmount / 10) * 10 + 10); // Add 10 Yuan buffer
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 6. Apply chart
    if (chartView->chart()) delete chartView->chart();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setVisible(false);
}
