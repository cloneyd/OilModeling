#include "tablewidget.hpp"

#include <QHeaderView>
#include <QScreen>

// Ctor
TableWidget::TableWidget() :
    QTableWidget{}
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// protected overridden functions
void TableWidget::closeEvent(QCloseEvent *event)
{
    emit closeSignal(this);
    QTableWidget::closeEvent(event);
}
