#include "honorwallwidget.h"
#include "ui_honorwallwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QSqlQuery>

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
    // connect(addButton, &QPushButton::clicked, this, &HonorWallWidget::addImage);
    buttonLayout->addWidget(addButton);

    // Modify button
    QPushButton* modifyButton = new QPushButton(tr("Modify Image"), this);
    // connect(modifyButton, &QPushButton::clicked, this, &HonorWallWidget::modifyImage);
    buttonLayout->addWidget(modifyButton);

    // Delete button
    QPushButton* deleteButton = new QPushButton(tr("Delete Image"), this);
    // connect(deleteButton, &QPushButton::clicked, this, &HonorWallWidget::deleteImage);
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
    QSqlQuery query("SELECT id, image_data FROM honor_wall");
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

            // connect(imageLabel, &ClickableLabel::clicked, this, &HonorWallWidget::onImageClicked);

            // Dynamically add to the grid layout
            int row = gridLayout->count() / 3; // 3 images per row
            int col = gridLayout->count() % 3;
            gridLayout->addWidget(imageLabel, row, col);
        } else {
            qWarning() << "Failed to load image data!";
        }
    }
}
