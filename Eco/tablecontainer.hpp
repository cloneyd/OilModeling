#ifndef TABLECONTAINER_HPP
#define TABLECONTAINER_HPP
#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QRect>

class TableContainer : public QWidget
{
    Q_OBJECT
private:
    QPushButton m_init_button;
    QDoubleSpinBox m_spin_box;
    QTableWidget m_table;
    QVBoxLayout m_layout;

public:
    explicit TableContainer(const QString &name = "", QWidget *parent = nullptr);
    ~TableContainer();

public slots:
    void fillSelectedCells() const; // connected with QPushButton(m_init_buttom) pressed()

// setters
public:
    void setupSize(const QRect &geometry);

// Getters
public:
    [[nodiscard]] inline QTableWidget& getTableWidget() noexcept { return m_table; } // WARNING: value can be changed
};

#endif // TABLECONTAINER_HPP
