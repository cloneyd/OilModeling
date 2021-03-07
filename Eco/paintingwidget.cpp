#include "paintingwidget.hpp"
#include "ui_paintingwidget.h"

#include <QScreen>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>

PaintingWidget::PaintingWidget(QWidget *parent) :
    QWidget(parent),
    m_painting_ui(new Ui::PaintingWidget),
    m_cell_scale_parameters_ui( new Ui::cell_scale_parametres),
    m_map_image{},
    m_cell_scale_parameters{},
    m_is_grid_drawn{},
    m_is_ctrl_held{},
    m_is_change_made{}
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
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    scene->setSceneRect(0., 0., width, height); // implicit casts
    m_painting_ui->map_editor_graphics_view->setFixedSize(width, height);
    m_painting_ui->map_editor_graphics_view->setMaximumSize(width, height);
    m_painting_ui->map_editor_graphics_view->setAlignment(Qt::AlignCenter);

    connect(scene, SIGNAL(changeLogChanged(int)),
            this, SLOT(changeLogChanged(int)));

    connect(scene, SIGNAL(stashedChangeLogChanged(int)),
            this, SLOT(changeLogStashChanged(int)));

    connect(scene, SIGNAL(markPositionChanged(const std::list<QPointF> &)),
            this, SLOT(markPositionChanged()));
}

PaintingWidget::~PaintingWidget()
{
    delete m_painting_ui;
}


// private slots
void PaintingWidget::acceptChangesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    auto pm{ getEdittedMapPixmap() };

    if(!m_is_grid_drawn || m_is_change_made) {
        emit createGrid(pm,
                        scene->getWaterObjectCoords(),
                        scene->getIslandsCoords(),
                        scene->getMarkPosition(),
                        PaintTableScene::water_object_color,
                        PaintTableScene::line_width);
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

void PaintingWidget::changeLogChanged(int nwrites)
{
    if(nwrites == 0) {
        m_painting_ui->discard_last_changes_button->setEnabled(false);
    }
    else{
        m_painting_ui->discard_last_changes_button->setEnabled(true);
    }
    m_is_change_made = true;
}

void PaintingWidget::changeLogStashChanged(int nwrites)
{
    if(nwrites == 0) {
        m_painting_ui->return_last_changes_button->setEnabled(false);
    }
    else {
        m_painting_ui->return_last_changes_button->setEnabled(true);
    }
}

void PaintingWidget::markPositionChanged()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    QPixmap pm { QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)) };
    if(m_is_grid_drawn) {
        drawGridInPixmap(pm, PaintTableScene::water_object_color, PaintTableScene::line_width);
        scene->addPixmap(scene->paintContentOnMap(pm, PaintStyle::ellipse));
        return;
    }
    scene->addPixmap(scene->paintContentOnMap(pm, PaintStyle::lines));
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

    m_is_grid_drawn = false;

    scene->addPixmap(QPixmap::fromImage(m_map_image));
}

void PaintingWidget::discardLastChandesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene() ) };
    if(scene->getNumberOfChanges() == 0)    return;

    QPixmap pm { QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)) };
    if(m_is_grid_drawn && !m_is_change_made) {
        auto answer{ QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы уверены, что хотите убрать изменения?\nЭто уничтожит сетку")) };
        if(answer == QMessageBox::No)   return;

        emit deleteGrid();
        m_is_grid_drawn = false;
    }
    else {
        scene->hideToStash(); // hiding last change to stash
        emit drawGridInPixmap(pm, PaintTableScene::water_object_color, PaintTableScene::line_width);
    }

    scene->QGraphicsScene::clear(); // clear graphics content
    scene->addPixmap(scene->paintContentOnMap(pm, PaintStyle::lines));
}

void PaintingWidget::returnLastChangesButtonPressed()
{    
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene() ) };
    if(scene->getNumberOfStashedChanges() == 0)    return;

    QPixmap pm { QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)) };
    if(m_is_grid_drawn && !m_is_change_made) {
        auto answer {QMessageBox::question(this, QString("Подтвердите действие"), QString("Вы уверены, что хотите вернуть изменения?\nЭто уничтожит сетку")) };
        if(answer == QMessageBox::No) return;

        emit deleteGrid();
        m_is_grid_drawn = false;
    }
    else {
        scene->getFromStash(); // get last change from stash
        emit drawGridInPixmap(pm, PaintTableScene::water_object_color, PaintTableScene::line_width);
    }

    scene->QGraphicsScene::clear(); // clear graphics content
    scene->addPixmap(scene->paintContentOnMap(pm, PaintStyle::lines));
}

void PaintingWidget::showChangesButtonPressed(PaintStyle style)
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    if(m_is_grid_drawn && !m_is_change_made) return;

    QPixmap pm(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    emit createGrid(pm,
                    scene->getWaterObjectCoords(),
                    scene->getIslandsCoords(),
                    scene->getMarkPosition(),
                    PaintTableScene::water_object_color,
                    PaintTableScene::line_width);
    scene->resetStashes(); // clear stashed stuff
    m_is_grid_drawn = true;
    scene->addPixmap(scene->paintContentOnMap(pm, style));
    m_is_change_made = false;
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
    return qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene())->getEditedPixmap();
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
    m_is_change_made = false;
    m_is_grid_drawn = false;
    QWidget::close();
}

void PaintingWidget::keyPressEvent(QKeyEvent *event)
{
    if(!isActiveWindow()) return;

    switch(event->key()) {
    case Qt::Key_Control:
        m_is_ctrl_held = true;
        break;

    case Qt::Key_Z:
        if(m_is_ctrl_held)  discardLastChandesButtonPressed();
        break;

    case Qt::Key_Y:
        if(m_is_ctrl_held)  returnLastChangesButtonPressed();
        break;

    case Qt::Key_Enter:
    case Qt::Key_Return:
        acceptChangesButtonPressed();
        break;

    case Qt::Key_Escape:
        discardAllChangesButtonPressed();
        break;
    }

    QWidget::keyPressEvent(event);
}

void PaintingWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control) {
        m_is_ctrl_held = false;
    }

    QWidget::keyReleaseEvent(event);
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
