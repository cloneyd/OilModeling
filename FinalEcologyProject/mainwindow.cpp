#include "mainwindow.hpp"

#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>

// ctor and dtor
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui{ new Ui::MainWindow }, // WARNING: may throw; should be replaced
          m_map_label{ new QLabel } // WARNING: may throw; should be replaced
{
    ui->setupUi(this);

    setWindowTitle(QString("Hydropolution"));
    ui->water_object_type_combo_box->addItem(QString("Река"));
    ui->water_object_type_combo_box->addItem(QString("Озеро"));
}

MainWindow::~MainWindow()
{
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

void MainWindow::openMapVisualizationButtonPressed()
{
    emit openMapVisualization();
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


void MainWindow::enterHeightsButtonPressed()
{
    ui->enter_speed_vectors_button->setEnabled(true);
    emit displayDeepsTableWidget();
}

void MainWindow::enterSpeedVectorsButtonPressed()
{
    displaySpeedsTableWidget();
}

void MainWindow::updateFullMapButtonPressed()
{
    auto answer{ QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы деуйствительно хотите\nредактировать сетку?\nЭто удалит ранее введеные высоты")) };
    if(answer == QMessageBox::Yes) {
        emit updateFullMap();
    }
}

void MainWindow::updateGridButtonPressed()
{
    auto answer{ QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы деуйствительно хотите\nперестроить сетку?\nЭто удалит ранее введеные высоты")) };
    if(answer == QMessageBox::Yes) {
        emit updateGrid();
    }
}

void MainWindow::saveMapInLabel(QPixmap pm)
{
    ui->map_label->clear();
    ui->map_label->setPixmap(pm);
    ui->map_label->resize(screen()->size().width() / 3 * 2, screen()->size().height() * 2 / 3); // NOTE: DO NOT CHANGE, 2/3 - scale ratio do save a distance unit
    ui->map_label->setScaledContents(true);
}
