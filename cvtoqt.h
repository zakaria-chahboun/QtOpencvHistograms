#ifndef CVTOQT_H
#define CVTOQT_H

#include <QObject>
#include <QImage>
#include <opencv2/imgcodecs.hpp>

/* Zakaria Chahboun 04/04 1:00 */

class CvToQt : public QObject
{
    Q_OBJECT
public:
    explicit CvToQt(QObject *parent = 0);

    // Convert OpenCv(Mat) to Qt(QImage)
    // Static Way :)
    static QImage MatToQImage(const cv::Mat & mat, bool isGray = false);
signals:

public slots:
};

#endif // CVTOQT_H
