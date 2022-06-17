#ifndef DIALOGABOUTPROGRAMM_H
#define DIALOGABOUTPROGRAMM_H

#include <QDialog>


namespace Ui {
class DialogAboutProgramm;
}

/**
 * @brief Класс диалогового окна "О программе" DialogAboutProgramm
 *
 * Класс наследуется от QDialog. Класс диалогового окна, которое вызывается в случае срабатывания action
 * из главного окна (класса MainWindow). Выводит основную информацию об авторе
 * работы
 */
class DialogAboutProgramm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор  класса DialogAboutProgramm
     * @param parent Указатель на объект родителя (обнуленный указатель)
     */
    explicit DialogAboutProgramm(QWidget *parent = nullptr);
    ~DialogAboutProgramm();

private:
    Ui::DialogAboutProgramm *ui;
};

#endif // DIALOGABOUTPROGRAMM_H
