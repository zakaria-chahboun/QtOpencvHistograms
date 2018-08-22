### QtOpenCvHistograms Easy
###### ZAKARIA CHAHBOUN

<img src='https://raw.githubusercontent.com/zakaria-chahboun/ZakiQtProjects/master/IMAGE1.png' />

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
> If *`calculation`* mathod return a void vector: **`calculation(...).size() == 0 `** it's an error! :no_entry:

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
* Colored Image: Cumulative Histogram and Filled
<img src='./Screenshots/cumul all.png' />

* Colored Image: Normal Histogram and not Filled
<img src='./Screenshots/not cumul all - not fill.PNG' />

* Grayscale Image:
<img src='./Screenshots/gray image - full.PNG' />

* an Other style: Black background!
<img src='./Screenshots/not cumul all.PNG' />

---------------------------
###### ZAKI | ZAKARIA CHAHBOUN
###### 19/05/2018 | 15:11
###### 22/08/2018 | 03:35

Tesed on Windows and Manjaro Linux :heart:

<img src="https://upload.wikimedia.org/wikipedia/fr/thumb/c/c8/Twitter_Bird.svg/1259px-Twitter_Bird.svg.png" width="20px"> <a href="https://twitter.com/Zaki_Chahboun">@Zaki_Chahboun</a>
<br>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c2/F_icon.svg/1024px-F_icon.svg.png" width="20px"> <a href="https://facebook.com/zakaria.chahboun.2018">Zakaria Chahboun</a>
<br>
<img src='https://vignette.wikia.nocookie.net/google/images/d/d3/New_Logo_Gmail.svg.png/revision/latest?cb=20151001044539' width="20px"> Zakaria.Chahboun.1996@Gmail.Com

<img src='https://raw.githubusercontent.com/zakaria-chahboun/ZakiQtProjects/master/IMAGE2.png' />
