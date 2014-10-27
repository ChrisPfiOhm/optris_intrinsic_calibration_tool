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
   /**
    * Abstract method to get calibration image
    * @return
    */
   virtual const cv::Mat& getCalibrationImage(void) = 0;

   virtual const cv::Mat& getVisualizationImage(void) = 0;
private:

};




#endif /* SRC_ISENSOR_H_ */
