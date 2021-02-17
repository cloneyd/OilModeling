/********************************************************************************
** Form generated from reading UI file 'gridcreatorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRIDCREATORWIDGET_H
#define UI_GRIDCREATORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GridCreatorWidget
{
public:
    QGraphicsView *graphics_view;

    void setupUi(QWidget *GridCreatorWidget)
    {
        if (GridCreatorWidget->objectName().isEmpty())
            GridCreatorWidget->setObjectName(QString::fromUtf8("GridCreatorWidget"));
        GridCreatorWidget->resize(400, 300);
        graphics_view = new QGraphicsView(GridCreatorWidget);
        graphics_view->setObjectName(QString::fromUtf8("graphics_view"));
        graphics_view->setGeometry(QRect(0, 0, 400, 300));

        retranslateUi(GridCreatorWidget);

        QMetaObject::connectSlotsByName(GridCreatorWidget);
    } // setupUi

    void retranslateUi(QWidget *GridCreatorWidget)
    {
        GridCreatorWidget->setWindowTitle(QCoreApplication::translate("GridCreatorWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GridCreatorWidget: public Ui_GridCreatorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRIDCREATORWIDGET_H
