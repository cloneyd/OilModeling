#include "excelworker.hpp"

#include <algorithm>
#include <QMessageBox>

// third party functions
extern void showErrorMessageBox(const QString &msg);


// ctor and dtor
ExcelWorker::ExcelWorker():
    QObject(nullptr),
    m_heights_doc{},
    m_speeds_doc{}
{
    // PASS
}

ExcelWorker::~ExcelWorker() noexcept
{
}


// publics slots
void ExcelWorker::acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    std::addressof(m_heights_doc)->~Document();
    new (&m_heights_doc) QXlsx::Document;
    m_heights_doc.addSheet("Глубины");

    std::addressof(m_speeds_doc)->~Document();
    new (&m_speeds_doc) QXlsx::Document;
    m_speeds_doc.addSheet("СкоростиOX");
    m_speeds_doc.addSheet("СкоростиOY");

    const auto nrows{ grid.size() };
    const auto ncols{ nrows > 0 ? grid[0].size() : 0 };

    m_grid.resize(nrows);
    QVector<QVector<QPair<bool, double>>> heights(nrows, QVector<QPair<bool, double>>(ncols));
    for(int i{}; i < nrows; ++i){
        m_grid[i].resize(ncols);

        for(int j{}; j < ncols; ++j) {
            heights[i][j] = qMakePair(grid[i][j].first, -1);
            m_grid[i][j] = grid[i][j].first;
        }
    }

    updateHeights(heights);
}

void ExcelWorker::updateHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{    
    const auto nrows{ heights.size() };
    const auto ncols{ nrows > 0 ? heights[0].size() : 0 };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(heights[i][j].first) {
                if(!m_heights_doc.write(i + 1, j + 1, heights[i][j].second)) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                }
            }
        }
    }
}

void ExcelWorker::saveHeightsFile(const QString &filepath)
{
    if(!m_heights_doc.saveAs(filepath)) {
        showErrorMessageBox(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"));
        return;
    }
}

void ExcelWorker::loadHeightsFromFile(const QString &file_path)
{
    const auto nrows{ m_grid.size() };
    const auto ncols{ nrows > 0 ? m_grid[0].size() : 0};

    QXlsx::Document file(file_path);

    QVector<QVector<QPair<bool, double>>> heights(nrows, QVector<QPair<bool, double>>(ncols));
    bool convertion_flag{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_grid[i][j]) {
                if(auto cell { file.cellAt(i + 1, j + 1) }; cell) {
                    if(auto value{ cell->value().toDouble(&convertion_flag) }; convertion_flag) {
                        heights[i][j] = qMakePair(true, value);
                    }
                    else {
                        QMessageBox::warning(nullptr, QString("Ошибка чтения"), QString("Не удалось прочитать данные.\nПожалуйста, проверьте корректность данных\nи повторите снова"));
                        return;
                    }
                }
                else {
                    QMessageBox::warning(nullptr, QString("Ошибка чтения"), QString("Не удалось считать ячейку\nПожалуйста, проверьте корректность файла\nи повторите попытку"));
                    return;
                }
            }
            else {
                heights[i][j] = qMakePair(false, -1.);
            }
        }
    }

    emit heightsLoaded(heights); // WARMING: heights will be empty after function call
}

void ExcelWorker::updateXSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != 2) {
        showErrorMessageBox("Файл скоростей поврежден");
    }

    m_speeds_doc.selectSheet(names.front());

    const auto nrows{ speeds.size() };
    const auto ncols{ nrows > 0 ? speeds[0].size() : 0 };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_grid[i][j]) {
                if(!m_speeds_doc.write(i + 1, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                }
            }
        }
    }
}

void ExcelWorker::updateYSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != 2) {
        showErrorMessageBox("Файл скоростей поврежден");
    }

    m_speeds_doc.selectSheet(names.back());

    const auto nrows{ speeds.size() };
    const auto ncols{ nrows > 0 ? speeds[0].size() : 0 };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_grid[i][j]) {
                if(!m_speeds_doc.write(i + 1, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                }
            }
        }
    }
}

void ExcelWorker::saveSpeedsAsExcel(const QString &filepath)
{
    if(!m_speeds_doc.saveAs(filepath)) {
        showErrorMessageBox(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"));
        return;
    }
}
