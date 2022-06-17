#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include "equipment.h"

/**
 * @brief Класс модели TableModel
 *
 * Класс наследуется от QAbstractTableModel. В нем описывается работа с данными
 * в модели.
 */

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса TableModel
     * @param parent Указатель на родителя объекта
     */
    explicit TableModel(QObject *parent = nullptr);

    /**
     * @brief метод updateCostByTypesPlus
     * вызывается при обновлении стоимости оборудования в большую сторону или
     * добавлении стоимости к новому оборудованию. Добавляет стоимость к
     * суммарной по типу (у каждого типа оборудования своя суммарная стоимость)
     * @param elem Объект класса Equipment, у которого была изменена стоимость
     */
    void updateCostByTypesPlus(const Equipment &elem);

    /**
     * @brief метод updateCostByTypesMinus
     * вызывается при обновлении стоимости оборудования в меньшую сторону или при
     * удалении оборудования из списка. Вычитает стоимость от суммарной по типу
     * (у каждого типа оборудлвания своя суммарная стоимость)
     * @param elem Объект класса Equipment, у которого была изменена стоимость
     */
    void updateCostByTypesMinus(const Equipment &elem);

    /**
     * @brief метод searchFreeId
     * ищет свободное значение в списке ID элементов оборудования (
     * @return свободный идентификатор
     */
    unsigned int searchFreeId();

    /**
     * @brief метод addUniqueId
     * добавляет уникальный идентификатор в список занятых уникальных
     * идентификаторов
     * @param iId Идентификатор, который записывается в уникальные
     */
    void addUniqueId(const unsigned int &iId);

    /**
     * @brief метод removeUniqueId
     * удаляет уникальный ID из списка ID при удалении строки с оборудованием из
     * списка listOfEquipment
     * @param idToRemove ID, который требуется удалить из списка уникальных
     */
    void removeUniqueId(const unsigned int &idToRemove);

    /**
     * @brief метод setValueInListOfEquipment
     * помещает объект класса Equipment (оборудование) в список оборудования
     * listOfEquipment. Из этого метода вызываются методы обновления суммарной
     * стоимости типа оборудования и добавление уникального ID
     * @param elem Объект класса Equipment, который добавляется в список оборудования
     * listOfEquipment
     */
    void setValueInListOfEquipment(const Equipment &elem);

    /**
     * @brief метод setIsModelChanged
     * - сеттер, устанавливает значение булевой переменной в значение true, что означает,
     * что в модели model были произведены изменения. Булевая переменная нужна
     * для предложения сохранить изменения при закрытии программы
     * @param isChanged булевая переменная,присваиваемая isModelChanged
     */
    void setIsModelChanged(bool isChanged);

    /**
     * @brief метод getListOfEquipment
     * - геттер, возвращает ссылку на список оборудования
     * @return ссылку на список электрооборудования (контейнер QList)
     */
    QList<Equipment>& getListOfEquipment();


    /**
     * @brief метод getIsModelChanged
     * - геттер, берет значение булевой переменной isModelChanged. true означает,
     * что в данных после загрузки в приложение есть изменения
     * @return булевую переменную isModelChanged
     */
    bool getIsModelChanged();

    /**
     * @brief метод getCostByTypes
     * - геттер, возвращает ссылку на карту QMap getCosOfTypes, отвечающую за
     * суммарную стоимость оборудования по их типу
     * @return ссылку на карту суммарной стоимости оборудования по типу
     */
    QMap<QString, double>& getCostByTypes();

    // QAbstractItemModel interface
public:
    /**
     * @brief метод rowCount
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), считает количество строк, которые находятся в
     * модели (равно количеству записей в списке электрооборудования)
     * @param parent Ссылка на родителя
     * @return количество строк в модели
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief метод columnCount
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), считает количество столбцов в модели (равно количеству
     * характеристик электрооборудования)
     * @param parent Ссылка на родителя
     * @return количество столбцов в модели
     */
    int columnCount(const QModelIndex &parent) const override;

    /**
     * @brief метод data
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), позволяет получить данные из конкретной ячейки модели
     * @param index Ссылка на индекс модели (включает номер строки и номер столбца)
     * @param role Роль при обращении к методу - считывание/редактирование
     * @return значение в конкретной ячейке модели типа QVariant
     */
    QVariant data(const QModelIndex &index, \
                   int role) const override;

    /**
     * @brief метод setData
     * является переопределенным, сеттер, устанавливает значение аргумента в
     * конкретную ячейку модели
     * @param index Ссылка на индекс модели (включает номер строки и номер столбца)
     * @param value Ссылка на значение, которое устанавливается в ячейку модели
     * @param role Роль при обращении к методу - считывание/редактирование
     * @return булевую переменную,true - установка удачна, false - неудачна
     */
    bool setData(const QModelIndex &index, \
                  const QVariant &value, \
                  int role) override;

    /**
     * @brief метод headerData
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), предоставляет информацию о названиях столбцов и строк
     * модели. Названия столбцов - предустановленные значения, названия строк -
     * порядковый номер
     * @param section Номер секции (если ориентация горизонтальная, то столбца,
     * если вертикальная, то строки)
     * @param orientation Ориентация, относительно чего будет производиться
     * нумерация
     * @param role Роль при обращении к методу - считывание/редактирование
     * @return название секции (строки/столбца) типа QVariant
     */
    QVariant headerData(int section, \
                         Qt::Orientation orientation, \
                         int role) const override;

    /**
     * @brief метод flags
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), позволяет получить флаги (разрешение на действия), которые
     * можно использовать для передаваемого в метод индекса. Возвращаются разные
     * флаги в зависимости от валидности индекса
     * @param index Ссылка на индекс модели (включает номер строки и номер столбца)
     * @return флаги, действия, разрешающиеся для данного индекса
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief метод removeRows
     * является переопределенным методом, удаляет из модели количество строк, указываемое
     * при вызове метода
     * @param row Номер строки, первой для удаления
     * @param count Количество строк, которые необходимо удалить
     * @param parent Ссылка на индекс родителя
     * @return булевое значение, true - удаление удачно, false - неудачно
     */
    bool removeRows(int row, int count, \
                     const QModelIndex &parent) override;

    /**
     * @brief метод insertRows
     * является переопределенным методом, производит вставку строк в модель,
     * количество определяется аргументом, передаваемом при вызове метода
     * @param row Номер строки, первый для вставки
     * @param count Количество строк, которое необходимо вставить
     * @param parent Ссылка на индекс родителя
     * @return булевое значение, true - вставка удачна, false - неудачна
     */
    bool insertRows(int row, int count, \
                     const QModelIndex &parent) override;

    /**
     * @brief метод mimeData
     * является переопределенным и константным (не может изменять параметры
     * внутри метода), вызывается при взятии данных для перетаскивания.
     * Обрабатывает взяты данные согласно типу MIME (медиа тип, каждый описывает
     * формат данных. Данные каждого из них можно передавать в разные среды,
     * например, в аналогичное приложение Qt или блокнот (в данной программе
     * используется 2 MIME типа))
     * @param indexes Ссылка на список индексов, передаваемых для копирования
     * @return ссылку на объект класса QMimeData для дальнейшего копирования
     * в определенную область (drop реализуется в методе dropMimeData)
     */
    QMimeData *mimeData(const QModelIndexList &indexes) const override;

    /**
     * @brief метод dropMimeData
     * является переопределенным, реализуется drop технологии drag and drop.
     * При реаоизации идет обращение к методу setData модели для вставки в
     * область приложения Qt и setItemData для копирования в область,
     * поддерживающую MIME тип "text/plain"
     * @param data Указатель на объект класса QMimeData
     * @param action Флаг, указывающий целевое действие при вызове метода
     * @param row Номер строки
     * @param column Номер столбца
     * @param parent Ссылка на индекс родителя
     * @return булевое значение, true - drop удачен, false - неудачен
     */
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

signals:
    /**
     * @brief сигнал signalIdError
     * испускается в случае попытки записи ID, который уже занят в модели
     * (все ID должны быть уникальными)
     * @param id ID, который пытались внести повторно
     */
    void signalIdError(const unsigned int &id);

private:
    QList<Equipment> listOfEquipment; // список оборудования
    QVector<unsigned int> uniqueIds; // уникальные значения Id
    QMap<QString, double> costByTypes; // суммарная стоимость по типам
    QString firstMimeType = "text/plain";
    QString secondMimeType = "application/x-qabstractitemmodeldatalist";
    QString columnDelimiter = ";";
    QString rowDelimiter = "\n";
    QString quotes = "\"";
    bool isModelChanged = false; // проверка, изменялись ли данные после открытия
    bool isIdExist(const unsigned int &id);
};

#endif // TABLEMODEL_H
