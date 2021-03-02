#include "mainwindow.hpp"

#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), // FIXME: can throw; must be replaced
      m_painting_widget{},
      m_deeps_table_container{},
      m_xwind_table_container{},
      m_ywind_table_container{},
      m_visualization_container{}
{
    ui->setupUi(this);

    setWindowTitle("Eco");

    connectPaintingSignalsWithMainWindow();

    ui->display_info_tool_box->setCurrentIndex(0);
    ui->main_panel_tab_widget->setCurrentIndex(0);

    //FIXME:
    ui->map_web_engine->load(QUrl("http://www.google.ru/maps/@59.9448043,30.3622528,9.83z"));
    ui->map_web_engine->setFocus();
    ui->map_web_engine->show();

    ui->relief_tab_page->addTab(&m_visualization_container, QString("3D Объект"));
    ui->relief_tab_page->addTab(&m_deeps_table_container, QString("Таблица глубин"));

    ui->winds_direction_tab->addTab(&m_xwind_table_container, QString("Таблица направлений OX"));
    ui->winds_direction_tab->addTab(&m_ywind_table_container, QString("Таблица направлений OY"));

    connect(&m_deeps_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveHeightsFromTableSender(QTableWidget &)));

    connect(&m_xwind_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveXSpeedsFromTableSender(QTableWidget &)));

    connect(&m_ywind_table_container, SIGNAL(saveButtonPressed(QTableWidget &)),
            this, SLOT(saveYSpeedsFromTableSender(QTableWidget &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


// public slots
void MainWindow::setupTables(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    auto rows{ grid.size() };
    auto cols{ rows > 0 ? grid[0].size() : 0 };

    auto& deep_table{ m_deeps_table_container.getTableWidget() };
    auto& xwind_table{ m_xwind_table_container.getTableWidget() };
    auto& ywind_table{ m_ywind_table_container.getTableWidget() };

    deep_table.clearContents();
    xwind_table.clearContents();
    ywind_table.clearContents();

    deep_table.setRowCount(rows);
    deep_table.setColumnCount(cols);

    xwind_table.setRowCount(rows);
    xwind_table.setColumnCount(cols);
    xwind_table.setEnabled(false);

    ywind_table.setRowCount(rows);
    ywind_table.setColumnCount(cols);
    ywind_table.setEnabled(false);

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(grid[i][j].first) {
                auto deep_item{ new QTableWidgetItem };
                deep_item->setBackground(Qt::cyan);
                deep_item->setTextAlignment(Qt::AlignCenter);
                deep_item->setText("-1");
                deep_table.setItem(i, j, deep_item);

                auto xwind_item{ new QTableWidgetItem };
                xwind_item->setBackground(Qt::cyan);
                xwind_item->setTextAlignment(Qt::AlignCenter);
                xwind_item->setText("-1");
                xwind_table.setItem(i, j, xwind_item);

                auto ywind_item{ new QTableWidgetItem };
                ywind_item->setBackground(Qt::cyan);
                ywind_item->setTextAlignment(Qt::AlignCenter);
                ywind_item->setText("-1");
                ywind_table.setItem(i, j, ywind_item);
            }
        }
    }
}

void MainWindow::loadFronSiteButtonPressed()
{
    emit ui->scale_spin_box->valueChanged(ui->scale_spin_box->value()); // updating values in other classes
    emit ui->cell_width_spin_box->valueChanged(ui->cell_width_spin_box->value()); // updating values in other classes
    emit ui->cell_height_spin_box->valueChanged(ui->cell_height_spin_box->value()); // updating values in other classes

    ui->display_info_tool_box->setCurrentIndex(0);
    m_painting_widget.setScenePixmap(getPixmapFromWebEngine());
    ui->edit_image_button->setEnabled(true);
}

void MainWindow::loadFromPCButtonPressed()
{
    emit ui->scale_spin_box->valueChanged(ui->scale_spin_box->value()); // updating values in other classes
    emit ui->cell_width_spin_box->valueChanged(ui->cell_width_spin_box->value()); // updating values in other classes
    emit ui->cell_height_spin_box->valueChanged(ui->cell_height_spin_box->value()); // updating values in other classes

    auto image_path { QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg *.jpeg)")) };
    if(image_path.isEmpty()) return;

    m_painting_widget.prepareGraphicsView(image_path);

    ui->edit_image_button->setEnabled(true);
}

void MainWindow::loadHeightsFromFileButtonPressed()
{
    auto file_path{ QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Excel files (*.xlsx)")) };
    if(file_path.isEmpty()) return;

    ui->save_heights_button->setEnabled(true);
    emit loadHeightsFromFileSender(file_path);
}

void MainWindow::editImageButtonPressed()
{
    m_painting_widget.show();
    m_painting_widget.activateWindow();
}

void MainWindow::setImageInMapLabel(const QImage &image)
{
    ui->grid_map_label->setScaledContents(true);
    ui->grid_map_label->setPixmap(QPixmap::fromImage(image));
    ui->display_info_tool_box->setCurrentIndex(1);
}


void MainWindow::createGridSender(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const QColor &color) const
{
    emit createGrid(pm, water_object_area, islands_area, color);

    ui->open_map_visualization_button->setEnabled(true);

    ui->enter_heights_button->setEnabled(true);

    ui->save_map_button->setEnabled(true);
    ui->map_save_format_combo_box->setEnabled(true);
}

void MainWindow::updateGridParameters(double cell_width, double cell_height, double scale) const
{
    ui->cell_width_spin_box->setValue(cell_width);
    ui->cell_height_spin_box->setValue(cell_height);
    ui->scale_spin_box->setValue(scale);
}

void MainWindow::deleteGridSender() const
{
    emit deleteGrid();
}

void MainWindow::saveHeightsFromTableSender(QTableWidget &table)
{
    emit saveHeightsFromTable(table);
    ui->enter_speed_vectors_button->setEnabled(true);
    m_xwind_table_container.getTableWidget().setEnabled(true);
    m_ywind_table_container.getTableWidget().setEnabled(true);
    ui->save_heights_button->setEnabled(true);
}

void MainWindow::saveXSpeedsFromTableSender(QTableWidget &table)
{
    emit saveXSpeedsFromTable(table);
    ui->wind_save_format_combo_box->setEnabled(true);
    ui->save_wind_button->setEnabled(true);
    ui->computate_speeds_button->setEnabled(true);
}

void MainWindow::saveYSpeedsFromTableSender(QTableWidget &table)
{
    emit saveYSpeedsFromTable(table);
    ui->wind_save_format_combo_box->setEnabled(true);
    ui->save_wind_button->setEnabled(true);
    ui->computate_speeds_button->setEnabled(true);
}

void MainWindow::openMapVisualizationButtonPressed()
{
    ui->display_info_tool_box->setCurrentIndex(2);
    ui->relief_tab_page->setCurrentIndex(0);
}

void MainWindow::enterHeightsButtonPressed()
{
    ui->display_info_tool_box->setCurrentIndex(2);
    ui->relief_tab_page->setCurrentIndex(1);
}

void MainWindow::updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto nrows{ heights.size() };
    auto ncols{ nrows > 0 ? heights[0].size() : 0 };

    auto& table{ m_deeps_table_container.getTableWidget() };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(heights[i][j].first) {
                table.item(i, j)->setText(QString("%1").arg(heights[i][j].second));
            }
        }
    }
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
    ui->display_info_tool_box->setCurrentIndex(3);
    ui->winds_direction_tab->setCurrentIndex(1);
}

void MainWindow::saveSpeedsButtonPressed()
{
    auto formats{ getFormatsFromComboBox(ui->wind_save_format_combo_box) };

    auto file_path { QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/wind_image" + ui->wind_save_format_combo_box->currentText(),
                                                  tr(formats.toStdString().c_str())) };
    if(file_path.isEmpty()) return;

    QString file_format;
    for(int i{ file_path.size() - 1 }; file_path[i] != '.'; --i) {
        file_format.push_front(file_path[i]);
    }

    if(file_format == QString("xlsx")) {
        ui->load_heights_from_file_button->setEnabled(true);
        emit saveSpeedsAsExcel(file_path);
        return;
    }

    if(ui->map_with_winds_label->pixmap(Qt::ReturnByValue).save(file_path)) {
        QMessageBox::warning(nullptr, QString("Ошибка сохранения"), QString("Возникла ошибка при сохранение\nизображения. Пожалуйста,\nпопробуйте еще раз"));
    }
}

void MainWindow::saveMapButtonPressed()
{
    auto formats{ getFormatsFromComboBox(ui->map_save_format_combo_box) };

    auto file_path { QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  "/home/map_image" + ui->map_save_format_combo_box->currentText(),
                                                  tr(formats.toStdString().c_str())) };
    if(file_path.isEmpty()) return;

    QString file_format;
    for(int i{ file_path.size() - 1 }; file_path[i] != '.'; --i) {
        file_format.push_front(file_path[i]);
    }

    if(file_format == QString("xlsx")) {
        ui->load_heights_from_file_button->setEnabled(true);
        emit saveMapAsExcel(file_path);
        return;
    }

    if(!m_painting_widget.getMapImage().save(file_path)) {
        QMessageBox::warning(nullptr, QString("Ошибка сохранения"), QString("Возникла ошибка при сохранение\nизображения. Пожалуйста,\nпопробуйте еще раз"));
    }
}

void MainWindow::computateSpeedsButtonPressed()
{
    // TODO
    emit computateSpeeds();
}


// private functions
QPixmap MainWindow::getPixmapFromWebEngine() const
{
    auto web_engine{ ui->map_web_engine };
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

void MainWindow::connectPaintingSignalsWithMainWindow()
{
    connect(&m_painting_widget, SIGNAL(imageChanged(const QImage &)),
            this, SLOT(setImageInMapLabel(const QImage &)));

    connect(&m_painting_widget, SIGNAL(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const QColor &)),
            this, SLOT(createGridSender(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const QColor &)));

    connect(&m_painting_widget, SIGNAL(cellScaleParametersChanged(double, double, double)),
            this, SLOT(updateGridParameters(double, double, double)));

    connect(&m_painting_widget, SIGNAL(deleteGrid()),
            this, SLOT(deleteGridSender()));
}
