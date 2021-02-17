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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *cell_width_label;
    QDoubleSpinBox *cell_width_spin_box;
    QLabel *cell_height_label;
    QDoubleSpinBox *cell_height_spin_box;
    QLabel *scale_label;
    QDoubleSpinBox *scale_spin_box;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *map_layout;
    QLabel *map_label;
    QWidget *gridLayoutWidget;
    QGridLayout *map_actions;
    QPushButton *load_button;
    QPushButton *open_map_visualization_button;
    QPushButton *save_map_as_image_button;
    QPushButton *enter_heights_button;
    QPushButton *open_map_button;
    QPushButton *save_map_as_excel_button;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *update_grid_button;
    QPushButton *update_map_button;
    QComboBox *water_object_type_combo_box;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *ratio_label;
    QDoubleSpinBox *ratio_double_spin_box;
    QPushButton *enter_speed_vectors_button;
    QPushButton *computate_pressures_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(851, 616);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(550, 0, 251, 91));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(5, 5, 5, 5);
        cell_width_label = new QLabel(formLayoutWidget);
        cell_width_label->setObjectName(QString::fromUtf8("cell_width_label"));
        cell_width_label->setMinimumSize(QSize(115, 20));
        cell_width_label->setMaximumSize(QSize(115, 20));
        cell_width_label->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, cell_width_label);

        cell_width_spin_box = new QDoubleSpinBox(formLayoutWidget);
        cell_width_spin_box->setObjectName(QString::fromUtf8("cell_width_spin_box"));
        cell_width_spin_box->setAlignment(Qt::AlignCenter);
        cell_width_spin_box->setDecimals(3);
        cell_width_spin_box->setMaximum(500000.000000000000000);
        cell_width_spin_box->setSingleStep(0.500000000000000);
        cell_width_spin_box->setValue(10.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cell_width_spin_box);

        cell_height_label = new QLabel(formLayoutWidget);
        cell_height_label->setObjectName(QString::fromUtf8("cell_height_label"));
        cell_height_label->setMinimumSize(QSize(115, 20));
        cell_height_label->setMaximumSize(QSize(115, 20));
        cell_height_label->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, cell_height_label);

        cell_height_spin_box = new QDoubleSpinBox(formLayoutWidget);
        cell_height_spin_box->setObjectName(QString::fromUtf8("cell_height_spin_box"));
        cell_height_spin_box->setAlignment(Qt::AlignCenter);
        cell_height_spin_box->setDecimals(3);
        cell_height_spin_box->setMaximum(500000.000000000000000);
        cell_height_spin_box->setSingleStep(0.500000000000000);
        cell_height_spin_box->setStepType(QAbstractSpinBox::DefaultStepType);
        cell_height_spin_box->setValue(10.000000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cell_height_spin_box);

        scale_label = new QLabel(formLayoutWidget);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setMinimumSize(QSize(115, 20));
        scale_label->setMaximumSize(QSize(115, 20));
        scale_label->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, scale_label);

        scale_spin_box = new QDoubleSpinBox(formLayoutWidget);
        scale_spin_box->setObjectName(QString::fromUtf8("scale_spin_box"));
        scale_spin_box->setAlignment(Qt::AlignCenter);
        scale_spin_box->setProperty("showGroupSeparator", QVariant(false));
        scale_spin_box->setDecimals(3);
        scale_spin_box->setMaximum(1000000.000000000000000);
        scale_spin_box->setSingleStep(0.500000000000000);
        scale_spin_box->setValue(10.000000000000000);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, scale_spin_box);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 551, 341));
        map_layout = new QVBoxLayout(verticalLayoutWidget);
        map_layout->setObjectName(QString::fromUtf8("map_layout"));
        map_layout->setContentsMargins(0, 0, 0, 0);
        map_label = new QLabel(verticalLayoutWidget);
        map_label->setObjectName(QString::fromUtf8("map_label"));
        map_label->setAlignment(Qt::AlignCenter);

        map_layout->addWidget(map_label);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 380, 549, 202));
        map_actions = new QGridLayout(gridLayoutWidget);
        map_actions->setObjectName(QString::fromUtf8("map_actions"));
        map_actions->setHorizontalSpacing(6);
        map_actions->setContentsMargins(5, 5, 5, 5);
        load_button = new QPushButton(gridLayoutWidget);
        load_button->setObjectName(QString::fromUtf8("load_button"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(load_button->sizePolicy().hasHeightForWidth());
        load_button->setSizePolicy(sizePolicy);
        load_button->setMinimumSize(QSize(100, 60));
        load_button->setMaximumSize(QSize(100, 60));
        load_button->setBaseSize(QSize(100, 50));
        load_button->setFlat(false);

        map_actions->addWidget(load_button, 0, 0, 1, 1);

        open_map_visualization_button = new QPushButton(gridLayoutWidget);
        open_map_visualization_button->setObjectName(QString::fromUtf8("open_map_visualization_button"));
        open_map_visualization_button->setEnabled(false);
        open_map_visualization_button->setMinimumSize(QSize(100, 60));
        open_map_visualization_button->setMaximumSize(QSize(100, 60));
        open_map_visualization_button->setBaseSize(QSize(100, 50));

        map_actions->addWidget(open_map_visualization_button, 1, 2, 1, 1);

        save_map_as_image_button = new QPushButton(gridLayoutWidget);
        save_map_as_image_button->setObjectName(QString::fromUtf8("save_map_as_image_button"));
        save_map_as_image_button->setEnabled(false);
        save_map_as_image_button->setMinimumSize(QSize(100, 60));
        save_map_as_image_button->setMaximumSize(QSize(100, 60));
        save_map_as_image_button->setBaseSize(QSize(100, 50));

        map_actions->addWidget(save_map_as_image_button, 0, 1, 1, 1);

        enter_heights_button = new QPushButton(gridLayoutWidget);
        enter_heights_button->setObjectName(QString::fromUtf8("enter_heights_button"));
        enter_heights_button->setEnabled(false);
        enter_heights_button->setMinimumSize(QSize(100, 60));
        enter_heights_button->setMaximumSize(QSize(100, 600));
        enter_heights_button->setBaseSize(QSize(100, 50));

        map_actions->addWidget(enter_heights_button, 0, 2, 1, 1);

        open_map_button = new QPushButton(gridLayoutWidget);
        open_map_button->setObjectName(QString::fromUtf8("open_map_button"));
        open_map_button->setEnabled(false);
        open_map_button->setMinimumSize(QSize(100, 60));
        open_map_button->setMaximumSize(QSize(100, 60));
        open_map_button->setBaseSize(QSize(100, 50));

        map_actions->addWidget(open_map_button, 1, 0, 1, 1);

        save_map_as_excel_button = new QPushButton(gridLayoutWidget);
        save_map_as_excel_button->setObjectName(QString::fromUtf8("save_map_as_excel_button"));
        save_map_as_excel_button->setEnabled(false);
        save_map_as_excel_button->setMinimumSize(QSize(100, 60));
        save_map_as_excel_button->setMaximumSize(QSize(100, 60));
        save_map_as_excel_button->setBaseSize(QSize(100, 50));

        map_actions->addWidget(save_map_as_excel_button, 1, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(550, 90, 251, 128));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        update_grid_button = new QPushButton(gridLayoutWidget_2);
        update_grid_button->setObjectName(QString::fromUtf8("update_grid_button"));
        update_grid_button->setEnabled(false);
        update_grid_button->setMinimumSize(QSize(100, 60));
        update_grid_button->setMaximumSize(QSize(100, 60));
        update_grid_button->setBaseSize(QSize(100, 50));

        gridLayout_2->addWidget(update_grid_button, 0, 1, 1, 1);

        update_map_button = new QPushButton(gridLayoutWidget_2);
        update_map_button->setObjectName(QString::fromUtf8("update_map_button"));
        update_map_button->setEnabled(false);
        update_map_button->setMinimumSize(QSize(100, 60));
        update_map_button->setMaximumSize(QSize(100, 60));
        update_map_button->setBaseSize(QSize(100, 50));

        gridLayout_2->addWidget(update_map_button, 0, 0, 1, 1);

        water_object_type_combo_box = new QComboBox(centralwidget);
        water_object_type_combo_box->setObjectName(QString::fromUtf8("water_object_type_combo_box"));
        water_object_type_combo_box->setGeometry(QRect(10, 350, 70, 20));
        sizePolicy.setHeightForWidth(water_object_type_combo_box->sizePolicy().hasHeightForWidth());
        water_object_type_combo_box->setSizePolicy(sizePolicy);
        water_object_type_combo_box->setMinimumSize(QSize(70, 20));
        water_object_type_combo_box->setMaximumSize(QSize(70, 20));
        water_object_type_combo_box->setBaseSize(QSize(70, 20));
        water_object_type_combo_box->setEditable(false);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(560, 230, 220, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ratio_label = new QLabel(horizontalLayoutWidget);
        ratio_label->setObjectName(QString::fromUtf8("ratio_label"));

        horizontalLayout->addWidget(ratio_label);

        ratio_double_spin_box = new QDoubleSpinBox(horizontalLayoutWidget);
        ratio_double_spin_box->setObjectName(QString::fromUtf8("ratio_double_spin_box"));
        ratio_double_spin_box->setDecimals(4);
        ratio_double_spin_box->setMaximum(9999.989999999999782);
        ratio_double_spin_box->setSingleStep(0.500000000000000);
        ratio_double_spin_box->setValue(0.001000000000000);

        horizontalLayout->addWidget(ratio_double_spin_box);

        enter_speed_vectors_button = new QPushButton(centralwidget);
        enter_speed_vectors_button->setObjectName(QString::fromUtf8("enter_speed_vectors_button"));
        enter_speed_vectors_button->setEnabled(false);
        enter_speed_vectors_button->setGeometry(QRect(560, 280, 100, 60));
        sizePolicy.setHeightForWidth(enter_speed_vectors_button->sizePolicy().hasHeightForWidth());
        enter_speed_vectors_button->setSizePolicy(sizePolicy);
        enter_speed_vectors_button->setMinimumSize(QSize(100, 60));
        enter_speed_vectors_button->setMaximumSize(QSize(100, 60));
        enter_speed_vectors_button->setBaseSize(QSize(100, 50));
        enter_speed_vectors_button->setFlat(false);
        computate_pressures_button = new QPushButton(centralwidget);
        computate_pressures_button->setObjectName(QString::fromUtf8("computate_pressures_button"));
        computate_pressures_button->setEnabled(false);
        computate_pressures_button->setGeometry(QRect(680, 280, 100, 60));
        sizePolicy.setHeightForWidth(computate_pressures_button->sizePolicy().hasHeightForWidth());
        computate_pressures_button->setSizePolicy(sizePolicy);
        computate_pressures_button->setMinimumSize(QSize(100, 60));
        computate_pressures_button->setMaximumSize(QSize(100, 60));
        computate_pressures_button->setBaseSize(QSize(100, 50));
        computate_pressures_button->setFlat(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 851, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(save_map_as_excel_button, SIGNAL(pressed()), MainWindow, SLOT(saveMapAsExcelButtonPressed()));
        QObject::connect(save_map_as_image_button, SIGNAL(pressed()), MainWindow, SLOT(saveMapAsImageButtonPressed()));
        QObject::connect(open_map_button, SIGNAL(pressed()), MainWindow, SLOT(openMapButtonPressed()));
        QObject::connect(update_grid_button, SIGNAL(pressed()), MainWindow, SLOT(updateGridButtonPressed()));
        QObject::connect(open_map_visualization_button, SIGNAL(pressed()), MainWindow, SLOT(openMapVisualizationButtonPressed()));
        QObject::connect(load_button, SIGNAL(pressed()), MainWindow, SLOT(loadMapButtonPressed()));
        QObject::connect(enter_heights_button, SIGNAL(pressed()), MainWindow, SLOT(enterHeightsButtonPressed()));
        QObject::connect(update_map_button, SIGNAL(pressed()), MainWindow, SLOT(updateFullMapButtonPressed()));
        QObject::connect(enter_speed_vectors_button, SIGNAL(pressed()), MainWindow, SLOT(enterSpeedVectorsButtonPressed()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        cell_width_label->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260 \321\217\321\207\320\265\320\271\320\272\320\270 \321\201\320\265\321\202\320\272\320\270", nullptr));
        cell_height_label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260 \321\217\321\207\320\265\320\271\320\272\320\270 \321\201\320\265\321\202\320\272\320\270", nullptr));
        scale_label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261 (\321\203.\320\265.:\320\274\320\265\321\202\321\200)", nullptr));
        map_label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        load_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214\n"
" \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        open_map_visualization_button->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 3D\n"
" \320\262\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\216\n"
" \321\202\320\265\320\272\321\203\321\211\320\265\320\263\320\276 \320\276\320\261\321\212\320\265\320\272\321\202\320\260", nullptr));
        save_map_as_image_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\321\203\n"
"(.jpeg, .png)", nullptr));
        enter_heights_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\262\321\213\321\201\320\276\321\202\n"
"(\320\277\321\200\320\270 \320\277\320\276\320\274\320\276\321\211\320\270 \n"
"\320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213)", nullptr));
        open_map_button->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\272\320\260\321\200\321\202\321\203 \320\262\n"
"\320\275\320\276\320\262\320\276\320\274 \320\276\320\272\320\275\320\265", nullptr));
        save_map_as_excel_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\321\203\n"
"(.xlsx)", nullptr));
        update_grid_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\321\202\321\200\320\276\320\270\321\202\321\214\n"
"\321\201\320\265\321\202\320\272\321\203", nullptr));
        update_map_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214\n"
"\320\276\320\261\320\273\320\260\321\201\321\202\321\214 \320\275\320\260\n"
"\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\270", nullptr));
        water_object_type_combo_box->setCurrentText(QString());
        ratio_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\220<span style=\" vertical-align:sub;\">z</span></p></body></html>", nullptr));
        enter_speed_vectors_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217\n"
"\320\262\320\265\320\272\321\202\320\276\321\200\320\276\320\262\n"
" \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\265\320\271", nullptr));
        computate_pressures_button->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217\n"
"\320\262\320\265\320\272\321\202\320\276\321\200\320\276\320\262\n"
" \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\265\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
