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
   bool capture(cv::Mat image1WithMarkers, cv::Mat image2WithMarkers);
   /**
    * Function to set type of calibration pattern
    * @param type
    * @param size
    */
   void setPattern(ConfigDialog::Pattern type, cv::Size size, const float dist);

   void addPoints(std::vector<cv::Point2f> p1,
                  std::vector<cv::Point2f> p2);

   // SETTERS
   /**
    * Function to set data of sensor 1
    * @param intrinsic
    * @param extrinsic
    */
   void setDataSensor1(const cv::Mat& intrinsic, const cv::Mat& distortion)
   {
      _intrinsic1  = intrinsic;
      _distortion1 = distortion;
   }
   /**
    * Function to set data of sensor 2
    * @param intrinsic
    * @param extrinsic
    */
   void setDataSensor2(const cv::Mat& intrinsic, const cv::Mat& distortion)
   {
      _intrinsic2  = intrinsic;
      _distortion2 = distortion;
   }

   // GETTERS
   /**
    * Function to return number of valid images for calibration
    * @return
    */
   const unsigned int& getNrOfValids(void) const { return _valid; }

   void setImage1(const cv::Mat image) { _image1 = image; }

   void setImage2(const cv::Mat image) { _image2 = image; }

   // OTHERS
   /**
    * Function to call for calibration
    * @return
    */
   bool calibrate(void);

   bool calibrated(void) { return _calibrated; }

   void undistore(const cv::Mat& image1, const cv::Mat& image2);

private:
   std::vector<std::vector<cv::Point2f> > _points1;         //!< found points for first sensor
   std::vector<std::vector<cv::Point2f> > _points2;         //!< found points for second sensor

   // members to describe pattern
   ConfigDialog::Pattern                  _pattern_type;    //!< type of pattern
   cv::Size                               _pattern_size;    //!< size in x and y of pattern
   float                                  _pattern_dist;    //!< distance for the pattern

   cv::Mat  _image1;
   cv::Mat  _image2;

   cv::Mat                                _intrinsic1;      //!< intrinsic matrix for sensor 1
   cv::Mat                                _intrinsic2;      //!< intrinsic matrix for sensor 2

   cv::Mat                                _distortion1;     //!< distortion parameter for sensor 1
   cv::Mat                                _distortion2;     //!< distortion parameter for sensor 1

   cv::Size                               _image_size;      //!< size of the image from sensor 1

   cv::Mat                                _R;               //!< estimated rotation matrix between the two sensors
   cv::Mat                                _r;               //!< rotation vector
   cv::Mat                                _t;               //!< estimated transformation matrix between the two sensors

   unsigned int                           _valid;           //!< number of valid frames for calibration
   bool                                   _calibrated;
};

#endif /* SRC_EXTRINSICCALIBRATION_H_ */
