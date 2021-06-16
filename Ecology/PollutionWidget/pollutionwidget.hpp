#ifndef POLLUTIONWIDGET_HPP
#define POLLUTIONWIDGET_HPP
// QT
#include <QWidget>
#include <QTableWidgetItem>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QCompleter>

// STL
#include <memory>

// current project
#include "pollutionwidget_utilities.hpp"
#include "Helpers/databasenote.hpp"
#include "Helpers/errorstatusstructures.hpp"

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

    struct  MatterPageReadingInfo{
        QVector<FileMatterInformation> m_last_read_page; // the read from file page
        bool m_ignore;

        int m_page_number; // page number means the offset from firts position; the number of note computate with m_page_size * m_page_number + index (index - number [1;m_page_size])
    };
    const int m_page_size; // the size of chunk which can be read from the file
    QVector<MatterPageReadingInfo> m_matter_info;

public:
    explicit PollutionWidget(WidgetMode mode, QWidget *parent = nullptr);

private slots:
    void sourceTypeChanged(int index); // connected with UI::[1]
    void mattersNamesIndexChanged(int index); // connected with Ui::matters_table::cell[1](combo box)::currentIndexChanged
    void addNewMatterButtonPressed(); // connected with Ui::[2]
    void deleteSelectedMatterButtonPressed(); // connected with Ui::[3]
    void saveButtonAccepted(); // connected with Ui::[4]; emits: {1}, {2}, {3}, {4}
    inline void saveButtonRejected() { close(); } // connected with Ui::[5]
    void searchSubstringInBox(const QString& what); // connected with UI::matters_table::combo box(cell[*][0])
    void addNewMatterToDatabaseButtonPressed(); // connected with Ui::add_new_matter_to_table::pressed

signals:
    void sourceCreated(const PointSource &source, const QVector<PollutionMatter> &matters) const; // [1]
    void sourceUpdated(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters) const; // [2]

    void sourceCreated(const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [3]
    void sourceUpdated(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [4]

    void loadMattersDataFromFile(const int page_number, const int page_size,
                                 QVector<FileMatterInformation> &where, ReadingState &state); // [5]
// setters
public:
    void setSource(const PointSource &source, const QVector<PollutionMatter> &matter);
    void setSource(const DiffusionSource &source, const QVector<PollutionMatter> &matter);
    inline void setSourceIndex(int source_index) noexcept { m_source_index = source_index; }

    ReadingState readMattersData(const int page_number, QVector<FileMatterInformation>& where); // emits [5]

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

    void setMattersNameToComboBox(const int row, bool is_initialization = false);
};

#endif // POLLUTIONWIDGET_HPP
