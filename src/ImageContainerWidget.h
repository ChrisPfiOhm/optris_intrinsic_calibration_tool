/*
 * ImageContainerWidget.h
 *
 *  Created on: 30.04.2015
 *      Author: chris
 */

#ifndef SRC_IMAGECONTAINERWIDGET_H_
#define SRC_IMAGECONTAINERWIDGET_H_

// qt includes
#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QDir>

// opencv includes
#include <opencv2/core/core.hpp>


/**
 * @namespace Ui
 */
namespace Ui {
class ImageContainerWidget;
}

/**
 * @class   ImageContainerWidget
 * @author  Christian Pfitzner
 * @date    2015-04-29
 */
class ImageContainerWidget : public QWidget
{
public:
   /**
    * Default constructor
    */
   ImageContainerWidget(QWidget* parent);
   /**
    * Defautl destructor
    */
   virtual ~ImageContainerWidget(void);


   // SETTERS
   /**
    * Function to add Image
    * @param image
    */
   void addImage(const cv::Mat& image);


   void setFolderName(QString folder = QDir::currentPath() + "cali_images") { _folder_path = folder; }

   // GETTERS
   /**
    * Function to get the number of images in the container
    * @return
    */
   unsigned int getNumbersOfImages(void);

   // PROCESSING
   bool loadImagesFromFolder(QDir dir);

private:
   Ui::ImageContainerWidget* _ui;

   QString                   _folder_path;
   QStandardItemModel*       _model;
   std::vector<cv::Mat>      _images;         //!< std vector to collect all images for calibration
};

#endif /* SRC_IMAGECONTAINERWIDGET_H_ */
