#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__

#include <QMainWindow>
#include <QTimer>
#include <QByteArray>

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

private slots:
    void tick(void);
    void calibrate(void);
    void saveToFile(void);

    void slot_calibrationSettings(void);

private:
    void findPoints(std::vector<cv::Point2f>& centers, cv::Mat& image);
    void cvMatToQString(QString& string, const cv::Mat& mat);

    Ui::MainWindow*                        _ui;
    OpenCvWidget                           _undistortView;
    QTimer                                 _timer;
    ThermoCam                              _thermo;
    ConfigDialog*                          _dialog;
    std::vector<std::vector<cv::Point2f> > _points;
    cv::Size                               _imageSize;
    cv::Mat                                _intrinsic;
    cv::Mat                                _distortion;
};

#endif
