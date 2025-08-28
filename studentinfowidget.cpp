#include "studentinfowidget.h"
#include "ui_studentinfowidget.h"
#include <QSqlQuery>
#include<QDialog>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QBuffer>
#include <QMessageBox>
#include <QSqlError>
#include "tabledelegates.h"
#include <QTableWidgetItem>
#include "service/StudentService.h"
#include "model/Student.h"

StudentInfoWidget::StudentInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentInfoWidget)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(100);
    ui->tableWidget->setAlternatingRowColors(true);


    //delegate gender column
    ComBoxDelegate *genderDelegate = new ComBoxDelegate(this);
    genderDelegate->setItems(QStringList()<<tr("Man")<<tr("Female"));
    ui->tableWidget->setItemDelegateForColumn(2,genderDelegate);

    //delegate progress column
    ComBoxDelegate *progressDelegate = new ComBoxDelegate(this);
    progressDelegate->setItems(QStringList()<<"0%"<<"20%"<<"40%"<<"60%"<<"80%"<<"100%");
    ui->tableWidget->setItemDelegateForColumn(6,progressDelegate);

    //delegate date column
    ui->tableWidget->setItemDelegateForColumn(3,new DateEditDelegate(this));
    ui->tableWidget->setItemDelegateForColumn(4,new DateEditDelegate(this));

    //delegate photo column
    ui->tableWidget->setItemDelegateForColumn(7,new ImageDelegate(this));

    //item changed signal
    connect(ui->tableWidget,&QTableWidget::itemChanged,this,&StudentInfoWidget::handleItemChanged);

    // 新增：初始化业务逻辑层
    m_studentService = new StudentService(this);

    refreshTable();
}

StudentInfoWidget::~StudentInfoWidget()
{
    delete ui;
}

void StudentInfoWidget::refreshTable()
{
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->setRowCount(0);
    QList<Student> students = m_studentService->getAllStudents();
    for(const Student& student : students) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(student.id));
        idItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 0, idItem);
        QTableWidgetItem* nameItem = new QTableWidgetItem(student.name);
        nameItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, nameItem);
        QTableWidgetItem* genderItem = new QTableWidgetItem(student.gender);
        genderItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, genderItem);
        // ...可扩展更多字段...
    }
    ui->tableWidget->blockSignals(false);
}

QGroupBox *StudentInfoWidget::createFormGroup()
{
    QGroupBox* formGroup = new QGroupBox(tr("Basic Info"));
    QFormLayout* formLayout = new QFormLayout(formGroup);

    //Initialize widget
    QLineEdit* idEdit = new QLineEdit();
    idEdit->setObjectName("idEdit");
    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setObjectName("nameEdit");
    QComboBox* genderCombox = new QComboBox();
    genderCombox->setObjectName("genderCombox");
    QDateEdit* birthdayEdit = new QDateEdit(QDate::currentDate());
    birthdayEdit->setObjectName("birthdayEdit");
    QDateEdit* joinDateEdit = new QDateEdit(QDate::currentDate());
    joinDateEdit->setObjectName("joinDateEdit");
    QLineEdit* goalEdit = new QLineEdit();
    goalEdit->setObjectName("goalEdit");
    QComboBox* progressCombox = new QComboBox();
    progressCombox->setObjectName("progressCombox");

    //Configure Widget
    genderCombox->addItems({tr("Man"),tr("Female")});
    progressCombox->addItems({tr("0%"),tr("20%"),tr("40%"),tr("60%"),tr("80%"),tr("100%")});
    birthdayEdit->setDisplayFormat("yyyy-MM-dd");
    joinDateEdit->setDisplayFormat("yyyy-MM-dd");
    birthdayEdit->setCalendarPopup(true);
    joinDateEdit->setCalendarPopup(true);
    //Add the Widget to Form
    formLayout->addRow(tr("ID: "),idEdit);
    formLayout->addRow(tr("Name:"),nameEdit);
    formLayout->addRow(tr("Gender: "), genderCombox);
    formLayout->addRow(tr("BrithDate:"),birthdayEdit);
    formLayout->addRow(tr("AdmissionDate: "),joinDateEdit);
    formLayout->addRow(tr("StudyGoal: "),goalEdit);
    formLayout->addRow(tr("CurrentProcess:"),progressCombox);

    return formGroup;
}

QGroupBox *StudentInfoWidget::createPhotoGroup()
{
    QGroupBox* photoGroup = new QGroupBox(tr("Upload Photo"));
    QVBoxLayout* photoLayout = new QVBoxLayout(photoGroup);
    //Initialize widget
    QLabel* lblPhotoPreview = new QLabel();
    QPushButton* btnSelectPhoto= new QPushButton(tr("Select Photo"));
    //Configure Widget
    lblPhotoPreview->setAlignment(Qt::AlignCenter);
    lblPhotoPreview->setMinimumSize(200,200);
    btnSelectPhoto->setFixedSize(100, 40);
    //Add controls to the layout
    photoLayout->addWidget(lblPhotoPreview);
    photoLayout->addWidget(btnSelectPhoto,0, Qt::AlignHCenter);
    //Connect photo selection feature
    connect(btnSelectPhoto, &QPushButton::clicked, [this, lblPhotoPreview]() {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Select photos"),
                                                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                        tr("Image File(*.png *.jpg *.jpeg)"));
        if(!fileName.isEmpty())
        {
            QPixmap pixmap(fileName);
            if(!pixmap.isNull())
            {
                pixmap=pixmap.scaled(//Smart Zoom
                    lblPhotoPreview->width()- 30,
                    lblPhotoPreview->height() - 30,
                    Qt::KeepAspectRatio
                    );
                //now can preview
                lblPhotoPreview->setPixmap(pixmap);
                QBuffer buffer(&photoData);//Convert to byte array
                buffer.open(QIODevice::WriteOnly);
                pixmap.save(&buffer,"PNG");
            }
            else {
                QMessageBox::warning(this,tr("Error"),tr("Unable to load image file!"));
            }
        }
    });
    return photoGroup;
}

//Handle dialog box confirmation
void StudentInfoWidget::handleDialogAccepted(QGroupBox *formGroup, QGroupBox *photoGroup)
{
    QLineEdit* idEdit = formGroup->findChild<QLineEdit*>("idEdit");
    QLineEdit* nameEdit = formGroup->findChild<QLineEdit*>("nameEdit");
    QComboBox* genderCombox = formGroup->findChild<QComboBox*>("genderCombox");
    QDateEdit* birthdayEdit = formGroup->findChild<QDateEdit*>("birthdayEdit");
    QDateEdit* joinDateEdit = formGroup->findChild<QDateEdit*>("joinDateEdit");
    QLineEdit* goalEdit = formGroup->findChild<QLineEdit*>("goalEdit");
    QComboBox* progressCombox = formGroup->findChild<QComboBox*>("progressCombox");
    if (idEdit->text().isEmpty() || nameEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("Error"),tr("Student ID and name cannot be empty!"));
        return;
    }
    Student student;
    student.id = idEdit->text().toInt();
    student.name = nameEdit->text();
    student.gender = genderCombox->currentText();
    student.major = goalEdit->text(); // 可根据实际字段调整
    // ...其他字段赋值...
    bool success = m_studentService->addStudent(student);
    if(success) {
        refreshTable();
        QMessageBox::information(this,tr("Success"),tr("have added student successfully: %1").arg(nameEdit->text()));
    } else {
        QMessageBox::critical(this,tr("Error"),tr("Addition failed"));
    }
}

void StudentInfoWidget::on_btnAddStudent_clicked()
{
    //Create a modal dialog using QDialog, it will block it's parent widget.
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Add Student Info"));
    dialog.setMinimumSize(600,400);
    //Initialize dialog layout
    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout* contentLayout = new QHBoxLayout();
    mainLayout->addLayout(contentLayout);
    //Add form and photo area
    QGroupBox* formGroup = createFormGroup();
    QGroupBox* photoGroup = createPhotoGroup();
    contentLayout->addWidget(formGroup,1);
    contentLayout->addWidget(photoGroup,1);
    //Add button Area
    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* btnConfirm = new QPushButton(tr("Confirm"));
    QPushButton* btnCancel = new QPushButton(tr("Cancel"));
    //Configure button
    btnConfirm->setFixedWidth(150);
    btnConfirm->setFixedWidth(150);
    //Add button to layout
    btnLayout->addStretch();
    btnLayout->addWidget(btnConfirm);
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    //add button layout to main layout
    mainLayout->addLayout(btnLayout);
    //connect button signal
    connect(btnConfirm,&QPushButton::clicked,&dialog,&QDialog::accept);
    connect(btnCancel,&QPushButton::clicked,&dialog,&QDialog::reject);

    //run dialog
    if(dialog.exec() == QDialog::Accepted) handleDialogAccepted(formGroup,photoGroup);
}


void StudentInfoWidget::on_btnDelStudent_clicked()
{
    auto selected = ui->tableWidget->selectionModel()->selectedRows();
    if(selected.isEmpty()) {
        QMessageBox::warning(this,"Warning","Please select the row you want to delete!");
        return;
    }
    bool allSuccess = true;
    for (const QModelIndex &index : selected) {
        int id = ui->tableWidget->item(index.row(),0)->text().toInt();
        if(!m_studentService->deleteStudent(id)) {
            allSuccess = false;
        }
    }
    refreshTable();
    if(allSuccess) {
        QMessageBox::information(this,"Success","Delete Success!");
    } else {
        QMessageBox::critical(this,"Error","Delete Failed!");
    }
}


void StudentInfoWidget::on_btnDelItem_clicked()
{
    auto selected = ui->tableWidget->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this,"Warning","Please select the cell you want to delete first!");
        return;
    }
    bool allSuccess = true;
    for (QTableWidgetItem *item : selected) {
        int row = item->row();
        int col = item->column();
        int id = ui->tableWidget->item(row,0)->text().toInt();
        Student student = m_studentService->getAllStudents().at(row); // 简单获取，建议优化
        switch(col) {
            case 1: student.name = ""; break;
            case 2: student.gender = ""; break;
            // ...其他字段...
        }
        if(!m_studentService->updateStudent(student)) {
            allSuccess = false;
        }
    }
    refreshTable();
    if(allSuccess) {
        QMessageBox::information(this,"Success","Update Success!");
    } else {
        QMessageBox::critical(this,"Error","Update Failed!");
    }
}

void StudentInfoWidget::handleItemChanged(QTableWidgetItem* item)
{
    const int row = item->row();
    const int col = item->column();
    if (col == 0) {
        QMessageBox::warning(this, "Warning", "Student ID is the primary key and cannot be modified!");
        refreshTable();
        return;
    }
    int id = ui->tableWidget->item(row, 0)->text().toInt();
    Student student = m_studentService->getAllStudents().at(row); // 简单获取，建议优化
    // 根据列更新 student 对应字段
    switch(col) {
        case 1: student.name = item->text(); break;
        case 2: student.gender = item->text(); break;
        // ...其他字段...
    }
    bool success = m_studentService->updateStudent(student);
    if(!success) {
        QMessageBox::critical(this, "Error", "Update Failed!");
        refreshTable();
    }
}

