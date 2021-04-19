#ifndef POLLUTIONWIDGET_HPP
#define POLLUTIONWIDGET_HPP
// QT
#include <QWidget>
#include <QTableWidgetItem>
#include <QDoubleSpinBox>
#include <QComboBox>

// STL
#include <memory>

// current project
#include "pollutionwidget_utilities.hpp"

namespace Ui {
class PollutionWidget;
}

class PollutionWidget : public QWidget
{
    Q_OBJECT

private: // data
    int m_source_index; // will be an index if WidgetMode is Display; -1 by default
    WidgetMode m_mode;
    std::unique_ptr<Ui::PollutionWidget> m_ui;

public:
    explicit PollutionWidget(WidgetMode mode, QWidget *parent = nullptr);

private slots:
    void sourceTypeChanged(int index); // connected with UI::[1]
    void addNewMatterButtonPressed(); // connected with Ui::[2]
    void deleteSelectedMatterButtonPressed(); // connected with Ui::[3]
    void saveButtonAccepted(); // connected with Ui::[4]; emits: {1}, {2}, {3}, {4}
    inline void saveButtonRejected() { close(); } // connected with Ui::[5]

signals:
    void sourceCreated(const PointSource &source, const QVector<PollutionMatter> &matters) const; // [1]
    void sourceUpdated(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters) const; // [2]

    void sourceCreated(const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [3]
    void sourceUpdated(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [4]

// setters
public:
    void setSource(const PointSource &source, const QVector<PollutionMatter> &matter);
    void setSource(const DiffusionSource &source, const QVector<PollutionMatter> &matter);
    inline void setSourceIndex(int source_index) noexcept { m_source_index = source_index; }

// helpers
private:
    template <class ...Flags>
    QTableWidgetItem* createItem(const QString &data, Flags&&...flags);
    QDoubleSpinBox* createDoubleSpinBox(double value, QWidget *owner = nullptr, double lower_bound = -10000., double upper_bound = 10000., int decimals = 4);

    void addMatterToTable(int row, const PollutionMatter &matter, QWidget *owner = nullptr); // adds widgets to row
    void setSourceItems(const PointSource &source);

    PointSource extractSourceInfo() const;
    PollutionMatter extractMatterInfo(int row) const;

    void setupUiConnections();
};

#endif // POLLUTIONWIDGET_HPP
