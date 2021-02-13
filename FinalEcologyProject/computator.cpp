#include "computator.hpp"

#include <QTableWidgetItem>

Computator::Computator() :
    QObject{},
    m_heights{},
    m_x_speed_vector_table_container{ new TableContainer(QString("Таблица значений проекций скорости на OX")) },
    m_y_speed_vector_table_container{ new TableContainer(QString("Таблица значений проекций скорости на OY")) },
    m_wo_type{ WaterObjectType::river },
    m_az_ratio{ 0.001 }
{
    connect(m_x_speed_vector_table_container->getTableWidget(), SIGNAL(closeSignal(TableWidget*)),
            this, SLOT(setupXSpeedVectors(TableWidget*)));
    connect(m_y_speed_vector_table_container->getTableWidget(), SIGNAL(closeSignal(TableWidget*)),
            this, SLOT(setupYSpeedVectors(TableWidget*)));
}

Computator::~Computator()
{
    delete m_y_speed_vector_table_container;
    delete m_x_speed_vector_table_container;
}


// public slots
void Computator::setupHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto rows{ heights.size() };
    if(rows < 1) {
        return;
    }

    auto cols{ heights[0].size() };
    if(cols < 1) {
        return;
    }

    m_heights.resize(rows);
    for(int i{}; i < rows; ++i) {
        m_heights[i].resize(cols);
        for(int j{}; j < cols; ++j) {
            m_heights[i][j] = heights[i][j];
        }
    }
}


void Computator::displayXYSpeedVectorTableWidgets()
{
    // clear old content
    auto x_table{ m_x_speed_vector_table_container->getTableWidget() };
    x_table->clear();

    auto y_table{ m_y_speed_vector_table_container->getTableWidget() };
    y_table->clear();

    auto rows{ m_heights.size() };
    auto cols{ rows > 0 ? m_heights[0].size() : 0 };
    x_table->setRowCount(rows);
    x_table->setColumnCount(cols);
    y_table->setRowCount(rows);
    y_table->setColumnCount(cols);

    if(m_xyspeeds_vectors.size() > 0) {
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(m_heights[i][j].first) {
                    auto x_item{ new QTableWidgetItem };
                    x_item->setText(QString("%1").arg(m_xyspeeds_vectors[i][j].first));
                    x_item->setBackground(QBrush(Qt::cyan));
                    x_item->setTextAlignment(Qt::AlignCenter);
                    x_table->setItem(i, j, x_item);

                    auto y_item{ new QTableWidgetItem };
                    y_item->setText(QString("%1").arg(m_xyspeeds_vectors[i][j].second));
                    y_item->setBackground(QBrush(Qt::cyan));
                    y_item->setTextAlignment(Qt::AlignCenter);
                    y_table->setItem(i, j, y_item);
                }
            }
        }
    }
    else {
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(m_heights[i][j].first) {
                    auto x_item{ new QTableWidgetItem };
                    x_item->setText("-1");
                    x_item->setBackground(QBrush(Qt::cyan));
                    x_item->setTextAlignment(Qt::AlignCenter);
                    x_table->setItem(i, j, x_item);

                    auto y_item{ new QTableWidgetItem };
                    y_item->setText("-1");
                    y_item->setBackground(QBrush(Qt::cyan));
                    y_item->setTextAlignment(Qt::AlignCenter);
                    y_table->setItem(i, j, y_item);
                }
            }
        }
    }

    m_x_speed_vector_table_container->show();
    m_x_speed_vector_table_container->activateWindow();

    m_y_speed_vector_table_container->show();
    m_y_speed_vector_table_container->activateWindow();
}

void Computator::setupXSpeedVectors(TableWidget *table)
{
    auto rows{ m_heights.size() };
    auto cols{ rows > 0 ? m_heights[0].size() : 0 };

    if(m_xyspeeds_vectors.size() == 0) {
        m_xyspeeds_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
            m_xyspeeds_vectors[i].resize(cols);
        }
    }

    bool convertion_flag{};
    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(m_heights[i][j].first) {
                if(auto value{ table->item(i, j)->text().toDouble(&convertion_flag) }; convertion_flag) {
                    m_xyspeeds_vectors[i][j].first = value;
                }
            }
        }
    }
}

void Computator::setupYSpeedVectors(TableWidget *table)
{
    auto rows{ m_heights.size() };
    auto cols{ rows > 0 ? m_heights[0].size() : 0 };

    if(m_xyspeeds_vectors.size() == 0) {
        m_xyspeeds_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
            m_xyspeeds_vectors[i].resize(cols);
        }
    }

    bool convertion_flag{};
    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(m_heights[i][j].first) {
                if(auto value{ table->item(i, j)->text().toDouble(&convertion_flag) }; convertion_flag) {
                    m_xyspeeds_vectors[i][j].second = value;
                }
            }
        }
    }
}

void Computator::setARatio(double ratio) noexcept
{
    m_az_ratio = ratio;
}

void Computator::setWOType(int index_type) noexcept
{
    if(index_type == 0)
    {
        m_wo_type = WaterObjectType::river;
    }
    else {
        m_wo_type = WaterObjectType::lake;
    }
}
