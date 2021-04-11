// QT
#include <QHeaderView>
#include <QMessageBox>

// current project
#include "tablecontainer.hpp"

TableContainer::TableContainer(double lower_bound, double upper_bound, int decimals,
                               const QString &window_name, QWidget *parent) :
    QWidget(parent),
    m_spin_box_lower_bound{ lower_bound },
    m_spin_box_upper_bound{ upper_bound },
    m_spin_box_decimals{ decimals },
    m_widget_layout(this),
    m_buttons_layout{}
{
    setWindowTitle(window_name);

    m_table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_init_button.setText("Инициализировать значения");
    m_save_button.setText("Сохранить значения");

    m_init_value_double_spin_box.setAlignment(Qt::AlignCenter);
    m_init_value_double_spin_box.setMinimum(m_spin_box_lower_bound);
    m_init_value_double_spin_box.setMaximum(m_spin_box_upper_bound);
    m_init_value_double_spin_box.setSingleStep(.5);
    m_init_value_double_spin_box.setDecimals(m_spin_box_decimals);

    m_init_button.setFixedSize(160, 40);
    m_save_button.setFixedSize(160, 40);

    m_widget_layout.addWidget(&m_table);
    m_widget_layout.addWidget(&m_init_value_double_spin_box);

    m_buttons_layout.addWidget(&m_save_button);
    m_buttons_layout.addWidget(&m_init_button);
    m_widget_layout.addLayout(&m_buttons_layout);

    setupIternalConnections();
}


// private slots
void TableContainer::fillSelectedCells()
{
    auto value{ m_init_value_double_spin_box.value() };

    auto selected_items{ m_table.selectedItems() };
    for(auto&& item : selected_items) {
        item->setText(QString("%1").arg(value, 0, 'f'));
    }
}

void TableContainer::saveButtonPressed()
{
    emit saveButtonPressed(m_table);
    QMessageBox::about(nullptr, windowTitle(), "Значения сохранены");
}

void TableContainer::validateCellValue(int row, int col)
{
    int will_be_unused{};
    auto&& text{ m_table.item(row, col)->text() };
    const auto text_size { text.size() };

    for(int i{}; i < text_size; ++i) {
        if(text[i] == '.') {
            text[i] = ',';
            m_table.blockSignals(true);
            m_table.item(row, col)->setText(text);
            m_table.blockSignals(false);
            break;
        }
    }

    if(!(m_init_value_double_spin_box.validate(text, will_be_unused) == QValidator::Acceptable)) {
        text.remove(text.size() - 1, 1);
        m_table.item(row, col)->setText(text); // recursive check
    }
}


// setters
void TableContainer::setGeometry(const QRect &geometry)
{
    QWidget::setGeometry(geometry);
    auto mysize{ size() };
    m_table.setGeometry(0, 0, mysize.width(), mysize.height() - 100);
    m_init_button.setGeometry(10, mysize.height() - 90, 130, 80);
    m_init_button.setFixedSize(130, 80);
    m_init_value_double_spin_box.setGeometry(150, mysize.height() - 90, 120, 35);
    m_init_value_double_spin_box.setFixedSize(120, 35);
}


// private helpers
void TableContainer::setupIternalConnections()
{
    connect(&m_init_button, SIGNAL(pressed()),
            this, SLOT(fillSelectedCells()));

    connect(&m_save_button, SIGNAL(pressed()),
            this, SLOT(saveButtonPressed()));

    connect(&m_table, SIGNAL(cellChanged(int, int)),
            this, SLOT(validateCellValue(int, int)));
}
