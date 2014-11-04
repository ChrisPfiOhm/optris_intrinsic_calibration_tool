#ifndef __OPEN_CV_LABEL__
#define __OPEN_CV_LABEL__

// qt includes
#include <QWidget>
#include <QMutex>

// opencv includes
#include <opencv2/core/core.hpp>

class QImage;

/**
 * @class   OpenCvWidget
 * @author  Christian Merkl
 * @date    2014-11-03
 */
class OpenCvWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor
     * @param parent
     */
    OpenCvWidget(QWidget* parent = 0) : QWidget(parent), _image(0) { }
    /**
     * Default destructor
     */
    virtual ~OpenCvWidget(void);

    /**
     * Function to get height for widght for constrained aspect ratio
     * @param w
     * @return
     */
    virtual int heightForWidth ( int w ) const { return _image->height()/_image->width();};

    /**
     * Function to set resized size of image
     * @param s
     */
    void setSize(QSize s);

public slots:
   /**
    * Function to set image via matrix
    */
    void setMat(const cv::Mat& mat);

protected:
    /**
     * Overloaded qt paint event
     * @param event
     */
    void paintEvent(QPaintEvent* event);

private:
    void resizeImage(void);


    QImage* _image;
    QMutex  _mutex;
    cv::Mat _mat;
    QSize   _scaledSize;
};

#endif
