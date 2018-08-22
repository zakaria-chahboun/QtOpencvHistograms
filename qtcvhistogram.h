#ifndef QTCVHISTOGRAM_H
#define QTCVHISTOGRAM_H
#include <QWidget>

// Zakaria Chahboun | 19/05/2018 | 15:11
// Zakaria Chahboun | 22/08/2018 | 03:35

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <cvtoqt.h>
#include <iostream>
#include <QDebug>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class QtCvHistogram : public QWidget
{
    Q_OBJECT
public:
    explicit QtCvHistogram(QWidget *parent = 0);

    enum Decoration {SIMPLE,FILL, BOTH};
    static QVector<cv::Mat> calculation(cv::Mat im1, bool cumul = false);
    static QVector<QPixmap> draw(QVector<cv::Mat> hist, QSize imSize = QSize(512,400), bool fill=true, QColor backColor = QColor(255,255,255));

signals:

public slots:
};

#endif // QTCVHISTOGRAM_H
