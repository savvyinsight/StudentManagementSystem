#ifndef HONORWALLWIDGET_H
#define HONORWALLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
namespace Ui {
class HonorWallWidget;
}

class QPushButton;
class QScrollArea;
class QGridLayout;

constexpr int imgH=500;
constexpr int imgW=300;

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
        QLabel::mousePressEvent(event);
    }
};

class HonorWallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HonorWallWidget(QWidget *parent = nullptr);
    ~HonorWallWidget();

private:
    void setupUI();
    void loadImagesFromDatabase();
    void addImage();
    void addImageToWall(const QString& imagePath);
    void addImageToUI(const QPixmap& pixmap);
    void onImageClicked();
    void deleteImage();
    void reorderImages();
    void modifyImage();
    QPushButton *addButton;
    QPushButton *modifyButton;
    QPushButton *deleteButton;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QGridLayout *gridLayout;
    Ui::HonorWallWidget *ui;
    ClickableLabel *selectedLabel;
};

#endif // HONORWALLWIDGET_H
