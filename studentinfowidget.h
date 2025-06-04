#ifndef STUDENTINFOWIDGET_H
#define STUDENTINFOWIDGET_H

#include <QWidget>
#include <QByteArray>
namespace Ui {
class StudentInfoWidget;
}

class QTableWidgetItem;
class QGroupBox;

class StudentInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfoWidget(QWidget *parent = nullptr);
    ~StudentInfoWidget();

private slots:
    void on_btnAddStudent_clicked();

    void on_btnDelStudent_clicked();

    void on_btnDelItem_clicked();
    void handleItemChanged(QTableWidgetItem* item);
private:
    void refreshTable();
    QGroupBox* createFormGroup();
    QGroupBox* createPhotoGroup();
    void handleDialogAccepted(QGroupBox* formGroup,QGroupBox* photoGroup);


    //use Byte Array to save on database.
    QByteArray photoData;
    Ui::StudentInfoWidget *ui;
};

#endif // STUDENTINFOWIDGET_H
