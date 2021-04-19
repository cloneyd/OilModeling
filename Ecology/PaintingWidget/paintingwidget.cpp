// current project
#include "paintingwidget.hpp"

PaintingWidget::PaintingWidget(QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent, flags),
    m_map_pixmap{},
    m_actions_buf{},
    m_stashed_actions{},
    m_source_indexes_buffer{},
    m_stashed_indexes{},
    m_sources_types_buf{},
    m_is_ctrl_held{},
    m_is_grid_created{},
    m_is_update_required{},
    m_grid_parameters_widget{},
    m_ui{ std::make_unique<Ui::PaintingWidget>() }, // WARNING: throws
    m_grid_parameters_ui{ std::make_unique<Ui::GridParameters>() }, // WARNING: throws,
    m_scene{ std::make_unique<PaintTableScene>() } // WARNING: throws
{
    m_ui->setupUi(this);
    m_grid_parameters_ui->setupUi(&m_grid_parameters_widget);

    setGeometry(10, 35, screen()->size().width() - 20, screen()->size().height() - 45);

    m_ui->map_editor_graphics_view->setScene(m_scene.get());
    const auto width{ screen()->size().width() * s_image_width_aspect_ratio };
    const auto height{ screen()->size().height() * s_image_height_aspect_ratio };
    m_ui->map_editor_graphics_view->setFixedSize(width, height);

    // view setup
    m_scene->setSceneRect(0., 0., width, height);
    m_ui->map_editor_graphics_view->setFixedSize(width, height);
    m_ui->map_editor_graphics_view->setAlignment(Qt::AlignCenter);

    setupGridParametersConnections();
    setupPaintTableSceneConnections();
    setupUiConnections();
}


// public slots
void PaintingWidget::setImage(QPixmap &image)
{
    // clear last content
    clearContent();

    image = image.scaled(m_scene->width(), m_scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_scene->addPixmap(image);
    m_map_pixmap = image;

    emit deleteGrid();
    m_is_grid_created = false;
    m_is_update_required = false;
    emit resetSources();
    emit imageChanged(m_map_pixmap, m_is_grid_created);
}

void PaintingWidget::setImage(const QString &filepath, bool *operation_status)
{
    QPixmap pm;
    if(!pm.load(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось загрузить изображение.\nПопробуйте еще раз");
        if(operation_status)    *operation_status = false;
        return;
    }

    clearContent();
    pm = pm.scaled(m_scene->width(), m_scene->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_scene->addPixmap(pm);
    m_map_pixmap = std::move(pm);

    emit deleteGrid();
    m_is_grid_created = false;
    m_is_update_required = false;
    emit resetSources();
    emit imageChanged(m_map_pixmap, m_is_grid_created);

    if(operation_status)    *operation_status = true;
}

/*void PaintingWidget::saveEdittedMapInFile(const QString &filepath, bool *operation_status)
{
    QPixmap pm(m_scene->sceneRect().size().toSize());
    QPainter painter;
    painter.begin(&pm);
    (m_scene->render(&painter));
    painter.end();

    if(!pm.save(filepath)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось сохранить изображение по данному пути.\nПожалуйста, проверьте путь и повторите попытку");
        if(operation_status)    *operation_status = false;
        return;
    }
    if(operation_status)    *operation_status = true;
}*/

void PaintingWidget::deleteSource(int source_index)
{
    Q_ASSERT_X(source_index < m_ui->source_name_combo_box->count(),
               "Class PaintingWidget", "Function - deleteSource, problem - invalid index");
    // clear action log and stashes
    deleteSourceChanges(source_index);
    clearStashes();

    // delete source
    m_ui->source_name_combo_box->removeItem(source_index);
    m_sources_types_buf.remove(source_index);
    m_scene->deleteSource(source_index);

    // repaint
    repaintScene(PaintStyle::Ellipse);
}

void PaintingWidget::appendNewSource(const PointSource &source)
{
    // first point always adds to the end
    m_sources_types_buf.append(SourceType::PointSource); // must be before addItem
    m_ui->source_name_combo_box->addItem(source.m_name);
    m_ui->source_type_combo_box->setCurrentIndex(0);
    m_ui->source_name_combo_box->setCurrentIndex(m_ui->source_name_combo_box->count() - 1); // implicitely emits signal
    m_actions_buf.push_back(ActionMakers::mark);
    m_source_indexes_buffer.push_back(m_ui->source_name_combo_box->count() - 1);
    // clear stashes
    clearStashes();

    QPointF pixpoint(toPixels(source.m_x), toPixels(source.m_y));
    if(m_is_grid_created && source.m_x > 0. && source.m_y > 0.) {
        QPoint indexes{};
        emit findMark(pixpoint, &indexes);
        if(indexes.x() < 0) {
            QMessageBox::warning(nullptr, "Предупреждение", "Источник \"" + source.m_name +
                                 "\" находится вне водного объекта.\nЗаданные координаты не будут учтены");
            m_scene->appendSourceMarks(QVector<QPointF>{});
            updateSourcesCoordinates(); // make coordinates invalid
            // deleting last action
            m_actions_buf.pop_back();
            m_source_indexes_buffer.pop_back();
            return;
        }
    }

    m_scene->appendSourceMarks(QVector{ pixpoint }); // no updateCoordinates is needed
    // repaint scene content
    repaintScene(PaintStyle::Ellipse);

    actionMadeCheck();
    // FIXME: sync()
}

void PaintingWidget::appendNewSource(const DiffusionSource &source)
{
    appendNewSource(static_cast<const PointSource&>(source));
    m_sources_types_buf.back() = SourceType::DiffusionSource;
    m_ui->source_type_combo_box->setCurrentIndex(1);
    // FIXME: sync()
}

void PaintingWidget::updateSource(int source_index, const PointSource &source)
{
    // if point coordinates invalid - only updates name and type and reset coordinates update
    Q_ASSERT_X(source_index < m_ui->source_name_combo_box->count(),
               "Class PaintingWidget", "Function - updateSource (PointSource), problem - invalid index");
    // updating name and type
    m_ui->source_name_combo_box->setCurrentIndex(source_index); // implicitely emits signal
    m_sources_types_buf[source_index] = SourceType::PointSource;
    m_ui->source_name_combo_box->setItemText(source_index, source.m_name);
    m_ui->source_type_combo_box->setCurrentIndex(0);

    // try to update coordinates
    if((std::fabs(source.m_x)) - 1. < 1e-4) {
        updateSourcesCoordinates(); // reset last coordinates changes
        return;
    }
    QPointF pixpoint(toPixels(source.m_x), toPixels(source.m_y));
    if(m_is_grid_created) {
        QPoint indexes{};
        emit findMark(pixpoint, &indexes);
        if(indexes.x() < 0) {
            QMessageBox::warning(nullptr, "Предупреждение", "Источник \"" + source.m_name +
                                 "\" находится вне водного объекта.\nЗаданные координаты не будут учтены");
            updateSourcesCoordinates(); // reset last coordinates changes
            return;
        }
    }

    // update actions log
    deleteSourceChanges(source_index); // deleting all previous action buffer information about this source
    m_actions_buf.push_back(ActionMakers::mark);
    m_source_indexes_buffer.push_back(source_index);
    // clear stashes
    clearStashes();

    // clears previous points
    m_scene->applySourceMarks(source_index, QVector{ pixpoint });
    //repaint scene content
    repaintScene(PaintStyle::Ellipse);

    actionMadeCheck();
    // FIXME: sync()
}

void PaintingWidget::updateSource(int source_index, const DiffusionSource &source)
{
    updateSource(source_index, static_cast<const PointSource&>(source));
    m_ui->source_type_combo_box->setCurrentIndex(1);
    m_sources_types_buf[source_index] = SourceType::DiffusionSource;
    // FIXME: sync()
}

void PaintingWidget::saveState(QTextStream &stream, const char delim)
{
    // m_grid_parameters_widget{} will be setted up by MainWindow::restoreState
    m_scene->saveState(stream, delim);

    auto writeToFileCasted = [&stream](const auto &container, const char delim) {
        stream << container.size() << delim;
        for(const auto &entity : container) {
            stream << static_cast<int>(entity) << '\t';
        }
        stream << delim; // control delim
    };

    auto writeToFile = [&stream](const auto &container, const char delim) {
        stream << container.size() << delim;
        for(const auto &entity : container) {
            stream << entity << '\t';
        }
        stream << delim; // control delim
    };

    writeToFileCasted(m_actions_buf, delim);
    writeToFileCasted(m_stashed_actions, delim);
    writeToFile(m_source_indexes_buffer, delim);
    writeToFile(m_stashed_indexes, delim);
    writeToFileCasted(m_sources_types_buf, delim);

    stream << m_is_ctrl_held << delim;
    stream << m_is_grid_created << delim;
    stream << m_is_update_required << delim;

    stream << delim; // control delim
}
void PaintingWidget::restoreState(QTextStream &stream, const char delim)
{
    // m_grid_parameters_widget{} will be setted up by MainWindow::restoreState
    m_scene->restoreState(stream, delim);

    auto readUntilDelim = [&stream](const char delim) -> QString {
        QString result{};
        char sym{};
        for(stream >> sym; sym != delim; stream >> sym) {
            result += sym;
        }
        return result;
    };

    auto readActionMakersFromFile = [&readUntilDelim, &stream](auto &container, const char delim) {
        stream << container.size() << delim;
        bool is_converted{};
        const auto container_size{ readUntilDelim(delim).toInt(&is_converted) };
        Q_ASSERT(is_converted);
        container.resize(container_size);

        for(auto &entity : container) {
            entity = static_cast<ActionMakers>(readUntilDelim('\t').toInt(&is_converted));
            Q_ASSERT(is_converted);
            Q_ASSERT(entity >= ActionMakers::MIN && entity <= ActionMakers::MAX);
        }
        char ctrl_delim{};
        stream >> ctrl_delim;
        Q_ASSERT(ctrl_delim == delim);
    };

    auto readSourceTypesFromFile = [&readUntilDelim, &stream](auto &container, const char delim) {
        stream << container.size() << delim;
        bool is_converted{};
        const auto container_size{ readUntilDelim(delim).toInt(&is_converted) };
        Q_ASSERT(is_converted);
        container.resize(container_size);

        for(auto &entity : container) {
            entity = static_cast<SourceType>(readUntilDelim('\t').toInt(&is_converted));
            Q_ASSERT(is_converted);
            Q_ASSERT(entity >= SourceType::MIN && entity <= SourceType::MAX);
        }
        char ctrl_delim{};
        stream >> ctrl_delim;
        Q_ASSERT(ctrl_delim == delim);
    };

    auto readFromFile = [&stream, &readUntilDelim](auto &container, const char delim) {
        bool is_converted{};
        const auto container_size{ readUntilDelim(delim).toInt(&is_converted) };
        Q_ASSERT(is_converted);
        container.resize(container_size);

        for(auto &entity : container) {
            entity = readUntilDelim('\t').toInt(&is_converted);
            Q_ASSERT(is_converted);
        }
        char ctrl_delim{};
        stream >> ctrl_delim;
        Q_ASSERT(ctrl_delim == delim);
    };

    readActionMakersFromFile(m_actions_buf, delim);
    readActionMakersFromFile(m_stashed_actions, delim);
    readFromFile(m_source_indexes_buffer, delim);
    readFromFile(m_stashed_indexes, delim);
    readSourceTypesFromFile(m_sources_types_buf, delim);

    bool is_converted{};
    m_is_ctrl_held = readUntilDelim(delim).toInt(&is_converted);
    Q_ASSERT(is_converted);

    m_is_grid_created = readUntilDelim(delim).toInt(&is_converted);
    Q_ASSERT(is_converted);

    m_is_update_required = readUntilDelim(delim).toInt(&is_converted);
    Q_ASSERT(is_converted);

    char ctrl_delim;
    stream >> ctrl_delim;
    Q_ASSERT(ctrl_delim == delim);

    repaintScene(PaintStyle::Lines);
    updateSourcesCoordinates();

    QPixmap pm{ m_scene->sceneRect().size().toSize() };
    QPainter painter(&pm);
    m_scene->render(&painter);
    emit imageChanged(pm, m_is_grid_created);
}


//private slots
void PaintingWidget::waterObjectChanged(ChangeType change_type)
{
    clearStashes();
    m_is_update_required = true;

    switch(change_type) {
    case ChangeType::Buffering:
        m_actions_buf.push_back(ActionMakers::water_object);
        break;

    case ChangeType::Deleted:
        deleteLastWOChange();
        break;

    default:
        return; // do nothing
    }

    actionMadeCheck();
}

void PaintingWidget::islandsChanged(ChangeType /*unused*/)
{
    m_is_update_required = true;
    clearStashes();
    m_actions_buf.push_back(ActionMakers::islands);
    actionMadeCheck();
}

void PaintingWidget::sourcesMarksChanged(ChangeType /*unused*/, const QPointF &pixel_pos)
{
    clearStashes();
    if(m_is_grid_created) { // if grid is created must check that new point belongs to grid
        QPoint indexes;
        findMark(pixel_pos, &indexes);

        if(indexes.x() < 0) { // if not belongs - delete it and not repaint
            QMessageBox::warning(nullptr, "Ошибка", "Заданная точка находится вне водного объекта.\nПоставьте точку в другое место");
            m_scene->deleteLastMark(m_ui->source_name_combo_box->currentIndex());
            return;
        }
    }

    if((m_actions_buf.back() != ActionMakers::grid && m_actions_buf.back() != ActionMakers::mark) || !m_is_grid_created) {
        m_is_update_required = true;
    }
    else {
        m_is_update_required = false;
    }
    // repaint
    repaintScene(PaintStyle::Lines);
    m_actions_buf.push_back(ActionMakers::mark);
    m_source_indexes_buffer.push_back(m_ui->source_name_combo_box->currentIndex());
    actionMadeCheck();
}

void PaintingWidget::gridParametersUpdateRejected()
{
    Q_ASSERT_X(m_grid_parameters_buffer.m_scale > 0., "Class PaintingWidget", "Function - gridParametersUpdateRejected, problem - invalid buffer");
    m_grid_parameters_ui->scale_double_spin_box->setValue(std::exchange(m_grid_parameters_buffer.m_scale, -1.));
    m_grid_parameters_ui->cell_width_double_spin_box->setValue(std::exchange(m_grid_parameters_buffer.m_cell_width, -1.));
    m_grid_parameters_ui->cell_height_double_spin_box->setValue(std::exchange(m_grid_parameters_buffer.m_cell_height, -1.));
    m_grid_parameters_widget.close();
}

void PaintingWidget::clearContentButtonPressed()
{
    clearContent();
    m_scene->addPixmap(m_map_pixmap);
    actionMadeCheck();
}

void PaintingWidget::returnButtonPressed()
{
    if(m_actions_buf.size() == 0)   return; // do nothing

    switch(m_actions_buf.back()) {
    case ActionMakers::grid:
        if(m_is_grid_created) {
            emit deleteGrid();
            m_is_grid_created = false;
            m_is_update_required = true;
            break;
        }
        else {
            emit createGrid(m_scene->getWaterObjectPoints(), m_scene->getIslandsPoints());
            m_is_grid_created = true;
            m_is_update_required = false;
            repaintScene(PaintStyle::Ellipse);
            return; // no work with buffer is needed
        }

    case ActionMakers::water_object:
        m_scene->hideLastWO();
        break;

    case ActionMakers::islands:
        m_scene->hideLastIsland();
        break;

    case ActionMakers::mark:
        m_scene->hideLastMark(m_source_indexes_buffer.back());
        m_stashed_indexes.push_back(m_source_indexes_buffer.back());
        m_source_indexes_buffer.pop_back();
        break;

    default:
        Q_ASSERT_X(false, "Class - PaintingWidget", "Function - returnButtonPressed, problem - bad action maker");
    }

    m_stashed_actions.push_back(std::move(m_actions_buf.back()));
    m_actions_buf.pop_back();
    actionMadeCheck();

    repaintScene(PaintStyle::Ellipse);
}

void PaintingWidget::forwardButtonPressed()
{
    if(m_stashed_actions.size() == 0)   return;

    switch(m_stashed_actions.back()) {
    case ActionMakers::grid:
        if(m_is_grid_created) {
            emit deleteGrid();
            m_is_grid_created = false;
            m_is_update_required = true;
            repaintScene(PaintStyle::Ellipse);
            return; // no work with buffer is needed
        }
        else {
            emit createGrid(m_scene->getWaterObjectPoints(), m_scene->getIslandsPoints());
            m_is_grid_created = true;
            m_is_update_required = false;
            break;
        }

    case ActionMakers::water_object:
        m_scene->returnFromWOStash();
        break;

    case ActionMakers::islands:
        m_scene->returnFromIslandsStash();
        break;

    case ActionMakers::mark:
        m_scene->returnFromMarksStash(m_stashed_indexes.back());
        m_source_indexes_buffer.push_back(m_stashed_indexes.back());
        m_stashed_indexes.pop_back();
        break;

    default:
        Q_ASSERT_X(false, "Class - PaintingWidget", "Function - forwardButtonPressed, problem - bad action maker");
    }

    m_actions_buf.push_back(std::move(m_stashed_actions.back()));
    m_stashed_actions.pop_back();
    actionMadeCheck();

    repaintScene(PaintStyle::Ellipse);
}

void PaintingWidget::changeGridParametersButtonPressed()
{
    m_grid_parameters_widget.show();
    m_grid_parameters_widget.activateWindow();
    m_grid_parameters_buffer = { m_grid_parameters_ui->scale_double_spin_box->value(),
                                 m_grid_parameters_ui->cell_width_double_spin_box->value(),
                                 m_grid_parameters_ui->cell_height_double_spin_box->value() };
}

void PaintingWidget::createGridButtonPressed(PaintStyle style)
{
    clearStashes();
    emit createGrid(m_scene->getWaterObjectPoints(), m_scene->getIslandsPoints());
    m_is_grid_created = true;
    m_is_update_required = false;
    repaintScene(style);

    m_actions_buf.push_back(ActionMakers::grid);
    actionMadeCheck();
}

void PaintingWidget::saveChangesButtonPressed()
{
    if(m_is_update_required || !m_is_grid_created) {
        createGridButtonPressed(PaintStyle::Lines);
    }
    else {
        repaintScene(PaintStyle::Lines);
    }

    updateSourcesCoordinates();

    QPixmap pm{ m_scene->sceneRect().size().toSize() };
    QPainter painter(&pm);
    m_scene->render(&painter);
    emit imageChanged(pm, m_is_grid_created);

    hide();
}

void PaintingWidget::discardChangesButtonPressed()
{
    clearContent();
    actionMadeCheck();
    if(m_is_grid_created){
        emit deleteGrid();
        m_is_grid_created = false;
    }

    updateSourcesCoordinates();
    m_scene->addPixmap(m_map_pixmap);
    emit imageChanged(m_map_pixmap, m_is_grid_created);
    close();
}

void PaintingWidget::sourceNameComboBoxIndexChanged(int index)
{
    switch(m_sources_types_buf[index]) {
    case SourceType::PointSource:
        m_ui->source_type_combo_box->setCurrentIndex(0);
        break;

    case SourceType::DiffusionSource:
        m_ui->source_type_combo_box->setCurrentIndex(1);
        break;

    default:
        return; // do nothing
    }
}



// overidden function
void PaintingWidget::closeEvent(QCloseEvent *event) /*override*/
{
    discardChangesButtonPressed();
    QWidget::closeEvent(event);
}

void PaintingWidget::keyPressEvent(QKeyEvent *event) /*override*/
{
    if(!isActiveWindow())    return;

    switch(event->key()) {
    case Qt::Key_Control:
        m_is_ctrl_held = true;
        break;

    case Qt::Key_Z:
        if(m_is_ctrl_held)  returnButtonPressed();
        break;

    case Qt::Key_Y:
        if(m_is_ctrl_held)  forwardButtonPressed();
        break;

    case Qt::Key_Enter:
    case Qt::Key_Return:
        saveChangesButtonPressed();
        break;

    case Qt::Key_Escape:
        discardChangesButtonPressed();
        break;
    }

    QWidget::keyPressEvent(event);
}

void PaintingWidget::keyReleaseEvent(QKeyEvent *event) /*override*/
{
    if(!isActiveWindow())    return;

    if(event->key() == Qt::Key_Control) {
        m_is_ctrl_held = false;
    }

    QWidget::keyReleaseEvent(event);
}


// private functions
void PaintingWidget::setupGridParametersConnections()
{
    connect(m_grid_parameters_ui->save_changes_button_box, SIGNAL(accepted()), // [1]
            this, SLOT(updateGridParameters()));

    connect(m_grid_parameters_ui->save_changes_button_box, SIGNAL(rejected()), // [1]
            this, SLOT(gridParametersUpdateRejected()));
}

void PaintingWidget::setupPaintTableSceneConnections()
{
    const auto *scene{ m_scene.get() };
    connect(scene, SIGNAL(woChanged(ChangeType)), // [1]
            this, SLOT(waterObjectChanged(ChangeType)));

    connect(scene, SIGNAL(islandChanged(ChangeType)), // [2]
            this, SLOT(islandsChanged(ChangeType)));

    connect(scene, SIGNAL(sourcesMarksChanged(ChangeType, const QPointF &)), // [3]
            this, SLOT(sourcesMarksChanged(ChangeType, const QPointF &)));

    connect(scene, SIGNAL(getCurrentSourceIndex(int &)), // [4]
            this, SLOT(giveCurrentSourceIndex(int &)));

    connect(scene, SIGNAL(getSourceType(int, SourceType &)), // [5]
            this, SLOT(giveSourceType(int, SourceType &)));
}

void PaintingWidget::setupUiConnections()
{
    connect(m_ui->clear_content_button, SIGNAL(pressed()), // [1]
            this, SLOT(clearContentButtonPressed()));

    connect(m_ui->return_button, SIGNAL(pressed()), // [2]
            this, SLOT(returnButtonPressed()));

    connect(m_ui->forward_button, SIGNAL(pressed()), // [3]
            this, SLOT(forwardButtonPressed()));

    connect(m_ui->change_grid_parameters_button, SIGNAL(pressed()), // [4]
            this, SLOT(changeGridParametersButtonPressed()));

    connect(m_ui->create_grid_button, SIGNAL(pressed()), // [5]
            this, SLOT(createGridButtonPressed()));

    connect(m_ui->save_changes_button, SIGNAL(pressed()), // [6]
            this, SLOT(saveChangesButtonPressed()));

    connect(m_ui->discard_changes_button, SIGNAL(pressed()), // [7]
            this, SLOT(discardChangesButtonPressed()));

    connect(m_ui->source_name_combo_box, SIGNAL(currentIndexChanged(int)), // [8]
            this, SLOT(sourceNameComboBoxIndexChanged(int)));
}

void PaintingWidget::clearContent()
{
    m_scene->clear();
    m_actions_buf.clear();
    m_stashed_actions.clear();
    m_source_indexes_buffer.clear();
    m_stashed_indexes.clear();
}

void PaintingWidget::clearStashes()
{
    m_scene->clearStashes();
    m_stashed_actions.clear();
    m_stashed_indexes.clear();
}

void PaintingWidget::actionMadeCheck()
{
    if(m_actions_buf.empty()) {
        m_ui->return_button->setEnabled(false);
    }
    else {
        m_ui->return_button->setEnabled(true);
    }

    if(m_stashed_actions.empty()) {
        m_ui->forward_button->setEnabled(false);
    }
    else {
        m_ui->forward_button->setEnabled(true);
    }
}

void PaintingWidget::deleteSourceChanges(int source_index)
{
    auto cur_source_iter{ --m_source_indexes_buffer.end() };
    auto remain_actions{ static_cast<int>(m_actions_buf.size()) };
    auto iter{ --m_actions_buf.end() };
    while(remain_actions > 1) {
        if(*iter == ActionMakers::mark) {
            if(*cur_source_iter == source_index) { // if source index and bufferized source index equal
                auto deleting_action_iter{ iter }; // deleting action
                --remain_actions;
                --iter;
                m_actions_buf.erase(deleting_action_iter);

                auto deleting_index_iter{ cur_source_iter }; // deleting index
                --cur_source_iter;
                m_source_indexes_buffer.erase(deleting_index_iter);
            }
            else { // skip this source
                --cur_source_iter;
            }
        }
        --iter;
        --remain_actions;
    }

    if(remain_actions > 0) {
        if(*cur_source_iter == source_index) {
            m_actions_buf.erase(iter);
            m_source_indexes_buffer.erase(cur_source_iter);
        }
    }
}

void PaintingWidget::deleteLastWOChange()
{
    auto action_iter{ --m_actions_buf.end() };
    auto remain_actions{ m_actions_buf.size() };
    while(remain_actions > 0) {
        if(*action_iter == ActionMakers::water_object) {
            m_actions_buf.erase(action_iter);
            return;
        }
        --remain_actions;
        --action_iter;
    }
}

void PaintingWidget::repaintScene(PaintStyle style)
{
    QPixmap pm{ m_map_pixmap };
    if(m_is_grid_created) emit drawGridOnPixmap(pm, PaintTableScene::s_wo_color, PaintTableSceneConstants::s_line_width);
    pm = m_scene->paintContent(pm, style);
    m_scene->QGraphicsScene::clear();
    m_scene->addPixmap(pm);
}

void PaintingWidget::updateSourcesCoordinates() const
{
    const auto& sources_marks{ m_scene->getSourcesMarks() };
    auto nsources{ sources_marks.size() };

    QVector<QVector<QPointF>> translated_marks(nsources);
    QVector<QVector<QPoint>> marks_indexes(nsources);

    auto type{ m_sources_types_buf.begin() };
    int tm_index{};
    for(const auto& marks_vector : sources_marks) {
        if(*type == SourceType::PointSource) {
            translated_marks[tm_index].resize(1);
            marks_indexes[tm_index].resize(1);
            translated_marks[tm_index][0] = { toMeters(marks_vector.back().x()), toMeters(marks_vector.back().y()) };
            emit findMark(marks_vector.back(), &marks_indexes[tm_index][0]);
        }
        else {
            int mark_index{};
            for(const auto& mark : marks_vector) {
                translated_marks[tm_index][mark_index] = { toMeters(mark.x()), toMeters(mark.y()) }; // converting to real meters
                emit findMark(mark, &marks_indexes[tm_index][mark_index]); // save point indexes in marks_indexes
                ++mark_index;
            }
        }
        ++tm_index;
    }

    emit sourcesCoordinatesChanged(translated_marks, marks_indexes);
}
