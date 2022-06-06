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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void slotIdError(const unsigned int &id);

private slots:
    void openAboutProgramDialog();
    void saveFile(QString &fileName);
    void loadFile(QString &fileName);
    void editElement();
    void deleteElement();
    void addElement();
    void menuRequested(QPoint pos);
    void readSettings();
    void writeSettings();
    void closeDocument(); // при его выборе есть возможность сохранить изменения
    void closeSomeDocuments(); // при его выборе невозможно сохранить изменения
    //void closeEvent(QCloseEvent *event);
    void switchLanguage(QAction *action);
    //void slotIdError(const unsigned int &id);

    QString getCurrentFileName() const;

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionNew_triggered();

    void on_lineSearch_textChanged(const QString &arg1);

    void on_tableViewElectric_clicked(const QModelIndex &index);

    void on_tableViewElectric_pressed(const QModelIndex &index);

    void on_actionToolbar_triggered(); // скрывает/показывает панель инструментов

    void on_actionCharts_triggered();

protected:
    void closeEvent(QCloseEvent *event) override; // ловит нажатие на крестик

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

    void createLanguageMenu();
};
#endif // MAINWINDOW_H
