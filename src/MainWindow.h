#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__

#include <QMainWindow>
#include <QTimer>
#include <QByteArray>
#include <QDebug>

// sensor includes
#include "sensors/ISensor.h"
#include "sensors/Openni.h"
#include "sensors/ThermoCam.h"
#include "sensors/RGBCamera.h"

#include "ConfigDialog.h"
#include "OpenCvWidget.h"

#include "IntrinsicCalibration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const char* configFile, QWidget* parent = 0);
    virtual ~MainWindow(void);

private slots:
    void tick(void);
    void calibrate(void);
    void saveToFile(void);
    void slot_calibrationSettings(void);

private:
    void cvMatToQString(QString& string, const cv::Mat& mat);

    Ui::MainWindow*                        _ui;
    OpenCvWidget                           _undistortView;
    QTimer                                 _timer;

    ISensor*                               _openni_sensor;
    ISensor*                               _thermo_sensor;
    ISensor*                               _rgb_sensor;

    IntrinsicCalibration                   _intrinsic_calibration;


    ConfigDialog*                          _dialog;
    cv::Size                               _imageSize;
    cv::Mat                                _intrinsic;
    cv::Mat                                _distortion;
    cv::Mat                                _depth;
};

#endif
