/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "CalibrationViewWidget.h"
#include "OpenCvWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOptions;
    QAction *actionSensor;
    QAction *actionUndistor;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    CalibrationViewWidget *_view1;
    CalibrationViewWidget *_view2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *_buttonCalibrate;
    QPushButton *_buttonCapture;
    QSpacerItem *verticalSpacer;
    OpenCvWidget *_fusion;
    QLabel *_labelResult;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuImage;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(875, 600);
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionSensor = new QAction(MainWindow);
        actionSensor->setObjectName(QString::fromUtf8("actionSensor"));
        actionUndistor = new QAction(MainWindow);
        actionUndistor->setObjectName(QString::fromUtf8("actionUndistor"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _view1 = new CalibrationViewWidget(centralwidget);
        _view1->setObjectName(QString::fromUtf8("_view1"));

        horizontalLayout->addWidget(_view1);

        _view2 = new CalibrationViewWidget(centralwidget);
        _view2->setObjectName(QString::fromUtf8("_view2"));

        horizontalLayout->addWidget(_view2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        _buttonCalibrate = new QPushButton(centralwidget);
        _buttonCalibrate->setObjectName(QString::fromUtf8("_buttonCalibrate"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_buttonCalibrate->sizePolicy().hasHeightForWidth());
        _buttonCalibrate->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(_buttonCalibrate);

        _buttonCapture = new QPushButton(centralwidget);
        _buttonCapture->setObjectName(QString::fromUtf8("_buttonCapture"));
        sizePolicy.setHeightForWidth(_buttonCapture->sizePolicy().hasHeightForWidth());
        _buttonCapture->setSizePolicy(sizePolicy);
        _buttonCapture->setCheckable(true);
        _buttonCapture->setChecked(false);

        verticalLayout->addWidget(_buttonCapture);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        _fusion = new OpenCvWidget(centralwidget);
        _fusion->setObjectName(QString::fromUtf8("_fusion"));
        _fusion->setMinimumSize(QSize(0, 80));

        verticalLayout->addWidget(_fusion);

        _labelResult = new QLabel(centralwidget);
        _labelResult->setObjectName(QString::fromUtf8("_labelResult"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_labelResult->sizePolicy().hasHeightForWidth());
        _labelResult->setSizePolicy(sizePolicy1);
        _labelResult->setMinimumSize(QSize(256, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        _labelResult->setFont(font);
        _labelResult->setText(QString::fromUtf8(""));
        _labelResult->setTextFormat(Qt::PlainText);

        verticalLayout->addWidget(_labelResult);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 875, 28));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuImage = new QMenu(menubar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuImage->menuAction());
        menuSettings->addAction(actionOptions);
        menuSettings->addAction(actionSensor);
        menuImage->addAction(actionUndistor);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Optris Intrinsic Calibration Tool", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "CalibrationPattern", 0, QApplication::UnicodeUTF8));
        actionSensor->setText(QApplication::translate("MainWindow", "Sensor", 0, QApplication::UnicodeUTF8));
        actionUndistor->setText(QApplication::translate("MainWindow", "Undistor", 0, QApplication::UnicodeUTF8));
        _buttonCalibrate->setText(QApplication::translate("MainWindow", "Calibrate", 0, QApplication::UnicodeUTF8));
        _buttonCapture->setText(QApplication::translate("MainWindow", "Caputre", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        menuImage->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
