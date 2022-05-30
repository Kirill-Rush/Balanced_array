#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "equipment.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    QList<Equipment> listOfEquipment;
    QString currentMimeType = "application/x-qabstractitemmodeldatalist";
public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setValueInListOfEquipment(const Equipment &elem);
    //void deleteElementFromList(const int &index);
    QList<Equipment>& getListOfEquipment();
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;

    // QAbstractItemModel interface
public:
    // типы данных, в которых передается перетаскиваемая информация
    QStringList mimeTypes() const override;
    // отвечает за обработку перетаскиваемой информации
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    // отвечает за вставку информации в модель
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    // QAbstractItemModel interface
public:
    Qt::DropActions supportedDropActions() const override;

//    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);
};

#endif // TABLEMODEL_H
