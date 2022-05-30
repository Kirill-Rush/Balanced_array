#include "equipment.h"
#include <iostream>

Equipment::Equipment():
    id(),
    nameOfEquipment(),
    typeOfEquipment(),
    perfomance(),
    power(),
    dateOfBuy(),
    dateOfUse(),
    cost()
{}

Equipment::Equipment(unsigned int iId, QString iNameOfEquipment, QString iTypeOfEquipment,\
                     float iPerfomance, float iPower, QString iDateOfBuy, QString iDateOfUse,\
                     unsigned int iCost):
    id(iId),
    nameOfEquipment(iNameOfEquipment),
    perfomance(iPerfomance),
    power(iPower),
    dateOfBuy(iDateOfBuy),
    dateOfUse(iDateOfUse),
    cost(iCost)
{
    if(iTypeOfEquipment == "Загрузчик сырья")
        typeOfEquipment = LOADER;
    else if(iTypeOfEquipment == "Сепаратор")
        typeOfEquipment = SEPARATOR;
    else if(iTypeOfEquipment == "Шнековый экструдер")
        typeOfEquipment = SQREW_EXTRUDER;
    else if(iTypeOfEquipment == "Линия грануляции")
        typeOfEquipment = LINE_OF_GRANULATION;
    else if(iTypeOfEquipment == "Фильтр расплава")
        typeOfEquipment = MELT_FILTER;
    else if(iTypeOfEquipment == "Шредер")
        typeOfEquipment = SHREDER;
    else if(iTypeOfEquipment == "Ленточный транспортер")
        typeOfEquipment = TRASNPORTER;
    else if(iTypeOfEquipment == "Полуавтомат выдува ПЭТ")
        typeOfEquipment = SEMIAUTOMATIC_BLOWER;
    else
        typeOfEquipment = NONE;
}

Equipment::~Equipment()
{}

void Equipment::setId(const unsigned int iId)
{
    id = iId;
}

void Equipment::setNameOfEquipment(const QString iNameOfEquipment)
{
    nameOfEquipment = iNameOfEquipment;
}

void Equipment::setTypeOfEquipment(const QString iTypeOfEquipment)
{
    if(iTypeOfEquipment == "Загрузчик сырья")
        typeOfEquipment = LOADER;
    else if(iTypeOfEquipment == "Сепаратор")
        typeOfEquipment = SEPARATOR;
    else if(iTypeOfEquipment == "Шнековый экструдер")
        typeOfEquipment = SQREW_EXTRUDER;
    else if(iTypeOfEquipment == "Линия грануляции")
        typeOfEquipment = LINE_OF_GRANULATION;
    else if(iTypeOfEquipment == "Фильтр расплава")
        typeOfEquipment = MELT_FILTER;
    else if(iTypeOfEquipment == "Шредер")
        typeOfEquipment = SHREDER;
    else if(iTypeOfEquipment == "Ленточный транспортер")
        typeOfEquipment = TRASNPORTER;
    else if(iTypeOfEquipment == "Полуавтомат выдува ПЭТ")
        typeOfEquipment = SEMIAUTOMATIC_BLOWER;
    else
        typeOfEquipment = NONE;
}

void Equipment::setPerfomance(const float iPerfomance)
{
    perfomance = iPerfomance;
}

void Equipment::setPower(const float iPower)
{
    power = iPower;
}

void Equipment::setDateOfBuy(const QString iDateOfBuy)
{
    dateOfBuy = iDateOfBuy;
}

void Equipment::setDateOfUse(const QString iDateOfUse)
{
    dateOfUse = iDateOfUse;
}

void Equipment::setCost(const unsigned int iCost)
{
    cost = iCost;
}

unsigned int Equipment::getId() const
{
    return id;
}

QString Equipment::getNameOfEquipment() const
{
    return nameOfEquipment;
}

QString Equipment::getTypeOfEquipment() const
{
    switch(typeOfEquipment)
    {
    case 0:
        return "-";
        break;
    case 1:
        return "Загрузчик сырья";
        break;
    case 2:
        return "Сепаратор";
        break;
    case 3:
        return "Шнековый экструдер";
        break;
    case 4:
        return "Линия грануляции";
        break;
    case 5:
        return "Фильтр расплава";
        break;
    case 6:
        return "Шредер";
        break;
    case 7:
        return "Ленточный транспортер";
        break;
    case 8:
        return "Полуавтомат выдува ПЭТ";
        break;
    }
}

QString Equipment::getPerfomance() const
{
    return QString::number(perfomance);
}

QString Equipment::getPower() const
{
    return QString::number(power);
}

QString Equipment::getDateOfBuy() const
{
    return dateOfBuy;
}

QString Equipment::getDateOfUse() const
{
    return dateOfUse;
}

unsigned int Equipment::getCost() const
{
    return cost;
}

