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

// TODO: объединить 6 функций обновления скоростей в одну
class ExcelWorker : public QObject
{
    Q_OBJECT

    enum ListLocation : unsigned char
    {
        list_of_u_projection,
        list_of_u0_projection,
        list_of_flows
    };

private:
    // excel file with heights
    QXlsx::Document m_heights_doc;
    QXlsx::Document m_speeds_doc;

    const QVector<QVector<QPair<bool, QPointF>>> *m_grid_ptr;

// static constanst used only in this class
private:
    static constexpr int number_of_speed_list{ 3 };

public:
    explicit ExcelWorker();
    ~ExcelWorker() noexcept;

public slots:
    void acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridHandler; signal - gridChanged(same)

    void updateHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with Visualization3DContainer; signal - heightsChanged(same)
    void saveHeightsFile(const QString &filepath); // connected with MainWidnow; signal - saveMapAsExcek(same)
    void loadHeightsFromFile(const QString &file_path); // connected with MainWindow; signal - loadHeightsFromFileSender(same)

    void updateUXSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - uxSpeedChanged(same)
    void updateUYSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - uySpeedChanged(same)
    void updateU0XSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - u0xSpeedChanged(same)
    void updateU0YSpeeds(const QVector<QVector<double>> &speeds); // connected with Computator; signal - u0ySpeedChanged(same
    void updateU(const QVector<QVector<double>> &speeds);
    void updateU0(const QVector<QVector<double>> &speeds);
    void saveSpeedsAsExcel(const QString &filepath); // connected with MainWindow; signal - saveSpeedsAsExcel(same)

signals:
    void heightsLoaded(QVector<QVector<QPair<bool, double>>> &heights); // WARNING: heights will be changed

// helpers
private:
    void updateSpeed(int row_offset, int col_offset, ListLocation page, const QString &label, const QVector<QVector<double>> &speeds);
};

#endif // EXCELWORKER_HPP
