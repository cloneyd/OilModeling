#include "databasenote.hpp"

DatabaseNote::DatabaseNote(QWidget *parent) :
    QWidget(parent)
{
    m_ui.setupUi(this);

    connect(m_ui.add_to_table_button, SIGNAL(pressed()),
            this, SLOT(addToTableButtonPressed()));
}

void DatabaseNote::addToTableButtonPressed()
{
    const auto name{ m_ui.matter_name_line_edit->text() };
    const auto group{ m_ui.matter_group_line_edit->text() };
    const auto mpc{ m_ui.mpc_double_spin_box->value() };

    if(name.isEmpty() || group.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Введите название вещества и группу!");
        return;
    }
    const auto state{ addNewNoteToDatabase(FileMatterInformation{name, mpc, group}) };

    switch(state) {
    case WrittingState::Ok:
        break; // silence the compiler

    case WrittingState::WrittingError:
        QMessageBox::warning(nullptr, "Ошибка записи", "Не удалось записать информацию о веществе в файл");
        break;

    case WrittingState::FileNotExist:
        QMessageBox::warning(nullptr, "Ошибка записи", "Файл веществ не обнаружен. Пожалуйста, свяжитесь с разработчиками");
        break;

    case WrittingState::FileCorrupted:
        QMessageBox::warning(nullptr, "Ошибка записи", "Файл веществ поврежден. Пожалуйста, свяжитесь с разработчиками");
        break;

    case WrittingState::FileNotSaved:
        QMessageBox::warning(nullptr, "Ошибка записи", "Не удалось сохранить файл. Пожалуйста, попробуйте снова");
        break;

    case WrittingState::Undefined:
        Q_ASSERT(false); // must be unreachable
        QMessageBox::warning(nullptr, "Ошибка записи", "Неизвестная ошибка. Пожалуйста, свяжитесь с разработчиками");
        break;
    }

    close();
}
