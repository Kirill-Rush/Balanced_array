#include "tablemodel.h"
#include <QBrush>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <mainwindow.h>

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

    setIsModelChanged(true);
    int column = index.column();
    int row = index.row(); 

    if(role == Qt::EditRole ||  role == Qt::DisplayRole)
    {
        switch(column)
        {
        case 0:
            if(role == Qt::DisplayRole) // для 1-го захода в метод при drag and drop
                break;

            if(isIdExist(value.toUInt()))
            {
                emit(signalIdError(value.toUInt()));
                return false;
            }
            removeUniqueId(data(index, Qt::DisplayRole).toUInt()); // удаление ID, который будет изменен
            listOfEquipment[row].setId(value.toUInt());
            addUniqueId(value.toUInt()); // вставка нового ID в вектор уникальных
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
            updateCostByTypesMinus(listOfEquipment[row]);
            listOfEquipment[row].setCost(value.toUInt());
            updateCostByTypesPlus(listOfEquipment[row]);
            break;
        }
        return true;
    }

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
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    emit(beginRemoveRows(QModelIndex(), row, row));
    for (int i=0; i < count; i++)
    {
        updateCostByTypesMinus(listOfEquipment.at(row + i));
        uniqueIds.remove(uniqueIds.indexOf(listOfEquipment.at(row + i).getId()));
        listOfEquipment.removeAt(row + i);
    }
    emit(endRemoveRows());
    isModelChanged = true;
    return true;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count);
    emit(beginInsertRows(parent, row, row));
    unsigned int id = searchFreeId();
    Equipment newElement(id);
    listOfEquipment.append(newElement);
    addUniqueId(id);
    emit(endInsertRows());
    isModelChanged = true;
    return true;
}

void TableModel::updateCostByTypesPlus(const Equipment &elem)
{
    costByTypes[elem.getTypeOfEquipment()] += elem.getCost();
}

void TableModel::updateCostByTypesMinus(const Equipment &elem)
{
    costByTypes[elem.getTypeOfEquipment()] -= elem.getCost();
}

bool TableModel::isIdExist(const unsigned int &id)
{
    QVector<unsigned int>::iterator it;
    for(it = uniqueIds.begin(); it != uniqueIds.end(); it++)
        if(*it == id)
            return true;

    return false;
}

unsigned int TableModel::searchFreeId()
{
    unsigned int sizeOfUniqueIds = uniqueIds.size();
    std::sort(uniqueIds.begin(), uniqueIds.end());
    for(unsigned int i = 0; i < sizeOfUniqueIds; i++)
        if(uniqueIds[i] != i + 1)
            return i + 1;

    if(sizeOfUniqueIds == 0)
        return 1;
    else
        return uniqueIds[sizeOfUniqueIds - 1] + 1;
}

void TableModel::addUniqueId(const unsigned int &iId)
{
    uniqueIds.append(iId);
}

void TableModel::removeUniqueId(const unsigned int &idToRemove)
{
    if(uniqueIds.contains(idToRemove))
        uniqueIds.remove(uniqueIds.indexOf(idToRemove));
}



void TableModel::setValueInListOfEquipment(const Equipment &elem)
{
    listOfEquipment.append(elem);
    updateCostByTypesPlus(elem);
    addUniqueId(elem.getId());
}

void TableModel::setIsModelChanged(bool isChanged)
{
    isModelChanged = isChanged;
}



QList<Equipment>& TableModel::getListOfEquipment()
{
    return listOfEquipment;
}

bool TableModel::getIsModelChanged()
{
    return isModelChanged;
}

QMap<QString, double>& TableModel::getCostByTypes()
{
    return costByTypes;
}



QMimeData *TableModel::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "mimeData FUNCTION";
    if(indexes.isEmpty())
        return nullptr;
    if(!indexes.at(0).isValid())
        return nullptr;

    if (firstMimeType == "text/plain" && secondMimeType == "application/x-qabstractitemmodeldatalist")
    {
        QString result;

        int topSelectionRange = indexes.at(0).row();
        int leftSelectionRange = indexes.at(0).column();
        int rowCountSelectionRange = 0;
        int columnCountSelectionRange = 0;
        for (int i = 0; i < indexes.count(); ++i) {
            // item отсутствует?
            if (!indexes.at(i).isValid())
                return nullptr;

            int c = indexes.at(i).column() - leftSelectionRange;
            int r = indexes.at(i).row() - topSelectionRange;

            if (c > 0 && (c < columnCountSelectionRange || indexes.at(i).row() == topSelectionRange))
                result += columnDelimiter;
            if (r > 0 && indexes.at(i).column() == leftSelectionRange)
                result += rowDelimiter;
            result += quotes +
                    indexes.at(i).data(Qt::DisplayRole).toString() +
                    quotes;

            if (indexes.at(i).row() == topSelectionRange)
                columnCountSelectionRange++;
            if (indexes.at(i).column() == leftSelectionRange)
                rowCountSelectionRange++;
        }

        result += rowDelimiter;
        qDebug() << result;

        // создаем mimeData, которая будет использоваться для drop
        QMimeData *mimeData = new QMimeData;
        // создаем mimeDataForLocal для записи типа и mimeData для внутренних переносов
        QMimeData *mimeDataForLocal = QAbstractTableModel::mimeData(indexes);
        // записываем типы с данными для drop в mimeData
        mimeData->setData(secondMimeType, mimeDataForLocal->data(secondMimeType));
        mimeData->setData(firstMimeType, result.toUtf8());
        return mimeData;
    }

    return nullptr;
}

bool TableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData FUNCTION";
    if(data == nullptr)
        return false;

    //QStringList mimeTypesFormats =  data->formats();

    QByteArray dataforsecond = data->data(secondMimeType);
    QMimeData *forsecond = new  QMimeData;
    forsecond->setData(secondMimeType, dataforsecond);
    forsecond->setText(dataforsecond);

    if(data->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        return QAbstractTableModel::dropMimeData(forsecond, action, row, column, parent);
    }

    if (data->hasFormat("text/plain"))
    {
        QStringList strings;
        strings = data->text().split(rowDelimiter);

        for (int rowSelected = 0; rowSelected < strings.count(); ++rowSelected)
        {
            if ((row + rowSelected) >= rowCount(parent))
                insertRow(rowCount(parent));
            QStringList tokens = strings[rowSelected].split(columnDelimiter);
            for (int columnSelected = 0; columnSelected < tokens.count(); columnSelected++)
            {
                QString token = tokens[columnSelected];
                token.remove(quotes);
                if (token.isEmpty())
                    continue;
                QAbstractItemModel *item = new TableModel;
                item->setData(parent, token, Qt::EditRole);
                QMap<int, QVariant> k;
                setItemData(item->data(parent, Qt::DisplayRole).toModelIndex(), k);
                delete item;
            }
        }
        return true;
    }

    return false;
}
