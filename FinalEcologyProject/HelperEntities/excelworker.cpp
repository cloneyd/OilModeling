#include "excelworker.hpp"

#include <algorithm>
#include <QMessageBox>

// ctor and dtor
ExcelWorker::ExcelWorker():
    QObject(nullptr),
    m_heights_doc{}
{
    // PASS
}

ExcelWorker::~ExcelWorker() noexcept
{
    if(m_heights_doc) delete m_heights_doc;
}


// publics slots
void ExcelWorker::updateHeightsFile(const QVector<QPair<int, QVector<QPointF>>> &grid)
{
    if(m_heights_doc)   delete m_heights_doc;
    m_heights_doc = new QXlsx::Document; // WARNING: may throw; should be replaced

    auto grid_size{ grid.size() };
    QVector<QPair<int, QVector<double>>> heights(grid_size);
    for(int i{}; i < grid_size; ++i){
        auto offset{ grid[i].first };
        heights[i].first = offset;

        auto size{ grid[i].second.size() };
        heights[i].second.fill(-1, size);
    }

    emit updateHeights(heights);
}

void ExcelWorker::updateHeights(const QVector<QPair<int, QVector<double>>> &heights)
{
    auto heights_size{ heights.size() };
    for(int i{}; i < heights_size; ++i) {
        auto offset{ heights[i].first };
        auto size{ heights[i].second.size() };
        for(int j{}; j < size; ++j) {
            m_heights_doc->write(i + 1, j + offset + 1, heights[i].second[j]);
        }
    }
}

void ExcelWorker::saveHeightsFile(const QString &filepath)
{
    if(!m_heights_doc->saveAs(filepath)) {
        QMessageBox msg;
        msg.setText(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"));
        msg.exec();
        return;
    }
}
