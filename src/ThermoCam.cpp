#include "ThermoCam.h"
#include "ThermoCamThread.h"

#include <QDebug>

ThermoCam::ThermoCam(const char* configFile)
    : _cam(new ThermoCamThread(configFile)),
      _image(0)
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
       qDebug() << "[" << __PRETTY_FUNCTION__ << "]: camera not available";
       exit(1);
       return;
    }
    _cam->switchBank();
    _image       = _cam->image();
    _temperature = _cam->temperature();
}
