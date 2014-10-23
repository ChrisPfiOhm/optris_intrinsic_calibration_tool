/********************************************************************************
** Form generated from reading UI file 'ConfigDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *_spinThreshold;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *_spinRows;
    QLabel *label_3;
    QSpinBox *_spinCols;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *_spinDistance;
    QComboBox *_patternBox;
    QLabel *image;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *_buttonClose;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QString::fromUtf8("ConfigDialog"));
        ConfigDialog->resize(240, 339);
        verticalLayout = new QVBoxLayout(ConfigDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ConfigDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        _spinThreshold = new QDoubleSpinBox(ConfigDialog);
        _spinThreshold->setObjectName(QString::fromUtf8("_spinThreshold"));
        _spinThreshold->setValue(30);

        horizontalLayout->addWidget(_spinThreshold);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(ConfigDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        _spinRows = new QSpinBox(ConfigDialog);
        _spinRows->setObjectName(QString::fromUtf8("_spinRows"));
        _spinRows->setMinimum(1);
        _spinRows->setValue(4);

        horizontalLayout_3->addWidget(_spinRows);

        label_3 = new QLabel(ConfigDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        _spinCols = new QSpinBox(ConfigDialog);
        _spinCols->setObjectName(QString::fromUtf8("_spinCols"));
        _spinCols->setMinimum(1);
        _spinCols->setValue(7);

        horizontalLayout_3->addWidget(_spinCols);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(ConfigDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        _spinDistance = new QDoubleSpinBox(ConfigDialog);
        _spinDistance->setObjectName(QString::fromUtf8("_spinDistance"));
        _spinDistance->setDecimals(3);
        _spinDistance->setMaximum(99.999);
        _spinDistance->setSingleStep(0.01);
        _spinDistance->setValue(0.05);

        horizontalLayout_4->addWidget(_spinDistance);


        verticalLayout->addLayout(horizontalLayout_4);

        _patternBox = new QComboBox(ConfigDialog);
        _patternBox->setObjectName(QString::fromUtf8("_patternBox"));

        verticalLayout->addWidget(_patternBox);

        image = new QLabel(ConfigDialog);
        image->setObjectName(QString::fromUtf8("image"));

        verticalLayout->addWidget(image);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        _buttonClose = new QPushButton(ConfigDialog);
        _buttonClose->setObjectName(QString::fromUtf8("_buttonClose"));

        horizontalLayout_2->addWidget(_buttonClose);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ConfigDialog);

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "Configuration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConfigDialog", "Temp Threshold:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConfigDialog", "Rows:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConfigDialog", "Cols:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ConfigDialog", "Point Distance: (mm)", 0, QApplication::UnicodeUTF8));
        _patternBox->clear();
        _patternBox->insertItems(0, QStringList()
         << QApplication::translate("ConfigDialog", "Symetrical Circles", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConfigDialog", "Chessboard", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConfigDialog", "Asymetrical Circles", 0, QApplication::UnicodeUTF8)
        );
        image->setText(QString());
        _buttonClose->setText(QApplication::translate("ConfigDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
