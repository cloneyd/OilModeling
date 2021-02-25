#ifndef TABLECONTAINER_HPP
#define TABLECONTAINER_HPP
#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QRect>
#include <QDoubleValidator>

class TableContainer : public QWidget
{
    Q_OBJECT
private:
    QPushButton m_init_button;
    QPushButton m_save_changes_button;

    QDoubleSpinBox m_spin_box;

    QDoubleValidator m_validator;

    QTableWidget m_table;

    QVBoxLayout m_layout;
    QHBoxLayout m_buttons_layout;

public:
    explicit TableContainer(const QString &name = "", QWidget *parent = nullptr);
    ~TableContainer();

public slots:
    void fillSelectedCells() const; // connected with m_init_button; signal - buttonPressed()

    void saveButtonPressed(); // connected with m_save_changes_button; signal - buttonPressed();

private slots:
    void validateCellValue(int row, int col);

signals:
    void saveButtonPressed(QTableWidget &table);

// setters
public:
    void setupSize(const QRect &geometry);

// Getters
public:
    [[nodiscard]] inline QTableWidget& getTableWidget() noexcept { return m_table; } // WARNING: value can be changed
};

#endif // TABLECONTAINER_HPP
