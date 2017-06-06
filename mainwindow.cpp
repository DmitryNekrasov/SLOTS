#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>

#include "videostream.h"
#include "videostreamfromcamera.h"
#include "videostreamfromimagesequence.h"
#include "videostreamfromvideofile.h"

static const std::string g_PathVideo = "/Users/ScanNorOne/Desktop/TrackingSamples/The_Rolling_Stones.mp4";
static const std::string g_PathImages = "/Users/ScanNorOne/Desktop/TrackingSamples/Dataset/Bolt/Bolt/img";

static void foo() {
    std::unique_ptr<VideoStream> video_stream = std::make_unique<VideoStreamFromImageSequence>(g_PathImages);
    while (video_stream->hasNext()) {
        auto frame = video_stream->nextFrame();
        cv::imshow("video", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    foo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
