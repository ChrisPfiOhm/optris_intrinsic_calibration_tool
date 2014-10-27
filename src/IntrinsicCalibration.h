/*
 * IntrinsicCalibration.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_INTRINSICCALIBRATION_H_
#define SRC_INTRINSICCALIBRATION_H_

#include <opencv2/core/core.hpp>

#include <ConfigDialog.h>

#include <QString>

/**
 * @class   IntrinsicCalibration
 * @author  Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Wrapper class for opencvs intrinsic calibration
 */
class IntrinsicCalibration
{
public:
   /**
    * Default constructor
    */
   IntrinsicCalibration(void);
   /**
    * Default destructor
    */
   virtual ~IntrinsicCalibration(void);

   // SETTERS
   /**
    * Function to set image for calibration. If corners are found the image is returned withing drawn corners
    * @param   binaryImage
    * @return  true if pattern was found
    */
   bool setImage(cv::Mat binaryImage, cv::Mat colorImage = cv::Mat());
   /**
    * Function to set type of calibration pattern
    * @param type
    * @param size
    */
   void setPattern(ConfigDialog::Pattern type, cv::Size size, const float dist);

   // GETTERS
   /**
    * Function to return intrinsic calibration matrix
    * @return  intrinsic matrix
    */
   cv::Mat getIntrinsic(void) const   { return _intrinsic;  }
   /**
    * Function to get distrotion of camera
    * @return
    */
   cv::Mat getDistortion(void) const  { return _distortion; }
   /**
    * Function to return number of valid images for calibration
    * @return
    */
   const unsigned int& getNrOfValids(void) const { return _valid; }


   const cv::Mat getUndistored(const cv::Mat image);
   // OTHERS
   /**
    * Function to call for calibration
    * @return     true if everything is ok
    */
   bool calibrate(void);

   bool calibrated(void) { return _calibration_flag; }

private:
   void cvMatToQString(QString& string, const cv::Mat& mat);

   std::vector<std::vector<cv::Point2f> > _points;

   ConfigDialog::Pattern _pattern_type;
   cv::Size              _pattern_size;
   float                 _pattern_dist;

   cv::Mat               _intrinsic;
   cv::Mat               _distortion;

   cv::Mat               _undistored;

   cv::Size              _image_size;

   unsigned int          _valid;

   bool                  _calibration_flag;
};

#endif /* SRC_INTRINSICCALIBRATION_H_ */
