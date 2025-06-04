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
    progressDelegate->setItems(QStringList()<<"0%"<<"20%"<<"40%"<<"60%"<<"80"<<"100%");
    ui->tableWidget->setItemDelegateForColumn(6,progressDelegate);

    //delegate date column
    ui->tableWidget->setItemDelegateForColumn(3,new DateEditDelegate(this));
    ui->tableWidget->setItemDelegateForColumn(4,new DateEditDelegate(this));

    //delegate photo column
    ui->tableWidget->setItemDelegateForColumn(7,new ImageDelegate(this));

    //item changed signal
    connect(ui->tableWidget,&QTableWidget::itemChanged,this,&StudentInfoWidget::handleItemChanged);

    refreshTable();
}

StudentInfoWidget::~StudentInfoWidget()
{
    delete ui;
}

void StudentInfoWidget::refreshTable()
{
    //when load data, block the table emit itemChanged etc. signal.
    //avoid unnesessary signal process or handle
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->setRowCount(0);

    QSqlQuery query("SELECT * FROM studentInfo");
    while(query.next())
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for(int col = 0;col < ui->tableWidget->columnCount();++col)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);

            if(col==ui->tableWidget->columnCount()-1) // handle photo
            {
                QByteArray photoData = query.value(col).toByteArray();
                if(!photoData.isEmpty())
                {
                    QPixmap photo;
                    photo.loadFromData(photoData);
                    item->setData(Qt::DecorationRole,photo.scaled(100,100,Qt::KeepAspectRatio));
                    item->setData(Qt::UserRole,photoData);
                }

            }else
            {
                item->setText(query.value(col).toString());
            }
            ui->tableWidget->setItem(row,col,item);
        }
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
    //Get form data
    QLineEdit* idEdit = formGroup->findChild<QLineEdit*>("idEdit");
    QLineEdit* nameEdit = formGroup->findChild<QLineEdit*>("nameEdit");
    QComboBox* genderCombox = formGroup->findChild<QComboBox*>("genderCombox");
    QDateEdit* birthdayEdit = formGroup->findChild<QDateEdit*>("birthdayEdit");
    QDateEdit* joinDateEdit = formGroup->findChild<QDateEdit*>("joinDateEdit");
    QLineEdit* goalEdit = formGroup->findChild<QLineEdit*>("goalEdit");
    QComboBox* progressCombox = formGroup->findChild<QComboBox*>("progressCombox");
    //Data Validation
    if (idEdit->text().isEmpty() || nameEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("Error"),tr("Student ID and name cannot be empty!"));
        return;
    }
    //Check the uniqueness of the student ID
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM studentInfo WHERE id = ?");
    checkQuery.addBindValue(idEdit->text());
    if (checkQuery.exec() && checkQuery.next()){
        QMessageBox::warning(this,tr("Error"),tr("The student ID %1 already exists!").arg(idEdit->text()));
        return;
    }
    //Insert data
    QSqlDatabase::database().transaction();
    QSqlQuery insertQuery;
    insertQuery.prepare(
        "INSERT INTO studentInfo"
        "(id,name,gender,birthday,join_date,study_goal,progress,photo)"
        "VALUES(?,?,?,?,?,?,?,?)"
        );
    //Bind parameters
    insertQuery.addBindValue(idEdit->text());
    insertQuery.addBindValue(nameEdit->text());
    insertQuery.addBindValue(genderCombox->currentText());
    insertQuery.addBindValue(birthdayEdit->date().toString("yyyy-MM-dd"));
    insertQuery.addBindValue(joinDateEdit->date().toString("yyyy-MM-dd"));
    insertQuery.addBindValue(goalEdit->text());
    insertQuery.addBindValue(progressCombox->currentText());
    insertQuery.addBindValue(photoData.isEmpty()?QVariant():photoData);
    // if not succeed to insert any one data, we rollback
    if (!insertQuery.exec()){
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this,tr("Error"),tr("Addition failed:")+insertQuery.lastError().text());
    }
    else
    {
        //if all insert success, we commit and change database.
        QSqlDatabase::database().commit();
        refreshTable();
        QMessageBox::information(this,tr("Success"),tr("have added student successfully: %1").arg(nameEdit->text()));
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
    if(selected.isEmpty())
    {
        QMessageBox::warning(this,"Warning","Please select the row you want to delete!");
        return;
    }
    QSqlDatabase::database().transaction();
    foreach (const QModelIndex &index, selected) {
        QString id = ui->tableWidget->item(index.row(),0)->text();
        QSqlQuery query;
        query.prepare("DELETE FROM studentInfo WHERE id = ?");
        query.addBindValue(id);
        if(!query.exec())
        {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this,"Error","Delete Failed: "+query.lastError().text());
            return;
        }
    }
    QSqlDatabase::database().commit();
    refreshTable();
}


void StudentInfoWidget::on_btnDelItem_clicked()
{
    auto selected = ui->tableWidget->selectedItems();
    if(selected.isEmpty())
    {
        QMessageBox::warning(this,"Warning","Please select the cell you want to delete first!");
        return;
    }

    QSqlDatabase::database().transaction();
    foreach (QTableWidgetItem *item, selected) {
        int row = item->row();
        int col = item->column();
        QString id = ui->tableWidget->item(row,0)->text();

        const QStringList columns = {"id","name","gender","birthday","join_date",
                                     "study_goal","progress","photo"};

        QSqlQuery query;
        query.prepare(QString("UPDATE studentInfo SET %1 = ? WHERE id= ?").arg(columns[col]));

        query.addBindValue("");
        query.addBindValue(id);

        if(!query.exec())
        {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this,"Error","Update Failed: "+query.lastError().text());
            return;
        }

        QSqlDatabase::database().commit();
        refreshTable();
    }
}

void StudentInfoWidget::handleItemChanged(QTableWidgetItem* item)
{
    // Get the modified item's position
    const int row = item->row();
    const int col = item->column();

    // If trying to modify the ID column (column 0), restore original value and show warning
    if (col == 0) {
        QMessageBox::warning(this, "Warning", "Student ID is the primary key and cannot be modified!");
        refreshTable();
        return;
    }

    const QString originalId = ui->tableWidget->item(row, 0)->text(); // Original student ID
    const QString columnName = QStringList{ "id", "name", "gender", "birthday",
                                           "join_date", "study_goal", "progress", "photo" }[col];

    // Start database transaction
    QSqlDatabase::database().transaction();
    try {
        // Prepare update statement
        QSqlQuery updateQuery;
        updateQuery.prepare(QString("UPDATE studentInfo SET %1 = ? WHERE id = ?").arg(columnName));

        // Bind data
        if (col == columnName.size()-1) { // Handle photo column
            updateQuery.addBindValue(item->data(Qt::UserRole).toByteArray());
        }
        else {
            updateQuery.addBindValue(item->text().trimmed());
        }

        updateQuery.addBindValue(originalId);

        // Execute update
        if (!updateQuery.exec()) {
            throw std::runtime_error("Update failed: " + updateQuery.lastError().text().toStdString());
        }

        // Commit transaction if successful
        QSqlDatabase::database().commit();
    }
    catch (const std::exception& e) {
        // Rollback transaction on error
        QSqlDatabase::database().rollback();
        // Refresh table to restore original data
        refreshTable();
        // Show error message
        QMessageBox::critical(this, "Operation Failed", QString::fromUtf8(e.what()));
    }
}

