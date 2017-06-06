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
    videostreamfromcamera.cpp

HEADERS  += mainwindow.h \
    videostream.h \
    videostreamfromvideofile.h \
    videostreamfromimagesequence.h \
    videostreamfromcamera.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/Cellar/opencv3/3.2.0/include
INCLUDEPATH += /usr/local/Cellar/boost/1.62.0/include

LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_aruco.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgcodecs.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stitching.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_aruco.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgcodecs.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stitching.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_aruco.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgcodecs.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stitching.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bgsegm.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgproc.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_structured_light.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bgsegm.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgproc.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_structured_light.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bgsegm.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_imgproc.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_structured_light.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bioinspired.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_line_descriptor.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_superres.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bioinspired.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_line_descriptor.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_superres.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_bioinspired.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_line_descriptor.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_superres.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_calib3d.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ml.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_surface_matching.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_calib3d.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ml.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_surface_matching.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_calib3d.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ml.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_surface_matching.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ccalib.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_objdetect.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_text.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ccalib.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_objdetect.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_text.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ccalib.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_objdetect.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_text.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_core.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_optflow.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_tracking.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_core.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_optflow.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_tracking.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_core.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_optflow.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_tracking.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_datasets.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_phase_unwrapping.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_video.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_datasets.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_phase_unwrapping.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_video.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_datasets.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_phase_unwrapping.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_video.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dnn.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_photo.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videoio.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dnn.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_photo.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videoio.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dnn.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_photo.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videoio.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dpm.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_plot.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videostab.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dpm.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_plot.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videostab.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_dpm.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_plot.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_videostab.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_face.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_reg.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xfeatures2d.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_face.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_reg.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xfeatures2d.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_face.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_reg.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xfeatures2d.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_features2d.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_rgbd.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ximgproc.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_features2d.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_rgbd.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ximgproc.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_features2d.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_rgbd.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_ximgproc.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_flann.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_saliency.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xobjdetect.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_flann.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_saliency.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xobjdetect.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_flann.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_saliency.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xobjdetect.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_fuzzy.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_shape.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xphoto.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_fuzzy.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_shape.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xphoto.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_fuzzy.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_shape.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_xphoto.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_highgui.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stereo.3.2.0.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_highgui.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stereo.3.2.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_highgui.dylib
LIBS += /usr/local/Cellar/opencv3/3.2.0/lib/libopencv_stereo.dylib

LIBS += /usr/local/Cellar/boost/1.62.0/lib/libboost_filesystem.dylib
LIBS += /usr/local/Cellar/boost/1.62.0/lib/libboost_serialization.dylib
LIBS += /usr/local/Cellar/boost/1.62.0/lib/libboost_system.dylib
