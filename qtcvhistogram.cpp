#include "qtcvhistogram.h"

/*
* Zakaria Chahboun 19/05/2018
* Twitter : Zaki_Chahboun
* Facebook : Zakaria.Chahboun.2018
* Gmail : ZakariaChahboun1996@Gmail.com
*/

using namespace cv;

QtCvHistogram::QtCvHistogram(QWidget *parent) : QWidget(parent)
{

}

QVector<cv::Mat> QtCvHistogram::calculation(Mat im1, bool cumul)
{
    // read image :)
    if(im1.empty()){
        qDebug() << "QtCvHistogram : image cannot laod!";
        QVector<cv::Mat> emp;
        return emp;
    }

    /************************** Variables ****************************/
    /*
      if a grayscale image : good, is a signal channel, stored in index = 0;
      if a colored image : separate B,G,R colors in a signel channels,
           [B]index = 0,[G]index = 1, [R]index = 2
    */
    std::vector<Mat> planes;
    split(im1,planes);

    // number of possibles values (bins) [axis = x]: 0 to 255 = 256
    int numbins = 256;
    // we know the colors range [0-255], The last one not countabel
    float range[] ={0,256};
    const float *rangeHist = {range};

    /*
      Where historgram calculation stored,
        if iamge is grayscale (1D), So hist.size() == 1
        if colored image [R,G,B] (1D), So hist.size() == 3
    */
    QVector<Mat> hist;
    QVector<Mat> cumulHist;
    /*************************************************************/

    // Histograms Caluculations ..
    for(int i=0; i<(int)planes.size(); i++){
        hist.insert(i, Mat());
        calcHist(&planes[i], 1, 0, Mat(), hist[i],1,&numbins,&rangeHist);
    }

    delete rangeHist; // good programmer :)

    // check : if cumululative histogram
    if(cumul){
        for(int i=0; i<(int)planes.size(); i++){
            // create cumulative histogram for each channel;
            cumulHist.insert(i,Mat(hist[i].size(),hist[i].type()));
            // init
            cumulHist[i].at<float>(0) = hist[i].at<float>(0);
            // Start Calculation :)
            for(int k = 1; k<numbins; k++)
            cumulHist[i].at<float>(k) = hist[i].at<float>(k) + cumulHist[i].at<float>(k-1);
        }

        // Return Cumulative Histogram
        return cumulHist;
    }

    // Return Normal Histogram
    return hist;
}

QVector<QPixmap> QtCvHistogram::draw(QVector<Mat> hist, QSize imSize, QColor backColor)
{
    // list of output images
    QVector<Mat> drawHist;
    QVector<QPixmap> drawHistQt;

    // images : size & background color
    int W=imSize.width() ,H=imSize.height();
    Scalar bcolor(backColor.blue(),backColor.green(),backColor.red());
    int numbins = 256; // 0 - 255

    // initialize images & nomrmalize histograms
    for(int i=0; i<hist.size(); i++){
        drawHist.insert(i,Mat(H,W,CV_8UC3,bcolor));
        normalize(hist[i],hist[i],0,H,NORM_MINMAX,-1,Mat());
    }

    // Draw Histograms :)
    int binStep= cvRound((float)W/(float)numbins);
    QVector<Scalar> colors;
    Scalar color(25,25,25);// beautiful gray :)
    if(hist.size() == 3){
        colors << Scalar(255,0,0);// blue
        colors << Scalar(0,255,0);// green
        colors << Scalar(0,0,255);// red
    }

    int ss = hist.size();
    for(int i=1; i< numbins; i++){

        for(int k=0; k<ss; k++){
            line(drawHist[k],
            Point(binStep*(i-1), H-cvRound(hist[k].at<float>(i-1))),
            Point( binStep*(i), H-cvRound(hist[k].at<float>(i))),
            ss == 3 ? colors[k] : color,2,LINE_AA);

            rectangle(drawHist[k],
                              Point(binStep*(i-1),H-cvRound(hist[k].at<float>(i-1))),
                              Point(binStep*(i),H),
                              ss == 3 ? colors[k] : color);
        }
    }

    // finally: convert Mat to QPixmap :)
    for(int i=0; i<hist.size(); i++){
        drawHistQt.insert(i,QPixmap::fromImage(CvToQt::MatToQImage(drawHist[i])));
    }

    return drawHistQt;
}
