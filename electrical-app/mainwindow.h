/**
 * \file Заголовочный файл с описанием класса MainWindow
 * \author Глебов К.И., ИЦТМС-2-7, МГСУ
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSortFilterProxyModel>
#include <QCloseEvent>
#include <QTranslator>
#include "dialogaboutprogramm.h"
#include "equipment.h"
#include "tablemodel.h"
#include "comboboxdelegate.h"
#include "delegateforvalidation.h"
#include "chart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;

/**
 * @brief Класс главного окна MainWindow
 *
 * Наследуется от класса QMainWindow. Данный класс описывает главное окно программы, в котором находятся основные функции
 * работы с ней, такие как: открытие/закрытие файла с данными, сохранение данных,
 * базовые настройки приложения (положение на экране, размер, язык). Обработка
 * нажатий на функциональные кнопки обрабатываются в данном классе с дальнейшим
 * обращением к методам других классов
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MainWindow
     * @param parent Указатель на родителя объекта */

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /**
     * @brief Метод closeEvent ловит нажатие на крестик (закрытие программы)
     * @param event Указатель на событие закрытия главного окна. Вызывает метод
     * closeDocument()
     */
    void closeEvent(QCloseEvent *event) override; // ловит нажатие на крестик

private slots:
    void openAboutProgramDialog();
    void editElement();
    void deleteElement();
    void addElement();
    void menuRequested(QPoint pos);
    void closeDocument(); // ззакрытие документа
    void closeAllDocuments(); // закрытие всех документов
    void switchLanguage(QAction *action);
    void slotIdError(const unsigned int &id);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    bool on_actionSave_triggered();

    bool on_actionSave_as_triggered();

    void on_lineSearch_textChanged(const QString &arg1);

    void on_tableViewElectric_clicked(const QModelIndex &index);

    void on_tableViewElectric_pressed(const QModelIndex &index);

    void on_actionToolbar_triggered(); // скрывает/показывает панель инструментов

    void on_actionCharts_triggered();

    void on_actionClear_all_table_triggered();

private:
    Ui::MainWindow *ui;
    TableModel *model;
    QSortFilterProxyModel *proxymodel;
    ComboBoxDelegate *comboBoxDelegate;
    DelegateForValidation *validationForColumns;
    QActionGroup *languageActionGroup;

    QTranslator appTranslator;
    QTranslator qtTranslator;
    QString qmPath;
    QString currentFileName;
    QString fileNameForNewOpen; // на случай Open при уже открытом файле

    bool saveFile(QString &fileName);
    void loadFile(QString &fileName);
    void readSettings();
    void writeSettings();
    void createLanguageMenu();

    QString getCurrentFileName() const;
};
#endif // MAINWINDOW_H
