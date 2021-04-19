#include "internalconfigurationfileshandler.hpp"

InternalConfigurationFilesHandler::InternalConfigurationFilesHandler(const char delim, QObject *parent) :
    QObject(parent),
    m_obj_delim{ delim }
{/*PASS*/}


// public slots
void InternalConfigurationFilesHandler::createConfigurationFile() const
{
    auto filepath{ QFileDialog::getSaveFileName(nullptr, tr("Save File"), "config") };
    if(filepath.isEmpty())  return;
    filepath.replace(QChar('\\'), QChar('/'));

    QFile file(filepath);
    Q_ASSERT(file.open(QIODevice::WriteOnly | QIODevice::Text));

    QTextStream stream(&file);
    stream << '$' << ObjectID::MainWindowID << m_obj_delim;
    emit saveMainWindowState(stream, m_obj_delim);

    stream << '$' << ObjectID::GridHandlerID << m_obj_delim;
    emit saveGridHandlerState(stream, m_obj_delim);

    stream << '$' << ObjectID::PaintingWidgetID << m_obj_delim;
    emit savePaintingWidgetState(stream, m_obj_delim);

    stream << '$' << ObjectID::ComputatorID << m_obj_delim;
    emit saveComputatorState(stream, m_obj_delim);

    stream << '$' << ObjectID::Object3DContainerID << m_obj_delim;
    emit saveObject3DContainerState(stream, m_obj_delim);
}

void InternalConfigurationFilesHandler::loadConfigurationFile() const
{
    auto filepath{ QFileDialog::getOpenFileName(nullptr, tr("Open File"), "/home", "All files (*)") };
    if(filepath.isEmpty())  return;
    filepath.replace(QChar('\\'), QChar('/'));

    QFile file(filepath);
    Q_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream(&file);
    auto readUntilDelim = [&stream](const char delim) -> QString {
        QString result{};
        char sym{};
        for(stream >> sym; sym != delim; stream >> sym) {
            result += sym;
        }
        return result;
    };

    bool is_converted{};
    while(!stream.atEnd()) {
        readUntilDelim('$');
        const int id{ readUntilDelim(m_obj_delim).toInt(&is_converted) };
        Q_ASSERT(is_converted);
        Q_ASSERT(id >= ObjectID::MIN && id <= ObjectID::MAX);

        switch(static_cast<ObjectID>(id)) {
        case ObjectID::MainWindowID:
            emit restoreMainWindowState(stream, m_obj_delim);
            break;

        case ObjectID::GridHandlerID:
            emit restoreGridHandlerState(stream, m_obj_delim);
            break;

        case ObjectID::PaintingWidgetID:
            emit restorePaintingWidgetState(stream, m_obj_delim);
            break;

        case ObjectID::ComputatorID:
            emit restoreComputatorState(stream, m_obj_delim);
            break;

        case ObjectID::Object3DContainerID:
            emit restoreObject3DContainerState(stream, m_obj_delim);
            break;
        }
    }
}
