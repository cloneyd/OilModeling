#ifndef TABLECONTAINER_HPP
#define TABLECONTAINER_HPP
#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "HelperEntities/Table/tablewidget.hpp"

class TableContainer : public QWidget
{
    Q_OBJECT
private:
    QPushButton *m_init_button;
    QDoubleSpinBox *m_spin_box;
    TableWidget *m_table;

public:
    explicit TableContainer(const QString &name, QWidget *parent = nullptr);
    ~TableContainer();

public slots:
    void show(); // overriden QWidget::show()

    void fillSelectedCells() const; // connected with QPushButton(m_init_buttom) pressed()

// Getters
public:
    [[nodiscard]] inline TableWidget* getTableWidget() noexcept { return m_table; } // WARNING: value can be changed

// Overloaded functions
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TABLECONTAINER_HPP
