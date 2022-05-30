#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSortFilterProxyModel>
#include "dialogaboutprogramm.h"
#include "equipment.h"
#include "tablemodel.h"
#include "comboboxdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString currentFileName;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    QString getCurrentFileName() const;

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionNew_triggered();

    void on_lineSearch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    TableModel *model;
    QSortFilterProxyModel *proxymodel;
    ComboBoxDelegate *comboBoxDelegate;
};
#endif // MAINWINDOW_H
