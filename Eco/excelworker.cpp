#include "excelworker.hpp"

#include <algorithm>
#include <QMessageBox>

// third party functions
extern void showErrorMessageBox(const QString &msg, const QString &title = "");


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
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                }
            }
        }
    }
}

void ExcelWorker::saveHeightsFile(const QString &filepath)
{
    if(!m_heights_doc.saveAs(filepath)) {
        showErrorMessageBox(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"), "Ошибка записи");
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
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
    }

    m_speeds_doc.selectSheet(names.front());

    const auto nrows{ speeds.size() };
    const auto ncols{ nrows > 0 ? speeds[0].size() : 0 };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_grid[i][j]) {
                if(!m_speeds_doc.write(i + 1, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                }
            }
        }
    }
}

void ExcelWorker::updateYSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != 2) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
    }

    m_speeds_doc.selectSheet(names.back());

    const auto nrows{ speeds.size() };
    const auto ncols{ nrows > 0 ? speeds[0].size() : 0 };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_grid[i][j]) {
                if(!m_speeds_doc.write(i + 1, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                }
            }
        }
    }
}

void ExcelWorker::saveSpeedsAsExcel(const QString &filepath)
{
    if(!m_speeds_doc.saveAs(filepath)) {
        showErrorMessageBox(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"), "Ошибка сохранения");
        return;
    }
}

void ExcelWorker::saveValuesWithHighlight(const QString &filepath, const QVector<QVector<double>> &value, double discard_flag) const
{
    constexpr auto atol{ 1e-4 };
    QXlsx::Document doc;

    QString value_sheet_name{ "Лист1" };
    doc.addSheet(value_sheet_name);
    doc.selectSheet(value_sheet_name);
    const auto value_nrows{ value.size() };
    auto max_value_cols{ -1 };
    if(value_nrows == 0)    return;
    for(int i{}; i < value_nrows; ++i) {
        const auto ncols{ value[i].size() };
        if(ncols == 0) continue;
        if(max_value_cols < ncols)    max_value_cols = ncols;

        for(int j{}; j < ncols; ++j) {
            if(std::fabs(std::fabs(value[i][j]) - std::fabs(discard_flag)) > atol) {
                if(!doc.write(i + 1, j + 1, value[i][j])) {
                    showErrorMessageBox("Не удалось записать данные в файл.\nПожалуйста, попробуйте еще раз", "Ошибка записи");
                }
            }
        }
    }

    if(!doc.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз", "Ошибка сохранения");
    }
}

void ExcelWorker::saveValuesWithHighlight(const QString &filepath, const QVector<QVector<double>> &first, const QVector<QVector<double>> &second, double discard_flag) const
{
    constexpr auto atol{ 1e-4 };
    QXlsx::Document doc;

    QString first_sheet_name{ "Лист1" };
    doc.addSheet(first_sheet_name);
    doc.selectSheet(first_sheet_name);
    const auto first_nrows{ first.size() };
    auto max_first_cols{ -1 };
    if(first_nrows == 0)    return;
    for(int i{}; i < first_nrows; ++i) {
        const auto ncols{ first[i].size() };
        if(ncols == 0) continue;
        if(max_first_cols < ncols)    max_first_cols = ncols;

        for(int j{}; j < ncols; ++j) {
            if(std::fabs(std::fabs(first[i][j]) - std::fabs(discard_flag)) > atol) {
                if(!doc.write(i + 1, j + 1, first[i][j])) {
                    showErrorMessageBox("Не удалось записать данные в файл.\nПожалуйста, попробуйте еще раз", "Ошибка записи");
                }
            }
        }
    }
    QXlsx::ConditionalFormatting first_cfm;
    first_cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    first_cfm.addRange(1, 1, first_nrows, max_first_cols);
    doc.addConditionalFormatting(first_cfm);

    QString second_sheet_name{ "Лист2" };
    doc.addSheet(second_sheet_name);
    doc.selectSheet(second_sheet_name);
    const auto second_nrows{ second.size() };
    auto max_second_cols{ -1 };
    if(first_nrows == 0)    return;
    for(int i{}; i < second_nrows; ++i) {
        const auto ncols{ second[i].size() };
        if(ncols == 0) continue;
        if(max_second_cols < ncols) max_second_cols = ncols;

        for(int j{}; j < ncols; ++j) {
            if(std::fabs(std::fabs(second[i][j]) - std::fabs(discard_flag)) > atol) {
                if(!doc.write(i + 1, j + 1, second[i][j])) {
                    showErrorMessageBox("Не удалось записать данные в файл.\nПожалуйста, попробуйте еще раз", "Ошибка записи");
                }
            }
        }
    }

    QXlsx::ConditionalFormatting second_cfm;
    second_cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    second_cfm.addRange(1, 1, second_nrows, max_second_cols);
    doc.addConditionalFormatting(second_cfm);

    if(!doc.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз");
    }
}
