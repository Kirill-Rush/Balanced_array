#include "comboboxdelegate.h"
#include <QComboBox>
#include <QMouseEvent>
#include <QAbstractItemView>
#include <QDebug>
#include <QTableWidget>

ComboBoxDelegate::ComboBoxDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *comboBox = new QComboBox(parent);

    // добавляем варианты из listOfVariants в comboBox
    comboBox->addItems(listOfVariants);

    // задаём значение по умолчанию
    comboBox->setCurrentIndex(0);

    return comboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor); // приведение класса к QComboBox

    // установка начального элемента в comboBox
    comboBox->setCurrentText(index.data().toString());
}

void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor); // приведение класса к QComboBox

    // запись выбора пользователя в таблицу
    model->setData(index, comboBox->currentText());
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect); // установка расположения виджета
}

bool ComboBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    Q_UNUSED(model);
    // отпускание указателя мыши в ячейке
    if (event->type() == QEvent::MouseButtonRelease)
    {
        // проверка для реакции только на нажатие по левой кнопки мыши
        if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton)
        {
            // Привидение типа к QWidget для перехода к ui->tableView
            QWidget *widget = const_cast<QWidget *>(option.widget);
            // Для доступа к itemView как к QAbstractItemView
            QAbstractItemView* item = qobject_cast<QAbstractItemView *>(widget);

            // Проверяем удалось ли получить указатель на объект QAbstractItemView
            if (item != nullptr)
            {
                // устанавливаем начальный индекс в списке
                item->setCurrentIndex(index);
                // Вызываем edit для открытия списка
                item->edit(index);
            }
            return true;
        }
    }
    return false;
}

void ComboBoxDelegate::setData(const QStringList &iListOfVariants)
{
    // передача вариантов выбора в listOfVariants
    listOfVariants = iListOfVariants;
}
