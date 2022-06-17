#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>

/**
 * @brief Класс хранения характеристик единицы электрооборудования Equipment
 *
 * Содержит в себе поля-характеристики для электрооборудования, которое вносится
 * в список модели для отображения в tableview
 * Содержит характеристики:
 * - уникальный идентификатор;
 * - название оборудования;
 * - тип оборудования;
 * - производительность;
 * - мощность;
 * - дату приобретения;
 * - дату ввода в эксплуатацию;
 * - стоимость
 *
 * Тип оборудования использует перечисляемый тип enum ввиду ограниченного
 * количества наименований
 */

class Equipment
{
private:
    unsigned int id;
    QString nameOfEquipment;
    enum enumTypeOfEquipment
    {
        NONE,                // отсутствует
        LOADER,              // загрузчик сырья
        SEPARATOR,           // сепаратор
        SQREW_EXTRUDER,      // шнековый экструдер
        LINE_OF_GRANULATION, // линия грануляции
        MELT_FILTER,         // фильтр расплава
        SHREDER,             // шредер
        TRASNPORTER,         // ленточный транспортер
        SEMIAUTOMATIC_BLOWER // полуавтомат выдува
    } typeOfEquipment;
    float perfomance;  // производительность
    float power;       // мощность
    QString dateOfBuy; // дата покупки
    QString dateOfUse; // дата начала эксплуатации
    unsigned int cost; // стоимость

public:
    /**
     * @brief Конструтор класса Equipment по умолчанию
     */
    Equipment();

    /**
     * @brief Конструктор класса Equipment с аргументом ID
     * @param iId Инициализирует поле ID
     */
    Equipment(unsigned int iId);

    /**
     * @brief Конструктор класса Equipment с инициализацией полей класса
     * @param iId Инициализирует поле ID
     * @param iNameOfEquipment Инициализирует поле nameOfEquipment
     * @param iTypeOfEquipment Инициализирует поле typeOfEquipment
     * @param iPerfomance Инициализирует поле perfomance
     * @param iPower Инициализирует поле power
     * @param iDateOfBuy Инициализирует поле dateOfBuy
     * @param iDateOfUse Инициализирует поле dateOfUse
     * @param iCost Инициализирует поле cost
     */
    Equipment(unsigned int iId, \
              QString iNameOfEquipment, \
              QString iTypeOfEquipment,\
              float iPerfomance, \
              float iPower, \
              QString iDateOfBuy, \
              QString iDateOfUse,\
              unsigned int iCost);
    ~Equipment();

    /**
     * @brief метод setId
     * - сеттер, устанавливает значение ID
     * @param iId ID, устанавливающийся в поле объекта класса
     */
    void setId(const unsigned int iId);

    /**
     * @brief метод setNameOfEquipment
     * - сеттер, устанавливает название оборудования
     * @param iNameOfEquipment Значение, устанавливающееся как название оборудования
     */
    void setNameOfEquipment(const QString iNameOfEquipment);

    /**
     * @brief метод setTypeOfEquipment
     * - сеттер, устанавливает тип оборудования
     * @param iTypeOfEquipment Значение, устанавливающееся как тип оборудования
     */
    void setTypeOfEquipment(const QString iTypeOfEquipment);

    /**
     * @brief метод setPerfomance
     * -  сеттер, устанавливает производительность оборудования
     * @param iPerfomance Значение, устанавливающееся как производительность
     * оборудования
     */
    void setPerfomance(const float iPerfomance);

    /**
     * @brief метод setPower
     * - сеттер, устанавливает мощность оборудованиия
     * @param iPower Значение, устанавливающееся как мощность оборудования
     */
    void setPower(const float iPower);

    /**
     * @brief метод setDateOfBuy
     * - сеттер, устанавливает дату покупки оборудованиия
     * @param iDateOfBuy Значение, устанавливающееся как дата покупки
     * оборудования
     */
    void setDateOfBuy(const QString iDateOfBuy);

    /**
     * @brief метод setDateOfUse
     * - сеттер, устанавливает дату ввода в эксплуатацию оборудованиия
     * @param iDateOfUse Значение, устанавливающееся как дата ввода в
     * эксплуатацию оборудования
     */
    void setDateOfUse(const QString iDateOfUse);

    /**
     * @brief метод setCost
     * - сеттер, устанавливает стоимость оборудованиия
     * @param iCost Значение, устанавливающееся стоимость оборудования
     */
    void setCost(const unsigned int iCost);

    /**
     * @brief метод getId
     * - геттер, возвращает ID оборудования
     * @return ID оборудования
     */
    unsigned int getId() const;

    /**
     * @brief метод getNameOfEquipment
     * - геттер, возвращает название оборудования
     * @return название оборудования
     */
    QString getNameOfEquipment() const;

    /**
     * @brief метод getTypeOfEquipment
     * - геттер, возвращает тип оборудования
     * @return тип оборудования
     */
    QString getTypeOfEquipment() const;

    /**
     * @brief метод getPerfomance
     * - геттер, возвращает производительность оборудования
     * @return производительность оборудования
     */
    QString getPerfomance() const;

    /**
     * @brief метод getPower
     * - геттер, возвращает мощность оборудования
     * @return мощность оборудования
     */
    QString getPower() const;

    /**
     * @brief метод getDateOfBuy
     * - геттер, возвращает дату покупки оборудования
     * @return дату покупки оборудования
     */
    QString getDateOfBuy() const;

    /**
     * @brief метод getDateOfUse
     * - геттер, возвращает дату ввода в эксплуатацию оборудования
     * @return дату ввода в эксплуатацию оборудования
     */
    QString getDateOfUse() const;

    /**
     * @brief метод getCost
     * - геттер, возвращает стоимость оборудования
     * @return стоимость оборудования
     */
    unsigned int getCost() const;
};

#endif // EQUIPMENT_H
