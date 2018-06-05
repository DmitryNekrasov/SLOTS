#include "playerdialog.h"
#include "ui_playerdialog.h"

#include <QDebug>
#include <QPainter>

#include <videostreamfromimagesequence.h>

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

    m_Timer = new QTimer();
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(mainExec()));
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::mainExec() {
    m_SLTracker->update();
}

void PlayerDialog::on_playButton_clicked() {
    qDebug() << "In on_playButton_clicked()" << "\n";
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
    if (m_Image != NULL) {
        painter.drawImage(0, 0, *m_Image);
    }

    qDebug() << "qqq" << "\n";
}
