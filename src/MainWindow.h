#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__

#include <QMainWindow>
#include <QTimer>
#include <QByteArray>
#include <QDebug>

// pcl includes
#include <pcl-1.7/pcl/point_cloud.h>
#include <pcl-1.7/pcl/point_types.h>
#include <pcl-1.7/pcl/io/openni_grabber.h>
#include <pcl-1.7/pcl/common/time.h>
#include <pcl/visualization/cloud_viewer.h>



#include "ThermoCam.h"
#include "ConfigDialog.h"
#include "OpenCvWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const char* configFile, QWidget* parent = 0);
    virtual ~MainWindow(void);

    void image_cb (const boost::shared_ptr<openni_wrapper::DepthImage>& img)    {
      float* buffer = new float[img->getHeight() * img->getWidth()];

      img->fillDepthImage(img->getWidth(),img->getHeight(), buffer);
      cv::Mat map=cv::Mat(img->getHeight(),img->getWidth(), CV_32FC1, buffer);

      this->depthToCV8UC1(map, _depth);
      delete buffer;
   }

private slots:
    void tick(void);
    void calibrate(void);
    void saveToFile(void);

    void slot_calibrationSettings(void);

    void depthToCV8UC1(const cv::Mat& float_img, cv::Mat& mono8_img)
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


private:
    void findPoints(std::vector<cv::Point2f>& centers, cv::Mat& image);
    void cvMatToQString(QString& string, const cv::Mat& mat);

    Ui::MainWindow*                        _ui;
    OpenCvWidget                           _undistortView;
    QTimer                                 _timer;
    ThermoCam                              _thermo;
    pcl::OpenNIGrabber*                    _kinect;


    ConfigDialog*                          _dialog;
    std::vector<std::vector<cv::Point2f> > _points;
    cv::Size                               _imageSize;
    cv::Mat                                _intrinsic;
    cv::Mat                                _distortion;
    cv::Mat                                _depth;
};

#endif
