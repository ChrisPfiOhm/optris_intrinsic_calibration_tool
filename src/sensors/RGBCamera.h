/*
 * RGBCamera.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_SENSORS_RGBCAMERA_H_
#define SRC_SENSORS_RGBCAMERA_H_

#include "ISensor.h"

/**
 * @class   RGBCamera
 * @author  Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Wrapper for opencv camera grabber
 */
class RGBCamera : public ISensor
{
public:
   /**
    * Default constructor
    */
   RGBCamera(const unsigned int id=0);
   /**
    * Default destructor
    */
   virtual ~RGBCamera(void);

   // GETTERS
   /**
    * Function to implement pure virtual method from interface to return binary image
    * @return
    */
   virtual const cv::Mat& getCalibrationImage(void)     { return _bin; }
   /**
    * Function to implement pure virtual method from interface to return visualization
    * @return
    */
   virtual const cv::Mat& getVisualizationImage(void)   { return _image; }

   // OTHERS
   /**
    * Function to grab image from device
    */
   virtual void grab(void);


private:
   cv::VideoCapture*        _camera;      //!< camera grabber

   cv::Mat                  _image;       //!< normal color image
   cv::Mat                  _bin;         //!< greyscale image

};
#endif /* SRC_SENSORS_RGBCAMERA_H_ */
