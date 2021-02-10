#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>

// ctor and dtor
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui{ new Ui::MainWindow }, // WARNING: may throw; should be replaced
          m_map_label{ new QLabel }, // WARNING: may throw; should be replaced
          m_table_container{ new TableContainer{} } // WARNING: may throw; should be replaced
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_table_container;
    delete m_map_label;
    delete ui;
}

// publis slots
void MainWindow::loadMapButtonPressed()
{
    QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
    if(image_path.isEmpty()) return;

    ui->open_map_button->setEnabled(true);
    ui->save_map_as_excel_button->setEnabled(true);
    ui->save_map_as_image_button->setEnabled(true);
    ui->open_map_visualization_button->setEnabled(true);
    ui->enter_heights_button->setEnabled(true);
    ui->update_map_button->setEnabled(true);
    ui->update_grid_button->setEnabled(true);
    ui->edit_grid_button->setEnabled(true);

    auto width_box{ ui->cell_width_spin_box };
    auto height_box{ ui->cell_height_spin_box };
    auto scale_box{ ui->scale_spin_box };
    emit width_box->valueChanged(width_box->value());
    emit height_box->valueChanged(height_box->value());
    emit scale_box->valueChanged(scale_box->value());

    emit createGrid(image_path);
}

void MainWindow::openMapButtonPressed()
{
    m_map_label->clear();
    m_map_label->setAlignment(Qt::AlignCenter);
    m_map_label->setPixmap(ui->map_label->pixmap(Qt::ReturnByValue));
    m_map_label->setScaledContents(true);
    m_map_label->show();
    m_map_label->activateWindow();
}

void MainWindow::saveMapAsExcelButtonPressed()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/map.xlsx",
                               tr("XLSX files (*.xlsx)"));
    if(dir.isEmpty()) return;

    emit saveMapAsExcel(dir);
}

void MainWindow::saveMapAsImageButtonPressed()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/map_image.jpeg",
                               tr("Images (*.png *.jpeg);;*.jpeg;;*.png"));
    if(dir.isEmpty()) return;

    auto map{ ui->map_label->pixmap(Qt::ReturnByValue) };
    map.scaled(screen()->size().width()* 2 / 3, screen()->size().height() * 2 / 3); // NOTE: do not change; 2/3 - scale ratio to save a distance unit

    if(!map.save(dir)) {
        QMessageBox msg;
        msg.setText(QString("Невозможно сохранить изображение.\nПожалуйста, попробуйте еще раз"));
        msg.exec();
    }
}

void MainWindow::openMapVisualizationButtonPressed()
{
    emit openMapVisualization();
}

void MainWindow::enterHeightsButtonPressed()
{
    auto table{ m_table_container->getTableWidget() };
    table->clear();
    emit setupTableWidget(table);
    m_table_container->show();
    m_table_container->activateWindow();
}

void MainWindow::saveMapInLabel(QPixmap pm)
{
    ui->map_label->clear();
    ui->map_label->setPixmap(pm);
    ui->map_label->resize(screen()->size().width() / 3 * 2, screen()->size().height() * 2 / 3); // NOTE: DO NOT CHANGE, 2/3 - scale ratio do save a distance unit
    ui->map_label->setScaledContents(true);
}

void MainWindow::updateFullMapButtonPressed()
{
    emit updateFullMap();
}

void MainWindow::updateGridButtonPressed()
{
    emit updateGrid();
}

void MainWindow::editGridButtonPressed()
{
    auto table{ m_table_container->getTableWidget() };
    table->clear();
    emit editGrid(table);
    m_table_container->show();
    m_table_container->activateWindow();
}


// public getters (methods)
[[nodiscard]] const QDoubleSpinBox* MainWindow::getCellWidthBox() const noexcept
{
    return ui->cell_width_spin_box;
}

[[nodiscard]] const QDoubleSpinBox* MainWindow::getCellHeightBox() const noexcept
{
    return ui->cell_height_spin_box;
}

[[nodiscard]] const QDoubleSpinBox* MainWindow::getScaleBox() const noexcept
{
    return ui->scale_spin_box;
}
