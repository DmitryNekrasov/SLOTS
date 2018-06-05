#include "playerdialog.h"
#include "ui_playerdialog.h"

#include <QDebug>
#include <QPainter>

#include <videostreamfromimagesequence.h>

static const int START_VIDEO_GAP = 130;

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

    m_SLTracker = std::make_unique<SLTracker>(std::make_unique<VideoStreamFromImageSequence>(m_Path.toUtf8().constData()));
    mainExec();

    setFixedWidth(START_VIDEO_GAP + m_Image.width());

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
    } else {
        m_Timer->stop();
        ui->playButton->setText("▶");
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
        painter.drawImage(START_VIDEO_GAP, 0, m_Image);
    }
}
