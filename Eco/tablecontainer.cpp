#include "tablecontainer.hpp"

#include <QScreen>
#include <QHeaderView>
#include <QMessageBox>
#include <QKeyEvent>

// Ctor and dtor
TableContainer::TableContainer(const QString &name, QWidget *parent) :
    QWidget(parent),
    m_init_button(QString("Инициализировать\nвыделенные значения"),this),
    m_save_changes_button(QString("Сохранить изменения"), this),
    m_spin_box(this),
    m_validator{},
    m_table(this),
    m_layout(this),
    m_buttons_layout{}
{
    setWindowTitle(name);

    m_table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_spin_box.setAlignment(Qt::AlignCenter);
    m_spin_box.setMinimum(min_spin_box_value);
    m_spin_box.setMaximum(max_spin_box_value);
    m_spin_box.setSingleStep(.5);
    m_spin_box.setDecimals(number_of_spin_decimals);

    m_validator.setBottom(min_spin_box_value);
    m_validator.setTop(max_spin_box_value);
    m_validator.setDecimals(number_of_spin_decimals);

    m_init_button.setFixedSize(150, 40);
    m_save_changes_button.setFixedSize(150, 40);

    m_layout.addWidget(&m_table);
    m_layout.addWidget(&m_spin_box);

    m_buttons_layout.addWidget(&m_save_changes_button);
    m_buttons_layout.addWidget(&m_init_button);
    m_layout.addLayout(&m_buttons_layout);

    connect(&m_init_button, SIGNAL(pressed()),
            this, SLOT(fillSelectedCells()));

    connect(&m_save_changes_button, SIGNAL(pressed()),
            this, SLOT(saveButtonPressed()));

    connect(&m_table, SIGNAL(cellChanged(int, int)),
            this, SLOT(validateCellValue(int, int)));
}

TableContainer::~TableContainer()
{
}


// public slots
void TableContainer::fillSelectedCells() const
{
    auto value{ m_spin_box.value() };

    auto selected_items{ m_table.selectedItems() };
    for(auto&& item : selected_items) {
        item->setText(QString("%1").arg(value));
    }
}

void TableContainer::saveButtonPressed()
{
    QMessageBox::about(nullptr, windowTitle(), "Значения сохранены");
    emit saveButtonPressed(m_table);
}

void TableContainer::setEnabled(bool flag)
{
    m_init_button.setEnabled(flag);
    m_save_changes_button.setEnabled(flag);
    m_spin_box.setEnabled(flag);
    m_table.setEnabled(flag);

    QWidget::setEnabled(flag);
}


// private slots
void TableContainer::validateCellValue(int row, int col)
{
    int will_be_unused{};
    auto&& text{ m_table.item(row, col)->text() };
    const auto text_size { text.size() };

    for(int i{}; i < text_size; ++i) {
        if(text[i] == '.') {
            text[i] = ',';
            break;
        }
    }

    if(!(m_validator.validate(text, will_be_unused) == QValidator::Acceptable)) {
        text.remove(text.size() - 1, 1);
        m_table.item(row, col)->setText(text);
    }
}


// setters
void TableContainer::setupSize(const QRect &geometry)
{
    setGeometry(geometry);
    auto mysize{ size() };
    m_table.setGeometry(0, 0, mysize.width(), mysize.height() - 100);
    m_init_button.setGeometry(10, mysize.height() - 90, 130, 80);
    m_init_button.setFixedSize(130, 80);
    m_spin_box.setGeometry(150, mysize.height() - 90, 120, 35);
    m_spin_box.setFixedSize(120, 35);

}
