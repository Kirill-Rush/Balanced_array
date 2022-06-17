#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief Класс делегата для столбца типа оборудования ComboBoxDelegate
 *
 * Класс наследуется от QStyledItemDelegate. Создает виджет редактора для выбора
 * одного из представленных типов оборудования
 */
class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    QStringList listOfVariants;

public:
    /**
     * @brief Конструктор класса ComboBoxDelegate
     * @param parent Указатель на родителя объекта (обнуленный указатель)
     */
    explicit ComboBoxDelegate(QWidget *parent = nullptr);

    /**
     * @brief метод createEditor
     * является переопределенным и константным, создает виджет редактора для
     * выбора типа оборудования
     * @param parent Указатель на объект родителя
     * @param option Ссылка на опции (параметры описания вмиджета)
     * @param index Индекс редактируемой ячейки
     * @return указатель на созданный виджет редактора
     */
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    /**
     * @brief метод setEditorData
     * является переопределенным и константным, служит для передачи данных
     * в редактор
     * @param editor Указатель на редактор
     * @param index Ссылка на индекс ячейки
     */
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    /**
     * @brief метод setModelData
     * является переопределенным и константным, служит для передачи данных
     * в таблицу
     * @param editor Указатель на редактор
     * @param model Указатель на модель
     * @param index Ссылка на индекс ячейки
     */
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    /**
     * @brief метод updateEditorGeometry
     * является переопределенным и константным, служит определения
     * месторасположения виджета
     * @param editor Указатель на редактор
     * @param option Ссылка на опции (параметры описания вмиджета)
     * @param index Ссылка на индекс ячейки
     */
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    /**
     * @brief метод editorEvent
     * является переопределенным, реакция ячейки на событие (нажатие кнопки мыши)
     * @param event Указатель на событие
     * @param model Указатель на модель
     * @param option Ссылка на опции (параметры описания вмиджета)
     * @param index Ссылка на индекс ячейки
     * @return булевое значение, true - нажатие по левой кнопке мыши, false -
     * иные события
     */
    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    /**
     * @brief метод setData
     * - сеттер, передача вариантов типов оборудования в редактор
     * @param iListOfVariants Ссылка на список типов оборудования
     */
    void setData(const QStringList &iListOfVariants);
};

#endif // COMBOBOXDELEGATE_H
