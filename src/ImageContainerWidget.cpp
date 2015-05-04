/*
 * ImageContainerWidget.cpp
 *
 *  Created on: 30.04.2015
 *      Author: chris
 */

#include "ImageContainerWidget.h"
#include "../build/ui_ImageContainerWidget.h"

#include <opencv2/opencv.hpp>

#include <QDebug>
#include <QCheckBox>
#include <QDir>
#include <QTableWidgetItem>



ImageContainerWidget::ImageContainerWidget(QWidget* parent) :
   QWidget(parent)
,  _ui(new Ui::ImageContainerWidget)
{
   _ui->setupUi(this);


   QStandardItemModel *model = new QStandardItemModel(this);
   _ui->tableView->setModel(model);

   _ui->tableView->horizontalHeader()->setStretchLastSection(true);
   _ui->tableView->verticalHeader()->hide();
   _ui->tableView->horizontalHeader()->hide();
   _ui->tableView->setShowGrid(false);



}

ImageContainerWidget::~ImageContainerWidget(void)
{

}

void ImageContainerWidget::addImage(const cv::Mat& image)
{
   qDebug() << "saving image";
   // push back image towards container
   _images.push_back(image);

   // save image to file
   QString filename;
   filename = "cali_images/image_" + QString::number(_images.size()) + ".png";
   cv::imwrite(filename.toStdString(), image);


   QStandardItemModel *model = static_cast<QStandardItemModel*>(_ui->tableView->model());

   QStandardItem* item       = new QStandardItem(filename);
   item->setCheckable(true);
   item->setCheckState(Qt::Checked);
   model->setItem(_images.size(), 0, item);

   for(unsigned int i=0 ; i<model->rowCount() ; i++)
   {
      QStandardItem* itemToCheck = model->item(i);
   }

}

unsigned int ImageContainerWidget::getNumbersOfImages(void)
{
   return _images.size();
}

bool ImageContainerWidget::loadImagesFromFolder(QDir dir)
{
   _images.clear();

   // get numbers of images in folder
   QStringList fileslist = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
   unsigned int nrImages = fileslist.size();

   for(unsigned int i=0 ; i<nrImages ; i++) {
      // generate filename
     QString filename;

     // check if file exists

      _images.push_back(cv::imread("filename"));
   }
   return true;
}

