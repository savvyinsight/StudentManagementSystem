#include "financialwidget.h"
#include "ui_financialwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
// QChartView is not in core module, so we need to add it CMakeLists.txt
#include <QChartView>
#include <QLabel>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
FinancialWidget::FinancialWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FinancialWidget)
{
    ui->setupUi(this);
    setupUI();
}

FinancialWidget::~FinancialWidget()
{
    delete ui;
}


// This function is used to set up the user interface for the FinancialWidget class.
// It's responsible for creating and arranging various UI components.
void FinancialWidget::setupUI()
{
    // Create a vertical layout for the main layout of the widget and set this widget as its parent.
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // Create a horizontal layout for the top section of the UI.
    QHBoxLayout* topLayout = new QHBoxLayout();
    // Create a horizontal layout for the middle section of the UI.
    QHBoxLayout* middleLayout = new QHBoxLayout();
    // Create a QChartView instance. This will be used to display a chart.
    chartView = new QChartView();
    // Add the topLayout to the mainLayout.
    mainLayout->addLayout(topLayout);
    // Add the middleLayout to the mainLayout and set its stretch factor to 60 (to occupy 60% of the available height).
    mainLayout->addLayout(middleLayout, 60);
    // Add the chartView to the mainLayout and set its stretch factor to 40 (to occupy 40% of the available height).
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
