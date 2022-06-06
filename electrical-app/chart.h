#ifndef CHART_H
#define CHART_H

#include <QMainWindow>
#include  <QtCharts>

namespace Ui {
class Chart;
}

class Chart : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString, double> costByTypes;
    double maxCost;

public:
    explicit Chart(QMainWindow *parent, QMap<QString, double> &iCostByTypes);
    ~Chart();

    // ищет наибольшее значение и возвращает немного бОльшее значение для
    // красивого отображения шкалы по Y
    double findMaxCost();

private:
    Ui::Chart *ui;
};

#endif // CHART_H
