#include "cvtoqt.h"

CvToQt::CvToQt(QObject *parent) : QObject(parent)
{

}

QImage CvToQt::MatToQImage(const cv::Mat &mat, bool isGray)
{
    if(!mat.empty()){
        // GrayScale Image
        if(isGray){
            return QImage(
                     mat.data,
                     mat.cols,
                     mat.rows,
                     mat.step,
                     QImage::Format_Grayscale8);
        }
        // Colored Image
        return QImage(
                 mat.data,
                 mat.cols,
                 mat.rows,
                 mat.step,
                 QImage::Format_RGB888).rgbSwapped(); //Swapped : BGR(cv) to RGB(Qt)
    }
    return QImage();
}

// 18-06/2018 01:35
QPixmap CvToQt::MatToQPixmap(const cv::Mat &mat, bool isGray)
{
    return QPixmap::fromImage(CvToQt::MatToQImage(mat,isGray));
}
