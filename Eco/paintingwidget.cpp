#include "paintingwidget.hpp"
#include "ui_paintingwidget.h"
#include  "painttablescene.hpp"

#include <QScreen>
#include <QFileDialog>
#include <QMessageBox>

PaintingWidget::PaintingWidget(QWidget *parent) :
    QWidget(parent),
    m_painting_ui(new Ui::PaintingWidget),
    m_cell_scale_parameters_ui( new Ui::cell_scale_parametres),
    m_map_image{},
    m_cell_scale_parameters{},
    m_is_accept_changes_flag{ true },
    m_is_grid_drawn{}
{
    m_painting_ui->setupUi(this);
    m_cell_scale_parameters_ui->setupUi(&m_cell_scale_parameters);

    setWindowTitle("Панель рисования");
    m_cell_scale_parameters.setWindowTitle("Панель параметров");

    setupConnectionsWithCellScaleParametersWidget();

    setGeometry(10, 35, screen()->size().width() - 20, screen()->size().height() - 45);

    m_painting_ui->map_editor_graphics_view->setScene(new PaintTableScene(m_painting_ui->map_editor_graphics_view));
    const auto width{ screen()->size().width() * image_scale_ratio };
    const auto height{ screen()->size().height() * image_scale_ratio };
    m_painting_ui->map_editor_graphics_view->setFixedSize(width, height);

    // view setup
    auto scene{ m_painting_ui->map_editor_graphics_view->scene() };
    scene->setSceneRect(0., 0., width, height); // implicit casts
    m_painting_ui->map_editor_graphics_view->setFixedSize(width, height);
    m_painting_ui->map_editor_graphics_view->setMaximumSize(width, height);
    m_painting_ui->map_editor_graphics_view->setAlignment(Qt::AlignCenter);
}

PaintingWidget::~PaintingWidget()
{
    delete m_painting_ui;
}


// public slots
void PaintingWidget::acceptChangesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    auto pm{ getEdittedMapPixmap() };

    if(m_is_accept_changes_flag) {
        emit createGrid(pm, scene->getWaterObjectCoords(), scene->getIslandsCoords(), PaintTableScene::water_object_color);
    }

    m_map_image = pm.toImage();
    emit imageChanged(m_map_image);

    close(); // set some flags;
}

void PaintingWidget::discardAllChangesButtonPressed()
{
    emit deleteGrid(); // deleting grid in GridHandler
    close(); // set some flags;
}

// setters
void PaintingWidget::setScenePixmap(const QPixmap &pm)
{
    auto scene{ m_painting_ui->map_editor_graphics_view->scene() };
    auto scaled_pm = pm.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->addPixmap(scaled_pm);
    m_map_image = scaled_pm.toImage();

    emit imageChanged(m_map_image);
}

void PaintingWidget::updateMapButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    scene->clear();

    m_is_accept_changes_flag = true;
    m_is_grid_drawn = false;

    scene->addPixmap(QPixmap::fromImage(m_map_image));
}

void PaintingWidget::discardLastChandesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene() ) };
    if(scene->getNumberOfChanges() == 0)    return;

    if(m_is_grid_drawn) {
        auto answer{ QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы уверены, что хотите убрать изменения?\nЭто уничтожит сетку")) };
        if(answer == QMessageBox::No)   return;

        emit deleteGrid();
        m_is_grid_drawn = false;
    }

    scene->hideToStash(); // hiding last change to stash
    scene->QGraphicsScene::clear(); // clear graphics content
    scene->addPixmap(drawAreasInMap());
}

void PaintingWidget::returnLastChangesButtonPressed()
{    
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene() ) };
    if(scene->getNumberOfStashedChanges() == 0)    return;

    if(m_is_grid_drawn) {
        auto answer {QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы уверены, что хотите вернуть изменения?\nЭто уничтожит сетку")) };
        if(answer == QMessageBox::No) return;

        emit deleteGrid();
        m_is_grid_drawn = false;
    }

    scene->getFromStash(); // get last change from stash
    scene->QGraphicsScene::clear(); // clear graphics content
    scene->addPixmap(drawAreasInMap());
}

void PaintingWidget::showChangesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    // FIXME: work with buffer is should be here
    auto pm{ drawAreasInMap() };
    emit createGrid(pm, scene->getWaterObjectCoords(), scene->getIslandsCoords(), PaintTableScene::water_object_color);
    m_is_grid_drawn = true;
    scene->addPixmap(pm);
    m_is_accept_changes_flag = false;
}

// FIXME
void PaintingWidget::brushType1ButtonPressed()
{
    // TODO
}

// FIXME
void PaintingWidget::brushType2ButtonPressed()
{
   // TODO
}

// FIXME
void PaintingWidget::brushType3ButtonPressed()
{
    // TODO
}

// FIXME
void PaintingWidget::brushType4ButtonPressed()
{
    // TODO
}

void PaintingWidget::updateGridButtonPressed()
{
    m_cell_scale_parameters.show();
    m_cell_scale_parameters.activateWindow();
}

// FIXME
void PaintingWidget::enableGridButtonPressed()
{
    // TODO
}

// FIXME
void PaintingWidget::shadowNonWOButtonPressed()
{
    // TODO
}

void PaintingWidget::saveChangesButtonClicked(QAbstractButton *btn)
{
    if(m_cell_scale_parameters_ui->save_changes_button_box->standardButton(btn) == QDialogButtonBox::Ok)
    {
        emit cellScaleParametersChanged(m_cell_scale_parameters_ui->cell_width_double_spin_box->value(),
                                        m_cell_scale_parameters_ui->cell_height_double_spin_box->value(),
                                        m_cell_scale_parameters_ui->scale_double_spin_box->value());
        showChangesButtonPressed();
    }

    m_cell_scale_parameters.close();
}


// Getters
QPixmap PaintingWidget::getEdittedMapPixmap() const
{
    auto scene{ m_painting_ui->map_editor_graphics_view->scene() };
    scene->clearSelection();   // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect()); // Reshrink the scene to it's bounding contents
    QPixmap pixmap(scene->sceneRect().size().toSize()); // WARNING: may throw; Create the image with the exact size of the shrunk scene

    QPainter painter(&pixmap);
    scene->render(&painter);
    return pixmap;
}


// overridden functions
void PaintingWidget::closeEvent(QCloseEvent *event)
{
    close();
    QWidget::closeEvent(event);
}


// redefined functions
void PaintingWidget::close()
{
    auto scene{ m_painting_ui->map_editor_graphics_view->scene() };
    qobject_cast<PaintTableScene*>(scene)->clear();
    scene->addPixmap(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    m_is_accept_changes_flag = true;
    m_is_grid_drawn = false;
    QWidget::close();
}


// Public modificators
void PaintingWidget::prepareGraphicsView(const QString &image_path)
{
    while(!m_map_image.load(image_path)) {
        auto answer{ QMessageBox::question(this, QString("Повторить действие"), QString("Не удалось загрузить изображение. Попробовать снова?")) };
        if(answer == QMessageBox::Yes) {
            QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
            if(image_path.isEmpty()) return;
        }
    }
    auto* scene{ m_painting_ui->map_editor_graphics_view->scene() };
    m_painting_ui->map_editor_graphics_view->scene()->addPixmap(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    emit imageChanged(m_map_image);
}

void PaintingWidget::setupConnectionsWithCellScaleParametersWidget()
{
    connect(m_cell_scale_parameters_ui->save_changes_button_box, SIGNAL(clicked(QAbstractButton *)),
            this, SLOT(saveChangesButtonClicked(QAbstractButton *)));

    connect(m_painting_ui->update_grid_button, SIGNAL(pressed()),
            this, SLOT(updateGridButtonPressed()));
}

QPixmap PaintingWidget::drawAreasInMap()
{
    auto* scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    QPixmap pm(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    auto&& water_object{ scene->getWaterObjectCoords() };
    auto wo_size{ water_object.size() };

    auto&& islands{ scene->getIslandsCoords() };
    auto islands_size{ islands.size() };

    auto line_width{ PaintTableScene::line_width };
    QPainter painter(&pm);
    painter.setPen(Qt::NoPen);
    painter.setBrush(PaintTableScene::water_object_color);
    for(int i{ }; i < wo_size; ++i) {
        painter.drawEllipse(water_object[i].x(), water_object[i].y(), line_width, line_width);
    }

    painter.setBrush(PaintTableScene::islands_color);
    for(int i{ }; i < islands_size; ++i){
        painter.drawEllipse(islands[i].x(), islands[i].y(), line_width, line_width);
    }

    return pm;
}
