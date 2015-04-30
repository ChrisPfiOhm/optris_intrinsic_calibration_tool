/*
 * ImageListItem.h
 *
 *  Created on: 30.04.2015
 *      Author: chris
 */

#ifndef SRC_IMAGELISTITEM_H_
#define SRC_IMAGELISTITEM_H_

#include <QDebug>
#include <QStandardItem>

class ImageListItem : public QStandardItem
{
public:
   // SETTERS
   void setText(QString text);
   void setChecked(bool checked = true);

   // GETTERS
   QString getText(void);
   bool  isChecked(void);
private:

};

#endif /* SRC_IMAGELISTITEM_H_ */
