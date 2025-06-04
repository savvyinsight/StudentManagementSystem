#ifndef TABLEDELEGATES_H
#define TABLEDELEGATES_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QBuffer>

class ComBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComBoxDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent){}
    //set dropdown menu options
    void setItems(const QStringList &items)
    {
        m_items = items;
    }
    //create editor
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,
                          const QModelIndex&index)const override
    {
        Q_UNUSED(option);
        Q_UNUSED(index);

        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_items);
        return editor;
    }

    //set Model data
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index,value,Qt::EditRole);
    }

private:
    QStringList m_items;    //Store the options for the dropdown menu

};


class DateEditDelegate : public QStyledItemDelegate
{
public:
    explicit DateEditDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        QDateEdit *editor = new QDateEdit(parent);
        editor->setDisplayFormat("yyyy-MM-dd");
        editor->setCalendarPopup(true);
        return editor;
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
        if(dateEdit)
        {
            model->setData(index,dateEdit->date().toString("yyyy-MM-dd"),Qt::EditRole);
        }
    }

};

class ImageDelegate : public QStyledItemDelegate {
public:
    explicit ImageDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    // Create an editor widget (a QLabel in this case) for the item
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override {
        Q_UNUSED(option);
        Q_UNUSED(index);
        QLabel* editor = new QLabel(parent);
        return editor;
    }

    // Save the image data from the editor back to the model
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override {
        QLabel* label = qobject_cast<QLabel*>(editor);
        if (label) {
            QByteArray imageData;
            QPixmap pixmap = label->pixmap(); // Get the QPixmap object directly
            if (!pixmap.isNull()) {
                QBuffer buffer(&imageData);
                buffer.open(QIODevice::WriteOnly);
                pixmap.save(&buffer, "PNG"); // Save the image as PNG format binary data
            }
            model->setData(index, imageData, Qt::UserRole); // Save binary data to the model
        }
    }

    // Paint the image in the item view
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override {
        // Get binary image data from the model
        QByteArray imageData = index.data(Qt::UserRole).toByteArray();
        if (imageData.isEmpty()) {
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }

        // Convert binary data to QPixmap
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        if (pixmap.isNull()) {
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }

        // Draw the image
        QRect rect = option.rect;
        QPixmap scaledPixmap = pixmap.scaled(rect.size(), Qt::KeepAspectRatio); // Scale the image
        painter->drawPixmap(rect, scaledPixmap);
    }

    // Handle editor events (double click to change image)
    bool editorEvent(QEvent* event, QAbstractItemModel* model,
                     const QStyleOptionViewItem& option, const QModelIndex& index) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                // Open file dialog to select a new image
                QString imagePath = QFileDialog::getOpenFileName(
                    nullptr, "Select Image", "", "Image Files (*.png *.jpg *.bmp)"
                    );

                if (!imagePath.isEmpty()) { // If user selected a valid image path
                    // Load the image file as binary data
                    QFile file(imagePath);
                    if (file.open(QIODevice::ReadOnly)) {
                        QByteArray imageData = file.readAll();
                        file.close();
                        model->setData(index, imageData, Qt::UserRole); // Save binary data to model
                    }
                }
                // If user cancels selection, keep the original image
                return true; // Event handled
            }
        }

        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
};
#endif // TABLEDELEGATES_H
