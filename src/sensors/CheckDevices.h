/*
 * CheckDevices.h
 *
 *  Created on: 04.05.2015
 *      Author: chris
 */

#ifndef SRC_SENSORS_CHECKDEVICES_H_
#define SRC_SENSORS_CHECKDEVICES_H_

#include <vector>

/**
 * @class   CheckDevices
 * @author  Christian Pfitzner
 * @date    2015-05-04
 *
 * @brief   Class to check for connected devices
 */
class CheckDevices
{
public:
   // GETTERS
   /**
    * Function to get all video devices in form "/dev/videoX" while x is returned as std vector
    * @return
    */
   std::vector<unsigned int> getVideoDevices(void) const { return _videoDevices; }

   // PROCESSING
   /**
    * Function to check for all devices connected to pc
    */
   void check(void);
   /**
    * Function to check if device is available
    * @param videoX
    * @return
    */
   bool deviceAvailable(const unsigned int& videoX);

private:
   std::vector<unsigned int> _videoDevices;
};

#endif /* SRC_SENSORS_CHECKDEVICES_H_ */
