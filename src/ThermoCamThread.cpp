#include "ThermoCamThread.h"

#include "Imager.h"
#include "ImageBuilder.h"

#include <QByteArray>
#include <QDebug>

#include <cstring>

namespace {
unsigned char*        _bufferShow = NULL;
unsigned short*       _bufferT    = NULL;
optris::ImageBuilder* _iBuilder   = NULL;

void callbackImager(unsigned short* image, unsigned int w, unsigned int h)
{
   if(!_bufferShow) _bufferShow = new unsigned char[w*h* 3];

   _iBuilder->setData(w, h, image);
   _iBuilder->convertTemperatureToPaletteImage(_bufferShow, true);
   std::memcpy(_bufferT, image, sizeof(unsigned short) * w * h);
}
}

ThermoCamThread::ThermoCamThread(const char* configFile, QObject* parent)
    : QThread(parent),
      _imager(new optris::PIImager(configFile)),
      _bufferRaw(0),
      _image(CountBanks),
      _temperature(CountBanks),
      _bank(BankA)
{

    if(!_imager->startStreaming()) {
       qDebug() << "Stream not ready"; exit(1);
    }

    delete    _iBuilder;
    delete [] _bufferT;
    delete [] _bufferShow;


    _iBuilder = new optris::ImageBuilder();
    _iBuilder->setPalette(optris::eIron);
    _iBuilder->setPaletteScalingMethod(optris::eMinMax);
    _iBuilder->setManualTemperatureRange(15.0f, 40.0f);

    _bufferT      = new unsigned short[_imager->getWidth()    * _imager->getHeight()];
    _bufferRaw    = new unsigned char[ _imager->getWidth()    * _imager->getHeight()* 2];

    _imager->setAutoFlag(true);
    _imager->setFrameCallback(callbackImager);

    _image[BankA].create(      _imager->getHeight(), _imager->getWidth(), CV_8UC3);
    _image[BankB].create(      _imager->getHeight(), _imager->getWidth(), CV_8UC3);
    _temperature[BankA].create(_imager->getHeight(), _imager->getWidth(),    CV_16UC1);
    _temperature[BankB].create(_imager->getHeight(), _imager->getWidth(),    CV_16UC1);



    this->start();
}

ThermoCamThread::~ThermoCamThread(void)
{
    delete [] _bufferShow; _bufferShow = NULL;
    delete _iBuilder;      _iBuilder   = NULL;

    delete    _imager;
    delete [] _bufferRaw;
}

void ThermoCamThread::run(void)
{
    if (!_imager ||  !_bufferRaw) {
        qDebug() << __PRETTY_FUNCTION__;
        qDebug() << "Can't start thread!";
        return;
    }

    QTimer timer;
    this->connect(&timer, SIGNAL(timeout()), this, SLOT(grab()), Qt::DirectConnection);

    timer.start(10);
    this->exec();
    timer.stop();
}

void ThermoCamThread::grab(void)
{
    _imager->getFrame(_bufferRaw);
    _imager->process( _bufferRaw);
    _imager->releaseFrame();

    this->copyToImage();
}

void ThermoCamThread::copyToImage(void)
{
    unsigned char* data = _bufferShow;
    BufferBank bank;

    _mutex.lock();

    if (_bank == BankA) bank = BankB;
    else                bank = BankA;

    unsigned char* dataMat = _image[bank].data;
    const int sizeMat      = _image[bank].rows * _image[bank].cols * 3;

    for (int i = 0; i < sizeMat; ++i)
        *dataMat++ = *data++;

    cv::cvtColor(_image[bank], _image[bank], CV_BGR2RGB);

    const unsigned short* dataBufferT = _bufferT;

    for (int row = 0; row < _temperature[bank].rows; row++){
        uint16_t* dataTemperature = reinterpret_cast<uint16_t*>(_temperature[bank].ptr(row));

        for (int col = 0; col < _temperature[bank].cols; col++){
            *dataTemperature++ = *dataBufferT++;
        }
    }

    _mutex.unlock();
}

void ThermoCamThread::setAutoScale(const bool state)
{
   qDebug() << __PRETTY_FUNCTION__ << ": not implemented";
}

void ThermoCamThread::setTemperatureRange(const float min, const float max)
{
    _iBuilder->setManualTemperatureRange(min, max);
}

void ThermoCamThread::switchBank(void)
{
    _mutex.lock();
    this->switching();
    _mutex.unlock();
}

void ThermoCamThread::switching(void)
{
    if (_bank == BankA) _bank = BankB;
    else                _bank = BankA;

}
