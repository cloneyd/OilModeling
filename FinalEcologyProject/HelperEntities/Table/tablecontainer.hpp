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
    explicit TableContainer(QWidget *parent = nullptr);
    ~TableContainer();

public slots:
    void show();

    void fillSelectedCells() const; // connected with QPushButton(m_init_buttom) pressed()

// Getters
public:
    [[nodiscard]] inline TableWidget* getTableWidget() { return m_table; }

// Overloaded functions
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TABLECONTAINER_HPP
