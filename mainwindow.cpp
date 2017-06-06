#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>

#include "videostream.h"
#include "videostreamfromvideofile.h"

static const std::string g_Path = "c:\\Users\\nekrasov\\Desktop\\The_Rolling_Stones.mp4";

static void foo() {
    std::unique_ptr<VideoStream> video_stream = std::make_unique<VideoStreamFromVideoFile>(g_Path);
    while (video_stream->hasNext()) {
        auto frame = video_stream->nextFrame();
        cv::imshow("video", frame);
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

    foo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
