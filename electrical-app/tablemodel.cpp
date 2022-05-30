#include "tablemodel.h"
#include <QBrush>
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfEquipment.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 8;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row(); // показывает, на какой строчке сейчас находимся
    int column = index.column(); // показывает, в каком столбце сейчас находимся

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch(column)
        {
        case 0:
            return QVariant(listOfEquipment.at(row).getId());
        case 1:
            return QVariant(listOfEquipment.at(row).getNameOfEquipment());
        case 2:
            return QVariant(listOfEquipment.at(row).getTypeOfEquipment());
        case 3:
            return QVariant(listOfEquipment.at(row).getPerfomance());
        case 4:
            return QVariant(listOfEquipment.at(row).getPower());
        case 5:
            return QVariant(listOfEquipment.at(row).getDateOfBuy());
        case 6:
            return QVariant(listOfEquipment.at(row).getDateOfUse());
        case 7:
            return QVariant(listOfEquipment.at(row).getCost());
        }
        break;
    case Qt::BackgroundRole:
        if(column == 0)
            if(listOfEquipment[row].getNameOfEquipment() == "Item 2")
                return QBrush(Qt::red);
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    int column = index.column();
    int row = index.row();

    if(role == Qt::EditRole)
    {
        switch(column)
        {
        case 0:
            listOfEquipment[row].setId(value.toUInt());
            break;
        case 1:
            listOfEquipment[row].setNameOfEquipment(value.toString());
            break;
        case 2:
            listOfEquipment[row].setTypeOfEquipment(value.toString());
            break;
        case 3:
            listOfEquipment[row].setPerfomance(value.toFloat());
            break;
        case 4:
            listOfEquipment[row].setPower(value.toFloat());
            break;
        case 5:
            listOfEquipment[row].setDateOfBuy(value.toString());
            break;
        case 6:
            listOfEquipment[row].setDateOfUse(value.toString());
            break;
        case 7:
            listOfEquipment[row].setCost(value.toUInt());
            break;
        }
        return true;
    }

//        if(column == 0)
//        {
//            listStrings.replace(index.row(), value.toString());
//            return true;
//        }

    return false;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0: return QString(tr("Id"));
        case 1: return QString(tr("Name"));
        case 2: return QString(tr("Type"));
        case 3: return QString(tr("Perfomance"));
        case 4: return QString(tr("Power"));
        case 5: return QString(tr("Date of buying"));
        case 6: return QString(tr("Date of use"));
        case 7: return QString(tr("Cost (rub.)"));
        }
    }

    if(orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString::number(section + 1);

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled;
    else
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled;
}

void TableModel::setValueInListOfEquipment(const Equipment &elem)
{
    listOfEquipment.append(elem);
}

//void TableModel::deleteElementFromList(const int &index)
//{
//    auto iter = listOfEquipment.begin();
//    for(int i = 0; iter != listOfEquipment.end() && i < index; iter++, i++);
//    listOfEquipment.erase(iter);
//}

QList<Equipment>& TableModel::getListOfEquipment()
{
    return listOfEquipment;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    emit(beginRemoveRows(QModelIndex(), row, row+count-1));
    for (int i=0; i < count; i++)
        listOfEquipment.removeAt(row);
    emit(endRemoveRows());
    return true;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count);
    beginInsertRows(parent, row, row);
    Equipment newElement;
    listOfEquipment.append(newElement);
    emit(endInsertRows());
    return true;
}

QStringList TableModel::mimeTypes() const
{
    QStringList types;
    types << "application/x-qabstractitemmodeldatalist";
    return types;
}

QMimeData *TableModel::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "mimeData FUNCTION";
    if(indexes.isEmpty())
        return nullptr;
    if(!indexes.at(0).isValid())
        return nullptr;

    QStringList types = mimeTypes();
    if (types.isEmpty())
        return nullptr;

    if(currentMimeType == "application/x-qabstractitemmodeldatalist")
    {
        qDebug() << "mimeData FUNCTION";
        return QAbstractItemModel::mimeData(indexes);
    }

    return nullptr;
}

bool TableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData FUNCTION";
    if(data == nullptr)
        return false;
    qDebug() << "dropMimeData FUNCTION";
    return QAbstractItemModel::dropMimeData(data, action, row, column, parent);
    //return QTableWidget::dropMimeData(row, column, data, action);
}

Qt::DropActions TableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
