#ifndef EXCELWORKER_HPP
#define EXCELWORKER_HPP
#include <QObject>
#include <QPair>
#include <QString>
#include <QVector>
#include <QPointF>

#include "xlsxconditionalformatting.h"
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
    void acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridHandler; signal - gridChanged(same)

    void updateHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with Visualization3DContainer; signal - heightsChanged(same)
    void saveHeightsFile(const QString &filepath); // connected with MainWidnow; signal - saveMapAsExcek(same)
    void loadHeightsFromFile(const QString &file_path); // connected with MainWindow; signal - loadHeightsFromFileSender(same)

    void updateXSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - xSpeedChanged(same)
    void updateYSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - ySpeedChanged(same)
    void saveSpeedsAsExcel(const QString &filepath); // connected with MainWindow; signal - saveSpeedsAsExcel(same)
    void saveValuesWithHighlight(const QString &filepath, const QVector<QVector<double>> &value, double discard_flag) const;
    void saveValuesWithHighlight(const QString &filepath, const QVector<QVector<double>> &first, const QVector<QVector<double>> &second, double discard_flag) const;

signals:
    void heightsLoaded(QVector<QVector<QPair<bool, double>>> &heights); // WARNING: heights will be changed
};

#endif // EXCELWORKER_HPP
