#include "pollutionwidget.hpp"
#include "ui_pollutionwidget.h"

PollutionWidget::PollutionWidget(WidgetMode mode, QWidget *parent) :
    QWidget(parent),
    m_source_index{ -1 },
    m_mode{ mode },
    m_ui(std::make_unique<Ui::PollutionWidget>())
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

void PollutionWidget::addNewMatterButtonPressed()
{
    const auto nrows{ m_ui->matters_table_widget_4->rowCount() };
    m_ui->matters_table_widget_4->setRowCount(nrows + 1);
    addMatterToTable(nrows, { {}, {}, -1., -1., -1., -1. -1., -1., -1., -1. });
}

void PollutionWidget::deleteSelectedMatterButtonPressed()
{
    const auto row{ m_ui->matters_table_widget_4->currentRow() };
    if(row == 0)    return;
    m_ui->matters_table_widget_4->removeRow(row);
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

void PollutionWidget::addMatterToTable(int row, const PollutionMatter &matter, QWidget *owner)
{
    auto combo_box{ new QComboBox(owner) }; // throws
    combo_box->setEditable(true);
    combo_box->setCurrentText(matter.m_name);
    m_ui->matters_table_widget_4->setCellWidget(row, 0, combo_box);

    combo_box = new QComboBox(owner);
    combo_box->setEditable(true);
    combo_box->setCurrentText(matter.m_group);
    m_ui->matters_table_widget_4->setCellWidget(row, 1, combo_box);

    m_ui->matters_table_widget_4->setCellWidget(row, 2, createDoubleSpinBox(matter.m_part, owner));
    m_ui->matters_table_widget_4->setCellWidget(row, 3, createDoubleSpinBox(matter.m_mpc, owner));
    m_ui->matters_table_widget_4->setCellWidget(row, 4, createDoubleSpinBox(matter.m_bc, owner));
    m_ui->matters_table_widget_4->setCellWidget(row, 5, createDoubleSpinBox(matter.m_sewerc, owner));

    auto box { createDoubleSpinBox(matter.m_maxc, owner) };
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(row, 6, box);

    box = createDoubleSpinBox(matter.m_averagec, owner);
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(row, 7, box);


    box = createDoubleSpinBox(matter.m_maxsewerc, owner);
    box->setReadOnly(true);
    m_ui->matters_table_widget_4->setCellWidget(row, 8, box);
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
             qobject_cast<const QComboBox*>(table->cellWidget(row, 1))->currentText(),
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
}
