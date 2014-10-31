/*
 * ISensor.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_ISENSOR_H_
#define SRC_ISENSOR_H_


#include <opencv2/opencv.hpp>

/**
 * @class   ISensor
 * @author  Christian Pfitzner
 * @date    2014-10-27
 */
class ISensor
{
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
   //! @todo implement load configuration for intrinsic and extrinsic parameters
//   void loadConfig(QString path) = 0;
   //! @todo implement save configuration for intrinsic and extrinsic parameters
//   void saveConfig(QString path) = 0;

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

   virtual const cv::Mat& getIntrinsic(void)  const  { return _intrinsic;  }
   virtual const cv::Mat& getDistortion(void) const  { return _distortion; }

   // SETTERS
   virtual void setIntrinsic(cv::Mat& intrinsic)   { _intrinsic = intrinsic; }
   virtual void setDistortion(cv::Mat& distortion) { _distortion = distortion; }

private:
   cv::Mat _intrinsic;
   cv::Mat _distortion;
};




#endif /* SRC_ISENSOR_H_ */
