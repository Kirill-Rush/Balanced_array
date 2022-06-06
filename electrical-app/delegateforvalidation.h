#ifndef DELEGATEFORVALIDATION_H
#define DELEGATEFORVALIDATION_H

#include <QStyledItemDelegate>

class DelegateForValidation : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DelegateForValidation(QWidget *parent = nullptr);

signals:


    // QAbstractItemDelegate interface
public:
    // метод, устанавливающий валидаторы для каждого из столбцов
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATEFORVALIDATION_H
