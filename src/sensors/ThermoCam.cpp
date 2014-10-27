#include <sensors/ThermoCam.h>
#include <sensors/ThermoCamThread.h>
#include <QDebug>

ThermoCam::ThermoCam(const char* configFile)
    : _cam(new ThermoCamThread(configFile)),
      _bin_th(30.0)
{

}

ThermoCam::~ThermoCam(void)
{
    _cam->quit();
    _cam->wait();
    delete _cam;
}

void ThermoCam::grab(void)
{
   if (!_cam) {
      qDebug() << "[" << __PRETTY_FUNCTION__ << "]: camera not available"; exit(1);
      return;
   }


   _cam->switchBank();
   _image       = _cam->image();
   _temperature = _cam->temperature();

   _bin = this->generateBin(*_temperature);

}


cv::Mat ThermoCam::generateBin(const cv::Mat temperature)
{
   const unsigned short tempMin = static_cast<unsigned short>(_bin_th* 10);

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

   if(tempImage.rows != _bin.rows || tempImage.cols != _bin.cols) {
      _bin = cv::Mat(tempImage.size(), CV_8UC1);
   }

   return(tempImage);

}

