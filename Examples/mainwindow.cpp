#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qtcvhistogram.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat image = cv::imread("/home/zaki/Pictures/05.jpg");
    auto calc = QtCvHistogram::calculation(image,true);
    auto dist = QtCvHistogram::draw(calc,QSize(500,300),true);

    ui->label->setPixmap(dist[0]);
    ui->label_2->setPixmap(dist[1]);
    ui->label_3->setPixmap(dist[2]);
    ui->label_4->setPixmap(dist[3]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
