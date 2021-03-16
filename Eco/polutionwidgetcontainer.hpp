#ifndef POLUTIONWIDGETCONTAINER_HPP
#define POLUTIONWIDGETCONTAINER_HPP
#include <QObject>

#include <variant>

#include "polutionwidget.hpp"

class PolutionWidgetContainer : public QObject
{
    Q_OBJECT

private:
    unsigned char m_nwidgets;

public:
    PolutionWidgetContainer();

public slots:
    void createNewPolutionWidget();
    void displaySelectedSource(int index) const;

private slots:
    void sourceCreatedSender(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    void sourceUpdatedSender(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters) const;
    void heldWidgetClosed();

signals:
    void getSourceInfo(int index, std::variant<PointSource, DiffusionSource> &source, QVector<PolutionMatter> &matters) const;
    void sourceCreated(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters) const;
    void sourceUpdated(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters) const;
};

#endif // POLUTIONWIDGETCONTAINER_HPP
