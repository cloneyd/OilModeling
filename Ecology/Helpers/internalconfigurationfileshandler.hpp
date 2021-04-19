#ifndef INTERNALCONFIGURATIONFILESHANDLER_H
#define INTERNALCONFIGURATIONFILESHANDLER_H
// Qt
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

class InternalConfigurationFilesHandler : public QObject
{
    Q_OBJECT

// helpers
private:
    enum ObjectID : unsigned char // OID, that objects will be marked with $
    {
        MIN,
        MainWindowID = MIN,
        GridHandlerID,
        PaintingWidgetID,
        ComputatorID,
        Object3DContainerID,
        MAX = Object3DContainerID
    };

// data
private:
    const char m_obj_delim;

public:
    InternalConfigurationFilesHandler(const char delim = '\n', QObject *parent = nullptr);

public slots:
    void createConfigurationFile() const; // connected with MainWindow::[32]; emits: [1], [3], [5], [7], [9]
    void loadConfigurationFile() const; // connected with MainWindow::[33]; emits: [2], [4], [6], [8], [10]

signals:
    void saveMainWindowState(QTextStream &where, const char obj_delim) const; // [1]
    void restoreMainWindowState(QTextStream &from, const char obj_delim) const; // [2]

    void saveGridHandlerState(QTextStream &where, const char obj_delim) const; // [3]
    void restoreGridHandlerState(QTextStream &from, const char obj_delim) const; // [4]

    void savePaintingWidgetState(QTextStream &where, const char obj_delim) const; // [5]
    void restorePaintingWidgetState(QTextStream &from, const char obj_delim) const; // [6]

    void saveComputatorState(QTextStream &where, const char obj_delim) const; // [7]
    void restoreComputatorState(QTextStream &from, const char obj_delim) const; // [8]

    void saveObject3DContainerState(QTextStream &where, const char obj_delim) const; // [9]
    void restoreObject3DContainerState(QTextStream &from, const char obj_delim) const; // [10]
};

#endif // INTERNALCONFIGURATIONFILESHANDLER_H
