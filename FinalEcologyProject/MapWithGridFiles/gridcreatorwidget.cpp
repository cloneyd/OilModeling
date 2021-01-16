#include "gridcreatorwidget.hpp"
#include "ui_gridcreatorwidget.h"

#include <QMessageBox>
#include <QScreen>
#include <QPainter>
#include <QImage>
#include <algorithm>

// Ctors and dtor
GridCreatorWidget::GridCreatorWidget(QWidget *parent) :
    QWidget(parent),
    m_cell_width{},
    m_cell_height{},
    m_scale{},
    m_image_filepath{},
    m_grid{},
    ui(new Ui::GridCreatorWidget) // WARNING: may throw; should be replaced
{
    ui->setupUi(this);
    ui->graphics_view->setScene(new PaintTableScene(ui->graphics_view)); // WARNING: may throw; should be replaced
}

GridCreatorWidget::~GridCreatorWidget()
{
    delete ui;
}


// public slots
void GridCreatorWidget::updateCellWidth(double width) noexcept
{
    m_cell_width = width;
}

void GridCreatorWidget::updateCellHeight(double height) noexcept
{
    m_cell_height = height;
}

void GridCreatorWidget::updateScale(double scale) noexcept
{
    m_scale = scale;
}

void GridCreatorWidget::createGridArea(const QString &image_filepath)
{
    m_grid.clear();

    m_image_filepath = std::move(const_cast<QString&>(image_filepath)); // WARNING: const_cast
    QImage map_image;
    if(!map_image.load(m_image_filepath)){
        QMessageBox msgBox;
        msgBox.setText(QString("Не удалось загрузить изображение.\nПожалуйста, попробуйте еще раз"));
        msgBox.exec();
        return;
    }

    if(m_cell_width < 1e-4) {
        QMessageBox msgBox;
        msgBox.setText(QString("Не удалось постоить сетку.\nПожалуйста, проверьте ширину ячейки и попробуйте еще раз"));
        msgBox.exec();
        return;
    }

    if(m_cell_height < 1e-4) {
        QMessageBox msgBox;
        msgBox.setText(QString("Не удалось постоить сетку.\nПожалуйста, проверьте высоту ячейки и попробуйте еще раз"));
        msgBox.exec();
        return;
    }


    if(m_scale < 1e-4) {
        QMessageBox msgBox;
        msgBox.setText(QString("Не удалось постоить сетку.\nПожалуйста, проверьте масштаб и попробуйте еще раз"));
        msgBox.exec();
        return;
    }

    const auto width{ screen()->size().width() * 3 / 4 };
    const auto height{ screen()->size().height() * 3 / 4 };
    setFixedSize(width, height);

    // view setup
    auto scene{ ui->graphics_view->scene() };
    scene->addPixmap(QPixmap::fromImage(map_image.scaled(width - 4, height - 4)));
    scene->setSceneRect(4., 4., width - 4., height - 4.); // implicit casts
    ui->graphics_view->setFixedSize(width, height);
    ui->graphics_view->setMaximumSize(width, height);
    // FIXME: graphics view scale problem

    setWindowTitle(QString("Нарисуйте область"));
    show();


}

void GridCreatorWidget::updateGridArea()
{
    m_grid.clear();
    qobject_cast<PaintTableScene*>(ui->graphics_view->scene())->clear();
    createGridArea(m_image_filepath);
}


// protected overridden functions
void GridCreatorWidget::closeEvent(QCloseEvent *event)
{
    gridCreation(); // create the grid

    // create the image with grid
    QPixmap pixmap{std::move(getPixmapFromScene())};
    QPainter painter;

    painter.begin(&pixmap);
    painter.setPen(Qt::darkRed);
    auto grid_size{m_grid.size()};
    auto realscale{screen()->physicalDotsPerInch() / 2.54 / m_scale }; // number of real units in one conventional unit
    auto cell_width{ realscale * m_cell_width };
    auto cell_height{realscale * m_cell_height };
    for(int i{}; i < grid_size; ++i){
        auto size {m_grid[i].size()};
        for(int j{}; j < size; ++j) {
            if(m_grid[i][j].first) {
                auto x{ m_grid[i][j].second.x() };
                auto y{ m_grid[i][j].second.y() };
                painter.drawLines({ QLineF(m_grid[i][j].second, QPointF(x + cell_width, y)),
                                    QLineF(QPointF(x + cell_width, y), QPointF(x + cell_width, y + cell_height)),
                                    QLineF(QPointF(x + cell_width, y + cell_height), QPointF(x, y + cell_height)),
                                    QLineF(QPointF(x, y + cell_height), m_grid[i][j].second)});
            }
        }
    }
    painter.end();

    qobject_cast<PaintTableScene*>(ui->graphics_view->scene())->clear();
    emit saveMapInLabel(pixmap);
    emit gridChanged(m_grid);
    event->accept();
}


// private methods
void GridCreatorWidget::gridCreation()
{
    const auto& points{ qobject_cast<PaintTableScene*>(ui->graphics_view->scene())->getAreaPoints() }; // ref to scene points (user drawn stuff)

    auto npoints = points.size();
    if(npoints == 0) return;

    auto xmin{ points[0].x() };
    auto xmax{ xmin };
    auto ymin{ points[0].y() };
    auto ymax{ ymin };

    for(int i{1}; i < npoints; ++i){
        auto x{ points[i].x() };
        auto y{ points[i].y() };

        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    double realscale = screen()->physicalDotsPerInch() / 2.54 / m_scale;
    auto cell_width{ realscale * m_cell_width };
    auto cell_height{ realscale * m_cell_height };
    for(auto y{ ymin }; ymax - y > 0; y += cell_height){
        QVector<QPair<bool, QPointF>> tmp;
        for(auto x{ xmin }; xmax - x > 0; x += cell_width){
            tmp.append(qMakePair(true, QPointF(x, y)));
        }
        m_grid.append(std::move(tmp));
    }

    //extraCellsDeletion();
}

QPixmap GridCreatorWidget::getPixmapFromScene()
{
    auto scene{ui->graphics_view->scene()};
    scene->clearSelection();   // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect()); // Reshrink the scene to it's bounding contents
    QPixmap pixmap(scene->sceneRect().size().toSize()); // WARNING: may throw; Create the image with the exact size of the shrunk scene

    QPainter painter(&pixmap);
    scene->render(&painter);
    return pixmap;
}

void GridCreatorWidget::extraCellsDeletion()
{
    auto rows {m_grid.size() };

    QVector<QPointF> area { qobject_cast<PaintTableScene*>(ui->graphics_view->scene())->getAreaPoints() };
    std::sort(area.begin(), area.end(), [](QPointF first, QPointF second) {return (first.y() - second.y()) < 0.; }); // WARNING: floating point number comparation)

    auto cell_height = screen()->physicalDotsPerInch() / 2.54 / m_scale * m_cell_height;
    auto y { m_grid[0][0].second.y() };
    auto area_size{ area.size() };
    QVector<QPointF> lines(rows * 2);
    double max{ -1. };
    double min{ 1e+5 };
    for(int i{}, j{}; i < area_size && j < rows * 2; ++i) {
        if(y - area[i].y() < -.5) {
            y += cell_height;
            lines[j] = QPointF(min, y);
            lines[j + 1] = QPointF(max, y);
            j += 2;
            min = 1e+5;
            max = - 1;
            continue;
        }

        if(area[i].x() < min) min = area[i].x();
        else if( area[i].x() > max) max = area[i].x();
    }

    QVector<QPair<int, QVector<QPoint>>> new_grid(rows);
    for(int i{}; i < rows; ++i) {
        auto cols{ m_grid[i].size() };
        for(int j{}; j < cols; ++j) {
            m_grid[i][j].first = isBelongsToArea(m_grid[i][j].second, lines);
        }
    }
}

bool GridCreatorWidget::isBelongsToArea(const QPointF &value, const QVector<QPointF> &vector)
{
//     auto cell_width = screen()->physicalDotsPerInch() / 2.54 / m_scale * m_cell_width;
//     auto cell_height = screen()->physicalDotsPerInch() / 2.54 / m_scale * m_cell_height;

//     auto size{ vector.size() };
//     for(int i{}; i < size; i += 2) {
//         auto x{ value.x() };
//         auto y{ value.y() };
//         auto left_x{ vector[i].x() };
//         auto left_y{ vector[i].y() };
//         auto right_x{ vector[i + 1].x() };
//         auto right_y{ vector[i + 1].y() };
//         if(!((x >= left_x && y >= left_y && x <= right_x && y <= right_y) ||
//              (x + cell_width >= left_x && y >= left_y && x + cell_width <= right_x && y <= right_y)) ||
//              (x >= left_x && y + cell_height >= left_y && x <= right_x && y + cell_height <= right_y) ||
//              (x + cell_width >= left_x && y + cell_height >= left_y && x + cell_width <= right_x && y + cell_height <= right_y)) {
//             return false;
//         }
//     }
//     return true;
    return true;
}
