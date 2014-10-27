/*
 * Openni.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#include <sensors/Openni.h>

Openni::Openni(void)
:  _kinect(new pcl::OpenNIGrabber()),
   _th(1.0)
{

   boost::function<void(const boost::shared_ptr<openni_wrapper::DepthImage>&)> f =
         boost::bind (&Openni::depth_cb, this, _1);

   boost::function<void(const boost::shared_ptr<openni_wrapper::Image>&)> g =
         boost::bind (&Openni::image_cb, this, _1);

   _kinect->registerCallback(f);
   _kinect->registerCallback(g);
   _kinect->start();
}

Openni::~Openni(void)
{
   _kinect->stop();
}

void Openni::grab(void)
{
   cv::threshold(_depth, _bin, 10, 255, cv::THRESH_BINARY);
}


// --> PIVATE

void Openni::depth_cb (const boost::shared_ptr<openni_wrapper::DepthImage>& img)
{
  float* buffer = new float[img->getHeight() * img->getWidth()];

  img->fillDepthImage(img->getWidth(), img->getHeight(), buffer);
  cv::Mat map=cv::Mat(img->getHeight(),img->getWidth(), CV_32FC1, buffer);

  this->depthToCV8UC1(map, _depth);

  delete buffer;
}

void Openni::image_cb (const boost::shared_ptr<openni_wrapper::Image>& img)
{

}


void Openni::depthToCV8UC1(const cv::Mat& float_img, cv::Mat& mono8_img)
{
   if(mono8_img.rows != float_img.rows || mono8_img.cols != float_img.cols)
   {
      mono8_img = cv::Mat(float_img.size(), CV_8UC1);
   }

   //The following doesn't work if there are NaNs
   double minVal, maxVal;
   minMaxLoc(float_img, &minVal, &maxVal);
   cv::convertScaleAbs(float_img, mono8_img, 100, 0.0);
}
