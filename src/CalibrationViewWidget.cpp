/*
 * CalibrationViewWidget.cpp
 *
 *  Created on: 31.10.2014
 *      Author: chris
 */

#include <CalibrationViewWidget.h>
#include <../ui_CalibrationViewWidget.h>

CalibrationViewWidget::CalibrationViewWidget(QWidget* parent)
: QWidget(parent),
  _sensor(NULL),
  _intrinsic(NULL),
  _ui(new Ui::CalibrationViewWidget)
{
   _ui->setupUi(this);

   // SIGNALS AND SLOTS


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
   _ui->_binViewer->setMat(image);

}

void CalibrationViewWidget::setSensor(ISensor* sensor)
{
   _sensor = sensor;
}

void CalibrationViewWidget::setIntrinsicCalibration(IntrinsicCalibration* intrinsic)
{
   _intrinsic = intrinsic;
}


void CalibrationViewWidget::update(void)
{
   this->setBinImage(  _sensor->getCalibrationImage());
   this->setColorImage(_sensor->getVisualizationImage());
}
