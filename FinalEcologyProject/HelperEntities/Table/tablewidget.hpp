
#ifndef TABLEWIDGET_HPP
#define TABLEWIDGET_HPP
#include <QTableWidget>
#include <QCloseEvent>

class TableWidget: public QTableWidget
{
    Q_OBJECT
public:
    using QTableWidget::QTableWidget;
    TableWidget();

signals:
    void closeSignal(TableWidget *table); // emitted when widget closed (closeEvent(QCloseEvent*) function)

// Overridden functions
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TABLEWIDGET_HPP
