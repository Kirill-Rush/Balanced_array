#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include  <QtCharts>

namespace Ui {
class Chart;
}

/**
 * @brief Класс окна с отображением графиков по данным Chart
 *
 * Окно с отобажением графика по данным модели. Производится графическое
 * отображение распределения затрат по типам оборудования
 */
class Chart : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString, double> costByTypes;
    double maxCost;

public:
    /**
     * @brief Конструктор класса Chart
     * Инициализирует поле costByTypes стоимости оборудования по типам
     * @param parent Указатель на родителя объекта
     * @param iCostByTypes Инициализирует поле costByTypes
     */
    explicit Chart(QMainWindow *parent, \
                   QMap<QString, double> &iCostByTypes);
    ~Chart();

    /**
     * @brief метод findMaxCost
     * Производит поиск максимальных затрат по типу оборудования и возвращает
     * значение + 500000 для удобного отображения графика по шкале Y
     * @return максимальное значение стоимости (с небольшим прибавлением)
     */
    double findMaxCost();

private:
    Ui::Chart *ui;
};

#endif // CHART_H
