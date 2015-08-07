/*
 * ReadFromFile.h
 *
 *  Created on: 07.08.2015
 *      Author: chris
 */

#ifndef SRC_SENSORS_READFROMFILE_H_
#define SRC_SENSORS_READFROMFILE_H_

#include "ISensor.h"

/**
 * @class   ReadFromFile
 * @author  Christian Pfitzner
 * @date    2015-08-07
 *
 * @brief   Class to read images from folder
 */
class ReadFromFile : public ISensor
{
public:
   /**
    * Default constructor
    * @param folder_path
    * @param prefix
    */
   ReadFromFile(const char* folder_path, const char* prefix = "");
   /**
    * Default virtual destructor
    */
   virtual ~ReadFromFile(void);
   /**
    * Grabbing function to acquire new image
    */
   virtual void grab(void);

   // GETTERS
   /**
    * Abstract method to get calibration image
    * @return
    */
   virtual const cv::Mat& getCalibrationImage(void)   { return _bin[_current_index];   }
   /**
    * Abstract method to get image for visualization
    * @return
    */
   virtual const cv::Mat& getVisualizationImage(void) { return _image[_current_index]; }

private:
   unsigned int             _current_index;

   std::vector<cv::Mat>     _image;
   std::vector<cv::Mat>     _bin;

   QString                  _folder_path;
   QString                  _file_prefix;
};

#endif /* SRC_SENSORS_READFROMFILE_H_ */
