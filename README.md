### QtOpenCvHistograms Easy
###### ZAKARIA CHAHBOUN
###### OPENCV 3

------------

*QtOpenCvHistogram* is a C++ class for make a beautiful histograms without complication!

Using **Qt5 framework** and **OpenCv 3.x**.

And of course for both histograms type : **Cumulative** & **Normal**.

> You can put a **colored** (BGR/RGB) or a **grayscale** image! :+1:
* Requirement: 
```Cpp
#include <cvtoqt.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
```
> `cvtoqt` class is my class for convert image from OpenCv to QImage or QPixmap :wink:

---------------

The QtCvHistogram class - has **two static** methods:
```Cpp
static QVector<cv::Mat> calculation(cv::Mat im1, bool cumul = false);
static QVector<QPixmap> draw(QVector<cv::Mat> hist, QSize imSize = QSize(512,400), bool fill=true, QColor backColor = QColor(255,255,255));
```
#### Explanation:

- First static method for **Calculing** the histogram image:
  - Parameter 1: The input image.
  - Parameter 2: (Optional) is Cumulative or Not?.
  - Return a `QVector` of `cv::Mat`.

- Second static method for **Drawing** the histogram image:
  - Parameter 1: The Histogram vector from *Calculation* function.
  - Parameter 2: (Optional) Size of output image(s)
  - Parameter 3: (Optional) Histogram curve filled or not.
  - Parameter 4: (Optional) Background color.
  - Return a `QVector` of `QPixmap`:
  
> The functions return: **3 objects** for colored image (Three channels R-G-B), or **1 object** for grayscale image.

#### Checking Errors:
If *`calculation`* mathod return a void vector: `calculation(...).size() == 0` it's an error! :no_entry:

### Examples:
```Cpp
    // Load Your Image
    cv::Mat image = cv::imread("/home/zaki/Pictures/05.jpg");
    // Calculate the histograms
    QVector<cv::Mat> calc = QtCvHistogram::calculation(image,true);
    // Get histograms images
    QVector<QPixmap> draw = QtCvHistogram::draw(calc);

    /* Checking Errors */
    if(calc.size() == 0){
      qDebug() << "Error!!";
      return;
    }
    
    /* If a single channel image (Grayscale) */
    if(calc.size() == 1)
      ui->label->setPixmap(draw[0]);
    
    /* If a normal colord image (RBG)*/
    else{
      ui->label->setPixmap(draw[0]); //Red
      ui->label_2->setPixmap(draw[1]); //Blue
      ui->label_3->setPixmap(draw[2]); //Green
      ui->label_4->setPixmap(draw[3]); // All curves in one image :)
      }
```

### ScreenShots:
