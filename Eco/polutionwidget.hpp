#ifndef POLUTIONWIDGET_HPP
#define POLUTIONWIDGET_HPP
#include <QWidget>
#include <QAbstractButton>
#include <QDoubleSpinBox>

#include <variant>

#include "pollution_widget_utilities.hpp"
#include "source_types.hpp"

namespace Ui {
class PolutionWidget;
}

class PolutionWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::PolutionWidget *m_ui;
    WidgetMode m_mode;
    int m_myindex;

public:
    explicit PolutionWidget(WidgetMode mode = WidgetMode::Create, QWidget *parent = nullptr);
    ~PolutionWidget();

private slots:
    void typeChanged(int type);
    void addNewMatterButtonPressed();
    void deleteSelectedMatterButtonPressed();
    void saveButtonAccepted();
    inline void saveButtonRejected() { close(); }

signals:
    void sourceCreated(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters) const;
    void sourceUpdated(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);

// setters
public:
    void setSource(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    inline void setIndex(int index) noexcept { m_myindex = index; }

// helpers
private:
    void addItemToMattersTable(int row, int col, const QString &text);
    void addWidgetsToMattersTable(int row);
    QDoubleSpinBox* createDoubleSpinBox(double lower = 0., double upper = 100000., int decimals = 3);
    void getPointSourceItems(const PointSource &source);
};

#endif // POLUTIONWIDGET_HPP
