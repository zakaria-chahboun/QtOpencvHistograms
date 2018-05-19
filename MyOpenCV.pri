# OpenCV Path : My Variable : ZAKI
OPENCV_PATH = C:/Qt/OpenCV3.2.0vc14/mybuild/install

INCLUDEPATH += $$OPENCV_PATH/include

LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_core320.dll
LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_imgcodecs320.dll
LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_imgproc320.dll
#LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_highgui320.dll
#LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_features2d320.dll
#LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_calib3d320.dll

#** Fore Video Capture
#LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_videoio320.dll

#** Fore Object (face detecting ..)
#LIBS += $$OPENCV_PATH/x86/mingw/bin/libopencv_objdetect320.dll
