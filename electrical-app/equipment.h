#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>

class Equipment
{
private:
    unsigned int id;
    QString nameOfEquipment;
    enum enumTypeOfEquipment
    {
        NONE, // отсутствует
        LOADER, // загрузчик сырья
        SEPARATOR, // сепаратор
        SQREW_EXTRUDER, // шнековый экструдер
        LINE_OF_GRANULATION, // линия грануляции
        MELT_FILTER, // фильтр расплава
        SHREDER, // шредер
        TRASNPORTER, // ленточный транспортер
        SEMIAUTOMATIC_BLOWER // полуавтомат выдува
    } typeOfEquipment;
    float perfomance; // производительность
    float power; // мощность
    QString dateOfBuy; // дата покупки
    QString dateOfUse; // дата начала эксплуатации
    unsigned int cost; // стоимость
public:
    Equipment();
    Equipment(unsigned int iId, QString iNameOfEquipment, QString iTypeOfEquipment,\
              float iPerfomance, float iPower, QString iDateOfBuy, QString iDateOfUse,\
              unsigned int iCost);
    ~Equipment();
    void setId(const unsigned int iId);
    void setNameOfEquipment(const QString iNameOfEquipment);
    void setTypeOfEquipment(const QString iTypeOfEquipment);
    void setPerfomance(const float iPerfomance);
    void setPower(const float iPower);
    void setDateOfBuy(const QString iDateOfBuy);
    void setDateOfUse(const QString iDateOfUse);
    void setCost(const unsigned int iCost);

    unsigned int getId() const;
    QString getNameOfEquipment() const;
    QString getTypeOfEquipment() const;
    QString getPerfomance() const;
    QString getPower() const;
    QString getDateOfBuy() const;
    QString getDateOfUse() const;
    unsigned int getCost() const;
};

#endif // EQUIPMENT_H
