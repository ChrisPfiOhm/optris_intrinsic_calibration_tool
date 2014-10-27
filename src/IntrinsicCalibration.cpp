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
:  _pattern_type(ConfigDialog::SymCircles),
   _valid(0),
   _pattern_dist(0.06),
   _calibration_flag(false)
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

   if (cv::findCirclesGrid(binaryImage, _pattern_size, centers, (cv::CALIB_CB_SYMMETRIC_GRID) |
                                                                 cv::CALIB_CB_ADAPTIVE_THRESH |
                                                                 cv::CALIB_CB_FAST_CHECK))
   {
       cv::drawChessboardCorners(colorImage, _pattern_size, cv::Mat(centers), true);
   }
   else
   {
       centers.clear();
   }

   // push back points for calibration
   if(centers.size() > 0) {
      _points.push_back(centers);
      qDebug() << _valid++;
      return true;
   }
   else {
      return false;
   }
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


   _pattern_dist = 0.06;


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

    for (int col = 0; col < mat.cols; col++) {
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
