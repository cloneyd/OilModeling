#include "polutionwidget.hpp"
#include "ui_polutionwidget.h"

#include <QLineEdit>
#include <QTableWidgetItem>


extern void showErrorMessageBox(const QString &msg, const QString &title = "");


PolutionWidget::PolutionWidget(WidgetMode mode, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PolutionWidget),
    m_mode{ mode },
    m_myindex{}
{
    m_ui->setupUi(this);

    m_ui->matters_table_widget->setColumnCount(9);
    m_ui->matters_table_widget->setRowCount(2);
    addItemToMattersTable(0, 0, "Вещество");
    addItemToMattersTable(0, 1, "Группа ЛПВ");
    addItemToMattersTable(0, 2, "Доля ЛПВ");
    addItemToMattersTable(0, 3, "ПДК, мг/дм^3");
    addItemToMattersTable(0, 4, "Сф, мг/дм^3");
    addItemToMattersTable(0, 5, "Сст, мг/дм^3");
    addItemToMattersTable(0, 6, "Сmax, мг/дм^3");
    addItemToMattersTable(0, 7, "Сср, мг/дм^3");
    addItemToMattersTable(0, 8, "Сст.доп, мг/дм^3");

    addWidgetsToMattersTable(1);

    setWindowTitle("Источник");

    connect(m_ui->type_combo_box, SIGNAL(currentIndexChanged(int)),
            this, SLOT(typeChanged(int)));
}

PolutionWidget::~PolutionWidget()
{
    delete m_ui;
}


// private slots
void PolutionWidget::typeChanged(int index)
{
    Q_ASSERT_X(index >= SourceType::MIN && index <= SourceType::MAX,
                "Class - PolutionWidget", "Function - typeChanged, problem - wrong index");
    switch(index) {
    case SourceType::Point:
        m_ui->length_double_spin_box->setEnabled(false);
        m_ui->direction_double_spin_box->setEnabled(false);
        m_ui->tubes_number_spin_box->setEnabled(false);
        break;

    case SourceType::Diffusion:
        m_ui->length_double_spin_box->setEnabled(true);
        m_ui->direction_double_spin_box->setEnabled(true);
        m_ui->tubes_number_spin_box->setEnabled(true);
        break;
    }
}

void PolutionWidget::addNewMatterButtonPressed()
{
    auto nrows{ m_ui->matters_table_widget->rowCount() };
    m_ui->matters_table_widget->setRowCount(nrows + 1);
    addWidgetsToMattersTable(nrows);
}

void PolutionWidget::deleteSelectedMatterButtonPressed()
{
    auto row{ m_ui->matters_table_widget->currentRow() };
    if(row == 0) return;

    m_ui->matters_table_widget->removeRow(row);
}

void PolutionWidget::saveButtonAccepted()
{
    auto current_type_index{ m_ui->type_combo_box->currentIndex() };
    Q_ASSERT_X(current_type_index >= SourceType::MIN && current_type_index <= SourceType::MAX,
               "Class - PolutionWidget", "Function - saveButtonClicked, problem - wrong index");

    std::variant<PointSource, DiffusionSource> source;
    switch(current_type_index) {
    case SourceType::Point:
        source.emplace<0>(PointSource{ m_ui->name_line_edit->text(),
                                       m_ui->x_double_spin_box->value(),
                                       m_ui->y_double_spin_box->value(),
                                       m_ui->spending_double_spin_box->value(),
                                       -1., -1., -1., -1.});
        break;

    case SourceType::Diffusion:
        source.emplace<1>(DiffusionSource{ { m_ui->name_line_edit->text(),
                                           m_ui->x_double_spin_box->value(),
                                           m_ui->y_double_spin_box->value(),
                                           m_ui->spending_double_spin_box->value(),
                                           -1., -1., -1., -1. }, // PointSource init
                                           m_ui->length_double_spin_box->value(),
                                           m_ui->direction_double_spin_box->value(),
                                           m_ui->tubes_number_spin_box->value() });
        break;
    }

    auto nmatters{ m_ui->matters_table_widget->rowCount() - 1 }; // except first row
    QVector<PolutionMatter> matters(nmatters);
    for(int i{}; i < nmatters; ++i) {
        matters[i].m_name = qobject_cast<QLineEdit*>(m_ui->matters_table_widget->cellWidget(i + 1, 0))->text();
        matters[i].m_group = qobject_cast<QLineEdit*>(m_ui->matters_table_widget->cellWidget(i + 1, 1))->text();
        matters[i].m_part = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 2))->value();
        matters[i].m_mpc = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 3))->value();
        matters[i].m_bc = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 4))->value();
        matters[i].m_sewerc = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 5))->value();
    }

    if(m_mode == WidgetMode::Create) {
        for(int i{}; i < nmatters; ++i) {
            matters[i].m_maxc = -1.;
            matters[i].m_averagec = -1.;
            matters[i].m_maxsewerc = -1.;
        }

        emit sourceCreated(source, matters);
    }
    else {
        for(int i{}; i < nmatters; ++i) {
            matters[i].m_maxc = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 6))->value();
            matters[i].m_averagec = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 7))->value();
            matters[i].m_maxsewerc = qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 8))->value();
        }

        if(current_type_index == SourceType::Point) {
            auto &&source_ref{ std::get<PointSource>(source) };
            source_ref.m_initial_dilution_ratio = m_ui->init_dilution_double_spin_box->value();
            source_ref.m_main_dilution_ratio = m_ui->main_dilution_double_spin_box->value();
            source_ref.m_common_dilution_ratio = m_ui->common_dilution_double_spin_box->value();
            source_ref.m_vat = m_ui->vat_double_spin_box->value();
        }
        else {
            auto &&source_ref{ std::get<DiffusionSource>(source) };
            source_ref.m_initial_dilution_ratio = m_ui->init_dilution_double_spin_box->value();
            source_ref.m_main_dilution_ratio = m_ui->main_dilution_double_spin_box->value();
            source_ref.m_common_dilution_ratio = m_ui->common_dilution_double_spin_box->value();
            source_ref.m_vat = m_ui->vat_double_spin_box->value();
        }

        emit sourceUpdated(m_myindex, source, matters);
    }

    close();
}


// setters
void PolutionWidget::setSource(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters)
{
    if(source.index() == 0) {
        PointSource current_source{ std::get<PointSource>(source) };
        getPointSourceItems(current_source);
    }
    else {
        DiffusionSource current_source{ std::get<DiffusionSource>(source) };
        getPointSourceItems(current_source);
        m_ui->type_combo_box->setCurrentIndex(SourceType::Diffusion);
        m_ui->length_double_spin_box->setValue(current_source.m_length);
        m_ui->direction_double_spin_box->setValue(current_source.m_direction);
        m_ui->tubes_number_spin_box->setValue(current_source.m_tubes_number);
    }

    const auto nmatters{ matters.size() };
    m_ui->matters_table_widget->setRowCount(nmatters + 1);
    for(int i{}; i < nmatters; ++i) {
        addWidgetsToMattersTable(i + 1);
        qobject_cast<QLineEdit*>(m_ui->matters_table_widget->cellWidget(i + 1, 0))->setText(matters[i].m_name);
        qobject_cast<QLineEdit*>(m_ui->matters_table_widget->cellWidget(i + 1, 1))->setText(matters[i].m_group);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 2))->setValue(matters[i].m_part);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 3))->setValue(matters[i].m_mpc);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 4))->setValue(matters[i].m_bc);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 5))->setValue(matters[i].m_sewerc);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 6))->setValue(matters[i].m_maxc);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 7))->setValue(matters[i].m_averagec);
        qobject_cast<QDoubleSpinBox*>(m_ui->matters_table_widget->cellWidget(i + 1, 8))->setValue(matters[i].m_maxsewerc);
    }
}


// private functions
void PolutionWidget::addItemToMattersTable(int row, int col, const QString &text)
{
    auto item{ new QTableWidgetItem };
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(text);
    item->setFlags(Qt::NoItemFlags);
    m_ui->matters_table_widget->setItem(row, col, item);
}

void PolutionWidget::addWidgetsToMattersTable(int row)
{
    auto line_edit{ new QLineEdit };
    line_edit->setAlignment(Qt::AlignCenter);
    m_ui->matters_table_widget->setCellWidget(row, 0, line_edit);

    line_edit = new QLineEdit;
    line_edit->setAlignment(Qt::AlignCenter);
    m_ui->matters_table_widget->setCellWidget(row, 1, line_edit);

    for(int i{ 2 }; i <= 5; ++i) {
        m_ui->matters_table_widget->setCellWidget(row, i, createDoubleSpinBox());
    }
    auto box{ createDoubleSpinBox() };
    box->setReadOnly(true);
    m_ui->matters_table_widget->setCellWidget(row, 6, box);

    box = createDoubleSpinBox();
    box->setReadOnly(true);
    m_ui->matters_table_widget->setCellWidget(row, 7, box);

    box = createDoubleSpinBox();
    box->setReadOnly(true);
    m_ui->matters_table_widget->setCellWidget(row, 8, box);
}

QDoubleSpinBox* PolutionWidget::createDoubleSpinBox(double lower, double upper, int decimals)
{
    auto double_spin_box{ new QDoubleSpinBox };
    double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
    double_spin_box->setDecimals(decimals);
    double_spin_box->setMinimum(lower);
    double_spin_box->setMaximum(upper);
    return double_spin_box;
}

void PolutionWidget::getPointSourceItems(const PointSource &current_source)
{
    m_ui->name_line_edit->setText(current_source.m_name);
    m_ui->type_combo_box->setCurrentIndex(SourceType::Point);
    m_ui->x_double_spin_box->setValue(current_source.m_x);
    m_ui->y_double_spin_box->setValue(current_source.m_y);
    m_ui->spending_double_spin_box->setValue(current_source.m_spending);
    m_ui->init_dilution_double_spin_box->setValue(current_source.m_initial_dilution_ratio);
    m_ui->main_dilution_double_spin_box->setValue(current_source.m_main_dilution_ratio);
    m_ui->common_dilution_double_spin_box->setValue(current_source.m_common_dilution_ratio);
    m_ui->vat_double_spin_box->setValue(current_source.m_vat);
}
