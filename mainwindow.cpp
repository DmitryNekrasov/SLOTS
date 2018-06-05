#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <memory>

#include <QDebug>
#include <QDir>
#include <QFileDialog>

#include "videostream.h"
#include "videostreamfromcamera.h"
#include "videostreamfromimagesequence.h"
#include "videostreamfromvideofile.h"

#include <opencv2/tracking/tracking.hpp>

static const std::string g_PathVideo = "/Users/ScanNorOne/Desktop/TrackingSamples/The_Rolling_Stones.mp4";
static const std::string g_PathImages = "/Users/ScanNorOne/Desktop/TrackingSamples/Dataset/Bolt/Bolt/img";

static void foo(std::string path) {
    std::unique_ptr<VideoStream> video_stream = std::make_unique<VideoStreamFromImageSequence>(path);

    cv::Ptr<cv::Tracker> tracker = cv::Tracker::create("KCF");

    auto frame = video_stream->nextFrame();

    cv::Rect2d roi = cv::selectROI("tracker", frame);
    qDebug() << "width: " << roi.width << ", height: " << roi.height << "\n";

    tracker->init(frame, roi);

    qDebug() << "Start the tracking process, press ESC to quit" << "\n";

    while (video_stream->hasNext()) {
        auto next_frame = video_stream->nextFrame();
        tracker->update(next_frame, roi);
        cv::rectangle(next_frame, roi, cv::Scalar(0, 0, 255), 2, 1);

        cv::imshow("tracker", next_frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

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

void MainWindow::on_pushButton_LoadVideoStream_clicked() {
    QString path = ui->lineEdit_Path->text();
    if (ui->radioButton_ImageSequence->isChecked() && path != "") {
        qDebug() << "path: " << path << "\n";
        foo(path.toUtf8().constData());
    }
}
