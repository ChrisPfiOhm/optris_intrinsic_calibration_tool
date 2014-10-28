/*
 * ExtrinsicCalibration.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#include <ExtrinsicCalibration.h>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <QDebug>

ExtrinsicCalibration::ExtrinsicCalibration(void)
:  _valid(0),
   _pattern_dist(0.06),
   _pattern_type(ConfigDialog::SymCircles)
{

}

ExtrinsicCalibration::~ExtrinsicCalibration(void)
{

}


bool ExtrinsicCalibration::setImages(cv::Mat image1Bin, cv::Mat image2Bin)
{
   std::vector<cv::Point2f> centers1;
   std::vector<cv::Point2f> centers2;

   _image_size = image1Bin.size();


   /*
    * Find circles for first image
    */
   if (cv::findCirclesGrid(image1Bin, _pattern_size, centers1, (cv::CALIB_CB_SYMMETRIC_GRID) |
                                                                cv::CALIB_CB_ADAPTIVE_THRESH |
                                                                cv::CALIB_CB_FAST_CHECK))
   {
       cv::drawChessboardCorners(image1Bin, _pattern_size, cv::Mat(centers1), true);
   }
   else {
       centers1.clear();
   }

   /*
    * Find circles for second image
    */
   if (cv::findCirclesGrid(image2Bin, _pattern_size, centers2, (cv::CALIB_CB_SYMMETRIC_GRID) |
                                                                cv::CALIB_CB_ADAPTIVE_THRESH |
                                                                cv::CALIB_CB_FAST_CHECK))
   {
       cv::drawChessboardCorners(image2Bin, _pattern_size, cv::Mat(centers2), true);
   }
   else {
       centers2.clear();
   }

   // push back points for calibration
   if((centers1.size() > 0) && (centers2.size() >0)) {
      _points1.push_back(centers1);
      _points2.push_back(centers2);
      qDebug() << _valid++;
      return true;
   }
   else {
      return false;
   }
}

void ExtrinsicCalibration::setPattern(ConfigDialog::Pattern type, cv::Size size, float dist)
{
   _pattern_type = type;
   _pattern_size = size;
   _pattern_dist = dist;
}


bool ExtrinsicCalibration::calibrate(void)
{
   std::vector<std::vector<cv::Point3f> > coords(1);

   _pattern_dist = 0.06;

   qDebug() << "h1";

   for (    int row = 0; row < _pattern_size.height; row++) {
       for (int col = 0; col < _pattern_size.width;  col++)
       {
          coords[0].push_back(cv::Point3f(static_cast<float>(row)  * _pattern_dist,
                                           static_cast<float>(col) * _pattern_dist,
                                           0.0));
       }
   }

   qDebug() << "h2";

   coords.resize(_points1.size(), coords[0]);

   cv::Mat E, F;
   double rms = cv::stereoCalibrate(coords[0], _points1[0], _points2[0],
                   _intrinsic1, _distortion1,
                   _intrinsic2, _distortion2,
                   _image_size,
                   _R, _T,
                   E, F,
                   cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 1e-5));

   qDebug() << "h3";
//                   TermCriteria(cv::CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5),
//                   CV_CALIB_FIX_ASPECT_RATIO +
//                   //CV_CALIB_ZERO_TANGENT_DIST +
//                   CV_CALIB_SAME_FOCAL_LENGTH +
//                   CV_CALIB_RATIONAL_MODEL +
//                   //CV_CALIB_FIX_K3);
//                   //CV_CALIB_FIX_K2);
//                   CV_CALIB_FIX_K3 + CV_CALIB_FIX_K4 + CV_CALIB_FIX_K5);
                   //CV_CALIB_FIX_K1 + CV_CALIB_FIX_K2 + CV_CALIB_FIX_K3 + CV_CALIB_FIX_K4 + CV_CALIB_FIX_K5);
       std::cout << "done with RMS error=" << rms << std::endl;

    return true;
}
