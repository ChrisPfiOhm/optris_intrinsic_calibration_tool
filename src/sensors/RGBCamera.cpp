/*
 * RGBCamera.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#include <sensors/RGBCamera.h>

#include "opencv2/highgui/highgui.hpp"

RGBCamera::RGBCamera(const unsigned int id)
:  _camera(new cv::VideoCapture(id))
{

}

RGBCamera::~RGBCamera()
{
   // nothing to do
}


void RGBCamera::grab(void)
{
   if (!_camera->isOpened()){
      std::cout  << "Cannot open the video file" << std::endl;
      return;
   }

   _camera->read(_image);

   cv::Mat viewGray;
   cvtColor(     _image, _bin, cv::COLOR_BGR2GRAY);
//   cv::threshold(_bin,   _bin, 120, 255, cv::THRESH_BINARY);

}
