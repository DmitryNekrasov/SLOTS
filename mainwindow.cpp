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

#include <playerdialog.h>

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
        PlayerDialog *playerDialog = new PlayerDialog(path);
        playerDialog->show();
    }
}
