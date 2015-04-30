/*
 * CalibrationViewWidget.h
 *
 *  Created on: 31.10.2014
 *      Author: chris
 */

#ifndef SRC_CALIBRATIONVIEWWIDGET_H_
#define SRC_CALIBRATIONVIEWWIDGET_H_

// qt includes
#include <QWidget>

// opencv includes
#include <opencv2/core/core.hpp>


// calibration includes
#include <sensors/ISensor.h>
#include "IntrinsicCalibration.h"

/**
 * @namespace Ui
 */
namespace Ui{
class CalibrationViewWidget;
}

/**
 * @class   CalibrationViewWidget
 * @author  Christian Pfitzner
 * @date    2014-10-30
 */
class CalibrationViewWidget : public QWidget
{
   Q_OBJECT
public:
   /**
    * Default Constructor
    */
   CalibrationViewWidget(QWidget* parent);
   /**
    * Default destructor
    */
   virtual ~CalibrationViewWidget(void);


   // SETTERS
   /**
    * Function to show binary image
    * @param image
    */
   void setBinImage(const cv::Mat& image);
   /**
    * Function to show color image
    * @param image
    */
   void setColorImage(const cv::Mat& image);
   /**
    * Function to set sensor
    * @param sensor
    */
   void setSensor(ISensor* sensor, QString name="");
   /**
    * Function to set intrinsic calibration
    * @param intrinsic
    */
   void setIntrinsicCalibration(IntrinsicCalibration* intrinsic);


public slots:
   /**
    * Slot to update visualization
    */
   void update(void);
   void slot_capture(void);

private slots:
   void slot_calibrate(void);
   void slot_calibrateExtrinsic(void);

private:
   ISensor*                   _sensor;
   IntrinsicCalibration*      _intrinsic;
   Ui::CalibrationViewWidget* _ui;         //!< pointer on gui

};

#endif /* SRC_CALIBRATIONVIEWWIDGET_H_ */
