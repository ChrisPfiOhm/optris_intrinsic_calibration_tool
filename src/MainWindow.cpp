#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>

#include <pcl/common/time.h>


#include <iostream>

namespace {
const char* TEXT_LABEL_RESULT = "Intrinsic Matrix:\n"
                                "----------------------------\n";
}

MainWindow::MainWindow(const char* configFile, QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _dialog(new ConfigDialog(QString(QDir::homePath() + "/workspace/optris_intrinsic_calibration_tool/config/pattern.ini"))),
      _openni_sensor(new Openni()),
      _thermo_sensor(new ThermoCam(configFile)),
      _rgb_sensor(   new RGBCamera(1)),
      _rgb2_sensor(  new RGBCamera(2))
{
    _ui->setupUi(this);
    _ui->_buttonCalibrate->setDisabled(true);

    _intrinsic_calibration.setPattern(_dialog->getPattern(),
                                      cv::Size(_dialog->getRows(), _dialog->getCols()),
                                      _dialog->getPointDistance());
    _extrinsic_calibration.setPattern(_dialog->getPattern(),
                                      cv::Size(_dialog->getRows(), _dialog->getCols()),
                                      _dialog->getPointDistance());

    this->connect(_ui->actionOptions,    SIGNAL(triggered()), this, SLOT(slot_calibrationSettings()));
    this->connect(&_timer,               SIGNAL(timeout()),   this, SLOT(tick()));
    this->connect(_ui->_buttonCalibrate, SIGNAL(clicked()),   this, SLOT(calibrate()));

    _timer.start(33);
}

MainWindow::~MainWindow(void)
{
   // nothing to do here
}

void MainWindow::tick(void)
{
   static unsigned int i=0;

   // grab sensors
    _thermo_sensor->grab();
    _openni_sensor->grab();
    _rgb_sensor->grab();
    _rgb2_sensor->grab();

     cv::Mat image(     _rgb_sensor->getCalibrationImage());
     cv::Mat image2(    _rgb2_sensor->getCalibrationImage());
//     cv::Mat colorImage(_rgb_sensor->getVisualizationImage());

     if(i%10 == 0)
     {
        //        _intrinsic_calibration.setImage(image, colorImage);
        _extrinsic_calibration.setImages(image, image2);
     }

     i++;

     _ui->_thermoView->setMat(_rgb_sensor->getCalibrationImage());
     _ui->_depthView->setMat( _rgb2_sensor->getCalibrationImage());




    // update visualization
//    _ui->_thermoView->setMat(   _thermo_sensor->getVisualizationImage());
//    if(_intrinsic_calibration.calibrated()) _ui->_thresholdView->setMat(_intrinsic_calibration.getUndistored(colorImage));
//    else                                    _ui->_thresholdView->setMat(colorImage);
//
//    _ui->_depthView->setMat(_rgb2_sensor->getVisualizationImage());


    if(_extrinsic_calibration.getNrOfValids() >20)
       _ui->_buttonCalibrate->setDisabled(false);
}

void MainWindow::calibrate(void)
{
//   _intrinsic_calibration.calibrate();
   _extrinsic_calibration.calibrate();
//   std::cout << _intrinsic_calibration.getIntrinsic()  << std::endl;
//   std::cout << _intrinsic_calibration.getDistortion() << std::endl;
}


void MainWindow::slot_calibrationSettings(void)
{
   _dialog->show();
   _intrinsic_calibration.setPattern(_dialog->getPattern(),
                                     cv::Size(9, 6),
                                     0.06);

}

