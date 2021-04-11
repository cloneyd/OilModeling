#ifndef TABLECONTAINER_HPP
#define TABLECONTAINER_HPP
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

class TableContainer : public QWidget
{
    Q_OBJECT

public:
    const double m_spin_box_lower_bound;
    const double m_spin_box_upper_bound;
    const int m_spin_box_decimals;

private: // data
    QTableWidget m_table;

    QPushButton m_save_button;
    QPushButton m_init_button;
    QDoubleSpinBox m_init_value_double_spin_box;

    QVBoxLayout m_widget_layout;
    QHBoxLayout m_buttons_layout;

public:
    TableContainer(double lower_bound = -10000., double upper_boun = 10000., int decimals = 4,
                   const QString &window_name = "", QWidget *parent = nullptr);

private slots:
    void fillSelectedCells(); // connected with Ui::[1]
    void saveButtonPressed(); // connected with Ui::[2]; emits - [1]
    void validateCellValue(int row, int col); // connected with Ui::[3]

signals:
    void saveButtonPressed(const QTableWidget &table) const;

// setters
public:
    void setGeometry(const QRect &geometry);

// Getters
public:
    [[nodiscard]] inline QTableWidget& getChangeableTableWidget() noexcept { return m_table; } // WARNING: value can be changed

// helpers
private:
    void setupIternalConnections();
};

#endif // TABLECONTAINER_HPP
