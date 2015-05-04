#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__


// qt includes
#include <QMainWindow>
#include <QTimer>
#include <QByteArray>
#include <QDebug>

// sensor includes
#include "sensors/ISensor.h"
#include "sensors/Openni.h"
#include "sensors/ThermoCam.h"
#include "sensors/RGBCamera.h"

// widget includes
#include "ConfigDialog.h"
#include "OpenCvWidget.h"

#include "IntrinsicCalibration.h"

/**
 * @namespace Ui
 */
namespace Ui {
class MainWindow;
}

/**
 * @class   MainWindow
 * @author  Christian Merkl and Christian Pfitzner
 * @date    2014-10-27
 *
 * @brief   Main window for calibration application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Default constructor
     * @param configFile
     * @param parent
     */
    MainWindow(const char* configFile, QWidget* parent = 0);
    /**
     * Default destructor
     */
    virtual ~MainWindow(void);

private slots:
   /**
    * Timer function
    */
    void tick(void);
    /**
     * Function to call config dialog
     */
    void slot_calibrationSettings(void);

    void slot_stereoCapture(void);

    void slot_reset(void);

private:
    Ui::MainWindow*       _ui;
    QTimer                _timer;

    ISensor*              _sensor1;
    ISensor*              _sensor2;

    IntrinsicCalibration  _intrinsic_sensor1;
    IntrinsicCalibration  _intrinsic_sensor2;

    ConfigDialog*         _dialog;
};

#endif
