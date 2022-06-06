#include "chart.h"
#include "ui_chart.h"

using namespace QtCharts;

Chart::Chart(QMainWindow *parent, QMap<QString, double> &iCostByTypes) :
    QMainWindow(parent = nullptr),
    ui(new Ui::Chart)
{
    ui->setupUi(this);

    costByTypes = iCostByTypes;
    maxCost = findMaxCost();

    setWindowTitle(tr("Statistics"));

    QBarSet *loader = new QBarSet("Загрузчик сырья");
    QBarSet *separator = new QBarSet("Сепаратор");
    QBarSet *sqrewExtruder = new QBarSet("Шнековый экструдер");
    QBarSet *lineOfGranulation = new QBarSet("Линия грануляции");
    QBarSet *meltFilter = new QBarSet("Фильтр расплава");
    QBarSet *shreder = new QBarSet("Шредер");
    QBarSet *transporter = new QBarSet("Ленточный транспортер");
    QBarSet *semiautomaticBlower = new QBarSet("Полуавтомат выдува ПЭТ");

    *loader              << costByTypes["Загрузчик сырья"];
    *separator           << costByTypes["Сепаратор"];
    *sqrewExtruder       << costByTypes["Шнековый экструдер"];
    *lineOfGranulation   << costByTypes["Линия грануляции"];
    *meltFilter          << costByTypes["Фильтр расплава"];
    *shreder             << costByTypes["Шредер"];
    *transporter         << costByTypes["Ленточный транспортер"];
    *semiautomaticBlower << costByTypes["Полуавтомат выдува ПЭТ"];


    QBarSeries *series = new QBarSeries();
    series->append(loader);
    series->append(separator);
    series->append(sqrewExtruder);
    series->append(lineOfGranulation);
    series->append(meltFilter);
    series->append(shreder);
    series->append(transporter);
    series->append(semiautomaticBlower);

    QList<QBarSet *> sets = series->barSets();
    float currentHue = 0.0;
    int sizeOfSets = sets.size();
    for(int i = 0; i < sizeOfSets; ++i)
    {
        QColor col = QColor::fromHslF(currentHue, 0.7, 0.5);
        currentHue += 0.618033988749895f;
        currentHue = std::fmod(currentHue, 1.0f);
        sets[i]->setColor(col);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Summary cost of equipment by types"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << tr("Types of equipment");
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories); // описание Х
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxCost); // задание макс значения по Y
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
    resize(800, 400);

}

Chart::~Chart()
{
    delete ui;
}

double Chart::findMaxCost()
{
    QMap<QString, double>::iterator it;
    double max = 0;
    for(it = costByTypes.begin(); it != costByTypes.end(); it++)
        if(it.value() > max)
            max = it.value();
    max = round(max + 500000);
    return max;
}
