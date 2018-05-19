# QtOpencvHistograms

Hi :) `QtCvHistogram` class is a simple *class* for calculing normal **`histograms`** & **`cumulative histograms`**
for both *`RGB or BGR`* images and for *`grayscale`* images, using Qt for displaying the result in **`QPixmap`**.

### Explications :

the `QtCvHistogram` class, has two *static* methods
first method has two arguments : **`input mat`** and **`boolean`** for cumulative or normal histogram,
this function return **`QVector<cv::Mat>`**, this vector has **3 elements** for colored images or **one** for gray image:
```cpp
QVector<cv::Mat> hist =  QtCvHistogram::calculation(input, isCumulative);
```

```cpp
	// Load Image
    cv::Mat im = cv::imread("image.jpg");

    // List or Vector for calculing Histograms
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
```