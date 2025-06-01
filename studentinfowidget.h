#ifndef STUDENTINFOWIDGET_H
#define STUDENTINFOWIDGET_H

#include <QWidget>
#include <QByteArray>
namespace Ui {
class StudentInfoWidget;
}
class QGroupBox;
class StudentInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfoWidget(QWidget *parent = nullptr);
    ~StudentInfoWidget();

private slots:
    void on_btnAddStudent_clicked();

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
