#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T14:22:01
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLOTS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videostream.cpp \
    videostreamfromvideofile.cpp \
    videostreamfromimagesequence.cpp \
    videostreamfromcamera.cpp \
    playerdialog.cpp \
    trackerrunner.cpp \
    defaultsmarttracker.cpp \
    magicsmarttracker.cpp

HEADERS  += mainwindow.h \
    videostream.h \
    videostreamfromvideofile.h \
    videostreamfromimagesequence.h \
    videostreamfromcamera.h \
    playerdialog.h \
    trackerrunner.h \
    smarttracker.h \
    defaultsmarttracker.h \
    magicsmarttracker.h \
    misc.h

FORMS    += mainwindow.ui \
    playerdialog.ui

INCLUDEPATH += /usr/local/Cellar/opencv3/3.2.0/include \
               /usr/local/Cellar/boost/1.62.0/include

LIBS += -L/usr/local/Cellar/opencv3/3.2.0/lib \
        -lopencv_shape \
        -lopencv_saliency \
        -lopencv_superres \
        -lopencv_rgbd \
        -lopencv_ccalib \
        -lopencv_flann \
        -lopencv_videostab \
        -lopencv_xphoto \
        -lopencv_calib3d \
        -lopencv_structured_light \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_tracking \
        -lopencv_line_descriptor \
        -lopencv_dpm \
        -lopencv_bgsegm \
        -lopencv_xobjdetect \
        -lopencv_stereo \
        -lopencv_videoio \
        -lopencv_dnn \
        -lopencv_plot \
        -lopencv_reg \
        -lopencv_phase_unwrapping \
        -lopencv_xfeatures2d \
        -lopencv_aruco \
        -lopencv_ximgproc \
        -lopencv_features2d \
        -lopencv_fuzzy \
        -lopencv_surface_matching \
        -lopencv_imgcodecs \
        -lopencv_photo \
        -lopencv_stitching \
        -lopencv_ml \
        -lopencv_objdetect \
        -lopencv_datasets \
        -lopencv_bioinspired \
        -lopencv_video \
        -lopencv_core \
        -lopencv_optflow \
        -lopencv_text \
        -lopencv_face \
        -lopencv_tracking

LIBS += -L/usr/local/Cellar/boost/1.62.0/lib \
        -lboost_filesystem \
        -lboost_serialization \
        -lboost_system
