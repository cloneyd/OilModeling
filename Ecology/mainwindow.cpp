// QT
#include <QFileDialog>
// current project
#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(std::make_unique<Ui::MainWindow>())
{
    m_ui->setupUi(this);

    m_ui->setupUi(this);

    setWindowTitle("Ecology");

    m_ui->display_info_tool_box->setCurrentIndex(0);
    m_ui->main_panel_tab_widget->setCurrentIndex(0);

    //FIXME: need to hold focus on this widget until map will be loaded
    m_ui->map_web_engine->load(QUrl("http://www.google.ru/maps/@59.9448043,30.3622528,9.83z"));
    m_ui->map_web_engine->setFocus();
    m_ui->map_web_engine->show();

    m_ui->relief_tab_page->addTab(&m_depth_table, QString("Таблица глубин"));

    m_ui->winds_direction_tab->addTab(&m_xprojections_table, QString("Таблица направлений OX"));
    m_ui->winds_direction_tab->addTab(&m_yprojections_table, QString("Таблица направлений OY"));

    createSourcesTableFirstRow();
    setupUiConnections();
    setupFieldsConnections();
    applyNewInstanceSettings(false);
}

// public slots:
void MainWindow::acceptGrid(const GridType &grid)
{
    clearTables();

    if(grid.size() == 0) {
        applyNewGridCreatedSettings(false);
        return;
    }
    if(grid[0].size() == 0) {
        applyNewGridCreatedSettings(false);
        return;
    }
    applyNewGridCreatedSettings(true);

   setupTableToNewGrid(m_depth_table, grid);
   setupTableToNewGrid(m_xprojections_table, grid);
   setupTableToNewGrid(m_yprojections_table, grid);
}

void MainWindow::acceptXProjections(const QVector<QVector<double>> &speeds)
{
    const auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    const auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;
    auto &xtable{ m_xprojections_table.getChangeableTableWidget() };
    Q_ASSERT(nrows == xtable.rowCount() && ncols == xtable.columnCount());

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(auto item{ xtable.item(i, j) }; item) {
                auto value{ QString("%1").arg(speeds[i][j], 0, 'f', 3) };
                item->setText(value);
            }
        }
    }
}

void MainWindow::acceptYProjections(const QVector<QVector<double>> &speeds)
{
    const auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    const auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;
    auto &ytable{ m_yprojections_table.getChangeableTableWidget() };
    Q_ASSERT(nrows == ytable.rowCount() && ncols == ytable.columnCount());

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(auto item{ ytable.item(i, j) }; item) {
                auto value{ QString("%1").arg(speeds[i][j], 0, 'f', 3) };
                item->setText(value);
            }
        }
    }
}

void MainWindow::acceptDepth(const DepthType &depth)
{
    const auto nrows{ depth.size() };
    if(nrows == 0)  return;
    const auto ncols{ depth[0].size() };
    if(ncols == 0)  return;
    auto &table{ m_depth_table.getChangeableTableWidget() };
    Q_ASSERT(nrows == table.rowCount() && ncols == table.columnCount());

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(depth[i][j].first) {
                auto value{ QString("%1").arg(depth[i][j].second, 0, 'f', 3) };
                table.item(i, j)->setText(value);
            }
        }
    }
}

void MainWindow::acceptNewSourceCoordinates(const QVector<QVector<QPointF>> &coordinates)
{
    const auto nsources{ coordinates.size() };
    Q_ASSERT(nsources == m_ui->sources_table_widget->rowCount() - 1);

    for(int i{}; i < nsources; ++i) {
        auto x_string{ QString("%1").arg(coordinates[i].front().x(), 0, 'f', 3) };
        m_ui->sources_table_widget->item(i + 1, 2)->setText(x_string);

        auto y_string{ QString("%1").arg(coordinates[i].front().y(), 0, 'f', 3) };
        m_ui->sources_table_widget->item(i + 1, 3)->setText(y_string);
    }
}

void MainWindow::acceptMapImage(const QPixmap &image, bool is_grid_created)
{
    m_ui->grid_map_label->clear();
    m_ui->grid_map_label->setPixmap(image);
    m_ui->grid_map_label->setScaledContents(true);
    m_ui->display_info_tool_box->setCurrentIndex(1);

    if(is_grid_created) {
        createGridBackgroundedTables();
    }
}

void MainWindow::saveDepthTable(const QTableWidget &table)
{
    const auto nrows{ table.rowCount() };
    if(nrows == 0)  return;
    const auto ncols{ table.columnCount() };
    if(ncols == 0)  return;

    DepthType vector(nrows, QVector<QPair<bool, double>>(ncols, qMakePair(false, -1.)));
    bool is_converted{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(const auto *item{ table.item(i, j) }; item) {
                auto text{ item->text() };
                text.replace(QChar(','), QChar('.'));
                if(const auto value{ text.toDouble(&is_converted) }; is_converted) {
                    vector[i][j] = qMakePair(true, value);
                }
            }
            is_converted = false;
        }
    }

    emit saveDepth(vector);
    m_ui->computate_speeds_button->setEnabled(true);
    m_ui->computate_pollutions_push_button->setEnabled(true);
}

void MainWindow::saveXProjectionTable(const QTableWidget &table)
{
    const auto nrows{ table.rowCount() };
    if(nrows == 0)  return;
    const auto ncols{ table.columnCount() };
    if(ncols == 0)  return;

    QVector<QVector<double>> vector(nrows, QVector<double>(ncols, -1.));
    bool is_converted{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(const auto *item{ table.item(i, j) }; item) {
                auto text{ item->text() };
                text.replace(QChar(','), QChar('.'));
                if(const auto value{ text.toDouble(&is_converted) }; is_converted) {
                    vector[i][j] = value;
                }
            }
            is_converted = false;
        }
    }
    emit saveXProjections(vector);
}

void MainWindow::saveYProjectionTable(const QTableWidget &table)
{
    const auto nrows{ table.rowCount() };
    if(nrows == 0)  return;
    const auto ncols{ table.columnCount() };
    if(ncols == 0)  return;

    QVector<QVector<double>> vector(nrows, QVector<double>(ncols, -1.));
    bool is_converted{};
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(const auto *item{ table.item(i, j) }; item) {
                auto text{ item->text() };
                text.replace(QChar(','), QChar('.'));
                if(const auto value{ text.toDouble(&is_converted) }; is_converted) {
                    vector[i][j] = value;
                }
            }
            is_converted = false;
        }
    }
    emit saveYProjections(vector);
}

// private slots
void MainWindow::loadFromSiteButton()
{
    m_ui->display_info_tool_box->setCurrentIndex(0);
    applyNewImageLoadedSettings(true);

    QPixmap pm{ getPixmapFromWebEngine() };
    emit setImage(pm);
}

void MainWindow::loadFromPCButtonPressed()
{
    auto image_path { QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg *.jpeg)")) };
    if(image_path.isEmpty()) {
        applyNewImageLoadedSettings(false);
        return;
    }

    bool is_operation_done{};
    emit setImage(image_path, &is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию", "Не удалось установить изображение по указанному пути.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            // FIXME: how to repair this operation?
            applyNewImageLoadedSettings(false); // image not setted
            return;
        }
        else {
            image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg *.jpeg)"));
            if(image_path.isEmpty()) {
                applyNewImageLoadedSettings(false);
                return;
            }
            emit setImage(image_path, &is_operation_done);
        }
    }

    applyNewImageLoadedSettings(true);
    QMessageBox::about(this, "Операция завершена", "Изображение загружено");
}

void MainWindow::loadDepthFromFile()
{
    auto file_path{ QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Excel files (*.xlsx)")) };
    if(file_path.isEmpty()) return;

    bool is_operation_done{};
    emit loadDepthFromFile(file_path, &is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию", "Не удалось установить изображение по указанному пути.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            // FIXME: how to repair this operation?
            m_ui->save_depth_button->setEnabled(false);
            m_ui->save_depth_button_2->setEnabled(false);
            m_ui->computate_speeds_button->setEnabled(false);
            m_ui->computate_pollutions_push_button->setEnabled(false);
            return;
        }
        else {
            file_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Excel files (*.xlsx)"));
            if(file_path.isEmpty()) {
                m_ui->save_depth_button->setEnabled(true);
                m_ui->save_depth_button_2->setEnabled(true);
                m_ui->computate_speeds_button->setEnabled(true);
                m_ui->computate_pollutions_push_button->setEnabled(true);
                return;
            }
            emit loadDepthFromFile(file_path, &is_operation_done);
        }
    }

    m_ui->save_depth_button->setEnabled(true);
    m_ui->save_depth_button_2->setEnabled(true);
    m_ui->computate_speeds_button->setEnabled(true);
    m_ui->computate_pollutions_push_button->setEnabled(true);
    QMessageBox::about(this, "Операция завершена", "Значения загружены");
}

void MainWindow::displaySelectedSourceButtonPressed() const
{
    auto index{ m_ui->sources_table_widget->currentRow() };
    if(index == 0)  return;
    emit displaySelectedSource(index - 1);
}

void MainWindow::deleteSelectedSourceButtonPressed()
{
    auto index{ m_ui->sources_table_widget->currentRow() };
    if(index == 0)  return;
    m_ui->sources_table_widget->removeRow(index);
    emit deleteSelectedSource(index - 1);
}

void MainWindow::forceSpeedDecomposeButtonPressed() const
{
    bool is_operation_done{};
    emit forceAbsSpeedDecompose(&is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию", "Не удалось выполнить разложение скорости на составляющие.\nПовторить операцию?") };
        if(answer == QMessageBox::No) {
            // How repair it?
            return;
        }
        else {
            emit forceAbsSpeedDecompose(&is_operation_done); // try again
        }
    }
    QMessageBox::about(nullptr, "Операция завершена", "Значения рассчитаны");
}

void MainWindow::computateSpeedsButtonPressed() const
{
    bool is_operation_done{};
    emit computateSpeeds(&is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию", "Не удалось выполнить расчет скоростей течений.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            // FIXME: how to repair this operation?
            return;
        }
        else {
            emit computateSpeeds(&is_operation_done);
        }
    }
    QMessageBox::about(nullptr, "Операция завершена", "Значения рассчитаны");
    m_ui->save_wind_button->setEnabled(true);
}

void MainWindow::computatePollutionButtonPressed() const
{
    bool is_operation_done{};
    emit computatePollution(&is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию",
                                                 "Не удалось выполнить расчет загрязнений.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            // FIXME: how to repair this operation?
            return;
        }
        else {
            emit computatePollution(&is_operation_done);
        }
    }
    QMessageBox::about(nullptr, "Операция завершена", "Значения рассчитаны");
}

void MainWindow::saveMapInFileButtonPressed()
{
    auto formats{ getFormatsFromComboBox(m_ui->map_save_format_combo_box) };

    auto file_path { QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/map_image" + m_ui->map_save_format_combo_box->currentText(),
                                                  tr(formats.toStdString().c_str())) };
    if(file_path.isEmpty()) return;

    QString file_format;
    for(int i{ file_path.size() - 1 }; file_path[i] != '.'; --i) {
        file_format.push_front(file_path[i]);
    }

    if(file_format == QString("xlsx")) {
        m_ui->load_depth_from_file_button->setEnabled(true);
        bool is_operation_done{};
        emit saveMapInFile(file_path, &is_operation_done);
        while(!is_operation_done) {
            const auto answer{ QMessageBox::question(nullptr, "Не удалось завершить операцию",
                                                     "Не удалось сохранить карту.\nПовторить попытку?") };
            if(answer == QMessageBox::No) {
                return;
            }
            else {
                file_path = QFileDialog::getSaveFileName(this, tr("Save file"), "/home/map.xlsx", "Excel files (*.xlsx)");
                if(file_path.isEmpty()) return;
                emit saveMapInFile(file_path, &is_operation_done);
            }
        }
        QMessageBox::about(this, "Операция завершена", "Значения сохранены");
        return;
    }

    while(!m_ui->grid_map_label->pixmap(Qt::ReturnByValue).save(file_path)) {
        const auto answer{ QMessageBox::question(nullptr, QString("Не удалось выполнить операцию"),
                                                 QString("Возникла ошибка при сохранении\nизображения. Повторить попытку?")) };
        if(answer == QMessageBox::No) {
            return; // do nothing
        }
        else {
            file_path = QFileDialog::getSaveFileName(this, tr("Save file"), "/home/map." + file_format,
                                                     "Images (*." + file_format + ")");
            if(file_path.isEmpty()) return;
        }
    }
    QMessageBox::about(this, "Операция завершена", "Значения сохранены");
}

void MainWindow::saveDepthInFileButtonPressed()
{
    auto file_path{ QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/depth.xlsx",
                                                  tr("Excel files(*.xlsx")) };
    if(file_path.isEmpty()) return;

    bool is_operation_done{};
    emit saveDepthInFile(file_path, &is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(this, "Не удалось завершить операцию", "Не удалось сохранить файл глубин.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            return; // do nothing
        }
        else {
            file_path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/home/depth.xlsx",
                                                    tr("Excel files(*.xlsx"));
            if(file_path.isEmpty()) return;
            emit saveDepthInFile(file_path, &is_operation_done);
        }
    }
    QMessageBox::about(this, "Операция завершена", "Значения сохранены");
}

void MainWindow::saveSpeedsInFileButtonPressed()
{
    auto file_path{ QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/speeds.xlsx",
                                                  tr("Excel files(*.xlsx")) };
    if(file_path.isEmpty()) return;

    bool is_operation_done{};
    emit saveSpeedsInFile(file_path, &is_operation_done);
    while(!is_operation_done) {
        const auto answer{ QMessageBox::question(this, "Не удалось завершить операцию",
                                                "Не удалось сохранить файл скоростей.\nПовторить попытку?") };
        if(answer == QMessageBox::No) {
            return; // do nothing
        }
        else {
            file_path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                     "/home/speeds.xlsx",
                                                     tr("Excel files(*.xlsx"));
            if(file_path.isEmpty()) return;
            emit saveSpeedsInFile(file_path, &is_operation_done);
        }
    }
    QMessageBox::about(this, "Операция завершена", "Значения сохранены");
}

// FIXME: #implementme
void MainWindow::createCommonOutputFileButtonPressed()
{
    return;
}

void MainWindow::azimuthStateChangedSender(int /*state*/)
{
    if(m_ui->azimuth_check_box->isChecked()) {
        if(m_ui->system_check_box->isChecked()) {
            m_ui->system_check_box->setChecked(false); // implicitely emits signal
        }
        m_ui->system_combo_box->setEnabled(false);

        m_ui->azimuth_double_spin_box->setEnabled(true);
        emit azimuthStateChanged({ true, m_ui->azimuth_double_spin_box->value() });
    }
    else {
        m_ui->system_combo_box->setEnabled(true);
        m_ui->system_check_box->setChecked(true);

        m_ui->azimuth_double_spin_box->setEnabled(false);
        emit azimuthStateChanged({ false, m_ui->azimuth_double_spin_box->value() });
    }
}

void MainWindow::systemStateChangedSender(int /*state*/)
{
    const auto current_index{ m_ui->system_combo_box->currentIndex() };
    Q_ASSERT(current_index >= static_cast<int>(WindDirection::MIN) && current_index <= static_cast<int>(WindDirection::MAX));

    if(m_ui->system_check_box->isChecked()) {
        if(m_ui->azimuth_check_box->isChecked()) {
            m_ui->azimuth_check_box->setChecked(false); // implicitely emits signal
        }
        emit windSystemStateChanged({ true,  static_cast<WindDirection>(current_index) });
    }
    else {
        m_ui->azimuth_check_box->setChecked(true);
        emit windSystemStateChanged({ false,  static_cast<WindDirection>(current_index) });
    }
    // all the rest work will be done by azimuthCheckBoxStateChanged(bool)
}

// public functions
void MainWindow::emitInitialSignals() const
{
    emit azimuthStateChanged({ m_ui->azimuth_check_box->isChecked(), m_ui->azimuth_double_spin_box->value() }); // [8]
    emit windSystemStateChanged({ m_ui->system_check_box->isChecked(), static_cast<WindDirection>(m_ui->system_combo_box->currentIndex()) }); // [9]
    emit aRatioChanged(m_ui->ratio_double_spin_box->value()); // [10]
    emit waterObjectTypeChanged(static_cast<WaterObjectType>(m_ui->water_object_type_combo_box->currentIndex())); // [11]
    emit horizonChanged(m_ui->horizon_spin_box->value()); // [12]
    emit atolChanged(m_ui->atol_percents_spin_box->value()); // [13]
    emit absSpeedChanged(m_ui->abs_wind_speed_spin_box->value()); // [14]
    emit maxComputationDistanceChanged(m_ui->max_computations_distance_double_spin_box->value()); // [15]
    emit scaleChanged(m_ui->scale_spin_box->value()); // [16]
    emit cellWidthChanged(m_ui->cell_width_spin_box->value()); // [17]
    emit cellHeightChanged(m_ui->cell_height_spin_box->value()); // [18]
}

// private functions
void MainWindow::resetSourcesTable()
{
    auto nrows{ m_ui->sources_table_widget->rowCount() };
    if(nrows == 1)  return; // do not delete first row
    for(int i{ 1 }; i < nrows; ++i) {
        m_ui->sources_table_widget->removeRow(i);
    }
}

void MainWindow::appendNewSourceToTable(const PointSource &source)
{
    auto nrows{ m_ui->sources_table_widget->rowCount()}; // one row for info
    m_ui->sources_table_widget->setRowCount(nrows + 1);

    updateSourceInTable(nrows - 1, source); // -1 cause updateSource increments value (for computator correct work)
}

void MainWindow::updateSourceInTable(int source_index, const PointSource &source)
{
    ++source_index; // increment in because source table have shifted indexes
    m_ui->sources_table_widget->setItem(source_index, 0, createTableWidgetItem(source.m_name));
    m_ui->sources_table_widget->setItem(source_index, 1, createTableWidgetItem("Точечный"));
    m_ui->sources_table_widget->setItem(source_index, 2, createTableWidgetItem(QString("%1").arg(source.m_x)));
    m_ui->sources_table_widget->setItem(source_index, 3, createTableWidgetItem(QString("%1").arg(source.m_y)));
    m_ui->sources_table_widget->setItem(source_index, 4, createTableWidgetItem(QString("%1").arg(source.m_spending)));
    m_ui->sources_table_widget->setItem(source_index, 5, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(source_index, 6, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(source_index, 7, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(source_index, 8, createTableWidgetItem(QString("%1").arg(source.m_initial_dilution_ratio)));
    m_ui->sources_table_widget->setItem(source_index, 9, createTableWidgetItem(QString("%1").arg(source.m_main_dilution_ratio)));
    m_ui->sources_table_widget->setItem(source_index, 10, createTableWidgetItem(QString("%1").arg(source.m_common_dilution_ratio)));
    m_ui->sources_table_widget->setItem(source_index, 11, createTableWidgetItem(QString("%1").arg(source.m_vat)));
}

void MainWindow::appendNewSourceToTable(const DiffusionSource &source)
{
    appendNewSourceToTable(static_cast<const PointSource&>(source));
    auto nrows{ m_ui->sources_table_widget->rowCount() - 1 }; // prev size

    updateSourceInTable(nrows - 1, source); // -1 cause updateSource increments value (for computator correct work)
}

void MainWindow::updateSourceInTable(int source_index, const DiffusionSource &source)
{
    updateSourceInTable(source_index, static_cast<const PointSource&>(source));
    ++source_index;
    m_ui->sources_table_widget->setItem(source_index, 1, createTableWidgetItem("Диффузионный"));
    m_ui->sources_table_widget->setItem(source_index, 5, createTableWidgetItem(QString("%1").arg(source.m_length)));
    m_ui->sources_table_widget->setItem(source_index, 6, createTableWidgetItem(QString("%1").arg(source.m_direction)));
    m_ui->sources_table_widget->setItem(source_index, 7, createTableWidgetItem(QString("%1").arg(source.m_tubes_number)));
}

void MainWindow::createGridBackgroundedTables()
{
    const GridType *pixgrid_ptr{};
    emit getPixgrid(&pixgrid_ptr);
    Q_ASSERT(pixgrid_ptr);

    const auto pixwidth{ toPixels(m_ui->cell_width_spin_box->value()) };
    const auto pixheight{ toPixels(m_ui->cell_height_spin_box->value()) };
    if(pixwidth <= GridHandlerConstants::s_max_error || pixheight <= GridHandlerConstants::s_max_error) {
        return;
    }

    const auto nrows{ pixgrid_ptr->size() };
    if(nrows == 0)  return;
    const auto ncols{ (*pixgrid_ptr)[0].size() };
    if(ncols == 0)  return;

    auto& depth_table{ m_depth_table.getChangeableTableWidget() };
    auto& xtable{ m_xprojections_table.getChangeableTableWidget() };
    auto& ytable{ m_yprojections_table.getChangeableTableWidget() };
    Q_ASSERT(nrows == depth_table.rowCount() &&
             ncols == depth_table.columnCount());
    Q_ASSERT(nrows == xtable.rowCount() &&
             ncols == xtable.columnCount());
    Q_ASSERT(nrows == ytable.rowCount() &&
             ncols == ytable.columnCount());

    drawBackgroundInTable(depth_table, pixgrid_ptr);
    drawBackgroundInTable(xtable, pixgrid_ptr);
    drawBackgroundInTable(ytable, pixgrid_ptr);
}

void MainWindow::drawBackgroundInTable(QTableWidget &table, const GridType *pixgrid_ptr)
{
    const auto nrows{ pixgrid_ptr->size() };
    const auto ncols{ (*pixgrid_ptr)[0].size() };
    const auto pixwidth{ toPixels(m_ui->cell_width_spin_box->value()) };
    const auto pixheight{ toPixels(m_ui->cell_height_spin_box->value()) };
    const auto cell_width{ table.horizontalHeader()->sectionSize(0) };
    const auto cell_height{ table.verticalHeader()->sectionSize(0) };
    QPainter painter;
    QPixmap map_pixmap{ m_ui->grid_map_label->pixmap(Qt::ReturnByValue) };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*pixgrid_ptr)[i][j].first) {
                QPixmap background(pixwidth, pixheight);
                painter.begin(&background);
                painter.drawPixmap(0, 0, map_pixmap, (*pixgrid_ptr)[i][j].second.x(), (*pixgrid_ptr)[i][j].second.y(), pixwidth, pixheight);
                painter.end();

                background = background.scaled(cell_width, cell_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                table.item(i, j)->setBackground(background);
            }
        }
    }
}

void MainWindow::setupTableToNewGrid(TableContainer &table_container, const GridType &grid)
{
    auto& table{ table_container.getChangeableTableWidget() };
    const auto nrows{ grid.size() };
    const auto ncols{ grid[0].size() };

    table.setRowCount(nrows);
    table.setColumnCount(ncols);

    auto* horizontal_header{ table.horizontalHeader() };
    horizontal_header->setSectionResizeMode(QHeaderView::Fixed);

    auto* vertical_header{ table.verticalHeader() };
    vertical_header->setSectionResizeMode(QHeaderView::Fixed);

    // standart cell size
    constexpr auto row_height{ 30 };
    constexpr auto column_width{ 120 };

    for(int row_index{}; row_index < nrows; ++row_index) {
        vertical_header->resizeSection(row_index, row_height);
    }

    for(int column_index{}; column_index < ncols; ++column_index) {
        horizontal_header->resizeSection(column_index, column_width);
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int column_index{}; column_index < ncols; ++column_index) {
            if(grid[row_index][column_index].first) {
                auto item{ createTableWidgetItem("-1") };
                item->setForeground(Qt::black);
                table.setItem(row_index, column_index, item);
            }
        }
    }
}

void MainWindow::clearTables()
{
    auto& depth_table{ m_depth_table.getChangeableTableWidget() };
    auto& xprojections_table{ m_xprojections_table.getChangeableTableWidget() };
    auto& yprojections_table{ m_yprojections_table.getChangeableTableWidget() };

    depth_table.clearContents();
    depth_table.setRowCount(0);
    depth_table.setColumnCount(0);

    xprojections_table.clearContents();
    xprojections_table.setRowCount(0);
    xprojections_table.setColumnCount(0);

    yprojections_table.clearContents();
    yprojections_table.setRowCount(0);
    yprojections_table.setColumnCount(0);
}

template <class...Flags>
[[nodiscard]] QTableWidgetItem* MainWindow::createTableWidgetItem(const QString &text, Flags&&... flags) const
{
    auto item{ new QTableWidgetItem };
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(text);
    ((item->setFlags(flags)),...);
    return item;
}

[[nodiscard]] QTableWidgetItem* MainWindow::createTableWidgetItem(const QString &text) const
{
    auto item{ new QTableWidgetItem };
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(text);
    return item;
}

[[nodiscard]] QPixmap MainWindow::getPixmapFromWebEngine() const
{
    auto web_engine{ m_ui->map_web_engine };
    QPixmap pixmap(web_engine->size());

    QPainter painter(&pixmap);
    web_engine->render(&painter);
    return pixmap;
}

[[nodiscard]] QString MainWindow::getFormatsFromComboBox(const QComboBox *box) const
{
    QString formats("Formats (");

    auto nfile_formats{ box->count() };
    for(int i{}; i < nfile_formats; ++i) {
        formats += '*' + box->itemText(i) + ' ';
    }
    formats += ");;";

    for(int i{}; i < nfile_formats; ++i) {
        formats += '*' + box->itemText(i) + ";;";
    }

    return formats;
}

void MainWindow::createSourcesTableFirstRow()
{
    auto *table{ m_ui->sources_table_widget };
    table->setRowCount(1);
    table->setColumnCount(DiffusionSource::number_of_properties + 1); // one for type

    table->setItem(0, 0, createTableWidgetItem("Источник", Qt::NoItemFlags));
    table->setItem(0, 1, createTableWidgetItem("Тип", Qt::NoItemFlags));
    table->setItem(0, 2, createTableWidgetItem("X", Qt::NoItemFlags));
    table->setItem(0, 3, createTableWidgetItem("Y", Qt::NoItemFlags));
    table->setItem(0, 4, createTableWidgetItem("Расход", Qt::NoItemFlags));
    table->setItem(0, 5, createTableWidgetItem("Длина", Qt::NoItemFlags));
    table->setItem(0, 6, createTableWidgetItem("Направление\nвыпуска", Qt::NoItemFlags));
    table->setItem(0, 7, createTableWidgetItem("Количество\nпатрубков", Qt::NoItemFlags));
    table->setItem(0, 8, createTableWidgetItem("Кратность начального\nразбравления", Qt::NoItemFlags));
    table->setItem(0, 9, createTableWidgetItem("Кратность основного\nразбавления", Qt::NoItemFlags));
    table->setItem(0, 10, createTableWidgetItem("Общее разбавление", Qt::NoItemFlags));
    table->setItem(0, 11, createTableWidgetItem("НДС", Qt::NoItemFlags));

    table->resizeRowsToContents(); // must be used AFTER items creation
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::applyNewInstanceSettings(bool enabled)
{
    m_ui->load_from_pc_button->setEnabled(true);
    m_ui->load_from_site_button->setEnabled(true);

    resetSourcesTable();
    applyNewImageLoadedSettings(enabled);
    applyNewGridCreatedSettings(enabled);

    m_xprojections_table.setEnabled(enabled);
    m_yprojections_table.setEnabled(enabled);
    m_ui->wind_save_format_combo_box->setEnabled(enabled);
    m_ui->save_wind_button->setEnabled(enabled);
    m_ui->map_save_format_combo_box->setEnabled(enabled);
    m_ui->save_map_button->setEnabled(enabled);
    m_ui->create_common_output_file_button->setEnabled(enabled);
    m_ui->computate_speeds_button->setEnabled(enabled);
    m_ui->computate_pollutions_push_button->setEnabled(enabled);
    m_ui->enter_speed_vectors_button->setEnabled(enabled);
    m_ui->force_abs_speed_decompose_button->setEnabled(enabled);
    m_ui->load_depth_from_file_button->setEnabled(enabled);
    m_ui->save_depth_button->setEnabled(enabled);
    m_ui->save_depth_button_2->setEnabled(enabled);
}

void MainWindow::applyNewImageLoadedSettings(bool enabled)
{
    m_ui->edit_image_button->setEnabled(enabled);
    m_depth_table.setEnabled(enabled);
    m_ui->add_new_polution_source_button->setEnabled(enabled);
    m_ui->delete_pollution_source_button->setEnabled(enabled);
    m_ui->current_source_matter_button->setEnabled(enabled);
    m_ui->sources_table_widget->setEnabled(enabled);
}

void MainWindow::applyNewGridCreatedSettings(bool enabled)
{
    m_xprojections_table.setEnabled(enabled);
    m_yprojections_table.setEnabled(enabled);

    m_ui->force_abs_speed_decompose_button->setEnabled(enabled);
    m_ui->enter_speed_vectors_button->setEnabled(enabled);
    m_ui->open_3d_visualization_button->setEnabled(enabled);
    m_ui->enter_depth_button->setEnabled(enabled);
    m_ui->save_map_button->setEnabled(enabled);
    m_ui->map_save_format_combo_box->setEnabled(enabled);
}

void MainWindow::setupUiConnections()
{
    connect(m_ui->load_from_site_button, SIGNAL(pressed()), // [1]
            this, SLOT(loadFromSiteButton()));

    connect(m_ui->load_from_pc_button, SIGNAL(pressed()), // [2]
            this, SLOT(loadFromPCButtonPressed()));

    connect(m_ui->edit_image_button, SIGNAL(pressed()), // [3]
            this, SLOT(editImageButtonPressed()));

    connect(m_ui->open_3d_visualization_button, SIGNAL(pressed()), // [4]
            this, SLOT(openVisualizationButtonPressed()));

    connect(m_ui->save_map_button, SIGNAL(pressed()), // [5]
            this, SLOT(saveMapInFileButtonPressed()));

    connect(m_ui->save_depth_button_2, SIGNAL(pressed()), // [6]
            this, SLOT(saveDepthInFileButtonPressed()));

    connect(m_ui->save_depth_button, SIGNAL(pressed()), // [6]
            this, SLOT(saveDepthInFileButtonPressed()));

    connect(m_ui->save_wind_button, SIGNAL(pressed()), // [7]
            this, SLOT(saveSpeedsInFileButtonPressed()));

    connect(m_ui->create_common_output_file_button, SIGNAL(pressed()), // [8]
            this, SLOT(createCommonOutputFileButtonPressed()));

    connect(m_ui->enter_speed_vectors_button, SIGNAL(pressed()), // [9]
            this, SLOT(enterSpeedsButtonPressed()));

    connect(m_ui->force_abs_speed_decompose_button, SIGNAL(pressed()), // [10]
            this, SLOT(forceSpeedDecomposeButtonPressed()));

    connect(m_ui->computate_speeds_button, SIGNAL(pressed()),  // [11]
            this, SLOT(computateSpeedsButtonPressed()));

    connect(m_ui->enter_depth_button, SIGNAL(pressed()),  // [12]
            this, SLOT(enterDepthButtonPressed()));

    connect(m_ui->load_depth_from_file_button, SIGNAL(pressed()),  // [13]
            this, SLOT(loadDepthFromFile()));

    connect(m_ui->computate_pollutions_push_button, SIGNAL(pressed()),  // [14]
            this, SLOT(computatePollutionButtonPressed()));

    connect(m_ui->scale_spin_box, SIGNAL(valueChanged(double)), // [15]
            this, SLOT(scaleValueChangedSender(double)));

    connect(m_ui->cell_width_spin_box, SIGNAL(valueChanged(double)), // [16]
            this, SLOT(cellWidthValueChangedSender(double)));

    connect(m_ui->cell_height_spin_box, SIGNAL(valueChanged(double)), // [17]
            this, SLOT(cellHeightValueChangedSender(double)));

    connect(m_ui->water_object_type_combo_box, SIGNAL(currentIndexChanged(int)), // [18]
            this, SLOT(woComboBoxCurrentIndexChangedSender(int)));

    connect(m_ui->horizon_spin_box, SIGNAL(valueChanged(double)), // [19]
            this, SLOT(horizonValueChangedSender(double)));

    connect(m_ui->ratio_double_spin_box, SIGNAL(valueChanged(double)), // [20]
            this, SLOT(aRatioValueChangedSender(double)));

    connect(m_ui->atol_percents_spin_box, SIGNAL(valueChanged(double)), // [21]
            this, SLOT(atolValueChangedSender(double)));

    connect(m_ui->abs_wind_speed_spin_box, SIGNAL(valueChanged(double)), // [22]
            this, SLOT(absSpeedValueChangedSender(double)));

    connect(m_ui->azimuth_double_spin_box, SIGNAL(valueChanged(double)), // [23]
            this, SLOT(azimuthValueChangedSenderSender(double)));

    connect(m_ui->system_combo_box, SIGNAL(currentIndexChanged(int)), // [24]
            this, SLOT(systemCurrentIndexChangedSender(int)));

    connect(m_ui->azimuth_check_box, SIGNAL(stateChanged(int)), // [25]
            this, SLOT(azimuthStateChangedSender(int)));

    connect(m_ui->system_check_box, SIGNAL(stateChanged(int)), // [26]
            this, SLOT(systemStateChangedSender(int)));

    connect(m_ui->max_computations_distance_double_spin_box, SIGNAL(valueChanged(double)), // [27]
            this, SLOT(maxComputationDistanceChangedSender(double)));

    connect(m_ui->add_new_polution_source_button, SIGNAL(pressed()), // [28]
            this, SLOT(addNewSourceButtonPressed()));

    connect(m_ui->current_source_matter_button, SIGNAL(pressed()), // [29]
            this, SLOT(displaySelectedSourceButtonPressed()));

    connect(m_ui->delete_pollution_source_button, SIGNAL(pressed()), // [30]
            this, SLOT(deleteSelectedSourceButtonPressed()));
}

void MainWindow::setupFieldsConnections()
{
    connect(&m_depth_table, SIGNAL(saveButtonPressed(const QTableWidget &)),
            this, SLOT(saveDepthTable(const QTableWidget &)));

    connect(&m_xprojections_table, SIGNAL(saveButtonPressed(const QTableWidget &)),
            this, SLOT(saveXProjectionTable(const QTableWidget &)));

    connect(&m_yprojections_table, SIGNAL(saveButtonPressed(const QTableWidget &)),
            this, SLOT(saveYProjectionTable(const QTableWidget &)));
}
