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
   _pattern_size(cv::Size(9, 6)),
   _pattern_dist(0.0375),
   _valid(0),
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

   this->findPattern(binaryImage, colorImage, centers);

   if(_capture) {
      _capture = false;
      // push back points for calibration
      if(centers.size() == 9*6) {
         _points.push_back(centers);
         qDebug() << _valid++;
         return true;
      }
   }
   return false;
}


void IntrinsicCalibration::setPattern(ConfigDialog::Pattern type, cv::Size size, float dist)
{
   _pattern_type     = type;
   _pattern_size     = size;
   _pattern_dist     = dist;
}


void IntrinsicCalibration::setCalibration(const cv::Mat& intrinsic, const cv::Mat& distortion)
{
   _intrinsic        = intrinsic;
   _distortion       = distortion;
   _calibration_flag = true;
}


void IntrinsicCalibration::setImages(std::vector<cv::Mat> images)
{
   for(unsigned int i=0 ; i<images.size() ; i++)
   {

   }
}



bool IntrinsicCalibration::slot_calibrate(void)
{

   if(!_points.size() > 0) {
      qDebug() << "not enough images";
      return false;
   }


   std::vector<std::vector<cv::Point3f> > coords(1);
   for (    int row = 0; row < _pattern_size.height; row++) {
       for (int col = 0; col < _pattern_size.width;  col++)
       {
           coords[0].push_back(cv::Point3f(static_cast<float>(row) * _pattern_dist,
                                           static_cast<float>(col) * _pattern_dist,
                                           0.0));
       }
   }

   coords.resize(_points.size(), coords[0]);
   cv::Mat intrinsic( 3, 3, CV_64F);
   cv::Mat distortion(1, 8, CV_64F);

   std::vector<cv::Mat>  rvecs;
   std::vector<cv::Mat>  tvecs;

   qDebug() << "----------------------------------------";
   qDebug() << "number of frames   : " << _points.size();
   qDebug() << "rms error intrinsic: " << cv::calibrateCamera(coords, _points, _image_size, intrinsic, distortion, rvecs, tvecs);

//    this->cvMatToQString(out, intrinsic);

   intrinsic.copyTo( _intrinsic);
   distortion.copyTo(_distortion);

   _calibration_flag = true;

   std::cout << _intrinsic  << std::endl;
   std::cout << _distortion << std::endl;

   this->saveToFile();

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

bool IntrinsicCalibration::findPattern(cv::Mat& image, cv::Mat& viz_image, std::vector<cv::Point2f>& centers)
{
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


   if (cv::findCirclesGrid(image, _pattern_size, centers,
      (cv::CALIB_CB_SYMMETRIC_GRID | cv::CALIB_CB_ADAPTIVE_THRESH), _blob_detector))
   {
       cv::drawChessboardCorners(viz_image, _pattern_size, cv::Mat(centers), true);

       if(_calibration_flag == true)
       {
          std::vector<cv::Point2d> imagePoints, imageFramePoints, imageOrigin;
          std::vector<cv::Point3d> framePoints;

          //generate points in the reference frame
          framePoints.push_back( cv::Point3d( 0.0, 0.0, 0.0 ) );
          framePoints.push_back( cv::Point3d( 5.0, 0.0, 0.0 ) );
          framePoints.push_back( cv::Point3d( 0.0, 5.0, 0.0 ) );
          framePoints.push_back( cv::Point3d( 0.0, 0.0, 5.0 ) );

          std::vector<cv::Point3d> boardPoints;

          //generate vectors for the points on the chessboard
          for (int i=0; i<6; i++) {
             for (int j=0; j<9; j++) {
                boardPoints.push_back( cv::Point3d( double(i), double(j), 0.0) );
             }
          }

          cv::Mat rvec = cv::Mat(cv::Size(3,1), CV_64F);
          cv::Mat tvec = cv::Mat(cv::Size(3,1), CV_64F);

          cv::solvePnP( cv::Mat(boardPoints), centers,  _intrinsic, _distortion, rvec, tvec, false );
          cv::projectPoints(framePoints, rvec, tvec,    _intrinsic, _distortion, imageFramePoints );

//          std::cout << "rvec: " << rvec << std::endl;
//          std::cout << "tvec: " << tvec*_pattern_dist << std::endl;

          _rvec = rvec;
          _tvec = tvec*_pattern_dist;

          // draw markers in image
          const unsigned int thickness = 6;
          cv::line(viz_image, imageFramePoints[0], imageFramePoints[1], CV_RGB(255,0,0), thickness );
          cv::line(viz_image, imageFramePoints[0], imageFramePoints[2], CV_RGB(0,255,0), thickness );
          cv::line(viz_image, imageFramePoints[0], imageFramePoints[3], CV_RGB(0,0,255), thickness );
       }
       return true;
   }
   return false;

}

void IntrinsicCalibration::saveToFile(void)
{
   if (_intrinsic.empty() || _distortion.empty()) {
       qDebug() << __PRETTY_FUNCTION__ << ": calibration matrix is empty."; return;
   }
   cv::FileStorage fs("/tmp/calibration.xml", cv::FileStorage::WRITE);
   fs << "intrinsic"  << _intrinsic;
   fs << "distortion" << _distortion;
}


void IntrinsicCalibration::slot_capture(void)
{
   qDebug() << __PRETTY_FUNCTION__;
   _capture = true;
}

void IntrinsicCalibration::slot_reset(void)
{
   _points.clear();
}


