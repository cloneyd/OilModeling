#include "pollutionwidgetgenerator.hpp"

PollutionWidgetGenerator::PollutionWidgetGenerator(QObject *parent) :
    QObject(parent),
    m_creatation_lock_widget{ nullptr }
{ /*PASS*/ }


// public slots
void PollutionWidgetGenerator::createDefaultConstructedWidget()
{
    if(m_creatation_lock_widget) {
        QMessageBox::about(nullptr, "Добавление источника",
                           "Можно добавлять только один источник.\nЗакончите добавление прошлого источника");
        m_creatation_lock_widget->activateWindow();
        return;
    }

    m_creatation_lock_widget = new PollutionWidget(WidgetMode::Create); // create lock widget
    m_creatation_lock_widget->setAttribute(Qt::WA_DeleteOnClose, true);
    m_creatation_lock_widget->show();
    connectDefaultWidget(m_creatation_lock_widget);
}

void PollutionWidgetGenerator::createFilledWidget(int source_index) const
{
    std::variant<PointSource, DiffusionSource> source;
    QVector<PollutionMatter> matters;
    emit getSourceInfo(source_index, source, matters);

    auto widget{ new PollutionWidget(WidgetMode::Display) };
    widget->setAttribute(Qt::WA_DeleteOnClose, true);
    widget->setSourceIndex(source_index);
    if(source.index() == 0) {
        widget->setSource(std::get<PointSource>(source), matters);
    }
    else {
        widget->setSource(std::get<DiffusionSource>(source), matters);
    }
    widget->show();
    connectFilledWidget(widget);
}


// private helpers
void PollutionWidgetGenerator::connectDefaultWidget(const PollutionWidget *widget) const
{
    connect(widget, SIGNAL(sourceCreated(const PointSource &, const QVector<PollutionMatter> &)), // [1]
            this, SLOT(sourceCreatedEmitter(const PointSource &, const QVector<PollutionMatter> &)));

    connect(widget, SIGNAL(sourceCreated(const DiffusionSource &, const QVector<PollutionMatter> &)), // [3]
            this, SLOT(sourceCreatedEmitter(const DiffusionSource &, const QVector<PollutionMatter> &)));

    connect(widget, SIGNAL(destroyed(QObject*)),
            this, SLOT(defaulWidgetCreationEnd(QObject *)));
}

void PollutionWidgetGenerator::connectFilledWidget(const PollutionWidget *widget) const
{
    connect(widget, SIGNAL((int, const PointSource &, const QVector<PollutionMatter> &)), // [2]
            this, SLOT(sourceUpdatedEmitter(int, const PointSource &, const QVector<PollutionMatter> &)));

    connect(widget, SIGNAL(sourceUpdated(int, const DiffusionSource &, const QVector<PollutionMatter> &)), // [4]
            this, SLOT(sourceUpdatedEmitter(int, const DiffusionSource &, const QVector<PollutionMatter> &)));
}
