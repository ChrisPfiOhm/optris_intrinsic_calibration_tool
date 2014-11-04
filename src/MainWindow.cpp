#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>

#include <pcl/common/time.h>
#include <iostream>

MainWindow::MainWindow(const char* configFile, QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _dialog(new ConfigDialog(QString(QDir::homePath() + "/workspace/optris_intrinsic_calibration_tool/config/pattern.ini"))),
      _openni_sensor(new Openni()),
      _thermo_sensor(new ThermoCam(configFile))
//      _rgb_sensor(   new RGBCamera(0))
//      _rgb2_sensor(  new RGBCamera(1))
{
    _ui->setupUi(this);

    _intrinsic_calibration_thermo.setPattern(_dialog->getPattern(),
                                             cv::Size(9, 6),
                                             0.075);
    _intrinsic_calibration_kinect.setPattern(_dialog->getPattern(),
                                             cv::Size(9, 6),
                                             0.075);

    _extrinsic_calibration.setPattern(_dialog->getPattern(),
                                      cv::Size(9, 6),
                                      0.075);

    this->connect(_ui->actionOptions,    SIGNAL(triggered()), this, SLOT(slot_calibrationSettings()));
    this->connect(_ui->_buttonCalibrate, SIGNAL(clicked()),   this, SLOT(slot_stereoCalibrate()));
    this->connect(_ui->_buttonCapture,   SIGNAL(clicked()),   this, SLOT(slot_stereoCapture()));
    this->connect(&_timer,               SIGNAL(timeout()),   this, SLOT(tick()));

    _timer.start(33);

    _thermo_sensor->loadConfig("/home/chris/workspace/thermo_intrinsic.ini");
    _openni_sensor->loadConfig("/home/chris/workspace/kinect_intrinsic.ini");

    _ui->_view1->setSensor(_openni_sensor, QString("Kinect"));
    _ui->_view2->setSensor(_thermo_sensor, QString("Thermo"));

    _ui->_view1->setIntrinsicCalibration(&_intrinsic_calibration_kinect);
    _ui->_view2->setIntrinsicCalibration(&_intrinsic_calibration_thermo);

    std::cout << _openni_sensor->getIntrinsic() << std::endl;

    std::cout <<

    _extrinsic_calibration.setDataSensor1(_openni_sensor->getIntrinsic(), _openni_sensor->getDistortion());
    _extrinsic_calibration.setDataSensor2(_thermo_sensor->getIntrinsic(), _thermo_sensor->getDistortion());
}

MainWindow::~MainWindow(void)
{
   // nothing to do here
}

void MainWindow::tick(void)
{
   _ui->_view1->update();
   _ui->_view2->update();
}


void MainWindow::slot_calibrationSettings(void)
{
   _dialog->show();
//   _intrinsic_calibration.setPattern(_dialog->getPattern(),
//                                     cv::Size(1, 1),
//                                     0.075);
}

void MainWindow::slot_stereoCalibrate(void)
{
   _extrinsic_calibration.calibrate();
}

void MainWindow::slot_stereoCapture(void)
{
   _extrinsic_calibration.setImages(_openni_sensor->getCalibrationImage(),
                                    _thermo_sensor->getCalibrationImage());
}

