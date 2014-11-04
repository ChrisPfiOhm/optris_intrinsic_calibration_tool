/*
 * Openni.h
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#ifndef SRC_SENSORS_OPENNI_H_
#define SRC_SENSORS_OPENNI_H_

#include "ISensor.h"

#include <pcl-1.7/pcl/point_cloud.h>
#include <pcl-1.7/pcl/point_types.h>
#include <pcl-1.7/pcl/io/openni_grabber.h>
#include <pcl-1.7/pcl/common/time.h>

/**
 * @class   Openni
 * @author  Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Wrapper class for openni implementation from pcl to sensor interface
 *          for extrinsic and intrinsic calibration
 */
class Openni : public ISensor
{
public:
   /**
    * Default constructor
    */
   Openni(void);
   /**
    * Default destructor
    */
   virtual ~Openni(void);


   // GETTERS
   /**
    * Function to get calibration image. Implementation from pure virtual method.
    */
   virtual const cv::Mat& getCalibrationImage(void)   { return _bin; }
   /**
    * Function to return image for visualization
    * @return
    */
   virtual const cv::Mat& getVisualizationImage(void) { return _depth; }
   /**
    * Function to return depth image as cv mat
    * @return
    */
   const cv::Mat& getDepth(void) { return _depth; }
   /**
    * Function to return color image
    * @return
    */
   const cv::Mat& getImage(void) { return _color; }


   // SETTERS
   void setThresholdBinaryDepthImage(float th) { _th = th; }

   // OTHERS
   /**
    * Implementation of pure virtual method from ISensor interface
    */
   virtual void grab(void);


private:
   void depth_cb (const boost::shared_ptr<openni_wrapper::DepthImage>& img);

   void image_cb (const boost::shared_ptr<openni_wrapper::Image>& img);

   void ir_image_cb(const boost::shared_ptr<openni_wrapper::IRImage>& img);

   cv::Mat generateBin(const cv::Mat depth);

   void depthToCV8UC1(const cv::Mat& float_img, cv::Mat& mono8_img);

   pcl::OpenNIGrabber*                    _kinect;


   cv::Mat  _bin;
   cv::Mat  _depth;
   cv::Mat  _color;
   cv::Mat  _ir;

   float    _th;
};

#endif /* SRC_SENSORS_OPENNI_H_ */
