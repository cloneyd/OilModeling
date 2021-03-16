/********************************************************************************
** Form generated from reading UI file 'polutionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLUTIONWIDGET_H
#define UI_POLUTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolutionWidget
{
public:
    QVBoxLayout *verticalLayout_9;
    QGroupBox *source_parameters_group_box;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *name_layout;
    QLabel *name_label;
    QLineEdit *name_line_edit;
    QVBoxLayout *type_layout;
    QLabel *type_label;
    QComboBox *type_combo_box;
    QVBoxLayout *x_layout;
    QLabel *x_label;
    QDoubleSpinBox *x_double_spin_box;
    QVBoxLayout *y_layout;
    QLabel *y_label;
    QDoubleSpinBox *y_double_spin_box;
    QVBoxLayout *spending_layout;
    QLabel *spending_label;
    QDoubleSpinBox *spending_double_spin_box;
    QVBoxLayout *length_layout;
    QLabel *length_label;
    QDoubleSpinBox *length_double_spin_box;
    QVBoxLayout *direction_layout;
    QLabel *direction_label;
    QDoubleSpinBox *direction_double_spin_box;
    QVBoxLayout *tubes_layout;
    QLabel *tube_number_label;
    QSpinBox *tubes_number_spin_box;
    QVBoxLayout *init_dilution_layout;
    QLabel *init_dilution_label;
    QDoubleSpinBox *init_dilution_double_spin_box;
    QVBoxLayout *main_dilution_layout;
    QLabel *main_dilution_label;
    QDoubleSpinBox *main_dilution_double_spin_box;
    QVBoxLayout *common_dilution_layout;
    QLabel *common_dilution_label;
    QDoubleSpinBox *common_dilution_double_spin_box;
    QGroupBox *matters_group_box;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *matters_table_widget;
    QHBoxLayout *matters_button_layout;
    QSpacerItem *horizontalSpacer;
    QPushButton *add_new_matter_button;
    QPushButton *delete_selected_matter_button;
    QHBoxLayout *save_button_layout;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *save_button;

    void setupUi(QWidget *PolutionWidget)
    {
        if (PolutionWidget->objectName().isEmpty())
            PolutionWidget->setObjectName(QString::fromUtf8("PolutionWidget"));
        PolutionWidget->resize(1024, 768);
        verticalLayout_9 = new QVBoxLayout(PolutionWidget);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        source_parameters_group_box = new QGroupBox(PolutionWidget);
        source_parameters_group_box->setObjectName(QString::fromUtf8("source_parameters_group_box"));
        source_parameters_group_box->setMaximumSize(QSize(1000, 100));
        horizontalLayout = new QHBoxLayout(source_parameters_group_box);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        name_layout = new QVBoxLayout();
        name_layout->setObjectName(QString::fromUtf8("name_layout"));
        name_label = new QLabel(source_parameters_group_box);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(name_label->sizePolicy().hasHeightForWidth());
        name_label->setSizePolicy(sizePolicy);
        name_label->setMaximumSize(QSize(16777215, 20));
        name_label->setAlignment(Qt::AlignCenter);

        name_layout->addWidget(name_label);

        name_line_edit = new QLineEdit(source_parameters_group_box);
        name_line_edit->setObjectName(QString::fromUtf8("name_line_edit"));
        sizePolicy.setHeightForWidth(name_line_edit->sizePolicy().hasHeightForWidth());
        name_line_edit->setSizePolicy(sizePolicy);
        name_line_edit->setMaximumSize(QSize(16777215, 25));
        name_line_edit->setCursorPosition(0);
        name_line_edit->setAlignment(Qt::AlignCenter);

        name_layout->addWidget(name_line_edit);


        horizontalLayout->addLayout(name_layout);

        type_layout = new QVBoxLayout();
        type_layout->setObjectName(QString::fromUtf8("type_layout"));
        type_label = new QLabel(source_parameters_group_box);
        type_label->setObjectName(QString::fromUtf8("type_label"));
        sizePolicy.setHeightForWidth(type_label->sizePolicy().hasHeightForWidth());
        type_label->setSizePolicy(sizePolicy);
        type_label->setMinimumSize(QSize(80, 0));
        type_label->setMaximumSize(QSize(80, 20));
        type_label->setAlignment(Qt::AlignCenter);

        type_layout->addWidget(type_label);

        type_combo_box = new QComboBox(source_parameters_group_box);
        type_combo_box->addItem(QString());
        type_combo_box->addItem(QString());
        type_combo_box->setObjectName(QString::fromUtf8("type_combo_box"));
        sizePolicy.setHeightForWidth(type_combo_box->sizePolicy().hasHeightForWidth());
        type_combo_box->setSizePolicy(sizePolicy);
        type_combo_box->setMinimumSize(QSize(80, 0));
        type_combo_box->setMaximumSize(QSize(80, 25));

        type_layout->addWidget(type_combo_box);


        horizontalLayout->addLayout(type_layout);

        x_layout = new QVBoxLayout();
        x_layout->setObjectName(QString::fromUtf8("x_layout"));
        x_label = new QLabel(source_parameters_group_box);
        x_label->setObjectName(QString::fromUtf8("x_label"));
        sizePolicy.setHeightForWidth(x_label->sizePolicy().hasHeightForWidth());
        x_label->setSizePolicy(sizePolicy);
        x_label->setMaximumSize(QSize(40, 20));
        x_label->setAlignment(Qt::AlignCenter);

        x_layout->addWidget(x_label);

        x_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        x_double_spin_box->setObjectName(QString::fromUtf8("x_double_spin_box"));
        sizePolicy.setHeightForWidth(x_double_spin_box->sizePolicy().hasHeightForWidth());
        x_double_spin_box->setSizePolicy(sizePolicy);
        x_double_spin_box->setMaximumSize(QSize(40, 25));
        x_double_spin_box->setWrapping(false);
        x_double_spin_box->setFrame(true);
        x_double_spin_box->setAlignment(Qt::AlignCenter);
        x_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        x_double_spin_box->setProperty("showGroupSeparator", QVariant(false));
        x_double_spin_box->setDecimals(3);
        x_double_spin_box->setMaximum(100000.000000000000000);

        x_layout->addWidget(x_double_spin_box);


        horizontalLayout->addLayout(x_layout);

        y_layout = new QVBoxLayout();
        y_layout->setObjectName(QString::fromUtf8("y_layout"));
        y_label = new QLabel(source_parameters_group_box);
        y_label->setObjectName(QString::fromUtf8("y_label"));
        sizePolicy.setHeightForWidth(y_label->sizePolicy().hasHeightForWidth());
        y_label->setSizePolicy(sizePolicy);
        y_label->setMaximumSize(QSize(40, 20));
        y_label->setAlignment(Qt::AlignCenter);

        y_layout->addWidget(y_label);

        y_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        y_double_spin_box->setObjectName(QString::fromUtf8("y_double_spin_box"));
        sizePolicy.setHeightForWidth(y_double_spin_box->sizePolicy().hasHeightForWidth());
        y_double_spin_box->setSizePolicy(sizePolicy);
        y_double_spin_box->setMaximumSize(QSize(40, 25));
        y_double_spin_box->setWrapping(false);
        y_double_spin_box->setFrame(true);
        y_double_spin_box->setAlignment(Qt::AlignCenter);
        y_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        y_double_spin_box->setProperty("showGroupSeparator", QVariant(false));
        y_double_spin_box->setDecimals(3);
        y_double_spin_box->setMaximum(100000.000000000000000);

        y_layout->addWidget(y_double_spin_box);


        horizontalLayout->addLayout(y_layout);

        spending_layout = new QVBoxLayout();
        spending_layout->setObjectName(QString::fromUtf8("spending_layout"));
        spending_label = new QLabel(source_parameters_group_box);
        spending_label->setObjectName(QString::fromUtf8("spending_label"));
        sizePolicy.setHeightForWidth(spending_label->sizePolicy().hasHeightForWidth());
        spending_label->setSizePolicy(sizePolicy);
        spending_label->setMaximumSize(QSize(100, 20));
        spending_label->setAlignment(Qt::AlignCenter);

        spending_layout->addWidget(spending_label);

        spending_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        spending_double_spin_box->setObjectName(QString::fromUtf8("spending_double_spin_box"));
        sizePolicy.setHeightForWidth(spending_double_spin_box->sizePolicy().hasHeightForWidth());
        spending_double_spin_box->setSizePolicy(sizePolicy);
        spending_double_spin_box->setMaximumSize(QSize(100, 25));
        spending_double_spin_box->setWrapping(false);
        spending_double_spin_box->setFrame(true);
        spending_double_spin_box->setAlignment(Qt::AlignCenter);
        spending_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spending_double_spin_box->setProperty("showGroupSeparator", QVariant(false));
        spending_double_spin_box->setDecimals(3);
        spending_double_spin_box->setMaximum(100000.000000000000000);

        spending_layout->addWidget(spending_double_spin_box);


        horizontalLayout->addLayout(spending_layout);

        length_layout = new QVBoxLayout();
        length_layout->setObjectName(QString::fromUtf8("length_layout"));
        length_label = new QLabel(source_parameters_group_box);
        length_label->setObjectName(QString::fromUtf8("length_label"));
        sizePolicy.setHeightForWidth(length_label->sizePolicy().hasHeightForWidth());
        length_label->setSizePolicy(sizePolicy);
        length_label->setMaximumSize(QSize(50, 20));
        length_label->setAlignment(Qt::AlignCenter);

        length_layout->addWidget(length_label);

        length_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        length_double_spin_box->setObjectName(QString::fromUtf8("length_double_spin_box"));
        length_double_spin_box->setEnabled(false);
        sizePolicy.setHeightForWidth(length_double_spin_box->sizePolicy().hasHeightForWidth());
        length_double_spin_box->setSizePolicy(sizePolicy);
        length_double_spin_box->setMaximumSize(QSize(40, 25));
        length_double_spin_box->setWrapping(false);
        length_double_spin_box->setFrame(true);
        length_double_spin_box->setAlignment(Qt::AlignCenter);
        length_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        length_double_spin_box->setProperty("showGroupSeparator", QVariant(false));
        length_double_spin_box->setDecimals(3);
        length_double_spin_box->setMaximum(100000.000000000000000);

        length_layout->addWidget(length_double_spin_box);


        horizontalLayout->addLayout(length_layout);

        direction_layout = new QVBoxLayout();
        direction_layout->setObjectName(QString::fromUtf8("direction_layout"));
        direction_label = new QLabel(source_parameters_group_box);
        direction_label->setObjectName(QString::fromUtf8("direction_label"));
        sizePolicy.setHeightForWidth(direction_label->sizePolicy().hasHeightForWidth());
        direction_label->setSizePolicy(sizePolicy);
        direction_label->setMaximumSize(QSize(16777215, 30));
        direction_label->setAlignment(Qt::AlignCenter);

        direction_layout->addWidget(direction_label);

        direction_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        direction_double_spin_box->setObjectName(QString::fromUtf8("direction_double_spin_box"));
        direction_double_spin_box->setEnabled(false);
        sizePolicy.setHeightForWidth(direction_double_spin_box->sizePolicy().hasHeightForWidth());
        direction_double_spin_box->setSizePolicy(sizePolicy);
        direction_double_spin_box->setMaximumSize(QSize(16777215, 25));
        direction_double_spin_box->setWrapping(false);
        direction_double_spin_box->setFrame(true);
        direction_double_spin_box->setAlignment(Qt::AlignCenter);
        direction_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        direction_double_spin_box->setProperty("showGroupSeparator", QVariant(false));
        direction_double_spin_box->setDecimals(3);
        direction_double_spin_box->setMaximum(100000.000000000000000);

        direction_layout->addWidget(direction_double_spin_box);


        horizontalLayout->addLayout(direction_layout);

        tubes_layout = new QVBoxLayout();
        tubes_layout->setObjectName(QString::fromUtf8("tubes_layout"));
        tube_number_label = new QLabel(source_parameters_group_box);
        tube_number_label->setObjectName(QString::fromUtf8("tube_number_label"));
        sizePolicy.setHeightForWidth(tube_number_label->sizePolicy().hasHeightForWidth());
        tube_number_label->setSizePolicy(sizePolicy);
        tube_number_label->setMaximumSize(QSize(100, 30));
        tube_number_label->setAlignment(Qt::AlignCenter);

        tubes_layout->addWidget(tube_number_label);

        tubes_number_spin_box = new QSpinBox(source_parameters_group_box);
        tubes_number_spin_box->setObjectName(QString::fromUtf8("tubes_number_spin_box"));
        tubes_number_spin_box->setEnabled(false);
        tubes_number_spin_box->setAlignment(Qt::AlignCenter);
        tubes_number_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        tubes_number_spin_box->setMaximum(10000);

        tubes_layout->addWidget(tubes_number_spin_box);


        horizontalLayout->addLayout(tubes_layout);

        init_dilution_layout = new QVBoxLayout();
        init_dilution_layout->setObjectName(QString::fromUtf8("init_dilution_layout"));
        init_dilution_label = new QLabel(source_parameters_group_box);
        init_dilution_label->setObjectName(QString::fromUtf8("init_dilution_label"));
        init_dilution_label->setMaximumSize(QSize(120, 30));
        init_dilution_label->setAlignment(Qt::AlignCenter);

        init_dilution_layout->addWidget(init_dilution_label);

        init_dilution_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        init_dilution_double_spin_box->setObjectName(QString::fromUtf8("init_dilution_double_spin_box"));
        init_dilution_double_spin_box->setMaximumSize(QSize(100, 20));
        init_dilution_double_spin_box->setFrame(false);
        init_dilution_double_spin_box->setAlignment(Qt::AlignCenter);
        init_dilution_double_spin_box->setReadOnly(true);
        init_dilution_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        init_dilution_double_spin_box->setDecimals(3);
        init_dilution_double_spin_box->setMaximum(10000.000000000000000);

        init_dilution_layout->addWidget(init_dilution_double_spin_box);


        horizontalLayout->addLayout(init_dilution_layout);

        main_dilution_layout = new QVBoxLayout();
        main_dilution_layout->setObjectName(QString::fromUtf8("main_dilution_layout"));
        main_dilution_label = new QLabel(source_parameters_group_box);
        main_dilution_label->setObjectName(QString::fromUtf8("main_dilution_label"));
        main_dilution_label->setMaximumSize(QSize(130, 30));
        main_dilution_label->setAlignment(Qt::AlignCenter);

        main_dilution_layout->addWidget(main_dilution_label);

        main_dilution_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        main_dilution_double_spin_box->setObjectName(QString::fromUtf8("main_dilution_double_spin_box"));
        main_dilution_double_spin_box->setMaximumSize(QSize(100, 20));
        main_dilution_double_spin_box->setFrame(false);
        main_dilution_double_spin_box->setAlignment(Qt::AlignCenter);
        main_dilution_double_spin_box->setReadOnly(true);
        main_dilution_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        main_dilution_double_spin_box->setDecimals(3);
        main_dilution_double_spin_box->setMaximum(10000.000000000000000);

        main_dilution_layout->addWidget(main_dilution_double_spin_box);


        horizontalLayout->addLayout(main_dilution_layout);

        common_dilution_layout = new QVBoxLayout();
        common_dilution_layout->setObjectName(QString::fromUtf8("common_dilution_layout"));
        common_dilution_label = new QLabel(source_parameters_group_box);
        common_dilution_label->setObjectName(QString::fromUtf8("common_dilution_label"));
        common_dilution_label->setMaximumSize(QSize(130, 30));
        common_dilution_label->setAlignment(Qt::AlignCenter);

        common_dilution_layout->addWidget(common_dilution_label);

        common_dilution_double_spin_box = new QDoubleSpinBox(source_parameters_group_box);
        common_dilution_double_spin_box->setObjectName(QString::fromUtf8("common_dilution_double_spin_box"));
        common_dilution_double_spin_box->setMaximumSize(QSize(100, 20));
        common_dilution_double_spin_box->setFrame(false);
        common_dilution_double_spin_box->setAlignment(Qt::AlignCenter);
        common_dilution_double_spin_box->setReadOnly(true);
        common_dilution_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        common_dilution_double_spin_box->setDecimals(3);
        common_dilution_double_spin_box->setMaximum(10000.000000000000000);

        common_dilution_layout->addWidget(common_dilution_double_spin_box);


        horizontalLayout->addLayout(common_dilution_layout);


        verticalLayout_9->addWidget(source_parameters_group_box);

        matters_group_box = new QGroupBox(PolutionWidget);
        matters_group_box->setObjectName(QString::fromUtf8("matters_group_box"));
        verticalLayout_10 = new QVBoxLayout(matters_group_box);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        matters_table_widget = new QTableWidget(matters_group_box);
        matters_table_widget->setObjectName(QString::fromUtf8("matters_table_widget"));
        matters_table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
        matters_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_10->addWidget(matters_table_widget);

        matters_button_layout = new QHBoxLayout();
        matters_button_layout->setObjectName(QString::fromUtf8("matters_button_layout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        matters_button_layout->addItem(horizontalSpacer);

        add_new_matter_button = new QPushButton(matters_group_box);
        add_new_matter_button->setObjectName(QString::fromUtf8("add_new_matter_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(add_new_matter_button->sizePolicy().hasHeightForWidth());
        add_new_matter_button->setSizePolicy(sizePolicy1);
        add_new_matter_button->setMaximumSize(QSize(150, 20));

        matters_button_layout->addWidget(add_new_matter_button);

        delete_selected_matter_button = new QPushButton(matters_group_box);
        delete_selected_matter_button->setObjectName(QString::fromUtf8("delete_selected_matter_button"));
        delete_selected_matter_button->setMaximumSize(QSize(170, 20));

        matters_button_layout->addWidget(delete_selected_matter_button);


        verticalLayout_10->addLayout(matters_button_layout);

        save_button_layout = new QHBoxLayout();
        save_button_layout->setObjectName(QString::fromUtf8("save_button_layout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        save_button_layout->addItem(horizontalSpacer_2);

        save_button = new QDialogButtonBox(matters_group_box);
        save_button->setObjectName(QString::fromUtf8("save_button"));
        save_button->setMaximumSize(QSize(160, 16777215));
        save_button->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        save_button_layout->addWidget(save_button);


        verticalLayout_10->addLayout(save_button_layout);


        verticalLayout_9->addWidget(matters_group_box);


        retranslateUi(PolutionWidget);
        QObject::connect(add_new_matter_button, SIGNAL(pressed()), PolutionWidget, SLOT(addNewMatterButtonPressed()));
        QObject::connect(delete_selected_matter_button, SIGNAL(pressed()), PolutionWidget, SLOT(deleteSelectedMatterButtonPressed()));
        QObject::connect(save_button, SIGNAL(accepted()), PolutionWidget, SLOT(saveButtonAccepted()));
        QObject::connect(save_button, SIGNAL(rejected()), PolutionWidget, SLOT(saveButtonRejected()));

        QMetaObject::connectSlotsByName(PolutionWidget);
    } // setupUi

    void retranslateUi(QWidget *PolutionWidget)
    {
        PolutionWidget->setWindowTitle(QCoreApplication::translate("PolutionWidget", "Form", nullptr));
        source_parameters_group_box->setTitle(QCoreApplication::translate("PolutionWidget", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        name_label->setText(QCoreApplication::translate("PolutionWidget", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        type_label->setText(QCoreApplication::translate("PolutionWidget", "\320\242\320\270\320\277", nullptr));
        type_combo_box->setItemText(0, QCoreApplication::translate("PolutionWidget", "\320\242\320\276\321\207\320\265\321\207\320\275\321\213\320\271", nullptr));
        type_combo_box->setItemText(1, QCoreApplication::translate("PolutionWidget", "\320\224\320\270\321\204\321\204\321\203\320\267\320\270\320\276\320\275\321\213\320\271", nullptr));

        x_label->setText(QCoreApplication::translate("PolutionWidget", "X, \320\274", nullptr));
        y_label->setText(QCoreApplication::translate("PolutionWidget", "Y, \320\274", nullptr));
        spending_label->setText(QCoreApplication::translate("PolutionWidget", "<html><head/><body><p>\320\240\320\260\321\201\321\205\320\276\320\264, \320\274<span style=\" vertical-align:super;\">3</span>/\321\201</p></body></html>", nullptr));
        length_label->setText(QCoreApplication::translate("PolutionWidget", "\320\224\320\273\320\270\320\275\320\260, \320\274", nullptr));
        direction_label->setText(QCoreApplication::translate("PolutionWidget", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \n"
"\320\262\321\213\320\277\321\203\321\201\320\272\320\260, \320\263\321\200\320\260\320\264", nullptr));
        tube_number_label->setText(QCoreApplication::translate("PolutionWidget", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\320\277\320\260\321\202\321\200\321\203\320\261\320\272\320\276\320\262", nullptr));
        init_dilution_label->setText(QCoreApplication::translate("PolutionWidget", "\320\232\321\200\320\260\321\202\320\275\320\276\321\201\321\202\321\214 \320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\263\320\276\n"
" \321\200\320\260\320\267\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        main_dilution_label->setText(QCoreApplication::translate("PolutionWidget", "\320\232\321\200\320\260\321\202\320\275\320\276\321\201\321\202\321\214 \320\276\321\201\320\275\320\276\320\262\320\275\320\276\320\263\320\276\n"
"\321\200\320\260\320\267\320\261\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        common_dilution_label->setText(QCoreApplication::translate("PolutionWidget", "\320\236\320\261\321\211\320\265\320\265 \321\200\320\260\320\267\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        matters_group_box->setTitle(QCoreApplication::translate("PolutionWidget", "\320\227\320\260\320\263\321\200\321\217\320\267\320\275\321\217\321\216\321\211\320\270\320\265 \320\262\320\265\321\211\320\265\321\201\321\202\320\262\320\260", nullptr));
        add_new_matter_button->setText(QCoreApplication::translate("PolutionWidget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\320\276\320\265 \320\262\320\265\321\211\320\265\321\201\321\202\320\262\320\276", nullptr));
        delete_selected_matter_button->setText(QCoreApplication::translate("PolutionWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\320\276\320\265 \320\262\320\265\321\211\320\265\321\201\321\202\320\262\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PolutionWidget: public Ui_PolutionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLUTIONWIDGET_H
