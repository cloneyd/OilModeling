#include "mainwindow.hpp"

#include <QTableWidgetItem>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_deeps_table_container{},
      m_xwind_table_container{},
      m_ywind_table_container{},
      m_visualization_container{}
{
    ui->setupUi(this);

    ui->display_info_tool_box->setCurrentIndex(0);
    ui->main_panel_tab_widget->setCurrentIndex(0);

    ui->map_editor_graphics_view->setScene(new PaintTableScene(ui->map_editor_graphics_view));

    //FIXME:
    ui->map_web_engine->load(QUrl("http://www.google.ru/maps/@59.9448043,30.3622528,9.83z"));
    ui->map_web_engine->setFocus();
    ui->map_web_engine->show();

    ui->relief_tab_page->addTab(&m_visualization_container, QString("3D Объект"));
    ui->relief_tab_page->addTab(&m_deeps_table_container, QString("Таблица глубин"));
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
    auto& ywind_table{ m_xwind_table_container.getTableWidget() };
    deep_table.clearContents();
    xwind_table.clearContents();
    ywind_table.clearContents();

    deep_table.setRowCount(rows);
    deep_table.setColumnCount(cols);
    xwind_table.setRowCount(rows);
    xwind_table.setColumnCount(cols);
    ywind_table.setRowCount(rows);
    ywind_table.setColumnCount(cols);

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

    ui->map_editor_graphics_view->scene()->addPixmap(getPixmapFromWebEngine());
}

void MainWindow::loadFromPCButtonPressed()
{
    emit ui->scale_spin_box->valueChanged(ui->scale_spin_box->value()); // updating values in other classes
    emit ui->cell_width_spin_box->valueChanged(ui->cell_width_spin_box->value()); // updating values in other classes
    emit ui->cell_height_spin_box->valueChanged(ui->cell_height_spin_box->value()); // updating values in other classes

    QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
    if(image_path.isEmpty()) return;

    while(!m_map_image.load(image_path)) {
        auto answer{ QMessageBox::question(this, QString("Повторить действие"), QString("Не удалось загрузить изображение. Повторить действие?")) };
        if(answer == QMessageBox::Yes) {
            QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
            if(image_path.isEmpty()) return;
        }
    }


    ui->edit_image_button->setEnabled(true);
    auto scene{ ui->map_editor_graphics_view->scene() };
    auto width{ ui->map_editor_graphics_view->size().width() };
    auto height{ ui->map_editor_graphics_view->size().height() };

    scene->addPixmap(QPixmap::fromImage(m_map_image)/*.scaled(width - 4., height - 4.)*/);
    //scene->setSceneRect(4., 4., width - 4., height - 4.); // implicit casts
    ui->map_editor_graphics_view->setAlignment(Qt::AlignCenter);

    ui->display_info_tool_box->setCurrentIndex(1);
}

void MainWindow::editImageButtonPressed()
{
    ui->map_editor_graphics_view->setEnabled(true);
    ui->display_info_tool_box->setCurrentIndex(1); // 1 - magic number which means a "painting page"

    ui->discard_last_changes_button->setEnabled(true);
    ui->return_last_changes_button->setEnabled(true);
    ui->accept_changes_button->setEnabled(true);
    ui->discard_all_changes_button->setEnabled(true);
    ui->save_changes_button_box->setEnabled(true);
}

void MainWindow::saveButtonBoxClicked(QAbstractButton *btn)
{
    auto scene{ qobject_cast<PaintTableScene*>(ui->map_editor_graphics_view->scene()) };
    if(ui->save_changes_button_box->standardButton(btn) == QDialogButtonBox::Ok) {
        // FIXME: work with buffer is should be here
        auto pm{ getPixmapFromScene() };
        emit createGrid(pm, scene->getWaterObjectCoords(), scene->getIslandsCoords());
        scene->clear();
        scene->addPixmap(pm);
        m_map_image = pm.toImage();
    }
    else {
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(m_map_image));
    }

    ui->map_editor_graphics_view->setEnabled(false);
    ui->discard_last_changes_button->setEnabled(false);
    ui->return_last_changes_button->setEnabled(false);
    ui->accept_changes_button->setEnabled(false);
    ui->discard_all_changes_button->setEnabled(false);
    ui->save_changes_button_box->setEnabled(false);
}


// private functions
QPixmap MainWindow::getPixmapFromScene() const
{
    auto scene{ui->map_editor_graphics_view->scene()};
    scene->clearSelection();   // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect()); // Reshrink the scene to it's bounding contents
    QPixmap pixmap(scene->sceneRect().size().toSize()); // WARNING: may throw; Create the image with the exact size of the shrunk scene

    QPainter painter(&pixmap);
    scene->render(&painter);
    return pixmap;
}

QPixmap MainWindow::getPixmapFromWebEngine() const
{
    auto web_engine{ ui->map_web_engine };
    QPixmap pixmap(web_engine->size()); // WARNING: may throw; Create the image with the exact size of the shrunk scene

    QPainter painter(&pixmap);
    web_engine->render(&painter);
    return pixmap;
}
