#include "ConfigDialog.h"
#include "ui_ConfigDialog.h"

#include <QDebug>
#include <QGraphicsScene>

ConfigDialog::ConfigDialog(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::ConfigDialog)
{
    _ui->setupUi(this);

    this->slot_patternChanged(0);


    connect(_ui->_buttonClose, SIGNAL(clicked()),                this, SLOT(accept()));
    connect(_ui->_patternBox,  SIGNAL(currentIndexChanged(int)), this, SLOT(slot_patternChanged(int)));
}


void ConfigDialog::loadConfig(QString path)
{

}

void ConfigDialog::saveConfig(QString path)
{

}


float ConfigDialog::threshold(void) const
{
    return _ui->_spinThreshold->value();
}

unsigned int ConfigDialog::rows(void) const
{
    return static_cast<unsigned int>(_ui->_spinRows->value());
}

unsigned int ConfigDialog::cols(void) const
{
    return static_cast<unsigned int>(_ui->_spinCols->value());
}

float ConfigDialog::pointDistance(void) const
{
    return _ui->_spinDistance->value();
}

void ConfigDialog::slot_patternChanged(int index)
{
   _pattern = Pattern(index);

   if(      index == SymCircles)    _ui->image->setPixmap(QPixmap(":pattern/circles.png"));
   else if (index == AsymCircles)   _ui->image->setPixmap(QPixmap(":pattern/acircles_pattern.png"));
   else if (index == Chessboard)    _ui->image->setPixmap(QPixmap(":pattern/chess_pattern.png"));
}
