#include "playerdialog.h"
#include "ui_playerdialog.h"

#include <cstdlib>

#include <QDebug>
#include <QPainter>

#include <videostreamfromimagesequence.h>

static const int START_VIDEO_GAP_X = 127;
static const int START_VIDEO_GAP_Y = 23;
static const int SLIDER_RIGHT_GAP = 5;

static bool g_IsPressed = false;

PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);
}

PlayerDialog::PlayerDialog(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog),
    m_Path(path),
    m_Image(NULL),
    m_VideoOnStart(true)
{
    ui->setupUi(this);

    m_Rects.clear();

    connect(this, SIGNAL(repaintSignal()), this, SLOT(repaint()));

    refreshTracker();

    setFixedWidth(START_VIDEO_GAP_X + m_Image.width());
    ui->horizontalSlider->setMinimumWidth(m_Image.width() - SLIDER_RIGHT_GAP);

    m_Timer = new QTimer();
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(mainExec()));
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::mainExec() {
    if (!m_SLTracker->isFinished()) {
        m_SLTracker->update();
        m_Image = m_SLTracker->getFrameAsQImage();
        repaintSignal();
        ui->horizontalSlider->setSliderPosition(int(m_SLTracker->getPercentageOfVideo()));
    } else {
        m_Timer->stop();
        ui->playButton->setText("▶");
        ui->playButton->setEnabled(false);
    }
}

void PlayerDialog::on_playButton_clicked() {
    if (m_VideoOnStart) {
        m_VideoOnStart = false;

        auto rois = convertRectsToRois();

        m_SLTracker->setRois(rois);
    }

    if (m_Timer->isActive()) {
        m_Timer->stop();
        ui->playButton->setText("▶");
    } else {
        m_Timer->start();
        ui->playButton->setText("❚❚");
    }
}

std::vector<cv::Rect2d> PlayerDialog::convertRectsToRois() {
    std::vector<cv::Rect2d> rois;
    for (auto&& rect : m_Rects) {
        cv::Rect2d roi(rect);
        roi.x = rect.x - START_VIDEO_GAP_X;
        roi.y = rect.y - START_VIDEO_GAP_Y;
        if (rect.width < 0) {
            roi.x = roi.x + rect.width;
            roi.width = -rect.width;
        }
        if (rect.height < 0) {
            roi.y = roi.y + rect.height;
            roi.height = -rect.height;
        }
        rois.push_back(roi);
    }
    return rois;
}

void PlayerDialog::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QColor("#ff0000"), 3);
    painter.setPen(pen);

    if (m_Image.data_ptr() != NULL) {
        painter.drawImage(START_VIDEO_GAP_X, START_VIDEO_GAP_Y, m_Image);
    }

    if (g_IsPressed) {
        for (auto&& rect : m_Rects) {
            painter.drawRect(rect.x, rect.y, rect.width, rect.height);
        }
    }
}

void PlayerDialog::mousePressEvent(QMouseEvent* ev) {
    if (m_VideoOnStart) {
        m_Rects.emplace_back(ev->x(), ev->y(), 0, 0);
        g_IsPressed = true;
    }
}

void PlayerDialog::mouseReleaseEvent(QMouseEvent*) {
    if (m_VideoOnStart) {
        g_IsPressed = false;
    }
}

void PlayerDialog::mouseMoveEvent(QMouseEvent* ev) {
    if (m_VideoOnStart && g_IsPressed) {
        auto& rect = m_Rects.back();
        rect.width = ev->x() - rect.x;
        rect.height = ev->y()- rect.y;
        repaintSignal();
    }
}

void PlayerDialog::on_stopButton_clicked() {
    m_VideoOnStart = true;
    m_Rects.clear();
    refreshTracker();
    m_Timer->stop();
    ui->playButton->setText("▶");
    ui->playButton->setEnabled(true);
}

void PlayerDialog::refreshTracker() {
    m_SLTracker = std::make_unique<SLTracker>(std::make_unique<VideoStreamFromImageSequence>(m_Path.toUtf8().constData()));
    mainExec();
}
