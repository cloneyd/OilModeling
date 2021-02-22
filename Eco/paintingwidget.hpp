#ifndef PAINTINGWIDGET_HPP
#define PAINTINGWIDGET_HPP

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QString>

#include "ui_cell_scale_parameters.h"
// TODO: thickness bar have not slot

namespace Ui {
class PaintingWidget;
}

class PaintingWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::PaintingWidget *m_painting_ui;
    Ui::cell_scale_parametres *m_cell_scale_parameters_ui;

    QImage m_map_image;

    QWidget m_cell_scale_parameters;

public:
    explicit PaintingWidget(QWidget *parent = nullptr);
    ~PaintingWidget();

public slots:
    void acceptChangesButtonPressed();
    void discardAllChangesButtonPressed();
    void updateMapButtonPressed();
    void discardLastChandesButtonPressed();
    void returnLastChangesButtonPressed();
    void showChangesButtonPressed();

    void brushType1ButtonPressed();
    void brushType2ButtonPressed();
    void brushType3ButtonPressed();
    void brushType4ButtonPressed();

    void updateGridButtonPressed();

    void enableGridButtonPressed();
    void shadowNonWOButtonPressed();

    void saveChangesButtonClicked(QAbstractButton *btn);

signals:
    void imageChanged(const QImage &image);

    void cellScaleParametersChanged(double width, double height, double scale) const;

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area);

// setters
public:
    void setScenePixmap(const QPixmap &pm);

// getters
public:
    QPixmap getEdittedMapPixmap() const;

    [[nodiscard]] inline const QImage& getMapImage() const noexcept { return m_map_image; }

// redefined functions
public:
    void close();

// modificators
public:
    void prepareGraphicsView(const QString &file_path);

// helpers
private:
    void setupConnectionsWithCellScaleParametersWidget();

    QPixmap drawAreasInMap();
};

#endif // PAINTINGWIDGET_HPP
