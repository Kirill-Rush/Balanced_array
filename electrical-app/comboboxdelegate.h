#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    QStringList listOfVariants;

public:
    explicit ComboBoxDelegate(QWidget *parent = nullptr);

    // создание виджета редактора
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    // передача значений в редактор
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    // передача данных в таблицу
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    // определение расположения виджета
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    // поведение ячейки как реакция на возникающие события
    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    // передача вариантов в listOfVariants
    void setData(const QStringList &iListOfVariants);
};

#endif // COMBOBOXDELEGATE_H
