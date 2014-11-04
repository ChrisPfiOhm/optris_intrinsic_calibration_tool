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
   _pattern_dist(0.075),
   _pattern_type(ConfigDialog::SymCircles),
   _pattern_size(9, 6)
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

   // set up the parameters (check the defaults in opencv's code in blobdetector.cpp)
   cv::SimpleBlobDetector::Params params;
   params.minDistBetweenBlobs = 5.0f;
   params.filterByInertia     = true;
   params.filterByConvexity   = false;
   params.filterByColor       = true;
   params.filterByCircularity = false;
   params.filterByArea        = true;
   params.minArea             = 30.0f;
   params.maxArea             = 3000.0f;
   params.maxInertiaRatio     = 30.0f;

   cv::Ptr<cv::FeatureDetector> _blob_detector = new cv::SimpleBlobDetector(params);
   _blob_detector->create("SimpleBlob");

   /*
    * Find circles for first image
    */
   if (cv::findCirclesGrid(image1Bin, _pattern_size, centers1,
      (cv::CALIB_CB_SYMMETRIC_GRID) | cv::CALIB_CB_ADAPTIVE_THRESH), _blob_detector){
       cv::drawChessboardCorners(image1Bin, _pattern_size, cv::Mat(centers1), true);
   }
   else{
       centers1.clear();
   }

   /*
    * Find circles for second image
    */
   if (cv::findCirclesGrid(image2Bin, _pattern_size, centers2,
      (cv::CALIB_CB_SYMMETRIC_GRID) | cv::CALIB_CB_ADAPTIVE_THRESH), _blob_detector) {
       cv::drawChessboardCorners(image2Bin, _pattern_size, cv::Mat(centers2), true);
   }
   else {
       centers2.clear();
   }

   // push back points for calibration
   if((centers1.size() > 0) && (centers2.size() >0))
   {
      if(centers1.size() != centers2.size()) {
//         qDebug() << "[" << __PRETTY_FUNCTION__ << "]: different size in blob detection. ";
//         qDebug() << "[" << __PRETTY_FUNCTION__ << "]: Size 1: " << centers1.size() <<
//                                                     " Size2:  " << centers2.size();
         return false;
      }

      if(centers1.size() != _pattern_size.width*_pattern_size.height) {
//         qDebug() << "[" << __PRETTY_FUNCTION__ << "]: wrong size in blob detection. ";
         return false;
      }

      qDebug() << "[" << __PRETTY_FUNCTION__ << "]: Captured " << ++_valid  << " frames";


      _points1.push_back(centers1);
      _points2.push_back(centers2);

      return true;
   }

   return false;
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

   _pattern_dist = 0.075;

   // generate coordinates from pattern
   for (    int row = 0; row < _pattern_size.height; row++) {
       for (int col = 0; col < _pattern_size.width;  col++)
       {
          coords[0].push_back(cv::Point3f(static_cast<float>(row)  * _pattern_dist,
                                           static_cast<float>(col) * _pattern_dist,
                                           0.0));
       }
   }

   coords.resize(_points2.size(), coords[0]);

//   std::cout << _points1.size()     << std::endl;
//   std::cout << _points2.size()     << std::endl;
//   std::cout << coords.size()       << std::endl;

   cv::Mat E, F, R, T;

   cv::Mat cameraMatrix[2], distCoeffs[2];
   cameraMatrix[0] = cv::Mat::eye( 3, 3, CV_64F );
   cameraMatrix[1] = cv::Mat::eye( 3, 3, CV_64F );

   std::cout << _intrinsic1  << std::endl;
   std::cout << _distortion2 << std::endl;
   std::cout << _intrinsic2  << std::endl;
   std::cout << _distortion2 << std::endl;

   double rms = cv::stereoCalibrate( coords,
                                     _points1, _points2,
                                     cameraMatrix[0], distCoeffs[0],
                                     cameraMatrix[1], distCoeffs[1],
                                     _image_size, R, T, E, F,
                                     cv::TermCriteria(
                                         CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
                                         300, 1e-5),
                                     CV_CALIB_FIX_ASPECT_RATIO +
//                                     CV_CALIB_ZERO_TANGENT_DIST +
//                                     CV_CALIB_FIX_INTRINSIC +
                                     CV_CALIB_RATIONAL_MODEL +
                                     CV_CALIB_FIX_K3 +
                                     CV_CALIB_FIX_K4 +
                                     CV_CALIB_FIX_K5 );

    std::cout << "done with RMS error=" << rms             << std::endl;
    std::cout << "Translation T: "      << T               << std::endl;
    std::cout << "Rotation R:    "      << R               << std::endl;
//    std::cout << "E:             "      << E               << std::endl;
//    std::cout << "F:             "      << F               << std::endl;
    std::cout << "Intrinsic 1    "      << cameraMatrix[0] << std::endl;
    std::cout << "Intrinsic 2    "      << cameraMatrix[1] << std::endl;


    return true;
}
