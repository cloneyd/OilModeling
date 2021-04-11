#ifndef EXCELWORKER_HPP
#define EXCELWORKER_HPP
// QT
#include <QObject>

// current project
#include "GridHandlerFiles/grid_handler_utilities.hpp"
#include "Visualization3D/object3d_utilities.hpp"

// 3d party library
#include "xlsxdocument.h"
#include "xlsxconditionalformatting.h"

class ExcelWorker : public QObject
{
    Q_OBJECT

private:
    enum SpeedsDocSheetsIndexes : unsigned char
    {
        u_projection,
        u0_projection,
        flows,
        num_of_sheets = 3
    };

private:
    QXlsx::Document m_depth_doc;
    QXlsx::Document m_speeds_doc;

    const GridType *m_pixgrid_ptr; // pointer to pixgrid which allows us search in all containers which have no belongness flags

    // conditional formatting colors
    QColor m_green;
    QColor m_yellow;
    QColor m_red;
public:
    explicit ExcelWorker(QObject *parent = nullptr);

public slots:
    void saveMap(const QString &filepath, bool *operation_status = nullptr); // connected with MainWindow::[7]; saves file where m_pixgrid_ptr.first == true with -1
    void loadDepth(const QString &filepath, bool *operation_status = nullptr) const; // connected with MainWindow::[20]; emits: [1] if successed
    void saveSpeeds(const QString &filepath, bool *operation_status = nullptr) const; // connected with MainWindow::[4];
    void saveDepth(const QString &filepath, bool *operation_status = nullptr) const; // connected with MainWindow::[5];
    void saveOutput(const QString &filepth, bool *operation_status = nullptr); // connected with MainWindow::[6]

    void acceptGrid(const GridType &pixgrid); // connected with GridHandler::[6]
    void acceptDepth(const DepthType &depth); // connected with Object3DContainer::[1]
    void acceptUXProjections(const QVector<QVector<double>> &speeds); // connected Computator::[1]
    void acceptUYProjections(const QVector<QVector<double>> &speeds); // connected Computator::[2]
    void acceptU0XProjections(const QVector<QVector<double>> &speeds); // connected Computator::[3]
    void acceptU0YProjections(const QVector<QVector<double>> &speeds); // connected Computator::[4]
    void acceptU(const QVector<QVector<double>> &speeds); // connected Computator::[5]
    void acceptU0(const QVector<QVector<double>> &speeds); // connected Computator::[6]

signals:
    void depthLoaded(DepthType &depth) const; // [1] transfer ownership

// helpers
private:
    void writeToFile(QXlsx::Document &where,
                     int row_offset, int col_offset,
                     int sheet_index,
                     const QVector<QVector<double>> &what, // belondness will be checked with m_pixgrid_ptr.first
                     const QString &label = "",
                     QXlsx::ConditionalFormatting *cfm = nullptr);

    void writeToFile(QXlsx::Document &where,
                     int row_offset, int col_offset,
                     int sheet_index,
                     const DepthType &what, // belondness will be checked what.first
                     const QString &label = "",
                     QXlsx::ConditionalFormatting *cfm = nullptr);

    // belondness will be checked with m_pixgrid_ptr.first and will be filled with -1
    void writeToFile(QXlsx::Document &where,
                     int row_offset, int col_offset,
                     int sheet_index, const QString &label = "");

    [[nodiscard]] bool verifyGrid() const; // if grid is nullptr or empty - false
};

#endif // EXCELWORKER_HPP
