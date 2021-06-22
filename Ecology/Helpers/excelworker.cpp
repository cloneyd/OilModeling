#include "excelworker.hpp"

ExcelWorker::ExcelWorker(QObject *parent) :
    QObject(parent),
    m_depth_doc{},
    m_speeds_doc{},
    m_pixgrid_ptr{},
    m_green(0x63BE7B),
    m_yellow(0xffEB84),
    m_red(0xf86968)
{ /* PASS */ }


// public slots
void ExcelWorker::saveMap(const QString &filepath, SaveOperationStatus *operation_status)
{
    if(!verifyGrid()) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Сетка не задана.\nФайл не был создан");
        if(operation_status)    *operation_status = SaveOperationStatus::ObjectError;
        return;
    }

    QXlsx::Document map;
    map.addSheet("Карта");
    writeToFile(map, 1, 1, 0);

    if(!map.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл.\nПожалуйста, попробуйте еще раз");
        if(operation_status)    *operation_status = SaveOperationStatus::FilepathError;
        return;
    }
    if(operation_status)    *operation_status = SaveOperationStatus::Ok;
}

void ExcelWorker::loadDepth(const QString &filepath, bool *operation_status) const
{
    if(!verifyGrid()) {
        QMessageBox::warning(nullptr, "Ошибка загрузки глубин", "Сетка не была задана.\nЗадайте сетку и попробуйте снова");
        if(operation_status)    *operation_status = false;
        return;
    }

    const auto nrows{ m_pixgrid_ptr->size() };
    const auto ncols{ (*m_pixgrid_ptr)[0].size() };
    QXlsx::Document file(filepath); // open file
    DepthType depth(nrows, QVector<QPair<bool, double>>(ncols, qMakePair(false, -1.)));
    bool is_converted{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_pixgrid_ptr)[i][j].first) {
                if(auto cell{ file.cellAt(i + 1, j + 1) }; cell) { // if cell is exist
                    if(auto cell_value{ cell->value().toDouble(&is_converted) }; is_converted) { // if cell value is convertable
                        depth[i][j] = qMakePair(true, cell_value);
                    }
                    else {
                        QMessageBox::warning(nullptr, "Ошибка чтения", QString("Данные ячейки ") +
                                             QString("%1;%2").arg(i + 1, j + 1) +
                                             QString(" повреждены или недоступны.\nПроверьте файл и повторите попытку"));
                        if(operation_status)    *operation_status = false;
                        return;
                    }
                }
                else {
                    QMessageBox::warning(nullptr, "Ошибка чтения", QString("Ячейка ") +
                                         QString("%1;%2").arg(i + 1, j + 1) +
                                         QString(" повреждена или недоступна.\nПроверьте файл и повторите попытку"));
                    if(operation_status)    *operation_status = false;
                    return;
                }
            }
        }
    }

    emit depthLoaded(depth);
    if(operation_status)    *operation_status = true;
}

void ExcelWorker::saveSpeeds(const QString &filepath, SaveOperationStatus *operation_status) const
{
    if(!verifyGrid()) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Сетка не задана.\nЗадайте сетку и повторите попытку");
        if(operation_status)    *operation_status = SaveOperationStatus::ObjectError;
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Файл скоростей поврежден, сохранение невозможно");
        if(operation_status)    *operation_status = SaveOperationStatus::FatalObjectError;
        return;
    }

    if(!m_speeds_doc.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл по указанному пути.\nПопробуйте еще раз");
        if(operation_status)    *operation_status = SaveOperationStatus::FilepathError;
        return;
    }

    if(operation_status)    *operation_status = SaveOperationStatus::Ok;
}

void ExcelWorker::acceptGrid(const GridType &pixgrid)
{
    m_pixgrid_ptr = std::addressof(pixgrid);

    // clear any content
    recreateDepthFile();
    recreateSpeedsFile();
    recreateOutputFile();
}

void ExcelWorker::saveDepth(const QString &filepath, SaveOperationStatus *operation_status) const
{
    if(!verifyGrid()) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Сетка не задана.\nЗадайте сетку и повторите попытку");
        if(operation_status)    *operation_status = SaveOperationStatus::ObjectError;
        return;
    }

    if(!m_depth_doc.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл по указанному пути.\nПожалуйста, попробуйте еще раз");
        if(operation_status)    *operation_status = SaveOperationStatus::FilepathError;
        return;
    }

    if(operation_status)    *operation_status = SaveOperationStatus::Ok;
}

void ExcelWorker::saveOutput(const QString &filepath, SaveOperationStatus *operation_status)
{
    if(!verifyGrid()) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Сетка не задана.\nЗадайте сетку и повторите попытку");
        if(operation_status)    *operation_status = SaveOperationStatus::ObjectError;
        return;
    }

    if(m_output_doc.sheetNames().size() != OutputDocSheetIndexes::MAX + 1) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Файл скоростей поврежден, сохранение невозможно");
        if(operation_status)    *operation_status = SaveOperationStatus::FatalObjectError;
        return;
    }

    if(!m_output_doc.saveAs(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка сохранения", "Не удалось сохранить файл по указанному пути.\nПопробуйте еще раз");
        if(operation_status)    *operation_status = SaveOperationStatus::FilepathError;
        return;
    }

    if(operation_status)    *operation_status = SaveOperationStatus::Ok;
}

void ExcelWorker::acceptDepth(const DepthType &depth)
{
    if(depth.size() == 0 || depth[0].size() == 0) {
        return;
    }

    const auto sheet_names{ m_depth_doc.sheetNames() };
    if(sheet_names.size() != 1) {
        QMessageBox::warning(nullptr, "Файл поврежден", "Файл глубин поврежден, запись невозможна");
        return;
    }

    recreateSheet(m_depth_doc, 0);

    writeToFile(m_depth_doc, 1, 1, 0, depth);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - AcceptDepth, problem - wrong number of output file sheets");
    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::depth_page, depth);
}

void ExcelWorker::acceptUXProjections(const QVector<QVector<double>> &speeds)
{
    if(speeds.size() == 0 || speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptUXProjections, problem - empty speeds");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Файл поврежден", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    recreateSheet(m_speeds_doc, SpeedsDocSheetsIndexes::u_projection);
    QXlsx::ConditionalFormatting speeds_doc_cfm;
    speeds_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, 1, 1, SpeedsDocSheetsIndexes::u_projection, speeds, "Проекции скоростей течений на OX", &speeds_doc_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptUXProjections"
                                                                                    "problem - wrong output file sheets number");
    recreateSheet(m_output_doc, OutputDocSheetIndexes::flows_xprojections_page);
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::flows_xprojections_page, speeds, "Проекции скоростей течений", &output_doc_cfm);
}

void ExcelWorker::acceptUYProjections(const QVector<QVector<double>> &speeds)
{
    const auto nrows{ speeds.size() };
    if(nrows == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptUYProjections, problem - empty rows");
        return;
    }

    if(speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptUYProjections, problem - empty cols");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Ошибка файла", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    QXlsx::ConditionalFormatting speeds_doc_cfm;
    speeds_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, nrows + 4, 1, SpeedsDocSheetsIndexes::u_projection, speeds, "Проекции скоростей течений на OY", &speeds_doc_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptUYProjections"
                                                                                    "problem - wrong output file sheets number");
    recreateSheet(m_output_doc, OutputDocSheetIndexes::flows_yprojections_page);
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::flows_yprojections_page, speeds,
                "Проекции скоростей течений", &output_doc_cfm);
}

void ExcelWorker::acceptU0XProjections(const QVector<QVector<double>> &speeds)
{
    if(speeds.size() == 0 || speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU0XProjections, problem - empty speeds");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Файл поврежден", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    recreateSheet(m_speeds_doc, SpeedsDocSheetsIndexes::u0_projection);
    QXlsx::ConditionalFormatting speeds_doc_cfm;
    speeds_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, 1, 1, SpeedsDocSheetsIndexes::u0_projection, speeds, "Проекции скоростей на поверхности на OX", &speeds_doc_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptU0XProjections"
                                                                                    "problem - wrong output file sheets number");
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, speeds.size() + 4, 1, OutputDocSheetIndexes::flows_xprojections_page,
                speeds, "Проекции скоростей на поверхности", &output_doc_cfm);
}

void ExcelWorker::acceptU0YProjections(const QVector<QVector<double>> &speeds)
{
    const auto nrows{ speeds.size() };
    if(nrows == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU0YProjections, problem - empty rows");
        return;
    }

    if(speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU0YProjections, problem - empty cols");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Ошибка файла", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    QXlsx::ConditionalFormatting speeds_doc_cfm;
    speeds_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, nrows + 4, 1, SpeedsDocSheetsIndexes::u0_projection,
                speeds, "Проекции скоростей на поверхности на OY", &speeds_doc_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptU0YProjections"
                                                                                    "problem - wrong output file sheets number");
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, nrows + 4, 1, OutputDocSheetIndexes::flows_yprojections_page,
                speeds, "Проекции скоростей на поверхности", &output_doc_cfm);
}

void ExcelWorker::acceptU(const QVector<QVector<double>> &speeds)
{
    if(speeds.size() == 0 || speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU, problem - empty speeds");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Файл поврежден", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    QXlsx::ConditionalFormatting speeds_cfm;
    speeds_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, 1, 1, SpeedsDocSheetsIndexes::flows, speeds, "Cкорости течений", &speeds_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptU"
                                                                                    "problem - wrong output file sheets number");
    recreateSheet(m_output_doc, OutputDocSheetIndexes::flows_page);
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::flows_page,
                speeds, "Скорости течений", &output_doc_cfm);
}

void ExcelWorker::acceptU0(const QVector<QVector<double>> &speeds)
{
    const auto nrows{ speeds.size() };
    if(nrows == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU0, problem - empty rows");
        return;
    }

    if(speeds[0].size() == 0) {
        Q_ASSERT_X(false, "Class - ExcelWorker", "Function - acceptU0, problem - empty cols");
        return;
    }

    if(m_speeds_doc.sheetNames().size() != SpeedsDocSheetsIndexes::num_of_sheets) {
        QMessageBox::warning(nullptr, "Ошибка файла", "Файл скоростей поврежден, запись в него невозможна");
        return;
    }

    QXlsx::ConditionalFormatting speeds_doc_cfm;
    speeds_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_speeds_doc, nrows + 4, 1, SpeedsDocSheetsIndexes::flows, speeds, "Cкорости на поверхности", &speeds_doc_cfm);

    Q_ASSERT_X(m_output_doc.sheetNames().size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Function - acceptU0"
                                                                                    "problem - wrong output file sheets number");
    QXlsx::ConditionalFormatting output_doc_cfm;
    output_doc_cfm.add3ColorScaleRule(m_green, m_yellow, m_red);
    writeToFile(m_output_doc, nrows + 4, 1, OutputDocSheetIndexes::flows_page,
                speeds, "Скорости на поверхности", &output_doc_cfm);
}

void ExcelWorker::acceptXProjections(const QVector<QVector<double>> &projections)
{
    const auto sheet_names{ m_output_doc.sheetNames() };
    Q_ASSERT_X(sheet_names.size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Functions - acceptXProjections,"
                                                                                            "problem - wrong sheet number");
    if(projections.size() == 0) {
        Q_ASSERT_X(false, "Class - Computator", "Function - acceptXProjections, problem - empty rows");
        return;
    }

    if(projections[0].size() == 0) {
        Q_ASSERT_X(false, "Class - Computator", "Function - acceptXProjections, problem - empty cols");
        return;
    }

    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::xspeed_projections_page);
}
void ExcelWorker::acceptYProjections(const QVector<QVector<double>> &projections)
{
    const auto sheet_names{ m_output_doc.sheetNames() };
    Q_ASSERT_X(sheet_names.size() == OutputDocSheetIndexes::MAX + 1, "Class - Computator", "Functions - acceptYProjections,"
                                                                                            "problem - wrong sheet number");
    if(projections.size() == 0) {
        Q_ASSERT_X(false, "Class - Computator", "Function - acceptYProjections, problem - empty rows");
        return;
    }

    if(projections[0].size() == 0) {
        Q_ASSERT_X(false, "Class - Computator", "Function - acceptYProjections, problem - empty cols");
        return;
    }

    writeToFile(m_output_doc, 1, 1, OutputDocSheetIndexes::yspeed_projections_page);
}

void ExcelWorker::loadMattersInformation(const int page_number, const int page_size,
                                         QVector<FileMatterInformation> &where,
                                         ReadingState &state) const
{
    QString filepath{ R"(:/text/TextInformation/Matters)" };

    if(QFile::exists("MattersBase")) {
        filepath = "MattersBase";
    }

    bool convertion_flag{};
    QXlsx::Document matters_doc(filepath);
    auto vec_size{ 0 };
    if(auto size{ matters_doc.read(1, 4) }; size.toString().isEmpty()) {
        Q_ASSERT(false);
        QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось считать информацию о веществах,\nтак как файл"
                                      " недоступен или поврежден");
        state = ReadingState::FileCorrupted;
        return;
    }
    else {
        vec_size = size.toInt(&convertion_flag);
        Q_ASSERT(convertion_flag);
        if(!convertion_flag) {
            QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось считать информацию о веществах,\nтак как файл"
                                          " недоступен или поврежден");
            state = ReadingState::ConvertionFailed;
            return;
        }
    }
    // nnotes - number of unread notes
    if(auto nnotes{ vec_size - (page_number + 1) * page_size }; nnotes <= 0) {
        state = ReadingState::NotEnoughData;  // silenced
        return;
    }
    else {
        vec_size = page_size <= nnotes ? page_size : nnotes; // read one page or remain info
    }

    QVector<FileMatterInformation> reader(vec_size, FileMatterInformation{{}, -1., {}});
    for(int row_index{ 1 }; row_index <= vec_size; ++row_index) {
        reader[row_index - 1].m_name = matters_doc.read(page_number * page_size + row_index, 1).toString();
        auto tmp{ matters_doc.read(page_number * page_size + row_index, 2).toString() };
        if(tmp.front() == '-') {
            reader[row_index - 1].m_mpc = -1.;
            convertion_flag = true;
        }
        else {
            tmp.replace(',', '.');
            reader[row_index - 1].m_mpc = tmp.toDouble(&convertion_flag);
        }
        Q_ASSERT(convertion_flag);
        if(!convertion_flag) {
            QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось считать информацию о веществах,\nтак как файл"
                                          " недоступен или поврежден");
            state = ReadingState::ConvertionFailed;
            return;
        }
        reader[row_index - 1].m_group = matters_doc.read(page_number * page_size +row_index, 3).toString();
    }
    state = ReadingState::Ok;
    where = std::move(reader);
}

// private functions
void ExcelWorker::writeToFile(QXlsx::Document &where,
                 int row_offset, int col_offset,
                 int sheet_index,
                 const QVector<QVector<double>> &what, // belondness will be checked with m_pixgrid_ptr.first
                 const QString &label,
                 QXlsx::ConditionalFormatting *cfm)
{
    where.selectSheet(where.sheetNames()[sheet_index]);

    const auto nrows{ what.size() };
    const auto ncols{ what[0].size()  };

    int shift{};
    if(!label.isEmpty()) {
        if(!where.write(row_offset, col_offset, label)) {
            QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
            return;
        }
        ++shift;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_pixgrid_ptr)[i][j].first) {
                if(!where.write(row_offset + i + shift, col_offset + j, what[i][j])) {
                    QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                    return;
                }
            }
        }
    }

    if(cfm) {
        cfm->addRange(row_offset + shift,  col_offset, row_offset + shift + nrows, col_offset + ncols);
        where.addConditionalFormatting(*cfm);
    }
}

void ExcelWorker::writeToFile(QXlsx::Document &where,
                 int row_offset, int col_offset,
                 int sheet_index,
                 const DepthType &what, // belondness will be checked what.first
                 const QString &label,
                 QXlsx::ConditionalFormatting *cfm)
{
    where.selectSheet(where.sheetNames()[sheet_index]);

    const auto nrows{ what.size() };
    const auto ncols{ what[0].size()  };

    int shift{};
    if(!label.isEmpty()) {
        if(!where.write(row_offset, col_offset, label)) {
            QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
            return;
        }
        ++shift;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(what[i][j].first) {
                if(!where.write(row_offset + i + shift, col_offset + j, what[i][j].second)) {
                    QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                    return;
                }
            }
        }
    }

    if(cfm) {
        cfm->addRange(row_offset + shift,  col_offset, row_offset + shift + nrows, col_offset + ncols);
        where.addConditionalFormatting(*cfm);
    }
}

// belongness will be checked with m_pixgrid_ptr.first and will be filled with -1
void ExcelWorker::writeToFile(QXlsx::Document &where,
                 int row_offset, int col_offset,
                 int sheet_index, const QString &label)
{
    where.selectSheet(where.sheetNames()[sheet_index]);

    const auto nrows{ (*m_pixgrid_ptr).size() };
    const auto ncols{ (*m_pixgrid_ptr)[0].size()  };

    int shift{};
    if(!label.isEmpty()) {
        if(!where.write(row_offset, col_offset, label)) {
            QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
            return;
        }
        ++shift;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_pixgrid_ptr)[i][j].first) {
                if(!where.write(row_offset + i + shift, col_offset + j, "-1.")) {
                    QMessageBox::warning(nullptr, "Ошибка записи", QString("Не удалось записать\nданные в файл. Пожалуйста,\nпопробуйте снова"));
                    return;
                }
            }
        }
    }
}

[[nodiscard]] bool ExcelWorker::verifyGrid() const
{
    if(!m_pixgrid_ptr) {
        return false;
    }

    if(m_pixgrid_ptr->size() == 0) {
        return false;
    }

    if((*m_pixgrid_ptr)[0].size() == 0) {
        return false;
    }

    return true;
}

void ExcelWorker::recreateSheet(QXlsx::Document &doc, int sheet_name_index)
{
    auto sheet_names{ doc.sheetNames() };

    if(sheet_names.size() == 1) {
        doc.renameSheet(sheet_names.front(), "Deleted");
        if(!doc.addSheet(sheet_names.front())) {
            Q_ASSERT_X(false, "Class - Computator", "Function - recreateSheet, problem - sheet name already used");
        }

        if(!doc.deleteSheet("Deleted")) {
            Q_ASSERT_X(false, "Class - Computator", "Function - recreateSheet, problem - sheet was not deleted");
        }
    }
    else {
        if(!doc.deleteSheet(sheet_names[sheet_name_index])) {
            Q_ASSERT_X(false, "Class - Computator", "Function - recreateSheet, problem - sheet was not deleted");
        }

        if(!doc.insertSheet(sheet_name_index, sheet_names[sheet_name_index])) {
            Q_ASSERT_X(false, "Class - Computator", "Function - recreateSheet, problem - sheet name already used");
        }
    }
}

void ExcelWorker::recreateDepthFile()
{
    m_depth_doc.~Document();
    new(std::addressof(m_depth_doc)) QXlsx::Document;
    m_depth_doc.addSheet("Глубины");
}

void ExcelWorker::recreateSpeedsFile()
{
    m_speeds_doc.~Document();
    new(std::addressof(m_speeds_doc)) QXlsx::Document;
    m_speeds_doc.addSheet("Проекции скоростей течений");
    m_speeds_doc.addSheet("Проекции скоростей на поверхности");
    m_speeds_doc.addSheet("Течения");
}

void ExcelWorker::recreateOutputFile()
{
   m_output_doc.~Document();
   new(std::addressof(m_output_doc)) QXlsx::Document;
   m_output_doc.addSheet("Глубины");
   m_output_doc.addSheet("Поле ветров (по оси x)");
   m_output_doc.addSheet("Поле ветров (по оси y)");
   m_output_doc.addSheet("Поле течений (по оси x)");
   m_output_doc.addSheet("Поле течений (по оси y)");
   m_output_doc.addSheet("Поле течений");
   m_output_doc.addSheet("Поле концентраций");
}

#include <QDebug>
// nonmember functions
WrittingState addNewNoteToDatabase(const FileMatterInformation& info)
{
    QString filepath{ R"(:/text/TextInformation/Matters)" };

    if(QFile::exists("MattersBase")) {
        filepath = "MattersBase";
    }

    QXlsx::Document matters_doc(filepath);

    bool is_converted{};
    const auto nnotes{ matters_doc.read(1, 4).toInt(&is_converted) };
    if(!is_converted) {
        return WrittingState::FileCorrupted;
    }

    QVector<FileMatterInformation> matters_info(nnotes + 1);
    matters_info[nnotes] = info;

    for(int index{1}; index <= nnotes; ++index) {
        const auto name{ matters_doc.read(index, 1).toString() };
        const auto mpc{ matters_doc.read(index, 2) };
        const auto group{ matters_doc.read(index, 3).toString() };
        if(mpc.toString() != "-") {
            matters_info[index - 1] = {name, mpc.toDouble(), group };
        }
        else {
            matters_info[index - 1] = {name, -1., group };
        }
    }

    for(int note_index{ nnotes - 1 }; note_index >= 0; --note_index) {
        if(matters_info[note_index].m_name > info.m_name) {
            std::swap(matters_info[note_index], matters_info[note_index + 1]);
        }
        else {
            break; // position is find
        }
    }

    for(int index{}, new_nnotes{ nnotes + 1 }; index < new_nnotes; ++index) {
        if(!matters_doc.write(index + 1, 1, matters_info[index].m_name)) {
            return WrittingState::WrittingError;
        }

        if(matters_info[index].m_mpc < 0.) {
            if(!matters_doc.write(index + 1, 2, "-")) {
                return WrittingState::WrittingError;
            }
        }
        else {
            if(!matters_doc.write(index + 1, 2, matters_info[index].m_mpc)) {
                return WrittingState::WrittingError;
            }
        }

        if(!matters_doc.write(index + 1, 3, matters_info[index].m_group)) {
            return WrittingState::WrittingError;
        }
    }

    if(!matters_doc.write(1, 4, nnotes + 1)) {
        return WrittingState::WrittingError;
    }

    // always must be saved like this
    if(!matters_doc.saveAs("MattersBase")) {
        return WrittingState::FileNotSaved;
    }

    return WrittingState::Ok;
}
