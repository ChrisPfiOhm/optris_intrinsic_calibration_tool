/*
 * CalibrationViewWidget.cpp
 *
 *  Created on: 31.10.2014
 *      Author: chris
 */

#include <CalibrationViewWidget.h>
#include <../build/ui_CalibrationViewWidget.h>

CalibrationViewWidget::CalibrationViewWidget(QWidget* parent)
: QWidget(parent),
  _sensor(NULL),
  _intrinsic(NULL),
  _ui(new Ui::CalibrationViewWidget),
  _initialized(false)
{
   _ui->setupUi(this);

   _ui->_binViewer->setSize(  QSize(320,240));
   _ui->_colorViewer->setSize(QSize(320,240));

   _ui->_saveButton->setDisabled(true);
}


CalibrationViewWidget::~CalibrationViewWidget(void)
{
   delete _ui;
}


void CalibrationViewWidget::setBinImage(const cv::Mat& image)
{
   _ui->_binViewer->setMat(image);
}


void CalibrationViewWidget::setColorImage(const cv::Mat& image)
{
   _ui->_colorViewer->setMat(image);
}


void CalibrationViewWidget::setSensor(ISensor* sensor, QString name)
{
   if(sensor == NULL)
      return;

   _sensor = sensor;
   _ui->_sensorName->setText(name);
   _initialized = true;
}


void CalibrationViewWidget::setIntrinsicCalibration(IntrinsicCalibration* intrinsic)
{
   _intrinsic = intrinsic;

   // SIGNALS AND SLOTS
   this->connect(_ui->_captureButton,      SIGNAL(clicked()),   this,       SLOT(slot_capture()));
   this->connect(_ui->_calibrateButton,    SIGNAL(clicked()),   this,       SLOT(slot_calibrate()));
}


void CalibrationViewWidget::update(void)
{
   if(!_initialized)      return;

   _sensor->grab();

   cv::Mat bin   =  _sensor->getCalibrationImage();
   cv::Mat viz   =  _sensor->getVisualizationImage();


   if(_intrinsic) {
      _intrinsic->setImage(bin, viz);

      if(_intrinsic->calibrated()) {
         viz = _intrinsic->getUndistored(viz);
      }
   }

   this->setBinImage(  bin);
   this->setColorImage(viz);
}

void CalibrationViewWidget::slot_capture(void)
{
   _intrinsic->slot_capture();
   _ui->_images->addImage(_sensor->getCalibrationImage());
}

void CalibrationViewWidget::slot_calibrate(void)
{
   _intrinsic->slot_calibrate();
   _sensor->setIntrinsic( _intrinsic->getIntrinsic());
   _sensor->setDistortion(_intrinsic->getDistortion());
   _sensor->slot_saveConfig("/tmp/thermo_intrinsic.ini");
   _ui->_saveButton->setDisabled(false);
}
