/********************************************************************************
** Form generated from reading UI file 'paintingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTINGWIDGET_H
#define UI_PAINTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintingWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *main_panel_tab_widget;
    QWidget *drawing_tab;
    QFrame *enter_data_delimeter_line;
    QPushButton *accept_changes_button;
    QPushButton *discard_all_changes_button;
    QFrame *save_changes_delimeter_line;
    QPushButton *discard_last_changes_button;
    QPushButton *return_last_changes_button;
    QPushButton *enable_grid_button;
    QFrame *brush_setting_delimeter_line;
    QLabel *brush_label;
    QSlider *thickness_horizontal_slider;
    QLabel *thickness_label;
    QPushButton *brush_type_1_button;
    QPushButton *brush_type_2_button;
    QPushButton *brush_type_3_button;
    QPushButton *brush_type_4_button;
    QFrame *display_delimeter_line;
    QLabel *border_label;
    QPushButton *shadow_nonWO_button;
    QLabel *grid_display_label;
    QPushButton *update_map_button;
    QPushButton *update_grid_button;
    QPushButton *show_changes_button;
    QGraphicsView *map_editor_graphics_view;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *PaintingWidget)
    {
        if (PaintingWidget->objectName().isEmpty())
            PaintingWidget->setObjectName(QString::fromUtf8("PaintingWidget"));
        PaintingWidget->resize(1302, 908);
        verticalLayout_2 = new QVBoxLayout(PaintingWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        main_panel_tab_widget = new QTabWidget(PaintingWidget);
        main_panel_tab_widget->setObjectName(QString::fromUtf8("main_panel_tab_widget"));
        main_panel_tab_widget->setEnabled(true);
        main_panel_tab_widget->setMinimumSize(QSize(0, 150));
        main_panel_tab_widget->setMaximumSize(QSize(16777215, 130));
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
        drawing_tab = new QWidget();
        drawing_tab->setObjectName(QString::fromUtf8("drawing_tab"));
        enter_data_delimeter_line = new QFrame(drawing_tab);
        enter_data_delimeter_line->setObjectName(QString::fromUtf8("enter_data_delimeter_line"));
        enter_data_delimeter_line->setGeometry(QRect(80, 10, 16, 81));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        enter_data_delimeter_line->setFont(font);
        enter_data_delimeter_line->setFrameShape(QFrame::VLine);
        enter_data_delimeter_line->setFrameShadow(QFrame::Sunken);
        accept_changes_button = new QPushButton(drawing_tab);
        accept_changes_button->setObjectName(QString::fromUtf8("accept_changes_button"));
        accept_changes_button->setEnabled(true);
        accept_changes_button->setGeometry(QRect(1010, 20, 80, 71));
        QFont font1;
        font1.setPointSize(23);
        accept_changes_button->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/imgs/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        accept_changes_button->setIcon(icon);
        accept_changes_button->setIconSize(QSize(40, 40));
        discard_all_changes_button = new QPushButton(drawing_tab);
        discard_all_changes_button->setObjectName(QString::fromUtf8("discard_all_changes_button"));
        discard_all_changes_button->setEnabled(true);
        discard_all_changes_button->setGeometry(QRect(1100, 20, 80, 71));
        discard_all_changes_button->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/imgs/images/cansel.png"), QSize(), QIcon::Normal, QIcon::Off);
        discard_all_changes_button->setIcon(icon1);
        discard_all_changes_button->setIconSize(QSize(60, 60));
        save_changes_delimeter_line = new QFrame(drawing_tab);
        save_changes_delimeter_line->setObjectName(QString::fromUtf8("save_changes_delimeter_line"));
        save_changes_delimeter_line->setGeometry(QRect(990, 10, 16, 81));
        save_changes_delimeter_line->setFont(font);
        save_changes_delimeter_line->setFrameShape(QFrame::VLine);
        save_changes_delimeter_line->setFrameShadow(QFrame::Sunken);
        discard_last_changes_button = new QPushButton(drawing_tab);
        discard_last_changes_button->setObjectName(QString::fromUtf8("discard_last_changes_button"));
        discard_last_changes_button->setEnabled(false);
        discard_last_changes_button->setGeometry(QRect(100, 20, 31, 25));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/imgs/images/arrow_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        discard_last_changes_button->setIcon(icon2);
        return_last_changes_button = new QPushButton(drawing_tab);
        return_last_changes_button->setObjectName(QString::fromUtf8("return_last_changes_button"));
        return_last_changes_button->setEnabled(false);
        return_last_changes_button->setGeometry(QRect(150, 20, 31, 25));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/imgs/images/arrow_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        return_last_changes_button->setIcon(icon3);
        enable_grid_button = new QPushButton(drawing_tab);
        enable_grid_button->setObjectName(QString::fromUtf8("enable_grid_button"));
        enable_grid_button->setEnabled(true);
        enable_grid_button->setGeometry(QRect(870, 20, 121, 25));
        brush_setting_delimeter_line = new QFrame(drawing_tab);
        brush_setting_delimeter_line->setObjectName(QString::fromUtf8("brush_setting_delimeter_line"));
        brush_setting_delimeter_line->setGeometry(QRect(190, 10, 16, 81));
        brush_setting_delimeter_line->setFont(font);
        brush_setting_delimeter_line->setFrameShape(QFrame::VLine);
        brush_setting_delimeter_line->setFrameShadow(QFrame::Sunken);
        brush_label = new QLabel(drawing_tab);
        brush_label->setObjectName(QString::fromUtf8("brush_label"));
        brush_label->setGeometry(QRect(210, 10, 61, 21));
        thickness_horizontal_slider = new QSlider(drawing_tab);
        thickness_horizontal_slider->setObjectName(QString::fromUtf8("thickness_horizontal_slider"));
        thickness_horizontal_slider->setGeometry(QRect(210, 70, 201, 18));
        thickness_horizontal_slider->setOrientation(Qt::Horizontal);
        thickness_label = new QLabel(drawing_tab);
        thickness_label->setObjectName(QString::fromUtf8("thickness_label"));
        thickness_label->setGeometry(QRect(210, 40, 61, 21));
        brush_type_1_button = new QPushButton(drawing_tab);
        brush_type_1_button->setObjectName(QString::fromUtf8("brush_type_1_button"));
        brush_type_1_button->setGeometry(QRect(258, 10, 31, 25));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../arrow_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        brush_type_1_button->setIcon(icon4);
        brush_type_2_button = new QPushButton(drawing_tab);
        brush_type_2_button->setObjectName(QString::fromUtf8("brush_type_2_button"));
        brush_type_2_button->setGeometry(QRect(300, 10, 31, 25));
        brush_type_2_button->setIcon(icon4);
        brush_type_3_button = new QPushButton(drawing_tab);
        brush_type_3_button->setObjectName(QString::fromUtf8("brush_type_3_button"));
        brush_type_3_button->setGeometry(QRect(342, 10, 31, 25));
        brush_type_3_button->setIcon(icon4);
        brush_type_4_button = new QPushButton(drawing_tab);
        brush_type_4_button->setObjectName(QString::fromUtf8("brush_type_4_button"));
        brush_type_4_button->setGeometry(QRect(384, 10, 31, 25));
        brush_type_4_button->setIcon(icon4);
        display_delimeter_line = new QFrame(drawing_tab);
        display_delimeter_line->setObjectName(QString::fromUtf8("display_delimeter_line"));
        display_delimeter_line->setGeometry(QRect(560, 10, 16, 81));
        display_delimeter_line->setFont(font);
        display_delimeter_line->setFrameShape(QFrame::VLine);
        display_delimeter_line->setFrameShadow(QFrame::Sunken);
        border_label = new QLabel(drawing_tab);
        border_label->setObjectName(QString::fromUtf8("border_label"));
        border_label->setGeometry(QRect(440, 10, 61, 21));
        shadow_nonWO_button = new QPushButton(drawing_tab);
        shadow_nonWO_button->setObjectName(QString::fromUtf8("shadow_nonWO_button"));
        shadow_nonWO_button->setEnabled(true);
        shadow_nonWO_button->setGeometry(QRect(870, 60, 121, 25));
        grid_display_label = new QLabel(drawing_tab);
        grid_display_label->setObjectName(QString::fromUtf8("grid_display_label"));
        grid_display_label->setGeometry(QRect(750, 20, 91, 21));
        update_map_button = new QPushButton(drawing_tab);
        update_map_button->setObjectName(QString::fromUtf8("update_map_button"));
        update_map_button->setEnabled(true);
        update_map_button->setGeometry(QRect(10, 20, 71, 60));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(update_map_button->sizePolicy().hasHeightForWidth());
        update_map_button->setSizePolicy(sizePolicy);
        update_map_button->setMinimumSize(QSize(0, 0));
        update_map_button->setMaximumSize(QSize(16777215, 16777215));
        update_map_button->setBaseSize(QSize(100, 50));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/imgs/images/pncl.png"), QSize(), QIcon::Normal, QIcon::Off);
        update_map_button->setIcon(icon5);
        update_map_button->setIconSize(QSize(40, 40));
        update_grid_button = new QPushButton(drawing_tab);
        update_grid_button->setObjectName(QString::fromUtf8("update_grid_button"));
        update_grid_button->setEnabled(true);
        update_grid_button->setGeometry(QRect(590, 30, 100, 60));
        update_grid_button->setMinimumSize(QSize(100, 60));
        update_grid_button->setMaximumSize(QSize(100, 60));
        update_grid_button->setBaseSize(QSize(100, 50));
        show_changes_button = new QPushButton(drawing_tab);
        show_changes_button->setObjectName(QString::fromUtf8("show_changes_button"));
        show_changes_button->setEnabled(true);
        show_changes_button->setGeometry(QRect(710, 60, 141, 25));
        main_panel_tab_widget->addTab(drawing_tab, QString());

        verticalLayout_2->addWidget(main_panel_tab_widget);

        map_editor_graphics_view = new QGraphicsView(PaintingWidget);
        map_editor_graphics_view->setObjectName(QString::fromUtf8("map_editor_graphics_view"));
        map_editor_graphics_view->setMinimumSize(QSize(1280, 720));

        verticalLayout_2->addWidget(map_editor_graphics_view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PaintingWidget);
        QObject::connect(brush_type_3_button, SIGNAL(pressed()), PaintingWidget, SLOT(brushType3ButtonPressed()));
        QObject::connect(brush_type_4_button, SIGNAL(pressed()), PaintingWidget, SLOT(brushType4ButtonPressed()));
        QObject::connect(return_last_changes_button, SIGNAL(pressed()), PaintingWidget, SLOT(returnLastChangesButtonPressed()));
        QObject::connect(shadow_nonWO_button, SIGNAL(pressed()), PaintingWidget, SLOT(shadowNonWOButtonPressed()));
        QObject::connect(update_map_button, SIGNAL(pressed()), PaintingWidget, SLOT(updateMapButtonPressed()));
        QObject::connect(enable_grid_button, SIGNAL(pressed()), PaintingWidget, SLOT(enableGridButtonPressed()));
        QObject::connect(brush_type_2_button, SIGNAL(pressed()), PaintingWidget, SLOT(brushType2ButtonPressed()));
        QObject::connect(discard_all_changes_button, SIGNAL(pressed()), PaintingWidget, SLOT(discardAllChangesButtonPressed()));
        QObject::connect(accept_changes_button, SIGNAL(pressed()), PaintingWidget, SLOT(acceptChangesButtonPressed()));
        QObject::connect(discard_last_changes_button, SIGNAL(pressed()), PaintingWidget, SLOT(discardLastChandesButtonPressed()));
        QObject::connect(show_changes_button, SIGNAL(pressed()), PaintingWidget, SLOT(showChangesButtonPressed()));
        QObject::connect(update_grid_button, SIGNAL(pressed()), PaintingWidget, SLOT(updateGridButtonPressed()));
        QObject::connect(brush_type_1_button, SIGNAL(pressed()), PaintingWidget, SLOT(brushType1ButtonPressed()));

        main_panel_tab_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PaintingWidget);
    } // setupUi

    void retranslateUi(QWidget *PaintingWidget)
    {
        PaintingWidget->setWindowTitle(QCoreApplication::translate("PaintingWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        accept_changes_button->setToolTip(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        accept_changes_button->setText(QString());
#if QT_CONFIG(tooltip)
        discard_all_changes_button->setToolTip(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\236\321\202\320\274\320\265\320\275\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        discard_all_changes_button->setText(QString());
#if QT_CONFIG(tooltip)
        discard_last_changes_button->setToolTip(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        discard_last_changes_button->setText(QString());
#if QT_CONFIG(tooltip)
        return_last_changes_button->setToolTip(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\265</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        return_last_changes_button->setText(QString());
        enable_grid_button->setText(QCoreApplication::translate("PaintingWidget", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", nullptr));
        brush_label->setText(QCoreApplication::translate("PaintingWidget", "\320\232\320\270\321\201\321\202\321\214:", nullptr));
        thickness_label->setText(QCoreApplication::translate("PaintingWidget", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260:", nullptr));
        brush_type_1_button->setText(QCoreApplication::translate("PaintingWidget", "1", nullptr));
        brush_type_2_button->setText(QCoreApplication::translate("PaintingWidget", "2", nullptr));
        brush_type_3_button->setText(QCoreApplication::translate("PaintingWidget", "3", nullptr));
        brush_type_4_button->setText(QCoreApplication::translate("PaintingWidget", "4", nullptr));
        border_label->setText(QCoreApplication::translate("PaintingWidget", "\320\223\321\200\320\260\320\275\320\270\321\206\320\260:", nullptr));
        shadow_nonWO_button->setText(QCoreApplication::translate("PaintingWidget", "\320\227\320\260\321\202\320\265\320\274\320\275\320\270\321\202\321\214", nullptr));
        grid_display_label->setText(QCoreApplication::translate("PaintingWidget", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265:", nullptr));
#if QT_CONFIG(tooltip)
        update_map_button->setToolTip(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\237\320\265\321\200\320\265\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\276\320\261\320\273\320\260\321\201\321\202\321\214 \320\275\320\260 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\270</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        update_map_button->setWhatsThis(QCoreApplication::translate("PaintingWidget", "<html><head/><body><p>\320\237\320\265\321\200\320\265\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214\\n\320\276\320\261\320\273\320\260\321\201\321\202\321\214 \320\275\320\260\\n\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\270</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        update_map_button->setText(QString());
        update_grid_button->setText(QCoreApplication::translate("PaintingWidget", "\320\237\320\265\321\200\320\265\321\201\321\202\321\200\320\276\320\270\321\202\321\214\n"
"\321\201\320\265\321\202\320\272\321\203", nullptr));
        show_changes_button->setText(QCoreApplication::translate("PaintingWidget", "\320\237\321\200\320\265\320\264\320\276\321\201\320\274\320\276\321\202\321\200 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\271", nullptr));
        main_panel_tab_widget->setTabText(main_panel_tab_widget->indexOf(drawing_tab), QCoreApplication::translate("PaintingWidget", "\320\240\320\270\321\201\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaintingWidget: public Ui_PaintingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTINGWIDGET_H
