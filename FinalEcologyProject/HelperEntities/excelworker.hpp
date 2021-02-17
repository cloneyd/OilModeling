#ifndef EXCELWORKER_HPP
#define EXCELWORKER_HPP
#include <QObject>
#include <QPair>

#include "xlsxdocument.h"
#include "pch.hpp"
//#define XLSX_NO_LIB // ??

class ExcelWorker : public QObject
{
    Q_OBJECT

private:
    // excel file with heights
    QXlsx::Document *m_heights_doc;

public:
    explicit ExcelWorker();
    ~ExcelWorker() noexcept;

public slots:
    void updateHeightsFile(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridCreator widget (signal - gridChanged(same))
    void updateHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with SurfaceContainer (signal - heightsChanged(same))
    void saveHeightsFile(const QString &filepath); // connected with MainWidnow (signal - saveInExcelFileButtonPressed(same))
};

#endif // EXCELWORKER_HPP
