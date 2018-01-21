

QT += core gui
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../defaults.pri)
# Use C++ 14
CONFIG += c++14
TEMPLATE = app

CONFIG += console # Print console output in external console

SOURCES +=  main.cpp \
    imageprocess/camera.cpp \
    actual_values_model.cpp \
    table_model_base.cpp \
    parameter_model.cpp \
    main_window.cpp \
    tracking_color.cpp \
    camera_view_painter.cpp \
    imageprocess/extract_color.cpp \
    qt_util.cpp


HEADERS  += \
    qt_util.h \
    imageprocess/camera.h \
    opencv_utils.h \
    actual_values_model.h \
    table_model_base.h \
    parameter_model.h \
    tracking_color.h \
    camera_view_painter.h \
    main_window.h \
    imageprocess/extract_color.h \
    time_levels.h


FORMS    += \
    main_window.ui

LIBS += -L$$OUT_PWD/../src/lib/ -lFollowMeFlie

INCLUDEPATH += $$PWD/../build/src/lib
DEPENDPATH += $$PWD/../build/src/lib

# Include opencv 3.2.0
opencv_path =     "E:\Code\lib\opencv-3.2.0-build"
INCLUDEPATH += $${opencv_path}/install/include
LIBS += $${opencv_path}/bin/libopencv_calib3d320.dll
LIBS += $${opencv_path}/bin/libopencv_core320.dll
LIBS += $${opencv_path}/bin/libopencv_features2d320.dll
LIBS += $${opencv_path}/bin/libopencv_flann320.dll
LIBS += $${opencv_path}/bin/libopencv_highgui320.dll
LIBS += $${opencv_path}/bin/libopencv_imgcodecs320.dll
LIBS += $${opencv_path}/bin/libopencv_imgproc320.dll
LIBS += $${opencv_path}/bin/libopencv_ml320.dll
LIBS += $${opencv_path}/bin/libopencv_objdetect320.dll
LIBS += $${opencv_path}/bin/libopencv_photo320.dll
LIBS += $${opencv_path}/bin/libopencv_shape320.dll
LIBS += $${opencv_path}/bin/libopencv_stitching320.dll
LIBS += $${opencv_path}/bin/libopencv_superres320.dll
LIBS += $${opencv_path}/bin/libopencv_video320.dll
LIBS += $${opencv_path}/bin/libopencv_videoio320.dll
LIBS += $${opencv_path}/bin/libopencv_videostab320.dll
