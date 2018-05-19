#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qtcvhistogram.h"

/*
 * Zakaria Chahboun 19/05/2018
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat im = cv::imread("image.jpg");
    //cv::cvtColor(im,im,CV_BGR2GRAY);

    QVector<cv::Mat> hist =  QtCvHistogram::calculation(im);
    QVector<QPixmap> draw = QtCvHistogram::draw(hist,QSize(256,200));

    // grayscale image
    if(hist.size() == 1)
    ui->image->setPixmap(draw[0]);

    // colored image
    if(hist.size() == 3){
        ui->blue->setPixmap(draw[0]);
        ui->green->setPixmap(draw[1]);
        ui->red->setPixmap(draw[2]);
    }

    // show original image
    ui->image->setPixmap(QPixmap::fromImage(CvToQt::MatToQImage(im)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
