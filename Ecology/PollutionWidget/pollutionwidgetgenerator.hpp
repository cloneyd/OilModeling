#ifndef POLLUTIONWIDGETGENERATOR_HPP
#define POLLUTIONWIDGETGENERATOR_HPP
// QT
#include <QObject>

// STL
#include <variant>

// current
#include "pollutionwidget.hpp"

class PollutionWidgetGenerator : public QObject
{
    Q_OBJECT

private: // data
    PollutionWidget *m_creatation_lock_widget; // if non - nullptr - new sources creation locks

public:
    explicit PollutionWidgetGenerator(QObject *parent = nullptr);

public slots:
    // it's prohibited to create more than one default constructed widget cause order of widgets could be important
    void createDefaultConstructedWidget(); // connected with MainWindow::[25]
    // we display more than one widget
    void createFilledWidget(int source_index) const; // connected with MainWindow::[26]; emits: [5]

private slots:
    // connected with PollutionWidget::[1]; emits: [1]
    inline void sourceCreatedEmitter(const PointSource &source, const QVector<PollutionMatter> &matters) const { emit sourceCreated(source, matters); }
    // connected with PollutionWidget::[2]; emits: [2]
    inline void sourceUpdatedEmitter(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters) const { emit sourceUpdated(source_index, source, matters); }

    // connected with PollutionWidget::[3]; emits: [3]
    inline void sourceCreatedEmitter(const DiffusionSource &source, const QVector<PollutionMatter> &matters) const { emit sourceCreated(source, matters); }
    // connected with PollutionWidget::[4]; emits[4]
    inline void sourceUpdatedEmitter(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters) const { emit sourceUpdated(source_index, source, matters); }

    /* connected with PollutionWidget which was created in createDefaultConstructedWidget;
     * signal - destroyed(QObject*)
     * unlock createDefaultConstructedWidget */
    inline void defaulWidgetCreationEnd(QObject *unused) noexcept { (void)unused; m_creatation_lock_widget = nullptr; }

    inline void catchPollutionWidgetDataLoadingCall(const int page_number, const int page_size,
                                                    QVector<FileMatterInformation> &where, ReadingState &state)
                                                    { emit transferInfromationLoading(page_number, page_size, where, state); }
signals:
    void sourceCreated(const PointSource &source, const QVector<PollutionMatter> &matters) const; // [1]
    void sourceUpdated(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters) const; // [2]

    void sourceCreated(const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [3]
    void sourceUpdated(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters) const; // [4]

    void getSourceInfo(int source_index, std::variant<PointSource, DiffusionSource> &source, QVector<PollutionMatter> &matters) const; // [5]
    void transferInfromationLoading(const int page_number, const int page_size,
                                    QVector<FileMatterInformation> &where, ReadingState &state); // [6]; transfers PollutionWidget call

// helpers
private:
    void connectDefaultWidget(const PollutionWidget *widget) const;
    void connectFilledWidget(const PollutionWidget *widget) const;
};

#endif // POLLUTIONWIDGETGENERATOR_HPP
