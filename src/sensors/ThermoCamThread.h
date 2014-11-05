#ifndef __THERMO_CAM_THREAD__
#define __THERMO_CAM_THREAD__

#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QVector>
#include <QWaitCondition>

#include <opencv2/opencv.hpp>

#include <libirimager/ImageBuilder.h>
#include <libirimager/IRImager.h>


class ThermoCamThread : public QThread
{
    Q_OBJECT

public:
    ThermoCamThread(const char* configFile, QObject* parent = 0);
    ~ThermoCamThread(void);

    const cv::Mat* image(void) const { return &_image[_bank]; }
    const cv::Mat* temperature(void) const { return &_temperature[_bank]; }
    void switchBank(void);

public slots:
    void setAutoScale(const bool state);
    void setTemperatureRange(const float min, const float max);

protected:
    virtual void run(void);

private slots:
    void grab(void);

private:

    enum BufferBank {
        BankA = 0,
        BankB,
        CountBanks
    };

    void copyToImage(void);
    void switching(void);

    optris::IRImager*   _imager;
    unsigned char*      _bufferRaw;
    QTimer              _timer;
    QVector<cv::Mat>    _image;
    QVector<cv::Mat>    _temperature;
    QMutex              _mutex;
    BufferBank          _bank;
    QWaitCondition      _waitFor;
};

#endif
