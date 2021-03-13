#include "mainwindow.hpp"

#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>

extern void showErrorMessageBox(const QString &msg, const QString &title = "");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow), // FIXME: can throw; must be replaced
      m_painting_widget{},
      m_deeps_table_container{},
      m_xwind_table_container{},
      m_ywind_table_container{},
      m_visualization_container{}
{
    m_ui->setupUi(this);

    setWindowTitle("Eco");

    setupIternalConnections();
    setupNewInstance();

    m_ui->display_info_tool_box->setCurrentIndex(0);
    m_ui->main_panel_tab_widget->setCurrentIndex(0);

    //FIXME:
    m_ui->map_web_engine->load(QUrl("http://www.google.ru/maps/@59.9448043,30.3622528,9.83z"));
    m_ui->map_web_engine->setFocus();
    m_ui->map_web_engine->show();

    m_ui->relief_tab_page->addTab(&m_visualization_container, QString("3D Объект"));
    m_ui->relief_tab_page->addTab(&m_deeps_table_container, QString("Таблица глубин"));

    m_ui->winds_direction_tab->addTab(&m_xwind_table_container, QString("Таблица направлений OX"));
    m_ui->winds_direction_tab->addTab(&m_ywind_table_container, QString("Таблица направлений OY"));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


// public slots
void MainWindow::setupTables(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    auto& deep_table{ m_deeps_table_container.getTableWidget() };
    auto& xwind_table{ m_xwind_table_container.getTableWidget() };
    auto& ywind_table{ m_ywind_table_container.getTableWidget() };

    deep_table.clearContents();
    xwind_table.clearContents();
    ywind_table.clearContents();

    auto nrows{ grid.size() };
    if(nrows == 0)  return;
    auto ncols{ grid[0].size() };
    if(ncols == 0)  return;

    deep_table.setRowCount(nrows);
    deep_table.setColumnCount(ncols);

    xwind_table.setRowCount(nrows);
    xwind_table.setColumnCount(ncols);

    ywind_table.setRowCount(nrows);
    ywind_table.setColumnCount(ncols);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(grid[i][j].first) {
                auto deep_item{ createTableWidgetItem("-1") };
                deep_item->setBackground(Qt::cyan);
                deep_table.setItem(i, j, deep_item);

                auto xwind_item{ createTableWidgetItem("-1") };
                xwind_item->setBackground(Qt::cyan);
                xwind_table.setItem(i, j, xwind_item);

                auto ywind_item{ createTableWidgetItem("-1") };
                ywind_item->setBackground(Qt::cyan);
                ywind_table.setItem(i, j, ywind_item);
            }
        }
    }


}

void MainWindow::createGridSender(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const std::list<QPointF> &mark_pos,
                                  const QColor &color, double line_width)
{
    emit createGrid(pm, water_object_area, islands_area, mark_pos, color, line_width);

    m_ui->open_map_visualization_button->setEnabled(true);

    m_ui->enter_heights_button->setEnabled(true);

    m_ui->save_map_button->setEnabled(true);
    m_ui->map_save_format_combo_box->setEnabled(true);

    m_xwind_table_container.setEnabled(true);
    m_ywind_table_container.setEnabled(true);
    m_ui->force_abs_speed_decompose_button->setEnabled(true);

    m_ui->enter_speed_vectors_button->setEnabled(true);
}

void MainWindow::updateGridParameters(double cell_width, double cell_height, double scale) const
{
    m_ui->cell_width_spin_box->setValue(cell_width);
    m_ui->cell_height_spin_box->setValue(cell_height);
    m_ui->scale_spin_box->setValue(scale);
}

void MainWindow::deleteGridSender() const
{
    emit deleteGrid();

    m_ui->open_map_visualization_button->setEnabled(false);

    m_ui->enter_heights_button->setEnabled(false);

    m_ui->save_map_button->setEnabled(false);
    m_ui->map_save_format_combo_box->setEnabled(false);
}

void MainWindow::drawGridInPixmapSender(QPixmap &map, const QColor &color, double line_width) const
{
    emit drawGridInPixmap(map, color, line_width);
}

void MainWindow::saveHeightsFromTableSender(QTableWidget &table)
{
    emit saveHeightsFromTable(table);

    m_ui->save_heights_button->setEnabled(true);
    m_ui->computate_speeds_button->setEnabled(true);
}

void MainWindow::saveXSpeedsFromTableSender(QTableWidget &table)
{
    emit saveXSpeedsFromTable(table);
}

void MainWindow::saveYSpeedsFromTableSender(QTableWidget &table)
{
    emit saveYSpeedsFromTable(table);
}

void MainWindow::updateXWindTable(const QVector<QVector<double>> &speeds)
{
    auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;

    auto& table{ m_xwind_table_container.getTableWidget() };

    Q_ASSERT_X(nrows == table.rowCount() && ncols == table.columnCount(),
               "Class - MainWindow", "Function - updateXWindTable, table problem");

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(table.item(i, j)) { // FIXME
                auto value{ QString("%1").arg(speeds[i][j], 0, 'f') };
                table.item(i, j)->setText(value);
            }
        }
    }
}

void MainWindow::updateYWindTable(const QVector<QVector<double>> &speeds)
{
    auto nrows{ speeds.size() };
    if(nrows == 0)  return;
    auto ncols{ speeds[0].size() };
    if(ncols == 0)  return;

    auto& table{ m_ywind_table_container.getTableWidget() };

    Q_ASSERT_X(nrows == table.rowCount() && ncols == table.columnCount(),
               "Class - MainWindow", "Function - updateYWindTable, table problem");

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(table.item(i, j)) { // FIXME
                auto value{ QString("%1").arg(speeds[i][j], 0, 'f') };
                value.replace('.', ',');
                table.item(i, j)->setText(value);
            }
        }
    }
}

void MainWindow::openMapVisualizationButtonPressed()
{
    m_ui->display_info_tool_box->setCurrentIndex(2);
    m_ui->relief_tab_page->setCurrentIndex(0);
}

void MainWindow::enterHeightsButtonPressed()
{
    m_ui->display_info_tool_box->setCurrentIndex(2);
    m_ui->relief_tab_page->setCurrentIndex(1);
}

void MainWindow::updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto nrows{ heights.size() };
    auto ncols{ nrows > 0 ? heights[0].size() : 0 };

    auto& table{ m_deeps_table_container.getTableWidget() };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(heights[i][j].first) {
                auto value{ QString("%1").arg(heights[i][j].second, 0, 'f') };
                table.item(i, j)->setText(value);
            }
        }
    }
}

void MainWindow::emitUiSignal() const
{
    emit m_ui->scale_spin_box->valueChanged(m_ui->scale_spin_box->value());
    emit m_ui->cell_width_spin_box->valueChanged(m_ui->cell_width_spin_box->value());
    emit m_ui->cell_height_spin_box->valueChanged(m_ui->cell_height_spin_box->value());
    emit m_ui->ratio_double_spin_box->valueChanged(m_ui->ratio_double_spin_box->value());
    emit m_ui->water_object_type_combo_box->currentIndexChanged(m_ui->water_object_type_combo_box->currentIndex());
    emit m_ui->horizon_spin_box->valueChanged(m_ui->horizon_spin_box->value());
    emit m_ui->atol_percents_spin_box->valueChanged(m_ui->atol_percents_spin_box->value());
    emit m_ui->abs_wind_speed_spin_box->valueChanged(m_ui->abs_wind_speed_spin_box->value());
    emit sendAzimuthState({ m_ui->azimuth_double_spin_box->value(), m_ui->azimuth_check_box->isChecked() });
    emit sendSystemState({ m_ui->system_combo_box->currentIndex(), m_ui->system_check_box->isChecked() });
    emit sendComputationDistance(m_ui->max_computations_distance_double_spin_box->value());
}

void MainWindow::enableSpeedsSaver()
{
    m_ui->wind_save_format_combo_box->setEnabled(true);
    m_ui->save_wind_button->setEnabled(true);
}

void MainWindow::setCurrentMapImageInPixmap(QPixmap &map)
{
    map = QPixmap::fromImage(m_painting_widget.getMapImage());
}

void MainWindow::setFlowMap(const QPixmap &pm)
{
    m_ui->map_with_winds_label->clear();
    m_ui->map_with_winds_label->setScaledContents(true);
    m_ui->map_with_winds_label->setPixmap(pm);
    m_ui->map_with_winds_label->show();
    m_ui->display_info_tool_box->setCurrentIndex(3);
    m_ui->winds_direction_tab->setCurrentIndex(0);
}

void MainWindow::addSourceToTable(const PointSource &source, const QVector<PolutionMatter> &matters) // matters - for future
{
    auto nrows{ m_ui->sources_table_widget->rowCount() };
    m_ui->sources_table_widget->setRowCount(nrows + 1);

    updateSourceInTable(nrows, source, matters);
}

void MainWindow::addSourceToTable(const DiffusionSource &source, const QVector<PolutionMatter> &matters) // matters - for future
{
    addSourceToTable(static_cast<const PointSource&>(source), matters);
    auto nrows{ m_ui->sources_table_widget->rowCount() - 1 }; // prev size

    updateSourceInTable(nrows, source, matters);
}

void MainWindow::updateSourceInTable(int index, const PointSource &source, const QVector<PolutionMatter> &/*matters*/) // matters - for future
{
    m_ui->sources_table_widget->setItem(index, 0, createTableWidgetItem(source.m_name));
    m_ui->sources_table_widget->setItem(index, 1, createTableWidgetItem("Точечный"));
    m_ui->sources_table_widget->setItem(index, 2, createTableWidgetItem(QString("%1").arg(source.m_x)));
    m_ui->sources_table_widget->setItem(index, 3, createTableWidgetItem(QString("%1").arg(source.m_y)));
    m_ui->sources_table_widget->setItem(index, 4, createTableWidgetItem(QString("%1").arg(source.m_spending)));
    m_ui->sources_table_widget->setItem(index, 5, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(index, 6, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(index, 7, createTableWidgetItem("-"));
    m_ui->sources_table_widget->setItem(index, 8, createTableWidgetItem(QString("%1").arg(source.m_initial_dilution_ratio)));
    m_ui->sources_table_widget->setItem(index, 9, createTableWidgetItem(QString("%1").arg(source.m_main_dilution_ratio)));
    m_ui->sources_table_widget->setItem(index, 10, createTableWidgetItem(QString("%1").arg(source.m_common_dilution_ratio)));
}

void MainWindow::updateSourceInTable(int index, const DiffusionSource &source, const QVector<PolutionMatter> &matters) // matters - for future
{
    updateSourceInTable(index, static_cast<const PointSource&>(source), matters);
    m_ui->sources_table_widget->setItem(index, 1, createTableWidgetItem("Диффузионный"));
    m_ui->sources_table_widget->setItem(index, 5, createTableWidgetItem(QString("%1").arg(source.m_length)));
    m_ui->sources_table_widget->setItem(index, 6, createTableWidgetItem(QString("%1").arg(source.m_direction)));
    m_ui->sources_table_widget->setItem(index, 7, createTableWidgetItem(QString("%1").arg(source.m_tubes_number)));
}


// private slots
void MainWindow::loadFromSiteButtonPressed()
{
    m_ui->display_info_tool_box->setCurrentIndex(0);
    m_painting_widget.setScenePixmap(getPixmapFromWebEngine());

    imageLoadedSettings();
}

void MainWindow::loadFromPCButtonPressed()
{
    auto image_path { QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg *.jpeg)")) };
    if(image_path.isEmpty()) return;

    m_painting_widget.prepareGraphicsView(image_path);
    imageLoadedSettings();
}

void MainWindow::loadHeightsFromFileButtonPressed()
{
    auto file_path{ QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Excel files (*.xlsx)")) };
    if(file_path.isEmpty()) return;

    m_ui->save_heights_button->setEnabled(true);
    m_ui->computate_speeds_button->setEnabled(true);

    emit loadHeightsFromFileSender(file_path);
}

void MainWindow::editImageButtonPressed()
{
    m_painting_widget.show();
    m_painting_widget.activateWindow();
}

void MainWindow::setImageInMapLabel(const QImage &image)
{
    m_ui->grid_map_label->setScaledContents(true);
    m_ui->grid_map_label->setPixmap(QPixmap::fromImage(image));
    m_ui->display_info_tool_box->setCurrentIndex(1);
}

void MainWindow::saveHeightsTableButtonPressed()
{
    auto file_path { QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/map.xlsx",
                                                  tr("Excel files(*.xlsx")) };
    if(file_path.isEmpty()) return;

    emit saveMapAsExcel(file_path);
}

void MainWindow::enterSpeedVectorButtonPressed()
{
    m_ui->display_info_tool_box->setCurrentIndex(3);
    m_ui->winds_direction_tab->setCurrentIndex(1);
}

void MainWindow::saveSpeedsButtonPressed()
{
    auto formats{ getFormatsFromComboBox(m_ui->wind_save_format_combo_box) };

    auto file_path { QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/wind_image" + m_ui->wind_save_format_combo_box->currentText(),
                                                  tr(formats.toStdString().c_str())) };
    if(file_path.isEmpty()) return;

    QString file_format;
    for(int i{ file_path.size() - 1 }; file_path[i] != '.'; --i) {
        file_format.push_front(file_path[i]);
    }

    if(file_format == QString("xlsx")) {
        emit saveSpeedsAsExcel(file_path);
        return;
    }

    if(m_ui->map_with_winds_label->pixmap(Qt::ReturnByValue).save(file_path)) {
        QMessageBox::warning(nullptr, QString("Ошибка сохранения"), QString("Возникла ошибка при сохранение\nизображения. Пожалуйста,\nпопробуйте еще раз"));
    }
}

void MainWindow::saveMapButtonPressed()
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
        m_ui->load_heights_from_file_button->setEnabled(true);
        emit saveMapAsExcel(file_path);
        return;
    }

    if(!m_painting_widget.getMapImage().save(file_path)) {
        QMessageBox::warning(nullptr, QString("Ошибка сохранения"), QString("Возникла ошибка при сохранение\nизображения. Пожалуйста,\nпопробуйте еще раз"));
    }
}

void MainWindow::computateSpeedsButtonPressed() const
{
    // TODO
    emit computateSpeeds();
}


void MainWindow::azimuthCheckBoxStateChanged(bool newstate)
{
    if(newstate) {
        if(m_ui->system_check_box->isChecked()) {
            m_ui->system_check_box->setChecked(false);
        }
        m_ui->system_combo_box->setEnabled(false);

        m_ui->azimuth_double_spin_box->setEnabled(true);
        emit sendAzimuthState({ m_ui->azimuth_double_spin_box->value(), true });
    }
    else {
        m_ui->system_combo_box->setEnabled(true);
        m_ui->system_check_box->setChecked(true);

        m_ui->azimuth_double_spin_box->setEnabled(false);
        emit sendAzimuthState({ m_ui->azimuth_double_spin_box->value(), false });
    }
}

void MainWindow::systemCheckBoxStateChanged(bool newstate)
{
    if(newstate) {
        if(m_ui->azimuth_check_box->isChecked()) {
            m_ui->azimuth_check_box->setChecked(false);
        }
        emit sendSystemState({ m_ui->system_combo_box->currentIndex(), true });
    }
    else {
        m_ui->azimuth_check_box->setChecked(true);
        emit sendSystemState({ m_ui->system_combo_box->currentIndex(), false });
    }
    // all the rest work will be done by azimuthCheckBoxStateChanged(bool)
}

void MainWindow::forceAbsSpeedDecomposeButtonPressed() const
{
    emit forceAbsSpeedDecompose();
}

void MainWindow::azimuthValueChanged(double angle) const
{
    emit sendAzimuthState({ angle, m_ui->azimuth_check_box->isChecked() });
}

void MainWindow::systemIndexChanged(int index) const
{
    emit sendSystemState({ index, m_ui->system_check_box->isChecked() });
}

void MainWindow::addNewSourceButtonPressed() const
{
    emit addNewSource();
}

void MainWindow::displaySelectedSourceButtonPressed()
{
    auto selected{ m_ui->sources_table_widget->selectedItems() };
    if(selected.empty()) {
        showErrorMessageBox("Выделите источник");
        return;
    }

    auto index{ selected.front()->row() };
    emit displaySelectedSource(index);
}

void MainWindow::deleteSelectedSouceButtonPressed()
{
    auto selected{ m_ui->sources_table_widget->selectedItems() };
    if(selected.empty()) {
        showErrorMessageBox("Выделите источник");
        return;
    }

    auto index{ selected.front()->row() };
    m_ui->sources_table_widget->removeRow(index);
    emit deleteSelectedSource(index);
}


// private functions
QPixmap MainWindow::getPixmapFromWebEngine() const
{
    auto web_engine{ m_ui->map_web_engine };
    QPixmap pixmap(web_engine->size());

    QPainter painter(&pixmap);
    web_engine->render(&painter);
    return pixmap;
}

QString MainWindow::getFormatsFromComboBox(const QComboBox *box) const
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

void MainWindow::setupNewInstance()
{
    m_ui->add_new_polution_source_button->setEnabled(false);
    m_ui->delete_polution_source_button->setEnabled(false);
    m_ui->current_source_matter_button->setEnabled(false);

    m_ui->sources_table_widget->setEnabled(false);
    m_ui->sources_table_widget->clear();
    m_ui->sources_table_widget->setColumnCount(DiffusionSource::number_of_properties + 1);
    m_ui->sources_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_xwind_table_container.setEnabled(false);
    m_ywind_table_container.setEnabled(false);
    m_deeps_table_container.setEnabled(false);

    m_ui->edit_image_button->setEnabled(false);
    m_deeps_table_container.setEnabled(false);

    m_ui->wind_save_format_combo_box->setEnabled(false);
    m_ui->save_wind_button->setEnabled(false);
    m_xwind_table_container.setEnabled(false);
    m_ywind_table_container.setEnabled(false);

    m_ui->map_save_format_combo_box->setEnabled(false);
    m_ui->save_map_button->setEnabled(false);

    m_ui->save_in_zip_button->setEnabled(false);

    m_ui->computate_speeds_button->setEnabled(false);
    m_ui->enter_speed_vectors_button->setEnabled(false);
    m_ui->force_abs_speed_decompose_button->setEnabled(false);

    m_ui->enter_heights_button->setEnabled(false);
    m_ui->load_heights_from_file_button->setEnabled(false);
    m_ui->save_heights_button->setEnabled(false);    
}

void MainWindow::imageLoadedSettings()
{
    setupNewInstance();

    m_ui->edit_image_button->setEnabled(true);
    m_deeps_table_container.setEnabled(true);

    m_ui->add_new_polution_source_button->setEnabled(true);
    m_ui->delete_polution_source_button->setEnabled(true);
    m_ui->current_source_matter_button->setEnabled(true);

    m_ui->sources_table_widget->setEnabled(true);
}

void MainWindow::setupIternalConnections()
{
    connectPaintingSignalsWithMainWindow();

    connect(&m_deeps_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveHeightsFromTableSender(QTableWidget &)));

    connect(&m_xwind_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveXSpeedsFromTableSender(QTableWidget &)));

    connect(&m_ywind_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveYSpeedsFromTableSender(QTableWidget &)));

    connect(m_ui->azimuth_check_box, SIGNAL(toggled(bool)),
            this, SLOT(azimuthCheckBoxStateChanged(bool)));

    connect(m_ui->system_check_box, SIGNAL(toggled(bool)),
            this, SLOT(systemCheckBoxStateChanged(bool)));

    connect(m_ui->azimuth_double_spin_box, SIGNAL(valueChanged(double)),
            this, SLOT(azimuthValueChanged(double)));

    connect(m_ui->system_combo_box, SIGNAL(currentIndexChanged(int)),
            this, SLOT( systemIndexChanged(int)));
}

void MainWindow::connectPaintingSignalsWithMainWindow()
{
    connect(&m_painting_widget, SIGNAL(imageChanged(const QImage &)),
            this, SLOT(setImageInMapLabel(const QImage &)));

    connect(&m_painting_widget, SIGNAL(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const std::list<QPointF> &, const QColor &, double)),
            this, SLOT(createGridSender(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const std::list<QPointF> &, const QColor &, double)));

    connect(&m_painting_widget, SIGNAL(cellScaleParametersChanged(double, double, double)),
            this, SLOT(updateGridParameters(double, double, double)));

    connect(&m_painting_widget, SIGNAL(deleteGrid()),
            this, SLOT(deleteGridSender()));

    connect(&m_painting_widget, SIGNAL(drawGridInPixmap(QPixmap &, const QColor &, double)),
            this, SLOT(drawGridInPixmapSender(QPixmap &, const QColor &, double)));
}

QTableWidgetItem* MainWindow::createTableWidgetItem(const QString &text) const
{
    auto item{ new QTableWidgetItem };
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(text);
    return item;
}
