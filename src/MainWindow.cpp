#include "MainWindow.h"
#include "../build/ui_MainWindow.h"

#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>

#include <iostream>

#include "sensors/CheckDevices.h"

#include <sys/ioctl.h>

MainWindow::MainWindow(const char* configFile, QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _sensor1(new RGBCamera(1)),
      _sensor2(new RGBCamera(2)),
      _dialog(new ConfigDialog(QString(QDir::homePath() + "/workspace/optris_intrinsic_calibration_tool/config/pattern.ini")))
{
    _ui->setupUi(this);

    // set config for calibration pattern
    _intrinsic_sensor1.setPattern(_dialog->getPattern(), cv::Size(9, 6), 0.0375);
    _intrinsic_sensor2.setPattern(_dialog->getPattern(), cv::Size(9, 6), 0.0375);

    this->connect(_ui->actionOptions,    SIGNAL(triggered()), this, SLOT(slot_calibrationSettings()));
    this->connect(_ui->_buttonCaliExt2,  SIGNAL(clicked()),   this, SLOT(slot_stereoCapture()));
    this->connect(_ui->_reset,           SIGNAL(clicked()),   this, SLOT(slot_reset()));
    this->connect(&_timer,               SIGNAL(timeout()),   this, SLOT(tick()));

    _ui->_buttonCaliExt2->setDisabled(true);


//    _thermo_sensor->loadConfig("/home/chris/workspace/thermo_intrinsic.ini");
//    _openni_sensor->loadConfig("/home/chris/workspace/kinect_intrinsic.ini");


    _ui->_view1->setSensor(_sensor1, QString("Sensor1"));
    _ui->_view2->setSensor(_sensor2, QString("Sensor2"));

    _ui->_view1->setIntrinsicCalibration(&_intrinsic_sensor1);
    _ui->_view2->setIntrinsicCalibration(&_intrinsic_sensor2);

    CheckDevices cd;
    cd.check();

    _timer.start(50);

}

MainWindow::~MainWindow(void)
{
   delete _sensor1;
   delete _sensor2;
}

void MainWindow::tick(void)
{
   _ui->_view1->update();
   _ui->_view2->update();


   // enable button for calibration
   if(_intrinsic_sensor1.calibrated() && _intrinsic_sensor2.calibrated())
      _ui->_buttonCaliExt2->setDisabled(false);
}


void MainWindow::slot_calibrationSettings(void)
{
   _dialog->show();
}

void MainWindow::slot_stereoCapture(void)
{
   // get translation vector
   cv::Mat t1 = _intrinsic_sensor1.getTranslationVector();
   cv::Mat t2 = _intrinsic_sensor2.getTranslationVector();

   // get rotation vectors
   cv::Mat r1 = _intrinsic_sensor1.getRotationVector();
   cv::Mat r2 = _intrinsic_sensor2.getRotationVector();

   // output to terminal
   std::cout << "Delta Translation: " << t1 - t2 << std::endl;
   std::cout << "Delta Rotation:    " << r1 - r2 << std::endl;
}

void MainWindow::slot_reset(void)
{
   _intrinsic_sensor1.slot_reset();
   _intrinsic_sensor2.slot_reset();
}

