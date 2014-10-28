#ifndef __THERMO_CAM__
#define __THERMO_CAM__

#include <opencv2/opencv.hpp>

class ThermoCamThread;
class QByteArray;

#include "ISensor.h"

/**
 * @class   ThermoCam
 * @author  Christian Merkl and Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Class for thermo cam
 */
class ThermoCam   : public ISensor
{
public:
   /**
    * Default costructor
    * @param configFile
    */
    ThermoCam(const char* configFile);
    /**
     * Default destructor
     */
    ~ThermoCam(void);

    // SETTERS
    /**
     * Function to set temperature threshold for binary image
     * @param th
     */
    void setTemperatureThreshold(const float th=30)      { _bin_th = th; }

    // GETTERS
    /**
     * Function to implement pure virtual method from interface to return binary image
     * @return
     */
    virtual const cv::Mat& getCalibrationImage(void)     { return _bin; }
    /**
     * Function to implement pure virtual method from interface to return visualization
     * @return
     */
    virtual const cv::Mat& getVisualizationImage(void)   { return *_image; }

    /**
     * Function to return thermal image
     * @return
     */
    const cv::Mat& image(void) const                     { return *_image; }
    /**
     * Function to return matrix with temperature
     * @return
     */
    const cv::Mat& temperature(void) const               { return *_temperature; }


    // OTHERS
    /**
     * Function to grab image
     */
    virtual void grab(void);

private:
    /**
     * Function to generate binary image
     * @param temperature
     * @return
     */
    cv::Mat generateBin(const cv::Mat temperature);

    ThermoCamThread* _cam;

    float   _bin_th;

    const cv::Mat*   _image;
    const cv::Mat*   _temperature;
    cv::Mat    _bin;
};

#endif
