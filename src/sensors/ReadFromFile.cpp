/*
 * ReadFromFile.cpp
 *
 *  Created on: 07.08.2015
 *      Author: chris
 */

#include "ReadFromFile.h"


#include <QDir>
#include <QDebug>


ReadFromFile::ReadFromFile(const char*  folder_path, const char* prefix) :
   _current_index(0)
,  _folder_path(folder_path)
, _file_prefix(prefix)
{
   QDir folder(folder_path);

   QStringList filters;
   filters << "*.png";
   QStringList images = folder.entryList(filters);

   // push back images to viz and calibration matrices
   for(unsigned int i=0 ; i<images.size() ; ++i) {
      qDebug() << "loading: " << images[i];
      cv::Mat read = cv::imread(folder_path + images[i].toStdString(), CV_8UC3);
      cv::Mat inverted = cv::Scalar::all(255) - read;
      _bin.push_back(  inverted);
      _image.push_back(read);

   }
}

ReadFromFile::~ReadFromFile()
{


}

void ReadFromFile::grab(void)
{
   if(_current_index < _image.size()-1) _current_index++;
   else                                 _current_index = 0;

}
