#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include "equipment.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

signals:
    void signalIdError(const unsigned int &id);

private:
    QList<Equipment> listOfEquipment;
    QVector<unsigned int> uniqueIds; // уникальные значения Id
    QMap<QString, double> costByTypes;
    QString firstMimeType = "text/plain";
    QString secondMimeType = "application/x-qabstractitemmodeldatalist";
    QString columnDelimiter = ";";
    QString rowDelimiter = "\n";
    QString quotes = "\"";
    bool isModelChanged = false; // проверка, изменялись ли данные после открытия
    bool isIdExist(const unsigned int &id);
    void setCurrentMimeType(QMimeData *data);

public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, \
                   int role) const override;
    bool setData(const QModelIndex &index, \
                  const QVariant &value, \
                  int role) override;
    QVariant headerData(int section, \
                         Qt::Orientation orientation, \
                         int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool removeRows(int row, int count, \
                     const QModelIndex &parent) override;
    bool insertRows(int row, int count, \
                     const QModelIndex &parent) override;
    void updateCostByTypesPlus(const Equipment &elem); // если создавали/удаляли запись
    void updateCostByTypesMinus(const Equipment &elem); // если создавали/удаляли запись
    void updateCostByTypesPlus(const Equipment &elem, \
                                const double &diff); // если редактировали запись
    void updateCostByTypesMinus(const Equipment &elem, \
                                 const double &diff); // если редактировали запись
    unsigned int searchFreeId();
    void addUniqueId(const unsigned int &iId);
    void removeUniqueId(const unsigned int &idToRemove);

    void setValueInListOfEquipment(const Equipment &elem);
    void setIsModelChanged(bool isChanged);
    QList<Equipment>& getListOfEquipment();
    bool getIsModelChanged();
    QMap<QString, double>& getCostByTypes();


    // QAbstractItemModel interface
public:
    // типы данных, в которых передается перетаскиваемая информация
    QStringList mimeTypes() const override;
    // отвечает за обработку перетаскиваемой информации
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    // отвечает за вставку информации в модель
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
};

#endif // TABLEMODEL_H
