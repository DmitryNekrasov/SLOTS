#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <memory>

#include <QDir>
#include <QFileDialog>

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

    setEnableBrowse(false);

//    foo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEnableBrowse(bool value) {
    ui->label_Path->setEnabled(value);
    ui->lineEdit_Path->setEnabled(value);
    ui->pushButton_Open->setEnabled(value);
}

void MainWindow::on_radioButton_Camera_toggled(bool checked) {
    setEnableBrowse(!checked);
}

void MainWindow::on_pushButton_Open_clicked() {
    QString start_path = "/Users/ScanNorOne/Desktop/TrackingSamples";
    QString path;

    if (ui->radioButton_VideoFile->isChecked()) {
        path = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Video File"), start_path));
    } else {
        path = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Image Sequence"), start_path));
    }

    ui->lineEdit_Path->setText(path);
}
