#include "tablecontainer.hpp"
#include "ui_tablecontainer.h"

#include <QScreen>
#include <QVBoxLayout>

// third party functions
extern void showErrorMessageBox(const QString &msg);


// Ctor and dtor
TableContainer::TableContainer(QWidget *parent) :
    QWidget(parent),
    m_init_button{ new QPushButton(QString("Инициализировать\nвыделенные значения"),this) }, // FIXME: unsafe; must be replaced
    m_spin_box{ new QDoubleSpinBox(this) }, // FIXME: unsafe; must be replaced
    m_table{ new TableWidget } // FIXME: unsafe; must be replaced
{
    setWindowTitle(QString("Таблица глубин"));
    setGeometry(30, 50, screen()->size().width() * 2 / 3, screen()->size().height() * 2 / 3);

    m_spin_box->setAlignment(Qt::AlignCenter);
    m_spin_box->setMinimum(0.);
    m_spin_box->setMaximum(10000.);
    m_spin_box->setSingleStep(.5);
    m_spin_box->setDecimals(3);

    auto mysize{ size() };
    m_table->setGeometry(0, 0, mysize.width(), mysize.height() - 100);
    m_init_button->setGeometry(10, mysize.height() - 90, 130, 80);
    m_init_button->setFixedSize(130, 80);
    m_spin_box->setGeometry(150, mysize.height() - 90, 120, 35);
    m_spin_box->setFixedSize(120, 35);

    QVBoxLayout *table_layout{ new QVBoxLayout(this) }; // FIXME: unsafe; must be replaced
    table_layout->addWidget(m_table);
    table_layout->addWidget(m_init_button);
    table_layout->addWidget(m_spin_box);

    connect(m_init_button, SIGNAL(pressed()),
            this, SLOT(fillSelectedCells()));
}

TableContainer::~TableContainer()
{
    delete m_table;
}


// public slots
void TableContainer::show()
{
    m_table->show();
    QWidget::show();
}

void TableContainer::fillSelectedCells() const
{
    auto value{ m_spin_box->value() };
    if(value <= 1e-5) {
        showErrorMessageBox(QString("Некорректное значение в поле.\nПожалуйста, введите число больше 0"));
        return;
    }

    auto selected_items{ m_table->selectedItems() };
    for(auto&& item : selected_items) {
        item->setText(QString("%1").arg(value));
    }
}


// protected functions
void TableContainer::closeEvent(QCloseEvent *event)
{
    m_table->close();
    QWidget::closeEvent(event);
}
