#include "tablecontainer.hpp"

#include <QScreen>
#include <QHeaderView>

// third party functions
extern void showErrorMessageBox(const QString &msg);


// Ctor and dtor
TableContainer::TableContainer(const QString &name, QWidget *parent) :
    QWidget(parent),
    m_init_button(QString("Инициализировать\nвыделенные значения"),this),
    m_spin_box(this),
    m_table(this),
    m_layout(this)
{
    setWindowTitle(name);

    m_table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_spin_box.setAlignment(Qt::AlignCenter);
    m_spin_box.setMinimum(0.);
    m_spin_box.setMaximum(10000.);
    m_spin_box.setSingleStep(.5);
    m_spin_box.setDecimals(3);

    m_layout.addWidget(&m_table);
    m_layout.addWidget(&m_init_button);
    m_layout.addWidget(&m_spin_box);

    connect(&m_init_button, SIGNAL(pressed()),
            this, SLOT(fillSelectedCells()));
}

TableContainer::~TableContainer()
{
}


// public slots
void TableContainer::fillSelectedCells() const
{
    auto value{ m_spin_box.value() };
    if(value <= 1e-5) {
        showErrorMessageBox(QString("Некорректное значение в поле.\nПожалуйста, введите число больше 0"));
        return;
    }

    auto selected_items{ m_table.selectedItems() };
    for(auto&& item : selected_items) {
        item->setText(QString("%1").arg(value));
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
