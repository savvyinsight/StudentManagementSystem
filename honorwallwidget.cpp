#include "honorwallwidget.h"
#include "ui_honorwallwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlError>
#include <QBuffer>
HonorWallWidget::HonorWallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HonorWallWidget)
{
    ui->setupUi(this);
    setupUI();
    loadImagesFromDatabase();
}

HonorWallWidget::~HonorWallWidget()
{
    delete ui;
}


void HonorWallWidget::setupUI()
{
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // Button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // Add button
    QPushButton* addButton = new QPushButton(tr("Add Image"), this);
    connect(addButton, &QPushButton::clicked, this, &HonorWallWidget::addImage);
    buttonLayout->addWidget(addButton);

    // Modify button
    QPushButton* modifyButton = new QPushButton(tr("Modify Image"), this);
    // connect(modifyButton, &QPushButton::clicked, this, &HonorWallWidget::modifyImage);
    buttonLayout->addWidget(modifyButton);

    // Delete button
    QPushButton* deleteButton = new QPushButton(tr("Delete Image"), this);
    connect(deleteButton, &QPushButton::clicked, this, &HonorWallWidget::deleteImage);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // Allow content area to resize

    // Content area
    QWidget* contentWidget = new QWidget(scrollArea);
    gridLayout = new QGridLayout(contentWidget);
    contentWidget->setLayout(gridLayout);

    // Set the content of the scroll area
    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);

    // Set the main layout
    setLayout(mainLayout);
}

void HonorWallWidget::loadImagesFromDatabase()
{
    // Clear all contents in the layout
     QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item; // Delete layout item
    }

    // Load images from the database
    QSqlQuery query("SELECT id, image_data FROM honorWall");
    while (query.next()) {
        int id = query.value(0).toInt();
        QByteArray imageData = query.value(1).toByteArray();

        // Convert binary data to QPixmap
        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        if (!pixmap.isNull()) {
            // Display the image on the interface
            ClickableLabel* imageLabel = new ClickableLabel(contentWidget);
            QPixmap scaledPixmap = pixmap.scaled(imgW, imgH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            imageLabel->setAlignment(Qt::AlignCenter);
            imageLabel->setStyleSheet("border: 1px solid #ccc; padding: 5px;");
            imageLabel->setProperty("id", id); // Set the id property

            connect(imageLabel, &ClickableLabel::clicked, this, &HonorWallWidget::onImageClicked);

            // Dynamically add to the grid layout
            int row = gridLayout->count() / 3; // 3 images per row
            int col = gridLayout->count() % 3;
            gridLayout->addWidget(imageLabel, row, col);
        } else {
            qWarning() << "Failed to load image data!";
        }
    }
}

void HonorWallWidget::addImage()
{
    // Open file dialog to select an image
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if (!imagePath.isEmpty()) addImageToWall(imagePath);
}

void HonorWallWidget::addImageToWall(const QString& imagePath)
{
    // Load image
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to load image!"));
        return;
    }
    // Convert image to binary data
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG"); // Save as PNG format
    // Insert image info into database
    QSqlQuery query;
    query.prepare("INSERT INTO honorWall (image_data, description, added_date) "
                  "VALUES(:image_data, :description, :added_date)");
    query.bindValue(":image_data", imageData);
    query.bindValue(":description", tr("No description")); // Default description
    query.bindValue(":added_date", QDate::currentDate().toString());
    if (!query.exec()) {
        qWarning() << tr("Failed to insert data:") << query.lastError().text();
        return;
    }
    // Display the image in UI
    addImageToUI(pixmap);
}

void HonorWallWidget::addImageToUI(const QPixmap& pixmap)
{
    if (pixmap.isNull()) {
        qWarning() << tr("Invalid image!");
        return;
    }
    QPixmap scaledPixmap = pixmap.scaled(imgW, imgH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // Create clickable QLabel to display image
    ClickableLabel* imageLabel = new ClickableLabel(contentWidget);
    if (!imageLabel) {
        qWarning() << tr("Failed to create QLabel!");
        return;
    }
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 1px solid #ccc; padding: 5px;");
    connect(imageLabel, &ClickableLabel::clicked, this, &HonorWallWidget::onImageClicked);
    // Dynamically add to grid layout
    int row = gridLayout->count() / 3; // 3 images per row
    int col = gridLayout->count() % 3;
    gridLayout->addWidget(imageLabel, row, col);
}

void HonorWallWidget::onImageClicked()
{
    if (selectedLabel) { // Clear previous selection style
        selectedLabel->setStyleSheet("border: 1px solid #ccc; padding: 5px;");
    }

    selectedLabel = qobject_cast<ClickableLabel*>(sender());
    if (selectedLabel) { // Update selected image style
        selectedLabel->setStyleSheet("border: 2px solid red; padding: 5px;");
    }
}


void HonorWallWidget::deleteImage()
{
    if (!selectedLabel) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Please select an image first!"));
        return;
    }

    // Confirm deletion
    if (QMessageBox::question(this,
                              tr("Confirm Deletion"),
                              tr("Are you sure you want to delete this image?"))
        != QMessageBox::Yes) {
        return;
    }

    // Get database ID of selected image
    int id = selectedLabel->property("id").toInt();

    // Delete record from database
    QSqlQuery query;
    query.prepare("DELETE FROM honorWall WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qWarning() << tr("Failed to delete data:") << query.lastError().text();
        return;
    }

    // Remove image from UI
    gridLayout->removeWidget(selectedLabel);
    delete selectedLabel;
    selectedLabel = nullptr;
    reorderImages(); // Reorder remaining images
}

void HonorWallWidget::reorderImages()
{
    // Clear all items from the layout
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->setParent(nullptr); // Remove widget
        }
        delete item; // Delete layout item
    }

    loadImagesFromDatabase(); // Reload images
}
