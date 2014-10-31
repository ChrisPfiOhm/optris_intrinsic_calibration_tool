/*
 * IntrinsicCalibration.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */

#include <IntrinsicCalibration.h>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>



#include <QDebug>
#include <QTextStream>


IntrinsicCalibration::IntrinsicCalibration(void)
:  QObject(0),
   _pattern_type(ConfigDialog::SymCircles),
   _valid(0),
   _pattern_dist(0.075),
   _calibration_flag(false),
   _capture(false)
{

}

IntrinsicCalibration::~IntrinsicCalibration(void)
{
   // nothing to do here
}


bool IntrinsicCalibration::setImage(cv::Mat binaryImage, cv::Mat colorImage)
{
   std::vector<cv::Point2f> centers;
   _image_size = binaryImage.size();


   // set up the parameters (check the defaults in opencv's code in blobdetector.cpp)
   cv::SimpleBlobDetector::Params params;
   params.minDistBetweenBlobs = 2.0f;
   params.filterByInertia     = true;
   params.filterByConvexity   = false;
   params.filterByColor       = true;
   params.filterByCircularity = false;
   params.filterByArea        = true;
   params.minArea             = 5.0f;
   params.maxArea             = 10000.0f;

   cv::Ptr<cv::FeatureDetector> _blob_detector = new cv::SimpleBlobDetector(params);
   _blob_detector->create("SimpleBlob");


   if (cv::findCirclesGrid(binaryImage, _pattern_size, centers, (cv::CALIB_CB_SYMMETRIC_GRID |
                                                                 cv::CALIB_CB_ADAPTIVE_THRESH),
                                                                 _blob_detector)){
       cv::drawChessboardCorners(colorImage, _pattern_size, cv::Mat(centers), true);
   }
   else {
       centers.clear();
   }

   if(_capture)
   {
      _capture = false;
      // push back points for calibration
      if(centers.size() > 0) {
         _points.push_back(centers);
         qDebug() << _valid++;
         return true;
      }
   }
   return false;
}


void IntrinsicCalibration::setPattern(ConfigDialog::Pattern type, cv::Size size, float dist)
{
   _pattern_type = type;
   _pattern_size = size;
   _pattern_dist = dist;
}



bool IntrinsicCalibration::calibrate(void)
{
   std::vector<std::vector<cv::Point3f> > coords(1);

   _pattern_dist = 0.075;


   for (    int row = 0; row < _pattern_size.height; row++)
       for (int col = 0; col < _pattern_size.width;  col++)
           coords[0].push_back(cv::Point3f(static_cast<float>(row) * _pattern_dist,
                                           static_cast<float>(col) * _pattern_dist,
                                           0.0));

   coords.resize(_points.size(), coords[0]);
   cv::Mat intrinsic( 3, 3, CV_64F);
   cv::Mat distortion(1, 8, CV_64F);
   std::vector<cv::Mat> rvecs, tvecs;

   QString out("-----------------");
   qDebug() << "number of points   : " << _points.size() << "\n";
   qDebug() << "rms error intrinsic: "
          << cv::calibrateCamera(coords, _points, _image_size, intrinsic, distortion, rvecs, tvecs);

    this->cvMatToQString(out, intrinsic);
    qDebug() << out;

   intrinsic.copyTo( _intrinsic);
   distortion.copyTo(_distortion);
   _calibration_flag = true;
   return true;
}


const cv::Mat IntrinsicCalibration::getUndistored(const cv::Mat image)
{
     cv::Mat undistortedImage;
     cv::undistort(image, undistortedImage, _intrinsic, _distortion);
     return undistortedImage;
}


void IntrinsicCalibration::cvMatToQString(QString& string, const cv::Mat& mat)
{
    QTextStream stream(&string);
    stream.setFieldAlignment(QTextStream::AlignRight);
    stream.setRealNumberPrecision(3);
    stream.setRealNumberNotation(QTextStream::FixedNotation);

    for (    int col = 0; col < mat.cols; col++) {
        for (int row = 0; row < mat.rows; row++)
        {
            stream.setFieldWidth(8);

            switch (mat.type())
            {
            case CV_64F:
                stream << mat.at<double>(row, col);
                break;

            default:
                break;
            }
            stream.setFieldWidth(0);
            stream << " ";
        }
        stream << "\n";
    }
}

void IntrinsicCalibration::saveToFile(void)
{
   if (_intrinsic.empty() || _distortion.empty()) {
       qDebug() << __PRETTY_FUNCTION__ << ": calibration matrix is empty."; return;
   }
   cv::FileStorage fs("calibration.xml", cv::FileStorage::WRITE);
   fs << "intrinsic"  << _intrinsic;
   fs << "distortion" << _distortion;
}


void IntrinsicCalibration::slot_capture(void)
{
   _capture = true;
}


