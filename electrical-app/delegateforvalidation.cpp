#include "delegateforvalidation.h"
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>

DelegateForValidation::DelegateForValidation(QWidget *parent):
    QStyledItemDelegate(parent)
{}

// установка валидаторов для столбцов
QWidget *DelegateForValidation::createEditor(QWidget *parent, \
                                             const QStyleOptionViewItem &option, \
                                             const QModelIndex &index) const
{
    Q_UNUSED(option)
    QLineEdit *lineEdit = new QLineEdit(parent);
    QRegularExpression expr;
    switch(index.column())
    {
    case 0: expr.setPattern("^[1-9]+[0-9]*$"); break;
    case 3:
    case 4: expr.setPattern("^((0\\.)|([1-9]+[0-9]*\\.?))[0-9]?[0-9]?$"); break;
    case 5:
    case 6: expr.setPattern("^(0?[1-9]|[12][0-9]|3[01])[\\.](0?[1-9]|1[012])[\\.]\\d{4}$"); break;
    default: delete lineEdit; return QStyledItemDelegate::createEditor(parent,option,index);
    }
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(expr);

    lineEdit->setValidator(validator);
    return lineEdit;
}
