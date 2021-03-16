#include "paintingwidget.hpp"
#include "grid_handler_utilities.hpp"

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

    connect(scene, SIGNAL(markPositionChanged(const QPointF &)),
            this, SLOT(markPositionChanged(const QPointF &)));

    connect(scene, SIGNAL(getCurrentSourceIndex(int&)),
            this, SLOT(giveCurrentSourceIndex(int &)));
}

PaintingWidget::~PaintingWidget()
{
    delete m_painting_ui;
}


// public sltos
[[nodiscard]] QPixmap* PaintingWidget::getEdittedMapPixmap(QPixmap *pm) const
{
    if(!pm) {
        auto map{ new QPixmap(qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene())->getEdittedPixmap()) }; // WARNING: may throw; replace?
        return map;
    }

    *pm = qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene())->getEdittedPixmap();
    return pm;
}

[[nodiscard]] QImage* PaintingWidget::getMapImage(QImage* image) const
{
    if(!image) {
        auto map{ new QImage(m_map_image) }; // WARNING: may throw; replace
        return map;
    }

    *image = m_map_image;
    return image;
}

void PaintingWidget::setScenePixmap(const QPixmap &pm)
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    scene->clear();

    m_is_grid_drawn = false;
    m_is_change_made = false;

    m_painting_ui->source_name_combo_box->clear();

    auto scaled_pm = pm.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->addPixmap(scaled_pm);
    m_map_image = scaled_pm.toImage();

    emit imageChanged(m_map_image);
}

void PaintingWidget::prepareGraphicsView(const QString &image_path)
{
    auto scene{ m_painting_ui->map_editor_graphics_view->scene() };
    qobject_cast<PaintTableScene*>(scene)->clear();
    scene->clear();

    m_painting_ui->source_name_combo_box->clear();

    m_is_change_made = false;
    m_is_grid_drawn = false;

    while(!m_map_image.load(image_path)) {
        auto answer{ QMessageBox::question(this, QString("Повторить действие"), QString("Не удалось загрузить изображение. Попробовать снова?")) };
        if(answer == QMessageBox::Yes) {
            QString image_path = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));
            if(image_path.isEmpty()) return;
        }
    }
    m_painting_ui->map_editor_graphics_view->scene()->addPixmap(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    emit imageChanged(m_map_image);
}

void PaintingWidget::deleteLastMark(int source_index)
{
    qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene())->deleteLastMark(source_index);
    repaint();
}

void PaintingWidget::updateSources(int count, int index, SourceType type, const QString &name, const QPointF &pos)
{
    auto *source_combo_box{ m_painting_ui->source_name_combo_box };
    auto *type_combo_box{ m_painting_ui->source_type_combo_box };
    auto *scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    if(auto current_count{ source_combo_box->count() }; current_count < count) {
        source_combo_box->insertItem(index, name);

        if(pos.x() > 0.) {
            scene->insertSource(index, { fromRealMetres(pos.x()), fromRealMetres(pos.y()) });
        }
        else {
            scene->insertSource(index);
        }
    }
    else if(current_count > count) {
        source_combo_box->removeItem(index);
        scene->deleteSource(index);
    }
    else {
       source_combo_box->setItemText(index, name);
       scene->updateSource(index, type, { fromRealMetres(pos.x()), fromRealMetres(pos.y()) });
    }

    if(type == SourceType::Point) {
        type_combo_box->setCurrentIndex(0);
    }
    else {
        type_combo_box->setCurrentIndex(1);
    }
}


// private slots
void PaintingWidget::acceptChangesButtonPressed()
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    QPixmap pm{ showChangesButtonPressed(PaintStyle::lines) };

    emit imageChanged(pm.toImage());
    scene->QGraphicsScene::clear();
    scene->addPixmap(pm);
    close();

    const auto &marks{ scene->getMarks() };
    const auto nsources{ marks.size() };
    if(nsources == 0)   return;
    QVector<QVector<QPointF>> coordinates(nsources);
    QVector<QVector<QPoint>> indexes;
    for(int i{}; i < nsources; ++i) {
        const auto nmarks{ marks[i].size() };
        QVector<QPointF> tmp(nmarks);
        QVector<QPoint> tmp_index(nmarks);
        for(int j{}; j < nmarks; ++j) {
            tmp[j].setX(toRealMetres(marks[i][j].x()));
            tmp[j].setY(toRealMetres(marks[i][j].y()));

            emit findMark(i, tmp[j], &tmp_index[j]);
        }
        coordinates[i] = std::move(tmp);
    }
    emit updateCoordinates(coordinates, indexes);
}

void PaintingWidget::discardAllChangesButtonPressed()
{
    emit deleteGrid(); // deleting grid in GridHandler

    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };
    scene->clear();
    m_is_grid_drawn = false;
    m_is_change_made = false;

    scene->addPixmap(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    close();
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

void PaintingWidget::markPositionChanged(const QPointF &pos)
{
    repaint();
    emit findMark(m_painting_ui->source_name_combo_box->currentIndex(), pos);
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

QPixmap PaintingWidget::showChangesButtonPressed(PaintStyle style)
{
    auto scene{ qobject_cast<PaintTableScene*>(m_painting_ui->map_editor_graphics_view->scene()) };

    if(m_is_grid_drawn && !m_is_change_made) return scene->getEdittedPixmap();

    QPixmap pm(QPixmap::fromImage(m_map_image.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    emit createGrid(pm,
                    scene->getWaterObjectCoords(),
                    scene->getIslandsCoords(),
                    PaintTableScene::water_object_color,
                    PaintTableScene::line_width);
    scene->resetStashes(); // clear stashed stuff
    m_is_grid_drawn = true;
    scene->addPixmap(pm = scene->paintContentOnMap(pm, style));
    m_is_change_made = false;

    return pm;
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


// overriden functions
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


// private functions
void PaintingWidget::setupConnectionsWithCellScaleParametersWidget()
{
    connect(m_cell_scale_parameters_ui->save_changes_button_box, SIGNAL(clicked(QAbstractButton *)),
            this, SLOT(saveChangesButtonClicked(QAbstractButton *)));

    connect(m_painting_ui->update_grid_button, SIGNAL(pressed()),
            this, SLOT(updateGridButtonPressed()));
}

void PaintingWidget::repaint()
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
