#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>

#include <pcl/common/time.h>



#include <iostream>

namespace {
const char* TEXT_LABEL_RESULT = "Intrinsic Matrix:\n"
                                "----------------------------\n";
}

MainWindow::MainWindow(const char* configFile, QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow),
      _thermo(configFile),
      _kinect(new pcl::OpenNIGrabber()),
      _dialog(new ConfigDialog(QString(QDir::homePath() + "/workspace/optris_intrinsic_calibration_tool/config/pattern.ini")))

{
    _ui->setupUi(this);
    _ui->_buttonCalibrate->setDisabled(true);

    this->connect(_ui->actionOptions,    SIGNAL(triggered()), this, SLOT(slot_calibrationSettings()));
    this->connect(&_timer,               SIGNAL(timeout()), this, SLOT(tick()));
    this->connect(_ui->_buttonCalibrate, SIGNAL(clicked()), this, SLOT(calibrate()));

    _timer.start(33);

    boost::function<void(const boost::shared_ptr<openni_wrapper::DepthImage>&)> f =
          boost::bind (&MainWindow::image_cb, this, _1);

    _kinect->registerCallback (f);
    _kinect->start();
}

MainWindow::~MainWindow(void)
{
   _kinect->stop();
}

void MainWindow::tick(void)
{
    _thermo.grab();

    cv::Mat image(_thermo.image());
    _imageSize = image.size();
    std::vector<cv::Point2f> centers;

    this->findPoints(centers, image);
    _ui->_thermoView->setMat(image);
    _ui->_depthView->setMat(_depth);

    if (!_intrinsic.empty() && !_distortion.empty()) {
        cv::Mat undistortedImage;
        cv::undistort(image, undistortedImage, _intrinsic, _distortion);
        _undistortView.setMat(undistortedImage);
    }

    if (!centers.size() || !_ui->_buttonCapture->isChecked()) return;

    _points.push_back(centers);
    _ui->_buttonCapture->setChecked(false);
    _ui->_buttonCalibrate->setEnabled(true);

    boost::this_thread::sleep (boost::posix_time::seconds (1));
}

void MainWindow::findPoints(std::vector<cv::Point2f>& centers, cv::Mat& image)
{
    const cv::Mat& temperature   = _thermo.temperature();
    const unsigned short tempMin = static_cast<unsigned short>(_dialog->threshold() * 10);

    cv::Mat tempImage(temperature.rows, temperature.cols, CV_8UC1);

    for (unsigned int row = 0; row < temperature.rows; row++)
    {
        const uint16_t* dataTemperature = reinterpret_cast<const uint16_t*>(temperature.ptr(row));
        unsigned char* dataTempImage = tempImage.ptr(row);

        for (unsigned int col = 0; col < temperature.cols; col++, dataTemperature++) {
            const unsigned short temp = *dataTemperature - 1000;

            if (temp < tempMin) *dataTempImage++ = 0xff;
            else                *dataTempImage++ = 0x00;
        }
    }

    _ui->_thresholdView->setMat(tempImage);

    const cv::Size patternSize(_dialog->getCols(), _dialog->getRows());

    if (cv::findCirclesGrid(tempImage, patternSize, centers, cv::CALIB_CB_SYMMETRIC_GRID))
        cv::drawChessboardCorners(image, patternSize, cv::Mat(centers), true);
    else
        centers.clear();
}

void MainWindow::calibrate(void)
{
    std::vector<std::vector<cv::Point3f> > coords(1);

    for (unsigned int row = 0; row < _dialog->getRows(); row++)
        for (unsigned int col = 0; col < _dialog->getCols(); col++)
            coords[0].push_back(cv::Point3f(static_cast<float>(row) * _dialog->getPointDistance(),
                                            static_cast<float>(col) * _dialog->getPointDistance(),
                                            0.0));

    coords.resize(_points.size(), coords[0]);
    cv::Mat intrinsic( 3, 3, CV_64F);
    cv::Mat distortion(1, 8, CV_64F);
    std::vector<cv::Mat> rvecs, tvecs;

    QString out(TEXT_LABEL_RESULT);
    QTextStream stream(&out);
    stream.setRealNumberPrecision(3);
    stream.setRealNumberNotation(QTextStream::FixedNotation);

    stream << "number of points   : " << _points.size() << "\n";
    stream << "rms error intrinsic: "
           << cv::calibrateCamera(coords, _points, _imageSize, intrinsic, distortion, rvecs, tvecs)
           << "\n\n";

    stream << "intrinsic:\n";
    this->cvMatToQString(out, intrinsic);
    stream << "\n";

    stream << "distortion:\n";
    this->cvMatToQString(out, distortion);

    _ui->_labelResult->setText(out);
    intrinsic.copyTo( _intrinsic);
    distortion.copyTo(_distortion);
}

void MainWindow::cvMatToQString(QString& string, const cv::Mat& mat)
{
    QTextStream stream(&string);
    stream.setFieldAlignment(QTextStream::AlignRight);
    stream.setRealNumberPrecision(3);
    stream.setRealNumberNotation(QTextStream::FixedNotation);

    for (unsigned int col = 0; col < mat.cols; col++) {
        for (unsigned int row = 0; row < mat.rows; row++)
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

void MainWindow::saveToFile(void)
{
    if (_intrinsic.empty() || _distortion.empty()) {
        qDebug() << __PRETTY_FUNCTION__ << ": calibration matrix is empty."; return;
    }
    cv::FileStorage fs("calibration.xml", cv::FileStorage::WRITE);
    fs << "intrinsic"  << _intrinsic;
    fs << "distortion" << _distortion;
}


void MainWindow::slot_calibrationSettings(void)
{
   _dialog->show();
}

