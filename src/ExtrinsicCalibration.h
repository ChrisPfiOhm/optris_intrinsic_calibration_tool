/*
 * ExtrinsicCalibration.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_EXTRINSICCALIBRATION_H_
#define SRC_EXTRINSICCALIBRATION_H_

#include <opencv2/core/core.hpp>

#include <ConfigDialog.h>

#include <QString>

/**
 * @class   ExtrinsicCalibration
 * @author  Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   OpenCV wrapper for stereo calibration of two cameras
 */
class ExtrinsicCalibration {
public:
   /**
    * Default constructor
    */
   ExtrinsicCalibration(void);
   /**
    * Default destructor
    */
   virtual ~ExtrinsicCalibration(void);

   /**
    * Function to set images
    * @param image1
    * @param image2
    */
   bool setImages(cv::Mat image1, cv::Mat image2);
   /**
    * Function to set type of calibration pattern
    * @param type
    * @param size
    */
   void setPattern(ConfigDialog::Pattern type, cv::Size size, const float dist);

   // SETTERS
   /**
    * Function to set data of sensor 1
    * @param intrinsic
    * @param extrinsic
    */
   void setDataSensor1(const cv::Mat intrinsic, const cv::Mat distortion);
   /**
    * Function to set data of sensor 2
    * @param intrinsic
    * @param extrinsic
    */
   void setDataSensor2(const cv::Mat intrinsic, const cv::Mat distortion);

   // GETTERS
   /**
    * Function to return number of valid images for calibration
    * @return
    */
   const unsigned int& getNrOfValids(void) const { return _valid; }

   // OTHERS
   bool calibrate(void);

private:
   std::vector<std::vector<cv::Point2f> > _points1;
   std::vector<std::vector<cv::Point2f> > _points2;



   ConfigDialog::Pattern _pattern_type;
   cv::Size              _pattern_size;
   float                 _pattern_dist;

   cv::Mat _intrinsic1;
   cv::Mat _distortion1;
   cv::Mat _intrinsic2;
   cv::Mat _distortion2;


   cv::Size _image_size;

   cv::Mat _R;
   cv::Mat _T;

   unsigned int          _valid;


};

#endif /* SRC_EXTRINSICCALIBRATION_H_ */
