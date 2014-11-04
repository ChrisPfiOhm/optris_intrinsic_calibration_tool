/*
 * IntrinsicCalibration.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_INTRINSICCALIBRATION_H_
#define SRC_INTRINSICCALIBRATION_H_

// opencv includes
#include <opencv2/core/core.hpp>

// cali includes
#include <ConfigDialog.h>

// qt includes
#include <QString>
#include <QObject>

/**
 * @class   IntrinsicCalibration
 * @author  Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Wrapper class for opencvs intrinsic calibration
 */
class IntrinsicCalibration : public QObject
{
   Q_OBJECT
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
   /**
    * Function to set intrinsic
    * @param intrinsic
    */
   void setCalibration(const cv::Mat& intrinsic, const cv::Mat& distortion);


   // GETTERS
   /**
    * Function to return intrinsic calibration matrix
    * @return  intrinsic matrix
    */
   cv::Mat getIntrinsic(void) const              { return _intrinsic;  }
   /**
    * Function to get distrotion of camera
    * @return
    */
   cv::Mat getDistortion(void) const             { return _distortion; }
   /**
    * Function to return number of valid images for calibration
    * @return
    */
   const unsigned int& getNrOfValids(void) const { return _valid; }

   /**
    * Function to get undistored image
    */
   const cv::Mat getUndistored(const cv::Mat image);


   // OTHERS
   /**
    * Function to return true if image is calibrated
    */
   bool calibrated(void) { return _calibration_flag; }

   /**
    * Function to save calibration to file
    */
   void saveToFile(void);

public slots:
   /**
    * Function to call for calibration
    * @return     true if everything is ok
    */
   bool slot_calibrate(void);
   /**
    * Slot to capture frame
    */
   void slot_capture(void);

private:
   /**
    * Function to convert opencv matrix to string
    * @param string
    * @param mat
    */
   void cvMatToQString(QString& string, const cv::Mat& mat);

   std::vector<std::vector<cv::Point2f> > _points;                //!< container for all found valid blobs

   // Settings for pattern
   ConfigDialog::Pattern _pattern_type;            //!< type of pattern
   cv::Size              _pattern_size;            //!< size of pattern n x m
   float                 _pattern_dist;            //!< distance between two markers

   cv::Mat               _intrinsic;               //!< matrix with intrinsic coefficients
   cv::Mat               _distortion;              //!< matrix with distortion coefficients

   cv::Mat               _undistored;              //!< undistored image

   cv::Size              _image_size;              //!< size of image

   unsigned int          _valid;                   //!< numbers of valid images taken for calibration
   bool                  _calibration_flag;        //!< true if image is already calibrated
   bool                  _capture;                 //!< true if image should be captured for calibration
};

#endif /* SRC_INTRINSICCALIBRATION_H_ */
