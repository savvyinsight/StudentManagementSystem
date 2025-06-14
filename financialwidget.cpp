#include "financialwidget.h"
#include "ui_financialwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

// QChartView is not in core module, so we need to add it CMakeLists.txt
// target_link_libraries(StudentManagementSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql Qt6::Charts)
// find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts)
// find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)

#include <QChartView>
#include <QLabel>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSqlQuery>
#include <QHeaderView>
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
    // connect(addButton, &QPushButton::clicked, this, &FinancialWidget::addRecord);
    // connect(deleteButton, &QPushButton::clicked, this, &FinancialWidget::deleteRecord);
    // connect(editButton, &QPushButton::clicked, this, &FinancialWidget::editRecord);
    // connect(studentComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
    //         this, &FinancialWidget::loadFinancialRecords);
    // connect(startDateEdit, &QDateEdit::dateChanged, this, &FinancialWidget::loadFinancialRecords);
    // connect(endDateEdit, &QDateEdit::dateChanged, this, &FinancialWidget::loadFinancialRecords);
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
    // updateChart(); // Update the line chart below
    // updatePieChart(); // Update the pie chart on the right
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
