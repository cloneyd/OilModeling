#include "pollutionwidget.hpp"
#include "ui_pollutionwidget.h"

PollutionWidget::PollutionWidget(WidgetMode mode, QWidget *parent) :
    QWidget(parent),
    m_source_index{ -1 },
    m_mode{ mode },
    m_ui(std::make_unique<Ui::PollutionWidget>()),
    m_page_size{ 400 }
{
    m_ui->setupUi(this);

    auto *table{ m_ui->matters_table_widget_4 };
    table->setRowCount(1);
    table->setColumnCount(PollutionMatter::number_of_properties);
    table->resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setItem(0, 0, createItem("Вещество", Qt::NoItemFlags));
    table->setItem(0, 1, createItem("Группа ЛПВ", Qt::NoItemFlags));
    table->setItem(0, 2, createItem("Доля ЛПВ", Qt::NoItemFlags));
    table->setItem(0, 3, createItem("ПДК, мг/дм^3", Qt::NoItemFlags));
    table->setItem(0, 4, createItem("Сф, мг/дм^3", Qt::NoItemFlags));
    table->setItem(0, 5, createItem("Сст, мг/дм^3", Qt::NoItemFlags));
    table->setItem(0, 6, createItem("Сmax, мг/дм^3", Qt::NoItemFlags));
    table->setItem(0, 7, createItem("Сср, мг/дм^3", Qt::NoItemFlags));
    table->setItem(0, 8, createItem("Сст.доп, мг/дм^3", Qt::NoItemFlags));

    setWindowTitle("Источник");
    setupUiConnections();
}


// setters
void PollutionWidget::setSource(const PointSource &source, const QVector<PollutionMatter> &matters)
{
    setSourceItems(source);

    const auto last_index{ m_ui->matters_table_widget_4->rowCount() };
    const auto nmatters{ matters.size() };
    m_ui->matters_table_widget_4->setRowCount(last_index + nmatters);
    for(int i{}; i < nmatters; ++i) {
        addMatterToTable(last_index + i, matters[i]);
    }
}

void PollutionWidget::setSource(const DiffusionSource &source, const QVector<PollutionMatter> &matters)
{
    setSource(static_cast<const PointSource&>(source), matters);

    m_ui->length_double_spin_box_4->setValue(source.m_length);
    m_ui->direction_double_spin_box_4->setValue(source.m_direction);
    m_ui->tubes_number_spin_box_4->setValue(source.m_tubes_number);
    m_ui->type_combo_box_4->setCurrentIndex(1);
}

ReadingState PollutionWidget::readMattersData(const int page_number, QVector<FileMatterInformation>& where)
{
    ReadingState state{ ReadingState::FileCorrupted };
    emit loadMattersDataFromFile(page_number, m_page_size, where, state);

    switch(state) {
    case ReadingState::NotEnoughData:
        Q_ASSERT_X(false, "Class - PollutionWidget", "readMattersData, problem - empty file");
        break;

    case ReadingState::FileCorrupted:
        Q_ASSERT_X(false, "Class - PollutionWidget", "readMattersData, problem - file corrupted");
        break;

    case ReadingState::Ok:
        break; // Do nothing, silence the compiler

    case ReadingState::ConvertionFailed:
        Q_ASSERT_X(false, "Class - PollutionWidget", "readMattersData, problem - data not converted");
        break;
    }

    return state;
}


// private slots
void PollutionWidget::sourceTypeChanged(int index)
{
    if(index == 0) {
        m_ui->length_double_spin_box_4->setEnabled(false);
        m_ui->direction_double_spin_box_4->setEnabled(false);
        m_ui->tubes_number_spin_box_4->setEnabled(false);
    }
    else {
        m_ui->length_double_spin_box_4->setEnabled(true);
        m_ui->direction_double_spin_box_4->setEnabled(true);
        m_ui->tubes_number_spin_box_4->setEnabled(true);
    }
}

void PollutionWidget::mattersNamesIndexChanged(int index)
{
    // first note in combo box is "-" and must be skipped
    // first meaningful combo box value must be skipped if page_number > 0
    const auto matters_table{ m_ui->matters_table_widget_4 };
    const auto current_row{ matters_table->currentRow() };
    auto& current_info{ m_matter_info[current_row - 1] };
    auto& last_read_page{ current_info.m_last_read_page };
    auto& ignore{ current_info.m_ignore };
    auto& page_number{ current_info.m_page_number };
    ignore = true; // disable the substring search

    auto box{ qobject_cast<QComboBox*>(matters_table->cellWidget(current_row, 0)) };
    const auto nnotes{ box->count() };

    box->blockSignals(true);
    if(index == nnotes - 1) {
        if(readMattersData(++page_number, current_info.m_last_read_page) == ReadingState::Ok) {
            setMattersNameToComboBox(current_row);
        }
        else {
            QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось прочитать страницу");
            --page_number;
        }
    }
    else if(index == 1 && page_number > 0) {
        if(readMattersData(--page_number, current_info.m_last_read_page) == ReadingState::Ok) {
            setMattersNameToComboBox(current_row);
        }
        else {
            QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось прочитать страницу");
            ++page_number;
        }
    }
    else if (index > 0 && index < nnotes) { // control check
        if(page_number > 0) {
            qobject_cast<QLineEdit*>(matters_table->cellWidget(current_row, 1))->setText(last_read_page[index - 2].m_group);
            qobject_cast<QDoubleSpinBox*>(matters_table->cellWidget(current_row, 3))->setValue(last_read_page[index - 2].m_mpc);
        }
        else {
            qobject_cast<QLineEdit*>(matters_table->cellWidget(current_row, 1))->setText(last_read_page[index - 1].m_group);
            qobject_cast<QDoubleSpinBox*>(matters_table->cellWidget(current_row, 3))->setValue(last_read_page[index - 1].m_mpc);
        }
    }
    box->blockSignals(false);
}

void PollutionWidget::addNewMatterButtonPressed()
{
    const auto nrows{ m_ui->matters_table_widget_4->rowCount() };
    m_ui->matters_table_widget_4->setRowCount(nrows + 1);
    m_matter_info.push_back({});
    if(m_matter_info.front().m_last_read_page.isEmpty()) {
        readMattersData(0, m_matter_info.front().m_last_read_page);
    }

    addMatterToTable(nrows, { {}, {}, -1., -1., -1., -1. -1., -1., -1., -1. });
    auto matters_combo_box{ qobject_cast<QComboBox*>(m_ui->matters_table_widget_4->cellWidget(nrows, 0)) };
    connect(matters_combo_box, SIGNAL(currentIndexChanged(int/*index*/)), // conencted with UI::matters_table_widget::cell[*][0]
            this, SLOT(mattersNamesIndexChanged(int)));
    connect(matters_combo_box, SIGNAL(currentTextChanged(const QString&/*what*/)), // conencted with UI::matters_table_widget::cell[*][0]
            this, SLOT(searchSubstringInBox(const QString&)));
}

void PollutionWidget::deleteSelectedMatterButtonPressed()
{
    const auto row{ m_ui->matters_table_widget_4->currentRow() };
    if(row == 0)    return;
    m_ui->matters_table_widget_4->removeRow(row);
    m_matter_info.remove(row - 1);
}

void PollutionWidget::saveButtonAccepted()
{
    auto nrows{ m_ui->matters_table_widget_4->rowCount() - 1};
    QVector<PollutionMatter> matters(nrows);
    for(int i{}; i < nrows; ++i) {
        matters[i] = extractMatterInfo(i + 1);
    }

    if(m_ui->type_combo_box_4->currentIndex() == 0) {
        PointSource source{ extractSourceInfo() };

        if(m_mode == WidgetMode::Create) {
            emit sourceCreated(source, matters);
        }
        else {
            Q_ASSERT_X(m_source_index >= 0, "Class - PollutionWidget", "function - saveButtonAccepted, problem - invalid index");
            emit sourceUpdated(m_source_index, source, matters);
        }
    }
    else {
        DiffusionSource source{ extractSourceInfo() };
        source.m_length =  m_ui->length_double_spin_box_4->value();
        source.m_direction = m_ui->direction_double_spin_box_4->value();
        source.m_tubes_number = m_ui->tubes_number_spin_box_4->value();

        if(m_mode == WidgetMode::Create) {
            emit sourceCreated(source, matters);
        }
        else {
            Q_ASSERT_X(m_source_index >= 0, "Class - PollutionWidget", "function - saveButtonAccepted, problem - invalid index");
            emit sourceUpdated(m_source_index, source, matters);
        }
    }

    close();
}

void PollutionWidget::searchSubstringInBox(const QString& what)
{
    if(what.isEmpty())   return;
    if(what == "Загрузить предыдущую страницу") return;

    const auto matters_table{ m_ui->matters_table_widget_4 };
    const auto current_row{ matters_table->currentRow() };
    auto& current_info{ m_matter_info[current_row - 1] };
    if(current_info.m_ignore) {
        current_info.m_ignore = false;
        return;
    }

    const auto box{ qobject_cast<QComboBox*>(matters_table->cellWidget(current_row, 0)) };
    if(box->completer()->currentCompletion().isEmpty()) {
        bool is_read_direction_find{}; // false by default
        const auto first_string{ current_info.m_last_read_page[0].m_name };
        auto nletters{ what.size() < first_string.size() ? what.size() : first_string.size() };

        for(int index{}; index < nletters; ++index) {
            const auto substring_character{ what[index] };
            const auto string_character{ first_string[index] };
            if(substring_character > string_character) {
                break;
            }
            if(substring_character == string_character) {
                continue;
            }
            if(substring_character < string_character) {
                is_read_direction_find = true;
                break;
            }
        }
        if(is_read_direction_find) {
            if(current_info.m_page_number > 0) {
                if(readMattersData(--current_info.m_page_number, current_info.m_last_read_page) == ReadingState::Ok) {
                    setMattersNameToComboBox(current_row);
                }
                else {
                    QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось прочитать данные из файла");
                }
            }
            else {
                QMessageBox::about(nullptr, "Элемент отсутствует", "Данного вещества нет в таблице веществ");
            }
        }
        else {
            const auto last_string{ current_info.m_last_read_page.back().m_name };
            auto nletters{ what.size() < last_string.size() ? what.size() : last_string.size() };
            for(int index{}; index < nletters; ++index) {
                const auto substring_character{ what[index] };
                const auto string_character{ last_string[index] };
                if(substring_character < string_character) {
                    break;
                }
                if(substring_character == string_character) {
                    continue;
                }
                if(substring_character > string_character) {
                    is_read_direction_find = true;
                    break;
                }
            }
           if(is_read_direction_find) {
               if(readMattersData(++current_info.m_page_number, current_info.m_last_read_page) == ReadingState::Ok) {
                   setMattersNameToComboBox(current_row);
               }
               else {
                   QMessageBox::warning(nullptr, "Ошибка чтения", "Не удалось прочитать данные из файла");
               }
           }
           else {
                QMessageBox::about(nullptr, "Элемент отсутствует", "Данного вещества нет в таблице веществ");
           }
       }
    }
}

void PollutionWidget::addNewMatterToDatabaseButtonPressed()
{
    auto db_note{ new DatabaseNote };
    db_note->setAttribute(Qt::WA_DeleteOnClose);
    db_note->show();
}

// private functions
template <class ...Flags>
QTableWidgetItem* PollutionWidget::createItem(const QString &text, Flags&&...flags)
{
    auto item{ new QTableWidgetItem };
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(text);
    ((item->setFlags(flags)),...);
    return item;
}

QDoubleSpinBox* PollutionWidget::createDoubleSpinBox(double value, QWidget *owner, double lower_bound, double upper_bound, int decimals)
{
    auto *spin_box{ new QDoubleSpinBox(owner) };
    spin_box->setMinimum(lower_bound);
    spin_box->setMaximum(upper_bound);
    spin_box->setDecimals(decimals);
    spin_box->setValue(value);
    spin_box->setAlignment(Qt::AlignCenter);
    spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
    return spin_box;
}

void PollutionWidget::addMatterToTable(int matter_table_index, const PollutionMatter &matter, QWidget *owner)
{
    auto combo_box{ new QComboBox(owner) }; // thmatter_table_indexs
    combo_box->setEditable(true);
    combo_box->setCurrentText(matter.m_name);
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 0, combo_box);

    auto line{ new QLineEdit(owner) }; // thmatter_table_indexs
    line->setText(matter.m_group);
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 1, line);

    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 2, createDoubleSpinBox(matter.m_part, owner));
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 3, createDoubleSpinBox(matter.m_mpc, owner));
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 4, createDoubleSpinBox(matter.m_bc, owner));
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 5, createDoubleSpinBox(matter.m_sewerc, owner));

    auto box { createDoubleSpinBox(matter.m_maxc, owner) };
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 6, box);

    box = createDoubleSpinBox(matter.m_averagec, owner);
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 7, box);


    box = createDoubleSpinBox(matter.m_maxsewerc, owner);
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(matter_table_index, 8, box);

    setMattersNameToComboBox(matter_table_index, true);
}

void PollutionWidget::setSourceItems(const PointSource &source)
{
    m_ui->name_combo_box->setCurrentText(source.m_name);
    m_ui->type_combo_box_4->setCurrentIndex(0);
    m_ui->x_double_spin_box_4->setValue(source.m_x);
    m_ui->y_double_spin_box_4->setValue(source.m_y);
    m_ui->spending_double_spin_box_4->setValue(source.m_spending);
    m_ui->init_dilution_double_spin_box_4->setValue(source.m_initial_dilution_ratio);
    m_ui->main_dilution_double_spin_box_4->setValue(source.m_main_dilution_ratio);
    m_ui->common_dilution_double_spin_box_4->setValue(source.m_common_dilution_ratio);
    m_ui->vat_double_spin_box_4->setValue(source.m_vat);
}

PointSource PollutionWidget::extractSourceInfo() const
{
    return { m_ui->name_combo_box->currentText(),
             m_ui->x_double_spin_box_4->value(),
             m_ui->y_double_spin_box_4->value(),
             m_ui->spending_double_spin_box_4->value(),
             m_ui->init_dilution_double_spin_box_4->value(),
             m_ui->main_dilution_double_spin_box_4->value(),
             m_ui->common_dilution_double_spin_box_4->value(),
             m_ui->vat_double_spin_box_4->value() };
}

PollutionMatter PollutionWidget::extractMatterInfo(int row) const
{
    const auto *table{ m_ui->matters_table_widget_4 };
    return { qobject_cast<const QComboBox*>(table->cellWidget(row, 0))->currentText(),
             qobject_cast<const QLineEdit*>(table->cellWidget(row, 1))->text(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 2))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 3))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 4))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 5))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 6))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 7))->value(),
             qobject_cast<const QDoubleSpinBox*>(table->cellWidget(row, 8))->value() };
}

void PollutionWidget::setupUiConnections()
{
    connect(m_ui->type_combo_box_4, SIGNAL(currentIndexChanged(int)), // [1]
            this, SLOT(sourceTypeChanged(int)));

    connect(m_ui->add_new_matter_button_4, SIGNAL(pressed()), // [2]
            this, SLOT(addNewMatterButtonPressed()));

    connect(m_ui->delete_selected_matter_button_4, SIGNAL(pressed()),
            this, SLOT(deleteSelectedMatterButtonPressed()));

    connect(m_ui->save_button_4, SIGNAL(accepted()),
            this, SLOT(saveButtonAccepted())); // [4]

    connect(m_ui->save_button_4, SIGNAL(rejected()), // [5]
            this, SLOT(saveButtonRejected()));

    connect(m_ui->add_new_matter_to_table_button, SIGNAL(pressed()),
            this, SLOT(addNewMatterToDatabaseButtonPressed()));
}

void PollutionWidget::setMattersNameToComboBox(const int matter_index, bool is_initialization)
{
    auto *names_box{ qobject_cast<QComboBox*>(m_ui->matters_table_widget_4->cellWidget(matter_index, 0)) };
    names_box->blockSignals(true);
    names_box->clear();
    names_box->addItem("-");

    QStringList search_list;
    auto& current_info{ m_matter_info[matter_index - 1] };
    if(current_info.m_page_number > 0) {
        names_box->addItem("Загрузить предыдущую страницу");
    }
    const static auto matters_init_values{ m_matter_info.front().m_last_read_page }; // will be always first page
    if(is_initialization) {
        for(const auto& note : matters_init_values) {
            names_box->addItem(note.m_name);
            search_list.append(note.m_name);
        }
    }
    else {
        for(const auto& note : current_info.m_last_read_page) {
            names_box->addItem(note.m_name);
            search_list.append(note.m_name);
        }
    }
    names_box->addItem("Загрузить следующую страницу");
    names_box->blockSignals(false);

    auto search_completer{ new QCompleter(search_list, names_box) };
    search_completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    search_completer->setCaseSensitivity(Qt::CaseInsensitive);
    search_completer->setFilterMode(Qt::MatchStartsWith);
}
