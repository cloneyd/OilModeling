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
void ExcelWorker::updateHeightsFile(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    if(m_heights_doc)   delete m_heights_doc;
    m_heights_doc = new QXlsx::Document; // WARNING: may throw; should be replaced

    auto grid_size{ grid.size() };
    QVector<QVector<QPair<bool, double>>> heights(grid_size);
    for(int i{}; i < grid_size; ++i){
        auto cols{ grid[i].size() };
        QVector<QPair<bool, double>> tmp(cols);
        for(int j{}; j < cols; ++j) {
            tmp[j] = qMakePair(grid[i][j].first, -1);
        }
        heights[i] = std::move(tmp);
    }

    updateHeights(heights);
}

void ExcelWorker::updateHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto heights_size{ heights.size() };
    for(int i{}; i < heights_size; ++i) {
        auto size{ heights[i].size() };
        for(int j{}; j < size; ++j) {
            if(heights[i][j].first) {
                m_heights_doc->write(i + 1, j + 1, heights[i][j].second);
            }
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
