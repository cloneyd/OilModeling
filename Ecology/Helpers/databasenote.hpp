#ifndef DATABASENOTE_HPP
#define DATABASENOTE_HPP
// QT
#include <QMessageBox>

// current project
#include "ui_databasenote.h"
#include "errorstatusstructures.hpp"
#include "PollutionWidget/pollutionwidget_utilities.hpp"

extern WrittingState addNewNoteToDatabase(const FileMatterInformation& info);

class DatabaseNote : public QWidget
{
    Q_OBJECT
private:
    Ui::DatabaseNote m_ui;

public:
    explicit DatabaseNote(QWidget *parent = nullptr);

private slots:
    void addToTableButtonPressed();
};

#endif // DATABASENOTE_HPP
