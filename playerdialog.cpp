#include "playerdialog.h"
#include "ui_playerdialog.h"

#include <cstdlib>

#include <QDebug>
#include <QPainter>

#include <videostreamfromimagesequence.h>

static const int START_VIDEO_GAP_X = 127;
static const int START_VIDEO_GAP_Y = 23;
static const int SLIDER_RIGHT_GAP = 5;

static int g_X, g_Y, g_Width, g_Height;
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
    m_Image(NULL)
{
    ui->setupUi(this);
    qDebug() << m_Path << "\n";

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
    if (m_Timer->isActive()) {
        m_Timer->stop();
        ui->playButton->setText("▶");
    } else {
        m_Timer->start();
        ui->playButton->setText("❚❚");
    }
}

void PlayerDialog::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen pen(QColor("#ff0000"), 3);
    painter.setPen(pen);

    if (m_Image.data_ptr() != NULL) {
        painter.drawImage(START_VIDEO_GAP_X, START_VIDEO_GAP_Y, m_Image);
    }
    if (g_IsPressed) {
        painter.drawRect(g_X, g_Y, g_Width, g_Height);
    }
}

void PlayerDialog::mousePressEvent(QMouseEvent* ev) {
    g_X = ev->x();
    g_Y = ev->y();
    g_IsPressed = true;
}

void PlayerDialog::mouseReleaseEvent(QMouseEvent* ev) {
    g_IsPressed = false;
    int x = g_X - START_VIDEO_GAP_X;
    int y = g_Y - START_VIDEO_GAP_Y;
    if (g_Width < 0) {
        x = x + g_Width;
        g_Width = -g_Width;
    }
    if (g_Height < 0) {
        y = y + g_Height;
        g_Height = -g_Height;
    }
    cv::Rect2d roi(x, y, g_Width, g_Height);
    m_SLTracker->setRoi(roi);
}

void PlayerDialog::mouseMoveEvent(QMouseEvent* ev) {
    if (g_IsPressed) {
        int x = ev->x();
        g_Width = ev->x() - g_X;
        g_Height = ev->y()- g_Y;
        repaintSignal();
    }
}

int normalizeX(int x) {
    return x - START_VIDEO_GAP_X;
}

int normalizeY(int y) {
    return y - START_VIDEO_GAP_Y;
}

void PlayerDialog::on_stopButton_clicked() {
    refreshTracker();
    m_Timer->stop();
    ui->playButton->setText("▶");
    ui->playButton->setEnabled(true);
}

void PlayerDialog::refreshTracker() {
    m_SLTracker = std::make_unique<SLTracker>(std::make_unique<VideoStreamFromImageSequence>(m_Path.toUtf8().constData()));
    mainExec();
}
