/*
 * RGBCamera.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_SENSORS_RGBCAMERA_H_
#define SRC_SENSORS_RGBCAMERA_H_

#include "ISensor.h"

class RGBCamera : public ISensor
{
public:
   /**
    * Default constructor
    */
   RGBCamera(void);
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
   virtual void grab(void);


private:
   cv::VideoCapture*        _camera;

   cv::Mat    _image;
   cv::Mat    _bin;

};
#endif /* SRC_SENSORS_RGBCAMERA_H_ */
