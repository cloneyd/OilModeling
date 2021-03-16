/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *main_panel_tab_widget;
    QWidget *enter_data_tab;
    QLabel *x_coordinate_label;
    QLabel *y_coordinate_label;
    QLabel *scale_label;
    QLabel *water_object_type_label;
    QFrame *tab_widget_delimeter_line;
    QDoubleSpinBox *x_coordinate_double_spin_box;
    QDoubleSpinBox *y_coordinate_double_spin_box;
    QLabel *cell_width_label;
    QLabel *cell_height_label;
    QDoubleSpinBox *cell_width_spin_box;
    QDoubleSpinBox *cell_height_spin_box;
    QComboBox *water_object_type_combo_box;
    QPushButton *load_from_pc_button;
    QDoubleSpinBox *scale_spin_box;
    QPushButton *load_from_site_button;
    QPushButton *edit_image_button;
    QWidget *output_data_tab;
    QFrame *save_wind_delimeter_line;
    QFrame *sav_map_delimeter_line;
    QComboBox *map_save_format_combo_box;
    QLabel *map_saver_format_label;
    QPushButton *save_map_button;
    QFrame *save_in_zip_delimeter_line;
    QPushButton *open_map_visualization_button;
    QPushButton *save_in_zip_button;
    QComboBox *wind_save_format_combo_box;
    QPushButton *save_wind_button;
    QLabel *wind_saver_format_label;
    QWidget *wind_tab;
    QPushButton *computate_speeds_button;
    QPushButton *enter_speed_vectors_button;
    QFrame *computator_parameters_delimeter_line;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *horizon_label;
    QDoubleSpinBox *horizon_spin_box;
    QLabel *ratio_label;
    QDoubleSpinBox *ratio_double_spin_box;
    QLabel *atol_label;
    QDoubleSpinBox *atol_percents_spin_box;
    QDoubleSpinBox *abs_wind_speed_spin_box;
    QLabel *abs_wind_speed_label;
    QFrame *computator_parameters_delimeter_line_2;
    QGroupBox *wind_direction_group_box;
    QGridLayout *gridLayout_5;
    QComboBox *system_combo_box;
    QCheckBox *system_check_box;
    QCheckBox *azimuth_check_box;
    QDoubleSpinBox *azimuth_double_spin_box;
    QPushButton *force_abs_speed_decompose_button;
    QWidget *relief_tab;
    QPushButton *enter_heights_button;
    QPushButton *load_heights_from_file_button;
    QPushButton *save_heights_button;
    QWidget *polution_tab;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *polution_computations_distance_label;
    QDoubleSpinBox *max_computations_distance_double_spin_box;
    QHBoxLayout *horizontalLayout_3;
    QToolBox *display_info_tool_box;
    QWidget *map_image_widget;
    QVBoxLayout *verticalLayout_2;
    QWebEngineView *map_web_engine;
    QHBoxLayout *horizontalLayout_4;
    QLabel *data_service_name_label;
    QLabel *current_service_name_label;
    QWidget *map_image_page;
    QHBoxLayout *horizontalLayout_2;
    QLabel *grid_map_label;
    QWidget *relief_page;
    QGridLayout *gridLayout_3;
    QTabWidget *relief_tab_page;
    QWidget *winds_direction_page;
    QGridLayout *gridLayout_4;
    QTabWidget *winds_direction_tab;
    QWidget *winds_image_container_tab;
    QGridLayout *gridLayout_2;
    QGroupBox *legend_group_box;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *map_with_winds_label;
    QWidget *polution_page;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *sources_table_widget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *add_new_polution_source_button;
    QPushButton *current_source_matter_button;
    QPushButton *delete_polution_source_button;
    QGroupBox *saved_in_current_session_files_group_box;
    QGridLayout *gridLayout_6;
    QListWidget *saved_files_list_box;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1533, 950);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        main_panel_tab_widget = new QTabWidget(centralwidget);
        main_panel_tab_widget->setObjectName(QString::fromUtf8("main_panel_tab_widget"));
        main_panel_tab_widget->setEnabled(true);
        main_panel_tab_widget->setMinimumSize(QSize(0, 150));
        main_panel_tab_widget->setMaximumSize(QSize(16777215, 150));
        QPalette palette;
        QBrush brush(QColor(56, 37, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(150, 187, 124, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush2);
        QBrush brush3(QColor(18, 59, 54, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush2);
        QBrush brush5(QColor(0, 120, 215, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        main_panel_tab_widget->setPalette(palette);
        main_panel_tab_widget->setDocumentMode(false);
        main_panel_tab_widget->setTabsClosable(false);
        main_panel_tab_widget->setMovable(false);
        enter_data_tab = new QWidget();
        enter_data_tab->setObjectName(QString::fromUtf8("enter_data_tab"));
        x_coordinate_label = new QLabel(enter_data_tab);
        x_coordinate_label->setObjectName(QString::fromUtf8("x_coordinate_label"));
        x_coordinate_label->setGeometry(QRect(10, 10, 16, 31));
        y_coordinate_label = new QLabel(enter_data_tab);
        y_coordinate_label->setObjectName(QString::fromUtf8("y_coordinate_label"));
        y_coordinate_label->setGeometry(QRect(10, 60, 16, 31));
        scale_label = new QLabel(enter_data_tab);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setGeometry(QRect(160, 20, 61, 21));
        water_object_type_label = new QLabel(enter_data_tab);
        water_object_type_label->setObjectName(QString::fromUtf8("water_object_type_label"));
        water_object_type_label->setGeometry(QRect(490, 10, 131, 31));
        tab_widget_delimeter_line = new QFrame(enter_data_tab);
        tab_widget_delimeter_line->setObjectName(QString::fromUtf8("tab_widget_delimeter_line"));
        tab_widget_delimeter_line->setGeometry(QRect(690, 10, 16, 81));
        tab_widget_delimeter_line->setFrameShape(QFrame::VLine);
        tab_widget_delimeter_line->setFrameShadow(QFrame::Sunken);
        x_coordinate_double_spin_box = new QDoubleSpinBox(enter_data_tab);
        x_coordinate_double_spin_box->setObjectName(QString::fromUtf8("x_coordinate_double_spin_box"));
        x_coordinate_double_spin_box->setGeometry(QRect(50, 12, 91, 31));
        x_coordinate_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        x_coordinate_double_spin_box->setDecimals(7);
        x_coordinate_double_spin_box->setMaximum(99.000000000000000);
        y_coordinate_double_spin_box = new QDoubleSpinBox(enter_data_tab);
        y_coordinate_double_spin_box->setObjectName(QString::fromUtf8("y_coordinate_double_spin_box"));
        y_coordinate_double_spin_box->setGeometry(QRect(50, 60, 91, 31));
        y_coordinate_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        y_coordinate_double_spin_box->setDecimals(7);
        cell_width_label = new QLabel(enter_data_tab);
        cell_width_label->setObjectName(QString::fromUtf8("cell_width_label"));
        cell_width_label->setGeometry(QRect(280, 10, 101, 31));
        cell_height_label = new QLabel(enter_data_tab);
        cell_height_label->setObjectName(QString::fromUtf8("cell_height_label"));
        cell_height_label->setGeometry(QRect(280, 60, 101, 31));
        cell_width_spin_box = new QDoubleSpinBox(enter_data_tab);
        cell_width_spin_box->setObjectName(QString::fromUtf8("cell_width_spin_box"));
        cell_width_spin_box->setGeometry(QRect(380, 20, 91, 25));
        cell_width_spin_box->setAlignment(Qt::AlignCenter);
        cell_width_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        cell_width_spin_box->setDecimals(3);
        cell_width_spin_box->setMaximum(500000.000000000000000);
        cell_width_spin_box->setSingleStep(0.500000000000000);
        cell_width_spin_box->setValue(10.000000000000000);
        cell_height_spin_box = new QDoubleSpinBox(enter_data_tab);
        cell_height_spin_box->setObjectName(QString::fromUtf8("cell_height_spin_box"));
        cell_height_spin_box->setGeometry(QRect(380, 60, 91, 25));
        cell_height_spin_box->setAlignment(Qt::AlignCenter);
        cell_height_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        cell_height_spin_box->setDecimals(3);
        cell_height_spin_box->setMaximum(500000.000000000000000);
        cell_height_spin_box->setSingleStep(0.500000000000000);
        cell_height_spin_box->setStepType(QAbstractSpinBox::DefaultStepType);
        cell_height_spin_box->setValue(10.000000000000000);
        water_object_type_combo_box = new QComboBox(enter_data_tab);
        water_object_type_combo_box->addItem(QString());
        water_object_type_combo_box->addItem(QString());
        water_object_type_combo_box->setObjectName(QString::fromUtf8("water_object_type_combo_box"));
        water_object_type_combo_box->setGeometry(QRect(500, 60, 101, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(water_object_type_combo_box->sizePolicy().hasHeightForWidth());
        water_object_type_combo_box->setSizePolicy(sizePolicy);
        water_object_type_combo_box->setMinimumSize(QSize(0, 0));
        water_object_type_combo_box->setMaximumSize(QSize(16777215, 16777215));
        water_object_type_combo_box->setBaseSize(QSize(70, 20));
        water_object_type_combo_box->setEditable(false);
        load_from_pc_button = new QPushButton(enter_data_tab);
        load_from_pc_button->setObjectName(QString::fromUtf8("load_from_pc_button"));
        load_from_pc_button->setGeometry(QRect(830, 20, 100, 60));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(load_from_pc_button->sizePolicy().hasHeightForWidth());
        load_from_pc_button->setSizePolicy(sizePolicy1);
        load_from_pc_button->setMinimumSize(QSize(100, 60));
        load_from_pc_button->setMaximumSize(QSize(100, 60));
        load_from_pc_button->setBaseSize(QSize(100, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/imgs/images/fws.png"), QSize(), QIcon::Normal, QIcon::Off);
        load_from_pc_button->setIcon(icon);
        load_from_pc_button->setIconSize(QSize(40, 40));
        load_from_pc_button->setFlat(false);
        scale_spin_box = new QDoubleSpinBox(enter_data_tab);
        scale_spin_box->setObjectName(QString::fromUtf8("scale_spin_box"));
        scale_spin_box->setGeometry(QRect(160, 60, 91, 25));
        scale_spin_box->setAlignment(Qt::AlignCenter);
        scale_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        scale_spin_box->setProperty("showGroupSeparator", QVariant(false));
        scale_spin_box->setDecimals(3);
        scale_spin_box->setMaximum(1000000.000000000000000);
        scale_spin_box->setSingleStep(0.500000000000000);
        scale_spin_box->setValue(10.000000000000000);
        load_from_site_button = new QPushButton(enter_data_tab);
        load_from_site_button->setObjectName(QString::fromUtf8("load_from_site_button"));
        load_from_site_button->setGeometry(QRect(720, 20, 100, 60));
        sizePolicy1.setHeightForWidth(load_from_site_button->sizePolicy().hasHeightForWidth());
        load_from_site_button->setSizePolicy(sizePolicy1);
        load_from_site_button->setMinimumSize(QSize(100, 60));
        load_from_site_button->setMaximumSize(QSize(100, 60));
        load_from_site_button->setBaseSize(QSize(100, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/imgs/images/load_from_site_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        load_from_site_button->setIcon(icon1);
        load_from_site_button->setIconSize(QSize(40, 40));
        load_from_site_button->setFlat(false);
        edit_image_button = new QPushButton(enter_data_tab);
        edit_image_button->setObjectName(QString::fromUtf8("edit_image_button"));
        edit_image_button->setEnabled(false);
        edit_image_button->setGeometry(QRect(940, 20, 100, 60));
        sizePolicy1.setHeightForWidth(edit_image_button->sizePolicy().hasHeightForWidth());
        edit_image_button->setSizePolicy(sizePolicy1);
        edit_image_button->setMinimumSize(QSize(100, 60));
        edit_image_button->setMaximumSize(QSize(100, 60));
        edit_image_button->setBaseSize(QSize(100, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/imgs/images/pncl.png"), QSize(), QIcon::Normal, QIcon::Off);
        edit_image_button->setIcon(icon2);
        edit_image_button->setIconSize(QSize(40, 40));
        edit_image_button->setFlat(false);
        main_panel_tab_widget->addTab(enter_data_tab, QString());
        output_data_tab = new QWidget();
        output_data_tab->setObjectName(QString::fromUtf8("output_data_tab"));
        save_wind_delimeter_line = new QFrame(output_data_tab);
        save_wind_delimeter_line->setObjectName(QString::fromUtf8("save_wind_delimeter_line"));
        save_wind_delimeter_line->setGeometry(QRect(120, 20, 16, 71));
        save_wind_delimeter_line->setFrameShape(QFrame::VLine);
        save_wind_delimeter_line->setFrameShadow(QFrame::Sunken);
        sav_map_delimeter_line = new QFrame(output_data_tab);
        sav_map_delimeter_line->setObjectName(QString::fromUtf8("sav_map_delimeter_line"));
        sav_map_delimeter_line->setGeometry(QRect(321, 20, 16, 71));
        sav_map_delimeter_line->setFrameShape(QFrame::VLine);
        sav_map_delimeter_line->setFrameShadow(QFrame::Sunken);
        map_save_format_combo_box = new QComboBox(output_data_tab);
        map_save_format_combo_box->addItem(QString());
        map_save_format_combo_box->addItem(QString());
        map_save_format_combo_box->addItem(QString());
        map_save_format_combo_box->addItem(QString());
        map_save_format_combo_box->setObjectName(QString::fromUtf8("map_save_format_combo_box"));
        map_save_format_combo_box->setEnabled(false);
        map_save_format_combo_box->setGeometry(QRect(341, 60, 75, 24));
        map_saver_format_label = new QLabel(output_data_tab);
        map_saver_format_label->setObjectName(QString::fromUtf8("map_saver_format_label"));
        map_saver_format_label->setGeometry(QRect(341, 30, 171, 16));
        save_map_button = new QPushButton(output_data_tab);
        save_map_button->setObjectName(QString::fromUtf8("save_map_button"));
        save_map_button->setEnabled(false);
        save_map_button->setGeometry(QRect(431, 60, 80, 25));
        save_in_zip_delimeter_line = new QFrame(output_data_tab);
        save_in_zip_delimeter_line->setObjectName(QString::fromUtf8("save_in_zip_delimeter_line"));
        save_in_zip_delimeter_line->setGeometry(QRect(521, 20, 16, 71));
        save_in_zip_delimeter_line->setFrameShape(QFrame::VLine);
        save_in_zip_delimeter_line->setFrameShadow(QFrame::Sunken);
        open_map_visualization_button = new QPushButton(output_data_tab);
        open_map_visualization_button->setObjectName(QString::fromUtf8("open_map_visualization_button"));
        open_map_visualization_button->setEnabled(false);
        open_map_visualization_button->setGeometry(QRect(20, 30, 100, 60));
        open_map_visualization_button->setMinimumSize(QSize(100, 60));
        open_map_visualization_button->setMaximumSize(QSize(100, 60));
        open_map_visualization_button->setBaseSize(QSize(100, 50));
        QFont font;
        font.setPointSize(28);
        open_map_visualization_button->setFont(font);
        save_in_zip_button = new QPushButton(output_data_tab);
        save_in_zip_button->setObjectName(QString::fromUtf8("save_in_zip_button"));
        save_in_zip_button->setEnabled(false);
        save_in_zip_button->setGeometry(QRect(550, 20, 281, 71));
        QFont font1;
        font1.setPointSize(21);
        save_in_zip_button->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/imgs/images/zip.png"), QSize(), QIcon::Normal, QIcon::Off);
        save_in_zip_button->setIcon(icon3);
        save_in_zip_button->setIconSize(QSize(40, 40));
        wind_save_format_combo_box = new QComboBox(output_data_tab);
        wind_save_format_combo_box->addItem(QString());
        wind_save_format_combo_box->addItem(QString());
        wind_save_format_combo_box->addItem(QString());
        wind_save_format_combo_box->setObjectName(QString::fromUtf8("wind_save_format_combo_box"));
        wind_save_format_combo_box->setEnabled(false);
        wind_save_format_combo_box->setGeometry(QRect(141, 60, 75, 24));
        save_wind_button = new QPushButton(output_data_tab);
        save_wind_button->setObjectName(QString::fromUtf8("save_wind_button"));
        save_wind_button->setEnabled(false);
        save_wind_button->setGeometry(QRect(231, 60, 80, 25));
        wind_saver_format_label = new QLabel(output_data_tab);
        wind_saver_format_label->setObjectName(QString::fromUtf8("wind_saver_format_label"));
        wind_saver_format_label->setGeometry(QRect(141, 30, 171, 16));
        main_panel_tab_widget->addTab(output_data_tab, QString());
        wind_tab = new QWidget();
        wind_tab->setObjectName(QString::fromUtf8("wind_tab"));
        computate_speeds_button = new QPushButton(wind_tab);
        computate_speeds_button->setObjectName(QString::fromUtf8("computate_speeds_button"));
        computate_speeds_button->setEnabled(false);
        computate_speeds_button->setGeometry(QRect(710, 20, 100, 60));
        sizePolicy1.setHeightForWidth(computate_speeds_button->sizePolicy().hasHeightForWidth());
        computate_speeds_button->setSizePolicy(sizePolicy1);
        computate_speeds_button->setMinimumSize(QSize(100, 60));
        computate_speeds_button->setMaximumSize(QSize(100, 60));
        computate_speeds_button->setBaseSize(QSize(100, 50));
        computate_speeds_button->setFlat(false);
        enter_speed_vectors_button = new QPushButton(wind_tab);
        enter_speed_vectors_button->setObjectName(QString::fromUtf8("enter_speed_vectors_button"));
        enter_speed_vectors_button->setEnabled(false);
        enter_speed_vectors_button->setGeometry(QRect(850, 20, 100, 60));
        sizePolicy1.setHeightForWidth(enter_speed_vectors_button->sizePolicy().hasHeightForWidth());
        enter_speed_vectors_button->setSizePolicy(sizePolicy1);
        enter_speed_vectors_button->setMinimumSize(QSize(100, 60));
        enter_speed_vectors_button->setMaximumSize(QSize(100, 60));
        enter_speed_vectors_button->setBaseSize(QSize(100, 50));
        enter_speed_vectors_button->setFlat(false);
        computator_parameters_delimeter_line = new QFrame(wind_tab);
        computator_parameters_delimeter_line->setObjectName(QString::fromUtf8("computator_parameters_delimeter_line"));
        computator_parameters_delimeter_line->setGeometry(QRect(350, 10, 16, 71));
        computator_parameters_delimeter_line->setFrameShape(QFrame::VLine);
        computator_parameters_delimeter_line->setFrameShadow(QFrame::Sunken);
        formLayoutWidget = new QWidget(wind_tab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 331, 127));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        horizon_label = new QLabel(formLayoutWidget);
        horizon_label->setObjectName(QString::fromUtf8("horizon_label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, horizon_label);

        horizon_spin_box = new QDoubleSpinBox(formLayoutWidget);
        horizon_spin_box->setObjectName(QString::fromUtf8("horizon_spin_box"));
        horizon_spin_box->setAlignment(Qt::AlignCenter);
        horizon_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        horizon_spin_box->setDecimals(4);
        horizon_spin_box->setMaximum(10000.000000000000000);
        horizon_spin_box->setSingleStep(0.500000000000000);
        horizon_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, horizon_spin_box);

        ratio_label = new QLabel(formLayoutWidget);
        ratio_label->setObjectName(QString::fromUtf8("ratio_label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, ratio_label);

        ratio_double_spin_box = new QDoubleSpinBox(formLayoutWidget);
        ratio_double_spin_box->setObjectName(QString::fromUtf8("ratio_double_spin_box"));
        ratio_double_spin_box->setAlignment(Qt::AlignCenter);
        ratio_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ratio_double_spin_box->setDecimals(4);
        ratio_double_spin_box->setMaximum(9999.989999999999782);
        ratio_double_spin_box->setSingleStep(0.500000000000000);
        ratio_double_spin_box->setValue(0.001000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, ratio_double_spin_box);

        atol_label = new QLabel(formLayoutWidget);
        atol_label->setObjectName(QString::fromUtf8("atol_label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, atol_label);

        atol_percents_spin_box = new QDoubleSpinBox(formLayoutWidget);
        atol_percents_spin_box->setObjectName(QString::fromUtf8("atol_percents_spin_box"));
        atol_percents_spin_box->setAlignment(Qt::AlignCenter);
        atol_percents_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        atol_percents_spin_box->setDecimals(3);
        atol_percents_spin_box->setMinimum(0.001000000000000);
        atol_percents_spin_box->setMaximum(100.000000000000000);
        atol_percents_spin_box->setSingleStep(1.000000000000000);
        atol_percents_spin_box->setValue(10.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, atol_percents_spin_box);

        abs_wind_speed_spin_box = new QDoubleSpinBox(formLayoutWidget);
        abs_wind_speed_spin_box->setObjectName(QString::fromUtf8("abs_wind_speed_spin_box"));
        abs_wind_speed_spin_box->setAlignment(Qt::AlignCenter);
        abs_wind_speed_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        abs_wind_speed_spin_box->setDecimals(4);
        abs_wind_speed_spin_box->setMaximum(9999.989999999999782);
        abs_wind_speed_spin_box->setSingleStep(0.500000000000000);
        abs_wind_speed_spin_box->setValue(10.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, abs_wind_speed_spin_box);

        abs_wind_speed_label = new QLabel(formLayoutWidget);
        abs_wind_speed_label->setObjectName(QString::fromUtf8("abs_wind_speed_label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, abs_wind_speed_label);

        computator_parameters_delimeter_line_2 = new QFrame(wind_tab);
        computator_parameters_delimeter_line_2->setObjectName(QString::fromUtf8("computator_parameters_delimeter_line_2"));
        computator_parameters_delimeter_line_2->setGeometry(QRect(690, 10, 16, 71));
        computator_parameters_delimeter_line_2->setFrameShape(QFrame::VLine);
        computator_parameters_delimeter_line_2->setFrameShadow(QFrame::Sunken);
        wind_direction_group_box = new QGroupBox(wind_tab);
        wind_direction_group_box->setObjectName(QString::fromUtf8("wind_direction_group_box"));
        wind_direction_group_box->setGeometry(QRect(380, 10, 301, 111));
        gridLayout_5 = new QGridLayout(wind_direction_group_box);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        system_combo_box = new QComboBox(wind_direction_group_box);
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->addItem(QString());
        system_combo_box->setObjectName(QString::fromUtf8("system_combo_box"));
        system_combo_box->setEnabled(false);
        sizePolicy.setHeightForWidth(system_combo_box->sizePolicy().hasHeightForWidth());
        system_combo_box->setSizePolicy(sizePolicy);
        system_combo_box->setMinimumSize(QSize(0, 0));
        system_combo_box->setMaximumSize(QSize(16777215, 16777215));
        system_combo_box->setBaseSize(QSize(70, 20));
        system_combo_box->setEditable(false);

        gridLayout_5->addWidget(system_combo_box, 1, 1, 1, 1);

        system_check_box = new QCheckBox(wind_direction_group_box);
        system_check_box->setObjectName(QString::fromUtf8("system_check_box"));
        system_check_box->setEnabled(true);

        gridLayout_5->addWidget(system_check_box, 1, 0, 1, 1);

        azimuth_check_box = new QCheckBox(wind_direction_group_box);
        azimuth_check_box->setObjectName(QString::fromUtf8("azimuth_check_box"));
        azimuth_check_box->setChecked(true);
        azimuth_check_box->setTristate(false);

        gridLayout_5->addWidget(azimuth_check_box, 0, 0, 1, 1);

        azimuth_double_spin_box = new QDoubleSpinBox(wind_direction_group_box);
        azimuth_double_spin_box->setObjectName(QString::fromUtf8("azimuth_double_spin_box"));
        azimuth_double_spin_box->setAlignment(Qt::AlignCenter);
        azimuth_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        azimuth_double_spin_box->setDecimals(2);
        azimuth_double_spin_box->setMaximum(360.000000000000000);
        azimuth_double_spin_box->setSingleStep(0.500000000000000);
        azimuth_double_spin_box->setValue(0.000000000000000);

        gridLayout_5->addWidget(azimuth_double_spin_box, 0, 1, 1, 1);

        force_abs_speed_decompose_button = new QPushButton(wind_direction_group_box);
        force_abs_speed_decompose_button->setObjectName(QString::fromUtf8("force_abs_speed_decompose_button"));
        force_abs_speed_decompose_button->setEnabled(false);

        gridLayout_5->addWidget(force_abs_speed_decompose_button, 2, 0, 1, 1);

        main_panel_tab_widget->addTab(wind_tab, QString());
        relief_tab = new QWidget();
        relief_tab->setObjectName(QString::fromUtf8("relief_tab"));
        enter_heights_button = new QPushButton(relief_tab);
        enter_heights_button->setObjectName(QString::fromUtf8("enter_heights_button"));
        enter_heights_button->setEnabled(false);
        enter_heights_button->setGeometry(QRect(10, 10, 100, 60));
        enter_heights_button->setMinimumSize(QSize(100, 60));
        enter_heights_button->setMaximumSize(QSize(100, 600));
        enter_heights_button->setBaseSize(QSize(100, 50));
        load_heights_from_file_button = new QPushButton(relief_tab);
        load_heights_from_file_button->setObjectName(QString::fromUtf8("load_heights_from_file_button"));
        load_heights_from_file_button->setEnabled(false);
        load_heights_from_file_button->setGeometry(QRect(160, 20, 171, 25));
        save_heights_button = new QPushButton(relief_tab);
        save_heights_button->setObjectName(QString::fromUtf8("save_heights_button"));
        save_heights_button->setEnabled(false);
        save_heights_button->setGeometry(QRect(160, 50, 171, 25));
        main_panel_tab_widget->addTab(relief_tab, QString());
        polution_tab = new QWidget();
        polution_tab->setObjectName(QString::fromUtf8("polution_tab"));
        formLayoutWidget_2 = new QWidget(polution_tab);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 0, 210, 31));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        polution_computations_distance_label = new QLabel(formLayoutWidget_2);
        polution_computations_distance_label->setObjectName(QString::fromUtf8("polution_computations_distance_label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, polution_computations_distance_label);

        max_computations_distance_double_spin_box = new QDoubleSpinBox(formLayoutWidget_2);
        max_computations_distance_double_spin_box->setObjectName(QString::fromUtf8("max_computations_distance_double_spin_box"));
        max_computations_distance_double_spin_box->setMaximumSize(QSize(16777210, 16777215));
        max_computations_distance_double_spin_box->setAlignment(Qt::AlignCenter);
        max_computations_distance_double_spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
        max_computations_distance_double_spin_box->setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
        max_computations_distance_double_spin_box->setMaximum(10000.000000000000000);
        max_computations_distance_double_spin_box->setValue(500.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, max_computations_distance_double_spin_box);

        main_panel_tab_widget->addTab(polution_tab, QString());

        verticalLayout->addWidget(main_panel_tab_widget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        display_info_tool_box = new QToolBox(centralwidget);
        display_info_tool_box->setObjectName(QString::fromUtf8("display_info_tool_box"));
        display_info_tool_box->setEnabled(true);
        sizePolicy.setHeightForWidth(display_info_tool_box->sizePolicy().hasHeightForWidth());
        display_info_tool_box->setSizePolicy(sizePolicy);
        display_info_tool_box->setMinimumSize(QSize(1280, 720));
        display_info_tool_box->setMaximumSize(QSize(16777215, 16777215));
        map_image_widget = new QWidget();
        map_image_widget->setObjectName(QString::fromUtf8("map_image_widget"));
        map_image_widget->setGeometry(QRect(0, 0, 1285, 595));
        verticalLayout_2 = new QVBoxLayout(map_image_widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        map_web_engine = new QWebEngineView(map_image_widget);
        map_web_engine->setObjectName(QString::fromUtf8("map_web_engine"));
        map_web_engine->setMinimumSize(QSize(1200, 523));

        verticalLayout_2->addWidget(map_web_engine);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        data_service_name_label = new QLabel(map_image_widget);
        data_service_name_label->setObjectName(QString::fromUtf8("data_service_name_label"));
        data_service_name_label->setMinimumSize(QSize(380, 20));
        data_service_name_label->setMaximumSize(QSize(380, 20));
#if QT_CONFIG(whatsthis)
        data_service_name_label->setWhatsThis(0u);
#endif // QT_CONFIG(whatsthis)
        data_service_name_label->setLayoutDirection(Qt::LeftToRight);
        data_service_name_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(data_service_name_label);

        current_service_name_label = new QLabel(map_image_widget);
        current_service_name_label->setObjectName(QString::fromUtf8("current_service_name_label"));
        current_service_name_label->setMinimumSize(QSize(130, 20));
        current_service_name_label->setMaximumSize(QSize(130, 20));

        horizontalLayout_4->addWidget(current_service_name_label);


        verticalLayout_2->addLayout(horizontalLayout_4);

        display_info_tool_box->addItem(map_image_widget, QString::fromUtf8("\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\267\320\260\320\263\321\200\321\203\320\266\320\265\320\275\320\275\320\276\320\271 \320\272\320\260\321\200\321\202\321\213"));
        map_image_page = new QWidget();
        map_image_page->setObjectName(QString::fromUtf8("map_image_page"));
        map_image_page->setGeometry(QRect(0, 0, 1285, 595));
        horizontalLayout_2 = new QHBoxLayout(map_image_page);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        grid_map_label = new QLabel(map_image_page);
        grid_map_label->setObjectName(QString::fromUtf8("grid_map_label"));
        grid_map_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(grid_map_label);

        display_info_tool_box->addItem(map_image_page, QString::fromUtf8("\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\201\320\265\321\202\320\276\321\207\320\275\320\276\320\271 \320\276\320\261\320\273\320\260\321\201\321\202\320\270"));
        relief_page = new QWidget();
        relief_page->setObjectName(QString::fromUtf8("relief_page"));
        relief_page->setGeometry(QRect(0, 0, 1285, 595));
        gridLayout_3 = new QGridLayout(relief_page);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        relief_tab_page = new QTabWidget(relief_page);
        relief_tab_page->setObjectName(QString::fromUtf8("relief_tab_page"));

        gridLayout_3->addWidget(relief_tab_page, 0, 0, 1, 1);

        display_info_tool_box->addItem(relief_page, QString::fromUtf8("\320\237\320\276\320\264\320\262\320\276\320\264\320\275\321\213\320\271 \321\200\320\265\320\273\321\214\320\265\321\204"));
        winds_direction_page = new QWidget();
        winds_direction_page->setObjectName(QString::fromUtf8("winds_direction_page"));
        winds_direction_page->setGeometry(QRect(0, 0, 1285, 595));
        gridLayout_4 = new QGridLayout(winds_direction_page);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        winds_direction_tab = new QTabWidget(winds_direction_page);
        winds_direction_tab->setObjectName(QString::fromUtf8("winds_direction_tab"));
        winds_image_container_tab = new QWidget();
        winds_image_container_tab->setObjectName(QString::fromUtf8("winds_image_container_tab"));
        gridLayout_2 = new QGridLayout(winds_image_container_tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        legend_group_box = new QGroupBox(winds_image_container_tab);
        legend_group_box->setObjectName(QString::fromUtf8("legend_group_box"));
        sizePolicy1.setHeightForWidth(legend_group_box->sizePolicy().hasHeightForWidth());
        legend_group_box->setSizePolicy(sizePolicy1);
        legend_group_box->setMinimumSize(QSize(40, 50));
        verticalLayout_3 = new QVBoxLayout(legend_group_box);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(legend_group_box);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label);


        gridLayout_2->addWidget(legend_group_box, 0, 1, 1, 1);

        map_with_winds_label = new QLabel(winds_image_container_tab);
        map_with_winds_label->setObjectName(QString::fromUtf8("map_with_winds_label"));
        map_with_winds_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(map_with_winds_label, 0, 0, 2, 1);

        winds_direction_tab->addTab(winds_image_container_tab, QString());

        gridLayout_4->addWidget(winds_direction_tab, 0, 0, 1, 1);

        display_info_tool_box->addItem(winds_direction_page, QString::fromUtf8("\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\262\320\265\321\202\321\200\320\276\320\262"));
        polution_page = new QWidget();
        polution_page->setObjectName(QString::fromUtf8("polution_page"));
        polution_page->setGeometry(QRect(0, 0, 1285, 595));
        verticalLayout_6 = new QVBoxLayout(polution_page);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        sources_table_widget = new QTableWidget(polution_page);
        sources_table_widget->setObjectName(QString::fromUtf8("sources_table_widget"));
        sources_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sources_table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
        sources_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_6->addWidget(sources_table_widget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        add_new_polution_source_button = new QPushButton(polution_page);
        add_new_polution_source_button->setObjectName(QString::fromUtf8("add_new_polution_source_button"));
        sizePolicy1.setHeightForWidth(add_new_polution_source_button->sizePolicy().hasHeightForWidth());
        add_new_polution_source_button->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(add_new_polution_source_button);

        current_source_matter_button = new QPushButton(polution_page);
        current_source_matter_button->setObjectName(QString::fromUtf8("current_source_matter_button"));

        horizontalLayout_5->addWidget(current_source_matter_button);

        delete_polution_source_button = new QPushButton(polution_page);
        delete_polution_source_button->setObjectName(QString::fromUtf8("delete_polution_source_button"));
        sizePolicy1.setHeightForWidth(delete_polution_source_button->sizePolicy().hasHeightForWidth());
        delete_polution_source_button->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(delete_polution_source_button);


        verticalLayout_6->addLayout(horizontalLayout_5);

        display_info_tool_box->addItem(polution_page, QString::fromUtf8("\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\276\320\262 \320\267\320\260\320\263\321\200\321\217\320\267\320\275\320\265\320\275\320\270\321\217"));

        horizontalLayout_3->addWidget(display_info_tool_box);

        saved_in_current_session_files_group_box = new QGroupBox(centralwidget);
        saved_in_current_session_files_group_box->setObjectName(QString::fromUtf8("saved_in_current_session_files_group_box"));
        saved_in_current_session_files_group_box->setMinimumSize(QSize(220, 0));
        saved_in_current_session_files_group_box->setMaximumSize(QSize(220, 16777215));
        gridLayout_6 = new QGridLayout(saved_in_current_session_files_group_box);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        saved_files_list_box = new QListWidget(saved_in_current_session_files_group_box);
        saved_files_list_box->setObjectName(QString::fromUtf8("saved_files_list_box"));

        gridLayout_6->addWidget(saved_files_list_box, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(saved_in_current_session_files_group_box);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1533, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(load_from_pc_button, SIGNAL(pressed()), MainWindow, SLOT(loadFromPCButtonPressed()));
        QObject::connect(edit_image_button, SIGNAL(pressed()), MainWindow, SLOT(editImageButtonPressed()));
        QObject::connect(load_from_site_button, SIGNAL(pressed()), MainWindow, SLOT(loadFromSiteButtonPressed()));
        QObject::connect(force_abs_speed_decompose_button, SIGNAL(pressed()), MainWindow, SLOT(forceAbsSpeedDecomposeButtonPressed()));
        QObject::connect(computate_speeds_button, SIGNAL(pressed()), MainWindow, SLOT(computateSpeedsButtonPressed()));
        QObject::connect(enter_speed_vectors_button, SIGNAL(pressed()), MainWindow, SLOT(enterSpeedVectorButtonPressed()));
        QObject::connect(save_wind_button, SIGNAL(pressed()), MainWindow, SLOT(saveSpeedsButtonPressed()));
        QObject::connect(save_map_button, SIGNAL(pressed()), MainWindow, SLOT(saveMapButtonPressed()));
        QObject::connect(open_map_visualization_button, SIGNAL(pressed()), MainWindow, SLOT(openMapVisualizationButtonPressed()));
        QObject::connect(enter_heights_button, SIGNAL(pressed()), MainWindow, SLOT(enterHeightsButtonPressed()));
        QObject::connect(load_heights_from_file_button, SIGNAL(pressed()), MainWindow, SLOT(loadHeightsFromFileButtonPressed()));
        QObject::connect(save_heights_button, SIGNAL(pressed()), MainWindow, SLOT(saveHeightsTableButtonPressed()));
        QObject::connect(add_new_polution_source_button, SIGNAL(pressed()), MainWindow, SLOT(addNewSourceButtonPressed()));
        QObject::connect(current_source_matter_button, SIGNAL(pressed()), MainWindow, SLOT(displaySelectedSourceButtonPressed()));
        QObject::connect(delete_polution_source_button, SIGNAL(pressed()), MainWindow, SLOT(deleteSelectedSouceButtonPressed()));

        main_panel_tab_widget->setCurrentIndex(2);
        display_info_tool_box->setCurrentIndex(3);
        relief_tab_page->setCurrentIndex(-1);
        winds_direction_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        x_coordinate_label->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        y_coordinate_label->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        scale_label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261:", nullptr));
        water_object_type_label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\262\320\276\320\264\320\275\320\276\320\263\320\276 \320\276\320\261\321\212\320\265\320\272\321\202\320\260:", nullptr));
        cell_width_label->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260 \321\217\321\207\320\265\320\271\320\272\320\270", nullptr));
        cell_height_label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260 \321\217\321\207\320\265\320\271\320\272\320\270", nullptr));
        cell_width_spin_box->setSuffix(QCoreApplication::translate("MainWindow", " \320\274", nullptr));
        cell_height_spin_box->setSuffix(QCoreApplication::translate("MainWindow", " \320\274", nullptr));
        water_object_type_combo_box->setItemText(0, QCoreApplication::translate("MainWindow", "\320\240\320\265\320\272\320\260", nullptr));
        water_object_type_combo_box->setItemText(1, QCoreApplication::translate("MainWindow", "\320\236\320\267\320\265\321\200\320\276", nullptr));

        water_object_type_combo_box->setCurrentText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\272\320\260", nullptr));
#if QT_CONFIG(tooltip)
        load_from_pc_button->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\320\265 \321\201\320\276\320\261\321\201\321\202\320\262\320\265\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\272\320\260\321\200\321\202\321\213 \320\270\320\267 \320\272\320\260\321\202\320\260\320\273\320\276\320\263\320\276\320\262 \320\272\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        load_from_pc_button->setText(QString());
        scale_spin_box->setSuffix(QString());
#if QT_CONFIG(tooltip)
        load_from_site_button->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\320\265 \320\272\320\260\321\200\321\202\321\203 \320\264\320\273\321\217 \321\200\320\270\321\201\320\276\320\262\320\260\320\275\320\270\321\217 \320\270\320\267 \320\262\321\213\320\261\321\200\320\260\320\275\320\276\320\271 \320\276\320\261\320\273\320\260\321\201\321\202\320\270 \320\275\320\260 \321\201\320\260\320\271\321\202\320\265 \320\262 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\272\320\260\321\200\321\202\321\213</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        load_from_site_button->setText(QString());
#if QT_CONFIG(tooltip)
        edit_image_button->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\236\321\202\321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\321\203\320\271\321\202\320\265 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        edit_image_button->setText(QString());
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(enter_data_tab), QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        map_save_format_combo_box->setItemText(0, QCoreApplication::translate("MainWindow", ".xlsx", nullptr));
        map_save_format_combo_box->setItemText(1, QCoreApplication::translate("MainWindow", ".jpg", nullptr));
        map_save_format_combo_box->setItemText(2, QCoreApplication::translate("MainWindow", ".png", nullptr));
        map_save_format_combo_box->setItemText(3, QCoreApplication::translate("MainWindow", ".jpeg", nullptr));

        map_saver_format_label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\321\203 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265:", nullptr));
        save_map_button->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
#if QT_CONFIG(tooltip)
        open_map_visualization_button->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\236\321\202\320\272\321\200\321\213\321\202\321\214 3D \320\262\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\216 \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\276\320\261\320\252\320\265\320\272\321\202\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        open_map_visualization_button->setText(QCoreApplication::translate("MainWindow", "3D", nullptr));
        save_in_zip_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 ZIP", nullptr));
        wind_save_format_combo_box->setItemText(0, QCoreApplication::translate("MainWindow", ".xlsx", nullptr));
        wind_save_format_combo_box->setItemText(1, QCoreApplication::translate("MainWindow", ".png", nullptr));
        wind_save_format_combo_box->setItemText(2, QCoreApplication::translate("MainWindow", ".jpeg", nullptr));

        save_wind_button->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        wind_saver_format_label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262\320\265\321\202\321\200\320\260  \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265:", nullptr));
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(output_data_tab), QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        computate_speeds_button->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \n"
"\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217\n"
" \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\265\320\271", nullptr));
        enter_speed_vectors_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217\n"
"\320\262\320\265\320\272\321\202\320\276\321\200\320\276\320\262\n"
" \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\265\320\271", nullptr));
        horizon_label->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202", nullptr));
        horizon_spin_box->setSuffix(QCoreApplication::translate("MainWindow", " \320\274", nullptr));
        ratio_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\220<span style=\" vertical-align:sub;\">z</span></p></body></html>", nullptr));
        atol_label->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\242\321\200\320\265\320\261\321\203\320\265\320\274\320\260\321\217 \321\202\320\276\321\207\320\275\320\276\321\201\321\202\321\214 \321\200\320\260\321\201\321\207\320\265\321\202\320\260 \317\210 (\320\277\321\200\320\276\321\206\320\265\320\275\321\202\321\213)</p></body></html>", nullptr));
        abs_wind_speed_spin_box->setSuffix(QCoreApplication::translate("MainWindow", " \320\274/\321\201", nullptr));
        abs_wind_speed_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\234\320\276\320\264\321\203\320\273\321\214 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270 \320\262\320\265\321\202\321\200\320\260</p></body></html>", nullptr));
        wind_direction_group_box->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\262\320\265\321\202\321\200\320\276\320\262", nullptr));
        system_combo_box->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\320\265\320\262\320\265\321\200", nullptr));
        system_combo_box->setItemText(1, QCoreApplication::translate("MainWindow", "\320\241\320\265\320\262\320\265\321\200\320\276-\320\222\320\276\321\201\321\202\320\276\320\272", nullptr));
        system_combo_box->setItemText(2, QCoreApplication::translate("MainWindow", "\320\222\320\276\321\201\321\202\320\276\320\272", nullptr));
        system_combo_box->setItemText(3, QCoreApplication::translate("MainWindow", "\320\256\320\263\320\276-\320\222\320\276\321\201\321\202\320\276\320\272", nullptr));
        system_combo_box->setItemText(4, QCoreApplication::translate("MainWindow", "\320\256\320\263", nullptr));
        system_combo_box->setItemText(5, QCoreApplication::translate("MainWindow", "\320\256\320\263\320\276-\320\227\320\260\320\277\320\260\320\264", nullptr));
        system_combo_box->setItemText(6, QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\260\320\264", nullptr));
        system_combo_box->setItemText(7, QCoreApplication::translate("MainWindow", "\320\241\320\265\320\262\320\265\321\200\320\276-\320\227\320\260\320\277\320\260\320\264", nullptr));

        system_combo_box->setCurrentText(QCoreApplication::translate("MainWindow", "\320\241\320\265\320\262\320\265\321\200", nullptr));
        system_check_box->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\321\201\321\214\320\274\320\270\321\200\321\203\320\274\320\261\320\276\320\262\320\260\321\217 \321\201\320\270\321\201\321\202\321\203\320\274\320\260", nullptr));
        azimuth_check_box->setText(QCoreApplication::translate("MainWindow", "\320\220\320\267\320\270\320\274\321\203\321\202", nullptr));
        force_abs_speed_decompose_button->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\273\320\276\320\266\320\270\321\202\321\214 \320\275\320\260 \320\262\320\265\320\272\321\202\320\276\321\200\320\260", nullptr));
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(wind_tab), QCoreApplication::translate("MainWindow", "\320\222\320\265\321\202\320\265\321\200", nullptr));
        enter_heights_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\262\321\213\321\201\320\276\321\202\n"
"(\320\277\321\200\320\270 \320\277\320\276\320\274\320\276\321\211\320\270 \n"
"\320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213)", nullptr));
        load_heights_from_file_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203 \320\263\320\273\321\203\320\261\320\270\320\275", nullptr));
        save_heights_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203 \320\263\320\273\321\203\320\261\320\270\320\275", nullptr));
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(relief_tab), QCoreApplication::translate("MainWindow", "\320\240\320\265\320\273\321\214\320\265\321\204", nullptr));
        polution_computations_distance_label->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\276\321\202 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        max_computations_distance_double_spin_box->setSuffix(QCoreApplication::translate("MainWindow", " \320\274", nullptr));
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(polution_tab), QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\217\320\267\320\275\320\265\320\275\320\270\320\265", nullptr));
        data_service_name_label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\277\321\200\320\265\320\264\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\275\321\213 \321\201\320\265\321\200\320\262\320\270\321\201\320\276\320\274:", nullptr));
        current_service_name_label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\201\320\265\321\200\320\262\320\270\321\201", nullptr));
        display_info_tool_box->setItemText(display_info_tool_box->indexOf(map_image_widget), QCoreApplication::translate("MainWindow", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\267\320\260\320\263\321\200\321\203\320\266\320\265\320\275\320\275\320\276\320\271 \320\272\320\260\321\200\321\202\321\213", nullptr));
        grid_map_label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\200\321\202\320\260", nullptr));
        display_info_tool_box->setItemText(display_info_tool_box->indexOf(map_image_page), QCoreApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\201\320\265\321\202\320\276\321\207\320\275\320\276\320\271 \320\276\320\261\320\273\320\260\321\201\321\202\320\270", nullptr));
        display_info_tool_box->setItemText(display_info_tool_box->indexOf(relief_page), QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\262\320\276\320\264\320\275\321\213\320\271 \321\200\320\265\320\273\321\214\320\265\321\204", nullptr));
        legend_group_box->setTitle(QCoreApplication::translate("MainWindow", "\320\233\320\265\320\263\320\265\320\275\320\264\320\260", nullptr));
        label->setText(QString());
        map_with_winds_label->setText(QCoreApplication::translate("MainWindow", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\272\320\260\321\200\321\202\321\213 \320\262\320\265\321\202\321\200\320\276\320\262", nullptr));
        winds_direction_tab->setTabText(winds_direction_tab->indexOf(winds_image_container_tab), QCoreApplication::translate("MainWindow", "\320\232\320\260\321\200\321\202\320\260", nullptr));
        display_info_tool_box->setItemText(display_info_tool_box->indexOf(winds_direction_page), QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\262\320\265\321\202\321\200\320\276\320\262", nullptr));
        add_new_polution_source_button->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272", nullptr));
        current_source_matter_button->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \320\262\320\265\321\211\320\265\321\201\321\202\320\262 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\263\320\276 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        delete_polution_source_button->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272", nullptr));
        display_info_tool_box->setItemText(display_info_tool_box->indexOf(polution_page), QCoreApplication::translate("MainWindow", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\276\320\262 \320\267\320\260\320\263\321\200\321\217\320\267\320\275\320\265\320\275\320\270\321\217", nullptr));
        saved_in_current_session_files_group_box->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
