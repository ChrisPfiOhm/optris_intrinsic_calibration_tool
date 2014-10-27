#include "ConfigDialog.h"
#include "ui_ConfigDialog.h"

#include <QDebug>
#include <QFile>
#include <QGraphicsScene>

#include <QSettings>

ConfigDialog::ConfigDialog(QString path, QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::ConfigDialog)
{

   _ui->setupUi(this);



   if(QFile::exists(path)) this->loadConfig("/home/chris/workspace/optris_intrinsic_calibration_tool/config/pattern.ini");
   else                    qDebug() << __PRETTY_FUNCTION__ << "]: config file not found.";


   this->slot_patternChanged(0);


   connect(_ui->_buttonBox,   SIGNAL(accepted()),                 this, SLOT(slot_accept()));
   connect(_ui->_buttonBox,   SIGNAL(rejected()),                 this, SLOT(reject()));
   connect(_ui->_patternBox,  SIGNAL(currentIndexChanged(int)), this, SLOT(slot_patternChanged(int)));
}


void ConfigDialog::loadConfig(QString path)
{
   _configPath = path;
   if(!path.length()) {
       qDebug() << "[" << __PRETTY_FUNCTION__ << "]: config path not set.";
       return;
   }

   QSettings settings(path, QSettings::NativeFormat);

   _ui->_patternBox->setCurrentIndex(settings.value("pattern").toInt());
   _ui->_spinCols->setValue(         settings.value("cols").toInt());
   _ui->_spinRows->setValue(         settings.value("rows").toInt());
   _ui->_spinDistance->setValue(     settings.value("dist").toInt());
}

void ConfigDialog::saveConfig(QString path)
{
   _configPath = path;
   if(!_configPath.length()) {
       qDebug() << "[" << __PRETTY_FUNCTION__ << "]: config path not set.";
       return;
   }

   QSettings settings(_configPath, QSettings::NativeFormat);
   settings.setValue("pattern",    QString::number(_ui->_patternBox->currentIndex()));
   settings.setValue("cols",       QString::number(_ui->_spinCols->value()));
   settings.setValue("rows",       QString::number(_ui->_spinRows->value()));
   settings.setValue("dist",       QString::number(_ui->_spinDistance->value()));
}


float ConfigDialog::threshold(void) const
{
    return _ui->_spinThreshold->value();
}

unsigned int ConfigDialog::getRows(void)
{
   _rows = static_cast<unsigned int>(_ui->_spinRows->value());
   return _rows;
}

unsigned int ConfigDialog::getCols(void)
{
   _cols = static_cast<unsigned int>(_ui->_spinCols->value());
   return _cols;
}

float ConfigDialog::getPointDistance(void)
{
   _dist = _ui->_spinDistance->value();
   return _dist;
}

void ConfigDialog::slot_patternChanged(int index)
{
   _pattern = Pattern(index);

   if(      index == SymCircles)    _ui->image->setPixmap(QPixmap(":pattern/circles.png"));
   else if (index == AsymCircles)   _ui->image->setPixmap(QPixmap(":pattern/acircles_pattern.png"));
   else if (index == Chessboard)    _ui->image->setPixmap(QPixmap(":pattern/chess_pattern.png"));
}

void ConfigDialog::slot_accept(void)
{
   if(_configPath.length()>0) this->saveConfig(_configPath);
   this->accept();
}
