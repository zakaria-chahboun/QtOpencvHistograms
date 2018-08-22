#include "qtcvhistogram.h"

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

    //delete rangeHist; // good programmer :)

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

QVector<QPixmap> QtCvHistogram::draw(QVector<Mat> hist, QSize imSize,bool fill, QColor backColor)
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
    QVector<Scalar> Fillcolors;
    Scalar color(25,25,25);// beautiful gray :)
    if(hist.size() == 3){
        colors << Scalar(255,0,0);// blue
        colors << Scalar(0,255,0);// green
        colors << Scalar(0,0,255);// red

        Fillcolors << Scalar(231,164,24);// light blue (for fill)
        Fillcolors << Scalar(80,250,88);// light green (for fill)
        Fillcolors << Scalar(121,51,251);// light red (for fill)
    }

    int ss = hist.size();
    Mat AllImages = Mat(H,W,CV_8UC3,bcolor);// Put all hists to one image :)
    for(int i=1; i< numbins; i++){

        for(int k=0; k<ss; k++){
            line(drawHist[k],
            Point(binStep*(i-1), H-cvRound(hist[k].at<float>(i-1))),
            Point( binStep*(i), H-cvRound(hist[k].at<float>(i))),
            ss == 3 ? colors[k] : color,2,LINE_AA);

            line(AllImages,
            Point(binStep*(i-1), H-cvRound(hist[k].at<float>(i-1))),
            Point( binStep*(i), H-cvRound(hist[k].at<float>(i))),
            ss == 3 ? colors[k] : color,2,LINE_AA);

            if(fill){
            rectangle(drawHist[k],Point(binStep*(i-1),
                      H-cvRound(hist[k].at<float>(i-1))),
                      Point( binStep*(i), H),
                      ss == 3 ? Fillcolors[k] : color,1);

            rectangle(AllImages,Point(binStep*(i-1),
                      H-cvRound(hist[k].at<float>(i-1))),
                      Point( binStep*(i), H),
                      ss == 3 ? Fillcolors[k] : color,1);
            }
        }
    }

    // finally: convert Mat to QPixmap :)
    for(int i=0; i<hist.size(); i++){
        drawHistQt.insert(i,QPixmap::fromImage(CvToQt::MatToQImage(drawHist[i])));
    }

    // finally finally step :p (if a normal image == three channels)
    if(hist.size() == 3)
        drawHistQt.insert(3,CvToQt::MatToQPixmap(AllImages));

    return drawHistQt;
}
