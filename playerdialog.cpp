#include "playerdialog.h"
#include "ui_playerdialog.h"

#include <QDebug>
#include <QPainter>

#include <videostreamfromimagesequence.h>

static const int START_VIDEO_GAP_X = 127;
static const int START_VIDEO_GAP_Y = 23;
static const int SLIDER_RIGHT_GAP = 5;

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
    if (m_Image.data_ptr() != NULL) {
        painter.drawImage(START_VIDEO_GAP_X, START_VIDEO_GAP_Y, m_Image);
    }
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
