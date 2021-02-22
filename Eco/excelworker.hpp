#ifndef EXCELWORKER_HPP
#define EXCELWORKER_HPP
#include <QObject>
#include <QPair>
#include <QString>
#include <QVector>
#include <QPointF>

#include "xlsxdocument.h"
//#define XLSX_NO_LIB // ??

class ExcelWorker : public QObject
{
    Q_OBJECT

private:
    // excel file with heights
    QXlsx::Document m_heights_doc;
    QXlsx::Document m_speeds_doc;

    QVector<QVector<bool>> m_grid;

public:
    explicit ExcelWorker();
    ~ExcelWorker() noexcept;

public slots:
    void acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridCreator widget (signal - gridChanged(same))

    void updateHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with SurfaceContainer (signal - heightsChanged(same))
    void saveHeightsFile(const QString &filepath); // connected with MainWidnow (signal - saveInExcelFileButtonPressed(same))
    void loadHeightsFromFile(const QString &file_path);

    void updateXSpeeds(const QVector<QVector<double>> &speeds);
    void updateYSpeeds(const QVector<QVector<double>> &speeds);
    void saveSpeedsAsExcel(const QString &filepath);

signals:
    void heightsLoaded(QVector<QVector<QPair<bool, double>>> &heights); // WARNING: heights will be changed
};

#endif // EXCELWORKER_HPP
