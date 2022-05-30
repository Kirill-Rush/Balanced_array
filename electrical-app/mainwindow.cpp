#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaboutprogramm.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <string>
#include <iostream>
#include <QDebug>
#include <QSettings>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new TableModel(this))
    , proxymodel(new QSortFilterProxyModel(this))
    , comboBoxDelegate(new ComboBoxDelegate(this))
{
    ui->setupUi(this);
    readSettings();

    // ниже включение ProxyModel, который сортирует значения в отображаемом tableview (в модели model ничего не меняется)
    proxymodel->setSourceModel(model); // "ресурсная" модель - наша
    ui->tableViewElectric->setModel(proxymodel); // отображаться в tableview будет прокси модель

    // устанавливаем контекстное меню
    ui->tableViewElectric->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableViewElectric, &QWidget::customContextMenuRequested, this, &MainWindow::menuRequested);

    // устанвка размеров столбцов таблицы
    const int MAX_COL_ID = 7;
    for(int i = 0; i < MAX_COL_ID; i++)
        switch(i)
        {
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            ui->tableViewElectric->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Interactive);
            break;
        default:
            ui->tableViewElectric->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    ui->tableViewElectric->horizontalHeader()->resizeSection(0, 30);
    ui->tableViewElectric->horizontalHeader()->resizeSection(5, 100);
    ui->tableViewElectric->horizontalHeader()->resizeSection(6, 100);

    connect(ui->actionAboutProgramm, &QAction::triggered, this, &MainWindow::openAboutProgramDialog);
    connect(ui->actionClose_all, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    connect(ui->actionEdit_row, &QAction::triggered, this, &MainWindow::editElement);     // вызов диалога редактирования
    connect(ui->actionAdd_row, &QAction::triggered, this, &MainWindow::addElement);     // вызов диалога добавления строки
    connect(ui->actionDelete_row, &QAction::triggered, this, &MainWindow::deleteElement);     // вызова диалога удаления строки

    // добавляем делегат для 3 столбца
    ui->tableViewElectric->setItemDelegateForColumn(2, comboBoxDelegate);
    // добавление вариантов в comboBoxDelegate
    comboBoxDelegate->setData({"Загрузчик сырья",\
                              "Сепаратор",\
                              "Шнековый экструдер",\
                              "Линия грануляции",\
                              "Фильтр расплава",\
                              "Шредер",\
                              "Ленточный транспортер",\
                              "Полуавтомат выдува ПЭТ",});

    ui->labelFilter->setText(tr("Search for: "));
    ui->comboBoxFilter->addItems({tr("- Not selected -"),\
                                  tr("Id"),\
                                  tr("Name"),\
                                  tr("Type"),\
                                  tr("Perfomance"),\
                                  tr("Power"),\
                                  tr("Date of buying"),\
                                  tr("Date of use"),\
                                  tr("Cost (rub.)")});
}

MainWindow::~MainWindow()
{
    writeSettings();

    delete comboBoxDelegate;
    delete proxymodel;
    delete model;
    delete ui;
}

void MainWindow::openAboutProgramDialog()
{
    DialogAboutProgramm dialog;
    dialog.exec();
}

void MainWindow::saveFile(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Error with saving file %1: %2")
                                                    .arg(fileName)
                                                    .arg(file.errorString()));
    }
    QTextStream streamOut(&file);
    QList<Equipment> &elementOfEquipment = model->getListOfEquipment();
    for(Equipment i: elementOfEquipment)
    {
        streamOut << QString::number(i.getId()) + ";" +\
                              i.getNameOfEquipment() + ";" +\
                              i.getTypeOfEquipment() + ";" +\
                              i.getPerfomance() + ";" +\
                              i.getPower() + ";" +\
                              i.getDateOfBuy() + ";" +\
                              i.getDateOfUse() + ";" +\
                              QString::number(i.getCost()) + "\n";
    }
    file.close();
}

void MainWindow::loadFile(QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Error with opening file %1: %2")
                                                    .arg(fileName)
                                                    .arg(file.errorString()));
        return;
    }
    QTextStream streamIn(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString stringOfEquipment;
    while(streamIn.readLineInto(&stringOfEquipment))
    {
        QStringList elementOfEquipment = stringOfEquipment.split(';');
        Equipment elem(elementOfEquipment[0].toUInt(),\
                elementOfEquipment[1], \
                elementOfEquipment[2], \
                elementOfEquipment[3].toFloat(), \
                elementOfEquipment[4].toFloat(), \
                elementOfEquipment[5], \
                elementOfEquipment[6], \
                elementOfEquipment[7].toUInt());
        model->setValueInListOfEquipment(elem); // занесение в список оборудования нового элемента
    }
    emit(model->layoutChanged());
    ui->tableViewElectric->resizeRowsToContents();
    QApplication::restoreOverrideCursor();

    this->currentFileName = fileName;
    file.close();
}

// редактирование элемента через контекстное меню
void MainWindow::editElement()
{
    int row = ui->tableViewElectric->selectionModel()->currentIndex().row();
    int column = ui->tableViewElectric->selectionModel()->currentIndex().column();
    QModelIndex modelIndex = proxymodel->index(row, column);
    ui->tableViewElectric->QAbstractItemView::edit(modelIndex); // редактирование конкретной ячейки
}

void MainWindow::deleteElement()
{
    // нахождение номера выбранной строки
    int row = ui->tableViewElectric->selectionModel()->currentIndex().row();
    int column = ui->tableViewElectric->selectionModel()->currentIndex().column();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::warning(this, \
                                              tr("Deleting the element"),\
                                              tr("Delete this element?"),\
                                              QMessageBox::Yes | QMessageBox::No);
        if(result == QMessageBox::No)
            return;
        else
        {
            QModelIndex modelIndex = proxymodel->index(row, column);
            proxymodel->removeRows(row, 1, modelIndex);
            emit(proxymodel->layoutChanged());

        }
    }
    else
        QMessageBox::warning(this, tr("Deleting the element"), \
                                   tr("Rows not selected"), \
                                   QMessageBox::Ok);
}

void MainWindow::addElement()
{
/*    QModelIndex modelIndex = proxymodel->index(0, 0);
    //int lastRow = proxymodel->rowCount(modelIndex);
    int lastRow = proxymodel->rowCount();
    proxymodel->insertRow(lastRow);
    ui->tableViewElectric->selectRow(lastRow);
    ui->tableViewElectric->setFocus();
    proxymodel->setData(model->index(lastRow, 0), "");
    proxymodel->submit();
    //model->submit();
    emit(proxymodel->layoutChanged());
    qDebug() << "All is good!";

    QString  asd = "hello";
    Equipment newel(200, "hello", 0, 120, 2, "2132131", "21231", 1231);
    model->setValueInListOfEquipment(newel);
    emit(model->layoutChanged());
    */
    int lastRow = proxymodel->rowCount();
    QModelIndex modelIndex = proxymodel->index(lastRow, 0);
    proxymodel->insertRows(lastRow, 1, modelIndex);
    emit(proxymodel->layoutChanged());
    ui->tableViewElectric->selectRow(lastRow);
}

void MainWindow::menuRequested(QPoint pos)
{
    // создание объекта меню
    QMenu *menu = new QMenu(this);
    // действия для контекстного меню
    QAction *editRecord = new QAction(tr("Edit"), this);
    QAction *deleteRecord = new QAction(tr("Delete Row"), this);
    QAction *addRecord = new QAction(tr("Add Row"));
    // подключение слотов и сигналов редактирования и удаления
    connect(editRecord, &QAction::triggered, this, &MainWindow::editElement);     // Обработчик вызова диалога редактирования
    connect(addRecord, &QAction::triggered, this, &MainWindow::addElement);       // Обработчик добавления записи
    connect(deleteRecord, &QAction::triggered, this, &MainWindow::deleteElement); // Обработчик удаления записи
    // добавление действий в контекстное меню
    menu->addAction(editRecord);
    menu->addAction(addRecord);
    menu->addAction(deleteRecord);
    // вызов контекстного меню
    menu->popup(ui->tableViewElectric->viewport()->mapToGlobal(pos));
}

void MainWindow::readSettings()
{
    QSettings settings("Glebov", "pr-electrical");
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(650, 440)).toSize());
    // определение координат х, у, чтобы по умолчанию окно находилось в центре экрана
    int x = (QApplication::desktop()->width() - window()->width())/2;
    int y = (QApplication::desktop()->height() - window()->height())/2;
    move(settings.value("pos", QPoint(x, y)).toPoint());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings("Glebov", "pr-electrical");
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

QString MainWindow::getCurrentFileName() const
{
    if(!this->currentFileName.isEmpty())
        return currentFileName;
    else
        return "";

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), \
                                                    QDir::currentPath(),\
                                                    tr("Text files (*.txt *.bat)"), \
                                                    nullptr,\
                                                    QFileDialog::DontUseNativeDialog);
    if(!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = getCurrentFileName();
    if(fileName.isEmpty())
    {
        on_actionSave_as_triggered();
        return;
    }
    saveFile(fileName);
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if(!fileName.isEmpty())
        saveFile(fileName);
}


void MainWindow::on_actionNew_triggered()
{
    MainWindow *newWindow = new MainWindow;

    newWindow->show();
}


void MainWindow::on_lineSearch_textChanged(const QString &arg1)
{
    int columnId;
    switch(ui->comboBoxFilter->currentIndex())
    {
    case 0: columnId = 0; return;
    case 1: columnId = 0; break;
    case 2: columnId = 1; break;
    case 3: columnId = 2; break;
    case 4: columnId = 3; break;
    case 5: columnId = 4; break;
    case 6: columnId = 5; break;
    case 7: columnId = 6; break;
    case 8: columnId = 7; break;
    }

    proxymodel->setFilterKeyColumn(columnId);
    QRegularExpression regularExp;
    regularExp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    regularExp.setPattern("^.*" + arg1 + ".*$");
    proxymodel->setFilterRegularExpression(regularExp);

    // чтобы строки не уменьшались до минимума после фильтра
    ui->tableViewElectric->resizeRowsToContents();
}
