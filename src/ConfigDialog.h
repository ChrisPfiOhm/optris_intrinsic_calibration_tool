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

    ConfigDialog(QWidget* parent = 0);

    void loadConfig(QString path);
    void saveConfig(QString path);

    float threshold(void) const;
    unsigned int rows(void) const;
    unsigned int cols(void) const;
    float pointDistance(void) const;

    // GETTERS
    Pattern getPattern(void) { return _pattern; }

private slots:
    void slot_patternChanged(int index);

private:
    Ui::ConfigDialog* _ui;

    Pattern _pattern;
    QString _configPath;
};

#endif
