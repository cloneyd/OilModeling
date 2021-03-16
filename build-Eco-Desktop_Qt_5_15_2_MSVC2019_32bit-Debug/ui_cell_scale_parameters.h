/********************************************************************************
** Form generated from reading UI file 'cell_scale_parameters.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELL_SCALE_PARAMETERS_H
#define UI_CELL_SCALE_PARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cell_scale_parametres
{
public:
    QFormLayout *formLayout;
    QLabel *cell_width_label;
    QLabel *cell_height_label;
    QLabel *scale_label;
    QDialogButtonBox *save_changes_button_box;
    QDoubleSpinBox *cell_width_double_spin_box;
    QDoubleSpinBox *cell_height_double_spin_box;
    QDoubleSpinBox *scale_double_spin_box;

    void setupUi(QWidget *cell_scale_parametres)
    {
        if (cell_scale_parametres->objectName().isEmpty())
            cell_scale_parametres->setObjectName(QString::fromUtf8("cell_scale_parametres"));
        cell_scale_parametres->resize(400, 151);
        formLayout = new QFormLayout(cell_scale_parametres);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        cell_width_label = new QLabel(cell_scale_parametres);
        cell_width_label->setObjectName(QString::fromUtf8("cell_width_label"));
        cell_width_label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, cell_width_label);

        cell_height_label = new QLabel(cell_scale_parametres);
        cell_height_label->setObjectName(QString::fromUtf8("cell_height_label"));
        cell_height_label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, cell_height_label);

        scale_label = new QLabel(cell_scale_parametres);
        scale_label->setObjectName(QString::fromUtf8("scale_label"));
        scale_label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, scale_label);

        save_changes_button_box = new QDialogButtonBox(cell_scale_parametres);
        save_changes_button_box->setObjectName(QString::fromUtf8("save_changes_button_box"));
        save_changes_button_box->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(3, QFormLayout::LabelRole, save_changes_button_box);

        cell_width_double_spin_box = new QDoubleSpinBox(cell_scale_parametres);
        cell_width_double_spin_box->setObjectName(QString::fromUtf8("cell_width_double_spin_box"));
        cell_width_double_spin_box->setAlignment(Qt::AlignCenter);
        cell_width_double_spin_box->setDecimals(3);
        cell_width_double_spin_box->setMaximum(100000.000000000000000);
        cell_width_double_spin_box->setSingleStep(0.500000000000000);
        cell_width_double_spin_box->setValue(10.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, cell_width_double_spin_box);

        cell_height_double_spin_box = new QDoubleSpinBox(cell_scale_parametres);
        cell_height_double_spin_box->setObjectName(QString::fromUtf8("cell_height_double_spin_box"));
        cell_height_double_spin_box->setAlignment(Qt::AlignCenter);
        cell_height_double_spin_box->setDecimals(3);
        cell_height_double_spin_box->setMaximum(100000.000000000000000);
        cell_height_double_spin_box->setSingleStep(0.500000000000000);
        cell_height_double_spin_box->setValue(10.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, cell_height_double_spin_box);

        scale_double_spin_box = new QDoubleSpinBox(cell_scale_parametres);
        scale_double_spin_box->setObjectName(QString::fromUtf8("scale_double_spin_box"));
        scale_double_spin_box->setAlignment(Qt::AlignCenter);
        scale_double_spin_box->setDecimals(3);
        scale_double_spin_box->setMaximum(100000.000000000000000);
        scale_double_spin_box->setSingleStep(0.500000000000000);
        scale_double_spin_box->setValue(10.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, scale_double_spin_box);


        retranslateUi(cell_scale_parametres);

        QMetaObject::connectSlotsByName(cell_scale_parametres);
    } // setupUi

    void retranslateUi(QWidget *cell_scale_parametres)
    {
        cell_scale_parametres->setWindowTitle(QCoreApplication::translate("cell_scale_parametres", "Form", nullptr));
        cell_width_label->setText(QCoreApplication::translate("cell_scale_parametres", "\320\250\320\270\321\200\320\270\320\275\320\260 \321\217\321\207\320\265\320\271\320\272\320\270", nullptr));
        cell_height_label->setText(QCoreApplication::translate("cell_scale_parametres", "\320\222\321\213\321\201\320\276\321\202\320\260 \321\217\321\207\320\265\320\271\320\272\320\270", nullptr));
        scale_label->setText(QCoreApplication::translate("cell_scale_parametres", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cell_scale_parametres: public Ui_cell_scale_parametres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELL_SCALE_PARAMETERS_H
