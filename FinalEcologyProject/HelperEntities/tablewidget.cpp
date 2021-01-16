#include "tablewidget.hpp"

// protected overridden functions
void TableWidget::closeEvent(QCloseEvent *event)
{
    emit closeSignal(this);
    QTableWidget::closeEvent(event);
}
