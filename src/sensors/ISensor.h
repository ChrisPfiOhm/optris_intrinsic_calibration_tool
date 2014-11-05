/*
 * ISensor.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_ISENSOR_H_
#define SRC_ISENSOR_H_


#include <opencv2/opencv.hpp>

// QT includes
#include <QSettings>
#include <QObject>
#include <QDebug>

class ISensor;



/**
 * @class   ISensor
 * @author  Christian Pfitzner
 * @date    2014-10-27
 */
class ISensor : public QObject
{
   Q_OBJECT
public:
   /**
    * Virtual destructor for interface
    */
   virtual ~ISensor(void) { }
   /**
    * Abstract method grab
    */
   virtual void grab(void) = 0;

   // SAVE AND LOAD
   /**
    * Function to load config parameters
    * @param path
    */
   void loadConfig(QString path = "")
   {
      if(!path.length()) {
          qDebug() << "[" << __PRETTY_FUNCTION__ << "]: config path not set.";
          return;
      }

      QSettings settings(path, QSettings::NativeFormat);


      cv::Mat intrinsic = cv::Mat::zeros(3, 3, CV_64F);
      settings.beginGroup("calibration");
      int size = settings.beginReadArray("intrinsic");

      // check for size of intrinsic matrix
      if(size != 9) {
         qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: error in config file " << path;
         qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: size of intrinsic wrong";
         return;
      }

      unsigned int idx = 0;
      for (   int col=0; col<intrinsic.cols ; col++) {
         for (int row=0; row<intrinsic.rows ; row++)
         {
            settings.setArrayIndex(idx);
            intrinsic.at<double>(row, col) = settings.value("value").toDouble();
            idx++;
         }
      }
      settings.endArray();


      cv::Mat distortion = cv::Mat::zeros(1, 5, CV_64F);
      size = settings.beginReadArray("distortion");

      // check for size of distortion parameters
      if(size != 5) {
         qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: error in config file " << path;
         qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: size of distortion wrong";
         return;
      }

      idx = 0;
      for (   unsigned int col=0; col<(unsigned int)distortion.cols ; col++) {
         for (unsigned int row=0; row<(unsigned int)distortion.rows ; row++)
         {
            settings.setArrayIndex(idx);
            distortion.at<double>(row, col) = settings.value("value").toDouble();
            idx++;
         }
      }

      settings.endArray();
      settings.endGroup();

      _intrinsic  = intrinsic;
      _distortion = distortion;
   }


   // GETTERS
   /**
    * Abstract method to get calibration image
    * @return
    */
   virtual const cv::Mat& getCalibrationImage(void)   = 0;
   /**
    * Abstract method to get image for visualization
    * @return
    */
   virtual const cv::Mat& getVisualizationImage(void) = 0;
   /**
    * Function to get intrinsic parameters
    * @return
    */
   virtual const cv::Mat& getIntrinsic(void)  const  { return _intrinsic;  }
   /**
    * Function to get distortion parameters
    * @return
    */
   virtual const cv::Mat& getDistortion(void) const  { return _distortion; }

   // SETTERS
   /**
    * Function to set intrinsic calibration parameters
    * @param intrinsic
    */
   virtual void setIntrinsic(const cv::Mat& intrinsic)   { _intrinsic = intrinsic; }
   /**
    * Function to set distortion parameters
    * @param distortion
    */
   virtual void setDistortion(const cv::Mat& distortion) { _distortion = distortion; }

public slots:
   void slot_saveConfig(QString path)
   {
      if(!path.length()) {
          qDebug() << "[" << __PRETTY_FUNCTION__ << "]: config path not set.";
          return;
      }

      QSettings settings(path, QSettings::NativeFormat);
      settings.beginGroup("calibration");

      // intrinsic parameters
      if(_intrinsic.rows != 0)
      {
         settings.beginWriteArray("intrinsic");
         unsigned int idx = 0;
         for (   int col = 0; col < _intrinsic.cols; col++) {
            for (int row = 0; row < _intrinsic.rows; row++)
            {
               settings.setArrayIndex(idx);
               settings.setValue("value", _intrinsic.at<double>(row, col));
               idx++;
            }
         }
         settings.endArray();
      }
      else
      {
         qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: intrinsic not set for saving";
      }

      // distortion parameters
      if(_distortion.rows != 0)
      {
         settings.beginWriteArray("distortion");
         unsigned int idx = 0;
         for (   int col = 0; col < _distortion.cols; col++) {
            for (int row = 0; row < _distortion.rows; row++)
            {
               settings.setArrayIndex(idx);
               settings.setValue("value", _distortion.at<double>(row, col));
               idx++;
            }
         }
         settings.endArray();
      }
      else
        {
           qDebug() << "[" <<__PRETTY_FUNCTION__ << "]: distortion not set for saving";
        }

      settings.endGroup();
   }

private:
   cv::Mat _intrinsic;
   cv::Mat _distortion;
};




#endif /* SRC_ISENSOR_H_ */
