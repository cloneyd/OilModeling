#include "excelworker.hpp"

#include <algorithm>
#include <QMessageBox>

// third party functions
extern void showErrorMessageBox(const QString &msg, const QString &title = "");


// ctor and dtor
ExcelWorker::ExcelWorker():
    QObject(nullptr),
    m_heights_doc{},
    m_speeds_doc{},
    m_grid_ptr{}
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
    if(!(m_speeds_doc.addSheet("Проеции скорости течений") &&
         m_speeds_doc.addSheet("Проекции скорости течений на поверхности") &&
         m_speeds_doc.addSheet("Общие скорости течений"))) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось создать файл скоростей.");
        return;
    }

    m_grid_ptr = nullptr;
    const auto nrows{ grid.size() };
    if(nrows == 0)  return;
    const auto ncols{ grid[0].size() };
    if(ncols == 0)  return;

    m_grid_ptr = &grid;

    QVector<QVector<QPair<bool, double>>> heights(nrows, QVector<QPair<bool, double>>(ncols));
    for(int i{}; i < nrows; ++i){
        for(int j{}; j < ncols; ++j) {
            heights[i][j] = qMakePair(grid[i][j].first, -1);
        }
    }

    updateHeights(heights);
}

void ExcelWorker::updateHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{    
    const auto nrows{ heights.size() };
    if(nrows == 0)  return;
    const auto ncols{ heights[0].size() };
    if(ncols == 0)  return;

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
    if(!m_grid_ptr) return;
    const auto nrows{ (*m_grid_ptr).size() };
    const auto ncols{ (*m_grid_ptr)[0].size() };

    QXlsx::Document file(file_path);

    QVector<QVector<QPair<bool, double>>> heights(nrows, QVector<QPair<bool, double>>(ncols));
    bool convertion_flag{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
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

void ExcelWorker::updateUXSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[list_of_u_projection]);

    const auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    const auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;

    if(!m_speeds_doc.write(1, 1, "Таблица скоростей Ux")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(i + 2, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(2, 1, nrows + 1, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::updateUYSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[ListLocation::list_of_u_projection]);

    const auto nrows{ speeds.size() };
    if(nrows == 0) return;
    const auto ncols{ speeds[0].size()  };
    if(ncols == 0) return;

    if(!m_speeds_doc.write(nrows + 4, 1, "Таблица скоростей Uy")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(nrows + 5 + i, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(nrows + 5, 1, nrows + 5 + nrows, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::updateU0XSpeeds(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[ListLocation::list_of_u0_projection]);

    const auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    const auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;

    if(!m_speeds_doc.write(1, 1, "Таблица проекций скоростей U0x")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{ }; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(i + 2, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(2, 1, nrows + 1, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::updateU0YSpeeds(const QVector<QVector<double>> &speeds)
{    
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[ListLocation::list_of_u0_projection]);

    const auto nrows{ speeds.size() };
    if(nrows == 0) return;
    const auto ncols{ speeds[0].size()  };
    if(ncols == 0) return;

    if(!m_speeds_doc.write(nrows + 4, 1, "Таблица проекций скоростей Vy")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(nrows + 5 + i, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(nrows + 5, 1, nrows + 5 + nrows, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::updateU(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[ListLocation::list_of_flows]);

    const auto nrows{ speeds.size() };
    if(nrows == 0) return;
    const auto ncols{ speeds[0].size()  };
    if(ncols == 0) return;

    if(!m_speeds_doc.write(1, 1, "Таблица скоростей U")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(i + 2, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(2, 1, nrows + 1, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::updateU0(const QVector<QVector<double>> &speeds)
{
    auto names{ m_speeds_doc.sheetNames() };
    if(names.size() != number_of_speed_list) {
        showErrorMessageBox("Файл скоростей поврежден", "Ошибка файла");
        return;
    }

    m_speeds_doc.selectSheet(names[ListLocation::list_of_flows]);

    const auto nrows{ speeds.size() };
    if(nrows == 0) return;
    const auto ncols{ speeds[0].size()  };
    if(ncols == 0) return;

    if(!m_speeds_doc.write(nrows + 4, 1, "Таблица скоростей течений на поверхности")) {
        showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
        return;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_grid_ptr)[i][j].first) {
                if(!m_speeds_doc.write(nrows + 5 + i, j + 1, speeds[i][j])) {
                    showErrorMessageBox(QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"), "Ошибка записи");
                    return;
                }
            }
        }
    }

    QXlsx::ConditionalFormatting cfm;
    cfm.add3ColorScaleRule(QColor(0x63BE7B), QColor(0xffEB84), QColor(0xf86968));
    cfm.addRange(nrows + 5, 1, nrows + 5 + nrows, ncols);
    m_speeds_doc.addConditionalFormatting(cfm);
}

void ExcelWorker::saveSpeedsAsExcel(const QString &filepath)
{
    if(!m_speeds_doc.saveAs(filepath)) {
        showErrorMessageBox(QString("Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз"), "Ошибка сохранения");
        return;
    }
}
