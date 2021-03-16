#include "polutionwidgetcontainer.hpp"

extern void showErrorMessageBox(const QString &msg, const QString &title ="");


PolutionWidgetContainer::PolutionWidgetContainer() :
    QObject{},
    m_nwidgets{}
{
    // PASS
}


// public slots
void PolutionWidgetContainer::createNewPolutionWidget()
{
    ++m_nwidgets;
    if(m_nwidgets > 1) {
        --m_nwidgets;
        showErrorMessageBox("Нельзя создавать более одного окна.\nЗакончите изменения прошлого источника");
        return;
    }

    auto widget{ new PolutionWidget };
    widget->setAttribute(Qt::WA_DeleteOnClose, true); // forcing delete when close
    widget->show();

    connect(widget, SIGNAL(sourceCreated(const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)),
            this, SLOT(sourceCreatedSender(const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)));
    connect(widget, SIGNAL(destroyed(QObject*)),
            this, SLOT(heldWidgetClosed()));
}

void PolutionWidgetContainer::displaySelectedSource(int index) const
{
    std::variant<PointSource, DiffusionSource> source;
    QVector<PolutionMatter> matters;
    emit getSourceInfo(index, source, matters);

    auto widget{ new PolutionWidget(WidgetMode::Display) };
    widget->setAttribute(Qt::WA_DeleteOnClose, true); // forcing delete when close
    widget->setSource(source, matters);
    widget->setIndex(index);

    connect(widget, SIGNAL(sourceUpdated(int, const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)),
            this, SLOT(sourceUpdatedSender(int, const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)));

    widget->show();
}


// private slots
void PolutionWidgetContainer::sourceCreatedSender(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters)
{
    emit sourceCreated(source, matters);
}

void PolutionWidgetContainer::sourceUpdatedSender(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters) const
{
    emit sourceUpdated(index, source, matters);
}

void PolutionWidgetContainer::heldWidgetClosed()
{
    --m_nwidgets;
}
