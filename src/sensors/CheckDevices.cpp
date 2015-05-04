/*
 * CheckDevices.cpp
 *
 *  Created on: 04.05.2015
 *      Author: chris
 */

#include "CheckDevices.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <QString>

#include <iostream>

const unsigned int maxVideoDevices = 10;


void CheckDevices::check(void)
{
   /*
    * check for devices of /dev/videoX
    */
   int fd;
   for(unsigned int i=0 ; i<maxVideoDevices ; i++)
   {
      QString device = "/dev/video" + QString::number(i);

      if((fd = open(device.toStdString().c_str(), O_RDONLY)) == -1){
          std::cout << "cam_info: Can't open device" << device.toStdString().c_str() << std::endl;
          return;
      }
      else {
         _videoDevices.push_back(i);
      }
   }
   return;
}


bool CheckDevices::deviceAvailable(const unsigned int& videoX)
{
   for(unsigned int i=0 ; i<maxVideoDevices ; i++) {
      if(i == videoX) return true;
   }

   return false;
}

