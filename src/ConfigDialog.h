#ifndef __CONFIG_DIALOG__
#define __CONFIG_DIALOG__

#include <QDialog>

namespace Ui {
class ConfigDialog;
}


/**
 * @class   ConfigDialgo
 * @author  Christian Merkl and Christian Pfitzne r
 */
class ConfigDialog : public QDialog
{
   Q_OBJECT
public:
   enum Pattern{
      SymCircles  = 0,
      AsymCircles = 1,
      Chessboard  = 2
   };

    ConfigDialog(QString path = "", QWidget* parent = 0);

    void loadConfig(QString path);
    void saveConfig(QString path);

    float threshold(void) const;


    // GETTERS
    /**
     * Function to get the set pattern
     * @return
     */
    Pattern getPattern(void) { return _pattern; }
    /**
     * Function to get rows of pattern
     * @return
     */
    unsigned int getRows(void);
    /**
     * Function to get numbers of columns of pattern
     * @return
     */
    unsigned int getCols(void);
    /**
     * Function to get size of pattern in meters
     * @return
     */
    float getPointDistance(void);


private slots:
    void slot_patternChanged(int index);

    void slot_accept(void);

private:
    Ui::ConfigDialog* _ui;

    Pattern       _pattern;
    unsigned int  _cols;
    unsigned int  _rows;
    float         _dist;

    QString    _configPath;
};

#endif
